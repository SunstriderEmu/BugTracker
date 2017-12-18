
/* ScriptData
SDName: Instance_Shattered_Halls
SD%Complete: 90
SDComment: Loots of the Executioner should depend on the amount of prisoners killed
SDCategory: Hellfire Citadel, Shattered Halls
EndScriptData */


#include "shattered_halls.h"

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
        instance_shattered_halls_script(Map* pMap) : InstanceScript(pMap) 
        { 
            Initialize(); 

            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);
        };

        uint32 SaveIntervalTimer;
        uint32 TimerLeft;

        uint64 FirstDoorGUID;
        uint64 SecondDoorGUID;
        uint64 NethekurseGUID;
        uint64 ExecutionerGUID;

        Creature* FirstPrisoner;
        Creature* SecondPrisoner;
        Creature* ThirdPrisoner;

        uint32 const TIMER = 80 * MINUTE * IN_MILLISECONDS;
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

            TimerLeft = TIMER;

            HeroicMode = this->instance->IsHeroic();
        }

        void OnGameObjectCreate(GameObject* pGo) override
        {
            InstanceScript::OnGameObjectCreate(pGo);

            switch (pGo->GetEntry())
            {
            case GO_GRAND_WARLOCK_CHAMBER_DOOR_1:
                FirstDoorGUID = pGo->GetGUID();
                if(GetBossState(DATA_NETHEKURSE) == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            case GO_GRAND_WARLOCK_CHAMBER_DOOR_2:
                SecondDoorGUID = pGo->GetGUID();
                if (GetBossState(DATA_NETHEKURSE) == DONE)
                    HandleGameObject(0, true, pGo);
                break;
            }
        }

        void OnCreatureCreate(Creature* creature) override
        {
            InstanceScript::OnCreatureCreate(creature);

            switch (creature->GetEntry()) 
            {
            case NPC_GRAND_WARLOCK_NETHEKURSE:     // Nethekurse
                NethekurseGUID = creature->GetGUID();
                break;
            case NPC_SHATTERED_EXECUTIONER:     // Executioner
                ExecutionerGUID = creature->GetGUID();
                creature->SetKeepActive(true);
                if (GetData(DATA_NETHEKURSE) == NOT_STARTED)
                    creature->SetVisible(false);
                if (GetData(DATA_BLADEFIST) == NOT_STARTED)
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
                            plr->CastSpell(plr, spellid, true);
                }
            }
        }

        void EnableExecutioner(bool attackable)
        {
            Creature* executioner = instance->GetCreature(DATA_EXECUTIONER_GUID);
            if (!executioner)
                return;

            if (attackable)
            {
                executioner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE);
            }
            else
            {
                executioner->SetVisible(true);
                executioner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NON_ATTACKABLE);
                // TODO: Yell something ?
            }
        }

        bool SetBossState(uint32 type, EncounterState state) override
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
                case DATA_NETHEKURSE:
                if (state == DONE)
                {
                    EnableExecutioner(true);

                    HandleGameObject(FirstDoorGUID, true, nullptr);
                    HandleGameObject(SecondDoorGUID, true, nullptr);
                }
                break;
                case DATA_BLADEFIST:
                    if (state == DONE)
                        EnableExecutioner(true);
                    break;
                case DATA_EXECUTIONER:
                    if (state == IN_PROGRESS)
                        EnableExecutioner(false);
                    break;
                default:
                    break;
            }
            return true;
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case DATA_TIMER_LEFT:
                TimerLeft = data;
                break;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case DATA_TIMER_LEFT:
                return TimerLeft;
            }

            return 0;
        }

        ObjectGuid GetGuidData(uint32 data) const override
        {
            switch (data)
            {
            case GO_GRAND_WARLOCK_CHAMBER_DOOR_1:
                return FirstDoorGUID;
            case GO_GRAND_WARLOCK_CHAMBER_DOOR_2:
                return SecondDoorGUID;
            case DATA_NETHEKURSE_GUID:
                return NethekurseGUID;
            case DATA_EXECUTIONER_GUID:
                return ExecutionerGUID;
            }

            return 0;
        }

        virtual void ReadSaveDataMore(std::istringstream& data) 
        { 
            data >> TimerLeft;

            if(TimerLeft > TIMER)
                SetBossState(DATA_EXECUTIONER, IN_PROGRESS);
        }

        virtual void WriteSaveDataMore(std::ostringstream& data) 
        { 
            data << TimerLeft;
        }

        // Update is only needed in Heroic, for the timer
        void Update(uint32 diff) override
        {
            if (!HeroicMode)
                return;

            // If Executioner is dead and some prisoners are still alive, reward players for quest
            /*if (Executioner && Executioner->IsDead() && GetBossState(DATA_EXECUTIONER) != DONE) {
                if ( (FirstPrisoner && FirstPrisoner->IsAlive()) || (SecondPrisoner && SecondPrisoner->IsAlive()) || (ThirdPrisoner && ThirdPrisoner->IsAlive()) ) {
                    RewardAllPlayersInMapForQuest();
                    SetBossState(DATA_EXECUTIONER, DONE);
                }
            }*/

            if (GetBossState(DATA_EXECUTIONER) != IN_PROGRESS)
                return;

            // Decrease timer at each update
            TimerLeft -= diff;

            if (!hasCasted80min) 
            {      // Event just started
                // TODO: Correct this [PH] yell
                if (Creature *Executioner = instance->GetCreature(ExecutionerGUID))
                    if (Executioner->IsInWorld())
                        Executioner->YellToMap("[PH] I got three hostages! In 55 minutes, I will kill the first one!");

                CastSpellOnAllPlayersInMap(SPELL_KARGATH_EXECUTIONER_1);
                Player* plr = GetPlayer();
                if (!plr) 
                {
                    TC_LOG_ERROR("scripts", "Instance Shattered Halls: Update: No player found in map when event started !");
                    return;
                }
                //SpawnPrisoners(plr->GetTeam(), 3);
                hasCasted80min = true;
            }

            if (TimerLeft < 25 * MINUTE * IN_MILLISECONDS && !hasCasted25min)
            {
                // TODO: Correct this [PH] yell
                if (Creature *Executioner = instance->GetCreature(ExecutionerGUID))
                    if (Executioner->IsInWorld())
                        Executioner->YellToMap("[PH] The first hostage is dead! In 10 minutes, I will kill a second!", LANG_UNIVERSAL);

                CastSpellOnAllPlayersInMap(GetData(SPELL_KARGATH_EXECUTIONER_2));      // 2nd timer of 10 mins
                /*if (FirstPrisoner && Executioner)
                    Executioner->DealDamage(FirstPrisoner, FirstPrisoner->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);*/
                hasCasted25min = true;
            }

            if (TimerLeft < 15 * MINUTE * IN_MILLISECONDS && !hasCasted15min) 
            {
                // TODO: Correct this [PH] yell
                if (Creature *Executioner = instance->GetCreature(ExecutionerGUID))
                    if (Executioner->IsInWorld())
                        Executioner->YellToMap("[PH] I killed the second hostage! In fifteen minutes, I will kill the last.");

                CastSpellOnAllPlayersInMap(GetData(SPELL_KARGATH_EXECUTIONER_3));      // 3rd (and last) timer of 15 mins
                /*if (SecondPrisoner && Executioner)
                    Executioner->DealDamage(SecondPrisoner, SecondPrisoner->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);*/
                hasCasted15min = true;
            }

            if (TimerLeft < diff) 
            {     // TIME UP ! Kill the third prisoner and stop the timer, killing executioner won't give the quest item
                // TODO: Correct this [PH] yell
                if (Creature *Executioner = instance->GetCreature(ExecutionerGUID)) {
                    if (Executioner->IsInWorld()) 
                    {
                        Executioner->YellToMap("[PH] You're too late! I killed them all.");
                        Executioner->loot.RemoveItem(31716);
                    }
                }
                /*if (ThirdPrisoner && Executioner)
                    Executioner->DealDamage(ThirdPrisoner, ThirdPrisoner->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);*/
                SetBossState(DATA_EXECUTIONER, FAIL);
            }

            // Save time left in DB every 30 sec
            if (SaveIntervalTimer <= diff) 
            {
                SetData(DATA_TIMER_LEFT, TimerLeft);
                SaveToDB();
                SaveIntervalTimer = 30 * MINUTE * IN_MILLISECONDS;
            } else 
                SaveIntervalTimer -= diff;
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
        if (InstanceScript* pInstance = ((InstanceScript*)pPlayer->GetInstanceScript())) 
        {
            if (pInstance->GetBossState(DATA_EXECUTIONER) == NOT_STARTED)
            {
                pInstance->SetBossState(DATA_EXECUTIONER, IN_PROGRESS);
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

