/* Copyright (C) 2008 - 2009 BroodWyrm */


#include "def_shattered_halls.h"

#define SPELL_BLADE_DANCE               30739
#define H_SPELL_CHARGE                  25821

#define TARGET_NUM                      5

#define MOB_SHATTERED_ASSASSIN          17695
#define MOB_HEARTHEN_GUARD              17621
#define MOB_SHARPSHOOTER_GUARD          17622
#define MOB_REAVER_GUARD                17623

float AssassEntrance[3] = {275.136,-84.29,2.3}; // y +-8
float AssassExit[3] = {184.233,-84.29,2.3}; // y +-8
float AddsEntrance[3] = {306.036,-84.29,1.93};

#define SOUND_AGGRO1                    10323
#define SAY_AGGRO1                      "Ours is the true Horde! The only Horde!"
#define SOUND_AGGRO2                    10324
#define SAY_AGGRO2                      "I'll carve the meat from your bones!"
#define SOUND_AGGRO3                    10325
#define SAY_AGGRO3                      "I am called Bladefist for a reason, as you will see!"
#define SOUND_SLAY1                     10326
#define SAY_SLAY1                       "For the real Horde!"
#define SOUND_SLAY2                     10327
#define SAY_SLAY2                       "I am the only Warchief!"
#define SOUND_DEATH                     10328
#define SAY_DEATH                       "The true Horde... will.. prevail.."

struct boss_warchief_kargath_bladefistAI : public ScriptedAI
{
    boss_warchief_kargath_bladefistAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        HeroicMode = me->GetMap()->IsHeroic();
    }

    InstanceScript* pInstance;
    bool HeroicMode;

    std::vector<uint64> adds;
    std::vector<uint64> assassins;

    uint32 Charge_timer;
    uint32 Blade_Dance_Timer;
    uint32 Summon_Assistant_Timer;
    uint32 resetcheck_timer;
    uint32 Wait_Timer;

    uint32 Assassins_Timer;

    uint32 summoned;
    bool InBlade;

    uint32 target_num;

    void Reset()
    override {
        removeAdds();

        me->SetSpeedRate(MOVE_RUN,2);
        me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);

        summoned = 2;
        InBlade = false;
        Wait_Timer = 0;

        Charge_timer = 0;
        Blade_Dance_Timer = 30000;
        Summon_Assistant_Timer = 20000;
        Assassins_Timer = 5000;
        resetcheck_timer = 5000;
        
        if (pInstance && pInstance->GetData(DATA_BLADEFIST_EVENT) != DONE)
            pInstance->SetData(DATA_BLADEFIST_EVENT, NOT_STARTED);
    }

    void EnterCombat(Unit *who)
    override {
        switch (rand()%3)
        {
        case 0:
            DoPlaySoundToSet(me,SOUND_AGGRO1);
            me->Yell(SAY_AGGRO1,LANG_UNIVERSAL,nullptr);
            break;
        case 1:
            DoPlaySoundToSet(me,SOUND_AGGRO2);
            me->Yell(SAY_AGGRO2,LANG_UNIVERSAL,nullptr);
            break;
        case 2:
            DoPlaySoundToSet(me,SOUND_AGGRO3);
            me->Yell(SAY_AGGRO3,LANG_UNIVERSAL,nullptr);
            break;
        }
        
        if (pInstance)
            pInstance->SetData(DATA_BLADEFIST_EVENT, IN_PROGRESS);
    }

    void JustSummoned(Creature* _summoned)
    override {
        switch(_summoned->GetEntry())
        {
            case MOB_HEARTHEN_GUARD:
            case MOB_SHARPSHOOTER_GUARD:
            case MOB_REAVER_GUARD:
				_summoned->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM,0));
                adds.push_back(_summoned->GetGUID());
                break;
            case MOB_SHATTERED_ASSASSIN:
                assassins.push_back(_summoned->GetGUID());
                break;
        }
    }

    void KilledUnit(Unit *victim)
    override {
        if(victim->GetTypeId() == TYPEID_PLAYER)
        {
            switch(rand()%2)
            {
            case 0:
                DoPlaySoundToSet(me, SOUND_SLAY1);
                me->Yell(SAY_SLAY1,LANG_UNIVERSAL,nullptr);
                break;
            case 1:
                DoPlaySoundToSet(me, SOUND_SLAY2);
                me->Yell(SAY_SLAY2,LANG_UNIVERSAL,nullptr);
                break;
            }
        }
    }

    void JustDied(Unit* Killer)
    override {
        DoPlaySoundToSet(me, SOUND_DEATH);
        me->Yell(SAY_DEATH,LANG_UNIVERSAL,nullptr);
        removeAdds();
        
        // Remove NOT_ATTACKABLE flag on the Executioner
        if (pInstance) {
            pInstance->SetData(DATA_BLADEFIST_EVENT, DONE);
            if (Creature* Executioner = ObjectAccessor::GetCreature((*me), pInstance->GetData64(DATA_EXECUTIONER_GUID)))
                Executioner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        }
    }

    void MovementInform(uint32 type, uint32 id)
    override {
        if(InBlade)
        {
            if(type != POINT_MOTION_TYPE)
                return;

            if(id != 1)
                return;

            if(target_num > 0) // to prevent loops
            {
                Wait_Timer = 1;
                DoCast(me,SPELL_BLADE_DANCE,true);
                target_num--;
            }
        }
    }

    void removeAdds()
    {
        for(uint64 & add : adds)
        {
            Creature* c = ObjectAccessor::GetCreature((*me),add);
            if (c)
            {
                c->SetDisableReputationGain(true); //no reputation gain
                c->DespawnOrUnsummon();
            }
        }
        adds.clear();

        for(uint64 & assassin : assassins)
        {
            Creature* c = ObjectAccessor::GetCreature((*me), assassin);
            if (c)
            {
                c->SetDisableReputationGain(true); //no reputation gain
                c->DespawnOrUnsummon();
            }
        }
        assassins.clear();
    }
    void SpawnAssassin()
    {
        me->SummonCreature(MOB_SHATTERED_ASSASSIN,AssassEntrance[0],AssassEntrance[1]+8, AssassEntrance[2], 0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10000);
        me->SummonCreature(MOB_SHATTERED_ASSASSIN,AssassEntrance[0],AssassEntrance[1]-8, AssassEntrance[2], 0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10000);
        me->SummonCreature(MOB_SHATTERED_ASSASSIN,AssassExit[0],AssassExit[1]+8, AssassExit[2], 0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10000);
        me->SummonCreature(MOB_SHATTERED_ASSASSIN,AssassExit[0],AssassExit[1]-8, AssassExit[2], 0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10000);
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim() )
            return;

        if(Assassins_Timer)
        {
            if(Assassins_Timer <= diff)
            {
                SpawnAssassin();
                Assassins_Timer = 0;
            } else Assassins_Timer -= diff;
        }
        
        if(InBlade)
        {
            if(Wait_Timer)
            {
                if(Wait_Timer <= diff)
                {
                    if(target_num <= 0)
                    {
                        // stop bladedance
                        InBlade = false;
                        me->SetSpeedRate(MOVE_RUN,2);
                        (*me).GetMotionMaster()->MoveChase(me->GetVictim());
                        Blade_Dance_Timer = 30000;
                        Wait_Timer = 0;
                        if(HeroicMode)
                            Charge_timer = 5000;
                    }
                    else
                    {
                        //move in bladedance
                        float x,y,randx,randy;
                        randx = (rand()%40);
                        randy = (rand()%40);
                        x = 210+ randx ;
                        y = -60- randy ;
                        (*me).GetMotionMaster()->MovePoint(1,x,y,me->GetPositionZ());
                        Wait_Timer = 0;
                    }
                }else Wait_Timer -= diff;
            }
        }
        else
        {
            if(Blade_Dance_Timer)
            {
                if(Blade_Dance_Timer <= diff)
                {
                    target_num = TARGET_NUM;
                    Wait_Timer = 1;
                    InBlade = true;
                    Blade_Dance_Timer = 0;
                    me->SetSpeedRate(MOVE_RUN,4);
                    return;
                }else Blade_Dance_Timer -= diff;
            }

            if(Charge_timer)
            {
                if(Charge_timer <= diff)
                {
                    DoCast(SelectTarget(SELECT_TARGET_RANDOM,0),H_SPELL_CHARGE);
                    Charge_timer = 0;
                } else { Charge_timer -= diff; }
            }

            if (Summon_Assistant_Timer <= diff)
            {
                Creature* Summoned;

                for(int i = 0; i < summoned; i++)
                {
                    switch(rand()%3)
                    {
                        case 0: Summoned = me->SummonCreature(MOB_HEARTHEN_GUARD,AddsEntrance[0],AddsEntrance[1], AddsEntrance[2], 0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10000); break;
                        case 1: Summoned = me->SummonCreature(MOB_SHARPSHOOTER_GUARD,AddsEntrance[0],AddsEntrance[1], AddsEntrance[2], 0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10000); break;
                        case 2: Summoned = me->SummonCreature(MOB_REAVER_GUARD,AddsEntrance[0],AddsEntrance[1], AddsEntrance[2], 0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10000); break;
                    }
                }
                if(rand()%100 < 20) summoned++;
                    Summon_Assistant_Timer = 20000 + (rand()%5000) ;
            } else Summon_Assistant_Timer -= diff;

            DoMeleeAttackIfReady();
        }

        if(resetcheck_timer < diff)
        {
            uint32 tempx,tempy;
            tempx = me->GetPositionX();
            tempy = me->GetPositionY();
            if ( tempx > 255 || tempx < 205)
            {
                EnterEvadeMode();
                return;
            }
            resetcheck_timer = 5000;
        }else resetcheck_timer -= diff;
    }
};

CreatureAI* GetAI_boss_warchief_kargath_bladefist(Creature *_Creature)
{
    return new boss_warchief_kargath_bladefistAI (_Creature);
}

void AddSC_boss_warchief_kargath_bladefist()
{
    OLDScript *newscript;
    newscript = new OLDScript;
    newscript->Name="boss_warchief_kargath_bladefist";
    newscript->GetAI = &GetAI_boss_warchief_kargath_bladefist;
    sScriptMgr->RegisterOLDScript(newscript);
}

