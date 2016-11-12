/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Instance_Mechanar
SD%Complete: 100
SDComment:
SDCategory: Mechanar
EndScriptData */


#include "def_mechanar.h"

#define ENCOUNTERS      5

#define MOARGDOOR1      184632
#define MOARGDOOR2      184322

class instance_mechanar : public InstanceMapScript
{
public:
    instance_mechanar() : InstanceMapScript("instance_mechanar", 554) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_mechanar_script(map);
    }

    struct instance_mechanar_script : public InstanceScript
    {
        instance_mechanar_script(Map *map) : InstanceScript(map) { Initialize(); };

        uint32 Encounters[ENCOUNTERS];

        uint64 MoargDoor1;
        uint64 MoargDoor2;

        void OnGameObjectCreate(GameObject* go) override
        {
            switch (go->GetEntry())
            {
            case MOARGDOOR1:
                MoargDoor1 = go->GetGUID();
                if (Encounters[0] == DONE)
                    HandleGameObject(0, true, go);
                break;
            case MOARGDOOR2:
                MoargDoor2 = go->GetGUID();
                if (Encounters[1] == DONE)
                    HandleGameObject(0, true, go);
                break;
            }
        }

        void Initialize()
            override {
            MoargDoor1 = 0;
            MoargDoor2 = 0;

            for (uint32 & Encounter : Encounters)
                Encounter = NOT_STARTED;
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 Encounter : Encounters)
                if (Encounter == IN_PROGRESS)
                    return true;

            return false;
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type) {
            case DATA_GATEWATCHER_GYROKILL:     return Encounters[0];
            case DATA_GATEWATCHER_IRONHAND:     return Encounters[1];
            case DATA_MECHLORD_CAPACITUS:       return Encounters[2];
            case DATA_NETHERMANCER:             return Encounters[3];
            case DATA_PATHALEON:                return Encounters[4];
            }

            return false;
        }

        uint64 GetData64(uint32 identifier) const override
        {
            switch (identifier) {
            case DATA_MOARGDOOR1_GUID:          return MoargDoor1;
            case DATA_MOARGDOOR2_GUID:          return MoargDoor2;
            default:                            return 0;
            }
        }

        void SetData(uint32 type, uint32 data)
            override {
            switch (type)
            {
            case DATA_GATEWATCHER_GYROKILL:     // This one is handled by ACID
                Encounters[0] = data;
                if (data == DONE)
                    HandleGameObject(MoargDoor1, true);
                break;
            case DATA_GATEWATCHER_IRONHAND:
                Encounters[1] = data;
                if (data == DONE)
                    HandleGameObject(MoargDoor2, true);
                break;
            case DATA_MECHLORD_CAPACITUS:       Encounters[2] = data;   break;
            case DATA_NETHERMANCER:             Encounters[3] = data;   break;
            case DATA_PATHALEON:                Encounters[4] = data;   break;
            case DATA_NETHERCHARGE:             AllPlayersCombatStop(); return;
            }

            if (data == DONE)
                SaveToDB();
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream stream;
            stream << Encounters[0] << " " << Encounters[1] << " " << Encounters[2] << " " << Encounters[3] << " " << Encounters[4];

            OUT_SAVE_INST_DATA_COMPLETE;
            return stream.str();
        }

        void Load(const char* in) override
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);
            std::istringstream stream(in);
            stream >> Encounters[0] >> Encounters[1] >> Encounters[2] >> Encounters[3] >> Encounters[4];

            for (uint32 & Encounter : Encounters)
                if (Encounter == IN_PROGRESS)                // Do not load an encounter as "In Progress" - reset it instead.
                    Encounter = NOT_STARTED;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void AllPlayersCombatStop() {
            Map::PlayerList const& players = instance->GetPlayers();
            if (!players.isEmpty())
            {
                for (const auto & player : players)
                {
                    if (Player* plr = player.GetSource())
                        plr->CombatStop();
                }
            }
        }
    };
};

void AddSC_instance_mechanar()
{
    new instance_mechanar();
}

