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
SDName: Boss_Anzu
SD%Complete: 80
SDComment:
SDCategory: Auchindoun, Sethekk Halls
EndScriptData */


#include "def_sethekk_halls.h"

enum eAnzu
{
    SPELL_CHARGE            = 22120,
    SPELL_BANISH            = 42354,
    SPELL_PARALYSING        = 40184,
    SPELL_FEATHER_CYCLONE   = 40321,
    SPELL_SPELL_BOMB        = 40303,
    
    CREATURE_BROOD          = 23132
};


struct boss_anzuAI : public ScriptedAI
{
    boss_anzuAI(Creature *c) : ScriptedAI(c), summons(me)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }
    
    InstanceScript *pInstance;
    
    uint32 chargeTimer;
    uint32 paralysingTimer;
    uint32 featherCycloneTimer;
    uint32 spellBombTimer;
    
    bool hasSummoned66;
    bool hasSummoned33;
    
    SummonList summons;
    
    void Reset()
    override {
        if (pInstance && me->IsAlive())
            pInstance->SetData(ANZU_EVENT, NOT_STARTED);
            
        chargeTimer = 9000;
        paralysingTimer = 14000;
        featherCycloneTimer = 5000;
        spellBombTimer = 22000;
        
        hasSummoned66 = false;
        hasSummoned33 = false;
        
        if (me->HasAuraEffect(SPELL_BANISH))
            me->RemoveAurasDueToSpell(SPELL_BANISH);
            
        summons.DespawnAll();
    }
    
    void JustDied(Unit *pKiller)
    override {
        if (pInstance)
            pInstance->SetData(ANZU_EVENT, DONE);
    }
    
    void JustSummoned(Creature* pSummon)
    override {
        summons.Summon(pSummon);
        
        if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
            pSummon->AI()->AttackStart(target);
    }
    
    void SummonedCreatureDespawn(Creature* pSummon) override { summons.Despawn(pSummon); }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!UpdateVictim())
            return;
            
        if (me->HasAuraEffect(SPELL_BANISH))
            return;
            
        if (chargeTimer <= diff) {
            if (rand()%10 < 8) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0, true, true), SPELL_CHARGE);
                chargeTimer = 9000;
            }
        } else chargeTimer -= diff;
        
        if (paralysingTimer <= diff) {
            DoCast(me->GetVictim(), SPELL_PARALYSING);
            paralysingTimer = 26000;
        } else paralysingTimer -= diff;
        
        if (featherCycloneTimer <= diff) {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0, true, true), SPELL_FEATHER_CYCLONE);
            featherCycloneTimer = 21000;
        } else featherCycloneTimer -= diff;
        
        if (spellBombTimer <= diff) {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_SPELL_BOMB);
            spellBombTimer = 30000;
        } else spellBombTimer -= diff;
        
        if (me->GetHealth() < me->GetMaxHealth()*0.66 && !hasSummoned66) {
            me->InterruptNonMeleeSpells(true);
            DoCast(me, SPELL_BANISH, true);
            int count;
            for (count = 0; count < 5; count++)
                me->SummonCreature(CREATURE_BROOD, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 90000);
            hasSummoned66 = true;
        }
        
        if (me->GetHealth() < me->GetMaxHealth()*0.33 && !hasSummoned33) {
            me->InterruptNonMeleeSpells(true);
            DoCast(me, SPELL_BANISH, true);
            int count;
            for (count = 0; count < 5; count++)
                me->SummonCreature(CREATURE_BROOD, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 90000);
            hasSummoned33 = true;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_anzu(Creature *pCreature)
{
    return new boss_anzuAI(pCreature);
}

void AddSC_boss_anzu()
{
    OLDScript *newscript;
    
    newscript = new OLDScript;
    newscript->Name = "boss_anzu";
    newscript->GetAI = &GetAI_boss_anzu;
    sScriptMgr->RegisterOLDScript(newscript);
}
