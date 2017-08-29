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


        virtual bool GossipHello(Player* pPlayer) override
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Se transformer en gnome mâle.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Se transformer en gnome femelle.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(907, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            switch(action)
            {
            case GOSSIP_ACTION_INFO_DEF:
                pPlayer->AddAura(SPELL_ILLUSION_GNOME_MALE,pPlayer);
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                pPlayer->AddAura(SPELL_ILLUSION_GNOME_FEMALE,pPlayer);
                break;
            }
            
            pPlayer->PlayerTalkClass->SendCloseGossip();
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
