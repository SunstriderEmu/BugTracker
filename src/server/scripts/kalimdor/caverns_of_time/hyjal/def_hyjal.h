/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_HYJAL_H
#define DEF_HYJAL_H

#define WORLD_STATE_WAVES         2842
#define WORLD_STATE_ENEMY         2453
#define WORLD_STATE_ENEMYCOUNT    2454

#define DATA_ANETHERON            1
#define DATA_ANETHERONEVENT       2
#define DATA_ARCHIMONDE           3
#define DATA_ARCHIMONDEEVENT      4
#define DATA_AZGALOR              5
#define DATA_AZGALOREVENT         6
#define DATA_JAINAPROUDMOORE      7
#define DATA_KAZROGAL             8
#define DATA_KAZROGALEVENT        9
#define DATA_RAGEWINTERCHILL      10
#define DATA_RAGEWINTERCHILLEVENT 11
#define DATA_THRALL               12
#define DATA_TYRANDEWHISPERWIND   13
#define DATA_TRASH                14
#define DATA_RESET_TRASH_COUNT    15
#define DATA_ALLIANCE_RETREAT     16
#define DATA_HORDE_RETREAT        17
#define DATA_RAIDDAMAGE           18
#define DATA_RESET_RAIDDAMAGE     19
#define DATA_CURRENT_WAVE         20
#define DATA_JAINAINCOMBAT        21

enum HyjalCreatures
{
    CREATURE_RAGE_WINTERCHILL   = 17767,
    CREATURE_ANATHERON          = 17808,
    CREATURE_KAZROGAL           = 17888,
    CREATURE_AZGALOR            = 17842,
    CREATURE_ARCHIMONDE         = 17968,
    CREATURE_JAINA              = 17772,
    CREATURE_THRALL             = 17852,
    CREATURE_TYRANDE            = 17948,

    CREATURE_ALLIANCE_FOOTMAN   = 17919,
    CREATURE_ALLIANCE_KNIGHT    = 17920,
    CREATURE_ALLIANCE_RIFLEMAN  = 17921,
    CREATURE_ALLIANCE_SORCERESS = 17922,
    CREATURE_ALLIANCE_PRIEST    = 17928,
};

enum HyjalGobjects
{
    GOBJECT_DOOR_ORC = 182060, // teleport door leading to orc encampment
    GOBJECT_DOOR_ELF = 182061, // teleport door leading to elf encampment
};

#define ERROR_INST_DATA     "TSCR: Instance data not set properly for Mount Hyjal. Encounters will be buggy"
#endif

