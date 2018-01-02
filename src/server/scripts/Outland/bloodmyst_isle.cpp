/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Bloodmyst_Isle
SD%Complete: 80
SDComment: Quest support: 9670, 9756(gossip items text needed).
SDCategory: Bloodmyst Isle
EndScriptData */

/* ContentData
mob_webbed_creature
npc_captured_sunhawk_agent
npc_razormaw
EndContentData */



/*######
## mob_webbed_creature
######*/

//possible creatures to be spawned
const uint32 possibleSpawns[32] = {17322, 17661, 17496, 17522, 17340, 17352, 17333, 17524, 17654, 17348, 17339, 17345, 17359, 17353, 17336, 17550, 17330, 17701, 17321, 17680, 17325, 17320, 17683, 17342, 17715, 17334, 17341, 17338, 17337, 17346, 17344, 17327};


class mob_webbed_creature : public CreatureScript
{
public:
    mob_webbed_creature() : CreatureScript("mob_webbed_creature")
    { }

    class mob_webbed_creatureAI : public ScriptedAI
    {
        public:
        mob_webbed_creatureAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
        }
    
        void JustDied(Unit* pKiller)
        override {
            uint32 spawnCreatureID = {};
    
            switch(rand()%3)
            {
                case 0:
                    spawnCreatureID = 17681;
                    if (pKiller->GetTypeId() == TYPEID_PLAYER)
                        (pKiller)->ToPlayer()->KilledMonsterCredit(spawnCreatureID, me->GetGUID());
                    break;
                case 1:
                case 2:
                    spawnCreatureID = possibleSpawns[rand()%31];
                    break;
            }
    
            DoSpawnCreature(spawnCreatureID,0,0,0,me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_webbed_creatureAI(creature);
    }
};


/*######
## npc_captured_sunhawk_agent
######*/

#define C_SUNHAWK_TRIGGER 17974

class npc_captured_sunhawk_agent : public CreatureScript
{
public:
    npc_captured_sunhawk_agent() : CreatureScript("npc_captured_sunhawk_agent")
    { }

   class npc_captured_sunhawk_agentAI : public ScriptedAI
   {
   public:
        npc_captured_sunhawk_agentAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->HasAuraEffect(31609,1) && pPlayer->GetQuestStatus(9756) == QUEST_STATUS_INCOMPLETE)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(9136, me->GetGUID());
            }
            else
                pPlayer->SEND_GOSSIP_MENU_TEXTID(9134, me->GetGUID());

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            ClearGossipMenuFor(player);
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU_TEXTID(9137, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                    player->SEND_GOSSIP_MENU_TEXTID(9138, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                    player->SEND_GOSSIP_MENU_TEXTID(9139, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+4:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    player->SEND_GOSSIP_MENU_TEXTID(9140, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+5:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                    player->SEND_GOSSIP_MENU_TEXTID(9141, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+6:
                    player->CLOSE_GOSSIP_MENU();
                    player->TalkedToCreature(C_SUNHAWK_TRIGGER, me->GetGUID());
                    break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_captured_sunhawk_agentAI(creature);
    }
};



/*######
## npc_exarch_admetius
######*/

class npc_exarch_admetius : public CreatureScript
{
public:
    npc_exarch_admetius() : CreatureScript("npc_exarch_admetius")
    { }

   class npc_exarch_admetiusAI : public ScriptedAI
   {
   public:
        npc_exarch_admetiusAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == 9756)
                pPlayer->AddAura(31609, pPlayer);
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_exarch_admetiusAI(creature);
    }
};


/*######
## npc_razormaw
######*/


class npc_razormaw : public CreatureScript
{
public:
    npc_razormaw() : CreatureScript("npc_razormaw")
    { }

    class npc_razormawAI : public ScriptedAI
    {
        public:
        npc_razormawAI(Creature* c) : ScriptedAI(c)
        {
            me->SetDisableGravity(true);
            me->GetMotionMaster()->MovePoint(1, -1204.845581, -12465.271484, 94.779945, false);
            me->SetKeepActive(true);
            landed = false;
        }
        
        bool landed;
        
        void Reset() override
        {
        }
        
        void MovementInform(uint32 type, uint32 id)
        override {
            if (id == 1) {
                me->SetKeepActive(false);
                me->SetDisableGravity(false);
                landed = true;
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
            }
        }
        
        void JustEngagedWith(Unit* who) override
        {
            me->SetDisableGravity(false);
            me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            landed = true;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!landed)
                return;
                
            if (!UpdateVictim(false))
                return;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_razormawAI(creature);
    }
};


void AddSC_bloodmyst_isle()
{

    new mob_webbed_creature();

    new npc_captured_sunhawk_agent();
    
    new npc_exarch_admetius();
    
    new npc_razormaw();
}

