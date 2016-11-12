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
SDName: Black_Temple
SD%Complete: 95
SDComment: Spirit of Olum: Player Teleporter to Seer Kanai Teleport after defeating Naj'entus and Supremus. TODO: Find proper gossip.
SDCategory: Black Temple
EndScriptData */

/* ContentData
npc_spirit_of_olum
npc_spirit_of_udalo
EndContentData */


#include "def_black_temple.h"

/*###
# npc_spirit_of_olum
####*/

//TODO translate
#define SPELL_TELEPORT      41566                           // s41566 - Teleport to Ashtongue NPC's
#define GOSSIP_OPTION_OLUM1        "Téléportez-moi au Sanctuaire des ombres."
#define SPELL_TELEPORT_UDALO    41570
#define GOSSIP_OPTION_UDALO            "Teleportez-moi au Conseil Illidari."
#define GOSSIP_

bool GossipHello_npc_spirit_of_olum(Player* player, Creature* _Creature)
{
    InstanceScript* pInstance = ((InstanceScript*)_Creature->GetInstanceScript());

    if (pInstance)
    {
        if (pInstance->GetData(DATA_SUPREMUSEVENT) == DONE && pInstance->GetData(DATA_HIGHWARLORDNAJENTUSEVENT) == DONE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_OLUM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU_TEXTID(4100, _Creature->GetGUID());
            return true;
        }
        if (pInstance->GetData(DATA_ILLIDARICOUNCILEVENT) == DONE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_UDALO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU_TEXTID(4100, _Creature->GetGUID());
            return true;
        }
    }
    player->SEND_GOSSIP_MENU_TEXTID(4101, _Creature->GetGUID());
    return true;
}

bool GossipSelect_npc_spirit_of_olum(Player* player, Creature* _Creature, uint32 sender, uint32 action)
{
    player->CLOSE_GOSSIP_MENU();
    if(action == GOSSIP_ACTION_INFO_DEF + 1) {
        player->InterruptNonMeleeSpells(false);
        player->CastSpell(player, SPELL_TELEPORT, false);
    }
    else if (action == GOSSIP_ACTION_INFO_DEF + 2) {
        player->InterruptNonMeleeSpells(false);
        player->CastSpell(player, SPELL_TELEPORT_UDALO, false);
    }

    return true;
}

/*######
## npc_spirit_of_udalo
######*/

bool GossipHello_npc_spirit_of_udalo(Player* player, Creature* _Creature)
{
    InstanceScript* pInstance = ((InstanceScript*)_Creature->GetInstanceScript());

    if(pInstance && (pInstance->GetData(DATA_ILLIDARICOUNCILEVENT) >= DONE))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_UDALO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    SEND_PREPARED_GOSSIP_MENU(player, _Creature);
    return true;
}

bool GossipSelect_npc_spirit_of_udalo(Player* player, Creature* _Creature, uint32 sender, uint32 action)
{
    if(action == GOSSIP_ACTION_INFO_DEF + 1)
        player->CLOSE_GOSSIP_MENU();

    player->InterruptNonMeleeSpells(false);
    player->CastSpell(player, SPELL_TELEPORT_UDALO, false);
    return true;
}

void AddSC_black_temple()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name = "npc_spirit_of_olum";
    newscript->OnGossipHello = &GossipHello_npc_spirit_of_olum;
    newscript->OnGossipSelect = &GossipSelect_npc_spirit_of_olum;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_spirit_of_udalo";
    newscript->OnGossipHello = &GossipHello_npc_spirit_of_udalo;
    newscript->OnGossipSelect = &GossipSelect_npc_spirit_of_udalo;
    sScriptMgr->RegisterOLDScript(newscript);
}

