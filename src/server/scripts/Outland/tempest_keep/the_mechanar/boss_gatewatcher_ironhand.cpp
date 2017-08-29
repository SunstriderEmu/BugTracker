/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ScriptData
SDName: Boss_Gatewatcher_Ironhand
SD%Complete: 75
SDComment:
SDCategory: Tempest Keep, The Mechanar
EndScriptData */


#include "def_mechanar.h"

#define SAY_AGGRO_1                     -1554006
#define SAY_HAMMER_1                    -1554007
#define SAY_HAMMER_2                    -1554008
#define SAY_SLAY_1                      -1554009
#define SAY_SLAY_2                      -1554010
#define SAY_DEATH_1                     -1554011
#define EMOTE_HAMMER                    -1554012

// Spells to be casted
#define SPELL_SHADOW_POWER              35322
#define H_SPELL_SHADOW_POWER            39193
#define SPELL_HAMMER_PUNCH              35326
#define SPELL_JACKHAMMER                35327
#define H_SPELL_JACKHAMMER              39194
#define SPELL_STREAM_OF_MACHINE_FLUID   35311

// Gatewatcher Iron-Hand AI
class boss_gatewatcher_iron_hand : public CreatureScript
{
public:
    boss_gatewatcher_iron_hand() : CreatureScript("boss_gatewatcher_iron_hand")
    { }

    class boss_gatewatcher_iron_handAI : public ScriptedAI
    {
        public:
        boss_gatewatcher_iron_handAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        InstanceScript* pInstance;
    
        bool HeroicMode;
    
        uint32 Shadow_Power_Timer;
        uint32 Jackhammer_Timer;
        uint32 Jackhammer_CastTime;
        uint8 Jackhammer_Progression;
        uint32 Stream_of_Machine_Fluid_Timer;
    
        void Reset()
        override {
            Shadow_Power_Timer = 40000 + rand()%5000;
            Jackhammer_Timer = 80000+rand()%10000;
            Stream_of_Machine_Fluid_Timer = 55000;
            Jackhammer_CastTime = 0;
            Jackhammer_Progression = 0;
        }
        void EnterCombat(Unit *who)
        override {
            DoScriptText(SAY_AGGRO_1, me);
        }
    
        void KilledUnit(Unit* victim)
        override {
            if (rand()%2)
                return;
    
            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2), me);
        }
    
        void JustDied(Unit* Killer)
        override {
            DoScriptText(SAY_DEATH_1, me);
    
            if (!pInstance)
                return;
    
            //SetData will open the Moarg Door 2
            pInstance->SetData(DATA_GATEWATCHER_IRONHAND, DONE);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            //Shadow Power
            if(Shadow_Power_Timer < diff)
            {
                DoCast(me,HeroicMode ? H_SPELL_SHADOW_POWER : SPELL_SHADOW_POWER);
                Shadow_Power_Timer = 55000 + rand()%5000;
            }else Shadow_Power_Timer -= diff;
    
            //Jack Hammer
            if(Jackhammer_Timer < diff)
            {
                switch(Jackhammer_Progression)
                {
                case 0: 
                    if(Jackhammer_CastTime == 0)
                    {
                        DoCast(me->GetVictim(),HeroicMode ? H_SPELL_JACKHAMMER : SPELL_JACKHAMMER);
                        DoScriptText(EMOTE_HAMMER, me);
                        Jackhammer_Progression++;
                    }
                    break;
                case 1: 
                    if(Jackhammer_CastTime > 2500)
                    {
                        DoScriptText(SAY_HAMMER_1, me); 
                        Jackhammer_Progression++;
                    }
                    break;
                case 2: 
                    if(Jackhammer_CastTime > 5500)
                    {
                        DoScriptText(SAY_HAMMER_2, me); 
                        Jackhammer_Progression++;
                    }
                    break;
                case 3:
                    if(Jackhammer_CastTime > 8000)
                    {
                        Jackhammer_Timer = 30000+rand()%15000;
                        Jackhammer_CastTime = 0;
                        Jackhammer_Progression = 0;
                    }
                    break;
                }
                
                Jackhammer_CastTime += diff;
            }else Jackhammer_Timer -= diff;
    
            //Stream of Machine Fluid
            if(Stream_of_Machine_Fluid_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_STREAM_OF_MACHINE_FLUID);
                Stream_of_Machine_Fluid_Timer = 55000;
            }else Stream_of_Machine_Fluid_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_gatewatcher_iron_handAI(creature);
    }
};


void AddSC_boss_gatewatcher_iron_hand()
{
    new boss_gatewatcher_iron_hand();
}

