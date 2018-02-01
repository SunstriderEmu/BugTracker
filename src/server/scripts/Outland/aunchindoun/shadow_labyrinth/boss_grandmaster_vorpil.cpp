
/* ScriptData
SDName: Boss_Grandmaster_Vorpil
SD%Complete: 100
SDComment:
SDCategory: Auchindoun, Shadow Labyrinth
EndScriptData */


#include "def_shadow_labyrinth.h"
#include "GameEventMgr.h"

#define SAY_INTRO                       -1555028
#define SAY_AGGRO1                      -1555029
#define SAY_AGGRO2                      -1555030
#define SAY_AGGRO3                      -1555031
#define SAY_HELP                        -1555032
#define SAY_SLAY1                       -1555033
#define SAY_SLAY2                       -1555034
#define SAY_DEATH                       -1555035

#define SPELL_RAIN_OF_FIRE          33617
#define H_SPELL_RAIN_OF_FIRE        39363

#define SPELL_DRAW_SHADOWS          33563
#define SPELL_SHADOWBOLT_VOLLEY     33841
#define SPELL_BANISH                38791

#define MOB_VOID_TRAVELER           19226
#define SPELL_SACRIFICE             33587
#define SPELL_SHADOW_NOVA           33846
#define SPELL_EMPOWERING_SHADOWS    33783
#define H_SPELL_EMPOWERING_SHADOWS  39364

#define MOB_VOID_PORTAL             19224
#define SPELL_VOID_PORTAL_VISUAL    33569

float VorpilPosition[3] = {-252.8820f, -264.3030f, 17.1f};

float VoidPortalCoords[5][3] =
{
    {-283.5894f, -239.5718f, 12.7f},
    {-306.5853f, -258.4539f, 12.7f},
    {-295.8789f, -269.0899f, 12.7f},
    {-209.3401f, -262.7564f, 17.1f},
    {-261.4533f, -297.3298f, 17.1f}
};

class mob_voidtraveler : public CreatureScript
{
public:
    mob_voidtraveler() : CreatureScript("mob_voidtraveler")
    { }

    class mob_voidtravelerAI : public ScriptedAI
    {
        public:
        mob_voidtravelerAI(Creature *c) : ScriptedAI(c)
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        bool HeroicMode;
        Unit *Vorpil;
        uint32 move;
        bool sacrificed;
    
        void Reset()
        override {
            Vorpil = nullptr;
            move = 0;
            sacrificed = false;
        }
    
        void JustEngagedWith(Unit *who)override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if(!Vorpil || Vorpil->IsDead())
            {
                me->DisappearAndDie();
                return;
            }
            if(move < diff)
            {
                if(sacrificed)
                {
                    uint32 spellId = HeroicMode ? H_SPELL_EMPOWERING_SHADOWS : SPELL_EMPOWERING_SHADOWS;
                    me->CastSpell(Vorpil, spellId);
                    DoCast(me, SPELL_SHADOW_NOVA, true);
                    me->KillSelf(); //spell should already kill us
                    return;
                }
                me->GetMotionMaster()->MoveFollow(Vorpil,0,0);
                if(me->GetDistance(Vorpil) < 3)
                {
                    DoCast(me, SPELL_SACRIFICE, false);
                    sacrificed = true;
                    move = 500;
                    return;
                }
                if(!Vorpil->IsInCombat() || Vorpil->IsDead())
                {
                    me->DespawnOrUnsummon();
                    return;
                }
                move = 1000;
            }else move -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetShadowLabyrinthAI<mob_voidtravelerAI>(creature);
    }
};


class boss_grandmaster_vorpil : public CreatureScript
{
public:
    boss_grandmaster_vorpil() : CreatureScript("boss_grandmaster_vorpil")
    { }

    class boss_grandmaster_vorpilAI : public BossAI
    {
        public:
        boss_grandmaster_vorpilAI(Creature* creature) : BossAI(creature, DATA_GRANDMASTER_VORPIL)
        {
            HeroicMode = me->GetMap()->IsHeroic();
            Intro = false;
        }
    
        bool Intro, HelpYell;
        bool sumportals;
        bool HeroicMode;
    
        uint32 ShadowBoltVolley_Timer;
        uint32 DrawShadows_Timer;
        uint32 summonTraveler_Timer;
        uint32 banish_Timer;
        ObjectGuid PortalsGuid[5];
        
        bool isEventActive()
        {
            const GameEventMgr::ActiveEvents& activeEvents = sGameEventMgr->GetActiveEventList();
            bool active = activeEvents.find(57) != activeEvents.end();
    
            return active;
        }
    
        void Reset()
        override {
            ShadowBoltVolley_Timer = 15000;
            DrawShadows_Timer = 45000;
            summonTraveler_Timer = 90000;
            banish_Timer = 17000;
            HelpYell = false;
            destroyPortals();
    
            _Reset();
            if (isEventActive())
                me->SetDisplayId(22801);
        }
    
        void summonPortals()
        {
            if(!sumportals)
            {
                for (int i = 0;i<5;i++)
                {
                    Creature *Portal = nullptr;
                    Portal = me->SummonCreature(MOB_VOID_PORTAL,VoidPortalCoords[i][0],VoidPortalCoords[i][1],VoidPortalCoords[i][2],0,TEMPSUMMON_CORPSE_DESPAWN,3000000);
                    if(Portal)
                    {
                        PortalsGuid[i] = Portal->GetGUID();
                        Portal->CastSpell(Portal, SPELL_VOID_PORTAL_VISUAL, TRIGGERED_NONE);
                        Portal->SetControlled(true, UNIT_STATE_ROOT);
                    }
                }
                sumportals = true;
                summonTraveler_Timer = 5000;
            }
        }
    
        void destroyPortals()
        {
            if(sumportals)
            {
                for (ObjectGuid & i : PortalsGuid)
                {
                    Unit *Portal = ObjectAccessor::GetUnit((*me), i);
                    if (Portal && Portal->IsAlive())
                        Portal->KillSelf();
                    i = ObjectGuid::Empty;
                }
                sumportals = false;
            }
        }
    
        void spawnVoidTraveler()
        {
            int pos = rand()%5;
            me->SummonCreature(MOB_VOID_TRAVELER,VoidPortalCoords[pos][0],VoidPortalCoords[pos][1],VoidPortalCoords[pos][2],0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,5000);
            if(!HelpYell)
            {
                DoScriptText(SAY_HELP, me);
                HelpYell = true;
            }
        }
    
        void JustSummoned(Creature *summoned)
        override {
            BossAI::JustSummoned(summoned);
            if (summoned && summoned->GetEntry() == MOB_VOID_TRAVELER)
                ((mob_voidtraveler::mob_voidtravelerAI*)summoned->AI())->Vorpil = me;
        }
    
        void KilledUnit(Unit *victim)
        override {
            switch(rand()%2)
            {
                case 0: DoScriptText(SAY_SLAY1, me); break;
                case 1: DoScriptText(SAY_SLAY2, me); break;
            }
        }
    
        void JustDied(Unit *victim)
        override {
            DoScriptText(SAY_DEATH, me);
            destroyPortals();
            _JustDied();
        }
    
        void JustEngagedWith(Unit *who)
        override {
            switch(rand()%3)
            {
                case 0: DoScriptText(SAY_AGGRO1, me); break;
                case 1: DoScriptText(SAY_AGGRO2, me); break;
                case 2: DoScriptText(SAY_AGGRO3, me); break;
            }
            summonPortals();
            _JustEngagedWith();
        }
    
        void MoveInLineOfSight(Unit *who)
        override {
            if(who && !me->GetVictim() && me->CanAggro(who) == CAN_ATTACK_RESULT_OK)
                AttackStart(who);
            if (!Intro && who && me->IsWithinLOSInMap(who)&& me->IsWithinDistInMap(who, 100) && me->IsHostileTo(who))
            {
                DoScriptText(SAY_INTRO, me);
                Intro = true;
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if (ShadowBoltVolley_Timer < diff)
            {
                DoCast(me,SPELL_SHADOWBOLT_VOLLEY);
                ShadowBoltVolley_Timer = 15000;
            }else ShadowBoltVolley_Timer -= diff;
    
            if (HeroicMode && banish_Timer < diff)
            {
                Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0,30,false);
                if (target)
                {
                    DoCast(target,SPELL_BANISH);
                    banish_Timer = 16000;
                }
            }else banish_Timer -= diff;
    
            if ( DrawShadows_Timer < diff)
            {
                Map *map = me->GetMap();
                Map::PlayerList const &PlayerList = map->GetPlayers();
                for(const auto & i : PlayerList)
                    if (Player* i_pl = i.GetSource())
                        if (i_pl->IsAlive() && !i_pl->HasAuraEffect(SPELL_BANISH,0) && i_pl->IsAttackableByAOE())
                            i_pl->TeleportTo(me->GetMapId(), VorpilPosition[0],VorpilPosition[1],VorpilPosition[2], 0, TELE_TO_NOT_LEAVE_COMBAT);
    
                me->Relocate(VorpilPosition[0],VorpilPosition[1],VorpilPosition[2]);
                DoCast(me,SPELL_DRAW_SHADOWS,true);
    
                DoCast(me,HeroicMode?H_SPELL_RAIN_OF_FIRE:SPELL_RAIN_OF_FIRE);
    
                ShadowBoltVolley_Timer = 6000;
                DrawShadows_Timer = 30000;
            }else DrawShadows_Timer -= diff;
    
            if ( summonTraveler_Timer < diff)
            {
                spawnVoidTraveler();
                summonTraveler_Timer = 10000;
                //enrage at 20%
                if((me->GetHealth()*5) < me->GetMaxHealth())
                    summonTraveler_Timer = 5000;
            }else summonTraveler_Timer -=diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetShadowLabyrinthAI<boss_grandmaster_vorpilAI>(creature);
    }
};


void AddSC_boss_grandmaster_vorpil()
{
    new boss_grandmaster_vorpil();
    new mob_voidtraveler();
}

