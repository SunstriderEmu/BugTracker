#include "def_hellfire_ramparts.h"

#define SAY_TAUNT               -1543000
#define SAY_HEAL                -1543001
#define SAY_SURGE               -1543002
#define SAY_AGGRO_1             -1543003
#define SAY_AGGRO_2             -1543004
#define SAY_AGGRO_3             -1543005
#define SAY_KILL_1              -1543006
#define SAY_KILL_2              -1543007
#define SAY_DIE                 -1543008

#define SPELL_MORTAL_WOUND      30641
#define H_SPELL_MORTAL_WOUND    36814
#define SPELL_SURGE             34645
#define SPELL_RETALIATION       22857
#define SPELL_OVERPOWER         32154

struct boss_watchkeeper_gargolmarAI : public ScriptedAI
{
    boss_watchkeeper_gargolmarAI(Creature *c) : ScriptedAI(c)
    {
        HeroicMode = me->GetMap()->IsHeroic();
    }

    bool HeroicMode;

    uint32 Surge_Timer;
    uint32 MortalWound_Timer;
    bool RetaliationCasted;

    uint32 Overpower_timer;

    bool HasTaunted;
    bool YelledForHeal;

    void Reset()
    override {
        Surge_Timer = urand(5000, 10000);
        MortalWound_Timer = urand(15000, 20000);
        Overpower_timer = 5000;
        RetaliationCasted = false;

        HasTaunted = false;
        YelledForHeal = false;
    }

    void EnterCombat(Unit *who)
    override {
        switch(rand()%3)
        {
            case 0: DoScriptText(SAY_AGGRO_1, me); break;
            case 1: DoScriptText(SAY_AGGRO_2, me); break;
            case 2: DoScriptText(SAY_AGGRO_3, me); break;
        }
    }

    void MoveInLineOfSight(Unit* who)
    override {
        if (!me->GetVictim() && me->CanAttack(who) == CAN_ATTACK_RESULT_OK && ( me->IsHostileTo( who )) && who->isInAccessiblePlaceFor(me) )
        {
            if (!me->CanFly() && me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                return;

            float attackRadius = me->GetAttackDistance(who);
            if (me->IsWithinDistInMap(who, attackRadius) && me->IsWithinLOSInMap(who))
            {
                //who->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
                AttackStart(who);
            }
            else if (!HasTaunted && me->IsWithinDistInMap(who, 60.0f))
            {
                DoScriptText(SAY_TAUNT, me);
                HasTaunted = true;
            }
        }
    }

    void KilledUnit(Unit* victim)
    override {
        switch(rand()%2)
        {
            case 0: DoScriptText(SAY_KILL_1, me); break;
            case 1: DoScriptText(SAY_KILL_2, me); break;
        }
    }

    void JustDied(Unit* Killer)
    override {
        DoScriptText(SAY_DIE, me);
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        if (MortalWound_Timer < diff)
        {
            if (me->GetVictim()->IsWithinMeleeRange(me))
            {
                DoCast(me->GetVictim(),HeroicMode ? H_SPELL_MORTAL_WOUND : SPELL_MORTAL_WOUND);
                MortalWound_Timer = urand(10000, 15000);
            }
        }else MortalWound_Timer -= diff;

        if (Surge_Timer < diff)
        {
            DoScriptText(SAY_SURGE, me);

            if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0))
                DoCast(target,SPELL_SURGE);

            Surge_Timer = urand(10000, 15000);

        }else Surge_Timer -= diff;

        if (Overpower_timer < diff)
        {
            //REACTIVE_OVERPOWER == target has dodged in the last 4 secs
            if (me->HasReactiveTimerActive(REACTIVE_OVERPOWER))
            {
                DoCast(me->GetVictim(), SPELL_OVERPOWER);
                Overpower_timer = 5000;
            }
        }
        else Overpower_timer -= diff;

        if (me->GetHealthPct() < 20.0f)
        {
            if (!RetaliationCasted)
            {
                DoCast(me,SPELL_RETALIATION);
                RetaliationCasted = true;
            }
        }

        if (!YelledForHeal)
        {
            if (me->GetHealthPct() < 30.0f)
            {
                DoScriptText(SAY_HEAL, me);
                YelledForHeal = true;
            }
        }

        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_boss_watchkeeper_gargolmarAI(Creature *_Creature)
{
    return new boss_watchkeeper_gargolmarAI (_Creature);
}

void AddSC_boss_watchkeeper_gargolmar()
{
    OLDScript *newscript;
    newscript = new OLDScript;
    newscript->Name="boss_watchkeeper_gargolmar";
    newscript->GetAI = &GetAI_boss_watchkeeper_gargolmarAI;
    sScriptMgr->RegisterOLDScript(newscript);
}

