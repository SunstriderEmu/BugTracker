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
SDName: npc_xp_blocker
SD%Complete: 100
SDComment: Block/Unblock XP for characters (to allow twinks)
SDCategory: NPCs
EndScriptData
*/

/* ContentData
npc_xp_blocker
EndContentData */



#define GOSSIP_BLOCK_XP     "Je souhaite bloquer ma barre d'expérience."
#define GOSSIP_UNBLOCK_XP   "Je souhaite débloquer ma barre d'expérience."

#define BLOCK_XP_PRICE      100000       // 10 gold

class npc_xp_blocker : public CreatureScript
{
public:
    npc_xp_blocker() : CreatureScript("npc_xp_blocker")
    { }

    class npc_xp_blockerAI : public ScriptedAI
    {
    public:
        npc_xp_blockerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->IsXpBlocked())
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNBLOCK_XP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            else
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_BLOCK_XP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2, "Confirmer le bloquage d'expérience ?", BLOCK_XP_PRICE, false);
                
            pPlayer->SEND_GOSSIP_MENU_TEXTID(42, me->GetGUID());
            
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch (action) {
            case GOSSIP_ACTION_INFO_DEF+1:      // Unblock, free
                player->SetXpBlocked(false);
                me->Whisper("Experience unfreezed.", LANG_UNIVERSAL, player);
                player->SaveToDB();
                break;
            case GOSSIP_ACTION_INFO_DEF+2:      // Block, 10 gold
                if (player->GetMoney() > BLOCK_XP_PRICE) {
                    player->SetXpBlocked(true);
                    me->Whisper("Experience freezed.", LANG_UNIVERSAL, player);
                    player->ModifyMoney(-(int32)BLOCK_XP_PRICE);
                    player->SaveToDB();
                }
                else
                    me->Whisper("You do not have enough money.", LANG_UNIVERSAL, player);
                break;
            }
            
            player->PlayerTalkClass->SendCloseGossip();
            
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_xp_blockerAI(creature);
    }
};



void AddSC_npc_xp_blocker()
{
    
    new npc_xp_blocker();
}
