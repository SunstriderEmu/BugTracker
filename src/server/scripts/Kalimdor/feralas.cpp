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
SDName: Feralas
SD%Complete: 100
SDComment: Quest support: 3520. Special vendor Gregan Brewspewer
SDCategory: Feralas
EndScriptData */


#include "EscortAI.h"

/*######
## npc_gregan_brewspewer
######*/

#define GOSSIP_HELLO "Buy somethin', will ya?"

class npc_gregan_brewspewer : public CreatureScript
{
public:
    npc_gregan_brewspewer() : CreatureScript("npc_gregan_brewspewer")
    { }

    class npc_gregan_brewspewerAI : public ScriptedAI
    {
    public:
        npc_gregan_brewspewerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (me->IsVendor() && pPlayer->GetQuestStatus(3909) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(2433, me->GetGUID());
            
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
                player->SEND_GOSSIP_MENU_TEXTID(2434, me->GetGUID());
            }
            if (action == GOSSIP_ACTION_TRADE)
                player->SEND_VENDORLIST(me->GetGUID());
                
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gregan_brewspewerAI(creature);
    }
};



/*######
## npc_oox22fe
######*/

enum eOOX
{
    //signed for 7806
    SAY_OOX_START           = -1060000,
    SAY_OOX_AGGRO1          = -1060001,
    SAY_OOX_AGGRO2          = -1060002,
    SAY_OOX_AMBUSH          = -1060003,
    SAY_OOX_END             = -1060005,

    NPC_YETI                = 7848,
    NPC_GORILLA             = 5260,
    NPC_WOODPAW_REAVER      = 5255,
    NPC_WOODPAW_BRUTE       = 5253,
    NPC_WOODPAW_ALPHA       = 5258,
    NPC_WOODPAW_MYSTIC      = 5254,

    QUEST_RESCUE_OOX22FE    = 2767,
    FACTION_ESCORTEE_A      = 774,
    FACTION_ESCORTEE_H      = 775
};


class npc_oox22fe : public CreatureScript
{
public:
    npc_oox22fe() : CreatureScript("npc_oox22fe")
    { }

    class npc_oox22feAI : public EscortAI
    {
        public:
        npc_oox22feAI(Creature* pCreature) : EscortAI(pCreature) { }
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            switch (i)
            {
                // First Ambush(3 Yetis)
                case 11:
                    DoScriptText(SAY_OOX_AMBUSH, me);
                    for (uint8 j = 0; j < 3; ++j)
                        me->SummonCreature(NPC_YETI, -4887.69, 1598.1, 67.45, 0.68, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    break;
                //Second Ambush(3 Gorillas)
                case 21:
                    DoScriptText(SAY_OOX_AMBUSH, me);
                    for (uint8 j = 0; j < 3; ++j)
                        me->SummonCreature(NPC_GORILLA, -4599.37, 2010.59, 52.77, 3.84, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    break;
                //Third Ambush(4 Gnolls)
                case 30:
                    DoScriptText(SAY_OOX_AMBUSH, me);
                    me->SummonCreature(NPC_WOODPAW_REAVER, -4425.14, 2075.87, 47.77, 3.77, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    me->SummonCreature(NPC_WOODPAW_BRUTE , -4426.68, 2077.98, 47.57, 3.77, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    me->SummonCreature(NPC_WOODPAW_MYSTIC, -4428.33, 2080.24, 47.43, 3.87, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    me->SummonCreature(NPC_WOODPAW_ALPHA , -4430.04, 2075.54, 46.83, 3.81, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    break;
                case 37:
                    DoScriptText(SAY_OOX_END, me);
                    if (Player* pPlayer = GetPlayerForEscort())
                        pPlayer->GroupEventHappens(QUEST_RESCUE_OOX22FE, me);
                    break;
            }
        }
    
        void Reset()
        override {
            if (!HasEscortState(STATE_ESCORT_ESCORTING))
                me->SetStandState(UNIT_STAND_STATE_DEAD);
        }
    
        void JustEngagedWith(Unit* pWho)
        override {
            if (pWho->GetEntry() == NPC_YETI || pWho->GetEntry() == NPC_GORILLA || pWho->GetEntry() == NPC_WOODPAW_REAVER ||
                    pWho->GetEntry() == NPC_WOODPAW_BRUTE || pWho->GetEntry() == NPC_WOODPAW_MYSTIC)
                return;
            DoScriptText(RAND(SAY_OOX_AGGRO1,SAY_OOX_AGGRO2), me);
        }
    
        void JustSummoned(Creature* summoned)
        override {
            summoned->AI()->AttackStart(me);
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if (pQuest->GetQuestId() == QUEST_RESCUE_OOX22FE)
            {
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                me->SetHealth(me->GetMaxHealth());
                me->SetUInt32Value(UNIT_FIELD_BYTES_1,0);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                DoScriptText(SAY_OOX_START, me);

                if (EscortAI* pEscortAI = CAST_AI(npc_oox22feAI, me->AI()))
                    pEscortAI->Start(true, false, pPlayer->GetGUID());

            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_oox22feAI(creature);
    }
};



/*######
## npc_screecher_spirit
######*/

class npc_screecher_spirit : public CreatureScript
{
public:
    npc_screecher_spirit() : CreatureScript("npc_screecher_spirit")
    { }

    class npc_screecher_spiritAI : public ScriptedAI
    {
    public:
        npc_screecher_spiritAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            Creature* screecher = nullptr;
            if ((screecher = me->FindNearestCreature(5307, 2.0f, false)))
                screecher->RemoveCorpse();
            else if ((screecher = me->FindNearestCreature(5308, 2.0f, false)))
                screecher->RemoveCorpse();

            pPlayer->SEND_GOSSIP_MENU_TEXTID(2039, me->GetGUID() );
            pPlayer->TalkedToCreature(me->GetEntry(), me->GetGUID());
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_screecher_spiritAI(creature);
    }
};


/*######
## AddSC
######*/

void AddSC_feralas()
{

    new npc_gregan_brewspewer();

    new npc_oox22fe();

    new npc_screecher_spirit();
}

