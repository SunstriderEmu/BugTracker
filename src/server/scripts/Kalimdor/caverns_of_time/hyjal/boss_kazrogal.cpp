

#include "def_hyjal.h"
#include "hyjal_trash.h"

enum Spells
{
    SPELL_CLEAVE    = 31436,
    SPELL_WARSTOMP  = 31480,
    SPELL_MARK      = 31447,
};

enum Timers
{
    TIMER_WARSTOMP_FIRST  = 10000,
    TIMER_CLEAVE          = 10000,
    TIMER_MARK_FIRST      = 45000,
};
#define TIMER_WARSTOMP 5000 + rand()%25000; //5-30s

enum Texts
{
    SAY_ONSLAY1 = -1801031,
    SAY_ONSLAY2 = -1801032,
    SAY_ONSLAY3 = -1801033,
    SAY_MARK1 = -1801034,
    SAY_MARK2 = -1801035,
    SAY_ONAGGRO = -1801036,
    SOUND_ONDEATH = 11018
};


class boss_kazrogal : public CreatureScript
{
public:
    boss_kazrogal() : CreatureScript("boss_kazrogal")
    { }

    class boss_kazrogalAI : public hyjal_trashAI
    {
        public:
        boss_kazrogalAI(Creature *c) : hyjal_trashAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            go = false;
            pos = 0;
        }
    
        uint32 CleaveTimer;
        uint32 WarStompTimer;
        uint32 MarkTimer;
        uint32 MarkTimerBase;
        bool go;
        uint32 pos;
    
        void Reset()
        override {
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);
    
            damageTaken = 0;
            CleaveTimer = TIMER_CLEAVE;
            WarStompTimer = TIMER_WARSTOMP_FIRST;
            MarkTimer = TIMER_MARK_FIRST;
            MarkTimerBase = TIMER_MARK_FIRST;
    
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_KAZROGALEVENT, NOT_STARTED);
        }
    
        void EnterCombat(Unit *who)
        override {
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_KAZROGALEVENT, IN_PROGRESS);
    
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
                Unit* target = ObjectAccessor::GetUnit((*me), pInstance->GetData64(DATA_THRALL));
                if (target && target->IsAlive())
                    me->AddThreat(target,0.0);
            }
        }
    
        void JustDied(Unit *victim)
        override {
            hyjal_trashAI::JustDied(victim);
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_KAZROGALEVENT, DONE);
    
            DoPlaySoundToSet(me, SOUND_ONDEATH);
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
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(0, 5492.91,    -2404.61,    1462.63);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(1, 5531.76,    -2460.87,    1469.55);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(2, 5554.58,    -2514.66,    1476.12);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(3, 5554.16,    -2567.23,    1479.90);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(4, 5540.67,    -2625.99,    1480.89);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(5, 5508.16,    -2659.2,    1480.15);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(6, 5489.62,    -2704.05,    1482.18);
                        ((npc_escortAI*)(me->AI()))->AddWaypoint(7, 5457.04,    -2726.26,    1485.10);
                        ((npc_escortAI*)(me->AI()))->Start(false, true, true);
                        ((npc_escortAI*)(me->AI()))->SetDespawnAtEnd(false);
                    }
                }
            }
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            if(CleaveTimer < diff)
            {
                if(DoCast(me, SPELL_CLEAVE) == SPELL_CAST_OK)
                    CleaveTimer = TIMER_CLEAVE;
            }else CleaveTimer -= diff;
    
            if(WarStompTimer < diff)
            {
                if(DoCast(me, SPELL_WARSTOMP) == SPELL_CAST_OK)
                    WarStompTimer = TIMER_WARSTOMP;
            }else WarStompTimer -= diff;
    
            if(me->HasAuraEffect(SPELL_MARK,0))
                me->RemoveAurasDueToSpell(SPELL_MARK);
            if(MarkTimer < diff)
            {
                if(DoCast(me,SPELL_MARK) == SPELL_CAST_OK)
                {
                    MarkTimerBase -= 5000;
                    if(MarkTimerBase < 5500)
                        MarkTimerBase = 5500;
                    MarkTimer = MarkTimerBase;
                    if(rand()%2)
                        DoScriptText(SAY_MARK1 - rand()%2,me);
                }
            }else MarkTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_kazrogalAI(creature);
    }
};


void AddSC_boss_kazrogal()
{
    new boss_kazrogal();
}
