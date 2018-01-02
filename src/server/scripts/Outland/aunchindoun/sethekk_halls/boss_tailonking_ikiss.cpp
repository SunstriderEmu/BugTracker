
/* ScriptData
SDName: Boss_Talon_King_Ikiss
SD%Complete: 80
SDComment: Heroic supported. Some details missing, but most are spell related.
SDCategory: Auchindoun, Sethekk Halls
EndScriptData */


#include "def_sethekk_halls.h"

#define SAY_INTRO                   -1556007

#define SAY_AGGRO_1                 -1556008
#define SAY_AGGRO_2                 -1556009
#define SAY_AGGRO_3                 -1556010

#define SAY_SLAY_1                  -1556011
#define SAY_SLAY_2                  -1556012
#define SAY_DEATH                   -1556013
#define EMOTE_ARCANE_EXP            -1556015

#define SPELL_BLINK                 38194
#define SPELL_BLINK_TELEPORT        38203
#define SPELL_MANA_SHIELD           38151
#define SPELL_ARCANE_BUBBLE         9438
#define H_SPELL_SLOW                35032

#define SPELL_POLYMORPH             38245
#define H_SPELL_POLYMORPH           43309

#define SPELL_ARCANE_VOLLEY         35059
#define H_SPELL_ARCANE_VOLLEY       40424

#define SPELL_ARCANE_EXPLOSION      38197
#define H_SPELL_ARCANE_EXPLOSION    40425


class boss_talon_king_ikiss : public CreatureScript
{
public:
    boss_talon_king_ikiss() : CreatureScript("boss_talon_king_ikiss")
    { }

    class boss_talon_king_ikissAI : public BossAI
    {
        public:
        boss_talon_king_ikissAI(Creature* creature) : BossAI(creature, DATA_TALON_KING_IKISS)
        {
        }
    
        bool HeroicMode;
    
        uint32 ArcaneVolley_Timer;
        uint32 Sheep_Timer;
        uint32 Blink_Timer;
        uint32 Slow_Timer;
    
        bool ManaShield;
        bool Blink;
        bool Intro;
    
        void Reset() override 
        {
            HeroicMode = me->GetMap()->IsHeroic();
    
            ArcaneVolley_Timer = 5000;
            Sheep_Timer = 8000;
            Blink_Timer = 35000;
            Slow_Timer = 15000+rand()%15000;
            Blink = false;
            Intro = false;
            ManaShield = false;
            _Reset();
        }
    
        void MoveInLineOfSight(Unit *who) override 
        {
            if( !me->GetVictim() && me->CanCreatureAttack(who) == CAN_ATTACK_RESULT_OK && ( me->IsHostileTo( who )) && who->isInAccessiblePlaceFor(me) )
            {
                if(!Intro && me->IsWithinDistInMap(who, 100))
                {
                    Intro = true;
                    DoScriptText(SAY_INTRO, me);
                }
    
                if (!me->CanFly() && me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                    return;
    
                float attackRadius = me->GetAggroRange(who);
                if( me->IsWithinDistInMap(who, attackRadius) && me->IsWithinLOSInMap(who) )
                {
                    //who->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
                    AttackStart(who);
                }
            }
        }
    
        void JustEngagedWith(Unit *who) override 
        {
            DoScriptText(RAND(SAY_AGGRO_1, SAY_AGGRO_2, SAY_AGGRO_3), me);
            _JustEngagedWith();
        }
    
        void JustDied(Unit* Killer)
        override {
            DoScriptText(SAY_DEATH, me);
            _JustDied();
        }
    
        void KilledUnit(Unit* victim)
        override {
            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2), me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
                
            // Check distance from spawn point, prevent bug abuse with the first room
            if (me->GetDistance(44.4522, 286.9020, 25.0132) > 65.0f)
                EnterEvadeMode();
    
            if (Blink)
            {
                DoCast(me,HeroicMode ? H_SPELL_ARCANE_EXPLOSION : SPELL_ARCANE_EXPLOSION);
                me->CastSpell(me,SPELL_ARCANE_BUBBLE, TRIGGERED_FULL_MASK);
                Blink = false;
            }
    
            if (ArcaneVolley_Timer < diff)
            {
                DoCast(me,HeroicMode ? H_SPELL_ARCANE_VOLLEY : SPELL_ARCANE_VOLLEY);
                ArcaneVolley_Timer = 10000+rand()%5000;
            }else ArcaneVolley_Timer -= diff;
    
            if (Sheep_Timer < diff)
            {
                //second top aggro target in normal, random target in heroic correct?
                Unit *target = nullptr;
                target = HeroicMode ? SelectTarget(SELECT_TARGET_RANDOM,0) : SelectTarget(SELECT_TARGET_TOPAGGRO,1);
                if (target)
                    DoCast(target,HeroicMode ? H_SPELL_POLYMORPH : SPELL_POLYMORPH);
                Sheep_Timer = 15000+rand()%2500;
            }else Sheep_Timer -= diff;
    
            //may not be correct time to cast
            if (!ManaShield && (me->GetHealthPct() < 20))
            {
                DoCast(me,SPELL_MANA_SHIELD);
                ManaShield = true;
            }
    
            if (HeroicMode)
            {
                if (Slow_Timer < diff)
                {
                    DoCast(me,H_SPELL_SLOW);
                    Slow_Timer = 15000+rand()%25000;
                }else Slow_Timer -= diff;
            }
    
            if (Blink_Timer < diff)
            {
                DoScriptText(EMOTE_ARCANE_EXP, me);
    
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                {
                    if (me->IsNonMeleeSpellCast(false))
                        me->InterruptNonMeleeSpells(false);
    
                    //Spell doesn't work, but we use for visual effect at least
                    DoCast(target,SPELL_BLINK);
    
                    float X = target->GetPositionX();
                    float Y = target->GetPositionY();
                    float Z = target->GetPositionZ();
    
                    DoTeleportTo(X,Y,Z);
    
                    DoCast(target,SPELL_BLINK_TELEPORT);
                    Blink = true;
                }
                Blink_Timer = 35000+rand()%5000;
            }else Blink_Timer -= diff;
    
            if (!Blink)
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetSethekkHallsAI<boss_talon_king_ikissAI>(creature);
    }
};


void AddSC_boss_talon_king_ikiss()
{
    new boss_talon_king_ikiss();
}

