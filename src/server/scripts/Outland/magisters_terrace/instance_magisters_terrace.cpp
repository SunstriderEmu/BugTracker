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
SDName: Instance_Magisters_Terrace
SD%Complete: 60
SDComment:  Designed only for Selin Fireheart
SDCategory: Magister's Terrace
EndScriptData */


#include "def_magisters_terrace.h"

#define NUMBER_OF_ENCOUNTERS      4

/*
0  - Selin Fireheart
1  - Vexallus
2  - Priestess Delrissa
3  - Kael'thas Sunstrider
*/

class instance_magisters_terrace : public InstanceMapScript
{
public:
    instance_magisters_terrace() : InstanceMapScript("instance_magisters_terrace", 585) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_magisters_terrace_script(map);
    }

    struct instance_magisters_terrace_script : public InstanceScript
    {
        instance_magisters_terrace_script(Map* map) : InstanceScript(map) { Initialize(); }

        bool hasDelrissaSummoned;

        uint32 DoorState[3];//0seline, 1vexallus, 2derlissa
        uint32 Encounters[NUMBER_OF_ENCOUNTERS];
        uint32 DelrissaDeathCount;

        std::list<uint64> FelCrystals;
        std::list<uint64>::iterator CrystalItr;

        uint64 KaelGUID;
        uint64 SelinGUID;
        uint64 DelrissaGUID;
        uint64 VexallusDoorGUID;
        uint64 SelinDoorGUID;
        uint64 SelinEncounterDoorGUID;
        uint64 DelrissaDoorGUID;
        uint64 KaelStatue[2];

        bool InitializedItr;

        void Initialize()
            override {
            for (uint32 & i : DoorState)
                i = 1;//1 closed, 0 opened

            for (uint32 & Encounter : Encounters)
                Encounter = NOT_STARTED;

            FelCrystals.clear();

            hasDelrissaSummoned = false;

            DelrissaDeathCount = 0;

            KaelGUID = 0;
            SelinGUID = 0;
            DelrissaGUID = 0;
            VexallusDoorGUID = 0;
            SelinDoorGUID = 0;
            SelinEncounterDoorGUID = 0;
            DelrissaDoorGUID = 0;
            KaelStatue[0] = 0;
            KaelStatue[1] = 0;

            InitializedItr = false;
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 Encounter : Encounters)
                if (Encounter == IN_PROGRESS)
                    return true;
            return false;
        }

        uint32 GetData(uint32 identifier) const override
        {
            switch (identifier)
            {
            case DATA_SELIN_EVENT:          return Encounters[0];
            case DATA_VEXALLUS_EVENT:       return Encounters[1];
            case DATA_DELRISSA_EVENT:       return Encounters[2];
            case DATA_KAELTHAS_EVENT:       return Encounters[3];
            case DATA_DELRISSA_DEATH_COUNT: return DelrissaDeathCount;
            case DATA_FEL_CRYSTAL_SIZE:     return FelCrystals.size();
            case HAS_DELRISSA_SUMMONED:     return (hasDelrissaSummoned ? 1 : 0);
            }
            return 0;
        }

        void SetData(uint32 identifier, uint32 data) override
        {
            switch (identifier)
            {
            case DATA_SELIN_EVENT:
                Encounters[0] = data;
                if (data == DONE)
                {
                    DoorState[0] = 0;
                    SaveToDB();
                }
                break;
            case DATA_VEXALLUS_EVENT:
                Encounters[1] = data;
                if (data == DONE)
                {
                    DoorState[1] = 0;
                    SaveToDB();
                }
                break;
            case DATA_DELRISSA_EVENT:
                Encounters[2] = data;
                if (data == DONE)
                {
                    DoorState[2] = 0;
                    SaveToDB();
                }
                break;
            case DATA_KAELTHAS_EVENT:    Encounters[3] = data;  break;

            case DATA_DELRISSA_DEATH_COUNT:
                if (data)  ++DelrissaDeathCount;
                else      DelrissaDeathCount = 0;
            case HAS_DELRISSA_SUMMONED:
                hasDelrissaSummoned = true;
            }
        }

        std::string GetSaveData() override
        {
            std::ostringstream ss;
            ss << "S " << DoorState[0] << " " << DoorState[1] << " " << DoorState[2];
            char* data = new char[ss.str().length() + 1];
            strcpy(data, ss.str().c_str());
            return data;
        }

        void Load(const char* load) override
        {
            if (!load) return;
            std::istringstream ss(load);
            char dataHead; // S
            uint32 data1, data2, data3;
            ss >> dataHead >> data1 >> data2 >> data3;
            if (dataHead == 'S')
            {
                DoorState[0] = data1;
                DoorState[1] = data2;
                DoorState[2] = data3;
            }
            else error_log("TSCR: Magister's Terrace: corrupted save data.");
        }

        void OnCreatureCreate(Creature *creature) override
        {
            switch (creature->GetEntry())
            {
            case 24723: SelinGUID = creature->GetGUID(); break;
            case 24560: DelrissaGUID = creature->GetGUID(); break;
            case 24722: FelCrystals.push_back(creature->GetGUID()); break;
            case 24664: KaelGUID = creature->GetGUID(); break;
            }
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            switch (go->GetEntry())
            {
            case 187896:
                VexallusDoorGUID = go->GetGUID();
                go->SetGoState(GOState(DoorState[1]));
                break;
                //SunwellRaid Gate 02
            case 187979:
                SelinDoorGUID = go->GetGUID();
                go->SetGoState(GOState(DoorState[0]));
                break;
                //Assembly Chamber Door
            case 188065:  SelinEncounterDoorGUID = go->GetGUID(); break;
            case 187770:
                DelrissaDoorGUID = go->GetGUID();
                go->SetGoState(GOState(DoorState[2]));
                break;
            case 188165:  KaelStatue[0] = go->GetGUID();          break;
            case 188166:  KaelStatue[1] = go->GetGUID();          break;
            }
        }

        void InitCristalItr()
        {
            if (!InitializedItr)
            {
                CrystalItr = FelCrystals.begin();
                InitializedItr = true;
            }
        }

        void SelectNextCristal()
        {
            ++CrystalItr;
        }

        uint64 GetData64(uint32 identifier) const override
        {
            switch (identifier)
            {
            case DATA_SELIN:                return SelinGUID;
            case DATA_KAEL:                 return KaelGUID;
            case DATA_DELRISSA:             return DelrissaGUID;
            case DATA_VEXALLUS_DOOR:        return VexallusDoorGUID;
            case DATA_SELIN_DOOR:           return SelinDoorGUID;
            case DATA_SELIN_ENCOUNTER_DOOR: return SelinEncounterDoorGUID;
            case DATA_DELRISSA_DOOR:        return DelrissaDoorGUID;
            case DATA_KAEL_STATUE_LEFT:     return KaelStatue[0];
            case DATA_KAEL_STATUE_RIGHT:    return KaelStatue[1];

            case DATA_FEL_CRYSTAL:
            {
                if (FelCrystals.empty())
                {
                    error_log("TSCR: Magisters Terrace: No Fel Crystals loaded in Inst Data");
                    return 0;
                }

                const_cast<instance_magisters_terrace_script*>(this)->InitCristalItr();

                uint64 guid = 0;
                if (CrystalItr != FelCrystals.end())
                {
                    guid = *CrystalItr;
                    const_cast<instance_magisters_terrace_script*>(this)->SelectNextCristal();
                }
                return guid;
            }
            }
            return 0;
        }
    };
};

void AddSC_instance_magisters_terrace()
{
    new instance_magisters_terrace();
}

