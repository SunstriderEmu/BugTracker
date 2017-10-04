#define SPELL_ILLUSION_GNOME_MALE 37808
#define SPELL_ILLUSION_GNOME_FEMALE 37809

/*######
## custom_gnominizer
######*/

class custom_gnominizer : public CreatureScript
{
public:
    custom_gnominizer() : CreatureScript("custom_gnominizer")
    { }

    class custom_gnominizerAI : public ScriptedAI
    {
    public:
        custom_gnominizerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Se transformer en gnome mâle.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Se transformer en gnome femelle.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            player->SEND_GOSSIP_MENU_TEXTID(907, me->GetGUID());

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch(action)
            {
            case GOSSIP_ACTION_INFO_DEF:
                player->AddAura(SPELL_ILLUSION_GNOME_MALE, player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->AddAura(SPELL_ILLUSION_GNOME_FEMALE, player);
                break;
            }
            
            player->PlayerTalkClass->SendCloseGossip();
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new custom_gnominizerAI(creature);
    }
};



void AddSC_custom_gnominizer()
{
    
    new custom_gnominizer();
}
