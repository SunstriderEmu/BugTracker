
/* ScriptData
SDName: npc_rez
SD%Complete: 100
SDComment: Custom NPC that rez all players in a given range every 30 sec (like in battlegrounds)
SDCategory: Custom
EndScriptData */



#define SPELL_SPIRIT_HEAL       22012

class npc_rez : public CreatureScript
{
public:
    npc_rez() : CreatureScript("npc_rez")
    { }

    class npc_rezAI : public ScriptedAI
    {
    public:
        npc_rezAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (!pPlayer->IsAlive())
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ramenez-moi à la vie", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            
            pPlayer->SEND_GOSSIP_MENU_TEXTID(907, me->GetGUID());
            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            if (action == GOSSIP_ACTION_INFO_DEF+1) {
                pPlayer->ResurrectPlayer(1.0f);
                pPlayer->SpawnCorpseBones();
                pPlayer->PlayerTalkClass->SendCloseGossip();
                
                return true;
            }
            
            return false;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_rezAI(creature);
    }
};



void AddSC_npc_rez()
{
    
    new npc_rez();
}
