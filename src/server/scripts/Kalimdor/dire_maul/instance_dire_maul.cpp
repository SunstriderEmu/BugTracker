/* Copyright (C) 2009 - 2010 WoWMania Core
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
SDName: Instance_Dire_Maul
SD%Complete: 0
SDComment: 
SDCategory: Dire_Maul
EndScriptData */


#include "def_dire_maul.h"
#include "GameEventMgr.h"

#define ENCOUNTERS 1

/* Dire Maul
    0 - Zevrin Thornhoof
*/

class instance_dire_maul : public InstanceMapScript
{
public:
    instance_dire_maul() : InstanceMapScript("instance_dire_maul", 429) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_dire_maul_script(map);
    }

    struct instance_dire_maul_script : public InstanceScript
    {
        instance_dire_maul_script(Map *pMap) : InstanceScript(pMap) { Initialize(); };

        uint32 Encounters[ENCOUNTERS];

        uint64 pusillinGUID;
        uint64 ironbarkGUID;
        uint64 ironbarkDoorGUID;

        void Initialize()
            override {
            pusillinGUID = 0;
            ironbarkGUID = 0;
            ironbarkDoorGUID = 0;
        }

        bool isEventActive()
        {
            const GameEventMgr::ActiveEvents& activeEvents = sGameEventMgr->GetActiveEventList();
            bool active = activeEvents.find(57) != activeEvents.end();

            return active;
        }

        bool IsEncounterInProgress() const
            override {
            for (uint32 Encounter : Encounters)
                if (Encounter == IN_PROGRESS)
                    return true;

            return false;
        }

        void OnCreatureCreate(Creature* creature) override
        {
            switch (creature->GetEntry()) {
            case 14354: pusillinGUID = creature->GetGUID(); break;
            case 11491: ironbarkGUID = creature->GetGUID(); break;
            case 11486:
                if (isEventActive())
                    creature->SetDisplayId(15734);

                break;
            }
        }

        void OnGameObjectCreate(GameObject *pGo) override
        {
            switch (pGo->GetEntry()) {
            case 179549: ironbarkDoorGUID = pGo->GetGUID(); break;
            }
        }

        uint64 GetData64(uint32 id) const override
        {
            switch (id) {
            case DATA_GUID_PUSILLIN:
                return pusillinGUID;
            case DATA_GUID_IRONBARKDOOR:
                return ironbarkDoorGUID;
            default:
                return 0;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type) {
            case DATA_ZEVRIM_THORNHOOF:
                return Encounters[0];
            default:
                return 0;
            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type) {
            case DATA_ZEVRIM_THORNHOOF:
                Encounters[0] = data;
                if (data == DONE) {
                    if (Creature *pIronbark = instance->GetCreature(ironbarkGUID))
                        pIronbark->UpdateEntry(14241);
                }
                break;
            }
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream stream;
            stream << Encounters[0] /*<< " "  << Encounters[1] << " "  << Encounters[2] << " "  << Encounters[3] << " "
                << Encounters[4] << " "  << Encounters[5]*/;

            OUT_SAVE_INST_DATA_COMPLETE
                return stream.str();
        }

        void Load(const char* in) override
        {
            if (!in) {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);
            std::istringstream stream(in);
            stream >> Encounters[0] /*>> Encounters[1] >> Encounters[2] >> Encounters[3]
                >> Encounters[4] >> Encounters[5]*/;
            for (uint32 & Encounter : Encounters)
                if (Encounter == IN_PROGRESS)                // Do not load an encounter as "In Progress" - reset it instead.
                    Encounter = NOT_STARTED;
            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_dire_maul()
{
    new instance_dire_maul();
}
