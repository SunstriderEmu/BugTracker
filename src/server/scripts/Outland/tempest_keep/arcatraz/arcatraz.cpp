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
SDName: Arcatraz
SD%Complete: 60
SDComment: Warden Mellichar, event controller for Skyriss event. Millhouse Manastorm. TODO: make better combatAI for Millhouse.
SDCategory: Tempest Keep, The Arcatraz
EndScriptData */

/* ContentData
npc_millhouse_manastorm
npc_warden_mellichar
mob_zerekethvoidzone
EndContentData */


#include "arcatraz.h"

/*#####
# npc_millhouse_manastorm
#####*/

#define SAY_INTRO_1                 -1552010
#define SAY_INTRO_2                 -1552011
#define SAY_WATER                   -1552012
#define SAY_BUFFS                   -1552013
#define SAY_DRINK                   -1552014
#define SAY_READY                   -1552015
#define SAY_KILL_1                  -1552016
#define SAY_KILL_2                  -1552017
#define SAY_PYRO                    -1552018
#define SAY_ICEBLOCK                -1552019
#define SAY_LOWHP                   -1552020
#define SAY_DEATH                   -1552021
#define SAY_COMPLETE                -1552022

#define SPELL_CONJURE_WATER         36879
#define SPELL_ARCANE_INTELLECT      36880
#define SPELL_ICE_ARMOR             36881

#define SPELL_ARCANE_MISSILES       33833
#define SPELL_CONE_OF_COLD          12611
#define SPELL_FIRE_BLAST            13341
#define SPELL_FIREBALL              14034
#define SPELL_FROSTBOLT             15497
#define SPELL_PYROBLAST             33975

//TODO make him move when target is out of range

class npc_millhouse_manastorm : public CreatureScript
{
public:
    npc_millhouse_manastorm() : CreatureScript("npc_millhouse_manastorm")
    { }

    class npc_millhouse_manastormAI : public ScriptedAI
    {
        public:
        npc_millhouse_manastormAI(Creature *c) : ScriptedAI(c)
        {
            me->AI()->SetCombatMovementAllowed(false);
            instance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* instance;
    
        uint32 EventProgress_Timer;
        uint32 Phase;
        bool Init;
        bool LowHp;
        bool hasRewarded;
    
        uint32 Pyroblast_Timer;
        uint32 Fireball_Timer;
    
        void Reset() override 
        {
            EventProgress_Timer = 2000;
            LowHp = false;
            Init = false;
            hasRewarded = false;
            Phase = 1;
    
            Pyroblast_Timer = 1000;
            Fireball_Timer = 2500;
    
            if( instance->GetData(DATA_WARDEN_2) == DONE )
                Init = true;
    
            if(instance->GetBossState(DATA_HARBINGER_SKYRISS) == DONE )
                DoScriptText(SAY_COMPLETE, me);
        }
    
        void KilledUnit(Unit *victim) override 
        {
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_KILL_1, me); break;
            case 1: DoScriptText(SAY_KILL_2, me); break;
            }
        }
    
        void JustDied(Unit *victim) override
        {
            DoScriptText(SAY_DEATH, me);
    
            /*for questId 10886 (heroic mode only)
            if( pInstance && pInstance->GetBossState(DATA_HARBINGER_SKYRISS) != DONE )
                ->FailQuest();*/
        }
        
        void CompleteQuestForAllPlayersInMap()
        {
            Map::PlayerList const& players = instance->instance->GetPlayers();
    
            if (!players.isEmpty())
            {
                for(const auto & player : players)
                {
                    if (Player* plr = player.GetSource()) {
                        if (plr->GetQuestStatus(10886) == QUEST_STATUS_INCOMPLETE)
                            plr->CompleteQuest(10886);
                    }
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (instance->GetBossState(DATA_HARBINGER_SKYRISS) == DONE && !hasRewarded) 
            {
                CompleteQuestForAllPlayersInMap();
                hasRewarded = true;
            }
            
            if( !Init )
            {
                if( EventProgress_Timer < diff )
                {
                    if( Phase < 8 )
                    {
                        switch( Phase )
                        {
                            case 1:
                                DoScriptText(SAY_INTRO_1, me);
                                EventProgress_Timer = 18000;
                                break;
                            case 2:
                                DoScriptText(SAY_INTRO_2, me);
                                EventProgress_Timer = 18000;
                                break;
                            case 3:
                                DoScriptText(SAY_WATER, me);
                                DoCast(me,SPELL_CONJURE_WATER);
                                EventProgress_Timer = 7000;
                                break;
                            case 4:
                                DoScriptText(SAY_BUFFS, me);
                                DoCast(me,SPELL_ICE_ARMOR);
                                EventProgress_Timer = 7000;
                                break;
                            case 5:
                                 DoScriptText(SAY_DRINK, me);
                                DoCast(me,SPELL_ARCANE_INTELLECT);
                                EventProgress_Timer = 7000;
                                break;
                            case 6:
                                  DoScriptText(SAY_READY, me);
                                EventProgress_Timer = 6000;
                                break;
                            case 7:
                                instance->SetData(DATA_WARDEN_2, DONE);
                                Init = true;
                                break;
                        }
                        ++Phase;
                    }
                } else EventProgress_Timer -= diff;
            }
    
            if( !UpdateVictim() )
                return;
    
            if( !LowHp && me->HealthBelowPct(20))
            {
                DoScriptText(SAY_LOWHP, me);
                LowHp = true;
            }
    
            if( Pyroblast_Timer < diff )
            {
                if( me->IsNonMeleeSpellCast(false) )
                    return;
    
                 DoScriptText(SAY_PYRO, me);
    
                DoCast(me->GetVictim(),SPELL_PYROBLAST);
                Pyroblast_Timer = 40000;
            }else Pyroblast_Timer -=diff;
    
            if( Fireball_Timer < diff )
            {
                DoCast(me->GetVictim(), SPELL_FIREBALL);
                Fireball_Timer = 4000;
            }else Fireball_Timer -=diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetArcatrazAI<npc_millhouse_manastormAI>(creature);
    }
};


/*#####
# npc_warden_mellichar
#####*/

#define YELL_INTRO1         -1552023
#define YELL_INTRO2         -1552024
#define YELL_RELEASE1       -1552025
#define YELL_RELEASE2A      -1552026
#define YELL_RELEASE2B      -1552027
#define YELL_RELEASE3       -1552028
#define YELL_RELEASE4       -1552029
#define YELL_WELCOME        -1552030

//phase 2(acid mobs)
#define ENTRY_TRICKSTER     20905
#define ENTRY_PH_HUNTER     20906
//phase 3
#define ENTRY_MILLHOUSE     20977
//phase 4(acid mobs)
#define ENTRY_AKKIRIS       20908
#define ENTRY_SULFURON      20909
//phase 5(acid mobs)
#define ENTRY_TW_DRAK       20910
#define ENTRY_BL_DRAK       20911
//phase 6
#define ENTRY_SKYRISS       20912

//TARGET_SCRIPT
#define SPELL_TARGET_ALPHA  36856
#define SPELL_TARGET_BETA   36854
#define SPELL_TARGET_DELTA  36857
#define SPELL_TARGET_GAMMA  36858
#define SPELL_TARGET_OMEGA  36852
#define SPELL_BUBBLE_VISUAL 36849

class npc_warden_mellichar : public CreatureScript
{
public:
    npc_warden_mellichar() : CreatureScript("npc_warden_mellichar")
    { }

    class npc_warden_mellicharAI : public ScriptedAI
    {
        public:
        npc_warden_mellicharAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        bool IsRunning;
        bool CanSpawn;
    
        uint32 EventProgress_Timer;
        uint32 Phase;
    
        uint64 aggroTarget;
    
        void Reset()
        override {
            IsRunning = false;
            CanSpawn = false;
            aggroTarget = 0;
    
            EventProgress_Timer = 24000;
            Phase = 1;
    
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            DoCast(me,SPELL_TARGET_OMEGA);

            instance->SetBossState(DATA_HARBINGER_SKYRISS, NOT_STARTED);
        }
    
        void AttackStart(Unit* who) override { }
    
        void MoveInLineOfSight(Unit *who) override
        {
            if( IsRunning )
                return;
    
            if( !me->GetVictim() && me->CanCreatureAttack(who) == CAN_ATTACK_RESULT_OK && ( me->IsHostileTo( who )) && who->isInAccessiblePlaceFor(me) )
            {
                if (!me->CanFly() && me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                    return;
                if (who->GetTypeId() != TYPEID_PLAYER)
                    return;
    
                float attackRadius = me->GetAggroRange(who)/5;
                if( me->IsWithinDistInMap(who, attackRadius) && me->IsWithinLOSInMap(who) )
                {
                    JustEngagedWith(who);
                    aggroTarget = who->GetGUID();
                }
            }
        }
    
        void JustEngagedWith(Unit *who) override
        {
            DoScriptText(YELL_INTRO1, me);
            DoCast(me,SPELL_BUBBLE_VISUAL);
    
            instance->SetBossState(DATA_HARBINGER_SKYRISS, IN_PROGRESS);
            instance->HandleGameObject(instance->GetGuidData(DATA_WARDENS_SHIELD), false);
            IsRunning = true;
        }
    
        bool CanProgress()
        {
            if( Phase == 7 && instance->GetData(DATA_WARDEN_4) == DONE )
                return true;
            if( Phase == 6 && instance->GetData(DATA_WARDEN_3) == DONE )
                return true;
            if( Phase == 5 && instance->GetData(DATA_WARDEN_2) == DONE )
                return true;
            if( Phase == 4 )
                return true;
            if( Phase == 3 && instance->GetData(DATA_WARDEN_1) == DONE )
                return true;
            if( Phase == 2 && instance->GetBossState(DATA_HARBINGER_SKYRISS) == IN_PROGRESS )
                return true;
            if( Phase == 1 && instance->GetBossState(DATA_HARBINGER_SKYRISS) == IN_PROGRESS )
                return true;
            return false;
        }
    
        void DoPrepareForPhase()
        {
            me->InterruptNonMeleeSpells(true);
            me->RemoveAurasByType(SPELL_AURA_DUMMY);
    
            switch( Phase )
            {
                case 2:
                    DoCast(me,SPELL_TARGET_ALPHA);
                    instance->SetData(DATA_WARDEN_1, IN_PROGRESS);
                    instance->HandleGameObject(instance->GetGuidData(DATA_WARDENS_SHIELD), false);
                    break;
                case 3:
                    DoCast(me,SPELL_TARGET_BETA);
                    instance->SetData(DATA_WARDEN_2,IN_PROGRESS);
                    break;
                case 5:
                    DoCast(me,SPELL_TARGET_DELTA);
                    instance->SetData(DATA_WARDEN_3,IN_PROGRESS);
                    break;
                case 6:
                    DoCast(me,SPELL_TARGET_GAMMA);
                    instance->SetData(DATA_WARDEN_4,IN_PROGRESS);
                    break;
                case 7:
                    instance->SetData(DATA_WARDEN_5,IN_PROGRESS);
                    break;
            }
            CanSpawn = true;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if( !IsRunning )
                return;
    
            if( EventProgress_Timer < diff )
            {
                if( instance->GetBossState(DATA_HARBINGER_SKYRISS) == FAIL )
                {
                    Reset();
                    return;
                }
    
                if( CanSpawn )
                {
                    //continue beam omega pod, unless we are about to summon skyriss
                    if( Phase != 7 )
                        DoCast(me,SPELL_TARGET_OMEGA);
    
                    
                    Creature* summon = nullptr;
                    switch( Phase )
                    {
                        case 2:
                            switch( rand()%2 )
                            {
                                case 0: summon = me->SummonCreature(ENTRY_TRICKSTER,478.326,-148.505,42.56,3.19,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000); break;
                                case 1: summon = me->SummonCreature(ENTRY_PH_HUNTER,478.326,-148.505,42.56,3.19,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000); break;
                            }
                            break;
                        case 3:
                            me->SummonCreature(ENTRY_MILLHOUSE,413.292,-148.378,42.56,6.27,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000);
                            break;
                        case 4:
                           DoScriptText(YELL_RELEASE2B, me);
                            break;
                        case 5:
                            switch( rand()%2 )
                            {
                                case 0: summon = me->SummonCreature(ENTRY_AKKIRIS,420.179,-174.396,42.58,0.02,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000); break;
                                case 1: summon = me->SummonCreature(ENTRY_SULFURON,420.179,-174.396,42.58,0.02,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000); break;
                            }
                            break;
                        case 6:
                            switch( rand()%2 )
                            {
                                case 0: summon = me->SummonCreature(ENTRY_TW_DRAK,471.795,-174.58,42.58,3.06,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000); break;
                                case 1: summon = me->SummonCreature(ENTRY_BL_DRAK,471.795,-174.58,42.58,3.06,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000); break;
                            }
                            break;
                        case 7:
                            summon = me->SummonCreature(ENTRY_SKYRISS,445.763,-191.639,44.64,1.60,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000);
                            DoScriptText(YELL_WELCOME, me);
                            break;
                    }
                    if(summon)
                    {
                        if(Player* pl = me->GetMap()->GetPlayer(aggroTarget))
                            summon->AI()->AttackStart(pl);
                    }
    
                    CanSpawn = false;
                    ++Phase;
                }
                if( CanProgress() )
                {
                    switch( Phase )
                    {
                        case 1:
                            DoScriptText(YELL_INTRO2, me);
                            EventProgress_Timer = 10000;
                            ++Phase;
                            break;
                        case 2:
                            DoScriptText(YELL_RELEASE1, me);
                            DoPrepareForPhase();
                            EventProgress_Timer = 7000;
                            break;
                        case 3:
                            DoScriptText(YELL_RELEASE2A, me);
                            DoPrepareForPhase();
                            EventProgress_Timer = 10000;
                            break;
                        case 4:
                            DoPrepareForPhase();
                            EventProgress_Timer = 15000;
                            break;
                        case 5:
                            DoScriptText(YELL_RELEASE3, me);
                            DoPrepareForPhase();
                            EventProgress_Timer = 15000;
                            break;
                        case 6:
                            DoScriptText(YELL_RELEASE4, me);
                            DoPrepareForPhase();
                            EventProgress_Timer = 15000;
                            break;
                        case 7:
                            DoPrepareForPhase();
                            EventProgress_Timer = 15000;
                            break;
                    }
                }
            } else EventProgress_Timer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetArcatrazAI<npc_warden_mellicharAI>(creature);
    }
};


/*#####
# mob_zerekethvoidzone (this script probably not needed in future -> `creature_template_addon`.`auras`='36120 0')
#####*/

#define SPELL_VOID_ZONE_DAMAGE 36120

class mob_zerekethvoidzone : public CreatureScript
{
public:
    mob_zerekethvoidzone() : CreatureScript("mob_zerekethvoidzone")
    { }

    class mob_zerekethvoidzoneAI : public ScriptedAI
    {
        public:
        mob_zerekethvoidzoneAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset() override
        {
            me->SetUInt32Value(UNIT_NPC_FLAGS,0);
            me->SetFaction(16);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    
            DoCast(me,SPELL_VOID_ZONE_DAMAGE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetArcatrazAI<mob_zerekethvoidzoneAI>(creature);
    }
};


void AddSC_arcatraz()
{
    new npc_millhouse_manastorm();
    new npc_warden_mellichar();
    new mob_zerekethvoidzone();
}

