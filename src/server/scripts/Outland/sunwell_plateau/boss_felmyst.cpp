// Fixme - triggers are affected by aoe and die

#include "def_sunwell_plateau.h"

enum Quotes
{
    YELL_BIRTH      =       -1580036,
    YELL_KILL1      =       -1580037,
    YELL_KILL2      =       -1580038,
    YELL_BREATH     =       -1580039,
    YELL_TAKEOFF    =       -1580040,
    YELL_BERSERK    =       -1580041,
    YELL_DEATH      =       -1580042,
    YELL_KALECGOS   =       -1580043,   //after felmyst's death spawned and say this
    EMOTE_DEEP_BREATH   =   -1580110    // "Felmyst takes a deep breath"
};

enum Spells
{
    //Aura
    AURA_SUNWELL_RADIANCE       =   45769,
    AURA_NOXIOUS_FUMES          =   47002,

    //Land phase
    SPELL_CLEAVE                =   19983,
    SPELL_CORROSION             =   45866,
    SPELL_GAS_NOVA              =   45855,
    SPELL_ENCAPSULATE_CHANNEL   =   45661,
    // SPELL_ENCAPSULATE_EFFECT    =   45665,
    // SPELL_ENCAPSULATE_AOE       =   45662,

    //Flight phase
    SPELL_VAPOR_SELECT          =   45391,   // fel to player, force cast 45392, 50000y selete target
    SPELL_VAPOR_SUMMON          =   45392,   // player summon vapor, radius around caster, 5y,
    SPELL_VAPOR_FORCE           =   45388,   // vapor to fel, force cast 45389
    SPELL_VAPOR_CHANNEL         =   45389,   // fel to vapor, green beam channel
    SPELL_VAPOR_TRIGGER         =   45411,   // linked to 45389, vapor to self, trigger 45410 and 46931
    SPELL_VAPOR_DAMAGE          =   46931,   // vapor damage, 4000
    SPELL_TRAIL_SUMMON          =   45410,   // vapor summon trail
    SPELL_TRAIL_TRIGGER         =   45399,   // trail to self, trigger 45402
    SPELL_TRAIL_DAMAGE          =   45402,   // trail damage, 2000 + 2000 dot
    SPELL_DEAD_SUMMON           =   45400,   // summon blazing dead, 5min
    SPELL_DEAD_PASSIVE          =   45415,
    SPELL_FOG_BREATH            =   45495,   // fel to self, speed burst
    SPELL_FOG_TRIGGER           =   45582,   // fog to self, trigger 45782
    SPELL_FOG_FORCE             =   45782,   // fog to player, force cast 45714
    SPELL_FOG_INFORM            =   45714,   // player let fel cast 45717, script effect
    SPELL_FOG_CHARM             =   45717,   // fel to player
    SPELL_FOG_CHARM2            =   45726,   // link to 45717

    SPELL_TRANSFORM_TRIGGER     =   44885,   // madrigosa to self, trigger 46350
    SPELL_TRANSFORM_VISUAL      =   46350,   //46411stun?
    SPELL_TRANSFORM_FELMYST     =   45068,   // become fel
    SPELL_FELMYST_SUMMON        =   45069,

    //Other
    SPELL_BERSERK               =   45078,
    SPELL_CLOUD_VISUAL          =   45212,
    SPELL_CLOUD_SUMMON          =   45884,
    SPELL_SOUL_SEVER            =   45917   // Casted at reset on all players with Fog of Corruption aura
};

enum PhaseFelmyst
{
    PHASE_NULL   = 0,
    PHASE_INTRO  = 1, //playing intro
    PHASE_RESET  = 2,
    PHASE_PULL   = 3, //ready to be pull
    PHASE_GROUND = 4,
    PHASE_FLIGHT = 5
};

#define ORIENTATION_LEFT    4.7984
#define ORIENTATION_RIGHT   1.3033

static float flightMobLeft[] = {1468.380005f, 730.267029f, 60.083302f};
static float flightMobRight[] = {1458.170044f, 501.295013f, 60.083302f};

static float lefts[3][3] = { {1446.540039f, 702.570007f, 52.083302f},    //south
                             {1469.939941f, 704.239014f, 52.083302f},    //middle
                             {1494.760010f, 705.000000f, 52.083302f}, }; //north

static float rights[3][3] = { {1441.640015f, 520.520020f, 52.083302f},   //south
                              {1467.219971f, 516.318970f, 52.083302f},   //middle
                              {1492.819946f, 515.668030f, 52.083302f}, };//north

static float prepareLandingLoc[2][3] = {  {1482.709961f, 649.406006f, 21.081100f},
                                          {1491.119995f, 553.672974f, 24.921900f}  };

static float kalecPos[] = { 1501.253174f, 764.737061f, 117.972687f, 4.626863f };

#define NON_COMBAT_PATH 25038

class boss_felmyst : public CreatureScript
{
public:
    boss_felmyst() : CreatureScript("boss_felmyst") {}

    class boss_felmystAI : public ScriptedAI
    {
        public:
        boss_felmystAI(Creature* creature) : ScriptedAI(creature), Summons(me)
        {
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
        }

        InstanceScript* pInstance;
        SummonList Summons;

        enum events
        {
            EVENT_CLEAVE               = 1,
            EVENT_CORROSION            ,
            EVENT_GAS_NOVA             ,
            EVENT_ENCAPSULATE          ,
            EVENT_ENCAPS_WARN          ,
            EVENT_FOG_CORRUPTION       ,
            EVENT_DEMONIC_VAPOR        ,
            EVENT_BERSERK              ,
        };

        EventMap events;

        uint32 flightPhaseTimer;
        uint32 flightPhase;
        uint32 introPhaseTimer;
        uint32 introPhase;
        uint32 BreathCount;
        uint32 demonicCount;
        bool origin;
        bool direction;
        bool inChaseOnFlight;
        uint8 chosenLane; //0-2, south - center - north
        uint8 phase;
        bool firstInit = true;

        ObjectGuid encapsTargetGUID;

        void Reset()
        override {
            origin = false;
            direction = false;
            inChaseOnFlight = false;
            chosenLane = 0;
            encapsTargetGUID = ObjectGuid::Empty;
            flightPhaseTimer = 60000;
            flightPhase = 0;
            introPhaseTimer = 0;
            introPhase = 0;
            BreathCount = 0;
            demonicCount = 0;

            //me->ApplyModFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE, true);

            events.Reset();
            if (firstInit)
                setPhase(PHASE_INTRO);
            else
                setPhase(PHASE_RESET);

            firstInit = false;

            me->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 10);
            me->SetFloatValue(UNIT_FIELD_COMBATREACH, 10);

            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);

            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);

            Summons.DespawnAll();

            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);

            if(pInstance)
                pInstance->SetData(DATA_FELMYST_EVENT, NOT_STARTED);

            me->CastSpell((Unit*)nullptr, SPELL_TRANSFORM_FELMYST, TRIGGERED_FULL_MASK);

            if (pInstance)
            {
                Map::PlayerList const& players = pInstance->instance->GetPlayers();
                if (!players.isEmpty())
                {
                    for(const auto & player : players)
                    {
                        if (Player* plr = player.GetSource())
                        {
                            if (plr->HasAuraEffect(SPELL_FOG_CHARM))
                                plr->CastSpell(plr, SPELL_SOUL_SEVER, TRIGGERED_FULL_MASK);
                        }
                    }
                }
            }

            me->RemoveAurasDueToSpell(AURA_SUNWELL_RADIANCE);
            me->CastSpell(me, AURA_SUNWELL_RADIANCE, TRIGGERED_FULL_MASK);
        }

        void setPhase(uint32 newPhase)
        {
            phase = newPhase;
            events.SetPhase(newPhase);
            switch (newPhase)
            {
                case PHASE_INTRO:
                    me->SetSpeedRate(MOVE_RUN, 1.3f, true);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_PASSIVE);
                    break;
                case PHASE_RESET:
                    me->SetSpeedRate(MOVE_RUN, 1.3f, true);
                    me->StopMoving();
                    me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
                    me->SetDisableGravity(true);
                    me->SendMovementFlagUpdate();
                    setPhase(PHASE_PULL);
                    break;
                case PHASE_PULL:
                    me->GetMotionMaster()->MovePath(NON_COMBAT_PATH, true, true); //use smoothSpline system
                    break;
                case PHASE_GROUND:
                    flightPhaseTimer = 60000;
                    events.RescheduleEvent(EVENT_CLEAVE, urand(5000, 10000), 0, PHASE_GROUND);
                    events.RescheduleEvent(EVENT_CORROSION, urand(10000, 20000), 0, PHASE_GROUND);
                    events.RescheduleEvent(EVENT_GAS_NOVA, urand(20000, 25000), 0, PHASE_GROUND);
                    events.RescheduleEvent(EVENT_ENCAPSULATE, 30000, 0, PHASE_GROUND);
                    events.RescheduleEvent(EVENT_ENCAPS_WARN, 29000, 0, PHASE_GROUND);
                    break;
                case PHASE_FLIGHT:
                    //me->ApplyModFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE, true);
                    me->SetSpeedRate(MOVE_RUN, 1.3f, true);
                    switch (rand()%2)
                    {
                        case 0:
                            origin = true;
                            direction = true;
                            break;
                        case 1:
                            origin = false;
                            direction = false;
                            break;
                    }

                    demonicCount = 0;
                    flightPhaseTimer = 300;
                    flightPhase = 0;
                    BreathCount = 0;
                    break;
            }
        }

        void JustEngagedWith(Unit* /*who*/)
        override {
            me->SetWalk(false);

            if (pInstance)
                pInstance->SetData(DATA_FELMYST_EVENT, IN_PROGRESS);

            me->CastSpell(me, AURA_NOXIOUS_FUMES, TRIGGERED_FULL_MASK);

            if (pInstance)
            {
                if (Creature* brutallus = ObjectAccessor::GetCreature(*me, ObjectGuid(pInstance->GetData64(DATA_BRUTALLUS)))) {
                    if (!brutallus->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE))
                        brutallus->SetVisible(false);
                }
            }
            inChaseOnFlight = true;
        }

        void AttackStart(Unit *pTarget)
        override {
            if (!pTarget)
                return;

            if (phase != PHASE_PULL && phase != PHASE_GROUND)
                return;

            CreatureAI::AttackStart(pTarget);
        }

        void JustDied(Unit* /*killer*/)
        override {
            DoScriptText(YELL_DEATH, me);

            if(pInstance)
                pInstance->SetData(DATA_FELMYST_EVENT, DONE);

            if (Creature* kalecgos = me->SummonCreature(24844, kalecPos[0],kalecPos[1],kalecPos[2],kalecPos[3], TEMPSUMMON_MANUAL_DESPAWN, 0))
                kalecgos->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void KilledUnit(Unit* /*victim*/)
        override {
            DoScriptText(RAND(YELL_KILL1, YELL_KILL2), me);
        }

        void JustSummoned(Creature* summoned)
        override {
            Summons.Summon(summoned);
            if(summoned->GetEntry() == MOB_DEAD)
            {
                summoned->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM, 0));
                summoned->CastSpell(summoned, SPELL_DEAD_PASSIVE, TRIGGERED_FULL_MASK);
            }
            else if (summoned->GetEntry() == MOB_VAPOR)
                me->SetTarget(summoned->GetGUID());
        }

        void SummonedCreatureDespawn(Creature* unit)
        override {
            if (unit->GetEntry() == MOB_VAPOR)
                me->SetTarget(ObjectGuid::Empty);

            Summons.Despawn(unit);
        }

        void MovementInform(uint32 type, uint32 id)
        override {
            if (type != POINT_MOTION_TYPE)
                return;

            switch (id)
            {
                case 1: //arrived at breath start position
                    flightPhase++;
                    flightPhaseTimer = 0;
                    break;
                case 2: //arrived at breath destination
                    me->RemoveAurasDueToSpell(SPELL_FOG_BREATH);
                    events.CancelEvent(EVENT_FOG_CORRUPTION);

                    flightPhase++;
                    flightPhaseTimer = 3000;
                    break;
                case 3: //arrived at landing position
                    me->StopMoving();

                    me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
                    me->SetDisableGravity(false);

                    float x, y, z;
                    me->GetPosition(x, y, z);
                    me->UpdateGroundPositionZ(x, y, z);
                    me->Relocate(x, y, z);

                    me->SendMovementFlagUpdate();

                    setPhase(PHASE_PULL);
                    if (Unit *target = SelectTarget(SELECT_TARGET_MAXTHREAT, 0))
                    {
                        AttackStart(target);
                        me->GetMotionMaster()->MoveChase(target);
                    }
                    else
                        EnterEvadeMode();
                    break;
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        {
            if(phase != PHASE_GROUND && damage >= me->GetHealth())
                damage = 0;
        }

        void MoveInLineOfSight(Unit* who)
        override {
            if (!me->IsInCombat())
                return;

            if(phase != PHASE_FLIGHT && phase != PHASE_INTRO)
                CreatureAI::MoveInLineOfSight(who);
        }

        void handleIntro(uint32 const diff)
        {
            if (introPhaseTimer <= diff)
            {
                switch (introPhase)
                {
                    case 0:
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        DoScriptText(YELL_BIRTH, me);
                        introPhaseTimer = 4000;
                        introPhase++;
                        break;
                    case 1:
                        me->StopMoving();
                        me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
                        me->SetDisableGravity(true);
                        me->SendMovementFlagUpdate();
                        introPhaseTimer = 500;
                        introPhase++;
                        break;
                    case 2:
                        me->SetHomePosition(1464.726440, 606.836243, 72.818344, 0);
                        me->GetMotionMaster()->MovePoint(0, 1464.726440, 606.836243, 72.818344,false);
                        introPhaseTimer = 6000;
                        introPhase++;
                        break;
                    case 3:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        setPhase(PHASE_PULL);
                        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                }
            }
            else
                introPhaseTimer -= diff;
        }

        void handleFlight(uint32 const diff)
        {
            if (flightPhaseTimer <= diff)
            {
                switch(flightPhase)
                {
                    case 0: // Lift off : emote
                        me->StopMoving();
                        me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
                        me->SetDisableGravity(true);
                        me->SendMovementFlagUpdate();
                        DoScriptText(YELL_TAKEOFF, me);
                        flightPhaseTimer = 2000;
                        flightPhase++;
                        break;
                    case 1: // Lift off : move higher
                        me->GetMotionMaster()->MovePoint(0, me->GetPositionX()+1, me->GetPositionY(), me->GetPositionZ() + 15.0f, false);
                        flightPhaseTimer = 30000; //wait 30 sec for the demonic vapor part
                        events.RescheduleEvent(EVENT_DEMONIC_VAPOR, 3000, 0, PHASE_FLIGHT);
                        flightPhase++;
                        break;
                    case 2: //fly near breath start position
                        me->SetSpeedRate(MOVE_RUN, 4.0f, true);
                        if (!direction)
                            me->GetMotionMaster()->MovePoint(1, flightMobRight[0], flightMobRight[1], flightMobRight[2], false);
                        else
                            me->GetMotionMaster()->MovePoint(1, flightMobLeft[0], flightMobLeft[1], flightMobLeft[2], false);

                        flightPhase++;
                        flightPhaseTimer = 20000; //just to be sure to not stay stuck
                        break;
                    case 3:
                        // Do nothing, flightPhase will be incremented in mouvement inform
                        flightPhase++; // should never be reached, just to be sure to not stay stuck
                        break;
                    case 4: //fly to start position
                        me->SetSpeedRate(MOVE_RUN, 1.3f, true);
                        chosenLane = rand()%3;
                        if (!direction)
                            me->GetMotionMaster()->MovePoint(1, rights[chosenLane][0], rights[chosenLane][1], rights[chosenLane][2], false);
                        else
                            me->GetMotionMaster()->MovePoint(1, lefts[chosenLane][0], lefts[chosenLane][1], lefts[chosenLane][2], false);

                        flightPhase++;
                        flightPhaseTimer = 20000; //just to be sure to not stay stuck
                        break;
                    case 5:
                        // Do nothing, flightPhase will be incremented in mouvement inform
                        flightPhase++; // should never be reached, just to be sure to not stay stuck
                        break;
                    case 6: // Face right direction, do emote and wait a bit
                        flightPhaseTimer = 4000;
                        flightPhase++;
                        DoScriptText(EMOTE_DEEP_BREATH, me);
                        if (!direction) //face the opposite
                            me->SetInFront(lefts[chosenLane][0], lefts[chosenLane][1]);
                        else
                            me->SetInFront(rights[chosenLane][0], rights[chosenLane][1]);
                        me->SetSpeedRate(MOVE_RUN, 4.0f, true);
                        me->SendMovementFlagUpdate();
                        break;
                    case 7: //start passage
                        if (!direction)
                            me->GetMotionMaster()->MovePoint(2, lefts[chosenLane][0], lefts[chosenLane][1], lefts[chosenLane][2], false);
                        else
                            me->GetMotionMaster()->MovePoint(2, rights[chosenLane][0], rights[chosenLane][1], rights[chosenLane][2], false);

                        me->CastSpell(me, SPELL_FOG_BREATH, TRIGGERED_NONE);
                        flightPhaseTimer = 1500;
                        flightPhase++;
                        break;
                    case 8: //spawn fogs

                        events.RescheduleEvent(EVENT_FOG_CORRUPTION, 50, 0, PHASE_FLIGHT);
                        direction = !direction;

                        flightPhaseTimer = 20000; //just to be sure to not stay stuck
                        flightPhase++;
                        break;
                    case 9:
                        // Do nothing, flightPhase will be incremented in mouvement inform
                        flightPhase++; // should never be reached, just to be sure to not stay stuck
                        break;
                    case 10: // wait 2 sec at arrival, then loop from flightPhase 4 until 3 breaths done
                        BreathCount++;
                        me->SetSpeedRate(MOVE_RUN, 1.3f, true);
                        flightPhase++;
                        flightPhaseTimer = 2000;
                        if(BreathCount < 3)
                            flightPhase = 4;
                        
                        break;
                    case 11: //prepare to land, landing is handled in onMovementInform
                        if (!origin)
                            me->GetMotionMaster()->MovePoint(3, prepareLandingLoc[0][0],prepareLandingLoc[0][1],prepareLandingLoc[0][2], false);
                        else
                            me->GetMotionMaster()->MovePoint(3, prepareLandingLoc[1][0],prepareLandingLoc[1][1],prepareLandingLoc[1][2], false);

                        flightPhase++;
                        flightPhaseTimer = 15000;
                        break;
                    default:
                        //shouldn't ever go there, but let's go back to 11 if this happens
                        flightPhase = 11;
                        break;
                }
            }
            else
                flightPhaseTimer -= diff;
        }

        void UpdateAI(const uint32 diff)
        override {
            if (phase == PHASE_INTRO)
            {
                handleIntro(diff);
                return;
            }

            events.Update(diff);

            if (me->IsNonMeleeSpellCast(false))
                return;

            UpdateVictim();

            switch (phase)
            {
                case PHASE_PULL:
                    if(!me->GetVictim()) return;
                    if (me->IsWithinMeleeRange(me->GetVictim()))
                    {
                        if (inChaseOnFlight)
                        {
                            me->StopMoving();
                            inChaseOnFlight = false;
                            me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
                            me->SetDisableGravity(false);

                            float x, y, z;
                            me->GetPosition(x, y, z);
                            me->UpdateGroundPositionZ(x, y, z);
                            me->Relocate(x, y, z);

                            me->SendMovementFlagUpdate();
                        }
                        setPhase(PHASE_GROUND);
                        events.RescheduleEvent(EVENT_BERSERK, 600000);
                    }
                    break;
                case PHASE_FLIGHT:
                    if (flightPhase >= 2)
                        me->SetTarget(ObjectGuid::Empty);

                    handleFlight(diff);
                    break;
                case PHASE_GROUND:
                    if(!me->GetVictim()) return;
                    if (flightPhaseTimer)
                    {
                        if (flightPhaseTimer <= diff)
                            setPhase(PHASE_FLIGHT);
                        else
                            flightPhaseTimer -= diff;
                    }

                    DoMeleeAttackIfReady();
                    if (encapsTargetGUID)
                        if(Unit* encapsTarget = ObjectAccessor::GetUnit((*me), encapsTargetGUID))
                            me->SetTarget(encapsTargetGUID);
                    break;
            }


            while (uint32 eventId = events.ExecuteEvent())
                switch (eventId)
                {
                    case 0:
                        break;
                    case EVENT_CLEAVE:
                        if(me->CastSpell(me->GetVictim(), SPELL_CLEAVE, TRIGGERED_NONE) == SPELL_CAST_OK)
                            events.RescheduleEvent(EVENT_CLEAVE, urand(5000, 10000), 0, PHASE_GROUND);
                        break;
                    case EVENT_CORROSION:
                        if(me->CastSpell(me->GetVictim(), SPELL_CORROSION, TRIGGERED_NONE) == SPELL_CAST_OK)
                            events.RescheduleEvent(EVENT_CORROSION, urand(20000, 30000), 0, PHASE_GROUND);
                        break;
                    case EVENT_GAS_NOVA:
                        if(me->CastSpell(me, SPELL_GAS_NOVA, TRIGGERED_NONE) == SPELL_CAST_OK)
                            events.RescheduleEvent(EVENT_GAS_NOVA, urand(21000, 26000), 0, PHASE_GROUND);
                        break;
                    case EVENT_ENCAPSULATE:
                        if(encapsTargetGUID)
                            if (Unit* encapsTarget = ObjectAccessor::GetUnit((*me), encapsTargetGUID))
                                if (me->CastSpell(encapsTarget, SPELL_ENCAPSULATE_CHANNEL, TRIGGERED_NONE) == SPELL_CAST_OK)
                                {

                                    phase = PHASE_GROUND;

                                    if (Unit* tank = SelectTarget(SELECT_TARGET_MAXTHREAT, 0, 150.0f, true))
                                        me->SetTarget(tank->GetGUID());

                                    events.RescheduleEvent(EVENT_ENCAPSULATE, 33000, 0, PHASE_GROUND);
                                    events.RescheduleEvent(EVENT_ENCAPS_WARN, 32000, 0, PHASE_GROUND);
                                }
                        break;
                    case EVENT_ENCAPS_WARN:
                        if (Unit* encapsTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))
                        {
                            encapsTargetGUID = encapsTarget->GetGUID();
                            me->SetTarget(encapsTargetGUID);
                        }

                        events.CancelEvent(EVENT_ENCAPS_WARN);
                        break;
                    case EVENT_BERSERK:
                        if (!me->HasAuraEffect(SPELL_BERSERK))
                        {
                            DoScriptText(YELL_BERSERK, me);
                            me->CastSpell(me, SPELL_BERSERK, TRIGGERED_FULL_MASK);
                        }
                        events.RescheduleEvent(EVENT_BERSERK, 10000);
                        break;
                    case EVENT_DEMONIC_VAPOR:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150, true)) //useless here ? The spell should do the random itself
                            me->CastSpell(me, SPELL_VAPOR_SELECT, TRIGGERED_FULL_MASK);

                        demonicCount++;
                        if (demonicCount >= 2)
                            events.CancelEvent(EVENT_DEMONIC_VAPOR);
                        else
                            events.RescheduleEvent(EVENT_DEMONIC_VAPOR, 11000, 0, PHASE_FLIGHT);
                        break;
                    case EVENT_FOG_CORRUPTION:
                    {
                        if (pInstance)
                        {
                            switch (chosenLane)
                            { //related trigger cast their fog via instanceScript, see instance_sunwell_plateau. Y position is given to advance fog progressively
                                case 0:
                                    pInstance->SetData((direction ? DATA_ACTIVATE_SOUTH_TO_LEFT : DATA_ACTIVATE_SOUTH_TO_RIGHT), (uint32) me->GetPositionY());
                                    break;
                                case 1:
                                    pInstance->SetData((direction ? DATA_ACTIVATE_CENTER_TO_LEFT : DATA_ACTIVATE_CENTER_TO_RIGHT), (uint32) me->GetPositionY());
                                    break;
                                case 2:
                                    pInstance->SetData((direction ? DATA_ACTIVATE_NORTH_TO_LEFT : DATA_ACTIVATE_NORTH_TO_RIGHT), (uint32) me->GetPositionY());
                                    break;
                            }
                        }

                        events.RescheduleEvent(EVENT_FOG_CORRUPTION, 50, 0, PHASE_FLIGHT);
                        break;
                    }
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new boss_felmystAI(creature);
    }
};

class mob_felmyst_vapor : public CreatureScript
{
public:
    mob_felmyst_vapor() : CreatureScript("mob_felmyst_vapor") {}

    class mob_felmyst_vaporAI : public ScriptedAI
    {
        public:
        mob_felmyst_vaporAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
        }

        InstanceScript* pInstance;
        bool startFollow;

        void Reset()
        override {
            startFollow = false;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetWalk(false);
        }

        void JustEngagedWith(Unit* /*who*/)
        override {
            startFollow = true;
            DoZoneInCombat();
            me->CastSpell((Unit*)nullptr, SPELL_VAPOR_FORCE, TRIGGERED_FULL_MASK);
            me->CastSpell(me, SPELL_VAPOR_TRIGGER, TRIGGERED_FULL_MASK);
        }

        void UpdateAI(uint32 const /*diff*/)
        override {
            if (startFollow)
            {
                if(!me->GetVictim())
                    if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 15.0f,true))
                    {
                        me->Attack(target,false); //just to set our victim
                        me->GetMotionMaster()->MoveFollow(target, 0.0f, 0);
                    }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_felmyst_vaporAI(creature);
    }
};

class mob_felmyst_trail : public CreatureScript
{
public:
    mob_felmyst_trail() : CreatureScript("mob_felmyst_trail") {}

    class mob_felmyst_trailAI : public CreatureAI
    {
        public:
        mob_felmyst_trailAI(Creature* creature) : CreatureAI(creature)
        {
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
            SetCombatMovementAllowed(false);
        }

        EventMap events;
        InstanceScript* pInstance;

        enum events
        {
            EVENT_DEAD            = 1
        };

        void Reset()
        override {
            events.RescheduleEvent(EVENT_DEAD, urand(7000, 8000));

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->CastSpell((Unit*)nullptr, SPELL_TRAIL_TRIGGER, TRIGGERED_FULL_MASK);
            me->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 0.01); // core bug
        }

        uint64 message(uint32 id, uint64 data)
        override {
            if (id == 1)
                events.CancelEvent(EVENT_DEAD);
            return 0;
        }
 
        void AttackStart(Unit* /*victim*/) override {}

        void UpdateAI(uint32 const diff)
        override {
            events.Update(diff);


            while (uint32 eventId = events.ExecuteEvent())
                switch (eventId)
                {
                    case 0:
                        break;
                    case EVENT_DEAD:
                        events.CancelEvent(EVENT_DEAD);
                        me->CastSpell((Unit*)nullptr, SPELL_DEAD_SUMMON, TRIGGERED_FULL_MASK);
                        me->DisappearAndDie();
                        break;
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_felmyst_trailAI(creature);
    }
};

class mob_unyielding_dead : public CreatureScript
{
public:
    mob_unyielding_dead() : CreatureScript("mob_unyielding_dead") {}

    class mob_unyielding_deadAI : public ScriptedAI
    {
        public:
        mob_unyielding_deadAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
        }

        InstanceScript* pInstance;

        void Reset()
        override {
            if(pInstance)
                DoZoneInCombat();

            if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
            {
                me->GetThreatManager().AddThreat(target,500.0f);
                AttackStart(target);
            }
            me->CastSpell((Unit*)nullptr, SPELL_DEAD_PASSIVE, TRIGGERED_FULL_MASK);
        }

        void UpdateAI(const uint32 diff)
        override {
            if (pInstance && pInstance->GetData(DATA_FELMYST_EVENT) != IN_PROGRESS)
                me->DisappearAndDie();

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_unyielding_deadAI(creature);
    }
};

void AddSC_boss_felmyst()
{
    new boss_felmyst();
    new mob_felmyst_vapor();
    new mob_felmyst_trail();
    new mob_unyielding_dead();
}
