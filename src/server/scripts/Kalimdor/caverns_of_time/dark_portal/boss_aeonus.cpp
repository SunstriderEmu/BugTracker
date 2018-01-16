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
SDName: Boss_Aeonus
SD%Complete: 80
SDComment: Some spells not implemented
SDCategory: Caverns of Time, The Dark Portal
EndScriptData */


#include "def_dark_portal.h"

enum eEnums
{
    SAY_ENTER           = -1269012,
    SAY_AGGRO           = -1269013,
    SAY_BANISH          = -1269014,
    SAY_SLAY1           = -1269015,
    SAY_SLAY2           = -1269016,
    SAY_DEATH           = -1269017,
    EMOTE_FRENZY        = -1269018,

    SPELL_CLEAVE        = 40504,
    SPELL_TIME_STOP     = 31422,
    SPELL_ENRAGE        = 37605,
    SPELL_SAND_BREATH   = 31473,
    H_SPELL_SAND_BREATH = 39049
};


class boss_aeonus : public CreatureScript
{
public:
    boss_aeonus() : CreatureScript("boss_aeonus")
    { }

    class boss_aeonusAI : public ScriptedAI
    {
        public:
        boss_aeonusAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        InstanceScript *pInstance;
        bool HeroicMode;
    
        uint32 SandBreath_Timer;
        uint32 TimeStop_Timer;
        uint32 Frenzy_Timer;
        uint32 Cleave_Timer;
    
        void Reset()
        override {
            SandBreath_Timer = 15000+rand()%15000;
            TimeStop_Timer = 10000+rand()%5000;
            Frenzy_Timer = 30000+rand()%15000;
            Cleave_Timer = 10000;
        }
    
        void JustEngagedWith(Unit *who) override
        {
            DoScriptText(SAY_AGGRO, me);
        }
    
        void MoveInLineOfSight(Unit *who)
        override {
            //Despawn Time Keeper
            if (who->GetTypeId() == TYPEID_UNIT && who->GetEntry() == C_TIME_KEEPER)
            {
                if (me->IsWithinDistInMap(who,20.0f))
                {
                    DoScriptText(SAY_BANISH, me);
                    Unit::DealDamage(me, who, who->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                }
            }
    
            ScriptedAI::MoveInLineOfSight(who);
        }
    
        void JustDied(Unit *killer)
        override {
            DoScriptText(SAY_DEATH, me);
    
             if (pInstance)
             {
                 pInstance->SetData(TYPE_RIFT,DONE);
                 pInstance->SetData(DATA_AEONUS, DONE);             
                 pInstance->SetData(TYPE_MEDIVH,DONE);//FIXME: later should be removed
             }
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(RAND(SAY_SLAY1,SAY_SLAY2), me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            //Sand Breath
            if (SandBreath_Timer < diff)
            {
                DoCast(me->GetVictim(), HEROIC(SPELL_SAND_BREATH, H_SPELL_SAND_BREATH));
                SandBreath_Timer = 15000+rand()%10000;
            }else SandBreath_Timer -= diff;
    
            //Time Stop
            if (TimeStop_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_TIME_STOP);
                TimeStop_Timer = 20000+rand()%15000;
            }else TimeStop_Timer -= diff;
    
            //Frenzy
            if (Frenzy_Timer < diff)
            {
                DoScriptText(EMOTE_FRENZY, me);
                DoCast(me, SPELL_ENRAGE);
                Frenzy_Timer = 20000+rand()%15000;
            }else Frenzy_Timer -= diff;
            
            //Cleave
            if (Cleave_Timer <= diff) {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                Cleave_Timer = 18000+rand()%5000;
            }else Cleave_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_aeonusAI(creature);
    }
};


void AddSC_boss_aeonus()
{
    new boss_aeonus();
}

