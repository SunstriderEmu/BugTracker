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
SDName: Instance_Mount_Hyjal
SD%Complete: 100
SDComment: Instance Data Scripts and functions to acquire mobs and set encounter status for use in various Hyjal Scripts
SDCategory: Caverns of Time, Mount Hyjal
EndScriptData */


#include "def_hyjal.h"
#include "hyjal_trash.h"

#define ENCOUNTERS     5

/* Battle of Mount Hyjal encounters:
0 - Rage Winterchill event
1 - Anetheron event
2 - Kaz'rogal event
3 - Azgalor event
4 - Archimonde event
*/
class instance_hyjal : public InstanceMapScript
{
public:
    instance_hyjal() : InstanceMapScript("instance_hyjal", 534) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_mount_hyjal_script(map);
    }

    struct instance_mount_hyjal_script : public InstanceScript
    {
        instance_mount_hyjal_script(Map *map) : InstanceScript(map) { Initialize(); };

        uint64 RageWinterchill;
        uint64 Anetheron;
        uint64 Kazrogal;
        uint64 Azgalor;
        uint64 Archimonde;
        uint64 JainaProudmoore;
        uint64 Thrall;
        uint64 TyrandeWhisperwind;
        uint64 HordeGate;
        uint64 ElfGate;

        uint32 Trash;
        uint32 Encounters[ENCOUNTERS];

        uint32 hordeRetreat;
        uint32 allianceRetreat;
        bool ArchiYell;

        uint32 RaidDamage;
        uint32 currentWave;

        std::list<uint64> allianceArmy;

        void Initialize()
            override {
            RageWinterchill = 0;
            Anetheron = 0;
            Kazrogal = 0;
            Azgalor = 0;
            Archimonde = 0;
            JainaProudmoore = 0;
            Thrall = 0;
            TyrandeWhisperwind = 0;
            HordeGate = 0;
            ElfGate = 0;
            ArchiYell = false;
            RaidDamage = 0;

            Trash = 0;
            for (uint32 & Encounter : Encounters)
                Encounter = NOT_STARTED;

            hordeRetreat = 0;
            allianceRetreat = 0;

            currentWave = 0;
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 Encounter : Encounters)
                if (Encounter == IN_PROGRESS) return true;

            return false;
        }

        void OnGameObjectCreate(GameObject *go) override
        {
            switch (go->GetEntry())
            {
            case GOBJECT_DOOR_ORC:
                HordeGate = go->GetGUID();
                if (allianceRetreat)
                    go->SetGoState(GO_STATE_ACTIVE);
                else
                    go->SetGoState(GO_STATE_READY);
                break;
            case GOBJECT_DOOR_ELF:
                ElfGate = go->GetGUID();
                if (hordeRetreat)
                    go->SetGoState(GO_STATE_ACTIVE);
                else
                    go->SetGoState(GO_STATE_READY);
                break;
            }
        }

        void OpenDoor(uint64 DoorGUID, bool open)
        {
            if (GameObject *Door = instance->GetGameObject(DoorGUID))
                Door->SetUInt32Value(GAMEOBJECT_STATE, open ? 0 : 1);
        }

        void PlayerDied(Player* player) override
        {
            if (GetData(DATA_ARCHIMONDEEVENT) == IN_PROGRESS) {
                if (Creature* archimonde = instance->GetCreature(Archimonde))
                    archimonde->AI()->message(0, player->GetClass());
            }
        }

        void OnCreatureCreate(Creature *creature, uint32 creature_entry) override
        {
            switch (creature_entry)
            {
            case CREATURE_RAGE_WINTERCHILL: RageWinterchill = creature->GetGUID(); break;
            case CREATURE_ANATHERON:        Anetheron = creature->GetGUID(); break;
            case CREATURE_KAZROGAL:         Kazrogal = creature->GetGUID();  break;
            case CREATURE_AZGALOR:          Azgalor = creature->GetGUID(); break;
            case CREATURE_ARCHIMONDE:       Archimonde = creature->GetGUID(); break;
            case CREATURE_JAINA:            JainaProudmoore = creature->GetGUID(); break;
            case CREATURE_THRALL:           Thrall = creature->GetGUID(); break;
            case CREATURE_TYRANDE:          TyrandeWhisperwind = creature->GetGUID(); break;

            case CREATURE_ALLIANCE_FOOTMAN:
            case CREATURE_ALLIANCE_KNIGHT:
            case CREATURE_ALLIANCE_RIFLEMAN:
            case CREATURE_ALLIANCE_SORCERESS:
            case CREATURE_ALLIANCE_PRIEST:
                allianceArmy.push_back(creature->GetGUID());
                break;
            }
        }

        uint64 GetData64(uint32 identifier) const override
        {
            switch (identifier)
            {
            case DATA_RAGEWINTERCHILL: return RageWinterchill;
            case DATA_ANETHERON: return Anetheron;
            case DATA_KAZROGAL: return Kazrogal;
            case DATA_AZGALOR: return Azgalor;
            case DATA_ARCHIMONDE: return Archimonde;
            case DATA_JAINAPROUDMOORE: return JainaProudmoore;
            case DATA_THRALL: return Thrall;
            case DATA_TYRANDEWHISPERWIND: return TyrandeWhisperwind;
            }

            return 0;
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case DATA_RAGEWINTERCHILLEVENT: Encounters[0] = data; break;
            case DATA_ANETHERONEVENT:
                Encounters[1] = data;
                if (data == DONE) {
                    currentWave = 0;
                    if (Creature* thrall = instance->GetCreature(Thrall))
                        thrall->AI()->SetData(0, 0);
                }
                break;
            case DATA_KAZROGALEVENT:        Encounters[2] = data; break;
            case DATA_AZGALOREVENT:
            {
                Encounters[3] = data;
                if (data == DONE)
                {
                    if (ArchiYell)break;
                    ArchiYell = true;

                    Creature* pCreature = instance->GetCreature(Azgalor);
                    if (pCreature)
                    {
                        Creature* pUnit = pCreature->SummonCreature(21987, pCreature->GetPositionX(), pCreature->GetPositionY(), pCreature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 10000);

                        Map *map = pCreature->GetMap();
                        if (!map)
                            break;

                        Creature* archimonde = map->GetCreature(GetData64(DATA_ARCHIMONDE));
                        if (!archimonde)
                            break;

                        if (map->IsDungeon() && pUnit)
                        {
                            pUnit->SetVisibility(VISIBILITY_OFF);
                            Map::PlayerList const &PlayerList = map->GetPlayers();
                            if (PlayerList.isEmpty())
                                break;

                            std::string yell = "All of your efforts have been in vain, for the draining of the World Tree has already begun. Soon the heart of your world will beat no more.";
                            for (const auto & i : PlayerList)
                            {
                                if (i.GetSource())
                                {
                                    WorldPacket data;
                                    ChatHandler::BuildChatPacket(data, CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, archimonde, i.GetSource(), yell);
                                    i.GetSource()->GetSession()->SendPacket(&data);

                                    WorldPacket data2(SMSG_PLAY_SOUND, 4);
                                    data2 << 10986;
                                    i.GetSource()->GetSession()->SendPacket(&data2);
                                }
                            }
                        }
                    }
                }
            }
            break;
            case DATA_ARCHIMONDEEVENT:      Encounters[4] = data; break;
            case DATA_RESET_TRASH_COUNT:    Trash = 0;            break;

            case DATA_TRASH:
                if (data) Trash = data;
                else     Trash--;
                UpdateWorldState(WORLD_STATE_ENEMYCOUNT, Trash);
                break;
            case DATA_ALLIANCE_RETREAT:
                allianceRetreat = data;
                OpenDoor(HordeGate, true);
                SaveToDB();
                break;
            case DATA_HORDE_RETREAT:
                hordeRetreat = data;
                OpenDoor(ElfGate, true);
                SaveToDB();
                break;
            case DATA_RAIDDAMAGE:
                RaidDamage += data;
                if (RaidDamage >= MINRAIDDAMAGE)
                    RaidDamage = MINRAIDDAMAGE;
                break;
            case DATA_RESET_RAIDDAMAGE:
                RaidDamage = 0;
                break;
            case DATA_CURRENT_WAVE:
                currentWave = data;
                SaveToDB();
                break;
            case DATA_JAINAINCOMBAT:
                JainaCallForHelp();
                break;
            }

            if (data == DONE)
                SaveToDB();
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case DATA_RAGEWINTERCHILLEVENT: return Encounters[0];
            case DATA_ANETHERONEVENT:       return Encounters[1];
            case DATA_KAZROGALEVENT:        return Encounters[2];
            case DATA_AZGALOREVENT:         return Encounters[3];
            case DATA_ARCHIMONDEEVENT:      return Encounters[4];
            case DATA_TRASH:                return Trash;
            case DATA_ALLIANCE_RETREAT:     return allianceRetreat;
            case DATA_HORDE_RETREAT:        return hordeRetreat;
            case DATA_RAIDDAMAGE:           return RaidDamage;
            case DATA_CURRENT_WAVE:         return currentWave;
            }
            return 0;
        }

        void UpdateWorldState(uint32 id, uint32 state)
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                for (const auto & itr : players)
                {
                    if (Player* player = itr.GetSource())
                        player->SendUpdateWorldState(id, state);
                }
            }
            else TC_LOG_ERROR("scripts", "Instance Hyjal: UpdateWorldState, but PlayerList is empty!");
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream stream;
            stream << Encounters[0] << " " << Encounters[1] << " " << Encounters[2] << " "
                << Encounters[3] << " " << Encounters[4] << " " << allianceRetreat << " " << hordeRetreat << " " << RaidDamage << " " << currentWave;

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
            std::istringstream loadStream;
            loadStream.str(in);
            loadStream >> Encounters[0] >> Encounters[1] >> Encounters[2] >> Encounters[3] >> Encounters[4] >> allianceRetreat >> hordeRetreat >> RaidDamage >> currentWave;
            for (uint32 & Encounter : Encounters)
                if (Encounter == IN_PROGRESS)                // Do not load an encounter as IN_PROGRESS - reset it instead.
                    Encounter = NOT_STARTED;
            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void JainaCallForHelp()
        {
            Creature* Jaina = instance->GetCreature(JainaProudmoore);
            if (!Jaina || !Jaina->GetVictim()) return;

            for (auto itr : allianceArmy)
            {
                Creature* soldier = instance->GetCreature(itr);
                if (!soldier) continue;
                if (soldier->IsAlive() && !soldier->IsInCombat())
                {
                    soldier->SetInCombatWith(Jaina->GetVictim());
                    soldier->AddThreat(Jaina->GetVictim(), 0.0f);
                }
            }
        }
    };
};

void AddSC_instance_mount_hyjal()
{
    new instance_hyjal();
}

