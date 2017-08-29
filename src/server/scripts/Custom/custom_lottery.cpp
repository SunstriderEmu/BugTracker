
/* ScriptData
SDName: npc_lottery
SD%Complete: 100
SDComment: NPC lottery
SDCategory: Custom Scripts
EndScriptData */


#include "ObjectMgr.h"
#include <cstring>
#include "CharacterCache.h"

/*######
## npc_lottery
######*/

class npc_lottery : public CreatureScript
{
public:
    npc_lottery() : CreatureScript("npc_lottery")
    { }

    class npc_lotteryAI : public ScriptedAI
    {
    public:
        npc_lotteryAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je m'inscris à la loterie.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            
            if (pPlayer->IsGameMaster())
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lancer le tirage au sort", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                
            pPlayer->SEND_GOSSIP_MENU_TEXTID(43, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            switch (action) {
            case GOSSIP_ACTION_INFO_DEF:
                // Check not already registered and check 30d played
                if (pPlayer->GetTotalAccountPlayedTime() > 1728000 || pPlayer->GetSession()->GetSecurity() > 0) {
                    uint32 playerAccountId = pPlayer->GetSession()->GetAccountId();
                    QueryResult result = CharacterDatabase.PQuery("SELECT * FROM lottery WHERE accountid = %u OR ip = '%s'", playerAccountId, pPlayer->GetSession()->GetRemoteAddress().c_str());
                    if (!result) {
                        CharacterDatabase.PExecute("INSERT INTO lottery VALUES (%u, %u, %I64u, %u, '%s')", pPlayer->GetGUIDLow(), playerAccountId, time(nullptr), pPlayer->GetTeam(), pPlayer->GetSession()->GetRemoteAddress().c_str());
                        pPlayer->SEND_GOSSIP_MENU_TEXTID(44, me->GetGUID());
                    }
                    else {
                        pPlayer->SEND_GOSSIP_MENU_TEXTID(45, me->GetGUID());
                    }
                }
                else {
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(46, me->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF+1:
                uint32 winner;
                QueryResult result = CharacterDatabase.PQuery("SELECT DISTINCT guid FROM lottery ORDER BY RAND() LIMIT 10", HORDE);
                if (!result)
                    break;
                    
                std::ostringstream oss;
                std::string winner_str;
                
                uint32 num = 1;
                    
                do {
                    oss.str("");
                    Field* fields = result->Fetch();
                    
                    winner = fields[0].GetUInt32();
                    sCharacterCache->GetCharacterNameByGuid(winner, winner_str);
                    
                    oss << "Le gagnant numéro " << num << " est " << winner_str << " !";
                    me->Yell(oss.str().c_str(), LANG_UNIVERSAL, nullptr);
                    
                    num++;
                } while (result->NextRow());

                break;
            }
            
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lotteryAI(creature);
    }
};



void AddSC_npc_lottery()
{
    
    new npc_lottery();
}
