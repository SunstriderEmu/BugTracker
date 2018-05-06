
/* ScriptData
SDName: Bosses_Opera
SD%Complete: 90
SDComment: Oz, Hood, and RAJ event implemented. RAJ event requires more testing.
SDCategory: Karazhan

TODO: Add ambiance sounds:
9357 - A_BarnesHoodAmbience
9358 - A_BarnesOzAmbience
9359 - A_BarnesRajAmbience
EndScriptData */


#include "karazhan.h"
#include "EscortAI.h"

/***********************************/
/*** OPERA WIZARD OF OZ EVENT *****/
/*********************************/

#define SAY_DOROTHEE_DEATH          -1532025
#define SAY_DOROTHEE_SUMMON         -1532026
#define SAY_DOROTHEE_TITO_DEATH     -1532027
#define SAY_DOROTHEE_AGGRO          -1532028

#define SAY_ROAR_AGGRO              -1532029
#define SAY_ROAR_DEATH              -1532030
#define SAY_ROAR_SLAY               -1532031

#define SAY_STRAWMAN_AGGRO          -1532032
#define SAY_STRAWMAN_DEATH          -1532033
#define SAY_STRAWMAN_SLAY           -1532034

#define SAY_TINHEAD_AGGRO           -1532035
#define SAY_TINHEAD_DEATH           -1532036
#define SAY_TINHEAD_SLAY            -1532037
#define EMOTE_RUST                  -1532038

#define SAY_CRONE_AGGRO             -1532039
#define SAY_CRONE_AGGRO2            -1532040
#define SAY_CRONE_DEATH             -1532041
#define SAY_CRONE_SLAY              -1532042

/**** Spells ****/
// Dorothee
#define SPELL_WATERBOLT         31012
#define SPELL_SCREAM            31013
#define SPELL_SUMMONTITO        31014

// Tito
#define SPELL_YIPPING           31015

// Strawman
#define SPELL_BRAIN_BASH        31046
#define SPELL_BRAIN_WIPE        31069
#define SPELL_BURNING_STRAW     31075

// Tinhead
#define SPELL_CLEAVE            31043
#define SPELL_RUST              31086

// Roar
#define SPELL_MANGLE            31041
#define SPELL_SHRED             31042

// Crone
#define SPELL_CHAIN_LIGHTNING   32337

// Cyclone
#define SPELL_KNOCKBACK         32334
#define SPELL_CYCLONE_VISUAL    32332

/** Creature Entries **/
#define CREATURE_TITO           17548
#define CREATURE_CYCLONE        18412
#define CREATURE_CRONE          18168

void SummonCroneIfReady(InstanceScript* pInstance, Creature *_Creature)
{
    pInstance->SetData(DATA_OPERA_OZ_DEATHCOUNT, 0);        // Increment DeathCount
    if(pInstance->GetData(DATA_OPERA_OZ_DEATHCOUNT) == 4)
    {
        Creature* Crone = _Creature->SummonCreature(CREATURE_CRONE,  -10891.96, -1755.95, _Creature->GetPositionZ(), 4.64, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
        if(Crone)
        {
            if(_Creature->GetVictim())
                Crone->AI()->AttackStart(_Creature->GetVictim());
        }
    }
};

class boss_dorothee : public CreatureScript
{
public:
    boss_dorothee() : CreatureScript("boss_dorothee")
    { }

    class boss_dorotheeAI : public ScriptedAI
    {
        public:
        boss_dorotheeAI(Creature* c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        uint32 AggroTimer;
    
        uint32 WaterBoltTimer;
        uint32 FearTimer;
        uint32 SummonTitoTimer;
    
        bool SummonedTito;
        bool TitoDied;
    
        void Reset()
        override {
            AggroTimer = 500;
    
            WaterBoltTimer = 5000;
            FearTimer = 15000;
            SummonTitoTimer = 47500;
    
            SummonedTito = false;
            TitoDied = false;
        }
    
        void JustEngagedWith(Unit* who)
        override {
            DoScriptText(SAY_DOROTHEE_AGGRO, me);
        }
    
        void SummonTito();                                      // See below
    
        void JustDied(Unit* /*killer*/)
        override {
            DoScriptText(SAY_DOROTHEE_DEATH, me);
    
            if(pInstance)
                SummonCroneIfReady(pInstance, me);
        }
    
        void AttackStart(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::AttackStart(who);
        }
    
        void MoveInLineOfSight(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::MoveInLineOfSight(who);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(AggroTimer)
            {
                if(AggroTimer <= diff)
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    AggroTimer = 0;
                }else AggroTimer -= diff;
            }
    
            if(!UpdateVictim())
                return;
    
            if(WaterBoltTimer < diff)
            {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_WATERBOLT);
                WaterBoltTimer = TitoDied ? 1500 : 5000;
            }else WaterBoltTimer -= diff;
    
            if(FearTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_SCREAM);
                FearTimer = 30000;
            }else FearTimer -= diff;
    
            if(!SummonedTito)
            {
                if(SummonTitoTimer < diff)
                    SummonTito();
                else SummonTitoTimer -= diff;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_dorotheeAI(creature);
    }
};

class boss_strawman : public CreatureScript
{
public:
    boss_strawman() : CreatureScript("boss_strawman")
    { }

    class boss_strawmanAI : public ScriptedAI
    {
        public:
        boss_strawmanAI(Creature* c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        uint32 AggroTimer;
        uint32 BrainBashTimer;
        uint32 BrainWipeTimer;
    
        void Reset()
        override {
            AggroTimer = 13000;
            BrainBashTimer = 5000;
            BrainWipeTimer = 7000;
        }
    
        void AttackStart(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::AttackStart(who);
        }
    
        void MoveInLineOfSight(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::MoveInLineOfSight(who);
        }
    
        void JustEngagedWith(Unit* who)
        override {
            DoScriptText(SAY_STRAWMAN_AGGRO, me);
        }
    
        void SpellHit(Unit* caster, const SpellInfo *Spell)
        override {
            if((Spell->SchoolMask == SPELL_SCHOOL_MASK_FIRE) && (!(rand()%10)))
                DoCast(me, SPELL_BURNING_STRAW, true);
        }
    
        void JustDied(Unit* /*killer*/)
        override {
            DoScriptText(SAY_STRAWMAN_DEATH, me);
    
            if(pInstance)
                SummonCroneIfReady(pInstance, me);
        }
    
        void KilledUnit(Unit* victim)
        override {
            DoScriptText(SAY_STRAWMAN_SLAY, me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(AggroTimer)
            {
                if(AggroTimer <= diff)
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    AggroTimer = 0;
                }else AggroTimer -= diff;
            }
    
            if(!UpdateVictim())
                return;
    
            if(BrainBashTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_BRAIN_BASH);
                BrainBashTimer = 15000;
            }else BrainBashTimer -= diff;
    
            if(BrainWipeTimer < diff)
            {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_BRAIN_WIPE);
                BrainWipeTimer = 20000;
            }else BrainWipeTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_strawmanAI(creature);
    }
};

class boss_tinhead : public CreatureScript
{
public:
    boss_tinhead() : CreatureScript("boss_tinhead")
    { }

    class boss_tinheadAI : public ScriptedAI
    {
        public:
        boss_tinheadAI(Creature* c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        uint32 AggroTimer;
        uint32 CleaveTimer;
        uint32 RustTimer;
    
        uint8 RustCount;
    
        void Reset()
        override {
            AggroTimer = 15000;
            CleaveTimer = 5000;
            RustTimer   = 30000;
    
            RustCount   = 0;
        }
    
        void JustEngagedWith(Unit* who)
        override {
            DoScriptText(SAY_TINHEAD_AGGRO, me);
        }
    
        void AttackStart(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::AttackStart(who);
        }
    
        void MoveInLineOfSight(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::MoveInLineOfSight(who);
        }
    
        void JustDied(Unit* /*killer*/)
        override {
            DoScriptText(SAY_TINHEAD_DEATH, me);
    
            if(pInstance)
                SummonCroneIfReady(pInstance, me);
        }
    
        void KilledUnit(Unit* victim)
        override {
            DoScriptText(SAY_TINHEAD_SLAY, me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(AggroTimer)
            {
                if(AggroTimer < diff)
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    AggroTimer = 0;
                }else AggroTimer -= diff;
            }
    
            if(!UpdateVictim())
                return;
    
            if(CleaveTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                CleaveTimer = 5000;
            }else CleaveTimer -= diff;
    
            if(RustCount < 8)
            {
                if(RustTimer < diff)
                {
                    RustCount++;
                     DoScriptText(EMOTE_RUST, me);
                    DoCast(me, SPELL_RUST);
                    RustTimer = 6000;
                }else RustTimer -= diff;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_tinheadAI(creature);
    }
};

class boss_roar : public CreatureScript
{
public:
    boss_roar() : CreatureScript("boss_roar")
    { }

    class boss_roarAI : public ScriptedAI
    {
        public:
        boss_roarAI(Creature* c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        uint32 AggroTimer;
        uint32 MangleTimer;
        uint32 ShredTimer;
    
        void Reset()
        override {
            AggroTimer = 20000;
            MangleTimer = 5000;
            ShredTimer  = 10000;
        }
    
        void MoveInLineOfSight(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::MoveInLineOfSight(who);
        }
    
        void AttackStart(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::AttackStart(who);
        }
    
        void JustEngagedWith(Unit* who)
        override {
            DoScriptText(SAY_ROAR_AGGRO, me);
        }
    
        void JustDied(Unit* /*killer*/)
        override {
            DoScriptText(SAY_ROAR_DEATH, me);
    
            if(pInstance)
                SummonCroneIfReady(pInstance, me);
        }
    
        void KilledUnit(Unit* victim)
        override {
            DoScriptText(SAY_ROAR_SLAY, me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(AggroTimer)
            {
                if(AggroTimer <= diff)
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    AggroTimer = 0;
                }else AggroTimer -= diff;
            }
    
            if(!UpdateVictim())
                return;
    
            if(MangleTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_MANGLE);
                MangleTimer = 5000 + rand()%3000;
            }else MangleTimer -= diff;
    
            if(ShredTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_SHRED);
                ShredTimer = 10000 + rand()%5000;
            }else ShredTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_roarAI(creature);
    }
};

class boss_crone : public CreatureScript
{
public:
    boss_crone() : CreatureScript("boss_crone")
    { }

    class boss_croneAI : public BossAI
    {
        public:
        boss_croneAI(Creature* c) : BossAI(c, DATA_OPERA_EVENT)
        {
        }
    
        uint32 CycloneTimer;
        uint32 ChainLightningTimer;
    
        void Reset()
        override {
            _Reset();
            CycloneTimer = 30000;
            ChainLightningTimer = 10000;
        }
    
        void JustEngagedWith(Unit* who)
        override {
            _JustEngagedWith();
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_CRONE_AGGRO, me); break;
            case 1: DoScriptText(SAY_CRONE_AGGRO2, me); break;
            }
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        }
    
        void JustDied(Unit* /*killer*/)
        override {
            _JustDied();
            DoScriptText(SAY_CRONE_DEATH, me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    
            if(CycloneTimer < diff)
            {
                Creature* Cyclone = DoSpawnCreature(CREATURE_CYCLONE, rand()%10, rand()%10, 0, 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
                if(Cyclone)
                    Cyclone->CastSpell(Cyclone, SPELL_CYCLONE_VISUAL, TRIGGERED_FULL_MASK);
                CycloneTimer = 30000;
            }else CycloneTimer -= diff;
    
            if(ChainLightningTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_CHAIN_LIGHTNING);
                ChainLightningTimer = 15000;
            }else ChainLightningTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_croneAI(creature);
    }
};

class mob_tito : public CreatureScript
{
public:
    mob_tito() : CreatureScript("mob_tito")
    { }

    class mob_titoAI : public ScriptedAI
    {
        public:
        mob_titoAI(Creature* c) : ScriptedAI(c) {}
    
        ObjectGuid DorotheeGUID;
    
        uint32 YipTimer;
    
        void Reset()
        override {
            DorotheeGUID = ObjectGuid::Empty;
    
            YipTimer = 10000;
        }
    
        void JustEngagedWith(Unit* who) override {}
    
        void JustDied(Unit* /*killer*/)
        override {
            if(DorotheeGUID)
            {
                Creature* Dorothee = (ObjectAccessor::GetCreature((*me), DorotheeGUID));
                if(Dorothee && Dorothee->IsAlive())
                {
                    ((boss_dorothee::boss_dorotheeAI*)Dorothee->AI())->TitoDied = true;
                    DoScriptText(SAY_DOROTHEE_TITO_DEATH, Dorothee);
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if(YipTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_YIPPING);
                YipTimer = 10000;
            }else YipTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_titoAI(creature);
    }
};

class mob_cyclone : public CreatureScript
{
public:
    mob_cyclone() : CreatureScript("mob_cyclone")
    { }

    class mob_cycloneAI : public ScriptedAI
    {
        public:
        mob_cycloneAI(Creature* c) : ScriptedAI(c) {}
    
        uint32 MoveTimer;
    
        void Reset()
        override {
            MoveTimer = 1000;
        }
    
        void JustEngagedWith(Unit* who) override {}
    
        void MoveInLineOfSight(Unit* who)
        override {
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!me->HasAuraEffect(SPELL_KNOCKBACK, 0))
                DoCast(me, SPELL_KNOCKBACK, true);
    
            if(MoveTimer < diff)
            {
                float PosX, PosY, PosZ;
                me->GetRandomPoint(me,10, PosX, PosY, PosZ);
                me->GetMotionMaster()->MovePoint(0, PosX, PosY, PosZ);
                MoveTimer = 5000 + rand()%3000;
            }else MoveTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_cycloneAI(creature);
    }
};

/**************************************/
/**** Opera Red Riding Hood Event ****/
/************************************/

/**** Yells for the Wolf ****/
#define SAY_WOLF_AGGRO                  -1532043
#define SAY_WOLF_SLAY                   -1532044
#define SAY_WOLF_HOOD                   -1532045
#define SOUND_WOLF_DEATH                9275                //Only sound on death, no text.

/**** Spells For The Wolf ****/
#define SPELL_LITTLE_RED_RIDING_HOOD    30768
#define SPELL_TERRIFYING_HOWL           30752
#define SPELL_WIDE_SWIPE                30761

#define OPTION_WHAT_PHAT_LEWTS_YOU_HAVE 7443

/**** The Wolf's Entry ****/
#define CREATURE_BIG_BAD_WOLF           17521

class npc_grandmother : public CreatureScript
{
public:
    npc_grandmother() : CreatureScript("npc_grandmother")
    { }

    class npc_grandmotherAI : public ScriptedAI
    {
    public:
        npc_grandmotherAI(Creature* creature) : ScriptedAI(creature)
        {}

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            if (menuId == OPTION_WHAT_PHAT_LEWTS_YOU_HAVE && gossipListId == 0)
            {
                Creature* BigBadWolf = me->SummonCreature(CREATURE_BIG_BAD_WOLF, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                if (BigBadWolf)
                {
                    BigBadWolf->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    BigBadWolf->EngageWithTarget(player);
                }
                me->DespawnOrUnsummon();
            }
            player->CLOSE_GOSSIP_MENU();
            return false;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_grandmotherAI(creature);
    }
};

class boss_bigbadwolf : public CreatureScript
{
public:
    boss_bigbadwolf() : CreatureScript("boss_bigbadwolf")
    { }

    class boss_bigbadwolfAI : public BossAI
    {
        public:
        boss_bigbadwolfAI(Creature* c) : BossAI(c, DATA_OPERA_EVENT)
        {
        }
        
        uint32 ChaseTimer;
        uint32 FearTimer;
        uint32 SwipeTimer;
    
        ObjectGuid HoodGUID;
        float TempThreat;
    
        bool IsChasing;
    
        void Reset()
        override 
        {
            _Reset();
            ChaseTimer = 30000;
            FearTimer = 25000 + rand()%10000;
            SwipeTimer = 5000;
    
            HoodGUID.Clear();
            TempThreat = 0;
    
            IsChasing = false;
            
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
        }
    
        void JustEngagedWith(Unit* who)
        override 
        {
            _JustEngagedWith();
            DoScriptText(SAY_WOLF_AGGRO, me);
        }
    
        void JustDied(Unit* /*killer*/)
        override 
        {
            _JustDied();
            DoPlaySoundToSet(me, SOUND_WOLF_DEATH);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
    
            if(ChaseTimer < diff)
            {
                if(!IsChasing)
                {
                    Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if(target && target->GetTypeId() == TYPEID_PLAYER)
                    {
                        DoScriptText(SAY_WOLF_HOOD, me);
    
                        DoCast(target, SPELL_LITTLE_RED_RIDING_HOOD, true);
                        TempThreat = me->GetThreatManager().GetThreat(target);
                        if(TempThreat)
                            ModifyThreatByPercent(target, -100);
                        HoodGUID = target->GetGUID();
                        me->GetThreatManager().AddThreat(target, 1000000.0f);
                        ChaseTimer = 20000;
                        IsChasing = true;
                        me->SetFullTauntImmunity(true);
                    }
                }
                else
                {
                    IsChasing = false;
                    me->SetFullTauntImmunity(false);
                    Unit* target = ObjectAccessor::GetUnit((*me), HoodGUID);
                    if(target)
                    {
                        HoodGUID = ObjectGuid::Empty;
                        if(me->GetThreatManager().GetThreat(target))
                            ModifyThreatByPercent(target, -100);
                        me->GetThreatManager().AddThreat(target, TempThreat);
                        TempThreat = 0;
                    }
    
                    ChaseTimer = 40000;
                }
            }else ChaseTimer -= diff;
    
            if(IsChasing)
                return;
    
            if(FearTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_TERRIFYING_HOWL);
                FearTimer = 25000 + rand()%10000;
            }else FearTimer -= diff;
    
            if(SwipeTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_WIDE_SWIPE);
                SwipeTimer = 25000 + rand()%5000;
            }else SwipeTimer -= diff;
    
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_bigbadwolfAI(creature);
    }
};

/**********************************************/
/******** Opera Romeo and Juliet Event *******/
/********************************************/

/**** Speech *****/
#define SAY_JULIANNE_AGGRO              -1532046
#define SAY_JULIANNE_ENTER              -1532047
#define SAY_JULIANNE_DEATH01            -1532048
#define SAY_JULIANNE_DEATH02            -1532049
#define SAY_JULIANNE_RESURRECT          -1532050
#define SAY_JULIANNE_SLAY               -1532051

#define SAY_ROMULO_AGGRO                -1532052
#define SAY_ROMULO_DEATH                -1532053
#define SAY_ROMULO_ENTER                -1532054
#define SAY_ROMULO_RESURRECT            -1532055
#define SAY_ROMULO_SLAY                 -1532056

/***** Spells For Julianne *****/
#define SPELL_BLINDING_PASSION          30890
#define SPELL_DEVOTION                  30887
#define SPELL_ETERNAL_AFFECTION         30878
#define SPELL_POWERFUL_ATTRACTION       30889
#define SPELL_DRINK_POISON              30907

/***** Spells For Romulo ****/
#define SPELL_BACKWARD_LUNGE            30815
#define SPELL_DARING                    30841
#define SPELL_DEADLY_SWATHE             30817
#define SPELL_POISON_THRUST             30822

/**** Other Misc. Spells ****/
#define SPELL_UNDYING_LOVE              30951
#define SPELL_RES_VISUAL                24171

/*** Misc. Information ****/
#define CREATURE_ROMULO             17533
#define ROMULO_X                    -10900
#define ROMULO_Y                    -1758

enum RAJPhase
{
    PHASE_JULIANNE      = 0,
    PHASE_ROMULO        = 1,
    PHASE_BOTH          = 2,
};

void PretendToDie(Creature* _Creature)
{
    _Creature->InterruptNonMeleeSpells(false);
    _Creature->SetHealth(0);
    _Creature->ClearComboPointHolders();
    _Creature->RemoveAllAurasOnDeath();
    _Creature->ModifyAuraState(AURA_STATE_HEALTHLESS_20_PERCENT, false);
    _Creature->ModifyAuraState(AURA_STATE_HEALTHLESS_35_PERCENT, false);
    _Creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    _Creature->ClearAllReactives();
    _Creature->SetGuidValue(UNIT_FIELD_TARGET, ObjectGuid::Empty);
    _Creature->GetMotionMaster()->Clear();
    _Creature->GetMotionMaster()->MoveIdle();
    _Creature->SetUInt32Value(UNIT_FIELD_BYTES_1,PLAYER_STATE_DEAD);
};

void Resurrect(Creature* target)
{
    target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    target->SetHealth(target->GetMaxHealth());
    target->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
    target->CastSpell(target, SPELL_RES_VISUAL, TRIGGERED_FULL_MASK);
    if(target->GetVictim())
    {
        target->SetGuidValue(UNIT_FIELD_TARGET, target->GetVictim()->GetGUID());
        target->GetMotionMaster()->MoveChase(target->GetVictim());
        target->AI()->AttackStart(target->GetVictim());
    }
};

void KillLovers(Creature* creature, Creature* creatureLover, Unit* killer)
{
    creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    Unit::Kill(killer, creature, false);
    if(creatureLover)
    {
        creatureLover->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        Unit::Kill(killer, creatureLover, false);
    }
}

void boss_dorothee::boss_dorotheeAI::SummonTito()
{
    Creature* Tito = DoSpawnCreature(CREATURE_TITO, 0, 0, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 45000);
    if (Tito)
    {
        DoScriptText(SAY_DOROTHEE_SUMMON, me);
        ((mob_tito::mob_titoAI*)Tito->AI())->DorotheeGUID = me->GetGUID();
        Tito->AI()->AttackStart(me->GetVictim());
        SummonedTito = true;
        TitoDied = false;
    }
}

class boss_julianne : public CreatureScript
{
public:
    boss_julianne() : CreatureScript("boss_julianne")
    { }

    class boss_julianneAI : public BossAI
    {
        public:
        boss_julianneAI(Creature* c) : BossAI(c, DATA_OPERA_EVENT)
        {
            EntryYellTimer = 1000;
            AggroYellTimer = 10000;
        }
    
        ObjectGuid RomuloGUID;
    
        uint32 Phase;
    
        uint32 EntryYellTimer;
        uint32 AggroYellTimer;
        uint32 BlindingPassionTimer;
        uint32 DevotionTimer;
        uint32 EternalAffectionTimer;
        uint32 PowerfulAttractionTimer;
        uint32 SummonRomuloTimer;
        uint32 ResurrectTimer;
    
        bool IsFakingDeath;
        bool SummonedRomulo;
        bool RomuloDead;
    
        void Reset()
        override {
            _Reset();
            if(RomuloGUID)
            {
                if(Unit* Romulo = ObjectAccessor::GetUnit(*me, RomuloGUID))
                {
                    Romulo->SetVisible(false);
                    Romulo->KillSelf();
                }
    
                RomuloGUID = ObjectGuid::Empty;
            }
    
            Phase = PHASE_JULIANNE;
    
            BlindingPassionTimer = 30000;
            DevotionTimer = 15000;
            EternalAffectionTimer = 25000;
            PowerfulAttractionTimer = 5000;
    
            if(IsFakingDeath)
                Resurrect(me);
    
            IsFakingDeath = false;
            SummonedRomulo = false;
            RomuloDead = false;
        }
    
        void JustEngagedWith(Unit* who) override 
        {
            _JustEngagedWith();
        }
    
        void AttackStart(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::AttackStart(who);
        }
    
        void MoveInLineOfSight(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::MoveInLineOfSight(who);
        }
    
        void DamageTaken(Unit* done_by, uint32 &damage) override;
    
        void JustDied(Unit* /*killer*/)
        override {
            _JustDied();
            DoScriptText(SAY_JULIANNE_DEATH02, me);
        }
    
        void KilledUnit(Unit* victim)
        override {
           DoScriptText(SAY_JULIANNE_SLAY, me);
        }
    
        void UpdateAI(const uint32 diff) override;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_julianneAI(creature);
    }
};

class boss_romulo : public CreatureScript
{
public:
    boss_romulo() : CreatureScript("boss_romulo")
    { }

    class boss_romuloAI : public ScriptedAI
    {
        public:
        boss_romuloAI(Creature* c) : ScriptedAI(c)
        {
            EntryYellTimer = 8000;
            AggroYellTimer = 15000;
        }
    
        ObjectGuid JulianneGUID;
    
        uint32 Phase;
    
        uint32 EntryYellTimer;
        uint32 AggroYellTimer;
        uint32 BackwardLungeTimer;
        uint32 DaringTimer;
        uint32 DeadlySwatheTimer;
        uint32 PoisonThrustTimer;
        uint32 ResurrectTimer;
    
        bool JulianneDead;
        bool IsFakingDeath;
    
        void Reset()
        override {
            JulianneGUID.Clear();
    
            Phase = PHASE_ROMULO;
    
            BackwardLungeTimer = 15000;
            DaringTimer = 20000;
            DeadlySwatheTimer = 25000;
            PoisonThrustTimer = 10000;
    
            if(IsFakingDeath)
                Resurrect(me);
    
            IsFakingDeath = false;
            JulianneDead = false;
        }
    
        void DamageTaken(Unit* done_by, uint32 &damage) override;
    
        void JustEngagedWith(Unit* who)
        override {
            DoScriptText(SAY_ROMULO_AGGRO, me);
            if(JulianneGUID)
            {
                Creature* Julianne = (ObjectAccessor::GetCreature((*me), JulianneGUID));
                if(Julianne && Julianne->GetVictim())
                {
                    me->GetThreatManager().AddThreat(Julianne->GetVictim(), 1.0f);
                    AttackStart(Julianne->GetVictim());
                }
            }
        }
    
        void MoveInLineOfSight(Unit* who)
        override {
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
    
            ScriptedAI::MoveInLineOfSight(who);
        }
    
        void JustDied(Unit* /*killer*/)
        override {
            DoScriptText(SAY_ROMULO_DEATH, me);
        }
    
        void KilledUnit(Unit* victim)
        override {
            DoScriptText(SAY_ROMULO_SLAY, me);
        }
    
        void UpdateAI(const uint32 diff) override;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_romuloAI(creature);
    }
};

void boss_julianne::boss_julianneAI::DamageTaken(Unit* done_by, uint32 &damage)
{
    if (damage < me->GetHealth())
        return;

    if (done_by && (done_by == me || done_by->GetGUID() == RomuloGUID))
        return;

    if (Phase == PHASE_JULIANNE)
    {
        DoScriptText(SAY_JULIANNE_DEATH01, me);
        me->InterruptNonMeleeSpells(true);
        DoCast(me, SPELL_DRINK_POISON);
        PretendToDie(me);
        Phase = PHASE_ROMULO;
        damage = 0;
        IsFakingDeath = true;
        SummonRomuloTimer = 10000;
        return;
    }

    if (!IsFakingDeath)
    {
        Creature* Romulo = (ObjectAccessor::GetCreature((*me), RomuloGUID));
        if (Romulo && Romulo->IsAlive() && !((boss_romulo::boss_romuloAI*)Romulo->AI())->IsFakingDeath)
        {
            ((boss_romulo::boss_romuloAI*)Romulo->AI())->ResurrectTimer = 10000;
            ((boss_romulo::boss_romuloAI*)Romulo->AI())->JulianneDead = true;
        }
        else
        {
            if (Romulo)
                KillLovers(me, Romulo, done_by);
            return;
        }

        IsFakingDeath = true;
        PretendToDie(me);
        damage = 0;
    }
    else
        damage = 0;
}

void boss_julianne::boss_julianneAI::UpdateAI(const uint32 diff)
{
    if (EntryYellTimer)
    {
        if (EntryYellTimer < diff)
        {
            DoScriptText(SAY_JULIANNE_ENTER, me);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            EntryYellTimer = 0;
        }
        else EntryYellTimer -= diff;
    }

    if (AggroYellTimer)
    {
        if (AggroYellTimer < diff)
        {
            DoScriptText(SAY_JULIANNE_AGGRO, me);
            AggroYellTimer = 0;
        }
        else AggroYellTimer -= diff;
    }

    if (Phase == PHASE_ROMULO && !SummonedRomulo)
    {
        if (SummonRomuloTimer < diff)
        {
            Creature* Romulo = me->SummonCreature(CREATURE_ROMULO, ROMULO_X, ROMULO_Y, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 45000);
            if (Romulo)
            {
                RomuloGUID = Romulo->GetGUID();
                ((boss_romulo::boss_romuloAI*)Romulo->AI())->JulianneGUID = me->GetGUID();
                ((boss_romulo::boss_romuloAI*)Romulo->AI())->Phase = PHASE_ROMULO;
                if (me->GetVictim())
                {
                    Romulo->AI()->AttackStart(me->GetVictim());
                    Romulo->GetThreatManager().AddThreat(me->GetVictim(), 50.0f);
                }
                DoZoneInCombat(Romulo);
            }
            SummonedRomulo = true;
        }
        else SummonRomuloTimer -= diff;
    }

    if (!UpdateVictim() || IsFakingDeath)
        return;

    if (RomuloDead)
    {
        if (ResurrectTimer < diff)
        {
            Creature* Romulo = (ObjectAccessor::GetCreature((*me), RomuloGUID));
            if (Romulo && ((boss_romulo::boss_romuloAI*)Romulo->AI())->IsFakingDeath)
            {
                DoScriptText(SAY_JULIANNE_RESURRECT, me);
                Resurrect(Romulo);
                ((boss_romulo::boss_romuloAI*)Romulo->AI())->IsFakingDeath = false;
                ResurrectTimer = 10000;
            }
            RomuloDead = false;
        }
        else ResurrectTimer -= diff;
    }

    if (BlindingPassionTimer < diff)
    {
        DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_BLINDING_PASSION);
        BlindingPassionTimer = 30000 + rand() % 15000;
    }
    else BlindingPassionTimer -= diff;

    if (DevotionTimer < diff)
    {
        DoCast(me, SPELL_DEVOTION);
        DevotionTimer = 15000 + rand() % 30000;
    }
    else DevotionTimer -= diff;

    if (PowerfulAttractionTimer < diff)
    {
        DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_POWERFUL_ATTRACTION);
        PowerfulAttractionTimer = 5000 + rand() % 25000;
    }
    else PowerfulAttractionTimer -= diff;

    if (EternalAffectionTimer < diff)
    {
        if (rand() % 2 == 1 && SummonedRomulo)
        {
            Creature* Romulo = (ObjectAccessor::GetCreature((*me), RomuloGUID));
            if (Romulo && Romulo->IsAlive() && !((boss_romulo::boss_romuloAI*)Romulo->AI())->IsFakingDeath)
                DoCast(Romulo, SPELL_ETERNAL_AFFECTION);
            else
                return;
        }
        else DoCast(me, SPELL_ETERNAL_AFFECTION);

        EternalAffectionTimer = 45000 + rand() % 15000;
    }
    else EternalAffectionTimer -= diff;

    DoMeleeAttackIfReady();
}

void boss_romulo::boss_romuloAI::DamageTaken(Unit* done_by, uint32 &damage)
{
    if (damage < me->GetHealth())
        return;

    if(done_by && (done_by == me || done_by->GetGUID() == JulianneGUID))
        return;

    if (!IsFakingDeath)
    {
        IsFakingDeath = true;
        PretendToDie(me);

        if (Phase == PHASE_BOTH)
        {
            Creature* Julianne = (ObjectAccessor::GetCreature((*me), JulianneGUID));
            if (Julianne && Julianne->IsAlive() && !((boss_julianne::boss_julianneAI*)Julianne->AI())->IsFakingDeath)
            {
                ((boss_julianne::boss_julianneAI*)Julianne->AI())->ResurrectTimer = 10000;
                ((boss_julianne::boss_julianneAI*)Julianne->AI())->RomuloDead = true;
            }
            else
            {
                if (Julianne)
                    KillLovers(me, Julianne, done_by);
                return;
            }
        }
        else
        {
            Creature* Julianne = (ObjectAccessor::GetCreature((*me), JulianneGUID));
            if (Julianne)
            {
                Resurrect(Julianne);
                me->SetHealth(me->GetMaxHealth());
                ((boss_julianne::boss_julianneAI*)Julianne->AI())->ResurrectTimer = 4000;
                ((boss_julianne::boss_julianneAI*)Julianne->AI())->RomuloDead = true;
                ((boss_julianne::boss_julianneAI*)Julianne->AI())->Phase = PHASE_BOTH;
                ((boss_julianne::boss_julianneAI*)Julianne->AI())->IsFakingDeath = false;
            }
            Phase = PHASE_BOTH;
        }

        damage = 0;
    }

    if (IsFakingDeath)
        damage = 0;
}

void boss_romulo::boss_romuloAI::UpdateAI(const uint32 diff)
{
    if (!UpdateVictim() || IsFakingDeath)
        return;

    if (JulianneDead)
    {
        if (ResurrectTimer < diff)
        {
            Creature* Julianne = (ObjectAccessor::GetCreature((*me), JulianneGUID));
            if (Julianne && ((boss_julianne::boss_julianneAI*)Julianne->AI())->IsFakingDeath)
            {
                DoScriptText(SAY_ROMULO_RESURRECT, me);
                Resurrect(Julianne);
                ((boss_julianne::boss_julianneAI*)Julianne->AI())->IsFakingDeath = false;
                ResurrectTimer = 10000;
            }
            JulianneDead = false;
        }
        else ResurrectTimer -= diff;
    }

    if (BackwardLungeTimer < diff)
    {
        Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0, true, true);
        if (target && !me->HasInArc(M_PI, target))
        {
            DoCast(target, SPELL_BACKWARD_LUNGE);
            BackwardLungeTimer = 15000 + rand() % 15000;
        }
    }
    else BackwardLungeTimer -= diff;

    if (DaringTimer < diff)
    {
        DoCast(me, SPELL_DARING);
        DaringTimer = 20000 + rand() % 20000;
    }
    else DaringTimer -= diff;

    if (DeadlySwatheTimer < diff)
    {
        DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_DEADLY_SWATHE);
        DeadlySwatheTimer = 15000 + rand() % 10000;
    }
    else DeadlySwatheTimer -= diff;

    if (PoisonThrustTimer < diff)
    {
        DoCast(me->GetVictim(), SPELL_POISON_THRUST);
        PoisonThrustTimer = 10000 + rand() % 10000;
    }
    else PoisonThrustTimer -= diff;

    DoMeleeAttackIfReady();
}


/*######
# npc_barnesAI
######*/

#define GOSSIP_READY        "I'm not an actor."

#define SAY_READY           "Splendid, I'm going to get the audience ready. Break a leg!"
#define SAY_OZ_INTRO1       "Finally, everything is in place. Are you ready for your big stage debut?"
#define OZ_GOSSIP1          "I'm not an actor."
#define SAY_OZ_INTRO2       "Don't worry, you'll be fine. You look like a natural!"
#define OZ_GOSSIP2          "Ok, I'll give it a try, then."

#define SAY_RAJ_INTRO1      "The romantic plays are really tough, but you'll do better this time. You have TALENT. Ready?"
#define RAJ_GOSSIP1         "I've never been more ready."

struct Dialogue
{
    int32 textid;
    uint32 timer;
};

static Dialogue OzDialogue[] =
{
    { -1532103, 6000 },
    { -1532104, 18000 },
    { -1532105, 9000 },
    { -1532106, 15000 }
};

static Dialogue HoodDialogue[] =
{
    { -1532107, 6000 },
    { -1532108, 10000 },
    { -1532109, 14000 },
    { -1532110, 15000 }
};

static Dialogue RAJDialogue[] =
{
    { -1532111, 5000 },
    { -1532112, 7000 },
    { -1532113, 14000 },
    { -1532114, 14000 }
};

// Entries and spawn locations for creatures in Oz event
float Spawns[6][2] =
{
    { 17535, -10896 },                                        // Dorothee
    { 17546, -10891 },                                        // Roar
    { 17547, -10884 },                                        // Tinhead
    { 17543, -10902 },                                        // Strawman
    { 17603, -10892 },                                        // Grandmother
    { 17534, -10900 },                                        // Julianne
}; 

float StageLocations[6][2] =
{
    { -10866.711f, -1779.816f },                                // Open door, begin walking (0)
    { -10894.917f, -1775.467f },                                // (1)
    { -10896.044f, -1782.619f },                                // Begin Speech after this (2)
    { -10894.917f, -1775.467f },                                // Resume walking (back to spawn point now) after speech (3)
    { -10866.711f, -1779.816f },                                // (4)
    { -10866.700f, -1781.030f }                                 // Summon mobs, open curtains, close door (5)
};

#define CREATURE_SPOTLIGHT  19525

#define SPELL_SPOTLIGHT     25824
#define SPELL_TUXEDO        32616

#define SPAWN_Z             90.5f
#define SPAWN_Y             -1758.0f
#define SPAWN_O             4.738f

class npc_barnes : public CreatureScript
{
public:
    npc_barnes() : CreatureScript("npc_barnes")
    { }

    class npc_barnesAI : public EscortAI
    {
    public:
        npc_barnesAI(Creature* c) : EscortAI(c)
        {
            RaidWiped = false;
            pInstance = ((InstanceScript*)c->GetInstanceScript());

            for (uint8 i = 0; i < 6; ++i)
                AddWaypoint(i, StageLocations[i][0], StageLocations[i][1], 90.465);

            PrepareStageSet();
        }

        InstanceScript* pInstance;

        ObjectGuid SpotlightGUID;

        uint32 TalkCount;
        uint32 TalkTimer;
        uint32 CurtainTimer;
        uint32 WipeTimer;
        uint32 Event;

        bool PerformanceReady;
        bool RaidWiped;
        bool IsTalking;

        void JustEngagedWith(Unit* who) override
        { }

        void Reset() override 
        {
            TalkCount = 0;
            TalkTimer = 2000;
            CurtainTimer = 5000;
            WipeTimer = 5000;
            RaidWiped = false;

            PerformanceReady = false;
            IsTalking = false;

            if (pInstance)
            {
                if (pInstance->GetBossState(DATA_OPERA_EVENT) == DONE)
                {
                    me->SetVisible(false);
                    return;
                }
                pInstance->SetBossState(DATA_OPERA_EVENT, NOT_STARTED);

                Event = pInstance->GetData(DATA_OPERA_PERFORMANCE);

                if (GameObject* Door = GameObject::GetGameObject((*me), pInstance->GetGuidData(DATA_GAMEOBJECT_STAGEDOORLEFT)))
                {
                    if (RaidWiped)
                        pInstance->HandleGameObject(pInstance->GetGuidData(DATA_GAMEOBJECT_STAGEDOORLEFT), true);
                    else
                        pInstance->HandleGameObject(pInstance->GetGuidData(DATA_GAMEOBJECT_STAGEDOORLEFT), false);
                }

                if (GameObject* Curtain = GameObject::GetGameObject((*me), pInstance->GetGuidData(DATA_GAMEOBJECT_CURTAINS)))
                    Curtain->ResetDoorOrButton();
            }
        }

        void WaypointReached(uint32 i, uint32 pathID)
            override {
            switch (i)
            {
            case 2:
                SetEscortPaused(true);
                TalkCount = 0;
                IsTalking = true;

                float x, y, z;
                me->GetPosition(x, y, z);
                if (Creature* Spotlight = me->SummonCreature(CREATURE_SPOTLIGHT, x, y, z, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 50000))
                {
                    Spotlight->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    Spotlight->CastSpell(Spotlight, SPELL_SPOTLIGHT, TRIGGERED_NONE);
                    SpotlightGUID = Spotlight->GetGUID();
                }
                break;

            case 5:
                if (pInstance)
                {
                    pInstance->HandleGameObject(pInstance->GetGuidData(DATA_GAMEOBJECT_STAGEDOORLEFT), false);
                }
                SetEscortPaused(false);
                PerformanceReady = true;
                me->SetVisible(false);
                break;
            }
        }

        void Talk(uint32 count)
        {
            int32 text = 0;

            switch (Event)
            {
            case EVENT_OZ:
                if (OzDialogue[count].textid)
                    text = OzDialogue[count].textid;
                if (OzDialogue[count].timer)
                    TalkTimer = OzDialogue[count].timer;
                break;

            case EVENT_HOOD:
                if (HoodDialogue[count].textid)
                    text = HoodDialogue[count].textid;
                if (HoodDialogue[count].timer)
                    TalkTimer = HoodDialogue[count].timer;
                break;

            case EVENT_RAJ:
                if (RAJDialogue[count].textid)
                    text = RAJDialogue[count].textid;
                if (RAJDialogue[count].timer)
                    TalkTimer = RAJDialogue[count].timer;
                break;
            }

            if (text)
                DoScriptText(text, me);
        }

        void UpdateAI(const uint32 diff)
            override {
            EscortAI::UpdateAI(diff);

            if (IsTalking)
            {
                if (TalkTimer < diff)
                {
                    if (TalkCount > 3)
                    {
                        if (Unit* Spotlight = ObjectAccessor::GetUnit((*me), SpotlightGUID))
                        {
                            Spotlight->RemoveAllAuras();
                            Spotlight->SetVisible(false);
                        }

                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                        IsTalking = false;
                        SetEscortPaused(false);
                        return;
                    }

                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_TALK);
                    Talk(TalkCount);
                    ++TalkCount;
                }
                else TalkTimer -= diff;
            }

            if (PerformanceReady)
            {
                if (CurtainTimer)
                {
                    if (CurtainTimer <= diff)
                    {
                        PrepareEncounter();

                        if (!pInstance)
                            return;

                        if (GameObject* Curtain = GameObject::GetGameObject((*me), pInstance->GetGuidData(DATA_GAMEOBJECT_CURTAINS)))
                            Curtain->UseDoorOrButton();

                        CurtainTimer = 0;
                    }
                    else CurtainTimer -= diff;
                }

                if (!RaidWiped)
                {
                    if (WipeTimer < diff)
                    {
                        Map *map = me->GetMap();
                        if (!map->IsDungeon()) return;

                        Map::PlayerList const &PlayerList = map->GetPlayers();
                        if (PlayerList.isEmpty())
                            return;

                        RaidWiped = true;
                        for (const auto & i : PlayerList)
                        {
                            if (i.GetSource()->IsAlive() && !i.GetSource()->IsGameMaster())
                            {
                                RaidWiped = false;
                                break;
                            }
                        }

                        if (RaidWiped)
                        {
                            RaidWiped = true;
                            EnterEvadeMode();
                            return;
                        }

                        WipeTimer = 15000;
                    }
                    else WipeTimer -= diff;
                }

            }
        }

        void StartEvent()
        {
            if (!pInstance)
                return;

            pInstance->SetBossState(DATA_OPERA_EVENT, IN_PROGRESS);

            pInstance->HandleGameObject(pInstance->GetGuidData(DATA_GAMEOBJECT_STAGEDOORLEFT), true);

            me->CastSpell(me, SPELL_TUXEDO, TRIGGERED_FULL_MASK);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            SetDespawnAtEnd(false);
            Start(false, false, ObjectGuid::Empty);
        }

        void PrepareStageSet()
        {
            Position backdropLoc(-10890.9, -1744.06, 90.4765, -1.67552);
            G3D::Quat backdropRotation(0, 0, -0.743146, 0.669129);
            switch (Event)
            {
            case EVENT_OZ:
                me->SummonGameObject(OPERA_BACKDROP_WIZARD_OF_OZ, backdropLoc, backdropRotation, 0);
                me->SummonGameObject(OPERA_WIZARD_OF_OZ_HAY, Position(-10909.5, -1761.79, 90.4773, -1.65806), G3D::Quat(0, 0, -0.737276, 0.675591), 0);
                me->SummonGameObject(OPERA_WIZARD_OF_OZ_HAY, Position(-10877.7, -1763.18, -1.69297, -1.65806), G3D::Quat(0, 0, -0.737276, 0.675591), 0);
                me->SummonGameObject(OPERA_WIZARD_OF_OZ_HAY, Position(-10883, -1751.81, 90.4765, -1.65806), G3D::Quat(0, 0, -0.737276, 0.675591), 0);
                me->SummonGameObject(OPERA_WIZARD_OF_OZ_HAY, Position(-10906.7, -1750.01, 90.4765, -1.65806), G3D::Quat(0, 0, -0.737276, 0.675591), 0);
                break;

            case EVENT_HOOD:
                me->SummonGameObject(OPERA_BACKDROP_RED_RIDING, backdropLoc, backdropRotation, 0);
                me->SummonGameObject(OPERA_RED_RIDING_HOOD_TREE, Position(-10881.7, -1753.65, 90.4771, 4.41055), G3D::Quat(0, 0, -0.737276, 0.675591), 0);
                me->SummonGameObject(OPERA_RED_RIDING_HOOD_TREE, Position(-10874.7, -1758.96, 90.4765, 4.18043), G3D::Quat(0, 0, 0.868108, -0.496376), 0);
                me->SummonGameObject(OPERA_RED_RIDING_HOOD_HOUSE, Position(-10903.8, -1749.94, 90.4766, 4.84016), G3D::Quat(0, 0, 0.66052, -0.750809), 0);
                break;

            case EVENT_RAJ:
                me->SummonGameObject(OPERA_BACKDROP_ROMEO_AND_JULIET, backdropLoc, backdropRotation, 0);
                me->SummonGameObject(OPERA_ROMEO_AND_JULIET_MOON, Position(-10903.4, -1752.81, 108.539, 4.67092), G3D::Quat(0, 0, 4.67092, -0.692293), 0);
                me->SummonGameObject(OPERA_ROMEO_AND_JULIET_BALCONY, Position(-10891.3, -1752.24, 90.4768, 4.6039), G3D::Quat(0, 0, 0.744405, -0.667729), 0);
                break;
            }
        }

        void PrepareEncounter()
        {
            uint8 index = 0;
            uint8 count = 0;
            Position backdropLoc(-10890.9, -1744.06, 90.4765, -1.67552);
            G3D::Quat backdropRotation(0, 0, -0.743146, 0.669129);
            switch (Event)
            {
            case EVENT_OZ:
                index = 0;
                count = 4;
                break;
            case EVENT_HOOD:
                index = 4;
                count = index + 1;
                break;
            case EVENT_RAJ:
                index = 5;
                count = index + 1;
                break;
            }

            for (; index < count; ++index)
            {
                uint32 entry = ((uint32)Spawns[index][0]);
                float PosX = Spawns[index][1];
                if (Creature* pCreature = me->SummonCreature(entry, PosX, SPAWN_Y, SPAWN_Z, SPAWN_O, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2 * MINUTE * IN_MILLISECONDS))
                {
                    // In case database has bad flags
                    pCreature->SetUInt32Value(UNIT_FIELD_FLAGS, 0);
                    pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
            }

            CurtainTimer = 10000;
            PerformanceReady = true;
            RaidWiped = false;
        }

        virtual bool GossipHello(Player* player) override
        {
            // Check for death of Moroes.
            if (pInstance && (pInstance->GetBossState(DATA_OPERA_EVENT) < DONE))
            {
                if (pInstance->GetBossState(DATA_MOROES_EVENT) >= DONE)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OZ_GOSSIP1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

                    if (!((npc_barnes::npc_barnesAI*)me->AI())->RaidWiped)
                        player->SEND_GOSSIP_MENU_TEXTID(8970, me->GetGUID()); //try again text
                    else
                        player->SEND_GOSSIP_MENU_TEXTID(8975, me->GetGUID());
                }
                else {
                    player->SEND_GOSSIP_MENU_TEXTID(8972, me->GetGUID()); //Someone should take care of Moroes
                }
            }

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OZ_GOSSIP2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(8971, me->GetGUID());
                break;

            case GOSSIP_ACTION_INFO_DEF + 2:
                player->CLOSE_GOSSIP_MENU();
                ((npc_barnes::npc_barnesAI*)me->AI())->StartEvent();
                break;
            }

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<npc_barnesAI>(creature);
    }
};

void AddSC_bosses_opera()
{
    // Oz
    new boss_dorothee();
    new boss_strawman();
    new boss_tinhead();
    new boss_roar();
    new boss_crone();
    new mob_tito();
    new mob_cyclone();

    // Hood
    new npc_grandmother();
    new boss_bigbadwolf();

    // Romeo And Juliet
    new boss_julianne();
    new boss_romulo();

    new npc_barnes();
}

