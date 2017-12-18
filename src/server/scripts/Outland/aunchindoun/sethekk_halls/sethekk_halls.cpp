
/* ScriptData
SDName: SethekkHalls
SD%Complete: 100
SDComment: Lakka's gossip to complete quest 10097
SDCategory: Sethekk Halls
EndScriptData */

/* ContentData
npc_lakka
go_ravens_claw
EndContentData */


#include "def_sethekk_halls.h"

/*######
## npc_lakka
######*/

#define QUEST_BRO_AGAINST_BRO   10097
#define GOSSIP_FREE_LAKKA       "You're free, Lakka!"

class npc_lakka : public CreatureScript
{
public:
    npc_lakka() : CreatureScript("npc_lakka")
    { }

   class npc_lakkaAI : public ScriptedAI
   {
   public:
        npc_lakkaAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if( player->GetQuestStatus(QUEST_BRO_AGAINST_BRO) == QUEST_STATUS_INCOMPLETE )
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FREE_LAKKA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                SEND_PREPARED_GOSSIP_MENU(player, me);
            }

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if( action == GOSSIP_ACTION_INFO_DEF+1 )
            {
                player->KilledMonsterCredit(18956,me->GetGUID());
                player->CLOSE_GOSSIP_MENU();
            }

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lakkaAI(creature);
    }
};


bool hasDespawned = false;

class RavensClaw : public GameObjectScript
{
public:
    RavensClaw() : GameObjectScript("go_ravens_claw")
    {}

    struct RavensClawAI : public GameObjectAI
    {
        RavensClawAI(GameObject* obj) : GameObjectAI(obj), pInstance(obj->GetInstanceScript()) { }

        InstanceScript* pInstance;

        bool GossipHello(Player* pPlayer) override
        {
            if (pInstance) 
            {
                if (!pInstance->GetGuidData(ANZU_SUMMONER_GUID).IsEmpty() && pPlayer->GetGUID() != pInstance->GetGuidData(ANZU_SUMMONER_GUID)) 
                {      
                    // Hehe, two different players summoning Anzu ? We aren't going to be friends...
                    pPlayer->DealDamage(pPlayer, pPlayer->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);

                    if (Creature* secondAnzu = me->FindNearestCreature(NPC_ANZU, 30.0f, true))
                    {
                        if (!hasDespawned) 
                        {
                            secondAnzu->DisappearAndDie();
                            hasDespawned = true;
                        }
                    }
                }
                else
                    pInstance->SetGuidData(ANZU_SUMMONER_GUID, pPlayer->GetGUID());

                return false;
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new RavensClawAI(go);
    }
};

/*######
## AddSC
######*/

void AddSC_sethekk_halls()
{

    new npc_lakka();
    
    new RavensClaw();
}
