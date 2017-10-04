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
SDName: Searing_Gorge
SD%Complete: 80
SDComment: Quest support: 3377, 3441 (More accurate info on Kalaran needed). Lothos Riftwaker teleport to Molten Core.
SDCategory: Searing Gorge
EndScriptData */

/* ContentData
npc_kalaran_windblade
npc_lothos_riftwaker
npc_zamael_lunthistle
EndContentData */



/*######
## npc_kalaran_windblade
######*/

class npc_kalaran_windblade : public CreatureScript
{
public:
    npc_kalaran_windblade() : CreatureScript("npc_kalaran_windblade")
    { }

    class npc_kalaran_windbladeAI : public ScriptedAI
    {
    public:
        npc_kalaran_windbladeAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            //todo translate
            if (player->GetQuestStatus(3441) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Expliquez-moi ce qui dirige votre vengeance ?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Continuez s'il vous plait", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU_TEXTID(1954, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Laissez-moi en discuter avec mes collègues", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(1955, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->CLOSE_GOSSIP_MENU();
                    player->AreaExploredOrEventHappens(3441);
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kalaran_windbladeAI(creature);
    }
};



/*######
## npc_lothos_riftwaker
######*/

class npc_lothos_riftwaker : public CreatureScript
{
public:
    npc_lothos_riftwaker() : CreatureScript("npc_lothos_riftwaker")
    { }

    class npc_lothos_riftwakerAI : public ScriptedAI
    {
    public:
        npc_lothos_riftwakerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if (player->GetQuestRewardStatus(7487) || player->GetQuestRewardStatus(7848))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport me to Molten Core", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            player->SEND_GOSSIP_MENU_TEXTID(player->GetGossipTextId(me), me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(409, 1096, -467, -104.6, 3.64);
            }

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lothos_riftwakerAI(creature);
    }
};



/*######
## npc_zamael_lunthistle
######*/

class npc_zamael_lunthistle : public CreatureScript
{
public:
    npc_zamael_lunthistle() : CreatureScript("npc_zamael_lunthistle")
    { }

    class npc_zamael_lunthistleAI : public ScriptedAI
    {
    public:
        npc_zamael_lunthistleAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if (player->GetQuestStatus(3377) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Racontez-moi votre histoire", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            player->SEND_GOSSIP_MENU_TEXTID(1920, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Continuez...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU_TEXTID(1921, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Au revoir", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(1922, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->CLOSE_GOSSIP_MENU();
                    player->AreaExploredOrEventHappens(3377);
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_zamael_lunthistleAI(creature);
    }
};



/*######
##
######*/

void AddSC_searing_gorge()
{

    new npc_kalaran_windblade();

    new npc_lothos_riftwaker();

    new npc_zamael_lunthistle();
}

