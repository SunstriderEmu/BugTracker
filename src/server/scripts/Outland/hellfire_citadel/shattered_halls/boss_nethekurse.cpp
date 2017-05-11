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
SDName: Boss_Grand_Warlock_Nethekurse
SD%Complete: 75
SDComment: encounter not fully completed. missing part where boss kill minions.
SDCategory: Hellfire Citadel, Shattered Halls
EndScriptData */

/* ContentData
boss_grand_warlock_nethekurse
mob_fel_orc_convert
mob_lesser_shadow_fissure
EndContentData */


#include "def_shattered_halls.h"
#include "GameEventMgr.h"

struct Say
{
    int32 id;
};

static Say PeonAttacked[]=
{
    {-1540001},
    {-1540002},
    {-1540003},
    {-1540004},
};
static Say PeonDies[]=
{
    {-1540005},
    {-1540006},
    {-1540007},
    {-1540008},
};

#define SAY_INTRO           -1540000
#define SAY_TAUNT_1         -1540009
#define SAY_TAUNT_2         -1540010
#define SAY_TAUNT_3         -1540011
#define SAY_AGGRO_1         -1540012
#define SAY_AGGRO_2         -1540013
#define SAY_AGGRO_3         -1540014
#define SAY_SLAY_1          -1540015
#define SAY_SLAY_2          -1540016
#define SAY_DIE             -1540017

#define SPELL_DEATH_COIL            30500
#define SPELL_DARK_SPIN             30502                   // core bug spell attack caster :D
#define SPELL_SHADOW_FISSURE        30496                   // Summon the ShadowFissure NPC

#define SPELL_SHADOW_CLEAVE         30495
#define H_SPELL_SHADOW_SLAM         35953

#define SPELL_HEMORRHAGE            30478

#define SPELL_CONSUMPTION           30497
#define SPELL_TEMPORARY_VISUAL      39312                   // this is wrong, a temporary solution. spell consumption already has the purple visual, but doesn't display as it should

struct boss_grand_warlock_nethekurseAI : public ScriptedAI
{
    boss_grand_warlock_nethekurseAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        HeroicMode = me->GetMap()->IsHeroic();
    }

    InstanceScript* pInstance;
    bool HeroicMode;

    bool IntroOnce;
    bool IsIntroEvent;
    bool IsMainEvent;
    bool SpinOnce;
    //bool HasTaunted;
    bool Phase;

    uint32 PeonEngagedCount;
    uint32 PeonKilledCount;

    uint32 IntroEvent_Timer;
    uint32 DeathCoil_Timer;
    uint32 ShadowFissure_Timer;
    uint32 Cleave_Timer;
    
    bool isEventActive()
    {
        const GameEventMgr::ActiveEvents& activeEvents = sGameEventMgr->GetActiveEventList();
        bool active = activeEvents.find(57) != activeEvents.end();

        return active;
    }

    void Reset()
    override {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        IsIntroEvent = false;
        IntroOnce = false;
        IsMainEvent = false;
        //HasTaunted = false;
        SpinOnce = false;
        Phase = false;

        PeonEngagedCount = 0;
        PeonKilledCount = 0;

        IntroEvent_Timer = 90000;                           //how long before getting bored and kills his minions?
        DeathCoil_Timer = 20000;
        ShadowFissure_Timer = 8000;
        Cleave_Timer = 5000;
        
        if (pInstance && pInstance->GetData(DATA_NETHEKURSE_EVENT) != DONE)
            pInstance->SetData(DATA_NETHEKURSE_EVENT, NOT_STARTED);
            
        if (isEventActive())
            me->SetDisplayId(22800);
    }

    void DoYellForPeonEnterCombat()
    {
        if (PeonEngagedCount >= 4)
            return;

        DoScriptText(PeonAttacked[PeonEngagedCount].id, me);
        ++PeonEngagedCount;
    }

    void DoYellForPeonDeath()
    {
        if (PeonKilledCount >= 4)
            return;

        DoScriptText(PeonDies[PeonKilledCount].id, me);
        ++PeonKilledCount;

        if (PeonKilledCount == 4)
        {
            IsIntroEvent = false;
            IsMainEvent = true;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    }

    void DoTauntPeons()
    {
        switch(rand()%3)
        {
            case 0: DoScriptText(SAY_TAUNT_1, me); break;
            case 1: DoScriptText(SAY_TAUNT_2, me); break;
            case 2: DoScriptText(SAY_TAUNT_3, me); break;
        }

        //TODO: kill the peons first
        IsIntroEvent = false;
        PeonEngagedCount = 4;
        PeonKilledCount = 4;
        IsMainEvent = true;
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void AttackStart(Unit* who) override
    {
        if (IsIntroEvent || !IsMainEvent)
            return;

        if (me->Attack(who, true))
        {
            me->AddThreat(who, 0.0f);

            if (Phase) 
                DoStartNoMovement(who);
            else 
                DoStartMovement(who);
        }
    }
    
    void DamageTaken(Unit *pDoneBy, uint32 &damage)
    override {
        // Enforce combat starting
        IsIntroEvent = false;
        IsMainEvent = true;
    }

    void MoveInLineOfSight(Unit *who)
    override {
        if (!me->GetVictim() && me->CanAttack(who) == CAN_ATTACK_RESULT_OK && ( me->IsHostileTo( who )) && who->isInAccessiblePlaceFor(me) )
        {
            if (!IntroOnce && me->IsWithinDistInMap(who, 75))
            {
                DoScriptText(SAY_INTRO, me);
                IntroOnce = true;
                IsIntroEvent = true;

                if (pInstance)
                    pInstance->SetData(DATA_NETHEKURSE_EVENT, IN_PROGRESS);
            }

            if (!me->CanFly() && me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE )
                return;

            if (IsIntroEvent || !IsMainEvent)
                return;

            float attackRadius = me->GetAggroRange(who);
            if (me->IsWithinDistInMap(who, attackRadius) && me->IsWithinLOSInMap(who) )
            {
                //who->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
                AttackStart(who);
            }
        }
    }

    void EnterCombat(Unit *who)
    override {
        DoScriptText(RAND(SAY_AGGRO_1, SAY_AGGRO_2, SAY_AGGRO_3), me);
        if (pInstance)
            pInstance->SetData(DATA_NETHEKURSE_EVENT, IN_PROGRESS);
    }

    void JustSummoned(Creature *summoned)
    override {
        summoned->SetFaction(14);
        summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void KilledUnit(Unit* victim)
    override {
        DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2), me);
    }

    void JustDied(Unit* Killer)
    override {
        DoScriptText(SAY_DIE, me);

        if (pInstance) {
            pInstance->SetData(DATA_NETHEKURSE_EVENT, DONE);
            if (Creature* Executioner = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_EXECUTIONER_GUID)))
                Executioner->SetVisible(true);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if (IsIntroEvent)
        {
            if (!pInstance)
                return;

            if (pInstance->GetData(DATA_NETHEKURSE_EVENT) == IN_PROGRESS)
            {
                if (IntroEvent_Timer < diff)
                {
                    DoTauntPeons();
                }else IntroEvent_Timer -= diff;
            }
        }

        if (!UpdateVictim() )
            return;

        if (!IsMainEvent)
            return;

        if (Phase)
        {
            if (!SpinOnce)
            {
                DoCast(me->GetVictim(),SPELL_DARK_SPIN);
                SpinOnce = true;
            }

            if (Cleave_Timer < diff)
            {
                DoCast(me->GetVictim(), (HeroicMode ? H_SPELL_SHADOW_SLAM : SPELL_SHADOW_CLEAVE));
                Cleave_Timer = 6000+rand()%2500;
            }else Cleave_Timer -= diff;
        }
        else
        {
            if (ShadowFissure_Timer < diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_SHADOW_FISSURE);
                ShadowFissure_Timer = 7500+rand()%7500;
            }else ShadowFissure_Timer -= diff;

            if (DeathCoil_Timer < diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_DEATH_COIL);
                DeathCoil_Timer = 15000+rand()%5000;
            }else DeathCoil_Timer -= diff;

            if (me->GetHealthPct() <= 20)
                Phase = true;

            DoMeleeAttackIfReady();
        }
    }
};

struct mob_fel_orc_convertAI : public ScriptedAI
{
    mob_fel_orc_convertAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }

    InstanceScript* pInstance;
    uint32 Hemorrhage_Timer;

    void Reset()
    override {
        me->SetNoCallAssistance(true);              //we don't want any assistance (WE R HEROZ!)
        Hemorrhage_Timer = 3000;
    }

    void MoveInLineOfSight(Unit *who)
    override {
        return;
    }

    void EnterCombat(Unit* who)
    override {
        if (pInstance)
        {
            if (pInstance->GetData64(DATA_NETHEKURSE_EVENT))
            {
                Creature *pKurse = ObjectAccessor::GetCreature(*me,pInstance->GetData64(DATA_NETHEKURSE_GUID));
                if (pKurse)
                    ((boss_grand_warlock_nethekurseAI*)pKurse->AI())->DoYellForPeonEnterCombat();
            }

            if (pInstance->GetData(DATA_NETHEKURSE_EVENT) == IN_PROGRESS)
                return;
            else pInstance->SetData(DATA_NETHEKURSE_EVENT, IN_PROGRESS);
        }
    }

    void JustDied(Unit* Killer)
    override {
        if (pInstance)
        {
            if (pInstance->GetData64(DATA_NETHEKURSE_GUID))
            {
                Creature *pKurse = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NETHEKURSE_GUID));
                if (pKurse)
                    ((boss_grand_warlock_nethekurseAI*)pKurse->AI())->DoYellForPeonDeath();
            }
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        if (Hemorrhage_Timer < diff)
        {
            DoCast(me->GetVictim(),SPELL_HEMORRHAGE);
            Hemorrhage_Timer = 15000;
        }else Hemorrhage_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

//NOTE: this creature are also summoned by other spells, for different creatures
struct mob_lesser_shadow_fissureAI : public ScriptedAI
{
    mob_lesser_shadow_fissureAI(Creature *c) : ScriptedAI(c) {}

    bool Start;
    uint32 Stop_Timer;

    void Reset()
    override {
        Start = false;
        Stop_Timer = 30000;
    }

    void EnterCombat(Unit* who) override { }

    void MoveInLineOfSight(Unit *who) override { return; }

    void AttackStart(Unit* who) override { return; }

    void UpdateAI(const uint32 diff)
    override {
        if (!Start)
        {
            //triggered spell of consumption does not properly show it's SpellVisual, hack it a bit
            me->CastSpell(me,SPELL_TEMPORARY_VISUAL,true);
            me->CastSpell(me,SPELL_CONSUMPTION,false);
            Start = true;
        }

        if (Stop_Timer < diff)
        {
            me->SetDeathState(JUST_DIED);
            me->SetHealth(0);
            me->CombatStop();
            me->DeleteThreatList();
        }else Stop_Timer -= diff;
    }
};

CreatureAI* GetAI_boss_grand_warlock_nethekurse(Creature* pCreature)
{
    return new boss_grand_warlock_nethekurseAI(pCreature);
}

CreatureAI* GetAI_mob_fel_orc_convert(Creature* pCreature)
{
    return new mob_fel_orc_convertAI(pCreature);
}

CreatureAI* GetAI_mob_lesser_shadow_fissure(Creature* pCreature)
{
    return new mob_lesser_shadow_fissureAI(pCreature);
}

void AddSC_boss_grand_warlock_nethekurse()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="boss_grand_warlock_nethekurse";
    newscript->GetAI = &GetAI_boss_grand_warlock_nethekurse;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="mob_fel_orc_convert";
    newscript->GetAI = &GetAI_mob_fel_orc_convert;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="mob_lesser_shadow_fissure";
    newscript->GetAI = &GetAI_mob_lesser_shadow_fissure;
    sScriptMgr->RegisterOLDScript(newscript);
}

