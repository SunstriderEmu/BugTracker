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

struct mobs_mana_tappedAI : public ScriptedAI
{
    mobs_mana_tappedAI(Creature *c) : ScriptedAI(c) {}

    void Reset() override { }

    void EnterCombat(Unit* pWho) override { }

    void SpellHit(Unit* pCaster, const SpellInfo* spell)
    override {
        if (pCaster->GetTypeId() == TYPEID_PLAYER)
            if( (pCaster)->ToPlayer()->GetQuestStatus(8346) == QUEST_STATUS_INCOMPLETE && !(pCaster)->ToPlayer()->GetReqKillOrCastCurrentCount(8346, me->GetEntry()) && spell->Id == 28734)
                (pCaster)->ToPlayer()->CastedCreatureOrGO(15468, me->GetGUID(), spell->Id);
        return;
    }
};

CreatureAI* GetAI_mobs_mana_tapped(Creature* pCreature)
{
    return new mobs_mana_tappedAI (pCreature);
}

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

struct npc_prospector_anvilwardAI : public npc_escortAI
{
    // CreatureAI functions
    npc_prospector_anvilwardAI(Creature *c) : npc_escortAI(c) {}

    // Pure Virtual Functions
    void WaypointReached(uint32 i)
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

    void EnterCombat(Unit* pWho) override {}

    void Reset()
    override {
        me->SetFaction(FACTION_CREATURE);
    }

    void JustDied(Unit* pKiller)
    override {
        me->SetFaction(FACTION_CREATURE);
    }

    void UpdateAI(const uint32 diff)
    override {
        npc_escortAI::UpdateAI(diff);
    }
};

CreatureAI* GetAI_npc_prospector_anvilward(Creature* pCreature)
{
    return new npc_prospector_anvilwardAI(pCreature);
}

bool GossipHello_npc_prospector_anvilward(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_THE_DWARVEN_SPY) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU_TEXTID(8239, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_prospector_anvilward(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action )
{
    switch(action)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SELECT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(8240, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->CLOSE_GOSSIP_MENU();
            if (npc_escortAI* pEscortAI = CAST_AI(npc_prospector_anvilwardAI, (pCreature->AI())))
                pEscortAI->Start(true, true, false, pPlayer->GetGUID(), pCreature->GetEntry());
            break;
    }
    return true;
}

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
## npc_second_trial_paladin
######*/

struct npc_secondTrialAI : public ScriptedAI
{
    npc_secondTrialAI(Creature *c) : ScriptedAI(c) {}

    uint32 timer;
    uint8  questPhase;
    uint64 summonerGuid;

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
      summonerGuid = 0;

      me->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_KNEEL);
      me->SetFaction(FACTION_CREATURE);

      spellFlashLight = false;
      spellJustice    = false;
      spellJudLight   = false;
      spellCommand    = false;

        switch(me->GetEntry()) {
            case CHAMPION_BLOODWRATH :
                spellFlashLight = true;
                timerFlashLight = TIMER_FLASH_OF_LIGHT;
            break;
            case CHAMPION_LIGHTREND :
                spellJustice    = true;
                timerJustice    = 500;
            break;
            case CHAMPION_SWIFTBLADE :
                spellJudLight   = false;  // Misses Script Effect // http://www.wowhead.com/?spell=20271
                timerJudLight   = 500;
            break;
            case CHAMPION_SUNSTRIKER :
                spellFlashLight = true;
                spellJudLight   = false;  // Misses Script Effect // http://www.wowhead.com/?spell=20271
                spellCommand    = false;  // Misses Dummy // http://www.wowhead.com/?spell=20375
                timerFlashLight = TIMER_FLASH_OF_LIGHT;
                timerJudLight   = 500;
                timerCommand    = 1500;
            break;
        }
    }

    void EnterCombat(Unit* pWho) override { }

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
                if(target && target->GetTypeId() == TYPEID_PLAYER) // only on players.
                {
                    me->AddThreat(target, 5000000.0f);
                    AttackStart(target);
                }
            } else timer -= diff;
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
                    timerFlashLight = TIMER_FLASH_OF_LIGHT + rand()%(TIMER_FLASH_OF_LIGHT);
                } else timerFlashLight -= diff;
            }
        }

        if (spellJustice)
        {
            if (timerJustice < diff)
            {
                DoCast(me, SPELL_SEAL_OF_JUSTICE);
                timerJustice = TIMER_SEAL_OF_JUSTICE +  rand()%( TIMER_SEAL_OF_JUSTICE );
            } else timerJustice -= diff;
        }

        if (spellJudLight)
        {
            if (timerJudLight < diff) {
                DoCast(me,  SPELL_JUDGEMENT_OF_LIGHT);
                timerJudLight = TIMER_JUDGEMENT_OF_LIGHT +  rand()%( TIMER_JUDGEMENT_OF_LIGHT );
            } else timerJudLight -= diff;
        }

        if (spellCommand)
        {
            if (timerCommand < diff) {
                DoCast(me,  TIMER_SEAL_OF_COMMAND);
                timerCommand = TIMER_SEAL_OF_COMMAND +  rand()%( TIMER_SEAL_OF_COMMAND );
            } else timerCommand -= diff;
        }

        DoMeleeAttackIfReady();
    }

    void Activate(uint64 summonerguid);
    void KilledUnit(Unit* pKilled) override;
    void JustDied(Unit* pKiller) override;

};

/*######
## npc_second_trial_controller
######*/

struct master_kelerun_bloodmournAI : public ScriptedAI
{
    master_kelerun_bloodmournAI(Creature *c) : ScriptedAI(c) {}

    uint8  questPhase;
    uint8  paladinPhase;
    uint32 timer;

    uint64 paladinGuid[4];

    void Reset() override {
      questPhase = 0;
      timer = 60 * SECOND * IN_MILLISECONDS;
      paladinPhase = 0;
	  for (uint8 i = 0; i < 4; i++)
		  paladinGuid[i] = 0;
    }

    void EnterCombat(Unit* pWho) override {}

    void UpdateAI(const uint32 diff)
    override {
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
                    CAST_AI(npc_secondTrialAI, (paladinSpawn->AI()))->Activate(me->GetGUID());

                    switch(paladinPhase)
                    {
                        case 0:
                            DoScriptText(TEXT_SECOND_TRIAL_1,me);
                        break;
                        case 1:
                            DoScriptText(TEXT_SECOND_TRIAL_2,me);
                        break;
                        case 2:
                            DoScriptText(TEXT_SECOND_TRIAL_3,me);
                        break;
                        case 3:
                            DoScriptText(TEXT_SECOND_TRIAL_4,me);
                        break;
                    }
                }
                else
                Reset();

                questPhase=4;
                timer = OFFSET_NEXT_ATTACK;
            } else timer -= diff;
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

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

    void SecondTrialKill();
    void SummonedCreatureDespawn(Creature* c) override {}
};


bool GossipHello_master_kelerun_bloodmourn(Player* pPlayer, Creature* pCreature)
{
    // quest only available if not already started
    // Quest_template flag is set to : QUEST_FLAGS_EVENT
    // Escort quests or any other event-driven quests. If player in party, all players that can accept this quest will receive confirmation box to accept quest.
    // !not sure if this really works!

    if (((master_kelerun_bloodmournAI*)pCreature->AI())->questPhase == 0) {
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());
        pPlayer->SendPreparedQuest(pCreature->GetGUID());
    }

    pPlayer->SEND_GOSSIP_MENU_TEXTID(pCreature->GetEntry(), pCreature->GetGUID());
    return true;
}

bool QuestAccept_master_kelerun_bloodmourn(Player* pPlayer, Creature* pCreature, Quest const* pQuest )
{
    // One Player exclusive quest, wait for user go activation
    if (pQuest->GetQuestId() == QUEST_SECOND_TRIAL )
        CAST_AI(master_kelerun_bloodmournAI, (pCreature->AI()))->questPhase = 1;

    return true;
}

void master_kelerun_bloodmournAI::SecondTrialKill()
{
    if (questPhase > 0)
    {
        ++paladinPhase;

        if (paladinPhase < 4)
            questPhase=2;
        else
            Reset();  // Quest Complete, OnQuestComplete handler is in npc_secondTrialAI::JustDied
    }
}

void npc_secondTrialAI::JustDied(Unit* pKiller)
{
    if (pKiller->GetTypeId() == TYPEID_PLAYER)
    {
        Creature* Summoner;
        Summoner = (ObjectAccessor::GetCreature((*me), summonerGuid));

        if (Summoner)
            CAST_AI(master_kelerun_bloodmournAI, (Summoner->AI()))->SecondTrialKill();

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

void npc_secondTrialAI::KilledUnit(Unit* pKilled)
{
    if (pKilled->GetTypeId() == TYPEID_PLAYER)
    {
        if ((pKilled)->ToPlayer()->GetQuestStatus(QUEST_SECOND_TRIAL) == QUEST_STATUS_INCOMPLETE)
            (pKilled)->ToPlayer()->FailQuest(QUEST_SECOND_TRIAL);
    }
}

void npc_secondTrialAI::Activate(uint64 summonerguid)
{
    questPhase=1;
    summonerGuid = summonerguid;
}

CreatureAI* GetAI_master_kelerun_bloodmourn(Creature* pCreature)
{
    return new master_kelerun_bloodmournAI(pCreature);
}

CreatureAI* GetAI_npc_secondTrial(Creature* pCreature)
{
    return new npc_secondTrialAI(pCreature);
}

class SecondTrialGO : public GameObjectScript
{
public:
    SecondTrialGO() : GameObjectScript("go_second_trial")
    {}

    bool OnGossipHello(Player* pPlayer, GameObject* pGo) override
    {
        // find spawn :: master_kelerun_bloodmourn
        Creature* event_controller = nullptr;
        Trinity::NearestCreatureEntryWithLiveStateInObjectRangeCheck u_check(*pGo, MASTER_KELERUN_BLOODMOURN, true, 30);
        Trinity::CreatureLastSearcher<Trinity::NearestCreatureEntryWithLiveStateInObjectRangeCheck> searcher(event_controller, u_check);
        pPlayer->VisitNearbyGridObject(MAX_SEARCHER_DISTANCE, searcher);

        if (event_controller)
            CAST_AI(master_kelerun_bloodmournAI, (event_controller->AI()))->StartEvent();

        return true;
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

struct npc_apprentice_mirvedaAI : public ScriptedAI
{
    npc_apprentice_mirvedaAI(Creature* c) : ScriptedAI(c), Summons(me) {}

    uint32 KillCount;
    uint64 PlayerGUID;
    bool Summon;
    bool Validated;
    SummonList Summons;

    void Reset()
    override {
        KillCount = 0;
        PlayerGUID = 0;
        Summons.DespawnAll();
        Summon = false;
        Validated = false;
        me->GetMotionMaster()->MoveTargetedHome();
    }

    void EnterCombat(Unit* pWho)override {}

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

    void JustDied(Unit* pKiller)
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
};

bool QuestAccept_npc_apprentice_mirveda(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_UNEXPECTED_RESULT)
    {
        CAST_AI(npc_apprentice_mirvedaAI, (pCreature->AI()))->Summon = true;
        CAST_AI(npc_apprentice_mirvedaAI, (pCreature->AI()))->PlayerGUID = pPlayer->GetGUID();
    }
    
    return true;
}

CreatureAI* GetAI_npc_apprentice_mirvedaAI(Creature* pCreature)
{
    return new npc_apprentice_mirvedaAI(pCreature);
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

struct npc_infused_crystalAI : public ScriptedAI
{
    npc_infused_crystalAI(Creature* c) : ScriptedAI(c) 
    {
        SetCombatMovementAllowed(false);
    }

    uint32 EndTimer;
    uint32 WaveTimer;
    bool Completed;
    bool Progress;
    uint64 PlayerGUID;

    void Reset()
    override {
        EndTimer = 0;
        Completed = false;
        Progress = false;
        PlayerGUID = 0;
        WaveTimer = 0;
    }

    void EnterCombat(Unit* pWho) override {}

    void MoveInLineOfSight(Unit* pWho)
    override {
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

    void JustDied(Unit* pKiller)
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
                            
                        pGroupGuy->KilledMonsterCredit(16364, 0);
                    }
                }
                else
                    player->KilledMonsterCredit(16364, 0);
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

CreatureAI* GetAI_npc_infused_crystalAI(Creature* pCreature)
{
    return new npc_infused_crystalAI(pCreature);
}

void AddSC_eversong_woods()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name="mobs_mana_tapped";
    newscript->GetAI = &GetAI_mobs_mana_tapped;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name= "npc_prospector_anvilward";
    newscript->GetAI = &GetAI_npc_prospector_anvilward;
    newscript->OnGossipHello =  &GossipHello_npc_prospector_anvilward;
    newscript->OnGossipSelect = &GossipSelect_npc_prospector_anvilward;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_second_trial_controller";
    newscript->GetAI = &GetAI_master_kelerun_bloodmourn;
    newscript->OnGossipHello = &GossipHello_master_kelerun_bloodmourn;
    newscript->OnQuestAccept = &QuestAccept_master_kelerun_bloodmourn;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_second_trial_paladin";
    newscript->GetAI = &GetAI_npc_secondTrial;
    sScriptMgr->RegisterOLDScript(newscript);

    new SecondTrialGO();

    newscript = new OLDScript;
    newscript->Name = "npc_apprentice_mirveda";
    newscript->GetAI = &GetAI_npc_apprentice_mirvedaAI;
    newscript->OnQuestAccept = &QuestAccept_npc_apprentice_mirveda;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_infused_crystal";
    newscript->GetAI = &GetAI_npc_infused_crystalAI;
    sScriptMgr->RegisterOLDScript(newscript);
}
