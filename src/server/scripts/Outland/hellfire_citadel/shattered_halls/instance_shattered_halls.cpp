
/* ScriptData
SDName: Instance_Shattered_Halls
SD%Complete: 90
SDComment: Loots of the Executioner should depend on the amount of prisoners killed
SDCategory: Hellfire Citadel, Shattered Halls
EndScriptData */

#include "shattered_halls.h"

uint32 HordePrisoners[3] = { 17296, 17295, 17297 };
uint32 AlliancePrisoners[3] = { 17290, 17292, 17289 };
float PrisonersCoord[3][4] = 
{
    { 147.752808f, -79.643730f, 1.917701f, 5.537074f },
    { 142.168777f, -84.358223f, 1.908038f, 6.264657f },
    { 145.993637f, -89.312386f, 1.915693f, 0.714077f }
};

class instance_shattered_halls : public InstanceMapScript
{
public:
    instance_shattered_halls() : InstanceMapScript("instance_shattered_halls", 540) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_shattered_halls_script(map);
    }

    struct instance_shattered_halls_script : public InstanceScript
    {
        instance_shattered_halls_script(Map* pMap) : InstanceScript(pMap) 
        { 
            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);

            FirstDoorGUID = 0;
            SecondDoorGUID = 0;
            NethekurseGUID = 0;
            executionerGUID = 0;
            kargathGUID = 0;

            victimsGUID[0] = 0;
            victimsGUID[1] = 0;
            victimsGUID[2] = 0;

            executionTimer = 0;
            SaveIntervalTimer = 30000;

            _team = 0;

            HeroicMode = pMap->IsHeroic();
        };

        uint32 SaveIntervalTimer;
        uint32 executionTimer;
        uint8 executed;
        uint32 _team;

        ObjectGuid FirstDoorGUID;
        ObjectGuid SecondDoorGUID;
        ObjectGuid NethekurseGUID;
        ObjectGuid executionerGUID;
        ObjectGuid kargathGUID;

        ObjectGuid victimsGUID[3];

        bool HeroicMode;

        void Initialize() override
        {
            if(HeroicMode)
                executionTimer = 55 * MINUTE * IN_MILLISECONDS;
        }

        void OnGameObjectCreate(GameObject* pGo) override
        {
            InstanceScript::OnGameObjectCreate(pGo);

            switch (pGo->GetEntry())
            {
            case GO_GRAND_WARLOCK_CHAMBER_DOOR_1:
                FirstDoorGUID = pGo->GetGUID();
                if(GetBossState(DATA_NETHEKURSE) == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            case GO_GRAND_WARLOCK_CHAMBER_DOOR_2:
                SecondDoorGUID = pGo->GetGUID();
                if (GetBossState(DATA_NETHEKURSE) == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            }
        }

        void OnPlayerEnter(Player* player) override
        {
            Aura* ex = nullptr;

            if (!_team)
                _team = player->GetTeam();

            player->CastSpell(player, SPELL_REMOVE_KARGATH_EXECUTIONER, true);

            if (!executionTimer || executionerGUID.IsEmpty())
                return;

            switch (executed)
            {
            case 0:
                ex = player->AddAura(SPELL_KARGATH_EXECUTIONER_1, player);
                break;
            case 1:
                ex = player->AddAura(SPELL_KARGATH_EXECUTIONER_2, player);
                break;
            case 2:
                ex = player->AddAura(SPELL_KARGATH_EXECUTIONER_3, player);
                break;
            default:
                break;
            }

            if (ex)
                ex->SetDuration(executionTimer);
        }

        void OnCreatureCreate(Creature* creature) override
        {
            InstanceScript::OnCreatureCreate(creature);

            if (!_team)
            {
                Map::PlayerList const& players = instance->GetPlayers();
                if (!players.isEmpty())
                    if (Player* player = players.begin()->GetSource())
                        _team = player->GetTeam();
            }

            switch (creature->GetEntry()) 
            {
            case NPC_GRAND_WARLOCK_NETHEKURSE:     // Nethekurse
                NethekurseGUID = creature->GetGUID();
                break;
            case NPC_KARGATH_BLADEFIST:
                kargathGUID = creature->GetGUID();
                break;
            case NPC_RANDY_WHIZZLESPROCKET:
                if (_team == HORDE)
                    creature->UpdateEntry(NPC_DRISELLA);
                break;
            case NPC_SHATTERED_EXECUTIONER:
                DoCastSpellOnPlayers(SPELL_KARGATH_EXECUTIONER_1);
                executionerGUID = creature->GetGUID();
                SaveToDB();
                break;
            case NPC_CAPTAIN_ALINA:
            case NPC_CAPTAIN_BONESHATTER:
                victimsGUID[0] = creature->GetGUID();
                break;
            case NPC_ALLIANCE_VICTIM_1:
            case NPC_HORDE_VICTIM_1:
                victimsGUID[1] = creature->GetGUID();
                break;
            case NPC_ALLIANCE_VICTIM_2:
            case NPC_HORDE_VICTIM_2:
                victimsGUID[2] = creature->GetGUID();
                break;
            }
        }

        // This is a hack. Actually, LootMgr should be able to dynamically change loot table depending on the amount of prisoners killed.
        void RewardAllPlayersInMapForQuest()
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                for (const auto & player : players)
                {
                    if (Player* plr = player.GetSource()) {
                        if (plr->GetQuestStatus(10884) == QUEST_STATUS_INCOMPLETE) {
                            plr->CompleteQuest(10884);      // Directly complete quest, so we are sure it is
                            // Now, we try to give the quest item, that looks more blizzlike that way
                            ItemPosCountVec dest;
                            uint8 msg = plr->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 31716, 1);
                            if (msg == EQUIP_ERR_OK) {
                                Item* item = plr->StoreNewItem(dest, 31716, true);
                                if (item)
                                    plr->SendNewItem(item, 1, false, true);
                            }
                            else
                                plr->SendEquipError(msg, nullptr, nullptr);
                        }
                    }
                }
            }
        }

        void CastSpellOnAllPlayersInMap(uint32 spellid)
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                for (const auto & player : players)
                {
                    if (Player* plr = player.GetSource())
                        if (plr->IsAttackableByAOE())
                            plr->CastSpell(plr, spellid, true);
                }
            }
        }

        void EnableExecutioner(bool visible)
        {
            Creature* executioner = instance->GetCreature(executionerGUID);
            if (!executioner)
                return;

            if (visible)
            {
                executioner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE);
                executioner->SetVisible(true);
            }
            else
            {
                executioner->SetVisible(false);
                executioner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE);
            }
            executioner->AI()->Reset();
        }

        bool SetBossState(uint32 type, EncounterState state) override
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
                case DATA_NETHEKURSE:
                if (state == DONE)
                {
                    HandleGameObject(FirstDoorGUID, true, nullptr);
                    HandleGameObject(SecondDoorGUID, true, nullptr);
                }
                break;
                case DATA_KARGATH:
                    if (state == DONE)
                        EnableExecutioner(true);
                    break;
                case DATA_SHATTERED_EXECUTIONER:
                {
                    if (state == IN_PROGRESS)
                    {
                        EnableExecutioner(false);
                    }
                    if (state == DONE)
                    {
                        DoCastSpellOnPlayers(SPELL_REMOVE_KARGATH_EXECUTIONER);
                        executionTimer = 0;
                        SaveToDB();
                    }
                    break;
                }
                default:
                    break;
            }
            return true;
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case DATA_TIMER_LEFT:
                executionTimer = data;
                break;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case DATA_TIMER_LEFT:
                return executionTimer;
            case DATA_TEAM_IN_INSTANCE:
                return _team;
            }

            return 0;
        }

        ObjectGuid GetGuidData(uint32 data) const override
        {
            switch (data)
            {
            case GO_GRAND_WARLOCK_CHAMBER_DOOR_1:
                return FirstDoorGUID;
            case GO_GRAND_WARLOCK_CHAMBER_DOOR_2:
                return SecondDoorGUID;
            case DATA_NETHEKURSE_GUID:
                return NethekurseGUID;
            case DATA_SHATTERED_EXECUTIONER_GUID:
                return executionerGUID;
            case NPC_KARGATH_BLADEFIST:
                return kargathGUID;
            case DATA_FIRST_PRISONER:
            case DATA_SECOND_PRISONER:
            case DATA_THIRD_PRISONER:
                return victimsGUID[data - DATA_FIRST_PRISONER];
            }

            return 0;
        }

        virtual void ReadSaveDataMore(std::istringstream& data) 
        {
            if (!instance->IsHeroic())
                return;
            data >> _team;

            uint32 readbuff;
            data >> readbuff;
            executed = uint8(readbuff);
            data >> readbuff;

            if (executed > VictimCount)
            {
                executed = VictimCount;
                executionTimer = 0;
                return;
            }

            if (!readbuff)
                return;

            Creature* executioner = nullptr;

            instance->LoadGrid(Executioner.GetPositionX(), Executioner.GetPositionY());
            if (Creature* kargath = instance->GetCreature(kargathGUID))
                if (executionerGUID.IsEmpty())
                    executioner = kargath->SummonCreature(NPC_SHATTERED_EXECUTIONER, Executioner);

            if (executioner)
            {
                for (uint8 i = executed; i < VictimCount; ++i)
                    executioner->SummonCreature(executionerVictims[i](GetData(DATA_TEAM_IN_INSTANCE)), executionerVictims[i].GetPos());
            }

            executionTimer = readbuff;

            if(executionTimer > 0 && executed < VictimCount)
                SetBossState(DATA_SHATTERED_EXECUTIONER, IN_PROGRESS);
        }

        virtual void WriteSaveDataMore(std::ostringstream& data) 
        { 
            if (!instance->IsHeroic())
                return;

            data << _team << ' ' << uint32(executed) << ' '
                << executionTimer << ' ';
        }

        // Update is only needed in Heroic, for the timer
        void Update(uint32 diff) override
        {
            if (!HeroicMode)
                return;

            if (executionTimer <= diff)
            {
                DoCastSpellOnPlayers(SPELL_REMOVE_KARGATH_EXECUTIONER);
                switch (++executed)
                {
                case 1:
                    DoCastSpellOnPlayers(SPELL_KARGATH_EXECUTIONER_2);
                    executionTimer = 10 * MINUTE * IN_MILLISECONDS;
                    break;
                case 2:
                    DoCastSpellOnPlayers(SPELL_KARGATH_EXECUTIONER_3);
                    executionTimer = 15 * MINUTE * IN_MILLISECONDS;
                    break;
                default:
                    SetBossState(DATA_SHATTERED_EXECUTIONER, FAIL);
                    executionTimer = 0;
                    break;
                }

                if (Creature* executioner = instance->GetCreature(executionerGUID))
                    executioner->AI()->SetData(DATA_PRISONERS_EXECUTED, executed);

                SaveToDB();
            }
            else
                executionTimer -= diff;


            // Save time left in DB every 30 sec
            if (SaveIntervalTimer <= diff)
            {
                SetData(DATA_TIMER_LEFT, executionTimer);
                SaveToDB();
                SaveIntervalTimer = 30 * SECOND * IN_MILLISECONDS;
            }
            else
                SaveIntervalTimer -= diff;
        }
    };
};

void AddSC_instance_shattered_halls()
{
    new instance_shattered_halls();
}

