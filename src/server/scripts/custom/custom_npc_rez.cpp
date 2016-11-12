/* Copyright (C) 2006 - 2010 WoWMania Core <https://scriptdev2.svn.sourceforge.net/>
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
SDName: npc_rez
SD%Complete: 100
SDComment: Custom NPC that rez all players in a given range every 30 sec (like in battlegrounds)
SDCategory: Custom
EndScriptData */



#define SPELL_SPIRIT_HEAL       22012

bool GossipHello_npc_rez(Player* pPlayer, Creature* pCreature)
{
    if (!pPlayer->IsAlive())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ramenez-moi à la vie", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    
    pPlayer->SEND_GOSSIP_MENU_TEXTID(907, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_rez(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1) {
        pPlayer->ResurrectPlayer(1.0f);
        pPlayer->SpawnCorpseBones();
        pPlayer->PlayerTalkClass->SendCloseGossip();
        
        return true;
    }
    
    return false;
}

void AddSC_npc_rez()
{
    OLDScript* newscript;
    
    newscript = new OLDScript;
    newscript->Name = "npc_rez";
    newscript->OnGossipHello = &GossipHello_npc_rez;
    newscript->OnGossipSelect = &GossipSelect_npc_rez;
    sScriptMgr->RegisterOLDScript(newscript);
}
