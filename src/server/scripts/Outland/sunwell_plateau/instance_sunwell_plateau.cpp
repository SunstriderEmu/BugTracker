/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

/* ScriptData
SDName: Instance_Sunwell_Plateau
SD%Complete: 20
SDComment: VERIFY SCRIPT, rename Gates
SDCategory: Sunwell_Plateau
EndScriptData */


#include "def_sunwell_plateau.h"

#define ENCOUNTERS 6

/*enum GoState{
CLOSE    = 1,
OPEN    = 0
};*/

/* Sunwell Plateau:
0 - Kalecgos and Sathrovarr
1 - Brutallus
2 - Felmyst
3 - Eredar Twins (Alythess and Sacrolash)
4 - M'uru
5 - Kil'Jaeden
*/

/*
* GAUNTLET TODO:
* 
* - les 4 trashs du début ont une position_z < 40, utiliser ce critère pour lancer l'event
* - fin de l'event quand on pull le commandant
* - check si les deux trashs sont random ou si c'est un de chaque sorte à chaque fois
* - fiels : 12 sec
* - autres : 40 sec
*/

class instance_sunwell_plateau : public InstanceMapScript
{
public:
    instance_sunwell_plateau() : InstanceMapScript("instance_sunwell_plateau", 580) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_sunwell_plateau_script(map);
    }

    struct instance_sunwell_plateau_script : public InstanceScript
    {
        instance_sunwell_plateau_script(Map *map) : InstanceScript(map) { Initialize(); };

        uint32 Encounters[ENCOUNTERS];

        /** Creatures **/
        ObjectGuid Kalecgos_Dragon;
        ObjectGuid Kalecgos_Human;
        ObjectGuid Sathrovarr;
        ObjectGuid Brutallus;
        ObjectGuid Madrigosa;
        ObjectGuid Felmyst;
        ObjectGuid Alythess;
        ObjectGuid Sacrolash;
        ObjectGuid Muru;
        ObjectGuid BlackHole;
        ObjectGuid Entropius;
        ObjectGuid KilJaeden;
        ObjectGuid KilJaedenController;
        ObjectGuid Anveena;
        ObjectGuid KalecgosKJ;
        ObjectGuid FlightLeft;
        ObjectGuid FlightRight;
        ObjectGuid CommanderGUID;
        ObjectGuid BarrierTriggerGUID;
        std::vector<ObjectGuid> northList, centerList, southList;

        /** GameObjects **/
        ObjectGuid ForceField;                                      // Kalecgos Encounter
        ObjectGuid KalecgosWall[2];
        ObjectGuid FireBarrier;                                     // Felmysts Encounter
        ObjectGuid MurusGate[2];                                    // Murus Encounter
        ObjectGuid IceBarrier;
        ObjectGuid SecondGate; // Just after the Twins

        /*** Misc ***/
        uint32 SpectralRealmTimer;
        std::vector<ObjectGuid> SpectralRealmList;
        uint32 GauntletStatus;
        uint32 BringersTimer;
        uint32 FiendTimer;
        uint32 IceBarrierTimer;
        bool IceBarrierDone;
        uint32 felmystNorthTimer, felmystCenterTimer, felmystSouthTimer;
        uint32 phaseEntropius;

        void Initialize() override
        {
            memset(&Encounters, 0, sizeof(Encounters));

            /*** Creatures ***/
            northList.clear();
            centerList.clear();
            southList.clear();

            /*** Misc ***/
            SpectralRealmTimer = 5000;
            BringersTimer = 40000;
            FiendTimer = 0;
            IceBarrierTimer = 1000;

            IceBarrierDone = false;

            felmystNorthTimer = 0;
            felmystCenterTimer = 0;
            felmystSouthTimer = 0;

            /*** Encounters ***/
            for (uint32 & Encounter : Encounters)
                Encounter = NOT_STARTED;

            GauntletStatus = NOT_STARTED;
            phaseEntropius = NOT_STARTED;
        }

        bool IsEncounterInProgress() const override
        {
            for (uint32 Encounter : Encounters)
                if (Encounter == IN_PROGRESS)
                    return true;

            return false;
        }

        // Override InstanceScript::GetPlayerInMap because of aura 45839 check
        Player* GetPlayer() const
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                for (const auto & player : players)
                {
                    Player* plr = player.GetSource();
                    if (plr)
                        return plr;
                }
            }

            TC_LOG_ERROR("scripts", "Instance Sunwell Plateau: GetPlayerInMap called, and not player found!");
            return nullptr;
        }

        Player* GetAlivePlayerInMap()
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                for (const auto & player : players)
                {
                    Player* plr = player.GetSource();
                    if (plr && plr->IsAlive() && !plr->IsGameMaster())
                        return plr;
                }
            }

            return nullptr;
        }

        void OnCreatureCreate(Creature* pCreature) override 
        {
            switch (pCreature->GetEntry())
            {
            case 24850: Kalecgos_Dragon = pCreature->GetGUID(); break;
            case 24891: Kalecgos_Human = pCreature->GetGUID(); break;
            case 24892: Sathrovarr = pCreature->GetGUID(); break;
            case 24882: Brutallus = pCreature->GetGUID(); pCreature->SetKeepActive(true); break;
            case 24895: Madrigosa = pCreature->GetGUID(); pCreature->SetKeepActive(true); break;
            case 25038: Felmyst = pCreature->GetGUID(); break;
            case 25166: Alythess = pCreature->GetGUID(); break;
            case 25165: Sacrolash = pCreature->GetGUID(); break;
            case 25741: Muru = pCreature->GetGUID(); break;
            case 25855: BlackHole = pCreature->GetGUID(); break;
            case 25840: Entropius = pCreature->GetGUID(); break;
            case 25315: KilJaeden = pCreature->GetGUID(); break;
            case 25608: KilJaedenController = pCreature->GetGUID(); break;
            case 26046: Anveena = pCreature->GetGUID(); break;
            case 25319: KalecgosKJ = pCreature->GetGUID(); break;
            case 25357: FlightLeft = pCreature->GetGUID(); pCreature->SetKeepActive(true); break;
            case 25358: FlightRight = pCreature->GetGUID(); pCreature->SetKeepActive(true); break;
            case 25837: CommanderGUID = pCreature->GetGUID(); pCreature->SetKeepActive(true); break;
            case 19871: BarrierTriggerGUID = pCreature->GetGUID(); break;
            case 23472: //fog triggers
                //TC_LOG_INFO("PositionX: %f", pCreature->GetPositionX());
                if (pCreature->GetPositionX() > 1480.0f)
                    northList.push_back(pCreature->GetGUID());
                else if (pCreature->GetPositionX() > 1460.0f)
                    centerList.push_back(pCreature->GetGUID());
                else
                    southList.push_back(pCreature->GetGUID());
                //TC_LOG_INFO("Lists sizes: %u - %u - %u", northList.size(), centerList.size(), southList.size());
                break;
            }
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetGUID();
        }

        void OnCreatureDeath(Creature* creature) override
        {
            switch (creature->GetEntry())
            {
            case 25653: //Power of the Blue Flight
                if(TempSummon* summoned = creature->ToTempSummon())
                    if (Unit* summoner = summoned->GetSummoner())
                    {
                        summoner->RemoveAurasDueToSpell(45838);
                        summoner->RemoveAurasDueToSpell(45839);
                    }
                break;
            }
        }

        void OnGameObjectCreate(GameObject* pGo) override
        {
            switch (pGo->GetEntry())
            {
            case 188421: ForceField = pGo->GetGUID(); break;
            case 188523: KalecgosWall[0] = pGo->GetGUID(); break;
            case 188524: KalecgosWall[1] = pGo->GetGUID(); break;
            case 188075:
                if (Encounters[2] == DONE)
                    HandleGameObject(ObjectGuid::Empty, true, pGo);
                FireBarrier = pGo->GetGUID();
                break;
            case 187990: MurusGate[0] = pGo->GetGUID(); break;
            case 188118:
                if (Encounters[4] == DONE)
                    HandleGameObject(ObjectGuid::Empty, true, pGo);
                MurusGate[1] = pGo->GetGUID();
                break;
                /*case 187766:    // The first gate FIXME: Always closed for now, will change later
                    HandleGameObject(0, false, pGo);
                    break;*/
            case 187764:    // The second gate FIXME: Always closed for now, will change later
                if (GetData(DATA_EREDAR_TWINS_EVENT) != DONE)
                    HandleGameObject(ObjectGuid::Empty, false, pGo);
                SecondGate = pGo->GetGUID();
                break;
            case 187765:    // The third gate FIXME: Always closed for now, will change later
                HandleGameObject(ObjectGuid::Empty, false, pGo);
                break;
            case 188119:
                IceBarrier = pGo->GetGUID();
                pGo->SetKeepActive(true);
                break;
            }
        }

        void ShowIceBarrier()
        {
            Map::PlayerList const& players = instance->GetPlayers();

            if (players.isEmpty())
                return;

            GameObject* barrier = instance->GetGameObject(IceBarrier);
            if (!barrier)
                return;

            for (const auto & player : players) {
                if (Player* plr = player.GetSource())
                    barrier->SendUpdateToPlayer(plr);
            }
        }

        uint32 GetData(uint32 id) const override
        {
            switch (id)
            {
            case DATA_KALECGOS_EVENT:     return Encounters[0];
            case DATA_BRUTALLUS_EVENT:    return Encounters[1];
            case DATA_FELMYST_EVENT:      return Encounters[2];
            case DATA_GAUNTLET_EVENT:     return GauntletStatus;
            case DATA_EREDAR_TWINS_EVENT: return Encounters[3];
            case DATA_MURU_EVENT:         return Encounters[4];
            case DATA_KILJAEDEN_EVENT:    return Encounters[5];
            case DATA_MURU_TO_ENTROPIUS:  return phaseEntropius;
            }
            return 0;
        }

        uint64 GetData64(uint32 id) const override
        {
            switch (id)
            {
            case DATA_KALECGOS_DRAGON:      return Kalecgos_Dragon;
            case DATA_KALECGOS_HUMAN:       return Kalecgos_Human;
            case DATA_SATHROVARR:           return Sathrovarr;
            case DATA_GO_FORCEFIELD:        return ForceField;
            case DATA_GO_KALEC_WALL_1:      return KalecgosWall[0];
            case DATA_GO_KALEC_WALL_2:      return KalecgosWall[1];
            case DATA_BRUTALLUS:            return Brutallus;
            case DATA_MADRIGOSA:            return Madrigosa;
            case DATA_FELMYST:              return Felmyst;
            case DATA_COMMANDER:            return CommanderGUID;
            case DATA_ALYTHESS:             return Alythess;
            case DATA_SACROLASH:            return Sacrolash;
            case DATA_MURU:                 return Muru;
            case DATA_BLACK_HOLE:           return BlackHole;
            case DATA_ENTROPIUS:            return Entropius;
            case DATA_KILJAEDEN:            return KilJaeden;
            case DATA_KILJAEDEN_CONTROLLER: return KilJaedenController;
            case DATA_ANVEENA:              return Anveena;
            case DATA_KALECGOS_KJ:          return KalecgosKJ;
            case MOB_FLIGHT_LEFT:           return FlightLeft;
            case MOB_FLIGHT_RIGHT:          return FlightRight;
            case DATA_PLAYER_GUID:
            {
                Player* Target = GetPlayer();
                if (!Target) TC_LOG_ERROR("scripts", "Sunwell: No target found in GetData64()!");
                return Target ? Target->GetGUID() : 0;
            }
            case DATA_GO_ICE_BARRIER:
                return IceBarrier;
            case DATA_GO_FIRE_BARRIER:
                return FireBarrier;
            }
            return 0;
        }

        void SetData(uint32 id, uint32 data) override
        {
            switch (id)
            {
            case DATA_KALECGOS_EVENT:
            {
                Encounters[0] = data;
                if (data == DONE)
                    ((InstanceMap *)instance)->PermBindAllPlayers();
            }
            break;
            case DATA_BRUTALLUS_EVENT:     Encounters[1] = data; break;
            case DATA_FELMYST_EVENT:
                /*if (data == DONE)
                    HandleGameObject(FireBarrier, true);*/
                Encounters[2] = data; break;
            case DATA_GAUNTLET_EVENT:
                GauntletStatus = data;
                if (data == IN_PROGRESS) {
                    BringersTimer = 5000;
                    FiendTimer = 2000;
                }
                break;
            case DATA_EREDAR_TWINS_EVENT:
                Encounters[3] = data;
                HandleGameObject(SecondGate, true);
                break;
            case DATA_MURU_EVENT:
                switch (data)
                {
                case DONE:
                    HandleGameObject(MurusGate[0], true);
                    HandleGameObject(MurusGate[1], true);
                    break;
                case NOT_STARTED:
                    HandleGameObject(MurusGate[0], true);
                    HandleGameObject(MurusGate[1], false);
                    break;
                }
                Encounters[4] = data; break;
            case DATA_KILJAEDEN_EVENT:     Encounters[5] = data; break;
            case DATA_ACTIVATE_NORTH_TO_LEFT:
                for (ObjectGuid & itr : northList) {
                    if (Creature *trigger = instance->GetCreature(itr)) {
                        if (trigger->GetPositionY() > data)
                            trigger->CastSpell(trigger, 45582, TRIGGERED_FULL_MASK);
                    }
                }
                break;
            case DATA_ACTIVATE_CENTER_TO_LEFT:
                for (ObjectGuid & itr : centerList) {
                    if (Creature *trigger = instance->GetCreature(itr)) {
                        if (trigger->GetPositionY() > data)
                            trigger->CastSpell(trigger, 45582, TRIGGERED_FULL_MASK);
                    }
                }
                break;
            case DATA_ACTIVATE_SOUTH_TO_LEFT:
                for (ObjectGuid & itr : southList) {
                    if (Creature *trigger = instance->GetCreature(itr)) {
                        if (trigger->GetPositionY() > data)
                            trigger->CastSpell(trigger, 45582, TRIGGERED_FULL_MASK);
                    }
                }
                break;
            case DATA_ACTIVATE_NORTH_TO_RIGHT:
                for (ObjectGuid & itr : northList) {
                    if (Creature *trigger = instance->GetCreature(itr)) {
                        if (trigger->GetPositionY() < data)
                            trigger->CastSpell(trigger, 45582, TRIGGERED_FULL_MASK);
                    }
                }
                break;
            case DATA_ACTIVATE_CENTER_TO_RIGHT:
                for (ObjectGuid & itr : centerList) {
                    if (Creature *trigger = instance->GetCreature(itr)) {
                        if (trigger->GetPositionY() < data)
                            trigger->CastSpell(trigger, 45582, TRIGGERED_FULL_MASK);
                    }
                }
                break;
            case DATA_ACTIVATE_SOUTH_TO_RIGHT:
                for (ObjectGuid & itr : southList) {
                    if (Creature *trigger = instance->GetCreature(itr)) {
                        if (trigger->GetPositionY() < data)
                            trigger->CastSpell(trigger, 45582, TRIGGERED_FULL_MASK);
                    }
                }
                break;
            case DATA_ICEBARRIER_EVENT:
                IceBarrierDone = true;
                IceBarrierTimer = 3600000;
                if (Creature* trigger = instance->GetCreature(BarrierTriggerGUID))
                    trigger->CastSpell(trigger, 47030, TRIGGERED_FULL_MASK);
                ShowIceBarrier();
                break;
            case DATA_MURU_GATE_EVENT:
                HandleGameObject(MurusGate[0], false);
                HandleGameObject(MurusGate[1], false);
                break;
            case DATA_MURU_TO_ENTROPIUS:
                phaseEntropius = data;
                break;
            }

            if (data == DONE)
                SaveToDB();
        }

        void Update(uint32 diff) override
        {
            if (!IceBarrierDone) {
                if (IceBarrierTimer <= diff) {
                    ShowIceBarrier();
                    IceBarrierTimer = 1000;
                }
                else
                    IceBarrierTimer -= diff;
            }

            /*if (felmystNorthTimer) {
                if (felmystNorthTimer <= diff) {
                    for (std::vector<uint64>::iterator itr = northList.begin(); itr != northList.end(); itr++) {
                        if (Creature *trigger = instance->GetCreature(*itr))
                            trigger->CastSpell(trigger, 45582, TRIGGERED_FULL_MASK);
                    }
                    felmystNorthTimer = 0;
                }
                else
                    felmystNorthTimer -= diff;
            }

            if (felmystCenterTimer) {
                if (felmystCenterTimer <= diff) {
                    for (std::vector<uint64>::iterator itr = centerList.begin(); itr != centerList.end(); itr++) {
                        if (Creature *trigger = instance->GetCreature(*itr))
                            trigger->CastSpell(trigger, 45582, TRIGGERED_FULL_MASK);
                    }
                    felmystCenterTimer = 0;
                }
                else
                    felmystCenterTimer -= diff;
            }

            if (felmystSouthTimer) {
                if (felmystSouthTimer <= diff) {
                    for (std::vector<uint64>::iterator itr = southList.begin(); itr != southList.end(); itr++) {
                        if (Creature *trigger = instance->GetCreature(*itr))
                            trigger->CastSpell(trigger, 45582, TRIGGERED_FULL_MASK);
                    }
                    felmystSouthTimer = 0;
                }
                else
                    felmystSouthTimer -= diff;
            }*/

            Unit* Commander = instance->GetCreature(CommanderGUID);
            if (!Commander || Commander->IsInCombat() || Commander->IsDead() || !GetAlivePlayerInMap())
                GauntletStatus = NOT_STARTED;

            if (GauntletStatus != IN_PROGRESS || GetData(DATA_EREDAR_TWINS_EVENT) == DONE) {
                BringersTimer = 40000;
                FiendTimer = 0;

                return;
            }

            if (BringersTimer <= diff) {
                float x, y, z;

                Commander->GetRandomPoint(Commander, 1.0f, x, y, z);
                if (Creature *Bringer1 = Commander->SummonCreature(MOB_SOULBINDER, x, y, z, Commander->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                    //Bringer1->Say("[DEBUG] First bringer!", LANG_UNIVERSAL);
                    Bringer1->SetKeepActive(true);
                    Bringer1->SetSpeedRate(MOVE_WALK, 3.5);
                    Bringer1->GetMotionMaster()->MovePath(25851, false); //this path is PATH_TYPE_ONCE
                }

                Commander->GetRandomPoint(Commander, 1.0f, x, y, z);
                if (Creature *Bringer2 = Commander->SummonCreature(MOB_DEATHBRINGER, x, y, z, Commander->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                    //Bringer2->Say("[DEBUG] Second bringer!", LANG_UNIVERSAL);
                    Bringer2->SetKeepActive(true);
                    Bringer2->SetSpeedRate(MOVE_WALK, 3.5);
                    Bringer2->GetMotionMaster()->MovePath(25851, false); //this path is PATH_TYPE_ONCE
                }

                BringersTimer = 80000;
            }
            else
                BringersTimer -= diff;

            if (FiendTimer <= diff) {
                float x, y, z;

                Commander->GetRandomPoint(Commander, 1.0f, x, y, z);
                if (TempSummon *Fiend = Commander->SummonCreature(CREATURE_VOLATILE_FELFIRE_FIEND, x, y, z, Commander->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                    //Fiend->MonsterSay("[DEBUG] Fiend!", LANG_UNIVERSAL, NULL);
                    Fiend->SetKeepActive(true);
                    Fiend->SetSpeedRate(MOVE_WALK, 5);
                }

                FiendTimer = 45000;
            }
            else
                FiendTimer -= diff;
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream stream;
            stream << Encounters[0] << " " << Encounters[1] << " " << Encounters[2] << " " << Encounters[3] << " "
                << Encounters[4] << " " << Encounters[5];

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
            stream >> Encounters[0] >> Encounters[1] >> Encounters[2] >> Encounters[3]
                >> Encounters[4] >> Encounters[5];
            for (uint32 & Encounter : Encounters)
                if (Encounter == IN_PROGRESS)                // Do not load an encounter as "In Progress" - reset it instead.
                    Encounter = NOT_STARTED;
            OUT_LOAD_INST_DATA_COMPLETE;
        }

        // Storage for GO-Guids and NPC-Guids
        typedef std::map<uint32, uint64> EntryGuidMap;
        EntryGuidMap m_mNpcEntryGuidStore;                  ///< Store unique NPC-Guids by entry
    };
};

void AddSC_instance_sunwell_plateau()
{
    new instance_sunwell_plateau();
}
