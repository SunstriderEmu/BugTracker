
#include "WorldPacket.h"

#define X_DIRECTION 0.89102085f
#define Y_DIRECTION 0.45396239f

enum Actions {
    ACTION_SPEED,
    ACTION_ANGLE,
    ACTION_GO
};


class npc_catapultmaster : public CreatureScript
{
public:
    npc_catapultmaster() : CreatureScript("npc_catapultmaster")
    { }

    class  catapultmasterAI : public ScriptedAI
    {
        public:
        float horizontal_speed;
        float vertical_speed;
        catapultmasterAI(Creature* creature) : 
            ScriptedAI(creature),
            horizontal_speed(-200.0f),
            vertical_speed(-10.0f)
        {}
    
        void JustEngagedWith(Unit* who)
        override {}

        virtual bool GossipHello(Player* player) override
        {
            
            player->ADD_GOSSIP_ITEM_EXTENDED( 0, "Vitesse", GOSSIP_SENDER_MAIN, ACTION_SPEED, "", 0, true);
            player->ADD_GOSSIP_ITEM_EXTENDED( 0, "Angle", GOSSIP_SENDER_MAIN, ACTION_ANGLE, "", 0, true);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "GO !", GOSSIP_SENDER_MAIN, ACTION_GO);
                
            player->SEND_GOSSIP_MENU_TEXTID(3,me->GetGUID());

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch(action)
            {
            case ACTION_GO:
                me->Say("YOLO !", LANG_UNIVERSAL, nullptr);

                WorldPacket data(SMSG_MOVE_KNOCK_BACK, (8+4+4+4+4+4));
                data << player->GetPackGUID();
                data << uint32(0);                                      // Sequence
                data << X_DIRECTION;                                    // x direction
                data << Y_DIRECTION;                                    // y direction
                data << horizontal_speed;      // Horizontal speed
                data << vertical_speed;                              // Z Movement speed (vertical)

                player->GetSession()->SendPacket(&data);
                break;
            }

            return true;
        }

        virtual bool GossipSelectCode(Player* player, uint32 sender, uint32 gossipListId, const char* Code) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch(action)
            {
            case ACTION_SPEED:
                horizontal_speed = -atof(Code);
                break;
            case ACTION_ANGLE:
                vertical_speed = -atof(Code);
                break;
            }

            player->PlayerTalkClass->SendCloseGossip();
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new catapultmasterAI(creature);
    }
};

void AddSC_catapultmaster()
{
    new npc_catapultmaster();
}
