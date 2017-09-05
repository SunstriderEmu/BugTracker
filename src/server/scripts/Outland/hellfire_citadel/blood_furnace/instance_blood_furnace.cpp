/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Instance_Blood_Furnace
SD%Complete: 85
SDComment:
SDCategory: Hellfire Citadel, Blood Furnace
EndScriptData */


#include "def_blood_furnace.h"

#define ENTRY_SEWER1                 181823
#define ENTRY_SEWER2                 181766
#define ENTRY_MAKER2                 181812
#define ENTRY_MAKER1                 181811
#define ENTRY_BROG1                  181822
#define ENTRY_BROG2                  181819

#define ENTRY_CELL_LEVER             181982
#define ENTRY_CELL_DOOR1             181817
#define ENTRY_CELL_DOOR2             181818
#define ENTRY_CELL_DOOR3             181820
#define ENTRY_CELL_DOOR4             181821

#define  MAX_ORC_WAVES               4
#define  MAX_BROGGOK_WAVES           5

#define NPC_BROGGOK                  17380
#define NPC_NASCENT_FEL_ORC          17398
#define NPC_FEL_ORC_NEOPHYTE         17429

#define SAY_BROGGOK_INTRO            -1542015

#define ENCOUNTERS                   3

class instance_blood_furnace : public InstanceMapScript
{
public:
    instance_blood_furnace() : InstanceMapScript("instance_blood_furnace", 542) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_blood_furnace_script(map);
    }

    struct instance_blood_furnace_script : public InstanceScript
    {
        instance_blood_furnace_script(Map *map) : InstanceScript(map) { Initialize(); };

        struct BroggokEventInfo
        {
            BroggokEventInfo() : IsCellOpened(false), KilledOrcCount(0) {}

            uint64 CellGuid;
            bool IsCellOpened;
            uint8 KilledOrcCount;
            std::set<uint64> SortedOrcGuids;
        };

        uint32 Encounter[ENCOUNTERS];
        BroggokEventInfo BroggokEvent[MAX_ORC_WAVES];
        std::vector<uint64> NascentOrcGuids;
        uint32 BroggokEventTimer;
        uint32 BroggokEventPhase;
        uint32 DoorTimer;
        uint64 BroggokGUID;
        uint64 Sewer1GUID;
        uint64 Sewer2GUID;
        uint64 Maker1GUID;
        uint64 Maker2GUID;
        uint64 Brog1GUID;
        uint64 Brog2GUID;
        uint64 LeverGUID;
        bool OrcsFlagFixed;

        void Initialize()
            override {
            Sewer1GUID = 0;
            Sewer2GUID = 0;
            Maker1GUID = 0;
            Maker2GUID = 0;
            Brog1GUID = 0;
            Brog2GUID = 0;
            LeverGUID = 0;
            DoorTimer = 0;
            BroggokEventTimer = 0;
            BroggokEventPhase = 0;
            OrcsFlagFixed = false;

            for (uint32 & i : Encounter) {
                if (i != DONE)
                    i = NOT_STARTED;
            }
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 i : Encounter)
                if (i == IN_PROGRESS) return true;

            return false;
        }

        void OnCreatureCreate(Creature* pCreature) override
        {
            switch (pCreature->GetEntry())
            {
            case NPC_BROGGOK: BroggokGUID = pCreature->GetGUID(); break;
            case NPC_NASCENT_FEL_ORC:
            case NPC_FEL_ORC_NEOPHYTE:
                NascentOrcGuids.push_back(pCreature->GetGUID()); break;
            }
        }

        void OnGameObjectCreate(GameObject* pGo) override
        {
            switch (pGo->GetEntry())
            {
            case ENTRY_SEWER1:
                Sewer1GUID = pGo->GetGUID();
                if (Encounter[2] == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            case ENTRY_SEWER2:
                Sewer2GUID = pGo->GetGUID();
                if (Encounter[2] == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            case ENTRY_MAKER1: Maker1GUID = pGo->GetGUID(); break;
            case ENTRY_MAKER2:
                Maker2GUID = pGo->GetGUID();
                if (Encounter[0] == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            case ENTRY_BROG1: Brog1GUID = pGo->GetGUID(); break;
            case ENTRY_BROG2:
                Brog2GUID = pGo->GetGUID();
                if (Encounter[1] == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            case ENTRY_CELL_LEVER: LeverGUID = pGo->GetGUID(); break;
            case ENTRY_CELL_DOOR1: BroggokEvent[0].CellGuid = pGo->GetGUID(); return;
            case ENTRY_CELL_DOOR2: BroggokEvent[1].CellGuid = pGo->GetGUID(); return;
            case ENTRY_CELL_DOOR3: BroggokEvent[2].CellGuid = pGo->GetGUID(); return;
            case ENTRY_CELL_DOOR4: BroggokEvent[3].CellGuid = pGo->GetGUID(); return;
            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case DATA_MAKEREVENT:
                if (data == IN_PROGRESS)
                {
                    HandleGameObject(Maker1GUID, false);
                }
                else HandleGameObject(Maker1GUID, true);
                if (data == DONE)
                {
                    HandleGameObject(Maker2GUID, true);
                    DoFixNascentOrcsFlags();
                }
                //if (Encounter[0] != DONE)
                Encounter[0] = data;
                break;
            case DATA_BROGGOKEVENT:
                if (data == IN_PROGRESS)
                {
                    if (Creature* pBroggok = instance->GetCreature(BroggokGUID))
                        DoScriptText(SAY_BROGGOK_INTRO, pBroggok);

                    HandleGameObject(Brog1GUID, false);

                    if (BroggokEventPhase <= MAX_ORC_WAVES)
                    {
                        DoSortBroggokOrcs();
                        DoNextBroggokEventPhase();
                    }
                }
                else
                {
                    HandleGameObject(Brog1GUID, true);
                }
                if (data == FAIL)
                {
                    if (BroggokEventPhase <= MAX_BROGGOK_WAVES)
                    {
                        for (auto & i : BroggokEvent)
                        {
                            if (!i.IsCellOpened)
                                continue;

                            i.KilledOrcCount = 0;
                            for (auto itr = i.SortedOrcGuids.begin(); itr != i.SortedOrcGuids.end(); ++itr)
                            {
                                if (Creature* pOrc = instance->GetCreature(*itr))
                                {
                                    if (!pOrc->IsAlive())
                                        pOrc->Respawn();
                                    BroggokEventPhase = 0;
                                }
                            }

                            DoUseDoorOrButton(i.CellGuid);
                            i.IsCellOpened = false;
                            if (GameObject *Lever = instance->GetGameObject(LeverGUID))
                            {
                                if (Lever)
                                    Lever->ResetDoorOrButton();
                            }
                        }
                    }

                    BroggokEventTimer = 0;
                }
                if (data == DONE)
                {
                    HandleGameObject(Brog2GUID, true);
                }
                //if (Encounter[1] != DONE)
                Encounter[1] = data;
                break;
            case DATA_KELIDANEVENT:
                if (data == DONE)
                {
                    HandleGameObject(Sewer1GUID, true);
                    HandleGameObject(Sewer2GUID, true);
                }
                //if (Encounter[2] != DONE)
                Encounter[2] = data;
                break;
            }

            if (data == DONE)
            {
                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case DATA_MAKEREVENT: return Encounter[0];
            case DATA_BROGGOKEVENT: return Encounter[1];
            case DATA_KELIDANEVENT: return Encounter[2];
            }
            return false;
        }

        uint64 GetData64(uint32 identifier) const override
        {
            return 0;
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream saveStream;

            saveStream << Encounter[0] << " " << Encounter[1] << " " << Encounter[2];

            OUT_SAVE_INST_DATA_COMPLETE
                return saveStream.str();
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
            loadStream >> Encounter[0] >> Encounter[1] >> Encounter[2];

            for (uint32 & i : Encounter)
                if (i == IN_PROGRESS)
                    i = NOT_STARTED;

            DoFixNascentOrcsFlags();

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void DoNextBroggokEventPhase()
        {
            float dx, dy;
            GetMovementDistanceForIndex(BroggokEventPhase, dx, dy);

            if (BroggokEventPhase >= MAX_ORC_WAVES)
            {
                DoUseDoorOrButton(Brog2GUID);

                if (Creature* pBroggok = instance->GetCreature(BroggokGUID))
                {
                    pBroggok->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    pBroggok->GetMotionMaster()->MovePoint(0, dx, dy, pBroggok->GetPositionZ());
                    DoorTimer = 5000;
                }
            }
            else
            {
                if (!BroggokEvent[BroggokEventPhase].IsCellOpened)
                    DoUseDoorOrButton(BroggokEvent[BroggokEventPhase].CellGuid);
                BroggokEvent[BroggokEventPhase].IsCellOpened = true;


                for (uint64 SortedOrcGuid : BroggokEvent[BroggokEventPhase].SortedOrcGuids)
                {
                    if (Creature* pOrc = instance->GetCreature(SortedOrcGuid))
                    {
                        pOrc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pOrc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        pOrc->GetMotionMaster()->MovePoint(0, pOrc->GetPositionX() + dx, pOrc->GetPositionY() + dy, pOrc->GetPositionZ());
                    }
                }
            }
            BroggokEventTimer = 80000;
            ++BroggokEventPhase;
        }

        void Update(uint32 diff) override
        {
            if (BroggokEventTimer && BroggokEventPhase < MAX_ORC_WAVES && instance->IsHeroic())
            {
                if (BroggokEventTimer <= diff)
                {
                    DoNextBroggokEventPhase();
                }
                else BroggokEventTimer -= diff;
            }

            if (DoorTimer)
            {
                if (DoorTimer <= diff)
                {
                    if (GameObject *Brog2 = instance->GetGameObject(Brog2GUID))
                    {
                        if (Brog2)
                            Brog2->ResetDoorOrButton();
                    }
                }
                else DoorTimer -= diff;
            }
        }

        void OnCreatureDeath(Creature* pCreature) override
        {
            DoFixNascentOrcsFlags();
            if (pCreature->GetEntry() == NPC_NASCENT_FEL_ORC || pCreature->GetEntry() == NPC_FEL_ORC_NEOPHYTE)
            {
                if (GetData(DATA_BROGGOKEVENT) != IN_PROGRESS)
                    return;

                uint8 uiClearedCells = 0;
                for (uint8 i = 0; i < std::min<uint32>(BroggokEventPhase, MAX_ORC_WAVES); ++i)
                {
                    if (BroggokEvent[i].SortedOrcGuids.size() == BroggokEvent[i].KilledOrcCount)
                    {
                        ++uiClearedCells;
                        continue;
                    }

                    if (BroggokEvent[i].SortedOrcGuids.find(pCreature->GetGUID()) != BroggokEvent[i].SortedOrcGuids.end())
                        BroggokEvent[i].KilledOrcCount++;

                    if (BroggokEvent[i].SortedOrcGuids.size() == BroggokEvent[i].KilledOrcCount)
                        ++uiClearedCells;
                }

                if (uiClearedCells == BroggokEventPhase)
                    DoNextBroggokEventPhase();
            }
        }

        void DoSortBroggokOrcs()
        {
            for (std::vector<uint64>::const_iterator itr = NascentOrcGuids.begin(); itr != NascentOrcGuids.end(); ++itr)
            {
                if (Creature* pOrc = instance->GetCreature(*itr))
                {
                    for (auto & i : BroggokEvent)
                    {
                        if (GameObject* pDoor = instance->GetGameObject(i.CellGuid))
                        {
                            if (pOrc->IsWithinDistInMap(pDoor, 8.0f))
                            {
                                i.SortedOrcGuids.insert(pOrc->GetGUID());
                                if (!pOrc->IsAlive())
                                    pOrc->Respawn();
                                break;
                            }
                        }
                    }
                }
            }
        }

        void DoFixNascentOrcsFlags()
        {
            for (std::vector<uint64>::const_iterator itr = NascentOrcGuids.begin(); itr != NascentOrcGuids.end(); ++itr)
            {
                if (Creature* pOrc = instance->GetCreature(*itr))
                {
                    bool updateFlag = true;
                    for (auto & i : BroggokEvent)
                    {
                        if (GameObject* pDoor = instance->GetGameObject(i.CellGuid))
                        {
                            if (pOrc->IsWithinDistInMap(pDoor, 8.0f))
                                updateFlag = false;
                        }
                    }

                    if (updateFlag) {
                        pOrc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pOrc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    }
                }
            }

            OrcsFlagFixed = true;
        }

        void GetMovementDistanceForIndex(uint32 uiIndex, float& dx, float& dy)
        {
            GameObject* pDoor[2];

            if (uiIndex < MAX_ORC_WAVES)
            {
                pDoor[0] = instance->GetGameObject(BroggokEvent[(uiIndex / 2) * 2].CellGuid);
                pDoor[1] = instance->GetGameObject(BroggokEvent[(uiIndex / 2) * 2 + 1].CellGuid);
            }
            else
            {
                pDoor[0] = instance->GetGameObject(BroggokEvent[0].CellGuid);
                pDoor[1] = instance->GetGameObject(BroggokEvent[3].CellGuid);
            }

            if (!pDoor[0] || !pDoor[1])
                return;

            if (uiIndex < MAX_ORC_WAVES)
            {
                dx = (pDoor[0]->GetPositionX() + pDoor[1]->GetPositionX()) / 2 - pDoor[uiIndex % 2]->GetPositionX();
                dy = (pDoor[0]->GetPositionY() + pDoor[1]->GetPositionY()) / 2 - pDoor[uiIndex % 2]->GetPositionY();
            }
            else
            {
                dx = (pDoor[0]->GetPositionX() + pDoor[1]->GetPositionX()) / 2;
                dy = (pDoor[0]->GetPositionY() + pDoor[1]->GetPositionY()) / 2;
            }
        }
    };
};

class PrisonCellLevel : public GameObjectScript
{
public:
    PrisonCellLevel() : GameObjectScript("go_prison_cell_lever")
    {}

    struct PrisonCellLevelAI : public GameObjectAI
    {
        PrisonCellLevelAI(GameObject* go) : GameObjectAI(go), instance(go->GetInstanceScript()) {}

        InstanceScript* instance;

        bool GossipHello(Player* /*player*/) override
        {
            if (!instance)
                return false;

            if (instance->GetData(DATA_BROGGOKEVENT) != DONE && instance->GetData(DATA_BROGGOKEVENT) != IN_PROGRESS)
            {
                instance->SetData(DATA_BROGGOKEVENT, IN_PROGRESS);
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new PrisonCellLevelAI(go);
    }
};

void AddSC_instance_blood_furnace()
{
    new instance_blood_furnace();
    new PrisonCellLevel();
}
