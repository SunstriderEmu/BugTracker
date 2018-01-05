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
SDName: Boss_Firemaw
SD%Complete: 100
SDComment:
SDCategory: Blackwing Lair
EndScriptData */



#define SPELL_SHADOWFLAME       22539
#define SPELL_WINGBUFFET        23339
#define SPELL_FLAMEBUFFET       23341

class boss_firemaw : public CreatureScript
{
public:
    boss_firemaw() : CreatureScript("boss_firemaw")
    { }

    class boss_firemawAI : public ScriptedAI
    {
        public:
        boss_firemawAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 ShadowFlame_Timer;
        uint32 WingBuffet_Timer;
        uint32 FlameBuffet_Timer;
    
        void Reset()
        override {
            ShadowFlame_Timer = 30000;                          //These times are probably wrong
            WingBuffet_Timer = 24000;
            FlameBuffet_Timer = 5000;
        }
    
        void JustEngagedWith(Unit *who)
        override {
            DoZoneInCombat();
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim() )
                return;
    
            //ShadowFlame_Timer
            if (ShadowFlame_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_SHADOWFLAME);
                ShadowFlame_Timer = 15000 + rand()%3000;
            }else ShadowFlame_Timer -= diff;
    
            //WingBuffet_Timer
            if (WingBuffet_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_WINGBUFFET);
                if(me->GetThreatManager().GetThreat(me->GetVictim()))
                    ModifyThreatByPercent(me->GetVictim(),-75);
    
                WingBuffet_Timer = 25000;
            }else WingBuffet_Timer -= diff;
    
            //FlameBuffet_Timer
            if (FlameBuffet_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_FLAMEBUFFET);
                FlameBuffet_Timer = 5000;
            }else FlameBuffet_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_firemawAI(creature);
    }
};


void AddSC_boss_firemaw()
{
    new boss_firemaw();
}

