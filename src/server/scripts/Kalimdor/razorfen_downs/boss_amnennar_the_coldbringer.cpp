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
SDName: Boss_Amnennar_the_coldbringer
SD%Complete: 100
SDComment:
SDCategory: Razorfen Downs
EndScriptData */


#include "def_razorfen_downs.h"

#define SAY_0             "You'll never leave this place... alive."
#define SAY_1             "Come, spirits, attend your master."
#define SAY_SLAY          "Too...easy!"
#define SOUND_AGGRO       5825
#define SOUND_SLAY        5826
#define SOUND_SUMMON      5829

#define SPELL_AMNENNARSWRATH          13009
#define SPELL_FROSTBOLT               10179
#define SPELL_SUMMON_FROST_SPECTRES   12642


class boss_amnennar_the_coldbringer : public CreatureScript
{
public:
    boss_amnennar_the_coldbringer() : CreatureScript("boss_amnennar_the_coldbringer")
    { }

    class boss_amnennar_the_coldbringerAI : public ScriptedAI
    {
        public:
        boss_amnennar_the_coldbringerAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
        uint32 AmnenarsWrath_Timer;
        uint32 FrostBolt_Timer;
        bool Spectrals;
        int Rand;
        int RandX;
        int RandY;
        Creature* Summoned;
    
        void Reset()
        override {
            AmnenarsWrath_Timer = 8000;
            FrostBolt_Timer = 1000;
            Spectrals = false;
            
            if (pInstance && pInstance->GetData(DATA_AMNENNAR_THE_COLDBRINGER_EVENT) != DONE)
                pInstance->SetData(DATA_AMNENNAR_THE_COLDBRINGER_EVENT, NOT_STARTED);
        }
    
        void EnterCombat(Unit *who)
        override {
            if (pInstance)
                pInstance->SetData(DATA_AMNENNAR_THE_COLDBRINGER_EVENT, IN_PROGRESS);
    
            me->Yell(SAY_0,LANG_UNIVERSAL,nullptr);
            DoPlaySoundToSet(me,SOUND_AGGRO);
        }
    
        void JustDied(Unit *killer)
        override {
            if (pInstance)
                pInstance->SetData(DATA_AMNENNAR_THE_COLDBRINGER_EVENT, DONE);
        }
    
        void KilledUnit(Unit* ) override
        {
            me->Yell(SAY_SLAY, LANG_UNIVERSAL, nullptr);
            DoPlaySoundToSet(me, SOUND_SLAY);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            //AmnenarsWrath_Timer
            if (AmnenarsWrath_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_AMNENNARSWRATH);
                AmnenarsWrath_Timer = 12000;
            } else AmnenarsWrath_Timer -= diff;
    
            //FrostBolt_Timer
            if (FrostBolt_Timer < diff)
            {
                Unit* target = nullptr;
                target = SelectTarget(SELECT_TARGET_RANDOM,0);
                if (target) DoCast(target,SPELL_FROSTBOLT);
    
                FrostBolt_Timer = 8000;
            } else FrostBolt_Timer -= diff;
    
            if ( !Spectrals && me->GetHealthPct() < 50 )
            {
                me->Yell(SAY_1, LANG_UNIVERSAL, nullptr);
                DoPlaySoundToSet(me, SOUND_SUMMON);
    
                Unit* target = nullptr;
                target = SelectTarget(SELECT_TARGET_RANDOM,0);
    
                if(target)
                    DoCast(target, SPELL_SUMMON_FROST_SPECTRES);
    
                Spectrals = true;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_amnennar_the_coldbringerAI(creature);
    }
};


void AddSC_boss_amnennar_the_coldbringer()
{
    new boss_amnennar_the_coldbringer();
}
