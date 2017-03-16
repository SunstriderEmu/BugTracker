#include <sstream>

struct npc_interpreterAI : public ScriptedAI
{
    npc_interpreterAI(Creature *c) : ScriptedAI(c) 
    {}

    void EnterCombat(Unit* /* who */) override {}
};

bool GossipHello_npc_interpreter(Player *player, Creature *_Creature)
{    
    player->ADD_GOSSIP_ITEM_EXTENDED( 0, "Repeter", GOSSIP_SENDER_MAIN, 1, "", 0, true);
        
    player->SEND_GOSSIP_MENU_TEXTID(3,_Creature->GetGUID());

    return true;
}

bool GossipSelectWithCode_npc_interpreter( Player *player, Creature *_Creature, uint32 sender, uint32 action, const char* Code )
{
    std::stringstream text;
    text << player->GetName() << " dit : " << Code;
    _Creature->Say(text.str().c_str(),LANG_UNIVERSAL,nullptr);

    player->CLOSE_GOSSIP_MENU();
    return true;
}

CreatureAI* GetAI_npc_interpreter(Creature *_Creature)
{
    return new npc_interpreterAI (_Creature);
}
 
void AddSC_npc_interpreter()
{
    OLDScript *newscript;
	
    newscript = new OLDScript;
    newscript->Name="npc_interpreter";
    newscript->GetAI = &GetAI_npc_interpreter;
    newscript->OnGossipHello = &GossipHello_npc_interpreter;
    newscript->OnGossipSelectCode = &GossipSelectWithCode_npc_interpreter;
    sScriptMgr->RegisterOLDScript(newscript);
}
