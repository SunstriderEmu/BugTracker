
/* ScriptData
SDName: Boss_The_Maker
SD%Complete: 80
SDComment: Mind control no support
SDCategory: Hellfire Citadel, Blood Furnace
EndScriptData */


#include "blood_furnace.h"

#define SAY_AGGRO_1                 -1542009
#define SAY_AGGRO_2                 -1542010
#define SAY_AGGRO_3                 -1542011
#define SAY_KILL_1                  -1542012
#define SAY_KILL_2                  -1542013
#define SAY_DIE                     -1542014

enum Spells
{
    SPELL_EXPLODING_BREAKER     = 30925,
    SPELL_EXPLODING_BREAKER_H   = 40059,
    SPELL_DOMINATION            = 30923
};

enum Events
{
    EVENT_EXPLODING_BREAKER = 1,
    EVENT_DOMINATION,
};

class boss_the_maker : public CreatureScript
{
public:
    boss_the_maker() : CreatureScript("boss_the_maker")
    { }

    class boss_the_makerAI : public BossAI
    {
        public:
        boss_the_makerAI(Creature* creature) : BossAI(creature, DATA_THE_MAKER)
        {
            pInstance = ((InstanceScript*)creature->GetInstanceScript());
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        InstanceScript* pInstance;
    
        uint32 ExplodingBreaker_Timer;
        uint32 Domination_Timer;
    
        bool HeroicMode;
    
        void JustEngagedWith(Unit *who) override 
        {
            _JustEngagedWith();
            switch(rand()%3)
            {
                case 0: DoScriptText(SAY_AGGRO_1, me); break;
                case 1: DoScriptText(SAY_AGGRO_2, me); break;
                case 2: DoScriptText(SAY_AGGRO_3, me); break;
            }

            events.ScheduleEvent(EVENT_EXPLODING_BREAKER, 6000);
            events.ScheduleEvent(EVENT_DOMINATION, 40000);
        }
    
        void KilledUnit(Unit* victim) override 
        {
            switch(rand()%2)
            {
                case 0: DoScriptText(SAY_KILL_1, me); break;
                case 1: DoScriptText(SAY_KILL_2, me); break;
            }
        }
    
        void JustDied(Unit* /*Killer*/) override 
        {
            _JustDied();
            DoScriptText(SAY_DIE, me);
        }
    
        void ExecuteEvent(uint32 eventId) override
        {
            switch (eventId)
            {
            case EVENT_EXPLODING_BREAKER:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                    DoCast(target, HeroicMode ? SPELL_EXPLODING_BREAKER_H : SPELL_EXPLODING_BREAKER);
                events.ScheduleEvent(EVENT_EXPLODING_BREAKER, urand(4000, 12000));
                break;
            case EVENT_DOMINATION:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    DoCast(target, SPELL_DOMINATION);
                events.ScheduleEvent(EVENT_DOMINATION, 40000);
                break;
            default:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetBloodFurnaceAI<boss_the_makerAI>(creature);
    }
};

void AddSC_boss_the_maker()
{
    new boss_the_maker();
}
