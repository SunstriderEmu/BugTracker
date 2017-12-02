
/* ScriptData
SDName: Custom_Gossip_Codebox
SD%Complete: 100
SDComment: Show a codebox in gossip option
SDCategory: OLDScript Examples
EndScriptData */


#include <cstring>

//This function is called when the player opens the gossip menubool
class custom_gossip_codebox : public CreatureScript
{
public:
    custom_gossip_codebox() : CreatureScript("custom_gossip_codebox")
    { }

    class custom_gossip_codeboxAI : public ScriptedAI
    {
    public:
        custom_gossip_codeboxAI(Creature* creature) : ScriptedAI(creature)
        {}

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM_EXTENDED(0, "A quiz: what's your name?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'm not interested", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

            player->SEND_GOSSIP_MENU_TEXTID(907,me->GetGUID());
            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if(action == GOSSIP_ACTION_INFO_DEF+2)
            {
                me->Say("Normal select, guess you're not interested.", LANG_UNIVERSAL, nullptr);
                player->CLOSE_GOSSIP_MENU();
            }
            return true;
        }

        virtual bool GossipSelectCode(Player* player, uint32 menuId, uint32 gossipListId, const char* sCode) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            uint32 const sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
            if(sender == GOSSIP_SENDER_MAIN)
            {
                if(action == GOSSIP_ACTION_INFO_DEF+1)
                {
                    if(std::strcmp(sCode, player->GetName().c_str())!=0)
                    {
                        me->Say("Wrong!", LANG_UNIVERSAL, nullptr);
                        me->CastSpell(player, 12826, TRIGGERED_FULL_MASK);
                    }
                    else
                    {
                        me->Say("You're right, you are allowed to see my inner secrets.", LANG_UNIVERSAL, nullptr);
                        me->CastSpell(player, 26990, TRIGGERED_FULL_MASK);
                    }
                    player->CLOSE_GOSSIP_MENU();
                    return true;
                }
            }
            return false;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new custom_gossip_codeboxAI(creature);
    }
};


//This function is called when the player clicks an option on the gossip menubool


void AddSC_custom_gossip_codebox()
{
    new custom_gossip_codebox();
}

