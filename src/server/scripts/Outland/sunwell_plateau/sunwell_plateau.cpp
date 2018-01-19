/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Sunwell_Plateau
SD%Complete: 0
SDComment: Placeholder, Epilogue after Kil'jaeden, Captain Selana Gossips
EndScriptData */

/* ContentData
npc_prophet_velen
npc_captain_selana
npc_sunblade_protector
npc_sunblade_scout
npc_sunblade_slayer
npc_sunblade_cabalist
npc_sunblade_dawnpriest
npc_sunblade_duskpriest
npc_sunblade_archmage
npc_shadowsword_vanquisher
npc_shadowsword_manafiend
npc_shadowsword_lifeshaper
npc_shadowsword_soulbinder
npc_shadowsword_deathbringer
npc_volatile_fiend
npc_moorba
npc_kalec_felmyst
EndContentData */


#include "def_sunwell_plateau.h"

enum Quotes
{
    YELL_ACTIVATE              =   -1580115,
    YELL_KILL                  =   -1580116,
    YELL_AGGRO                 =   -1580117,
    YELL_AGGRO2                =   -1580118,
};

/*######
## npc_prophet_velen
######*/

enum ProphetSpeeches
{
    PROPHET_SAY1 = -1580099,
    PROPHET_SAY2 = -1580100,
    PROPHET_SAY3 = -1580101,
    PROPHET_SAY4 = -1580102,
    PROPHET_SAY5 = -1580103,
    PROPHET_SAY6 = -1580104,
    PROPHET_SAY7 = -1580105,
    PROPHET_SAY8 = -1580106
};

enum LiadrinnSpeeches
{
    LIADRIN_SAY1 = -1580107,
    LIADRIN_SAY2 = -1580108,
    LIADRIN_SAY3 = -1580109
};

/*######
## npc_captain_selana
######*/

#define CS_GOSSIP1 "Give me a situation report, Captain."
#define CS_GOSSIP2 "What went wrong?"
#define CS_GOSSIP3 "Why did they stop?"
#define CS_GOSSIP4 "Your insight is appreciated."

/*######
## npc_sunblade_protector
######*/

#define SPELL_SW_RADIANCE       45769
#define SPELL_FEL_LIGHTNING     46480


class npc_sunblade_protector : public CreatureScript
{
public:
    npc_sunblade_protector() : CreatureScript("npc_sunblade_protector")
    { }

    class npc_sunblade_protectorAI : public ScriptedAI
    {
        public:
        npc_sunblade_protectorAI(Creature *c) : ScriptedAI(c)
        {
            isActivated = false;
            JustReachedHome();
        }
        
        uint32 felLightningTimer;
        
        bool isActivated;
        
        void JustReachedHome()
        override {
            if(me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE)
                me->AddAura(25171,me); //freeze visual, not the right spell
        }
        
        void MovementInform(uint32 type, uint32 i)
        override {
    
        }
    
        void Reset()
        override {
            felLightningTimer = 5000;
            
            if(me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE)
                me->SetReactState(REACT_DEFENSIVE);
    
            if (isActivated)
            {
                DoScriptText(YELL_KILL, me);
                isActivated = false;
            }
    
            DoCast(me, SPELL_SW_RADIANCE);
        }
        
        void JustDied(Unit* /*killer*/)
        override {
            //remove loot for the first protector
            if (me->GetDefaultMovementType() == WAYPOINT_MOTION_TYPE)
                me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
        }
        
        void JustEngagedWith(Unit *pWho)
        override {
            me->RemoveAurasDueToSpell(25171);
            DoScriptText(YELL_AGGRO, me);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (felLightningTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FEL_LIGHTNING);
                felLightningTimer = 7000+rand()%5000;
            }
            else
                felLightningTimer -= diff;
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sunblade_protectorAI(creature);
    }
};


/*######
## npc_sunblade_scout
######*/

#define SPELL_ACTIVATE_PROTEC   46475
#define SPELL_SINISTER_STRIKE   46558
#define SPELL_DUAL_WIELD        42459

#define NPC_SUNBLADE_PROTEC     25507


class npc_sunblade_scout : public CreatureScript
{
public:
    npc_sunblade_scout() : CreatureScript("npc_sunblade_scout")
    { }

    class npc_sunblade_scoutAI : public ScriptedAI
    {    
        public:
        npc_sunblade_scoutAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 sinisterStrikeTimer;
        
        ObjectGuid pullerGUID;
        Creature *protector;
        
        bool hasActivated;
        bool startedRunning;
        
        void Reset()
        override {
            DoCast(me, SPELL_SW_RADIANCE);
            DoCast(me, SPELL_DUAL_WIELD, true);
            sinisterStrikeTimer = 0;
            pullerGUID = ObjectGuid::Empty;
            protector = nullptr;
            hasActivated = false;
            startedRunning = false;
            sinisterStrikeTimer = 2000;
    
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetSpeedRate(MOVE_RUN, 2.0f);
        }
        
        void JustEngagedWith(Unit *pWho)
        override {
            pullerGUID = pWho->GetGUID();
            protector = me->FindNearestCreature(NPC_SUNBLADE_PROTEC, 60.0f, true);
    
            DoScriptText(YELL_AGGRO2, me);
        }
        
        void OnSpellFinish(Unit *caster, uint32 spellId, Unit *target, bool ok)
        override {
            if (spellId == 46475 && ok) {
                if (Unit* puller = ObjectAccessor::GetUnit(*me, pullerGUID)) {
                    //puller = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    me->SetGuidValue(UNIT_FIELD_TARGET, puller->GetGUID());
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->ClearUnitState(UNIT_STATE_ROOT);
                    if (target->ToCreature()) {
                        target->RemoveAurasDueToSpell(25171);
                        target->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                        ((npc_sunblade_protector::npc_sunblade_protectorAI*)target->ToCreature()->AI())->felLightningTimer = 5000;
                        ((npc_sunblade_protector::npc_sunblade_protectorAI*)target->ToCreature()->AI())->isActivated = true;
                        DoScriptText(YELL_ACTIVATE, target->ToCreature());
                    }
                    target->GetMotionMaster()->MoveChase(puller);
                    target->Attack(puller, true);
                    me->GetMotionMaster()->MoveChase(puller);
                    AttackStart(puller);
                }
                else {
                    AttackStart(me->SelectNearestTarget(50.0f));
                    if (target->ToCreature()) {
                        target->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                        ((npc_sunblade_protector::npc_sunblade_protectorAI*)target->ToCreature()->AI())->felLightningTimer = 5000;
                        ((npc_sunblade_protector::npc_sunblade_protectorAI*)target->ToCreature()->AI())->isActivated = true;
                         DoScriptText(YELL_ACTIVATE, target->ToCreature());
                        target->ToCreature()->AI()->AttackStart(me->SelectNearestTarget(50.0f));
                    }
                }
            }
    
            me->ClearUnitState(UNIT_STATE_ROOT);
            me->SetReactState(REACT_AGGRESSIVE);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!hasActivated) {
                if (protector) {
                    if(!startedRunning)
                    {
                        startedRunning = true;
                        me->SetReactState(REACT_PASSIVE);
                        me->SetUnitMovementFlags(MOVE_RUN);
                        me->GetMotionMaster()->MovePoint(0, protector->GetPositionX(), protector->GetPositionY(), protector->GetPositionZ());
                        me->SetGuidValue(UNIT_FIELD_TARGET, protector->GetGUID());
                    }
    
                    if (me->GetDistance(protector) <= 15.0f) {
                        me->GetMotionMaster()->MovementExpired(false);
                        me->StopMoving();
                        me->AddUnitState(UNIT_STATE_ROOT);
                        DoCast(protector, SPELL_ACTIVATE_PROTEC);
                        me->SetInFront(protector);
                        hasActivated = true;
                        me->SetSpeedRate(MOVE_WALK, 1.0f);
                        sinisterStrikeTimer = 2000;
                    }
                }
            }
            
            if (!UpdateVictim())
                return;
            
            if (sinisterStrikeTimer) {
                if (sinisterStrikeTimer <= diff) {
                    DoCast(me->GetVictim(), SPELL_SINISTER_STRIKE);
                    sinisterStrikeTimer = 2000+rand()%2000;
                }
                else
                    sinisterStrikeTimer -= diff;
            }
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sunblade_scoutAI(creature);
    }
};


/*######
## npc_sunblade_slayer
######*/

#define SPELL_SHOOT            47001
#define SPELL_SCATTER_SHOT     46681
#define SPELL_SLAYING_SHOT     46557


class npc_sunblade_slayer : public CreatureScript
{
public:
    npc_sunblade_slayer() : CreatureScript("npc_sunblade_slayer")
    { }

    class npc_sunblade_slayerAI : public ScriptedAI
    {
        public:
        npc_sunblade_slayerAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 shootTimer;
        uint32 scatterTimer;
        uint32 slayingTimer;
        
        void Reset()
        override {
            DoCast(me, SPELL_SW_RADIANCE);
            
            shootTimer = 1000;
            scatterTimer = 4000;
            slayingTimer = 8000;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
    
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim() || me->IsPolymorphed())
                return;
                
            if (shootTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_SHOOT);
                shootTimer = 4000;
            }
            else
                shootTimer -= diff;
    
            if (scatterTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_SCATTER_SHOT);
                scatterTimer = 6000+rand()%4000;
            }
            else
                scatterTimer -= diff;
    
            if (slayingTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_SLAYING_SHOT);
                slayingTimer = 8000+rand()%5000;
            }
            else
                slayingTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sunblade_slayerAI(creature);
    }
};


/*######
## npc_fire_fiend
######*/

#define SPELL_FIRE_NOVA   46551


class npc_fire_fiend : public CreatureScript
{
public:
    npc_fire_fiend() : CreatureScript("npc_fire_fiend")
    { }

    class npc_fire_fiendAI : public ScriptedAI
    {
    public:
        npc_fire_fiendAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 fireNovaTimer;
        
        void Reset()
        override {
            fireNovaTimer = urand(5000, 10000);
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
    
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
    
            if (fireNovaTimer <= diff)
            {
                DoCast(me, SPELL_FIRE_NOVA, false);
                fireNovaTimer = urand(5000, 10000);
            }
            else
                fireNovaTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fire_fiendAI(creature);
    }
};


/*######
## npc_shadowsword_vanquisher
######*/

#define SPELL_CLEAVE        46468
#define SPELL_MELT_ARMOR    46469


class npc_shadowsword_vanquisher : public CreatureScript
{
public:
    npc_shadowsword_vanquisher() : CreatureScript("npc_shadowsword_vanquisher")
    { }

    class npc_shadowsword_vanquisherAI : public ScriptedAI
    {
        public:
        npc_shadowsword_vanquisherAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        uint32 cleaveTimer;
        uint32 meltArmorTimer;
        
        InstanceScript *pInstance;
        
        void Reset()
        override {
            cleaveTimer = 5000;
            meltArmorTimer = 2000;
        }
        
        void JustEngagedWith(Unit *pWho)
        override {
            if (pInstance && pInstance->GetData(DATA_GAUNTLET_EVENT) == NOT_STARTED)
                pInstance->SetData(DATA_GAUNTLET_EVENT, IN_PROGRESS);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (cleaveTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                cleaveTimer = 5000+rand()%3000;
            }
            else
                cleaveTimer -= diff;
                
            if (meltArmorTimer <= diff) {
                if (!me->GetVictim()->HasAuraEffect(SPELL_MELT_ARMOR)) {
                    DoCast(me->GetVictim(), SPELL_MELT_ARMOR);
                }
                meltArmorTimer = 10000+rand()%5000;
            }
            else
                meltArmorTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_shadowsword_vanquisherAI(creature);
    }
};


/*######
## npc_shadowsword_manafiend
######*/

#define SPELL_ARCANE_EXPLOSION_MANAFIEND    46457
#define SPELL_DRAIN_MANA                    46453


class npc_shadowsword_manafiend : public CreatureScript
{
public:
    npc_shadowsword_manafiend() : CreatureScript("npc_shadowsword_manafiend")
    { }

    class npc_shadowsword_manafiendAI : public ScriptedAI
    {
        public:
        npc_shadowsword_manafiendAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        uint32 arcaneExploTimer;
        uint32 drainManaTimer;
        
        InstanceScript *pInstance;
        
        void Reset()
        override {
            arcaneExploTimer = 8000+rand()%2000;
            drainManaTimer = 15000+rand()%5000;
        }
        
        void JustEngagedWith(Unit *pWho)
        override {
            if (pInstance && pInstance->GetData(DATA_GAUNTLET_EVENT) == NOT_STARTED)
                pInstance->SetData(DATA_GAUNTLET_EVENT, IN_PROGRESS);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (arcaneExploTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_ARCANE_EXPLOSION_MANAFIEND);
                arcaneExploTimer = 8000+rand()%2000;
            }
            else
                arcaneExploTimer -= diff;
                
            if (drainManaTimer <= diff) {
                if (me->GetPower(POWER_MANA) <= ((me->GetMaxPower(POWER_MANA) / 100.0f) * 10.0f)) {
                    DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0, true, true), SPELL_DRAIN_MANA);
                    drainManaTimer = 15000+rand()%5000;
                }
            }
            else
                drainManaTimer -= diff;
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_shadowsword_manafiendAI(creature);
    }
};


/*######
## npc_shadowsword_lifeshaper
######*/

#define SPELL_DRAIN_LIFE        46466
#define SPELL_HEALTH_FUNNEL     46467


class npc_shadowsword_lifeshaper : public CreatureScript
{
public:
    npc_shadowsword_lifeshaper() : CreatureScript("npc_shadowsword_lifeshaper")
    { }

    class npc_shadowsword_lifeshaperAI : public ScriptedAI
    {
        public:
        npc_shadowsword_lifeshaperAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        uint32 drainLifeTimer;
        uint32 healthFunnelTimer;
        
        InstanceScript *pInstance;
        
        void Reset()
        override {
            drainLifeTimer = 15000+rand()%5000;
            healthFunnelTimer = 18000+rand()%5000;
        }
        
        void JustEngagedWith(Unit *pWho)
        override {
            if (pInstance && pInstance->GetData(DATA_GAUNTLET_EVENT) == NOT_STARTED)
                pInstance->SetData(DATA_GAUNTLET_EVENT, IN_PROGRESS);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (drainLifeTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_DRAIN_LIFE);
                drainLifeTimer = 15000+rand()%5000;
            }
            else
                drainLifeTimer -= diff;
                
            if (healthFunnelTimer <= diff) {
                DoCast(DoSelectLowestHpFriendly(40.0f, 1), SPELL_HEALTH_FUNNEL);
                healthFunnelTimer = 15000+rand()%5000;
            }
            else
                healthFunnelTimer -= diff;
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_shadowsword_lifeshaperAI(creature);
    }
};


/*######
## npc_shadowsword_soulbinder
######*/

#define SPELL_CURSE_EXHAUSTION      46434
#define SPELL_FLASH_DARKNESS        46442
#define SPELL_DOMINATION            46427


class npc_shadowsword_soulbinder : public CreatureScript
{
public:
    npc_shadowsword_soulbinder() : CreatureScript("npc_shadowsword_soulbinder")
    { }

    class npc_shadowsword_soulbinderAI : public ScriptedAI
    {
        public:
        npc_shadowsword_soulbinderAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        uint32 curseExhaustionTimer;
        uint32 flashDarknessTimer;
        uint32 dominationTimer;
        uint32 despawnTimer;
        
        InstanceScript *pInstance;
        
        void Reset()
        override {
            curseExhaustionTimer = 5000+rand()%3000;
            flashDarknessTimer = 8000+rand()%2000;
            dominationTimer = 15000;
            despawnTimer = 0;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void MovementInform(uint32 type, uint32 i)
        override {
            //TC_LOG_INFO("Reached waypoint %u (type %u)", i, type);
            if (type == WAYPOINT_MOTION_TYPE && i == 11)
                despawnTimer = 2000;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (despawnTimer) {
                if (despawnTimer <= diff) {
                    me->DisappearAndDie();
                    return;
                }
                else
                    despawnTimer -= diff;
            }
            
            if (!UpdateVictim())
                return;
                
            if (curseExhaustionTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_CURSE_EXHAUSTION);
                curseExhaustionTimer = 5000+rand()%3000;
            }
            else
                curseExhaustionTimer -= diff;
                
            if (flashDarknessTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FLASH_DARKNESS);
                flashDarknessTimer = 8000+rand()%2000;
            }
            else
                flashDarknessTimer -= diff;
                
            if (dominationTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0, true, true), SPELL_DOMINATION);
                dominationTimer = 15000;
            }
            else
                dominationTimer -= diff;
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_shadowsword_soulbinderAI(creature);
    }
};


/*######
## npc_shadowsword_deathbringer
######*/

#define SPELL_DISEASE_BUFFET        46481
#define SPELL_VOLATILE_DISEASE      46483


class npc_shadowsword_deathbringer : public CreatureScript
{
public:
    npc_shadowsword_deathbringer() : CreatureScript("npc_shadowsword_deathbringer")
    { }

    class npc_shadowsword_deathbringerAI : public ScriptedAI
    {
        public:
        npc_shadowsword_deathbringerAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        uint32 buffetTimer;
        uint32 volatileTimer;
        uint32 despawnTimer;
        
        InstanceScript *pInstance;
        
        void Reset()
        override {
            buffetTimer = 5000+rand()%5000;
            volatileTimer = 15000+rand()%5000;
            despawnTimer = 0;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void MovementInform(uint32 type, uint32 i)
        override {
            if (type == WAYPOINT_MOTION_TYPE && i == 11)
                despawnTimer = 2000;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (despawnTimer) {
                if (despawnTimer <= diff) {
                    me->DisappearAndDie();
                    return;
                }
                else
                    despawnTimer -= diff;
            }
            
            if (!UpdateVictim())
                return;
            
            if (buffetTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_DISEASE_BUFFET);
                buffetTimer = 5000+rand()%5000;
            }
            else
                buffetTimer -= diff;
                
            if (volatileTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true), SPELL_VOLATILE_DISEASE);
                volatileTimer = 15000+rand()%5000;
            }
            else
                volatileTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_shadowsword_deathbringerAI(creature);
    }
};


/*######
## npc_volatile_fiend
######*/

#define SPELL_BURNING_DESTRUCTION               47287
#define SPELL_BURNING_DESTRUCTION_TRIGGERED     46218
#define SPELL_BURNING_WINDS                     46308
#define SPELL_FELFIRE_FISSION                   45779


class npc_volatile_fiend : public CreatureScript
{
public:
    npc_volatile_fiend() : CreatureScript("npc_volatile_fiend")
    { }

    class npc_volatile_fiendAI : public ScriptedAI
    {
        public:
        npc_volatile_fiendAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        uint32 despawnTimer;    // FIXME: Need new hook OnSpellTriggered and despawn when spell 46218 is triggered
        uint32 damageTimer;
        uint32 fissionTimer;
        
        InstanceScript *pInstance;
        
        void Reset()
        override {
            //DoCast(me, SPELL_BURNING_WINDS);
            despawnTimer = 0;
            damageTimer = 1000;
            fissionTimer = 2000;
            
            me->ApplySpellImmune(0, IMMUNITY_ID, 1499, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 14310, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 14311, true);
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void DamageTaken(Unit *done_by, uint32 &damage)
        override {
            DoCast(me, SPELL_BURNING_DESTRUCTION);
        }
        
        void JustDied(Unit *pKilled)
        override {
            DoCast(me, SPELL_BURNING_DESTRUCTION_TRIGGERED, true);
        }
        
        void OnSpellFinish(Unit *caster, uint32 spellId, Unit *target, bool ok)
        override {
            if (spellId == 47287)
                despawnTimer = 2100;
        }
        
        void MovementInform(uint32 type, uint32 i)
        override {
            if (type == WAYPOINT_MOTION_TYPE && i == 11)
                despawnTimer = 2000;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (despawnTimer) {
                if (despawnTimer <= diff) {
                    me->DisappearAndDie();
                    return;
                }
                else
                    despawnTimer -= diff;
            }
    
            if (!UpdateVictim())
                return;
                
            if (me->IsWithinMeleeRange(me->GetVictim())) {
                if (damageTimer <= diff) {      // Should happen only one time, as creature explodes 2 sec after reaching melee
                    DoCast(me, SPELL_FELFIRE_FISSION);
                    DoCast(me, SPELL_BURNING_DESTRUCTION_TRIGGERED, true);
                    
                    damageTimer = 2000;
                }
                else
                    damageTimer -= diff;
            
                if (fissionTimer <= diff) {
                    DoCast(me, SPELL_FELFIRE_FISSION);
                    fissionTimer = 2000;
                }
                else
                    fissionTimer -= diff;
            }
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_volatile_fiendAI(creature);
    }
};


/*######
## npc_selana
######*/

#define TEXT_HELLO             20006
#define TEXT_MENU1             20007
#define TEXT_MENU2             20008
#define TEXT_MENU3             20009
#define TEXT_MENU4             20010
#define GOSSIP_ITEM_1          20011
#define GOSSIP_ITEM_2          20012
#define GOSSIP_ITEM_3          20013
#define GOSSIP_ITEM_4          20014

class npc_selana : public CreatureScript
{
public:
    npc_selana() : CreatureScript("npc_selana")
    { }

    class npc_selanaAI : public ScriptedAI
    {
    public:
        npc_selanaAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            player->SEND_GOSSIP_MENU_TEXTID(TEXT_HELLO,me->GetGUID());
            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU1,me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                    player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU2,me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                    player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU3,me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+4:
                    player->SEND_GOSSIP_MENU_TEXTID(TEXT_MENU4,me->GetGUID());
                    break;
            }

            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_selanaAI(creature);
    }
};



/*######
## npc_moorba
######*/

class npc_moorba : public CreatureScript
{
public:
    npc_moorba() : CreatureScript("npc_moorba")
    { }

    class npc_moorbaAI : public ScriptedAI
    {
    public:
        npc_moorbaAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            //todo translate
            if (InstanceScript *pInstance = ((InstanceScript*)me->GetInstanceScript())) {
                if (pInstance->GetData(DATA_KALECGOS_EVENT) == DONE)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Téléportez-moi dans la salle de Kalecgos.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                if (pInstance->GetData(DATA_EREDAR_TWINS_EVENT) == DONE)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Téléportez-moi dans la salle des Jumelles Erédar.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                /*if (pInstance->GetData(DATA_BRUTALLUS_EVENT) == DONE)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tééportez-moi dans la salle de Brutallus.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);*/
            }
            
            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action) {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->TeleportTo(580, 1703.977051, 928.625610, 53.077671, 4.748818);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->CastSpell(player, 46883, TRIGGERED_FULL_MASK);
                break;
            }
            
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_moorbaAI(creature);
    }
};




class npc_kalec_felmyst : public CreatureScript
{
public:
    npc_kalec_felmyst() : CreatureScript("npc_kalec_felmyst")
    { }

    class npc_kalec_felmystAI : public ScriptedAI
    {
        public:
        npc_kalec_felmystAI(Creature* c) : ScriptedAI(c)
        {
            me->SetDisableGravity(true);
            
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        uint32 waitTimer;
        uint8 phase;
        
        InstanceScript* pInstance;
        
        void Reset()
        override {
            waitTimer = 0;
            phase = 0;
            
            me->GetMotionMaster()->MovePoint(0, 1483.408203, 717.707275, 93.492821, false);
            me->SetSpeedRate(MOVE_FLIGHT, 5.0f, true);
        }
        
        void JustEngagedWith(Unit* who) override {}
        
        void MovementInform(uint32 type, uint32 id)
        override {
            if (!pInstance)
                return;
    
            switch (id) {
            case 0:
            {
                waitTimer = 300;
                break;
            }
            case 1:
            {
                waitTimer = 2000;
                break;
            }
            case 2:
            {
                waitTimer = 500;
                break;
            }
            case 3:
                me->DespawnOrUnsummon(1); //despawn at next update, otherwise may cause crash when deleting waypoint movement generator immediately (this function is called from there)
                break;
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
    
            if (waitTimer) {
                if (waitTimer <= diff) {
                    switch (phase) {
                    case 0: // Go to Felyst corpse
                    {
                        if (!pInstance)
                            break;
    
                        if (Creature* felmyst = ObjectAccessor::GetCreature(*me, ObjectGuid(pInstance->GetData64(DATA_FELMYST)))) 
                        {
                            float x, y, z;
                            felmyst->GetPosition(x, y, z);
                            me->GetMotionMaster()->MovePoint(1, x, y, z+8, false);
                        }
                        waitTimer = 0;
                        phase++;
                        break;
                    }
                    case 1: // Yell on Felmyst corpse
                        DoScriptText(-1580043, me);
                        waitTimer = 8000;
                        phase++;
                        break;
                    case 2: // Takeoff
                        me->GetMotionMaster()->MovePoint(2, 1534.859009, 535.921204, 45.530205, false);
                        waitTimer = 0;
                        phase++;
                        break;
                    case 3: // Breathe on fire wall
                        DoCast(me, 46650);
                        if (pInstance)
                            pInstance->HandleGameObject(ObjectGuid(pInstance->GetData64(DATA_GO_FIRE_BARRIER)), true);
                        waitTimer = 4000;
                        phase++;
                        break;
                    case 4:
                        me->GetMotionMaster()->MovePoint(3, 1601.979736, 519.187988, 119.142479, false);
                        waitTimer = 0;
                        phase++;
                        break;
                    }
                }
                else
                    waitTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kalec_felmystAI(creature);
    }
};


/*######
## npc_doomfire_destroyer
######*/

#define SPELL_CREATE_DOOMFIRE               46306


class npc_doomfire_destroyer : public CreatureScript
{
public:
    npc_doomfire_destroyer() : CreatureScript("npc_doomfire_destroyer")
    { }

    class npc_doomfire_destroyerAI : public ScriptedAI
    {
        public:
        npc_doomfire_destroyerAI(Creature *c) : ScriptedAI(c), Summons(me)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        InstanceScript *pInstance;
        SummonList Summons;
        uint32 summonTimer;
        
        void Reset()
        override {
            summonTimer = 10000;
            Summons.DespawnAll();
        }
    
        void JustEngagedWith(Unit* who) override {}
    
        void JustSummoned(Creature* summoned)
        override {
            Summons.Summon(summoned);
        }
    
        void SummonedCreatureDespawn(Creature* unit)
        override {
            Summons.Despawn(unit);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
    
            if (summonTimer <= diff)
            {
                Unit* random = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true);
                if (random)
                    DoCast(random, SPELL_CREATE_DOOMFIRE, false);
    
                summonTimer = 10000;
            }
            else
                summonTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_doomfire_destroyerAI(creature);
    }
};


/*######
## AddSC
######*/

void AddSC_sunwell_plateau()
{
    
    new npc_sunblade_scout();
    
    new npc_sunblade_protector();
    
    new npc_sunblade_slayer();
    
    new npc_fire_fiend();
    
    new npc_shadowsword_vanquisher();
    
    new npc_shadowsword_manafiend();
    
    new npc_shadowsword_lifeshaper();
    
    new npc_shadowsword_soulbinder();
    
    new npc_shadowsword_deathbringer();
    
    new npc_volatile_fiend();
    
    new npc_moorba();

    new npc_selana();
    
    new npc_kalec_felmyst();

    new npc_doomfire_destroyer();
}
