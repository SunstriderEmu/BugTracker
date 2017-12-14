
/* ScriptData
SDName: Instance_Karazhan
SD%Complete: 70
SDComment: Instance OLDScript for Karazhan to help in various encounters. TODO: GameObject visibility for Opera event.
SDCategory: Karazhan
EndScriptData */


#include "karazhan.h"
#include "AreaBoundary.h"

/*
0  - Attumen + Midnight (optional)
1  - Moroes
2  - Maiden of Virtue (optional)
3  - Hyakiss the Lurker /  Rokad the Ravager  / Shadikith the Glider
4  - Opera Event
5  - Curator
6  - Shade of Aran (optional)
7  - Terestian Illhoof (optional)
8  - Netherspite (optional)
9  - Chess Event
10 - Prince Malchezzar
11 - Nightbane
*/

BossBoundaryData const boundaries =
{
    { DATA_ATTUMEN_EVENT,           new CircleBoundary(Position(-11126.0f, -1929.0f), 55.0f) },
    { DATA_MAIDENOFVIRTUE_EVENT,    new CircleBoundary(Position(-10945.0f, -2103.0f), 50.0f) },
    { DATA_MOROES_EVENT,            new RectangleBoundary(-11030.0f, -10935.0f, -1980.0f, -1850.0f ) },
    { DATA_OPERA_EVENT,             new CircleBoundary(Position(-10894.0f, -1775.0f), 50.0f) },
    { DATA_CURATOR_EVENT,           new CircleBoundary(Position(-11135.0f, -1882.0f), 125.0f) },
    { DATA_TERESTIAN_EVENT,         new CircleBoundary(Position(-11229.0f, -1696.0f), 40.0f) },
    { DATA_SHADEOFARAN_EVENT,       new CircleBoundary(Position(-11164.0f, -1911.0f), 50.0f) },
    { DATA_NETHERSPITE_EVENT,       new CircleBoundary(Position(-11144.0f, -1632.0f), 100.0f) },
    { DATA_NIGHTBANE_EVENT,         new CircleBoundary(Position(-11134.0f, -1909.0f), 200.0f) },
    { DATA_MALCHEZZAR_EVENT,        new CircleBoundary(Position(-10953.0f, -1992.0f), 70.0f) },
};

DoorData const doorData[] =
{
    { GO_PRIVATE_LIBRARY_DOOR,                DATA_SHADEOFARAN_EVENT,     DOOR_TYPE_ROOM },
    { GO_MASTERS_TERRACE_DOOR,                DATA_NIGHTBANE_EVENT,       DOOR_TYPE_ROOM },
    { GO_MASTERS_TERRACE_DOOR2,               DATA_NIGHTBANE_EVENT,       DOOR_TYPE_ROOM },
    { GO_NETHERSPACE_DOOR,                    DATA_MALCHEZZAR_EVENT,      DOOR_TYPE_ROOM },
    { GO_MASSIVE_DOOR,                        DATA_NETHERSPITE_EVENT,     DOOR_TYPE_ROOM },
    { GO_SIDE_ENTRANCE_DOOR,                  DATA_OPERA_EVENT,           DOOR_TYPE_PASSAGE },
    { GO_GAMESMAN_HALL_EXIT_DOOR,             DATA_CHESS_EVENT,           DOOR_TYPE_PASSAGE },
    { 0,                                      0,                          DOOR_TYPE_ROOM }  // END
};

class instance_karazhan : public InstanceMapScript
{
public:
    instance_karazhan() : InstanceMapScript(KZScriptName, 532) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_karazhan_script(map);
    }

    struct instance_karazhan_script : public InstanceScript
    {
        instance_karazhan_script(Map* map) : InstanceScript(map) 
        { 
            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);
            LoadDoorData(doorData);
            LoadBossBoundaries(boundaries);

            Initialize(); 
        }

        void Initialize()
            override 
        {
            OperaEvent = urand(1, 3);                   // 1 - OZ, 2 - HOOD, 3 - RAJ, this never gets altered (expect when loading from DB)
            OzDeathCount = 0;

            CurtainGUID = 0;
            StageDoorLeftGUID = 0;
            StageDoorRightGUID = 0;

            KilrekGUID = 0;
            TerestianGUID = 0;
            MoroesGUID = 0;
            MalchezaarGUID = 0;

            LibraryDoor = 0;
            MassiveDoor = 0;
            GamesmansDoor = 0;
            GamesmansExitDoor = 0;
            NetherspaceDoor = 0;
            SideEntranceDoor = 0;
            MastersTerraceDoor[0] = 0;
            MastersTerraceDoor[1] = 0;
            ChessMedivhGUID = 0;
            ChessTeam = 0;

            ChessPieces.resize(0);
            MedivhCheatFires.resize(0);
            ChessGamePhase = NOTSTARTED;
        }

        void OnCreatureCreate(Creature *creature) override
        {
            InstanceScript::OnCreatureCreate(creature);
            switch (creature->GetEntry())
            {
            case NPC_KILREK:            KilrekGUID = creature->GetGUID();      break;
            case NPC_TERESTIAN_ILLHOOF: TerestianGUID = creature->GetGUID();   break;
            case NPC_MOROES:            MoroesGUID = creature->GetGUID();      break;
            case NPC_MEDIVH:            ChessMedivhGUID = creature->GetGUID();       break;
            case NPC_MALCHEZAAR:        MalchezaarGUID = creature->GetGUID();  break;
            case NPC_PAWN_H:
            case NPC_KNIGHT_H:
            case NPC_QUEEN_H:
            case NPC_BISHOP_H:
            case NPC_ROOK_H:
            case NPC_KING_H:
            case NPC_PAWN_A:
            case NPC_KNIGHT_A:
            case NPC_QUEEN_A:
            case NPC_BISHOP_A:
            case NPC_ROOK_A:
            case NPC_KING_A:
                ChessPieces.push_back(creature->GetGUID());
                creature->SetHealth(creature->GetMaxHealth());
                break;
            case 22521:
                MedivhCheatFires.push_back(creature->GetGUID());
                break;
            }
        }

        uint32 GetData(uint32 identifier) const override
        {
            switch (identifier)
            {
            case DATA_OPERA_PERFORMANCE:      return OperaEvent;
            case DATA_OPERA_OZ_DEATHCOUNT:    return OzDeathCount;
            case CHESS_EVENT_TEAM:            return ChessTeam;
            case DATA_CHESS_GAME_PHASE:       return ChessGamePhase;
            }

            return 0;
        }

        void OnPlayerEnter(Player* player) override
        {
            if (GetBossState(DATA_CHESS_EVENT) != IN_PROGRESS)
                player->RemoveAurasDueToSpell(39331);

            player->RemoveAurasDueToSpell(30019);
        }

        ObjectGuid GetGuidData(uint32 data) const override
        {
            switch (data)
            {
            case DATA_KILREK:                      return KilrekGUID;
            case DATA_TERESTIAN:                   return TerestianGUID;
            case DATA_MOROES:                      return MoroesGUID;
            case DATA_GAMEOBJECT_STAGEDOORLEFT:    return StageDoorLeftGUID;
            case DATA_GAMEOBJECT_STAGEDOORRIGHT:   return StageDoorRightGUID;
            case DATA_GAMEOBJECT_CURTAINS:         return CurtainGUID;
            case DATA_GAMEOBJECT_LIBRARY_DOOR:     return LibraryDoor;
            case DATA_GAMEOBJECT_MASSIVE_DOOR:     return MassiveDoor;
            case DATA_GAMEOBJECT_GAME_DOOR:        return GamesmansDoor;
            case DATA_GAMEOBJECT_GAME_EXIT_DOOR:   return GamesmansExitDoor;
            case DATA_GAMEOBJECT_NETHER_DOOR:      return NetherspaceDoor;
            case DATA_MASTERS_TERRACE_DOOR_1:      return MastersTerraceDoor[0];
            case DATA_MASTERS_TERRACE_DOOR_2:      return MastersTerraceDoor[1];
            case DATA_CHESS_ECHO_OF_MEDIVH:        return ChessMedivhGUID;
            case DATA_IMAGE_OF_MEDIVH:             return NightbaneMedivhGUID;
            case DATA_MALCHEZAAR:                  return MalchezaarGUID;
            }

            return 0;
        }

        void ReinitChestPieces()
        {
            for (uint64 ChessPiece : ChessPieces)
            {
                if (Creature* piece = instance->GetCreature(ChessPiece))
                {
                    piece->CombatStop();
                    piece->SetDeathState(JUST_RESPAWNED);
                    piece->SetHealth(piece->GetMaxHealth());
                    piece->AI()->SetData(0, 0);
                    float x, y, z, o;
                    piece->GetHomePosition(x, y, z, o);
                    piece->Relocate(x, y, z, o);
                    piece->SendMovementFlagUpdate();
                    piece->AI()->SetData(1, 0); // Reset default orientation
                    piece->RemoveAurasDueToSpell(39339);
                    piece->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
            }
            for (uint64 MedivhCheatFire : MedivhCheatFires) {
                if (Creature* fire = instance->GetCreature(MedivhCheatFire))
                    fire->DisappearAndDie();
            }
            MedivhCheatFires.resize(0);
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
                case DATA_OPERA_OZ_DEATHCOUNT:     ++OzDeathCount;        break;
                case CHESS_EVENT_TEAM:             ChessTeam = data;      break;
                case DATA_CHESS_GAME_PHASE:        ChessGamePhase = data; break;
                case DATA_CHESS_REINIT_PIECES:     ReinitChestPieces();   break;
            }
        }

        bool SetBossState(uint32 type, EncounterState state) override
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
            case DATA_OPERA_EVENT:
            {
                GameObject* sideDoor = instance->GetGameObject(SideEntranceDoor);
                if (state == DONE)
                {
                    if (sideDoor)
                        sideDoor->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);

                    //HandleGameObject(SideEntranceDoor, true);
                    HandleGameObject(StageDoorLeftGUID, true); // DATA_GAMEOBJECT_STAGEDOORLEFT
                    HandleGameObject(StageDoorRightGUID, true); // DATA_GAMEOBJECT_STAGEDOORRIGHT
                }
                else if (state == FAIL || state == NOT_STARTED)
                {
                    if (sideDoor)
                        sideDoor->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);

                    //HandleGameObject(SideEntranceDoor, false);
                    HandleGameObject(StageDoorLeftGUID, false); // DATA_GAMEOBJECT_STAGEDOORLEFT
                    HandleGameObject(StageDoorRightGUID, false); // DATA_GAMEOBJECT_STAGEDOORRIGHT
                }
                break;
            }
            case DATA_CHESS_EVENT:
                if (state == FAIL || state == DONE || state == NOT_STARTED)
                    DoRemoveAurasDueToSpellOnPlayers(39331);
                /*else if (data == IN_PROGRESS || data == SPECIAL)
                CastOnAllPlayers(39331);*/
                break;
            case DATA_CHESS_CHECK_PIECES_ALIVE:
                for (uint64 ChessPiece : ChessPieces) {
                    if (Creature* piece = instance->GetCreature(ChessPiece)) {
                        if (!piece->IsAlive()) {
                            piece->SetDeathState(JUST_RESPAWNED);
                            piece->SetHealth(piece->GetMaxHealth());
                        }
                    }
                }
                break;
            }
            return true;
        }

        void SetGuidData(uint32 identifier, ObjectGuid data) override
        {
            switch (identifier)
            {
                case DATA_CHESS_ECHO_OF_MEDIVH:      ChessMedivhGUID = data;     break;
                case DATA_IMAGE_OF_MEDIVH:           NightbaneMedivhGUID = data; break;
            }
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            InstanceScript::OnGameObjectCreate(go);
            switch (go->GetEntry())
            {
            case GO_STAGE_CURTAIN:
                CurtainGUID = go->GetGUID();         
                break;
            case GO_STAGE_DOOR_LEFT:
                StageDoorLeftGUID = go->GetGUID();
                if (GetBossState(DATA_OPERA_EVENT) == DONE)
                    HandleGameObject(StageDoorLeftGUID, true);  
                break;
            case GO_STAGE_DOOR_RIGHT:
                StageDoorRightGUID = go->GetGUID();
                if (GetBossState(DATA_OPERA_EVENT) == DONE)
                    HandleGameObject(StageDoorRightGUID, true);
                break;
            case GO_PRIVATE_LIBRARY_DOOR:
                LibraryDoor = go->GetGUID();        
                break;
            case GO_MASSIVE_DOOR:
                MassiveDoor = go->GetGUID();        
                break;
            case GO_GAMESMAN_HALL_DOOR:
                GamesmansDoor = go->GetGUID();         
                break;
            case GO_GAMESMAN_HALL_EXIT_DOOR:
                GamesmansExitDoor = go->GetGUID();         
                break;
            case GO_NETHERSPACE_DOOR:
                NetherspaceDoor = go->GetGUID();         
                break;
            case GO_MASTERS_TERRACE_DOOR:
                MastersTerraceDoor[0] = go->GetGUID();         
                break;
            case GO_MASTERS_TERRACE_DOOR2:
                MastersTerraceDoor[1] = go->GetGUID();         
                break;
            case GO_SIDE_ENTRANCE_DOOR:
                SideEntranceDoor = go->GetGUID();
                if (DATA_OPERA_EVENT < DONE)
                {
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                    HandleGameObject(SideEntranceDoor, true);
                }
                break;
            }

            switch (OperaEvent)
            {
                //TODO: Set Object visibilities for Opera based on performance
                case EVENT_OZ:
                    break;

                case EVENT_HOOD:
                    break;

                case EVENT_RAJ:
                    break;
            }
        }


        void WriteSaveDataMore(std::ostringstream& data) override
        {
            data << OperaEvent;
        }

        void ReadSaveDataMore(std::istringstream& data) override
        {
            data >> OperaEvent;
        }

        private:
            uint32 OperaEvent;
            uint32 OzDeathCount;
            uint32 ChessTeam;

            uint64 CurtainGUID;
            uint64 StageDoorLeftGUID;
            uint64 StageDoorRightGUID;
            uint64 KilrekGUID;
            uint64 TerestianGUID;
            uint64 MoroesGUID;
            uint64 MalchezaarGUID;
            uint64 LibraryDoor;                                     // Door at Shade of Aran
            uint64 MassiveDoor;                                     // Door at Netherspite
            uint64 GamesmansDoor;                                   // Door before Chess
            uint64 GamesmansExitDoor;                               // Door after Chess
            uint64 NetherspaceDoor;                                // Door at Malchezaar
            uint64 SideEntranceDoor;                                // Inside top entrance door
            uint64 MastersTerraceDoor[2];
            uint64 NightbaneMedivhGUID;
            uint64 ChessMedivhGUID;

            uint32 ChessGamePhase;

            std::vector<uint64> ChessPieces;
            std::vector<uint64> MedivhCheatFires;
    };
};

void AddSC_instance_karazhan()
{
    new instance_karazhan();
}

