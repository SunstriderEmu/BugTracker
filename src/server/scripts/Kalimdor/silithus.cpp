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
SDName: Silithus
SD%Complete: 100
SDComment: Quest support: 7785, 8304.
SDCategory: Silithus
EndScriptData */

/* ContentData
npc_highlord_demitrian
npcs_rutgar_and_frankal
EndContentData */



/*###
## npc_highlord_demitrian
###*/

#define GOSSIP_DEMITRIAN1 "Qu'en savez-vous ?"
#define GOSSIP_DEMITRIAN2 "J'écoute, Demitrian."
#define GOSSIP_DEMITRIAN3 "Continuez, s'il vous plait."
#define GOSSIP_DEMITRIAN4 "Une bataille ?"
#define GOSSIP_DEMITRIAN5 "<Hocher la tête>"
#define GOSSIP_DEMITRIAN6 "Pris par surprise ? Comment ?"
#define GOSSIP_DEMITRIAN7 "Qu'a fait Ragnaros ensuite ?"

class npc_highlord_demitrian : public CreatureScript
{
public:
    npc_highlord_demitrian() : CreatureScript("npc_highlord_demitrian")
    { }

    class npc_highlord_demitrianAI : public ScriptedAI
    {
    public:
        npc_highlord_demitrianAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            if (player->GetQuestStatus(7785) == QUEST_STATUS_NONE &&
                (player->HasItemCount(18563,1,false) || player->HasItemCount(18564,1,false)))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DEMITRIAN1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            player->SEND_GOSSIP_MENU_TEXTID(6812, me->GetGUID());
                return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DEMITRIAN2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU_TEXTID(6842, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DEMITRIAN3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU_TEXTID(6843, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DEMITRIAN4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->SEND_GOSSIP_MENU_TEXTID(6844, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DEMITRIAN5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                player->SEND_GOSSIP_MENU_TEXTID(6867, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DEMITRIAN6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                player->SEND_GOSSIP_MENU_TEXTID(6868, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DEMITRIAN7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                player->SEND_GOSSIP_MENU_TEXTID(6869, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                player->SEND_GOSSIP_MENU_TEXTID(6870, me->GetGUID());

                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 19016, 1);
                if (msg == EQUIP_ERR_OK) {
                    Item *item = player->StoreNewItem(dest, 19016, true);
                    player->SendNewItem(item, 1, true, false);
                }
                break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_highlord_demitrianAI(creature);
    }
};



/*###
## npcs_rutgar_and_frankal
###*/

//gossip item text best guess
#define GOSSIP_ITEM1 "Je cherche des informations sur Natalia"

#define GOSSIP_ITEM2 "Cela semble dangereux !"
#define GOSSIP_ITEM3 "Qu'avez-vous fait ?"
#define GOSSIP_ITEM4 "Qui ?"
#define GOSSIP_ITEM5 "Les femmes font ça. Qu'a-t-elle demandé ?"
#define GOSSIP_ITEM6 "Que voulez-vous dire ?"
#define GOSSIP_ITEM7 "Qu'est-il arrivé après ?"
#define GOSSIP_ITEM11 "Oui, continuez s'il vous plait"
#define GOSSIP_ITEM12 "Quel langue ?"
#define GOSSIP_ITEM13 "La Prêtresse vous a attaqué ?"
#define GOSSIP_ITEM14 "Je devrais demander au singe"
#define GOSSIP_ITEM15 "Et puis quoi..."

//trigger creatures to kill
#define TRIGGER_RUTGAR 15222
#define TRIGGER_FRANKAL 15221

class npcs_rutgar_and_frankal : public CreatureScript
{
public:
    npcs_rutgar_and_frankal() : CreatureScript("npcs_rutgar_and_frankal")
    { }

    class npcs_rutgar_and_frankalAI : public ScriptedAI
    {
    public:
        npcs_rutgar_and_frankalAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if (player->GetQuestStatus(8304) == QUEST_STATUS_INCOMPLETE &&
                me->GetEntry() == 15170 &&
                !player->GetReqKillOrCastCurrentCount(8304, TRIGGER_RUTGAR ))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            if (player->GetQuestStatus(8304) == QUEST_STATUS_INCOMPLETE &&
                me->GetEntry() == 15171 &&
                player->GetReqKillOrCastCurrentCount(8304, TRIGGER_RUTGAR ))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);

            player->SEND_GOSSIP_MENU_TEXTID(7754, me->GetGUID());

            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU_TEXTID(7755, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(7756, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU_TEXTID(7757, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 3:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->SEND_GOSSIP_MENU_TEXTID(7758, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 4:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                    player->SEND_GOSSIP_MENU_TEXTID(7759, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 5:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                    player->SEND_GOSSIP_MENU_TEXTID(7760, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 6:
                    player->SEND_GOSSIP_MENU_TEXTID(7761, me->GetGUID());
                    //'kill' our trigger to update quest status
                    player->KilledMonsterCredit( TRIGGER_RUTGAR, me->GetGUID() );
                    break;
                case GOSSIP_ACTION_INFO_DEF + 9:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM11, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                    player->SEND_GOSSIP_MENU_TEXTID(7762, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 10:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM12, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                    player->SEND_GOSSIP_MENU_TEXTID(7763, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 11:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM13, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                    player->SEND_GOSSIP_MENU_TEXTID(7764, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 12:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM14, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                    player->SEND_GOSSIP_MENU_TEXTID(7765, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 13:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM15, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                    player->SEND_GOSSIP_MENU_TEXTID(7766, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 14:
                    player->SEND_GOSSIP_MENU_TEXTID(7767, me->GetGUID());
                                                                    //'kill' our trigger to update quest status
                    player->KilledMonsterCredit( TRIGGER_FRANKAL, me->GetGUID() );
                    break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npcs_rutgar_and_frankalAI(creature);
    }
};



/*###
##
####*/

void AddSC_silithus()
{

    new npc_highlord_demitrian();

    new npcs_rutgar_and_frankal();
}

