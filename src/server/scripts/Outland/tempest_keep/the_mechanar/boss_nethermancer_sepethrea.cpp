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
SDName: Boss_Nethermancer_Sepethrea
SD%Complete: 90
SDComment: Need adjustments to initial summons
SDCategory: Tempest Keep, The Mechanar
EndScriptData */


#include "def_mechanar.h"
#include "GameEventMgr.h"

#define SAY_AGGRO                       -1554013
#define SAY_SUMMON                      -1554014
#define SAY_DRAGONS_BREATH_1            -1554015
#define SAY_DRAGONS_BREATH_2            -1554016
#define SAY_SLAY1                       -1554017
#define SAY_SLAY2                       -1554018
#define SAY_DEATH                       -1554019

#define SPELL_SUMMON_RAGIN_FLAMES       35275
#define H_SPELL_SUMMON_RAGIN_FLAMES     39084

#define SPELL_FROST_ATTACK              35263
#define SPELL_ARCANE_BLAST              35314
#define SPELL_DRAGONS_BREATH            35250
#define SPELL_KNOCKBACK                 37317
#define SPELL_SOLARBURN                 35267


class boss_nethermancer_sepethrea : public CreatureScript
{
public:
    boss_nethermancer_sepethrea() : CreatureScript("boss_nethermancer_sepethrea")
    { }

    class boss_nethermancer_sepethreaAI : public ScriptedAI
    {
        public:
        boss_nethermancer_sepethreaAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        InstanceScript *pInstance;
    
        bool HeroicMode;
    
        uint32 frost_attack_Timer;
        uint32 arcane_blast_Timer;
        uint32 dragons_breath_Timer;
        uint32 knockback_Timer;
        uint32 solarburn_Timer;
        
        bool isEventActive()
        {
            const GameEventMgr::ActiveEvents& activeEvents = sGameEventMgr->GetActiveEventList();
            bool active = activeEvents.find(57) != activeEvents.end();
    
            return active;
        }
    
        void Reset()
        override {
            frost_attack_Timer = 7000 + rand()%3000;
            arcane_blast_Timer = 12000 + rand()%6000;
            dragons_breath_Timer = 18000 + rand()%4000;
            knockback_Timer = 22000 + rand()%6000;
            solarburn_Timer = 30000;
    
            if(pInstance && pInstance->GetData(DATA_NETHERMANCER) != DONE)
                pInstance->SetData(DATA_NETHERMANCER, NOT_STARTED);
                
            if (isEventActive())
                me->SetDisplayId(22804);
        }
    
        void EnterCombat(Unit *who)
        override {
            if(pInstance)
                pInstance->SetData(DATA_NETHERMANCER, IN_PROGRESS);
    
            DoScriptText(SAY_AGGRO, me);
            DoCast(who, HeroicMode ? H_SPELL_SUMMON_RAGIN_FLAMES : SPELL_SUMMON_RAGIN_FLAMES, true);
            DoScriptText(SAY_SUMMON, me);
        }
    
        void KilledUnit(Unit* victim)
        override {
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_SLAY1, me); break;
            case 1: DoScriptText(SAY_SLAY2, me); break;
            }
        }
        
        void JustSummoned(Creature* summoned)
        override {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
            {
                summoned->AI()->AttackStart(target);
                summoned->GetThreatManager().AddThreat(target,999999.0f);
            }
        }
    
        void JustDied(Unit* Killer)
        override {
            DoScriptText(SAY_DEATH, me);
    
            if(pInstance)
                pInstance->SetData(DATA_NETHERMANCER, DONE);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            //Frost Attack
            if(frost_attack_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_FROST_ATTACK);
                frost_attack_Timer = 7000 + rand()%30000;
            }else frost_attack_Timer -= diff;
    
            //Arcane Blast
            if(arcane_blast_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_ARCANE_BLAST);
                arcane_blast_Timer = 15000;
            }else arcane_blast_Timer -= diff;
    
            //Dragons Breath
            if(dragons_breath_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_DRAGONS_BREATH);
                {
                    if (rand()%2)
                        return;
    
                    switch(rand()%2)
                    {
                    case 0: DoScriptText(SAY_DRAGONS_BREATH_1, me); break;
                    case 1: DoScriptText(SAY_DRAGONS_BREATH_2, me); break;
                    }
                }
                dragons_breath_Timer = 12000 + rand()%10000;
            }else dragons_breath_Timer -= diff;
    
            //Knockback
            if(knockback_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_KNOCKBACK);
                knockback_Timer = 15000 + rand()%10000;
            }else knockback_Timer -= diff;
    
            //Solarburn
            if(solarburn_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_SOLARBURN);
                solarburn_Timer = 30000;
            }else solarburn_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_nethermancer_sepethreaAI(creature);
    }
};


#define SPELL_INFERNO                   35268
#define H_SPELL_INFERNO                 39346
#define SPELL_FIRE_TAIL                 35278

class mob_ragin_flames : public CreatureScript
{
public:
    mob_ragin_flames() : CreatureScript("mob_ragin_flames")
    { }

    class mob_ragin_flamesAI : public ScriptedAI
    {
        public:
        mob_ragin_flamesAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());        HeroicMode = me->GetMap()->IsHeroic();
        }
    
        InstanceScript *pInstance;
    
        bool HeroicMode;
    
        uint32 inferno_Timer;
        uint32 flame_timer;
        uint32 Check_Timer;
    
        bool onlyonce;
    
        void Reset()
        override {
            inferno_Timer = 10000;
            flame_timer = 500;
            Check_Timer = 2000;
            onlyonce = false;
            me->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);
            me->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, true);
            me->SetSpeedRate(MOVE_RUN, HeroicMode ? 0.7f : 0.5f);
        }
    
        void EnterCombat(Unit* who)
        override {
        }
    
        void UpdateAI(const uint32 diff)
        override {
             //Check_Timer
            if(Check_Timer < diff)
            {
                if(pInstance)
                {
                    if(pInstance->GetData(DATA_NETHERMANCER) != IN_PROGRESS)
                    {
                        me->DespawnOrUnsummon();
                    }
                }
                Check_Timer = 1000;
            }else Check_Timer -= diff;
    
            if (!UpdateVictim())
                return;
    
            if (!onlyonce)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    me->GetMotionMaster()->MoveChase(target);
                onlyonce = true;
            }
    
            if(inferno_Timer < diff)
            {
                DoCast(me->GetVictim(),HeroicMode ? H_SPELL_INFERNO : SPELL_INFERNO);
                me->TauntApply(me->GetVictim());
                inferno_Timer = 10000;
            }else inferno_Timer -= diff;
    
            if(flame_timer < diff)
            {
                DoCast(me,SPELL_FIRE_TAIL);
                flame_timer = 500;
            }else flame_timer -=diff;
    
            DoMeleeAttackIfReady();
        }
    
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_ragin_flamesAI(creature);
    }
};

void AddSC_boss_nethermancer_sepethrea()
{
    new boss_nethermancer_sepethrea();

    new mob_ragin_flames();
}

