/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_SHATTERED_H
#define DEF_SHATTERED_H

#define SHScriptName "instance_shattered_halls"
#define DataHeader "SH"

uint32 const EncounterCount          = 5;
uint32 const VictimCount             = 3;

enum eShatteredHalls 
{
    DATA_NETHEKURSE   = 0,
    DATA_PORUNG       = 1,
    DATA_OMROGG       = 2,
    DATA_BLADEFIST    = 3,
    DATA_EXECUTIONER  = 4,

    DATA_NETHEKURSE_GUID    = 5,
    DATA_EXECUTIONER_GUID   = 6,

    DATA_TIMER_LEFT         = 7,    // Every 30 sec, timer is saved in DB (total time = 55 + 10 + 15 = 80 minutes, first buff at 80' left, second at 25', third at 15')
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
};

enum eSpellsExecutioner 
{
    SPELL_KARGATH_EXECUTIONER_1       = 39288, //55
    SPELL_KARGATH_EXECUTIONER_2       = 39289, //10
    SPELL_KARGATH_EXECUTIONER_3       = 39290, //15
    
    SPELL_REMOVE_KARGATH_EXECUTIONER  = 39291,
};

template <class AI, class T>
inline AI* GetShatteredHallsAI(T* obj)
{
    return GetInstanceAI<AI>(obj, SHScriptName);
}

#endif

