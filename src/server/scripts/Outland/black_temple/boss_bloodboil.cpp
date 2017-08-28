
#include "def_black_temple.h"

//Speech'n'Sound
enum Says
{
    SAY_AGGRO               = -1564029,
    SAY_SLAY1               = -1564030,
    SAY_SLAY2               = -1564031,
    SAY_SPECIAL1            = -1564032,
    SAY_SPECIAL2            = -1564033,
    SAY_ENRAGE1             = -1564034,
    SAY_ENRAGE2             = -1564035,
    SAY_DEATH               = -1564036
};

//Spells
enum Spells
{
    //Phase 1
    SPELL_ARCING_SMASH_1        = 40457,
    SPELL_ACIDIC_WOUND          = 40484, //Trigger Aura
    SPELL_BEWILDERING_STRIKE    = 40491,
    SPELL_EJECT_1               = 40486,
    SPELL_FELBREATH_1           = 40508,
    SPELL_BLOODBOIL             = 42005,

    //Phase 2
    SPELL_ARCING_SMASH_2        = 40599,
    SPELL_EJECT_2               = 40597,
    SPELL_FELBREATH_2           = 40595,
    SPELL_FEL_GEYSER            = 40593,

    //Fel Rage
    SPELL_INSIGNIFIGANCE        = 40618,
    SPELL_TAUNT_GURTOGG         = 40603,
    SPELL_FEL_RAGE_SELF         = 40594,
    SPELL_FEL_RAGE_1            = 40604,
    SPELL_FEL_RAGE_2            = 40616,
    SPELL_FEL_RAGE_3            = 41625,
    SPELL_FEL_RAGE_SCALE        = 46787,

    SPELL_CHARGE                = 40602,
    SPELL_BERSERK               = 45078,

    SPELL_SELFSTUN              = 53088, //2.5s stun
};

#define COORD_Z_HOME                64.0f

//This is used to sort the players by distance in preparation for the Bloodboil cast.
struct ObjectDistanceOrderReversed : public std::binary_function<const WorldObject, const WorldObject, bool>
{
    const Unit* m_pSource;
    ObjectDistanceOrderReversed(const Unit* pSource) : m_pSource(pSource) {};

    bool operator()(const WorldObject* pLeft, const WorldObject* pRight) const
    {
        return !m_pSource->GetDistanceOrder(pLeft, pRight);
    }
};


class boss_gurtogg_bloodboil : public CreatureScript
{
public:
    boss_gurtogg_bloodboil() : CreatureScript("boss_gurtogg_bloodboil")
    { }

    class boss_gurtogg_bloodboilAI : public ScriptedAI
    {
        public:
        boss_gurtogg_bloodboilAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        uint64 TargetGUID;
    
        float TargetThreat;
    
        uint32 BloodboilTimer;
        uint32 BloodboilCount;
        
        uint32 FelGeyserTimer;
        uint32 BewilderingStrikeTimer;
        
        uint32 ArcingSmashTimer;
        uint32 FelBreathTimer;
        uint32 EjectTimer;
    
        uint32 PhaseChangeTimer;
    
        uint32 EnrageTimer;
    
        uint32 Charge_Timer;
    
        bool Phase1;
    
        void Reset() override
        {
            if(pInstance && me->IsAlive())
                pInstance->SetData(DATA_GURTOGGBLOODBOILEVENT, NOT_STARTED);
    
            TargetGUID = 0;
    
            TargetThreat = 0;
    
            BloodboilTimer = 10000;
            BloodboilCount = 0;
    
            FelGeyserTimer = 1000;
            BewilderingStrikeTimer = 15000;
    
            ArcingSmashTimer = 19000;
            FelBreathTimer = 25000;
            EjectTimer = 10000;
    
            PhaseChangeTimer = 60000;
            EnrageTimer = 600000;
    
            Phase1 = true;
    
            Charge_Timer = 30000;
    
          /*  me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, false); // FIXME: false? Typo?
            me->ApplySpellImmune(0, IMMUNITY_EFFECT,SPELL_EFFECT_ATTACK_ME, false); */
            me->SetFullTauntImmunity(true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);
        }
    
        void EnterCombat(Unit *who) override
        {
            DoZoneInCombat();
            DoScriptText(SAY_AGGRO, me);
            if(pInstance)
                pInstance->SetData(DATA_GURTOGGBLOODBOILEVENT, IN_PROGRESS);
        }
    
        void KilledUnit(Unit *victim) override
        {
            DoScriptText(RAND(SAY_SLAY1,SAY_SLAY2), me);
        }
    
        void JustDied(Unit *victim) override
        {
            if(pInstance)
                pInstance->SetData(DATA_GURTOGGBLOODBOILEVENT, DONE);
    
            DoScriptText(SAY_DEATH, me);
        }
    
        // Note: This seems like a very complicated fix. The fix needs to be handled by the core, as implementation of limited-target AoE spells are still not limited.
        void CastBloodboil()
        {
            std::list<Unit *> targets;
            Map *map = me->GetMap();
            if(map->IsDungeon())
            {
                InstanceMap::PlayerList const &PlayerList = ((InstanceMap*)map)->GetPlayers();
                for (const auto & i : PlayerList)
                {
                    if (Player* i_pl = i.GetSource())
                    {
                        if (i_pl && i_pl->IsAttackableByAOE())
                            targets.push_back(i_pl);
                    }
                }
            }
    
            //Sort the list of players
            targets.sort(ObjectDistanceOrderReversed(me));
            //Resize so we only get top 5
            if(targets.size() > 5)
                targets.resize(5);
    
            //Aura each player in the targets list with Bloodboil.
            for(auto player : targets)
            {
                if(player && player->IsAlive())
                    me->AddAura(SPELL_BLOODBOIL, player);
            }
            targets.clear();
        }
    
        void RevertThreatOnTarget(uint64 guid)
        {
            Unit* pUnit = nullptr;
            pUnit = ObjectAccessor::GetUnit((*me), guid);
            if(pUnit)
            {
                if(me->GetThreat(pUnit))
                    DoModifyThreatPercent(pUnit, -100);
                if(TargetThreat)
                    me->AddThreat(pUnit, TargetThreat);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //do not update victim if we already have one on phase 2 (extra security to be sure)
            if(!UpdateVictim())
                return;
            if (!Phase1 && me->GetVictim()->GetGUID() != TargetGUID)
            {
                Unit* target = ObjectAccessor::GetUnit((*me), TargetGUID);
                if (target && me->CanAttack(target) == CAN_ATTACK_RESULT_OK)
                    AttackStart(target);
            }
                
            if(!me->HasAuraEffect(SPELL_BERSERK, 0))
            {
                if(EnrageTimer < diff)
                {
                    DoCast(me, SPELL_BERSERK);
                    switch(rand()%2)
                    {
                    case 0: DoScriptText(SAY_ENRAGE1, me); break;
                    case 1: DoScriptText(SAY_ENRAGE2, me); break;
                    }
                }else EnrageTimer -= diff;
            }
    
            if(FelBreathTimer < diff)
            {
                if(DoCast(me->GetVictim(),Phase1 ? SPELL_FELBREATH_1 : SPELL_FELBREATH_2) == SPELL_CAST_OK)
                    FelBreathTimer = 25000;
            }else FelBreathTimer -= diff;
            
            if(EjectTimer < diff)
            {
                if(DoCast(me->GetVictim(),Phase1 ? SPELL_EJECT_1 : SPELL_EJECT_2) == SPELL_CAST_OK)
                    EjectTimer = 15000;
            }else EjectTimer -= diff;
    
            if(Charge_Timer < diff)
            {
                if(me->GetVictim() && me->GetDistance2d(me->GetVictim()) > 15)
                    DoCast(me->GetVictim(),SPELL_CHARGE);
                Charge_Timer = 10000;
            }else Charge_Timer -= diff;
    
            if(Phase1)
            {
                if(BewilderingStrikeTimer < diff)
                {
                    if(DoCast(me->GetVictim(), SPELL_BEWILDERING_STRIKE) == SPELL_CAST_OK)
                        BewilderingStrikeTimer = 20000;
                }else BewilderingStrikeTimer -= diff;
    
                if(BloodboilTimer < diff)
                {
                    if(BloodboilCount < 5)                      // Only cast it five times.
                    {
                        CastBloodboil();
                        ++BloodboilCount;
                        BloodboilTimer = 10000;
                    }
                }else BloodboilTimer -= diff;
                
                if(ArcingSmashTimer < diff)
                {
                    if(DoCast(me->GetVictim(), SPELL_ARCING_SMASH_1) == SPELL_CAST_OK)
                        ArcingSmashTimer = 10000;
                }else ArcingSmashTimer -= diff;
            }
    
            if(!Phase1)
            {
                if(FelGeyserTimer < diff)
                {
                    if(DoCast(me->GetVictim(), SPELL_FEL_GEYSER) == SPELL_CAST_OK)
                        FelGeyserTimer = 30000;
                }else FelGeyserTimer -= diff;
    
                if(me->GetVictim() && me->GetVictim()->IsImmunedToDamage(SPELL_SCHOOL_MASK_ALL))
                    me->getThreatManager().modifyThreatPercent(me->GetVictim(),-100);
            }
    
            if(PhaseChangeTimer < diff)
            {
                if(Phase1)
                {
                    Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50000, true);
                    if(target && me->CanAttack(target) == CAN_ATTACK_RESULT_OK)
                    {
                        Phase1 = false;
    
                        //TargetThreat = me->GetThreat(target);
                        TargetGUID = target->GetGUID();
                        /*if(me->GetThreat(target))
                            DoModifyThreatPercent(target, -100);*/
                        me->AddThreat(target, 50000000.0f);
                        target->CastSpell(me, SPELL_TAUNT_GURTOGG, true);
                        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                        me->ApplySpellImmune(0, IMMUNITY_EFFECT,SPELL_EFFECT_ATTACK_ME, true);
                        
                        // If VMaps are disabled, this spell can call the whole instance
                        target->ApplySpellImmune(0, IMMUNITY_ID, SPELL_INSIGNIFIGANCE, true);
                        DoCast(me, SPELL_INSIGNIFIGANCE, true);
                        DoCast(target,SPELL_FEL_RAGE_1, true);
                        DoCast(target,SPELL_FEL_RAGE_2, true);
                        DoCast(target,SPELL_FEL_RAGE_3, true);
                        DoCast(target,SPELL_FEL_RAGE_SCALE, true);
                        target->ApplySpellImmune(0, IMMUNITY_ID, SPELL_INSIGNIFIGANCE, false);
    
                        //Cast this without triggered so that it appears in combat logs and shows visual.
                        DoCast(me, SPELL_FEL_RAGE_SELF);
    
                        DoScriptText(RAND(SAY_SPECIAL1,SAY_SPECIAL2), me);
                        DoCast(me,SPELL_SELFSTUN,true); //2,5 inactivity
    
                        FelGeyserTimer = 1000;
                        PhaseChangeTimer = 30000;
                    }
                }
                else                                           // Encounter is a loop pretty much. Phase 1 -> Phase 2 -> Phase 1 -> Phase 2 till death or enrage
                {
                    if(TargetGUID)
                        RevertThreatOnTarget(TargetGUID);
                    DoResetThreat();
                    TargetGUID = 0;
                    Phase1 = true;
                    BloodboilTimer = 10000;
                    BloodboilCount = 0;
                    ArcingSmashTimer += 2000;
                    FelBreathTimer += 2000;
                    EjectTimer += 2000;
                    PhaseChangeTimer = 60000;
                    me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, false);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT,SPELL_EFFECT_ATTACK_ME, false);
                }
            }else PhaseChangeTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_gurtogg_bloodboilAI(creature);
    }
};


void AddSC_boss_gurtogg_bloodboil()
{
    new boss_gurtogg_bloodboil();
}

