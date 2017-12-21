
/* ScriptData
SDName: Instance_Arcatraz
SD%Complete: 80
SDComment: Mainly Harbringer Skyriss event
SDCategory: Tempest Keep, The Arcatraz
EndScriptData */


#include "arcatraz.h"


/* Arcatraz encounters:
1 - Zereketh the Unbound event
2 - Dalliah the Doomsayer event
3 - Wrath-Scryer Soccothrates event
4 - Harbinger Skyriss event, 5 sub-events
*/

DoorData const doorData[] =
{
    { GO_CONTAINMENT_CORE_SECURITY_FIELD_ALPHA, DATA_SOCCOTHRATES,  DOOR_TYPE_PASSAGE },
    { GO_CONTAINMENT_CORE_SECURITY_FIELD_BETA,  DATA_DALLIAH,       DOOR_TYPE_PASSAGE },
    { 0,                                        0,                  DOOR_TYPE_ROOM } // END
};

class instance_arcatraz : public InstanceMapScript
{
public:
    instance_arcatraz() : InstanceMapScript(ArcatrazScriptName, 552) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_arcatraz_script(map);
    }

    struct instance_arcatraz_script : public InstanceScript
    {
        instance_arcatraz_script(Map *map) : InstanceScript(map) 
        { 
            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);
            LoadDoorData(doorData);

            ConversationState = NOT_STARTED;

            memset(StasisPodStates, NOT_STARTED, 5 * sizeof(uint8));
        };


        ObjectGuid DalliahGUID;
        ObjectGuid SoccothratesGUID;
        ObjectGuid MellicharGUID;
        ObjectGuid MulhouseGUID;
        ObjectGuid GoSphereGUID;
        ObjectGuid WardensShieldGUID;

        ObjectGuid StasisPodGUIDs[5];
        uint8 StasisPodStates[5];

        uint8 ConversationState;

        void OnGameObjectCreate(GameObject *go) override
        {
            InstanceScript::OnGameObjectCreate(go);

            switch (go->GetEntry())
            {
            case GO_STASIS_POD_ALPHA:
                StasisPodGUIDs[0] = go->GetGUID();
                break;
            case GO_STASIS_POD_BETA:
                StasisPodGUIDs[1] = go->GetGUID();
                break;
            case GO_STASIS_POD_DELTA:
                StasisPodGUIDs[2] = go->GetGUID();
                break;
            case GO_STASIS_POD_GAMMA:
                StasisPodGUIDs[3] = go->GetGUID();
                break;
            case GO_STASIS_POD_OMEGA:
                StasisPodGUIDs[4] = go->GetGUID();
                break;
            case GO_WARDENS_SHIELD:
                WardensShieldGUID = go->GetGUID();
                break;
            default:
                break;
            }
        }

        void OnCreatureCreate(Creature* creature) override 
        {
            InstanceScript::OnCreatureCreate(creature);

            switch (creature->GetEntry())
            {
            case NPC_DALLIAH:
                DalliahGUID = creature->GetGUID();
                break;
            case NPC_MELLICHAR:
                MellicharGUID = creature->GetGUID();
                break;
            case NPC_MULHOUSE:
                MulhouseGUID = creature->GetGUID();
                break;
            case NPC_SOCCOTHRATES:
                SoccothratesGUID = creature->GetGUID();
                break;
            }
        }
        
        bool SetBossState(uint32 type, EncounterState state) override
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
            case DATA_HARBINGER_SKYRISS:
                if (state == NOT_STARTED || state == FAIL)
                {
                    SetData(DATA_WARDEN_1, NOT_STARTED);
                    SetData(DATA_WARDEN_2, NOT_STARTED);
                    SetData(DATA_WARDEN_3, NOT_STARTED);
                    SetData(DATA_WARDEN_4, NOT_STARTED);
                    SetData(DATA_WARDEN_5, NOT_STARTED);
                }
                break;
            }
            return true;
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case DATA_WARDEN_1:
            case DATA_WARDEN_2:
            case DATA_WARDEN_3:
            case DATA_WARDEN_4:
            case DATA_WARDEN_5:
                if (data == IN_PROGRESS)
                    HandleGameObject(StasisPodGUIDs[type - DATA_WARDEN_1], true);
                StasisPodStates[type - DATA_WARDEN_1] = uint8(data);
                break;
            case DATA_CONVERSATION:
                ConversationState = uint8(data);
                break;
            default:
                break;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case DATA_WARDEN_1:
            case DATA_WARDEN_2:
            case DATA_WARDEN_3:
            case DATA_WARDEN_4:
            case DATA_WARDEN_5:
                return StasisPodStates[type - DATA_WARDEN_1];
            case DATA_CONVERSATION:
                return ConversationState;
            default:
                break;
            }
            return 0;
        }

        ObjectGuid GetGuidData(uint32 data) const override
        {
            switch (data)
            {
            case DATA_DALLIAH:
                return DalliahGUID;
            case DATA_SOCCOTHRATES:
                return SoccothratesGUID;
            case DATA_MELLICHAR:
                return MellicharGUID;
            case DATA_WARDENS_SHIELD:
                return WardensShieldGUID;
            default:
                break;
            }
            return ObjectGuid::Empty;
        }
    };
};

void AddSC_instance_arcatraz()
{
    new instance_arcatraz();
}

