
/* ScriptData
SDName: Boss_Leotheras_The_Blind
SD%Complete: 80
SDComment: Possesion Support
SDCategory: Coilfang Resevoir, Serpent Shrine Cavern
EndScriptData */


#include "def_serpent_shrine.h"

// --- Spells used by Leotheras The Blind
#define SPELL_WHIRLWIND         37640
#define SPELL_CHAOS_BLAST       37674
#define SPELL_BERSERK           26662
#define SPELL_INSIDIOUS_WHISPER 37676
#define SPELL_DUAL_WIELD        42459

// --- Spells used in banish phase ---
#define BANISH_BEAM             38909
#define AURA_BANISH             37833

// --- Spells used by Greyheart Spellbinders
#define SPELL_EARTHSHOCK        39076
#define SPELL_MINDBLAST         37531

// --- Spells used by Inner Demons and creature ID
#define INNER_DEMON_ID          21857
#define AURA_DEMONIC_ALIGNMENT  37713
#define SPELL_SHADOWBOLT        39309
#define SPELL_SOUL_LINK         38007
#define SPELL_CONSUMING_MADNESS 37749 //not supported by core yet

//Misc.
#define MODEL_DEMON             20125
#define MODEL_NIGHTELF          20514
#define DEMON_FORM              21875
#define MOB_SPELLBINDER         21806

#define SAY_AGGRO               -1548009
#define SAY_SWITCH_TO_DEMON     -1548010
#define SAY_INNER_DEMONS        -1548011
#define SAY_DEMON_SLAY1         -1548012
#define SAY_DEMON_SLAY2         -1548013
#define SAY_DEMON_SLAY3         -1548014
#define SAY_NIGHTELF_SLAY1      -1548015
#define SAY_NIGHTELF_SLAY2      -1548016
#define SAY_NIGHTELF_SLAY3      -1548017
#define SAY_FINAL_FORM          -1548018
#define SAY_FREE                -1548019
#define SAY_DEATH               -1548020

class InsidiousAura : public Aura {
public:
    InsidiousAura(SpellInfo *spell, uint32 eff, int32 *bp, Unit *target, Unit *caster) : Aura(spell, eff, bp, target, caster, nullptr)
    {}
};


class mob_inner_demon : public CreatureScript
{
public:
    mob_inner_demon() : CreatureScript("mob_inner_demon")
    { }

    class mob_inner_demonAI : public ScriptedAI
    {
    public:
        mob_inner_demonAI(Creature *c) : ScriptedAI(c)
        {
            victimGUID = 0;
        }

        uint32 ShadowBolt_Timer;

        uint32 Link_Timer;
        uint64 victimGUID;

        void Reset()
            override {
            ShadowBolt_Timer = 10000;
            Link_Timer = 1000;
        }
        void JustDied(Unit *victim)
            override {
            Unit* pUnit = ObjectAccessor::GetUnit((*me), victimGUID);
            if (pUnit && pUnit->HasAuraEffect(SPELL_INSIDIOUS_WHISPER, 0))
                pUnit->RemoveAurasDueToSpell(SPELL_INSIDIOUS_WHISPER);
        }

        void DamageTaken(Unit *done_by, uint32 &damage)
            override {
            if (done_by->GetGUID() != victimGUID && done_by->GetGUID() != me->GetGUID())
            {
                damage = 0;
                DoModifyThreatPercent(done_by, -100);
            }
        }

        void EnterCombat(Unit *who)
            override {
            if (!victimGUID) return;
        }

        void UpdateAI(const uint32 diff)
            override {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (me->GetVictim()->GetGUID() != victimGUID)
            {
                Unit* owner = ObjectAccessor::GetUnit((*me), victimGUID);
                if (owner)
                    AttackStart(owner);
            }
            if (Link_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_SOUL_LINK, true);
                Link_Timer = 1000;
            }
            else Link_Timer -= diff;


            if (!me->HasAuraEffect(AURA_DEMONIC_ALIGNMENT, 0))
                DoCast(me, AURA_DEMONIC_ALIGNMENT, true);

            if (ShadowBolt_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_SHADOWBOLT, false);
                ShadowBolt_Timer = 10000;
            }
            else ShadowBolt_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_inner_demonAI(creature);
    }
};

//Original Leotheras the Blind AI

//Leotheras the Blind Demon Form AI
class boss_leotheras_the_blind : public CreatureScript
{
public:
    boss_leotheras_the_blind() : CreatureScript("boss_leotheras_the_blind")
    { }

    class boss_leotheras_the_blindAI : public ScriptedAI
    {
        public:
        boss_leotheras_the_blindAI(Creature *c) : ScriptedAI(c)
        {
            me->GetPosition(x,y,z);
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            Demon = 0;
    
            for(uint64 & i : SpellBinderGUID)//clear guids
                i = 0;
        }
    
        InstanceScript *pInstance;
    
        uint32 Whirlwind_Timer;
        uint32 ChaosBlast_Timer;
        uint32 SwitchToDemon_Timer;
        uint32 SwitchToHuman_Timer;
        uint32 Berserk_Timer;
        uint32 InnerDemons_Timer;
        uint32 BanishTimer;
    
        bool DealDamage;
        bool NeedThreatReset;
        bool DemonForm;
        bool IsFinalForm;
        bool EnrageUsed;
        float x,y,z;
    
        uint64 InnderDemon[5];
        uint32 InnderDemon_Count;
        uint64 Demon;
        uint64 SpellBinderGUID[3];
    
        void Reset()
        override {
            CheckChannelers();
            BanishTimer = 1000;
            Whirlwind_Timer = 15000;
            ChaosBlast_Timer = 1000;
            SwitchToDemon_Timer = 45000;
            SwitchToHuman_Timer = 60000;
            Berserk_Timer = 600000;
            InnerDemons_Timer = 30000;
            me->SetCanDualWield(true);
            DealDamage = true;
            DemonForm = false;
            IsFinalForm = false;
            NeedThreatReset = false;
            EnrageUsed = false;
            InnderDemon_Count = 0;
            me->SetSpeedRate( MOVE_RUN, 2.0f, true);
            me->SetUInt32Value(UNIT_FIELD_DISPLAYID, MODEL_NIGHTELF);
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY  , 0);
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
            me->CastSpell(me, SPELL_DUAL_WIELD, true);
            me->SetCorpseDelay(1000*60*60);
            if(pInstance)
                pInstance->SetData(DATA_LEOTHERASTHEBLINDEVENT, NOT_STARTED);
        }
    
        void CheckChannelers(bool DoEvade = true)
        {
            for(uint8 i = 0; i < 3; i++)
            {
                Creature *add = ObjectAccessor::GetCreature(*me,SpellBinderGUID[i]);
                if(add)
                    add->DespawnOrUnsummon();
    
                float nx = x;
                float ny = y;
                float o = 2.4f;
                switch (i)
                {
                    case 0: nx += 10; ny -= 5; o = 2.5f; break;
                    case 1: nx -= 8; ny -= 7; o = 0.9f; break;
                    case 2: nx -= 3; ny += 9; o = 5.0f; break;
                }
                if (Creature* binder = me->SummonCreature(MOB_SPELLBINDER, nx, ny, z, o, TEMPSUMMON_DEAD_DESPAWN, 0))
                    SpellBinderGUID[i] = binder->GetGUID();
    
            }
        }
        void MoveInLineOfSight(Unit *who)
        override {
            if(me->HasAuraEffect(AURA_BANISH, 0))
                return;
    
            if( !me->GetVictim() && me->CanAttack(who) == CAN_ATTACK_RESULT_OK && ( me->IsHostileTo( who )) && who->isInAccessiblePlaceFor(me) )
            {
                if (me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                    return;
    
                float attackRadius = me->GetAggroRange(who);
                if(me->IsWithinDistInMap(who, attackRadius))
                {
                    // Check first that object is in an angle in front of this one before LoS check
                    if( me->HasInArc(M_PI/2.0f, who) && me->IsWithinLOSInMap(who) )
                    {
                        AttackStart(who);
                    }
                }
            }
        }
    
        void StartEvent()
        {
            DoScriptText(SAY_AGGRO, me);
            if(pInstance)
                pInstance->SetData(DATA_LEOTHERASTHEBLINDEVENT, IN_PROGRESS);
        }
    
        void CheckBanish()
        {
            uint8 AliveChannelers = 0;
            for(uint64 i : SpellBinderGUID)
            {
                Unit *add = ObjectAccessor::GetUnit(*me,i);
                if (add && add->IsAlive())
                    AliveChannelers++;
            }
    
            // channelers == 0 remove banish aura
            if(AliveChannelers == 0 && me->HasAuraEffect(AURA_BANISH, 0))
            {
                // removing banish aura
                me->RemoveAurasDueToSpell(AURA_BANISH);
    
                // Leotheras is getting immune again
                me->ApplySpellImmune(AURA_BANISH, IMMUNITY_MECHANIC, MECHANIC_BANISH, true);
    
                // changing model to bloodelf
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID, MODEL_NIGHTELF);
    
                // and reseting equipment
                me->LoadEquipment(me->GetEquipmentId());
    
                if(pInstance && pInstance->GetData64(DATA_LEOTHERAS_EVENT_STARTER))
                {
                    Unit *victim = nullptr;
                    victim = ObjectAccessor::GetUnit(*me, pInstance->GetData64(DATA_LEOTHERAS_EVENT_STARTER));
                    if(victim)
                        me->getThreatManager().addThreat(victim, 1);
                    StartEvent();
                }
            }
            else if(AliveChannelers != 0 && !me->HasAuraEffect(AURA_BANISH, 0))
            {
                // channelers != 0 apply banish aura
                // removing Leotheras banish immune to apply AURA_BANISH
                me->ApplySpellImmune(AURA_BANISH, IMMUNITY_MECHANIC, MECHANIC_BANISH, false);
                DoCast(me, AURA_BANISH);
    
                // changing model
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID, MODEL_DEMON);
    
                // and removing weapons
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY  , 0);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
            }
        }
    
        //Despawn all Inner Demon summoned
        void DespawnDemon()
        {
            for(uint64 & i : InnderDemon)
            {
                if(i)
                {
                        //delete creature
                        Unit* pUnit = ObjectAccessor::GetUnit((*me), i);
                        if (pUnit && pUnit->IsAlive())
                        {
                            pUnit->DealDamage(pUnit, pUnit->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                        }
                        i = 0;
                }
            }
    
            InnderDemon_Count = 0;
        }
    
        void CastConsumingMadness() //remove this once SPELL_INSIDIOUS_WHISPER is supported by core
        {
            for(uint64 i : InnderDemon)
            {
                if(i > 0 )
                {
                    Unit* pUnit = ObjectAccessor::GetUnit((*me), i);
                    if (pUnit && pUnit->IsAlive())
                    {
                        Unit* pUnit_target = ObjectAccessor::GetUnit((*pUnit), ((mob_inner_demon::mob_inner_demonAI*)(pUnit->ToCreature())->AI())->victimGUID);
                        if( pUnit_target && pUnit_target->IsAlive())
                        {
                            pUnit->CastSpell(pUnit_target, SPELL_CONSUMING_MADNESS, true);
                            DoModifyThreatPercent(pUnit_target, -100);
                        }
                    }
                }
            }
        }
    
        void KilledUnit(Unit *victim)
        override {
            if (victim->GetTypeId() != TYPEID_PLAYER)
                return;
    
            if (DemonForm)
            {
                switch(rand()%3)
                {
                    case 0: DoScriptText(SAY_DEMON_SLAY1, me); break;
                    case 1: DoScriptText(SAY_DEMON_SLAY2, me); break;
                    case 2: DoScriptText(SAY_DEMON_SLAY3, me); break;
                }
            }
            else
            {
                switch(rand()%3)
                {
                    case 0: DoScriptText(SAY_NIGHTELF_SLAY1, me); break;
                    case 1: DoScriptText(SAY_NIGHTELF_SLAY2, me); break;
                    case 2: DoScriptText(SAY_NIGHTELF_SLAY3, me); break;
                }
            }
        }
    
        void JustDied(Unit *victim)
        override {
            DoScriptText(SAY_DEATH, me);
    
            //despawn copy
            if (Demon)
            {
                Unit *pUnit = nullptr;
                pUnit = ObjectAccessor::GetUnit((*me), Demon);
    
                if (pUnit)
                    pUnit->DealDamage(pUnit, pUnit->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
            }
            if (pInstance)
                pInstance->SetData(DATA_LEOTHERASTHEBLINDEVENT, DONE);
        }
    
        void EnterCombat(Unit *who)
        override {
            if(me->HasAuraEffect(AURA_BANISH, 0))
            return;
    
            me->LoadEquipment(me->GetEquipmentId());
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Return since we have no target
            if (me->HasAuraEffect(AURA_BANISH, 0) || !UpdateVictim())
            {
                if(BanishTimer<diff)
                {
                    CheckBanish();//no need to check every update tick
                    BanishTimer = 1000;
                }else BanishTimer -= diff;
                return;
            }
            if(me->HasAuraEffect(SPELL_WHIRLWIND, 0))
            {
                if(Whirlwind_Timer < diff)
                {
                    Unit *newTarget = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if(newTarget)
                    {
                        DoResetThreat();
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MovePoint(0,newTarget->GetPositionX(),newTarget->GetPositionY(),newTarget->GetPositionZ());
                    }
                    Whirlwind_Timer = 2000;
                }else Whirlwind_Timer -= diff;
            }
    
            // reseting after changing forms and after ending whirlwind
            if(NeedThreatReset && !me->HasAuraEffect(SPELL_WHIRLWIND, 0))
            {
                // when changing forms seting timers (or when ending whirlwind - to avoid adding new variable i use Whirlwind_Timer to countdown 2s while whirlwinding)
                if(DemonForm)
                    InnerDemons_Timer = 30000;
                else
                    Whirlwind_Timer =  15000;
    
                NeedThreatReset = false;
                DoResetThreat();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveChase(me->GetVictim());
            }
    
            //Enrage_Timer ( 10 min )
            if(Berserk_Timer < diff && !EnrageUsed)
            {
                DoCast(me, SPELL_BERSERK);
                EnrageUsed = true;
            }else Berserk_Timer -= diff;
    
            if(!DemonForm)
            {
                //Whirldind Timer
                if(!me->HasAuraEffect(SPELL_WHIRLWIND, 0))
                {
                    if(Whirlwind_Timer < diff)
                    {
                        DoCast(me, SPELL_WHIRLWIND);
                        // while whirlwinding this variable is used to countdown target's change
                        Whirlwind_Timer = 2000;
                        NeedThreatReset = true;
                    }else Whirlwind_Timer -= diff;
                }
                //Switch_Timer
    
                if(!IsFinalForm)
                {
                    if(SwitchToDemon_Timer < diff)
                    {
                        //switch to demon form
                        me->RemoveAurasDueToSpell(SPELL_WHIRLWIND,nullptr);
                        me->SetUInt32Value(UNIT_FIELD_DISPLAYID, MODEL_DEMON);
                        DoScriptText(SAY_SWITCH_TO_DEMON, me);
                        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY  , 0);
                        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
                        DemonForm = true;
                        NeedThreatReset = true;
                        SwitchToDemon_Timer = 45000;
                    }else SwitchToDemon_Timer -= diff;
                }
                
                DoMeleeAttackIfReady();
            }
            else
            {
                //ChaosBlast_Timer
                if (!me->GetVictim())
                    return;
                if(me->GetDistance(me->GetVictim()) < 30)
                    me->StopMoving();
                if(ChaosBlast_Timer < diff)
                {
                    // will cast only when in range of spell
                    if(me->GetDistance(me->GetVictim()) < 30)
                    {
                        //me->CastSpell(me->GetVictim(), SPELL_CHAOS_BLAST, true);
                        int damage = 100;
                        me->CastCustomSpell(me->GetVictim(), SPELL_CHAOS_BLAST, &damage, nullptr, nullptr, false, nullptr, nullptr, me->GetGUID());
                    }
                    ChaosBlast_Timer = 3000;
                }else ChaosBlast_Timer -= diff;
                //Summon Inner Demon
                if(InnerDemons_Timer < diff)
                {
                    std::list<HostileReference *>& ThreatList = me->getThreatManager().getThreatList();
                    std::vector<Unit *> TargetList;
                    for(auto & itr : ThreatList)
                    {
                        Unit *tempTarget = ObjectAccessor::GetUnit(*me, itr->getUnitGuid());
                        if(tempTarget && tempTarget->GetTypeId() == TYPEID_PLAYER && tempTarget->GetGUID() != me->GetVictim()->GetGUID() && TargetList.size()<5)
                            TargetList.push_back( tempTarget );
                    }
                    SpellInfo *spell = (SpellInfo *)sSpellMgr->GetSpellInfo(SPELL_INSIDIOUS_WHISPER);
                    for(auto & itr : TargetList)
                    {
                        if( itr && itr->IsAlive() )
                        {
                            Creature * demon = me->ToCreature()->SummonCreature(INNER_DEMON_ID, itr->GetPositionX()+10, itr->GetPositionY()+10, itr->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                            if(demon)
                            {
                                ((ScriptedAI *)demon->AI())->AttackStart( itr );
                                ((mob_inner_demon::mob_inner_demonAI *)demon->AI())->victimGUID = itr->GetGUID();
    
                                for (int i=0; i<3; i++)
                                {
                                    if (!spell->Effects[i].Effect)
                                        continue;
                                    itr->AddAura(new InsidiousAura(spell, i, nullptr, itr, itr));
                                }
                                if( InnderDemon_Count > 4 ) InnderDemon_Count = 0;
    
                                //Safe storing of creatures
                                InnderDemon[InnderDemon_Count] = demon->GetGUID();
    
                                //Update demon count
                                InnderDemon_Count++;
                            }
                        }
                    }
                    DoScriptText(SAY_INNER_DEMONS, me);
    
                    InnerDemons_Timer = 999999;
                }else InnerDemons_Timer -= diff;
    
                //Switch_Timer
                if(SwitchToHuman_Timer < diff)
                {
                    //switch to nightelf form
                    me->SetUInt32Value(UNIT_FIELD_DISPLAYID, MODEL_NIGHTELF);
                    me->LoadEquipment(me->GetEquipmentId());
    
                    CastConsumingMadness();
                    DespawnDemon();
    
                    DemonForm = false;
                    NeedThreatReset = true;
    
                    SwitchToHuman_Timer = 60000;
                }else SwitchToHuman_Timer -= diff;
            }
    
            if (!IsFinalForm && me->GetHealthPct() < 15)
            {
                //at this point he divides himself in two parts
                Creature *Copy = nullptr;
                Copy = DoSpawnCreature(DEMON_FORM, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 6000);
                if(Copy)
                 {
                     Demon = Copy->GetGUID();
                    if (me->GetVictim())
                        Copy->AI()->AttackStart(me->GetVictim());
                }
                //set nightelf final form
                IsFinalForm = true;
                DemonForm = false;
    
                DoScriptText(SAY_FINAL_FORM, me);
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID, MODEL_NIGHTELF);
                me->LoadEquipment(me->GetEquipmentId());
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_leotheras_the_blindAI(creature);
    }
};


class boss_leotheras_the_blind_demonform : public CreatureScript
{
public:
    boss_leotheras_the_blind_demonform() : CreatureScript("boss_leotheras_the_blind_demonform")
    { }

    class boss_leotheras_the_blind_demonformAI : public ScriptedAI
    {
        public:
        boss_leotheras_the_blind_demonformAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 ChaosBlast_Timer;
        bool DealDamage;
    
        void Reset()
        override {
            ChaosBlast_Timer = 1000;
            DealDamage = true;
        }
    
        void StartEvent()
        {
            DoScriptText(SAY_FREE, me);
        }
    
        void KilledUnit(Unit *victim)
        override {
            if (victim->GetTypeId() != TYPEID_PLAYER)
                return;
    
            switch(rand()%3)
            {
                case 0: DoScriptText(SAY_DEMON_SLAY1, me); break;
                case 1: DoScriptText(SAY_DEMON_SLAY2, me); break;
                case 2: DoScriptText(SAY_DEMON_SLAY3, me); break;
            }
        }
    
        void JustDied(Unit *victim)
        override {
            //invisibility (blizzlike, at the end of the fight he doesn't die, he disappears)
            me->CastSpell(me, 8149, true);
        }
    
        void EnterCombat(Unit *who)
        override {
            StartEvent();
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Return since we have no target
            if (!UpdateVictim() )
                return;
            //ChaosBlast_Timer
            if(me->GetDistance(me->GetVictim()) < 30)
                me->StopMoving();
    
            if(ChaosBlast_Timer < diff)
             {
                // will cast only when in range od spell
                if(me->GetDistance(me->GetVictim()) < 30)
                {
                    //me->CastSpell(me->GetVictim(),SPELL_CHAOS_BLAST,true);
                    int damage = 100;
                    me->CastCustomSpell(me->GetVictim(), SPELL_CHAOS_BLAST, &damage, nullptr, nullptr, false, nullptr, nullptr, me->GetGUID());
                    ChaosBlast_Timer = 3000;
                }
             }else ChaosBlast_Timer -= diff;
    
            //Do NOT deal any melee damage to the target.
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_leotheras_the_blind_demonformAI(creature);
    }
};


class mob_greyheart_spellbinder : public CreatureScript
{
public:
    mob_greyheart_spellbinder() : CreatureScript("mob_greyheart_spellbinder")
    { }

    class mob_greyheart_spellbinderAI : public ScriptedAI
    {
        public:
        mob_greyheart_spellbinderAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript *)c->GetInstanceScript());;
            leotherasGUID = 0;
            AddedBanish = false;
        }
    
        InstanceScript *pInstance;
    
        uint64 leotherasGUID;
    
        uint32 Mindblast_Timer;
        uint32 Earthshock_Timer;
    
        bool AddedBanish;
    
        void Reset()
        override {
            Mindblast_Timer  = 3000 + rand()%5000;
            Earthshock_Timer = 5000 + rand()%5000;
    
            if(pInstance)
            {
                pInstance->SetData64(DATA_LEOTHERAS_EVENT_STARTER, 0);
                Unit *leotheras_unit = ObjectAccessor::GetUnit(*me, leotherasGUID);
                Creature *leotheras = leotheras_unit ? leotheras_unit->ToCreature() : nullptr;
                if(leotheras && leotheras->IsAlive())
                    ((boss_leotheras_the_blind::boss_leotheras_the_blindAI*)leotheras->AI())->CheckChannelers(false);
            }
        }
    
        void EnterCombat(Unit *who)
        override {
            me->InterruptNonMeleeSpells(false);
            if(pInstance)
                pInstance->SetData64(DATA_LEOTHERAS_EVENT_STARTER, who->GetGUID());
        }
    
        void JustRespawned()
        override {
            AddedBanish = false;
            Reset();
        }
    
        void CastChanneling()
        {
            if(!me->IsInCombat() && !me->m_currentSpells[CURRENT_CHANNELED_SPELL])
            {
                if(leotherasGUID)
                {
                    Creature *leotheras = (Creature*)ObjectAccessor::GetUnit(*me, leotherasGUID);
                    if(leotheras && leotheras->IsAlive())
                        DoCast(leotheras, BANISH_BEAM);
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(pInstance)
            {
                if(!leotherasGUID)
                    leotherasGUID = pInstance->GetData64(DATA_LEOTHERAS);
    
                if(!me->IsInCombat() && pInstance->GetData64(DATA_LEOTHERAS_EVENT_STARTER))
                {
                    Unit *victim = nullptr;
                    victim = ObjectAccessor::GetUnit(*me, pInstance->GetData64(DATA_LEOTHERAS_EVENT_STARTER));
                    if(victim)
                        AttackStart(victim);
                }
            }
    
            if(!UpdateVictim())
            {
                CastChanneling();
                return;
            }
    
            if(pInstance && !pInstance->GetData64(DATA_LEOTHERAS_EVENT_STARTER))
            {
                EnterEvadeMode();
                return;
            }
    
            if(Mindblast_Timer < diff)
            {
                Unit* target = nullptr;
                target = SelectTarget(SELECT_TARGET_RANDOM,0);
    
                if ( target )DoCast(target, SPELL_MINDBLAST);
    
                Mindblast_Timer = 10000 + rand()%5000;
            }else Mindblast_Timer -= diff;
    
            if(Earthshock_Timer < diff)
            {
                Map *map = me->GetMap();
                Map::PlayerList const &PlayerList = map->GetPlayers();
                for(const auto & itr : PlayerList)
                {
                    if (Player* i_pl = itr.GetSource())
                    {
                        if (!i_pl->IsAttackableByAOE())
                            continue;
    
                        bool isCasting = false;
                        for(auto & m_currentSpell : i_pl->m_currentSpells)
                            if(m_currentSpell)
                                isCasting = true;
    
                        if(isCasting)
                        {
                            DoCast(i_pl, SPELL_EARTHSHOCK);
                            break;
                        }
                    }
                }
                Earthshock_Timer = 8000 + rand()%7000;
            }else Earthshock_Timer -= diff;
            DoMeleeAttackIfReady();
        }
    
        void JustDied(Unit *killer) override {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_greyheart_spellbinderAI(creature);
    }
};

void AddSC_boss_leotheras_the_blind()
{

    new boss_leotheras_the_blind();

    new boss_leotheras_the_blind_demonform();

    new mob_greyheart_spellbinder();

    new mob_inner_demon();
}

