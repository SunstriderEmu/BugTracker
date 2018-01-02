
/* ScriptData
SDName: Boss_Magtheridon
SD%Complete: 60
SDComment: In Development
SDCategory: Hellfire Citadel, Magtheridon's lair
EndScriptData */


#include "def_magtheridons_lair.h"

struct Yell
{
    int32 id;
};

static Yell RandomTaunt[]=
{
    {-1544000},
    {-1544001},
    {-1544002},
    {-1544003},
    {-1544004},
    {-1544005},
};

#define SAY_FREED                   -1544006
#define SAY_AGGRO                   -1544007
#define SAY_BANISH                  -1544008
#define SAY_CHAMBER_DESTROY         -1544009
#define SAY_PLAYER_KILLED           -1544010
#define SAY_DEATH                   -1544011

#define EMOTE_BERSERK               -1544012
#define EMOTE_BLASTNOVA             -1544013
#define EMOTE_BEGIN                 -1544014

#define MOB_MAGTHERIDON     17257
#define MOB_ROOM            17516
#define MOB_CHANNELLER      17256
#define MOB_ABYSSAL         17454

#define SPELL_BLASTNOVA             30616
#define SPELL_CLEAVE                30619
#define SPELL_QUAKE_TRIGGER         30657 // must be cast with 30561 as the proc spell
#define SPELL_QUAKE_KNOCKBACK       30571
#define SPELL_BLAZE_TARGET          30541 // core bug, does not support target 7
#define SPELL_BLAZE_TRAP            30542
#define SPELL_DEBRIS_KNOCKDOWN      36449
#define SPELL_DEBRIS_VISUAL         30632
#define SPELL_DEBRIS_DAMAGE         30631 // core bug, does not support target 8
#define SPELL_CAMERA_SHAKE          36455
#define SPELL_BERSERK               27680

#define SPELL_SHADOW_CAGE           30168
#define SPELL_SHADOW_GRASP          30410
#define SPELL_SHADOW_GRASP_VISUAL   30166
#define SPELL_MIND_EXHAUSTION       44032   //Casted by the cubes when channeling ends

#define SPELL_SHADOW_CAGE_C         30205
#define SPELL_SHADOW_GRASP_C        30207

#define SPELL_SHADOW_BOLT_VOLLEY    30510
#define SPELL_DARK_MENDING          30528
#define SPELL_FEAR                  30530 //39176
#define SPELL_BURNING_ABYSSAL       30511
#define SPELL_SOUL_TRANSFER         30531 // core bug, does not support target 7

#define SPELL_FIRE_BLAST            37110

// count of clickers needed to interrupt blast nova
#define CLICKERS_COUNT              5

typedef std::map<ObjectGuid, ObjectGuid> CubeMap;



class mob_abyssal : public CreatureScript
{
public:
    mob_abyssal() : CreatureScript("mob_abyssal")
    { }

    class mob_abyssalAI : public ScriptedAI
    {
    public:
        mob_abyssalAI(Creature *c) : ScriptedAI(c)
        {
            trigger = 0;
            Despawn_Timer = 60000;
        }

        uint32 FireBlast_Timer;
        uint32 Despawn_Timer;
        uint32 trigger;

        void Reset()
            override {
            FireBlast_Timer = 6000;
        }

        void SpellHit(Unit*, const SpellInfo *spell)
            override {
            if (trigger == 2 && spell->Id == SPELL_BLAZE_TARGET)
            {
                me->CastSpell(me, SPELL_BLAZE_TRAP, TRIGGERED_FULL_MASK);
                me->SetVisible(false);
                Despawn_Timer = 130000;
            }
        }

        void SetTrigger(uint32 _trigger)
        {
            trigger = _trigger;
            me->SetDisplayId(11686);
            if (trigger == 1) //debris
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->CastSpell(me, SPELL_DEBRIS_VISUAL, TRIGGERED_FULL_MASK);
                FireBlast_Timer = 5000;
                Despawn_Timer = 10000;
            }
        }

        void JustEngagedWith(Unit*) override { DoZoneInCombat(); }
        void AttackStart(Unit *who) override { if (!trigger) ScriptedAI::AttackStart(who); }
        void MoveInLineOfSight(Unit *who) override { if (!trigger) ScriptedAI::MoveInLineOfSight(who); }

        void UpdateAI(const uint32 diff)
            override {
            if (trigger)
            {
                if (trigger == 1)
                {
                    if (FireBlast_Timer < diff)
                    {
                        me->CastSpell(me, SPELL_DEBRIS_DAMAGE, TRIGGERED_FULL_MASK);
                        trigger = 3;
                    }
                    else FireBlast_Timer -= diff;
                }
                return;
            }

            if (Despawn_Timer < diff)
            {
                me->SetVisible(false);
                me->SetDeathState(JUST_DIED);
            }
            else Despawn_Timer -= diff;

            if (!UpdateVictim())
                return;

            if (FireBlast_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_FIRE_BLAST);
                FireBlast_Timer = 5000 + rand() % 10000;
            }
            else FireBlast_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_abyssalAI(creature);
    }
};


class boss_magtheridon : public CreatureScript
{
public:
    boss_magtheridon() : CreatureScript("boss_magtheridon")
    { }

    class boss_magtheridonAI : public ScriptedAI
    {
        public:
        boss_magtheridonAI(Creature *c) : ScriptedAI(c)
        {
            pInstance =(InstanceScript*)me->GetInstanceScript();
            me->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 10);
            me->SetFloatValue(UNIT_FIELD_COMBATREACH, 10);
        }
    
        CubeMap Cube;
    
        InstanceScript* pInstance;
    
        uint32 Berserk_Timer;
        uint32 Quake_Timer;
        uint32 Cleave_Timer;
        uint32 BlastNova_Timer;
        uint32 Blaze_Timer;
        uint32 Debris_Timer;
        uint32 RandChat_Timer;
    
        bool Phase3;
        bool NeedCheckCube;
    
        void Reset()
        override {
            if(pInstance)
            {
                pInstance->SetData(DATA_MAGTHERIDON_EVENT, NOT_STARTED);
                pInstance->SetData(DATA_COLLAPSE, false);
            }
    
            Berserk_Timer = 1320000;
            Quake_Timer = 40000;
            Debris_Timer = 10000;
            Blaze_Timer = 10000+rand()%20000;
            BlastNova_Timer = 60000;
            Cleave_Timer = 15000;
            RandChat_Timer = 90000;
    
            Phase3 = false;
    
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->AddUnitState(UNIT_STATE_STUNNED);
            me->CastSpell(me, SPELL_SHADOW_CAGE_C, TRIGGERED_FULL_MASK);
        }
    
        void SetClicker(ObjectGuid cubeGUID, ObjectGuid clickerGUID)
        {
            // to avoid multiclicks from 1 cube
            if(ObjectGuid guid = Cube[cubeGUID])
                DebuffClicker(ObjectAccessor::GetUnit(*me, guid));
            Cube[cubeGUID] = clickerGUID;
            NeedCheckCube = true;
        }
    
        //function to interrupt channeling and debuff clicker with mind exh(used if second person clicks with same cube or after dispeling/ending shadow grasp DoT)
        void DebuffClicker(Unit *clicker)
        {
            if(!clicker || !clicker->IsAlive())
                return;
    
            clicker->RemoveAurasDueToSpell(SPELL_SHADOW_GRASP); // cannot interrupt triggered spells
            clicker->InterruptNonMeleeSpells(false);
            clicker->CastSpell(clicker, SPELL_MIND_EXHAUSTION, TRIGGERED_FULL_MASK);
        }
    
        void NeedCheckCubeStatus()
        {
            uint32 ClickerNum = 0;
            // now checking if every clicker has debuff from manticron(it is dispelable atm rev 6110 : S)
            // if not - apply mind exhaustion and delete from clicker's list
            for(auto & i : Cube)
            {
                Unit *clicker = ObjectAccessor::GetUnit(*me, i.second);
                if(!clicker || !clicker->HasAuraEffect(SPELL_SHADOW_GRASP, 1))
                {
                    DebuffClicker(clicker);
                    i.second.Clear();
                }else ClickerNum++;
            }
    
            // if 5 clickers from other cubes apply shadow cage
            if(ClickerNum >= CLICKERS_COUNT && !me->HasAuraEffect(SPELL_SHADOW_CAGE, 0))
            {
                DoScriptText(SAY_BANISH, me);
                me->CastSpell(me, SPELL_SHADOW_CAGE, TRIGGERED_FULL_MASK);
            }
            else if(ClickerNum < CLICKERS_COUNT && me->HasAuraEffect(SPELL_SHADOW_CAGE, 0))
                me->RemoveAurasDueToSpell(SPELL_SHADOW_CAGE);
    
            if(!ClickerNum) NeedCheckCube = false;
        }
    
        void KilledUnit(Unit* victim)
        override {
            DoScriptText(SAY_PLAYER_KILLED, me);
        }
    
        void JustDied(Unit* Killer)
        override {
            if(pInstance)
                pInstance->SetData(DATA_MAGTHERIDON_EVENT, DONE);
    
            DoScriptText(SAY_DEATH, me);
        }
    
        void MoveInLineOfSight(Unit*) override {}
    
        void AttackStart(Unit *who)
        override {
            if(!me->HasUnitState(UNIT_STATE_STUNNED))
                ScriptedAI::AttackStart(who);
        }
    
        void JustEngagedWith(Unit *who)
        override {
            if(pInstance)
                pInstance->SetData(DATA_MAGTHERIDON_EVENT, IN_PROGRESS);
            DoZoneInCombat();
    
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->RemoveAurasDueToSpell(SPELL_SHADOW_CAGE_C);
    
            DoScriptText(SAY_FREED, me);
       }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!me->IsInCombat())
            {
                if (RandChat_Timer < diff)
                {
                    DoScriptText(RandomTaunt[rand()%6].id, me);
                    RandChat_Timer = 90000;
                }else RandChat_Timer -= diff;
            }
    
            if(!UpdateVictim())
                return;
    
            if(NeedCheckCube) NeedCheckCubeStatus();
    
            if(Berserk_Timer < diff)
            {
                me->CastSpell(me, SPELL_BERSERK, TRIGGERED_FULL_MASK);
                DoScriptText(EMOTE_BERSERK, me);
                Berserk_Timer = 60000;
            }else Berserk_Timer -= diff;
    
            if(Cleave_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_CLEAVE);
                Cleave_Timer = 10000;
            }else Cleave_Timer -= diff;
    
            if(BlastNova_Timer < diff)
            {
                // to avoid earthquake interruption
                if(!me->HasUnitState(UNIT_STATE_STUNNED))
                {
                    DoScriptText(EMOTE_BLASTNOVA, me);
                    DoCast(me, SPELL_BLASTNOVA);
                    BlastNova_Timer = 60000;
                }
            }else BlastNova_Timer -= diff;
    
            if(Quake_Timer < diff)
            {
                // to avoid blastnova interruption
                if(!me->IsNonMeleeSpellCast(false))
                {
                    me->CastSpell(me, SPELL_QUAKE_TRIGGER, TRIGGERED_FULL_MASK);
                    Quake_Timer = 50000;
                }
            }else Quake_Timer -= diff;
    
            if(Blaze_Timer < diff)
            {
                if(Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    float x, y, z;
                    target->GetPosition(x, y, z);
                    Creature *summon = me->SummonCreature(MOB_ABYSSAL, x, y, z, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    if(summon)
                    {
                        ((mob_abyssal::mob_abyssalAI*)summon->AI())->SetTrigger(2);
                        me->CastSpell(summon, SPELL_BLAZE_TARGET, TRIGGERED_FULL_MASK);
                        summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    }
                }
                Blaze_Timer = 20000 + rand()%20000;
            }else Blaze_Timer -= diff;
    
            if(!Phase3 && me->GetHealth()*10 < me->GetMaxHealth()*3
                && !me->IsNonMeleeSpellCast(false) // blast nova
                && !me->HasUnitState(UNIT_STATE_STUNNED)) // shadow cage and earthquake
            {
                Phase3 = true;
                DoScriptText(SAY_CHAMBER_DESTROY, me);
                me->CastSpell(me, SPELL_CAMERA_SHAKE, TRIGGERED_FULL_MASK);
                me->CastSpell(me, SPELL_DEBRIS_KNOCKDOWN, TRIGGERED_FULL_MASK);
    
                if(pInstance)
                    pInstance->SetData(DATA_COLLAPSE, true);
            }
    
            if(Phase3)
            {
                if(Debris_Timer < diff)
                {
                    if(Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    {
                        float x, y, z;
                        target->GetPosition(x, y, z);
                        Creature *summon = me->SummonCreature(MOB_ABYSSAL, x, y, z, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                        if(summon) ((mob_abyssal::mob_abyssalAI*)summon->AI())->SetTrigger(1);
                    }
                    Debris_Timer = 10000;
                }else Debris_Timer -= diff;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_magtheridonAI(creature);
    }
};

class ManticronCube : public GameObjectScript
{
public:
    ManticronCube() : GameObjectScript("go_manticron_cube")
    {}

    struct ManticronCubeAI : public GameObjectAI
    {
        ManticronCubeAI(GameObject* obj) : GameObjectAI(obj), pInstance(obj->GetInstanceScript()) { }

        InstanceScript* pInstance;

        bool GossipHello(Player* player) override
        {
            if (!pInstance)
                return true;
            if (pInstance->GetData(DATA_MAGTHERIDON_EVENT) != IN_PROGRESS) return true;
            Creature *Magtheridon = ObjectAccessor::GetCreature(*me, ObjectGuid(pInstance->GetData64(DATA_MAGTHERIDON)));
            if (!Magtheridon || !Magtheridon->IsAlive()) return true;

            // if exhausted or already channeling return
            if (player->HasAuraEffect(SPELL_MIND_EXHAUSTION, 0) || player->HasAuraEffect(SPELL_SHADOW_GRASP, 1))
                return true;

            player->InterruptNonMeleeSpells(false);
            player->CastSpell(player, SPELL_SHADOW_GRASP, TRIGGERED_FULL_MASK);
            player->CastSpell(player, SPELL_SHADOW_GRASP_VISUAL, TRIGGERED_NONE);
            ((boss_magtheridon::boss_magtheridonAI*)Magtheridon->AI())->SetClicker(me->GetGUID(), player->GetGUID());
            return true;
        }

    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ManticronCubeAI(go);
    }
};

class mob_hellfire_channeler : public CreatureScript
{
public:
    mob_hellfire_channeler() : CreatureScript("mob_hellfire_channeler")
    { }

    class mob_hellfire_channelerAI : public ScriptedAI
    {
        public:
        mob_hellfire_channelerAI(Creature *c) : ScriptedAI(c)
        {
            pInstance =(InstanceScript*)me->GetInstanceScript();
        }
    
        InstanceScript* pInstance;
    
        uint32 ShadowBoltVolley_Timer;
        uint32 DarkMending_Timer;
        uint32 Fear_Timer;
        uint32 Infernal_Timer;
    
        uint32 Check_Timer;
    
        void Reset()
        override {
            ShadowBoltVolley_Timer = 8000 + rand()%2000;
            DarkMending_Timer = 10000;
            Fear_Timer = 15000 + rand()%5000;
            Infernal_Timer = 10000 + rand()%40000;
    
            Check_Timer = 5000;
    
            if(pInstance)
                pInstance->SetData(DATA_CHANNELER_EVENT, NOT_STARTED);
    
            me->RemoveAllAuras();
            me->CastSpell(me, SPELL_SHADOW_GRASP_C, TRIGGERED_NONE);
        }
    
        void JustEngagedWith(Unit *who)
        override {
            if(pInstance)
                pInstance->SetData(DATA_CHANNELER_EVENT, IN_PROGRESS);
    
            me->InterruptNonMeleeSpells(false);
            DoZoneInCombat();
        }
    
        void JustSummoned(Creature *summon) override {summon->AI()->AttackStart(me->GetVictim());}
    
        void MoveInLineOfSight(Unit*) override {}
    
        void DamageTaken(Unit*, uint32 &damage)
        override {
            if(damage >= me->GetHealth())
                me->CastSpell(me, SPELL_SOUL_TRANSFER, TRIGGERED_FULL_MASK);
        }
    
        void JustDied(Unit*)
        override {
            if(pInstance)
                pInstance->SetData(DATA_CHANNELER_EVENT, DONE);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if(ShadowBoltVolley_Timer < diff)
            {
                DoCast(me, SPELL_SHADOW_BOLT_VOLLEY);
                ShadowBoltVolley_Timer = 10000 + rand()%10000;
            }else ShadowBoltVolley_Timer -= diff;
    
            if(DarkMending_Timer < diff)
            {
                if((me->GetHealthPct()) < 50)
                    DoCast(me, SPELL_DARK_MENDING);
                DarkMending_Timer = 10000 +(rand() % 10000);
            }else DarkMending_Timer -= diff;
    
            if(Fear_Timer < diff)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0, true, true))
                    DoCast(target, SPELL_FEAR);
                Fear_Timer = 25000 + rand()%15000;
            }else Fear_Timer -= diff;
    
            if(Infernal_Timer < diff)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    me->CastSpell(target, SPELL_BURNING_ABYSSAL, TRIGGERED_FULL_MASK);
                Infernal_Timer = 30000 + rand()%10000;
            }else Infernal_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_hellfire_channelerAI(creature);
    }
};


void AddSC_boss_magtheridon()
{
    new boss_magtheridon();

    new mob_hellfire_channeler();

    new ManticronCube();

    new mob_abyssal();

}

