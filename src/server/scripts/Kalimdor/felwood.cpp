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
SDName: Felwood
SD%Complete: 95
SDComment: Quest support: 4101, 4102
SDCategory: Felwood
EndScriptData */

/* ContentData
npcs_riverbreeze_and_silversky
EndContentData */



/*######
## npcs_riverbreeze_and_silversky
######*/

#define GOSSIP_ITEM_BEACON  "Please make me a Cenarion Beacon"

class npcs_riverbreeze_and_silversky : public CreatureScript
{
public:
    npcs_riverbreeze_and_silversky() : CreatureScript("npcs_riverbreeze_and_silversky")
    { }

    class npcs_riverbreeze_and_silverskyAI : public ScriptedAI
    {
    public:
        npcs_riverbreeze_and_silverskyAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            uint32 eCreature = me->GetEntry();

            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu( me->GetGUID() );

            if (eCreature==9528)
            {
                if (pPlayer->GetQuestRewardStatus(4101))
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BEACON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2848, me->GetGUID());
                }
                else if (pPlayer->GetTeam() == HORDE)
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2845, me->GetGUID());
                else
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2844, me->GetGUID());
            }

            if (eCreature == 9529)
            {
                if (pPlayer->GetQuestRewardStatus(4102))
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BEACON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2849, me->GetGUID());
                }
                else if (pPlayer->GetTeam() == ALLIANCE)
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2843, me->GetGUID());
                else
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2842, me->GetGUID());
            }

            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action==GOSSIP_ACTION_INFO_DEF+1)
            {
                player->CLOSE_GOSSIP_MENU();
                me->CastSpell(player, 15120, false);
            }
            
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npcs_riverbreeze_and_silverskyAI(creature);
    }
};



void AddSC_felwood()
{

    new npcs_riverbreeze_and_silversky();
}

