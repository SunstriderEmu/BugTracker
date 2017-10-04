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
SDName: Blasted_Lands
SD%Complete: 90
SDComment: Quest support: 2784, 2801, 3628. Missing some texts for Fallen Hero. Teleporter to Rise of the Defiler missing group support.
SDCategory: Blasted Lands
EndScriptData */

/* ContentData
npc_deathly_usher
npc_fallen_hero_of_horde
EndContentData */



/*######
## npc_deathly_usher
######*/

#define GOSSIP_ITEM_USHER "I wish to to visit the Rise of the Defiler."

enum eUsherTeleport
{
SPELL_TELEPORT_SINGLE           = 12885,
SPELL_TELEPORT_SINGLE_IN_GROUP  = 13142,
SPELL_TELEPORT_GROUP            = 27686
};

class npc_deathly_usher : public CreatureScript
{
public:
    npc_deathly_usher() : CreatureScript("npc_deathly_usher")
    { }

    class npc_deathly_usherAI : public ScriptedAI
    {
    public:
        npc_deathly_usherAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if(pPlayer->GetQuestStatus(3628) == QUEST_STATUS_INCOMPLETE && pPlayer->HasItemCount(10757, 1))
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_USHER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if(action == GOSSIP_ACTION_INFO_DEF)
            {
                player->CLOSE_GOSSIP_MENU();
                me->CastSpell(player, SPELL_TELEPORT_SINGLE, true);
            }

            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_deathly_usherAI(creature);
    }
};



/*######
## npc_fallen_hero_of_horde
######*/

//TODO translate
#define GOSSIP_H_F1 "Why are you here?"
#define GOSSIP_H_F2 "Continue story..."

#define GOSSIP_ITEM_FALLEN "Continue..."

#define GOSSIP_ITEM_FALLEN1 "What could be worse than death?"
#define GOSSIP_ITEM_FALLEN2 "Subordinates?"
#define GOSSIP_ITEM_FALLEN3 "What are the stones of binding?"
#define GOSSIP_ITEM_FALLEN4 "You can count on me, Hero"
#define GOSSIP_ITEM_FALLEN5 "I shall"

class npc_fallen_hero_of_horde : public CreatureScript
{
public:
    npc_fallen_hero_of_horde() : CreatureScript("npc_fallen_hero_of_horde")
    { }

    class npc_fallen_hero_of_hordeAI : public ScriptedAI
    {
    public:
        npc_fallen_hero_of_hordeAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu( me->GetGUID() );

            if (pPlayer->GetQuestStatus(2784) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_H_F1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            if (pPlayer->GetQuestStatus(2801) == QUEST_STATUS_INCOMPLETE && pPlayer->GetTeam() == HORDE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_H_F2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

            if (pPlayer->GetQuestStatus(2801) == QUEST_STATUS_INCOMPLETE && pPlayer->GetTeam() == ALLIANCE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_H_F1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FALLEN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                    player->SEND_GOSSIP_MENU_TEXTID(1392, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+11:
                    player->SEND_GOSSIP_MENU_TEXTID(1411, me->GetGUID());
                    if (player->GetQuestStatus(2784) == QUEST_STATUS_INCOMPLETE)
                        player->AreaExploredOrEventHappens(2784);
                    if (player->GetTeam() == ALLIANCE)
                    {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FALLEN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                        player->SEND_GOSSIP_MENU_TEXTID(1411, me->GetGUID());
                    }
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_FALLEN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                    player->SEND_GOSSIP_MENU_TEXTID(1451, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+21:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_FALLEN1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
                    player->SEND_GOSSIP_MENU_TEXTID(1452, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+22:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_FALLEN2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
                    player->SEND_GOSSIP_MENU_TEXTID(1453, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+23:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_FALLEN3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
                    player->SEND_GOSSIP_MENU_TEXTID(1454, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+24:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_FALLEN4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
                    player->SEND_GOSSIP_MENU_TEXTID(1455, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+25:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_FALLEN5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
                    player->SEND_GOSSIP_MENU_TEXTID(1456, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+26:
                    player->CLOSE_GOSSIP_MENU();
                    player->AreaExploredOrEventHappens(2801);
                    break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fallen_hero_of_hordeAI(creature);
    }
};



void AddSC_blasted_lands()
{

    new npc_deathly_usher();

    new npc_fallen_hero_of_horde();
}

