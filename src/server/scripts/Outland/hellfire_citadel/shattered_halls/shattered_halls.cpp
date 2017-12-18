#include "shattered_halls.h"

// AreaTrigger that starts the timed event
class ATShatteredHalls : AreaTriggerScript
{
public:
    ATShatteredHalls() : AreaTriggerScript("at_shattered_halls") {}

    bool OnTrigger(Player* player, AreaTriggerEntry const* at) override
    {
        if (InstanceScript* is = player->GetInstanceScript())
        {
            if (is->instance->IsHeroic())
            {
                Creature* executioner = nullptr;

                is->instance->LoadGrid(Executioner.GetPositionX(), Executioner.GetPositionY());
                if (Creature* kargath = ObjectAccessor::GetCreature(*player, is->GetGuidData(NPC_KARGATH_BLADEFIST)))
                {
                    if (is->GetGuidData(NPC_SHATTERED_EXECUTIONER).IsEmpty() && is->GetBossState(DATA_KARGATH) != DONE)
                    {
                        executioner = kargath->SummonCreature(NPC_SHATTERED_EXECUTIONER, Executioner);
                        kargath->AI()->DoAction(ACTION_EXECUTIONER_TAUNT);
                    }
                }

                if (executioner)
                    for (uint8 i = 0; i < VictimCount; ++i)
                    {
                        if (Creature* victim = executioner->SummonCreature(executionerVictims[i](is->GetData(DATA_TEAM_IN_INSTANCE)), executionerVictims[i].GetPos()))
                            victim->SetImmuneToAll(true);
                    }
            }
        }

        return false;
    }
};


enum Spells
{
    SPELL_CLEAVE = 15284
};

class boss_shattered_executioner : public CreatureScript
{
public:
    boss_shattered_executioner() : CreatureScript("boss_shattered_executioner") { }

    struct boss_shattered_executionerAI : public BossAI
    {
        boss_shattered_executionerAI(Creature* creature) : BossAI(creature, DATA_SHATTERED_EXECUTIONER)
        {
            Initialize();
        };

        void Initialize()
        {
            cleaveTimer = 500;
        }

        void Reset() override
        {
            _Reset();

            // _Reset() resets the loot mode, so we add them again, if any
            /*
            uint32 prisonersExecuted = instance->GetData(DATA_PRISONERS_EXECUTED);
            if (prisonersExecuted == 0)
                me->AddLootMode(LOOT_MODE_HARD_MODE_3);
            if (prisonersExecuted <= 1)
                me->AddLootMode(LOOT_MODE_HARD_MODE_2);
            if (prisonersExecuted <= 2)
            {
                //me->AddLootMode(LOOT_MODE_HARD_MODE_1);
                me->loot.RemoveItem(31716);
             }
            */

            if (instance->GetBossState(DATA_KARGATH) == DONE)
                me->SetImmuneToPC(false);
            else
                me->SetImmuneToPC(true);

            Initialize();
        }

        void JustSummoned(Creature*) override { } // avoid despawn of prisoners on death/reset

        void JustDied(Unit*) override
        {
            _JustDied();

            if (instance->GetData(DATA_PRISONERS_EXECUTED) > 0)
                return;

            Map::PlayerList const& players = instance->instance->GetPlayers();
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
            {
                Player* pl = itr->GetSource();
                uint32 qId = pl->GetTeam() == ALLIANCE ? QUEST_IMPRISONED_A : QUEST_IMPRISONED_H;
                if (pl->GetQuestStatus(qId) == QUEST_STATUS_INCOMPLETE)
                    pl->CompleteQuest(qId);
            }
        }

        void SetData(uint32 type, uint32 data, Unit* setter) override
        {
            if (type == DATA_PRISONERS_EXECUTED && data <= 3)
            {
                if (Creature* victim = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_FIRST_PRISONER + data - 1)))
                    me->Kill(victim);

                if (data == 1)
                {
                    Map::PlayerList const& players = instance->instance->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                    {
                        Player* pl = itr->GetSource();
                        uint32 qId = pl->GetTeam() == ALLIANCE ? QUEST_IMPRISONED_A : QUEST_IMPRISONED_H;
                        if (pl->GetQuestStatus(qId) == QUEST_STATUS_INCOMPLETE)
                            pl->FailQuest(qId);
                    }
                }

                switch (data)
                {
                case 3:
                    //me->RemoveLootMode(LOOT_MODE_HARD_MODE_1);
                    me->YellToMap("[PH] You're too late! I killed them all.");
                    me->loot.RemoveItem(31716);
                case 2:
                    //me->RemoveLootMode(LOOT_MODE_HARD_MODE_2);
                    me->YellToMap("[PH] I killed the second hostage! In fifteen minutes, I will kill the last.");
                case 1:
                    //me->RemoveLootMode(LOOT_MODE_HARD_MODE_3);
                    me->YellToMap("[PH] The first hostage is dead! In 10 minutes, I will kill a second!", LANG_UNIVERSAL);
                default:
                    break;
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (cleaveTimer <= diff)
            {
                DoCastVictim(SPELL_CLEAVE);
                cleaveTimer = urand(5000, 7000);
            }
            else
                cleaveTimer -= diff;

            DoMeleeAttackIfReady();
        }
    private:
        uint32 cleaveTimer;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetShatteredHallsAI<boss_shattered_executionerAI>(creature);
    }
};


void AddSC_shattered_halls()
{
    new ATShatteredHalls();
    new boss_shattered_executioner();
}

