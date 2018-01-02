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
SDName: Azuremyst_Isle
SD%Complete: 75
SDComment: Quest support: 9283, 9537, 9582, 9554, 9531, 9303(special flight path, proper model for mount missing). Injured Draenei cosmetic only, 9582.
SDCategory: Azuremyst Isle
EndScriptData */

/* ContentData
npc_draenei_survivor
npc_engineer_spark_overgrind
npc_injured_draenei
npc_magwin
npc_susurrus
npc_geezle
mob_nestlewood_owlkin
go_ravager_cage
npc_death_ravager
EndContentData */


#include "EscortAI.h"
#include <cmath>
#include "Pet.h"

/*######
## npc_draenei_survivor
######*/

enum eDraeneiSurvivor
{
HEAL1       = -1000248,
HEAL2       = -1000249,
HEAL3       = -1000250,
HEAL4       = -1000251,

HELP1       = -1000252,
HELP2       = -1000253,
HELP3       = -1000254,
HELP4       = -1000255
};


class npc_draenei_survivor : public CreatureScript
{
public:
    npc_draenei_survivor() : CreatureScript("npc_draenei_survivor")
    { }

    class npc_draenei_survivorAI : public ScriptedAI
    {
        public:
        npc_draenei_survivorAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 UnSpawnTimer;
        uint32 ResetlifeTimer;
        uint32 SayingTimer;
        uint32 HealSayTimer;
        bool UnSpawn;
        bool say;
        bool HealSay;
        bool isRun;
        bool isMove;
    
        void Reset() override
        {
            UnSpawnTimer = 2500;
            ResetlifeTimer= 60000;
            SayingTimer    = 5000;
            HealSayTimer = 6000;
            say = false;
            isRun = false;
            isMove = false;
            UnSpawn    = false;
            HealSay = false;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
            //cast red shining
            me->CastSpell(me, 29152, TRIGGERED_NONE, nullptr);
            //set creature health
            me->SetHealth(int(me->GetMaxHealth()*.1));
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 3);
        }
    
        void MoveInLineOfSight(Unit *who) override                      //MoveInLineOfSight is called if creature could see you, updated all 100 ms
        {
            if (!who)
                return;
    
            if(who->GetTypeId() == TYPEID_PLAYER && me->IsFriendlyTo(who) && me->IsWithinDistInMap(who, 15) && say && !isRun)
            {
                switch (rand()%4)                               //Random switch between 4 texts
                {
                    case 0:
                        DoScriptText(HELP1, me);
                        SayingTimer = 15000;
                        say = false;
                        break;
                    case 1:
                        DoScriptText(HELP2, me);
                        SayingTimer = 15000;
                        say = false;
                        break;
                    case 2:
                        DoScriptText(HELP3, me);
                        SayingTimer = 15000;
                        say = false;
                        break;
                    case 3:
                        DoScriptText(HELP4, me);
                        SayingTimer = 15000;
                        say = false;
                        break;
                }
            }
            else
            {
                isRun = false;
            }
        }
    
        void UpdateAI(const uint32 diff) override                        //Is also called each ms for Creature AI Updates...
        {
            if (me->GetHealth() > 50)
            {
                if(ResetlifeTimer < diff)
                {
                    ResetlifeTimer = 60000;
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
                    //set creature health
                    me->SetHealth(int(me->GetMaxHealth()*.1));
                    // ley down
                    me->SetUInt32Value(UNIT_FIELD_BYTES_1,3);
                }
                else ResetlifeTimer -= diff;
            }
    
            if(HealSay)
            {
                if (HealSayTimer < diff)
                {
                    UnSpawn = true;
                    isRun = true;
                    isMove = true;
                }else HealSayTimer -= diff;
            }
    
            if(UnSpawn)
            {
                if(isMove)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MovePoint(0, -4115.053711f, -13754.831055f, 73.508949f);
                    isMove = false;
                }
    
                if (UnSpawnTimer < diff)
                {
                    me->StopMoving();
                    EnterEvadeMode();
                    //set creature health
                    me->SetHealth(int(me->GetMaxHealth()*.1));
                    return;
                }else UnSpawnTimer -= diff;
            }
    
            if(SayingTimer < diff)
            {
                say = true;
            }else SayingTimer -= diff;
        }
    
        void SpellHit(Unit *Hitter, const SpellInfo *Spellkind) override //Called if you cast a spell and do some things if Specified spell is true!
        {
            if (Hitter && Spellkind->Id == 28880)
            {
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                me->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
                me->HandleEmoteCommand(ANIM_RISE);
                switch (rand()%4)                               //This switch doesn't work at all, creature say nothing!
                {
                    case 0: DoScriptText(HEAL1, me, Hitter); break;
                    case 1: DoScriptText(HEAL2, me, Hitter); break;
                    case 2: DoScriptText(HEAL3, me, Hitter); break;
                    case 3: DoScriptText(HEAL4, me, Hitter); break;
                }
                HealSay    = true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_draenei_survivorAI(creature);
    }
};


/*######
## npc_engineer_spark_overgrind
######*/

enum eSparkOvergrind
{
SAY_TEXT        = -1000256,
SAY_EMOTE       = -1000257,
ATTACK_YELL     = -1000258,

SPELL_DYNAMITE  = 7978
};

//TODO translate
#define GOSSIP_FIGHT    "Traître ! Tu vas être livré à la justice !"


class npc_engineer_spark_overgrind : public CreatureScript
{
public:
    npc_engineer_spark_overgrind() : CreatureScript("npc_engineer_spark_overgrind")
    { }

    class npc_engineer_spark_overgrindAI : public ScriptedAI
    {
        public:
        npc_engineer_spark_overgrindAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 Dynamite_Timer;
        uint32 Emote_Timer;
    
        void Reset() override
        {
            Dynamite_Timer = 8000;
            Emote_Timer = 120000 + rand()%30000;
            me->SetFaction(875);
        }
    
        void UpdateAI(const uint32 diff) override
        {
            if( !me->IsInCombat() )
            {
                if (Emote_Timer < diff)
                {
                    DoScriptText(SAY_TEXT, me);
                    DoScriptText(SAY_EMOTE, me);
                    Emote_Timer = 120000 + rand()%30000;
                }else Emote_Timer -= diff;
            }
    
            if(!UpdateVictim())
                return;
    
            if (Dynamite_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_DYNAMITE);
                Dynamite_Timer = 8000;
            } else Dynamite_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }

        virtual bool GossipHello(Player* pPlayer) override
        {
            if( pPlayer->GetQuestStatus(9537) == QUEST_STATUS_INCOMPLETE )
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FIGHT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if( action == GOSSIP_ACTION_INFO_DEF )
            {
                player->CLOSE_GOSSIP_MENU();
                me->SetFaction(FACTION_MONSTER);
                DoScriptText(ATTACK_YELL, me, player);
                ((npc_engineer_spark_overgrind::npc_engineer_spark_overgrindAI*)me->AI())->AttackStart(player);
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_engineer_spark_overgrindAI(creature);
    }
};




/*######
## npc_injured_draenei
######*/

class npc_injured_draenei : public CreatureScript
{
public:
    npc_injured_draenei() : CreatureScript("npc_injured_draenei")
    { }

    class npc_injured_draeneiAI : public ScriptedAI
    {
        public:
        npc_injured_draeneiAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
            me->SetHealth(int(me->GetMaxHealth()*.15));
            switch (rand()%2)
            {
                case 0: me->SetUInt32Value(UNIT_FIELD_BYTES_1, 1); break;
                case 1: me->SetUInt32Value(UNIT_FIELD_BYTES_1, 3); break;
            }
        }
    
        void MoveInLineOfSight(Unit *who)
        override {
            return;                                             //ignore everyone around them (won't aggro anything)
        }
    
        void UpdateAI(const uint32 diff)
        override {
            return;
        }
    
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_injured_draeneiAI(creature);
    }
};


/*######
## npc_magwin
######*/

enum eMagwin
{
SAY_START               = -1000111,
SAY_AGGRO               = -1000112,
SAY_PROGRESS            = -1000113,
SAY_END1                = -1000114,
SAY_END2                = -1000115,
EMOTE_HUG               = -1000116,

QUEST_A_CRY_FOR_HELP    = 9528
};


class npc_magwin : public CreatureScript
{
public:
    npc_magwin() : CreatureScript("npc_magwin")
    { }

    class npc_magwinAI : public EscortAI
    {
        public:
        npc_magwinAI(Creature *c) : EscortAI(c) {}
    
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* player = GetPlayerForEscort();
    
            if (!player)
                return;
    
            switch(i)
            {
            case 0:
                DoScriptText(SAY_START, me, player);
                break;
            case 17:
                DoScriptText(SAY_PROGRESS, me, player);
                break;
            case 28:
                DoScriptText(SAY_END1, me, player);
                break;
            case 29:
                DoScriptText(EMOTE_HUG, me, player);
                DoScriptText(SAY_END2, me, player);
                player->GroupEventHappens(QUEST_A_CRY_FOR_HELP,me);
                break;
            }
        }
    
        void JustEngagedWith(Unit* who)
        override {
            DoScriptText(SAY_AGGRO, me, who);
        }
    
        void Reset()
        override {
            if (!HasEscortState(STATE_ESCORT_ESCORTING))
                me->SetFaction(80);
        }
    
        void JustDied(Unit* killer)
        override {
            if (_playerGUID)
            {
                Player* player = GetPlayerForEscort();
                if (player)
                    player->FailQuest(QUEST_A_CRY_FOR_HELP);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            EscortAI::UpdateAI(diff);
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_A_CRY_FOR_HELP)
            {
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                if (EscortAI* pEscortAI = CAST_AI(npc_magwin::npc_magwinAI, (me->AI())))
                    pEscortAI->Start(true,false, pPlayer->GetGUID(), quest);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_magwinAI(creature);
    }
};



/*######
## npc_susurrus
######*/

class npc_susurrus : public CreatureScript
{
public:
    npc_susurrus() : CreatureScript("npc_susurrus")
    { }

   class npc_susurrusAI : public ScriptedAI
   {
   public:
        npc_susurrusAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (pPlayer->HasItemCount(23843, 1, true))
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I am ready.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);

            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF)
            {
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 32474, TRIGGERED_FULL_MASK);               //apparently correct spell, possible not correct place to cast, or correct caster

                std::vector<uint32> nodes;

                nodes.resize(2);
                nodes[0] = 92;                                      //from susurrus
                nodes[1] = 91;                                      //end at exodar
                player->ActivateTaxiPathTo(nodes/*,11686*/);            //TaxiPath 506. Using invisible model, possible Trinity must allow 0(from dbc) for cases like this.
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_susurrusAI(creature);
    }
};



/*######
## npc_geezle
######*/

enum eGeezle
{
GEEZLE_SAY_1    = -1000259,
SPARK_SAY_2     = -1000260,
SPARK_SAY_3     = -1000261,
GEEZLE_SAY_4    = -1000262,
SPARK_SAY_5     = -1000263,
SPARK_SAY_6     = -1000264,
GEEZLE_SAY_7    = -1000265,

EMOTE_SPARK     = -1000266,

MOB_SPARK       = 17243,
GO_NAGA_FLAG    = 181694
};

static float SparkPos[3] = {-5030.95f, -11291.99f, 7.97f};


class npc_geezle : public CreatureScript
{
public:
    npc_geezle() : CreatureScript("npc_geezle")
    { }

    class npc_geezleAI : public ScriptedAI
    {
        public:
        npc_geezleAI(Creature *c) : ScriptedAI(c) {}
    
        std::list<GameObject*> FlagList;
    
        ObjectGuid SparkGUID;
    
        uint32 Step;
        uint32 SayTimer;
    
        bool EventStarted;
    
        void Reset() override
        {
            SparkGUID = ObjectGuid::Empty;
            Step = 0;
            StartEvent();
        }
    
        void StartEvent()
        {
            Step = 1;
            EventStarted = true;
            Creature* Spark = me->SummonCreature(MOB_SPARK, SparkPos[0], SparkPos[1], SparkPos[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
            if(Spark)
            {
                SparkGUID = Spark->GetGUID();
                Spark->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                Spark->GetMotionMaster()->MovePoint(0, -5080.70, -11253.61, 0.56);
            }
            me->GetMotionMaster()->MovePoint(0, -5092.26, -11252, 0.71);
            SayTimer = 23000;
        }
    
        uint32 NextStep(uint32 step)
        {
            Unit* Spark = ObjectAccessor::GetUnit((*me), SparkGUID);
    
            switch(step)
            {
            case 0: return 99999;
            case 1:
                //DespawnNagaFlag(true);
                DoScriptText(EMOTE_SPARK, Spark);
                return 1000;
            case 2:
                DoScriptText(GEEZLE_SAY_1, me, Spark);
                if(Spark)
                {
                    Spark->SetInFront(me);
                    me->SetInFront(Spark);
                }
                return 5000;
            case 3: DoScriptText(SPARK_SAY_2, Spark); return 7000;
            case 4: DoScriptText(SPARK_SAY_3, Spark); return 8000;
            case 5: DoScriptText(GEEZLE_SAY_4, me, Spark); return 8000;
            case 6: DoScriptText(SPARK_SAY_5, Spark); return 9000;
            case 7: DoScriptText(SPARK_SAY_6, Spark); return 8000;
            case 8: DoScriptText(GEEZLE_SAY_7, me, Spark); return 2000;
            case 9:
                me->GetMotionMaster()->MoveTargetedHome();
                if(Spark)
                    Spark->GetMotionMaster()->MovePoint(0, -5030.95, -11291.99, 7.97);
                return 20000;
            case 10:
                if(Spark)
                    Spark->DealDamage(Spark,Spark->GetHealth(),nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                //DespawnNagaFlag(false);
                me->SetVisible(false);
            default: return 99999999;
            }
        }
    
        void DespawnNagaFlag(bool despawn)
        {
            Trinity::AllGameObjectsWithEntryInGrid go_check(GO_NAGA_FLAG);
            Trinity::GameObjectListSearcher<Trinity::AllGameObjectsWithEntryInGrid> go_search(me, FlagList, go_check);
            Cell::VisitGridObjects(me, go_search, MAX_SEARCHER_DISTANCE);
    
            if (!FlagList.empty())
            {
                for(auto & itr : FlagList)
                {
                    //TODO: Found how to despawn and respawn
                    if(despawn)
                        itr->RemoveFromWorld();
                    else
                        itr->Respawn();
                }
            } else error_log("SD2 ERROR: FlagList is empty!");
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(SayTimer < diff)
            {
                if(EventStarted)
                {
                    SayTimer = NextStep(++Step);
                }
            }else SayTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_geezleAI(creature);
    }
};


/*######
## mob_nestlewood_owlkin
######*/

enum eNestlewoodOwlkin
{
    INOCULATION_CHANNEL        = 29528,
    INOCULATION_EMOTE        = 0,
    INOCULATED_OWLKIN        = 16534
};


class mob_nestlewood_owlkin : public CreatureScript
{
public:
    mob_nestlewood_owlkin() : CreatureScript("mob_nestlewood_owlkin")
    { }

    class mob_nestlewood_owlkinAI : public ScriptedAI
    {
        public:
        mob_nestlewood_owlkinAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 ChannelTimer;
        ObjectGuid PlayerGUID;
        bool Channeled;
        bool Hitted;
    
        void Reset()
        override {
            PlayerGUID = ObjectGuid::Empty;
            ChannelTimer = 0;
            Channeled = false;
            Hitted = false;
        }
    
        void SpellHit(Unit* caster, const SpellInfo* spell)
        override {
            if(!caster)
                return;
    
            if(!Hitted && caster->GetTypeId() == TYPEID_PLAYER && spell->Id == INOCULATION_CHANNEL)
            {
                ChannelTimer = 3000;
                Hitted = true;
                PlayerGUID = caster->GetGUID();
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(ChannelTimer < diff && !Channeled && Hitted)
            {
                Channeled = true;
                me->UpdateEntry(INOCULATED_OWLKIN);
                me->SetRespawnRadius(10.0f); 
                me->DespawnOrUnsummon(10 * SECOND * IN_MILLISECONDS);
                Talk(INOCULATION_EMOTE);
    
                if(Player* channeler = me->GetMap()->GetPlayer(PlayerGUID))
                    channeler->CastedCreatureOrGO(INOCULATED_OWLKIN, me->GetGUID(), INOCULATION_CHANNEL);
        
            }else ChannelTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_nestlewood_owlkinAI(creature);
    }
};


/*######
## go_ravager_cage
######*/

enum eRavegerCage
{
NPC_DEATH_RAVAGER       = 17556,

SPELL_REND              = 13443,
SPELL_ENRAGING_BITE     = 30736,

QUEST_STRENGTH_ONE      = 9582
};

class RavagerCage : public GameObjectScript
{
public:
    RavagerCage() : GameObjectScript("go_ravager_cage")
    {} 

    struct RavagerCageAI : public GameObjectAI
    {
        RavagerCageAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* p) override
        {
            if (p->GetQuestStatus(QUEST_STRENGTH_ONE) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature* ravager = me->FindNearestCreature(NPC_DEATH_RAVAGER, 5.0f, true))
                {
                    ravager->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    ravager->SetReactState(REACT_AGGRESSIVE);
                    ravager->AI()->AttackStart(p);
                }
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new RavagerCageAI(go);
    }
};

/*######
## npc_death_ravager
######*/


class npc_death_ravager : public CreatureScript
{
public:
    npc_death_ravager() : CreatureScript("npc_death_ravager")
    { }

    class npc_death_ravagerAI : public ScriptedAI
    {
        public:
        npc_death_ravagerAI(Creature *c) : ScriptedAI(c){}
    
        uint32 RendTimer;
        uint32 EnragingBiteTimer;
    
        void Reset()
        override {
            RendTimer = 30000;
            EnragingBiteTimer = 20000;
    
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
        }
        
        void JustEngagedWith(Unit* who) override {}
        
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if(RendTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_REND);
                RendTimer = 30000;
            }
            else RendTimer -= diff;
    
            if(EnragingBiteTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_ENRAGING_BITE);
                EnragingBiteTimer = 15000;
            }
            else EnragingBiteTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_death_ravagerAI(creature);
    }
};


/*########
## Quest: The Prophecy of Akida
########*/

enum BristlelimbCage
{
    QUEST_THE_PROPHECY_OF_AKIDA         = 9544,
    NPC_STILLPINE_CAPITIVE              = 17375,
    GO_BRISTELIMB_CAGE                  = 181714

};



class npc_stillpine_capitive : public CreatureScript
{
public:
    npc_stillpine_capitive() : CreatureScript("npc_stillpine_capitive")
    { }

    class npc_stillpine_capitiveAI : public ScriptedAI
    {
        public:
        npc_stillpine_capitiveAI(Creature *c) : ScriptedAI(c){}
    
        uint32 FleeTimer;
    
        void Reset()
        override {
            FleeTimer = 0;
            /*GameObject* cage = me->FindNearestGameObject(GO_BRISTELIMB_CAGE, 5.0f);
            if(cage)
                cage->ResetDoorOrButton();*/
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(FleeTimer)
            {
                if(FleeTimer <= diff)
                    me->DespawnOrUnsummon();
                else FleeTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stillpine_capitiveAI(creature);
    }
};



class BristelimbCage : public GameObjectScript
{
public:
    BristelimbCage() : GameObjectScript("go_bristlelimb_cage")
    {}

    struct BristelimbCageAI : public GameObjectAI
    {
        BristelimbCageAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* p) override
        {
            if (p->GetQuestStatus(QUEST_THE_PROPHECY_OF_AKIDA) == QUEST_STATUS_INCOMPLETE)
            {
                Creature* pCreature = me->FindNearestCreature(NPC_STILLPINE_CAPITIVE, 5.0f, true);
                if (pCreature)
                {
                    pCreature->AI()->Talk(0, p);
                    pCreature->GetMotionMaster()->MoveFleeing(p);
                    p->KilledMonsterCredit(pCreature->GetEntry(), pCreature->GetGUID());
                    CAST_AI(npc_stillpine_capitive::npc_stillpine_capitiveAI, pCreature->AI())->FleeTimer = 3500;
                    return false;
                }
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new BristelimbCageAI(go);
    }
};

/*######
## npc_trigger_quest10956
######*/


class npc_trigger_quest10956 : public CreatureScript
{
public:
    npc_trigger_quest10956() : CreatureScript("npc_trigger_quest10956")
    { }

    class npc_trigger_quest10956AI : public ScriptedAI
    {
        public:
        npc_trigger_quest10956AI(Creature* c) : ScriptedAI(c) {}
    
        void MoveInLineOfSight(Unit* pWho)
        override {
            if (me->GetDistance(pWho) <= 15.0f && pWho->GetTypeId() == TYPEID_PLAYER) {
                if (ObjectGuid critter_guid = pWho->ToPlayer()->GetCritterGUID())
                    if (Creature* pet = pWho->GetMap()->GetCreature(critter_guid)) {
                        if (pWho->ToPlayer()->GetQuestStatus(10956) == QUEST_STATUS_INCOMPLETE && pet->GetEntry() == 22818)
                            pWho->ToPlayer()->AreaExploredOrEventHappens(10956);
                    }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trigger_quest10956AI(creature);
    }
};


/*######
## AddSC
######*/

void AddSC_azuremyst_isle()
{

    new npc_draenei_survivor();

    new npc_engineer_spark_overgrind();

    new npc_injured_draenei();

    new npc_magwin();

    new npc_susurrus();

    new npc_geezle();

    new mob_nestlewood_owlkin();

    new npc_death_ravager();

    new RavagerCage();

    new npc_stillpine_capitive();
    
    new BristelimbCage();
    
    new npc_trigger_quest10956();
}

