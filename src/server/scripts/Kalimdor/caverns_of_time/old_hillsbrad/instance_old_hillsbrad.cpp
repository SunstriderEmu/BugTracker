
/* ScriptData
SDName: Instance_Old_Hillsbrad
SD%Complete: 75
SDComment: If thrall escort fail, all parts will reset. In future, save sub-parts and continue from last known.
SDCategory: Caverns of Time, Old Hillsbrad Foothills
EndScriptData */


#include "def_old_hillsbrad.h"

#define ENCOUNTERS      6

#define THRALL_ENTRY    17876
#define TARETHA_ENTRY   18887
#define EPOCH_ENTRY    18096

#define DRAKE_ENTRY             17848

#define QUEST_ENTRY_DIVERSION   10283
#define LODGE_QUEST_TRIGGER     20155

class instance_old_hillsbrad : public InstanceMapScript
{
public:
    instance_old_hillsbrad() : InstanceMapScript("instance_old_hillsbrad", 560) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_old_hillsbrad_script(map);
    }

    struct instance_old_hillsbrad_script : public InstanceScript
    {
        instance_old_hillsbrad_script(Map *map) : InstanceScript(map) { Initialize(); };

        uint32 Encounter[ENCOUNTERS];
        uint32 mBarrelCount;
        uint32 mThrallEventCount;

        ObjectGuid ThrallGUID;
        ObjectGuid TarethaGUID;
        ObjectGuid EpochGUID;

        void Initialize()
            override {
            mBarrelCount = 0;
            mThrallEventCount = 0;

            for (uint32 & i : Encounter) {
                if (i != DONE)
                    i = NOT_STARTED;
            }
        }

        void UpdateOHWorldState()
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                for (const auto & itr : players)
                {
                    if (Player* player = itr.GetSource())
                    {
                        player->SendUpdateWorldState(WORLD_STATE_OH, mBarrelCount);

                        if (mBarrelCount == 5)
                            player->KilledMonsterCredit(LODGE_QUEST_TRIGGER, ObjectGuid::Empty);
                    }
                }
            }
            else
                TC_LOG_ERROR("FIXME", "TSCR: Instance Old Hillsbrad: UpdateOHWorldState, but PlayerList is empty!");
        }

        void OnCreatureCreate(Creature *creature) override
        {
            switch (creature->GetEntry())
            {
            case THRALL_ENTRY:
                ThrallGUID = creature->GetGUID();
                break;
            case TARETHA_ENTRY:
                TarethaGUID = creature->GetGUID();
                break;
            case EPOCH_ENTRY:
                EpochGUID = creature->GetGUID();
                break;
            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            Player *player = GetPlayer();

            if (!player)
                return;

            switch (type)
            {
            case TYPE_BARREL_DIVERSION:
            {
                if (data == IN_PROGRESS)
                {
                    if (mBarrelCount >= 5)
                        return;

                    ++mBarrelCount;
                    UpdateOHWorldState();

                    Encounter[0] = IN_PROGRESS;

                    if (mBarrelCount == 5)
                    {
                        player->SummonCreature(DRAKE_ENTRY, 2128.43, 71.01, 64.42, 1.74, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 1800000);
                        Encounter[0] = DONE;
                    }
                }
                else 
                    Encounter[0] = data;
                break;
            }
            case TYPE_THRALL_EVENT:
            {
                if (data == FAIL)
                {
                    if (mThrallEventCount <= 20)
                    {
                        mThrallEventCount++;
                        Encounter[1] = NOT_STARTED;
                        Encounter[2] = NOT_STARTED;
                        Encounter[3] = NOT_STARTED;
                        Encounter[4] = NOT_STARTED;
                        Encounter[5] = NOT_STARTED;
                    }
                    else if (mThrallEventCount > 20)
                    {
                        Encounter[1] = data;
                        Encounter[2] = data;
                        Encounter[3] = data;
                        Encounter[4] = data;
                        Encounter[5] = data;
                    }
                }
                else
                    Encounter[1] = data;
                break;
            }
            case TYPE_THRALL_PART1:
                Encounter[2] = data;
                break;
            case TYPE_THRALL_PART2:
                Encounter[3] = data;
                break;
            case TYPE_THRALL_PART3:
                Encounter[4] = data;
                break;
            case TYPE_THRALL_PART4:
                Encounter[5] = data;
                break;
            }
        }

        uint32 GetData(uint32 data) const override
        {
            switch (data)
            {
            case TYPE_BARREL_DIVERSION:
                return Encounter[0];
            case TYPE_THRALL_EVENT:
                return Encounter[1];
            case TYPE_THRALL_PART1:
                return Encounter[2];
            case TYPE_THRALL_PART2:
                return Encounter[3];
            case TYPE_THRALL_PART3:
                return Encounter[4];
            case TYPE_THRALL_PART4:
                return Encounter[5];
            }
            return 0;
        }

        uint64 GetData64(uint32 data) const override
        {
            switch (data)
            {
            case DATA_THRALL:
                return ThrallGUID;
            case DATA_TARETHA:
                return TarethaGUID;
            case DATA_EPOCH:
                return EpochGUID;
            }
            return 0;
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream stream;
            stream << Encounter[0] << " " << Encounter[1] << " " << Encounter[2] << " " << Encounter[3] << " " << Encounter[4] << " " << Encounter[5];
            char* out = new char[stream.str().length() + 1];
            strcpy(out, stream.str().c_str());
            if (out)
            {
                OUT_SAVE_INST_DATA_COMPLETE;
                return out;
            }

            return nullptr;
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
            stream >> Encounter[0] >> Encounter[1] >> Encounter[2] >> Encounter[3] >> Encounter[4] >> Encounter[5];
            //for(uint8 i = 0; i < ENCOUNTERS; ++i)
                //if(Encounters[i] == IN_PROGRESS)                // Do not load an encounter as "In Progress" - reset it instead.
                //    Encounters[i] = NOT_STARTED;
            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_old_hillsbrad()
{
    new instance_old_hillsbrad();
}

