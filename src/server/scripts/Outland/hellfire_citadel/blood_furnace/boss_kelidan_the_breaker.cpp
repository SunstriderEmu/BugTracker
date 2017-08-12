
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


#include "def_blood_furnace.h"

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
    {302,-87,-24.4,0.157},
    {321,-63.5,-24.6,4.887},
    {346,-74.5,-24.6,3.595},
    {344,-103.5,-24.5,2.356},
    {316,-109,-24.6,1.257}
};

class BurningNovaAura : public Aura
{
    public:
        BurningNovaAura(SpellInfo *spell, uint32 eff, Unit *target, Unit *caster) : Aura(spell, eff, nullptr, target, caster, nullptr){}
};

struct boss_kelidan_the_breakerAI : public ScriptedAI
{
    boss_kelidan_the_breakerAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        HeroicMode = me->GetMap()->IsHeroic();
        for(uint64 & Channeler : Channelers) Channeler = 0;
    }

    InstanceScript* pInstance;
    bool HeroicMode;

    uint32 ShadowVolley_Timer;
    uint32 BurningNova_Timer;
    uint32 Firenova_Timer;
    uint32 Corruption_Timer;
    uint32 check_Timer;
    bool Firenova;
    bool addYell;
    uint64 Channelers[5];

    void Reset()
    override {
        ShadowVolley_Timer = 1000;
        BurningNova_Timer = 15000;
        Corruption_Timer = 5000;
        check_Timer = 0;
        Firenova = false;
        addYell = false;
        SummonChannelers();
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetReactState(REACT_PASSIVE);
        SetCombatMovementAllowed(true);
        if (pInstance && me->IsAlive())
            pInstance->SetData(DATA_KELIDANEVENT, NOT_STARTED);
    }

    void EnterCombat(Unit *who)
    override {
        DoScriptText(SAY_WAKE, me);
        if (me->IsNonMeleeSpellCast(false))
            me->InterruptNonMeleeSpells(true);
        DoStartMovement(who);
        if (pInstance)
            pInstance->SetData(DATA_KELIDANEVENT, IN_PROGRESS);
    }
    
    void MoveInLineOfSight(Unit* who)
    override {
        if (me->HasAuraEffect(SPELL_EVOCATION))
            return;
    }

    void KilledUnit(Unit* victim)
    override {
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
        for(uint64 Channeler : Channelers)
        {
            Creature *channeler = ObjectAccessor::GetCreature(*me, Channeler);
            if(who && channeler && !channeler->IsInCombat())
                channeler->AI()->AttackStart(who);
        }
    }

    void ChannelerDied(Unit* killer)
    {
        for(uint64 Channeler : Channelers)
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

    uint64 GetChanneled(Creature *channeler1)
    {
        SummonChannelers();
        if(!channeler1) 
            return 0;

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
            if(channeler)
                Channelers[i] = channeler->GetGUID();
            else
                Channelers[i] = 0;
        }
    }

    void JustDied(Unit* Killer)
    override {
        DoScriptText(SAY_DIE, me);
        if(pInstance)
            pInstance->SetData(DATA_KELIDANEVENT, DONE);
    }

    void UpdateAI(const uint32 diff)
    override {
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

CreatureAI* GetAI_boss_kelidan_the_breaker(Creature *_Creature)
{
    return new boss_kelidan_the_breakerAI (_Creature);
}

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

struct mob_shadowmoon_channelerAI : public ScriptedAI
{
    mob_shadowmoon_channelerAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        HeroicMode = me->GetMap()->IsHeroic();
    }

    InstanceScript* pInstance;
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
    
    void JustRespawned()
    override {
        Creature* kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 50.0f, true);
        if (!kelidan)
            me->Kill(me);
    }

    void EnterCombat(Unit* who)
    override {
        if(Creature *Kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 100))
            ((boss_kelidan_the_breakerAI*)Kelidan->AI())->ChannelerEngaged(who);

        if (me->IsNonMeleeSpellCast(false))
            me->InterruptNonMeleeSpells(true);

        DoScriptText(RAND(CHANNELER_SAY_AGGRO_1, CHANNELER_SAY_AGGRO_2, CHANNELER_SAY_AGGRO_3), me, nullptr);

        DoStartMovement(who);
    }

    void JustDied(Unit* Killer)
    override {
       if(Creature *Kelidan = me->FindNearestCreature(ENTRY_KELIDAN, 100))
           ((boss_kelidan_the_breakerAI*)Kelidan->AI())->ChannelerDied(Killer);
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
                        uint64 channeler = ((boss_kelidan_the_breakerAI*)Kelidan->AI())->GetChanneled(me);
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

CreatureAI* GetAI_mob_shadowmoon_channeler(Creature *_Creature)
{
    return new mob_shadowmoon_channelerAI (_Creature);
}

void AddSC_boss_kelidan_the_breaker()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="boss_kelidan_the_breaker";
    newscript->GetAI = &GetAI_boss_kelidan_the_breaker;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="mob_shadowmoon_channeler";
    newscript->GetAI = &GetAI_mob_shadowmoon_channeler;
    sScriptMgr->RegisterOLDScript(newscript);
}

