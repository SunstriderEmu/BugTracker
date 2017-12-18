
/* ScriptData
SDName: Instance_Blood_Furnace
SD%Complete: 85
SDComment:
SDCategory: Hellfire Citadel, Blood Furnace
EndScriptData */


#include "blood_furnace.h"

#define MAX_ORC_WAVES               4
#define MAX_BROGGOK_WAVES           5

#define SAY_BROGGOK_INTRO            -1542015

DoorData const doorData[] =
{
    { GO_PRISON_DOOR_01, DATA_KELIDAN_THE_BREAKER, DOOR_TYPE_PASSAGE },
    { GO_PRISON_DOOR_02, DATA_THE_MAKER,           DOOR_TYPE_ROOM },
    { GO_PRISON_DOOR_03, DATA_THE_MAKER,           DOOR_TYPE_PASSAGE },
    { GO_PRISON_DOOR_04, DATA_BROGGOK,             DOOR_TYPE_PASSAGE },
    { GO_PRISON_DOOR_05, DATA_BROGGOK,             DOOR_TYPE_ROOM },
    { GO_SUMMON_DOOR,    DATA_KELIDAN_THE_BREAKER, DOOR_TYPE_PASSAGE },
    { 0,                 0,                        DOOR_TYPE_ROOM } // END
};

class instance_blood_furnace : public InstanceMapScript
{
public:
    instance_blood_furnace() : InstanceMapScript(BFScriptName, 542) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_blood_furnace_script(map);
    }

    struct instance_blood_furnace_script : public InstanceScript
    {
        instance_blood_furnace_script(Map *map) : InstanceScript(map) 
        {
            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);
            LoadDoorData(doorData);

            PrisonerCounter5 = 0;
            PrisonerCounter6 = 0;
            PrisonerCounter7 = 0;
            PrisonerCounter8 = 0;

            PrisonDoor4GUID = 0;
            BroggokLeverGUID = 0;
        };

        uint64 BroggokGUID;
        uint64 PrisonDoor4GUID;
        uint64 BroggokLeverGUID;

        ObjectGuid PrisonCellGUIDs[8];

        uint8 PrisonerCounter5;
        uint8 PrisonerCounter6;
        uint8 PrisonerCounter7;
        uint8 PrisonerCounter8;
        
        void OnCreatureCreate(Creature* creature) override
        {
            InstanceScript::OnCreatureCreate(creature);

            switch (creature->GetEntry())
            {
                case NPC_BROGGOK: BroggokGUID = creature->GetGUID(); break;
            }
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            InstanceScript::OnGameObjectCreate(go);

            switch (go->GetEntry())
            {
            case GO_PRISON_DOOR_04:
                PrisonDoor4GUID = go->GetGUID();
                break;
            case GO_BROGGOK_LEVER: 
                BroggokLeverGUID = go->GetGUID();
                break;
            case GO_PRISON_CELL_DOOR_1:
                PrisonCellGUIDs[DATA_PRISON_CELL1 - DATA_PRISON_CELL1] = go->GetGUID();
                break;
            case GO_PRISON_CELL_DOOR_2:
                PrisonCellGUIDs[DATA_PRISON_CELL2 - DATA_PRISON_CELL1] = go->GetGUID();
                break;
            case GO_PRISON_CELL_DOOR_3:
                PrisonCellGUIDs[DATA_PRISON_CELL3 - DATA_PRISON_CELL1] = go->GetGUID();
                break;
            case GO_PRISON_CELL_DOOR_4:
                PrisonCellGUIDs[DATA_PRISON_CELL4 - DATA_PRISON_CELL1] = go->GetGUID();
                break;
            case GO_PRISON_CELL_DOOR_5:
                PrisonCellGUIDs[DATA_PRISON_CELL5 - DATA_PRISON_CELL1] = go->GetGUID();
                break;
            case GO_PRISON_CELL_DOOR_6:
                PrisonCellGUIDs[DATA_PRISON_CELL6 - DATA_PRISON_CELL1] = go->GetGUID();
                break;
            case GO_PRISON_CELL_DOOR_7:
                PrisonCellGUIDs[DATA_PRISON_CELL7 - DATA_PRISON_CELL1] = go->GetGUID();
                break;
            case GO_PRISON_CELL_DOOR_8:
                PrisonCellGUIDs[DATA_PRISON_CELL8 - DATA_PRISON_CELL1] = go->GetGUID();
                break;
            }
        }

        bool SetBossState(uint32 type, EncounterState data) override
        {
            if (!InstanceScript::SetBossState(type, data))
                return false;

            switch (type)
            {
                case DATA_BROGGOK:
                {
                    switch (data)
                    {
                    case NOT_STARTED:
                        ResetPrisons();
                        if (GameObject* lever = instance->GetGameObject(BroggokLeverGUID))
                            if (!lever->isSpawned())
                                lever->Respawn();
                            else
                                lever->ResetDoorOrButton();
                        break;
                    }
                    break;
                }
            }

            return true;
        }

        ObjectGuid GetGuidData(uint32 data) const override
        {
            switch (data)
            {
            case DATA_BROGGOK_GUID:
                return BroggokGUID;
            case DATA_BROGGOK_LEVER:
                return BroggokLeverGUID;
            }

            return 0;
        }

        void ResetPrisons()
        {
            HandleGameObject(PrisonCellGUIDs[DATA_PRISON_CELL5 - DATA_PRISON_CELL1], false);
            HandleGameObject(PrisonCellGUIDs[DATA_PRISON_CELL6 - DATA_PRISON_CELL1], false);
            HandleGameObject(PrisonCellGUIDs[DATA_PRISON_CELL7 - DATA_PRISON_CELL1], false);
            HandleGameObject(PrisonCellGUIDs[DATA_PRISON_CELL8 - DATA_PRISON_CELL1], false);
        }
        
        void SetData(uint32 type, uint32 data) override {
            switch (type)
            {
            case DATA_ACTIVATE_CELL:
                switch (data)
                {
                case DATA_PRISON_CELL5:
                case DATA_PRISON_CELL6:
                case DATA_PRISON_CELL7:
                case DATA_PRISON_CELL8:
                    HandleGameObject(PrisonCellGUIDs[data - DATA_PRISON_CELL1], true);
                    break;
                case DATA_DOOR_4:
                    HandleGameObject(PrisonDoor4GUID, true);
                }
                break;
            }
        }
    };
};

class PrisonCellLevel : public GameObjectScript
{
public:
    PrisonCellLevel() : GameObjectScript("go_prison_cell_lever")
    {}

    struct PrisonCellLevelAI : public GameObjectAI
    {
        PrisonCellLevelAI(GameObject* go) : GameObjectAI(go), instance(go->GetInstanceScript()) {}

        InstanceScript* instance;

        bool GossipHello(Player* /*player*/) override
        {
            if (!instance)
                return false;

            if (instance->GetBossState(DATA_BROGGOK) != DONE && instance->GetBossState(DATA_BROGGOK) != IN_PROGRESS)
            {
                instance->SetBossState(DATA_BROGGOK, IN_PROGRESS);
                if (Creature* broggok = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_BROGGOK_GUID)))
                    broggok->AI()->DoAction(ACTION_START_EVENT);
            }

            me->UseDoorOrButton();
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return GetBloodFurnaceAI<PrisonCellLevelAI>(go);
    }
};

void AddSC_instance_blood_furnace()
{
    new instance_blood_furnace();
    new PrisonCellLevel();
}
