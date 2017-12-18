/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_SHATTERED_H
#define DEF_SHATTERED_H

#define SHScriptName "instance_shattered_halls"
#define DataHeader "SH"

uint32 const EncounterCount          = 4;
uint32 const VictimCount             = 3;

enum eShatteredHalls 
{
    DATA_NETHEKURSE   = 0,
    DATA_PORUNG       = 1,
    DATA_OMROGG       = 2,
    DATA_KARGATH      = 3,
    DATA_SHATTERED_EXECUTIONER  = 4,

    DATA_NETHEKURSE_GUID    = 5,
    DATA_SHATTERED_EXECUTIONER_GUID   = 6,

    DATA_TIMER_LEFT         = 7,    // Every 30 sec, timer is saved in DB (total time = 55 + 10 + 15 = 80 minutes, first buff at 80' left, second at 25', third at 15')
    DATA_PRISONERS_EXECUTED = 8,

    DATA_TEAM_IN_INSTANCE,

    DATA_FIRST_PRISONER,
    DATA_SECOND_PRISONER,
    DATA_THIRD_PRISONER
};

enum SHGameobjectIds
{
    GO_GRAND_WARLOCK_CHAMBER_DOOR_1  = 182539,
    GO_GRAND_WARLOCK_CHAMBER_DOOR_2  = 182540,
};

enum SHCreatureIds
{
    NPC_GRAND_WARLOCK_NETHEKURSE     = 16807,
    NPC_KARGATH_BLADEFIST            = 16808,

    NPC_SHATTERED_EXECUTIONER        = 17301,

    //Prisoners
    // Alliance Ids
    NPC_RANDY_WHIZZLESPROCKET        = 17288,

    NPC_CAPTAIN_ALINA                = 17290,
    NPC_ALLIANCE_VICTIM_1            = 17289,
    NPC_ALLIANCE_VICTIM_2            = 17292,

    // Horde Ids
    NPC_DRISELLA                     = 17294,

    NPC_CAPTAIN_BONESHATTER          = 17296,
    NPC_HORDE_VICTIM_1               = 17295,
    NPC_HORDE_VICTIM_2               = 17297
};

enum SHQuestIds
{
    QUEST_IMPRISONED_A               = 9524,
    QUEST_IMPRISONED_H               = 9525,
};

enum eSpellsExecutioner 
{
    SPELL_KARGATH_EXECUTIONER_1       = 39288, //55
    SPELL_KARGATH_EXECUTIONER_2       = 39289, //10
    SPELL_KARGATH_EXECUTIONER_3       = 39290, //15
    
    SPELL_REMOVE_KARGATH_EXECUTIONER  = 39291,
};

enum SHActions
{
    ACTION_EXECUTIONER_TAUNT = 1
};

Position const Executioner = { 152.8524f, -83.63912f, 2.021005f, 0.06981317f };

struct FactionSpawnerHelper
{
    FactionSpawnerHelper(uint32 allianceEntry, uint32 hordeEntry, Position const& pos) : _allianceNPC(allianceEntry), _hordeNPC(hordeEntry), _spawnPos(pos) { }

    inline uint32 operator()(uint32 teamID) const { return teamID == ALLIANCE ? _allianceNPC : _hordeNPC; }
    inline Position const& GetPos() const { return _spawnPos; }

private:
    uint32 const _allianceNPC;
    uint32 const _hordeNPC;
    Position const _spawnPos;
};

FactionSpawnerHelper const executionerVictims[VictimCount] =
{
    { NPC_CAPTAIN_ALINA,     NPC_CAPTAIN_BONESHATTER,{ 138.8807f, -84.22707f, 1.992269f, 0.06981317f } },
    { NPC_ALLIANCE_VICTIM_1, NPC_HORDE_VICTIM_1,{ 151.2411f, -91.02930f, 2.019741f, 1.57079600f } },
    { NPC_ALLIANCE_VICTIM_2, NPC_HORDE_VICTIM_2,{ 151.0459f, -77.51981f, 2.021008f, 4.74729500f } }
};

template <class AI, class T>
inline AI* GetShatteredHallsAI(T* obj)
{
    return GetInstanceAI<AI>(obj, SHScriptName);
}

#endif

