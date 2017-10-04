#include <sstream>


class npc_interpreter : public CreatureScript
{
public:
    npc_interpreter() : CreatureScript("npc_interpreter")
    { }

    class npc_interpreterAI : public ScriptedAI
    {
        public:
        npc_interpreterAI(Creature *c) : ScriptedAI(c) 
        {}
    
        void EnterCombat(Unit* /* who */) override {}

        virtual bool GossipHello(Player* player) override
        {
            
            player->ADD_GOSSIP_ITEM_EXTENDED( 0, "Repeter", GOSSIP_SENDER_MAIN, 1, "", 0, true);
                
            player->SEND_GOSSIP_MENU_TEXTID(3,me->GetGUID());

            return true;

        }


        virtual bool GossipSelectCode(Player* player, uint32 menuId, uint32 gossipListId, const char* Code) override
        {
            std::stringstream text;
            text << player->GetName() << " dit : " << Code;
            me->Say(text.str().c_str(),LANG_UNIVERSAL,nullptr);

            player->CLOSE_GOSSIP_MENU();
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_interpreterAI(creature);
    }
};



 
void AddSC_npc_interpreter()
{
    
    new npc_interpreter();
}
