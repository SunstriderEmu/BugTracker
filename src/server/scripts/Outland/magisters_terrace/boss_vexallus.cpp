/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Boss_Vexallus
SD%Complete: 90
SDComment: Heroic and Normal support. Needs further testing.
SDCategory: Magister's Terrace
EndScriptData */


#include "def_magisters_terrace.h"

#define SAY_AGGRO                   -1585007
#define SAY_ENERGY                  -1585008
#define SAY_OVERLOAD                -1585009
#define SAY_KILL                    -1585010
#define EMOTE_DISCHARGE_ENERGY      -1585011
//is this text for real?
#define SAY_DEATH                   "What...happen...ed."

//Pure energy spell info
#define SPELL_ENERGY_BOLT           44342
#define SPELL_ENERGY_FEEDBACK       44335

//Vexallus spell info
#define SPELL_CHAIN_LIGHTNING       44318
#define SPELL_SUMMON_PURE_ENERGY    44322                   //not-working, this script summon this creatures without this spell
#define SPELL_OVERLOAD              44353
#define SPELL_ARCANE_SHOCK          44319
#define ASTRAL_FLARE_VISUAL         30237

//Creatures
#define CREATURE_PURE_ENERGY        24745


class boss_vexallus : public CreatureScript
{
public:
    boss_vexallus() : CreatureScript("boss_vexallus")
    { }

    class boss_vexallusAI : public ScriptedAI
    {
        public:
        boss_vexallusAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());         Heroic = c->GetMap()->IsHeroic();
        }
    
        InstanceScript* pInstance;
    
        uint32 ChainLightningTimer;
        uint32 ArcaneShockTimer;
        uint32 OverloadTimer;
        uint32 SpawnAddInterval;
        uint32 AlreadySpawnedAmount;
        bool Enraged;
        bool Heroic;
    
        void Reset()
        override {
            ChainLightningTimer = 10000;
            ArcaneShockTimer = 8000;
            OverloadTimer = 2200;
            SpawnAddInterval = 15;
            AlreadySpawnedAmount = 0;
    
            Enraged = false;
    
            if(pInstance)
            {
                if (me->IsDead())
                    pInstance->SetData(DATA_VEXALLUS_EVENT, DONE);
                else pInstance->SetData(DATA_VEXALLUS_EVENT, NOT_STARTED);
            }
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(SAY_KILL, me);
        }
    
        void JustDied(Unit *victim)
        override {
            me->Yell(SAY_DEATH, LANG_UNIVERSAL, nullptr);
            if (pInstance)
            {
                pInstance->SetData(DATA_VEXALLUS_EVENT, DONE);
    
                GameObject* Door = nullptr;
                Door = GameObject::GetGameObject((*me), ObjectGuid(pInstance->GetData64(DATA_VEXALLUS_DOOR)));
                if (Door)
                    Door->UseDoorOrButton();
            }
        }
    
        void JustEngagedWith(Unit *who)
        override {
            DoScriptText(SAY_AGGRO, me);
            if (pInstance)
                pInstance->SetData(DATA_VEXALLUS_EVENT, IN_PROGRESS);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim() )
                return;
    
            if(me->GetHealthPct() < 11)
            {
                Enraged = true;
            }
    
            if(!Enraged)
            {
                //used for check, when Vexallus cast adds 85%, 70%, 55%, 40%, 25%
                if ((me->GetHealthPct()) < (100-(SpawnAddInterval*(AlreadySpawnedAmount+1))))
                {
                    DoScriptText(SAY_ENERGY, me);
                    DoScriptText(EMOTE_DISCHARGE_ENERGY, me);
                    Creature* PureEnergyCreature = nullptr;
                    PureEnergyCreature = DoSpawnCreature(CREATURE_PURE_ENERGY, 10, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    Unit* target = nullptr;
                    target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if (PureEnergyCreature && target)
                        PureEnergyCreature->AI()->AttackStart(target);
    
                    if(Heroic)                                  // *Heroic mode only - he summons two instead of one.
                    {
                        PureEnergyCreature = DoSpawnCreature(CREATURE_PURE_ENERGY, -10, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                        target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                        if (PureEnergyCreature && target)
                            PureEnergyCreature->AI()->AttackStart(target);
                    }
    
                    ++AlreadySpawnedAmount;
                };
    
                if(ChainLightningTimer < diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(target, SPELL_CHAIN_LIGHTNING);
                    ChainLightningTimer = 10000;
                }else ChainLightningTimer -= diff;
    
                if(ArcaneShockTimer < diff)
                {
                    Unit* target = nullptr;
                    target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if(target)
                        DoCast(target, SPELL_ARCANE_SHOCK);
                    ArcaneShockTimer = 8000;
                }else ArcaneShockTimer -= diff;
            }else
            {
                if(OverloadTimer < diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(target, SPELL_OVERLOAD);
                    OverloadTimer = 2200;
                }else OverloadTimer -= diff;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_vexallusAI(creature);
    }
};



class mob_pure_energy : public CreatureScript
{
public:
    mob_pure_energy() : CreatureScript("mob_pure_energy")
    { }

    class mob_pure_energyAI : public ScriptedAI
    {
        public:
        mob_pure_energyAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 EnergyBoltTimer;
        uint32 VisualTimer;
    
        void Reset()
        override {
            EnergyBoltTimer = 1700;
            VisualTimer = 1000;
            me->SetSpeedRate(MOVE_RUN, 0.5f);
            me->SetSpeedRate(MOVE_WALK, 0.5f);
        }
    
        void JustDied(Unit* slayer) override 
        {
            CastSpellExtraArgs args;
            args.TriggerFlags = TRIGGERED_FULL_MASK;
            args.SetOriginalCaster(me->GetGUID());
            if(slayer)
                slayer->CastSpell(slayer, SPELL_ENERGY_FEEDBACK, args);
        }
    
        void JustEngagedWith(Unit *who)override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if(EnergyBoltTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_ENERGY_BOLT);
                EnergyBoltTimer = 1700;
            }else   EnergyBoltTimer -= diff;
            if(VisualTimer < diff)
            {
                DoCast(me->GetVictim(), ASTRAL_FLARE_VISUAL, true);
                VisualTimer = 1000;
            }else   VisualTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_pure_energyAI(creature);
    }
};


void AddSC_boss_vexallus()
{

    new boss_vexallus();

    new mob_pure_energy();
}

