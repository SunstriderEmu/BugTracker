/* Possible bug:
Infernal may seem to appear instead of falling from the sky... This happens if the relay creature is too far to be visible at client.
How to fix? Either only use the close relay, or somehow force visibility on both relays.
*/

#include "karazhan.h"

#define SAY_AGGRO           -1532091
#define SAY_AXE_TOSS1       -1532092
#define SAY_AXE_TOSS2       -1532093
#define SAY_SPECIAL1        -1532094
#define SAY_SPECIAL2        -1532095
#define SAY_SPECIAL3        -1532096
#define SAY_SLAY1           -1532097
#define SAY_SLAY2           -1532098
#define SAY_SLAY3           -1532099
#define SAY_SUMMON1         -1532100
#define SAY_SUMMON2         -1532101
#define SAY_DEATH           -1532102

#define INFERNAL_Z  275.5

#define TOTAL_INFERNAL_POINTS 19

//Enfeeble is supposed to reduce hp to 1 and then heal player back to full when it ends
//Along with reducing healing and regen while enfeebled to 0%
//This spell effect will only reduce healing

#define SPELL_ENFEEBLE          30843                       //Enfeeble during phase 1 and 2
#define SPELL_ENFEEBLE_EFFECT   41624

#define SPELL_SHADOWNOVA        30852                       //Shadownova used during all phases
#define SPELL_SW_PAIN           30854                       //Shadow word pain during phase 1 and 3 (different targeting rules though)
#define SPELL_THRASH_PASSIVE    12787                       //Extra attack chance during phase 2
#define SPELL_SUNDER_ARMOR      30901                       //Sunder armor during phase 2
#define SPELL_THRASH_AURA       3417                        //Passive proc chance for thrash
#define SPELL_EQUIP_AXES        30857                       //Visual for axe equiping
#define SPELL_AMPLIFY_DAMAGE    12738                       //Amplifiy during phase 3
#define SPELL_HELLFIRE          30859                       //Infenals' hellfire aura
#define NETHERSPITE_INFERNAL    17646                       //The netherspite infernal creature
#define MALCHEZARS_AXE          17650                       //Malchezar's axes (creatures), summoned during phase 3

#define INFERNAL_MODEL_INVISIBLE 11686                      //Infernal Effects
#define SPELL_INFERNAL_RELAY          30834                 //visual effect + dummy effect on target 17646
#define SPELL_INFERNAL_RELAY_SUMMON   30836                 //summon creature (not used here)
#define SPELL_INFERNAL_RELAY2         30835                 //also visual + script effect on nearby entry (not used here)
#define SPELL_INFERNAL_RELAY_TRIGGER  53108                 //custom spell, target max 1 CREATURE_INFERNAL_RELAY and do script effect
#define SPELL_INFERAL_LAND_VISUAL     24207                 // Not right id but same visual
#define CREATURE_INFERNAL_RELAY  17645                      //rain down inferno from this one
#define CREATURE_INFERNAL        17646

#define AXE_EQUIP_MODEL          40066                      //Axes model

//---------Infernal code first

struct InfernalPoint
{
    float x, y;
};

class netherspite_infernal : public CreatureScript
{
public:
    netherspite_infernal() : CreatureScript("netherspite_infernal")
    { }

    class netherspite_infernalAI : public ScriptedAI
    {
        public:
        netherspite_infernalAI(Creature *c) : ScriptedAI(c) ,
            HellfireTimer(0)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        uint32 HellfireTimer;
        InstanceScript* pInstance;
        
        void Reset()
        override
        {
            me->SetStunned(true);
            me->AI()->SetCombatMovementAllowed(false);
        }
    
        void UpdateAI(const uint32 diff)
        override 
        {
            if(HellfireTimer)
            {
                if(HellfireTimer <= diff)
                {
                    if (pInstance->GetBossState(DATA_MALCHEZZAR_EVENT) != IN_PROGRESS)
                    {
                        me->DespawnOrUnsummon();
                        return;
                    }

                    me->SetFaction(FACTION_MONSTER);
                    DoCast(me, SPELL_HELLFIRE);
                    HellfireTimer = 0;
                }
                else 
                    HellfireTimer -= diff;
            }
        }
    
        void KilledUnit(Unit *who)
        override 
        {
            Unit *pMalchezaar = ObjectAccessor::GetUnit(*me, pInstance->GetGuidData(DATA_MALCHEZAAR));
            if(pMalchezaar)
                (pMalchezaar->ToCreature())->AI()->KilledUnit(who);
        }
    
        void SpellHit(Unit *who, const SpellInfo *spell)
        override 
        {
            if(spell->Id == SPELL_INFERNAL_RELAY)
            {
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID, me->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                HellfireTimer = 4000;
            }
        }
    
        void DamageTaken(Unit* done_by, uint32 &damage)
        override 
        
        {
            if(done_by->GetEntry() != NPC_MALCHEZAAR)
                damage = 0;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<netherspite_infernalAI>(creature);
    }
};

class boss_malchezaar : public CreatureScript
{
public:
    boss_malchezaar() : CreatureScript("boss_malchezaar")
    { }

    class boss_malchezaarAI : public BossAI
    {
        // Coordinates for Infernal spawns
        InfernalPoint InfernalPoints[19] =
        {
            { -10922.8f, -1985.2f },
            { -10916.2f, -1996.2f },
            { -10932.2f, -2008.1f },
            { -10948.8f, -2022.1f },
            { -10958.7f, -1997.7f },
            { -10971.5f, -1997.5f },
            { -10990.8f, -1995.1f },
            { -10989.8f, -1976.5f },
            { -10971.6f, -1973.0f },
            { -10955.5f, -1974.0f },
            { -10939.6f, -1969.8f },
            { -10958.0f, -1952.2f },
            { -10941.7f, -1954.8f },
            { -10943.1f, -1988.5f },
            { -10948.8f, -2005.1f },
            { -10984.0f, -2019.3f },
            { -10932.8f, -1979.6f },
            { -10932.8f, -1979.6f },
            { -10935.7f, -1996.0f }
        };

    public:
        boss_malchezaarAI(Creature* creature) : BossAI(creature, DATA_MALCHEZZAR_EVENT)
        { }
    
        uint32 EnfeebleTimer;
        uint32 EnfeebleResetTimer;
        uint32 ShadowNovaTimer;
        uint32 SWPainTimer;
        uint32 SunderArmorTimer;
        uint32 AmplifyDamageTimer;
        uint32 InfernalTimer;
        uint32 AxesTargetSwitchTimer;
        uint32 InfernalCleanupTimer;
    
        std::vector<uint64> infernals; //spawned infernal guids
        std::vector<InfernalPoint> positions; //free infernal positions
    
        ObjectGuid axes[2];
        ObjectGuid enfeeble_targets[5];
        uint64 enfeeble_health[5];
    
        uint32 phase;
    
        bool GetRandomInferalPosition(float& x, float& y)
        {
            if (positions.empty())
                ResetFreeInfernalsPosition();

            auto itr = positions.begin() + rand() % positions.size();
            InfernalPoint& point = *itr;
            x = point.x;
            y = point.y;
            positions.erase(itr);
            return true;
        }
            
        void ResetFreeInfernalsPosition()
        {
            positions.clear();
            for (auto & InfernalPoint : InfernalPoints)
                positions.push_back(InfernalPoint);
        }

        void Reset()   override 
        {
            _Reset();
            AxesCleanup();
            ClearWeapons();
            InfernalCleanup();
    
            for(ObjectGuid & enfeeble_target : enfeeble_targets)
                enfeeble_target = ObjectGuid::Empty;
    
            EnfeebleTimer = 30000;
            EnfeebleResetTimer = 38000;
            ShadowNovaTimer = 35000;
            SWPainTimer = 20000;
            AmplifyDamageTimer = 10000;
            InfernalTimer = 25000;
            InfernalCleanupTimer = 47000;
            AxesTargetSwitchTimer = 7500 + rand()%12500;
            phase = 1;
    
            ResetFreeInfernalsPosition();
        }
    
        void KilledUnit(Unit *victim) override 
        {
            switch(rand()%3)
            {
            case 0: DoScriptText(SAY_SLAY1, me); break;
            case 1: DoScriptText(SAY_SLAY2, me); break;
            case 2: DoScriptText(SAY_SLAY3, me); break;
            }
        }
    
        void JustDied(Unit *victim) override 
        {
            _JustDied();
            DoScriptText(SAY_DEATH, me);
    
            AxesCleanup();
            ClearWeapons();
            InfernalCleanup();
        }
    
        void JustEngagedWith(Unit *who)  override 
        {
            _JustEngagedWith();
            DoScriptText(SAY_AGGRO, me);
        }
    
        void InfernalCleanup()
        {
            std::list<Creature*> _infernals;
            me->GetCreatureListWithEntryInGrid(_infernals, CREATURE_INFERNAL, 250.0f);

            if (_infernals.empty())
            {
                TC_LOG_WARN("scripts", "Malchezaar did not find any infernals to clean");
                return;
            }

            //Infernal Cleanup
            for(auto& infernal : _infernals)
            {
                if(infernal->IsAlive())
                {
                    infernal->SetVisible(false);
                    infernal->SetDeathState(JUST_DIED);
                }
            }
        }
    
        void AxesCleanup()
        {
            for(ObjectGuid & i : axes)
            {
                Unit *axe = ObjectAccessor::GetUnit(*me, i);
                if(axe && axe->IsAlive())
                    axe->DealDamage(axe, axe->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                i = ObjectGuid::Empty;
            }
        }
    
        void ClearWeapons()
        {
            me->SetWeapon(WEAPON_SLOT_MAINHAND, 0, ITEM_SUBCLASS_WEAPON_AXE, INVTYPE_WEAPON);
            me->SetWeapon(WEAPON_SLOT_OFFHAND, 0, ITEM_SUBCLASS_WEAPON_AXE, INVTYPE_WEAPON);
    
            //damage
            /*FIXMEDMG
            const CreatureTemplate *cinfo = me->GetCreatureTemplate();
            me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, cinfo->mindmg);
            me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, cinfo->maxdmg);
            me->UpdateDamagePhysical(BASE_ATTACK);
            */
        }
    
        void EnfeebleHealthEffect()
        {
            const SpellInfo *info = sSpellMgr->GetSpellInfo(SPELL_ENFEEBLE_EFFECT);
            if(!info)
                return;
    
            std::list<HostileReference *> t_list = me->GetThreatManager().getThreatList();
            std::vector<Unit *> targets;
    
            if(!t_list.size())
                return;
    
            //begin + 1 , so we don't target the one with the highest threat
            auto itr = t_list.begin();
            std::advance(itr, 1);
            for( ; itr!= t_list.end(); ++itr)                   //store the threat list in a different container
            {
                Unit *target = ObjectAccessor::GetUnit(*me, (*itr)->getUnitGuid());
                                                                //only on alive players
                if(target && target->IsAlive() && target->GetTypeId() == TYPEID_PLAYER && target != me->GetVictim() )
                    targets.push_back( target);
            }
    
            //cut down to size if we have more than 5 targets
            while(targets.size() > 5)
                targets.erase(targets.begin()+rand()%targets.size());
    
            int i = 0;
            for(auto itr2 = targets.begin(); itr2 != targets.end(); ++itr2, ++i)
            {
                Unit *target = *itr2;
                if(target)
                {
                    enfeeble_targets[i] = target->GetGUID();
                    enfeeble_health[i] = target->GetHealth();
    
                    //target->CastSpell(target, SPELL_ENFEEBLE, TRIGGERED_FULL_MASK, 0, 0, me->GetGUID());
                    target->AddAura(SPELL_ENFEEBLE, target);
                    target->SetHealth(1);
                }
            }
    
        }
    
        void EnfeebleResetHealth()
        {
            for(int i = 0; i < 5; ++i)
            {
                Unit *target = ObjectAccessor::GetUnit(*me, enfeeble_targets[i]);
                if(target && target->IsAlive())
                    target->SetHealth(enfeeble_health[i]);
                enfeeble_targets[i].Clear();
                enfeeble_health[i] = 0;
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim() )
                return;
    
            if(EnfeebleResetTimer)
            {
                if(EnfeebleResetTimer <= diff)                  //Let's not forget to reset that
                {
                    EnfeebleResetHealth();
                    EnfeebleResetTimer=0;
                } else { 
                    EnfeebleResetTimer -= diff; 
                }
            }
            if(me->HasUnitState(UNIT_STATE_STUNNED))     //While shifting to phase 2 malchezaar stuns himself
                return;
    
            if(me->GetGuidValue(UNIT_FIELD_TARGET)!=me->GetVictim()->GetGUID())
                me->SetGuidValue(UNIT_FIELD_TARGET, me->GetVictim()->GetGUID());
    
            if(phase == 1)
            {
                if(me->GetHealthPct() < 60)
                {
                    me->InterruptNonMeleeSpells(false);
    
                    phase = 2;
    
                    //animation
                    DoCast(me, SPELL_EQUIP_AXES);
    
                    //text
                    DoScriptText(SAY_AXE_TOSS1, me);
    
                    //passive thrash aura
                    me->CastSpell(me, SPELL_THRASH_AURA, TRIGGERED_FULL_MASK);
    
                    //weapons
                    me->SetWeapon(WEAPON_SLOT_MAINHAND, AXE_EQUIP_MODEL, ITEM_SUBCLASS_WEAPON_AXE, INVTYPE_WEAPON);
                    me->SetWeapon(WEAPON_SLOT_OFFHAND,  AXE_EQUIP_MODEL, ITEM_SUBCLASS_WEAPON_AXE, INVTYPE_WEAPON);
                    
                    //damage
                    /* FIXMEDMG 
                    const CreatureTemplate *cinfo = me->GetCreatureTemplate();
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, 2*cinfo->mindmg);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, 2*cinfo->maxdmg);
                    me->UpdateDamagePhysical(BASE_ATTACK);
    
                    me->SetBaseWeaponDamage(OFF_ATTACK, MINDAMAGE, cinfo->mindmg);
                    me->SetBaseWeaponDamage(OFF_ATTACK, MAXDAMAGE, cinfo->maxdmg);
                    //Sigh, updating only works on main attack , do it manually ....
                    me->SetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE, cinfo->mindmg);
                    me->SetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE, cinfo->maxdmg); */
    
                    me->SetAttackTime(OFF_ATTACK, (me->GetAttackTime(BASE_ATTACK)*150)/100);
                }
            }
            else if(phase == 2)
            {
                if(me->IsBelowHPPercent(30.0f))
                {
                    InfernalTimer = 15000;
    
                    phase = 3;
    
                    ClearWeapons();
    
                    //remove thrash
                    me->RemoveAurasDueToSpell(SPELL_THRASH_AURA);
    
                    DoScriptText(SAY_AXE_TOSS2, me);
    
                    Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    for(ObjectGuid & i : axes)
                    {
                        Creature *axe = me->SummonCreature(MALCHEZARS_AXE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
                        if(axe)
                        {
                            //no displayid, already on creaturemodel, but set correct weapon info
                            axe->SetWeapon(WEAPON_SLOT_MAINHAND, 0, ITEM_SUBCLASS_WEAPON_AXE, INVTYPE_WEAPON);
                            axe->SetWeapon(WEAPON_SLOT_OFFHAND,  0, ITEM_SUBCLASS_WEAPON_AXE, INVTYPE_WEAPON);
    
                            axe->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            axe->SetFaction(me->GetFaction());
                            i = axe->GetGUID();
                            if(target)
                            {
                                axe->AI()->AttackStart(target);
                                axe->GetThreatManager().AddThreat(target, 10000000.0f);
                            }
                        }
                    }
    
                    if(ShadowNovaTimer > 35000)
                        ShadowNovaTimer = EnfeebleTimer + 5000;
    
                    return;
                }
    
                if(SunderArmorTimer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_SUNDER_ARMOR);
                    SunderArmorTimer = 15000;
    
                }else SunderArmorTimer -= diff;
            }
            else
            {
                if(AxesTargetSwitchTimer < diff)
                {
                    AxesTargetSwitchTimer = 7500 + rand()%12500 ;
    
                    Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if(target)
                    {
                        for(ObjectGuid& i : axes)
                        {
                            Unit *axe = ObjectAccessor::GetUnit(*me, i);
                            if(axe)
                            {
                                float threat = 1000000.0f;
                                if(axe->GetVictim() && me->GetThreat(axe->GetVictim()))
                                {
                                    threat = axe->GetThreatManager().getThreat(axe->GetVictim());
                                    axe->GetThreatManager().modifyThreatPercent(axe->GetVictim(), -100);
                                }
                                if(target)
                                    axe->GetThreatManager().AddThreat(target, threat);
                            }
                        }
                    }
                } else AxesTargetSwitchTimer -= diff;
    
                if(AmplifyDamageTimer < diff)
                {
                    DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_AMPLIFY_DAMAGE);
                    AmplifyDamageTimer = 20000 + rand()%10000;
                }else AmplifyDamageTimer -= diff;
            }
    
            //Time for global and double timers
            if(InfernalTimer < diff)
            {
                DoCast(me, SPELL_INFERNAL_RELAY_TRIGGER);
                DoScriptText(rand()%2 ? SAY_SUMMON1 : SAY_SUMMON2, me);
                InfernalTimer =  phase == 3 ? 30000 : 45000;    //30 secs in phase 3, 45 otherwise
            }else InfernalTimer -= diff;
    
            if(ShadowNovaTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_SHADOWNOVA);
                ShadowNovaTimer = phase == 3 ? 35000 : -1;
            }else ShadowNovaTimer -= diff;
    
            if(phase != 2)
            {
                if(SWPainTimer < diff)
                {
                    Unit* target = nullptr;
                    if(phase == 1)
                        target = me->GetVictim();       // the tank
                    else                                        //anyone but the tank
                        target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0, true, true);
    
                    if (target)
                        DoCast(target, SPELL_SW_PAIN);
    
                    SWPainTimer = 20000;
                }else SWPainTimer -= diff;
            }
    
            if(phase != 3)
            {
                if(EnfeebleTimer < diff)
                {
                    EnfeebleHealthEffect();
                    EnfeebleTimer = 30000;
                    ShadowNovaTimer = 5000;
                    EnfeebleResetTimer = 9000;
                }else EnfeebleTimer -= diff;
            }
    
            if(phase==2)
                DoMeleeAttacksIfReady();
            else
                DoMeleeAttackIfReady();
        }
    
        void DoMeleeAttacksIfReady()
        {
            if( me->IsWithinMeleeRange(me->GetVictim()) && !me->IsNonMeleeSpellCast(false))
            {
                //Check for base attack
                if( me->IsAttackReady() && me->GetVictim() )
                {
                    me->AttackerStateUpdate(me->GetVictim());
                    me->ResetAttackTimer();
                }
                //Check for offhand attack
                if( me->IsAttackReady(OFF_ATTACK) && me->GetVictim() )
                {
                    me->AttackerStateUpdate(me->GetVictim(), OFF_ATTACK);
                    me->ResetAttackTimer(OFF_ATTACK);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<boss_malchezaarAI>(creature);
    }
};

//This npc summons an infernal to a random position when hit by spell SPELL_INFERNAL_RELAY_TRIGGER
class npc_infernal_relay : public CreatureScript
{
public:
    npc_infernal_relay() : CreatureScript("npc_infernal_relay")
    { }

    class infernal_relayAI : public ScriptedAI
    {
        public:
        infernal_relayAI(Creature *c) : ScriptedAI(c) 
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            me->SetReactState(REACT_PASSIVE);
        }
    
        InstanceScript* pInstance;
    
        void SummonInfernal()
        {
            float posX, posY, posZ;
            if(me->GetMapId() != 532) //not kara
            {
                me->GetRandomPoint(me, 60.0f, posX, posY, posZ);
            }
            else
            {
                Creature* malch = ObjectAccessor::GetCreature(*me, pInstance->GetGuidData(DATA_MALCHEZAAR));
                if(!malch)
                {
                    TC_LOG_ERROR("scripts","infernal_relayAI : could not find malchezaar");
                    return;
                }
                auto malchAI = dynamic_cast<boss_malchezaar::boss_malchezaarAI*>(malch->GetAI());
                if (!malchAI)
                {
                    TC_LOG_ERROR("scripts", "infernal_relayAI : Malchezaar has wrong AI");
                    return;
                }
                
                bool ok = malchAI->GetRandomInferalPosition(posX, posY);
                if(!ok)
                {
                    TC_LOG_ERROR("scripts","infernal_relayAI : Malchezaar did not return any point");
                    return;
                }
    
                posZ = INFERNAL_Z;
            }
    
            //creature is faction 35 at spawn
            if (Creature *Infernal = me->SummonCreature(NETHERSPITE_INFERNAL, posX, posY, posZ, 0, TEMPSUMMON_TIMED_DESPAWN, 20 * MINUTE * IN_MILLISECONDS))
            {
                //creature is invisible until SPELL_INFERNAL_RELAY touch it
                Infernal->SetUInt32Value(UNIT_FIELD_DISPLAYID, INFERNAL_MODEL_INVISIBLE);
                DoCast(Infernal, SPELL_INFERNAL_RELAY);
            }
        }
    
        void SpellHit(Unit *who, const SpellInfo *spell)
        override {
            //this spell is cast by Malchezaar whenever he wants a new inferno
            if(spell->Id == SPELL_INFERNAL_RELAY_TRIGGER)
            {
                SummonInfernal();
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID, me->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
                me->CastSpell(me,SPELL_INFERAL_LAND_VISUAL, TRIGGERED_FULL_MASK);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<infernal_relayAI>(creature);
    }
};


void AddSC_boss_malchezaar()
{
    new boss_malchezaar();
    new netherspite_infernal();
    new npc_infernal_relay();
}
