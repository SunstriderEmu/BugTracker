
/* ScriptData
SDName: Eversong_Woods
SD%Complete: 100
SDComment: Quest support: 8346, 8483, 8488, 8490
SDCategory: Eversong Woods
EndScriptData */

/* ContentData
mobs_mana_tapped
npc_prospector_anvilward
npc_apprentice_mirveda
npc_infused_crystal
EndContentData */


#include "EscortAI.h"

/*######
## mobs_mana_tapped
######*/


class mobs_mana_tapped : public CreatureScript
{
public:
    mobs_mana_tapped() : CreatureScript("mobs_mana_tapped")
    { }

    class mobs_mana_tappedAI : public ScriptedAI
    {
        public:
        mobs_mana_tappedAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset() override { }
    
        void JustEngagedWith(Unit* pWho) override { }
    
        void SpellHit(Unit* pCaster, const SpellInfo* spell)
        override {
            if (pCaster->GetTypeId() == TYPEID_PLAYER)
                if( (pCaster)->ToPlayer()->GetQuestStatus(8346) == QUEST_STATUS_INCOMPLETE && !(pCaster)->ToPlayer()->GetReqKillOrCastCurrentCount(8346, me->GetEntry()) && spell->Id == 28734)
                    (pCaster)->ToPlayer()->CastedCreatureOrGO(15468, me->GetGUID(), spell->Id);
            return;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mobs_mana_tappedAI(creature);
    }
};


/*######
## npc_prospector_anvilward
######*/

#define GOSSIP_HELLO    "J'ai besoin d'un peu de votre temps, seigneur."
#define GOSSIP_SELECT   "Pourquoi... oui, bien sûr. J'ai quelque chose à vous montrer juste dans ce bâtiment, Mr. Garde-enclume."

enum eAnvilward
{
SAY_PR_1                = -1000281,
SAY_PR_2                = -1000282,

QUEST_THE_DWARVEN_SPY   = 8483
};


class npc_prospector_anvilward : public CreatureScript
{
public:
    npc_prospector_anvilward() : CreatureScript("npc_prospector_anvilward")
    { }

    class npc_prospector_anvilwardAI : public EscortAI
    {
        public:
        // CreatureAI functions
        npc_prospector_anvilwardAI(Creature *c) : EscortAI(c) {}
    
        // Pure Virtual Functions
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* player = GetPlayerForEscort();
    
            if(!player)
                return;
    
            switch (i)
            {
                case 0: DoScriptText(SAY_PR_1, me, player); break;
                case 5: DoScriptText(SAY_PR_2, me, player); break;
                case 6: me->SetFaction(24); break;
            }
        }
    
        void JustEngagedWith(Unit* pWho) override {}
    
        void Reset()
        override {
            me->SetFaction(FACTION_CREATURE);
        }
    
        void JustDied(Unit* /*pKiller*/)
        override {
            me->SetFaction(FACTION_CREATURE);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            EscortAI::UpdateAI(diff);
        }

        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(QUEST_THE_DWARVEN_SPY) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(8239, me->GetGUID());
            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            ClearGossipMenuFor(player);
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch(action)
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SELECT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU_TEXTID(8240, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->CLOSE_GOSSIP_MENU();
                    if (EscortAI* pEscortAI = CAST_AI(npc_prospector_anvilward::npc_prospector_anvilwardAI, (me->AI())))
                        pEscortAI->Start(true, false, player->GetGUID());
                    break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_prospector_anvilwardAI(creature);
    }
};




/*######
## Quest 9686 Second Trial
######*/

enum eSecondTrial
{
QUEST_SECOND_TRIAL              = 9686,

MASTER_KELERUN_BLOODMOURN       = 17807,

CHAMPION_BLOODWRATH             = 17809,
CHAMPION_LIGHTREND              = 17810,
CHAMPION_SWIFTBLADE             = 17811,
CHAMPION_SUNSTRIKER             = 17812,

HARBINGER_OF_THE_SECOND_TRIAL   = 182052,

SPELL_FLASH_OF_LIGHT            = 19939,
TIMER_FLASH_OF_LIGHT            = 3225,

SPELL_SEAL_OF_JUSTICE           = 20164,
TIMER_SEAL_OF_JUSTICE           = 10000,

SPELL_JUDGEMENT_OF_LIGHT        = 20271,
TIMER_JUDGEMENT_OF_LIGHT        = 10000,

SPELL_SEAL_OF_COMMAND           = 20375,
TIMER_SEAL_OF_COMMAND           = 20000,

OFFSET_NEXT_ATTACK              = 750,

FACTION_HOSTILE                 = 45,

TEXT_SECOND_TRIAL_1             = -1645006,
TEXT_SECOND_TRIAL_2             = -1645007,
TEXT_SECOND_TRIAL_3             = -1645008,
TEXT_SECOND_TRIAL_4             = -1645009
};

struct Locations
{
    float x, y, z, o;
};

static Locations SpawnPosition[]=
{
    {  5.3f,  -11.80f, 0.361f, 4.20f},
    { 11.2f,  -29.17f, 0.361f, 2.70f},
    { -5.7f,  -34.85f, 0.361f, 1.09f},
    { -11.9f, -18.00f, 0.361f, 5.87f}
};

static uint32 PaladinEntry[]= {CHAMPION_BLOODWRATH, CHAMPION_LIGHTREND, CHAMPION_SWIFTBLADE, CHAMPION_SUNSTRIKER};

/*######
## npc_second_trial_controller
######*/

class npc_second_trial_controller : public CreatureScript
{
public:
    npc_second_trial_controller() : CreatureScript("npc_second_trial_controller")
    { }

    class master_kelerun_bloodmournAI : public ScriptedAI
    {
    public:
        master_kelerun_bloodmournAI(Creature *c) : ScriptedAI(c) {}

        uint8  questPhase;
        uint8  paladinPhase;
        uint32 timer;

        ObjectGuid paladinGuid[4];

        void Reset() override {
            questPhase = 0;
            timer = 60 * SECOND * IN_MILLISECONDS;
            paladinPhase = 0;
            for (uint8 i = 0; i < 4; i++)
                paladinGuid[i].Clear();
        }

        void JustEngagedWith(Unit* pWho) override {}

        void UpdateAI(const uint32 diff) override; //defined later

        void StartEvent()
        {
            if (questPhase == 1)
            { // no player check, quest can be finished as group, so no complex playerguid/group search code
                for (int i = 0; i<4; i++)
                {
                    Creature* Summoned;
                    Summoned = DoSpawnCreature(PaladinEntry[i], SpawnPosition[i].x, SpawnPosition[i].y, SpawnPosition[i].z, SpawnPosition[i].o, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 180000);

                    if (Summoned)
                        paladinGuid[i] = Summoned->GetGUID();
                }

                timer = OFFSET_NEXT_ATTACK;
                questPhase = 2;
            }
        }

        void SecondTrialKill()
        {
            if (questPhase > 0)
            {
                ++paladinPhase;

                if (paladinPhase < 4)
                    questPhase = 2;
                else
                    Reset();  // Quest Complete, OnQuestComplete handler is in npc_secondTrialAI::JustDied
            }
        }

        void SummonedCreatureDespawn(Creature* c) override {}

        virtual bool GossipHello(Player* pPlayer) override
        {
            // quest only available if not already started
            // Quest_template flag is set to : QUEST_FLAGS_EVENT
            // Escort quests or any other event-driven quests. If player in party, all players that can accept this quest will receive confirmation box to accept quest.
            // !not sure if this really works!

            if (questPhase == 0) {
                pPlayer->PrepareQuestMenu(me->GetGUID());
                pPlayer->SendPreparedQuest(me->GetGUID());
            }

            pPlayer->SEND_GOSSIP_MENU_TEXTID(me->GetEntry(), me->GetGUID());
            return true;

        }

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            // One Player exclusive quest, wait for user go activation
            if (pQuest->GetQuestId() == QUEST_SECOND_TRIAL)
                questPhase = 1;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new master_kelerun_bloodmournAI(creature);
    }
};

/*######
## npc_second_trial_paladin
######*/

class npc_second_trial_paladin : public CreatureScript
{
public:
    npc_second_trial_paladin() : CreatureScript("npc_second_trial_paladin")
    { }

    class npc_secondTrialAI : public ScriptedAI
    {
    public:
        npc_secondTrialAI(Creature *c) : ScriptedAI(c) {}

        uint32 timer;
        uint8  questPhase;
        ObjectGuid summonerGuid;

        bool spellFlashLight;
        bool spellJustice;
        bool spellJudLight;
        bool spellCommand;

        uint32 timerFlashLight;
        uint32 timerJustice;
        uint32 timerJudLight;
        uint32 timerCommand;


        void Reset() override {

            timer = 2000;
            questPhase = 0;
            summonerGuid.Clear();

            me->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_KNEEL);
            me->SetFaction(FACTION_CREATURE);

            spellFlashLight = false;
            spellJustice = false;
            spellJudLight = false;
            spellCommand = false;

            switch (me->GetEntry()) {
            case CHAMPION_BLOODWRATH:
                spellFlashLight = true;
                timerFlashLight = TIMER_FLASH_OF_LIGHT;
                break;
            case CHAMPION_LIGHTREND:
                spellJustice = true;
                timerJustice = 500;
                break;
            case CHAMPION_SWIFTBLADE:
                spellJudLight = false;  // Misses Script Effect // http://www.wowhead.com/?spell=20271
                timerJudLight = 500;
                break;
            case CHAMPION_SUNSTRIKER:
                spellFlashLight = true;
                spellJudLight = false;  // Misses Script Effect // http://www.wowhead.com/?spell=20271
                spellCommand = false;  // Misses Dummy // http://www.wowhead.com/?spell=20375
                timerFlashLight = TIMER_FLASH_OF_LIGHT;
                timerJudLight = 500;
                timerCommand = 1500;
                break;
            }
        }

        void JustEngagedWith(Unit* pWho) override { }

        void UpdateAI(const uint32 diff)
            override {
            if (questPhase == 1)
            {
                if (timer < diff)
                {
                    me->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_NONE);
                    me->SetFaction(FACTION_HOSTILE);
                    questPhase = 0;

                    Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if (target && target->GetTypeId() == TYPEID_PLAYER) // only on players.
                    {
                        me->GetThreatManager().AddThreat(target, 5000000.0f);
                        AttackStart(target);
                    }
                }
                else timer -= diff;
            }

            if (!UpdateVictim())
                return;

            // healer
            if (spellFlashLight)
            {
                if (me->GetHealthPct() < 70)
                {
                    if (timerFlashLight < diff)
                    {
                        DoCast(me, SPELL_FLASH_OF_LIGHT);
                        timerFlashLight = TIMER_FLASH_OF_LIGHT + rand() % (TIMER_FLASH_OF_LIGHT);
                    }
                    else timerFlashLight -= diff;
                }
            }

            if (spellJustice)
            {
                if (timerJustice < diff)
                {
                    DoCast(me, SPELL_SEAL_OF_JUSTICE);
                    timerJustice = TIMER_SEAL_OF_JUSTICE + rand() % (TIMER_SEAL_OF_JUSTICE);
                }
                else timerJustice -= diff;
            }

            if (spellJudLight)
            {
                if (timerJudLight < diff) {
                    DoCast(me, SPELL_JUDGEMENT_OF_LIGHT);
                    timerJudLight = TIMER_JUDGEMENT_OF_LIGHT + rand() % (TIMER_JUDGEMENT_OF_LIGHT);
                }
                else timerJudLight -= diff;
            }

            if (spellCommand)
            {
                if (timerCommand < diff) {
                    DoCast(me, TIMER_SEAL_OF_COMMAND);
                    timerCommand = TIMER_SEAL_OF_COMMAND + rand() % (TIMER_SEAL_OF_COMMAND);
                }
                else timerCommand -= diff;
            }

            DoMeleeAttackIfReady();
        }


        void JustDied(Unit* pKiller) override
        {
            if (pKiller && pKiller->GetTypeId() == TYPEID_PLAYER)
            {
                Creature* Summoner;
                Summoner = (ObjectAccessor::GetCreature((*me), summonerGuid));

                if (Summoner)
                    CAST_AI(npc_second_trial_controller::master_kelerun_bloodmournAI, (Summoner->AI()))->SecondTrialKill();

                // last kill quest complete for group
                if (me->GetEntry() == CHAMPION_SUNSTRIKER)
                {
                    if (Group *pGroup = (pKiller)->ToPlayer()->GetGroup())
                    {
                        for (GroupReference *itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
                        {
                            Player* pGroupGuy = itr->GetSource();

                            // for any leave or dead (with not released body) group member at appropriate distance
                            if (pGroupGuy && pGroupGuy->IsAtGroupRewardDistance(me) && !pGroupGuy->GetCorpse() && pGroupGuy->GetQuestStatus(QUEST_SECOND_TRIAL) == QUEST_STATUS_INCOMPLETE)
                                pGroupGuy->CompleteQuest(QUEST_SECOND_TRIAL);
                        }
                    }
                    else
                    {
                        if ((pKiller)->ToPlayer()->GetQuestStatus(QUEST_SECOND_TRIAL) == QUEST_STATUS_INCOMPLETE)
                            (pKiller)->ToPlayer()->CompleteQuest(QUEST_SECOND_TRIAL);
                    }
                }
            }
        }

        void KilledUnit(Unit* pKilled) override
        {
            if (pKilled->GetTypeId() == TYPEID_PLAYER)
            {
                if ((pKilled)->ToPlayer()->GetQuestStatus(QUEST_SECOND_TRIAL) == QUEST_STATUS_INCOMPLETE)
                    (pKilled)->ToPlayer()->FailQuest(QUEST_SECOND_TRIAL);
            }
        }

        void Activate(ObjectGuid summonerguid)
        {
            questPhase = 1;
            summonerGuid = summonerguid;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_secondTrialAI(creature);
    }
};


class SecondTrialGO : public GameObjectScript
{
public:
    SecondTrialGO() : GameObjectScript("go_second_trial")
    {}

    struct SecondTrialGOAI : public GameObjectAI
    {
        SecondTrialGOAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            // find spawn :: master_kelerun_bloodmourn
            Creature* event_controller = nullptr;
            Trinity::NearestCreatureEntryWithLiveStateInObjectRangeCheck u_check(*me, MASTER_KELERUN_BLOODMOURN, true, 30);
            Trinity::CreatureLastSearcher<Trinity::NearestCreatureEntryWithLiveStateInObjectRangeCheck> searcher(me, event_controller, u_check);
            Cell::VisitGridObjects(pPlayer, searcher, MAX_SEARCHER_DISTANCE);

            if (event_controller)
                CAST_AI(npc_second_trial_controller::master_kelerun_bloodmournAI, (event_controller->AI()))->StartEvent();

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new SecondTrialGOAI(go);
    }
};

/*######
## npc_apprentice_mirveda
######*/

enum eMirveda
{
QUEST_UNEXPECTED_RESULT     = 8488,
MOB_GHARZUL                 = 15958,
MOB_ANGERSHADE              = 15656
};


class npc_apprentice_mirveda : public CreatureScript
{
public:
    npc_apprentice_mirveda() : CreatureScript("npc_apprentice_mirveda")
    { }

    class npc_apprentice_mirvedaAI : public ScriptedAI
    {
        public:
        npc_apprentice_mirvedaAI(Creature* c) : ScriptedAI(c), Summons(me) {}
    
        uint32 KillCount;
        ObjectGuid PlayerGUID;
        bool Summon;
        bool Validated;
        SummonList Summons;
    
        void Reset()
        override {
            KillCount = 0;
            PlayerGUID = ObjectGuid::Empty;
            Summons.DespawnAll();
            Summon = false;
            Validated = false;
            me->GetMotionMaster()->MoveTargetedHome();
        }
    
        void JustEngagedWith(Unit* pWho)override {}
    
        void JustSummoned(Creature* pSummoned)
        override {
            pSummoned->AI()->AttackStart(me);
            Summons.Summon(pSummoned);
        }
    
        void SummonedCreatureDespawn(Creature* pSummoned)
        override {
            Summons.Despawn(pSummoned);
            ++KillCount;
        }
    
        void JustDied(Unit* /*pKiller*/)
        override {
            if (PlayerGUID)
            {
                Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                if (player && !Validated)
                    player->FailQuest(QUEST_UNEXPECTED_RESULT);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (KillCount >= 3 && !Validated)
            {
                if (PlayerGUID)
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                    if (player)
                        player->AreaExploredOrEventHappens(QUEST_UNEXPECTED_RESULT);
                }
                
                Validated = true;
                Reset();
            }
    
            if (Summon)
            {
                me->SummonCreature(MOB_GHARZUL, 8745, -7134.32, 35.22, 0, TEMPSUMMON_CORPSE_DESPAWN, 4000);
                me->SummonCreature(MOB_ANGERSHADE, 8745, -7134.32, 35.22, 0, TEMPSUMMON_CORPSE_DESPAWN, 4000);
                me->SummonCreature(MOB_ANGERSHADE, 8745, -7134.32, 35.22, 0, TEMPSUMMON_CORPSE_DESPAWN, 4000);
                Summon = false;
            }
            
            if (!UpdateVictim(false))
                return;
                
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if (pQuest->GetQuestId() == QUEST_UNEXPECTED_RESULT)
            {
                CAST_AI(npc_apprentice_mirveda::npc_apprentice_mirvedaAI, (me->AI()))->Summon = true;
                CAST_AI(npc_apprentice_mirveda::npc_apprentice_mirvedaAI, (me->AI()))->PlayerGUID = pPlayer->GetGUID();
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_apprentice_mirvedaAI(creature);
    }
};

void npc_second_trial_controller::master_kelerun_bloodmournAI::UpdateAI(const uint32 diff) {
    // Quest accepted but object not activated, object despawned (if in sync 1 minute!)
    if (questPhase == 1)
    {
        if (timer < diff)
            Reset();
        else timer -= diff;
    }
    // fight the 4 paladin mobs phase
    else if (questPhase == 2)
    {
        if (timer < diff)
        {
            Creature* paladinSpawn;
            paladinSpawn = (ObjectAccessor::GetCreature((*me), paladinGuid[paladinPhase]));
            if (paladinSpawn)
            {
                CAST_AI(npc_second_trial_paladin::npc_secondTrialAI, (paladinSpawn->AI()))->Activate(me->GetGUID());

                switch (paladinPhase)
                {
                case 0:
                    DoScriptText(TEXT_SECOND_TRIAL_1, me);
                    break;
                case 1:
                    DoScriptText(TEXT_SECOND_TRIAL_2, me);
                    break;
                case 2:
                    DoScriptText(TEXT_SECOND_TRIAL_3, me);
                    break;
                case 3:
                    DoScriptText(TEXT_SECOND_TRIAL_4, me);
                    break;
                }
            }
            else
                Reset();

            questPhase = 4;
            timer = OFFSET_NEXT_ATTACK;
        }
        else timer -= diff;
    }

    if (!UpdateVictim())
        return;

    DoMeleeAttackIfReady();
}

/*######
## npc_infused_crystal
######*/

enum eInfusedCrystal
{
MOB_ENRAGED_WRAITH          = 17086,
EMOTE                       = -1000283,
QUEST_POWERING_OUR_DEFENSES = 8490
};

struct Location
{
    float x, y, z;
};

static Location SpawnLocations[]=
{
    {8270.68f, -7188.53f, 139.619f},
    {8284.27f, -7187.78f, 139.603f},
    {8297.43f, -7193.53f, 139.603f},
    {8303.50f, -7201.96f, 139.577f},
    {8273.22f, -7241.82f, 139.382f},
    {8254.89f, -7222.12f, 139.603f},
    {8278.51f, -7242.13f, 139.162f},
    {8267.97f, -7239.17f, 139.517f}
};


class npc_infused_crystal : public CreatureScript
{
public:
    npc_infused_crystal() : CreatureScript("npc_infused_crystal")
    { }

    class npc_infused_crystalAI : public ScriptedAI
    {
        public:
        npc_infused_crystalAI(Creature* c) : ScriptedAI(c) 
        {
            SetCombatMovementAllowed(false);
        }
    
        uint32 EndTimer;
        uint32 WaveTimer;
        bool Completed;
        bool Progress;
        ObjectGuid PlayerGUID;
    
        void Reset()
        override {
            EndTimer = 0;
            Completed = false;
            Progress = false;
            PlayerGUID = ObjectGuid::Empty;
            WaveTimer = 0;
        }
    
        void MoveInLineOfSight(Unit* pWho) override 
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER && me->CanAggro(pWho) != CAN_ATTACK_RESULT_OK && !Progress)
            {
                if ((pWho)->ToPlayer()->GetQuestStatus(QUEST_POWERING_OUR_DEFENSES) == QUEST_STATUS_INCOMPLETE)
                {
                    float Radius = 10.0;
                    if (me->IsWithinDistInMap(pWho, Radius))
                    {
                        PlayerGUID = pWho->GetGUID();
                        WaveTimer = 1000;
                        EndTimer = 60000;
                        Progress = true;
                    }
                }
            }
        }
    
        void JustSummoned(Creature* pSummoned)
        override {
            pSummoned->AI()->AttackStart(me);
        }
    
        void JustDied(Unit* /*pKiller*/)
        override {
            if (PlayerGUID && !Completed)
            {
                Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                if (player)
                    player->FailQuest(QUEST_POWERING_OUR_DEFENSES);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (EndTimer < diff && Progress)
            {
                DoScriptText(EMOTE, me);
                Completed = true;
                if (PlayerGUID)
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                    if (Group* group = player->GetGroup()) {
                        for (GroupReference *itr = group->GetFirstMember(); itr != nullptr; itr = itr->next()) {
                            Player* pGroupGuy = itr->GetSource();
                            if (!pGroupGuy)
                                continue;
    
                            if (!pGroupGuy->IsAtGroupRewardDistance(player))
                                continue;
                                
                            pGroupGuy->KilledMonsterCredit(16364, ObjectGuid::Empty);
                        }
                    }
                    else
                        player->KilledMonsterCredit(16364, ObjectGuid::Empty);
                }
                me->DespawnOrUnsummon();
            } else EndTimer -= diff;
    
            if (WaveTimer < diff && !Completed && Progress)
            {
                uint32 ran1 = rand()%8;
                uint32 ran2 = rand()%8;
                uint32 ran3 = rand()%8;
                me->SummonCreature(MOB_ENRAGED_WRAITH, SpawnLocations[ran1].x, SpawnLocations[ran1].y, SpawnLocations[ran1].z, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 10000);
                me->SummonCreature(MOB_ENRAGED_WRAITH, SpawnLocations[ran2].x, SpawnLocations[ran2].y, SpawnLocations[ran2].z, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 10000);
                me->SummonCreature(MOB_ENRAGED_WRAITH, SpawnLocations[ran3].x, SpawnLocations[ran3].y, SpawnLocations[ran3].z, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 10000);
                WaveTimer = 30000;
            } else WaveTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_infused_crystalAI(creature);
    }
};


void AddSC_eversong_woods()
{
    new mobs_mana_tapped();
    new npc_prospector_anvilward();
    new npc_second_trial_controller();
    new npc_second_trial_paladin();
    new SecondTrialGO();
    new npc_apprentice_mirveda();
    new npc_infused_crystal();
}
