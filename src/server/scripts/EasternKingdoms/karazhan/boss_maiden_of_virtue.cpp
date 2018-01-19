
#include "karazhan.h"

#define SAY_AGGRO               -1532018
#define SAY_SLAY1               -1532019
#define SAY_SLAY2               -1532020
#define SAY_SLAY3               -1532021
#define SAY_REPENTANCE1         -1532022
#define SAY_REPENTANCE2         -1532023
#define SAY_DEATH               -1532024

#define SPELL_REPENTANCE        29511
#define SPELL_HOLYFIRE          29522
#define SPELL_HOLYWRATH         32445
#define SPELL_HOLYGROUND        29512
#define SPELL_BERSERK           26662


class boss_maiden_of_virtue : public CreatureScript
{
public:
    boss_maiden_of_virtue() : CreatureScript("boss_maiden_of_virtue")
    { }

    class boss_maiden_of_virtueAI : public BossAI
    {
        public:
        boss_maiden_of_virtueAI(Creature *creature) : BossAI(creature, DATA_MAIDENOFVIRTUE_EVENT)
        {
        }
    
        uint32 Repentance_Timer;
        uint32 Holyfire_Timer;
        uint32 Holywrath_Timer;
        uint32 Holyground_Timer;
        uint32 Enrage_Timer;
    
        bool enraged;
    
        void Reset()
        override {
            _Reset();
            Repentance_Timer    = 20000;
            Holyfire_Timer      = urand(8000,20000);
            Holywrath_Timer     = 20000;
            Holyground_Timer    = 3000;
            Enrage_Timer        = 600000;
    
            enraged = false;
        }
    
        void KilledUnit(Unit* Victim)
        override {
            if (roll_chance_i(50))
                return;
    
            switch(rand()%3)
            {
            case 0: DoScriptText(SAY_SLAY1, me);break;
            case 1: DoScriptText(SAY_SLAY2, me);break;
            case 2: DoScriptText(SAY_SLAY3, me);break;
            }
        }
    
        void JustDied(Unit* /*Killer*/)
        override {
            DoScriptText(SAY_DEATH, me);
            _JustDied();
        }
    
        void JustEngagedWith(Unit *who)
        override {
            _JustEngagedWith();
             DoScriptText(SAY_AGGRO, me);

             DoCastSelf(SPELL_HOLYGROUND, true);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim() )
                return;
    
            if (Enrage_Timer < diff && !enraged)
            {
                DoCast(me, SPELL_BERSERK,true);
                enraged = true;
            }else Enrage_Timer -=diff;
    
            if (Holyground_Timer < diff)
            {
                DoCast(me, SPELL_HOLYGROUND, true);     //Triggered so it doesn't interrupt her at all
                Holyground_Timer = 3000;
            }else Holyground_Timer -= diff;
    
            if (Repentance_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_REPENTANCE);
    
                DoScriptText(rand()%2 ? SAY_REPENTANCE1 : SAY_REPENTANCE2, me);
                Repentance_Timer = 15000 + rand()%10000;
            }else Repentance_Timer -= diff;
    
            if (Holyfire_Timer < diff)
            {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [&](Unit* target) {
                    return target->IsAlive()
                        && target->GetTypeId() == TYPEID_PLAYER
                        && me->IsWithinCombatRange(target, 80.0f)
                        && !target->HasAuraEffect(SPELL_REPENTANCE, 1);
                });

                if (target) //don't select target with repentance
                    DoCast(target,SPELL_HOLYFIRE);
    
                    Holyfire_Timer = 8000 + rand()%17000; //Anywhere from 8 to 25 seconds, good luck having several of those in a row!
            }else Holyfire_Timer -= diff;
    
            if (Holywrath_Timer < diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_HOLYWRATH);
    
                Holywrath_Timer = 20000;
    
            }else Holywrath_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<boss_maiden_of_virtueAI>(creature);
    }
};

void AddSC_boss_maiden_of_virtue()
{
    new boss_maiden_of_virtue();
}

