/* Missing timer!
*/

#include "blood_furnace.h"

#define SAY_AGGRO               -1542008

enum Spells
{
    SPELL_SLIME_SPRAY           = 30913,
    SPELL_SLIME_SPRAY_H         = 38458,
    SPELL_POISON_CLOUD          = 30916,
    SPELL_POISON_BOLT           = 30917,
    SPELL_POISON_BOLT_H         = 38459,

    SPELL_POISON_CLOUD_PASSIVE  = 30914,
};

struct Prisoner
{
    Prisoner(Position pos, uint32 entry)
        : pos(pos), entry(entry)
    { }

    Position pos;
    uint32 entry;
};

enum Events
{
    EVENT_SLIME_SPRAY = 1,
    EVENT_POISON_BOLT,
    EVENT_POISON_CLOUD,
};

class boss_broggok : public CreatureScript
{
public:
    boss_broggok() : CreatureScript("boss_broggok")
    { }

    class boss_broggokAI : public BossAI
    {
        //mobs are probably wrong, from what I read there a 3 mobs on the two first, and 4 on the two last.
        //there is at always one 17429 after first cell
        std::vector<Prisoner> const prisonnersCell1 =
        {
            { Prisoner({ 502.64f, 112.954f, 9.66f, 2.33f }, NPC_PRISONER) },
            { Prisoner({ 502.63f, 116.706f, 9.66f, 3.97f }, NPC_PRISONER) },
            { Prisoner({ 498.78f, 116.599f, 9.66f, 5.44f }, NPC_PRISONER) },
            { Prisoner({ 498.35f, 112.381f, 9.66f, 0.63f }, NPC_PRISONER) },
        };

        std::vector<Prisoner> const prisonnersCell2 =
        {
            { Prisoner({ 409.11f, 112.17f, 9.66f, 1.19f }, NPC_PRISONER) },
            { Prisoner({ 411.02f, 117.18f, 9.66f, 4.41f }, NPC_PRISONER) },
            { Prisoner({ 407.17f, 115.17f, 9.66f, 0.01f }, NPC_PRISONER) },
            { Prisoner({ 413.39f, 114.31f, 9.66f, 3.02f }, NPC_FEL_ORC_NEOPHYTE) },
        };

        std::vector<Prisoner> const prisonnersCell3 =
        {
            { Prisoner({ 498.06f,  86.54f, 9.66f, 5.42f }, NPC_PRISONER) },
            { Prisoner({ 499.08f,  82.68f, 9.66f, 1.36f }, NPC_PRISONER) },
            { Prisoner({ 501.71f,  85.96f, 9.66f, 3.76f }, NPC_FEL_ORC_NEOPHYTE) },
        };

        std::vector<Prisoner> const prisonnersCell4 =
        {
            { Prisoner({ 410.76f,  86.12f, 9.66f, 4.94f }, NPC_PRISONER) },
            { Prisoner({ 409.22f,  83.29f, 9.66f, 0.14f }, NPC_PRISONER) },
            { Prisoner({ 413.18f,  83.60f, 9.66f, 2.85f }, NPC_FEL_ORC_NEOPHYTE) },
        };

        public:
        boss_broggokAI(Creature* creature) : BossAI(creature, DATA_BROGGOK)
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
        
        enum EventPhase
        {
            PHASE_NOT_STARTED = 0,
            PHASE_DOOR1,
            PHASE_DOOR2,
            PHASE_DOOR3,
            PHASE_DOOR4,
            PHASE_BOSS,
        };

        uint32 eventPhaseTimer; //Max time for players to clean a cell before sending next mobs. Only on heroic
        
        bool HeroicMode;
        EventPhase prisonPhase = PHASE_NOT_STARTED; //0 is not started, 1/2/3/4 are doors, 5 is boss
        
        std::vector<ObjectGuid> prisonnersGUID[4];

        void SpawnPrisonners(std::vector<Prisoner> prisonners, std::vector<ObjectGuid>& container)
        {
            container.clear();
            for (auto p : prisonners)
                if (Creature* prisoner = me->SummonCreature(p.entry, p.pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5 * MINUTE * IN_MILLISECONDS))
                {
                    container.push_back(prisoner->GetGUID());
                    prisoner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    prisoner->SetImmuneToAll(true);
                    summons.Summon(prisoner);
                }
        }

        void ResetPrisonners()
        {
            summons.DespawnAll();
            SpawnPrisonners(prisonnersCell1, prisonnersGUID[0]);
            SpawnPrisonners(prisonnersCell2, prisonnersGUID[1]);
            SpawnPrisonners(prisonnersCell3, prisonnersGUID[2]);
            SpawnPrisonners(prisonnersCell4, prisonnersGUID[3]);
        }

        void Reset() override
        {
            StartPhase(PHASE_NOT_STARTED);
            eventPhaseTimer = 0;

            _Reset(); //reset all doors and levers in InstanceScript
            ResetPrisonners();
        }
    
        void JustEngagedWith(Unit *who) override
        {
            DoScriptText(SAY_AGGRO, me);
    
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            _JustEngagedWith();

            events.ScheduleEvent(EVENT_SLIME_SPRAY, 10000);
            events.ScheduleEvent(EVENT_POISON_BOLT, 7000);
            events.ScheduleEvent(EVENT_POISON_CLOUD, 5000);
        }
        
        void EnterEvadeMode(EvadeReason /* why */) override
        {
            me->RemoveAllAuras();
            me->GetThreatManager().ClearAllThreat();
            me->CombatStop(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            Reset();
    
            if (!me->IsAlive())
                return;    
    
            instance->SetBossState(DATA_BROGGOK, FAIL);
            float fRespX, fRespY, fRespZ;
            me->GetRespawnPosition(fRespX, fRespY, fRespZ);
            me->GetMotionMaster()->MovePoint(0, fRespX, fRespY, fRespZ);
        }
    
        void MovementInform(uint32 uiMotionType, uint32 uiPointId) override 
        {
            if (uiMotionType == POINT_MOTION_TYPE) 
            {
                if (GameObject* pFrontDoor = me->FindNearestGameObject(GO_PRISON_DOOR_04, 60.0f))
                {
                    me->SetOrientation(me->GetAngle(pFrontDoor->GetPositionX(), pFrontDoor->GetPositionY()));
                    me->SendMovementFlagUpdate();
                }
            }
        }

        void JustSummoned(Creature* summoned) override
        {
            if (summoned->GetEntry() == NPC_BROGGOK_POISON_CLOUD)
            {
                summoned->SetReactState(REACT_PASSIVE);
                summoned->CastSpell(summoned, SPELL_POISON_CLOUD_PASSIVE, true);
                summons.Summon(summoned);
            }
        }
        void UpdateAI(const uint32 diff) override
        {
            events.Update(diff);

            UpdateEvent(diff); 

            if (!UpdateVictim())
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                ExecuteEvent(eventId);
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
            }

            DoMeleeAttackIfReady();
        }

        void ExecuteEvent(uint32 eventId) override
        {
            switch (eventId)
            {
            case EVENT_SLIME_SPRAY:
                DoCastVictim(HeroicMode ? SPELL_SLIME_SPRAY_H : SPELL_SLIME_SPRAY);
                events.ScheduleEvent(EVENT_SLIME_SPRAY, urand(4000, 12000));
                break;
            case EVENT_POISON_BOLT:
                DoCastVictim(HeroicMode ? SPELL_POISON_BOLT_H : SPELL_POISON_BOLT);
                events.ScheduleEvent(EVENT_POISON_BOLT, urand(4000, 12000));
                break;
            case EVENT_POISON_CLOUD:
                DoCast(me, SPELL_POISON_CLOUD);
                events.ScheduleEvent(EVENT_POISON_CLOUD, 15000);
                break;
            default:
                break;
            }
        } 

        void DoAction(int32 action) override
        {
            switch (action)
            {
            case ACTION_START_EVENT:
                if (prisonPhase != PHASE_NOT_STARTED)
                    return;

                StartPhase(PHASE_DOOR1);
                break;
            }
        }

        void SendCellAttackers(std::vector<ObjectGuid>& attackers)
        {
            for (auto itr : attackers)
                if (Creature* prisoner = me->GetMap()->GetCreature(itr))
                {
                    prisoner->AI()->DoZoneInCombat();
                    prisoner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    prisoner->SetImmuneToAll(false);
                    prisoner->AI()->DoZoneInCombat();
                }
        }

        void HandleStartPhase(std::vector<ObjectGuid>& attackers, BFDataTypes door)
        {
            eventPhaseTimer = HeroicMode ? 2 * MINUTE * IN_MILLISECONDS : 0;
            instance->SetData(DATA_ACTIVATE_CELL, door);
            SendCellAttackers(attackers);
        }

        void StartPhase(EventPhase phase)
        {
            switch (phase)
            {
            case PHASE_NOT_STARTED:
                eventPhaseTimer = 0;
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetImmuneToAll(true);
                break;
            case PHASE_DOOR1:
                HandleStartPhase(prisonnersGUID[0], DATA_PRISON_CELL5);
                break;
            case PHASE_DOOR2:
                HandleStartPhase(prisonnersGUID[1], DATA_PRISON_CELL6);
                break;
            case PHASE_DOOR3:
                HandleStartPhase(prisonnersGUID[2], DATA_PRISON_CELL7);
                break;
            case PHASE_DOOR4:
                HandleStartPhase(prisonnersGUID[3], DATA_PRISON_CELL8);
                break;
            case PHASE_BOSS:
                instance->SetData(DATA_ACTIVATE_CELL, DATA_DOOR_4);
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->AI()->DoZoneInCombat();
                me->SetImmuneToAll(false);
                return;
            }
            prisonPhase = phase;
        }

        bool CellPackCleaned(std::vector<ObjectGuid>& attackers) const
        {
            for (auto itr : attackers)
                if (Creature* prisoner = me->GetMap()->GetCreature(itr))
                    if (prisoner->IsAlive())
                        return false;

            return true;
        }

        void CheckWipe()
        {
            bool inCombatPlayer = false;
            Map::PlayerList const& players = me->GetMap()->GetPlayers();
            for (const auto& player : players)
            {
                if (Player* plr = player.GetSource()) {
                    if (plr->IsInCombat())
                    {
                        inCombatPlayer = true;
                        break;
                    }
                }
            }
            if (!inCombatPlayer)
            {
                EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
                instance->SetBossState(DATA_BROGGOK, NOT_STARTED);
            }
        }

        //return true if timer expired
        bool UpdatePhaseTimer(uint32 diff)
        {
            if (!eventPhaseTimer) //no timer active
                return false;

            if (eventPhaseTimer < diff)
            {
                eventPhaseTimer = 0;
                return true;
            }
            else
                eventPhaseTimer -= diff;

            return false;
        }

        void HandleUpdateEvent(std::vector<ObjectGuid>& pack, EventPhase nextPhase, uint32 diff)
        {
            if (CellPackCleaned(pack) || UpdatePhaseTimer(diff))
                StartPhase(nextPhase);
            else
                CheckWipe();
        }

        void UpdateEvent(uint32 diff)
        {
            switch (prisonPhase)
            {
            case PHASE_NOT_STARTED:
                return;
            case PHASE_DOOR1:
                HandleUpdateEvent(prisonnersGUID[0], PHASE_DOOR2, diff);
                break;
            case PHASE_DOOR2:
                HandleUpdateEvent(prisonnersGUID[1], PHASE_DOOR3, diff);
                break;
            case PHASE_DOOR3:
                HandleUpdateEvent(prisonnersGUID[2], PHASE_DOOR4, diff);
                break;
            case PHASE_DOOR4:
                HandleUpdateEvent(prisonnersGUID[3], PHASE_BOSS, diff);
                break;
            case PHASE_BOSS:
                return;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetBloodFurnaceAI<boss_broggokAI>(creature);
    }
};


/*######
## mob_nascent_orc
######*/

#define SPELL_BLOW     22427
#define SPELL_STOMP    31900


class mob_nascent_orc : public CreatureScript
{
public:
    mob_nascent_orc() : CreatureScript("mob_nascent_orc")
    { }

    class mob_nascent_orcAI : public ScriptedAI
    {
        public:
        mob_nascent_orcAI(Creature *c) : ScriptedAI(c)
        { }
    
        uint32 Blow_Timer;
        uint32 Stomp_Timer;
    
        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetUnitMovementFlags(MOVEMENTFLAG_NONE);
            Blow_Timer = 4000 + rand()%4000;
            Stomp_Timer = 5000 + rand()%4000;
        }
    
        void MovementInform(uint32 uiMotionType, uint32 uiPointId) override
        {
            if (uiMotionType == POINT_MOTION_TYPE)
            {
                if (Unit *pTarget = me->SelectNearestTarget(99.0f))
                {
                    me->AI()->AttackStart(pTarget);
                }
           }
        }
    
        void EnterEvadeMode(EvadeReason /* why */) override
        {
            me->GetThreatManager().ClearAllThreat();
            me->CombatStop(true);
            me->GetMotionMaster()->MoveTargetedHome();
            Reset();
        }
    
        void UpdateAI(const uint32 diff) override
        {
            if (!UpdateVictim())
                return;
    
            if (Blow_Timer <= diff)
            {
                DoCast(me->GetVictim(),SPELL_BLOW);
                Blow_Timer = 10000+rand()%4000;
            } else Blow_Timer -=diff;
    
            if (Stomp_Timer <= diff)
            {
                DoCast(me->GetVictim(),SPELL_STOMP);
                Stomp_Timer = 15000+rand()%4000;
            } else Stomp_Timer -=diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetBloodFurnaceAI<mob_nascent_orcAI>(creature);
    }
};

/*######
## mob_fel_orc_neophyte
######*/

#define SPELL_CHARGE    22120
#define SPELL_FRENZY    8269


class mob_fel_orc_neophyte : public CreatureScript
{
public:
    mob_fel_orc_neophyte() : CreatureScript("mob_fel_orc_neophyte")
    { }

    class mob_fel_orc_neophyteAI : public ScriptedAI
    {
        public:
        mob_fel_orc_neophyteAI(Creature *c) : ScriptedAI(c)
        {
        }
    
        uint32 ChargeTimer;
        
        bool Frenzy;
    
        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetUnitMovementFlags(MOVEMENTFLAG_NONE);
            ChargeTimer = 8000;
        }
        
        void MovementInform(uint32 uiMotionType, uint32 uiPointId) override
        {
            if (uiMotionType == POINT_MOTION_TYPE)
            {
                if (Unit *pTarget = me->SelectNearestTarget(99.0f))
                {
                    me->AI()->AttackStart(pTarget);
                }
           }
        }
    
        void EnterEvadeMode(EvadeReason /* why */) override
        {
            me->GetThreatManager().ClearAllThreat();
            me->CombatStop(true);
            me->GetMotionMaster()->MoveTargetedHome();
            Reset();
        }
    
        void UpdateAI(const uint32 diff) override 
        {
            if (!UpdateVictim())
                return;
    
            if (ChargeTimer <= diff) 
            {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0, true, true), SPELL_CHARGE);
                ChargeTimer = 25000 + rand()+5000;
            }
            else
                ChargeTimer -= diff;
                
            if (!Frenzy && me->IsBelowHPPercent(30)) 
            {
                DoCast(me, SPELL_FRENZY);
                Frenzy = true;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetBloodFurnaceAI<mob_fel_orc_neophyteAI>(creature);
    }
};

/*######
## mob_broggok_poisoncloud
######*/

#define SPELL_POISON      30914
#define SPELL_POISON_H    38462

class mob_broggok_poisoncloud : public CreatureScript
{
public:
    mob_broggok_poisoncloud() : CreatureScript("mob_broggok_poisoncloud")
    { }

    class mob_broggok_poisoncloudAI : public ScriptedAI
    {
        public:
        mob_broggok_poisoncloudAI(Creature *c) : ScriptedAI(c)
        { }
    
        void Reset() override
        {
            DoCast(me, me->GetMap()->IsHeroic() ? SPELL_POISON_H : SPELL_POISON);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetBloodFurnaceAI<mob_broggok_poisoncloudAI>(creature);
    }
};

void AddSC_boss_broggok()
{
    new boss_broggok();
    new mob_nascent_orc();
    new mob_fel_orc_neophyte();
    new mob_broggok_poisoncloud();
}