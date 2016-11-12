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
SDName: Boss_Buru
SD%Complete: 0
SDComment: Place Holder
SDCategory: Ruins of Ahn'Qiraj
EndScriptData */


#include "def_ruins_of_ahnqiraj.h"

enum Yells
{
    EMOTE_TARGET               = -1509002
};

enum Spells
{
    SPELL_EGG_EXPLOSION              = 19593,
    SPELL_SUMMON_HIVE_HATCHALING     = 1881,
    SPELL_BURU_EGG_TRIGGER_EFFECT    = 26646,
    SPELL_CREEPING_PLAGUE            = 20512,
    SPELL_THORNS                     = 25640,
    SPELL_DISMEMBER                  = 96,
    SPELL_BURU_TRANSFORM             = 24721,
    SPELL_GATHERING_SPEED            = 1834,
};

class boss_buru : public CreatureScript
{
public:
    boss_buru() : CreatureScript("boss_buru") {}
    
    class boss_buruAI : public CreatureAI
    {
        public:
        boss_buruAI(Creature* creature) : CreatureAI(creature)
        {
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
        }

        InstanceScript* pInstance;

        uint32 perc;
        uint32 creepingplagueTimer;
        uint32 dismemberTimer;
        uint32 gatheringspeedTimer;
        uint32 phase;
        bool actionDone;

        void Reset()
        override {
            perc = 0;
            phase = 0;
            creepingplagueTimer = 1000;
            dismemberTimer = urand(4000, 10000);
            gatheringspeedTimer = 9000;
            actionDone = false;

            if (pInstance)
            {
                if (pInstance->GetData(DATA_BURU_EVENT) != DONE)
                    pInstance->SetData(DATA_BURU_EVENT, NOT_STARTED);
            }

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void EnterCombat(Unit * /*who*/)
        override {
            if (pInstance)
                pInstance->SetData(DATA_BURU_EVENT, IN_PROGRESS);

            me->CastSpell(me, SPELL_THORNS, false);
        }

        void JustDied(Unit* /*killer*/)
        override {
            if (pInstance)
                pInstance->SetData(DATA_BURU_EVENT, DONE);
        }

        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;

            if (phase == 0)
            {
                if (dismemberTimer <= diff)
                {
                    if (me->GetVictim())
                        me->CastSpell(me->GetVictim(), SPELL_DISMEMBER, false);
                    dismemberTimer = urand(4000, 10000);
                }
                else
                    dismemberTimer -= diff;
            }

            if (gatheringspeedTimer <= diff)
            {
                me->CastSpell(me, SPELL_GATHERING_SPEED, false);
                gatheringspeedTimer = 9000;
            }
            else
                gatheringspeedTimer -= diff;

            perc = (me->GetHealth()*100) / me->GetMaxHealth();
            if (perc <= 20 && !actionDone)
            {
                phase = 1;
                actionDone = true;
                me->CastSpell(me, SPELL_BURU_TRANSFORM, false);
                me->RemoveAurasDueToSpell(SPELL_THORNS);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
            
            if (phase == 1)
            {
                if (creepingplagueTimer <= diff)
                {
                    me->CastSpell(me, SPELL_CREEPING_PLAGUE, false);
                    creepingplagueTimer = urand(8000, 15000);
                }
                else
                    creepingplagueTimer -= diff;
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new boss_buruAI(creature);
    }
};

class buru_egg : public CreatureScript
{
public:
    buru_egg() : CreatureScript("buru_egg") {}
    
    class buru_eggAI : public ScriptedAI
    {
        public:
        buru_eggAI(Creature* creature) : ScriptedAI(creature), Summons(me)
        {
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
            SetCombatMovementAllowed(false);
        }

        InstanceScript* pInstance;
        SummonList Summons;

        void JustSummoned(Creature* summoned)
        override {
            summoned->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM,0, 100.0f, false));
            Summons.Summon(summoned);
        }

        void SummonedCreatureDespawn(Creature* unit)
        override {
            Summons.Despawn(unit);
        }

        void EnterCombat(Unit* who)
        override {
            if (Creature* buru = pInstance->instance->GetCreature(pInstance->GetData64(DATA_BURU)))
                if (!buru->IsInCombat())
                    buru->AI()->AttackStart(who);
        }

        void JustDied(Unit* /*killer*/)
        override {
            me->CastSpell((Unit*)nullptr, SPELL_EGG_EXPLOSION, false);
            me->CastSpell(me, SPELL_SUMMON_HIVE_HATCHALING, false);
            if (Creature* buru = pInstance->instance->GetCreature(pInstance->GetData64(DATA_BURU)))
                buru->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, false));
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new buru_eggAI(creature);
    }
};

class buru_egg_trigger : public CreatureScript
{
public:
    buru_egg_trigger() : CreatureScript("buru_egg_trigger") {}
    
    class buru_egg_triggerAI : public CreatureAI
    {
        public:
        buru_egg_triggerAI(Creature* creature) : CreatureAI(creature) 
        {
            SetCombatMovementAllowed(false);
        }

        uint32 DespawnTimer;

        void Reset()
        override {
            DespawnTimer = 2000;
            me->CastSpell(me, SPELL_BURU_EGG_TRIGGER_EFFECT, false);
        }

        void UpdateAI(const uint32 diff)
        override {
            if (DespawnTimer <= diff)
                me->DisappearAndDie();
            else
                DespawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new buru_egg_triggerAI(creature);
    }
};

void AddSC_boss_buru()
{
    new boss_buru();
    new buru_egg();
    new buru_egg_trigger();
}
