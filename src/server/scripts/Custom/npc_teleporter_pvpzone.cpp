#define GOSSIP_MENU 907 //change me later?
#define PVPZONE_ARRIVAL_ALLIANCE 1, 4809.387207, -2012.331177, 1068.865967, 1.220856 
#define PVPZONE_ARRIVAL_HORDE 1, 4803.802734, -1924.144043, 1069.050171, 5.099141

class npc_teleporter_pvpzone : public CreatureScript
{
public:
    npc_teleporter_pvpzone() : CreatureScript("npc_teleporter_pvpzone")
    { }

    class npc_teleporter_pvpzoneAI : public ScriptedAI
    {
    public:
        npc_teleporter_pvpzoneAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Téléportez-moi dans la zone PvP.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport me in PvP Zone.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU,me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            	float x = {}, y = {}, z = {}, o = {};
                uint32 map = 0;
            	bool loaded = false;
            
                QueryResult query = WorldDatabase.PQuery("SELECT position_x, position_y, position_z, orientation, map FROM game_tele WHERE name = 'duelzone'");
                if (query) {
                    Field* fields = query->Fetch();
                    if(fields)
                    {
                        x = fields[0].GetFloat();
                        y = fields[1].GetFloat();
                        z = fields[2].GetFloat();
                        o = fields[3].GetFloat();
                        map = fields[4].GetUInt32();
            			loaded = true;
                    }
            	}
            
            	if(!loaded)
            	{
            		TC_LOG_ERROR("scripts", "GossipSelect_npc_teleporter_pvpzone: Could not get duelzone coordinates from DB");
            		return true;
            	}
                
                if (action == GOSSIP_ACTION_INFO_DEF)
                {
                    if(!map) //return to default values
                    {
                        if(pPlayer->GetTeam() == HORDE)
                            pPlayer->TeleportTo(PVPZONE_ARRIVAL_HORDE);
                        else
                            pPlayer->TeleportTo(PVPZONE_ARRIVAL_ALLIANCE);
                    } else {
                        pPlayer->TeleportTo(map,x,y,z,o);
                    }
                    pPlayer->PlayerTalkClass->SendCloseGossip();
                    return true;
                }
                return false;
            
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_teleporter_pvpzoneAI(creature);
    }
};



void AddSC_npc_teleporter_pvpzone()
{
    
    new npc_teleporter_pvpzone();
}
