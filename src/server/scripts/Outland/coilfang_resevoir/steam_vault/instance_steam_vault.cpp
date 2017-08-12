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
SDName: Instance_Steam_Vault
SD%Complete: 80
SDComment:  Instance script and access panel GO
SDCategory: Coilfang Resevoir, The Steamvault
EndScriptData */


#include "def_steam_vault.h"

#define ENCOUNTERS 4

#define MAIN_CHAMBERS_DOOR      183049
#define ACCESS_PANEL_HYDRO      184125
#define ACCESS_PANEL_MEK        184126

/* Steam Vaults encounters:
1 - Hydromancer Thespia Event
2 - Mekgineer Steamrigger Event
3 - Warlord Kalithresh Event
*/

class MainChambersAccessPanel : public GameObjectScript
{
public:
    MainChambersAccessPanel() : GameObjectScript("go_main_chambers_access_panel")
    {}

    struct MainChambersAccessPanelAI : public GameObjectAI
    {
        MainChambersAccessPanelAI(GameObject* obj) : GameObjectAI(obj), pInstance(obj->GetInstanceScript()) { }

        InstanceScript* pInstance;

        bool GossipHello(Player* player) override
        {
            InstanceScript* pInstance = (InstanceScript*)me->GetInstanceScript();

            if (!pInstance)
                return false;

            if (me->GetEntry() == ACCESS_PANEL_HYDRO && (pInstance->GetData(TYPE_HYDROMANCER_THESPIA) == DONE || pInstance->GetData(TYPE_HYDROMANCER_THESPIA) == SPECIAL))
                pInstance->SetData(TYPE_HYDROMANCER_THESPIA, SPECIAL);

            if (me->GetEntry() == ACCESS_PANEL_MEK && (pInstance->GetData(TYPE_MEKGINEER_STEAMRIGGER) == DONE || pInstance->GetData(TYPE_MEKGINEER_STEAMRIGGER) == SPECIAL))
                pInstance->SetData(TYPE_MEKGINEER_STEAMRIGGER, SPECIAL);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new MainChambersAccessPanelAI(go);
    }
};

class instance_steam_vault : public InstanceMapScript
{
public:
    instance_steam_vault() : InstanceMapScript("instance_steam_vault", 545) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_steam_vault_script(map);
    }

    struct instance_steam_vault_script : public InstanceScript
    {
        instance_steam_vault_script(Map *map) : InstanceScript(map) { Initialize(); };

        uint32 Encounter[ENCOUNTERS];

        uint64 ThespiaGUID;
        uint64 MekgineerGUID;
        uint64 KalithreshGUID;

        uint64 MainChambersDoor;
        uint64 AccessPanelHydro;
        uint64 AccessPanelMek;

        void Initialize() override
        {
            ThespiaGUID = 0;
            MekgineerGUID = 0;
            KalithreshGUID = 0;
            MainChambersDoor = 0;
            AccessPanelHydro = 0;
            AccessPanelMek = 0;

            for (uint32 & i : Encounter)
                i = NOT_STARTED;
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 i : Encounter)
                if (i == IN_PROGRESS)
                    return true;

            return false;
        }

        void OnCreatureCreate(Creature *creature) override
        {
            switch (creature->GetEntry())
            {
            case 17797: ThespiaGUID = creature->GetGUID(); break;
            case 17796: MekgineerGUID = creature->GetGUID(); break;
            case 17798: KalithreshGUID = creature->GetGUID(); break;
            }
        }

        void OnGameObjectCreate(GameObject *go) override
        {
            switch (go->GetEntry())
            {
            case MAIN_CHAMBERS_DOOR: MainChambersDoor = go->GetGUID(); break;
            case ACCESS_PANEL_HYDRO: AccessPanelHydro = go->GetGUID(); break;
            case ACCESS_PANEL_MEK:   AccessPanelMek = go->GetGUID(); break;
            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            Player *player = GetPlayer();

            if (!player)
                return;

            switch (type)
            {
            case TYPE_HYDROMANCER_THESPIA:
                if (data == SPECIAL)
                {
                    if (GameObject *_go = GameObject::GetGameObject(*player, AccessPanelHydro))
                        _go->UseDoorOrButton();

                    if (GetData(TYPE_MEKGINEER_STEAMRIGGER) == SPECIAL)
                    {
                        if (GameObject *_go = GameObject::GetGameObject(*player, MainChambersDoor))
                            _go->UseDoorOrButton();
                    }
                }
                Encounter[0] = data;
                break;
            case TYPE_MEKGINEER_STEAMRIGGER:
                if (data == SPECIAL)
                {
                    if (GameObject *_go = GameObject::GetGameObject(*player, AccessPanelMek))
                        _go->UseDoorOrButton();

                    if (GetData(TYPE_HYDROMANCER_THESPIA) == SPECIAL)
                    {
                        if (GameObject *_go = GameObject::GetGameObject(*player, MainChambersDoor))
                            _go->UseDoorOrButton();
                    }
                }
                Encounter[1] = data;
                break;
            case TYPE_WARLORD_KALITHRESH:
                Encounter[2] = data;
                break;
            case TYPE_DISTILLER:
                Encounter[3] = data;
                break;
            }

            if (data == DONE || data == SPECIAL)
                SaveToDB();
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case TYPE_HYDROMANCER_THESPIA:
                return Encounter[0];
            case TYPE_MEKGINEER_STEAMRIGGER:
                return Encounter[1];
            case TYPE_WARLORD_KALITHRESH:
                return Encounter[2];
            case TYPE_DISTILLER:
                return Encounter[3];
            }
            return 0;
        }

        uint64 GetData64(uint32 data) const override
        {
            switch (data)
            {
            case DATA_THESPIA:
                return ThespiaGUID;
            case DATA_MEKGINEERSTEAMRIGGER:
                return MekgineerGUID;
            case DATA_KALITRESH:
                return KalithreshGUID;
            }
            return 0;
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream stream;
            stream << Encounter[0] << " " << Encounter[1] << " " << Encounter[2] << " " << Encounter[3];

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
            stream >> Encounter[0] >> Encounter[1] >> Encounter[2] >> Encounter[3];
            for (uint32 & i : Encounter)
                if (i == IN_PROGRESS)
                    i = NOT_STARTED;
            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_steam_vault()
{
    new instance_steam_vault();
    new MainChambersAccessPanel();
}

