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
SDName: Boss_Herod
SD%Complete: 95
SDComment: Should in addition spawn Myrmidons in the hallway outside
SDCategory: Scarlet Monastery
EndScriptData */


#include "EscortAI.h"

#define SAY_AGGRO                   -1189000
#define SAY_WHIRLWIND               -1189001
#define SAY_ENRAGE                  -1189002
#define SAY_KILL                    -1189003
#define EMOTE_ENRAGE                -1189004

#define SPELL_RUSHINGCHARGE         8260
#define SPELL_CLEAVE                15496
#define SPELL_WHIRLWIND             8989
#define SPELL_FRENZY                8269

#define ENTRY_SCARLET_TRAINEE       6575
#define ENTRY_SCARLET_MYRMIDON      4295


class boss_herod : public CreatureScript
{
public:
    boss_herod() : CreatureScript("boss_herod")
    { }

    class boss_herodAI : public ScriptedAI
    {
        public:
        boss_herodAI(Creature *c) : ScriptedAI(c) {}
    
        bool Enrage;
    
        uint32 Cleave_Timer;
        uint32 Whirlwind_Timer;
    
    
        void Reset()
        override {
            Enrage = false;
            Cleave_Timer = 12000;
            Whirlwind_Timer = 60000;
        }
    
        void JustEngagedWith(Unit *who)
        override {
            DoScriptText(SAY_AGGRO, me);
            DoCast(me,SPELL_RUSHINGCHARGE);
        }
    
         void KilledUnit(Unit *victim)
         override {
             DoScriptText(SAY_KILL, me);
         }
    
         void JustDied(Unit* killer)
         override {
             for(uint8 i = 0; i < 20; ++i)
                 me->SummonCreature(ENTRY_SCARLET_TRAINEE, 1939.18, -431.58, 17.09, 6.22, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000);
         }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            //If we are <30% hp goes Enraged
            if (!Enrage && me->GetHealthPct() <= 30 && !me->IsNonMeleeSpellCast(false))
            {
                DoScriptText(EMOTE_ENRAGE, me);
                DoScriptText(SAY_ENRAGE, me);
                DoCast(me,SPELL_FRENZY);
                Enrage = true;
            }
    
            //Cleave_Timer
            if (Cleave_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_CLEAVE);
                Cleave_Timer = 12000;
            }else Cleave_Timer -= diff;
    
            // Whirlwind_Timer
            if (Whirlwind_Timer < diff)
            {
                DoScriptText(SAY_WHIRLWIND, me);
                DoCast(me->GetVictim(),SPELL_WHIRLWIND);
                Whirlwind_Timer = 30000;
            }else Whirlwind_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_herodAI(creature);
    }
};


float Location[12][3]=
{
    {1945.81f, -431.54f, 16.36f},
    {1946.21f, -436.41f, 16.36f},
    {1950.01f, -444.11f, 14.63f},
    {1956.08f, -449.34f, 13.12f},
    {1966.59f, -450.55f, 11.27f},
    {1976.09f, -447.51f, 11.27f},
    {1983.42f, -435.85f, 11.27f},
    {1978.17f, -428.81f, 11.27f},
    {1973.97f, -422.08f, 9.04f},
    {1963.84f, -418.90f, 6.17f},
    {1961.22f, -422.74f, 6.17f},
    {1964.80f, -431.26f, 6.17f}
};

uint32 Wait[12][1]=
{
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{600000}
};

/* Probably not working... */
class mob_scarlet_trainee : public CreatureScript
{
public:
    mob_scarlet_trainee() : CreatureScript("mob_scarlet_trainee")
    { }

    class mob_scarlet_traineeAI : public EscortAI
    {
        public:
        mob_scarlet_traineeAI(Creature *c) : EscortAI(c) 
        {
            for (uint32 i = 0; i < 12; ++i)
                AddWaypoint(i, Location[i][0], Location[i][1], Location[i][2], 0.0f, Wait[i][0]);
        }
    
        uint32 Start_Timer;
    
        void Reset()
        override {
            Start_Timer = urand(1500,4500);
        }

        void WaypointReached(uint32, uint32) override {} //must be implemented because we inherit from EscortAI

        void JustEngagedWith(Unit* who) override { }
    
        void UpdateAI(const uint32 diff)
        override {
            if (Start_Timer)
            {
                if (Start_Timer < diff)
                {
                    Start(true,true, ObjectGuid::Empty);
                    Start_Timer = 0;
                } else Start_Timer -= diff;
            }
    
            EscortAI::UpdateAI(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_scarlet_traineeAI(creature);
    }
};


void AddSC_boss_herod()
{
    new boss_herod();
    new mob_scarlet_trainee();
}

