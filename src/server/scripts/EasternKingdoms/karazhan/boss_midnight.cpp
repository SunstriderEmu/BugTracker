
#include "karazhan.h"

#define SAY_MIDNIGHT_KILL           -1532000
#define SAY_APPEAR1                 -1532001
#define SAY_APPEAR2                 -1532002
#define SAY_APPEAR3                 -1532003
#define SAY_MOUNT                   -1532004
#define SAY_KILL1                   -1532005
#define SAY_KILL2                   -1532006
#define SAY_DISARMED                -1532007
#define SAY_DEATH                   -1532008
#define SAY_RANDOM1                 -1532009
#define SAY_RANDOM2                 -1532010
#define EMOTE_CALL_ATTUMEN          -1999933
#define EMOTE_MOUNT                 -1999934

#define SPELL_SHADOWCLEAVE          29832
#define SPELL_INTANGIBLE_PRESENCE   29833
#define SPELL_CHARGE                29847                   //Only when mounted
#define SPELL_KNOCKDOWN             29711

#define MOUNTED_DISPLAYID           16040

//Attumen (TODO: Use the summoning spell instead of creature id. It works , but is not convenient for us)
#define SUMMON_ATTUMEN 15550


class boss_midnight : public CreatureScript
{
public:
    boss_midnight() : CreatureScript("boss_midnight")
    { }

    class boss_midnightAI : public BossAI
    {
        public:
        boss_midnightAI(Creature* creature) : BossAI(creature, DATA_ATTUMEN_EVENT)
        {
        }
    
        ObjectGuid Attumen;
        uint8 Phase;
        uint32 Mount_Timer;
        uint32 KnockDownTimer;
    
        void JustSummoned(Creature* summon) override
        {
            //override this just to block BossAI::JustSummoned, we don't want attumen added to summon list and despawned when we die
        }

        void Reset()
        override 
        {
            _Reset();
            Phase = 1;
            Attumen = ObjectGuid::Empty;
            Mount_Timer = 0;
            KnockDownTimer = urand(20000, 25000);
    
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetVisible(true);
        }
        
        void KilledUnit(Unit *victim)
        override 
        {
            if(Phase == 2)
            {
                if (Unit* pUnit = ObjectAccessor::GetUnit(*me, Attumen))
                    DoScriptText(SAY_MIDNIGHT_KILL, pUnit);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if(Phase == 1 || Phase == 2)
            {
                if(KnockDownTimer < diff)
                {
                    if(DoCast(me->GetVictim(),SPELL_KNOCKDOWN) == SPELL_CAST_OK)
                    {
                        KnockDownTimer = 10000 + rand()%10000;
                    }                
                } else { KnockDownTimer -= diff; }
            }
            
            if(Phase == 1 && (me->IsBelowHPPercent(95.0f)))
            {
                DoScriptText(EMOTE_CALL_ATTUMEN, me);
                Phase = 2;
                Creature *pAttumen = DoSpawnCreature(SUMMON_ATTUMEN, 0, 0, 0, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                if(pAttumen)
                {
                    Attumen = pAttumen->GetGUID();
                    pAttumen->AI()->AttackStart(me->GetVictim());
                    pAttumen->AI()->SetGUID(me->GetGUID(), NPC_MIDNIGHT);
                    switch(rand()%3)
                    {
                    case 0: DoScriptText(SAY_APPEAR1, pAttumen); break;
                    case 1: DoScriptText(SAY_APPEAR2, pAttumen); break;
                    case 2: DoScriptText(SAY_APPEAR3, pAttumen); break;
                    }
                }
            }
            else if(Phase == 2 && (me->IsBelowHPPercent(25.0f)))
            {
                if (Unit *pAttumen = ObjectAccessor::GetUnit(*me, Attumen))
                    Mount(pAttumen);
            }
            else if(Phase ==3)
            {
                if(Mount_Timer)
                {
                    if(Mount_Timer <= diff)
                    {
                        Mount_Timer = 0;
                        me->SetVisible(false);
                        me->GetMotionMaster()->MoveIdle();
                        if (Unit *pAttumen = ObjectAccessor::GetUnit(*me, Attumen))
                        {
                            pAttumen->SetUInt32Value(UNIT_FIELD_DISPLAYID, MOUNTED_DISPLAYID);
                            pAttumen->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            if(pAttumen->GetVictim())
                            {
                                pAttumen->GetMotionMaster()->MoveChase(pAttumen->GetVictim());
                                pAttumen->SetTarget(pAttumen->GetVictim()->GetGUID());
                            }
                            pAttumen->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
                        }
                    } else Mount_Timer -= diff;
                }
            }
    
            if(Phase != 3)
                DoMeleeAttackIfReady();
        }
    
        void Mount(Unit *pAttumen)
        {
            DoScriptText(SAY_MOUNT, pAttumen);
            DoScriptText(EMOTE_MOUNT, me);
            Phase = 3;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            pAttumen->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            float angle = me->GetAngle(pAttumen);
            float distance = me->GetDistance2d(pAttumen);
            float newX = me->GetPositionX() + cos(angle)*(distance/2) ;
            float newY = me->GetPositionY() + sin(angle)*(distance/2) ;
            float newZ = 50;
            //me->Relocate(newX,newY,newZ,angle);
            //me->SendMonsterMove(newX, newY, newZ, 0, true, 1000);
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MovePoint(0, newX, newY, newZ);
            distance += 10;
            newX = me->GetPositionX() + cos(angle)*(distance/2) ;
            newY = me->GetPositionY() + sin(angle)*(distance/2) ;
            pAttumen->GetMotionMaster()->Clear();
            pAttumen->GetMotionMaster()->MovePoint(0, newX, newY, newZ);
            //pAttumen->Relocate(newX,newY,newZ,-angle);
            //pAttumen->SendMonsterMove(newX, newY, newZ, 0, true, 1000);
            Mount_Timer = 1000;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<boss_midnightAI>(creature);
    }
};


class boss_attumen : public CreatureScript
{
public:
    boss_attumen() : CreatureScript("boss_attumen")
    { }

    class boss_attumenAI : public BossAI
    {
        public:
        boss_attumenAI(Creature* creature) : BossAI(creature, DATA_ATTUMEN_EVENT)
        {
            Phase = 1;
    
            CleaveTimer = urand(10000, 15000); 
            CurseTimer = 30000;
            RandomYellTimer = urand(30000, 60000);         //Occasionally yell
            ChargeTimer = 20000;
            ResetTimer = 0;
            KnockDownTimer = 0;
        }
    
        bool mounted;
        ObjectGuid _midnightGUID;
        uint8 Phase;
        uint32 CleaveTimer;
        uint32 CurseTimer;
        uint32 RandomYellTimer;
        uint32 ChargeTimer;                                     //only when mounted
        uint32 ResetTimer;
        uint32 KnockDownTimer;
    
        void Reset()
        override 
        {
            _Reset();
            ResetTimer = 2000;
            CleaveTimer = 15000 + rand()%5000;
            CurseTimer = 30000;
            KnockDownTimer = 10000 + rand()%5000;
        }

        void EnterEvadeMode(EvadeReason /*why*/) override
        {
            //respawn midnight and despawn self
            if (Creature* midnight = ObjectAccessor::GetCreature(*me, _midnightGUID))
                BossAI::_DespawnAtEvade(Seconds(10), midnight);

            me->DespawnOrUnsummon();
        }

        void KilledUnit(Unit *victim)
        override 
        {
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_KILL1, me); break;
            case 1: DoScriptText(SAY_KILL2, me); break;
            }
        }

        void JustDied(Unit *victim)
        override 
        {
            _JustDied();
            DoScriptText(SAY_DEATH, me);
            if (Unit* pMidnight = ObjectAccessor::GetUnit(*me, _midnightGUID))
                pMidnight->DealDamage(pMidnight, pMidnight->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
        }

        void SetGUID(ObjectGuid const& guid, int32 data) override
        {
            if (data == NPC_MIDNIGHT)
                _midnightGUID = guid;
        }

        void UpdateAI(const uint32 diff)
        override 
        {
            if (!UpdateVictim())
                return;
    
            if(me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE ))
                return;
    
            if(CleaveTimer < diff)
            {
                if(DoCast(me->GetVictim(), SPELL_SHADOWCLEAVE) == SPELL_CAST_OK)
                    CleaveTimer = 15000 + rand()%5000;
            } else CleaveTimer -= diff;
    
            if(CurseTimer < diff)
            {
                if (DoCast(me->GetVictim(), SPELL_INTANGIBLE_PRESENCE) == SPELL_CAST_OK)
                    CurseTimer = 30000;
            } else CurseTimer -= diff;
    
            if(RandomYellTimer < diff)
            {
                switch(rand()%2)
                {
                case 0: DoScriptText(SAY_RANDOM1, me); break;
                case 1: DoScriptText(SAY_RANDOM2, me); break;
                }
                RandomYellTimer = 30000 + (rand()%31)*IN_MILLISECONDS;
            } else RandomYellTimer -= diff;
    
            //only when mounted
            if(me->GetUInt32Value(UNIT_FIELD_DISPLAYID) == MOUNTED_DISPLAYID)
            {
                if(ChargeTimer < diff)
                {
                    Unit *target = nullptr;
                    std::list<HostileReference *> t_list = me->GetThreatManager().getThreatList();
                    std::vector<Unit *> target_list;
                    for(auto & itr : t_list)
                    {
                        target = ObjectAccessor::GetUnit(*me, itr->getUnitGuid());
                        if(target && target->GetDistance2d(me) > 5)
                            target_list.push_back(target);
                        target = nullptr;
                    }
                    if(target_list.size())
                        target = *(target_list.begin()+rand()%target_list.size());
    
                    if (target)
                    {
                        DoCast(target, SPELL_CHARGE);
                        ChargeTimer = 20000;
                    }
                } else ChargeTimer -= diff;
    
                if(KnockDownTimer < diff)
                {
                    if(DoCast(me->GetVictim(),SPELL_KNOCKDOWN) == SPELL_CAST_OK)
                        KnockDownTimer = 10000 + rand()%10000;
                } else KnockDownTimer -= diff;
            }
            else
            {
                if(me->IsBelowHPPercent(25.0f))
                {
                    Creature *pMidnight = ObjectAccessor::GetCreature(*me, _midnightGUID);
                    mounted = true;
                    if(pMidnight && pMidnight->GetTypeId() == TYPEID_UNIT)
                    {
                        ((boss_midnight::boss_midnightAI*)(pMidnight->AI()))->Mount(me);
                        me->SetHealth(pMidnight->GetHealth());
                    }
                }
            }
    
            DoMeleeAttackIfReady();
        }
    
        void SpellHit(Unit *source, const SpellInfo *spell)
        override 
        {
            if(spell->Mechanic == MECHANIC_DISARM)
                DoScriptText(SAY_DISARMED, me);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<boss_attumenAI>(creature);
    }
};

void AddSC_boss_attumen()
{
    new boss_attumen();
    new boss_midnight();
}

