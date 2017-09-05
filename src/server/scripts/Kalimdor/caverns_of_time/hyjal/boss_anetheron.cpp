

#include "def_hyjal.h"
#include "hyjal_trash.h"

enum Spells
{
    SPELL_CARRION_SWARM  = 31306,
    SPELL_SLEEP          = 31298,
    SPELL_VAMPIRIC_AURA  = 38196,
    SPELL_INFERNO        = 31299
};

enum Timers
{
    TIMER_INFERNO             = 50000,
    TIMER_INFERNO_START       = 20000,
    TIMER_SLEEP               = 20000,
    TIMER_CARRION_SWARM       = 15000,
    TIMER_CARRION_SWARM_FIRST = 25000
};

enum Texts {
    SAY_ONDEATH = -1801010,
    SAY_ONSLAY1 = -1801011,
    SAY_ONSLAY2 = -1801012,
    SAY_ONSLAY3 = -1801013,
    SAY_SWARM1 = -1801014,
    SAY_SWARM2 = -1801015,
    SAY_SLEEP1 = -1801016,
    SAY_SLEEP2 = -1801017,
    SAY_INFERNO1 = -1801018,
    SAY_INFERNO2 = -1801019,
    SAY_ONAGGRO = -1801020
};


class boss_anetheron : public CreatureScript
{
public:
    boss_anetheron() : CreatureScript("boss_anetheron")
    { }

    class boss_anetheronAI : public hyjal_trashAI
    {
        public:
        boss_anetheronAI(Creature *c) : hyjal_trashAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            go = false;
            pos = 0;
        }
    
        uint32 SwarmTimer;
        uint32 SleepTimer;
        uint32 InfernoTimer;
        bool go;
        uint32 pos;
    
        void Reset()
        override {
            damageTaken = 0;
            SwarmTimer = TIMER_CARRION_SWARM_FIRST;
            SleepTimer = TIMER_SLEEP;
            InfernoTimer = TIMER_INFERNO_START;
    
            DoCast(me, SPELL_VAMPIRIC_AURA,true);
    
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_ANETHERONEVENT, NOT_STARTED);
        }
    
        void EnterCombat(Unit *who) override
        {
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_ANETHERONEVENT, IN_PROGRESS);
    
            DoScriptText(SAY_ONAGGRO,me);
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(SAY_ONSLAY1 - rand()%3,me);
        }
    
        void WaypointReached(uint32 i)
        override {
            pos = i;
            if (i == 7 && pInstance)
            {
                Unit* target = ObjectAccessor::GetUnit((*me), pInstance->GetData64(DATA_JAINAPROUDMOORE));
                if (target && target->IsAlive())
                    me->AddThreat(target,0.0);
            }
        }
    
        void JustDied(Unit *victim)
        override {
            hyjal_trashAI::JustDied(victim);
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_ANETHERONEVENT, DONE);
    
            DoScriptText(SAY_ONDEATH,me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (IsEvent)
            {
                //Must update npc_escortAI
                npc_escortAI::UpdateAI(diff);
                if(!go)
                {
                    go = true;
                    if(pInstance)
                    {
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(0, 4896.08,    -1576.35,    1333.65);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(1, 4898.68,    -1615.02,    1329.48);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(2, 4907.12,    -1667.08,    1321.00);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(3, 4963.18,    -1699.35,    1340.51);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(4, 4989.16,    -1716.67,    1335.74);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(5, 5026.27,    -1736.89,    1323.02);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(6, 5037.77,    -1770.56,    1324.36);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(7, 5067.23,    -1789.95,    1321.17);
                        ((npc_escortAI*)(me->AI()))->Start(false, true, true);
                        ((npc_escortAI*)(me->AI()))->SetDespawnAtEnd(false);
                    }
                }
            }
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            if(SwarmTimer < diff)
            {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,100,true);
                if(target && DoCast(target,SPELL_CARRION_SWARM) == SPELL_CAST_OK)
                {
                    SwarmTimer = TIMER_CARRION_SWARM;
                    DoScriptText(SAY_SWARM1 - rand()%2,me);
                }
            }else SwarmTimer -= diff;
    
            if(SleepTimer < diff)
            {
                for(uint8 i=0;i<3;++i)
                {
                    Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,100,true);
                    if(target)
                        target->CastSpell(target,SPELL_SLEEP,true);
                }
                SleepTimer = TIMER_SLEEP;
                DoScriptText(SAY_SLEEP1 - rand()%2,me);
            }else SleepTimer -= diff;
    
            if(InfernoTimer < diff)
            {
                if(DoCast(SelectTarget(SELECT_TARGET_RANDOM,0,100,true), SPELL_INFERNO) == SPELL_CAST_OK)
                {
                    InfernoTimer = TIMER_INFERNO;
                    DoScriptText(SAY_INFERNO1 - rand()%2,me);
                }
            }else InfernoTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_anetheronAI(creature);
    }
};


enum InfernoSpells
{
    SPELL_IMMOLATION     = 31303,
    SPELL_INFERNO_EFFECT = 31302
};

enum InfernoTimers
{
    TIMER_IMMOLATION     = 2000
};


class mob_towering_infernal : public CreatureScript
{
public:
    mob_towering_infernal() : CreatureScript("mob_towering_infernal")
    { }

    class mob_towering_infernalAI : public ScriptedAI
    {
        public:
        mob_towering_infernalAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            if(pInstance)
                AnetheronGUID = pInstance->GetData64(DATA_ANETHERON);
        }
    
        uint32 ImmolationTimer;
        uint32 CheckTimer;
        uint64 AnetheronGUID;
        InstanceScript* pInstance;
    
        void Reset() override
        {
            DoCast(me, SPELL_INFERNO_EFFECT);
            ImmolationTimer = TIMER_IMMOLATION;
            CheckTimer = 5000;
        }
    
        void KilledUnit(Unit *victim) override
        {
    
        }
    
        void JustDied(Unit *victim) override
        {
    
        }
    
        void MoveInLineOfSight(Unit *who) override
        {
            if (me->GetDistance(who) <= 50 && !me->IsInCombat() && me->IsHostileTo(who))
            {
                me->AddThreat(who,0.0);
                me->Attack(who,false);
            }
        }
    
        void UpdateAI(const uint32 diff) override
        {
            if(CheckTimer < diff)
            {
                if(AnetheronGUID)
                {
                    Creature* boss = ObjectAccessor::GetCreature((*me),AnetheronGUID);
                    if(!boss || (boss && boss->IsDead()))
                    {
                        me->DespawnOrUnsummon();
                        return;
                    }
                }
                CheckTimer = 5000;
            }else CheckTimer -= diff;
    
            //Return since we have no target
            if (!UpdateVictim())
                return;
    
            if(ImmolationTimer < diff)
            {
                DoCast(me, SPELL_IMMOLATION);
                ImmolationTimer = TIMER_IMMOLATION;
            }else ImmolationTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_towering_infernalAI(creature);
    }
};


void AddSC_boss_anetheron()
{
    new boss_anetheron();

    new mob_towering_infernal();
}
