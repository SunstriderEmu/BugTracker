/* Custom OLDScript - WoWManiaCore
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
SDName: Custom_Example
SD%Complete: 100
SDComment: NPC teleporter to help organizing events
SDCategory: Custom Scripts
EndScriptData */


#include <cstring>

#define NPC_TELEPORTER_ENTRY 41
#define NPC_ARRIVAL_HORDE_1 42
#define NPC_ARRIVAL_ALLY_1 44
#define NPC_ARRIVAL_HORDE_2 91504
#define NPC_ARRIVAL_ALLY_2 91505

/*######
## npc_teleporter
######*/

bool GossipHello_npc_teleporter(Player *pPlayer, Creature *pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je souhaite être téléporté.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    
    if (pPlayer->IsGameMaster()) //add an option to check guid of spawned arrivals
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Quels sont les GUIDs des PNJ d'arrivée spawn ?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        
    pPlayer->SEND_GOSSIP_MENU_TEXTID(907,pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_teleporter(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF)
    {
        if (pPlayer->HasLevelInRangeForTeleport() || pPlayer->IsGameMaster()) {
            uint32 destEntry;
            if(pCreature->GetCreatureTemplate()->Entry == NPC_TELEPORTER_ENTRY)
                destEntry = pPlayer->GetTeam() == TEAM_HORDE ? NPC_ARRIVAL_HORDE_1 : NPC_ARRIVAL_ALLY_1; //depends on player's team
            else
                destEntry = pPlayer->GetTeam() == TEAM_HORDE ? NPC_ARRIVAL_HORDE_2 : NPC_ARRIVAL_ALLY_2;
            
            //get coordinates of target in DB
            QueryResult result = WorldDatabase.PQuery("SELECT map, position_x, position_y, position_z, orientation FROM creature WHERE id = %u LIMIT 1", destEntry);
            
            uint32 mapId;
            float destX;
            float destY;
            float destZ;
            float destO;
            if (result)
            {
                Field *fields = result->Fetch();
                mapId = fields[0].GetUInt32();
                destX = fields[1].GetFloat();
                destY = fields[2].GetFloat();
                destZ = fields[3].GetFloat();
                destO = fields[4].GetFloat();
            
                Trinity::NormalizeMapCoord(destX);
            
                pPlayer->TeleportTo(mapId, destX, destY, destZ, destO);
            }
            else
            {
                pCreature->Whisper("Error: No destination", LANG_UNIVERSAL, pPlayer);
                pPlayer->PlayerTalkClass->SendCloseGossip();
                return false;
            }
        }
        else {
            pCreature->Whisper("Your level is not in the correct range.", LANG_UNIVERSAL, pPlayer);
            pPlayer->PlayerTalkClass->SendCloseGossip();
            return false;
        }
    }
    
    if (action == GOSSIP_ACTION_INFO_DEF+1 && pPlayer->IsGameMaster()) //double check
    {
        uint32 destEntry1, destEntry2;
        if(pCreature->GetCreatureTemplate()->Entry == NPC_TELEPORTER_ENTRY)
        {
            destEntry1 = NPC_ARRIVAL_HORDE_1;
            destEntry2 = NPC_ARRIVAL_ALLY_1;
        } else {
            destEntry1 = NPC_ARRIVAL_HORDE_2;
            destEntry2 = NPC_ARRIVAL_ALLY_2;
        }

        QueryResult result = WorldDatabase.PQuery("SELECT guid FROM creature WHERE id = %u OR id = %u",destEntry1,destEntry2);
        
        if (!result)
        {
            pCreature->Whisper("No destination NPC found.", LANG_UNIVERSAL, pPlayer);
            pPlayer->PlayerTalkClass->SendCloseGossip();
            return false;
        }
        else
        {
            do
            {
                Field *fields = result->Fetch();
                std::string guid = fields[0].GetString();
                pCreature->Whisper(guid.c_str(), LANG_UNIVERSAL, pPlayer);
            }while (result->NextRow());

            pPlayer->PlayerTalkClass->SendCloseGossip();
        }
    }
    return true;
}

/*######
## AddSC
######*/

void AddSC_npc_teleporter()
{
    OLDScript *newscript;
    
    newscript = new OLDScript;
    newscript->Name = "npc_teleporter";
    newscript->OnGossipHello = &GossipHello_npc_teleporter;
    newscript->OnGossipSelect = &GossipSelect_npc_teleporter;
    sScriptMgr->RegisterOLDScript(newscript);
}
