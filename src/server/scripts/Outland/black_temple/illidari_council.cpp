
#include "def_black_temple.h"
#include "Spell.h"

//Speech'n'Sounds
#define SAY_GATH_SLAY           -1564085
#define SAY_GATH_SLAY_COMNT     -1564089
#define SAY_GATH_DEATH          -1564093
#define SAY_GATH_SPECIAL1       -1564077
#define SAY_GATH_SPECIAL2       -1564081

#define SAY_VERA_SLAY           -1564086
#define SAY_VERA_COMNT          -1564089
#define SAY_VERA_DEATH          -1564094
#define SAY_VERA_SPECIAL1       -1564078
#define SAY_VERA_SPECIAL2       -1564082

#define SAY_MALA_SLAY           -1564087
#define SAY_MALA_COMNT          -1564090
#define SAY_MALA_DEATH          -1564095
#define SAY_MALA_SPECIAL1       -1564079
#define SAY_MALA_SPECIAL2       -1564083

#define SAY_ZERE_SLAY           -1564088
#define SAY_ZERE_COMNT          -1564091
#define SAY_ZERE_DEATH          -1564096
#define SAY_ZERE_SPECIAL1       -1564080
#define SAY_ZERE_SPECIAL2       -1564084

#define ERROR_INST_DATA           "SD2 ERROR: Instance Data for Black Temple not set properly; Illidari Council event will not function properly."

#define AKAMAID                 23089

struct CouncilYells
{
    int32 entry;
    uint32 timer;
};

static CouncilYells CouncilAggro[]=
{
    {-1564069, 5000},                                       // Gathios
    {-1564070, 5500},                                       // Veras
    {-1564071, 5000},                                       // Malande
    {-1564072, 0},                                          // Zerevor
};

// Need to get proper timers for this later
static CouncilYells CouncilEnrage[]=
{
    {-1564073, 2000},                                       // Gathios
    {-1564074, 6000},                                       // Veras
    {-1564075, 5000},                                       // Malande
    {-1564076, 0},                                          // Zerevor
};

// High Nethermancer Zerevor's spells
#define SPELL_FLAMESTRIKE          41481
#define SPELL_BLIZZARD             41482
#define SPELL_ARCANE_BOLT          41483
#define SPELL_ARCANE_EXPLOSION     41524
#define SPELL_DAMPEN_MAGIC         41478

// Lady Malande's spells
#define SPELL_EMPOWERED_SMITE      41471
#define SPELL_CIRCLE_OF_HEALING    41455
#define SPELL_REFLECTIVE_SHIELD    41475
#define SPELL_DIVINE_WRATH         41472
#define SPELL_HEAL_VISUAL          24171

// Gathios the Shatterer's spells
#define SPELL_BLESS_PROTECTION     41450
#define SPELL_BLESS_SPELLWARD      41451
#define SPELL_CONSECRATION         41541
#define SPELL_HAMMER_OF_JUSTICE    41468
#define SPELL_SEAL_OF_COMMAND      41469
//#define SPELL_JUDGEMENT_OF_COMMAND 41470
#define SPELL_SEAL_OF_BLOOD        41459
//#define SPELL_JUDGEMENT_OF_BLOOD   41461
#define SPELL_CHROMATIC_AURA       41453
#define SPELL_DEVOTION_AURA        41452
#define SPELL_JUDGEMENT            41467 //effect scripted in SpellEffects.cpp

// Veras Darkshadow's spells
#define SPELL_DEADLY_POISON        41485
#define SPELL_DEADLY_STRIKE        41480 //aura on caster, peridiodic apply SPELL_DEADLY_POISON on caster's target
#define SPELL_ENVENOM              41487
#define SPELL_VANISH               41476
#define SPELL_VANISH_STUN          41479 //self 3s stun

#define SPELL_BERSERK              41476

enum Messages
{
    VERAS_HAS_VANISHED,
};


class mob_blood_elf_council_voice_trigger : public CreatureScript
{
public:
    mob_blood_elf_council_voice_trigger() : CreatureScript("mob_blood_elf_council_voice_trigger")
    { }

    class mob_blood_elf_council_voice_triggerAI : public ScriptedAI
    {
    public:
        mob_blood_elf_council_voice_triggerAI(Creature* c) : ScriptedAI(c)
        {
            for (uint64 & i : Council)
                i = 0;
        }

        uint64 Council[4];

        uint32 EnrageTimer;
        uint32 AggroYellTimer;

        uint8 YellCounter;                                      // Serves as the counter for both the aggro and enrage yells

        bool EventStarted;

        void Reset()
            override {
            EnrageTimer = 900000;                               // 15 minutes
            AggroYellTimer = 500;

            YellCounter = 0;

            EventStarted = false;
        }

        // finds and stores the GUIDs for each Council member using instance data system.
        void LoadCouncilGUIDs()
        {
            if (InstanceScript* pInstance = ((InstanceScript*)me->GetInstanceScript()))
            {
                Council[0] = pInstance->GetData64(DATA_GATHIOSTHESHATTERER);
                Council[1] = pInstance->GetData64(DATA_VERASDARKSHADOW);
                Council[2] = pInstance->GetData64(DATA_LADYMALANDE);
                Council[3] = pInstance->GetData64(DATA_HIGHNETHERMANCERZEREVOR);
            }
            else error_log(ERROR_INST_DATA);
        }

        void EnterCombat(Unit* who) override {}

        void AttackStart(Unit* who) override {}
        void MoveInLineOfSight(Unit* who) override {}

        void UpdateAI(const uint32 diff)
            override {
            if (!EventStarted)
                return;

            if (YellCounter > 3)
                return;

            if (AggroYellTimer)
            {
                if (AggroYellTimer <= diff)
                {
                    if (Unit* pMember = ObjectAccessor::GetUnit(*me, Council[YellCounter]))
                    {
                        DoScriptText(CouncilAggro[YellCounter].entry, pMember);
                        AggroYellTimer = CouncilAggro[YellCounter].timer;
                    }
                    ++YellCounter;
                    if (YellCounter > 3)
                        YellCounter = 0;                            // Reuse for Enrage Yells
                }
                else AggroYellTimer -= diff;
            }

            if (EnrageTimer)
            {
                if (EnrageTimer <= diff)
                {
                    if (Unit* pMember = ObjectAccessor::GetUnit(*me, Council[YellCounter]))
                    {
                        pMember->CastSpell(pMember, SPELL_BERSERK, true);
                        DoScriptText(CouncilEnrage[YellCounter].entry, pMember);
                        EnrageTimer = CouncilEnrage[YellCounter].timer;
                    }
                    ++YellCounter;
                }
                else EnrageTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_blood_elf_council_voice_triggerAI(creature);
    }
};



class mob_illidari_council : public CreatureScript
{
public:
    mob_illidari_council() : CreatureScript("mob_illidari_council")
    { }

    class mob_illidari_councilAI : public ScriptedAI
    {
    public:
        mob_illidari_councilAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            for (uint64 & i : Council)
                i = 0;
        }

        InstanceScript* pInstance;

        uint64 Council[4];

        uint32 CheckTimer;
        uint32 EndEventTimer;

        uint8 DeathCount;

        bool EventBegun;

        void Reset()
            override {
            CheckTimer = 2000;
            EndEventTimer = 0;

            DeathCount = 0;

            Creature* pMember = nullptr;
            for (uint64 i : Council)
            {
                pMember = ObjectAccessor::GetCreature((*me), i);
                if (pMember)
                {
                    if (!pMember->IsAlive())
                    {
                        pMember->DespawnOrUnsummon();
                        pMember->Respawn();
                    }
                    pMember->AI()->EnterEvadeMode();
                }
            }

            if (pInstance && pInstance->GetData(DATA_ILLIDARICOUNCILEVENT) != DONE)
            {
                pInstance->SetData(DATA_ILLIDARICOUNCILEVENT, NOT_STARTED);
                if (Creature* VoiceTrigger = (ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_BLOOD_ELF_COUNCIL_VOICE))))
                    VoiceTrigger->AI()->EnterEvadeMode();
            }

            EventBegun = false;

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetDisplayId(11686);
        }

        void EnterCombat(Unit *who) override {}
        void AttackStart(Unit* who) override {}
        void MoveInLineOfSight(Unit* who) override {}

        void StartEvent(Unit *target)
        {
            if (!pInstance) return;

            if (target && target->IsAlive())
            {
                // /!\ Not same order as in mob_blood_elf_council_voice_triggerAI
                Council[0] = pInstance->GetData64(DATA_GATHIOSTHESHATTERER);
                Council[1] = pInstance->GetData64(DATA_HIGHNETHERMANCERZEREVOR);
                Council[2] = pInstance->GetData64(DATA_LADYMALANDE);
                Council[3] = pInstance->GetData64(DATA_VERASDARKSHADOW);

                // Start the event for the Voice Trigger
                if (Creature* VoiceTrigger = (ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_BLOOD_ELF_COUNCIL_VOICE))))
                {
                    ((mob_blood_elf_council_voice_trigger::mob_blood_elf_council_voice_triggerAI*)VoiceTrigger->AI())->LoadCouncilGUIDs();
                    ((mob_blood_elf_council_voice_trigger::mob_blood_elf_council_voice_triggerAI*)VoiceTrigger->AI())->EventStarted = true;
                }

                for (uint64 i : Council)
                {
                    Unit* Member = nullptr;
                    if (i)
                    {
                        Member = ObjectAccessor::GetUnit((*me), i);
                        if (Member && Member->IsAlive())
                            (Member->ToCreature())->AI()->AttackStart(target);
                    }
                }

                pInstance->SetData(DATA_ILLIDARICOUNCILEVENT, IN_PROGRESS);

                EventBegun = true;
            }
        }

        void UpdateAI(const uint32 diff)
            override {
            if (!EventBegun) return;

            if (EndEventTimer)
            {
                if (EndEventTimer <= diff)
                {
                    if (DeathCount >= 4)
                    {
                        if (pInstance)
                        {
                            if (Creature* VoiceTrigger = (ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_BLOOD_ELF_COUNCIL_VOICE))))
                                VoiceTrigger->DealDamage(VoiceTrigger, VoiceTrigger->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                            pInstance->SetData(DATA_ILLIDARICOUNCILEVENT, DONE);
                            //me->SummonCreature(AKAMAID,746.466980f,304.394989f,311.90208f,6.272870f,TEMPSUMMON_DEAD_DESPAWN,0);
                        }
                        DoZoneInCombat(); //be sure to have all players in threat list
                        for (auto itr : me->getThreatManager().getThreatList())
                        {
                            Player* p = ObjectAccessor::GetPlayer(*me, itr->getUnitGuid());
                            if (p)
                                for (uint8 i = 0; i < 4; i++)
                                    p->RewardReputation(me, 1.0f);
                        }
                        me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                        return;
                    }

                    Creature* pMember = (ObjectAccessor::GetCreature(*me, Council[DeathCount]));
                    if (pMember && pMember->IsAlive())
                        pMember->DealDamage(pMember, pMember->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);

                    ++DeathCount;
                    EndEventTimer = 500;
                }
                else EndEventTimer -= diff;
            }

            if (CheckTimer)
            {
                if (CheckTimer <= diff)
                {
                    uint8 EvadeCheck = 0;
                    for (uint64 i : Council)
                    {
                        if (i)
                        {
                            if (Creature* Member = (ObjectAccessor::GetCreature((*me), i)))
                            {
                                // This is the evade/death check.
                                if (Member->IsAlive() && !Member->GetVictim())
                                    ++EvadeCheck;                   //If all members evade, we reset so that players can properly reset the event
                                else if (!Member->IsAlive())         // If even one member dies, kill the rest, set instance data, and kill self.
                                {
                                    EndEventTimer = 500;
                                    CheckTimer = 0;
                                    return;
                                }
                            }
                        }
                    }

                    if (EvadeCheck > 3)
                        Reset();

                    CheckTimer = 500;
                }
                else CheckTimer -= diff;
            }

        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_illidari_councilAI(creature);
    }
};



struct boss_illidari_councilAI : public ScriptedAI
{
    boss_illidari_councilAI(Creature* c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        for(uint64 & i : Council)
            i = 0;
        LoadedGUIDs = false;
    }

    uint64 Council[4];

    InstanceScript* pInstance;

    bool LoadedGUIDs;

    void EnterCombat(Unit* who)
    override {
        if(pInstance)
        {
            if (pInstance->GetData(DATA_RELIQUARYOFSOULSEVENT) == IN_PROGRESS) {
                EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
                return;
            }
            
            Creature* Controller = (ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ILLIDARICOUNCIL)));
            if (Controller)
                ((mob_illidari_council::mob_illidari_councilAI*)Controller->AI())->StartEvent(who);
        }
        else
        {
            error_log(ERROR_INST_DATA);
            EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
            return;
        }
        DoZoneInCombat();
        // Load GUIDs on first aggro because the creature guids are only set as the creatures are created in world-
        // this means that for each creature, it will attempt to LoadGUIDs even though some of the other creatures are
        // not in world, and thus have no GUID set in the instance data system. Putting it in aggro ensures that all the creatures
        // have been loaded and have their GUIDs set in the instance data system.
        if(!LoadedGUIDs)
            LoadGUIDs();
    }
    
    bool TryDoCast(Unit *victim, uint32 spellId, bool triggered = false)
    {
        if(me->IsNonMeleeSpellCast(false)) return false;

        DoCast(victim,spellId,triggered);
        return true;
    }

    void EnterEvadeMode(EvadeReason why)
    override {
        for(uint64 i : Council)
        {
            if(Unit* pUnit = ObjectAccessor::GetUnit(*me, i))
                if(pUnit != me && pUnit->GetVictim())
                {
                    AttackStart(pUnit->GetVictim());
                    return;
                }
        }
        ScriptedAI::EnterEvadeMode(why);
    }

    void DamageTaken(Unit* done_by, uint32 &damage)
    override {
        if(done_by == me)
            return;

        damage /= GetAliveCount();
        for(uint64 i : Council)
        {
            if(Creature* pUnit = ObjectAccessor::GetCreature(*me, i))
                if(pUnit != me && pUnit->IsAlive())
                {
                    if(damage <= pUnit->GetHealth())
                    {
                        pUnit->LowerPlayerDamageReq(damage);
                        pUnit->SetHealth(pUnit->GetHealth() - damage);
                    }
                    else
                    {
                        pUnit->LowerPlayerDamageReq(damage);
                        pUnit->Kill(pUnit, false);
                    }
                }
        }
    }
    
    uint8 GetAliveCount() // Returns number of alive council members, to share damage
    {
        uint8 count = 0;
        for(uint64 i : Council)
        {
            if (Creature* pUnit = ObjectAccessor::GetCreature(*me, i))
            {
                if (pUnit->IsAlive())
                    count++;
            }
        }
        
        if (!count)
            count = 4;
        
        return count;
    }

    void LoadGUIDs()
    {
        if(!pInstance)
        {
            error_log(ERROR_INST_DATA);
            return;
        }

        Council[0] = pInstance->GetData64(DATA_LADYMALANDE);
        Council[1] = pInstance->GetData64(DATA_HIGHNETHERMANCERZEREVOR);
        Council[2] = pInstance->GetData64(DATA_GATHIOSTHESHATTERER);
        Council[3] = pInstance->GetData64(DATA_VERASDARKSHADOW);

        LoadedGUIDs = true;
    }
};

#define TIMER_CONSECRATION 30000
#define TIMER_CONSECRATION_FIRST 10000
#define TIMER_AURA 30000
#define TIMER_AURA_FIRST 6000
#define TIMER_SEAL_FIRST 15000 + rand()%5000
#define TIMER_BLESSING 15000
#define TIMER_JUDGEMENT 15000
#define TIMER_HAMMER_OF_JUSTICE 20000
#define TIMER_HAMMER_OF_JUSTICE_FIRST 10000

class boss_gathios_the_shatterer : public CreatureScript
{
public:
    boss_gathios_the_shatterer() : CreatureScript("boss_gathios_the_shatterer")
    { }

    class boss_gathios_the_shattererAI : public boss_illidari_councilAI
    {
        public:
        boss_gathios_the_shattererAI(Creature *c) : boss_illidari_councilAI(c) {}
    
        uint32 ConsecrationTimer;
        uint32 HammerOfJusticeTimer;
        uint32 SealTimer;
        uint32 AuraTimer;
        uint32 BlessingTimer;
        uint32 JudgeTimer;
        uint32 combatTimer;
        bool lastAura;
        bool lastBlessing;
        bool lastSeal;
    
        void Reset()
        override {
            ConsecrationTimer = TIMER_CONSECRATION_FIRST;
            HammerOfJusticeTimer = TIMER_HAMMER_OF_JUSTICE_FIRST;
            SealTimer = TIMER_SEAL_FIRST;
            AuraTimer = TIMER_AURA_FIRST;
            BlessingTimer = TIMER_BLESSING;
            JudgeTimer = uint32(-1);
            lastAura = rand()%2;
            lastBlessing = rand()%2;
            lastSeal = rand()%2;
            combatTimer = 0;
    
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(SAY_GATH_SLAY, me);
        }
    
        void JustDied(Unit *victim)
        override {
            DoScriptText(SAY_GATH_DEATH, me);
        }
    
        Unit* SelectCouncilMember(bool magicWard)
        {
            Unit* target = me;
            uint8 member = urand(0, 2);
    
            if(member == 2) // do not target Veras while he is stealthed
            {
                member = 3; // member 2 is actually gathios which can't be targeted
                if(Creature* veras = ObjectAccessor::GetCreature((*me),Council[3]))
                    if(veras->AI()->message(VERAS_HAS_VANISHED,0))
                        member = 0; //do not rerand, not sure about this but this could explain why malande seems to be targeted more often
            }
            if(member == 1 && magicWard && combatTimer < 20000) //avoid magic protection on zerevor at combat start
                member = 0;
    
            target = ObjectAccessor::GetUnit((*me), Council[member]);
            return target;
        }
    
        bool CastAuraOnCouncil()
        {
            uint32 spellid = 0;
            if(lastAura == 1)
                spellid = SPELL_DEVOTION_AURA;
            else
                spellid = SPELL_CHROMATIC_AURA;
    
            bool success = true;
    
            for(uint64 i : Council)
            {
                SpellCastResult result = SPELL_CAST_OK;
                Unit* pUnit = ObjectAccessor::GetUnit((*me), i);
                if (pUnit)
                    result = SpellCastResult(pUnit->CastSpell(pUnit, spellid, true, nullptr, nullptr, me->GetGUID()));
    
                success = success && result == SPELL_CAST_OK;
            }
    
            if(success)
                lastAura = !lastAura;
    
            return true;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            combatTimer += diff;
    
            if(BlessingTimer < diff)
            {
                uint32 spellid = lastBlessing ? SPELL_BLESS_SPELLWARD : SPELL_BLESS_PROTECTION;
    
                if(Unit* pUnit = SelectCouncilMember(lastBlessing))
                    if(DoCast(pUnit,spellid,true) == SPELL_CAST_OK)
                    {
                        BlessingTimer = TIMER_BLESSING;
                        lastBlessing = !lastBlessing;
                    }
    
            } else BlessingTimer -= diff;
    
            if(JudgeTimer < diff)
            {
                if(DoCast(me->GetVictim(),SPELL_JUDGEMENT) == SPELL_CAST_OK)
                {
                    JudgeTimer = uint32(-1);
                    SealTimer = 2200; //just after finishing casting judgement (2s cast)
                }
            } else JudgeTimer -= diff;
    
            if(ConsecrationTimer < diff)
            {
                if(DoCast(me, SPELL_CONSECRATION) == SPELL_CAST_OK)
                    ConsecrationTimer = TIMER_CONSECRATION;
            } else ConsecrationTimer -= diff;
    
            if(HammerOfJusticeTimer < diff)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))
                {
                    // is in ~10-40 yd range
                    if(me->GetDistance2d(target) > 10)
                    {
                        if(DoCast(target, SPELL_HAMMER_OF_JUSTICE) == SPELL_CAST_OK)
                            HammerOfJusticeTimer = TIMER_HAMMER_OF_JUSTICE;
                    }
                }
            } else HammerOfJusticeTimer -= diff;
    
            if(SealTimer < diff)
            {
                uint32 spellid;
                if(lastSeal == 1)
                    spellid = SPELL_SEAL_OF_COMMAND;
                else
                    spellid = SPELL_SEAL_OF_BLOOD;
    
                if(DoCast(me,spellid) == SPELL_CAST_OK)
                {
                    lastSeal = !lastSeal;
                    SealTimer = uint32(-1);
                    JudgeTimer = TIMER_JUDGEMENT;
                }
            } else SealTimer -= diff;
    
            if(AuraTimer < diff)
            {
                if(CastAuraOnCouncil())
                    AuraTimer = TIMER_AURA;
            } else AuraTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_gathios_the_shattererAI(creature);
    }
};

#define TIMER_SMITE 10000
#define TIMER_DIVINE_WRATH 10000
#define TIMER_CIRCLE_OF_HEALING 15000
#define TIMER_CIRCLE_OF_HEALING_FIRST 40000
#define TIMER_REFLECTIVE_SHIELD 35000 + rand()%10000

class boss_lady_malande : public CreatureScript
{
public:
    boss_lady_malande() : CreatureScript("boss_lady_malande")
    { }

    class boss_lady_malandeAI : public boss_illidari_councilAI
    {
        public:
        boss_lady_malandeAI(Creature *c) : boss_illidari_councilAI(c) {}
    
        uint32 EmpoweredSmiteTimer;
        uint32 CircleOfHealingTimer;
        uint32 DivineWrathTimer;
        uint32 ReflectiveShieldTimer;
    
        void Reset()
        override {
            EmpoweredSmiteTimer = TIMER_SMITE;
            CircleOfHealingTimer = TIMER_CIRCLE_OF_HEALING_FIRST;
            DivineWrathTimer = TIMER_DIVINE_WRATH;
            ReflectiveShieldTimer = TIMER_REFLECTIVE_SHIELD;
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(SAY_MALA_SLAY, me);
        }
    
        void JustDied(Unit *victim)
        override {
            DoScriptText(SAY_MALA_DEATH, me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if(EmpoweredSmiteTimer < diff)
            {
                if(DoCast(me->GetVictim(), SPELL_EMPOWERED_SMITE) == SPELL_CAST_OK)
                    EmpoweredSmiteTimer = TIMER_SMITE;
    
            }else EmpoweredSmiteTimer -= diff;
    
            if(CircleOfHealingTimer < diff)
            {
                if(DoCast(me, SPELL_CIRCLE_OF_HEALING) == SPELL_CAST_OK)
                    CircleOfHealingTimer = TIMER_CIRCLE_OF_HEALING;
    
            }else CircleOfHealingTimer -= diff;
    
            if(DivineWrathTimer < diff)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    if(DoCast(target, SPELL_DIVINE_WRATH) == SPELL_CAST_OK)
                        DivineWrathTimer = TIMER_DIVINE_WRATH;
    
            }else DivineWrathTimer -= diff;
    
            if(ReflectiveShieldTimer < diff)
            {
                if(DoCast(me, SPELL_REFLECTIVE_SHIELD) == SPELL_CAST_OK)
                    ReflectiveShieldTimer = TIMER_REFLECTIVE_SHIELD;
    
            }else ReflectiveShieldTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_lady_malandeAI(creature);
    }
};

#define TIMER_VANISH 60000
#define TIMER_VANISH_FIRST 25000
#define TIMER_VANISH_DURATION 30000
#define TIMER_WAIT_AFTER_VANISH 3000

class boss_veras_darkshadow : public CreatureScript
{
public:
    boss_veras_darkshadow() : CreatureScript("boss_veras_darkshadow")
    { }

    class boss_veras_darkshadowAI : public boss_illidari_councilAI
    {
        public:
        boss_veras_darkshadowAI(Creature *c) : boss_illidari_councilAI(c) {}
    
        uint64 appliedPoisonTarget;
        uint64 changeTargetTimer;
    
        uint32 VanishTimer;
        uint32 VanishTimeLeft;
        uint32 EnvenomTimer;
    
        bool HasVanished;
    
        uint64 message(uint32 id, uint64 data) 
        override { 
            if(id == VERAS_HAS_VANISHED)
                return HasVanished || VanishTimer > (TIMER_VANISH - 5000); // also give some time when we just got out of vanish
    
            return 0;
        }
    
        void Reset()
        override {
            appliedPoisonTarget = 0;
            changeTargetTimer = 0;
            VanishTimer = TIMER_VANISH_FIRST;
            VanishTimeLeft = TIMER_VANISH_DURATION;
            EnvenomTimer = uint32(-1);
    
            HasVanished = false;
            me->SetVisible(true);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
        
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(SAY_VERA_SLAY, me);
        }
    
        void JustDied(Unit *victim)
        override {
            me->SetVisible(true);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            DoScriptText(SAY_VERA_DEATH, me);
        }
    
        //try to exclude the mage tank
        Unit* GetPoisonTarget()
        {
            ScriptedAI* zerevorAI = nullptr;
            Creature* zerevor = ObjectAccessor::GetCreature(*me, Council[1]);
            if(zerevor)
                zerevorAI = static_cast<ScriptedAI*>(zerevor->AI());
            if(zerevorAI)
                return zerevorAI->SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0, true, true); //except mage tank
    
            //else select it myself
            return SelectTarget(SELECT_TARGET_RANDOM, 0);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!HasVanished)
            {
                if(!UpdateVictim())
                    return;
    
                if(VanishTimer < diff)                    
                {
                    if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    {
                        VanishTimer = TIMER_VANISH;
                        VanishTimeLeft = TIMER_VANISH_DURATION;
                        appliedPoisonTarget = 0;
                        HasVanished = true;
                        me->SetVisible(false);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        DoCast(me,SPELL_VANISH,true); //just for combat log
                        DoResetThreat();
                        me->AddAura(SPELL_DEADLY_STRIKE,me);
                        changeTargetTimer = 0;
                    }
                }else VanishTimer -= diff;
    
                DoMeleeAttackIfReady();
            }
            else
            {
                if(!me->GetVictim())
                {
                    EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
                    return;
                }
    
                //end vanish
                if(VanishTimeLeft < diff)
                {
                    HasVanished = false;
                    me->SetVisible(true);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    Unit* currentTarget = me->GetVictim();
                    DoResetThreat();
                    me->AddThreat(currentTarget, 1200.0f);
                    DoCast(me,SPELL_VANISH_STUN);
                    return;
                }else VanishTimeLeft -= diff;
    
                if(changeTargetTimer < diff)
                {
                     if(Unit* newTarget = GetPoisonTarget())
                     {
                         DoResetThreat();
                         me->AddThreat(newTarget, 999000.0f);
                         AttackStart(newTarget);
                         EnvenomTimer = 4800;
                         appliedPoisonTarget = newTarget->GetGUID();
                         changeTargetTimer = 5000;
                     }
                } else changeTargetTimer -= diff;
    
                if(EnvenomTimer < diff) 
                {
                    if(appliedPoisonTarget)
                        if(Player* p = me->GetMap()->GetPlayer(appliedPoisonTarget))
                            if(DoCast(p,SPELL_ENVENOM,true) == SPELL_CAST_OK)
                                appliedPoisonTarget = 0;
    
                }else EnvenomTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_veras_darkshadowAI(creature);
    }
};

#define TIMER_AOE 12000
#define TIMER_DAMPEN_MAGIC 67200

class boss_high_nethermancer_zerevor : public CreatureScript
{
public:
    boss_high_nethermancer_zerevor() : CreatureScript("boss_high_nethermancer_zerevor")
    { }

    class boss_high_nethermancer_zerevorAI : public boss_illidari_councilAI
    {
        public:
        boss_high_nethermancer_zerevorAI(Creature *c) : boss_illidari_councilAI(c) {}
    
        uint32 AoETimer;
        uint32 ArcaneBoltTimer;
        uint32 DampenMagicTimer;
        uint32 ArcaneExplosionTimer;
    
        void Reset()
        override {
            AoETimer = TIMER_AOE;
            ArcaneBoltTimer = 500;
            DampenMagicTimer = 200;
            ArcaneExplosionTimer = 14000;
    
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(SAY_ZERE_SLAY, me);
        }
    
        void JustDied(Unit *victim)
        override {
            DoScriptText(SAY_ZERE_DEATH, me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            //prefer staying at 15m
            if(me->isMoving() && me->GetDistance2d(me->GetVictim()) < 15 && me->IsWithinLOSInMap(me->GetVictim()))
                me->StopMoving();
    
            if(!me->IsWithinLOSInMap(me->GetVictim()))
                me->GetMotionMaster()->MoveChase(me->GetVictim());
    
            if(DampenMagicTimer < diff)
            {
                me->InterruptNonMeleeSpells(false);
                if(DoCast(me, SPELL_DAMPEN_MAGIC, true) == SPELL_CAST_OK)
                {
                    DampenMagicTimer = TIMER_DAMPEN_MAGIC;          // 1.12 minute
                    ArcaneBoltTimer += 2000;
                }
            }else DampenMagicTimer -= diff;
    
            if(AoETimer < diff)
            {
                uint32 spellID = rand()%2 ? SPELL_BLIZZARD : SPELL_FLAMESTRIKE;
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    if(DoCast(target, spellID) == SPELL_CAST_OK)
                        AoETimer = TIMER_AOE;
            } else AoETimer -= diff;
    
            if(ArcaneExplosionTimer < diff)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 8, true))
                    if(DoCast(target, SPELL_ARCANE_EXPLOSION) == SPELL_CAST_OK)
                        ArcaneExplosionTimer = 3000;
            }else ArcaneExplosionTimer -= diff;
    
            if(ArcaneBoltTimer < diff)
            {
                if(DoCast(me->GetVictim(), SPELL_ARCANE_BOLT) == SPELL_CAST_OK)
                    ArcaneBoltTimer = 3000;
            } else ArcaneBoltTimer -= diff;       
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_high_nethermancer_zerevorAI(creature);
    }
};


void AddSC_boss_illidari_council()
{
    new mob_illidari_council();
    new mob_blood_elf_council_voice_trigger();
    new boss_gathios_the_shatterer();
    new boss_lady_malande();
    new boss_veras_darkshadow();
    new boss_high_nethermancer_zerevor();
}
