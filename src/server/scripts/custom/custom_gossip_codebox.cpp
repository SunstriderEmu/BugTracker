
/* ScriptData
SDName: Custom_Gossip_Codebox
SD%Complete: 100
SDComment: Show a codebox in gossip option
SDCategory: OLDScript Examples
EndScriptData */


#include <cstring>

//This function is called when the player opens the gossip menubool
bool GossipHello_custom_gossip_codebox(Player *player, Creature *_Creature)
{
    player->ADD_GOSSIP_ITEM_EXTENDED(0, "A quiz: what's your name?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'm not interested", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    player->SEND_GOSSIP_MENU_TEXTID(907,_Creature->GetGUID());
    return true;
}

//This function is called when the player clicks an option on the gossip menubool
bool GossipSelect_custom_gossip_codebox(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
    if(action == GOSSIP_ACTION_INFO_DEF+2)
    {
        _Creature->Say("Normal select, guess you're not interested.", LANG_UNIVERSAL, nullptr);
        player->CLOSE_GOSSIP_MENU();
    }
    return true;
}

bool GossipSelectWithCode_custom_gossip_codebox( Player *player, Creature *_Creature, uint32 sender, uint32 action, const char* sCode )
{
    if(sender == GOSSIP_SENDER_MAIN)
    {
        if(action == GOSSIP_ACTION_INFO_DEF+1)
        {
            if(std::strcmp(sCode, player->GetName().c_str())!=0)
            {
                _Creature->Say("Wrong!", LANG_UNIVERSAL, nullptr);
                _Creature->CastSpell(player, 12826, true);
            }
            else
            {
                _Creature->Say("You're right, you are allowed to see my inner secrets.", LANG_UNIVERSAL, nullptr);
                _Creature->CastSpell(player, 26990, true);
            }
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
    }
    return false;
}

void AddSC_custom_gossip_codebox()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="custom_gossip_codebox";
    newscript->OnGossipHello =           &GossipHello_custom_gossip_codebox;
    newscript->OnGossipSelect =          &GossipSelect_custom_gossip_codebox;
    newscript->OnGossipSelectCode =  &GossipSelectWithCode_custom_gossip_codebox;
    sScriptMgr->RegisterOLDScript(newscript);
}

