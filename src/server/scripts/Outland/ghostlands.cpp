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
SDName: Ghostlands
SD%Complete: 100
SDComment: Quest support: 9692, 9212. Obtain Budd's Guise of Zul'aman. Vendor Rathis Tomber
SDCategory: Ghostlands
EndScriptData */

/* ContentData
npc_blood_knight_dawnstar
npc_budd_nedreck
npc_rathis_tomber
npc_ranger_lilatha
EndContentData */


#include "EscortAI.h"

/*######
## npc_blood_knight_dawnstar
######*/

#define GOSSIP_H_BKD "Take Blood Knight Insignia"

class npc_blood_knight_dawnstar : public CreatureScript
{
public:
    npc_blood_knight_dawnstar() : CreatureScript("npc_blood_knight_dawnstar")
    { }

   class npc_blood_knight_dawnstarAI : public ScriptedAI
   {
   public:
        npc_blood_knight_dawnstarAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(9692) == QUEST_STATUS_INCOMPLETE && !pPlayer->HasItemCount(24226,1,true))
                pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_H_BKD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);

            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 24226, 1);
                if (msg == EQUIP_ERR_OK)
                {
                    player->StoreNewItem( dest, 24226, 1, true);
                    player->PlayerTalkClass->ClearMenus();
                }
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_blood_knight_dawnstarAI(creature);
    }
};



/*######
## npc_budd_nedreck
######*/

#define GOSSIP_HBN "You gave the crew disguises?"

class npc_budd_nedreck : public CreatureScript
{
public:
    npc_budd_nedreck() : CreatureScript("npc_budd_nedreck")
    { }

   class npc_budd_nedreckAI : public ScriptedAI
   {
   public:
        npc_budd_nedreckAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if( me->IsQuestGiver())
                pPlayer->PrepareQuestMenu( me->GetGUID() );

            if( pPlayer->GetQuestStatus(11166) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HBN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if( action == GOSSIP_ACTION_INFO_DEF )
            {
                player->CLOSE_GOSSIP_MENU();
                me->CastSpell(player, 42540, false);
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_budd_nedreckAI(creature);
    }
};



/*######
## npc_rathis_tomber
######*/

class npc_rathis_tomber : public CreatureScript
{
public:
    npc_rathis_tomber() : CreatureScript("npc_rathis_tomber")
    { }

   class npc_rathis_tomberAI : public ScriptedAI
   {
   public:
        npc_rathis_tomberAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (me->IsVendor() && pPlayer->GetQuestRewardStatus(9152))
            {
                pPlayer->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(8432, me->GetGUID());
            }
            else
                pPlayer->SEND_GOSSIP_MENU_TEXTID(8431,me->GetGUID());

            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_TRADE)
                player->SEND_VENDORLIST(me->GetGUID());
                
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_rathis_tomberAI(creature);
    }
};



class GildedBrazier : public GameObjectScript
{
public:
    GildedBrazier() : GameObjectScript("go_gilded_brazier")
    {}

    struct GildedBrazierAI : public GameObjectAI
    {
        GildedBrazierAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(9678) == QUEST_STATUS_INCOMPLETE)
            {
                Creature *Stillblade = pPlayer->SummonCreature(17716, 8106.11, -7542.06, 151.775, 3.02598, TEMPSUMMON_DEAD_DESPAWN, 60000);
                if (Stillblade)
                    CAST_AI(CreatureAI, (Stillblade->AI()))->AttackStart(pPlayer);
            }

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new GildedBrazierAI(go);
    }
};

/*######
## npc_ranger_lilatha
######*/

enum eLilatha
{
SAY_START                           = -1000140,
SAY_PROGRESS1                       = -1000141,
SAY_PROGRESS2                       = -1000142,
SAY_PROGRESS3                       = -1000143,
SAY_END1                            = -1000144,
SAY_END2                            = -1000145,
SAY_CAPTAIN_ANSWER                  = -1000146,

QUEST_ESCAPE_FROM_THE_CATACOMBS     = 9212,
GO_CAGE                             = 181152,
NPC_CAPTAIN_HELIOS                  = 16220
};


class npc_ranger_lilatha : public CreatureScript
{
public:
    npc_ranger_lilatha() : CreatureScript("npc_ranger_lilatha")
    { }

    class npc_ranger_lilathaAI : public npc_escortAI
    {
        public:
        npc_ranger_lilathaAI(Creature *c) : npc_escortAI(c) {}
    
        std::list<GameObject*> CageList;
    
        void WaypointReached(uint32 i)
        override {
            Player* player = GetPlayerForEscort();
    
            if (!player)
                return;
    
            switch(i)
            {
            case 0:
                {
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                GameObject* Cage = me->FindNearestGameObject(GO_CAGE, 20);
                if(Cage)
                    Cage->UseDoorOrButton();
                DoScriptText(SAY_START, me, player);
                break;
                }
            case 5:
                DoScriptText(SAY_PROGRESS1, me, player);
            case 11:
                DoScriptText(SAY_PROGRESS2, me, player);
                me->SetOrientation(4.762841);
                break;
            case 18:
                {
                DoScriptText(SAY_PROGRESS3, me, player);
                Creature* Summ1 = me->SummonCreature(16342, 7627.083984, -7532.538086, 152.128616, 1.082733, TEMPSUMMON_DEAD_DESPAWN, 0);
                Creature* Summ2 = me->SummonCreature(16343, 7620.432129, -7532.550293, 152.454865, 0.827478, TEMPSUMMON_DEAD_DESPAWN, 0);
                if(Summ1 && Summ2)
                {
                    Summ1->Attack(me, true);
                    Summ2->Attack(player, true);
                }
                me->AI()->AttackStart(Summ1);
                break;
                }
            case 19: me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING); break;
            case 25: me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING); break;
            case 30:
                player->GroupEventHappens(QUEST_ESCAPE_FROM_THE_CATACOMBS,me);
                break;
            case 32:
                me->SetOrientation(2.978281);
                DoScriptText(SAY_END1, me, player);
                break;
            case 33:
                me->SetOrientation(5.858011);
                DoScriptText(SAY_END2, me, player);
                Unit* CaptainHelios = me->FindNearestCreature(NPC_CAPTAIN_HELIOS, 50);
                if(CaptainHelios)
                DoScriptText(SAY_CAPTAIN_ANSWER, CaptainHelios, player);
                break;
            }
        }
    
        void EnterCombat(Unit* who) override {}
    
        void Reset()
        override {
            if (!HasEscortState(STATE_ESCORT_ESCORTING))
                me->SetFaction(1602);
    
            GameObject* Cage = me->FindNearestGameObject(GO_CAGE, 20);
            if (Cage)
                Cage->ResetDoorOrButton();
        }
    
        void JustDied(Unit* killer)
        override {
            if (PlayerGUID)
            {
                Player* player = GetPlayerForEscort();
                if (player)
                    player->FailQuest(QUEST_ESCAPE_FROM_THE_CATACOMBS);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            npc_escortAI::UpdateAI(diff);
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_ESCAPE_FROM_THE_CATACOMBS)
            {
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                ((npc_escortAI*)(me->AI()))->Start(true, true, false, player->GetGUID(), me->GetEntry());
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ranger_lilathaAI(creature);
    }
};



void AddSC_ghostlands()
{

    new npc_blood_knight_dawnstar();

    new npc_budd_nedreck();

    new npc_rathis_tomber();

    new GildedBrazier();

    new npc_ranger_lilatha();
}

