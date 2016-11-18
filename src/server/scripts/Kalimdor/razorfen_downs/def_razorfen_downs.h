/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef DEF_RAZORFEN_DOWNS_H
#define DEF_RAZORFEN_DOWNS_H

/*** Encounters ***/
enum Data
{
    DATA_WAVE_EVENT,
    DATA_CREATURE_CREDIT,
    DATA_TUTEN_KASH_EVENT,
    DATA_MORDRESH_FIRE_EYE,
    DATA_RAGGLESNOUT_EVENT,
    DATA_AMNENNAR_THE_COLDBRINGER_EVENT,
    DATA_GLUTTON_EVENT,
    DATA_PLAGUEMAW_THE_ROTTING_EVENT,
};

enum Creatures
{
    /* Misc */
    BOSS_TUTEN_KASH                       = 7355,
    BOSS_MORDRESH_FIRE_EYE                = 7357,
    BOSS_RAGGLESNOUT                      = 7354,
    BOSS_AMNENNAR_THE_COLDBRINGER         = 7358,
    BOSS_GLUTTON                          = 8567,
    BOSS_PLAGUEMAW_THE_ROTTING            = 7356,

    /* Tuten Kash adds */
    NPC_TOMB_FIEND                        = 7349,
    NPC_TOMB_REAVER                       = 7351,
};

enum GameObjects
{
    GAMEOBJECT_GONG                       = 148917,
};

#endif
