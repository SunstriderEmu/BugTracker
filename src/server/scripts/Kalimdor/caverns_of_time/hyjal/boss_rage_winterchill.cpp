//TODO : English translations


#include "def_hyjal.h"
#include "hyjal_trash.h"

enum Spells 
{
    SPELL_FROST_ARMOR      = 31256,
    SPELL_DEATH_AND_DECAY  = 31258,
    SPELL_FROST_NOVA       = 31250,
    SPELL_ICEBOLT          = 31249,
    SPELL_BERSERK          = 26662
};

enum Timers
{
    TIMER_ENRAGE                = 600000,
    TIMER_FROST_ARMOR           = 60000,
    TIMER_ICEBOLT               = 5000,
    TIMER_ICEBOLT_START         = 12000,
    TIMER_DEATH_AND_DECAY       = 30000,
    TIMER_FROST_NOVA            = 30000,
    TIMER_FROST_NOVA_FIRST      = 20000,
};

enum Texts
{
    SAY_ONDEATH = -1801000,
    SAY_ONSLAY1 = -1801001,
    SAY_ONSLAY2 = -1801002,
    SAY_ONSLAY3 = -1801003,
    SAY_DECAY1  = -1801004,
    SAY_DECAY2  = -1801005,
    SAY_NOVA1   = -1801006,
    SAY_NOVA2   = -1801007,
    SAY_ONAGGRO = -1801008
};


class boss_rage_winterchill : public CreatureScript
{
public:
    boss_rage_winterchill() : CreatureScript("boss_rage_winterchill")
    { }

    class boss_rage_winterchillAI : public hyjal_trashAI
    {
        public:
        boss_rage_winterchillAI(Creature *c) : hyjal_trashAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            go = false;
            pos = 0;
        }
    
        uint32 FrostArmorTimer;
        uint32 DecayTimer;
        uint32 NovaTimer;
        uint32 IceboltTimer;
        uint32 BerserkTimer;
        bool go;
        uint32 pos;
    
        void Reset()
        override {
            damageTaken = 0;
            FrostArmorTimer = TIMER_FROST_ARMOR;
            DecayTimer = TIMER_DEATH_AND_DECAY;
            NovaTimer = TIMER_FROST_NOVA_FIRST;
            IceboltTimer = TIMER_ICEBOLT_START;
            BerserkTimer = TIMER_ENRAGE;
    
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_RAGEWINTERCHILLEVENT, NOT_STARTED);
        }
    
        void JustEngagedWith(Unit *who)
        override {
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_RAGEWINTERCHILLEVENT, IN_PROGRESS);
    
            DoScriptText(SAY_ONAGGRO,me);
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(SAY_ONSLAY1 - rand()%3,me);
        }
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            pos = i;
            if (i == 7 && pInstance)
            {
                Unit* target = ObjectAccessor::GetUnit((*me), ObjectGuid(pInstance->GetData64(DATA_JAINAPROUDMOORE)));
                if (target && target->IsAlive())
                    me->GetThreatManager().AddThreat(target,0.0);
            }
        }
    
        void JustDied(Unit *victim)
        override {
            hyjal_trashAI::JustDied(victim);
            if(pInstance && IsEvent)
                pInstance->SetData(DATA_RAGEWINTERCHILLEVENT, DONE);
    
            DoScriptText(SAY_ONDEATH,me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (IsEvent)
            {
                //Must update EscortAI
                EscortAI::UpdateAI(diff);
                if(!go)
                {
                    go = true;
                    if(pInstance)
                    {
                        ((EscortAI*)(me->AI()))->AddWaypoint(0, 4896.08,    -1576.35,    1333.65);
                        ((EscortAI*)(me->AI()))->AddWaypoint(1, 4898.68,    -1615.02,    1329.48);
                        ((EscortAI*)(me->AI()))->AddWaypoint(2, 4907.12,    -1667.08,    1321.00);
                        ((EscortAI*)(me->AI()))->AddWaypoint(3, 4963.18,    -1699.35,    1340.51);
                        ((EscortAI*)(me->AI()))->AddWaypoint(4, 4989.16,    -1716.67,    1335.74);
                        ((EscortAI*)(me->AI()))->AddWaypoint(5, 5026.27,    -1736.89,    1323.02);
                        ((EscortAI*)(me->AI()))->AddWaypoint(6, 5037.77,    -1770.56,    1324.36);
                        ((EscortAI*)(me->AI()))->AddWaypoint(7, 5067.23,    -1789.95,    1321.17);
                        ((EscortAI*)(me->AI()))->Start(true, true, ObjectGuid::Empty);
                        ((EscortAI*)(me->AI()))->SetDespawnAtEnd(false);
                    }
                }
            }
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            if(FrostArmorTimer < diff)
            {
                if(DoCast(me, SPELL_FROST_ARMOR) == SPELL_CAST_OK)
                    FrostArmorTimer = TIMER_FROST_ARMOR;
            } else FrostArmorTimer -= diff;
    
            if(DecayTimer < diff)
            {
                if(DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true), SPELL_DEATH_AND_DECAY) == SPELL_CAST_OK)
                {
                    DecayTimer = TIMER_DEATH_AND_DECAY;
                    DoScriptText(SAY_DECAY1 - rand()%2,me);
                }
            } else DecayTimer -= diff;
    
            if(NovaTimer < diff)
            {
                if(DoCast(me->GetVictim(), SPELL_FROST_NOVA) == SPELL_CAST_OK)
                {
                    NovaTimer = TIMER_FROST_NOVA;
                    DoScriptText(SAY_NOVA1 - rand()%2,me);
                }
            } else NovaTimer -= diff;
    
            if(IceboltTimer < diff)
            {
                if(DoCast(SelectTarget(SELECT_TARGET_RANDOM,0,40.0f,true), SPELL_ICEBOLT) == SPELL_CAST_OK)
                    IceboltTimer = TIMER_ICEBOLT;
            } else IceboltTimer -= diff;
    
            if(BerserkTimer < diff)
            {
                if(DoCast(me,SPELL_BERSERK,true) == SPELL_CAST_OK)
                    BerserkTimer = 300000;
            } else BerserkTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_rage_winterchillAI(creature);
    }
};


void AddSC_boss_rage_winterchill()
{
    new boss_rage_winterchill();
}
