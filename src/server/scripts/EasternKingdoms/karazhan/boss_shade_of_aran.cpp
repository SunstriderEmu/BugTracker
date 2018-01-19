
/* ScriptData
SDName: Boss_Shade_of_Aran
SD%Complete: 95
SDComment: Flame wreath missing cast animation, mods won't triggere.
SDCategory: Karazhan
EndScriptData */


#include "SimpleAI.h"
#include "karazhan.h"
#include "GameObject.h"

#define SAY_AGGRO1                  -1532073
#define SAY_AGGRO2                  -1532074
#define SAY_AGGRO3                  -1532075
#define SAY_FLAMEWREATH1            -1532076
#define SAY_FLAMEWREATH2            -1532077
#define SAY_BLIZZARD1               -1532078
#define SAY_BLIZZARD2               -1532079
#define SAY_EXPLOSION1              -1532080
#define SAY_EXPLOSION2              -1532081
#define SAY_DRINK                   -1532082                //Low Mana / AoE Pyroblast
#define SAY_ELEMENTALS              -1532083
#define SAY_KILL1                   -1532084
#define SAY_KILL2                   -1532085
#define SAY_TIMEOVER                -1532086
#define SAY_DEATH                   -1532087
#define SAY_ATIESH                  -1532088                //Atiesh is equipped by a raid member

//Spells
#define SPELL_FROSTBOLT     29954
#define SPELL_FIREBALL      29953
#define SPELL_ARCMISSLE     29955
#define SPELL_CHAINSOFICE   29991
#define SPELL_DRAGONSBREATH 29964
#define SPELL_MASSSLOW      30035
#define SPELL_FLAME_WREATH  29946
#define SPELL_AOE_CS        29961
#define SPELL_PLAYERPULL    32265
#define SPELL_AEXPLOSION    29973
#define SPELL_MASS_POLY     29963
#define SPELL_BLINK_CENTER  29967
#define SPELL_ELEMENTALS    29962
#define SPELL_CONJURE       29975
#define SPELL_DRINK         30024
#define SPELL_POTION        32453
#define SPELL_AOE_PYROBLAST 29978

//Creature Spells
#define SPELL_CIRCULAR_BLIZZARD     29952                   //29952 is the REAL circular blizzard that leaves persistant blizzards that last for 10 seconds
#define SPELL_WATERBOLT             31012
#define SPELL_SHADOW_PYRO           29978

//Creatures
#define CREATURE_WATER_ELEMENTAL    17167
#define CREATURE_SHADOW_OF_ARAN     18254
#define CREATURE_ARAN_BLIZZARD      17161

enum SuperSpell
{
    SUPER_FLAME = 0,
    SUPER_BLIZZARD,
    SUPER_AE,
};



class boss_shade_of_aran : public CreatureScript
{
public:
    boss_shade_of_aran() : CreatureScript("boss_shade_of_aran")
    { }

    class boss_aranAI : public BossAI
    {
        public:
        boss_aranAI(Creature* creature) : BossAI(creature, DATA_SHADEOFARAN_EVENT)
        {

        }
    
        uint32 SecondarySpellTimer;
        uint32 NormalCastTimer;
        uint32 SuperCastTimer;
        uint32 BerserkTimer;
    
        uint8 LastSuperSpell;
    
        uint32 FlameWreathTimer;
        uint32 FlameWreathCheckTime;
        ObjectGuid FlameWreathTarget[3];
        float FWTargPosX[3];
        float FWTargPosY[3];
    
        uint32 CurrentNormalSpell;
        uint32 ArcaneCooldown;
        uint32 FireCooldown;
        uint32 FrostCooldown;
    
        uint32 DrinkInturruptTimer;
    
        bool ElementalsSpawned;
        bool Drinking;
        bool DrinkInturrupted;
    
        void Reset() override 
        {
            _Reset();
            SecondarySpellTimer = 5000;
            NormalCastTimer = 0;
            SuperCastTimer = 35000;
            BerserkTimer = 720000;
    
            LastSuperSpell = rand()%3;
    
            FlameWreathTimer = 0;
            FlameWreathCheckTime = 0;
    
            CurrentNormalSpell = 0;
            ArcaneCooldown = 0;
            FireCooldown = 0;
            FrostCooldown = 0;
    
            DrinkInturruptTimer = 10000;
    
            ElementalsSpawned = false;
            Drinking = false;
            DrinkInturrupted = false;
        }
    
        void KilledUnit(Unit *victim)
        override {
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_KILL1, me); break;
            case 1: DoScriptText(SAY_KILL2, me); break;
            }
        }
    
        void JustDied(Unit *victim)
        override {
            _JustDied();
            DoScriptText(SAY_DEATH, me);

            if (victim->GetTypeId() != TYPEID_PLAYER)
                TC_LOG_ERROR("scripts","Aran has been killed by NON-PLAYER unit with entry %u", victim->GetEntry());
        }
    
        void JustEngagedWith(Unit *who) override 
        {
            _JustEngagedWith();
            switch(rand()%3)
            {
            case 0: DoScriptText(SAY_AGGRO1, me); break;
            case 1: DoScriptText(SAY_AGGRO2, me); break;
            case 2: DoScriptText(SAY_AGGRO3, me); break;
            }
        }
    
        void FlameWreathEffect()
        {
            std::list<Unit *> targets;
            SelectTargetList(targets, 3, SELECT_TARGET_RANDOM, 0, 100.0f, true);

            uint32 i = 0;
            for(auto & target : targets)
            {
                if(target)
                {
                    FlameWreathTarget[i] = target->GetGUID();
                    FWTargPosX[i] = target->GetPositionX();
                    FWTargPosY[i] = target->GetPositionY();
                    me->CastSpell(target, SPELL_FLAME_WREATH, TRIGGERED_FULL_MASK);
                    i++;
                }
            }
        }
        
        void OnSpellFinish(Unit *caster, uint32 spellId, Unit *target, bool ok)
        override {
            if (spellId == SPELL_AEXPLOSION)
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim() )
                return;
    
            //Cooldowns for casts
            if (ArcaneCooldown)
            {
                if (ArcaneCooldown >= diff)
                    ArcaneCooldown -= diff;
            else ArcaneCooldown = 0;
            }
    
            if (FireCooldown)
            {
                if (FireCooldown >= diff)
                    FireCooldown -= diff;
            else FireCooldown = 0;
            }
    
            if (FrostCooldown)
            {
                if (FrostCooldown >= diff)
                    FrostCooldown -= diff;
            else FrostCooldown = 0;
            }
    
            if(!Drinking && me->GetMaxPower(POWER_MANA) && (me->GetPower(POWER_MANA)*100 / me->GetMaxPower(POWER_MANA)) < 20)
            {
                Drinking = true;
                me->InterruptNonMeleeSpells(false);
    
                DoScriptText(SAY_DRINK, me);
    
                if (!DrinkInturrupted)
                {
                    me->CastSpell(me, SPELL_MASS_POLY, TRIGGERED_FULL_MASK);
                    me->CastSpell(me, SPELL_CONJURE, TRIGGERED_NONE);
                    me->CastSpell(me, SPELL_DRINK, TRIGGERED_NONE);
                                                                //Sitting down
                    me->SetUInt32Value(UNIT_FIELD_BYTES_1, 1);
                    DrinkInturruptTimer = 10000;
                }
            }
    
            //Drink Inturrupt
            if (Drinking && DrinkInturrupted)
            {
                Drinking = false;
                me->RemoveAurasDueToSpell(SPELL_DRINK);
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA)-32000);
                me->CastSpell(me, SPELL_POTION, TRIGGERED_NONE);
            }
    
            //Drink Inturrupt Timer
            if (Drinking && !DrinkInturrupted)
            {
                if (DrinkInturruptTimer >= diff)
                {
                    DrinkInturruptTimer -= diff;
                } else {
                    me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                    me->CastSpell(me, SPELL_POTION, TRIGGERED_FULL_MASK);
                    me->CastSpell(me, SPELL_AOE_PYROBLAST, TRIGGERED_NONE);
                    DrinkInturrupted = true;
                    Drinking = false;
                }
            }
    
            //Don't execute any more code if we are drinking
            if (Drinking)
                return;
    
            //Normal casts
            if(NormalCastTimer < diff)
            {
                if (!me->IsNonMeleeSpellCast(false))
                {
                    Unit* target = nullptr;
                    target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if (!target)
                        return;
    
                    uint32 Spells[3];
                    uint8 AvailableSpells = 0;
    
                    //Check for what spells are not on cooldown
                    if (!ArcaneCooldown)
                    {
                        Spells[AvailableSpells] = SPELL_ARCMISSLE;
                        AvailableSpells++;
                    }
                    if (!FireCooldown)
                    {
                        Spells[AvailableSpells] = SPELL_FIREBALL;
                        AvailableSpells++;
                    }
                    if (!FrostCooldown)
                    {
                        Spells[AvailableSpells] = SPELL_FROSTBOLT;
                        AvailableSpells++;
                    }
    
                    //If no available spells wait 1 second and try again
                    if (AvailableSpells)
                    {
                        CurrentNormalSpell = Spells[rand() % AvailableSpells];
                        DoCast(target, CurrentNormalSpell);
                    }
                }
                NormalCastTimer = 1000;
            }else NormalCastTimer -= diff;
    
            if(SecondarySpellTimer < diff)
            {
                switch (rand()%2)
                {
    
                    case 0:
                        DoCast(me, SPELL_AOE_CS);
                        break;
                    case 1:
                        if (Unit* pUnit = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(pUnit, SPELL_CHAINSOFICE);
                        break;
                }
                SecondarySpellTimer = 5000 + (rand()%15000);
            }else SecondarySpellTimer -= diff;
    
            if(SuperCastTimer < diff)
            {
                uint8 Available[2];
    
                switch (LastSuperSpell)
                {
                    case SUPER_AE:
                        Available[0] = SUPER_FLAME;
                        Available[1] = SUPER_BLIZZARD;
                        break;
                    case SUPER_FLAME:
                        Available[0] = SUPER_AE;
                        Available[1] = SUPER_BLIZZARD;
                        break;
                    case SUPER_BLIZZARD:
                        Available[0] = SUPER_FLAME;
                        Available[1] = SUPER_AE;
                        break;
                }
    
                LastSuperSpell = Available[rand()%2];
    
                switch (LastSuperSpell)
                {
                    case SUPER_AE:
    
                        if (rand()%2)
                            DoScriptText(SAY_EXPLOSION1, me);
                        else
                            DoScriptText(SAY_EXPLOSION2, me);
                            
                        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
    
                        me->CastSpell(me, SPELL_BLINK_CENTER, TRIGGERED_FULL_MASK);
                        me->CastSpell(me, SPELL_PLAYERPULL, TRIGGERED_FULL_MASK);
                        me->CastSpell(me, SPELL_MASSSLOW, TRIGGERED_FULL_MASK);
                        me->CastSpell(me, SPELL_AEXPLOSION, TRIGGERED_NONE);
                        break;
    
                    case SUPER_FLAME:
                        if (rand()%2)
                            DoScriptText(SAY_FLAMEWREATH1, me);
                        else
                            DoScriptText(SAY_FLAMEWREATH2, me);
    
                        FlameWreathTimer = 20000;
                        FlameWreathCheckTime = 500;
    
                        FlameWreathTarget[0].Clear();
                        FlameWreathTarget[1].Clear();
                        FlameWreathTarget[2].Clear();
    
                        FlameWreathEffect();
                        break;
    
                    case SUPER_BLIZZARD:
    
                        if (rand()%2)
                            DoScriptText(SAY_BLIZZARD1, me);
                        else
                            DoScriptText(SAY_BLIZZARD2, me);
    
                        Creature* Spawn = nullptr;
                        Spawn = DoSpawnCreature(CREATURE_ARAN_BLIZZARD, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN, 25000);
                        if (Spawn)
                        {
                            Spawn->SetFaction(me->GetFaction());
                            Spawn->CastSpell(Spawn, SPELL_CIRCULAR_BLIZZARD, TRIGGERED_NONE);
                        }
                        break;
                }
    
                SuperCastTimer = 35000 + (rand()%5000);
            }else SuperCastTimer -= diff;
    
            if(!ElementalsSpawned &&  me->GetHealthPct() < 40)
            {
                ElementalsSpawned = true;
    
                for (uint32 i = 0; i < 4; i++)
                {
                    Creature* pUnit = DoSpawnCreature(CREATURE_WATER_ELEMENTAL, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN, 90000);
                    if (pUnit)
                    {
                        pUnit->Attack(me->GetVictim(), true);
                        pUnit->SetFaction(me->GetFaction());
                    }
                }
    
                DoScriptText(SAY_ELEMENTALS, me);
            }
    
            if(BerserkTimer < diff)
            {
                for (uint32 i = 0; i < 5; i++)
                {
                    Creature* pUnit = DoSpawnCreature(CREATURE_SHADOW_OF_ARAN, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    if (pUnit)
                    {
                        pUnit->Attack(me->GetVictim(), true);
                        pUnit->SetFaction(me->GetFaction());
                    }
                }
    
                DoScriptText(SAY_TIMEOVER, me);
    
                BerserkTimer = 60000;
            }else BerserkTimer -= diff;
    
            //Flame Wreath check
            if (FlameWreathTimer)
            {
                if (FlameWreathTimer >= diff)
                    FlameWreathTimer -= diff;
                else FlameWreathTimer = 0;
    
                if (FlameWreathCheckTime < diff)
                {
                    for (uint32 i = 0; i < 3; i++)
                    {
                        if (!FlameWreathTarget[i])
                            continue;
    
                        Unit* pUnit = ObjectAccessor::GetUnit(*me, FlameWreathTarget[i]);
                        if (pUnit && pUnit->GetDistance2d(FWTargPosX[i], FWTargPosY[i]) > 3)
                        {
                            CastSpellExtraArgs args;
                            args.TriggerFlags = TRIGGERED_FULL_MASK;
                            args.SetOriginalCaster(me->GetGUID());
                            pUnit->CastSpell(pUnit, 20476, args);
                            pUnit->CastSpell(pUnit, 11027, TRIGGERED_FULL_MASK);
                            FlameWreathTarget[i].Clear();
                        }
                    }
                    FlameWreathCheckTime = 500;
                }else FlameWreathCheckTime -= diff;
            }
    
            if (ArcaneCooldown && FireCooldown && FrostCooldown)
                DoMeleeAttackIfReady();
        }
    
        void DamageTaken(Unit* pAttacker, uint32 &damage) override 
        {
            if (!DrinkInturrupted && Drinking && damage)
                DrinkInturrupted = true;
    
            if (pAttacker && pAttacker->ToCreature() && pAttacker->GetEntry() == 16524)
                damage = 0;
        }
    
        void SpellHit(Unit* pAttacker, const SpellInfo* Spell) override 
        {
            //We only care about inturrupt effects and only if they are durring a spell currently being casted
            if ((Spell->Effects[0].Effect != SPELL_EFFECT_INTERRUPT_CAST &&
                Spell->Effects[1].Effect != SPELL_EFFECT_INTERRUPT_CAST &&
                Spell->Effects[2].Effect != SPELL_EFFECT_INTERRUPT_CAST) || !me->IsNonMeleeSpellCast(false))
                return;
    
            //Inturrupt effect
            me->InterruptNonMeleeSpells(false);
    
            //Normally we would set the cooldown equal to the spell duration
            //but we do not have access to the DurationStore
    
            switch (CurrentNormalSpell)
            {
                case SPELL_ARCMISSLE: ArcaneCooldown = 5000; break;
                case SPELL_FIREBALL: FireCooldown = 5000; break;
                case SPELL_FROSTBOLT: FrostCooldown = 5000; break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<boss_aranAI>(creature);
    }
};


class mob_aran_elemental : public CreatureScript
{
public:
    mob_aran_elemental() : CreatureScript("mob_aran_elemental")
    { }

    class water_elementalAI : public ScriptedAI
    {
        public:
        water_elementalAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 CastTimer;
    
        void Reset()
        override {
            CastTimer = 2000 + (rand()%3000);
        }
    
        void JustEngagedWith(Unit* who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim() )
                return;
    
            if(CastTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_WATERBOLT);
                CastTimer = 2000 + (rand()%3000);
            }else CastTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<water_elementalAI>(creature);
    }
};


// CONVERT TO ACID
class mob_shadow_of_aran : public CreatureScript
{
public:
    mob_shadow_of_aran() : CreatureScript("mob_shadow_of_aran")
    { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        auto ai = new SimpleAI(creature);

        ai->Spell[0].Enabled = true;
        ai->Spell[0].Spell_Id = SPELL_SHADOW_PYRO;
        ai->Spell[0].Cooldown = 5000;
        ai->Spell[0].First_Cast = 1000;
        ai->Spell[0].Cast_Target_Type = CAST_HOSTILE_TARGET;

        ai->EnterEvadeMode();

        return ai;
    }
};

void AddSC_boss_shade_of_aran()
{
    new boss_shade_of_aran();
    new mob_shadow_of_aran();
    new mob_aran_elemental();
}

