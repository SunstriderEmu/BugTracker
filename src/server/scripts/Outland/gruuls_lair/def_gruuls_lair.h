
#ifndef DEF_GRUULS_LAIR_H
#define DEF_GRUULS_LAIR_H

#define GLScriptName "instance_gruuls_lair"
#define DataHeader   "GL"

enum GLDataTypes
{
    // Encounter States/Boss GUIDs
    DATA_MAULGAR = 0,
    DATA_GRUUL   = 1,

    DATA_KIGGLERTHECRAZED_GUID = 3,
    DATA_KROSHFIREHAND_GUID = 4,
    DATA_MAULGAR_GUID = 5,
    DATA_MAULGAREVENT_TANK = 6,
    DATA_OLMTHESUMMONER_GUID = 7,
    DATA_MAULGARDOOR_GUID = 8,
    DATA_GRUULDOOR_GUID = 9,
    DATA_BLINDEYETHESEER_GUID = 10,
};

uint32 const EncounterCount = 2;

enum GLCreatureIds
{
    NPC_MAULGAR = 18831,
    NPC_KROSH_FIREHAND = 18832,
    NPC_OLM_THE_SUMMONER = 18834,
    NPC_KIGGLER_THE_CRAZED = 18835,
    NPC_BLINDEYE_THE_SEER = 18836
};

enum GLGameObjectIds
{
    GO_MAULGAR_DOOR = 184468,
    GO_GRUUL_DOOR = 184662
};

template <class AI, class T>
inline AI* GetGruulsLairAI(T* obj)
{
    return GetInstanceAI<AI>(obj, GLScriptName);
}

#endif

