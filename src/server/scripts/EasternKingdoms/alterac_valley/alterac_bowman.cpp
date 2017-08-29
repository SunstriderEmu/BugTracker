#define MAX_RANGE 75.0f
#define SPELL_SHOOT 22121
#define SPELL_INFINITE_ROOT 53107
#define TIMER_SHOOT urand(2000,3000)


class alterac_bowman : public CreatureScript
{
public:
    alterac_bowman() : CreatureScript("alterac_bowman")
    { }

    class alterac_bowmanAI : public ScriptedAI
    {
        public:
        alterac_bowmanAI(Creature *c) : ScriptedAI(c) 
        {   
            shoot_timer = 0;
            SetCombatDistance(80.0f); //Disable melee visual
            SetCombatMovementAllowed(false);
            me->SetSheath(SHEATH_STATE_RANGED);
        }
    
        uint16 shoot_timer;
        uint64 targetGUID;
    
        void JustReachedHome()
        override {
           me->AddAura(SPELL_INFINITE_ROOT,me); //this creature can't be displaced even via CM
        }
    
        void Reset()
        override {   
           targetGUID = 0;
        }
    
        void UpdateAI(const uint32 diff)
        override {    
            if(!targetGUID)
            {
                if(me->GetVictim())
                    EnterEvadeMode();
                return;
            }
    
            Unit* target = ObjectAccessor::GetUnit(*me,targetGUID);
            if(!target)
            {
                targetGUID = 0;
                return;
            }
    
            if(!isValidTarget(target))
            {
                EnterEvadeMode();
                return;
            }
    
            if(me->GetDistance(target) > NOMINAL_MELEE_RANGE)
            {
                if (shoot_timer < diff)
                {
                    if(me->GetVictim() != target)
                    {
                        AttackStart(target);
                    }
                        
                   // me->SetInFront(target);
                    DoCast(target,SPELL_SHOOT,false);
                    shoot_timer = TIMER_SHOOT;
                } else shoot_timer -= diff;
            } else {
                DoMeleeAttackIfReady();
            }
        }
        
        void MoveInLineOfSight(Unit *who)
        override {    
            if (   !targetGUID
                && isValidTarget(who))
                    targetGUID = who->GetGUID();
        }
    
        bool isValidTarget(Unit* target)
        {
            float distance = me->GetDistance(target);
            if (me->CanAggro(target) == CAN_ATTACK_RESULT_OK
                && (distance < MAX_RANGE) 
                && (distance > NOMINAL_MELEE_RANGE)
                && me->IsWithinLOSInMap(target))
                    return true;
            
            return false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new alterac_bowmanAI(creature);
    }
};


void AddSC_alterac_bowman()
{

    new alterac_bowman();
}

