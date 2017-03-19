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


#include "def_razorfen_downs.h"

#define ENCOUNTERS 6

class instance_razorfen_downs : public InstanceMapScript
{
public:
    instance_razorfen_downs() : InstanceMapScript("instance_razorfen_downs", 129) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_razorfen_downs_scrip(map);
    }

    struct instance_razorfen_downs_scrip : public InstanceScript
    {
        instance_razorfen_downs_scrip(Map *map) : InstanceScript(map) {};

        void Initialize()
            override {
            IsWipe = false;
            waves = 0;
            creatureCredit = 0;
            tuten_kashGUID = 0;
            mordresh_fire_eyeGUID = 0;
            plaguemaw_the_rottingGUID = 0;
            ragglesnoutGUID = 0;
            gluttonGUID = 0;
            amnennar_the_coldbringerGUID = 0;

            for (uint32 & Encounter : Encounters)
                Encounter = NOT_STARTED;
        }

        uint32 waves;
        uint32 creatureCredit;
        uint64 tuten_kashGUID;
        uint64 mordresh_fire_eyeGUID;
        uint64 plaguemaw_the_rottingGUID;
        uint64 ragglesnoutGUID;
        uint64 gluttonGUID;
        uint64 amnennar_the_coldbringerGUID;

        uint32 Encounters[ENCOUNTERS];
        std::string str_data;
        bool IsWipe;

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case DATA_WAVE_EVENT:
                waves++;
                break;
            case DATA_CREATURE_CREDIT:
                creatureCredit = data;
                break;
            case DATA_TUTEN_KASH_EVENT:
                Encounters[0] = data;
                break;
            case DATA_MORDRESH_FIRE_EYE:
                Encounters[1] = data;
            case DATA_RAGGLESNOUT_EVENT:
                Encounters[2] = data;
            case DATA_AMNENNAR_THE_COLDBRINGER_EVENT:
                Encounters[3] = data;
            case DATA_GLUTTON_EVENT:
                Encounters[4] = data;
            case DATA_PLAGUEMAW_THE_ROTTING_EVENT:
                Encounters[5] = data;
                break;
            }

            if (data == DONE)
            {

                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << Encounters[0] << " " << Encounters[1] << " " << Encounters[2] << " " << Encounters[3] << " " << Encounters[4] << " " << Encounters[5];

                str_data = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case DATA_TUTEN_KASH_EVENT:                 return Encounters[0];
            case DATA_MORDRESH_FIRE_EYE:                return Encounters[1];
            case DATA_RAGGLESNOUT_EVENT:                return Encounters[2];
            case DATA_AMNENNAR_THE_COLDBRINGER_EVENT:   return Encounters[3];
            case DATA_GLUTTON_EVENT:                    return Encounters[4];
            case DATA_PLAGUEMAW_THE_ROTTING_EVENT:      return Encounters[5];
            case DATA_WAVE_EVENT:                       return waves;
            case DATA_CREATURE_CREDIT:                  return creatureCredit;
            }
            return 0;
        }

        uint64 GetData64(uint32 identifier) const override
        {
            switch (identifier)
            {
            case DATA_TUTEN_KASH_EVENT:
                return tuten_kashGUID;
            case DATA_MORDRESH_FIRE_EYE:
                return mordresh_fire_eyeGUID;
            case DATA_RAGGLESNOUT_EVENT:
                return ragglesnoutGUID;
            case DATA_AMNENNAR_THE_COLDBRINGER_EVENT:
                return amnennar_the_coldbringerGUID;
            case DATA_GLUTTON_EVENT:
                return gluttonGUID;
            case DATA_PLAGUEMAW_THE_ROTTING_EVENT:
                return plaguemaw_the_rottingGUID;
            }
            return 0;
        }

        void OnCreatureCreate(Creature *creature) override
        {
            switch (creature->GetEntry())
            {
            case BOSS_TUTEN_KASH:
                tuten_kashGUID = creature->GetGUID();
            case BOSS_MORDRESH_FIRE_EYE:
                mordresh_fire_eyeGUID = creature->GetGUID();
            case BOSS_RAGGLESNOUT:
                ragglesnoutGUID = creature->GetGUID();
            case BOSS_AMNENNAR_THE_COLDBRINGER:
                amnennar_the_coldbringerGUID = creature->GetGUID();
            case BOSS_GLUTTON:
                gluttonGUID = creature->GetGUID();
            case BOSS_PLAGUEMAW_THE_ROTTING:
                plaguemaw_the_rottingGUID = creature->GetGUID();
                break;
            }
        }

        void OnCreatureKill(Creature* victim) override
        {
            switch (victim->GetEntry())
            {
            case NPC_TOMB_FIEND:
            case NPC_TOMB_REAVER:
                if (creatureCredit > 0)
                    creatureCredit--;
                break;
            }
        }

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
            loadStream >> Encounters[0] >> Encounters[1] >> Encounters[2] >> Encounters[3] >> Encounters[4] >> Encounters[5];

            for (uint32 & Encounter : Encounters)
                if (Encounter == IN_PROGRESS)
                    Encounter = NOT_STARTED;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

    };
};

void AddSC_instance_razorfen_downs()
{
    new instance_razorfen_downs();
}
