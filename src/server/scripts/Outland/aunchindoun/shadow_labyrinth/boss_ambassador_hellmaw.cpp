
/* ScriptData
SDName: Boss_Ambassador_Hellmaw
SD%Complete: 75
SDComment: Waypoints after Intro not implemented. Enrage spell missing/not known
SDCategory: Auchindoun, Shadow Labyrinth
EndScriptData */


#include "def_shadow_labyrinth.h"

#define SAY_INTRO       -1555000

#define SAY_AGGRO1      -1555001
#define SAY_AGGRO2      -1555002
#define SAY_AGGRO3      -1555003

#define SAY_HELP        -1555004

#define SAY_SLAY1       -1555005
#define SAY_SLAY2       -1555006

#define SAY_DEATH       -1555007

enum Spells
{
    SPELL_BANISH            = 30231,
    SPELL_CORROSIVE_ACID    = 33551,
    SPELL_FEAR              = 33547,
    SPELL_ENRAGE            = 34970
};

class boss_ambassador_hellmaw : public CreatureScript
{
public:
    boss_ambassador_hellmaw() : CreatureScript("boss_ambassador_hellmaw")
    { }

    class boss_ambassador_hellmawAI : public BossAI
    {
        public:
        boss_ambassador_hellmawAI(Creature* creature) : BossAI(creature, DATA_AMBASSADOR_HELLMAW)
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        bool HeroicMode;
    
        uint32 EventCheck_Timer;
        uint32 CorrosiveAcid_Timer;
        uint32 Fear_Timer;
        uint32 Enrage_Timer;
        bool Intro;
        bool IsBanished;
    
        void Reset() override
        {
            EventCheck_Timer = 5000;
            CorrosiveAcid_Timer = 25000;
            Fear_Timer = 40000;
            Enrage_Timer = 180000;
            IsBanished = false;
    
            DoAction(ACTION_AMBASSADOR_HELLMAW_BANISH);
            _Reset();
        }

        void DoAction(int32 actionId) override
        {
            if (actionId == ACTION_AMBASSADOR_HELLMAW_INTRO)
                DoIntro();
            else if (actionId == ACTION_AMBASSADOR_HELLMAW_BANISH)
            {
                if (instance->GetData(DATA_FEL_OVERSEER) > 0)
                    DoCast(me, SPELL_BANISH, true);
            }
        }

        void MoveInLineOfSight(Unit *who) override
        {
            if (me->HasAuraEffect(SPELL_BANISH,0))
                return;
    
            ScriptedAI::MoveInLineOfSight(who);
        }
    
        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != POINT_MOTION_TYPE)
                return;
        }
    
        void DoIntro() 
        {
            DoScriptText(SAY_INTRO, me);
    
            if (me->HasAuraEffect(SPELL_BANISH,0))
                me->RemoveAurasDueToSpell(SPELL_BANISH);
    
            IsBanished = false;
            Intro = true;
        }
    
        void EnterCombat(Unit *who) override
        {
            switch(rand()%3)
            {
                case 0: DoScriptText(SAY_AGGRO1, me); break;
                case 1: DoScriptText(SAY_AGGRO2, me); break;
                case 2: DoScriptText(SAY_AGGRO3, me); break;
            }
            _EnterCombat();
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
    
        void UpdateAI(const uint32 diff) override
        {
            if (!me->IsInCombat() && !IsBanished)
            {
                //this is where we add MovePoint()
                //DoWhine("I haz no mount!", LANG_UNIVERSAL, NULL);
            }
    
            if (!UpdateVictim() )
                return;
    
            if(me->HasAuraEffect(SPELL_BANISH, 0))
            {
                EnterEvadeMode();
                return;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (CorrosiveAcid_Timer < diff)
            {
                DoCast(me,SPELL_CORROSIVE_ACID);
                CorrosiveAcid_Timer = 25000;
            }else CorrosiveAcid_Timer -= diff;
    
            if (Fear_Timer < diff)
            {
                DoCast(me,SPELL_FEAR);
                Fear_Timer = 35000;
            }else Fear_Timer -= diff;
    
            if (HeroicMode)
            {
                if (Enrage_Timer < diff)
                {
                    DoCast(me,SPELL_ENRAGE);
                }else Enrage_Timer -= diff;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetShadowLabyrinthAI<boss_ambassador_hellmawAI>(creature);
    }
};


void AddSC_boss_ambassador_hellmaw()
{
    new boss_ambassador_hellmaw();
}

