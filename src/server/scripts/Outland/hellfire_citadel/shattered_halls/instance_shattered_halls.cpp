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
SDName: Instance_Shattered_Halls
SD%Complete: 90
SDComment: Loots of the Executioner should depend on the amount of prisoners killed
SDCategory: Hellfire Citadel, Shattered Halls
EndScriptData */


#include "def_shattered_halls.h"

#define ENCOUNTERS  6

uint32 HordePrisoners[3] = { 17296, 17295, 17297 };
uint32 AlliancePrisoners[3] = { 17290, 17292, 17289 };
float PrisonersCoord[3][4] = 
{
    { 147.752808f, -79.643730f, 1.917701f, 5.537074f },
    { 142.168777f, -84.358223f, 1.908038f, 6.264657f },
    { 145.993637f, -89.312386f, 1.915693f, 0.714077f }
};

class instance_shattered_halls : public InstanceMapScript
{
public:
    instance_shattered_halls() : InstanceMapScript("instance_shattered_halls", 540) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_shattered_halls_script(map);
    }

    struct instance_shattered_halls_script : public InstanceScript
    {
        instance_shattered_halls_script(Map* pMap) : InstanceScript(pMap) { Initialize(); };

        uint32 Encounters[ENCOUNTERS];
        uint32 SaveIntervalTimer;
        uint32 TimerLeft;

        uint64 FirstDoorGUID;
        uint64 SecondDoorGUID;
        uint64 NethekurseGUID;
        uint64 ExecutionerGUID;

        Creature* FirstPrisoner;
        Creature* SecondPrisoner;
        Creature* ThirdPrisoner;

        bool HeroicMode;
        bool hasCasted80min;
        bool hasCasted25min;
        bool hasCasted15min;

        void Initialize() override
        {
            SaveIntervalTimer = 30000;                  // Saving every 30 sec looks correct

            FirstDoorGUID = 0;
            SecondDoorGUID = 0;
            NethekurseGUID = 0;
            ExecutionerGUID = 0;

            FirstPrisoner = nullptr;
            SecondPrisoner = nullptr;
            ThirdPrisoner = nullptr;

            for (uint8 i = 0; i < ENCOUNTERS - 1; i++)     // Do not override saved Timer value !
                Encounters[i] = NOT_STARTED;

            TimerLeft = 4800000;                        // 80 mins, in ms

            HeroicMode = this->instance->IsHeroic();
        }

        void OnGameObjectCreate(GameObject* pGo) override
        {
            switch (pGo->GetEntry())
            {
            case ENTRY_FIRST_DOOR:
                FirstDoorGUID = pGo->GetGUID();
                if (Encounters[DATA_NETHEKURSE_EVENT] == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            case ENTRY_SECOND_DOOR:
                SecondDoorGUID = pGo->GetGUID();
                if (Encounters[DATA_NETHEKURSE_EVENT] == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            }
        }

        void OnCreatureCreate(Creature* creature) override
        {
            switch (creature->GetEntry()) {
            case 16807:     // Nethekurse
                NethekurseGUID = creature->GetGUID();
                break;
            case 17301:     // Executioner
                ExecutionerGUID = creature->GetGUID();
                creature->SetKeepActive(true);
                if (GetData(DATA_NETHEKURSE_EVENT) == NOT_STARTED)
                    creature->SetVisible(false);
                if (GetData(DATA_BLADEFIST_EVENT) == NOT_STARTED)
                    creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                break;
            }
        }

        // This is a hack. Actually, LootMgr should be able to dynamically change loot table depending on the amount of prisoners killed.
        void RewardAllPlayersInMapForQuest()
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                for (const auto & player : players)
                {
                    if (Player* plr = player.GetSource()) {
                        if (plr->GetQuestStatus(10884) == QUEST_STATUS_INCOMPLETE) {
                            plr->CompleteQuest(10884);      // Directly complete quest, so we are sure it is
                            // Now, we try to give the quest item, that looks more blizzlike that way
                            ItemPosCountVec dest;
                            uint8 msg = plr->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 31716, 1);
                            if (msg == EQUIP_ERR_OK) {
                                Item* item = plr->StoreNewItem(dest, 31716, true);
                                if (item)
                                    plr->SendNewItem(item, 1, false, true);
                            }
                            else
                                plr->SendEquipError(msg, nullptr, nullptr);
                        }
                    }
                }
            }
        }

        void CastSpellOnAllPlayersInMap(uint32 spellid)
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                for (const auto & player : players)
                {
                    if (Player* plr = player.GetSource())
                        if (plr->IsAttackableByAOE())
                            plr->CastSpell(plr, spellid, TRIGGERED_FULL_MASK);
                }
            }
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 Encounter : Encounters)
                if (Encounter == IN_PROGRESS) return true;

            return false;
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case DATA_NETHEKURSE_EVENT:
                Encounters[DATA_NETHEKURSE_EVENT] = data;
                if (data == DONE) {
                    HandleGameObject(FirstDoorGUID, true, nullptr);
                    HandleGameObject(SecondDoorGUID, true, nullptr);
                }
                break;
            case DATA_PORUNG_EVENT:
                Encounters[DATA_PORUNG_EVENT] = data;
                break;
            case DATA_OMROGG_EVENT:
                Encounters[DATA_OMROGG_EVENT] = data;
                break;
            case DATA_BLADEFIST_EVENT:
                Encounters[DATA_BLADEFIST_EVENT] = data;
                break;
            case DATA_EXECUTIONER_EVENT:
                Encounters[DATA_EXECUTIONER_EVENT] = data;
                break;
            case DATA_TIMER_LEFT:
                Encounters[5] = data;
            }

            if (data == DONE)
                SaveToDB();
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case DATA_NETHEKURSE_EVENT:
                return Encounters[DATA_NETHEKURSE_EVENT];
            case DATA_PORUNG_EVENT:
                return Encounters[DATA_PORUNG_EVENT];
            case DATA_OMROGG_EVENT:
                return Encounters[DATA_OMROGG_EVENT];
            case DATA_BLADEFIST_EVENT:
                return Encounters[DATA_BLADEFIST_EVENT];
            case DATA_EXECUTIONER_EVENT:
                return Encounters[DATA_EXECUTIONER_EVENT];
            case DATA_TIMER_LEFT:
                return Encounters[5];
            }

            return 0;
        }

        uint64 GetData64(uint32 data) const override
        {
            switch (data)
            {
            case ENTRY_FIRST_DOOR:
                return FirstDoorGUID;
            case ENTRY_SECOND_DOOR:
                return SecondDoorGUID;
            case DATA_NETHEKURSE_GUID:
                return NethekurseGUID;
            case DATA_EXECUTIONER_GUID:
                return ExecutionerGUID;
            }

            return 0;
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream stream;
            stream << Encounters[0] << " " << Encounters[1] << " " << Encounters[2] << " " << Encounters[3] << " " << Encounters[4] << " " << Encounters[5];

            OUT_SAVE_INST_DATA_COMPLETE;
            return stream.str();
        }

        void Load(const char* in) override
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);
            std::istringstream stream(in);
            stream >> Encounters[0] >> Encounters[1] >> Encounters[2] >> Encounters[3] >> Encounters[4] >> Encounters[5];
            for (uint8 i = 0; i < ENCOUNTERS; ++i)
                if (Encounters[i] == IN_PROGRESS && i != 4)                // Do not load an encounter as "In Progress" - reset it instead, except for Executioner.
                    Encounters[i] = NOT_STARTED;

            TimerLeft = Encounters[5];

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        // Update is only needed in Heroic, for the timer
        void Update(uint32 diff) override
        {
            if (!HeroicMode)
                return;

            // If Executioner is dead and some prisoners are still alive, reward players for quest
            /*if (Executioner && Executioner->IsDead() && GetData(DATA_EXECUTIONER_EVENT) != DONE) {
                if ( (FirstPrisoner && FirstPrisoner->IsAlive()) || (SecondPrisoner && SecondPrisoner->IsAlive()) || (ThirdPrisoner && ThirdPrisoner->IsAlive()) ) {
                    RewardAllPlayersInMapForQuest();
                    SetData(DATA_EXECUTIONER_EVENT, DONE);
                }
            }*/

            if (GetData(DATA_EXECUTIONER_EVENT) != IN_PROGRESS)
                return;

            // Decrease timer at each update
            TimerLeft -= diff;

            if (!hasCasted80min) {      // Event just started
                // TODO: Correct this [PH] yell
                if (Creature *Executioner = instance->GetCreature(ExecutionerGUID))
                    if (Executioner->IsInWorld())
                        Executioner->YellToMap("[PH] I got three hostages! In 55 minutes, I will kill the first one!");
                CastSpellOnAllPlayersInMap(EXEC_TIMER_55);
                Player* plr = GetPlayer();
                if (!plr) {
                    TC_LOG_ERROR("scripts", "Instance Shattered Halls: Update: No player found in map when event started !");
                    return;
                }
                //SpawnPrisoners(plr->GetTeam(), 3);
                hasCasted80min = true;
            }

            if (TimerLeft < 1500000 && !hasCasted25min) {               // 25 min left and debuff not casted yet
                // TODO: Correct this [PH] yell
                if (Creature *Executioner = instance->GetCreature(ExecutionerGUID))
                    if (Executioner->IsInWorld())
                        Executioner->YellToMap("[PH] The first hostage is dead! In 10 minutes, I will kill a second!", LANG_UNIVERSAL);
                CastSpellOnAllPlayersInMap(GetData(EXEC_TIMER_10));      // 2nd timer of 10 mins
                /*if (FirstPrisoner && Executioner)
                    Executioner->DealDamage(FirstPrisoner, FirstPrisoner->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);*/
                hasCasted25min = true;
            }

            if (TimerLeft < 900000 && !hasCasted15min) {                // 15 min left and debuff not casted yet
                // TODO: Correct this [PH] yell
                if (Creature *Executioner = instance->GetCreature(ExecutionerGUID))
                    if (Executioner->IsInWorld())
                        Executioner->YellToMap("[PH] I killed the second hostage! In fifteen minutes, I will kill the last.");
                CastSpellOnAllPlayersInMap(GetData(EXEC_TIMER_15));      // 3rd (and last) timer of 15 mins
                /*if (SecondPrisoner && Executioner)
                    Executioner->DealDamage(SecondPrisoner, SecondPrisoner->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);*/
                hasCasted15min = true;
            }

            if (TimerLeft < diff) {     // TIME UP ! Kill the third prisoner and stop the timer, killing executioner won't give the quest item
                // TODO: Correct this [PH] yell
                if (Creature *Executioner = instance->GetCreature(ExecutionerGUID)) {
                    if (Executioner->IsInWorld()) {
                        Executioner->YellToMap("[PH] You're too late! I killed them all.");
                        Executioner->loot.RemoveItem(31716);
                    }
                }
                /*if (ThirdPrisoner && Executioner)
                    Executioner->DealDamage(ThirdPrisoner, ThirdPrisoner->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);*/
                SetData(DATA_EXECUTIONER_EVENT, FAIL);
            }

            // Save time left in DB every 30 sec
            if (SaveIntervalTimer <= diff) {
                SetData(DATA_TIMER_LEFT, TimerLeft);
                SaveToDB();
                SaveIntervalTimer = 30000;
            }
            else SaveIntervalTimer -= diff;
        }
    };
};

// AreaTrigger that starts the timed event
class ATShatteredHalls : AreaTriggerScript
{
public:
    ATShatteredHalls() : AreaTriggerScript("at_shattered_halls") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (InstanceScript* pInstance = ((InstanceScript*)pPlayer->GetInstanceScript())) {
            if (pInstance->GetData(DATA_EXECUTIONER_EVENT) != IN_PROGRESS) {
                pInstance->SetData(DATA_EXECUTIONER_EVENT, IN_PROGRESS);
                if (Creature* Executioner = ObjectAccessor::GetCreature(*pPlayer, pInstance->GetData64(DATA_EXECUTIONER_GUID))) {
                    Executioner->SetVisible(true);
                    Executioner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    // TODO: Yell something ?
                }
            }
        }

        return true;
    }
};

void AddSC_instance_shattered_halls()
{
    new instance_shattered_halls();
    new ATShatteredHalls();
}

