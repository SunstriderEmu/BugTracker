
/* ScriptData
SDName: Boss_Darkweaver_Syth
SD%Complete: 85
SDComment: Shock spells/times need more work. Heroic partly implemented.
SDCategory: Auchindoun, Sethekk Halls
EndScriptData */

#include "def_sethekk_halls.h"

#define SAY_SUMMON                  -1556000

#define SAY_AGGRO_1                 -1556001
#define SAY_AGGRO_2                 -1556002
#define SAY_AGGRO_3                 -1556003

#define SAY_SLAY_1                  -1556004
#define SAY_SLAY_2                  -1556005

#define SAY_DEATH                   -1556006

#define SPELL_FROST_SHOCK           21401 //37865
#define SPELL_FLAME_SHOCK           34354
#define SPELL_SHADOW_SHOCK          30138
#define SPELL_ARCANE_SHOCK          37132

#define SPELL_CHAIN_LIGHTNING       15659 //15305

#define SPELL_SUMMON_SYTH_FIRE      33537                   // Spawns 19203
#define SPELL_SUMMON_SYTH_ARCANE    33538                   // Spawns 19205
#define SPELL_SUMMON_SYTH_FROST     33539                   // Spawns 19204
#define SPELL_SUMMON_SYTH_SHADOW    33540                   // Spawns 19206

#define SPELL_FLAME_BUFFET          (HeroicMode?38141:33526)
#define SPELL_ARCANE_BUFFET         (HeroicMode?38138:33527)
#define SPELL_FROST_BUFFET          (HeroicMode?38142:33528)
#define SPELL_SHADOW_BUFFET         (HeroicMode?38143:33529)


class boss_darkweaver_syth : public CreatureScript
{
public:
    boss_darkweaver_syth() : CreatureScript("boss_darkweaver_syth")
    { }

    class boss_darkweaver_sythAI : public BossAI
    {
        public:
        boss_darkweaver_sythAI(Creature* creature) : BossAI(creature, DATA_DARKWEAVER_SYTH)
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        uint32 flameshock_timer;
        uint32 arcaneshock_timer;
        uint32 frostshock_timer;
        uint32 shadowshock_timer;
        uint32 chainlightning_timer;
    
        bool summon90;
        bool summon50;
        bool summon10;
        bool HeroicMode;
        
        void Reset() override 
        {
            flameshock_timer = 2000;
            arcaneshock_timer = 4000;
            frostshock_timer = 6000;
            shadowshock_timer = 8000;
            chainlightning_timer = 15000;
    
            summon90 = false;
            summon50 = false;
            summon10 = false;
            
            _Reset();
        }
    
        void JustEngagedWith(Unit *who) override 
        {
            DoScriptText(RAND(SAY_AGGRO_1, SAY_AGGRO_2, SAY_AGGRO_3), me);
            _JustEngagedWith();
        }
    
        void JustDied(Unit* /*Killer*/) override 
        {
            DoScriptText(SAY_DEATH, me);
            
            _JustDied();
        }
    
        void KilledUnit(Unit* pVictim) override 
        {
            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2), me);
        }
        
        void SythSummoning()
        {
            DoScriptText(SAY_SUMMON, me);
    
            if (me->IsNonMeleeSpellCast(false))
                me->InterruptNonMeleeSpells(false);
    
            DoCast(me,SPELL_SUMMON_SYTH_ARCANE,true);   //front
            DoCast(me,SPELL_SUMMON_SYTH_FIRE,true);     //back
            DoCast(me,SPELL_SUMMON_SYTH_FROST,true);    //left
            DoCast(me,SPELL_SUMMON_SYTH_SHADOW,true);   //right
        }
    
        void UpdateAI(const uint32 diff) override 
        {
            if (!UpdateVictim())
                return;
    
            if ((me->GetHealthPct() < 90) && !summon90)
            {
                SythSummoning();
                summon90 = true;
            }
    
            if ((me->GetHealthPct() < 50) && !summon50)
            {
                SythSummoning();
                summon50 = true;
            }
    
            if ((me->GetHealthPct() < 10) && !summon10)
            {
                SythSummoning();
                summon10 = true;
            }
    
            if (flameshock_timer < diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_FLAME_SHOCK);
    
                flameshock_timer = 10000 + rand()%5000;
            } else flameshock_timer -= diff;
    
            if (arcaneshock_timer < diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_ARCANE_SHOCK);
    
                arcaneshock_timer = 10000 + rand()%5000;
            } else arcaneshock_timer -= diff;
    
            if (frostshock_timer < diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_FROST_SHOCK);
    
                frostshock_timer = 10000 + rand()%5000;
            } else frostshock_timer -= diff;
    
            if (shadowshock_timer < diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_SHADOW_SHOCK);
    
                shadowshock_timer = 10000 + rand()%5000;
            } else shadowshock_timer -= diff;
    
            if (chainlightning_timer < diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_CHAIN_LIGHTNING);
    
                chainlightning_timer = 25000;
            } else chainlightning_timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetSethekkHallsAI<boss_darkweaver_sythAI>(creature);
    }
};


/* ELEMENTALS */

class mob_syth_fire : public CreatureScript
{
public:
    mob_syth_fire() : CreatureScript("mob_syth_fire")
    { }

    class mob_syth_fireAI : public ScriptedAI
    {
        public:
        mob_syth_fireAI(Creature *c) : ScriptedAI(c)
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        uint32 flameshock_timer;
        uint32 flamebuffet_timer;
        bool HeroicMode;
    
        void Reset() override 
        {
            me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, true);
            flameshock_timer = 2500;
            flamebuffet_timer = 5000;
        }
    
        void UpdateAI(const uint32 diff) override 
        {
            if (!UpdateVictim())
                return;
    
            if(flameshock_timer < diff)
            {
                if( Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0) )
                    DoCast(target,SPELL_FLAME_SHOCK);
    
                flameshock_timer = 5000;
            } else flameshock_timer -= diff;
    
            if(flamebuffet_timer < diff)
            {
                if( Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0) )
                    DoCast(target,SPELL_FLAME_BUFFET);
    
                flamebuffet_timer = 5000;
            } else flamebuffet_timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetSethekkHallsAI<mob_syth_fireAI>(creature);
    }
};

class mob_syth_arcane : public CreatureScript
{
public:
    mob_syth_arcane() : CreatureScript("mob_syth_arcane")
    { }

    class mob_syth_arcaneAI : public ScriptedAI
    {
        public:
        mob_syth_arcaneAI(Creature *c) : ScriptedAI(c)
    
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        uint32 arcaneshock_timer;
        uint32 arcanebuffet_timer;
        bool HeroicMode;
    
        void Reset() override 
        {
            me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_ARCANE, true);
            arcaneshock_timer = 2500;
            arcanebuffet_timer = 5000;
        }
    
        void JustEngagedWith(Unit *who) override { }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if(arcaneshock_timer < diff)
            {
                if( Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0) )
                    DoCast(target,SPELL_ARCANE_SHOCK);
    
                arcaneshock_timer = 5000;
            }else arcaneshock_timer -= diff;
    
            if(arcanebuffet_timer < diff)
            {
                if( Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0) )
                    DoCast(target,SPELL_ARCANE_BUFFET);
    
                arcanebuffet_timer = 5000;
            }else arcanebuffet_timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetSethekkHallsAI<mob_syth_arcaneAI>(creature);
    }
};



class mob_syth_frost : public CreatureScript
{
public:
    mob_syth_frost() : CreatureScript("mob_syth_frost")
    { }

    class mob_syth_frostAI : public ScriptedAI
    {
        public:
        mob_syth_frostAI(Creature *c) : ScriptedAI(c)
    
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        uint32 frostshock_timer;
        uint32 frostbuffet_timer;
        bool HeroicMode;
    
        void Reset()
        override {
            me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FROST, true);
            frostshock_timer = 2500;
            frostbuffet_timer = 5000;
        }
    
        void JustEngagedWith(Unit *who) override { }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if(frostshock_timer < diff)
            {
                if( Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0) )
                    DoCast(target,SPELL_FROST_SHOCK);
    
                frostshock_timer = 5000;
            }else frostshock_timer -= diff;
    
            if(frostbuffet_timer < diff)
            {
                if( Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0) )
                    DoCast(target,SPELL_FROST_BUFFET);
    
                frostbuffet_timer = 5000;
            }else frostbuffet_timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetSethekkHallsAI<mob_syth_frostAI>(creature);
    }
};



class mob_syth_shadow : public CreatureScript
{
public:
    mob_syth_shadow() : CreatureScript("mob_syth_shadow")
    { }

    class mob_syth_shadowAI : public ScriptedAI
    {
        public:
        mob_syth_shadowAI(Creature *c) : ScriptedAI(c)
    
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        uint32 shadowshock_timer;
        uint32 shadowbuffet_timer;
        bool HeroicMode;
    
        void Reset()
        override {
            me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_SHADOW, true);
            shadowshock_timer = 2500;
            shadowbuffet_timer = 5000;
        }
    
        void JustEngagedWith(Unit *who) override { }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if(shadowshock_timer < diff)
            {
                if( Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0) )
                    DoCast(target,SPELL_SHADOW_SHOCK);
    
                shadowshock_timer = 5000;
            }else shadowshock_timer -= diff;
    
            if(shadowbuffet_timer < diff)
            {
                if( Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0) )
                    DoCast(target,SPELL_SHADOW_BUFFET);
    
                shadowbuffet_timer = 5000;
            }else shadowbuffet_timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetSethekkHallsAI<mob_syth_shadowAI>(creature);
    }
};


void AddSC_boss_darkweaver_syth()
{
    new boss_darkweaver_syth();
    new mob_syth_fire();
    new mob_syth_arcane();
    new mob_syth_frost();
    new mob_syth_shadow();
}

