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
SDName: Silverpine_Forest
SD%Complete: 100
SDComment: Quest support: 1886, 435
SDCategory: Silverpine Forest
EndScriptData */

/* ContentData
npc_astor_hadren
npc_deathstalker_erland
EndContentData */


#include "EscortAI.h"

/*######
## npc_astor_hadren
######*/

#define GOSSIP_HAH "You're Astor Hadren, right?"
#define GOSSIP_SAH "You've got something I need, Astor. And I'll be taking it now."

class npc_astor_hadren : public CreatureScript
{
public:
    npc_astor_hadren() : CreatureScript("npc_astor_hadren")
    { }

    class npc_astor_hadrenAI : public ScriptedAI
    {
        public:
        npc_astor_hadrenAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
            me->SetFaction(68);
        }
    
        void JustEngagedWith(Unit* who)
        override {
        }
    
        void JustDied(Unit *who)
        override {
            me->SetFaction(68);
        }

        virtual bool GossipHello(Player* player) override
        {
            if (player->GetQuestStatus(1886) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HAH, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            player->SEND_GOSSIP_MENU_TEXTID(623, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF + 1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SAH, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(624, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2:
                    player->CLOSE_GOSSIP_MENU();
                    me->SetFaction(21);
                    if(player)
                        ((npc_astor_hadren::npc_astor_hadrenAI*)me->AI())->AttackStart(player);
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_astor_hadrenAI(creature);
    }
};




/*######
## npc_deathstalker_erland
######*/

#define SAY_QUESTACCEPT -1000335
#define SAY_START       -1000336
#define SAY_AGGRO_1     -1000337
#define SAY_AGGRO_2     -1000338
#define SAY_LAST        -1000339

#define SAY_THANKS      -1000340
#define SAY_RANE        -1000341
#define SAY_ANSWER      -1000342
#define SAY_MOVE_QUINN  -1000343

#define SAY_GREETINGS   -1000344
#define SAY_QUINN       -1000345
#define SAY_ON_BYE      -1000346

#define QUEST_ESCORTING 435
#define NPC_RANE        1950
#define NPC_QUINN       1951


class npc_deathstalker_erland : public CreatureScript
{
public:
    npc_deathstalker_erland() : CreatureScript("npc_deathstalker_erland")
    { }

    class npc_deathstalker_erlandAI : public EscortAI
    {
        public:
        npc_deathstalker_erlandAI(Creature *c) : EscortAI(c) {}
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* player = GetPlayerForEscort();
    
            if (!player)
                return;
    
            switch(i)
            {
            case 1: DoScriptText(SAY_START, me, player);break;
            case 13:
                DoScriptText(SAY_LAST, me, player);
                player->GroupEventHappens(QUEST_ESCORTING, me);break;
            case 14: DoScriptText(SAY_THANKS, me, player);break;
            case 15: {
                    Unit* Rane = me->FindNearestCreature(NPC_RANE, 20);
                    if(Rane)
                        DoScriptText(SAY_RANE, Rane);
                    break;}
            case 16: DoScriptText(SAY_ANSWER, me);break;
            case 17: DoScriptText(SAY_MOVE_QUINN, me); break;
            case 24: DoScriptText(SAY_GREETINGS, me);break;
            case 25: {
                    Unit* Quinn = me->FindNearestCreature(NPC_QUINN, 20);
                    if(Quinn)
                        DoScriptText(SAY_QUINN, Quinn);
                    break;}
            case 26: DoScriptText(SAY_ON_BYE, me, nullptr);break;
    
            }
        }
    
        void Reset() override {}
    
        void JustEngagedWith(Unit* who)
        override {
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_AGGRO_1, me, who);break;
            case 1: DoScriptText(SAY_AGGRO_2, me, who);break;
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            EscortAI::UpdateAI(diff);
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_ESCORTING)
            {
                DoScriptText(SAY_QUESTACCEPT, me, player);
                ((EscortAI*)(me->AI()))->Start(true, false, player->GetGUID(), quest);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_deathstalker_erlandAI(creature);
    }
};



/* ScriptData
SDName: pyrewood_ambush
SD%Complete: 100
SDComment: Quest pyrewood ambush (id 452), you have to kill 4 waves of people: 1, 2, 3, 3.
           The quest giver is here for help you.
SDCategory: OLDScript Quests

EndScriptData */

#define QUEST_PYREWOOD_AMBUSH 452

#define NPCSAY_INIT "Get ready, they'll be arriving any minute..." //no blizzlike
#define NPCSAY_END "Thanks for your help!" //no blizzlike

static float SpawnPoints[3][4] =
{
    //pos_x   pos_y     pos_z    orien
    //door
    {-396.17f, 1505.86f, 19.77f, 0.0f},
    {-396.91f, 1505.77f, 19.77f, 0.0f},
    {-397.94f, 1504.74f, 19.77f, 0.0f},
};

#define WAIT_SECS 6000


class pyrewood_ambush : public CreatureScript
{
public:
    pyrewood_ambush() : CreatureScript("pyrewood_ambush")
    { }

    class pyrewood_ambushAI : public ScriptedAI
    {
        public:
    
        pyrewood_ambushAI(Creature *c) : ScriptedAI(c), Summons(me)
        {
           QuestInProgress = false;
        }
    
    
        uint32 Phase;
        int KillCount;
        uint32 WaitTimer;
        ObjectGuid PlayerGUID;
        SummonList Summons;
    
        bool QuestInProgress;
    
        void Reset() override
        {
            WaitTimer = WAIT_SECS;
    
            if(!QuestInProgress) //fix reset values (see UpdateVictim)
            {
                Phase = 0;
                KillCount = 0;
                PlayerGUID = ObjectGuid::Empty;
                Summons.DespawnAll();
            }
        }
    
        void JustEngagedWith(Unit *who) override  
        {}
    
        void JustSummoned(Creature *pSummoned) override
        {
            Summons.Summon(pSummoned);
            ++KillCount;
        }
    
        void SummonedCreatureDespawn(Creature* pSummoned)
        override {
            Summons.Despawn(pSummoned);
            --KillCount;
        }
        
        void JustAppeared() override
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        }
    
        void SummonCreatureWithRandomTarget(uint32 creatureId, int position)
        {
            Creature *pSummoned = me->SummonCreature(creatureId, SpawnPoints[position][0], SpawnPoints[position][1], SpawnPoints[position][2], SpawnPoints[position][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000);
            if(pSummoned)
            {
                Player* pPlayer = nullptr;
                Unit* pTarget = nullptr;
                if (PlayerGUID)
                {
                    pPlayer = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                    switch(rand()%2)
                    {
                        case 0: pTarget = me; break;
                        case 1: pTarget = pPlayer; break;
                    }
                }else
                    pTarget = me;
    
                pSummoned->SetFaction(168);
                pSummoned->GetThreatManager().AddThreat(pTarget, 32.0f);
                (pSummoned->ToCreature())->AI()->AttackStart(pTarget);
            }
        }
    
        void JustDied(Unit* pKiller) override
        {
            if (PlayerGUID)
            {
                Player* pPlayer = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                if (pPlayer && (pPlayer->ToPlayer())->GetQuestStatus(QUEST_PYREWOOD_AMBUSH) == QUEST_STATUS_INCOMPLETE)
                    (pPlayer->ToPlayer())->FailQuest(QUEST_PYREWOOD_AMBUSH);
            }
    
        }
    
        void UpdateAI(const uint32 diff) override
        {
    
            //TC_LOG_INFO("DEBUG: p(%i) k(%i) d(%u) W(%i)", Phase, KillCount, diff, WaitTimer);
    
            if(!QuestInProgress)
                return;
                
            if (PlayerGUID) {
                Player* pPlayer = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                if (!pPlayer)
                    return;
                
                if (pPlayer->IsDead()) {
                    pPlayer->FailQuest(QUEST_PYREWOOD_AMBUSH);
                    Summons.DespawnAll();
                    QuestInProgress = false;
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                }
            }
    
            if(KillCount && (Phase < 6))
            {
                if(!UpdateVictim() ) //reset() on target Despawn...
                    return;
    
                DoMeleeAttackIfReady();
                return;
            }
    
    
            switch(Phase){
                case 0:
                    if(WaitTimer == WAIT_SECS)
                        me->Say(NPCSAY_INIT, LANG_UNIVERSAL, nullptr); //no blizzlike
    
                    if(WaitTimer <= diff)
                    {
                        WaitTimer -= diff;
                        return;
                    }
                    break;
                case 1:
                    SummonCreatureWithRandomTarget(2060, 1);
                    break;
                case 2:
                    SummonCreatureWithRandomTarget(2061, 2);
                    SummonCreatureWithRandomTarget(2062, 0);
                    break;
                case 3:
                    SummonCreatureWithRandomTarget(2063, 1);
                    SummonCreatureWithRandomTarget(2064, 2);
                    SummonCreatureWithRandomTarget(2065, 0);
                    break;
                case 4:
                    SummonCreatureWithRandomTarget(2066, 1);
                    SummonCreatureWithRandomTarget(2067, 0);
                    SummonCreatureWithRandomTarget(2068, 2);
                    break;
                case 5: //end
                    if (PlayerGUID)
                    {
                        Unit* player = ObjectAccessor::GetUnit((*me), PlayerGUID);
                        if( player && player->GetTypeId() == TYPEID_PLAYER )
                        {
                            me->Say(NPCSAY_END, LANG_UNIVERSAL, nullptr); //no blizzlike
                            (player->ToPlayer())->GroupEventHappens(QUEST_PYREWOOD_AMBUSH, me);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        }
                    }
                    QuestInProgress = false;
                    Reset();
                    break;
             }
    
             Phase++; //prepare next phase
    
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if ((pQuest->GetQuestId() == QUEST_PYREWOOD_AMBUSH) && (!((pyrewood_ambush::pyrewood_ambushAI*)(me->AI()))->QuestInProgress))
            {
                ((pyrewood_ambush::pyrewood_ambushAI*)(me->AI()))->QuestInProgress = true;
                ((pyrewood_ambush::pyrewood_ambushAI*)(me->AI()))->Phase = 0;
                ((pyrewood_ambush::pyrewood_ambushAI*)(me->AI()))->KillCount = 0;
                ((pyrewood_ambush::pyrewood_ambushAI*)(me->AI()))->PlayerGUID = pPlayer->GetGUID();
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new pyrewood_ambushAI(creature);
    }
};



/*######
## AddSC
######*/

void AddSC_silverpine_forest()
{

    new npc_astor_hadren();

    new npc_deathstalker_erland();

    new pyrewood_ambush();
}

