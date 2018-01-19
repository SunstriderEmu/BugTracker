/* Copyright ?2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ScriptData
SDName: boss_Akilzon
SD%Complete: 75%
SDComment: Missing timer for Call Lightning and Sound ID's
SQLUpdate:
#Temporary fix for Soaring Eagles

EndScriptData */


#include "def_zulaman.h"
#include "Weather.h"

#define SPELL_STATIC_DISRUPTION     44008 /*43622*/
#define SPELL_STATIC_VISUAL         45265
#define SPELL_CALL_LIGHTNING        43661 //Missing timer
#define SPELL_GUST_OF_WIND          43621
#define SPELL_ELECTRICAL_STORM      43648
#define SPELL_BERSERK               45078
#define SPELL_ELECTRICAL_DAMAGE     43657
#define SPELL_ELECTRICAL_OVERLOAD   43658
#define SPELL_EAGLE_SWOOP           44732

// TODO TRANSLATE
//"Your death gonna be quick, strangers. You shoulda never have come to this place..."
#define SAY_ONAGGRO "Moi, chuis le prédateur ! Vous, z'êtes la proie…"
#define SAY_ONDEATH "Mon esprit, vous ne pouvez pas... le tuer !"
#define SAY_ONSLAY1 "Vous êtes nuls !"
#define SAY_ONSLAY2 "Arrêtez de pleurnicher !"
#define SAY_ONSUMMON "Mangez, mes frères !"
#define SAY_ONENRAGE "Vous m'faites perdre mon temps, rien d'autre !"
#define SOUND_ONAGGRO 12013
#define SOUND_ONDEATH 12019
#define SOUND_ONSLAY1 12017
#define SOUND_ONSLAY2 12018
#define SOUND_ONSUMMON 12014
#define SOUND_ONENRAGE 12016

#define MOB_SOARING_EAGLE 24858
#define SE_LOC_X_MAX 400
#define SE_LOC_X_MIN 335
#define SE_LOC_Y_MAX 1435
#define SE_LOC_Y_MIN 1370

//Soaring Eagle
class mob_akilzon_eagle : public CreatureScript
{
public:
    mob_akilzon_eagle() : CreatureScript("mob_akilzon_eagle")
    { }

    class mob_soaring_eagleAI : public ScriptedAI
    {
        public:
        mob_soaring_eagleAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 EagleSwoop_Timer;
        bool arrived;
        ObjectGuid TargetGUID;
    
        void Reset()
        override {
            EagleSwoop_Timer = 5000 + rand()%5000;
            arrived = true;
            TargetGUID = ObjectGuid::Empty;
            me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
        }
    
        void JustEngagedWith(Unit *who) override
        {
            DoZoneInCombat();
        }
    
        void AttackStart(Unit *who) override
        {
            if (!me->IsInCombat())
            {
                JustEngagedWith(who);
            }
        }
    
        void MoveInLineOfSight(Unit *) override 
        {} 
    
        void MovementInform(uint32, uint32) override
        {
            arrived = true;
            if(TargetGUID)
            {
                if(Unit* target = ObjectAccessor::GetUnit(*me, TargetGUID))
                    me->CastSpell(target, SPELL_EAGLE_SWOOP, TRIGGERED_FULL_MASK);
                TargetGUID = ObjectGuid::Empty;
                me->SetSpeedRate(MOVE_RUN, 1.2f);
                EagleSwoop_Timer = 5000 + rand()%5000;
            }
        }
    
        void UpdateAI(const uint32 diff) override
        {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
    
            if(EagleSwoop_Timer < diff) EagleSwoop_Timer = 0;
            else EagleSwoop_Timer -= diff;
    
            if(arrived)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    float x, y, z;
                    if(EagleSwoop_Timer)
                    {
                        x = target->GetPositionX() + 10 - rand()%20;
                        y = target->GetPositionY() + 10 - rand()%20;
                        z = target->GetPositionZ() + 10 + rand()%5;
                        if(z > 95) z = 95 - rand()%5;
                    }
                    else
                    {
                        target->GetContactPoint(me, x, y, z);
                        z += 2;
                        me->SetSpeedRate(MOVE_RUN, 5.0f);
                        TargetGUID = target->GetGUID();
                    }
                    me->SetDisableGravity(true);
                    me->GetMotionMaster()->MovePoint(0, x, y, z);
                    me->SetDisableGravity(false);
                    arrived = false;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_soaring_eagleAI(creature);
    }
};


class boss_akilzon : public CreatureScript
{
public:
    boss_akilzon() : CreatureScript("boss_akilzon")
    { }

    class boss_akilzonAI : public ScriptedAI
    {
        public:
        boss_akilzonAI(Creature *c) : ScriptedAI(c)
        {
            SpellInfo *TempSpell = (SpellInfo*)sSpellMgr->GetSpellInfo(SPELL_ELECTRICAL_DAMAGE);
            if(TempSpell)
                TempSpell->Effects[1].BasePoints = 49;//disable bugged lightning until fixed in core
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        InstanceScript *pInstance;
    
        ObjectGuid BirdGUIDs[8];
        ObjectGuid TargetGUID;
        ObjectGuid CycloneGUID;
        ObjectGuid CloudGUID;
    
        uint32 StaticDisruption_Timer;
        uint32 GustOfWind_Timer;
        uint32 CallLighting_Timer;
        uint32 ElectricalStorm_Timer;
        uint32 SummonEagles_Timer;
        uint32 Enrage_Timer;
    
        uint32 StormCount;
        uint32 StormSequenceTimer;
    
        bool isRaining;
    
        void Reset()
        override {
            if(pInstance && pInstance->GetData(DATA_AKILZONEVENT) != DONE)
                pInstance->SetData(DATA_AKILZONEVENT, NOT_STARTED);
    
            StaticDisruption_Timer = (10+rand()%10)*IN_MILLISECONDS; //10 to 20 seconds (bosskillers)
            GustOfWind_Timer = (20+rand()%10)*IN_MILLISECONDS; //20 to 30 seconds(bosskillers)
            CallLighting_Timer = (10+rand()%10)*IN_MILLISECONDS; //totaly random timer. can't find any info on this
            ElectricalStorm_Timer = 60*IN_MILLISECONDS; //60 seconds(bosskillers)
            Enrage_Timer = 10*60*IN_MILLISECONDS; //10 minutes till enrage(bosskillers)
            SummonEagles_Timer = 99999;
    
            TargetGUID = ObjectGuid::Empty;
            CloudGUID = ObjectGuid::Empty;
            CycloneGUID = ObjectGuid::Empty;
            DespawnSummons();
            for(ObjectGuid & BirdGUID : BirdGUIDs)
                BirdGUID = ObjectGuid::Empty;
    
            StormCount = 0;
            StormSequenceTimer = 0;
    
            isRaining = false;
    
            SetWeather(WEATHER_STATE_FINE, 0.0f);
            
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
        }
    
        void JustEngagedWith(Unit *who) override
        {
            me->Yell(SAY_ONAGGRO, LANG_UNIVERSAL, nullptr);
            DoPlaySoundToSet(me, SOUND_ONAGGRO);
            //DoZoneInCombat();
            if(pInstance)
                pInstance->SetData(DATA_AKILZONEVENT, IN_PROGRESS);
        }
    
        void JustDied(Unit* /*Killer*/)
        override {
            me->Yell(SAY_ONDEATH,LANG_UNIVERSAL,nullptr);
            DoPlaySoundToSet(me, SOUND_ONDEATH);
            if(pInstance)
                pInstance->SetData(DATA_AKILZONEVENT, DONE);
            DespawnSummons();
        }
    
        void KilledUnit(Unit* victim)
        override {
            switch(rand()%2)
            {
            case 0:
                me->Yell(SAY_ONSLAY1, LANG_UNIVERSAL, nullptr);
                DoPlaySoundToSet(me, SOUND_ONSLAY1);
                break;
            case 1:
                me->Yell(SAY_ONSLAY2, LANG_UNIVERSAL, nullptr);
                DoPlaySoundToSet(me, SOUND_ONSLAY2);
                break;
            }
        }
    
        void DespawnSummons()
        {
            for (ObjectGuid BirdGUID : BirdGUIDs)
            {
                Unit* bird = ObjectAccessor::GetUnit(*me, BirdGUID);
                if(bird && bird->IsAlive())
                {
                    bird->SetVisible(false);
                    bird->SetDeathState(JUST_DIED);
                }
            }
        }
    
        void SetWeather(uint32 weather, float grade)
        {
            Map *map = me->GetMap();
            if (!map->IsDungeon()) return;
    
            WorldPacket data(SMSG_WEATHER, (4+4+4));
            data << uint32(weather) << (float)grade << uint8(0);
    
            map->SendToPlayers(&data);
        }
    
        void HandleStormSequence(Unit *Cloud) // 1: begin, 2-9: tick, 10: end
        {
            if(StormCount < 10 && StormCount > 1)
            {
                // deal damage
                int32 bp0 = 800;
                for(uint8 i = 2; i < StormCount; ++i)
                    bp0 *= 2;
    
                /*CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
                Cell cell(p);
                cell.data.Part.reserved = ALL_DISTRICT;
                cell.SetNoCreate();
    
                std::list<Unit *> tempUnitMap;
    
                {
                    Trinity::AnyAoETargetUnitInObjectRangeCheck u_check(me, me, 999);
                    Trinity::UnitListSearcher<Trinity::AnyAoETargetUnitInObjectRangeCheck> searcher(me, tempUnitMap, u_check);
    
                    TypeContainerVisitor<Trinity::UnitListSearcher<Trinity::AnyAoETargetUnitInObjectRangeCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
                    TypeContainerVisitor<Trinity::UnitListSearcher<Trinity::AnyAoETargetUnitInObjectRangeCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);
    
                    cell.Visit(p, world_unit_searcher, *(me->GetMap()));
                    cell.Visit(p, grid_unit_searcher, *(me->GetMap()));
                }
                //dealdamege
                for(std::list<Unit*>::iterator i = tempUnitMap.begin(); i != tempUnitMap.end(); ++i)
                {
                    if(Cloud->GetDistance2d(*i)>= 6)
                    {
                        CastSpellExtraArgs args;
                        args.TriggerFlags = TRIGGERED_FULL_MASK;
                        args.AddSpellBP0(int32(bp0));
                        args.SetOriginalCaster(me->GetGUID());
                        Cloud->CastSpell(*i, 43137, args);
                    }
                }*/
                Map::PlayerList const& players = pInstance->instance->GetPlayers();
                if (players.isEmpty()) {
                    EnterEvadeMode();
                    return;
                }
                for(const auto & player : players) 
                {
                    if (Player* plr = player.GetSource()) 
                    {
                        if (Cloud->GetDistance2d(plr) >= 6 && plr->IsAttackableByAOE())
                        {
                            CastSpellExtraArgs args;
                            args.TriggerFlags = TRIGGERED_FULL_MASK;
                            args.AddSpellBP0(int32(bp0));
                            args.SetOriginalCaster(me->GetGUID());
                            Cloud->CastSpell(plr, 43137, args);
                        }
                    }
                }
                // visual
                /*float x,y,z;
                z = me->GetPositionZ();
                for(uint8 i = 0; i < 5+rand()%5; ++i)
                {
                    x = 343+rand()%60;
                    y = 1380+rand()%60;
                    //if(Unit *trigger = me->SummonTrigger(x, y, z, 0, 2000))
                    if (Unit *trigger = me->SummonCreature(WORLD_TRIGGER, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN, 2000))
                    {
                        trigger->SetFaction(FACTION_FRIENDLY);
                        trigger->SetMaxHealth(100000);
                        trigger->SetHealth(100000);
                        trigger->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        if (Cloud)
                        {
                            CastSpellExtraArgs args;
                            args.TriggerFlags = TRIGGERED_FULL_MASK;
                            args.AddSpellBP0(int32(bp0));
                            args.SetOriginalCaster(Cloud->GetGUID());
                            Cloud->CastSpell(trigger, 43137, args);
                        }
                    }
                }*/
            }
            StormCount++;
            if(StormCount > 10)
            {
                StormCount = 0; // finish
                SummonEagles_Timer = 5000;
                me->InterruptNonMeleeSpells(false);
                CloudGUID = ObjectGuid::Empty;
                if (Cloud)
                    Cloud->KillSelf();
                SetWeather(WEATHER_STATE_FINE, 0.0f);
                isRaining = false;
            }
            StormSequenceTimer = 1000;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if(StormCount)
            {
                Unit* target = ObjectAccessor::GetUnit(*me, CloudGUID);
                if(!target || !target->IsAlive())
                {
                    EnterEvadeMode();
                    return;
                }
                else if(Unit* Cyclone = ObjectAccessor::GetUnit(*me, CycloneGUID))
                    Cyclone->CastSpell(target, 25160, TRIGGERED_FULL_MASK); // keep casting or...
    
                if(StormSequenceTimer < diff) {
                    HandleStormSequence(target);
                }else StormSequenceTimer -= diff;
                return;
            }
    
            if (Enrage_Timer < diff) {
                me->Yell(SAY_ONENRAGE, LANG_UNIVERSAL, nullptr);
                DoPlaySoundToSet(me, SOUND_ONENRAGE);
                me->CastSpell(me, SPELL_BERSERK, TRIGGERED_FULL_MASK);
                Enrage_Timer = 600000;
            }else Enrage_Timer -= diff;
    
            if (StaticDisruption_Timer < diff) {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0, true, true);
                if(!target) target = me->GetVictim();
                TargetGUID = target->GetGUID();
                me->CastSpell(target, SPELL_STATIC_DISRUPTION, TRIGGERED_NONE);
                /*Unit *target = NULL; 
                for (auto const& pair : me->GetCombatManager().GetPvECombatRefs())
                    Unit* target = pair.second->GetOther(me);
                    if ((target->GetTypeId() == TYPEID_PLAYER || ((Creature*)target)->IsPet()) && !((Creature*)target)->IsTotem() && target->GetDistance2d(me) <= 12 && target != me->GetVictim())
                        DoCast(target, SPELL_STATIC_DISRUPTION);
                }*/
                me->SetInFront(me->GetVictim());
                StaticDisruption_Timer = (10+rand()%8)*IN_MILLISECONDS; // < 20s
    
                /*float dist = me->GetDistance(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
                if (dist < 5.0f) dist = 5.0f;
                SDisruptAOEVisual_Timer = 1000 + floor(dist / 30 * 1000.0f);*/
            }else StaticDisruption_Timer -= diff;
    
            if (GustOfWind_Timer < diff) {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0, true, true);
                if(!target) target = me->GetVictim();
                DoCast(target, SPELL_GUST_OF_WIND);
                GustOfWind_Timer = (20+rand()%10)*IN_MILLISECONDS; //20 to 30 seconds(bosskillers)
            } else GustOfWind_Timer -= diff;
    
            if (CallLighting_Timer < diff) {
                DoCast(me->GetVictim(), SPELL_CALL_LIGHTNING);
                CallLighting_Timer = (12 + rand()%5)*IN_MILLISECONDS; //totaly random timer. can't find any info on this
            } else CallLighting_Timer -= diff;
    
            if (!isRaining && ElectricalStorm_Timer < 8000 + rand()%5000) {
                SetWeather(WEATHER_STATE_HEAVY_RAIN, 0.9999f);
                isRaining = true;
            }
    
            if (ElectricalStorm_Timer < diff) {
                if (StaticDisruption_Timer < 15000)
                    StaticDisruption_Timer += 15000;
    
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f, true);
                if(!target)
                {
                    EnterEvadeMode();
                    return;
                }
                target->CastSpell(target, 44007, TRIGGERED_FULL_MASK);//cloud visual
                me->CastSpell(target, SPELL_ELECTRICAL_STORM, TRIGGERED_NONE);//storm cyclon + visual
                float x,y,z;
                target->GetPosition(x,y,z);
                if (target)
                {
                    target->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
                    target->MonsterMoveWithSpeed(x, y, me->GetPositionZ()+15, 0);
                }
                Unit *Cloud = me->SummonCreature(WORLD_TRIGGER, x, y, me->GetPositionZ()+16, 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
                if(Cloud)
                {
                    CloudGUID = Cloud->GetGUID();
                    Cloud->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
                    Cloud->StopMoving();
                    Cloud->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
                    Cloud->SetFaction(FACTION_FRIENDLY);
                    Cloud->SetMaxHealth(9999999);
                    Cloud->SetHealth(9999999);
                    Cloud->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
                ElectricalStorm_Timer = 60000; //60 seconds(bosskillers)
                StormCount = 1;
                StormSequenceTimer = 0;
            } else ElectricalStorm_Timer -= diff;
    
            if (SummonEagles_Timer < diff) {
                me->Yell(SAY_ONSUMMON, LANG_UNIVERSAL, nullptr);
                DoPlaySoundToSet(me, SOUND_ONSUMMON);
    
                float x, y, z;
                me->GetPosition(x, y, z);
    
                for (ObjectGuid & BirdGUID : BirdGUIDs)
                {
                    Unit* bird = ObjectAccessor::GetUnit(*me,BirdGUID);
                    if(!bird)//they despawned on die
                    {
                        if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            x = target->GetPositionX() + 10 - rand()%20;
                            y = target->GetPositionY() + 10 - rand()%20;
                            z = target->GetPositionZ() + 6 + rand()%5 + 10;
                            if(z > 95) z = 95 - rand()%5;
                        }
                        Creature *pCreature = me->SummonCreature(MOB_SOARING_EAGLE, x, y, z, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                        if (pCreature)
                        {
                            pCreature->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                            pCreature->GetThreatManager().AddThreat(me->GetVictim(), 1.0f);
                            pCreature->AI()->AttackStart(me->GetVictim());
                            BirdGUID = pCreature->GetGUID();
                        }
                    }
                }
                SummonEagles_Timer = 999999;
            } else SummonEagles_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_akilzonAI(creature);
    }
};


void AddSC_boss_akilzon()
{

    new boss_akilzon();

    new mob_akilzon_eagle();
}

