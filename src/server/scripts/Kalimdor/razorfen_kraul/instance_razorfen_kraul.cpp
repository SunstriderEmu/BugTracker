/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Instance_Razorfen_Kraul
SD%Complete:
SDComment:
SDCategory: Razorfen Kraul
EndScriptData */


#include "def_razorfen_kraul.h"


#define WARD_KEEPERS_NR 2

class instance_razorfen_kraul : public InstanceMapScript
{
public:
    instance_razorfen_kraul() : InstanceMapScript("instance_razorfen_kraul", 47) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_razorfen_kraul_script(map);

    }

    struct instance_razorfen_kraul_script : public InstanceScript
    {
        instance_razorfen_kraul_script(Map *map) : InstanceScript(map) { Initialize(); };

        uint64 DoorWardGUID;
        int WardKeeperAlive;

        void Initialize()
            override {
            WardKeeperAlive = 0;
            DoorWardGUID = 0;
        }

        void OnGameObjectCreate(GameObject *go)
            override {
            switch (go->GetEntry())
            {
            case 21099:
                DoorWardGUID = go->GetGUID();
                break;
            }
        }

        void OnCreatureCreate(Creature* creature)
            override {
            switch (creature->GetEntry())
            {
            case 4625:
                WardKeeperAlive++;
                break;
            }
        }

        void SetData(uint32 type, uint32 data)
            override {
            switch (type)
            {
            case TYPE_WARD_KEEPERS:
                if (data == NOT_STARTED)
                {
                    if (WardKeeperAlive > 0)
                    {
                        WardKeeperAlive--;
                        if (WardKeeperAlive == 0)
                        {
                            if (GameObject *door = instance->GetGameObject(DoorWardGUID))
                                door->SwitchDoorOrButton(true);
                        }
                    }
                }
                break;
            }
        }
    };
};

void AddSC_instance_razorfen_kraul()
{
    new instance_razorfen_kraul();
}
