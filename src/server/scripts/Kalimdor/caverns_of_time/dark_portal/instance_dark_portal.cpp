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
SDName: Instance_Dark_Portal
SD%Complete: 75
SDComment: Quest support: 9836, 10297. Currently in progress.
SDCategory: Caverns of Time, The Dark Portal
EndScriptData */


#include "def_dark_portal.h"

#define ENCOUNTERS              5

#define C_MEDIVH                15608
#define C_TIME_RIFT             17838

#define SPELL_RIFT_CHANNEL      31387

#define RIFT_BOSS               1
inline uint32 RandRiftBoss() { return rand()%2 ? C_RKEEP : C_RLORD; }

float PortalLocation[4][4]=
{
    {-2031.817261f, 7070.159180f, 29.99f, 1.30f},
    {-1986.737549f, 7069.349609f, 21.93f, 2.12f},
    {-1951.568481f, 7110.390625f, 22.32f, 3.07f},
    {-1968.634766f, 7160.240723f, 22.11f, 3.44f}
};

struct Wave
{
    uint32 PortalBoss;                                      //protector of current portal
    uint32 NextPortalTime;                                  //time to next portal, or 0 if portal boss need to be killed
};

static Wave RiftWaves[]=
{
    {RIFT_BOSS, 0},
    {C_DEJA, 0},
    {RIFT_BOSS, 120000},
    {C_TEMPO, 0},
    {RIFT_BOSS, 120000},
    {C_AEONUS, 0}
};

class instance_dark_portal : public InstanceMapScript
{
public:
    instance_dark_portal() : InstanceMapScript("instance_dark_portal", 269) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_dark_portal_script(map);
    }


    struct instance_dark_portal_script : public InstanceScript
    {
        instance_dark_portal_script(Map *map) : InstanceScript(map) { Initialize(); };

        Creature* currentBoss;      // Store current wave's boss to despawn it if Medivh dies during an encounter

        uint32 Encounter[ENCOUNTERS];

        uint32 mRiftPortalCount;
        uint32 mShieldPercent;
        uint8 mRiftWaveCount;
        uint8 mRiftWaveId;

        uint32 NextPortal_Timer;

        uint64 MedivhGUID;
        uint8 CurrentRiftId;

        bool bIsInstanceBossInProgress;

        void Initialize()
            override {
            bIsInstanceBossInProgress = false;
            MedivhGUID = 0;
            Clear();
            SetData(DATA_INSTANCE_BOSS, NOT_STARTED);
            for (uint32 & i : Encounter)
                i = NOT_STARTED;
        }

        void Clear()
        {
            for (uint8 i = 0; i < 2; i++)        // Do not reset bosses !
                Encounter[i] = NOT_STARTED;

            mRiftPortalCount = 0;
            mShieldPercent = 100;
            mRiftWaveCount = 0;
            mRiftWaveId = 0;

            CurrentRiftId = 0;

            NextPortal_Timer = 0;
        }

        void UpdateBMWorldState(uint32 id, uint32 state)
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                for (const auto & itr : players)
                {
                    if (Player* player = itr.GetSource())
                        player->SendUpdateWorldState(id, state);
                }
            }
            else TC_LOG_ERROR("scripts", "TSCR: Instance Black Portal: UpdateBMWorldState, but PlayerList is empty!");
        }

        void InitWorldState(bool Enable = true)
        {
            UpdateBMWorldState(WORLD_STATE_BM, Enable ? 1 : 0);
            UpdateBMWorldState(WORLD_STATE_BM_SHIELD, 100);
            UpdateBMWorldState(WORLD_STATE_BM_RIFT, 0);
        }

        bool IsEncounterInProgress() const override
        {
            if (GetData(TYPE_MEDIVH) == IN_PROGRESS)
                return true;

            return false;
        }

        void OnPlayerEnter(Player *player) override
        {
            if (GetData(TYPE_MEDIVH) == IN_PROGRESS)
                return;

            player->SendUpdateWorldState(WORLD_STATE_BM, 0);
        }

        void OnCreatureCreate(Creature *pCreature) override
        {
            if (pCreature->GetEntry() == C_MEDIVH)
                MedivhGUID = pCreature->GetGUID();
        }

        //what other conditions to check?
        bool CanProgressEvent()
        {
            if (!GetPlayer())
                return false;

            return true;
        }

        uint8 GetRiftWaveId()
        {
            switch (mRiftPortalCount)
            {
            case 6:
                mRiftWaveId = 2;
                return 1;
            case 12:
                mRiftWaveId = 4;
                return 3;
            case 18:
                return 5;
            default:
                return mRiftWaveId;
            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case TYPE_MEDIVH:
                if (data == SPECIAL && Encounter[0] == IN_PROGRESS)
                {
                    --mShieldPercent;
                    UpdateBMWorldState(WORLD_STATE_BM_SHIELD, mShieldPercent);

                    if (!mShieldPercent)
                    {
                        if (Unit *medivh = instance->GetCreature(MedivhGUID))
                        {
                            if (medivh->IsAlive())
                            {
                                medivh->DealDamage(medivh, medivh->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                                // Despawn current boss
                                if (currentBoss) {
                                    currentBoss->DealDamage(currentBoss, medivh->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                                    currentBoss->DespawnOrUnsummon();
                                }
                                Encounter[0] = FAIL;
                                Encounter[1] = NOT_STARTED;
                            }
                        }
                    }
                }
                else
                {
                    if (data == IN_PROGRESS)
                    {
                        InitWorldState();
                        //prevent players from complete quest during event
                        if (Unit *medivh = instance->GetCreature(MedivhGUID))
                            medivh->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        Encounter[1] = IN_PROGRESS;
                        NextPortal_Timer = 30000;
                    }

                    if (data == DONE)
                    {
                        //this may be completed further out in the post-event
                        Map::PlayerList const& players = instance->GetPlayers();

                        //setting Quest Giver flag back after event
                        if (Unit *medivh = instance->GetCreature(MedivhGUID))
                            medivh->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

                        if (!players.isEmpty())
                        {
                            for (const auto & player : players)
                            {
                                if (Player* pPlayer = player.GetSource())
                                {
                                    if (pPlayer->GetQuestStatus(QUEST_OPENING_PORTAL) == QUEST_STATUS_INCOMPLETE)
                                        pPlayer->AreaExploredOrEventHappens(QUEST_OPENING_PORTAL);

                                    if (pPlayer->GetQuestStatus(QUEST_MASTER_TOUCH) == QUEST_STATUS_INCOMPLETE)
                                        pPlayer->AreaExploredOrEventHappens(QUEST_MASTER_TOUCH);
                                }
                            }
                        }
                    }

                    Encounter[0] = data;
                }
                break;
            case TYPE_RIFT:
                if (data == SPECIAL)
                {
                    //if (mRiftPortalCount < 7)
                    NextPortal_Timer = 30000;
                }
                else
                    Encounter[1] = data;
                break;
            case DATA_DEJA:
                Encounter[2] = data;
                if (data == DONE) {
                    SaveToDB();
                    SetData(DATA_INSTANCE_BOSS, NOT_STARTED);
                }
                break;
            case DATA_TEMPORUS:
                Encounter[3] = data;
                if (data == DONE) {
                    SaveToDB();
                    SetData(DATA_INSTANCE_BOSS, NOT_STARTED);
                }
                break;
            case DATA_AEONUS:
                Encounter[4] = data;
                if (data == DONE) {
                    SaveToDB();
                    SetData(DATA_INSTANCE_BOSS, NOT_STARTED);
                }
                break;
            case DATA_INSTANCE_BOSS:
                if (data == IN_PROGRESS)
                    bIsInstanceBossInProgress = true;
                else
                    bIsInstanceBossInProgress = false;
                break;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case TYPE_MEDIVH:
                return Encounter[0];
            case TYPE_RIFT:
                return Encounter[1];
            case DATA_PORTAL_COUNT:
                return mRiftPortalCount;
            case DATA_SHIELD:
                return mShieldPercent;
            case DATA_DEJA:
                return Encounter[2];
            case DATA_TEMPORUS:
                return Encounter[3];
            case DATA_AEONUS:
                return Encounter[4];
            case DATA_INSTANCE_BOSS:
                return bIsInstanceBossInProgress ? 1 : 0;
            }
            return 0;
        }

        uint64 GetData64(uint32 data) const override
        {
            if (data == DATA_MEDIVH)
                return MedivhGUID;
            if (data == TYPE_GET_PLAYER) {
                Player* player = GetPlayer();
                return player ? player->GetGUID() : 0;
            }

            return 0;
        }

        Unit* SummonedPortalBoss(Unit* source)
        {
            uint32 entry = RiftWaves[GetRiftWaveId()].PortalBoss;

            // Spawn normal wave is boss has been defeated in a previous try
            if ((GetRiftWaveId() == 1 && GetData(DATA_DEJA) == DONE) || (GetRiftWaveId() == 3 && GetData(DATA_TEMPORUS) == DONE) || (GetRiftWaveId() == 5 && GetData(DATA_AEONUS) == DONE))
                entry = RIFT_BOSS;

            if (entry == RIFT_BOSS)
                entry = RandRiftBoss();
            else        // This is an instance boss, don't spawn anything else from that portal
                SetData(DATA_INSTANCE_BOSS, IN_PROGRESS);

            float x, y, z;
            source->GetRandomPoint(source, 10.0f, x, y, z);

            //normalize Z-level if we can, if rift is not at ground level.
            z = std::max(instance->GetHeight(x, y, MAX_HEIGHT), instance->GetWaterLevel(x, y));

            Unit *Summon = source->SummonCreature(entry, x, y, z, source->GetOrientation(),
                TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000);

            if (Summon) {
                currentBoss = Summon->ToCreature();
                return Summon;
            }

            TC_LOG_ERROR("scripts", "Instance Dark Portal: what just happened there? No boss, no loot, no fun...");
            return nullptr;
        }

        void DoSpawnPortal()
        {
            if (Creature* pMedivh = instance->GetCreature(MedivhGUID))
            {
                int tmp = rand() % (4 - 1);

                if (tmp >= CurrentRiftId)
                    tmp++;

                CurrentRiftId = tmp;

                Creature* pTemp = pMedivh->SummonCreature(C_TIME_RIFT,
                    PortalLocation[tmp][0], PortalLocation[tmp][1], PortalLocation[tmp][2], PortalLocation[tmp][3],
                    TEMPSUMMON_CORPSE_DESPAWN, 0);
                if (pTemp)
                {

                    pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                    if (Creature* pBoss = (SummonedPortalBoss(pTemp))->ToCreature())
                    {
                        if (pBoss->GetEntry() == C_AEONUS)
                        {
                            pBoss->GetThreatManager().AddThreat(pMedivh, 0.1f);
                            pBoss->AI()->AttackStart(pMedivh);
                        }
                        else
                        {
                            pBoss->GetThreatManager().AddThreat(pTemp, 0.1f);
                            pTemp->CastSpell(pBoss, SPELL_RIFT_CHANNEL, TRIGGERED_NONE);
                            pBoss->AI()->AttackStart(pMedivh);
                        }
                    }
                }
            }
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream stream;
            stream << Encounter[0] << " " << Encounter[1] << " " << Encounter[2] << " " << Encounter[3] << " " << Encounter[4];

            OUT_SAVE_INST_DATA_COMPLETE
                return stream.str();
        }

        void Load(const char* in) override
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);
            std::istringstream stream(in);
            stream >> Encounter[0] >> Encounter[1] >> Encounter[2] >> Encounter[3] >> Encounter[4];
            for (uint32 & i : Encounter)
                if (i == IN_PROGRESS)                // Do not load an encounter as "In Progress" - reset it instead.
                    i = NOT_STARTED;
            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void Update(uint32 diff) override
        {
            if (Encounter[1] != IN_PROGRESS)
                return;

            if (mRiftPortalCount >= 18)  // Event is done, stop here
                return;

            //add delay timer?
            if (!CanProgressEvent())
            {
                Clear();
                return;
            }

            if (NextPortal_Timer)
            {
                if (NextPortal_Timer <= diff)
                {
                    ++mRiftPortalCount;

                    UpdateBMWorldState(WORLD_STATE_BM_RIFT, mRiftPortalCount);

                    DoSpawnPortal();
                    NextPortal_Timer = RiftWaves[GetRiftWaveId()].NextPortalTime;
                }
                else NextPortal_Timer -= diff;
            }
        }
    };
};

void AddSC_instance_dark_portal()
{
    new instance_dark_portal();
}

