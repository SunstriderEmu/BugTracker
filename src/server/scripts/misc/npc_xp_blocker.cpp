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

bool GossipHello_npc_xp_blocker(Player* pPlayer, Creature* pCreature) {
    if (pPlayer->IsXpBlocked())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNBLOCK_XP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    else
        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_BLOCK_XP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2, "Confirmer le bloquage d'expérience ?", BLOCK_XP_PRICE, false);
        
    pPlayer->SEND_GOSSIP_MENU_TEXTID(42, pCreature->GetGUID());
    
    return true;
}

bool GossipSelect_npc_xp_blocker(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action) {
    switch (action) {
    case GOSSIP_ACTION_INFO_DEF+1:      // Unblock, free
        pPlayer->SetXpBlocked(false);
        pCreature->Whisper("Experience unfreezed.", LANG_UNIVERSAL, pPlayer);
        pPlayer->SaveToDB();
        break;
    case GOSSIP_ACTION_INFO_DEF+2:      // Block, 10 gold
        if (pPlayer->GetMoney() > BLOCK_XP_PRICE) {
            pPlayer->SetXpBlocked(true);
            pCreature->Whisper("Experience freezed.", LANG_UNIVERSAL, pPlayer);
            pPlayer->ModifyMoney(-(int32)BLOCK_XP_PRICE);
            pPlayer->SaveToDB();
        }
        else
            pCreature->Whisper("You do not have enough money.", LANG_UNIVERSAL, pPlayer);
        break;
    }
    
    pPlayer->PlayerTalkClass->SendCloseGossip();
    
    return true;
}

void AddSC_npc_xp_blocker()
{
    OLDScript* newscript;
    
    newscript = new OLDScript;
    newscript->Name = "npc_xp_blocker";
    newscript->OnGossipHello = &GossipHello_npc_xp_blocker;
    newscript->OnGossipSelect = &GossipSelect_npc_xp_blocker;
    sScriptMgr->RegisterOLDScript(newscript);
}
