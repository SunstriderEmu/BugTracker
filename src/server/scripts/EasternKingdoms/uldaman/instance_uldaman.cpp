
/* ScriptData
SDName: instance_uldaman
SD%Complete: 99%
SDComment: Need some cosmetics updates when archeadas door are closing (Guardians Waypoints).
SDCategory: Uldaman
EndScriptData */


#include "def_uldaman.h"

#define SPELL_ARCHAEDAS_AWAKEN        10347
#define SPELL_AWAKEN_VAULT_WALKER     10258

#define ARCHAEDAS_TEMPLE_DOOR           141869
#define ALTAR_OF_ARCHAEDAS              133234

#define ALTAR_OF_THE_KEEPER_TEMPLE_DOOR 124367
#define ALTAR_OF_THE_KEEPER_TEMPLE      130511

#define ANCIENT_VAULT_DOOR              124369
#define IRONAYA_SEAL_DOOR               124372

#define KEYSTONE_GO                     124371

#define ENCOUNTERS 3

class instance_uldaman : public InstanceMapScript
{
public:
    instance_uldaman() : InstanceMapScript("instance_uldaman", 70) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_uldaman_script(map);
    }

    struct instance_uldaman_script : public InstanceScript
    {
        instance_uldaman_script(Map *map) : InstanceScript(map) {};

        void Initialize() override
        {
            ironayaSealDoorTimer = 26000;
            keystoneCheck = false;

            for (uint32 & Encounter : Encounters)
                Encounter = NOT_STARTED;
        }

        ObjectGuid archaedasGUID;
        ObjectGuid ironayaGUID;
        ObjectGuid whoWokeArchaedasGUID;

        ObjectGuid altarOfTheKeeperTempleDoor;
        ObjectGuid archaedasTempleDoor;
        ObjectGuid ancientVaultDoor;
        ObjectGuid ironayaSealDoor;

        ObjectGuid keystoneGUID;

        uint32 ironayaSealDoorTimer;
        bool keystoneCheck;

        std::vector<ObjectGuid> stoneKeeper;
        std::vector<ObjectGuid> altarOfTheKeeperCount;
        std::vector<ObjectGuid> vaultWalker;
        std::vector<ObjectGuid> earthenGuardian;
        std::vector<ObjectGuid> archaedasWallMinions;    // minions lined up around the wall

        uint32 Encounters[ENCOUNTERS];
        std::string str_data;

        void OnGameObjectCreate(GameObject* go) override
        {
            switch (go->GetEntry())
            {
            case ALTAR_OF_THE_KEEPER_TEMPLE_DOOR:         // lock the door
                altarOfTheKeeperTempleDoor = go->GetGUID();

                if (Encounters[0] == DONE)
                    HandleGameObject(ObjectGuid::Empty, true, go);
                break;

            case ARCHAEDAS_TEMPLE_DOOR:
                archaedasTempleDoor = go->GetGUID();

                if (Encounters[0] == DONE)
                    HandleGameObject(ObjectGuid::Empty, true, go);
                break;

            case ANCIENT_VAULT_DOOR:
                go->ResetDoorOrButton();
                go->SetUInt32Value(GAMEOBJECT_FLAGS, GO_FLAG_NODESPAWN | GO_FLAG_IN_USE);
                ancientVaultDoor = go->GetGUID();

                if (Encounters[1] == DONE)
                    HandleGameObject(ObjectGuid::Empty, true, go);
                break;

            case IRONAYA_SEAL_DOOR:
                ironayaSealDoor = go->GetGUID();

                if (Encounters[2] == DONE)
                    HandleGameObject(ObjectGuid::Empty, true, go);
                break;

            case KEYSTONE_GO:
                keystoneGUID = go->GetGUID();

                if (Encounters[2] == DONE)
                {
                    HandleGameObject(ObjectGuid::Empty, true, go);
                    go->SetUInt32Value(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                }
                break;
            }
        }

        void SetFrozenState(Creature *creature)
        {
            creature->SetFaction(FACTION_FRIENDLY);
            creature->RemoveAllAuras();
            //creature->RemoveFlag (UNIT_FIELD_FLAGS,UNIT_FLAG_ANIMATION_FROZEN);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_REMOVE_CLIENT_CONTROL);
        }

        void SetDoor(ObjectGuid guid, bool open)
        {
            GameObject *go = instance->GetGameObject(guid);
            if (!go)
                return;

            HandleGameObject(ObjectGuid::Empty, open, go);
        }

        void BlockGO(ObjectGuid guid)
        {
            GameObject *go = instance->GetGameObject(guid);
            if (!go)
                return;
            go->SetUInt32Value(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);

        }

        void ActivateStoneKeepers()
        {
            for (ObjectGuid & i : stoneKeeper)
            {
                Creature *target = instance->GetCreature(i);
                if (!target || !target->IsAlive() || target->GetFaction() == 14)
                    continue;
                target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_REMOVE_CLIENT_CONTROL);
                target->SetFaction(FACTION_MONSTER);
                target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                return;        // only want the first one we find
            }
            // if we get this far than all four are dead so open the door
            SetData(DATA_ALTAR_DOORS, DONE);
            SetDoor(archaedasTempleDoor, true); //open next the door too
        }

        void ActivateWallMinions()
        {
            Creature *archaedas = instance->GetCreature(archaedasGUID);
            if (!archaedas)
                return;

            for (ObjectGuid & archaedasWallMinion : archaedasWallMinions)
            {
                Creature *target = instance->GetCreature(archaedasWallMinion);
                if (!target || !target->IsAlive() || target->GetFaction() == 14)
                    continue;
                archaedas->CastSpell(target, SPELL_AWAKEN_VAULT_WALKER, TRIGGERED_FULL_MASK);
                target->CastSpell(target, SPELL_ARCHAEDAS_AWAKEN, TRIGGERED_FULL_MASK);
                return;        // only want the first one we find
            }
        }

        // used when Archaedas dies.  All active minions must be despawned.
        void DeActivateMinions()
        {
            // first despawn any aggroed wall minions
            for (ObjectGuid & archaedasWallMinion : archaedasWallMinions)
            {
                Creature *target = instance->GetCreature(archaedasWallMinion);
                if (!target || target->IsDead() || target->GetFaction() != 14)
                    continue;
                target->DespawnOrUnsummon();
            }

            // Vault Walkers
            for (ObjectGuid & i : vaultWalker)
            {
                Creature *target = instance->GetCreature(i);
                if (!target || target->IsDead() || target->GetFaction() != 14)
                    continue;
                target->DespawnOrUnsummon();
            }

            // Earthen Guardians
            for (ObjectGuid & i : earthenGuardian)
            {
                Creature *target = instance->GetCreature(i);
                if (!target || target->IsDead() || target->GetFaction() != 14)
                    continue;
                target->DespawnOrUnsummon();
            }
        }

        void ActivateArchaedas(ObjectGuid target)
        {
            Creature *archaedas = instance->GetCreature(archaedasGUID);
            if (!archaedas)
                return;

            if (Unit *victim = ObjectAccessor::GetUnit(*archaedas, target))
            {
                archaedas->CastSpell(archaedas, SPELL_ARCHAEDAS_AWAKEN, TRIGGERED_NONE);
                whoWokeArchaedasGUID = target;
            }
        }

        void ActivateIronaya()
        {
            Creature *ironaya = instance->GetCreature(ironayaGUID);
            if (!ironaya)
                return;

            ironaya->SetFaction(415);
            ironaya->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_REMOVE_CLIENT_CONTROL);
            ironaya->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void RespawnMinions()
        {
            // first respawn any aggroed wall minions
            for (ObjectGuid & archaedasWallMinion : archaedasWallMinions)
            {
                Creature *target = instance->GetCreature(archaedasWallMinion);
                if (target && target->IsDead())
                {
                    target->Respawn();
                    target->GetMotionMaster()->MoveTargetedHome();
                    SetFrozenState(target);
                }
            }

            // Vault Walkers
            for (ObjectGuid & i : vaultWalker)
            {
                Creature *target = instance->GetCreature(i);
                if (target && target->IsDead())
                {
                    target->Respawn();
                    target->GetMotionMaster()->MoveTargetedHome();
                    SetFrozenState(target);
                }
            }

            // Earthen Guardians
            for (ObjectGuid & i : earthenGuardian)
            {
                Creature *target = instance->GetCreature(i);
                if (target && target->IsDead())
                {
                    target->Respawn();
                    target->GetMotionMaster()->MoveTargetedHome();
                    SetFrozenState(target);
                }
            }
        }

        void Update(uint32 diff) override
        {
            if (!keystoneCheck)
                return;

            if (ironayaSealDoorTimer <= diff)
            {
                ActivateIronaya();

                SetDoor(ironayaSealDoor, true);
                BlockGO(keystoneGUID);

                SetData(DATA_IRONAYA_DOOR, DONE); //save state
                keystoneCheck = false;
            }
            else
                ironayaSealDoorTimer -= diff;
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case DATA_ALTAR_DOORS:
                Encounters[0] = data;
                if (data == DONE)
                    SetDoor(altarOfTheKeeperTempleDoor, true);
                break;

            case DATA_ANCIENT_DOOR:
                Encounters[1] = data;
                if (data == DONE) //archeadas defeat
                {
                    SetDoor(archaedasTempleDoor, true); //re open enter door
                    SetDoor(ancientVaultDoor, true);
                }
                break;

            case DATA_IRONAYA_DOOR:
                Encounters[2] = data;
                break;

            case DATA_STONE_KEEPERS:
                ActivateStoneKeepers();
                break;

            case DATA_MINIONS:
                switch (data)
                {
                case NOT_STARTED:
                    if (Encounters[0] == DONE) //if players opened the doors 
                        SetDoor(archaedasTempleDoor, true);

                    RespawnMinions();
                    break;
                case IN_PROGRESS:
                    ActivateWallMinions();
                    break;
                case SPECIAL:
                    DeActivateMinions();
                    break;
                }
                break;

            case DATA_IRONAYA_SEAL:
                keystoneCheck = true;
                break;
            }

            if (data == DONE)
            {

                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << Encounters[0] << " " << Encounters[1] << " " << Encounters[2];

                str_data = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;

            }
        }

        void SetData64(uint32 type, uint64 data) override
        {
            // Archaedas
            if (type == 0)
            {
                ActivateArchaedas(ObjectGuid(data));
                SetDoor(archaedasTempleDoor, false); //close when event is started
            }
        }


        void OnCreatureCreate(Creature *creature) override
        {
            switch (creature->GetEntry()) {
            case 4857:    // Stone Keeper
                SetFrozenState(creature);
                stoneKeeper.push_back(creature->GetGUID());
                break;

            case 7309:    // Earthen Custodian
                archaedasWallMinions.push_back(creature->GetGUID());
                break;

            case 7077:    // Earthen Hallshaper
                archaedasWallMinions.push_back(creature->GetGUID());
                break;

            case 7076:    // Earthen Guardian
                earthenGuardian.push_back(creature->GetGUID());
                break;

            case 7228:   // Ironaya
                ironayaGUID = creature->GetGUID();

                if (Encounters[2] != DONE)
                    SetFrozenState(creature);
                break;

            case 10120:    // Vault Walker
                vaultWalker.push_back(creature->GetGUID());
                break;

            case 2748:    // Archaedas
                archaedasGUID = creature->GetGUID();
                break;

            } // end switch
        } // end OnCreatureCreate


        uint64 GetData64(uint32 identifier) const override
        {
            if (identifier == 0) return whoWokeArchaedasGUID;
            if (identifier == 1) return vaultWalker[0];    // VaultWalker1
            if (identifier == 2) return vaultWalker[1];    // VaultWalker2
            if (identifier == 3) return vaultWalker[2];    // VaultWalker3
            if (identifier == 4) return vaultWalker[3];    // VaultWalker4

            if (identifier == 5) return earthenGuardian[0];
            if (identifier == 6) return earthenGuardian[1];
            if (identifier == 7) return earthenGuardian[2];
            if (identifier == 8) return earthenGuardian[3];
            if (identifier == 9) return earthenGuardian[4];
            if (identifier == 10) return earthenGuardian[5];

            return 0;
        } // end GetData64

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
            loadStream >> Encounters[0] >> Encounters[1] >> Encounters[2];

            for (uint32 & Encounter : Encounters)
                if (Encounter == IN_PROGRESS)
                    Encounter = NOT_STARTED;

            OUT_LOAD_INST_DATA_COMPLETE;

        }

    };
};

void AddSC_instance_uldaman()
{
    new instance_uldaman();
}

