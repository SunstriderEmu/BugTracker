#ifndef DEF_SETHEKK_HALLS_H
#define DEF_SETHEKK_HALLS_H

#define SHScriptName "instance_sethekk_halls"
#define DataHeader "SH"

uint32 const EncounterCount = 3;
enum SHDataTypes
{
    // Encounter States/Boss GUIDs
    DATA_DARKWEAVER_SYTH                = 0,
    DATA_TALON_KING_IKISS               = 1,
    DATA_ANZU                           = 2,

    ANZU_SUMMONER_GUID                  = 3,

    // Additional Data
    //DATA_TALON_KING_COFFER              = 3
};

enum SHCreatureIds
{
    NPC_ANZU                            = 23035,
    NPC_BROOD_OF_ANZU                   = 23132,
};

enum SHGameObjectIds
{
    GO_IKISS_DOOR                       = 177203,
    GO_TALON_KING_COFFER                = 187372,
};

template <class AI, class T>
inline AI* GetSethekkHallsAI(T* obj)
{
    return GetInstanceAI<AI>(obj, SHScriptName);
}

#endif

