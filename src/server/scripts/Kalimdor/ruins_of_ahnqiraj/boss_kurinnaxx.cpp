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
SDName: Boss_Kurinnaxx
SD%Complete: 100
SDComment: VERIFY SCRIPT AND SQL
SDCategory: Ruins of Ahn'Qiraj
EndScriptData */


#include "def_ruins_of_ahnqiraj.h"

enum Spells
{
    SPELL_ENRAGE                 = 28798,
    SPELL_MORTAL_WOUND           = 25646,
    SPELL_SANDTRAP               = 25648,
    SPELL_SANDTRAP_DAMAGE        = 25656,
    SPELL_WIDE_SLASH             = 25814,
    SPELL_SUMMON_PLAYER          = 26446,
    SPELL_TRASH                  =  3391
};

enum Events
{
    EV_MORTAL_WOUND = 1,
    EV_SANDTRAP,
    EV_WIDE_SLASH ,
    EV_SUMMON_PLAYER ,
    EV_TRASH,
};

class Boss_kurinaxx : public CreatureScript
{
public:
    Boss_kurinaxx() : CreatureScript("boss_kurinaxx_new") {}

    CreatureAI* GetAI(Creature* creature) const
        override {
        return new Boss_kurinaxx_newAI(creature);
    }

    class Boss_kurinaxx_newAI : public CreatureAI
    {
    public:
        Boss_kurinaxx_newAI(Creature* creature) : CreatureAI(creature)
        {
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
        }
        
        EventMap events;

        void Reset()
        override {
            events.RescheduleEvent(EV_MORTAL_WOUND, urand(2000, 7000));
            events.RescheduleEvent(EV_SANDTRAP, urand(10000, 15000));
            events.RescheduleEvent(EV_WIDE_SLASH, urand(10000, 15000));
            events.RescheduleEvent(EV_TRASH, urand(20000, 25000));
            events.RescheduleEvent(EV_SUMMON_PLAYER, urand(30000, 40000));
            
            enraged = false;
            
            if (pInstance)
                pInstance->SetData(DATA_KURINNAXX_EVENT, NOT_STARTED);
        }
        
        void JustDied(Unit* /*pKiller*/)
        override {
            if (pInstance)
                pInstance->SetData(DATA_KURINNAXX_EVENT, DONE);
        }
        
        void JustEngagedWith(Unit* who)
        override {
            if (pInstance)
                pInstance->SetData(DATA_KURINNAXX_EVENT, IN_PROGRESS);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            
            if (me->IsBelowHPPercent(30.0f) && !enraged) {
                me->CastSpell(me, SPELL_ENRAGE, TRIGGERED_FULL_MASK);
                enraged = true;
            }

            while (uint32 eventId = events.ExecuteEvent())
                switch (eventId)
                {
                case EV_MORTAL_WOUND:
                    me->CastSpell(me->GetVictim(), SPELL_MORTAL_WOUND);
                    events.RescheduleEvent(EV_MORTAL_WOUND, 2000, 7000);
                    break;
                case EV_SANDTRAP:
                    me->CastSpell(SelectTarget(SELECT_TARGET_RANDOM, 3, 200.0f, true), SPELL_SANDTRAP, TRIGGERED_FULL_MASK);
                    events.RescheduleEvent(EV_SANDTRAP, 20000);
                    break;
                case EV_WIDE_SLASH:
                    me->CastSpell(me->GetVictim(), SPELL_WIDE_SLASH);
                    events.RescheduleEvent(EV_WIDE_SLASH, urand(10000, 15000));
                    break;
                case EV_TRASH:
                    me->CastSpell(me, SPELL_TRASH);
                    events.RescheduleEvent(EV_TRASH, urand(20000, 25000));
                    break;
                case EV_SUMMON_PLAYER:
                    me->CastSpell(SelectTarget(SELECT_TARGET_RANDOM, 3, 150.0f, true), SPELL_SUMMON_PLAYER);
                    events.RescheduleEvent(EV_SUMMON_PLAYER, urand(30000, 40000));
                    break;
                }

            DoMeleeAttackIfReady();
        }
        
    private:
        bool enraged;
        
        InstanceScript* pInstance;
    };
};

void AddSC_boss_kurinnaxx()
{
    new Boss_kurinaxx();
}

