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
SDName: Instance_Shadow_Labyrinth
SD%Complete: 85
SDComment: Some cleanup left along with save
SDCategory: Auchindoun, Shadow Labyrinth
EndScriptData */


#include "def_shadow_labyrinth.h"

#define ENCOUNTERS 5

#define REFECTORY_DOOR          183296                      //door opened when blackheart the inciter dies
#define SCREAMING_HALL_DOOR     183295                      //door opened when grandmaster vorpil dies

/* Shadow Labyrinth encounters:
1 - Ambassador Hellmaw event
2 - Blackheart the Inciter event
3 - Grandmaster Vorpil event
4 - Murmur event
*/

class instance_shadow_labyrinth : public InstanceMapScript
{
public:
    instance_shadow_labyrinth() : InstanceMapScript("instance_shadow_labyrinth", 555) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_shadow_labyrinth_script(map);
    }

    struct instance_shadow_labyrinth_script : public InstanceScript
    {
        instance_shadow_labyrinth_script(Map *map) : InstanceScript(map) { Initialize(); };

        uint32 Encounter[ENCOUNTERS];
        std::string str_data;

        uint64 RefectoryDoorGUID;
        uint64 ScreamingHallDoorGUID;

        uint64 GrandmasterVorpil;
        uint32 FelOverseerCount;

        void Initialize() override
        {
            RefectoryDoorGUID = 0;
            ScreamingHallDoorGUID = 0;

            GrandmasterVorpil = 0;
            FelOverseerCount = 0;

            for (uint32 & i : Encounter)
                i = NOT_STARTED;
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 i : Encounter)
                if (i == IN_PROGRESS) return true;

            return false;
        }

        void OnGameObjectCreate(GameObject *go) override
        {
            switch (go->GetEntry())
            {
            case REFECTORY_DOOR: RefectoryDoorGUID = go->GetGUID(); break;
            case SCREAMING_HALL_DOOR: ScreamingHallDoorGUID = go->GetGUID(); break;
            }
        }

        void OnCreatureCreate(Creature *creature) override
        {
            switch (creature->GetEntry())
            {
            case 18732:
                GrandmasterVorpil = creature->GetGUID();
                break;
            case 18796:
                ++FelOverseerCount;
                break;
            }
        }

        void HandleGameObject(uint64 guid, uint32 state)
        {
            Player *player = GetPlayer();

            if (!player || !guid)
            {
                TC_LOG_ERROR("scripts", "Shadow Labyrinth: HandleGameObject fail");
                return;
            }

            if (GameObject *go = GameObject::GetGameObject(*player, guid))
                go->SetGoState(GOState(state));
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case TYPE_HELLMAW:
                Encounter[0] = data;
                break;

            case TYPE_OVERSEER:
                if (data != DONE)
                    error_log("TSCR: Shadow Labyrinth: TYPE_OVERSEER did not expect other data than DONE");
                if (FelOverseerCount)
                {
                    --FelOverseerCount;
                }
                if (FelOverseerCount == 0)
                {
                    Encounter[1] = DONE;
                }
                break;

            case DATA_BLACKHEARTTHEINCITEREVENT:
                if (data == DONE)
                {
                    HandleGameObject(RefectoryDoorGUID, 0);
                }
                Encounter[2] = data;
                break;

            case DATA_GRANDMASTERVORPILEVENT:
                if (data == DONE)
                {
                    HandleGameObject(ScreamingHallDoorGUID, 0);
                }
                Encounter[3] = data;
                break;

            case DATA_MURMUREVENT:
                Encounter[4] = data;
                break;
            }

            if (data == DONE)
            {
                if (type == TYPE_OVERSEER && FelOverseerCount != 0)
                    return;

                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << Encounter[0] << " " << Encounter[1] << " "
                    << Encounter[2] << " " << Encounter[3] << " " << Encounter[4];

                str_data = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case TYPE_HELLMAW: return Encounter[0];
            case TYPE_OVERSEER: return Encounter[1];
            case DATA_GRANDMASTERVORPILEVENT: return Encounter[3];
            case DATA_MURMUREVENT: return Encounter[4];
            }
            return false;
        }

        uint64 GetData64(uint32 identifier) const override
        {
            if (identifier == DATA_GRANDMASTERVORPIL)
                return GrandmasterVorpil;

            return 0;
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            return str_data;
            OUT_SAVE_INST_DATA_COMPLETE;
        }

        void Load(const char* in) override
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            std::istringstream loadStream(in);
            loadStream >> Encounter[0] >> Encounter[1] >> Encounter[2] >> Encounter[3] >> Encounter[4];

            for (uint32 & i : Encounter)
                if (i == IN_PROGRESS)
                    i = NOT_STARTED;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_shadow_labyrinth()
{
    new instance_shadow_labyrinth();
}

