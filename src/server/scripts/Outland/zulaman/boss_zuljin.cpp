
#include "def_zulaman.h"

enum {
    YELL_INTRO  = 0,
    YELL_TRANSFORM_TO_LYNX,
    YELL_TRANSFORM_TO_BEAR,
    YELL_TRANSFORM_TO_DRAGONHAWK,
    YELL_TRANSFORM_TO_EAGLE,
    YELL_KILL,
    YELL_FIRE_BREATH,
    YELL_AGGRO,
    YELL_BERSERK,
    YELL_DEATH,
};

enum {
    // Troll Form
    SPELL_WHIRLWIND                 = 17207,
    SPELL_GRIEVOUS_THROW            = 43093,   // remove debuff after full healed
    
    // Bear Form
    SPELL_CREEPING_PARALYSIS        = 43095,   // should cast on the whole raid
    SPELL_OVERPOWER                 = 43456,   // use after melee attack dodged
    
    // Eagle Form
    SPELL_ENERGY_STORM              = 43983,   // enemy area aura, trigger 42577
    SPELL_ZAP_INFORM                = 42577,
    SPELL_ZAP_DAMAGE                = 43137,   // 1250 damage
    SPELL_SUMMON_CYCLONE            = 43112,   // summon four feather vortex
    CREATURE_FEATHER_VORTEX         = 24136,
    SPELL_CYCLONE_VISUAL            = 43119,   // trigger 43147 visual
    SPELL_CYCLONE_PASSIVE           = 43120,   // trigger 43121 (4y aoe) every second
    
    // Lynx Form
    SPELL_CLAW_RAGE_CHARGE          = 42583,
    SPELL_CLAW_RAGE_TRIGGER         = 43149,
    SPELL_CLAW_RAGE_DAMAGE          = 43150,
    SPELL_LYNX_RUSH_HASTE           = 43152,
    SPELL_LYNX_RUSH_DAMAGE          = 43153,
    
    // Dragonhawk Form
    SPELL_FLAME_WHIRL               = 43213,   // trigger two spells
    SPELL_FLAME_BREATH              = 43215,
    SPELL_SUMMON_PILLAR             = 43216,   // summon 24187
    CREATURE_COLUMN_OF_FIRE         = 24187,
    SPELL_PILLAR_TRIGGER            = 43218,   // trigger 43217

    // Cosmetic
    SPELL_SPIRIT_AURA               = 42466,
    SPELL_SIPHON_SOUL               = 43501,

    // Transforms
    SPELL_SHAPE_OF_THE_BEAR         = 42594,   // 15% dmg
    SPELL_SHAPE_OF_THE_EAGLE        = 42606,
    SPELL_SHAPE_OF_THE_LYNX         = 42607,   // haste melee 30%
    SPELL_SHAPE_OF_THE_DRAGONHAWK   = 42608,

    SPELL_BERSERK                   = 45078
};

enum {
    PHASE_TROLL = 1,
    PHASE_BEAR,
    PHASE_EAGLE,
    PHASE_LYNX,
    PHASE_DRAGONHAWK,
};


#define CENTER_X 120.148811
#define CENTER_Y 703.713684
#define CENTER_Z 45.111477

struct SpiritInfoStruct
{
    uint32 entry;
    float x, y, z, orient;
};

static SpiritInfoStruct SpiritInfo[] =
{
    {23878, 147.87f, 706.51f, 45.11f, 3.04f},
    {23880, 88.95f, 705.49f, 45.11f, 6.11f},
    {23877, 137.23f, 725.98f, 45.11f, 3.71f},
    {23879, 104.29f, 726.43f, 45.11f, 5.43f}
};

struct TransformStruct
{
    uint32 textid;
    uint32 spell;
    uint32 unaura;
};
    
static TransformStruct Transform[] =
{
    {YELL_TRANSFORM_TO_BEAR, SPELL_SHAPE_OF_THE_BEAR, SPELL_WHIRLWIND},
    {YELL_TRANSFORM_TO_EAGLE, SPELL_SHAPE_OF_THE_EAGLE, SPELL_SHAPE_OF_THE_BEAR},
    {YELL_TRANSFORM_TO_LYNX, SPELL_SHAPE_OF_THE_LYNX, SPELL_SHAPE_OF_THE_EAGLE},
    {YELL_TRANSFORM_TO_DRAGONHAWK, SPELL_SHAPE_OF_THE_DRAGONHAWK, SPELL_SHAPE_OF_THE_LYNX}
};

class Boss_zuljin : public CreatureScript
{
public:
    Boss_zuljin() : CreatureScript("boss_zuljin_new") {}
    
    class Boss_zuljin_newAI : public ScriptedAI
    {
    public:
        enum events {
            EV_OVERPOWER_READY   = 1,// PHASE_BEAR
            EV_WHIRLWIND        ,    // PHASE_TROLL
            EV_GRIEVOUS_THROW   ,    // PHASE TROLL
            EV_CREEPING_PARA    ,    // PHASE BEAR
            EV_CLAW_RAGE        ,    // PHASE_LYNX
            EV_CLAW_RAGE_RESET  ,    // PHASE_LYNX - Resets threat on target after claw rage
            EV_LYNX_RUSH        ,    // PHASE_LYNX
            EV_FLAME_WHIRL      ,    // PHASE_DRAGONHAWK
            EV_PILLAR_OF_FIRE   ,    // PHASE_DRAGONHAWK
            EV_FLAME_BREATH     ,    // PHASE_DRAGONHAWK
            EV_REINIT_SPEED     ,    // PHASE_LYNX
        };

        Boss_zuljin_newAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            instance = ((InstanceScript*)creature->GetInstanceScript());
        }
        
        InstanceScript* instance;
        //phase is kept in both events and phase
        EventMap events;
        uint8 phase;
        SummonList summons;
        
        void Reset()
        override {
            phase = 0;

            if (instance && instance->GetData(DATA_ZULJINEVENT) != DONE)
                instance->SetData(DATA_ZULJINEVENT, NOT_STARTED);
            
            me->SetFullTauntImmunity(true);
            me->SetSheath(SHEATH_STATE_MELEE);

            summons.DespawnAll();

            events.Reset();
            events.SetPhase(PHASE_TROLL);
            
            events.RescheduleEvent(EV_WHIRLWIND, 7000, 0, PHASE_TROLL);
            // Setup events
                events.RescheduleEvent(EV_WHIRLWIND, 7000, 0, PHASE_TROLL);
                events.RescheduleEvent(EV_GRIEVOUS_THROW, 8000, PHASE_TROLL);
                events.RescheduleEvent(EV_OVERPOWER_READY, 5000, PHASE_BEAR);
                events.RescheduleEvent(EV_CREEPING_PARA, 7000, 0, PHASE_BEAR);
                events.RescheduleEvent(EV_CLAW_RAGE, 5000, 0, PHASE_LYNX);
                events.RescheduleEvent(EV_LYNX_RUSH, 14000, 0, PHASE_LYNX);
                events.RescheduleEvent(EV_FLAME_WHIRL, 5000, 0, PHASE_DRAGONHAWK);
                events.RescheduleEvent(EV_PILLAR_OF_FIRE, 6000, 0, PHASE_DRAGONHAWK);
                events.RescheduleEvent(EV_FLAME_BREATH, 7000, 0, PHASE_DRAGONHAWK);
                events.CancelEvent(EV_REINIT_SPEED);
                events.CancelEvent(EV_CLAW_RAGE_RESET);
            
            overpowerReady = false;
            clawRageTargetGUID = 0;
        }
        
        void EnterCombat(Unit* victim)
        override {
            if (instance)
                instance->SetData(DATA_ZULJINEVENT, IN_PROGRESS);
                
            DoZoneInCombat();
            spawnSpirits();
            
            Talk(YELL_INTRO);
        }
        
        void KilledUnit(Unit* killed)
        override {
            Talk(YELL_KILL);
        }
        
        void JustDied(Unit* killer)
        override {
            summons.DespawnEntry(CREATURE_COLUMN_OF_FIRE);
            
            Talk(YELL_DEATH);
            
            if (instance)
                instance->SetData(DATA_ZULJINEVENT, DONE);
                
            if (Unit* spirit = ObjectAccessor::GetUnit(*me, spiritGUIDs[4]))
                spirit->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_DEAD);
        }
        
        void AttackStart(Unit* victim)
        override {
            CreatureAI::AttackStart(victim);
            if (events.IsInPhase(PHASE_EAGLE))
                me->GetMotionMaster()->MoveIdle();
        }
        
        void JustSummoned(Creature* summoned)
        override {
            summons.Summon(summoned);
        }
        
        void SummonedCreatureDespawn(Creature* summoned)
        override {
            summons.Despawn(summoned);
        }
        
        void setPhase(uint32 newPhase)
        {
            phase = newPhase;
            events.SetPhase(newPhase);
            switch (newPhase) {
            case PHASE_TROLL:
                break;
            case PHASE_BEAR:
            case PHASE_EAGLE:
            case PHASE_LYNX:
            case PHASE_DRAGONHAWK:
                DoTeleportTo(CENTER_X, CENTER_Y, CENTER_Z, 100);
                DoResetThreat();

                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 0); // TODO: Implement a wrapper for this
                me->RemoveAurasDueToSpell(Transform[newPhase - 2].unaura);
                me->CastSpell(me, Transform[newPhase - 2].spell);

                Talk(Transform[newPhase - 2].textid);

                if (Unit* spirit = ObjectAccessor::GetUnit(*me, spiritGUIDs[newPhase - 2]))
                    spirit->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_DEAD);

                if (Unit* spirit = ObjectAccessor::GetUnit(*me, spiritGUIDs[newPhase - 1]))
                    spirit->CastSpell(me, SPELL_SIPHON_SOUL, TRIGGERED_NONE);
                    
                if (newPhase == PHASE_EAGLE) {
                    me->GetMotionMaster()->Clear();
                    me->CastSpell(me, SPELL_ENERGY_STORM, TRIGGERED_FULL_MASK);
                    for (uint8 i = 0; i < 4; i++) {
                        Creature* vortex = me->SummonCreature(CREATURE_FEATHER_VORTEX, 0, 0, 0, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                        if (vortex) {
                            vortex->CastSpell(vortex, SPELL_CYCLONE_PASSIVE, TRIGGERED_FULL_MASK);
                            vortex->CastSpell(vortex, SPELL_CYCLONE_VISUAL, TRIGGERED_FULL_MASK);
                            vortex->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            vortex->SetSpeedRate(MOVE_RUN, 1.0f);
                            vortex->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM, 0)); // FIXME: when converting vortex AI, change this
                            vortex->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                            DoZoneInCombat();
                        }
                    }
                }
                else
                    me->AI()->AttackStart(me->GetVictim());

                if (newPhase == PHASE_LYNX) {
                    me->RemoveAurasDueToSpell(SPELL_ENERGY_STORM);
                    summons.DespawnEntry(CREATURE_FEATHER_VORTEX);
                    me->GetMotionMaster()->MoveChase(me->GetVictim());
                }
                break;
            default:
                break;
            }
        }
        
        void spawnSpirits()
        {
            Creature* spirit = nullptr;
            for (uint8 i = 1; i < 5; i++) {
                if ((spirit = me->SummonCreature(SpiritInfo[i - 1].entry, SpiritInfo[i - 1].x, SpiritInfo[i - 1].y, SpiritInfo[i - 1].z, SpiritInfo[i - 1].orient, TEMPSUMMON_DEAD_DESPAWN, 0))) 
                {
                    spirit->CastSpell(spirit, SPELL_SPIRIT_AURA, TRIGGERED_FULL_MASK);
                    spirit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    spirit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    spiritGUIDs[i] = spirit->GetGUID();
                }
            }
            spiritGUIDs[0] = 0;
        }
        
        //ugly hack to get SPELL_OVERPOWER to activate when melee misses (this is wrong since we need to do it only on dodge)
        void DoMeleeAttackIfReady()
        override {
            if (!me->IsNonMeleeSpellCast(false)) 
            {
                if (me->IsAttackReady() && me->IsWithinMeleeRange(me->GetVictim())) 
                { // It seems that there is no triggering aura we could use with the proper procflags :(
                    if (events.IsInPhase(PHASE_BEAR) && overpowerReady) 
                    {
                        uint32 health = me->GetVictim()->GetHealth();
                        me->AttackerStateUpdate(me->GetVictim());
                        if (me->GetVictim() && health == me->GetVictim()->GetHealth()) 
                        { // Dodged
                            me->CastSpell(me->GetVictim(), SPELL_OVERPOWER, TRIGGERED_NONE);
                            overpowerReady = false;
                            events.RescheduleEvent(EV_OVERPOWER_READY, 5000, 0, PHASE_BEAR);
                        }
                    }
                    else
                        me->AttackerStateUpdate(me->GetVictim());

                    me->ResetAttackTimer();
                }
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
            
            if (me->GetHealth() < ((me->GetMaxHealth() / 5.0f) * (5 - phase)))
                setPhase(++phase);
            
            events.Update(diff);
            
            switch (events.GetEvent())
            {
                case 0:
                    break;
                case EV_OVERPOWER_READY:
                    overpowerReady = true;
                    events.CancelEvent(EV_OVERPOWER_READY);
                    break;
                case EV_WHIRLWIND:
                    if (me->CastSpell(me, SPELL_WHIRLWIND) == SPELL_CAST_OK)
                        events.RescheduleEvent(EV_WHIRLWIND, urand(15000, 20000), 0, PHASE_TROLL);
                    break;
                case EV_GRIEVOUS_THROW:
                    if(me->CastSpell(SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f, true), SPELL_GRIEVOUS_THROW) == SPELL_CAST_OK)
                        events.RescheduleEvent(EV_GRIEVOUS_THROW, 10000, 0, PHASE_TROLL);
                    break;
                case EV_CREEPING_PARA:
                    if(me->CastSpell(me, SPELL_CREEPING_PARALYSIS) == SPELL_CAST_OK)
                        events.RescheduleEvent(EV_CREEPING_PARA, 20000, 0, PHASE_BEAR);
                    break;
                case EV_CLAW_RAGE:
                {
                    Unit* clawRageTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0, true, true);
                    if (clawRageTarget) {
                        clawRageTargetGUID = clawRageTarget->GetGUID();
                        me->GetThreatManager().AddThreat(clawRageTarget, 1000000); // 1.000.000 threat should be enough
                        me->SetSpeedRate(MOVE_RUN, 1.2f);
                        events.RescheduleEvent(EV_REINIT_SPEED, 2000, 0, PHASE_LYNX);
                        me->CastSpell(clawRageTarget, SPELL_CLAW_RAGE_CHARGE);
                        me->CastSpell(me, SPELL_CLAW_RAGE_TRIGGER, TRIGGERED_FULL_MASK); // Triggers SPELL_CLAW_RAGE_DAMAGE every 500 ms
                    }

                    //reset claw rage focus after 5.5
                    events.RescheduleEvent(EV_CLAW_RAGE_RESET, 5500, 0, PHASE_LYNX);
                    //schedule next claw rage
                    events.RescheduleEvent(EV_CLAW_RAGE, urand(15000, 20000), 0, PHASE_LYNX);
                    events.SetMinimalDelay(EV_LYNX_RUSH, 5500);
                    break;
                }
                case EV_CLAW_RAGE_RESET: // reset clawRageTargetGUID, remove threat, disable EV_CLAW_RAGE_RESET event
                    if (Unit* clawRageTarget = ObjectAccessor::GetUnit(*me, clawRageTargetGUID))
                        me->GetThreatManager().AddThreat(clawRageTarget, -1000000);

                    clawRageTargetGUID = 0;
                    events.CancelEvent(EV_CLAW_RAGE_RESET);
                    break;
                case EV_LYNX_RUSH:
                    me->SetSpeedRate(MOVE_RUN, 1.2f);
                    if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0, true, true))
                        if (me->CastSpell(target, SPELL_LYNX_RUSH_DAMAGE) == SPELL_CAST_OK)
                        {
                            events.SetMinimalDelay(EV_CLAW_RAGE, 2000);
                            events.RescheduleEvent(EV_REINIT_SPEED, 2000);
                            events.RescheduleEvent(EV_LYNX_RUSH, urand(25000, 30000), 0, PHASE_LYNX);
                        }
                    break;
                case EV_FLAME_WHIRL:
                    if(me->CastSpell(me, SPELL_FLAME_WHIRL) == SPELL_CAST_OK)
                        events.RescheduleEvent(EV_FLAME_WHIRL, 12000, 0, PHASE_DRAGONHAWK);
                    break;
                case EV_PILLAR_OF_FIRE:
                    if(me->CastSpell(SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f, true), SPELL_SUMMON_PILLAR) == SPELL_CAST_OK)
                        events.RescheduleEvent(EV_PILLAR_OF_FIRE, 10000, 0, PHASE_DRAGONHAWK);
                    break;
                case EV_FLAME_BREATH:
                    if(me->CastSpell(SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f, true), SPELL_FLAME_BREATH) == SPELL_CAST_OK)
                        events.RescheduleEvent(EV_FLAME_BREATH, 10000, 0, PHASE_DRAGONHAWK);
                    break;
                case EV_REINIT_SPEED:
                    me->SetSpeedRate(MOVE_RUN, 1.0f);
                    events.CancelEvent(EV_REINIT_SPEED);
                    break;
            }
            
            DoMeleeAttackIfReady();
        }
        
    private:
        uint64 spiritGUIDs[5];
        uint64 clawRageTargetGUID;
        
        bool overpowerReady;
    };
    
    ScriptedAI* GetAI(Creature* creature) const
    override {
        return new Boss_zuljin_newAI(creature);
    }
};

void AddSC_boss_zuljin()
{
    new Boss_zuljin();
}
