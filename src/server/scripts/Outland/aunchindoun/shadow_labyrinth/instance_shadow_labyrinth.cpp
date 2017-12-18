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
SDName: Instance_Shadow_Labyrinth
SD%Complete: 85
SDComment: Some cleanup left along with save
SDCategory: Auchindoun, Shadow Labyrinth
EndScriptData */


#include "def_shadow_labyrinth.h"

/* Shadow Labyrinth encounters:
1 - Ambassador Hellmaw event
2 - Blackheart the Inciter event
3 - Grandmaster Vorpil event
4 - Murmur event
*/
DoorData const doorData[] =
{
    { GO_REFECTORY_DOOR,        DATA_BLACKHEART_THE_INCITER,    DOOR_TYPE_PASSAGE },
    { GO_SCREAMING_HALL_DOOR,   DATA_GRANDMASTER_VORPIL,        DOOR_TYPE_PASSAGE },
    { 0,                        0,                              DOOR_TYPE_ROOM } // END
};

class instance_shadow_labyrinth : public InstanceMapScript
{
public:
    instance_shadow_labyrinth() : InstanceMapScript(SLScriptName, 555) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_shadow_labyrinth_script(map);
    }

    struct instance_shadow_labyrinth_script : public InstanceScript
    {
        instance_shadow_labyrinth_script(Map *map) : InstanceScript(map) { Initialize(); };

        ObjectGuid AmbassadorHellmawGUID;
        uint64 GrandmasterVorpilGUID;
        uint32 FelOverseerCount;

        void Initialize() override
        {
            GrandmasterVorpilGUID = 0;
            FelOverseerCount = 0;
        }

        void OnCreatureCreate(Creature *creature) override
        {
            switch (creature->GetEntry())
            {
            case NPC_AMBASSADOR_HELLMAW:
                AmbassadorHellmawGUID = creature->GetGUID();
                break;
            case NPC_GRANDMASTER_VORPIL:
                GrandmasterVorpilGUID = creature->GetGUID();
                break;
            case NPC_FEL_OVERSEER:
                if (creature->IsAlive())
                {
                    ++FelOverseerCount;
                    if (Creature* hellmaw = instance->GetCreature(AmbassadorHellmawGUID))
                        hellmaw->AI()->DoAction(ACTION_AMBASSADOR_HELLMAW_BANISH);
                }
                break;
            }
        }

        void OnUnitDeath(Unit* unit) override
        {
            Creature* creature = unit->ToCreature();
            if (!creature)
                return;

            if (creature->GetEntry() == NPC_FEL_OVERSEER)
            {
                if (FelOverseerCount)
                    --FelOverseerCount;

                if (!FelOverseerCount)
                    if (Creature* hellmaw = instance->GetCreature(AmbassadorHellmawGUID))
                        hellmaw->AI()->DoAction(ACTION_AMBASSADOR_HELLMAW_INTRO);
            }
        }
    };
};

void AddSC_instance_shadow_labyrinth()
{
    new instance_shadow_labyrinth();
}

