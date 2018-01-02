#include "def_the_eye.h"

class instance_the_eye : public InstanceMapScript
{
public:
    instance_the_eye() : InstanceMapScript(TheEyeScriptName, 550) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_the_eye_script(map);
    }

    struct instance_the_eye_script : public InstanceScript
    {
        instance_the_eye_script(Map *map) : InstanceScript(map) 
        {
            //LoadDoorData(doorData);
            Initialize(); 
        };

        ObjectGuid ThaladredTheDarkener;
        ObjectGuid LordSanguinar;
        ObjectGuid GrandAstromancerCapernian;
        ObjectGuid MasterEngineerTelonicus;
        ObjectGuid Kaelthas;
        ObjectGuid Astromancer;
        ObjectGuid Alar;
        ObjectGuid BridgeWindowGUID;
        ObjectGuid KaelStateRightGUID;
        ObjectGuid KaelStateLeftGUID;

        uint32 Encounters[MAX_ENCOUNTER];

        void Initialize() override
        {
            for (uint32 & Encounter : Encounters)
                Encounter = NOT_STARTED;
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 Encounter : Encounters)
                if (Encounter == IN_PROGRESS) 
                    return true;

            return false;
        }

        void OnCreatureCreate(Creature *creature) override 
        {
            switch (creature->GetEntry())
            {
            case NPC_THALADRED: ThaladredTheDarkener = creature->GetGUID(); break;
            case NPC_TELONICUS: MasterEngineerTelonicus = creature->GetGUID(); break;
            case NPC_CAPERNIAN: GrandAstromancerCapernian = creature->GetGUID(); break;
            case NPC_LORD_SANGUINAR: LordSanguinar = creature->GetGUID(); break;
            case NPC_KAELTHAS: Kaelthas = creature->GetGUID(); break;
            case NPC_ASTROMANCER: Astromancer = creature->GetGUID(); break;
            case NPC_ALAR: Alar = creature->GetGUID(); break;
            }
        }

        void OnGameObjectCreate(GameObject* gobject) override
        {
            switch (gobject->GetEntry())
            {
            case GO_BRIDGE_WINDOW:
                BridgeWindowGUID = gobject->GetGUID();
                break;
            case GO_KAEL_STATUE_RIGHT:
                KaelStateRightGUID = gobject->GetGUID();
                break;
            case GO_KAEL_STATUE_LEFT:
                KaelStateLeftGUID = gobject->GetGUID();
                break;
            }
        }
        uint64 GetData64(uint32 identifier) const override
        {
            switch (identifier)
            {
            case GO_BRIDGE_WINDOW:                  return BridgeWindowGUID;
            case GO_KAEL_STATUE_RIGHT:              return KaelStateRightGUID;
            case GO_KAEL_STATUE_LEFT:              return KaelStateLeftGUID;
            case DATA_THALADREDTHEDARKENER:        return ThaladredTheDarkener;
            case DATA_LORDSANGUINAR:               return LordSanguinar;
            case DATA_GRANDASTROMANCERCAPERNIAN:   return GrandAstromancerCapernian;
            case DATA_MASTERENGINEERTELONICUS:     return MasterEngineerTelonicus;
            case NPC_KAELTHAS:                     return Kaelthas;
            case NPC_ASTROMANCER:                  return Astromancer;
            case NPC_ALAR:                         return Alar;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data) override
        {
            if (type >= MAX_ENCOUNTER)
                return;

            Encounters[type] = data;
            if (data == DONE)
                SaveToDB();
        }

        uint32 GetData(uint32 type) const override
        {
            if (type >= MAX_ENCOUNTER)
                return 0;

            return Encounters[type];
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream stream;
            stream << Encounters[0] << " " << Encounters[1] << " " << Encounters[2] << " " << Encounters[3];

            OUT_SAVE_INST_DATA_COMPLETE;
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
            stream >> Encounters[0] >> Encounters[1] >> Encounters[2] >> Encounters[3];
            for (uint32 & Encounter : Encounters)
                if (Encounter == IN_PROGRESS)                // Do not load an encounter as "In Progress" - reset it instead.
                    Encounter = NOT_STARTED;
            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_the_eye()
{
    new instance_the_eye();
}

