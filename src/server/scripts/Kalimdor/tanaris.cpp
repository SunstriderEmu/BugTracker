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
SDName: Tanaris
SD%Complete: 80
SDComment: Quest support: 2882, 2954, 4005, 10277, 648, 10279(Special flight path). Noggenfogger vendor
SDCategory: Tanaris
EndScriptData */

/* ContentData
mob_aquementas
npc_custodian_of_time
npc_marin_noggenfogger
npc_steward_of_time
npc_stone_watcher_of_norgannon
npc_OOX17
go_landmark_treasure
npc_jhordy_lapforge
npc_tooga
npc_trigger_quest10963
EndContentData */


#include "EscortAI.h"
#include "FollowerAI.h"
#include "Pet.h"

/*######
## mob_aquementas
######*/

#define AGGRO_YELL_AQUE     -1000350

#define SPELL_AQUA_JET      13586
#define SPELL_FROST_SHOCK   15089

class mob_aquementas : public CreatureScript
{
public:
    mob_aquementas() : CreatureScript("mob_aquementas")
    { }

    class mob_aquementasAI : public ScriptedAI
    {
        public:
        mob_aquementasAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 SendItem_Timer;
        uint32 SwitchFaction_Timer;
        bool isFriendly;
    
        uint32 FrostShock_Timer;
        uint32 AquaJet_Timer;
    
        void Reset()
        override {
            SendItem_Timer = 0;
            SwitchFaction_Timer = 10000;
            me->SetFaction(FACTION_FRIENDLY);
            isFriendly = true;
    
            AquaJet_Timer = 5000;
            FrostShock_Timer = 1000;
        }
    
        void SendItem(Unit* receiver)
        {
            if ((receiver->ToPlayer())->HasItemCount(11169,1,false) &&
                (receiver->ToPlayer())->HasItemCount(11172,11,false) &&
                (receiver->ToPlayer())->HasItemCount(11173,1,false) &&
                !(receiver->ToPlayer())->HasItemCount(11522,1,true))
            {
                ItemPosCountVec dest;
                uint8 msg = (receiver->ToPlayer())->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, 11522, 1);
                if( msg == EQUIP_ERR_OK )
                    (receiver->ToPlayer())->StoreNewItem( dest, 11522, 1, true);
            }
        }
    
        void JustEngagedWith(Unit* who)
        override {
            DoScriptText(AGGRO_YELL_AQUE, me, who);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if( isFriendly )
            {
                if( SwitchFaction_Timer < diff )
                {
                    me->SetFaction(91);
                    isFriendly = false;
                }else SwitchFaction_Timer -= diff;
            }
    
            if (!UpdateVictim())
                return;
    
            if( !isFriendly )
            {
                if( SendItem_Timer < diff )
                {
                    if( me->GetVictim()->GetTypeId() == TYPEID_PLAYER )
                        SendItem(me->GetVictim());
                    SendItem_Timer = 5000;
                }else SendItem_Timer -= diff;
            }
    
            if( FrostShock_Timer < diff )
            {
                DoCast(me->GetVictim(),SPELL_FROST_SHOCK);
                FrostShock_Timer = 15000;
            }else FrostShock_Timer -= diff;
    
            if( AquaJet_Timer < diff )
            {
                DoCast(me,SPELL_AQUA_JET);
                AquaJet_Timer = 15000;
            }else AquaJet_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_aquementasAI(creature);
    }
};


/*######
## npc_custodian_of_time
######*/

#define WHISPER_CUSTODIAN_1     -1000150
#define WHISPER_CUSTODIAN_2     -1000151
#define WHISPER_CUSTODIAN_3     -1000152
#define WHISPER_CUSTODIAN_4     -1000153
#define WHISPER_CUSTODIAN_5     -1000154
#define WHISPER_CUSTODIAN_6     -1000155
#define WHISPER_CUSTODIAN_7     -1000156
#define WHISPER_CUSTODIAN_8     -1000157
#define WHISPER_CUSTODIAN_9     -1000158
#define WHISPER_CUSTODIAN_10    -1000159
#define WHISPER_CUSTODIAN_11    -1000160
#define WHISPER_CUSTODIAN_12    -1000161
#define WHISPER_CUSTODIAN_13    -1000162
#define WHISPER_CUSTODIAN_14    -1000163


class npc_custodian_of_time : public CreatureScript
{
public:
    npc_custodian_of_time() : CreatureScript("npc_custodian_of_time")
    { }

    class npc_custodian_of_timeAI : public EscortAI
    {
        public:
        npc_custodian_of_timeAI(Creature *c) : EscortAI(c) {}
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player *pPlayer = GetPlayerForEscort();
            if( !pPlayer )
                return;
    
            switch( i )
            {
                case 0: DoScriptText(WHISPER_CUSTODIAN_1, me, pPlayer); break;
                case 1: DoScriptText(WHISPER_CUSTODIAN_2, me, pPlayer); break;
                case 2: DoScriptText(WHISPER_CUSTODIAN_3, me, pPlayer); break;
                case 3: DoScriptText(WHISPER_CUSTODIAN_4, me, pPlayer); break;
                case 5: DoScriptText(WHISPER_CUSTODIAN_5, me, pPlayer); break;
                case 6: DoScriptText(WHISPER_CUSTODIAN_6, me, pPlayer); break;
                case 7: DoScriptText(WHISPER_CUSTODIAN_7, me, pPlayer); break;
                case 8: DoScriptText(WHISPER_CUSTODIAN_8, me, pPlayer); break;
                case 9: DoScriptText(WHISPER_CUSTODIAN_9, me, pPlayer); break;
                case 10: DoScriptText(WHISPER_CUSTODIAN_4, me, pPlayer); break;
                case 13: DoScriptText(WHISPER_CUSTODIAN_10, me, pPlayer); break;
                case 14: DoScriptText(WHISPER_CUSTODIAN_4, me, pPlayer); break;
                case 16: DoScriptText(WHISPER_CUSTODIAN_11, me, pPlayer); break;
                case 17: DoScriptText(WHISPER_CUSTODIAN_12, me, pPlayer); break;
                case 18: DoScriptText(WHISPER_CUSTODIAN_4, me, pPlayer); break;
                case 22: DoScriptText(WHISPER_CUSTODIAN_13, me, pPlayer); break;
                case 23: DoScriptText(WHISPER_CUSTODIAN_4, me, pPlayer); break;
                case 24:
                    DoScriptText(WHISPER_CUSTODIAN_14, me, pPlayer);
                    DoCast(pPlayer,34883);
                    //below here is temporary workaround, to be removed when spell works properly
                    pPlayer->AreaExploredOrEventHappens(10277);
                    break;
            }
        }
    
        void MoveInLineOfSight(Unit *who)
        override {
            if(HasEscortState(STATE_ESCORT_ESCORTING))
                return;
    
            if( who->GetTypeId() == TYPEID_PLAYER )
            {
                if( (who->ToPlayer())->HasAuraEffect(34877,1) && (who->ToPlayer())->GetQuestStatus(10277) == QUEST_STATUS_INCOMPLETE )
                {
                    float Radius = 10.0;
                    if( me->IsWithinDistInMap(who, Radius) )
                    {
                        ((EscortAI*)(me->AI()))->Start(false, false, who->GetGUID());
                    }
                }
            }
        }
    
        void JustEngagedWith(Unit* who) override { }
        void Reset() override { }
    
        void UpdateAI(const uint32 diff)
        override {
            EscortAI::UpdateAI(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_custodian_of_timeAI(creature);
    }
};


/*######
## npc_marin_noggenfogger
######*/

class npc_marin_noggenfogger : public CreatureScript
{
public:
    npc_marin_noggenfogger() : CreatureScript("npc_marin_noggenfogger")
    { }

    class npc_marin_noggenfoggerAI : public ScriptedAI
    {
    public:
        npc_marin_noggenfoggerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if( me->IsQuestGiver() )
                player->PrepareQuestMenu( me->GetGUID() );

            if( me->IsVendor() && player->GetQuestRewardStatus(2662) )
                player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if( action == GOSSIP_ACTION_TRADE )
                player->SEND_VENDORLIST( me->GetGUID() );

            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_marin_noggenfoggerAI(creature);
    }
};



/*######
## npc_steward_of_time
######*/

#define GOSSIP_ITEM_FLIGHT  "Please take me to the master's lair."

class npc_steward_of_time : public CreatureScript
{
public:
    npc_steward_of_time() : CreatureScript("npc_steward_of_time")
    { }

    class npc_steward_of_timeAI : public ScriptedAI
    {
    public:
        npc_steward_of_timeAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if( me->IsQuestGiver() )
                player->PrepareQuestMenu( me->GetGUID() );

            if( player->GetQuestStatus(10279) == QUEST_STATUS_INCOMPLETE || player->GetQuestRewardStatus(10279) )
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU_TEXTID(9978,me->GetGUID());
            }
            else
                player->SEND_GOSSIP_MENU_TEXTID(9977,me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if( action == GOSSIP_ACTION_INFO_DEF + 1 )
                player->CastSpell(player,34891, TRIGGERED_FULL_MASK);               //(Flight through Caverns)

            return true;

        }


        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if( quest->GetQuestId() == 10279 )                      //Quest: To The Master's Lair
                player->CastSpell(player,34891, TRIGGERED_FULL_MASK);               //(Flight through Caverns)
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_steward_of_timeAI(creature);
    }
};




/*######
## npc_stone_watcher_of_norgannon
######*/

#define GOSSIP_ITEM_NORGANNON_1     "What function do you serve?"
#define GOSSIP_ITEM_NORGANNON_2     "What are the Plates of Uldum?"
#define GOSSIP_ITEM_NORGANNON_3     "Where are the Plates of Uldum?"
#define GOSSIP_ITEM_NORGANNON_4     "Excuse me? We've been \"reschedueled for visitations\"? What does that mean?!"
#define GOSSIP_ITEM_NORGANNON_5     "So, what's inside Uldum?"
#define GOSSIP_ITEM_NORGANNON_6     "I will return when i have the Plates of Uldum."

class npc_stone_watcher_of_norgannon : public CreatureScript
{
public:
    npc_stone_watcher_of_norgannon() : CreatureScript("npc_stone_watcher_of_norgannon")
    { }

    class npc_stone_watcher_of_norgannonAI : public ScriptedAI
    {
    public:
        npc_stone_watcher_of_norgannonAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if( me->IsQuestGiver() )
                player->PrepareQuestMenu( me->GetGUID() );

            if( player->GetQuestStatus(2954) == QUEST_STATUS_INCOMPLETE )
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_NORGANNON_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            player->SEND_GOSSIP_MENU_TEXTID(1674, me->GetGUID());

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_NORGANNON_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                    player->SEND_GOSSIP_MENU_TEXTID(1675, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_NORGANNON_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU_TEXTID(1676, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_NORGANNON_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                    player->SEND_GOSSIP_MENU_TEXTID(1677, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_NORGANNON_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                    player->SEND_GOSSIP_MENU_TEXTID(1678, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+4:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_NORGANNON_6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    player->SEND_GOSSIP_MENU_TEXTID(1679, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+5:
                    player->CLOSE_GOSSIP_MENU();
                    player->AreaExploredOrEventHappens(2954);
                    break;
            }
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stone_watcher_of_norgannonAI(creature);
    }
};



/*######
## npc_OOX17
######*/

#define Q_OOX17             648
#define SPAWN_FIRST         7803
#define SPAWN_SECOND_1      5617
#define SPAWN_SECOND_2      7805
#define SAY_SCOFF           -1060004
#define SAY_CHICKEN_ACC     -1060000
#define SAY_CHICKEN_AGGRO_1 -1060001
#define SAY_CHICKEN_AGGRO_2 -1060002
#define SAY_CHICKEN_AMB     -1060003
#define SAY_CHICKEN_COMP    -1060005


class npc_OOX17 : public CreatureScript
{
public:
    npc_OOX17() : CreatureScript("npc_OOX17")
    { }

    class npc_OOX17AI : public EscortAI
    {
        public:
        npc_OOX17AI(Creature *c) : EscortAI(c)
        {
            complete = false;
        }
        
        bool complete;
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* player = GetPlayerForEscort();
    
            if (!player)
                return;
    
            switch(i) {
                case 23:
                    me->SummonCreature(SPAWN_FIRST, -8350.96, -4445.79, 10.10, 6.20, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    me->SummonCreature(SPAWN_FIRST, -8355.96, -4447.79, 10.10, 6.27, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    me->SummonCreature(SPAWN_FIRST, -8353.96, -4442.79, 10.10, 6.08, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    DoScriptText(SAY_CHICKEN_AMB, me);
                    break;
    
                case 56:
                    me->SummonCreature(SPAWN_SECOND_1, -7510.07, -4795.50, 9.35, 6.06, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    me->SummonCreature(SPAWN_SECOND_2, -7515.07, -4797.50, 9.35, 6.22, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    me->SummonCreature(SPAWN_SECOND_2, -7518.07, -4792.50, 9.35, 6.22, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    DoScriptText(SAY_CHICKEN_AMB, me);
                    {Unit* scoff = me->FindNearestCreature(SPAWN_SECOND_2, 30);
                    if(scoff)
                        DoScriptText(SAY_SCOFF, scoff);}break;
                    break;
    
                case 86:
                    DoScriptText(SAY_CHICKEN_COMP, me);
                    player->GroupEventHappens(Q_OOX17, me);
                    complete = true;
                    break;
            }
        }
    
        void Reset() override {}
    
        void JustEngagedWith(Unit* who)
        override {
            DoScriptText(RAND(SAY_CHICKEN_AGGRO_1, SAY_CHICKEN_AGGRO_2), me);
        }
    
        void JustSummoned(Creature* summoned)
        override {
            summoned->AI()->AttackStart(me);
        }
    
        void JustDied(Unit* killer)
        override {
            if (_playerGUID && !complete)
            {
                if (Player* player = GetPlayerForEscort())
                    player->FailQuest(Q_OOX17);
            }
        }
    
    
        void UpdateAI(const uint32 diff)
        override {
            EscortAI::UpdateAI(diff);
            if (!UpdateVictim())
                return;
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == Q_OOX17) {
                me->SetFaction(player->GetFaction());
                me->SetHealth(me->GetMaxHealth());
                me->SetUInt32Value(UNIT_FIELD_BYTES_1,0);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                DoScriptText(SAY_CHICKEN_ACC, me);
                ((EscortAI*)(me->AI()))->Start(true, false, player->GetGUID(), quest);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_OOX17AI(creature);
    }
};



/*######
## go_landmark_treasure
######*/

#define QUEST_CUERGOS_GOLD 2882

#define NPC_BUCCANEER      7902
#define NPC_PIRATE         7899
#define NPC_SWASHBUCKLER   7901

#define GO_TREASURE        142194

#define PATH_ENTRY_1       2090
#define PATH_ENTRY_2       2091
#define PATH_ENTRY_3       2092
#define PATH_ENTRY_4       2093
#define PATH_ENTRY_5       2094

class LandmarkTreasure : public GameObjectScript
{
public:
    LandmarkTreasure() : GameObjectScript("go_landmark_treasure")
    {}

    struct LandmarkTreasureAI : public GameObjectAI
    {
        LandmarkTreasureAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->GetQuestStatus(QUEST_CUERGOS_GOLD) != QUEST_STATUS_INCOMPLETE)
                return false;

            Creature * spawn = nullptr;

            spawn = player->SummonCreature(NPC_PIRATE, -10029.78, -4032.54, 19.41, 3.40, TEMPSUMMON_TIMED_DESPAWN, 340000);
            if (spawn)
                spawn->GetMotionMaster()->MovePath(PATH_ENTRY_1);
            spawn = player->SummonCreature(NPC_PIRATE, -10031.64, -4032.14, 19.11, 3.40, TEMPSUMMON_TIMED_DESPAWN, 340000);
            if (spawn)
                spawn->GetMotionMaster()->MovePath(PATH_ENTRY_3);

            spawn = player->SummonCreature(NPC_SWASHBUCKLER, -10029.86, -4030.51, 20.02, 3.40, TEMPSUMMON_TIMED_DESPAWN, 340000);
            if (spawn)
                spawn->GetMotionMaster()->MovePath(PATH_ENTRY_4);
            spawn = player->SummonCreature(NPC_SWASHBUCKLER, -10031.83, -4030.70, 19.52, 3.40, TEMPSUMMON_TIMED_DESPAWN, 340000);
            if (spawn)
                spawn->GetMotionMaster()->MovePath(PATH_ENTRY_5);

            spawn = player->SummonCreature(NPC_BUCCANEER, -10028.90, -4029.65, 20.53, 3.40, TEMPSUMMON_TIMED_DESPAWN, 340000);
            if (spawn)
                spawn->GetMotionMaster()->MovePath(PATH_ENTRY_2);

            player->SummonGameObject(GO_TREASURE, Position(-10119.70, -4050.45, 5.33, 0), G3D::Quat(), 240);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new LandmarkTreasureAI(go);
    }
};

/*######
## npc_jhordy_lapforge
######*/

#define GOSSIP_ZAP                  "[PH] J'aimerais recevoir le transporteur ultra-sécurisé."
#define SPELL_GNOME_ENGINEER        20219
#define SPELL_ULTRASAFE_TELE        23489

class npc_jhordy_lapforge : public CreatureScript
{
public:
    npc_jhordy_lapforge() : CreatureScript("npc_jhordy_lapforge")
    { }

    class npc_jhordy_lapforgeAI : public ScriptedAI
    {
    public:
        npc_jhordy_lapforgeAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->HasSkill(SKILL_ENGINEERING) && (pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 260) && pPlayer->HasSpell(SPELL_GNOME_ENGINEER) && !pPlayer->HasSpell(SPELL_ULTRASAFE_TELE)) {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ZAP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(3377, me->GetGUID());
                
                return true;
            }
            
            return false;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1) {
                player->LearnSpell(SPELL_ULTRASAFE_TELE, false);
                
                player->CLOSE_GOSSIP_MENU();
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_jhordy_lapforgeAI(creature);
    }
};



/*####
# npc_tooga
####*/

enum eTooga
{
    SAY_TOOG_THIRST             = -1600391,
    SAY_TOOG_WORRIED            = -1600392,
    SAY_TOOG_POST_1             = -1600393,
    SAY_TORT_POST_2             = -1600394,
    SAY_TOOG_POST_3             = -1600395,
    SAY_TORT_POST_4             = -1600396,
    SAY_TOOG_POST_5             = -1600397,
    SAY_TORT_POST_6             = -1600398,

    QUEST_TOOGA                 = 1560,
    NPC_TORTA                   = 6015,

    POINT_ID_TO_WATER           = 1,
    FACTION_TOOG_ESCORTEE       = 113
};

const float m_afToWaterLoc[] = {-7032.664551f, -4906.199219f, -1.606446f};


class npc_tooga : public CreatureScript
{
public:
    npc_tooga() : CreatureScript("npc_tooga")
    { }

    class npc_toogaAI : public FollowerAI
    {
        public:
        npc_toogaAI(Creature* pCreature) : FollowerAI(pCreature) { }
    
        uint32 m_uiCheckSpeechTimer;
        uint32 m_uiPostEventTimer;
        uint32 m_uiPhasePostEvent;
    
        uint64 TortaGUID;
    
        void Reset()
        override {
            m_uiCheckSpeechTimer = 2500;
            m_uiPostEventTimer = 1000;
            m_uiPhasePostEvent = 0;
    
            TortaGUID = 0;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
    
        void MoveInLineOfSight(Unit *pWho)
        override {
            FollowerAI::MoveInLineOfSight(pWho);
    
            if (!me->GetVictim() && !HasFollowState(STATE_FOLLOW_COMPLETE | STATE_FOLLOW_POSTEVENT) && pWho->GetEntry() == NPC_TORTA)
            {
                if (me->IsWithinDistInMap(pWho, INTERACTION_DISTANCE))
                {
                    if (Player* pPlayer = GetLeaderForFollower())
                    {
                        if (pPlayer->GetQuestStatus(QUEST_TOOGA) == QUEST_STATUS_INCOMPLETE)
                            pPlayer->GroupEventHappens(QUEST_TOOGA, me);
                    }
    
                    TortaGUID = pWho->GetGUID();
                    SetFollowComplete(true);
                }
            }
        }
    
        void MovementInform(uint32 uiMotionType, uint32 uiPointId)
        override {
            FollowerAI::MovementInform(uiMotionType, uiPointId);
    
            if (uiMotionType != POINT_MOTION_TYPE)
                return;
    
            if (uiPointId == POINT_ID_TO_WATER)
                SetFollowComplete();
        }
    
        void UpdateFollowerAI(const uint32 uiDiff)
        override {
            if (!UpdateVictim())
            {
                //we are doing the post-event, or...
                if (HasFollowState(STATE_FOLLOW_POSTEVENT))
                {
                    if (m_uiPostEventTimer <= uiDiff)
                    {
                        m_uiPostEventTimer = 5000;
    
                        Unit *pTorta = ObjectAccessor::GetUnit(*me, TortaGUID);
                        if (!pTorta || !pTorta->IsAlive())
                        {
                            //something happened, so just complete
                            SetFollowComplete();
                            return;
                        }
    
                        switch(m_uiPhasePostEvent)
                        {
                            case 1:
                                DoScriptText(SAY_TOOG_POST_1, me);
                                break;
                            case 2:
                                DoScriptText(SAY_TORT_POST_2, pTorta);
                                break;
                            case 3:
                                DoScriptText(SAY_TOOG_POST_3, me);
                                break;
                            case 4:
                                DoScriptText(SAY_TORT_POST_4, pTorta);
                                break;
                            case 5:
                                DoScriptText(SAY_TOOG_POST_5, me);
                                break;
                            case 6:
                                DoScriptText(SAY_TORT_POST_6, pTorta);
                                me->GetMotionMaster()->MovePoint(POINT_ID_TO_WATER, m_afToWaterLoc[0], m_afToWaterLoc[1], m_afToWaterLoc[2]);
                                break;
                        }
    
                        ++m_uiPhasePostEvent;
                    }
                    else
                        m_uiPostEventTimer -= uiDiff;
                }
                //...we are doing regular speech check
                else if (HasFollowState(STATE_FOLLOW_INPROGRESS))
                {
                    if (m_uiCheckSpeechTimer <= uiDiff)
                    {
                        m_uiCheckSpeechTimer = 5000;
    
                        if (urand(0,9) > 8)
                            DoScriptText(RAND(SAY_TOOG_THIRST,SAY_TOOG_WORRIED), me);
                    }
                    else
                        m_uiCheckSpeechTimer -= uiDiff;
                }
    
                return;
            }
    
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if (pQuest->GetQuestId() == QUEST_TOOGA)
            {
                if (npc_toogaAI* pToogaAI = CAST_AI(npc_tooga::npc_toogaAI, me->AI())) {
                    pToogaAI->StartFollow(pPlayer, FACTION_TOOG_ESCORTEE, pQuest);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_toogaAI(creature);
    }
};



/*######
## npc_trigger_quest10963
######*/


class npc_trigger_quest10963 : public CreatureScript
{
public:
    npc_trigger_quest10963() : CreatureScript("npc_trigger_quest10963")
    { }

    class npc_trigger_quest10963AI : public ScriptedAI
    {
        public:
        npc_trigger_quest10963AI(Creature* c) : ScriptedAI(c) {}
        
        void JustEngagedWith(Unit* pWho) override {}
        
        void MoveInLineOfSight(Unit* pWho)
        override {
            if (me->GetDistance(pWho) <= 10.0f && pWho->GetTypeId() == TYPEID_PLAYER) {
                if (uint64 critter_guid = pWho->ToPlayer()->GetCritterGUID())
                    if (Creature* pet = pWho->GetMap()->GetCreature(critter_guid)) {
                        if (pWho->ToPlayer()->GetQuestStatus(10963) == QUEST_STATUS_INCOMPLETE && pet->GetEntry() == 22817)
                            pWho->ToPlayer()->AreaExploredOrEventHappens(10963);
                        else if (pWho->ToPlayer()->GetQuestStatus(10962) == QUEST_STATUS_INCOMPLETE && pet->GetEntry() == 22818)
                            pWho->ToPlayer()->AreaExploredOrEventHappens(10962);
                    }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trigger_quest10963AI(creature);
    }
};


/*######
## AddSC
######*/

void AddSC_tanaris()
{

    new mob_aquementas();

    new npc_custodian_of_time();

    new npc_marin_noggenfogger();

    new npc_steward_of_time();

    new npc_stone_watcher_of_norgannon();

    new npc_OOX17();

    new LandmarkTreasure();
    
    new npc_jhordy_lapforge();
    
    new npc_tooga();
    
    new npc_trigger_quest10963();
}

