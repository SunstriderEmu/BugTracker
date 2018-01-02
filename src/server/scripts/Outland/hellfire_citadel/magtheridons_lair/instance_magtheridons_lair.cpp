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
SDName: Instance_Magtheridons_Lair
SD%Complete: 100
SDComment:
SDCategory: Hellfire Citadel, Magtheridon's lair
EndScriptData */


#include "def_magtheridons_lair.h"

#define SPELL_SOUL_TRANSFER         30531 // core bug, does not support target 7
#define SPELL_BLAZE_TARGET          30541 // core bug, does not support target 7

#define CHAMBER_CENTER_X            -15.14
#define CHAMBER_CENTER_Y              1.8
#define CHAMBER_CENTER_Z             -0.4

#define ENCOUNTERS 2

class instance_magtheridons_lair : public InstanceMapScript
{
public:
    instance_magtheridons_lair() : InstanceMapScript("instance_magtheridons_lair", 544) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_magtheridons_lair_script(map);
    }

    struct instance_magtheridons_lair_script : public InstanceScript
    {
        instance_magtheridons_lair_script(Map *Map) : InstanceScript(Map)
        {
            Initialize();
        }

        uint32 Encounters[ENCOUNTERS];

        ObjectGuid MagtheridonGUID;
        std::set<ObjectGuid> ChannelerGUID;
        ObjectGuid DoorGUID;
        std::set<ObjectGuid> ColumnGUID;

        uint32 CageTimer;
        uint32 RespawnTimer;

        void Initialize()
            override {
            for (uint32 & Encounter : Encounters)
                Encounter = NOT_STARTED;
            
            CageTimer = 0;
            RespawnTimer = 0;
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 Encounter : Encounters)
                if (Encounter == IN_PROGRESS) return true;
            return false;
        }

        void OnCreatureCreate(Creature *creature) override 
        {
            switch (creature->GetEntry())
            {
            case 17257:
                MagtheridonGUID = creature->GetGUID();
                break;
            case 17256:
                ChannelerGUID.insert(creature->GetGUID());
                break;
            }
        }

        void OnGameObjectCreate(GameObject *go) override
        {
            switch (go->GetEntry())
            {
            case 181713:
                go->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
                break;
            case 183847:
                DoorGUID = go->GetGUID();
                break;
            case 184653: // hall
            case 184634: // six columns
            case 184635:
            case 184636:
            case 184637:
            case 184638:
            case 184639:
                ColumnGUID.insert(go->GetGUID());
                break;
            }
        }

        uint64 GetData64(uint32 type) const override
        {
            switch (type)
            {
            case DATA_MAGTHERIDON:
                return MagtheridonGUID;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case DATA_MAGTHERIDON_EVENT:
                Encounters[0] = data;
                if (data == NOT_STARTED)
                    RespawnTimer = 10000;
                if (data != IN_PROGRESS)
                {
                    if (GameObject *Door = instance->GetGameObject(DoorGUID))
                        Door->UseDoorOrButton();
                }
                break;
            case DATA_CHANNELER_EVENT:
                switch (data)
                {
                case NOT_STARTED: // Reset all channelers once one is reset.
                    if (Encounters[1] != NOT_STARTED)
                    {
                        Encounters[1] = NOT_STARTED;
                        for (ObjectGuid i : ChannelerGUID)
                        {
                            if (Creature *Channeler = instance->GetCreature(i))
                            {
                                if (Channeler->IsAlive())
                                    Channeler->AI()->EnterEvadeMode();
                                else
                                    Channeler->Respawn();
                            }
                        }
                        CageTimer = 0;
                        if (GameObject *Door = instance->GetGameObject(DoorGUID))
                            Door->UseDoorOrButton();
                    }break;
                case IN_PROGRESS: // Event start.
                    if (Encounters[1] != IN_PROGRESS)
                    {
                        Encounters[1] = IN_PROGRESS;
                        // Let all five channelers aggro.
                        for (ObjectGuid i : ChannelerGUID)
                        {
                            Creature *Channeler = instance->GetCreature(i);
                            if (Channeler && Channeler->IsAlive())
                                Channeler->AI()->AttackStart(Channeler->SelectNearestTarget(999));
                        }
                        // Release Magtheridon after two minutes.
                        Creature *Magtheridon = instance->GetCreature(MagtheridonGUID);
                        if (Magtheridon && Magtheridon->IsAlive())
                        {
                            Magtheridon->TextEmote("'s bonds begin to weaken!", nullptr);
                            CageTimer = 120000;
                        }
                        if (GameObject *Door = instance->GetGameObject(DoorGUID))
                            Door->ResetDoorOrButton();
                    }break;
                case DONE: // Add buff and check if all channelers are dead.
                    for (ObjectGuid i : ChannelerGUID)
                    {
                        Creature *Channeler = instance->GetCreature(i);
                        if (Channeler && Channeler->IsAlive())
                        {
                            //Channeler->CastSpell(Channeler, SPELL_SOUL_TRANSFER, TRIGGERED_FULL_MASK);
                            data = IN_PROGRESS;
                            break;
                        }
                    }break;
                }
                Encounters[1] = data;
                break;
            case DATA_COLLAPSE:
                // true - collapse / false - reset
                for (ObjectGuid i : ColumnGUID)
                {
                    if (GameObject *Column = instance->GetGameObject(i))
                        Column->SetGoState(GOState(!data));
                }
                break;
            default:
                break;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            if (type == DATA_MAGTHERIDON_EVENT)
                return Encounters[0];
            return 0;
        }

        void Update(uint32 diff) override
        {
            if (CageTimer)
            {
                if (CageTimer <= diff)
                {
                    Creature *Magtheridon = instance->GetCreature(MagtheridonGUID);
                    if (Magtheridon && Magtheridon->IsAlive())
                    {
                        Magtheridon->ClearUnitState(UNIT_STATE_STUNNED);
                        Magtheridon->AI()->AttackStart(Magtheridon->SelectNearestTarget(999));
                    }
                    CageTimer = 0;
                }
                else CageTimer -= diff;
            }

            if (RespawnTimer)
            {
                if (RespawnTimer <= diff)
                {
                    for (ObjectGuid i : ChannelerGUID)
                    {
                        if (Creature *Channeler = instance->GetCreature(i))
                        {
                            if (Channeler->IsAlive())
                                Channeler->AI()->EnterEvadeMode();
                            else
                                Channeler->Respawn();
                        }
                    }
                    RespawnTimer = 0;
                }
                else RespawnTimer -= diff;
            }
        }
    };
};

void AddSC_instance_magtheridons_lair()
{
    new instance_magtheridons_lair();
}

