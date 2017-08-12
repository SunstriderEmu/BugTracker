
/* ScriptData
SDName: boss_illidan_stormrage
SD%Complete: 90
SDComment: Somewhat of a workaround for Parasitic Shadowfiend.
SDCategory: Black Temple
EndScriptData */


#include "def_black_temple.h"
#include "NullCreatureAI.h"

#define GETGO(obj, guid)      GameObject* obj = GameObject::GetGameObject(*me, guid)
#define GETUNIT(unit, guid)   Unit* unit = ObjectAccessor::GetUnit(*me, guid)
#define GETCRE(cre, guid)     Creature* cre = ObjectAccessor::GetCreature(*me, guid)
#define HPPCT(unit)           unit->GetHealth()*100 / unit->GetMaxHealth()

/************* Quotes and Sounds ***********************/
// Gossip for when a player clicks Akama
#define GOSSIP_INTRO           450
#define GOSSIP_START           452
#define MENU_INTRO             451
#define MENU_START             453

// Yells for/by Akama
#define SAY_AKAMA_INTRO1      -1566032 //intro after council
#define SAY_AKAMA_INTRO2      -1566033
#define SAY_AKAMA_STANDASIDE  -1566034
#define SAY_AKAMA_CHANNELFAIL -1566035
#define SAY_UDALO_NOTALONE    -1566036
#define SAY_OLUM_NOTALONE     -1566037
#define SAY_AKAMA_THANKS      -1566038

#define SAY_AKAMA_BEWARE      -1566000
#define SAY_AKAMA_MINION      -1566001
#define SAY_AKAMA_LEAVE       -1566002

// Self explanatory
#define SAY_KILL1             -1566003
#define SAY_KILL2             -1566004

// I think I'll fly now and let my subordinates take you on
#define SAY_TAKEOFF           -1566005
#define SAY_SUMMONFLAMES      -1566006

// When casting Eye Blast. Demon Fire will be appear on places that he casts this
#define SAY_EYE_BLAST         -1566007

// kk, I go big, dark and demon on you.
#define SAY_MORPH             -1566008

// I KILL!
#define SAY_ENRAGE            -1566009

/************** Spells *************/
enum Spells
{
    // Normal Form
    SPELL_SHEAR                   = 41032, // Reduces Max. Health by = 60,% for = 7, seconds. Can stack = 19, times. = 1,.5 second cast
    SPELL_FLAME_CRASH             = 40832, // Summons an invis/unselect passive mob that has an aura of flame in a circle around him.
    SPELL_DRAW_SOUL               = 40904, // = 5,k Shadow Damage in front of him. Heals Illidan for = 100,k health (script effect)
    SPELL_PARASITIC_SHADOWFIEND   = 41917, // DoT of = 3,k Shadow every = 2, seconds. Lasts = 10, seconds. (OLDScript effect: Summon = 2, parasites once the debuff has ticked off)
    SPELL_PARASITIC_SHADOWFIEND2  = 41914, // Used by Parasitic
    SPELL_SUMMON_PARASITICS       = 41915, // Summons = 2, Parasitic Shadowfiends on the target. It's supposed to be cast as soon as the Parasitic Shadowfiend debuff is gone, but the spells aren't linked :(
    SPELL_AGONIZING_FLAMES        = 40932, // = 4,k fire damage initial to target and anyone w/i = 5, yards. PHASE = 3, ONLY
    SPELL_ENRAGE                  = 40683, // Increases damage by = 50,% and attack speed by = 30,%. = 20, seconds, PHASE = 5, ONLY
    // Flying (Phase = 2,)
    SPELL_THROW_GLAIVE            = 39635, // Throws a glaive on the ground
    SPELL_THROW_GLAIVE2           = 39849, // Animation for the above spell
    SPELL_GLAIVE_RETURNS          = 39873, // Glaive flies back to Illidan
    SPELL_FIREBALL                = 40598, // = 2,.5k-3.5k damage in = 10, yard radius. = 2, second cast time.
    SPELL_DARK_BARRAGE            = 40585, // = 10, second channeled spell, = 3,k shadow damage per second.
    // Demon Form
    SPELL_DEMON_TRANSFORM_1       = 40511, // First phase of animations for transforming into Dark Illidan (fall to ground)
    SPELL_DEMON_TRANSFORM_2       = 40398, // Second phase of animations (kneel)
    SPELL_DEMON_TRANSFORM_3       = 40510, // Final phase of animations (stand up and roar)
    SPELL_DEMON_FORM              = 40506, // Transforms into Demon Illidan. Has an Aura of Dread on him.
    SPELL_SHADOW_BLAST            = 41078, // = 8,k - = 11,k Shadow Damage. Targets highest threat. Has a splash effect, damaging anyone in = 20, yards of the target.
    SPELL_FLAME_BURST             = 41126, // Hurls fire at entire raid for ~3.5k damage every = 10, seconds. Resistable. (Does not work: OLDScript effect)
    SPELL_FLAME_BURST_EFFECT      = 41131, // The actual damage. Have each player cast it on itself (workaround)
    // Other Illidan spells
    SPELL_SHADOW_PRISON           = 40647, // Illidan casts this spell to immobilize entire raid when he summons Maiev.
    SPELL_DEATH                   = 41220, // This spell doesn't do anything except stun Illidan and set him on his knees.
    SPELL_BERSERK                 = 45078, // Damage increased by = 500,%, attack speed by = 150,%
    SPELL_DUAL_WIELD              = 42459,
    //Phase Normal spells
    SPELL_FLAME_CRASH_EFFECT      = 40836, // Firey blue ring of circle that the other flame crash summons
    SPELL_SUMMON_SHADOWDEMON      = 41117, // Summon four shadowfiends
    SPELL_SHADOWFIEND_PASSIVE     = 41913, // Passive aura for shadowfiends, modified : effectApplyAuraName1 = 4
    SPELL_SHADOW_DEMON_PASSIVE    = 41079, // Adds the "shadowform" aura to Shadow Demons.
    SPELL_CONSUME_SOUL            = 41080, // Once the Shadow Demons reach their target, they use this to kill them
    SPELL_PARALYZE                = 41083, // Shadow Demons cast this on their target
    SPELL_PURPLE_BEAM             = 39123, // Purple Beam connecting Shadow Demon to their target
    //Phase Flight spells
    SPELL_AZZINOTH_CHANNEL        = 39857, // Glaives cast it on Flames. Not sure if this is the right spell.
    SPELL_EYE_BLAST_TRIGGER       = 40017, // This summons Demon Form every few seconds and deals ~20k damage in its radius
    SPELL_EYE_BLAST               = 39908, // This does the blue flamey animation.
    SPELL_BLAZE_EFFECT            = 40610, // Green flame on the ground, triggers damage (5k) every few seconds
    SPELL_BLAZE_SUMMON            = 40637, // Summons the Blaze creature
    SPELL_DEMON_FIRE              = 40029, // Blue fire trail left by Eye Blast. Deals = 2,k per second if players stand on it.
    SPELL_FLAME_BLAST             = 40631, // Flames of Azzinoth use this. Frontal cone AoE = 7,k-9k damage.
    SPELL_CHARGE                  = 41581, //40602 // Flames of Azzinoth charges whoever is too far from them. They enrage after this. For simplicity, we'll use the same enrage as Illidan.
    SPELL_FLAME_ENRAGE            = 45078,
    SPELL_SELFSTUN                = 53088, //2.5s stun
    //Akama spells
    SPELL_AKAMA_DOOR_CHANNEL      = 41268, // Akama's channel spell on the door before the Temple Summit
    SPELL_DEATHSWORN_DOOR_CHANNEL = 41269, // Olum and Udalo's channel spell on the door before the Temple Summit
    SPELL_AKAMA_DOOR_FAIL         = 41271, // Not sure where this is really used...
    SPELL_HEALING_POTION          = 40535, // Akama uses this to heal himself to full.
    SPELL_CHAIN_LIGHTNING         = 40536, // = 6938, to = 8062, for = 5, targets
    //Maiev spells
    SPELL_CAGE_TRAP_DUMMY         = 40761, // Put this in DB for cage trap GO.
    SPELL_CAGED                   = 40695, // Caged Trap triggers will cast this on Illidan if he is within = 3, yards
    SPELL_CAGE_TRAP_SUMMON        = 40694, // Summons a Cage Trap GO (bugged) on the ground along with a Cage Trap Disturb Trigger mob (working)
    SPELL_CAGE_TRAP_BEAM          = 40713, // = 8, Triggers on the ground in an octagon cast spells like this on Illidan 'caging him'
    SPELL_TELEPORT_VISUAL         = 41232, // Teleport visual for Maiev
    SPELL_SHADOW_STRIKE           = 40685, // = 4375, to = 5625, every = 3, seconds for = 12, seconds
    SPELL_THROW_DAGGER            = 41152, // = 5400, to = 6600, damage, need dagger
    SPELL_FAN_BLADES              = 39954, // bugged visual
};

// Other defines
#define CENTER_X            676.740
#define CENTER_Y            305.297
#define CENTER_Z            353.192

#define FLAME_ENRAGE_DISTANCE   35
#define FLAME_CHARGE_DISTANCE   50

/**** Creature Summon and Recognition IDs ****/
enum CreatureEntry
{
    EMPTY                   =       0,
    AKAMA                   =   23089,
    ILLIDAN_STORMRAGE       =   22917,
    BLADE_OF_AZZINOTH       =   22996,
    FLAME_OF_AZZINOTH       =   22997,
    MAIEV_SHADOWSONG        =   23197,
    SHADOW_DEMON            =   23375,
    DEMON_FIRE              =   23069,
    FLAME_CRASH             =   23336,
    ILLIDAN_DOOR_TRIGGER    =   23412,
    SPIRIT_OF_OLUM          =   23411,
    SPIRIT_OF_UDALO         =   23410,
    ILLIDARI_ELITE          =   23226,
    PARASITIC_SHADOWFIEND   =   23498,
    CAGE_TRAP_TRIGGER       =   23292,
    INVISIBLE_DUMMY         =   9,
};

/*** Phase Names ***/
enum PhaseIllidan
{
    PHASE_ILLIDAN_NULL          =   0,
    PHASE_NORMAL                =   1, //aka Phase 1
    PHASE_FLIGHT                =   2, //aka Phase 2 : randomizing flight points and casting spells
    PHASE_NORMAL_2              =   3, //aka Phase 3 : when both flames are dead, alternated with PHASE_DEMON
    PHASE_DEMON                 =   4, //aka Phase 4 : alternated with PHASE_NORMAL_2 or PHASE_NORMAL_MAIEV
    PHASE_NORMAL_MAIEV          =   5, //aka Phase 5 : alternated with PHASE_DEMON when reached 30%
    PHASE_TALK_SEQUENCE         =   6,
    PHASE_FLIGHT_SEQUENCE       =   7, //dust off, going into position, enter PHASE_FLIGHT and resume after both flamme are dead, then land
    PHASE_TRANSFORM_SEQUENCE    =   8, //enter or leave PHASE_DEMON
    PHASE_ILLIDAN_MAX           =   9,
};//Maiev uses the same phase

enum PhaseAkama
{
    PHASE_AKAMA_NULL,
    PHASE_COUNCIL_INTRO,
    PHASE_CHANNEL, //channeling and going upstairs
    PHASE_READY, //waiting just before Illidan
    PHASE_WALK, //before AND when returning back to fight elites
    PHASE_TALK,
    PHASE_FIGHT_ILLIDAN,
    PHASE_FIGHT_MINIONS,
    PHASE_RETURN,
};

enum EventIllidan
{
    EVENT_NULL                  =   0,
    EVENT_BERSERK               =   1,
    //normal phase
    EVENT_TAUNT                 =   2,
    EVENT_SHEAR                 =   3,
    EVENT_FLAME_CRASH           =   4,
    EVENT_PARASITIC_SHADOWFIEND =   5,
    EVENT_PARASITE_CHECK        =   6,
    EVENT_DRAW_SOUL             =   7,
    EVENT_AGONIZING_FLAMES      =   8,
    EVENT_TRANSFORM_NORMAL      =   9, //from normal to demon
    EVENT_ENRAGE                =   10,
    //flight phase
    EVENT_FIREBALL              =   2,
    EVENT_DARK_BARRAGE          =   3,
    EVENT_EYE_BLAST             =   4,
    EVENT_MOVE_POINT            =   5,
    //demon phase
    EVENT_SHADOW_BLAST          =   2,
    EVENT_FLAME_BURST           =   3,
    EVENT_SHADOWDEMON           =   4,
    EVENT_TRANSFORM_DEMON       =   5, //from demon to normal
    //sequence phase
    EVENT_TALK_SEQUENCE         =   2,
    EVENT_FLIGHT_SEQUENCE       =   2, //transition P2 -> P3, then P3 -> P4
    EVENT_TRANSFORM_SEQUENCE    =   2,
};

enum EventMaiev
{
    EVENT_MAIEV_NULL            =   0,
    EVENT_MAIEV_STEALTH         =   1,
    EVENT_MAIEV_TAUNT           =   2,
    EVENT_MAIEV_SHADOW_STRIKE   =   3,
    EVENT_MAIEV_THROW_DAGGER    =   4,
    EVENT_MAIEV_TRAP            =   4,
};

static EventIllidan MaxTimer[]=
{
    EVENT_NULL,
    EVENT_DRAW_SOUL, //Phase 1
    EVENT_MOVE_POINT, //Phase 2
    EVENT_TRANSFORM_NORMAL, //Phase 3
    EVENT_TRANSFORM_DEMON, //Phase 4
    EVENT_ENRAGE, //Phase 5
    EVENT_TALK_SEQUENCE,
    EVENT_FLIGHT_SEQUENCE,
    EVENT_TRANSFORM_SEQUENCE
};

struct Yells
{
    int dbEntry;
    uint32 creature, timer, emote;
    bool Talk;
};

static Yells Conversation[]=
{
    {0, ILLIDAN_STORMRAGE, 6000, false},
    {-1566018, ILLIDAN_STORMRAGE, 8000, true},
    {0, ILLIDAN_STORMRAGE, 5000, 396, true},
    {-1566019, AKAMA, 7000, 25, true},
    {0, AKAMA, 5000, 66, true},
    {-1566020, ILLIDAN_STORMRAGE, 8000, 396, true},
    {-1566021, AKAMA, 3000, 22, true},
    {0, AKAMA, 2000, 15, true},
    {-1566022, ILLIDAN_STORMRAGE, 3000, 406, true},
    {0, EMPTY, 1000, 0, true},
    {0, EMPTY, 0, 0, false},//9
    {-1566023, ILLIDAN_STORMRAGE, 8000, 0, true},
    {-1566024, MAIEV_SHADOWSONG, 8000, 5, true},
    {-1566025, ILLIDAN_STORMRAGE, 5000, 1, true},
    {-1566026, MAIEV_SHADOWSONG, 8000, 15, true},
    {-1566027, ILLIDAN_STORMRAGE, 1000, 0, false},//14
    {-1566028, MAIEV_SHADOWSONG, 6000, 0, true},//15
    {-1566029, ILLIDAN_STORMRAGE, 30000, 65, true}, // Emote dead for now. Kill him later
    {-1566030, MAIEV_SHADOWSONG, 9000, 0, true},
    {11498, MAIEV_SHADOWSONG, 5000, 0, true},
    {11498, EMPTY, 1000, 0, true},//19 Maiev disappear
    {-1566031, AKAMA, 8000, 0, true},
    {0, EMPTY, 1000, 0, false}//21
};

static Yells RandomTaunts[]=
{
    {-1566010, ILLIDAN_STORMRAGE, 0, 0, false},
    {-1566011, ILLIDAN_STORMRAGE, 0, 0, false},
    {-1566012, ILLIDAN_STORMRAGE, 0, 0, false},
    {-1566013, ILLIDAN_STORMRAGE, 0, 0, false},
};

static Yells MaievTaunts[]=
{
    {-1566014, MAIEV_SHADOWSONG, 0, 0, false},
    {-1566015, MAIEV_SHADOWSONG, 0, 0, false},
    {-1566016, MAIEV_SHADOWSONG, 0, 0, false},
    {-1566017, MAIEV_SHADOWSONG, 0, 0, false},
};

struct Locations
{
    float x, y, z;
};

static Locations HoverPosition[]=
{
    {657, 340, 355},
    {657, 275, 355},
    {705, 275, 355},
    {705, 340, 355}
};

static Locations GlaivePosition[]=
{
    {678.059998, 285.220001, 354.325012},
    {676.226013, 325.230988, 354.319000},
    {677.792297, 288.365387, 354.143616},
    {676.655762, 321.935272, 354.135986}
};

static Locations EyeBlast[]=
{
    {640.187500, 304.764313, 354},
    {713.145081, 305.173889, 354}
};

static Locations AkamaWPCouncil[]=
{
    {612.28, 305.63, 271.8}, //behind the council door
    {660.89, 305.57, 271.69}, //talk spot
    {755.77, 304.29, 312.18}, //second talk spot (in front of the doors)
};

static Locations AkamaWP[]=
{
    {770.01, 304.50, 312.29}, // Bottom of the first stairs, at the doors
    {780.66, 304.50, 319.74}, // Top of the first stairs
    {788.08, 285.88, 322.49}, // Bottom of the second stairs (right from the entrance)
    {784.33, 262.27, 341.46}, // Top of the second stairs
    {780.72, 257.71, 341.58}, // Bottom of the third stairs
    {762.89, 245.76, 353.65}, // Top of the third stairs
    {750.08, 237.49, 353.01}, // Before the door-thingy
    {742.85, 270.06, 353.00}, // Somewhere further
    {732.69, 305.13, 353.00}, // In front of Illidan - (8)
    {738.11, 365.44, 353.00}, // in front of the door-thingy (the other one!)
    {792.18, 366.62, 341.42}, // Down the first flight of stairs
    {796.84, 304.89, 319.76}, // Down the second flight of stairs
    {782.01, 304.55, 319.76}  // Final location - back at the initial gates. This is where he will fight the minions! (12)
};
// 755.762, 304.0747, 312.1769 -- This is where Akama should be spawned
static Locations SpiritSpawns[]=
{
    {755.5426, 309.9156, 312.2129},
    {755.5426, 298.7923, 312.0834}
};

struct Animation // For the demon transformation
{
    uint32 aura, unaura, timer, size, displayid, phase;
    bool equip;
};

static Animation DemonTransformation[]=
{
    {SPELL_DEMON_TRANSFORM_1, 0, 1000, 0, 0, 6, true},
    {SPELL_DEMON_TRANSFORM_2, SPELL_DEMON_TRANSFORM_1, 4000, 0, 0, 6, true},
    {0, 0, 3000, 1073741824, 21322, 6, false},//stunned, cannot cast demon form
    {SPELL_DEMON_TRANSFORM_3, SPELL_DEMON_TRANSFORM_2, 3500, 0, 0, 6, false},
    {SPELL_DEMON_FORM, SPELL_DEMON_TRANSFORM_3, 0, 0, 0, 4, false},
    {SPELL_DEMON_TRANSFORM_1, 0, 1000, 0, 0, 6, false},
    {SPELL_DEMON_TRANSFORM_2, SPELL_DEMON_TRANSFORM_1, 4000, 0, 0, 6, false},
    {0, SPELL_DEMON_FORM, 3000, 1069547520, 21135, 6, false},
    {SPELL_DEMON_TRANSFORM_3, SPELL_DEMON_TRANSFORM_2, 3500, 0, 0, 6, true},
    {0, SPELL_DEMON_TRANSFORM_3, 0, 0, 0, 8, true}
};

#define EMOTE_SETS_GAZE_ON     "sets its gaze on $N!"
#define EMOTE_UNABLE_TO_SUMMON "is unable to summon Maiev Shadowsong and enter Phase 4. Resetting Encounter."

/************************************** Illidan's AI ***************************************/
struct boss_illidan_stormrageAI : public ScriptedAI
{
    boss_illidan_stormrageAI(Creature* c) : ScriptedAI(c), Summons(me)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        me->CastSpell(me, SPELL_DUAL_WIELD, true);
    }

    InstanceScript* pInstance;

    PhaseIllidan Phase;
    EventIllidan Event;
    uint32 Timer[EVENT_ENRAGE + 1];

    uint32 TalkCount;
    uint32 TransformCount;
    uint32 FlightCount;

    uint32 HoverPoint;

    uint64 AkamaGUID;
    uint64 MaievGUID;
    uint64 FlameGUID[2];
    uint64 GlaiveGUID[2];

    SummonList Summons;

    void Reset() override;

    void JustSummoned(Creature* summon) override;

    void SummonedCreatureDespawn(Creature* summon)
    override {
        if(summon->GetCreatureTemplate()->Entry == FLAME_OF_AZZINOTH)
        {
            for(uint64 & i : FlameGUID)
                if(summon->GetGUID() == i)
                    i = 0;

            if(!FlameGUID[0] && !FlameGUID[1] && Phase == PHASE_FLIGHT)
            {
                me->InterruptNonMeleeSpells(true);
                FlightCount++; //get out of our dummy step
                EnterPhase(PHASE_FLIGHT_SEQUENCE); //start landing 2 sec after
            }
        }
        Summons.Despawn(summon);
    }

    void MovementInform(uint32 MovementType, uint32 Data)
    override {
        if(FlightCount == 7) //we're in or should be entering PHASE_FLIGHT
        {
            if(me->GetVictim())
            {
                me->SetInFront(me->GetVictim());
                me->StopMoving();
            }
            EnterPhase(PHASE_FLIGHT); //just reset timers
        }
        else // handle flight sequence
            Timer[EVENT_FLIGHT_SEQUENCE] = 1000;
    }

    void EnterCombat(Unit *who)
    override {
        me->SetKeepActive(true);
        DoZoneInCombat();
    }

    void AttackStart(Unit *who)
    override {
        if(!who || Phase >= PHASE_TALK_SEQUENCE)
            return;

        if(Phase == PHASE_FLIGHT || Phase == PHASE_DEMON)
            ScriptedAI::AttackStart(who, false);
        else
            ScriptedAI::AttackStart(who, true);
    }

    void MoveInLineOfSight(Unit *who) override {}

    void JustDied(Unit *killer)
    override {
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

        if(!pInstance)
            return;

        pInstance->SetData(DATA_ILLIDANSTORMRAGEEVENT, DONE); // Completed

        for(uint8 i = DATA_GAMEOBJECT_ILLIDAN_DOOR_R; i < DATA_GAMEOBJECT_ILLIDAN_DOOR_L + 1; ++i)
        {
            GameObject* Door = GameObject::GetGameObject((*me), pInstance->GetData64(i));
            if(Door)
                Door->UseDoorOrButton(); // Open Doors
        }
    }

    void KilledUnit(Unit *victim)
    override {
        if(victim == me) return;

        DoScriptText(rand()%2 ? SAY_KILL1 : SAY_KILL2, me);
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    override {
        if(damage >= me->GetHealth() && done_by != me) {
            if (Phase != PHASE_NORMAL_MAIEV)
                Phase = PHASE_NORMAL_MAIEV;
            damage = 0;
        }
        if(done_by->GetGUID() == MaievGUID)
            done_by->AddThreat(me, -(3*(float)damage)/4); // do not let maiev tank him
    }

    void SpellHit(Unit *caster, const SpellInfo *spell)
    override {
        if(spell->Id == SPELL_GLAIVE_RETURNS) // Re-equip our warblades!
        {
            if(!me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY))
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 45479);
            else
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 45481);
            me->SetSheath(SHEATH_STATE_MELEE);
        }
    }

    void DeleteFromThreatList(uint64 TargetGUID)
    {
        for(auto & itr : me->getThreatManager().getThreatList())
        {
            if(itr->getUnitGuid() == TargetGUID)
            {
                itr->removeReference();
                break;
            }
        }
    }

    void Talk(uint32 count)
    {
        Timer[EVENT_TALK_SEQUENCE] = Conversation[count].timer;

        Creature* creature = nullptr;
        if(Conversation[count].creature == ILLIDAN_STORMRAGE)
            creature = me;
        else if(Conversation[count].creature == AKAMA)
            creature = (ObjectAccessor::GetCreature((*me), AkamaGUID));
        else if(Conversation[count].creature == MAIEV_SHADOWSONG)
            creature = (ObjectAccessor::GetCreature((*me), MaievGUID));

        if(creature)
        {
            if(Conversation[count].emote)
                creature->HandleEmoteCommand(Conversation[count].emote); // Make the creature do some animation!
            if(Conversation[count].dbEntry)
                DoScriptText(Conversation[count].dbEntry,creature);
        }
    }

    void EnterPhase(PhaseIllidan NextPhase);
    bool CastEyeBlast();
    void SummonFlamesOfAzzinoth();
    void SummonMaiev();
    void HandleTalkSequence();
    void HandleFlightSequence()
    {
        switch(FlightCount)
        {
        case 1://lift off
            me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
            me->SetDisableGravity(true);
            me->StopMoving();
            DoScriptText(SAY_TAKEOFF,me);
            Timer[EVENT_FLIGHT_SEQUENCE] = 3000;
            break;
        case 2://move to center
            me->GetMotionMaster()->MovePoint(0, CENTER_X + 5, CENTER_Y, CENTER_Z); //+5, for SPELL_THROW_GLAIVE bug
            Timer[EVENT_FLIGHT_SEQUENCE] = 0;
            break;
        case 3://throw one glaive
            {
                uint8 i=1;
                Creature* Glaive = me->SummonCreature(BLADE_OF_AZZINOTH, GlaivePosition[i].x, GlaivePosition[i].y, GlaivePosition[i].z, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                if(Glaive)
                {
                    GlaiveGUID[i] = Glaive->GetGUID();
                    Glaive->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    Glaive->SetUInt32Value(UNIT_FIELD_DISPLAYID, 11686);
                    Glaive->SetFaction(me->GetFaction());
                    DoCast(Glaive, SPELL_THROW_GLAIVE2);
                }
            }
            Timer[EVENT_FLIGHT_SEQUENCE] = 700;
            break;
        case 4://throw another
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 0);
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
            {
                uint8 i=0;
                Creature* Glaive = me->SummonCreature(BLADE_OF_AZZINOTH, GlaivePosition[i].x, GlaivePosition[i].y, GlaivePosition[i].z, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                if(Glaive)
                {
                    GlaiveGUID[i] = Glaive->GetGUID();
                    Glaive->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    Glaive->SetUInt32Value(UNIT_FIELD_DISPLAYID, 11686);
                    Glaive->SetFaction(me->GetFaction());
                    DoCast(Glaive, SPELL_THROW_GLAIVE, true);
                }
            }
            Timer[EVENT_FLIGHT_SEQUENCE] = 5000;
            break;
        case 5://summon flames
            SummonFlamesOfAzzinoth();
            Timer[EVENT_FLIGHT_SEQUENCE] = 3000;
            break;
        case 6://fly to hover point
            HoverPoint = rand()%4; //randomize first hover point
            me->GetMotionMaster()->MovePoint(0, HoverPosition[HoverPoint].x, HoverPosition[HoverPoint].y, HoverPosition[HoverPoint].z);
            Timer[EVENT_FLIGHT_SEQUENCE] = 0;
            //this phase will is resumed only when both flammes are dead, see SummonedCreatureDespawn(...)
            //Phase will be set to PHASE_FLIGHT when reaching MovePoint
            break;
        case 7: //Dummy step, should never happen. This is here to debug one recurring bug. PHASE_FLIGHT should always have FlightCount = 7
            TC_LOG_ERROR("scripts","Illidan : Entered HandleFlightSequence 7 (should never happen)");
            Timer[EVENT_FLIGHT_SEQUENCE] = 1;
            break;
        case 8://end this phase, return to center
            me->InterruptNonMeleeSpells(true);
            me->GetMotionMaster()->MovePoint(0, CENTER_X, CENTER_Y, CENTER_Z);
            Timer[EVENT_FLIGHT_SEQUENCE] = 0;
            break;
        case 9://glaive return
            for(uint64 i : GlaiveGUID)
            {
                if(i)
                {
                    Unit* Glaive = ObjectAccessor::GetUnit((*me), i);
                    if(Glaive)
                    {
                        Glaive->CastSpell(me, SPELL_GLAIVE_RETURNS, false); // Make it look like the Glaive flies back up to us
                        Glaive->SetUInt32Value(UNIT_FIELD_DISPLAYID, 11686); // disappear but not die for now
                    }
                }
            }
            Timer[EVENT_FLIGHT_SEQUENCE] = 2000;
            break;
        case 10://land
            me->SetDisableGravity(false);
            me->StopMoving();
            me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
            for(uint64 & i : GlaiveGUID)
            {
                if(i)
                {
                    if(GETUNIT(Glaive, i))
                    {
                        Glaive->SetVisible(false);
                        Glaive->SetDeathState(JUST_DIED); // Despawn the Glaive
                    }
                    i = 0;
                }
            }
            Timer[EVENT_FLIGHT_SEQUENCE] = 4000;
            break;
        case 11://attack
            DoResetThreat();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE + UNIT_FLAG_NOT_SELECTABLE);
            me->SetSheath(SHEATH_STATE_MELEE);
            EnterPhase(PHASE_NORMAL_2);
            break;
        default:
            break;
        }
        FlightCount++;
    }

    void HandleTransformSequence()
    {
        if(DemonTransformation[TransformCount].unaura)
            me->RemoveAurasDueToSpell(DemonTransformation[TransformCount].unaura);

        if(DemonTransformation[TransformCount].aura)
            DoCast(me, DemonTransformation[TransformCount].aura, true);

        if(DemonTransformation[TransformCount].displayid)
            me->SetUInt32Value(UNIT_FIELD_DISPLAYID, DemonTransformation[TransformCount].displayid); // It's morphin time!

        if(DemonTransformation[TransformCount].equip)
        {
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 45479); // Requip warglaives if needed
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 45481);
            me->SetSheath(SHEATH_STATE_MELEE);
        }
        else
        {
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 0); // Unequip warglaives if needed
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
        }

        switch(TransformCount)
        {
        case 2:
            DoResetThreat();
            break;
        case 4:
            EnterPhase(PHASE_DEMON);
            break;
        case 7:
            DoResetThreat();
            break;
        case 9:
            if(MaievGUID)
                EnterPhase(PHASE_NORMAL_MAIEV); // Depending on whether we summoned Maiev, we switch to either phase 5 or 3
            else
                EnterPhase(PHASE_NORMAL_2);
            break;
        default:
            break;
        }
        if(Phase == PHASE_TRANSFORM_SEQUENCE)
            Timer[EVENT_TRANSFORM_SEQUENCE] = DemonTransformation[TransformCount].timer;
        TransformCount++;
    }

    void UpdateAI(const uint32 diff)
    override {
        if((!UpdateVictim()) && Phase < PHASE_TALK_SEQUENCE)
            return;
        
        if(me->GetVictim() && (me->GetVictim()->GetEntry() == AKAMA || me->GetVictim()->GetEntry() == MAIEV_SHADOWSONG))
        {
            //Reset if no other targets
            if(me->getThreatManager().getThreatList().size() == 1)
            {
                EnterEvadeMode();
                return;
            }
        }

        Event = EVENT_NULL;
        for(uint32 i = 1; i <= MaxTimer[Phase]; i++)
        {
            if(Timer[i]) // Event is enabled
            {
                if(Timer[i] <= diff)
                {
                    if(!Event) // No event with higher priority
                        Event = (EventIllidan)i;
                }
                else Timer[i] -= diff;
            }
        }

        switch(Phase)
        {
        case PHASE_NORMAL:
            if(HPPCT(me) < 65)
                EnterPhase(PHASE_FLIGHT_SEQUENCE);
            break;

        case PHASE_NORMAL_2:
            if(HPPCT(me) < 30) {
                EnterPhase(PHASE_TALK_SEQUENCE);
                Summons.DespawnEntry(PARASITIC_SHADOWFIEND);
            }
            break;

        case PHASE_NORMAL_MAIEV:
            if(HPPCT(me) < 1)
                EnterPhase(PHASE_TALK_SEQUENCE);
            break;

        case PHASE_TALK_SEQUENCE:
            if(Event == EVENT_TALK_SEQUENCE)
                HandleTalkSequence();
            break;

        case PHASE_FLIGHT_SEQUENCE: //end via SummonedCreatureDespawn
            if(Event == EVENT_FLIGHT_SEQUENCE)
                HandleFlightSequence();
            break;

        case PHASE_TRANSFORM_SEQUENCE:
            if(Event == EVENT_TRANSFORM_SEQUENCE)
                HandleTransformSequence();
            break;
        }

        if(me->IsNonMeleeSpellCast(false))
            return;

        //Handle various spells for each phases
        if(Phase == PHASE_NORMAL || Phase == PHASE_NORMAL_2 || (Phase == PHASE_NORMAL_MAIEV && !me->HasAuraEffect(SPELL_CAGED, 0)))
        {
            switch(Event)
            {
                //PHASE_NORMAL
            case EVENT_BERSERK:
                DoScriptText(SAY_ENRAGE,me);
                DoCast(me, SPELL_BERSERK, true);
                Timer[EVENT_BERSERK] = 5000;//The buff actually lasts forever.
                break;

            case EVENT_TAUNT:
                {
                    uint32 random = rand()%4;
                    uint32 dbEntry = RandomTaunts[random].dbEntry;
                    if(dbEntry)
                        DoScriptText(dbEntry,me);
                }
                Timer[EVENT_TAUNT] = 25000 + rand()%10000;
                break;

            case EVENT_SHEAR:
                if(DoCast(me->GetVictim(), SPELL_SHEAR) == SPELL_CAST_OK)
                    Timer[EVENT_SHEAR] = 10000 + (rand()%5000);
                break;

            case EVENT_FLAME_CRASH:
                if(DoCast(me->GetVictim(), SPELL_FLAME_CRASH) == SPELL_CAST_OK)
                    Timer[EVENT_FLAME_CRASH] = 23000 + rand()%4000;
                break;

            case EVENT_PARASITIC_SHADOWFIEND:
                {
                    if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0, true, true))
                        me->CastSpell(target, SPELL_PARASITIC_SHADOWFIEND, true);
                    Timer[EVENT_PARASITIC_SHADOWFIEND] = 35000 + rand()%10000;
                }break;

            case EVENT_PARASITE_CHECK:
                Timer[EVENT_PARASITE_CHECK] = 0;
                break;

            case EVENT_DRAW_SOUL:
                if(DoCast(me->GetVictim(), SPELL_DRAW_SOUL) == SPELL_CAST_OK)
                    Timer[EVENT_DRAW_SOUL] = 28000 + rand()%4000;
                break;

                //PHASE_NORMAL_2
            case EVENT_AGONIZING_FLAMES:
                if(DoCast(SelectTarget(SELECT_TARGET_RANDOM,0), SPELL_AGONIZING_FLAMES) == SPELL_CAST_OK)
                    Timer[EVENT_AGONIZING_FLAMES] = 0;
                break;

            case EVENT_TRANSFORM_NORMAL: //transform from normal to demon
                EnterPhase(PHASE_TRANSFORM_SEQUENCE);
                break;

                //PHASE_NORMAL_MAIEV
            case EVENT_ENRAGE:
                if(DoCast(me, SPELL_ENRAGE) == SPELL_CAST_OK)
                    Timer[EVENT_ENRAGE] = 0;
                break;

            default:
                break;
            }
            DoMeleeAttackIfReady();
        }

        if(Phase == PHASE_FLIGHT)
        {
            switch(Event)
            {
            case EVENT_FIREBALL:
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_FIREBALL);
                Timer[EVENT_FIREBALL] = 3000;
                break;

            //25% chance to be cast each time we enter PHASE_FLIGHT
            case EVENT_DARK_BARRAGE:
                if(DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f, true), SPELL_DARK_BARRAGE) == SPELL_CAST_OK)
                    Timer[EVENT_DARK_BARRAGE] = 0;
                break;

            case EVENT_EYE_BLAST:
                if(CastEyeBlast())
                    Timer[EVENT_EYE_BLAST] = 45000;
                break;

            case EVENT_MOVE_POINT:
                Phase = PHASE_FLIGHT_SEQUENCE;
                Timer[EVENT_FLIGHT_SEQUENCE] = 0;//do not start Event when changing hover point
                HoverPoint += (rand()%3 + 1); //randomize a different hover point
                if(HoverPoint > 3)
                    HoverPoint -= 4;
                me->GetMotionMaster()->MovePoint(0, HoverPosition[HoverPoint].x, HoverPosition[HoverPoint].y, HoverPosition[HoverPoint].z);
                break;

            default:
                break;
            }
        }

        if(Phase == PHASE_DEMON)
        {
            switch(Event)
            {
            case EVENT_SHADOW_BLAST:
                me->GetMotionMaster()->Clear(false);
                if(!me->IsWithinDistInMap(me->GetVictim(), 50)||!me->IsWithinLOSInMap(me->GetVictim()))
                    me->GetMotionMaster()->MoveChase(me->GetVictim(), 30);
                else
                    me->GetMotionMaster()->MoveIdle();
                if(DoCast(me->GetVictim(), SPELL_SHADOW_BLAST) == SPELL_CAST_OK)
                    Timer[EVENT_SHADOW_BLAST] = 4000;
                break;
            case EVENT_SHADOWDEMON:
                me->InterruptNonMeleeSpells(true);
                if(DoCast(me, SPELL_SUMMON_SHADOWDEMON) == SPELL_CAST_OK)
                {
                    Timer[EVENT_SHADOWDEMON] = 0;
                    Timer[EVENT_FLAME_BURST] += 10000;
                }
                break;
            case EVENT_FLAME_BURST:
                me->InterruptNonMeleeSpells(true);
                if(DoCast(me, SPELL_FLAME_BURST) == SPELL_CAST_OK)
                    Timer[EVENT_FLAME_BURST] = 20000;
                break;
            case EVENT_TRANSFORM_DEMON:
                EnterPhase(PHASE_TRANSFORM_SEQUENCE);
                break;
            default:
                break;
            }
        }
    }
};

/********************************** End of Illidan AI ******************************************/

struct flame_of_azzinothAI : public ScriptedAI
{
    flame_of_azzinothAI(Creature *c) : ScriptedAI(c) 
    {
        DoCast(me,SPELL_SELFSTUN,true); //2.5sec inactivity at spawn        
        me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, true);
    }

    uint32 FlameBlastTimer;
    uint32 CheckTimer;
    uint64 GlaiveGUID;

    void Reset()
    override {
        FlameBlastTimer = 15000;
        CheckTimer = 5000;
        GlaiveGUID = 0;
    }

    void EnterCombat(Unit *who) override {DoZoneInCombat();}

    void ChargeCheck()
    {
        Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 200, false);
        if(target && (!me->IsWithinCombatRange(target, FLAME_CHARGE_DISTANCE)))
        {
            me->AddThreat(target, 5000000.0f);
            AttackStart(target);
            DoCast(target, SPELL_CHARGE);
            //me->TextEmote("pose son regard sur %n !", target); //"sets its gaze on $N!"
        }
    }

    //Enrage if too far from glaive
    void EnrageCheck()
    {
        if(GETUNIT(Glaive, GlaiveGUID))
        {
            if(!me->IsWithinDistInMap(Glaive, FLAME_ENRAGE_DISTANCE))
            {
                Glaive->InterruptNonMeleeSpells(true);
                DoCast(me, SPELL_FLAME_ENRAGE, true);
                DoResetThreat();
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                if(target && target->IsAlive())
                {
                    me->AddThreat(me->GetVictim(), 5000000.0f);
                    AttackStart(me->GetVictim());
                }
            }
            /*
            else if(!me->HasAuraEffect(SPELL_AZZINOTH_CHANNEL, 0))
            {
                Glaive->CastSpell(me, SPELL_AZZINOTH_CHANNEL, false);
                me->RemoveAurasDueToSpell(SPELL_FLAME_ENRAGE);
            } */
        }
    }

    void SetGlaiveGUID(uint64 guid){ GlaiveGUID = guid; }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;
            
        // If a warlock ban a Flame of Azzinoth, remove ban aura and instakill him (he won't do it twice)
        if (me->HasAuraEffect(710) || me->HasAuraEffect(18647)) {
            if (me->HasAuraEffect(710)) {
                if (Aura* aur = me->GetAura(710, 0)) {
                    if (Player* plr = (aur->GetCaster())->ToPlayer())
                        plr->DealDamage(plr, plr->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                }
                me->RemoveAurasDueToSpell(710);
            }
            else {
                if (Aura* aur = me->GetAura(18647, 0)) {
                    if (Player* plr = (aur->GetCaster())->ToPlayer())
                        plr->DealDamage(plr, plr->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                }
                me->RemoveAurasDueToSpell(18647);
            }
        }

        if(FlameBlastTimer < diff)
        {
            DoCast(me->GetVictim(), SPELL_BLAZE_SUMMON, true); //appear at victim
            DoCast(me->GetVictim(), SPELL_FLAME_BLAST);
            FlameBlastTimer = 15000;
            DoZoneInCombat(); //in case someone is revived
        }else FlameBlastTimer -= diff;

        if(CheckTimer < diff)
        {
            ChargeCheck();
            EnrageCheck();
            CheckTimer = 1000;
        }else CheckTimer -= diff;

        DoMeleeAttackIfReady();
    }
};



/******* Functions and vars for Akama's AI ******/
struct npc_akama_illidanAI : public ScriptedAI
{
    npc_akama_illidanAI(Creature* c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        JustCreated = true;
        introDone = false;
        baseFaction = me->GetFaction();
        me->SetFaction(FACTION_FRIENDLY); //temporary set to be sure to avoid the akama wandering all over the instance bug

        if(pInstance && pInstance->GetData(DATA_ILLIDARICOUNCILEVENT) != DONE)
        {
            councilEventDone = false;
            me->Relocate(AkamaWPCouncil[0].x, AkamaWPCouncil[0].y, AkamaWPCouncil[0].z); //behind council door
        } else
            councilEventDone = true;
    }

    bool JustCreated;
    bool introDone;
    bool councilEventDone;

    InstanceScript* pInstance;

    PhaseAkama Phase;
    bool Event;
    uint32 Timer;

    uint64 IllidanGUID;
    uint64 ChannelGUID;
    uint64 SpiritGUID[2];
    uint64 GateGUID; //below stairs
    uint64 DoorGUID[2]; //upstairs

    uint32 CouncilIntroCount;
    uint32 ChannelCount;
    uint32 WalkCount;
    uint32 TalkCount;
    uint32 Check_Timer;

    uint32 baseFaction;

    void Reset()
    override {
        WalkCount = 0;
        if(pInstance)
        {
            pInstance->SetData(DATA_ILLIDANSTORMRAGEEVENT, NOT_STARTED);

            IllidanGUID = pInstance->GetData64(DATA_ILLIDANSTORMRAGE);
            GateGUID = pInstance->GetData64(DATA_GAMEOBJECT_ILLIDAN_GATE);
            DoorGUID[0] = pInstance->GetData64(DATA_GAMEOBJECT_ILLIDAN_DOOR_R);
            DoorGUID[1] = pInstance->GetData64(DATA_GAMEOBJECT_ILLIDAN_DOOR_L);

            if(JustCreated)//close all doors at create
            {
                pInstance->HandleGameObject(GateGUID, false);

                for (uint64 i : DoorGUID)
                    pInstance->HandleGameObject(i, false);
                JustCreated = false;
            }else
            {//open all doors, raid wiped
                pInstance->HandleGameObject(GateGUID, true);
                WalkCount = 1;//skip first wp
                for (uint64 i : DoorGUID)
                    pInstance->HandleGameObject(i, true);
            }
        }
        else
        {
            IllidanGUID = 0;
            GateGUID = 0;
            DoorGUID[0] = 0;
            DoorGUID[1] = 0;
        }

        ChannelGUID = 0;
        SpiritGUID[0] = 0;
        SpiritGUID[1] = 0;

        if(introDone)
            Phase = PHASE_READY;
        else
            Phase = PHASE_AKAMA_NULL;
        
        Timer = 0;

        CouncilIntroCount = 0;
        ChannelCount = 0;
        WalkCount = 0;
        TalkCount = 0;
        Check_Timer = 5000;

        KillAllElites();

        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        me->SetSheath(SHEATH_STATE_UNARMED);
        me->SetKeepActive(false);
        if (pInstance->GetData(DATA_ILLIDARICOUNCILEVENT) != DONE)
            me->SetVisible(false);
        else
            me->SetVisible(true);
            
        me->SetReactState(REACT_PASSIVE);
    }

    // Do not call reset in Akama's evade mode, as this will stop him from summoning minions after he kills the first bit
    void EnterEvadeMode(EvadeReason /* why */) override
    {
        me->InterruptNonMeleeSpells(true);
        me->RemoveAllAuras();
        me->DeleteThreatList();
        me->CombatStop(true);
    }

    void EnterCombat(Unit *who)
    override {
		if (!me->IsVisible())
            me->CombatStop();
    }

    void MoveInLineOfSight(Unit *) override {}

    void MovementInform(uint32 MovementType, uint32 Data)
    override {
        if(MovementType == POINT_MOTION_TYPE)
            Timer = 1;
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    override {
        if(damage > me->GetHealth() || done_by->GetGUID() != IllidanGUID)
            damage = 0;
    }

    void KillAllElites()
    {
        std::list<HostileReference*>& threatList = me->getThreatManager().getThreatList();
        std::vector<Unit*> eliteList;
        for(auto & itr : threatList)
        {
            Unit* pUnit = ObjectAccessor::GetUnit((*me), itr->getUnitGuid());
            if(pUnit && pUnit->GetEntry() == ILLIDARI_ELITE)
                eliteList.push_back(pUnit);
        }
        for(auto & itr : eliteList)
            itr->SetDeathState(JUST_DIED);
        EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
    }

    void BeginTalk()
    {
        if(pInstance)
            pInstance->SetData(DATA_ILLIDANSTORMRAGEEVENT, IN_PROGRESS);

        for(uint64 i : DoorGUID)
            if(GETGO(Door, i))
                Door->SetUInt32Value(GAMEOBJECT_STATE, 1);

        if(GETCRE(Illidan, IllidanGUID))
        {
            //Illidan->AddThreat(me,99999.0f); //be sure we won't face another target for now
            me->SetInFront(Illidan);
            //Illidan->SetInFront(me);
            me->SendMovementFlagUpdate();
            //Illidan->SendMovementFlagUpdate();
            ((boss_illidan_stormrageAI*)Illidan->AI())->AkamaGUID = me->GetGUID();
            ((boss_illidan_stormrageAI*)Illidan->AI())->EnterPhase(PHASE_TALK_SEQUENCE);
        }
    }

    void OpenUpperDoors()
    {
        for(uint64 i : DoorGUID)
            if(GETGO(Door, i))
                Door->UseDoorOrButton();
    }

    void BeginChannel()
    {
        GateGUID = pInstance->GetData64(DATA_GAMEOBJECT_ILLIDAN_GATE);
        DoorGUID[0] = pInstance->GetData64(DATA_GAMEOBJECT_ILLIDAN_DOOR_R);
        DoorGUID[1] = pInstance->GetData64(DATA_GAMEOBJECT_ILLIDAN_DOOR_L);

        OpenUpperDoors();

        me->SetSpeedRate(MOVE_RUN, 1.0f);

        for(uint8 i = 0; i < 2; ++i)
            if(Creature* Spirit = me->SummonCreature(i ? SPIRIT_OF_UDALO : SPIRIT_OF_OLUM, SpiritSpawns[i].x, SpiritSpawns[i].y, SpiritSpawns[i].z, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 360000))
            {
                Spirit->SetVisible(false);
                Spirit->RemoveFlag(UNIT_NPC_FLAGS,UNIT_NPC_FLAG_GOSSIP);
                SpiritGUID[i] = Spirit->GetGUID();
            }

                
        float x, y, z;
		if (GETGO(Gate, GateGUID))
			Gate->GetPosition(x, y, z);
		else
			return;

        if(Creature* Channel = me->SummonCreature(ILLIDAN_DOOR_TRIGGER, x, y, z+5, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 360000))
        {
            ChannelGUID = Channel->GetGUID();
            Channel->SetUInt32Value(UNIT_FIELD_DISPLAYID, 11686); // Invisible but spell visuals can still be seen.
        }
    }

    void EnterPhase(PhaseAkama NextPhase)
    {
        me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING); //why does this seem to be reset sometimes ?
        if(!pInstance)  return;
        switch(NextPhase)
        {
        case PHASE_COUNCIL_INTRO:
            me->SetFaction(baseFaction); //restore our faction
            CouncilIntroCount = 0;
            Timer = 1;
            break;
        case PHASE_CHANNEL:
            BeginChannel();
            Timer = 1;
            ChannelCount = 0;
            me->SetFaction(baseFaction); //restore our faction
            me->SetSheath(SHEATH_STATE_UNARMED);
            break;
        case PHASE_READY:
            me->SetHomePosition(AkamaWP[6].x, AkamaWP[6].y, AkamaWP[6].z, 2.0); //upstairs
            if(GETCRE(Illidan, IllidanGUID))
            {
                ((boss_illidan_stormrageAI*)Illidan->AI())->DeleteFromThreatList(me->GetGUID());
                me->SetInFront(Illidan);
                me->SendMovementFlagUpdate();
            }
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            OpenUpperDoors();
            break;
        case PHASE_WALK:
            me->RemoveFlag(UNIT_NPC_FLAGS,UNIT_NPC_FLAG_GOSSIP);
            if(Phase == PHASE_READY) 
                WalkCount = 7;
            else if(Phase == PHASE_TALK)
            {
                if(GETCRE(Illidan, IllidanGUID))
                    ((boss_illidan_stormrageAI*)Illidan->AI())->DeleteFromThreatList(me->GetGUID());
                EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                WalkCount++;
            }
            Timer = 1;
            break;
        case PHASE_TALK:
            if(Phase == PHASE_WALK)
            {
                BeginTalk();
                Timer = 0;
            }
            else if(Phase == PHASE_FIGHT_ILLIDAN)
            {
                Timer = 1;
                TalkCount = 0;
            }
            break;
        case PHASE_FIGHT_ILLIDAN:
            me->SetSheath(SHEATH_STATE_MELEE);
            me->SetReactState(REACT_DEFENSIVE); //else the MoveChase in AttackStart fails
            if(GETUNIT(Illidan, IllidanGUID))
                AttackStart(Illidan,true);

            Timer = 30000; //chain lightning
            break;
        case PHASE_FIGHT_MINIONS:
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            Timer = 10000 + rand()%6000;//summon minion
            break;
        case PHASE_RETURN:
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            KillAllElites();
            WalkCount = 0;
            Timer = 1;
            break;
        default:
            break;
        }
        Phase = NextPhase;
        Event = false;
    }

    void HandleCouncilIntro()
    {
        switch(CouncilIntroCount)
        {
        case 0:
            me->SetSheath(SHEATH_STATE_UNARMED);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetVisible(true);
            me->GetMotionMaster()->MovePoint(WalkCount, AkamaWPCouncil[1].x, AkamaWPCouncil[1].y, AkamaWPCouncil[1].z); //go trough door
            Timer = 0;
            break;
        case 1:
            DoScriptText(SAY_AKAMA_INTRO1,me);
            Timer = 5000;
            break;
        case 2:
            DoScriptText(SAY_AKAMA_INTRO2,me);
            Timer = 6000;
            break;
        case 3:
            me->GetMotionMaster()->MovePoint(WalkCount, AkamaWPCouncil[2].x, AkamaWPCouncil[2].y, AkamaWPCouncil[2].z); //upstairs
            Timer = 0;
            break;
        case 4:
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetOrientation(0); //face the door
            me->SendMovementFlagUpdate();
            councilEventDone = true;
            DoScriptText(SAY_AKAMA_STANDASIDE, me);
            Phase = PHASE_AKAMA_NULL;
        }
        CouncilIntroCount++;
    }

    void HandleTalkSequence()
    {
        switch(TalkCount)
        {
        case 0:
            if(GETCRE(Illidan, IllidanGUID))
            {
                ((boss_illidan_stormrageAI*)Illidan->AI())->Timer[EVENT_TAUNT] += 30000;
                DoScriptText(SAY_AKAMA_MINION, Illidan);
            }
            Timer = 8000;
            break;
        case 1:
            DoScriptText(SAY_AKAMA_LEAVE, me);
            Timer = 3000;
            break;
        case 2:
            EnterPhase(PHASE_WALK);
            break;
        }
        TalkCount++;
    }

    void HandleChannelSequence()
    {
		Unit* Channel = nullptr;
		Unit* Spirit[2] = { nullptr };

        if(ChannelCount <= 10)
        {
            Channel = ObjectAccessor::GetUnit((*me), ChannelGUID);
            Spirit[0] = ObjectAccessor::GetUnit((*me), SpiritGUID[0]);
            Spirit[1] = ObjectAccessor::GetUnit((*me), SpiritGUID[1]);
            if(!Channel || !Spirit[0] || !Spirit[1])
                return;
        }

        switch(ChannelCount)
        {
        case 0:
            me->SetKeepActive(true);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            introDone = true;
            Timer = 4000;
            break;
        case 1:
            DoCast(Channel, SPELL_AKAMA_DOOR_FAIL);
            Timer = 5000;
            break;
        case 2: // channel failed
            me->InterruptNonMeleeSpells(true);
            Timer = 2000;
            break;
        case 3:
            DoScriptText(SAY_AKAMA_CHANNELFAIL,me);
            Timer = 2500;
            break;
        case 4: // spirit appear
            Spirit[0]->SetVisible(true);
            Timer = 1500;
            break;
        case 5:
            DoScriptText(SAY_UDALO_NOTALONE,Spirit[0]);
            Spirit[1]->SetVisible(true);
            Timer = 3000;
            break;
        case 6:
            DoScriptText(SAY_OLUM_NOTALONE,Spirit[1]);
            Timer = 3000;
            break;
        case 7: // spirit help
            DoCast(Channel, SPELL_AKAMA_DOOR_CHANNEL);
            Spirit[0]->CastSpell(Channel, SPELL_DEATHSWORN_DOOR_CHANNEL,false);
            Spirit[1]->CastSpell(Channel, SPELL_DEATHSWORN_DOOR_CHANNEL,false);
            Timer = 5000;
            break;
        case 8: //open the gate
            me->InterruptNonMeleeSpells(true);
            Spirit[0]->InterruptNonMeleeSpells(true);
            Spirit[1]->InterruptNonMeleeSpells(true);
            if(GETGO(Gate, GateGUID))
                Gate->UseDoorOrButton();
            Timer = 2000;
            break;
        case 9:
            me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
            DoScriptText(SAY_AKAMA_THANKS,me);
            Spirit[0]->SetVisible(false);
            Spirit[1]->SetVisible(false);
            Timer = 2000;
            break;
        case 10:
            Channel->SetDeathState(JUST_DIED);
            Spirit[0]->SetDeathState(JUST_DIED);
            Spirit[1]->SetDeathState(JUST_DIED);
            Timer = 3000;
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            me->GetMotionMaster()->MovePoint(0, AkamaWP[ChannelCount-11].x, AkamaWP[ChannelCount-11].y, AkamaWP[ChannelCount-11].z); // WP 0 to 6
            Timer = 0;
            break;
        case 18:
            DoScriptText(SAY_AKAMA_BEWARE, me);
            EnterPhase(PHASE_READY); //wait for players to ask to start
            break;
        }
        ChannelCount++;
    }

    void HandleWalkSequence()
    {
        switch(WalkCount)
        {
        case 8:
            if(Phase == PHASE_WALK)
                EnterPhase(PHASE_TALK);
            else
                EnterPhase(PHASE_FIGHT_ILLIDAN);
            break;
        case 12:
            EnterPhase(PHASE_FIGHT_MINIONS);
            break;
        }

        if(Phase == PHASE_WALK)
        {
            Timer = 0;
            WalkCount++;
            me->GetMotionMaster()->MovePoint(WalkCount, AkamaWP[WalkCount].x, AkamaWP[WalkCount].y, AkamaWP[WalkCount].z);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!me->IsVisible())
        {
            if (Check_Timer <= diff)
            {
                if(pInstance && pInstance->GetData(DATA_ILLIDARICOUNCILEVENT) == DONE)
                {
                    me->SetVisible(true);
                    if(!councilEventDone)
                        EnterPhase(PHASE_COUNCIL_INTRO);
                }

                Check_Timer = 5000;
            } else Check_Timer -= diff;
        }
        
        Event = false;
        if(Timer)
        {
            if(Timer <= diff)
                Event = true;
            else Timer -= diff;
        }

        if(Event)
        {
            switch(Phase)
            {
            case PHASE_COUNCIL_INTRO:
                HandleCouncilIntro();
                break;
            case PHASE_CHANNEL:
                HandleChannelSequence();
                break;
            case PHASE_TALK:
                HandleTalkSequence();
                break;
            case PHASE_WALK:
            case PHASE_RETURN:
                HandleWalkSequence();
                break;
            case PHASE_FIGHT_ILLIDAN:
                DoCast(me->GetVictim(), SPELL_CHAIN_LIGHTNING);
                Timer = 30000;
                break;
            case PHASE_FIGHT_MINIONS:
                {
                    float x, y, z;
                    me->GetPosition(x, y, z);
                    /*Creature* Elite = me->SummonCreature(ILLIDARI_ELITE, x+rand()%10, y+rand()%10, z, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                    //Creature* Elite = me->SummonCreature(ILLIDARI_ELITE, x, y, z, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                    if(Elite)
                    {
                        Elite->AI()->AttackStart(me);
                        Elite->AddThreat(me, 1000000.0f);
                        AttackStart(Elite);
                        me->AddThreat(Elite, 1000000.0f);
                    }*/
                    Timer = 10000 + rand()%6000;
                    GETUNIT(Illidan, IllidanGUID);
                    if(Illidan && HPPCT(Illidan) < 10)
                        EnterPhase(PHASE_RETURN);
                }
                break;
            default:
                break;
            }
        }

        if(!UpdateVictim())
            return;

        GETUNIT(Illidan, IllidanGUID);
        if(Illidan && HPPCT(Illidan) < 90)
        {
            EnterPhase(PHASE_TALK);
            return;
        }

        if(me->GetHealthPct() < 20)
            DoCast(me, SPELL_HEALING_POTION);

        DoMeleeAttackIfReady();
    }
};


struct boss_maievAI : public ScriptedAI
{
    boss_maievAI(Creature *c) : ScriptedAI(c) {};

    uint64 IllidanGUID;

    PhaseIllidan Phase;
    EventMaiev Event;
    uint32 Timer[5];
    uint32 MaxTimer;

    void Reset()
    override {
        MaxTimer = 0;
        Phase = PHASE_NORMAL_MAIEV;
        IllidanGUID = 0;
        Timer[EVENT_MAIEV_STEALTH] = 0;
        Timer[EVENT_MAIEV_TAUNT] = 22000 + rand()%21 * 1000;
        Timer[EVENT_MAIEV_SHADOW_STRIKE] = 30000;
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 44850);
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + 1, 0);
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + 2, 45738);
    }

    void EnterCombat(Unit *who) override {}
    void MoveInLineOfSight(Unit *who) override {}
    void EnterEvadeMode(EvadeReason /* why */) override {}
    void GetIllidanGUID(uint64 guid) { IllidanGUID = guid; }

    void DamageTaken(Unit *done_by, uint32 &damage)
    override {
        if(done_by->GetGUID() != IllidanGUID )
            damage = 0;
        else
        {
            GETUNIT(Illidan, IllidanGUID);
            if(Illidan && Illidan->GetVictim() == me)
                damage = me->GetMaxHealth()/10;
            if(damage >= me->GetHealth())
                damage = 0;
        }
    }

    void AttackStart(Unit *who)
    override {
        if(!who || Timer[EVENT_MAIEV_STEALTH])
            return;

        if(Phase == PHASE_TALK_SEQUENCE)
            ScriptedAI::AttackStart(who, false);
        else if(Phase == PHASE_DEMON || Phase == PHASE_TRANSFORM_SEQUENCE )
        {
            GETUNIT(Illidan, IllidanGUID);
            if(Illidan && me->IsWithinDistInMap(Illidan, 25))
                BlinkToPlayer();//Do not let dread aura hurt her.
            ScriptedAI::AttackStart(who, false);
        }
        else
            ScriptedAI::AttackStart(who, true);
    }

    void DoAction(const int32 param)
    override {
        if(param > PHASE_ILLIDAN_NULL && param < PHASE_ILLIDAN_MAX)
            EnterPhase(PhaseIllidan(param));
    }

    void EnterPhase(PhaseIllidan NextPhase)//This is in fact Illidan's phase.
    {
        switch(NextPhase)
        {
        case PHASE_TALK_SEQUENCE:
            if(Timer[EVENT_MAIEV_STEALTH])
            {
                me->SetHealth(me->GetMaxHealth());
                me->SetVisible(true);
                Timer[EVENT_MAIEV_STEALTH] = 0;
            }
            me->InterruptNonMeleeSpells(false);
            me->GetMotionMaster()->Clear(false);
            me->AttackStop();
            me->SetUInt64Value(UNIT_FIELD_TARGET, IllidanGUID);
            MaxTimer = 0;
            break;
        case PHASE_TRANSFORM_SEQUENCE:
            MaxTimer = 4;
            Timer[EVENT_MAIEV_TAUNT] += 10000;
            Timer[EVENT_MAIEV_THROW_DAGGER] = 2000;
            break;
        case PHASE_DEMON:
            break;
        case PHASE_NORMAL_MAIEV:
            MaxTimer = 4;
            Timer[EVENT_MAIEV_TAUNT] += 10000;
            Timer[EVENT_MAIEV_TRAP] = 22000;
            break;
        default:
            break;
        }
        if(Timer[EVENT_MAIEV_STEALTH])
            MaxTimer = 1;
        Phase = NextPhase;
    }

    void BlinkTo(float x, float y, float z)
    {
        me->AttackStop();
        me->InterruptNonMeleeSpells(false);
        me->GetMotionMaster()->Clear(false);
        DoTeleportTo(x, y, z);
        DoCast(me, SPELL_TELEPORT_VISUAL, true);
    }

    void BlinkToPlayer()
    {
        if(GETCRE(Illidan, IllidanGUID))
        {
            Unit* target = ((boss_illidan_stormrageAI*)Illidan->AI())->SelectTarget(SELECT_TARGET_RANDOM, 0);

            if(!target || !me->IsWithinDistInMap(target, 80) || Illidan->IsWithinDistInMap(target, 20))
            {
                uint8 pos = rand()%4;
                BlinkTo(HoverPosition[pos].x, HoverPosition[pos].y, HoverPosition[pos].z);
            }
            else
            {
                float x, y, z;
                target->GetPosition(x, y, z);
                BlinkTo(x, y, z);
            }
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if((!UpdateVictim())
            && !Timer[EVENT_MAIEV_STEALTH])
            return;

        Event = EVENT_MAIEV_NULL;
        for(uint8 i = 1; i <= MaxTimer; i++)
            if(Timer[i])
            {
                if(Timer[i] <= diff)
                    Event = (EventMaiev)i;
                else Timer[i] -= diff;
            }

            switch(Event)
            {
            case EVENT_MAIEV_STEALTH:
                {
                    me->SetHealth(me->GetMaxHealth());
                    me->SetVisible(true);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    Timer[EVENT_MAIEV_STEALTH] = 0;
                    BlinkToPlayer();
                    EnterPhase(Phase);
                }break;
            case EVENT_MAIEV_TAUNT:
                {
                    uint32 random = rand()%4;
                    DoScriptText(MaievTaunts[random].dbEntry,me);
                    Timer[EVENT_MAIEV_TAUNT] = 22000 + rand()%21 * 1000;
                }break;
            case EVENT_MAIEV_SHADOW_STRIKE:
                DoCast(me->GetVictim(), SPELL_SHADOW_STRIKE);
                Timer[EVENT_MAIEV_SHADOW_STRIKE] = 60000;
                break;
            case EVENT_MAIEV_TRAP:
                if(Phase == PHASE_NORMAL_MAIEV)
                {
                    BlinkToPlayer();
                    DoCast(me, SPELL_CAGE_TRAP_SUMMON);
                    Timer[EVENT_MAIEV_TRAP] = 22000;
                }
                else
                {
                    if(!me->IsWithinDistInMap(me->GetVictim(), 40))
                        me->GetMotionMaster()->MoveChase(me->GetVictim(), 30);
                    DoCast(me->GetVictim(), SPELL_THROW_DAGGER);
                    Timer[EVENT_MAIEV_THROW_DAGGER] = 2000;
                }
                break;
            default:
                break;
            }

            if(me->IsVisible() && (me->GetHealthPct() < 50))
            {
                me->SetVisible(false);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                if(GETCRE(Illidan, IllidanGUID))
                    ((boss_illidan_stormrageAI*)Illidan->AI())->DeleteFromThreatList(me->GetGUID());
                me->AttackStop();
                Timer[EVENT_MAIEV_STEALTH] = 5000; //reappear after 5s
                MaxTimer = 1;
            }

            if(Phase == PHASE_NORMAL_MAIEV)
                DoMeleeAttackIfReady();
    }
};


bool GossipSelect_npc_akama_at_illidan(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if(((npc_akama_illidanAI*)_Creature->AI())->Phase == PHASE_READY)
        ((npc_akama_illidanAI*)_Creature->AI())->EnterPhase(PHASE_WALK); //walk to illidan and start fight
    else
        ((npc_akama_illidanAI*)_Creature->AI())->EnterPhase(PHASE_CHANNEL);

    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool GossipHello_npc_akama_at_illidan(Player *player, Creature *_Creature)
{
    if(((npc_akama_illidanAI*)_Creature->AI())->Phase == PHASE_READY)
    {
        player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_START, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->SEND_GOSSIP_MENU_TEXTID(MENU_START, _Creature->GetGUID());
    } else {
        player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_INTRO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->SEND_GOSSIP_MENU_TEXTID(MENU_INTRO, _Creature->GetGUID());
    }

    return true;
}

struct cage_trap_triggerAI : public ScriptedAI
{
    cage_trap_triggerAI(Creature *c) : ScriptedAI(c) 
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }

    InstanceScript* pInstance;

    uint64 IllidanGUID;
    uint32 DespawnTimer;
    uint64 CageTrapGUID;

    bool Active;

    void Reset()
    override {
        if(pInstance)
            IllidanGUID = pInstance->GetData64(DATA_ILLIDANSTORMRAGE);
        else
            me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);

        CageTrapGUID = 0;
        Active = false;

        DespawnTimer = 0;
    }

    void EnterCombat(Unit *who)override {}

    float DegreeToRadian(float degree) { return degree / (180/3.14159265); }

    void HandleTrapActivation()
    {
        GETCRE(Illidan,IllidanGUID);
        if(Illidan && me->IsWithinDistInMap(Illidan, 3) && (!Illidan->HasAuraEffect(SPELL_CAGED, 0)))
        {
            Illidan->CastSpell(Illidan, SPELL_CAGED, true);
            DespawnTimer = 5000;
            if(Illidan->HasAuraEffect(SPELL_ENRAGE, 0))
                Illidan->RemoveAurasDueToSpell(SPELL_ENRAGE); // Dispel his enrage
            if(GameObject* CageTrap = GameObject::GetGameObject(*me, CageTrapGUID))
                CageTrap->SetLootState(GO_JUST_DEACTIVATED);

            //octogonal cage, spawn a visual and another at the the opposite x4
            float x,y,z,tX,tY;
            Illidan->GetPosition(x,y,z);
            for(uint8 i = 0; i < 8; i++) 
            {
                tX = x + cos(DegreeToRadian(45)*i) * 5;
                tY = y + sin(DegreeToRadian(45)*i) * 5;
                Unit* visual = me->SummonCreature(INVISIBLE_DUMMY,tX,tY,z+1,0,TEMPSUMMON_TIMED_DESPAWN,15000);
                if(visual)
                {
                    visual->CastSpell(Illidan,SPELL_CAGE_TRAP_BEAM,true);
                    Illidan->CastSpell(visual,SPELL_CAGE_TRAP_BEAM,true);
                }
            }
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(DespawnTimer)
        {
            if(DespawnTimer <= diff)
            {
                me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                return;
            } else DespawnTimer -= diff;
        }
        
        if(!Active)
            return;

        HandleTrapActivation();
    }
};



class CageTrap : public GameObjectScript
{
public:
    CageTrap() : GameObjectScript("gameobject_cage_trap")
    {}

    struct CageTrapAI : public GameObjectAI
    {
        CageTrapAI(GameObject* obj) : GameObjectAI(obj), pInstance(obj->GetInstanceScript()) { }

        InstanceScript* pInstance;
        
        bool GossipHello(Player* plr) override
        {
            float x, y, z;
            plr->GetPosition(x, y, z);

            Creature* trigger = nullptr;

            // Grid search for nearest live creature of entry 23304 within 10 yards
            Trinity::NearestCreatureEntryWithLiveStateInObjectRangeCheck check(*plr, 23304, true, 10.0f);
            Trinity::CreatureLastSearcher<Trinity::NearestCreatureEntryWithLiveStateInObjectRangeCheck> searcher(trigger, check);

            Cell::VisitGridObjects(plr, searcher, 20.0f);

            if (trigger)
            {
                ((cage_trap_triggerAI*)trigger->AI())->Active = true;
                ((cage_trap_triggerAI*)trigger->AI())->CageTrapGUID = me->GetGUID();
            }
            me->UseDoorOrButton();
            me->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new CageTrapAI(go);
    }
};

struct shadow_demonAI : public ScriptedAI
{
    shadow_demonAI(Creature *c) : ScriptedAI(c) 
    {
        DoZoneInCombat();
    }

    uint64 TargetGUID;

    void EnterCombat(Unit *who) override {DoZoneInCombat();}

    void Reset()
    override {
        TargetGUID = 0;
        me->CastSpell(me, SPELL_SHADOW_DEMON_PASSIVE, true);
        SelectRandomTarget();
    }

    void JustDied(Unit *killer)
    override {
        if(Unit* target = ObjectAccessor::GetUnit((*me), TargetGUID))
            target->RemoveAurasDueToSpell(SPELL_PARALYZE);
    }

    void SelectRandomTarget()
    {
        if(Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 999, true)) // only on players.
        {
            me->AddThreat(target, 5000000.0f);
            me->AI()->AttackStart(target);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim()) return;

        if(!me->GetVictim()->HasAuraEffect(SPELL_PARALYZE, 0))
        {
            TargetGUID = me->GetVictim()->GetGUID();
            DoCast(me->GetVictim(), SPELL_PURPLE_BEAM, true);
            DoCast(me->GetVictim(), SPELL_PARALYZE, true);
        }

        // Kill our target if we're very close.
        if(me->IsWithinDistInMap(me->GetVictim(), 3))
        {
            DoCast(me->GetVictim(), SPELL_CONSUME_SOUL);
            SelectRandomTarget();
        }
    }
};

// Shadowfiends interact with Illidan, setting more targets in Illidan's hashmap
struct mob_parasitic_shadowfiendAI : public ScriptedAI
{
    mob_parasitic_shadowfiendAI(Creature* c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }

    InstanceScript* pInstance;
    uint64 IllidanGUID;
    uint32 CheckTimer;

    void Reset()
    override {
        if(pInstance)
            IllidanGUID = pInstance->GetData64(DATA_ILLIDANSTORMRAGE);
        else
            IllidanGUID = 0;

        CheckTimer = 5000;
        DoCast(me, SPELL_SHADOWFIEND_PASSIVE, true);
    }

    void EnterCombat(Unit* who) override { DoZoneInCombat(); }

    void DoMeleeAttackIfReady() override
    {
        if( me->IsAttackReady() && me->IsWithinMeleeRange(me->GetVictim()))
        {
            if(!me->GetVictim()->HasAuraEffect(SPELL_PARASITIC_SHADOWFIEND, 0)
                && !me->GetVictim()->HasAuraEffect(SPELL_PARASITIC_SHADOWFIEND2, 0))
            {
                me->CastSpell(me->GetVictim(), SPELL_PARASITIC_SHADOWFIEND2, true, nullptr, nullptr, IllidanGUID); //do not stack
            }
            me->AttackerStateUpdate(me->GetVictim());
            me->ResetAttackTimer();
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!me->GetVictim())
        {
            if(Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 999, true))
                AttackStart(target);
            else
            {
                me->SetVisible(false);
                me->SetDeathState(JUST_DIED);
                return;
            }
        }

        if(CheckTimer < diff)
        {
            GETUNIT(Illidan, IllidanGUID);
            if(!Illidan || (Illidan->ToCreature())->IsInEvadeMode())
            {
                me->SetVisible(false);
                me->SetDeathState(JUST_DIED);
                return;
            }else CheckTimer = 5000;
        }else CheckTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct blade_of_azzinothAI : public NullCreatureAI
{
    blade_of_azzinothAI(Creature* c) : NullCreatureAI(c) {}

    void SpellHit(Unit *caster, const SpellInfo *spell)
    override {
        if(spell->Id == SPELL_THROW_GLAIVE2 || spell->Id == SPELL_THROW_GLAIVE)
            me->SetUInt32Value(UNIT_FIELD_DISPLAYID, 21431);//appear when hit by Illidan's glaive
    }
};

void boss_illidan_stormrageAI::Reset()
{
    if(pInstance)
        pInstance->SetData(DATA_ILLIDANSTORMRAGEEVENT, NOT_STARTED);

    if(AkamaGUID)
    {
        if(GETCRE(Akama, AkamaGUID))
        {
            if(!Akama->IsAlive())
                Akama->Respawn();
            else
            {
                ((npc_akama_illidanAI*)Akama->AI())->EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
                Akama->GetMotionMaster()->MoveTargetedHome();
                ((npc_akama_illidanAI*)Akama->AI())->Reset();
            }
        }
        AkamaGUID = 0;
    }

    MaievGUID = 0;
    for(int i = 0; i < 2; ++i)
    {
        FlameGUID[i] = 0;
        GlaiveGUID[i] = 0;
    }

    Phase = PHASE_ILLIDAN_NULL;
    Event = EVENT_NULL;
    Timer[EVENT_BERSERK] = 1500000;

    HoverPoint = 0;
    TalkCount = 0;
    FlightCount = 0;
    TransformCount = 0;

    me->SetUInt32Value(UNIT_FIELD_DISPLAYID, 21135);
    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 0);
    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
    me->SetDisableGravity(false);
    me->SetStandState(UNIT_STAND_STATE_KNEEL);
    me->SetKeepActive(false);
    Summons.DespawnAll();
}

void boss_illidan_stormrageAI::JustSummoned(Creature* summon)
{
    Summons.Summon(summon);
    switch(summon->GetEntry())
    {
    case PARASITIC_SHADOWFIEND:
        {
            if(Phase == PHASE_TALK_SEQUENCE)
            {
                summon->SetVisible(false);
                summon->SetDeathState(JUST_DIED);
                return;
            }
            Unit *target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 999, true);
            if(!target || target->HasAuraEffect(SPELL_PARASITIC_SHADOWFIEND, 0)
                || target->HasAuraEffect(SPELL_PARASITIC_SHADOWFIEND2, 0))
                target = SelectTarget(SELECT_TARGET_RANDOM, 0, 999, true);
            if(target)
                summon->AI()->AttackStart(target);
        }break;
    case MAIEV_SHADOWSONG:
        {
            summon->SetVisible(false); // Leave her invisible until she has to talk
            summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            MaievGUID = summon->GetGUID();
            ((boss_maievAI*)summon->AI())->GetIllidanGUID(me->GetGUID());
            summon->AI()->DoAction(PHASE_TALK_SEQUENCE);
        }break;
    case FLAME_OF_AZZINOTH:
        {
            summon->AI()->AttackStart(summon->SelectNearestTarget(999));
        }break;
    default:
        break;
    }
}

void boss_illidan_stormrageAI::HandleTalkSequence()
{
    switch(TalkCount)
    {
    case 0:
        me->SetStandState(UNIT_STAND_STATE_STAND); //kneel up
        break;
    case 1:
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        break;
    case 9:
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 45479); // Equip our warglaives!
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 45481);
        me->SetSheath(SHEATH_STATE_MELEE);
        me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
        break;
    case 10:
        if(GETCRE(Akama, AkamaGUID))
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE + UNIT_FLAG_NOT_SELECTABLE);
            DoResetThreat();
            me->AddThreat(Akama, -9999999.0f);
            ((npc_akama_illidanAI*)Akama->AI())->EnterPhase(PHASE_FIGHT_ILLIDAN);
            EnterPhase(PHASE_NORMAL);
        }
        break;
    case 11:
        SummonMaiev();
        break;
    case 12:
        if(GETUNIT(Maiev, MaievGUID))
        {
            Maiev->SetVisible(true); // Maiev is now visible
            Maiev->CastSpell(Maiev, SPELL_TELEPORT_VISUAL, true); // onoz she looks like she teleported!
            Maiev->SetInFront(me); // Have her face us
            me->SetInFront(Maiev); // Face her, so it's not rude =P
            Maiev->GetMotionMaster()->MoveIdle();
            me->GetMotionMaster()->MoveIdle();
        }break;
    case 15:
        if(GETCRE(Maiev, MaievGUID))
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE + UNIT_FLAG_NOT_SELECTABLE);
            Maiev->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE + UNIT_FLAG_NOT_SELECTABLE);
            Maiev->AddThreat(me, 10000000.0f); // Have Maiev add a lot of threat on us so that players don't pull her off if they damage her via AOE
            Maiev->AI()->AttackStart(me); // Force Maiev to attack us.
            me->AddThreat(Maiev, -9999999.0f); //do not allow her to tank
            EnterPhase(PHASE_NORMAL_MAIEV);
        }break;
    case 16:
        DoCast(me, SPELL_DEATH); // Animate his kneeling + stun him
        Summons.DespawnAll();
        break;
    case 18:
        if(GETUNIT(Akama, AkamaGUID))
        {
            if(!me->IsWithinDistInMap(Akama, 15))
            {
                float x, y, z;
                me->GetPosition(x, y, z);
                x += 10; y += 10;
                Akama->GetMotionMaster()->Clear(false);
                //Akama->GetMotionMaster()->MoveIdle();
                Akama->Relocate(x, y, z);
                Akama->MonsterMoveWithSpeed(x, y, z, 0); //Illidan must not die until Akama arrives.
                Akama->GetMotionMaster()->MoveChase(me);
            }
        }
        break;
    case 20: // Make Maiev leave
        if(GETUNIT(Maiev, MaievGUID))
        {
            Maiev->CastSpell(Maiev, SPELL_TELEPORT_VISUAL, true);
            Maiev->SetDeathState(JUST_DIED);
            me->SetUInt32Value(UNIT_FIELD_BYTES_1,PLAYER_STATE_DEAD);
        }
        break;
    case 22: // Kill ourself.
        me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
        break;
    default:
        break;
    }
    if(Phase == PHASE_TALK_SEQUENCE)
        Talk(TalkCount); // This function does most of the talking
    TalkCount++;
}


bool boss_illidan_stormrageAI::CastEyeBlast()
{
    me->InterruptNonMeleeSpells(false);

    // spawn trigger at closer eyeBlast point
    float distx, disty, dist[2];
    for(uint8 i = 0; i < 2; ++i)
    {
        distx = EyeBlast[i].x - HoverPosition[HoverPoint].x;
        disty = EyeBlast[i].y - HoverPosition[HoverPoint].y;
        dist[i] = distx * distx + disty * disty;
    }
    Locations initial = EyeBlast[dist[0] < dist[1] ? 0 : 1];

    // move trigger to closer glaive position
    for(uint8 i = 0; i < 2; ++i)
    {
        distx = GlaivePosition[i].x - HoverPosition[HoverPoint].x;
        disty = GlaivePosition[i].y - HoverPosition[HoverPoint].y;
        dist[i] = distx * distx + disty * disty;
    }
    Locations final = GlaivePosition[dist[0] < dist[1] ? 0 : 1];

    final.x = 2 * final.x - initial.x;
    final.y = 2 * final.y - initial.y;

    Creature* Trigger = me->SummonCreature(DEMON_FIRE, initial.x, initial.y, initial.z, 0, TEMPSUMMON_TIMED_DESPAWN, 13000);
    if(!Trigger) return false;

    Trigger->SetSpeedRate(MOVE_WALK, 3);
    Trigger->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
    Trigger->GetMotionMaster()->MovePoint(0, final.x, final.y, final.z);

    //Trigger->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    me->SetUInt64Value(UNIT_FIELD_TARGET, Trigger->GetGUID());
    //SPELL_DEMON_FIRE is cast via creature_template
    if(DoCast(Trigger, SPELL_EYE_BLAST) == SPELL_CAST_OK)
    {
        DoScriptText(SAY_EYE_BLAST,me);
        return true;
    }

    return false;
}

void boss_illidan_stormrageAI::SummonFlamesOfAzzinoth()
{
    DoScriptText(SAY_SUMMONFLAMES,me);

    for(uint8 i = 0; i < 2; ++i)
    {
        if(GETUNIT(Glaive, GlaiveGUID[i]))
        {
            Creature* Flame = me->SummonCreature(FLAME_OF_AZZINOTH, GlaivePosition[i+2].x, GlaivePosition[i+2].y, GlaivePosition[i+2].z, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000);
            if(Flame)
            {
                Flame->SetFaction(me->GetFaction()); // Just in case the database has it as a different faction
                Flame->SetMeleeDamageSchool(SPELL_SCHOOL_FIRE);
                FlameGUID[i] = Flame->GetGUID(); // Record GUID in order to check if they're dead later on to move to the next phase
                ((flame_of_azzinothAI*)Flame->AI())->SetGlaiveGUID(GlaiveGUID[i]);
                Glaive->CastSpell(Flame, SPELL_AZZINOTH_CHANNEL, false); // Glaives do some random Beam type channel on it.
            }
        }
    }
}

void boss_illidan_stormrageAI::SummonMaiev()
{
    me->CastSpell(me, SPELL_SHADOW_PRISON, true);
    me->CastSpell(me, 40403, true);
    if(!MaievGUID) // If Maiev cannot be summoned, reset the encounter and post some errors to the console.
    {
        EnterEvadeMode();
        me->TextEmote("is unable to summon Maiev Shadowsong and enter Phase 4. Resetting Encounter.", nullptr);
        error_log("SD2 ERROR: Unable to summon Maiev Shadowsong (entry: 23197). Check your database to see if you have the proper SQL for Maiev Shadowsong (entry: 23197)");
    }
}


void boss_illidan_stormrageAI::EnterPhase(PhaseIllidan NextPhase)
{
    switch(NextPhase)
    {
    case PHASE_NORMAL:
    case PHASE_NORMAL_2:
    case PHASE_NORMAL_MAIEV:
        DoZoneInCombat();
        AttackStart(me->GetVictim());
        Timer[EVENT_TAUNT] = 32000;
        Timer[EVENT_SHEAR] = 10000 + rand()%15 * 1000;
        Timer[EVENT_FLAME_CRASH] = 20000;
        Timer[EVENT_PARASITIC_SHADOWFIEND] = 25000;
        Timer[EVENT_PARASITE_CHECK] = 0;
        Timer[EVENT_DRAW_SOUL] = 30000;
        if(NextPhase == PHASE_NORMAL)
            break;
        Timer[EVENT_AGONIZING_FLAMES] = 35000;
        Timer[EVENT_TRANSFORM_NORMAL] = 60000;
        if(NextPhase == PHASE_NORMAL_2)
            break;
        Timer[EVENT_ENRAGE] = 30000 + rand()%10 * 1000;
        break;
    case PHASE_FLIGHT:
        Timer[EVENT_FIREBALL] = 1000;
        if(!(rand()%4))
            Timer[EVENT_DARK_BARRAGE] = 10000;
        Timer[EVENT_EYE_BLAST] = 10000 + rand()%15 * 1000;
        Timer[EVENT_MOVE_POINT] = 20000 + rand()%20 * 1000;
        break;
    case PHASE_DEMON:
        Timer[EVENT_SHADOW_BLAST] = 1000;
        Timer[EVENT_FLAME_BURST] = 10000;
        Timer[EVENT_SHADOWDEMON] = 30000;
        Timer[EVENT_TRANSFORM_DEMON] = 60000;
        AttackStart(me->GetVictim());
        break;
    case PHASE_TALK_SEQUENCE:
        Timer[EVENT_TALK_SEQUENCE] = 100;
        me->RemoveAllAuras();
        me->InterruptNonMeleeSpells(false);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE + UNIT_FLAG_NOT_SELECTABLE);
        me->GetMotionMaster()->Clear(false);
        me->AttackStop();
        me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
        break;
    case PHASE_FLIGHT_SEQUENCE:
        if(Phase == PHASE_NORMAL) //lift off
        {
            FlightCount = 1;
            Timer[EVENT_FLIGHT_SEQUENCE] = 1;
            me->RemoveAllAuras();
            me->InterruptNonMeleeSpells(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->GetMotionMaster()->Clear(false);
            me->AttackStop();
        }
        else //land
            Timer[EVENT_FLIGHT_SEQUENCE] = 2000;
        break;
    case PHASE_TRANSFORM_SEQUENCE:
        if(Phase == PHASE_DEMON)
            Timer[EVENT_TRANSFORM_SEQUENCE] = 500;
        else
        {
            TransformCount = 0;
            Timer[EVENT_TRANSFORM_SEQUENCE] = 500;
            DoScriptText(SAY_MORPH,me);
        }
        me->GetMotionMaster()->Clear();
        me->AttackStop();
        break;
    default:
        break;
    }
    if(MaievGUID)
    {
        GETCRE(Maiev, MaievGUID);
        if(Maiev && Maiev->IsAlive())
            Maiev->AI()->DoAction(NextPhase);
    }
    Phase = NextPhase;
    Event = EVENT_NULL;
}

CreatureAI* GetAI_boss_illidan_stormrage(Creature *_Creature)
{
    return new boss_illidan_stormrageAI (_Creature);
}

CreatureAI* GetAI_npc_akama_at_illidan(Creature *_Creature)
{
    return new npc_akama_illidanAI(_Creature);
}

CreatureAI* GetAI_boss_maiev(Creature *_Creature)
{
    return new boss_maievAI (_Creature);
}

CreatureAI* GetAI_mob_flame_of_azzinoth(Creature *_Creature)
{
    return new flame_of_azzinothAI (_Creature);
}

CreatureAI* GetAI_cage_trap_trigger(Creature *_Creature)
{
    return new cage_trap_triggerAI (_Creature);
}

CreatureAI* GetAI_shadow_demon(Creature *_Creature)
{
    return new shadow_demonAI (_Creature);
}

CreatureAI* GetAI_blade_of_azzinoth(Creature *_Creature)
{
    return new blade_of_azzinothAI (_Creature);
}

CreatureAI* GetAI_parasitic_shadowfiend(Creature *_Creature)
{
    return new mob_parasitic_shadowfiendAI (_Creature);
}

void AddSC_boss_illidan()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name = "boss_illidan_stormrage";
    newscript->GetAI = &GetAI_boss_illidan_stormrage;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_akama_illidan";
    newscript->GetAI = &GetAI_npc_akama_at_illidan;
    newscript->OnGossipHello = &GossipHello_npc_akama_at_illidan;
    newscript->OnGossipSelect = &GossipSelect_npc_akama_at_illidan;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "boss_maiev_shadowsong";
    newscript->GetAI = &GetAI_boss_maiev;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "mob_flame_of_azzinoth";
    newscript->GetAI = &GetAI_mob_flame_of_azzinoth;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "mob_blade_of_azzinoth";
    newscript->GetAI = &GetAI_blade_of_azzinoth;
    sScriptMgr->RegisterOLDScript(newscript);

    new CageTrap();

    newscript = new OLDScript;
    newscript->Name="mob_cage_trap_trigger";
    newscript->GetAI = &GetAI_cage_trap_trigger;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "mob_shadow_demon";
    newscript->GetAI = &GetAI_shadow_demon;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "mob_parasitic_shadowfiend";
    newscript->GetAI = &GetAI_parasitic_shadowfiend;
    sScriptMgr->RegisterOLDScript(newscript);
}

