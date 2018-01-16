// Some fixes to do, converstion from CreatureAINew is not yet finished. See FIXME's
//Dialogs have been disabled with removal of DialogueHelper class, dialogs must be reimplemented. All dialogs are still in creature_text table, ids are in comments in this scripts

#include "def_sunwell_plateau.h"

enum SpellIds
{
    /* Hand of the Deceiver's spells and cosmetics */
    SPELL_SHADOW_BOLT_VOLLEY                            = 45770, // ~30 yard range Shadow Bolt Volley for ~2k(?) damage
    SPELL_SHADOW_INFUSION                               = 45772, // They gain this at 20% - Immunity to Stun/Silence and makes them look angry!
    SPELL_FELFIRE_PORTAL                                = 46875, // Creates a portal that spawns Felfire Fiends (LIVE FOR THE SWARM!1 FOR THE OVERMIND!)
    SPELL_SHADOW_CHANNELING                             = 46757, // Channeling animation out of combat
    /* Felfire Portal */
    SPELL_SUMMON_FELFIRE_FIEND                          = 46464,
    
    /* Volatile Felfire Fiend's spells */
    SPELL_FELFIRE_FISSION                               = 45779, // Felfire Fiends explode when they die or get close to target.

    /* Kil'Jaeden's spells and cosmetics */
    SPELL_TRANS                                         = 23188, // Surprisingly, this seems to be the right spell.. (Where is it used?)
    SPELL_REBIRTH                                       = 44200, // Emerge from the Sunwell
    SPELL_SOUL_FLAY                                     = 45442, // 9k Shadow damage over 3 seconds. Spammed throughout all the fight.
    SPELL_LEGION_LIGHTNING                              = 45664, // Chain Lightning, 4 targets, ~3k Shadow damage, 1.5k mana burn
    SPELL_FIRE_BLOOM                                    = 45641, // Places a debuff on 5 raid members, which causes them to deal 2k Fire damage to nearby allies and selves. MIGHT NOT WORK


    SPELL_SINISTER_REFLECTION                           = 45892,
    SPELL_SINISTER_REFLECTION_CLONE                     = 45785, // Summon shadow copies of 5 raid members that fight against KJ's enemies
    SPELL_SINISTER_REFLECTION_CLASS                     = 45893, // Increase the size of the clones

    SPELL_SHADOW_SPIKE                                  = 46680, // Bombard random raid members with Shadow Spikes (Very similar to Void Reaver orbs)
    SPELL_FLAME_DART                                    = 45737, // Bombards the raid with flames every 3(?) seconds
    SPELL_DARKNESS_OF_A_THOUSAND_SOULS                  = 46605, // Begins a 8-second channeling, after which he will deal 50'000 damage to the raid
    SPELL_DARKNESS_OF_A_THOUSAND_SOULS_DAMAGE           = 45657, // effective damage spell (already triggered by SPELL_DARKNESS_OF_A_THOUSAND_SOULS)

    /* Armageddon spells wrong visual */
    SPELL_ARMAGEDDON_TRIGGER                            = 45909, // Meteor spell trigger missile should cast creature on himself
    SPELL_ARMAGEDDON_VISUAL                             = 45911, // Does the hellfire visual to indicate where the meteor missle lands
    SPELL_ARMAGEDDON_VISUAL2                            = 45914, // Does the light visual to indicate where the meteor missle lands
    SPELL_ARMAGEDDON_VISUAL3                            = 24207, // This shouldn't correct but same as seen on the movie
    SPELL_ARMAGEDDON_PERIODIC_SUMMON                    = 45921, // Summon trigger on target that cast the other spells on himself
    SPELL_ARMAGEDDON_SUMMON_TRIGGER                     = 45910, // actually summon trigger 25735
    SPELL_ARMAGEDDON_DAMAGE                             = 45915, // This does the area damage

    /* Shield Orb Spells*/
    SPELL_SHADOW_BOLT                                   = 45680, //45679 would be correct but triggers to often //TODO fix console error


    /* Anveena's spells and cosmetics (Or, generally, everything that has "Anveena" in name) */
    SPELL_ANVEENA_PRISON                                = 46367, // She hovers locked within a bubble
    SPELL_ANVEENA_ENERGY_DRAIN                          = 46410, // Sunwell energy glow animation (Control mob uses this)
    SPELL_SACRIFICE_OF_ANVEENA                          = 46474, // This is cast on Kil'Jaeden when Anveena sacrifices herself into the Sunwell

    /* Sinister Reflection Spells */
    SPELL_SR_CURSE_OF_AGONY                             = 46190,
    SPELL_SR_SHADOW_BOLT                                = 47076,

    SPELL_SR_EARTH_SHOCK                                = 47071,

    SPELL_SR_FIREBALL                                   = 47074,

    SPELL_SR_HEMORRHAGE                                 = 45897,

    SPELL_SR_HOLY_SHOCK                                 = 38921,
    SPELL_SR_HAMMER_OF_JUSTICE                          = 37369,

    SPELL_SR_HOLY_SMITE                                 = 47077,
    SPELL_SR_RENEW                                      = 47079,

    SPELL_SR_SHOOT                                      = 16496,
    SPELL_SR_MULTI_SHOT                                 = 48098,
    SPELL_SR_WING_CLIP                                  = 40652,

    SPELL_SR_WHIRLWIND                                  = 17207,

    SPELL_SR_MOONFIRE                                   = 47072,

    /*** Other Spells (used by players, etc) ***/
    SPELL_VENGEANCE_OF_THE_BLUE_FLIGHT                  = 45839, // Possess the blue dragon from the orb to help the raid.
    SPELL_POWER_OF_THE_BLUE_FLIGHT                      = 45833,
    SPELL_POSSESS_DRAKE_IMMUNE                          = 45838, // immunity while the player possesses the dragon
    SPELL_RING_OF_BLUE_FLAMES                           = 45825, // Cast this spell when the go is activated
    SPELL_DESTROY_DRAKES                                = 46707,
    SPELL_VISUAL_MOONFIRE                               = 45821, // uppon orb activation
    SPELL_KNOCK_BACK                                    = 45800, // custom spell, no damage

    // outro
    SPELL_TELEPORT_VISUAL                               = 41232,
    SPELL_KALEC_TELEPORT                                = 46473, // teleports and transforms Kalec in human form
    SPELL_CALL_ENTROPIUS                                = 46818, // pulling effect
    SPELL_ENTROPIUS_BODY                                = 46819, // Visual for Entropius at the Epilogue
    SPELL_BLAZE_TO_LIGHT                                = 46821,
    SPELL_SUNWELL_IGNITION                              = 46822, // same visual as SPELL_ANVEENA_ENERGY_DRAIN
    SPELL_OPEN_PORTAL                                   = 46801,
    SPELL_PORTAL_VISUAL                                 = 42047,

};

enum boss_kiljaedenAI_Messages
{
    MESSAGE_SET_PHASE,
};

/*** GameObjects ***/
#define GAMEOBJECT_ORB_OF_THE_BLUE_DRAGONFLIGHT 188415

/*** Others ***/
#define FLOOR_Z 28.050388
#define SHIELD_ORB_Z 45.000
#define CREATURE_INVISIBLE_DUMMY 9
#define GOSSIP_KALEC_END 25319
#define DISPLAYID_PORTAL_OPENING 22742

enum Phase
{
    PHASE_DECEIVERS     = 1, // Fight 3 adds
    PHASE_NORMAL        = 2, // Kil'Jaeden emerges from the sunwell
    PHASE_DARKNESS      = 3, // At 85%, he gains few abilities; Kalecgos joins the fight
    PHASE_ARMAGEDDON    = 4, // At 55%, he gains even more abilities
    PHASE_SACRIFICE     = 5, // At 25%, Anveena sacrifices herself into the Sunwell; at this point he becomes enraged and has *significally* shorter cooldowns.
};

//Events
enum KilJaedenEvents
{
    EVENT_KALEC_JOIN            = 1,

    //Phase 2
    EVENT_SOUL_FLAY             ,
    EVENT_LEGION_LIGHTNING      ,
    EVENT_FIRE_BLOOM            ,
    EVENT_SUMMON_SHILEDORB      ,

    //Phase 3
    EVENT_SHADOW_SPIKE          ,
    EVENT_FLAME_DART            ,
    EVENT_DARKNESS              ,
    EVENT_ORBS_EMPOWER          ,
    EVENT_SINISTER_REFLECTION   ,

    //Phase 4
    EVENT_ARMAGEDDON            ,
};

enum KilJaedenControllerEvents
{
    EVENT_SAY                   = 1
};

enum HandOfTheDeceiverEvents
{
    EVENT_SHADOWBOLT            = 1,
    EVENT_FELFIRE               = 2
};

enum FelfirePortal
{
    EVENT_SPAWNFIEND            = 1
};

enum FelfireFiend
{
    EVENT_STUN                  = 1,
    EVENT_EXPLODE               ,
    EVENT_DIE_F                 ,
};

enum Armageddontarget
{
    EVENT_VISUAL1               = 1,
    EVENT_TRIGGER               ,
    EVENT_DIE                   ,
};

enum ShieldOrb
{
    EVENT_SHADOWBOLT_S          = 1
};

// Locations of the Hand of Deceiver adds
float DeceiverLocations[3][3]=
{
    {1687.777f, 638.084f, 5.527f},
    {1684.099f, 618.848f, 0.589f},
    {1704.398f, 612.848f, 1.884f},
};

// Locations, where Shield Orbs will spawn
float ShieldOrbLocations[4][2]=
{
    {1698.900f, 627.870f},       //middle pont of Sunwell
    {12.0f, 3.14f},              // First one spawns northeast of KJ
    {12.0f, 3.14f/0.7f},         // Second one spawns southeast
    {12.0f, 3.14f*3.8f}          // Third one spawns (?)
};

/* Unused, what was that for ?
float OrbLocations[4][5] =
{
    (1694.48f, 674.29f,  28.0502f, 4.86985f),
    (1745.68f, 621.823f, 28.0505f, 2.93777f),
    (1704.14f, 583.591f, 28.1696f, 1.59003f),
    (1653.12f, 635.41f,  28.0932f, 0.0977725f),
};
 */

float KJLocation[4] = { 1698.930f, 628.264f, 28.400f, 3.7f };

struct Speech
{
    int32 textid;
    uint32 creature, timer;
};

enum Controller
{
    SAY_KJ_OFFCOMBAT = 0,
};

enum KilJaeden
{
    SAY_KJ_DEATH = 0,
    SAY_KJ_SLAY = 1,
    SAY_KJ_REFLECTION = 2,
    SAY_KJ_EMERGE = 3,
    SAY_KJ_DARKNESS = 4,
    SAY_KJ_PHASE3 = 5,
    SAY_KJ_PHASE4 = 6,
    SAY_KJ_PHASE5 = 7,
    EMOTE_KJ_DARKNESS = 8,
};

enum Kalecgos
{
    SAY_KALECGOS_ENCOURAGE = 0,
    SAY_KALEC_ORB_READY1 = 1,
    SAY_KALEC_ORB_READY2 = 2,
    SAY_KALEC_ORB_READY3 = 3,
    SAY_KALEC_ORB_READY4 = 4,
    /*SAY_KALECGOS_AWAKEN = 5,
    SAY_KALECGOS_LETGO = 6,
    SAY_KALECGOS_FOCUS = 7,
    SAY_KALECGOS_FATE = 8,
    SAY_KALECGOS_GOODBYE = 9, */
    SAY_KALEC_JOIN = 10,
    SAY_KALEC_1    = -1580082,
    SAY_KALEC_2    = -1580084,
    SAY_KALEC_3    = -1580086,
    SAY_KALEC_4    = -1580088,
    SAY_KALEC_5    = -1580098,
    SAY_KALEC_6    = -1580091,

};

enum Anveena
{
    SAY_ANVEENA_1  = -1580083,
    SAY_ANVEENA_2  = -1580085,
    SAY_ANVEENA_3  = -1580087,
    SAY_ANVEENA_4  = -1580089,
};

// outro
enum Outro
{
    SAY_KALECGOS_GOODBYE        = -1580090,
    SAY_OUTRO_1                 = -1580099,
    SAY_OUTRO_2                 = -1580100,
    SAY_OUTRO_3                 = -1580111,
    SAY_OUTRO_4                 = -1580101,
    SAY_OUTRO_5                 = -1580107,
    SAY_OUTRO_6                 = -1580102,
    SAY_OUTRO_7                 = -1580108,
    SAY_OUTRO_8                 = -1580103,
    SAY_OUTRO_9                 = -1580104,
    SAY_OUTRO_10                = -1580109,
    SAY_OUTRO_11                = -1580105,
    SAY_OUTRO_12                = -1580106,
};

enum
{
    POINT_KILJAEDEN_DIE = 1,
    POINT_TELEPORT_KALECGOS,
    POINT_SUMMON_SHATTERED,
    POINT_SUMMON_PORTAL,
    POINT_SUMMON_PORTAL_ENDOPENANIM,
    POINT_SUMMON_SOLDIERS_RIGHT,
    POINT_SUMMON_SOLDIERS_LEFT,
    POINT_SUMMON_PROPHET,
    POINT_SUMMON_LIADRIN,
    POINT_CALL_ENTROPIUS,
    POINT_MOVE_LIADRIN,
    POINT_BLAZE,
    POINT_IGNITE,
    POINT_EVENT_SOLDIER_EXIT,
    POINT_EVENT_VELEN_EXIT,
    POINT_END_STUN,
};

/*
static const  uint32  firstDialogue[][] =
{
    {SAY_KALEC_1,                 CREATURE_KALECGOS,  5000},
    {SAY_ANVEENA_1,               CREATURE_ANVEENA,   3000},
    {0,                           0,                  0},
};

static const  uint32  secondDialogue[][] =
{
    {SAY_KALEC_2,                 CREATURE_KALECGOS,  7000},
    {SAY_ANVEENA_2,               CREATURE_ANVEENA,   5000},
    {0,                           0,                  0},
};

static const uint32*  thirdDialogue[] =
{
    {SAY_KALEC_3,                 CREATURE_KALECGOS,  10000},//Anveena, I love you! Focus on my voice, come back for me now! Only you can cleanse the Sunwell!
    {SAY_ANVEENA_3,               CREATURE_ANVEENA,   2000}, //Kalec... Kalec?
    {SAY_KALEC_4,                 CREATURE_KALECGOS,  8000}, //Yes, Anveena! Let fate embrace you now!
    {SAY_ANVEENA_4,               CREATURE_ANVEENA,   6000}, //The nightmare is over, the spell is broken! Goodbye, Kalec, my love!
    {SAY_KJ_PHASE5,               CREATURE_KILJAEDEN, 12000},//WATAVIOUDONE ?
    {SAY_KALEC_5,                 CREATURE_KALECGOS,  5000}, //I have channeled all I can! The power is in your hands!
    {SAY_KALEC_6,                 CREATURE_KALECGOS,  5000}, //Strike now, heroes, while he is weakened! Vanquish the Deceiver!
    {0,                           0,                  0},
};

// Epilogue dialogue
static const uint32  aOutroDialogue[][] =
{
    {POINT_KILJAEDEN_DIE,         0,                  15000},
    {POINT_TELEPORT_KALECGOS,     0,                  2000},
    {SAY_KALECGOS_GOODBYE,        CREATURE_KALECGOS,  15000},
    {POINT_SUMMON_SHATTERED,      0,                  15000},
    {POINT_SUMMON_PORTAL,         0,                  500},
    {POINT_SUMMON_PORTAL_ENDOPENANIM, 0,              3500},
    {POINT_SUMMON_SOLDIERS_RIGHT, 0,                  8000},
    {POINT_SUMMON_SOLDIERS_LEFT,  0,                  10000},
    {POINT_SUMMON_PROPHET,        0,                  2000},
    {POINT_SUMMON_LIADRIN,        0,                  4000},
    {SAY_OUTRO_1,                 CREATURE_PROPHET,   25000},
    {SAY_OUTRO_2,                 CREATURE_PROPHET,   14000},
    {SAY_OUTRO_3,                 CREATURE_PROPHET,   10000},
    {POINT_CALL_ENTROPIUS,        0,                  10000},
    {SAY_OUTRO_4,                 CREATURE_PROPHET,   22000},
    {POINT_MOVE_LIADRIN,          0,                  6000},
    {SAY_OUTRO_5,                 CREATURE_LIADRIN,   10000},
    {SAY_OUTRO_6,                 CREATURE_PROPHET,   15000},
    {SAY_OUTRO_7,                 CREATURE_LIADRIN,   2500},
    {SAY_OUTRO_8,                 CREATURE_PROPHET,   4000},
    {POINT_BLAZE,                 0,                  10000},
    {POINT_IGNITE,                0,                  500},
    {SAY_OUTRO_9,                 CREATURE_PROPHET,   15000},
    {SAY_OUTRO_10,                CREATURE_LIADRIN,   20000},
    {SAY_OUTRO_11,                CREATURE_PROPHET,   6000},
    {SAY_OUTRO_12,                CREATURE_PROPHET,   2000},
    {POINT_EVENT_SOLDIER_EXIT,    0,                  8000},
    {POINT_EVENT_VELEN_EXIT,      0,                  0},
    {0,                           0,                  0},
};
*/

struct EventLocations
{
    float m_fX, m_fY, m_fZ, m_fO;
};

static const EventLocations aOutroLocations[] =
{
    {1728.337f, 656.641f, 28.55f, 3.86f},       // portal summon loc
    {1703.159f, 654.043f, 28.05f, 1.06f},       // first shattered summon loc
    {1723.888f, 631.342f, 28.05f, 0.16f},       // second shattered summon loc
    {1716.969f, 646.407f, 28.05f, 3.91f},       // velen summon loc
    {1718.862f, 644.528f, 28.05f, 3.87f},       // liadrin summon loc
    {1709.719f, 639.359f, 27.28f},              // velen move forward
    {1711.537f, 637.600f, 27.34f},              // liadrin move forward
    {1716.962f, 661.839f, 28.05f},              // first shattered move
    {1735.141f, 643.680f, 28.23f},              // second shattered move
    {1723.220f, 663.026f, 30.00f},              // first shattered spell target
    {1734.877f, 649.574f, 30.00f},              // second shattered spell target
};

static const EventLocations SoldierLocations[] =
{
    {1722.709f, 640.308f, 28.05f, 3.774f}, // summon first
    {1727.329f, 639.419f, 28.05f, 3.721f}, // summon first
    {1724.606f, 645.376f, 28.05f, 3.755f}, // summon first
    {1719.543f, 644.635f, 28.05f, 3.718f}, // summon first
    {1720.937f, 649.376f, 28.05f, 3.859f}, // summon first
    {1715.420f, 648.200f, 28.05f, 4.507f}, // summon first
    {1715.948f, 653.606f, 28.05f, 3.892f}, // summon first
    {1710.871f, 651.645f, 28.05f, 4.252f}, // summon first
    {1709.924f, 656.442f, 28.05f, 4.035f}, // summon first
    {1705.944f, 654.201f, 28.05f, 4.290f}, // summon first
    {1707.783f, 653.139f, 28.05f, 4.375f}, // summon second
    {1712.047f, 655.015f, 28.05f, 4.208f}, // summon second
    {1712.432f, 650.853f, 28.05f, 4.166f}, // summon second
    {1717.019f, 652.191f, 28.05f, 3.986f}, // summon second
    {1716.611f, 647.399f, 28.05f, 4.060f}, // summon second
    {1721.737f, 648.310f, 28.05f, 3.893f}, // summon second
    {1720.509f, 643.163f, 28.05f, 3.851f}, // summon second
    {1725.338f, 643.300f, 28.05f, 3.634f}, // summon second
    {1723.557f, 638.104f, 28.05f, 3.401f}, // summon second
    {1728.344f, 636.061f, 28.05f, 3.305f}  // summon second
};

static const EventLocations SoldierMiddle[] =
{
    {1718.604f, 608.202f, 28.05f, 1.090f}, // first
    {1679.347f, 648.365f, 28.05f, 0.368f}, // second
};

class AllOrbsInGrid
{
    public:
        AllOrbsInGrid() {}
        bool operator() (GameObject* go)
        {
            if(go->GetEntry() == GAMEOBJECT_ORB_OF_THE_BLUE_DRAGONFLIGHT)
                return true;
            return false;
        }
};

class OrbOfTheBlueFlight : public GameObjectScript
{
public:
    OrbOfTheBlueFlight() : GameObjectScript("go_orb_of_the_blue_flight")
    {}

    struct OrbOfTheBlueFlightAI : public GameObjectAI
    {
        OrbOfTheBlueFlightAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* plr) override
        {
            if (me->GetUInt32Value(GAMEOBJECT_FACTION) == 35)
            {
                //remove blue ring, a bit hacky but simple
                if (Creature* dummy = plr->FindNearestCreature(CREATURE_INVISIBLE_DUMMY, 20.0f, true))
                    if (DynamicObject* Dyn = dummy->GetDynObject(SPELL_RING_OF_BLUE_FLAMES))
                        Dyn->RemoveFromWorld();

                plr->CastSpell(plr, SPELL_POWER_OF_THE_BLUE_FLIGHT, TRIGGERED_FULL_MASK);
                me->SetUInt32Value(GAMEOBJECT_FACTION, 0); //not usable anymore
                me->Refresh();
            }

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new OrbOfTheBlueFlightAI(go);
    }
};

//AI for Kalecgos
class boss_kalecgos_kj : public CreatureScript
{
public:
    boss_kalecgos_kj() : CreatureScript("boss_kalecgos_kj") {}
    
    class boss_kalecgos_kjAI : public CreatureAI
    {
        public:
        boss_kalecgos_kjAI(Creature* creature) : CreatureAI(creature)
        {
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
            if(!pInstance)
                me->DespawnOrUnsummon();
        }

        void Reset()
        override {
            for (ObjectGuid & i : Orb)
                i = ObjectGuid::Empty;

            for (ObjectGuid & OrbDummie : OrbDummies)
                if (OrbDummie != 0)
                {
                    //despawn already spawned dummies
                    if (Creature* dummy = pInstance->instance->GetCreature(OrbDummie))
                        dummy->DisappearAndDie();
                    OrbDummie = ObjectGuid::Empty;
                }

            EmpowerCount = 0;
            me->SetDisableGravity(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetKeepActive(30 * MINUTE*IN_MILLISECONDS);
            Searched = false;
            me->SetVisible(false);
            me->SetReactState(REACT_PASSIVE);
        }

        void FindOrbs()
        {
            std::list<GameObject*> orbList;
            AllOrbsInGrid check;
            Trinity::GameObjectListSearcher<AllOrbsInGrid> searcher(me, orbList, check);
            Cell::VisitGridObjects(me, searcher, MAX_SEARCHER_DISTANCE);

            if (orbList.empty())
                return;

            uint8 i = 0;
            for (auto itr = orbList.begin(); itr != orbList.end(); ++itr, ++i)
            {
                Orb[i] = (*itr)->GetGUID();
                if (Unit* dummy = (*itr)->SummonCreature(CREATURE_INVISIBLE_DUMMY,(*itr)->GetPositionX(),(*itr)->GetPositionY(),(*itr)->GetPositionZ(),0,TEMPSUMMON_MANUAL_DESPAWN,0))
                    OrbDummies[i] = dummy->GetGUID();
            }
        }

        void ResetOrbs()
        {
            for (uint8 i = 0; i < 4; ++i)
            {
                if(Unit* dummy = pInstance->instance->GetCreature(OrbDummies[i]))
                    dummy->RemoveDynObject(SPELL_RING_OF_BLUE_FLAMES);

                if(GameObject *orb = pInstance->instance->GetGameObject(Orb[i]))
                    orb->SetUInt32Value(GAMEOBJECT_FACTION, 0);
            }
        }

        void EmpowerOrb(uint8 i)
        {
            GameObject *orb = pInstance->instance->GetGameObject(Orb[i]);
            if (!orb)
                return;
            if(Unit* dummy = pInstance->instance->GetCreature(OrbDummies[i]))
            {
                dummy->CastSpell(dummy,SPELL_VISUAL_MOONFIRE, TRIGGERED_FULL_MASK);
                dummy->CastSpell(dummy, SPELL_RING_OF_BLUE_FLAMES, TRIGGERED_FULL_MASK);
            }
            orb->SetUInt32Value(GAMEOBJECT_FACTION, 35);
            orb->SetKeepActive(true);
            orb->Refresh();
        }

        void EmpowerOrb(bool all)
        {
            if (all)
            {
                for (uint8 i = 0; i < 4; ++i)
                    EmpowerOrb(i);
            }
            else
            {
                uint8 random = rand()%3;
                EmpowerOrb(random);
            }
        
            ++EmpowerCount;

            switch (EmpowerCount)
            {
                case 1:
                    Talk(SAY_KALEC_ORB_READY1);
                    break;
                case 2:
                    Talk(SAY_KALEC_ORB_READY2);
                    break;
                case 3:
                    Talk(SAY_KALEC_ORB_READY3);
                    break;
                case 4:
                    Talk(SAY_KALEC_ORB_READY4);
                    break;
            }
        }

        void UpdateAI(uint32 const diff)
        override {
            if (!Searched)
            {
                FindOrbs();
                Searched = true;
            }
        }

        bool GossipHello(Player *player) override
        {
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_KALEC_END, me->GetGUID());

            return true;
        }
            
        InstanceScript* pInstance;
    private:
        ObjectGuid Orb[4]; //orb gobjects
        ObjectGuid OrbDummies[4]; //Used for some visual effects only
   
        uint8 EmpowerCount;

        bool Searched;
    };


    CreatureAI* GetAI(Creature* creature) const
    override {
        return new boss_kalecgos_kjAI(creature);
    }
};

//AI for Kil'Jaeden Event Controller
class mob_kiljaeden_controller : public CreatureScript
{
public:
    mob_kiljaeden_controller() : CreatureScript("mob_kiljaeden_controller") {}
    
    class mob_kiljaeden_controllerAI : public CreatureAI
    {
        private:
            InstanceScript* pInstance;

            SummonList Summons;

            bool KiljaedenDeath;
            ObjectGuid handDeceiver[3];
            ObjectGuid riftGuid[2];
            ObjectGuid riftTargets[2];
            ObjectGuid soldiersGuid[20];
            ObjectGuid m_EntropiusGuid;
            ObjectGuid m_PortalGuid;
            uint32 m_currentAngleFirst;
            uint32 m_currentAngleSecond;
            
            uint32 combatCheckTimer;
            uint8 phase;
        public:
            mob_kiljaeden_controllerAI(Creature* creature) : CreatureAI(creature), Summons(me)
            {
                pInstance = ((InstanceScript*)creature->GetInstanceScript());
                SetCombatMovementAllowed(false);
            }

            EventMap events;

            uint8 DeceiverDeathCount;

            void Reset()
            override {
                if (pInstance)
                {
                    if (pInstance->GetData(DATA_KILJAEDEN_EVENT) == DONE)
                    {
                        me->CastSpell(me,SPELL_SUNWELL_IGNITION, TRIGGERED_FULL_MASK);
                        return;
                    } else {
                        me->CastSpell(me,SPELL_ANVEENA_ENERGY_DRAIN, TRIGGERED_FULL_MASK);
                        
                        pInstance->SetData(DATA_KILJAEDEN_EVENT, NOT_STARTED);
                    }
                } else {
                    me->DespawnOrUnsummon();
                    return;
                }

                events.RescheduleEvent(EVENT_SAY, urand(45000, 75000));
                
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                phase = PHASE_DECEIVERS;

                if (Creature *KalecKJ = pInstance->instance->GetCreature(ObjectGuid(pInstance->GetData64(DATA_KALECGOS_KJ))))
                    ((boss_kalecgos_kj::boss_kalecgos_kjAI*)KalecKJ->AI())->ResetOrbs();

                DeceiverDeathCount = 0;
                KiljaedenDeath = false;

                Summons.DespawnAll();

                for(uint8 i = 0; i < 3; ++i)
                    if (TempSummon *hand = me->SummonCreature(CREATURE_HAND_OF_THE_DECEIVER, DeceiverLocations[i][0], DeceiverLocations[i][1], FLOOR_Z, DeceiverLocations[i][2], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                        handDeceiver[i] = hand->GetGUID();

                me->SummonCreature(CREATURE_ANVEENA, me->GetPositionX(), me->GetPositionY(), 60, 0, TEMPSUMMON_DEAD_DESPAWN, 0);

                me->CastSpell(me,SPELL_DESTROY_DRAKES, TRIGGERED_FULL_MASK);

                m_currentAngleFirst = 0;
                m_currentAngleSecond = 0;

                combatCheckTimer = 10000;
            }

            void JustSummoned(Creature* summoned)
            override {
                Summons.Summon(summoned);
                switch(summoned->GetEntry())
                {
                    case CREATURE_HAND_OF_THE_DECEIVER:
                        summoned->CastSpell(summoned, SPELL_SHADOW_CHANNELING, TRIGGERED_NONE);
                        break;
                    case CREATURE_ANVEENA:
                    {
                        summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        summoned->SetDisableGravity(true);
                        summoned->SendMovementFlagUpdate();
                        summoned->CastSpell(summoned, SPELL_ANVEENA_PRISON, TRIGGERED_FULL_MASK);
                        summoned->SetReactState(REACT_PASSIVE);
                        break;
                    }
                    case CREATURE_KILJAEDEN:
                        summoned->CastSpell((Unit*)nullptr, SPELL_REBIRTH, TRIGGERED_NONE);
                        summoned->AI()->message(boss_kiljaedenAI_Messages::MESSAGE_SET_PHASE, PHASE_NORMAL);
                        break;
                    case NPC_RIFTWALKER:
                        summoned->CastSpell(summoned, SPELL_TELEPORT_VISUAL, TRIGGERED_FULL_MASK);
                        break;
                    case NPC_SOLDIER:
                        summoned->CastSpell(summoned, SPELL_TELEPORT_VISUAL, TRIGGERED_FULL_MASK);
                        summoned->SetWalk(false);
                        summoned->SetSpeedRate(MOVE_RUN, 1.0f);
                        break;
                    case CREATURE_PROPHET:
                        summoned->GetMotionMaster()->MovePoint(0, aOutroLocations[5].m_fX, aOutroLocations[5].m_fY, aOutroLocations[5].m_fZ);
                        // no break here
                    case CREATURE_LIADRIN:
                        summoned->CastSpell(summoned, SPELL_TELEPORT_VISUAL, TRIGGERED_FULL_MASK);
                        break;
                    case NPC_CORE_ENTROPIUS:
                        summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        summoned->CastSpell(summoned, SPELL_ENTROPIUS_BODY, TRIGGERED_FULL_MASK);
                        summoned->SetDisableGravity(true);
                        summoned->SendMovementFlagUpdate();
                        m_EntropiusGuid = summoned->GetGUID();
                        break;
                    case NPC_BOSS_PORTAL:
                        m_PortalGuid = summoned->GetGUID();
                        break;
                }
            }

            void SummonedCreatureDespawn(Creature* unit)
            override {
                Summons.Despawn(unit);
            }

            void startDialogueText()
            {
                //StartNextDialogueText(POINT_KILJAEDEN_DIE);
            }

            /*
            void JustDidDialogueStep(int32 iEntry)
            override {
                if (!pInstance)
                    return;

                switch (iEntry)
                {
                    case POINT_KILJAEDEN_DIE:
                        // While Kil'Jaeden die
                        if (Creature* Anveena = pInstance->instance->GetCreature(pInstance->GetData64(DATA_ANVEENA)))
                            Anveena->ForcedDespawn(); //this should already be done but let's do it again in case phase was gm rushed

                        if (Creature* pKalec = pInstance->instance->GetCreature(pInstance->GetData64(DATA_KALECGOS_KJ)))
                            ((boss_kalecgos_kj::boss_kalecgos_kjAI*)pKalec->AI())->ResetOrbs();
                        break;
                    case POINT_TELEPORT_KALECGOS:
                        if (Creature* pKalec = pInstance->instance->GetCreature(pInstance->GetData64(DATA_KALECGOS_KJ)))
                        {
                            pKalec->SetVisible(true);
                            pKalec->CastSpell(pKalec, SPELL_KALEC_TELEPORT, TRIGGERED_FULL_MASK);
                            pKalec->SetDisableGravity(false);
                            pKalec->SendMovementFlagUpdate();
                        }

                        if (Creature* pKJ = pInstance->instance->GetCreature(pInstance->GetData64(DATA_KILJAEDEN)))
                            pKJ->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE); //allow loot
                        break;
                    case POINT_SUMMON_SHATTERED:
                        if (Creature *portal = me->SummonCreature(NPC_BOSS_PORTAL, aOutroLocations[0].m_fX, aOutroLocations[0].m_fY, aOutroLocations[0].m_fZ, aOutroLocations[0].m_fO, TEMPSUMMON_CORPSE_DESPAWN, 0))
                            portal->SetSummoner(me);

                        for (uint8 i = 1; i < 3; i++)
                        {
                            if (Creature * riftWalker = me->SummonCreature(NPC_RIFTWALKER, aOutroLocations[i].m_fX, aOutroLocations[i].m_fY, aOutroLocations[i].m_fZ, aOutroLocations[i].m_fO, TEMPSUMMON_CORPSE_DESPAWN, 0))
                            {
                                riftGuid[i - 1] = riftWalker->GetGUID();
                                riftWalker->SetSummoner(me);
                                if (i == 1)
                                    riftWalker->GetMotionMaster()->MovePoint(0, aOutroLocations[7].m_fX, aOutroLocations[7].m_fY, aOutroLocations[7].m_fZ);
                                else
                                    riftWalker->GetMotionMaster()->MovePoint(1, aOutroLocations[8].m_fX, aOutroLocations[8].m_fY, aOutroLocations[8].m_fZ);

                                if (Creature * riftTarget = me->SummonCreature(CREATURE_INVISIBLE_DUMMY, aOutroLocations[8+i].m_fX, aOutroLocations[8+i].m_fY, aOutroLocations[8+i].m_fZ, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0))
                                {
                                    riftTargets[i - 1] = riftTarget->GetGUID();
                                    riftTarget->SetSummoner(me);
                                    riftTarget->SetSpeedRate(MOVE_RUN, 0.5f);
                                    riftTarget->SetDisableGravity(true);
                                    riftTarget->ToCreature();
                                }
                            }
                        }
                        break;
                    case POINT_SUMMON_PORTAL:
                        if (Creature* portal = pInstance->GetSingleCreatureFromStorage(NPC_BOSS_PORTAL))
                        {                     
                            portal->SetDisplayId(DISPLAYID_PORTAL_OPENING);
                            for (uint64 i : riftTargets)
                            {
                                if (Creature* riftTarget = pInstance->instance->GetCreature(i))
                                    riftTarget->ForcedDespawn(1000);
                            }
                        }
                        break;
                    case POINT_SUMMON_PORTAL_ENDOPENANIM:
                        if (Creature* portal = pInstance->GetSingleCreatureFromStorage(NPC_BOSS_PORTAL))
                            portal->SetStandState(UNIT_STAND_STATE_SIT); //this smoothly stop the explosion effect and just let the smokes continues
                        break;
                    case POINT_SUMMON_SOLDIERS_RIGHT:
                        for (ObjectGuid i : riftGuid)
                        {
                            if (Creature* rift = pInstance->instance->GetCreature(i))
                            {
                                rift->RemoveAurasDueToSpell(SPELL_OPEN_PORTAL);
                                rift->InterruptNonMeleeSpells(false);
                            }
                        }

                        for (uint8 i = 0; i < 10; i++)
                        {
                            if (Creature *soldier = me->SummonCreature(NPC_SOLDIER, SoldierLocations[i].m_fX, SoldierLocations[i].m_fY, SoldierLocations[i].m_fZ, SoldierLocations[i].m_fO, TEMPSUMMON_CORPSE_DESPAWN, 0))
                            {
                                soldier->SetSummoner(me);
                                soldiersGuid[i] = soldier->GetGUID();
                                soldier->GetMotionMaster()->MovePoint(0, SoldierMiddle[0].m_fX, SoldierMiddle[0].m_fY, SoldierMiddle[0].m_fZ, false);
                                
                                if(i==0)
                                {
                                    soldier->GetMotionMaster()->MovePoint(0, SoldierMiddle[0].m_fX, SoldierMiddle[0].m_fY, SoldierMiddle[0].m_fZ, false);
                                } else {
                                    float sx, sy;
                                    float angle = m_currentAngleFirst * (2*M_PI) / 360;
                                    float rayon = 5.0f;
                                    sx = SoldierMiddle[0].m_fX + cos(angle) * rayon;
                                    sy = SoldierMiddle[0].m_fY + sin(angle) * rayon;
                                    soldier->GetMotionMaster()->MovePoint(0, sx, sy, SoldierMiddle[0].m_fZ, false);
                                    m_currentAngleFirst = m_currentAngleFirst + 36;
                                }
                            }
                        }
                        break;
                    case POINT_SUMMON_SOLDIERS_LEFT:
                        for (uint8 i = 10; i < 20; i++)
                        {
                            if (Creature *soldier = me->SummonCreature(NPC_SOLDIER, SoldierLocations[i].m_fX, SoldierLocations[i].m_fY, SoldierLocations[i].m_fZ, SoldierLocations[i].m_fO, TEMPSUMMON_CORPSE_DESPAWN, 0))
                            {
                                soldier->SetSummoner(me);
                                soldiersGuid[i] = soldier->GetGUID();

                                if(i == 10)
                                {
                                    soldier->GetMotionMaster()->MovePoint(0, SoldierMiddle[1].m_fX, SoldierMiddle[1].m_fY, SoldierMiddle[1].m_fZ, false);
                                } else {
                                    float sx, sy;
                                    float angle = m_currentAngleFirst * (2*M_PI) / 360;
                                    float rayon = 5.0f;
                                    sx = SoldierMiddle[1].m_fX + cos(angle) * rayon;
                                    sy = SoldierMiddle[1].m_fY + sin(angle) * rayon;
                                    soldier->GetMotionMaster()->MovePoint(0, sx, sy, SoldierMiddle[1].m_fZ, false);
                                    m_currentAngleFirst = m_currentAngleFirst + 36;
                                }
                            }
                        }
                        break;
                    case POINT_SUMMON_PROPHET:
                        if (Creature *prophet = me->SummonCreature(CREATURE_PROPHET, aOutroLocations[3].m_fX, aOutroLocations[3].m_fY, aOutroLocations[3].m_fZ, aOutroLocations[3].m_fO, TEMPSUMMON_CORPSE_DESPAWN, 0))
                            prophet->SetSummoner(me);

                        if (Creature * core = me->SummonCreature(NPC_CORE_ENTROPIUS, me->GetPositionX(), me->GetPositionY(), 85.0f, 0, TEMPSUMMON_CORPSE_DESPAWN, 0))
                            core->SetSummoner(me);
                        break;
                    case POINT_SUMMON_LIADRIN:
                        if (Creature *liadrin = me->SummonCreature(CREATURE_LIADRIN, aOutroLocations[4].m_fX, aOutroLocations[4].m_fY, aOutroLocations[4].m_fZ, aOutroLocations[4].m_fO, TEMPSUMMON_TIMED_DESPAWN, 4 * MINUTE * IN_MILLISECONDS))
                            liadrin->SetSummoner(me);
                        break;
                    case POINT_CALL_ENTROPIUS:
                        // Set point id = 1 for movement event
                        if (Creature* pEntropius = me->GetMap()->GetCreature(m_EntropiusGuid))
                        {
                            if (Creature* pVelen = pInstance->GetSingleCreatureFromStorage(CREATURE_PROPHET))
                                pVelen->CastSpell(pEntropius, SPELL_CALL_ENTROPIUS, TRIGGERED_NONE);

                            pEntropius->SetWalk(false);
                            pEntropius->GetMotionMaster()->MovePoint(1, me->GetPositionX(), me->GetPositionY(), 40.0f);
                        }
                        break;
                    case POINT_MOVE_LIADRIN:
                        if (Creature* pLiadrin = pInstance->GetSingleCreatureFromStorage(CREATURE_LIADRIN))
                            pLiadrin->GetMotionMaster()->MovePoint(0, aOutroLocations[6].m_fX, aOutroLocations[6].m_fY, aOutroLocations[6].m_fZ);
                        break;
                    case POINT_BLAZE:
                        if (Creature* pEntropius = me->GetMap()->GetCreature(m_EntropiusGuid))
                        {
                            pEntropius->CastSpell(pEntropius, SPELL_BLAZE_TO_LIGHT, TRIGGERED_FULL_MASK);
                            pEntropius->RemoveAurasDueToSpell(SPELL_ENTROPIUS_BODY);
                        }
                        break;
                    case POINT_IGNITE:
                        // When the purified Muru reaches the ground the sunwell ignites and Muru despawns
                        me->CastSpell(me, SPELL_SUNWELL_IGNITION);

                        if (Creature* pLiadrin = pInstance->GetSingleCreatureFromStorage(CREATURE_LIADRIN))
                            pLiadrin->SetStandState(UNIT_STAND_STATE_KNEEL);

                        if (Creature* pEntropius = me->GetMap()->GetCreature(m_EntropiusGuid))
                            pEntropius->ForcedDespawn();
                        break;
                    case POINT_EVENT_SOLDIER_EXIT:
                        for (uint8 i = 0; i < 20; i++)
                        {
                            if (Creature* soldier = pInstance->instance->GetCreature(soldiersGuid[i]))
                            {
                                soldier->SetWalk(false);
                                soldier->SetSpeedRate(MOVE_RUN, 1.0f);
                                soldier->GetMotionMaster()->MovePoint(2, SoldierLocations[i].m_fX, SoldierLocations[i].m_fY, SoldierLocations[i].m_fZ, false);
                            }
                        }
                        break;
                    case POINT_EVENT_VELEN_EXIT:
                        // Set point id = 1 for the despawn event
                        if (Creature* pVelen = pInstance->GetSingleCreatureFromStorage(CREATURE_PROPHET))
                            pVelen->GetMotionMaster()->MovePoint(1, aOutroLocations[3].m_fX, aOutroLocations[3].m_fY, aOutroLocations[3].m_fZ);

                        if (Creature* pKalec = pInstance->GetSingleCreatureFromStorage(CREATURE_KALECGOS))
                        {
                            pKalec->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            pKalec->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        }
                        break;
                }
            }
            */

            /*FIXME
            void summonedMovementInform(Creature* pSummoned, uint32 uiType, uint32 uiPointId)
            override {
                if (uiType != POINT_MOTION_TYPE)
                    return;

                switch(uiPointId)
                {
                case 0:
                    switch(pSummoned->GetEntry())
                    {
                    case NPC_RIFTWALKER:
                        if(Creature* riftTarget = pSummoned->GetMap()->GetCreature(riftTargets[0]))
                        {
                            pSummoned->CastSpell(riftTarget, SPELL_OPEN_PORTAL, TRIGGERED_NONE);
                            riftTarget->GetMotionMaster()->MovePoint(0, aOutroLocations[9].m_fX, aOutroLocations[9].m_fY, aOutroLocations[9].m_fZ+13.0f);
                        }
                        break;
                    case NPC_SOLDIER:
                        if (pSummoned->GetGUID() == soldiersGuid[0] || pSummoned->GetGUID() == soldiersGuid[10])
                            pSummoned->SetStandState(UNIT_STAND_STATE_KNEEL);

                        if(Creature* portal = pInstance->GetSingleCreatureFromStorage(NPC_BOSS_PORTAL))
                        {
                            pSummoned->SetOrientation(pSummoned->GetAngle(aOutroLocations[5].m_fX, aOutroLocations[5].m_fY)); //velen talk position
                            pSummoned->SendMovementFlagUpdate();
                        }
                        break;
                    }
                    break;
                case 1:
                    switch(pSummoned->GetEntry())
                    {
                    case NPC_RIFTWALKER:
                        if(Creature* riftTarget = pSummoned->GetMap()->GetCreature(riftTargets[1]))
                        {
                            pSummoned->CastSpell(riftTarget, SPELL_OPEN_PORTAL, TRIGGERED_NONE);
                            riftTarget->GetMotionMaster()->MovePoint(0, aOutroLocations[10].m_fX, aOutroLocations[10].m_fY, aOutroLocations[10].m_fZ+13.0f);
                        }
                        break;
                    case NPC_CORE_ENTROPIUS:
                        if (Creature* pVelen = pInstance->GetSingleCreatureFromStorage(CREATURE_PROPHET))
                            pVelen->InterruptNonMeleeSpells(false);
                        break;
                    case CREATURE_PROPHET:
                        pSummoned->ForcedDespawn(1000);

                        // Note: portal should despawn only after all the soldiers have reached this point and "teleported" outside
                        if (Creature* pPortal = me->GetMap()->GetCreature(m_PortalGuid))
                           pPortal->ForcedDespawn(30000);

                        for (uint8 i = 0; i < 2; i++)
                        {
                            if (Creature* rift = pInstance->instance->GetCreature(riftGuid[i]))
                                rift->ForcedDespawn(1000);
                        }

                        me->ForcedDespawn(300000);
                        break;
                    }
                    break;
                case 2:
                    if (pSummoned->GetEntry() == NPC_SOLDIER)
                        pSummoned->ForcedDespawn(1000);
                    break;
                case 10:
                    if (pSummoned->GetEntry() == NPC_SOLDIER)
                    {
                        pSummoned->SetOrientation(SoldierMiddle[0].m_fO);
                        pSummoned->SendMovementFlagUpdate();
                    }
                    break;
                case 11:
                    if (pSummoned->GetEntry() == NPC_SOLDIER)
                    {
                        pSummoned->SetOrientation(SoldierMiddle[1].m_fO);
                        pSummoned->SendMovementFlagUpdate();
                    }
                    break;
                }
            }
            */

            void JustEngagedWith(Unit* victim)
            override {
                // DEBUG
                char w[50];
                snprintf(w, 50, "pull : %s",victim->GetName().c_str());
                me->Say(w,LANG_UNIVERSAL,nullptr);
                //
                DoZoneInCombat();
                for (ObjectGuid i : handDeceiver)
                {
                    if (Creature *hand = pInstance->instance->GetCreature(i))
                    {
                        hand->AI()->DoZoneInCombat();
                        if (!hand->IsInCombat())
                            hand->AI()->AttackStart(victim);

                        hand->SetReactState(REACT_AGGRESSIVE);
                        hand->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        hand->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    }
                }
            }

            void UpdateAI(uint32 const diff)
            override {
                //DialogueUpdate(diff);

                events.Update(diff);
            

                while (uint32 eventId = events.ExecuteEvent())
                    switch (eventId)
                    {
                        case 0:
                            break;
                        case EVENT_SAY:
                            if (pInstance->GetData(DATA_MURU_EVENT) != DONE && pInstance->GetData(DATA_KILJAEDEN_EVENT) == NOT_STARTED)
                                Talk(SAY_KJ_OFFCOMBAT); 

                            events.RescheduleEvent(EVENT_SAY, 20*MINUTE*IN_MILLISECONDS, 30*MINUTE*IN_MILLISECONDS);
                            break;
                    }

                if(pInstance && (pInstance->GetData(DATA_MURU_EVENT) != DONE || pInstance->GetData(DATA_KILJAEDEN_EVENT) == DONE))
                    return;

                if (pInstance->GetData(DATA_KILJAEDEN_EVENT) == NOT_STARTED)
                {
                    if(combatCheckTimer < diff)
                    {
                        Map::PlayerList const& players = pInstance->instance->GetPlayers();
                        for(const auto & player : players)
                        //for(auto itr : players) //why does using auto call ~GroupReference() for every ref ?
                            if (Player* plr = player.GetSource())
                                if (me->GetDistance(plr) <= 50.0f && me->IsHostileTo(plr))
                                {
                                    pInstance->SetData(DATA_KILJAEDEN_EVENT,IN_PROGRESS);
                                    JustEngagedWith(plr);
                                    break;
                                }
                        combatCheckTimer = 2500;
                    } else combatCheckTimer -= diff;
                }

                if (pInstance->GetData(DATA_MURU_EVENT) != DONE)
                {
                    EnterEvadeMode();
                    return;
                }

                if (DeceiverDeathCount > 2 && phase == PHASE_DECEIVERS)
                {
                    me->RemoveAurasDueToSpell(SPELL_ANVEENA_ENERGY_DRAIN);
                    phase = PHASE_NORMAL;
                    me->SummonCreature(CREATURE_KILJAEDEN, KJLocation[0], KJLocation[1], KJLocation[2], KJLocation[3], TEMPSUMMON_MANUAL_DESPAWN, 0);
                }
            }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_kiljaeden_controllerAI(creature);
    }
};

//AI for Kil'jaeden
class boss_kiljaeden : public CreatureScript
{
public:
    boss_kiljaeden() : CreatureScript("boss_kiljaeden") {}

    class boss_kiljaedenAI : public CreatureAI
    {
        private:
            InstanceScript* pInstance;

            SummonList Summons;
            BumpHelper bumpHelper;

            uint32 animSpawnTimer;
            bool firstDialogueStep;
            bool secondDialogueStep;
            bool thirdDialogueStep;
            
            uint8 phaseDarknessCount;
            EventMap events;
            bool initDone = false;
            uint8 phase = 0;

        public:

        boss_kiljaedenAI(Creature* creature) : CreatureAI(creature), Summons(me), bumpHelper(2000)
        {
            SetCombatMovementAllowed(false);
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
            me->SetDisableGravity(true);
            me->Relocate(KJLocation[0], KJLocation[1], KJLocation[2]);
            me->SendMovementFlagUpdate();
            phaseDarknessCount = 0;
            phase = PHASE_DECEIVERS;
        }

        uint64 message(uint32 id, uint64 data) override
        {
            switch (id)
            {
            case MESSAGE_SET_PHASE:
                setPhase(data);
                break;
            }
            return 0;
        }

        void Reset()
        override {
            Summons.DespawnAll();
            //destroy at non spawn reset
            if(initDone)
            {
                if (TempSummon* u = me->ToTempSummon())
                    if(u->GetSummoner() && u->GetSummoner()->ToCreature() && u->GetSummoner()->ToCreature()->AI())
                        u->GetSummoner()->ToCreature()->AI()->EnterEvadeMode();

                if(pInstance)
                    pInstance->SetData(DATA_KILJAEDEN_EVENT,NOT_STARTED);
                me->DespawnOrUnsummon();
                return;
            }

            me->SetDisableGravity(true);
            setPhase(PHASE_DECEIVERS);

            me->Say("Script to fix, most event disabled with removing of CreatureAINew");
            /*
            addEvent(EVENT_KALEC_JOIN, 30000, 30000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(2) | phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            // Phase 2
            addEvent(EVENT_SOUL_FLAY, 1000, 1000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(2) | phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            addEvent(EVENT_LEGION_LIGHTNING, 10000, 20000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(2) | phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            addEvent(EVENT_FIRE_BLOOM, 10000, 15000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(2) | phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            addEvent(EVENT_SUMMON_SHILEDORB, 10000, 15000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(2) | phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            // Phase 3
            addEvent(EVENT_SHADOW_SPIKE, 4000, 4000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            addEvent(EVENT_FLAME_DART, 4500, 4500, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            addEvent(EVENT_DARKNESS, 75000, 75000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            addEvent(EVENT_ORBS_EMPOWER, 35000, 35000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            addEvent(EVENT_SINISTER_REFLECTION, 500, 500, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(3) | phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            // Phase 4
            addEvent(EVENT_ARMAGEDDON, 21000, 21000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(4) | phaseMaskForPhase(5)));
            */
            firstDialogueStep = false;
            secondDialogueStep = false;
            thirdDialogueStep = false;

            me->SetFullTauntImmunity(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->AddUnitState(UNIT_STATE_STUNNED);
            animSpawnTimer = 11000;
            initDone = true;

        }

        void setPhase(uint32 newPhase)
        {
            phase = newPhase;
            switch (newPhase)
            {
                case PHASE_DARKNESS:
                    // Phase 2
                    events.RescheduleEvent(EVENT_SOUL_FLAY, 1000);
                    events.RescheduleEvent(EVENT_LEGION_LIGHTNING, urand(10000, 20000));
                    events.RescheduleEvent(EVENT_FIRE_BLOOM, urand(10000, 15000));
                    events.RescheduleEvent(EVENT_SUMMON_SHILEDORB, urand(10000, 15000));

                    Talk(SAY_KJ_PHASE3);
                    break;
                case PHASE_ARMAGEDDON:
                    // Phase 2
                    events.RescheduleEvent(EVENT_SOUL_FLAY, 1000);
                    events.RescheduleEvent(EVENT_LEGION_LIGHTNING, urand(10000, 20000));
                    events.RescheduleEvent(EVENT_FIRE_BLOOM, urand(10000, 15000));
                    events.RescheduleEvent(EVENT_SUMMON_SHILEDORB, urand(10000, 15000));
                    // Phase 3
                    events.RescheduleEvent(EVENT_SHADOW_SPIKE, 4000);
                    events.RescheduleEvent(EVENT_FLAME_DART, urand(50000, 65000));
                    events.RescheduleEvent(EVENT_DARKNESS, 75000);
                    events.RescheduleEvent(EVENT_ORBS_EMPOWER, 35000);
                    events.RescheduleEvent(EVENT_SINISTER_REFLECTION, 500);

                    Talk(SAY_KJ_PHASE4);
                    me->CastSpell((Unit*)nullptr, SPELL_DESTROY_DRAKES, TRIGGERED_FULL_MASK);
                    break;
                case PHASE_SACRIFICE:
                    // Phase 2
                    events.RescheduleEvent(EVENT_SOUL_FLAY, 1000);
                    events.RescheduleEvent(EVENT_LEGION_LIGHTNING, urand(10000, 20000));
                    events.CancelEvent(EVENT_FIRE_BLOOM);
                    events.RescheduleEvent(EVENT_SUMMON_SHILEDORB, urand(10000, 15000));
                    // Phase 3
                    events.RescheduleEvent(EVENT_SHADOW_SPIKE, 4000);
                    events.RescheduleEvent(EVENT_FLAME_DART, urand(50000, 65000));
                    events.RescheduleEvent(EVENT_DARKNESS, 25000);
                    events.RescheduleEvent(EVENT_ORBS_EMPOWER, 500);
                    events.RescheduleEvent(EVENT_SINISTER_REFLECTION, 500);
                    // Phase 4
                    events.RescheduleEvent(EVENT_ARMAGEDDON, 21000);

                    Talk(SAY_KJ_PHASE5);
                    me->CastSpell((Unit*)nullptr, SPELL_DESTROY_DRAKES, TRIGGERED_FULL_MASK);
                    break;
            }
            phaseDarknessCount = 0;
        }

        void JustSummoned(Creature* summoned)
        override {
            Summons.Summon(summoned);
            switch (summoned->GetEntry())
            {
                case CREATURE_ARMAGEDDON_TARGET:
                    summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    summoned->AI()->DoZoneInCombat();
                    break;
            }
        }

        void SummonedCreatureDespawn(Creature* unit)
        override {
            Summons.Despawn(unit);
        }

        void JustDied(Unit* /*killer*/)
        override {
            Talk(SAY_KJ_DEATH);
            Summons.DespawnAll();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            if (pInstance)
                pInstance->SetData(DATA_KILJAEDEN_EVENT, DONE);

            if (Creature *controller = pInstance->instance->GetCreature(ObjectGuid(pInstance->GetData64(DATA_KILJAEDEN_CONTROLLER))))
            {
                controller->SetFaction(FACTION_FRIENDLY);
                controller->RemoveAllAuras();
                controller->GetThreatManager().ClearAllThreat();
                controller->CombatStop();
                ((mob_kiljaeden_controller::mob_kiljaeden_controllerAI*)controller->AI())->startDialogueText();
            }
        }

        void KilledUnit(Unit* /*victim*/)
        override {
            Talk(SAY_KJ_SLAY);
        }

        void JustEngagedWith(Unit* /*who*/)
        override {
            DoZoneInCombat();
            Talk(SAY_KJ_EMERGE);
        }

        /** FIXME
        void onSpellPrepare(SpellInfo const* spell, Unit* target)
        override {
            if (spell->Id == SPELL_DARKNESS_OF_A_THOUSAND_SOULS_DAMAGE)
                Talk(SAY_KJ_DARKNESS);
        }
        */

        /*
        void JustDidDialogueStep(int32 iEntry)
        override {
            if (!pInstance)
                return;

            switch (iEntry)
            {
                case SAY_ANVEENA_4:
                    if (Creature* Anveena = pInstance->instance->GetCreature(pInstance->GetData64(DATA_ANVEENA)))
                    {
                        Anveena->RemoveAurasDueToSpell(SPELL_ANVEENA_PRISON);
                        Anveena->CastSpell((Unit*)nullptr, SPELL_SACRIFICE_OF_ANVEENA, TRIGGERED_FULL_MASK);
                        Anveena->ForcedDespawn(3000);
                    }
                    me->SetControlled(true, UNIT_STATE_STUNNED);
                    break;
                case SAY_KJ_PHASE5:
                    me->SetControlled(false, UNIT_STATE_STUNNED);
                    break;
                case SAY_KALEC_5:
                    setPhase(PHASE_SACRIFICE);
                    break;
            }
        }
        */

        void bumpClosePlayers(const uint32 diff)
        {
            bumpHelper.Update(diff);
            Map::PlayerList const& players = pInstance->instance->GetPlayers();
            for(const auto & player : players)
            {
                Player* pl = player.GetSource();
                if (pl->IsAttackableByAOE() && pl->GetExactDistance2d(me->GetPositionX(),me->GetPositionY()) <= 13.0f) //~when a player set foot in the well
                    if (bumpHelper.AddCooldown(pl)) //return true if player wasn't knocked back < 2s ago
                        me->CastSpell(pl, SPELL_KNOCK_BACK, TRIGGERED_FULL_MASK);
            }
        }

        void UpdateAI(const uint32 diff)
        override {
            if (animSpawnTimer)
            {
                me->SetTarget(ObjectGuid::Empty);
                if (animSpawnTimer <= diff)
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->ClearUnitState(UNIT_STATE_STUNNED);
                    DoZoneInCombat();
                    if (Unit *unit = SelectTarget(SELECT_TARGET_MINDISTANCE, 0, 100.0f, true))
                    {
                        AttackStart(unit);
                        animSpawnTimer = 0;
                    }
                    else
                        EnterEvadeMode();
                }
                else
                    animSpawnTimer -= diff;
                return;
            }

            //DialogueUpdate(diff);

            if (!UpdateVictim())
                return;

            bumpClosePlayers(diff);
            events.Update(diff);

            if (!firstDialogueStep)
            {
                if (me->IsBelowHPPercent(80))
                {
                    firstDialogueStep = true;
                    //StartNextDialogueText(SAY_KALEC_1);
                }
            }

            if (!secondDialogueStep)
            {
                if (me->IsBelowHPPercent(50))
                {
                    //SetNewArray(secondDialogue);
                    secondDialogueStep = true;
                    //StartNextDialogueText(SAY_KALEC_2);
                }
            }

            if (!thirdDialogueStep)
            {
                if (me->IsBelowHPPercent(25))
                {
                    events.CancelEvent(EVENT_DARKNESS); //no darkness before phase changed
                    //SetNewArray(thirdDialogue);
                    thirdDialogueStep = true;
                    //StartNextDialogueText(SAY_KALEC_3);
                }
            }

            if (me->HasUnitState(UNIT_STATE_CASTING) || me->HasUnitState(UNIT_STATE_STUNNED))
                return;

            //Phase 3
            if (phase <= PHASE_NORMAL)
            {
                if (phase == PHASE_NORMAL && me->IsBelowHPPercent(85))
                    setPhase(PHASE_DARKNESS);
            }

            //Phase 4
            if (phase <= PHASE_DARKNESS)
            {
                if (phase == PHASE_DARKNESS && me->IsBelowHPPercent(55))
                    setPhase(PHASE_ARMAGEDDON);
            }


            while (uint32 eventId = events.ExecuteEvent())
                switch (eventId)
                {
                    case EVENT_KALEC_JOIN:
                        events.CancelEvent(EVENT_KALEC_JOIN);
                        if (Creature* kalec = pInstance->instance->GetCreature(ObjectGuid(pInstance->GetData64(DATA_KALECGOS_KJ))))
                        {
                            kalec->AI()->Talk(SAY_KALEC_JOIN);
                            kalec->SetVisible(true);
                        }
                        break;
                    case EVENT_SOUL_FLAY:
                        if(me->CastSpell(me->GetVictim(), SPELL_SOUL_FLAY) == SPELL_CAST_OK)
                            events.RescheduleEvent(EVENT_SOUL_FLAY, urand(4000, 5000));
                        break;
                    case EVENT_LEGION_LIGHTNING:
                        if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            if(me->CastSpell(target, SPELL_LEGION_LIGHTNING) == SPELL_CAST_OK)
                                events.RescheduleEvent(EVENT_LEGION_LIGHTNING, urand(10000, 20000));
                        break;
                    case EVENT_FIRE_BLOOM:
                        me->CastSpell(nullptr, SPELL_FIRE_BLOOM);
                        switch(phase)
                        {
                        case PHASE_NORMAL:
                            events.RescheduleEvent(EVENT_FIRE_BLOOM, 22000);
                            break;
                        case PHASE_DARKNESS:
                        case PHASE_ARMAGEDDON:
                            events.RescheduleEvent(EVENT_FIRE_BLOOM, urand(40000, 65000));
                            break;
                        case PHASE_SACRIFICE:
                            events.RescheduleEvent(EVENT_FIRE_BLOOM, urand(90000, 105000));
                            break;
                        }
                        break;
                    case EVENT_SUMMON_SHILEDORB:
                        for (uint8 i = 1; i < phase; ++i)
                        {
                            float sx, sy;
                            sx = ShieldOrbLocations[0][0] + sin(ShieldOrbLocations[i][0]);
                            sy = ShieldOrbLocations[0][1] + sin(ShieldOrbLocations[i][1]);
                            if (Creature* orb = me->SummonCreature(CREATURE_SHIELD_ORB, sx, sy, SHIELD_ORB_Z, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 45000))
                                orb->AI()->DoZoneInCombat();
                        }

                        events.RescheduleEvent(EVENT_SUMMON_SHILEDORB, urand(25000, 30000));
                        if (phase == PHASE_SACRIFICE)
                            events.CancelEvent(EVENT_SUMMON_SHILEDORB);

                        break;
                    case EVENT_SHADOW_SPIKE:
                        if(me->CastSpell((Unit*)nullptr, SPELL_SHADOW_SPIKE) == SPELL_CAST_OK)
                            events.CancelEvent(EVENT_SHADOW_SPIKE);
                        break;
                    case EVENT_FLAME_DART:
                        if(me->CastSpell((Unit*)nullptr, SPELL_FLAME_DART) == SPELL_CAST_OK)
                            events.RescheduleEvent(EVENT_FLAME_DART, urand(50000, 65000));
                        break;
                    case EVENT_DARKNESS:
                        phaseDarknessCount++;
                        Talk(EMOTE_KJ_DARKNESS);
                        if (me->CastSpell((Unit*)nullptr, SPELL_DARKNESS_OF_A_THOUSAND_SOULS) == SPELL_CAST_OK)
                        {
                            events.RescheduleEvent(EVENT_DARKNESS, (phase == PHASE_SACRIFICE) ? 28000 : 48000);
                            events.RescheduleEvent(EVENT_SUMMON_SHILEDORB, urand(9000, 10000));
                            events.RescheduleEvent(EVENT_FLAME_DART, urand(5000, 20000));
                            if (phase == PHASE_NORMAL)
                                events.RescheduleEvent(EVENT_FIRE_BLOOM, 25000);
                            else if (phaseDarknessCount == 1)
                                events.RescheduleEvent(EVENT_FIRE_BLOOM, urand(10000, 40000));
                            else
                                events.RescheduleEvent(EVENT_FIRE_BLOOM, urand(15000, 20000));

                            me->RemoveAurasDueToSpell(SPELL_ARMAGEDDON_PERIODIC_SUMMON);
                            if (phase >= PHASE_ARMAGEDDON)
                                events.RescheduleEvent(EVENT_ARMAGEDDON, 8000);
                        }
                        break;
                    case EVENT_ORBS_EMPOWER:
                        if (phase == PHASE_SACRIFICE)
                        {
                            if (Creature* kalec = pInstance->instance->GetCreature(ObjectGuid(pInstance->GetData64(DATA_KALECGOS_KJ))))
                                ((boss_kalecgos_kj::boss_kalecgos_kjAI*)kalec->AI())->EmpowerOrb(true);
                        }
                        else
                        {
                            if (Creature* kalec = pInstance->instance->GetCreature(ObjectGuid(pInstance->GetData64(DATA_KALECGOS_KJ))))
                                ((boss_kalecgos_kj::boss_kalecgos_kjAI*)kalec->AI())->EmpowerOrb(false);

                        }

                        events.CancelEvent(EVENT_ORBS_EMPOWER);
                        break;
                    case EVENT_SINISTER_REFLECTION:
                        Talk(SAY_KJ_REFLECTION);
                        me->CastSpell((Unit*)nullptr, SPELL_SINISTER_REFLECTION, TRIGGERED_FULL_MASK);

                        events.CancelEvent(EVENT_SINISTER_REFLECTION);
                        break;
                    case EVENT_ARMAGEDDON:
                    { 
                        me->CastSpell(me, SPELL_ARMAGEDDON_PERIODIC_SUMMON, TRIGGERED_FULL_MASK);

                        if (phase == PHASE_SACRIFICE)
                            events.CancelEvent(EVENT_ARMAGEDDON); //timer will be reset uppon EVENT_DARKNESS
                        else
                            events.RescheduleEvent(EVENT_ARMAGEDDON, 26000); //about ~15 seconds where KJ don't spawns any new armaggedon area on the ground (checked on retail https://www.youtube.com/watch?v=Xwv_UZDl_AM)
                        break;
                    }
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new boss_kiljaedenAI(creature);
    }
};

//AI for Hand of the Deceiver
class mob_hand_of_the_deceiver : public CreatureScript
{
public:
    mob_hand_of_the_deceiver() : CreatureScript("mob_hand_of_the_deceiver") {}

    class mob_hand_of_the_deceiverAI : public CreatureAI
    {
        private:
            InstanceScript* pInstance;

            SummonList Summons;
        public:
            mob_hand_of_the_deceiverAI(Creature* creature) : CreatureAI(creature), Summons(me)
            {
                pInstance = ((InstanceScript*)creature->GetInstanceScript());
            }

            EventMap events;

            void JustSummoned(Creature* summoned)
            override {
                Summons.Summon(summoned);
            }

            void SummonedCreatureDespawn(Creature* unit)
            override {
                Summons.Despawn(unit);
            }

            void Reset()
            override {
                events.RescheduleEvent(EVENT_SHADOWBOLT, urand(2000, 3000));
                events.RescheduleEvent(EVENT_FELFIRE, urand(5000, 10000));

                pInstance->SetData(DATA_KILJAEDEN_EVENT,NOT_STARTED);

                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                Summons.DespawnAll();
            }

            void JustEngagedWith(Unit* victim)
            override {
                if(pInstance)
                {
                    pInstance->SetData(DATA_KILJAEDEN_EVENT, IN_PROGRESS);
                    if (Creature* Control = pInstance->instance->GetCreature(ObjectGuid(pInstance->GetData64(DATA_KILJAEDEN_CONTROLLER))))
                        if (!Control->GetVictim())
                            Control->AI()->AttackStart(victim);
                }

                me->InterruptNonMeleeSpells(true);
            }

            void JustDied(Unit* /*killer*/)
            override {
                me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
                Summons.DespawnAll();

                if(pInstance)
                    if (Creature* Control = pInstance->instance->GetCreature(ObjectGuid(pInstance->GetData64(DATA_KILJAEDEN_CONTROLLER))))
                        ((mob_kiljaeden_controller::mob_kiljaeden_controllerAI*)Control->AI())->DeceiverDeathCount++;
            }

            void UpdateAI(uint32 const diff)
            override {
                if (!me->IsInCombat())
                    me->CastSpell(me, SPELL_SHADOW_CHANNELING);

                if (!UpdateVictim())
                    return;

                if (pInstance->GetData(DATA_MURU_EVENT) != DONE)
                {
                    EnterEvadeMode();
                    return;
                }

                // Gain Shadow Infusion
                if (me->IsBetweenHPPercent(20, 25) && !me->HasAuraEffect(SPELL_SHADOW_INFUSION))
                    if (rand()%2)
                        me->CastSpell(me, SPELL_SHADOW_INFUSION, TRIGGERED_FULL_MASK);

                events.Update(diff);
            

                while (uint32 eventId = events.ExecuteEvent())
                    switch (eventId)
                    {
                        case 0:
                            break;
                        case EVENT_SHADOWBOLT:
                            me->CastSpell(me, SPELL_SHADOW_BOLT_VOLLEY);
                            events.RescheduleEvent(EVENT_SHADOWBOLT, 300);
                            break;
                        case EVENT_FELFIRE:
                            if(me->CastSpell(me, SPELL_FELFIRE_PORTAL) == SPELL_CAST_OK)
                                events.RescheduleEvent(EVENT_FELFIRE, 20000);
                            break;
                    }

                DoMeleeAttackIfReady();
            }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_hand_of_the_deceiverAI(creature);
    }
};

//AI for Felfire Portal
class mob_felfire_portal : public CreatureScript
{
public:
    mob_felfire_portal() : CreatureScript("mob_felfire_portal") {}
    
    class mob_felfire_portalAI : public CreatureAI
    {
        private:
            InstanceScript* pInstance;

            SummonList Summons;

        public:
        mob_felfire_portalAI(Creature* creature) : CreatureAI(creature), Summons(me)
        {
            SetCombatMovementAllowed(false);
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
        }

        EventMap events;

        void Reset()
        override {
            events.RescheduleEvent(EVENT_SPAWNFIEND, 1000);

            Summons.DespawnAll();
        }

        void JustSummoned(Creature* summoned)
        override {
            Summons.Summon(summoned);
        }

        void SummonedCreatureDespawn(Creature* unit)
        override {
            Summons.Despawn(unit);
        }

        void UpdateAI(uint32 const diff)
        override {
            if (pInstance && pInstance->GetData(DATA_KILJAEDEN_EVENT) == NOT_STARTED)
            {
                me->DisappearAndDie();
                return;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
                switch (eventId)
                {
                    case 0:
                        break;
                    case EVENT_SPAWNFIEND:
                        me->CastSpell(me, SPELL_SUMMON_FELFIRE_FIEND, TRIGGERED_NONE);
                        events.CancelEvent(EVENT_SPAWNFIEND);
                        break;
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_felfire_portalAI(creature);
    }
};

//AI for Felfire Fiend
class mob_volatile_felfire_fiend : public CreatureScript
{
public:
    mob_volatile_felfire_fiend() : CreatureScript("mob_volatile_felfire_fiend") {}

    class mob_volatile_felfire_fiendAI : public CreatureAI
    {
        private:
            InstanceScript* pInstance;
        public:
            mob_volatile_felfire_fiendAI(Creature* creature) : CreatureAI(creature)
            {
                pInstance = ((InstanceScript*)creature->GetInstanceScript());
            }

            EventMap events;

            void Reset()
            override {
                events.RescheduleEvent(EVENT_STUN, 2000);
                events.RescheduleEvent(EVENT_EXPLODE, 2000);
                events.CancelEvent(EVENT_DIE_F);

                me->AddUnitState(UNIT_STATE_STUNNED);
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            override {
                me->CastSpell(me, SPELL_FELFIRE_FISSION);
                if (!events.GetNextEventTime(EVENT_DIE_F))
                    events.RescheduleEvent(EVENT_DIE_F, 500);
            }

            void UpdateAI(uint32 const diff)
            override {
                if (pInstance->GetData(DATA_KILJAEDEN_EVENT) == NOT_STARTED)
                {
                    me->DisappearAndDie();
                    return;
                }

                events.Update(diff);


                while (uint32 eventId = events.ExecuteEvent())
                    switch (eventId)
                    {
                        case 0:
                            break;
                        case EVENT_STUN:
                            me->ClearUnitState(UNIT_STATE_STUNNED);
                            if (TempSummon* _me = me->ToTempSummon())
                            {
                                if (Unit* summoner = _me->GetSummoner())
                                {
                                    if (summoner->GetEntry() == 25837)
                                    {
                                        me->GetMotionMaster()->MovePath(25851); //this path is PATH_TYPE_ONCE
                                        events.CancelEvent(EVENT_STUN);
                                    }
                                    else
                                    {
                                        DoZoneInCombat();
                                        if (Unit *unit = SelectTarget(SELECT_TARGET_MINDISTANCE, 0, 100.0f, false))
                                        {
                                            AttackStart(unit);
                                            me->GetThreatManager().AddThreat(unit, 10000000.0f);
                                            events.CancelEvent(EVENT_STUN);
                                        }
                                    }
                                }
                            }
                            events.RescheduleEvent(EVENT_STUN, 500);
                            break;
                        case EVENT_EXPLODE:
                            if (me->IsWithinMeleeRange(me->GetVictim()))
                            {
                                // Explode if it's close enough to it's target
                                me->CastSpell(me, SPELL_FELFIRE_FISSION);
                                events.CancelEvent(EVENT_EXPLODE);
                                if(!events.GetNextEventTime(EVENT_DIE_F))
                                    events.ScheduleEvent(EVENT_DIE_F, 500);
                            }
                            events.RescheduleEvent(EVENT_EXPLODE, 2000);
                            break;
                        case EVENT_DIE_F:
                            events.CancelEvent(EVENT_DIE_F);
                            me->DisappearAndDie();
                            break;
                    }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_volatile_felfire_fiendAI(creature);
    }
};

//AI for Armageddon target
class mob_armageddon : public CreatureScript
{
public:
    mob_armageddon() : CreatureScript("mob_armageddon") {}

    class mob_armageddonAI : public CreatureAI
    {
        private:
            InstanceScript* pInstance;
        public:
            mob_armageddonAI(Creature* creature) : CreatureAI(creature)
            {
                SetCombatMovementAllowed(false);
                pInstance = ((InstanceScript*)creature->GetInstanceScript());
            }

            EventMap events;

            void Reset()
            override {
                events.RescheduleEvent(EVENT_VISUAL1, 1, 0, 0);
                events.CancelEvent(EVENT_TRIGGER);
                events.CancelEvent(EVENT_DIE);
            }

            void UpdateAI(uint32 const diff)
            override {
                if (pInstance && pInstance->GetData(DATA_KILJAEDEN_EVENT) == NOT_STARTED)
                {
                    me->DisappearAndDie();
                    return;
                }

                events.Update(diff);


                while (uint32 eventId = events.ExecuteEvent())
                    switch (eventId)
                    {
                        case 0:
                            break;
                        case EVENT_VISUAL1:
                            if (me->CastSpell(me, SPELL_ARMAGEDDON_VISUAL, TRIGGERED_FULL_MASK) == SPELL_CAST_OK)
                            {
                                events.CancelEvent(EVENT_VISUAL1);
                                if (!events.GetNextEventTime(EVENT_TRIGGER))
                                    events.ScheduleEvent(EVENT_TRIGGER, 9000);
                            }
                            break;
                        case EVENT_TRIGGER:
                            if (me->CastSpell(me, SPELL_ARMAGEDDON_TRIGGER, TRIGGERED_FULL_MASK) == SPELL_CAST_OK)
                            {
                                events.CancelEvent(EVENT_TRIGGER);
                                if (!events.GetNextEventTime(EVENT_DIE))
                                    events.ScheduleEvent(EVENT_DIE, 5000);
                            }
                            break;
                        case EVENT_DIE:
                            events.CancelEvent(EVENT_DIE);
                            me->DisappearAndDie();
                            break;
                    }
            }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_armageddonAI(creature);
    }
};

//AI for Shield Orbs
class mob_shield_orb : public CreatureScript
{
public:
    mob_shield_orb() : CreatureScript("mob_shield_orb") {}

    class mob_shield_orbAI : public CreatureAI
    {
        private:
            bool PointReached;
            bool Clockwise;
            uint32 checkTimer;

            InstanceScript *pInstance;

            float x, y, r, c, mx, my;
        public:

            mob_shield_orbAI(Creature* creature) : CreatureAI(creature)
            {
                pInstance = ((InstanceScript*)creature->GetInstanceScript());
            }

            EventMap events;

            void JustDied(Unit* /*killer*/)
            override {
                PointReached = true;
            }
            void Reset()
            override {
                PointReached = true;

                r = 17;
                c = 0;
                checkTimer = 2000;
        
                mx = ShieldOrbLocations[0][0];
                my = ShieldOrbLocations[0][1];

                if (rand()%2)
                    Clockwise = true;
                else
                    Clockwise = false;

                /** FIXME
                if (onSpawn)
                {
                    addEvent(EVENT_SHADOWBOLT_S, 500, 1000, EVENT_FLAG_DELAY_IF_CASTING, true, PhaseMask(phaseMaskForPhase(2) | phaseMaskForPhase(3) | phaseMaskForPhase(4)));
                }
                else
                {
                    resetEvent(EVENT_SHADOWBOLT_S, 500, 1000);
                }
                */

                me->SetFullTauntImmunity(true);
            }

            void AttackStart(Unit* victim)
            override {
                if (!victim)
                    return;

                me->Attack(victim, false);
            }

            void MovementInform(uint32 type, uint32 /*id*/)
            override {
                if(type != POINT_MOTION_TYPE)
                    return;

                PointReached = true;
            }

            void UpdateAI(uint32 const diff)
            override {
                if (pInstance->GetData(DATA_KILJAEDEN_EVENT) == NOT_STARTED)
                {
                    me->DisappearAndDie();
                    return;
                }

                if (PointReached)
                {
                    if (Clockwise)
                    {
                        y = my - r * sin(c);
                        x = mx - r * cos(c);
                    }
                    else
                    {
                        y = my + r * sin(c);
                        x = mx + r * cos(c);
                    }

                    PointReached = false;
                    checkTimer = 1000;

                    me->GetMotionMaster()->MovePoint(1, x, y, SHIELD_ORB_Z);
            
                    c += M_PI/32;
                }
                else
                {
                    if (checkTimer <= diff)
                        PointReached = true;
                    else
                        checkTimer -= diff;
                }

                if (!UpdateVictim())
                    return;

                events.Update(diff);


                while (uint32 eventId = events.ExecuteEvent())
                    switch (eventId)
                    {
                        case 0:
                            break;
                        case EVENT_SHADOWBOLT_S:
                            if (Unit* random = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                if(me->CastSpell(random, SPELL_SHADOW_BOLT, TRIGGERED_NONE) == SPELL_CAST_OK)
                                    events.RescheduleEvent(EVENT_SHADOWBOLT_S, urand(500, 1000));
                            break;
                    }
            }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_shield_orbAI(creature);
    }
};

//AI for Sinister Reflection
class mob_sinster_reflection : public CreatureScript
{
public:
    mob_sinster_reflection() : CreatureScript("mob_sinster_reflection") {}

    class mob_sinster_reflectionAI : public CreatureAI
    {
        private:
            InstanceScript *pInstance;

            uint8 Class;
            uint32 Timer[3];
            bool canAttack;
            Creature *m_kj;
        public:
            mob_sinster_reflectionAI(Creature* creature) : CreatureAI(creature)
            {
                pInstance = ((InstanceScript*)creature->GetInstanceScript());
                m_kj = nullptr;
            }

            EventMap events;

            void Reset()
            override {
                if(pInstance)
                {
                    if (Creature* kj = pInstance->instance->GetCreature(ObjectGuid(pInstance->GetData64(DATA_KILJAEDEN))))
                        m_kj = kj;
                }

                Timer[0] = urand(1000, 4000);
                Timer[1] = urand(1000, 4000);
                Timer[2] = urand(1000, 4000);
                Class = 0;
                canAttack = false;
                events.RescheduleEvent(EVENT_STUN, 4000);

                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);
                me->AddUnitState(UNIT_STATE_STUNNED);

                me->CastSpell(me, 45893, TRIGGERED_FULL_MASK);
            }

            void UpdateAI(uint32 const diff)
            override {
                if (pInstance && pInstance->GetData(DATA_KILJAEDEN_EVENT) == NOT_STARTED)
                {
                    me->DisappearAndDie();
                    return;
                }

                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                    switch (eventId)
                    {
                        case 0:
                            break;
                        case EVENT_STUN:
                            canAttack = true;
                            me->ClearUnitState(UNIT_STATE_STUNNED);
                            if (TempSummon* _me = me->ToTempSummon())
                                if (Unit* summoner = _me->GetSummoner())
                                    me->GetThreatManager().AddThreat(summoner, 2500); //no idea if this is correct
                            events.CancelEvent(EVENT_STUN);
                            break;
                    }

                if (!canAttack)
                    return;

                if (Class == 0)
                {
                    Class = me->GetVictim()->GetClass();
                    switch(Class)
                    {
                        case CLASS_DRUID:
                        case CLASS_HUNTER:
                        case CLASS_MAGE:
                        case CLASS_WARLOCK:
                        case CLASS_PALADIN:
                        case CLASS_PRIEST:
                            break;
                        case CLASS_WARRIOR:
                        case CLASS_SHAMAN:
                        case CLASS_ROGUE:
                            me->SetCanDualWield(true);
                            break;
                    }
                }

                switch (Class)
                {
                    case CLASS_DRUID:
                        if (Timer[0] <= diff)
                        {
                            if (Unit* random = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                                me->CastSpell(random, SPELL_SR_MOONFIRE, TRIGGERED_NONE);
                            Timer[0] = urand(5000, 7000);
                        }
                        break;
                    case CLASS_HUNTER:
                        if (Timer[0] <= diff)
                        {
                            if (Unit *random = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                                me->CastSpell(random, SPELL_SR_MULTI_SHOT, TRIGGERED_NONE);
                            Timer[0] = urand(8000, 10000);
                        }

                        if (Timer[1] <= diff)
                        {
                            if (Unit *random = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                                me->CastSpell(random, SPELL_SR_SHOOT, TRIGGERED_NONE);
                            Timer[1] = urand(4000, 6000);
                        }

                        if (me->IsWithinMeleeRange(me->GetVictim(), 6))
                        {
                            if (Timer[2] <= diff)
                            {
                                me->CastSpell(me->GetVictim(), SPELL_SR_WING_CLIP, TRIGGERED_NONE);
                                Timer[2] = urand(6000, 8000);
                            }
                
                            DoMeleeAttackIfReady();
                        }
                        break;
                    case CLASS_MAGE:
                        if (Timer[0] <= diff)
                        {
                            me->CastSpell(me->GetVictim(), SPELL_SR_FIREBALL, TRIGGERED_NONE);
                            Timer[0] = urand(2000, 4000);
                        }
                        break;
                    case CLASS_WARLOCK:
                        if (Timer[0] <= diff)
                        {
                            me->CastSpell(me->GetVictim(), SPELL_SR_SHADOW_BOLT, TRIGGERED_NONE);
                            Timer[0] = urand(3000, 5000);
                        }

                        if (Timer[1] <= diff)
                        {
                            if (Unit *random = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                                me->CastSpell(random, SPELL_SR_CURSE_OF_AGONY, TRIGGERED_NONE);
                            Timer[1] = urand(15000, 17000);
                        }
                        break;
                    case CLASS_WARRIOR:
                        if (Timer[0] <= diff)
                        {
                            me->CastSpell(me->GetVictim(), SPELL_SR_WHIRLWIND, TRIGGERED_NONE);
                            Timer[0] = urand(9000, 11000);
                        }
                        break;
                    case CLASS_PALADIN:
                        if (Timer[0] <= diff)
                        {
                            me->CastSpell(me->GetVictim(), SPELL_SR_HAMMER_OF_JUSTICE, TRIGGERED_NONE);
                            Timer[0] = urand(9000, 12000);
                        }

                        if (Timer[1] <= diff)
                        {
                            me->CastSpell(me->GetVictim(), SPELL_SR_HOLY_SHOCK, TRIGGERED_NONE);
                            Timer[1] = urand(2000, 4000);
                        }
                        break;
                    case CLASS_PRIEST:
                        if (Timer[0] <= diff)
                        {
                            me->CastSpell(me->GetVictim(), SPELL_SR_HOLY_SMITE, TRIGGERED_NONE);
                            Timer[0] = urand(4000, 6000);
                        }

                        if (Timer[1] <= diff)
                        {
                            me->CastSpell(urand(0, 1) ? me : m_kj,  SPELL_SR_RENEW, TRIGGERED_NONE);
                            Timer[1] = urand(6000, 8000);
                        }
                        break;
                    case CLASS_SHAMAN:
                        if (Timer[0] <= diff)
                        {
                            me->CastSpell(me->GetVictim(), SPELL_SR_EARTH_SHOCK, TRIGGERED_NONE);
                            Timer[0] = urand(4000, 6000);
                        }
                        break;
                    case CLASS_ROGUE:
                        if (Timer[0] <= diff)
                        {
                            me->CastSpell(me->GetVictim(), SPELL_SR_HEMORRHAGE, TRIGGERED_NONE);
                            Timer[0] = urand(4000, 6000);
                        }
                        break;
                }
                if(Class != CLASS_HUNTER) //handled in hunter case
                    DoMeleeAttackIfReady(); 

                for (uint32 & i : Timer)
                    i -= diff;
            }
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new mob_sinster_reflectionAI(creature);
    }
};

void AddSC_boss_kiljaeden_new()
{
    new OrbOfTheBlueFlight();
    new boss_kalecgos_kj();
    new boss_kiljaeden();
    new mob_kiljaeden_controller();
    new mob_hand_of_the_deceiver();
    new mob_felfire_portal();
    new mob_volatile_felfire_fiend();
    new mob_armageddon();
    new mob_shield_orb();
    new mob_sinster_reflection();
}
