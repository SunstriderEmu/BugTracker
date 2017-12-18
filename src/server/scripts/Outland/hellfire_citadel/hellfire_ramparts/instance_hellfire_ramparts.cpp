
#include "ScriptMgr.h"
#include "GameObject.h"
#include "hellfire_ramparts.h"
#include "InstanceScript.h"
#include "Map.h"

class instance_ramparts : public InstanceMapScript
{
    public:
        instance_ramparts() : InstanceMapScript(HRScriptName, 543) { }

        struct instance_ramparts_InstanceMapScript : public InstanceScript
        {
            instance_ramparts_InstanceMapScript(Map* map) : InstanceScript(map)
            {
                SetHeaders(DataHeader);
                SetBossNumber(EncounterCount);
            }

            void OnGameObjectCreate(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_FEL_IRON_CHEST_NORMAL:
                    case GO_FEL_IRON_CHEST_HEROIC:
                        felIronChestGUID = go->GetGUID();
                        break;
                }
            }

            bool SetBossState(uint32 type, EncounterState state) override
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                    case DATA_VAZRUDEN:
                    case DATA_NAZAN:
                        if (GetBossState(DATA_VAZRUDEN) == DONE && GetBossState(DATA_NAZAN) == DONE)
                            if (GameObject* chest = instance->GetGameObject(felIronChestGUID))
                                chest->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                        break;
                    default:
                        break;
                }
                return true;
            }

        protected:
            ObjectGuid felIronChestGUID;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const override
        {
            return new instance_ramparts_InstanceMapScript(map);
        }
};

void AddSC_instance_ramparts()
{
    new instance_ramparts;
}
