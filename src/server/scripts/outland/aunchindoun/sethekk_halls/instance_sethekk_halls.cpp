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

class instance_sethekk_halls : public InstanceMapScript
{
public:
    instance_sethekk_halls() : InstanceMapScript("instance_sethekk_halls", 556) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_sethekk_halls_script(map);
    }

    struct instance_sethekk_halls_script : public InstanceScript
    {
        instance_sethekk_halls_script(Map *map) : InstanceScript(map) { Initialize(); };

        GameObject *IkissDoor;

        uint64 summonerGUID;

        void Initialize()
            override {
            IkissDoor = nullptr;
            summonerGUID = 0;
        }

        void OnGameObjectCreate(GameObject *go)
            override {
            switch (go->GetEntry())
            {
            case IKISS_DOOR:
                IkissDoor = go;
                break;
            }
        }

        void SetData(uint32 type, uint32 data)
            override {
            switch (type)
            {
            case DATA_IKISSDOOREVENT:
                if (IkissDoor)
                    IkissDoor->SetGoState(GO_STATE_ACTIVE);
                break;
            }
        }

        void SetData64(uint32 identifier, uint64 data)
            override {
            switch (identifier)
            {
            case ANZU_SUMMONER:
                summonerGUID = data;
                break;
            }
        }

        uint64 GetData64(uint32 identifier) const override
        {
            switch (identifier)
            {
            case ANZU_SUMMONER:
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

