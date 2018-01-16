
/* ScriptData
SDName: Boss_Kelidan_The_Breaker
SD%Complete: 100
SDComment:
SDCategory: Hellfire Citadel, Blood Furnace
EndScriptData */

/* ContentData
boss_kelidan_the_breaker
mob_shadowmoon_channeler
EndContentData */


#include "blood_furnace.h"

#define SAY_WAKE                    -1542000

#define SAY_ADD_AGGRO_1             -1542001
#define SAY_ADD_AGGRO_2             -1542002
#define SAY_ADD_AGGRO_3             -1542003

#define SAY_KILL_1                  -1542004
#define SAY_KILL_2                  -1542005
#define SAY_NOVA                    -1542006
#define SAY_DIE                     -1542007

#define SPELL_CORRUPTION            30938
#define SPELL_EVOCATION             30935
#define SPELL_BURNING_NOVA          30940

#define SPELL_FIRE_NOVA             33132
#define H_SPELL_FIRE_NOVA           37371

#define SPELL_SHADOW_BOLT_VOLLEY    28599
#define H_SPELL_SHADOW_BOLT_VOLLEY  40070

#define ENTRY_KELIDAN               17377
#define ENTRY_CHANNELER             17653

const float ShadowmoonChannelers[5][4]=
{
    {302,-87.0f,-24.4f,0.157f},
    {321,-63.5f,-24.6f,4.887f},
    {346,-74.5f,-24.6f,3.595f},
    {344,-103.5f,-24.5f,2.356f},
    {316,-109.0f,-24.6f,1.257f}
};

class BurningNovaAura : public Aura
{
    public:
        BurningNovaAura(SpellInfo *spell, uint32 eff, Unit *target, Unit *caster) : Aura(spell, eff, nullptr, target, caster, nullptr){}
};


class boss_kelidan_the_breaker : public CreatureScript
{
public:
    boss_kelidan_the_breaker() : CreatureScript("boss_kelidan_the_breaker")
    { }

    class boss_kelidan_the_breakerAI : public BossAI
    {
        public:
        boss_kelidan_the_breakerAI(Creature* creature) : BossAI(creature, DATA_KELIDAN_THE_BREAKER)
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        bool HeroicMode;
    
        uint32 ShadowVolley_Timer;
        uint32 BurningNova_Timer;
        uint32 Firenova_Timer;
        uint32 Corruption_Timer;
        uint32 check_Timer;
        bool Firenova;
        bool addYell;
        ObjectGuid Channelers[5];
    
        void Reset() override 
        {
            _Reset();

            ShadowVolley_Timer = 1000;
            BurningNova_Timer = 15000;
            Corruption_Timer = 5000;
            check_Timer = 0;
            Firenova = false;
            addYell = false;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            SetCombatMovementAllowed(true);
            SummonChannelers();
        }
    
        void JustEngagedWith(Unit *who) override 
        {
            DoScriptText(SAY_WAKE, me);
            if (me->IsNonMeleeSpellCast(false))
                me->InterruptNonMeleeSpells(true);
            DoStartMovement(who);
            _JustEngagedWith();
        }
        
        void MoveInLineOfSight(Unit* who) override 
        {
            if (me->HasAuraEffect(SPELL_EVOCATION))
                return;
        }
    
        void KilledUnit(Unit* victim) override 
        {
            if (rand()%2)
                return;
    
            DoScriptText(RAND(SAY_KILL_1, SAY_KILL_2), me);
        }
    
        void ChannelerEngaged(Unit* who)
        {
            if (who && !addYell)
            {
                addYell = true;
                /*switch(rand()%3)
                {
                    case 0: DoScriptText(SAY_ADD_AGGRO_1, me); break; // This was wrong anyway, should be who instead of me to make add yell, not self
                    case 1: DoScriptText(SAY_ADD_AGGRO_2, me); break;
                    default: DoScriptText(SAY_ADD_AGGRO_3, me); break;
                }*/
            }
            for(ObjectGuid Channeler : Channelers)
            {
                Creature *channeler = ObjectAccessor::GetCreature(*me, Channeler);
                if(who && channeler && !channeler->IsInCombat())
                    channeler->AI()->AttackStart(who);
            }
        }
    
        void ChannelerDied(Unit* killer)
        {
            for(ObjectGuid& Channeler : Channelers)
            {
                Creature *channeler = ObjectAccessor::GetCreature(*me, Channeler);
                if(channeler && channeler->IsAlive())
                    return;
            }
    
            //release me
            if (killer)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_AGGRESSIVE);
                me->AI()->AttackStart(killer);
            }
        }
    
        ObjectGuid GetChanneled(Creature *channeler1)
        {
            SummonChannelers();
            if (!channeler1)
                return ObjectGuid::Empty;
    
            int i;
            for(i=0; i<5; ++i)
            {
                Creature *channeler = ObjectAccessor::GetCreature(*me, Channelers[i]);
                if(channeler && channeler->GetGUID()==channeler1->GetGUID())
                    break;
            }
            return Channelers[(i+2)%5];
        }
    
        void SummonChannelers()
        {
            if (me->IsDead())
                return;
    
            for(int i=0; i<5; ++i)
            {
                Creature *channeler = ObjectAccessor::GetCreature(*me, Channelers[i]);
                if(!channeler || channeler->IsDead())
                    channeler = me->SummonCreature(ENTRY_CHANNELER,ShadowmoonChannelers[i][0],ShadowmoonChannelers[i][1],ShadowmoonChannelers[i][2],ShadowmoonChannelers[i][3],TEMPSUMMON_CORPSE_TIMED_DESPAWN,300000);
                if (channeler)
                    Channelers[i] = channeler->GetGUID();
                else
                    Channelers[i].Clear();
            }
        }
    
        void JustDied(Unit* Killer) override 
        {
            DoScriptText(SAY_DIE, me);
            _JustDied();
        }
    
        void UpdateAI(const uint32 diff) override 
        {
            if (!UpdateVictim())
            {
                if(check_Timer < diff)
                {
                    if (!me->IsNonMeleeSpellCast(false))
                        DoCast(me,SPELL_EVOCATION);
                    check_Timer = 5000;
                }else check_Timer -= diff;
                return;
            }
            
            float x, y, z, o;
            me->GetHomePosition(x, y, z, o);
            if (me->GetDistance(x, y, z) > 80.0f) {
                EnterEvadeMode();
                return;
            }
    
            if (Firenova)
            {
                if (Firenova_Timer < diff)
                {
                    DoCast(me,HeroicMode ? H_SPELL_FIRE_NOVA : SPELL_FIRE_NOVA,true);
                    Firenova = false;
                    SetCombatMovementAllowed(true);
                    ShadowVolley_Timer = 2000;
                }else Firenova_Timer -=diff;
    
                return;
            }
    
            if (ShadowVolley_Timer < diff)
            {
                DoCast(me,HeroicMode ? H_SPELL_SHADOW_BOLT_VOLLEY : SPELL_SHADOW_BOLT_VOLLEY);
                ShadowVolley_Timer = 5000+rand()%8000;
            }else ShadowVolley_Timer -=diff;
    
            if (Corruption_Timer < diff)
            {
                DoCast(me,SPELL_CORRUPTION);
                Corruption_Timer = 30000+rand()%20000;
            }else Corruption_Timer -=diff;
    
            if (BurningNova_Timer < diff)
            {
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(true);
    
                DoScriptText(SAY_NOVA, me);
    
                if(SpellInfo *nova = (SpellInfo*)sSpellMgr->GetSpellInfo(SPELL_BURNING_NOVA))
                {
                    for(uint32 i = 0; i < 3; ++i)
                        if(nova->Effects[i].Effect == SPELL_EFFECT_APPLY_AURA)
                        {
                            Aura *Aur = new BurningNovaAura(nova, i, me, me);
                            me->AddAura(Aur);
                        }
                }
    
                if (HeroicMode)
                    DoTeleportAll(me->GetPositionX(),me->GetPositionY(),me->GetPositionZ(),me->GetOrientation());
    
                BurningNova_Timer = 20000+rand()%8000;
                Firenova_Timer= 5000;
                Firenova = true;
                SetCombatMovementAllowed(false);
            }else BurningNova_Timer -=diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetBloodFurnaceAI<boss_kelidan_the_breakerAI>(creature);
    }
};


/*######
## mob_shadowmoon_channeler
######*/

#define SPELL_SHADOW_BOLT       12739
#define H_SPELL_SHADOW_BOLT     15472

#define SPELL_MARK_OF_SHADOW    30937
#define SPELL_CHANNELING        39123

#define CHANNELER_SAY_AGGRO_1   -1765300
#define CHANNELER_SAY_AGGRO_2   -1765301
#define CHANNELER_SAY_AGGRO_3   -1765302


class mob_shadowmoon_channeler : public CreatureScript
{
public:
    mob_shadowmoon_channeler() : CreatureScript("mob_shadowmoon_channeler")
    { }

    class mob_shadowmoon_channelerAI : public ScriptedAI
    {
        public:
        mob_shadowmoon_channelerAI(Creature *c) : ScriptedAI(c)
        {
            HeroicMode = me->GetMap()->IsHeroic();
        }
    
        bool HeroicMode;
    
        uint32 ShadowBolt_Timer;
        uint32 MarkOfShadow_Timer;
        uint32 check_Timer;
    
        void Reset()
        override {
            ShadowBolt_Timer = 1000+rand()%1000;
            MarkOfShadow_Timer = 5000+rand()%2000;
            check_Timer = 0;
            if (me->IsNonMeleeSpellCast(false))
                me->InterruptNonMeleeSpells(true);
        }
        
        void JustAppeared()
        override {
            Creature* kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 50.0f, true);
            if (!kelidan)
                me->DisappearAndDie();
        }
    
        void JustEngagedWith(Unit* who)
        override {
            if(Creature *Kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 100))
                ((boss_kelidan_the_breaker::boss_kelidan_the_breakerAI*)Kelidan->AI())->ChannelerEngaged(who);
    
            if (me->IsNonMeleeSpellCast(false))
                me->InterruptNonMeleeSpells(true);
    
            DoScriptText(RAND(CHANNELER_SAY_AGGRO_1, CHANNELER_SAY_AGGRO_2, CHANNELER_SAY_AGGRO_3), me, nullptr);
     
            DoStartMovement(who);
        }
    
        void JustDied(Unit* Killer)
        override {
           if(Creature *Kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 100))
               ((boss_kelidan_the_breaker::boss_kelidan_the_breakerAI*)Kelidan->AI())->ChannelerDied(Killer);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
            {
                if(check_Timer < diff)
                {
                    if (!me->IsNonMeleeSpellCast(false))
                        if(Creature *Kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 100))
                        {
                            ObjectGuid channeler = ((boss_kelidan_the_breaker::boss_kelidan_the_breakerAI*)Kelidan->AI())->GetChanneled(me);
                            if(Unit *channeled = ObjectAccessor::GetUnit(*me, channeler))
                                DoCast(channeled,SPELL_CHANNELING);
                        }
                    check_Timer = 5000;
                }else check_Timer -= diff;
                return;
            }
    
            if (MarkOfShadow_Timer < diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target,SPELL_MARK_OF_SHADOW);
                MarkOfShadow_Timer = 15000+rand()%5000;
            }else MarkOfShadow_Timer -=diff;
    
            if (ShadowBolt_Timer < diff)
            {
                DoCast(me->GetVictim(),HeroicMode ? H_SPELL_SHADOW_BOLT : SPELL_SHADOW_BOLT);
                ShadowBolt_Timer = 5000+rand()%1000;
            }else ShadowBolt_Timer -=diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetBloodFurnaceAI<mob_shadowmoon_channelerAI>(creature);
    }
};

void AddSC_boss_kelidan_the_breaker()
{
    new boss_kelidan_the_breaker();
    new mob_shadowmoon_channeler();
}

