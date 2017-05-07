#include "def_black_temple.h"
#include "Spell.h"

enum ReliquaryOfSoulsData {
    // Essence of Suffering
    TALK_SUFF_SAY_FREED             = 0,
    TALK_SUFF_SAY_AGGRO             = 1,
    TALK_SUFF_SAY_SLAY              = 2,
    TALK_SUFF_SAY_RECAP             = 3,
    TALK_SUFF_SAY_AFTER             = 4,
    TALK_SUFF_EMOTE_ENRAGE          = 5,
    // Essence of Desire
    TALK_DESI_SAY_FREED             = 0,
    TALK_DESI_SAY_SLAY              = 1,
    TALK_DESI_SAY_SPEC              = 2,
    TALK_DESI_SAY_RECAP             = 3,
    TALK_DESI_SAY_AFTER             = 4,
    // Essence of Anger
    TALK_ANGER_SAY_FREED            = 0,
    TALK_ANGER_SAY_SLAY             = 1,
    TALK_ANGER_SAY_SPEC             = 2,
    TALK_ANGER_SAY_BEFORE           = 3,
    TALK_ANGER_SAY_DEATH            = 4,
    
    // Spells
    SPELL_SUMMON_SOUL               = 41537, // trigger 41538
    SPELL_SUMMON_SOUL2              = 41538, // actual summoning

    AURA_OF_SUFFERING               = 41292,
    AURA_OF_SUFFERING_ARMOR         = 42017, // linked aura, need core support
    ESSENCE_OF_SUFFERING_PASSIVE    = 41296, // periodic trigger 41294
    ESSENCE_OF_SUFFERING_PASSIVE2   = 41623,
    SPELL_FIXATE_TARGET             = 41294, // dummy, select target
    SPELL_FIXATE_TAUNT              = 41295, // force taunt
    SPELL_ENRAGE                    = 41305,
    SPELL_SOUL_DRAIN                = 41303,

    AURA_OF_DESIRE                  = 41350,
    AURA_OF_DESIRE_DAMAGE           = 41352,
    SPELL_RUNE_SHIELD               = 41431,
    SPELL_DEADEN                    = 41410,
    SPELL_SOUL_SHOCK                = 41426,

    AURA_OF_ANGER                   = 41337,
    SPELL_SELF_SEETHE               = 41364, // force cast 41520
    SPELL_ENEMY_SEETHE              = 41520,
    SPELL_SOUL_SCREAM               = 41545,
    SPELL_SPITE_TARGET              = 41376, // cast 41377 after 6 sec
    SPELL_SPITE_DAMAGE              = 41377,

    ENSLAVED_SOUL_PASSIVE           = 41535,
    SPELL_SOUL_RELEASE              = 41542,
    SPELL_SUBMERGE                  = 37550, //dropout 'head'
    SPELL_SELFSTUN                  = 53088, //2.5s stun
    
    // Misc
    CREATURE_ENSLAVED_SOUL          = 23469,
    NUMBER_ENSLAVED_SOUL            = 15,
    DATA_SOUL_DEATH                 = 0,
    DATA_SOUL_SPAWN                 = 1,
    DATA_ESSENCE_OF_ANGER_DEATH     = 2,

    CREATURE_RIFT_MARKER            = 23472,
    
    // Phases
    PHASE_NONE                      = 0,
    PHASE_SUFFERING                 = 1,
    PHASE_DESIRE                    = 2,
    PHASE_ANGER                     = 3
};

class Boss_reliquary_of_souls : public CreatureScript
{
public:
    Boss_reliquary_of_souls() : CreatureScript("boss_reliquary_of_souls") {}
    
    class Boss_reliquary_of_soulsAI : public ScriptedAI
    {
    public:
        Boss_reliquary_of_soulsAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = ((InstanceScript*)creature->GetInstanceScript());
            essenceGUID = 0;
            phase = PHASE_NONE;
            step = 0;
            timer = 0;
            SetCombatMovementAllowed(false);
        }
        
        Creature* getRandomRift()
        {
            if(riftMarkers.size() == 0)
                return nullptr;

            auto itr = riftMarkers.begin();
            std::advance(itr, urand(0, riftMarkers.size() - 1));

            return me->GetMap()->GetCreature(*itr);
        }

        void findRifts()
        {
            riftMarkers.clear();

            std::list<Creature*> RiftList;

            Trinity::AllCreaturesOfEntryInRange check(me, CREATURE_RIFT_MARKER, 75.0f);
            Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, RiftList, check);
            me->VisitNearbyGridObject(75.0f, searcher);

            for(auto itr : RiftList)
                riftMarkers.push_back(itr->GetGUID());

            if(riftMarkers.size() == 0)
                TC_LOG_ERROR("FIXME","Reliquary of Souls : Cannot find any rifts markers.");
        }

        void Reset()
        override {
            if (instance && instance->GetData(DATA_RELIQUARYOFSOULSEVENT) != DONE)
                instance->SetData(DATA_RELIQUARYOFSOULSEVENT, NOT_STARTED);

            if (essenceGUID != 0) {
                Creature* essence = ObjectAccessor::GetCreature(*me, essenceGUID);
                if (essence)
                    essence->DisappearAndDie();
                    
                essenceGUID = 0;
            }

            phase = PHASE_NONE;
            
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
            me->RemoveAurasDueToSpell(SPELL_SUBMERGE);
            
            if (instance)
                instance->RemoveAuraOnAllPlayers(SPELL_ENEMY_SEETHE);
                
            //me->SetNoCallAssistance(true);
        }
        
        void EnterCombat(Unit* victim)
        override {
            if(riftMarkers.size() == 0) findRifts();
            me->AddThreat(victim, 10000.0f);
            DoZoneInCombat();
            
            if (instance)
                instance->SetData(DATA_RELIQUARYOFSOULSEVENT, IN_PROGRESS);
                
            phase = PHASE_SUFFERING;
            step = 0;
            timer = 0;
        }
        
        void summonSoul()
        {
            Creature* rift = getRandomRift();

            if(rift)
                rift->CastSpell(rift,SPELL_SUMMON_SOUL2,true,nullptr,nullptr,me->GetGUID());
        }

        void JustDied(Unit* killer)
        override {
            if (instance) {
                instance->SetData(DATA_RELIQUARYOFSOULSEVENT, DONE);
                instance->RemoveAuraOnAllPlayers(SPELL_ENEMY_SEETHE);
            }
        }
        
        uint64 message(uint32 id, uint64 data)
        override {
            switch(id)
            {
            case DATA_SOUL_DEATH:
                if(data == 1)
                    soulDeathCount++;;
                break;
            case DATA_SOUL_SPAWN:
                {
                soulCount++;
                Creature* soul = me->GetMap()->GetCreature(MAKE_NEW_GUID(data, CREATURE_ENSLAVED_SOUL, HighGuid::Unit));
                if (soul)
                {
                    Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,200.0f,true);
                    if(target)
                    {
                        soul->AI()->AttackStart(target);
                        soul->AddThreat(target, 1500.0f);
                    }
                }
                }
                break;
            case DATA_ESSENCE_OF_ANGER_DEATH:
                me->CastSpell(me, 7, true); //suicide
                break;
            }
            return 0;
        }
        
        void MoveInLineOfSight(Unit* who)
        override {
            if (!me->IsInCombat() && who->ToPlayer() && who->GetDistance(me) <= 75.0f)
                AttackStart(who);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (phase == PHASE_NONE)
                return;
                
            if (me->getThreatManager().getThreatList().empty()) {
                EnterEvadeMode();
                return;
            }
            
			Creature* essence = nullptr;
            if (essenceGUID != 0) {
                essence = ObjectAccessor::GetCreature(*me, essenceGUID);
            }

			if (!essence) {
				EnterEvadeMode();
				return;
			}

            if (timer <= diff) {
                switch (step) {
                case 0:
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    timer = 3000;
                    break;
                case 1: //open ribs
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_SUBMERGE);
                    me->CastSpell(me, SPELL_SUBMERGE);
                    timer = 2500; //2800 avant
                    break;
                case 2: //summon essence
                    if (Creature* summon = me->SummonCreature(23417 + phase, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0)) {
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_SUBMERGED);
                        if (summon->AI()) {
                            //summon->getAI()->attackStart(SelectTarget(SELECT_TARGET_TOPAGGRO, 0));
                            Unit* target = SelectTarget(SELECT_TARGET_NEAREST,0,200.0f,true);
                            summon->AI()->AttackStart(target);
                            essenceGUID = summon->GetGUID();
                            summon->SetSummoner(me);
                            me->GetMotionMaster()->MoveIdle();
                        }
                    }
                    else
                        EnterEvadeMode();
                    timer = 5000;
                    break;
                case 3: // wait for essence to be done or die if this was last essence
                    if(phase == PHASE_ANGER)
                        return;

                    if (!essence->IsAlive()) //debugging purpose for now
                    {
                        TC_LOG_ERROR("scripts","RoS : Essence is dead (phase = %u), skipping animation",phase);
                        step = 5; //goto despawn essence
                        return;
                    }
                    if (essence->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE)) {
                        //mergeThreatList(essence);
                        essence->DeleteThreatList();
                        essence->SetReactState(REACT_PASSIVE);
                        essence->GetMotionMaster()->MoveFollow(me, 0, 0);
                    }
                    else
                        return;
                    timer = 1000;
                    break;
                case 4: // wait for essence to reach me & close ribs
                    timer = 500;
                    if (essence->IsWithinDistInMap(me, 10.0f)) {
                        timer = 2000;
                        me->RemoveAurasDueToSpell(SPELL_SUBMERGE);
                        essence->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_SUBMERGE); // Rotate and disappear
                    }
                    else { // Really necessary?
                        //mergeThreatList(essence);
                        essence->DeleteThreatList();
                        essence->SetReactState(REACT_PASSIVE);
                        essence->GetMotionMaster()->MoveFollow(me, 0, 0);
                        return;
                    }
                    break;
                case 5: //despawn essence
                    if (phase == PHASE_SUFFERING) {
                        essence->AI()->Talk(TALK_SUFF_SAY_AFTER);
                    }
                    else {
                        essence->AI()->Talk(TALK_DESI_SAY_AFTER);
                    }
                    
                    essence->SetVisibility(VISIBILITY_OFF);
                    essence->SetDeathState(DEAD);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                    essenceGUID = 0;
                    soulCount = 0;
                    soulDeathCount = 0;
                    timer = 3000;
                    break;
                case 6: //summon souls
                    if (soulCount < NUMBER_ENSLAVED_SOUL-2) {
                        for(uint8 i = 0; i < 3; i++)
                            summonSoul();
                            
                        timer = 3000;
                        return;
                    }
                    break;
                case 7: //wait for souls deaths to continue to next phase
                    if (soulDeathCount >= soulCount) {
                        step = 1;
                        phase++;
                        timer = 5000;
                    }
                    return;
                default:
                    break;
                }
                
                step++;
            }
            else
                timer -= diff;
        }
        
        
    private:
        InstanceScript* instance;
        std::list<uint64> riftMarkers;

        uint64 essenceGUID;
        
        uint32 timer;
        uint32 soulCount;
        uint32 soulDeathCount;
        
        uint8 phase;
        uint8 step;
    };
    
    CreatureAI* GetAI(Creature* creature) const
    override {
        return new Boss_reliquary_of_soulsAI(creature);
    }
};

//Phase 1
class Boss_essence_of_suffering : public CreatureScript
{
public:
    Boss_essence_of_suffering() : CreatureScript("boss_essence_of_suffering") {}
    
    class Boss_essence_of_sufferingAI : public ScriptedAI
    {
    public:
        Boss_essence_of_sufferingAI(Creature* creature) : ScriptedAI(creature) {}
        
        enum events {
            EV_FIXATE       = 1,
            EV_ENRAGE       = 2,
            EV_SOUL_DRAIN   = 3
        };
        
        EventMap events;

        void Reset()
        override {
            events.RescheduleEvent(EV_FIXATE, 8000);
            events.RescheduleEvent(EV_ENRAGE, 45000);
            events.RescheduleEvent(EV_SOUL_DRAIN, 20000);
            
            me->SetFullTauntImmunity(true);
            //me->SetNoCallAssistance(true);
        }
        
        void EnterEvadeMode(EvadeReason why)
        override {
            if (Creature* reliquary = me->GetSummoner()->ToCreature())
                reliquary->AI()->EnterEvadeMode(why);
                
            CreatureAI::EnterEvadeMode(why);
        }
        
        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        override {
            if (damage >= me->GetHealth()) {
                damage = 0;
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAllAuras();
                Talk(TALK_SUFF_SAY_RECAP);
            }
        }
        
        void EnterCombat(Unit* victim)
        override {
            Talk(TALK_SUFF_SAY_FREED);
            DoZoneInCombat();
            me->CastSpell(me, AURA_OF_SUFFERING, true);
            me->CastSpell(me, ESSENCE_OF_SUFFERING_PASSIVE, true);
            me->CastSpell(me, ESSENCE_OF_SUFFERING_PASSIVE2, true);
        }
        
        void JustDied(Unit* victim)
        override {
            Talk(TALK_SUFF_SAY_SLAY);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                return;

            if (!UpdateVictim())
                return;
                
            events.Update(diff);
            
            switch (events.GetEvent())
            {
                case EV_FIXATE:
                {
                    Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 30.0f, true);

                    if (target) {
                        target->CastSpell(me, SPELL_FIXATE_TAUNT, true);
                        DoResetThreat();
                        me->AddThreat(target, 1000000.0f);
                        
                        if ((rand() % 16) == 0)
                            Talk(TALK_SUFF_SAY_AGGRO);
                    }
                    
                    events.RescheduleEvent(EV_FIXATE, 5000);
                    break;
                }
                case EV_ENRAGE:
                    if (me->CastSpell(me, SPELL_ENRAGE) == SPELL_CAST_OK)
                    {
                        Talk(TALK_SUFF_EMOTE_ENRAGE);
                        events.RescheduleEvent(EV_ENRAGE, 30000);
                    }
                    break;
                case EV_SOUL_DRAIN:
                    if(me->CastSpell(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_SOUL_DRAIN) == SPELL_CAST_OK)
                        events.RescheduleEvent(EV_SOUL_DRAIN, 20000);
                    break;
            }
            
            DoMeleeAttackIfReady();
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const
    override {
        return new Boss_essence_of_sufferingAI(creature);
    }
};

//Phase 2
class Boss_essence_of_desire : public CreatureScript
{
public:
    Boss_essence_of_desire() : CreatureScript("boss_essence_of_desire") {}
    
    class Boss_essence_of_desireAI : public ScriptedAI
    {
    public:
        Boss_essence_of_desireAI(Creature* creature) : ScriptedAI(creature) {}
        
        //Debugging 
        void JustDied(Unit* killer) 
        override {
            TC_LOG_ERROR("scripts","essence of desire died killed by a %s (guid : %u)",killer->ToCreature() ? "creature" : "player",killer->GetGUIDLow());
        }

        enum events {
            EV_RUNE_SHIELD  = 1,
            EV_DEADEN       = 2,
            EV_SOUL_SHOCK   = 3
        };
        
        EventMap events;

        void Reset()
        override {
            events.RescheduleEvent(EV_RUNE_SHIELD, 12000);
            events.RescheduleEvent(EV_DEADEN, 25000);
            events.RescheduleEvent(EV_SOUL_SHOCK, 6000);
            
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_CONFUSE, true);
           // me->SetNoCallAssistance(true);
        }
        
        void EnterEvadeMode(EvadeReason why)
        override {
            if (Creature* reliquary = me->GetSummoner()->ToCreature())
                reliquary->AI()->EnterEvadeMode(why);
                
            CreatureAI::EnterEvadeMode(why);
        }
        
        void DamageTaken(Unit* attacker, uint32& damage)
        override {
            if (damage >= me->GetHealth()) {
                damage = 0;
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAllAuras();
                Talk(TALK_DESI_SAY_RECAP);
            }
            else {
                int32 bp0 = damage / 2;
                me->CastCustomSpell(attacker, AURA_OF_DESIRE_DAMAGE, &bp0, nullptr, nullptr, true);
            }
        }
        
        void SpellHit(Unit* caster, SpellInfo const* spell)
        override {
            if (me->m_currentSpells[CURRENT_GENERIC_SPELL]) 
            {
                for (const auto & Effect : spell->Effects) 
                {
                    if (Effect.Effect == SPELL_EFFECT_INTERRUPT_CAST) 
                    {
                        if (me->m_currentSpells[CURRENT_GENERIC_SPELL]->m_spellInfo->Id == SPELL_SOUL_SHOCK
                                || me->m_currentSpells[CURRENT_GENERIC_SPELL]->m_spellInfo->Id == SPELL_DEADEN)
                            me->InterruptSpell(CURRENT_GENERIC_SPELL, false);
                    }
                }
            }
        }
        
        void EnterCombat(Unit* victim)
        override {
            Talk(TALK_DESI_SAY_FREED);
            DoZoneInCombat();
            me->CastSpell(me, AURA_OF_DESIRE, true);
        }
        
        void KilledUnit(Unit* victim)
        override {
            Talk(TALK_DESI_SAY_SLAY);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                return;

            if (!UpdateVictim())
                return;
                
            events.Update(diff);
            
            switch (events.GetEvent())
            {
                case 0:
                    break;
                case EV_RUNE_SHIELD:
                    if (me->CastSpell(me, SPELL_RUNE_SHIELD, true) == SPELL_CAST_OK)
                    {
                        events.SetMinimalDelay(EV_SOUL_SHOCK, 2000);
                        events.SetMinimalDelay(EV_DEADEN, 2000);
                        events.RescheduleEvent(EV_RUNE_SHIELD, 15000);
                    }
                    break;
                case EV_SOUL_SHOCK:
                    if(me->CastSpell(me->GetVictim(), SPELL_SOUL_SHOCK) == SPELL_CAST_OK)
                        events.RescheduleEvent(EV_SOUL_SHOCK, 6000);
                    break;
                case EV_DEADEN:
                    if (me->CastSpell(me->GetVictim(), SPELL_DEADEN) == SPELL_CAST_OK)
                    {
                        events.RescheduleEvent(EV_DEADEN, 30000);
                        if ((rand() % 2) == 0)
                            Talk(TALK_DESI_SAY_SPEC);
                    }
                    break;
            }
            
            DoMeleeAttackIfReady();
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const
    override {
        return new Boss_essence_of_desireAI(creature);
    }
};

//Phase 3
class Boss_essence_of_anger : public CreatureScript
{
public:
    Boss_essence_of_anger() : CreatureScript("boss_essence_of_anger") {}
    
    class Boss_essence_of_angerAI : public ScriptedAI
    {
    public:
        Boss_essence_of_angerAI(Creature* creature) : ScriptedAI(creature)
        { }
        
        enum events {
            EV_CHECK_TANK   = 1,
            EV_SOUL_SCREAM  = 2,
            EV_SPITE        = 3
        };
        
        EventMap events;

        void Reset()
        override {
            events.RescheduleEvent(EV_CHECK_TANK, 3000);
            events.RescheduleEvent(EV_SOUL_SCREAM, 10000);
            events.RescheduleEvent(EV_SPITE, 20000);
            
            tankGUID = 0;
            spiteGUIDs.clear();
            //me->SetNoCallAssistance(true);
        }
        
        void EnterEvadeMode(EvadeReason why)
        override {
            if (Creature* reliquary = me->GetSummoner()->ToCreature())
                reliquary->AI()->EnterEvadeMode(why);
                
            CreatureAI::EnterEvadeMode(why);
        }
        
        void EnterCombat(Unit* victim)
        override {
            tankGUID = victim->GetGUID();
            victim->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SPITE_TARGET, true); //else we would change target if it's casted on him
            
            Talk(TALK_ANGER_SAY_FREED);
            DoZoneInCombat();
            me->CastSpell(me, AURA_OF_ANGER, true);
        }
        
        void JustDied(Unit* killer)
        override {
            Player* tank = ObjectAccessor::GetPlayer(*me,tankGUID);
            if(tank) tank->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SPITE_TARGET, false);
            Talk(TALK_ANGER_SAY_DEATH);

            if (Creature* reliquary = me->GetSummoner()->ToCreature())
                reliquary->AI()->message(DATA_ESSENCE_OF_ANGER_DEATH, 0);
        }
        
        void KilledUnit(Unit* victim)
        override {
            Talk(TALK_ANGER_SAY_SLAY);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                return;

            if (!UpdateVictim())
                return;
                
            events.Update(diff);
            
            switch (events.GetEvent())
            {
                case 0:
                    break;
                case EV_CHECK_TANK:
                    if (me->GetVictim() && me->GetVictim()->GetGUID() != tankGUID) {
                        if (me->CastSpell(me, SPELL_SELF_SEETHE, true) == SPELL_CAST_OK)
                        {
                            Talk(TALK_ANGER_SAY_BEFORE);
                            tankGUID = me->GetVictim()->GetGUID();
                        }
                    }
                    events.RescheduleEvent(EV_CHECK_TANK, 2000);
                    break;
                case EV_SOUL_SCREAM:
                    if (me->CastSpell(me->GetVictim(), SPELL_SOUL_SCREAM) == SPELL_CAST_OK)
                    {
                        if ((rand() % 3) == 0)
                            Talk(TALK_ANGER_SAY_SPEC);
                        events.RescheduleEvent(EV_SOUL_SCREAM, urand(9000, 11000));
                    }
                    break;
                case EV_SPITE:
                    if (me->CastSpell(me, SPELL_SPITE_TARGET) == SPELL_CAST_OK)
                    {
                        Talk(TALK_ANGER_SAY_SPEC);
                        events.RescheduleEvent(EV_SPITE, 20000);
                    }
                    break;
            }
            
            DoMeleeAttackIfReady();
        }
        
    private:
        uint64 tankGUID;
        
        std::list<uint64> spiteGUIDs;
    };
    
    CreatureAI* GetAI(Creature* creature) const
    override {
        return new Boss_essence_of_angerAI(creature);
    }
};

class Npc_enslaved_soul : public CreatureScript
{
public:
    Npc_enslaved_soul() : CreatureScript("npc_enslaved_soul") {}
    
    class Npc_enslaved_soulAI : public CreatureAI
    {
    public:
        Npc_enslaved_soulAI(Creature* creature) : CreatureAI(creature) 
        { 
            instance = ((InstanceScript*)creature->GetInstanceScript());
            if(instance)
                reliquaryGUID = instance->GetData64(DATA_RELIQUARY_OF_SOULS);

            me->CastSpell(me, ENSLAVED_SOUL_PASSIVE, true);
            me->CastSpell(me, SPELL_SELFSTUN, true); //2.5s inactivity
            Creature* reliquary = me->GetMap()->GetCreature(reliquaryGUID);
            if (reliquary)
                reliquary->AI()->message(DATA_SOUL_SPAWN, me->GetGUIDLow());
        }
        
        void Reset()
        override {
            me->DisappearAndDie();
        }

        void JustDied(Unit* killer)
        override {
            
            Creature* reliquary = me->GetMap()->GetCreature(reliquaryGUID);
            if (reliquary)
                reliquary->AI()->message(DATA_SOUL_DEATH, 1);
                
            me->CastSpell(me, SPELL_SOUL_RELEASE, true);
        }        
    private:
        InstanceScript* instance;
        uint64 reliquaryGUID;
    };

    CreatureAI* GetAI(Creature* creature) const 
    override {
        return new Npc_enslaved_soulAI(creature);
    };
};

void AddSC_boss_reliquary_of_souls()
{
    new Boss_reliquary_of_souls();
    new Boss_essence_of_suffering();
    new Boss_essence_of_desire();
    new Boss_essence_of_anger();
    new Npc_enslaved_soul();
}
