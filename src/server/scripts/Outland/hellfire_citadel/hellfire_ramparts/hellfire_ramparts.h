
#define HRScriptName "instance_ramparts"
#define DataHeader "HR"

uint32 const EncounterCount = 4;

enum HRDataTypes
{
    DATA_WATCHKEEPER_GARGOLMAR    = 0,
    DATA_OMOR_THE_UNSCARRED       = 1,
    DATA_VAZRUDEN                 = 2,
    DATA_NAZAN                    = 3
};

enum HRCreatureIds
{
    NPC_HELLFIRE_SENTRY           = 17517,
    NPC_VAZRUDEN_HERALD           = 17307,
    NPC_VAZRUDEN                  = 17537,
    NPC_NAZAN                     = 17536,
    NPC_LIQUID_FIRE               = 22515,

    //the healing guys in Gargolmar fight
    NPC_HELLFIRE_WATCHER          = 17309,
};
enum HRGameobjectIds
{
    GO_FEL_IRON_CHEST_NORMAL = 185168,
    GO_FEL_IRON_CHEST_HEROIC = 185169
};

template <class AI, class T>
inline AI* GetHellfireRampartsAI(T* obj)
{
    return GetInstanceAI<AI>(obj, HRScriptName);
}
