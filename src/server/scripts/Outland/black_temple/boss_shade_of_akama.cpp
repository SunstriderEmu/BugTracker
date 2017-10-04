/* TODO : 
- Defender not sensible to aggro until they reach akama
*/

#include "def_black_temple.h"

enum Texts {
    SAY_LOW_HEALTH             =  9, // I will not last much longer...  sound 11385
    SAY_DEATH                  = 10, // No! Not yet... sound 11386
    
    // Ending cinematic texts
    SAY_FREE                   = 11, // Come out from the shadows! I've returned to lead you against our true enemy! Shed your chains and raise your weapons against your Illidari masters!
    SAY_BROKEN_FREE_01         = 12, // Hail our leader! Hail Akama!
    SAY_BROKEN_FREE_02         = 13, // Hail Akama!

    GOSSIP_HELLO               = 393, // Need you to save my people blablabla
    GOSSIP_ITEM                = 394  // Im with you, akama
};

struct Location
{
    float x, y, o, z;
};

// Around akama
static Location ChannelerLocations[]=
{
    {463.161f, 401.220f, 3.142f, 118.540f},
    {457.378f, 391.228f, 2.106f, 118.540f},
    {446.012f, 391.228f, 1.072f, 118.540f},
    {439.534f, 401.227f, 0.000f, 118.540f},
    {446.012f, 411.212f, 5.211f, 118.540f},
    {457.378f, 411.212f, 4.177f, 118.540f}
};

static Location spawnLocations[]=
{
    {498.653f, 461.728f, 0.000f, 113.538f}, // East alcove (left facing shade)
    {498.505f, 339.619f, 0.000f, 113.538f}  // West alcove (right facing shade)
};

static Location AkamaWP[]=
{
    // intro event
    {515.32f,  400.793f, M_PI,  112.784f},
    // outro event
    {482.35f,  401.163f, 0.000f, 112.784f},
    {469.35f,  400.880f, 0.000f, 118.540f}
};

// Brokens summoning coords
static Location BrokenCoords[]=
{
    {541.376f, 401.440f, M_PI  ,  112.784f}, // The place where akama channels
    {534.130f, 352.395f, 2.164f,        112.784f}, // Behind a 'pillar' which is behind the east alcove
    {499.621f, 341.535f, 1.653f,        112.784f}, // East Alcove
    {499.151f, 461.036f, 4.771f,        112.784f}, // West Alcove
};

// Brokens target points
static Location BrokenWP[]=
{
    {492.492f, 400.745f, 3.122f, 112.784f},
    {494.336f, 382.222f, 2.676f, 112.784f},
    {489.556f, 373.507f, 2.416f, 112.784f},
    {491.136f, 427.869f, 3.520f, 112.784f},
};

enum AkamaSpells {
    SPELL_VERTEX_SHADE_BLACK    =    39833,
    SPELL_KNEEL                 =    39656, // wrong spell?

    SPELL_AKAMA_STEALTH         =    34189, // wrong spell
    SPELL_DESTRUCTIVE_POISON    =    40874,
    SPELL_LIGHTNING_BOLT        =    42024,

    SPELL_AKAMA_SOUL_CHANNEL    =    40447, // self stun + dummy aura on target
    SPELL_AKAMA_SOUL_RETRIEVE   =    40902,
    SPELL_AKAMA_SOUL_EXPEL      =    40855,
    
    SPELL_SHADE_SOUL_CHANNEL    =    40401, // aura dummy + trigger SPELL_SHADE_SOUL_CHANNEL_2 (see Aura::HandleAuraDummy, custom handling there)
    SPELL_SHADE_SOUL_CHANNEL_2  =    40520, // descrease speed aura (does stack)
};

enum AkamaTimers {
    TIMER_SUMMON_DEFENDER       =    15000,
    TIMER_SUMMON_PACK           =    35000,
    TIMER_SUMMON_PACK_FIRST     =     5000,
    TIMER_SUMMON_SORCERER       =    25000,
    TIMER_SUMMON_SORCERER_START =     5000,
    
    TIMER_SPELL_LIGHTNING_BOLT  =    10000,

    TIMER_RESET_TIMER           =    30000,
    TIMER_CHANNELER_UPDATE      =     2000,
    TIMER_INTRO_DELAY            =    5000 // delay after akama starts channeling before starting event
};

#define TIMER_SPELL_DESTRUCTIVE_POISON 6000 + rand()%1000

enum AkamaCreatures {
    CREATURE_CHANNELER          =    23421,
    CREATURE_SORCERER           =    23215,
    CREATURE_DEFENDER           =    23216,

    //Creatures pack
    CREATURE_ELEMENTALIST       =    23523,
    CREATURE_ROGUE              =    23318,
    CREATURE_SPIRITBINDER       =    23524,
    
    CREATURE_BROKEN             =    23319,
};

const uint32 spawnPackEntries[]= { CREATURE_ELEMENTALIST, CREATURE_ROGUE, CREATURE_SPIRITBINDER };

enum ChannelerMessages {
    MESSAGE_SHADE_GUID
};

enum ShadeMessages 
{
    MESSAGE_SELECTABLE_CHANNELERS,
    MESSAGE_HAS_KILLED_AKAMA,
    MESSAGE_AKAMA_GUID
};

enum AkamaMessages {
    MESSAGE_BEGIN_EVENT,
    MESSAGE_SHADE_FREE,
    MESSAGE_SHADE_DIED,
};



struct npc_akamaAI;



class boss_shade_of_akama : public CreatureScript
{
public:
    boss_shade_of_akama() : CreatureScript("boss_shade_of_akama")
    { }

    class boss_shade_of_akamaAI : public ScriptedAI
    {
        public:
        boss_shade_of_akamaAI(Creature* c) : 
            ScriptedAI(c), 
            summons(me)
        {
            pInstance = ((InstanceScript*)me->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        std::list<uint64> channelers;
        uint64 akamaGUID;
    
        uint32 summonPackTimer;
        uint32 defenderTimer;       
        uint32 sorcererTimer;
        uint32 waitingForResetTimer; // Reset encounter timer on akama's death
    
        bool isBanished;
        bool waitingForReset;
        SummonList summons;
    
        void MoveInLineOfSight(Unit* /* who */) override {}
    
        // When killed Akama
        void FakeReset()
        {
            // InCombat stays true -- TODO: InCombat variable has been removed, this is probably broken
            waitingForReset = true;
            me->RemoveAllAurasExcept(SPELL_VERTEX_SHADE_BLACK);
            me->DeleteThreatList();
            me->CombatStop();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->GetMotionMaster()->MoveTargetedHome();
            summons.DespawnAll();
            me->SetReactState(REACT_PASSIVE);
            if(pInstance)
                pInstance->SetData(DATA_SHADEOFAKAMAEVENT, NOT_STARTED);
        }
    
        void Reset()
        override {
            waitingForReset = false;
            isBanished = true;
            summons.DespawnAll();
    
            summonPackTimer = TIMER_SUMMON_PACK_FIRST;
            defenderTimer = TIMER_SUMMON_DEFENDER;
            sorcererTimer = TIMER_SUMMON_SORCERER_START;
            waitingForResetTimer = TIMER_RESET_TIMER;
    
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STUN);
    
            if(pInstance && pInstance->GetData(DATA_SHADEOFAKAMAEVENT) != DONE)
                pInstance->SetData(DATA_SHADEOFAKAMAEVENT, NOT_STARTED);
            
            Creature* akama = me->GetMap()->GetCreature(akamaGUID);
            if(akama)
            {
                if(akama->IsInCombat())
                    akama->AI()->EnterEvadeMode();
                else if(akama->IsDead())
                    akama->Respawn();
            }
    
            if(!me->IsDead())
                spawnChannelers();
        }
    
        void JustReachedHome() 
        override {
            spawnChannelers(); // They're still respawn uppon Reset() later but, just for visual
        }
    
        void DamageTaken(Unit* /* done_by */, uint32 &damage)  //just to be sure
        override {
            if(waitingForReset)
            {
                damage = 0;
                EnterEvadeMode();
            }
        }
    
        void JustDied(Unit* killer)
        override {
            if(Creature* akama = me->GetMap()->GetCreature(akamaGUID))
                akama->AI()->message(AkamaMessages::MESSAGE_SHADE_DIED,0);
    
            summons.DespawnAll();
            if(pInstance) pInstance->SetData(DATA_SHADEOFAKAMAEVENT, DONE);
        }
    
        void JustSummoned(Creature *summon) 
        override {
            summons.Summon(summon);
        }
    
        void SummonedCreatureDespawn(Creature *summon) 
        override {
            summons.Despawn(summon);
        }
        
        void KillRemainingChannelers()
        {
            for(auto itr : channelers)
                if(Creature* channeler = me->GetMap()->GetCreature(itr))
                    channeler->DisappearAndDie();
        }
    
        void spawnChannelers()
        {
            me->RemoveAurasDueToSpell(SPELL_SHADE_SOUL_CHANNEL);
            KillRemainingChannelers();
    
            for(auto & ChannelerLocation : ChannelerLocations)
            {
                Creature* channeler = me->SummonCreature(CREATURE_CHANNELER, ChannelerLocation.x, ChannelerLocation.y, ChannelerLocation.z, ChannelerLocation.o, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000);
                if(channeler)
                {
                    channeler->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    channeler->AI()->message(ChannelerMessages::MESSAGE_SHADE_GUID,me->GetGUID());
                    channelers.push_back(channeler->GetGUID());
                }
            }
        }
    
        void SummonCreaturesPack()
        {
            for(auto & spawnLocation : spawnLocations)
            {
                for(uint32 spawnPackEntrie : spawnPackEntries)
                {
                    if(Creature* spawn = me->SummonCreature(spawnPackEntrie, spawnLocation.x, spawnLocation.y, spawnLocation.z, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000))
                    {
                        Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0,100.0f,true);
                        if(target) 
                        {
                            spawn->AI()->AttackStart(target);
                            spawn->AddThreat(target, 500.0f);
                        }
                        if(Creature* akama = me->GetMap()->GetCreature(akamaGUID))
                        {
                            if(!spawn->GetVictim()) //attack him if we haven't found any player to attack
                                spawn->AI()->AttackStart(target);
    
                            spawn->AddThreat(akama,1.0f); //else still put him in threatlist to attack him in case of wipe
                        }
                    }
                }
            }
        }
        
        void SummonSorcerer()
        {
            // Always summoned on akama's left
            Creature* Sorcerer = me->SummonCreature(CREATURE_SORCERER, spawnLocations[1].x, spawnLocations[1].y, spawnLocations[1].z, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000);
            if(Sorcerer)
            {
                Sorcerer->AI()->message(ChannelerMessages::MESSAGE_SHADE_GUID,me->GetGUID());
                Sorcerer->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                channelers.push_back(Sorcerer->GetGUID());
                //avoir channelers packing
                /*
                float x,y,z;
                Sorcerer->GetRandomContactPoint(me,x,y,z,0,20.0f);
                Sorcerer->GetMotionMaster()->MovePoint(0,x,y,z);
                */
            }
        }
    
        void SummonDefender()
        {
            uint32 ran = rand()%2;
            Creature* Defender = me->SummonCreature(CREATURE_DEFENDER, spawnLocations[ran].x, spawnLocations[ran].y, spawnLocations[ran].z, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000);
            if(Defender)
            {
                Defender->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                if(Creature* akama = me->GetMap()->GetCreature(akamaGUID))
                {
                    float x, y, z;
                    akama->GetPosition(x,y,z);
                    Defender->GetMotionMaster()->MovePoint(0, x, y, z);
                    Defender->AI()->AttackStart(akama);
                    Defender->AddThreat(akama, 500.0f);
                }
            }
        }
    
        void SetSelectableChannelers()
        {
            for(auto itr : channelers)
                if(Creature* channeler = me->GetMap()->GetCreature(itr))
                    channeler->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
    
        void RewardRepFromAkamaDeath()
        {
            Creature* akama = me->GetMap()->GetCreature(akamaGUID);
            if(!akama)
                return;
    
            for(auto itr : me->getThreatManager().getThreatList())
            {
                Player* p = ObjectAccessor::GetPlayer(*me,itr->getUnitGuid());
                if(p)
                    p->RewardReputation(akama,1.0f);
            }
        }
    
        uint64 message(uint32 id, uint64 data)
        override {
            switch(id)
            {
            case MESSAGE_SELECTABLE_CHANNELERS:
                SetSelectableChannelers();
                break;
            case MESSAGE_HAS_KILLED_AKAMA:
                FakeReset();
                RewardRepFromAkamaDeath(); // Still reward players with 250 reputation
                break;
            case MESSAGE_AKAMA_GUID:
                akamaGUID = data;
                break;
            }
            return 0;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!me->IsInCombat())
                return;
    
            if(waitingForReset)
            {
                if(waitingForResetTimer < diff)
                {
                    EnterEvadeMode();
                    return;
                } else waitingForResetTimer -= diff;
                return;
            }
    
            if(isBanished)
            {
                if(defenderTimer < diff)
                {
                    SummonDefender();
                    defenderTimer = TIMER_SUMMON_DEFENDER;
                } else defenderTimer -= diff;
    
                if(sorcererTimer < diff)
                {
                    SummonSorcerer();
                    sorcererTimer = TIMER_SUMMON_SORCERER;
                } else sorcererTimer -= diff;
    
                if(summonPackTimer < diff)
                {
                    SummonCreaturesPack();
                    summonPackTimer = TIMER_SUMMON_PACK;
                } else summonPackTimer -= diff;
    
                Creature* akama = me->GetMap()->GetCreature(akamaGUID);
                if(akama && akama->IsAlive())
                {
                    //TC_LOG_INFO("scripts","me->GetDistance2d(akama) = %f", me->GetDistance2d(akama));
                    if(me->GetDistance2d(akama) < NOMINAL_MELEE_RANGE)
                    {
                        KillRemainingChannelers();
                        isBanished = false;
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        akama->AI()->message(AkamaMessages::MESSAGE_SHADE_FREE,0);
                        me->RemoveAurasDueToSpell(SPELL_SHADE_SOUL_CHANNEL_2);// Just to hide it from players
                    }
                }
            } else {
                DoMeleeAttackIfReady();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_shade_of_akamaAI(creature);
    }
};


class mob_ashtongue_channeler : public CreatureScript
{
public:
    mob_ashtongue_channeler() : CreatureScript("mob_ashtongue_channeler")
    { }

    class mob_ashtongue_channelerAI : public ScriptedAI
    {
        public:
        mob_ashtongue_channelerAI(Creature* c) : 
            ScriptedAI(c),
            shadeGUID(0),
            updateTimer(0)
        { }
    
        uint64 shadeGUID;
        uint32 updateTimer;
       
        uint64 message(uint32 id, uint64 data) 
        override {
            if(id == MESSAGE_SHADE_GUID)
                shadeGUID = data;        
                
            return 0;     
        }
    
        bool HasMyStack(Creature* c)
        {
            Aura* myStack = c->GetAuraByCasterSpell(SPELL_SHADE_SOUL_CHANNEL,me->GetGUID());
            if(myStack)
                return true;
            else
                return false;
        }
    
        void RemoveMyStackIfAny(Creature* shade)
        {
            Aura* myStack = shade->GetAuraByCasterSpell(SPELL_SHADE_SOUL_CHANNEL,me->GetGUID());
            if(myStack)
                myStack->SetRemoveMode(AURA_REMOVE_BY_DEFAULT);
        }
    
        void JustDied(Unit* /* killer */)
        override {
            Creature* shade = me->GetMap()->GetCreature(shadeGUID);
            if(shade)
                RemoveMyStackIfAny(shade);
        }
    
        void AttackStart(Unit* /* who */) override {}
    
        void MoveInLineOfSight(Unit* /* who */) override {}
    
        void UpdateAI(const uint32 diff) 
        override {
            if(updateTimer < diff)
            {
                if(!shadeGUID)
                    return;
            
                Creature* shade = me->GetMap()->GetCreature(shadeGUID);
                if(!shade)
                    return;
    
                if(HasMyStack(shade) && me->IsNonMeleeSpellCast(false))
                    return;
    
                me->CastStop();
                RemoveMyStackIfAny(shade);
    
                if(me->GetDistance2d(shade) < 20.0f && me->IsWithinLOSInMap(shade))
                {
                    if(me->isMoving())
                    {
                        me->GetMotionMaster()->Clear(false);
                        me->GetMotionMaster()->MoveIdle();
                    }
                    me->CastSpell(shade, SPELL_SHADE_SOUL_CHANNEL, false);
                } else {
                    if(!me->isMoving())
                        me->GetMotionMaster()->MoveFollow(shade,10.0f,(float)rand()/1000); //random angle to avoid packing
                }
                updateTimer = TIMER_CHANNELER_UPDATE;
            } else updateTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_ashtongue_channelerAI(creature);
    }
};


class mob_ashtongue_sorcerer : public CreatureScript
{
public:
    mob_ashtongue_sorcerer() : CreatureScript("mob_ashtongue_sorcerer")
    { }

    class mob_ashtongue_sorcererAI : public mob_ashtongue_channeler::mob_ashtongue_channelerAI
    {
        public:
        mob_ashtongue_sorcererAI(Creature* c) : mob_ashtongue_channeler::mob_ashtongue_channelerAI(c) {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_ashtongue_sorcererAI(creature);
    }
};


class npc_akama_shade : public CreatureScript
{
public:
    npc_akama_shade() : CreatureScript("npc_akama_shade")
    { }

    class npc_akamaAI : public ScriptedAI
    {
        public:
        npc_akamaAI(Creature* c) : 
            ScriptedAI(c), 
            summons(me)
        {
            pInstance = ((InstanceScript*)me->GetInstanceScript());
            if(pInstance) shadeGUID = pInstance->GetData64(DATA_SHADEOFAKAMA);
        }
    
        InstanceScript* pInstance;
        uint64 shadeGUID;
        
        bool eventBegun; // Players started event
        bool startedMeleeCombat; // shade reached akama
        bool hasYelledLowHealth;
        SummonList summons;
    
        uint32 destructivePoisonTimer;
        uint32 lightningBoltTimer;
    
        uint8 outroProgress;
        uint32 outroWaitTimer;
        uint32 outroTalkCount;    
        bool summoningBrokenEvent;
        uint32 summonBrokenTimer;
        uint32 brokenSummonIndex;
    
        uint8  introProgress;
        uint32 introWaitTimer; // Delay after akama starts channeling before starting event
    
        void Reset()
        override {
            eventBegun = false;
            startedMeleeCombat = false;
            hasYelledLowHealth = false;
            summons.DespawnAll();
    
            destructivePoisonTimer = TIMER_SPELL_DESTRUCTIVE_POISON;
            lightningBoltTimer = TIMER_SPELL_LIGHTNING_BOLT;
            
            me->SetReactState(REACT_PASSIVE);
            me->AI()->SetCombatMovementAllowed(false);
    
            if (pInstance && pInstance->GetData(DATA_SHADEOFAKAMAEVENT) != DONE)
            {
                me->AddAura(SPELL_AKAMA_STEALTH,me);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                
                Creature* shade = me->GetMap()->GetCreature(shadeGUID);
                if(shade)
                {
                    if(shade->IsInCombat())
                        shade->AI()->EnterEvadeMode();
                    else if(shade->IsDead())
                        shade->Respawn();
                }
            } else {
                // Replace on end event final point
                me->Relocate(AkamaWP[2].x, AkamaWP[2].y, AkamaWP[2].z, AkamaWP[2].o);
            }
            
            outroProgress = 0;
            outroWaitTimer = 0;  
            summonBrokenTimer = 0;
            outroTalkCount = 0;
            brokenSummonIndex = 0;
            summoningBrokenEvent = false;
    
            introProgress = 0;
            introWaitTimer = TIMER_INTRO_DELAY;
        }
    
        void JustSummoned(Creature *summon) 
        override {
            summons.Summon(summon);
        }
        void SummonedCreatureDespawn(Creature *summon) 
        override {
            summons.Despawn(summon);
        }
    
        void HealReceived(Unit* /* done_by */, uint32& addhealth)
        override {
            addhealth = 0;
        }
    
        void BeginEvent()
        {
            if(pInstance)
                shadeGUID = pInstance->GetData64(DATA_SHADEOFAKAMA);
    
            if(!shadeGUID)
                return;
    
            Creature* shade = me->GetMap()->GetCreature(shadeGUID);
            if(shade && shade->IsAlive())
            {
                shade->AI()->message(ShadeMessages::MESSAGE_AKAMA_GUID,me->GetGUID());
                pInstance->SetData(DATA_SHADEOFAKAMAEVENT, IN_PROGRESS);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                introProgress = 1; // Start intro
            }
        }
    
        void JustDied(Unit* /* killer */)
        override {
            me->Yell(SAY_DEATH);
            Creature* shade = me->GetMap()->GetCreature(shadeGUID);
            if(shade && shade->IsAlive())
                shade->AI()->message(ShadeMessages::MESSAGE_HAS_KILLED_AKAMA,0);
            summons.DespawnAll();
        }
    
        uint64 message(uint32 id, uint64 data) 
        override { 
            switch(id)
            {
            case MESSAGE_BEGIN_EVENT:
                BeginEvent();
                break;
            case MESSAGE_SHADE_FREE:
                me->InterruptNonMeleeSpells(false);
                startedMeleeCombat = true;
                break;
            case MESSAGE_SHADE_DIED:
                me->InterruptNonMeleeSpells(false);
                me->SetReactState(REACT_PASSIVE);
                outroProgress = 1;
                break;
            default:
                break;
            }
    
            return 0;     
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!eventBegun)
            {
                HandleIntro(diff);
                return;
            }
    
            if ((me->GetHealthPct()) < 15 && !hasYelledLowHealth)
            {
                DoScriptText(SAY_LOW_HEALTH, me);
                hasYelledLowHealth = true;
            }
    
            HandleOutro(diff);
    
            if(!startedMeleeCombat || !me->GetVictim())
                return;
    
            if(destructivePoisonTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_DESTRUCTIVE_POISON);
                destructivePoisonTimer = TIMER_SPELL_DESTRUCTIVE_POISON;
            } else destructivePoisonTimer -= diff;
    
            if(lightningBoltTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_LIGHTNING_BOLT);
                lightningBoltTimer = TIMER_SPELL_LIGHTNING_BOLT;
            } else lightningBoltTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    
        void HandleIntro(const uint32 diff)
        {
            switch(introProgress)
            {
            default:
            case 0: // Intro not started or waiting for MovementInform to resume
                break;
    
            case 1: // Going to the middle of the hall
                {
                me->RemoveAurasDueToSpell(SPELL_AKAMA_STEALTH);
                me->GetMotionMaster()->MovePoint(0, AkamaWP[0].x, AkamaWP[0].y, AkamaWP[0].z);
                introProgress = 0; // This is re set to 2 in MovementInform when point reached
                }
                break;
            
            case 2: // Begining to cast & init fight
                {
                if (Creature* shade = me->GetMap()->GetCreature(shadeGUID))
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    shade->SetReactState(REACT_AGGRESSIVE);
                    DoZoneInCombat(shade);
                    AttackStart(shade,false);
                    shade->AI()->AttackStart(me);
                    me->AddThreat(shade, 10000000.0f);
                    shade->AddThreat(me, 10000000.0f);
                    DoCast(shade, SPELL_AKAMA_SOUL_CHANNEL);
                } else { Reset(); return; }
                introProgress++;
                }
                break;
    
            case 3: // After 5 sec of channeling, start fight
                if(introWaitTimer < diff)
                {
                    eventBegun = true;
                    Creature* shade = me->GetMap()->GetCreature(shadeGUID);
                    if (shade) shade->AI()->message(ShadeMessages::MESSAGE_SELECTABLE_CHANNELERS,0);
                    introProgress = 0; // Intro end
                } else introWaitTimer -= diff;
                break;
    
            }
        }
            
        void HandleOutro(const uint32 diff)
        {
            if(summoningBrokenEvent)
            {
                if(summonBrokenTimer <= diff)
                {
                    for(uint8 i = 0; i < 4; ++i)
                    {
                        float x = BrokenCoords[brokenSummonIndex].x + (i*5);
                        float y = BrokenCoords[brokenSummonIndex].y + (1*5);
                        float z = BrokenCoords[brokenSummonIndex].z;
                        float o = BrokenCoords[brokenSummonIndex].o;
                        Creature* Broken = me->SummonCreature(CREATURE_BROKEN, x, y, z, o, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 360000);
                        if(Broken)
                        {
                            float wx = BrokenWP[brokenSummonIndex].x + (i*5);
                            float wy = BrokenWP[brokenSummonIndex].y + (i*5);
                            float wz = BrokenWP[brokenSummonIndex].z;
                            Broken->GetMotionMaster()->MovePoint(0, wx, wy, wz);
                            Broken->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        }
                    }
                    brokenSummonIndex++;
                    summonBrokenTimer = 1000;
                } else summonBrokenTimer -= diff;
    
                if(brokenSummonIndex == 4)
                    summoningBrokenEvent = false;
            }
    
            if(outroWaitTimer >= diff)
            {
                outroWaitTimer -= diff;
                return;
            }
    
            switch(outroProgress)
            {
            default:
            case 0: // Not started or waiting for MovementInform to resume
                break;
    
            case 1:
                me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
                me->GetMotionMaster()->MovePoint(1, AkamaWP[1].x, AkamaWP[1].y, AkamaWP[1].z);
                outroProgress = 0; // This is re set to 2 in MovementInform when point reached
                break;
    
            case 2:
                me->GetMotionMaster()->MovePoint(2, AkamaWP[2].x, AkamaWP[2].y, AkamaWP[2].z);
                outroProgress = 0; // This is re set to 3 in MovementInform when point reached
                break;
    
            case 3:
                outroWaitTimer = 1500;
                outroProgress++;
                break;
    
            case 4:
                if(Creature* shade = me->GetMap()->GetCreature(shadeGUID))
                {
                    me->SetUInt64Value(UNIT_FIELD_TARGET, shadeGUID);
                    DoCast(shade, SPELL_AKAMA_SOUL_RETRIEVE,true);
                    outroWaitTimer = 16000; // SPELL_AKAMA_SOUL_RETRIEVE duration + 1000
                }
                outroProgress++;
                break;
    
            case 5:
                me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                summoningBrokenEvent = true;
                outroWaitTimer = 2000;
                outroProgress++;
                break;
    
            case 6:
                DoScriptText(SAY_FREE, me);
                outroWaitTimer = 25000;
                outroProgress++;
                break;
    
            case 7:
                {
                bool Yelled = false;
                for(auto itr : summons)
                    if(Creature* c = me->GetMap()->GetCreature(itr))
                    {
                        if(!Yelled)
                        {
                            DoScriptText(SAY_BROKEN_FREE_01, c);
                            Yelled = true;
                        }
                        c->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
                    }
                outroProgress++;
                outroWaitTimer = 1500;
                }
                break;
    
            case 8:
                for(auto itr : summons)
                    if(Creature* c = me->GetMap()->GetCreature(itr))
                        c->CastSpell(c, SPELL_KNEEL, true);
    
                outroProgress++;
                outroWaitTimer = 5000;
                break;
    
            case 9:
                bool firstSkipped = false; // The first one made the call !
                for(auto itr : summons)
                    if(Creature* c = me->GetMap()->GetCreature(itr))
                    {
                        if(firstSkipped)
                            c->Yell(SAY_BROKEN_FREE_02);
                        else
                            firstSkipped = true;
                    }
                outroProgress = 0; // Outro end
                break;
    
            }
        }
    
        void MovementInform(uint32 type, uint32 id)
        override {
            if(type != POINT_MOTION_TYPE)
                return;
    
            switch(id)
            {
            case 0: introProgress = 2; break; //HandleIntro case 1 point reached
            case 1: outroProgress = 2; break; //HandleOutro case 1 point reached
            case 2: outroProgress = 3; break; //HandleOutro case 2 point reached
            }
        }

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM_TEXTID( 0, (int)GOSSIP_ITEM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_HELLO, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF + 1) // Fight time !
            {
                player->CLOSE_GOSSIP_MENU();
                me->AI()->message(AkamaMessages::MESSAGE_BEGIN_EVENT,0);
            }

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_akamaAI(creature);
    }
};




void AddSC_boss_shade_of_akama()
{
    new boss_shade_of_akama();

    new mob_ashtongue_channeler();

    new mob_ashtongue_sorcerer();

    new npc_akama_shade();
}

