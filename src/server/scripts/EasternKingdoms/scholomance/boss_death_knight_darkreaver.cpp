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
SDName: Boss_Death_knight_darkreaver
SD%Complete: 100
SDComment:
SDCategory: Scholomance
EndScriptData */



class boss_death_knight_darkreaver : public CreatureScript
{
public:
    boss_death_knight_darkreaver() : CreatureScript("boss_death_knight_darkreaver")
    { }

    class boss_death_knight_darkreaverAI : public ScriptedAI
    {
        public:
        boss_death_knight_darkreaverAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
        }
    
        void DamageTaken(Unit *done_by, uint32 &damage)
        override {
            if (me->GetHealth() <= damage)
            {
                me->CastSpell(me,23261, TRIGGERED_FULL_MASK);   //Summon Darkreaver's Fallen Charger
            }
        }
    
        void EnterCombat(Unit *who)
        override {
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_death_knight_darkreaverAI(creature);
    }
};


void AddSC_boss_death_knight_darkreaver()
{

    new boss_death_knight_darkreaver();
}

