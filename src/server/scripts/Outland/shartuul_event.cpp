/* Copyright (C) 2009 - 2011 Windrunner <http://www.wowmania.fr/>
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
 
 

/* ContentData: Legion Ring event

*/

/* Misc */
#define WS_REMAINING_SHIELD     3055

/* Triggers */
#define LR_EVENT_CONTROLLER     23059
#define LR_TRIGGER              23260
#define LR_STUN_FIELD           23312
#define LR_STUN_ROPE_DUMMY      23313
#define LR_EREDAR_BREATH_TARGET 23328
#define LR_SHIELD_ZAPPER        23500
#define LR_PORTAL_SHIELD        23116

/* GameObjects */
#define LR_FOG                  185593

/* Spells */
#define LR_SPELL_IMMUNE_INVIS   40357
#define LR_COSMETIC_SHIELD      40158

/* Creatures */
#define LR_FELGUARD_DEGRADER    23055
#define LR_DOOMGUARD_PUNISHER   23113
#define LR_SHIVAN_ASSASSIN      23220
#define LR_EYE_OF_SHARTUUL      23228
#define LR_DREADMAW             23275
#define LR_SHARTUUL             23230
#define LR_SHARTUUL_VOICE       23063


class npc_lr_trigger : public CreatureScript
{
public:
    npc_lr_trigger() : CreatureScript("npc_lr_trigger")
    { }

    class npc_lr_triggerAI : public ScriptedAI
    {
        public:
        npc_lr_triggerAI(Creature *c) : ScriptedAI(c) {}
        
        void Reset()
        override {
            DoCast(me, 40380);
            
            me->ApplySpellImmune(0, IMMUNITY_ID, 40381, true);
        }
        
        void EnterCombat(Unit *pWho) override {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lr_triggerAI(creature);
    }
};


void AddSC_shartuul_event()
{
    
    new npc_lr_trigger();
}
