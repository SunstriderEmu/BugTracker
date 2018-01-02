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
SDName: Instance_ZulFarrak
SD%Complete: 80
SDComment: does most of the pyramid event handling
SDCategory: Zul'Farrak
EndScriptData */


#include "def_zulfarrak.h"

int const pyramidSpawnTotal = 54;
/* list of wave spawns: 0 = wave ID, 1 = creature id, 2 = x, 3 = y 
    no z coordinat b/c they're all the same */
float pyramidSpawns [pyramidSpawnTotal][4] = {
    {1,7789,1894.64f,1206.29f},
    {1,7787,1890.08f,1218.68f},
    {1,8876,1883.76f,1222.30f},
    {1,7789,1874.18f,1221.24f},
    {1,7787,1892.28f,1225.49f},
    {1,7788,1889.94f,1212.21f},
    {1,7787,1879.02f,1223.06f},
    {1,7789,1874.45f,1204.44f},
    {1,8876,1898.23f,1217.97f},
    {1,7787,1882.07f,1225.70f},
    {1,8877,1896.46f,1205.62f},
    {1,7787,1886.97f,1225.86f},
    {1,7787,1894.72f,1221.91f},
    {1,7787,1883.50f,1218.25f},
    {1,7787,1886.93f,1221.40f},
    {1,8876,1889.82f,1222.51f},
    {1,7788,1893.07f,1215.26f},
    {1,7788,1878.57f,1214.16f},
    {1,7788,1883.74f,1212.35f},
    {1,8877,1877.0f,1207.27f},
    {1,8877,1873.63f,1204.65f},
    {1,8876,1877.4f,1216.41f},
    {1,8877,1899.63f,1202.52f},
    {2,7789,1902.83f,1223.41f},
    {2,8876,1889.82f,1222.51f},
    {2,7787,1883.5f,1218.25f},
    {2,7788,1883.74f,1212.35f},
    {2,8877,1877.00f,1207.27f},
    {2,7787,1890.08f,1218.68f},
    {2,7789,1894.64f,1206.29f},
    {2,8876,1877.40f,1216.41f},
    {2,7787,1892.28f,1225.49f},
    {2,7788,1893.07f,1215.26f},
    {2,8877,1896.46f,1205.62f},
    {2,7789,1874.45f,1204.44f},
    {2,7789,1874.18f,1221.24f},
    {2,7787,1879.02f,1223.06f},
    {2,8876,1898.23f,1217.97f},
    {2,7787,1882.07f,1225.70f},
    {2,8877,1873.63f,1204.65f},
    {2,7787,1886.97f,1225.86f},
    {2,7788,1878.57f,1214.16f},
    {2,7787,1894.72f,1221.91f},
    {2,7787,1886.93f,1221.40f},
    {2,8876,1883.76f,1222.30f},
    {2,7788,1889.94f,1212.21f},
    {2,8877,1899.63f,1202.52f},
    {3,7788,1878.57f,1214.16f},
    {3,7787,1894.72f,1221.91f},
    {3,7787,1886.93f,1221.40f},
    {3,8876,1883.76f,1222.30f},
    {3,7788,1889.94f,1212.21f},
    {3,7275,1889.23f,1207.72f},
    {3,7796,1879.77f,1207.96f}
};

struct ZFPosition
{
    float x, y, z, orientation;
};

class instance_zulfarrak : public InstanceMapScript
{
public:
    instance_zulfarrak() : InstanceMapScript("instance_zulfarrak", 209) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_zulfarrak_script(map);
    }

    struct instance_zulfarrak_script : public InstanceScript
    {
        instance_zulfarrak_script(Map* pMap) : InstanceScript(pMap) { Initialize(); };

        ObjectGuid ZumrahGUID;
        ObjectGuid BlyGUID, WeegliGUID, OroGUID, RavenGUID, MurtaGUID;
        ObjectGuid EndDoorGUID;
        uint32 PyramidPhase;

        void Initialize()
            override {
            SetData(EVENT_PYRAMID, PYRAMID_NOT_STARTED);
        }

        void OnCreatureCreate(Creature* pCreature)
            override {
            switch (pCreature->GetEntry())
            {
            case ENTRY_ZUMRAH: ZumrahGUID = pCreature->GetGUID(); break;
            case ENTRY_BLY:
                BlyGUID = pCreature->GetGUID();
                pCreature->SetReactState(REACT_PASSIVE); // starts out passive (in a cage)
                break;
            case ENTRY_RAVEN:
                RavenGUID = pCreature->GetGUID();
                pCreature->SetReactState(REACT_PASSIVE);// starts out passive (in a cage)
                break;
            case ENTRY_ORO:
                OroGUID = pCreature->GetGUID();
                pCreature->SetReactState(REACT_PASSIVE);// starts out passive (in a cage)
                break;
            case ENTRY_WEEGLI:
                WeegliGUID = pCreature->GetGUID();
                pCreature->SetReactState(REACT_PASSIVE);// starts out passive (in a cage)
                break;
            case ENTRY_MURTA:
                MurtaGUID = pCreature->GetGUID();
                pCreature->SetReactState(REACT_PASSIVE);// starts out passive (in a cage)
                break;
            }
        }

        void OnGameObjectCreate(GameObject* pGo)
            override {
            switch (pGo->GetEntry())
            {
            case GO_END_DOOR:
                EndDoorGUID = pGo->GetGUID();
                break;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case EVENT_PYRAMID:
                return PyramidPhase;
            }
            return 0;
        }

        uint64 GetData64(uint32 data) const override
        {
            switch (data)
            {
            case ENTRY_ZUMRAH:
                return ZumrahGUID;
            case ENTRY_BLY:
                return BlyGUID;
            case ENTRY_RAVEN:
                return RavenGUID;
            case ENTRY_ORO:
                return OroGUID;
            case ENTRY_WEEGLI:
                return WeegliGUID;
            case ENTRY_MURTA:
                return MurtaGUID;
            case GO_END_DOOR:
                return EndDoorGUID;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data)
            override {
            switch (type)
            {
            case EVENT_PYRAMID:
                PyramidPhase = data;
                break;
            }
        }

        uint32 major_wave_Timer, minor_wave_Timer;
        uint32 addGroupSize;

        void Update(uint32 diff)
            override {
            switch (PyramidPhase)
            {
            case PYRAMID_NOT_STARTED:
            case PYRAMID_KILLED_ALL_TROLLS:
                break;
            case PYRAMID_ARRIVED_AT_STAIR:
                SpawnPyramidWave(1);
                SetData(EVENT_PYRAMID, PYRAMID_WAVE_1);
                major_wave_Timer = 120000;
                minor_wave_Timer = 0;
                addGroupSize = 2;
                break;
            case PYRAMID_WAVE_1:
                if (IsWaveAllDead()) {
                    SetData(EVENT_PYRAMID, PYRAMID_PRE_WAVE_2);
                    major_wave_Timer = 10000;               // Give players a few seconds before wave 2 starts to rebuff
                }
                else if (minor_wave_Timer < diff) {
                    SendAddsUpStairs(addGroupSize++);
                    minor_wave_Timer = 10000;
                }
                else minor_wave_Timer -= diff;
                break;
            case PYRAMID_PRE_WAVE_2:
                if (major_wave_Timer < diff) {
                    // beginning 2nd wave!
                    SpawnPyramidWave(2);
                    SetData(EVENT_PYRAMID, PYRAMID_WAVE_2);
                    minor_wave_Timer = 0;
                    addGroupSize = 2;
                }
                else major_wave_Timer -= diff;
                break;
            case PYRAMID_WAVE_2:
                if (IsWaveAllDead()) {
                    SpawnPyramidWave(3);
                    SetData(EVENT_PYRAMID, PYRAMID_PRE_WAVE_3);
                    major_wave_Timer = 5000;                // Give NPCs time to return to their home spots
                }
                else if (minor_wave_Timer < diff) {
                    SendAddsUpStairs(addGroupSize++);
                    minor_wave_Timer = 10000;
                }
                else minor_wave_Timer -= diff;
                break;
            case PYRAMID_PRE_WAVE_3:
                if (major_wave_Timer < diff) {
                    // move NPCs to bottom of stair
                    MoveNPCIfAlive(ENTRY_BLY, 1887.92, 1228.179, 9.98, 4.78);
                    MoveNPCIfAlive(ENTRY_MURTA, 1891.57, 1228.68, 9.69, 4.78);
                    MoveNPCIfAlive(ENTRY_ORO, 1897.23, 1228.34, 9.43, 4.78);
                    MoveNPCIfAlive(ENTRY_RAVEN, 1883.68, 1227.95, 9.543, 4.78);
                    MoveNPCIfAlive(ENTRY_WEEGLI, 1878.02, 1227.65, 9.485, 4.78);
                    SetData(EVENT_PYRAMID, PYRAMID_WAVE_3);
                }
                else major_wave_Timer -= diff;
                break;
            case PYRAMID_WAVE_3:
                if (IsWaveAllDead()) {                  // Move NPCS to their final positions
                    SetData(EVENT_PYRAMID, PYRAMID_KILLED_ALL_TROLLS);
                    MoveNPCIfAlive(ENTRY_BLY, 1883.82, 1200.83, 8.87, 1.32);
                    MoveNPCIfAlive(ENTRY_MURTA, 1891.83, 1201.45, 8.87, 1.32);
                    MoveNPCIfAlive(ENTRY_ORO, 1894.50, 1204.40, 8.87, 1.32);
                    MoveNPCIfAlive(ENTRY_RAVEN, 1874.11, 1206.17, 8.87, 1.32);
                    MoveNPCIfAlive(ENTRY_WEEGLI, 1877.52, 1199.63, 8.87, 1.32);
                }
                break;
            }
        }

        std::list<ObjectGuid> addsAtBase, movedadds;

        void MoveNPCIfAlive(uint32 entry, float x, float y, float z, float o) 
        {
            if (Creature* npc = instance->GetCreature(ObjectGuid(GetData64(entry)))) {
                if (npc->IsAlive()) {
                    npc->ClearUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                    npc->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    npc->GetMotionMaster()->MovePoint(1, x, y, z);
                    npc->SetHomePosition(x, y, z, o);
                }
            }
        }

        void SpawnPyramidWave(uint32 wave)
        {
            for (auto & pyramidSpawn : pyramidSpawns) {
                if (pyramidSpawn[0] == (float)wave) {
                    ZFPosition pos = { pyramidSpawn[2], pyramidSpawn[3], 8.87f, 0 };
                    if (Player* plr = GetPlayer()) {
                        Creature* ts = plr->SummonCreature(pyramidSpawn[1], pos.x, pos.y, pos.z, pos.orientation, TEMPSUMMON_DEAD_DESPAWN, 600000);
                        ts->GetMotionMaster()->MoveRandom(10);
                        addsAtBase.push_back(ts->GetGUID());
                    }
                }
            }
        }

        bool IsWaveAllDead()
        {
            for (ObjectGuid & itr : addsAtBase) {
                if (Creature* add = instance->GetCreature(itr)) {
                    if (add->IsAlive())
                        return false;
                }
            }
            for (ObjectGuid & movedadd : movedadds) {
                if (Creature* add = instance->GetCreature((movedadd))) {
                    if (add->IsAlive())
                        return false;
                }
            }
            return true;
        }

        void SendAddsUpStairs(uint32 count) {
            //pop a add from list, send him up the stairs...
            for (uint32 addCount = 0; addCount < count && !addsAtBase.empty(); addCount++) {
                Creature* add = instance->GetCreature(*addsAtBase.begin());
                if (add) {
                    /*add->GetMotionMaster()->MovePoint(1,1887.786865, 1228.898560, 10.198944);
                    add->GetMotionMaster()->MovePoint(2,1887.199341, 1231.333862, 11.570065);
                    add->GetMotionMaster()->MovePoint(3,1887.309570, 1243.335449, 22.842709);
                    add->GetMotionMaster()->MovePoint(4,1887.265259, 1252.211182, 31.544107);*/
                    add->GetMotionMaster()->MovePoint(1, 1887.163208, 1261.078857, 40.592354);
                    movedadds.push_back(add->GetGUID());
                }
                addsAtBase.erase(addsAtBase.begin());
            }
        }
    };
};

void AddSC_instance_zulfarrak()
{
    new instance_zulfarrak();
}
