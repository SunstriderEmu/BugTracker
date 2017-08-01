/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_THE_EYE_H
#define DEF_THE_EYE_H

#include "CreatureAIImpl.h"

#define TheEyeScriptName "instance_the_eye"

enum EyeData
{
    DATA_ALAR_EVENT = 0,
    DATA_ASTROMANCER_EVENT = 1,
    DATA_VOIDREAVER_EVENT = 2,
    DATA_KAELTHAS_EVENT = 3,
    MAX_ENCOUNTER = 4,

    DATA_KAEL_ADVISOR1 = 10,
    DATA_KAEL_ADVISOR2 = 11,
    DATA_KAEL_ADVISOR3 = 12,
    DATA_KAEL_ADVISOR4 = 13,
};

enum EyeNPCs
{
    NPC_ALAR = 19514,
    NPC_ASTROMANCER = 18805,
    NPC_KAELTHAS = 19622,
    NPC_THALADRED = 20064,
    NPC_LORD_SANGUINAR = 20060,
    NPC_CAPERNIAN = 20062,
    NPC_TELONICUS = 20063
};

enum EyeGOs
{
    GO_BRIDGE_WINDOW = 184069,
    GO_KAEL_STATUE_RIGHT = 184596,
    GO_KAEL_STATUE_LEFT = 184597
};

template <class AI, class T>
inline AI* GetTheEyeAI(T* obj)
{
    //return GetInstanceAI<AI>(obj, TheEyeScriptName); //compil fails...
    return new AI(obj);
}

#endif

