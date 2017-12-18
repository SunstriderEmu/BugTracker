
#ifndef MANA_TOMBS_H_
#define MANA_TOMBS_H_

#include "CreatureAIImpl.h"

#define MTScriptName "instance_mana_tombs"
#define DataHeader "MT"

uint32 const EncounterCount = 4;

enum MTDataTypes
{
    // Encounter States/Boss GUIDs
    DATA_PANDEMONIUS            = 0,
    DATA_TAVAROK                = 1,
    DATA_NEXUSPRINCE_SHAFFAR    = 2,
    DATA_YOR                    = 3
};

template <class AI, class T>
inline AI* GetManaTombsAI(T* obj)
{
    return GetInstanceAI<AI>(obj, MTScriptName);
}

#endif // MANA_TOMBS_H_
