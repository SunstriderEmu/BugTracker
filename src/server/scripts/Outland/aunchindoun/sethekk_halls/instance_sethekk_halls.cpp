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

/* ScriptData
SDName: Instance - Sethekk Halls
SD%Complete: 50
SDComment: Instance Data for Sethekk Halls instance
SDCategory: Auchindoun, Sethekk Halls
EndScriptData */


#include "def_sethekk_halls.h"

#define IKISS_DOOR          183398
#define GOBJECT_CAGE        183051

DoorData const doorData[] =
{
    { GO_IKISS_DOOR, DATA_TALON_KING_IKISS, DOOR_TYPE_PASSAGE },
    { 0,             0,                     DOOR_TYPE_ROOM } // END
};


class instance_sethekk_halls : public InstanceMapScript
{
public:
    instance_sethekk_halls() : InstanceMapScript(SHScriptName, 556) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_sethekk_halls_script(map);
    }

    struct instance_sethekk_halls_script : public InstanceScript
    {
        instance_sethekk_halls_script(Map *map) : InstanceScript(map) 
        {
            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);
            LoadDoorData(doorData);

            summonerGUID = 0;
        };

        void OnCreatureCreate(Creature* creature) override
        {
            if (creature->GetEntry() == NPC_ANZU)
            {
                if (GetBossState(DATA_ANZU) == DONE)
                    creature->DisappearAndDie();
                else
                    SetBossState(DATA_ANZU, IN_PROGRESS);
            }
        }

        uint64 summonerGUID;

        bool SetBossState(uint32 type, EncounterState state) override
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
            case DATA_TALON_KING_IKISS:
                if (state == DONE)
                {
                    //chest handling done in boss script
                }
            }
            return true;
        }

        void SetGuidData(uint32 identifier, ObjectGuid data)
            override {
            switch (identifier)
            {
            case ANZU_SUMMONER_GUID:
                summonerGUID = data;
                break;
            }
        }

        ObjectGuid GetGuidData(uint32 identifier) const override
        {
            switch (identifier)
            {
            case ANZU_SUMMONER_GUID:
                return summonerGUID;
            default:
                return 0;
            }
        }
    };
};

void AddSC_instance_sethekk_halls()
{
    new instance_sethekk_halls();
}

