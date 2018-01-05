
/* ScriptData
SDName: Boss_Blackheart_the_Inciter
SD%Complete: 75
SDComment: Incite Chaos not functional since core lacks Mind Control support
SDCategory: Auchindoun, Shadow Labyrinth
EndScriptData */


#include "def_shadow_labyrinth.h"

#define SPELL_INCITE_CHAOS    33676
#define SPELL_INCITE_CHAOS_B  33684                         //debuff applied to each member of party
#define SPELL_CHARGE          33709
#define SPELL_WAR_STOMP       33707

#define SAY_INTRO1          -1555008
#define SAY_INTRO2          -1555009
#define SAY_INTRO3          -1555010
#define SAY_AGGRO1          -1555011
#define SAY_AGGRO2          -1555012
#define SAY_AGGRO3          -1555013
#define SAY_SLAY1           -1555014
#define SAY_SLAY2           -1555015
#define SAY_HELP            -1555016
#define SAY_DEATH           -1555017

#define SAY2_INTRO1         -1555018
#define SAY2_INTRO2         -1555019
#define SAY2_INTRO3         -1555020
#define SAY2_AGGRO1         -1555021
#define SAY2_AGGRO2         -1555022
#define SAY2_AGGRO3         -1555023
#define SAY2_SLAY1          -1555024
#define SAY2_SLAY2          -1555025
#define SAY2_HELP           -1555026
#define SAY2_DEATH          -1555027

class boss_blackheart_the_inciter : public CreatureScript
{
public:
    boss_blackheart_the_inciter() : CreatureScript("boss_blackheart_the_inciter")
    { }

    class boss_blackheart_the_inciterAI : public BossAI
    {
        public:
        boss_blackheart_the_inciterAI(Creature* creature) : BossAI(creature, DATA_BLACKHEART_THE_INCITER)
        {
        }
    
        bool InciteChaos;
        uint32 InciteChaos_Timer;
        uint32 InciteChaosWait_Timer;
        uint32 Charge_Timer;
        uint32 Knockback_Timer;
    
        void Reset()
        override {
            InciteChaos = false;
            InciteChaos_Timer = 20000;
            InciteChaosWait_Timer = 15000;
            Charge_Timer = 5000;
            Knockback_Timer = 15000;
            _Reset();
        }
    
        void KilledUnit(Unit *victim) override
        {
            switch(rand()%2)
            {
                case 0: DoScriptText(SAY_SLAY1, me); break;
                case 1: DoScriptText(SAY_SLAY2, me); break;
            }
        }
    
        void JustDied(Unit *victim) override
        {
            DoScriptText(SAY_DEATH, me);
            _JustDied();
        }
    
        void JustEngagedWith(Unit *who) override
        {
            switch(rand()%3)
            {
                case 0: DoScriptText(SAY_AGGRO1, me); break;
                case 1: DoScriptText(SAY_AGGRO2, me); break;
                case 2: DoScriptText(SAY_AGGRO3, me); break;
            }
            _JustEngagedWith();
        }
    
        void UpdateAI(const uint32 diff) override
        {
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            if (InciteChaos)
            {
                if (InciteChaosWait_Timer < diff)
                {
                    InciteChaos = false;
                    InciteChaosWait_Timer = 15000;
                }else InciteChaosWait_Timer -= diff;
    
                return;
            }
    
            if (InciteChaos_Timer < diff)
            {
                DoCast(me, SPELL_INCITE_CHAOS);
    
                for (auto const& pair : me->GetCombatManager().GetPvECombatRefs())
                {
                    Unit* target = pair.second->GetOther(me);
                    if (target && target->GetTypeId() == TYPEID_PLAYER)
                        target->CastSpell(target,SPELL_INCITE_CHAOS_B, true);
                }
    
                ResetThreatList();
                InciteChaos = true;
                InciteChaos_Timer = 40000;
                return;
            }else InciteChaos_Timer -= diff;
    
            //Charge_Timer
            if (Charge_Timer < diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_CHARGE);
                Charge_Timer = 25000;
            }else Charge_Timer -= diff;
    
            //Knockback_Timer
            if (Knockback_Timer < diff)
            {
                DoCast(me, SPELL_WAR_STOMP);
                Knockback_Timer = 20000;
            }else Knockback_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetShadowLabyrinthAI<boss_blackheart_the_inciterAI>(creature);
    }
};


void AddSC_boss_blackheart_the_inciter()
{
    new boss_blackheart_the_inciter();
}

