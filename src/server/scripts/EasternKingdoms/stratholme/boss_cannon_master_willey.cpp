
/* ScriptData
SDName: boss_cannon_master_willey
SD%Complete: 100
SDComment:
SDCategory: Stratholme
EndScriptData */


#include "def_stratholme.h"
#include "GameEventMgr.h"

struct Location
{
    float x, y, z, o;
};

static Location SpawnLocations[] =
{
    { 3553.85f, -2945.88f, 125.001f, 0.592f },
    { 3559.20f, -2952.92f, 125.001f, 0.592f },
    { 3552.41f, -2948.66f, 125.001f, 0.592f },
    { 3555.65f, -2953.51f, 125.001f, 0.592f },
    { 3547.92f, -2950.97f, 125.001f, 0.592f },
    { 3553.09f, -2952.12f, 125.001f, 0.592f },
    { 3552.72f, -2957.77f, 125.001f, 0.592f },
    { 3547.15f, -2953.16f, 125.001f, 0.592f },
    { 3550.20f, -2957.43f, 125.001f, 0.592f }
};

enum eWilleySpells {
    SPELL_KNOCKAWAY     = 10101,
    SPELL_PUMMEL        = 15615,
    SPELL_SHOOT         = 16496
};
//#define SPELL_SUMMONCRIMSONRIFLEMAN    17279

class boss_cannon_master_willey : public CreatureScript
{
public:
    boss_cannon_master_willey() : CreatureScript("boss_cannon_master_willey")
    { }

    class boss_cannon_master_willeyAI : public ScriptedAI
    {
        public:
        boss_cannon_master_willeyAI(Creature *c) : ScriptedAI(c), summons(me) {}
    
        uint32 KnockAway_Timer;
        uint32 Pummel_Timer;
        uint32 Shoot_Timer;
        uint32 SummonRifleman_Timer;
        
        SummonList summons;
    
        bool isEventActive()
        {
            const GameEventMgr::ActiveEvents& activeEvents = sGameEventMgr->GetActiveEventList();
            bool active = activeEvents.find(57) != activeEvents.end();
    
            return active;
        }
    
        void Reset() override
        {
            Shoot_Timer = 1000;
            Pummel_Timer = 7000;
            KnockAway_Timer = 11000;
            SummonRifleman_Timer = 10000;
            
            if (InstanceScript* pInstance = ((InstanceScript*)me->GetInstanceScript()))
                pInstance->SetData(TYPE_CANNONMASTER, FAIL);
                
            summons.DespawnAll();
            
            if (isEventActive())
                me->SetDisplayId(15733);
        }
    
        void JustDied(Unit* Victim) override
        {
            summons.DespawnAll();
        }
        
        void JustSummoned(Creature* pSummon) override
        {
            summons.Summon(pSummon);
            
            /*if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                pSummon->AI()->AttackStart(target);*/
        }
        
        void SummonedCreatureDespawn(Creature* pSummon) override { summons.Despawn(pSummon); }
    
        void EnterCombat(Unit *who) override
        {
            if (InstanceScript* pInstance = ((InstanceScript*)me->GetInstanceScript()))
                pInstance->SetData(TYPE_CANNONMASTER, IN_PROGRESS);
        }
        
        void CannonFired()
        {
            summons.DespawnAll();
        }
    
        void UpdateAI(const uint32 diff) override
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;
    
            //Pummel
            if (Pummel_Timer < diff)
            {
                //Cast
                if (rand()%100 < 90) //90% chance to cast
                    DoCast(me->GetVictim(),SPELL_PUMMEL);
                //12 seconds until we should cast this again
                Pummel_Timer = 12000;
            }else Pummel_Timer -= diff;
    
            //KnockAway
            if (KnockAway_Timer < diff)
            {
                //Cast
                if (rand()%100 < 80) //80% chance to cast
                    DoCast(me->GetVictim(),SPELL_KNOCKAWAY);
                //14 seconds until we should cast this again
                KnockAway_Timer = 14000;
            }else KnockAway_Timer -= diff;
    
            //Shoot
            if (Shoot_Timer < diff)
            {
                //Cast
                DoCast(me->GetVictim(),SPELL_SHOOT);
                //1 seconds until we should cast this again
                Shoot_Timer = 1000;
            }else Shoot_Timer -= diff;
    
            //SummonRifleman
            if (SummonRifleman_Timer < diff)
            {
                //Cast
                switch (rand()%9)
                {
                case 0:
                    me->SummonCreature(11054, SpawnLocations[0].x, SpawnLocations[0].y, SpawnLocations[0].z, SpawnLocations[0].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[1].x, SpawnLocations[1].y, SpawnLocations[1].z, SpawnLocations[1].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[3].x, SpawnLocations[3].y, SpawnLocations[3].z, SpawnLocations[3].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    break;
                case 1:
                    me->SummonCreature(11054, SpawnLocations[1].x, SpawnLocations[1].y, SpawnLocations[1].z, SpawnLocations[1].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[2].x, SpawnLocations[2].y, SpawnLocations[2].z, SpawnLocations[2].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[4].x, SpawnLocations[4].y, SpawnLocations[4].z, SpawnLocations[4].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    break;
                case 2:
                    me->SummonCreature(11054, SpawnLocations[2].x, SpawnLocations[2].y, SpawnLocations[2].z, SpawnLocations[2].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[3].x, SpawnLocations[3].y, SpawnLocations[3].z, SpawnLocations[3].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[5].x, SpawnLocations[5].y, SpawnLocations[5].z, SpawnLocations[5].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    break;
                case 3:
                    me->SummonCreature(11054, SpawnLocations[3].x, SpawnLocations[3].y, SpawnLocations[3].z, SpawnLocations[3].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[4].x, SpawnLocations[4].y, SpawnLocations[4].z, SpawnLocations[4].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[6].x, SpawnLocations[6].y, SpawnLocations[6].z, SpawnLocations[6].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    break;
                case 4:
                    me->SummonCreature(11054, SpawnLocations[4].x, SpawnLocations[4].y, SpawnLocations[4].z, SpawnLocations[4].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[5].x, SpawnLocations[5].y, SpawnLocations[5].z, SpawnLocations[5].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[7].x, SpawnLocations[7].y, SpawnLocations[7].z, SpawnLocations[7].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    break;
                case 5:
                    me->SummonCreature(11054, SpawnLocations[5].x, SpawnLocations[5].y, SpawnLocations[5].z, SpawnLocations[5].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[6].x, SpawnLocations[6].y, SpawnLocations[6].z, SpawnLocations[6].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[8].x, SpawnLocations[8].y, SpawnLocations[8].z, SpawnLocations[8].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    break;
                case 6:
                    me->SummonCreature(11054, SpawnLocations[6].x, SpawnLocations[6].y, SpawnLocations[6].z, SpawnLocations[6].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[7].x, SpawnLocations[7].y, SpawnLocations[7].z, SpawnLocations[7].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[0].x, SpawnLocations[0].y, SpawnLocations[0].z, SpawnLocations[0].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    break;
                case 7:
                    me->SummonCreature(11054, SpawnLocations[7].x, SpawnLocations[7].y, SpawnLocations[7].z, SpawnLocations[7].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[8].x, SpawnLocations[8].y, SpawnLocations[8].z, SpawnLocations[8].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[1].x, SpawnLocations[1].y, SpawnLocations[1].z, SpawnLocations[1].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    break;
                case 8:
                    me->SummonCreature(11054, SpawnLocations[8].x, SpawnLocations[8].y, SpawnLocations[8].z, SpawnLocations[8].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[0].x, SpawnLocations[0].y, SpawnLocations[0].z, SpawnLocations[0].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    me->SummonCreature(11054, SpawnLocations[2].x, SpawnLocations[2].y, SpawnLocations[2].z, SpawnLocations[2].o, TEMPSUMMON_TIMED_DESPAWN, 240000);
                    break;
                }
                //30 seconds until we should cast this again
                SummonRifleman_Timer = 30000;
            }else SummonRifleman_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_cannon_master_willeyAI(creature);
    }
};


class ScarletCannon : public GameObjectScript
{
public:
    ScarletCannon() : GameObjectScript("go_scarlet_cannon")
    {}

    struct ScarletCannonAI : public GameObjectAI
    {
        ScarletCannonAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (Creature* willey = me->FindNearestCreature(10997, 10.0f, true)) {
                CAST_AI(boss_cannon_master_willey::boss_cannon_master_willeyAI, (willey->AI()))->CannonFired();
                me->Respawn();

                return false;
            }

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ScarletCannonAI(go);
    }
};

void AddSC_boss_cannon_master_willey()
{
    
    new boss_cannon_master_willey();
    
    new ScarletCannon();
}

