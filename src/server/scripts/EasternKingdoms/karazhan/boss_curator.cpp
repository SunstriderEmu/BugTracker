/* ScriptData
SDName: Boss_Curator
SD%Complete: 95
SDComment: Need to check timers.
SDCategory: Karazhan
EndScriptData */

#include "karazhan.h"

enum CuratorData
{
    // Texts
    SAY_AGGRO                       = -1532057,
    SAY_SUMMON1                     = -1532058,
    SAY_SUMMON2                     = -1532059,
    SAY_EVOCATE                     = -1532060,
    SAY_ENRAGE                      = -1532061,
    SAY_KILL1                       = -1532062,
    SAY_KILL2                       = -1532063,
    SAY_DEATH                       = -1532064,

    // Spells
    // -- Curator
    SPELL_HATEFUL_BOLT              = 30383,
    SPELL_EVOCATION                 = 30254,
    SPELL_ENRAGE                    = 30403,    // Arcane Infusion: Transforms Curator and adds damage.
    SPELL_BERSERK                   = 26662,

    // -- Astral Flare
    SPELL_ASTRAL_FLARE_PASSIVE      = 30234,    // Visual effect + Flare damage
    SPELL_ASTRAL_FLARE_VISUAL       = 30237,
//    SPELL_ASTRAL_FLARE_NE           = 30236,    // Not in DBC
//    SPELL_ASTRAL_FLARE_NW           = 30239,    // Not in DBC
//    SPELL_ASTRAL_FLARE_SE           = 30240,    // Not in DBC
//    SPELL_ASTRAL_FLARE_SW           = 30241,    // Not in DBC

    // Creatures
    NPC_ASTRAL_FLARE                = 17096
};

class boss_curator : public CreatureScript
{
  public:
    boss_curator() : CreatureScript("boss_curator") { }

    class boss_curatorAI : public BossAI
    {
      public:
        boss_curatorAI(Creature* creature) : BossAI(creature, DATA_CURATOR_EVENT), _infused(false)
        {
        }

        enum CuratorEvents
        {
            EVENT_FLARE_SUMMON = 1,
            EVENT_HATEFUL_BOLT,
            EVENT_BERSERK
        };

        enum CuratorPhases
        {
            PHASE_NORMAL = 1,
            PHASE_ENRAGED,
        };

        void Reset()
        override {
            _Reset();
            _infused = false;

            events.Reset();
            events.RescheduleEvent(EVENT_FLARE_SUMMON, 10 * IN_MILLISECONDS, PHASE_NORMAL);
            events.RescheduleEvent(EVENT_HATEFUL_BOLT, 15 * IN_MILLISECONDS, PHASE_NORMAL);
            events.RescheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS, PHASE_NORMAL);

            me->SetFullTauntImmunity(true);
            me->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_ARCANE, true);
        }

        void KilledUnit(Unit* /*victim*/)
        override 
        {
            switch (rand()%2)
            {
                case 0: DoScriptText(SAY_KILL1, me); break;
                case 1: DoScriptText(SAY_KILL2, me); break;
            }
        }

        void JustDied(Unit* /*killer*/) 
        override {
            _JustDied();
            DoScriptText(SAY_DEATH, me);
        }
        
        void EnterCombat(Unit* /*victim*/)
        override {
            _EnterCombat();
            DoScriptText(SAY_AGGRO, me);
            DoZoneInCombat();
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
        override {
            if(me->HealthBelowPct(15) && !_infused)
            {
                _infused = true;
                events.SetPhase(PHASE_ENRAGED);

                me->InterruptNonMeleeSpells(false);
                me->CastSpell(me, SPELL_ENRAGE);
                DoScriptText(SAY_ENRAGE, me);
            }
        }

        void ExecuteEvent(uint32 eventId) override
        {
            switch(eventId)
            {
                case 0:
                    break;
                case EVENT_BERSERK:
                {
                    if (me->CastSpell(me, SPELL_BERSERK) == SPELL_CAST_OK)
                        events.RescheduleEvent(EVENT_BERSERK, 1 * MINUTE * IN_MILLISECONDS);
                    break;
                }
                case EVENT_FLARE_SUMMON:
                {
                    // Summon Astral Flare
                    me->SummonCreature(NPC_ASTRAL_FLARE, me->GetPositionX() + rand()%37, me->GetPositionY() + rand()%37, me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5 * IN_MILLISECONDS);

                    // reduce mana by 10% of maximum
                    if (int32 iMana = me->GetMaxPower(POWER_MANA))
                    {
                        me->ModifyPower(POWER_MANA, -(iMana / 10));

                        // if this get's us below 10%, then we evocate (the 10th should be summoned now
                        if (me->GetPower(POWER_MANA) * 10 < me->GetMaxPower(POWER_MANA))
                        {
                            me->InterruptNonMeleeSpells(false);
                            if (DoCastSelf(SPELL_EVOCATION) == SPELL_CAST_OK)
                            {
                                DoScriptText(SAY_EVOCATE, me);
                                // this small delay should make next flare appear fast after evocate
                                events.RescheduleEvent(EVENT_FLARE_SUMMON, 1 * IN_MILLISECONDS, PHASE_NORMAL);
                            }

                            return;
                        }
                        else
                        {
                            switch (urand(0, 3))
                            {
                                case 0: DoScriptText(SAY_SUMMON1, me); break;
                                case 1: DoScriptText(SAY_SUMMON2, me); break;
                            }
                        }
                    }
                    events.RescheduleEvent(EVENT_FLARE_SUMMON, 10 * SECOND * IN_MILLISECONDS, PHASE_NORMAL);
                    break;
                }
                case EVENT_HATEFUL_BOLT:
                {
                    Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 1);
                    if (target)
                        if(me->CastSpell(target, SPELL_HATEFUL_BOLT) == SPELL_CAST_OK)
                            events.RescheduleEvent(EVENT_HATEFUL_BOLT, 15 * IN_MILLISECONDS, PHASE_NORMAL);
                    break;
                }
                default:
                    break;
            }
        }

      private:
        bool _infused;
    };
    
    CreatureAI* GetAI(Creature* creature) const
    override 
    {
        return GetKarazhanAI<boss_curatorAI>(creature);
    }
};

class npc_curator_astral_flare : public CreatureScript
{
public:
    npc_curator_astral_flare() : CreatureScript("npc_curator_astral_flare") { }

    struct npc_curator_astral_flareAI : public ScriptedAI
    {
        npc_curator_astral_flareAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void Reset() override
        {
            // Flare start with aggro on it's target, should be immune to arcane
            me->CastSpell(me, SPELL_ASTRAL_FLARE_PASSIVE, true);
            me->CastSpell(me, SPELL_ASTRAL_FLARE_VISUAL, true);
            me->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_ARCANE, true);

            _scheduler.Schedule(Seconds(2), [this](TaskContext /*context*/)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                DoZoneInCombat();
            });
        }

        void UpdateAI(uint32 diff) override
        {
            _scheduler.Update(diff);
            UpdateVictim();
            //no melee
        }

    private:
        TaskScheduler _scheduler;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<npc_curator_astral_flareAI>(creature);
    }
};

void AddSC_boss_curator()
{
    new boss_curator();
    new npc_curator_astral_flare();
}

