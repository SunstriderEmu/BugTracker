
/* ScriptData
SDName: Instance_Gruuls_Lair
SD%Complete: 100
SDComment:
SDCategory: Gruul's Lair
EndScriptData */


#include "def_gruuls_lair.h"

#define ENCOUNTERS 2

/* Gruuls Lair encounters:
1 - High King Maulgar event
2 - Gruul event
*/

DoorData const doorData[] =
{
    { GO_MAULGAR_DOOR,  DATA_MAULGAR_GUID,  DOOR_TYPE_PASSAGE },
    { GO_GRUUL_DOOR,    DATA_GRUUL,         DOOR_TYPE_ROOM },
    { 0,                0,                  DOOR_TYPE_ROOM } // END
};

class instance_gruuls_lair : public InstanceMapScript
{
public:
    instance_gruuls_lair() : InstanceMapScript(GLScriptName, 565) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_gruuls_lair_script(map);
    }

    struct instance_gruuls_lair_script : public InstanceScript
    {
        instance_gruuls_lair_script(Map *map) : InstanceScript(map)
        {
            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);
            LoadDoorData(doorData);

            MaulgarEvent_Tank = 0;
            KigglerTheCrazed = 0;
            BlindeyeTheSeer = 0;
            OlmTheSummoner = 0;
            KroshFirehand = 0;
            Maulgar = 0;

            MaulgarDoor = 0;
            GruulDoor = 0;
        };

        uint64 MaulgarEvent_Tank;
        uint64 KigglerTheCrazed;
        uint64 BlindeyeTheSeer;
        uint64 OlmTheSummoner;
        uint64 KroshFirehand;
        uint64 Maulgar;

        uint64 MaulgarDoor;
        uint64 GruulDoor;

        void OnCreatureCreate(Creature *creature) override
        {
            InstanceScript::OnCreatureCreate(creature);

            switch (creature->GetEntry())
            {
            case NPC_KIGGLER_THE_CRAZED: KigglerTheCrazed = creature->GetGUID(); break;
            case NPC_BLINDEYE_THE_SEER: BlindeyeTheSeer = creature->GetGUID();  break;
            case NPC_OLM_THE_SUMMONER: OlmTheSummoner = creature->GetGUID();   break;
            case NPC_KROSH_FIREHAND: KroshFirehand = creature->GetGUID();    break;
            case NPC_MAULGAR: Maulgar = creature->GetGUID();          break;
            }
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            InstanceScript::OnGameObjectCreate(go);

            switch (go->GetEntry())
            {
            case GO_MAULGAR_DOOR:
                MaulgarDoor = go->GetGUID();
                break;
            case GO_GRUUL_DOOR:
                GruulDoor = go->GetGUID(); break;
            }
        }

        void SetGuidData(uint32 type, ObjectGuid data) override
        {
            switch (type)
            {
            case DATA_MAULGAREVENT_TANK:
                MaulgarEvent_Tank = data;
                break;

            }
        }

        ObjectGuid GetGuidData(uint32 identifier) const override
        {
            switch (identifier)
            {
            case DATA_MAULGAREVENT_TANK:         return MaulgarEvent_Tank;
            case DATA_KIGGLERTHECRAZED_GUID:     return KigglerTheCrazed;
            case DATA_BLINDEYETHESEER_GUID:      return BlindeyeTheSeer;
            case DATA_OLMTHESUMMONER_GUID:       return OlmTheSummoner;
            case DATA_KROSHFIREHAND_GUID:        return KroshFirehand;
            case DATA_MAULGARDOOR_GUID:          return MaulgarDoor;
            case DATA_GRUULDOOR_GUID:            return GruulDoor;
            case DATA_MAULGAR_GUID:              return Maulgar;
            }
            return 0;
        }
    };
};

void AddSC_instance_gruuls_lair()
{
    new instance_gruuls_lair();
}

