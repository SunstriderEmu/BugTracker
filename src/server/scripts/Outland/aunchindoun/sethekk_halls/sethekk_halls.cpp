/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

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


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
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
            if (pInstance) {
                if (pInstance->GetData64(ANZU_SUMMONER) != 0 && pPlayer->GetGUID() != pInstance->GetData64(ANZU_SUMMONER)) {      // Hehe, two different players summoning Anzu ? We aren't going to be friends...
                    pPlayer->DealDamage(pPlayer, pPlayer->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);

                    if (Creature* secondAnzu = me->FindNearestCreature(23035, 30.0f, true)) {
                        if (!hasDespawned) {
                            secondAnzu->DisappearAndDie();
                            hasDespawned = true;
                        }
                    }
                }
                else
                    pInstance->SetData64(ANZU_SUMMONER, pPlayer->GetGUID());
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
