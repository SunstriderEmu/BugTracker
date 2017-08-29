
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

class npc_teleporter : public CreatureScript
{
public:
    npc_teleporter() : CreatureScript("npc_teleporter")
    { }

    class npc_teleporterAI : public ScriptedAI
    {
    public:
        npc_teleporterAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je souhaite être téléporté.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            
            if (pPlayer->IsGameMaster()) //add an option to check guid of spawned arrivals
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Quels sont les GUIDs des PNJ d'arrivée spawn ?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                
            pPlayer->SEND_GOSSIP_MENU_TEXTID(907,me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            if (action == GOSSIP_ACTION_INFO_DEF)
            {
                if (pPlayer->HasLevelInRangeForTeleport() || pPlayer->IsGameMaster()) {
                    uint32 destEntry;
                    if(me->GetCreatureTemplate()->Entry == NPC_TELEPORTER_ENTRY)
                        destEntry = pPlayer->GetTeam() == HORDE ? NPC_ARRIVAL_HORDE_1 : NPC_ARRIVAL_ALLY_1; //depends on player's team
                    else
                        destEntry = pPlayer->GetTeam() == HORDE ? NPC_ARRIVAL_HORDE_2 : NPC_ARRIVAL_ALLY_2;
                    
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
                        me->Whisper("Error: No destination", LANG_UNIVERSAL, pPlayer);
                        pPlayer->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                }
                else {
                    me->Whisper("Your level is not in the correct range.", LANG_UNIVERSAL, pPlayer);
                    pPlayer->PlayerTalkClass->SendCloseGossip();
                    return false;
                }
            }
            
            if (action == GOSSIP_ACTION_INFO_DEF+1 && pPlayer->IsGameMaster()) //double check
            {
                uint32 destEntry1, destEntry2;
                if(me->GetCreatureTemplate()->Entry == NPC_TELEPORTER_ENTRY)
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
                    me->Whisper("No destination NPC found.", LANG_UNIVERSAL, pPlayer);
                    pPlayer->PlayerTalkClass->SendCloseGossip();
                    return false;
                }
                else
                {
                    do
                    {
                        Field *fields = result->Fetch();
                        std::string guid = fields[0].GetString();
                        me->Whisper(guid.c_str(), LANG_UNIVERSAL, pPlayer);
                    }while (result->NextRow());

                    pPlayer->PlayerTalkClass->SendCloseGossip();
                }
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_teleporterAI(creature);
    }
};



/*######
## AddSC
######*/

void AddSC_npc_teleporter()
{
    
    new npc_teleporter();
}
