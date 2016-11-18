/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Boss_Warlord_Kalithres
SD%Complete: 65
SDComment: Contains workarounds regarding warlord's rage spells not acting as expected. Both scripts here require review and fine tuning.
SDCategory: Coilfang Resevoir, The Steamvault
EndScriptData */


#include "def_steam_vault.h"
#include "Object.h"

#define SAY_INTRO                   -1545016
#define SAY_REGEN                   -1545017
#define SAY_AGGRO1                  -1545018
#define SAY_AGGRO2                  -1545019
#define SAY_AGGRO3                  -1545020
#define SAY_SLAY1                   -1545021
#define SAY_SLAY2                   -1545022
#define SAY_DEATH                   -1545023

#define SPELL_SPELL_REFLECTION      31534
#define SPELL_IMPALE                39061
#define SPELL_WARLORDS_RAGE         37081
#define SPELL_WARLORDS_RAGE_NAGA    31543

#define SPELL_WARLORDS_RAGE_PROC    36453

#define CREATURE_KALITHRESH 17798
#define CREATURE_DISTILLER 17954

struct mob_naga_distillerAI : public ScriptedAI
{
    mob_naga_distillerAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        SetCombatMovementAllowed(false);
    }

    InstanceScript *pInstance;
    bool checkDistance;
    uint32 checkDistanceTimer;

    void Reset()
    override {
        checkDistance = false;
        checkDistanceTimer = 500;
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        //hack, due to really weird spell behaviour :(
        if (pInstance)
        {
            if (pInstance->GetData(TYPE_DISTILLER) == IN_PROGRESS)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
        }
    }

    void EnterCombat(Unit *who) override { }

    void StartRageGen(Unit *caster)
    {
        checkDistance = true;
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    override {
        if (me->GetHealth() <= damage)
            if (pInstance)
                pInstance->SetData(TYPE_DISTILLER,DONE);
    }

    void UpdateAI(const uint32 diff)
    override {
        if (checkDistance)
        {
            if(checkDistanceTimer <= diff)
            {
                if(Creature* boss = pInstance->instance->GetCreature(pInstance->GetData64(DATA_KALITRESH)))
                {
                    if(me->GetDistance(boss) < 5.0f)
                    {
                        boss->GetMotionMaster()->Clear();
                        boss->GetMotionMaster()->MoveChase(boss->GetVictim(), 0.0f, 0.0f);
                        checkDistance = false;

                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                        DoCast(boss, SPELL_WARLORDS_RAGE_NAGA, true);

                        DoScriptText(SAY_REGEN, boss);
                        boss->CastSpell(boss, SPELL_WARLORDS_RAGE, true);

                        if (pInstance)
                            pInstance->SetData(TYPE_DISTILLER, IN_PROGRESS);
                    }
                }
                
                checkDistanceTimer = 500;
            } else checkDistanceTimer -= diff;
        }
    }
};

struct boss_warlord_kalithreshAI : public ScriptedAI
{
    boss_warlord_kalithreshAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }

    InstanceScript *pInstance;

    uint32 Reflection_Timer;
    uint32 Impale_Timer;
    uint32 Rage_Timer;
    bool CanRage;

    void Reset()
    override {
        Reflection_Timer = 10000;
        Impale_Timer = 7000+rand()%7000;
        Rage_Timer = 45000;
        CanRage = false;

        if (pInstance)
            pInstance->SetData(TYPE_WARLORD_KALITHRESH, NOT_STARTED);
    }

    void EnterCombat(Unit *who)
    override {
        switch(rand()%3)
        {
            case 0: DoScriptText(SAY_AGGRO1, me); break;
            case 1: DoScriptText(SAY_AGGRO2, me); break;
            case 2: DoScriptText(SAY_AGGRO3, me); break;
        }

        if (pInstance)
            pInstance->SetData(TYPE_WARLORD_KALITHRESH, IN_PROGRESS);
    }

    void KilledUnit(Unit* victim)
    override {
        switch(rand()%2)
        {
            case 0: DoScriptText(SAY_SLAY1, me); break;
            case 1: DoScriptText(SAY_SLAY2, me); break;
        }
    }

    void SpellHit(Unit *caster, const SpellInfo *spell)
    override {
        //hack :(
        if (spell->Id == SPELL_WARLORDS_RAGE_PROC)
            if (pInstance)
                if (pInstance->GetData(TYPE_DISTILLER) == DONE)
                    me->RemoveAurasDueToSpell(SPELL_WARLORDS_RAGE_PROC);
    }

    void JustDied(Unit* Killer)
    override {
        DoScriptText(SAY_DEATH, me);

        if (pInstance)
            pInstance->SetData(TYPE_WARLORD_KALITHRESH, DONE);
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim() )
            return;

        if (Rage_Timer < diff)
        {
            if (Aura* aur = me->GetAura(36453, 0))
            {
                if (aur->GetStackAmount() < 10)
                {
                    Creature* distiller = me->FindNearestCreature(CREATURE_DISTILLER, 100.0f);
                    if (distiller)
                    {
                        me->GetMotionMaster()->MovePoint(0, distiller->GetPositionX(), distiller->GetPositionY(), distiller->GetPositionZ());
                        ((mob_naga_distillerAI*)distiller->AI())->StartRageGen(me);
                    }
                }
            }
            else
            {
                Creature* distiller = me->FindNearestCreature(CREATURE_DISTILLER, 100.0f);
                if (distiller)
                {
                    me->GetMotionMaster()->MovePoint(0, distiller->GetPositionX(), distiller->GetPositionY(), distiller->GetPositionZ());
                    ((mob_naga_distillerAI*)distiller->AI())->StartRageGen(me);
                }
            }
            Rage_Timer = urand(22000, 25000);
        }else Rage_Timer -= diff;

        //Reflection_Timer
        if (Reflection_Timer < diff)
        {
            DoCast(me, SPELL_SPELL_REFLECTION);
            Reflection_Timer = 15000+rand()%10000;
        }else Reflection_Timer -= diff;

        //Impale_Timer
        if (Impale_Timer < diff)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                DoCast(target,SPELL_IMPALE);

            Impale_Timer = 7500+rand()%5000;
        }else Impale_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_naga_distiller(Creature *_Creature)
{
    return new mob_naga_distillerAI (_Creature);
}

CreatureAI* GetAI_boss_warlord_kalithresh(Creature *_Creature)
{
    return new boss_warlord_kalithreshAI (_Creature);
}

void AddSC_boss_warlord_kalithresh()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="mob_naga_distiller";
    newscript->GetAI = &GetAI_mob_naga_distiller;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="boss_warlord_kalithresh";
    newscript->GetAI = &GetAI_boss_warlord_kalithresh;
    sScriptMgr->RegisterOLDScript(newscript);
}

