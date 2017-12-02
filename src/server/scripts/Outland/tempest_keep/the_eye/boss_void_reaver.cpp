/* ScriptData
SDName: Boss_Void_Reaver
SD%Complete: 90
SDComment: Should reset if raid are out of room.
SDCategory: Tempest Keep, The Eye
EndScriptData */


#include "def_the_eye.h"

#define SAY_AGGRO                   -1550000
#define SAY_SLAY1                   -1550001
#define SAY_SLAY2                   -1550002
#define SAY_SLAY3                   -1550003
#define SAY_DEATH                   -1550004
#define SAY_POUNDING1               -1550005
#define SAY_POUNDING2               -1550006

#define SPELL_POUNDING              34162 // FIX MY HACK : Damage *= 1.5 in Unit::DealDamage
#define SPELL_ARCANE_ORB            34172
#define SPELL_KNOCK_AWAY            25778
#define SPELL_BERSERK               27680


class boss_void_reaver : public CreatureScript
{
public:
    boss_void_reaver() : CreatureScript("boss_void_reaver")
    { }

    class boss_void_reaverAI : public BossAI
    {
        public:
        boss_void_reaverAI(Creature *c) : BossAI(c, DATA_VOIDREAVER_EVENT)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        uint32 Pounding_Timer;
        uint32 ArcaneOrb_Timer;
        uint32 KnockAway_Timer;
        uint32 Berserk_Timer;
        uint32 EvadeTimer;
    
        bool Enraged;
    
        void Reset()
        override {
            BossAI::Reset();
    
            Pounding_Timer = 15000;
            ArcaneOrb_Timer = 3000;
            KnockAway_Timer = 30000;
            Berserk_Timer = 600000;
            EvadeTimer = 5000;
    
            Enraged = false;
    
             me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
             me->SetFullTauntImmunity(true);
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(RAND(SAY_SLAY1, SAY_SLAY2, SAY_SLAY3), me);
        }
    
        void JustDied(Unit *who)
        override {
            DoScriptText(SAY_DEATH, me);
    
            BossAI::JustDied(who);
        }
    
        void EnterCombat(Unit *who)
        override {
            DoScriptText(SAY_AGGRO, me);
    
            BossAI::EnterCombat(who);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim() )
                return;
            
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
    
            // Pounding
            if(Pounding_Timer < diff)
            {
                //if (!me->IsNonMeleeSpellCast(false))
                //{
                    //DoCast(me->GetVictim(),SPELL_POUNDING); //Not correct, or maybe the spell is not considered as AoE as it should
                    //cast Pounding on ALL the players in ThreatList that are <= 18 yards from Void Reaver
                    //I hope it won't cause freezes...
                    Unit *target = nullptr;
                    std::list<HostileReference *> t_list = me->GetThreatManager().getThreatList();
                    for(auto & itr : t_list)
                    {
                        target = ObjectAccessor::GetUnit(*me, itr->getUnitGuid());
                        Creature *cr = target ? target->ToCreature() : nullptr;
                        Player *pl = target ? target->ToPlayer() : nullptr;
                        if (target && (pl || (cr && cr->IsPet())) && target->GetDistance2d(me) <= 18)
                        {
                            TC_LOG_DEBUG("misc","Casting Pounding on %s", target->GetName().c_str());
                            DoCast(target, SPELL_POUNDING);
                        }
                    }
                    
                    DoScriptText(RAND(SAY_POUNDING1, SAY_POUNDING2), me);
                    Pounding_Timer = 12000;                         // 12 sec.
                    ArcaneOrb_Timer += 3500;            // Add 3.5 sec on the timer to prevent interrupting Pounding
                    KnockAway_Timer += 3500;
                //}
                //else Pounding_Timer += 300;     // Do it at next update
            }else Pounding_Timer -= diff;
    
            // Arcane Orb
            if(ArcaneOrb_Timer < diff)
            {
                //if (!me->IsNonMeleeSpellCast(false))
                //{
                    Unit *target = nullptr;
                    std::list<HostileReference *> t_list = me->GetThreatManager().getThreatList();
                    std::vector<Unit *> target_list;
                    for(auto & itr : t_list)
                    {
                        target = ObjectAccessor::GetUnit(*me, itr->getUnitGuid());
                        if (!target)
                            continue;
                        
                                                                    //18 yard radius minimum
                        if(target && target->GetTypeId() == TYPEID_PLAYER && target->IsAlive() && target->GetDistance2d(me) >= 18)
                            target_list.push_back(target);
                        target = nullptr;
                    }
                    if(target_list.size())
                        target = *(target_list.begin()+rand()%target_list.size());
    
                    if (target)
                        me->CastSpell(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), SPELL_ARCANE_ORB, TRIGGERED_NONE);
                    else if (me->GetVictim())   // If no target >= 18 meters, cast Arcane Orb on the tank
                        me->CastSpell(me->GetVictim()->GetPositionX(),me->GetVictim()->GetPositionY(),me->GetVictim()->GetPositionZ(), SPELL_ARCANE_ORB, TRIGGERED_NONE);
    
                    ArcaneOrb_Timer = 3000;
                //}
                //else ArcaneOrb_Timer += 300;    // Do it at next update
            }else ArcaneOrb_Timer -= diff;
    
            // Single Target knock back, reduces aggro
            if(KnockAway_Timer < diff)
            {
                //if (!me->IsNonMeleeSpellCast(false))
                //{
                    DoCast(me->GetVictim(),SPELL_KNOCK_AWAY);
    
                    //Drop 25% aggro
                    if(me->GetThreat(me->GetVictim()))
                        DoModifyThreatPercent(me->GetVictim(),-25);
    
                    KnockAway_Timer = 30000;
                //}
                //else KnockAway_Timer += 300;    // Do it at next update
            }else KnockAway_Timer -= diff;
    
            //Berserk
            if(Berserk_Timer < diff && !Enraged)
            {
                me->InterruptNonMeleeSpells(false);
                DoCast(me,SPELL_BERSERK);
                Enraged = true;
            }else Berserk_Timer -= diff;
            
            //Check distance from center of the room
            if(EvadeTimer < diff)
            {
                float sx = 432.59f;
                float sy = 371.93f;
                float dX, dY, ax, ay, az, center_distance;
                me->GetPosition(ax, ay, az);
                dX = sx - ax; dY = sy - ay;
                center_distance = sqrt( ( dX * dX ) + ( dY * dY ) );
                if(center_distance > 105.0f)
                {
                    EnterEvadeMode();
                }
                EvadeTimer = 5000;
            } else EvadeTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_void_reaverAI(creature);
    }
};


void AddSC_boss_void_reaver()
{
    new boss_void_reaver();
}

