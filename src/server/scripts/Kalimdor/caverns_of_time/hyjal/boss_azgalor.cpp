
#include "def_hyjal.h"
#include "hyjal_trash.h"

enum Spells
{
    SPELL_RAIN_OF_FIRE      = 31340,
    SPELL_DOOM              = 31347,
    SPELL_HOWL_OF_AZGALOR   = 31344,
    SPELL_CLEAVE            = 31345,
    SPELL_BERSERK           = 26662,
};

enum Timers
{
    TIMER_BERSERK            = 600000,
    TIMER_DOOM               = 45000,
    TIMER_CLEAVE             = 5000,
    TIMER_HOWL_OF_AZGALOR    = 15000,
    TIMER_RAIN_OF_FIRE       = 13000,
    TIMER_RAIN_OF_FIRE_FIRST = 30000,
};

enum Texts
{
    SAY_ONDEATH = -1801022,
    SAY_ONSLAY1 = -1801023,
    SAY_ONSLAY2 = -1801024,
    SAY_ONSLAY3 = -1801025,
    SAY_DOOM1 = -1801026,
    SAY_DOOM2 = -1801027,
    SAY_ONAGGRO = -1801028
};


class boss_azgalor : public CreatureScript
{
public:
    boss_azgalor() : CreatureScript("boss_azgalor")
    { }

    class boss_azgalorAI : public hyjal_trashAI
    {
        public:
        boss_azgalorAI(Creature *c) : hyjal_trashAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            go = false;
            pos = 0;
        }
    
        uint32 RainTimer;
        uint32 DoomTimer;
        uint32 HowlTimer;
        uint32 CleaveTimer;
        uint32 EnrageTimer;
    
        bool go;
        uint32 pos;
    
        void Reset() override
        {
            damageTaken = 0;
            RainTimer = TIMER_RAIN_OF_FIRE_FIRST;
            DoomTimer = TIMER_DOOM;
            HowlTimer = TIMER_HOWL_OF_AZGALOR;
            CleaveTimer = TIMER_CLEAVE;
            EnrageTimer = TIMER_BERSERK;
    
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_AZGALOREVENT, NOT_STARTED);
        }
    
        void JustEngagedWith(Unit *who) override
        {
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_AZGALOREVENT, IN_PROGRESS);
    
            DoScriptText(SAY_ONAGGRO,me);
        }
    
        void KilledUnit(Unit *victim) override
        {
            DoScriptText(SAY_ONSLAY1 - rand()%3,me);
        }
    
        void WaypointReached(uint32 i, uint32 pathID) override
        {
            pos = i;
            if (i == 7 && pInstance)
            {
                Unit* target = ObjectAccessor::GetUnit((*me), pInstance->GetData64(DATA_THRALL));
                if (target && target->IsAlive())
                    me->GetThreatManager().AddThreat(target,0.0);
            }
        }
    
        void JustDied(Unit *victim)
        override {
            hyjal_trashAI::JustDied(victim);
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_AZGALOREVENT, DONE);
    
            DoScriptText(SAY_ONDEATH,me);
        }
    
        bool HasTwoPlayersInFront()
        {
            uint8 playersInArc = 0;
            std::list<HostileReference*> const& threatlist = me->GetThreatManager().getThreatList();
    
            for (auto itr : threatlist)
            {
                Unit* unit = itr->getTarget();
                if  (   unit->ToPlayer()
                    && me->GetDistance2d(unit) < 8.0f
                    && me->HasInArc(M_PI,unit)
                    )
                    playersInArc++;
    
                if(playersInArc > 1)
                    return true;
            }
    
            return false;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (IsEvent)
            {
                //Must update EscortAI
                EscortAI::UpdateAI(diff);
                if(!go)
                {
                    go = true;
                    if(pInstance)
                    {
                        ((EscortAI*)(me->AI()))->AddWaypoint(0, 5492.91,    -2404.61,    1462.63);
                        ((EscortAI*)(me->AI()))->AddWaypoint(1, 5531.76,    -2460.87,    1469.55);
                        ((EscortAI*)(me->AI()))->AddWaypoint(2, 5554.58,    -2514.66,    1476.12);
                        ((EscortAI*)(me->AI()))->AddWaypoint(3, 5554.16,    -2567.23,    1479.90);
                        ((EscortAI*)(me->AI()))->AddWaypoint(4, 5540.67,    -2625.99,    1480.89);
                        ((EscortAI*)(me->AI()))->AddWaypoint(5, 5508.16,    -2659.2,    1480.15);
                        ((EscortAI*)(me->AI()))->AddWaypoint(6, 5489.62,    -2704.05,    1482.18);
                        ((EscortAI*)(me->AI()))->AddWaypoint(7, 5457.04,    -2726.26,    1485.10);
                        ((EscortAI*)(me->AI()))->Start(false, true, true);
                        ((EscortAI*)(me->AI()))->SetDespawnAtEnd(false);
                    }
                }
            }
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            if(RainTimer < diff)
            {
                if(DoCast(SelectTarget(SELECT_TARGET_RANDOM,0,30,true), SPELL_RAIN_OF_FIRE) == SPELL_CAST_OK)
                    RainTimer = TIMER_RAIN_OF_FIRE;
            }else RainTimer -= diff;
    
            if(DoomTimer < diff)
            {
                if(DoCast(me, SPELL_DOOM) == SPELL_CAST_OK) //target is randomized in the spell itself
                {
                    DoomTimer = TIMER_DOOM;
                    DoScriptText(SAY_DOOM1 - rand()%2,me);
                }
            }else DoomTimer -= diff;
    
            if(HowlTimer < diff)
            {
                if(DoCast(me, SPELL_HOWL_OF_AZGALOR) == SPELL_CAST_OK)
                    HowlTimer = TIMER_HOWL_OF_AZGALOR;
            }else HowlTimer -= diff;
    
            if(CleaveTimer < diff)
            {
                if(HasTwoPlayersInFront())
                    if(DoCast(me->GetVictim(), SPELL_CLEAVE) == SPELL_CAST_OK)
                        CleaveTimer = TIMER_CLEAVE;
            }else CleaveTimer -= diff;
    
            if(EnrageTimer < diff)
            {
                if(DoCast(me, SPELL_BERSERK, true) == SPELL_CAST_OK)
                    EnrageTimer = TIMER_BERSERK;
            }else EnrageTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_azgalorAI(creature);
    }
};


enum DoomguardSpells
{
    SPELL_THRASH       = 12787,
    SPELL_CRIPPLE      = 31406,
    SPELL_WARSTOMP     = 31408
};


class mob_lesser_doomguard : public CreatureScript
{
public:
    mob_lesser_doomguard() : CreatureScript("mob_lesser_doomguard")
    { }

    class mob_lesser_doomguardAI : public hyjal_trashAI
    {
        public:
        mob_lesser_doomguardAI(Creature *c) : hyjal_trashAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            if(pInstance)
                AzgalorGUID = pInstance->GetData64(DATA_AZGALOR);
            else
                AzgalorGUID = 0;
        }
    
        uint32 CrippleTimer;
        uint32 WarstompTimer;
        uint32 CheckTimer;
        uint64 AzgalorGUID;
        InstanceScript* pInstance;
    
        void WaypointReached(uint32, uint32) override {} //must be implemented because we inherit from EscortAI

        void Reset() override
        {
            CrippleTimer = 50000;
            WarstompTimer = 10000;
            DoCast(me, SPELL_THRASH);
            CheckTimer = 5000;
        }
        
        void MoveInLineOfSight(Unit *who) override
        {
            if (me->GetDistance(who) <= 50 && !me->IsInCombat() && me->IsHostileTo(who))
            {
                me->GetThreatManager().AddThreat(who,0.0);
                me->Attack(who,false);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(CheckTimer < diff)
            {
                if(AzgalorGUID)
                {
                    Creature* boss = ObjectAccessor::GetCreature((*me),AzgalorGUID);
                    if(!boss || boss->IsDead())
                    {
                        me->DespawnOrUnsummon();
                        return;
                    }
                }
                CheckTimer = 5000;
            }else CheckTimer -= diff;
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            if(WarstompTimer < diff)
            {
                DoCast(me, SPELL_WARSTOMP);
                WarstompTimer = 10000+rand()%5000;
            }else WarstompTimer -= diff;
    
            if(CrippleTimer < diff)
            {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM,0,100,true), SPELL_CRIPPLE);
                CrippleTimer = 25000+rand()%5000;
            }else CrippleTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_lesser_doomguardAI(creature);
    }
};


void AddSC_boss_azgalor()
{
    new boss_azgalor();

    new mob_lesser_doomguard();
}
