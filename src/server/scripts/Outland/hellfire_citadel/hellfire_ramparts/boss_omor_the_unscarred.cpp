#include "hellfire_ramparts.h"

#define SAY_AGGRO_1                 -1543009
#define SAY_AGGRO_2                 -1543010
#define SAY_AGGRO_3                 -1543011
#define SAY_SUMMON                  -1543012
#define SAY_CURSE                   -1543013
#define SAY_KILL_1                  -1543014
#define SAY_DIE                     -1543015
#define SAY_WIPE                    -1543016
#define EMOTE_SHIELD                -1543026

#define SPELL_ORBITAL_STRIKE        30637
#define SPELL_SHADOW_WHIP           30638
#define SPELL_TREACHEROUS_AURA      30695
#define H_SPELL_BANE_OF_TREACHERY   37566
#define SPELL_DEMONIC_SHIELD        31901
#define SPELL_SHADOW_BOLT           30686
#define H_SPELL_SHADOW_BOLT         39297
#define SPELL_SUMMON_FIENDISH_HOUND 30707


class boss_omor_the_unscarred : public CreatureScript
{
public:
    boss_omor_the_unscarred() : CreatureScript("boss_omor_the_unscarred")
    { }

    class boss_omor_the_unscarredAI : public BossAI
    {
        public:
        boss_omor_the_unscarredAI(Creature* creature) : BossAI(creature, DATA_OMOR_THE_UNSCARRED)
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        bool HeroicMode;
    
        uint32 OrbitalStrike_Timer;
        uint32 ShadowWhip_Timer;
        uint32 Aura_Timer;
        bool DemonicShieldCasted;
        uint32 Shadowbolt_Timer;
        uint32 Summon_Timer;
        uint64 orbitarStrikeTargetGUID;
        bool CanPullBack;
    
        void Reset() override 
        {
            _Reset();
            SetCombatMovementAllowed(false);
    
            OrbitalStrike_Timer = urand(40000,45000);
            ShadowWhip_Timer = 2000;
            Aura_Timer = urand(15000,20000);
            DemonicShieldCasted = false;
            Shadowbolt_Timer = 500;
            Summon_Timer = 25000;
            orbitarStrikeTargetGUID = 0;
            CanPullBack = false;
        }
    
        void JustReachedHome() override
        {
            _JustReachedHome();
            DoScriptText(SAY_WIPE, me);
        }
    
        void EnterCombat(Unit *who) override 
        {
            _EnterCombat();
            switch(rand()%3)
            {
                case 0: DoScriptText(SAY_AGGRO_1, me); break;
                case 1: DoScriptText(SAY_AGGRO_2, me); break;
                case 2: DoScriptText(SAY_AGGRO_3, me); break;
            }
        }
    
        void KilledUnit(Unit* victim) override 
        {
            if (rand()%2)
                return;
    
            DoScriptText(SAY_KILL_1, me);
        }
    
        void JustSummoned(Creature* summoned) override 
        {
            BossAI::JustSummoned(summoned);
            DoScriptText(SAY_SUMMON, me);
    
            if (Unit* random = SelectTarget(SELECT_TARGET_RANDOM, 0))
                summoned->AI()->AttackStart(random);
        }
    
        void JustDied(Unit* Killer) override 
        {
            _JustDied();
            DoScriptText(SAY_DIE, me);
        }
    
        void UpdateAI(const uint32 diff) override 
        {
            if (!UpdateVictim())
                return;
    
            if (Summon_Timer < diff)
            {
                me->InterruptNonMeleeSpells(false);
                DoCast(me,SPELL_SUMMON_FIENDISH_HOUND);
                Summon_Timer = urand(20000, 30000);
            }else Summon_Timer -= diff;
    
            if (CanPullBack)
            {
                if (ShadowWhip_Timer < diff)
                {
                    if (Unit* temp = me->GetMap()->GetPlayer(orbitarStrikeTargetGUID))
                    {
                        //if unit dosen't have this flag, then no pulling back (script will attempt cast, even if orbital strike was resisted)
                        if (temp->HasUnitMovementFlag(MOVEMENTFLAG_JUMPING_OR_FALLING))
                            DoCast(temp,SPELL_SHADOW_WHIP, true);
                    }
                    orbitarStrikeTargetGUID = 0;
                    ShadowWhip_Timer = 2000;
                    CanPullBack = false;
                } else ShadowWhip_Timer -= diff;
            }
            else if (OrbitalStrike_Timer < diff)
            {
                Unit* playerTarget = nullptr;
                if (me->IsWithinMeleeRange(me->GetVictim()))
                    playerTarget = me->GetVictim();
                else 
                    playerTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true, false);
    
                if (playerTarget)
                {
                    if (DoCast(playerTarget, SPELL_ORBITAL_STRIKE) == SPELL_CAST_OK)
                    {
                        OrbitalStrike_Timer = urand(20000, 25000);
                        orbitarStrikeTargetGUID = playerTarget->GetGUID();
                        //not sure how this is done blizzlike. Tanks always seems to loose aggro whenever he get bumped
                        DoModifyThreatPercent(playerTarget, -100);
                        CanPullBack = true;
                    }
                }
            } else OrbitalStrike_Timer -= diff;
    
            if (!DemonicShieldCasted && me->GetHealthPct() < 20.0f)
            {
                DoCast(me, SPELL_DEMONIC_SHIELD, true);
                DoScriptText(EMOTE_SHIELD, me);
                DemonicShieldCasted = true;
            }
    
            if (Aura_Timer < diff)
            {
                DoScriptText(SAY_CURSE, me);
    
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                {
                    DoCast(target,HeroicMode ? H_SPELL_BANE_OF_TREACHERY : SPELL_TREACHEROUS_AURA);
                    Aura_Timer = urand(15000, 20000);
                }
            }else Aura_Timer -= diff;
    
            if (!me->IsWithinMeleeRange(me->GetVictim()))
            {
                if (Shadowbolt_Timer < diff)
                {
                    if (!me->IsWithinMeleeRange(me->GetVictim()))
                    {
                        DoCast(me->GetVictim(), HeroicMode ? H_SPELL_SHADOW_BOLT : SPELL_SHADOW_BOLT);
                        Shadowbolt_Timer = 500;
                    }
                }
                else Shadowbolt_Timer -= diff;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_omor_the_unscarredAI(creature);
    }
};


void AddSC_boss_omor_the_unscarred()
{
    new boss_omor_the_unscarred();
}

