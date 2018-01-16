
/* ScriptData
SDName: Boss_Murmur
SD%Complete: 90
SDComment: Timers may be incorrect
SDCategory: Auchindoun, Shadow Labyrinth
EndScriptData */

#include "def_shadow_labyrinth.h"

#define EMOTE_SONIC_BOOM            -1555036

#define SPELL_SONIC_BOOM_CAST       (HeroicMode?38796:33923)
#define SPELL_SONIC_BOOM_EFFECT     (HeroicMode?38795:33666)
#define SPELL_RESONANCE             33657
#define SPELL_MURMURS_TOUCH         (HeroicMode?38794:33711)
#define SPELL_MAGNETIC_PULL         33689
#define SPELL_SONIC_SHOCK           38797
#define SPELL_THUNDERING_STORM      39365


class boss_murmur : public CreatureScript
{
public:
    boss_murmur() : CreatureScript("boss_murmur")
    { }

    class boss_murmurAI : public BossAI
    {
        public:
        boss_murmurAI(Creature* creature) : BossAI(creature, DATA_MURMUR)
        {
            HeroicMode = me->GetMap()->IsHeroic();
            SetCombatMovementAllowed(false);
        }
    
        uint32 SonicBoom_Timer;
        uint32 MurmursTouch_Timer;
        uint32 Resonance_Timer;
        uint32 MagneticPull_Timer;
        uint32 SonicShock_Timer;
        uint32 ThunderingStorm_Timer;
        bool HeroicMode;
        bool SonicBoom;
    
        void Reset()
        override {
            SonicBoom_Timer = 30000;
            MurmursTouch_Timer = 20000;
            Resonance_Timer = 10000;
            MagneticPull_Timer = 20000;
            ThunderingStorm_Timer = 15000;
            SonicShock_Timer = 10000;
            SonicBoom = false;
    
            //database should have `RegenHealth`=0 to prevent regen
            uint32 hp = (me->GetMaxHealth()*40)/100;
            if (hp) me->SetHealth(hp);
            me->ResetPlayerDamageReq();
            _Reset();
        }
    
        // Sonic Boom instant damage (needs core fix instead of this)
        void SpellHitTarget(Unit *target, const SpellInfo *spell)
        override {
            if(target && target->IsAlive() && spell && spell->Id == uint32(SPELL_SONIC_BOOM_EFFECT))
                Unit::DealDamage(me, target, (target->GetHealth()*90)/100, nullptr, SPELL_DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NATURE, spell);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Return since we have no target or casting
            if (!UpdateVictim() || me->IsNonMeleeSpellCast(false))
                return;
    
            // Sonic Boom
            if(SonicBoom)
            {
                DoCast(me, SPELL_SONIC_BOOM_EFFECT, true);
                SonicBoom = false;
                Resonance_Timer = 2000;
            }
            if (SonicBoom_Timer < diff)
            {
                DoScriptText(EMOTE_SONIC_BOOM, me);
                DoCast(me, SPELL_SONIC_BOOM_CAST);
                SonicBoom_Timer = 30000;
                SonicBoom = true;
                return;
            }else SonicBoom_Timer -= diff;
    
            // Murmur's Touch
            if (MurmursTouch_Timer < diff)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,80,true))
                    DoCast(target, SPELL_MURMURS_TOUCH);
                MurmursTouch_Timer = 30000;
            }else MurmursTouch_Timer -= diff;
    
            // Resonance
            if (Resonance_Timer < diff)
            {
                if (!me->IsWithinMeleeRange(SelectTarget(SELECT_TARGET_MINDISTANCE,0,20,true)))
                    DoCast(me, SPELL_RESONANCE);
                Resonance_Timer = 5000;
            }else Resonance_Timer -= diff;
    
            if (!HeroicMode) {
                // Magnetic Pull
                if (MagneticPull_Timer < diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                        if (target->GetTypeId() == TYPEID_PLAYER && target->IsAlive())
                        {
                            DoCast(target, SPELL_MAGNETIC_PULL);
                            MagneticPull_Timer = 20000+rand()%15000;
                            return;
                        }
                    MagneticPull_Timer = 500;
                }else MagneticPull_Timer -= diff;
            }
    
            if(HeroicMode)
            {
                // Thundering Storm
                if(ThunderingStorm_Timer < diff)
                {
                    for (auto const& pair : me->GetCombatManager().GetPvECombatRefs())
                        if(Unit* target = pair.second->GetOther(me))
                            if(target->IsAlive() && me->GetDistance2d(target) > 35)
                                DoCast(target, SPELL_THUNDERING_STORM, true);
                    ThunderingStorm_Timer = 15000;
                }else ThunderingStorm_Timer -= diff;
    
                // Sonic Shock
                if(SonicShock_Timer < diff)
                {
                    if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,20,false))
                        if(target->IsAlive())
                            DoCast(target, SPELL_SONIC_SHOCK);
                    SonicShock_Timer = 10000+rand()%10000;
                }else SonicShock_Timer -= diff;
            }
    
            // Select nearest most aggro target if top aggro too far
            if(!me->IsAttackReady())
                return;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetShadowLabyrinthAI<boss_murmurAI>(creature);
    }
};


void AddSC_boss_murmur()
{
    new boss_murmur();
}

