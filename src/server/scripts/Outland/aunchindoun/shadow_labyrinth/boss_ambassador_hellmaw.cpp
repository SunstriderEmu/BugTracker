
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

#define SPELL_BANISH            30231
#define SPELL_CORROSIVE_ACID    23313
#define SPELL_FEAR              33547
#define SPELL_ENRAGE            0                           //need to find proper spell

class boss_ambassador_hellmaw : public CreatureScript
{
public:
    boss_ambassador_hellmaw() : CreatureScript("boss_ambassador_hellmaw")
    { }

    class boss_ambassador_hellmawAI : public ScriptedAI
    {
        public:
        boss_ambassador_hellmawAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        InstanceScript* pInstance;
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
            Intro = false;
            IsBanished = false;
    
            if (pInstance)
            {
                if (pInstance->GetData(TYPE_HELLMAW) == NOT_STARTED)
                {
                    DoCast(me,SPELL_BANISH);
                    IsBanished = true;
                }
                else pInstance->SetData(TYPE_HELLMAW,FAIL);
                if (pInstance->GetData(TYPE_OVERSEER) == DONE)
                {
                    if (me->HasAuraEffect(SPELL_BANISH,0))
                        me->RemoveAurasDueToSpell(SPELL_BANISH);
                    Intro = true;
                }
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
    
            if (pInstance)
                pInstance->SetData(TYPE_HELLMAW, IN_PROGRESS);
        }
    
        void EnterCombat(Unit *who) override
        {
            switch(rand()%3)
            {
                case 0: DoScriptText(SAY_AGGRO1, me); break;
                case 1: DoScriptText(SAY_AGGRO2, me); break;
                case 2: DoScriptText(SAY_AGGRO3, me); break;
            }
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
    
            if (pInstance)
                pInstance->SetData(TYPE_HELLMAW, DONE);
        }
    
        void UpdateAI(const uint32 diff) override
        {
            if (!Intro)
            {
                if (EventCheck_Timer < diff)
                {
                    if(pInstance)
                    {
                        if (pInstance->GetData(TYPE_OVERSEER) == DONE)
                            DoIntro();
                    }
                    EventCheck_Timer = 5000;
                }else EventCheck_Timer -= diff;
            }
    
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
    
            /*if (HeroicMode)
            {
                if (Enrage_Timer < diff)
                {
                    DoCast(me,SPELL_ENRAGE);
                }else Enrage_Timer -= diff;
            }*/
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_ambassador_hellmawAI(creature);
    }
};


void AddSC_boss_ambassador_hellmaw()
{
    new boss_ambassador_hellmaw();
}

