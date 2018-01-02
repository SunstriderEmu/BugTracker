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
SDName: Silvermoon_City
SD%Complete: 100
SDComment: Quest support: 9685
SDCategory: Silvermoon City
EndScriptData */

/* ContentData
npc_blood_knight_stillblade
npc_schweitzer
EndContentData */

#include "Pet.h"

/*#######
# npc_blood_knight_stillblade
#######*/

#define SAY_HEAL -1000334

#define QUEST_REDEEMING_THE_DEAD        9685
#define SPELL_SHIMMERING_VESSEL         31225
#define SPELL_REVIVE_SELF               32343


class npc_blood_knight_stillblade : public CreatureScript
{
public:
    npc_blood_knight_stillblade() : CreatureScript("npc_blood_knight_stillblade")
    { }

    class npc_blood_knight_stillbladeAI : public ScriptedAI
    {
        public:
        npc_blood_knight_stillbladeAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 lifeTimer;
        bool spellHit;
    
        void Reset()
        override {
            lifeTimer = 120000;
            me->SetUInt32Value(UNIT_DYNAMIC_FLAGS, 32);
            me->SetUInt32Value(UNIT_FIELD_BYTES_1,7);   // lay down
            spellHit = false;
        }
    
        void JustEngagedWith(Unit *who)
        override {
        }
    
        void MoveInLineOfSight(Unit *who)
        override {
            return;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!me->GetUInt32Value(UNIT_FIELD_BYTES_1))
            {
                if(lifeTimer < diff)
                    me->AI()->EnterEvadeMode();
                else
                    lifeTimer -= diff;
            }
        }
    
        void SpellHit(Unit *Hitter, const SpellInfo *Spellkind)
        override {
            if((Spellkind->Id == SPELL_SHIMMERING_VESSEL) && !spellHit &&
                (Hitter->GetTypeId() == TYPEID_PLAYER) && ((Hitter->ToPlayer())->IsActiveQuest(QUEST_REDEEMING_THE_DEAD)))
            {
                (Hitter->ToPlayer())->AreaExploredOrEventHappens(QUEST_REDEEMING_THE_DEAD);
                DoCast(me,SPELL_REVIVE_SELF);
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                me->SetUInt32Value(UNIT_DYNAMIC_FLAGS, 0);
                //me->RemoveAllAuras();
                DoScriptText(SAY_HEAL, me);
                spellHit = true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_blood_knight_stillbladeAI(creature);
    }
};


/*######
## npc_schweitzer
######*/


class npc_schweitzer : public CreatureScript
{
public:
    npc_schweitzer() : CreatureScript("npc_schweitzer")
    { }

    class npc_schweitzerAI : public ScriptedAI
    {
        public:
        npc_schweitzerAI(Creature* c) : ScriptedAI(c) {}
        
        void JustEngagedWith(Unit* pWho) override {}
        
        void MoveInLineOfSight(Unit* pWho)
        override {
            if (me->GetDistance(pWho) <= 5.0f && pWho->GetTypeId() == TYPEID_PLAYER) {
                if(ObjectGuid critter_guid = pWho->ToPlayer()->GetCritterGUID())
                    if (Creature* pet = me->GetMap()->GetCreature(critter_guid)) {
                        if (pWho->ToPlayer()->GetQuestStatus(11975) == QUEST_STATUS_INCOMPLETE && pet->GetEntry() == 22817)
                            pWho->ToPlayer()->AreaExploredOrEventHappens(11975);
                    }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_schweitzerAI(creature);
    }
};


void AddSC_silvermoon_city()
{
    new npc_blood_knight_stillblade();
    
    new npc_schweitzer();
}

