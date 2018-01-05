
/* ScriptData
SDName: Boss_High_King_Maulgar
SD%Complete: 90
SDComment: Correct timers, after whirlwind melee attack bug, prayer of healing
SDCategory: Gruul's Lair
EndScriptData */


#include "def_gruuls_lair.h"

#define SAY_AGGRO               -1565000
#define SAY_ENRAGE              -1565001
#define SAY_OGRE_DEATH1         -1565002
#define SAY_OGRE_DEATH2         -1565003
#define SAY_OGRE_DEATH3         -1565004
#define SAY_OGRE_DEATH4         -1565005
#define SAY_SLAY1               -1565006
#define SAY_SLAY2               -1565007
#define SAY_SLAY3               -1565008
#define SAY_DEATH               -1565009

// High King Maulgar
#define SPELL_ARCING_SMASH      39144
#define SPELL_MIGHTY_BLOW       33230
#define SPELL_WHIRLWIND         33238
#define SPELL_BERSERKER_C       26561
#define SPELL_ROAR              16508
#define SPELL_FLURRY            33232
#define SPELL_DUAL_WIELD        29651 //used in phase

// Olm the Summoner
#define SPELL_DARK_DECAY        33129
#define SPELL_DEATH_COIL        33130
#define SPELL_SUMMON_WFH        33131

//Kiggler the Craed
#define SPELL_GREATER_POLYMORPH     33173
#define SPELL_LIGHTNING_BOLT        36152
#define SPELL_ARCANE_SHOCK          33175
#define SPELL_ARCANE_EXPLOSION      33237

//Blindeye the Seer
#define SPELL_GREATER_PW_SHIELD         33147
#define SPELL_HEAL                      33144
#define SPELL_PRAYER_OH                 33152

//Krosh Firehand
#define SPELL_GREATER_FIREBALL  33051
#define SPELL_SPELLSHIELD       33054
#define SPELL_BLAST_WAVE        33061

bool CheckAllBossDied(InstanceScript* pInstance, Creature* me)
{
    if(!pInstance || !me)
        return false;

    ObjectGuid MaulgarGUID = ObjectGuid::Empty;
    ObjectGuid KigglerGUID = ObjectGuid::Empty;
    ObjectGuid BlindeyeGUID = ObjectGuid::Empty;
    ObjectGuid OlmGUID = ObjectGuid::Empty;
    ObjectGuid KroshGUID = ObjectGuid::Empty;

    Creature* Maulgar = nullptr;
    Creature* Kiggler = nullptr;
    Creature* Blindeye = nullptr;
    Creature* Olm = nullptr;
    Creature* Krosh = nullptr;

    MaulgarGUID = pInstance->GetGuidData(DATA_MAULGAR_GUID);
    KigglerGUID = pInstance->GetGuidData(DATA_KIGGLERTHECRAZED_GUID);
    BlindeyeGUID = pInstance->GetGuidData(DATA_BLINDEYETHESEER_GUID);
    OlmGUID = pInstance->GetGuidData(DATA_OLMTHESUMMONER_GUID);
    KroshGUID = pInstance->GetGuidData(DATA_KROSHFIREHAND_GUID);

    Maulgar = (Creature*)(ObjectAccessor::GetUnit((*me), MaulgarGUID));
    Kiggler = (Creature*)(ObjectAccessor::GetUnit((*me), KigglerGUID));
    Blindeye = (Creature*)(ObjectAccessor::GetUnit((*me), BlindeyeGUID));
    Olm = (Creature*)(ObjectAccessor::GetUnit((*me), OlmGUID));
    Krosh = (Creature*)(ObjectAccessor::GetUnit((*me), KroshGUID));

    if(!Maulgar || !Kiggler || !Blindeye || !Olm || !Krosh)
        return false;

    if(!Maulgar->IsAlive() && !Kiggler->IsAlive() && !Blindeye->IsAlive() && !Olm->IsAlive() && !Krosh->IsAlive())
        return true;

    return false;
}

class boss_high_king_maulgar : public CreatureScript
{
public:
    boss_high_king_maulgar() : CreatureScript("boss_high_king_maulgar")
    { }

    class boss_high_king_maulgarAI : public BossAI
    {
        public:
        boss_high_king_maulgarAI(Creature* c) : BossAI(c, DATA_MAULGAR)
        {
        }
    
        uint32 ArcingSmash_Timer;
        uint32 MightyBlow_Timer;
        uint32 Whirlwind_Timer;
        uint32 Charging_Timer;
        uint32 Roar_Timer;
    
        bool Phase2;
    
        ObjectGuid Council[4];
    
        void Reset() override
        {
            ArcingSmash_Timer = 10000;
            MightyBlow_Timer = 40000;
            Whirlwind_Timer = 30000;
            Charging_Timer = 0;
            Roar_Timer = 0;
    
            me->CastSpell(me, SPELL_DUAL_WIELD, TRIGGERED_NONE);
    
            Phase2 = false;
    
            Creature *pCreature = nullptr;
            for(ObjectGuid i : Council)
            {
                if(i)
                {
                    pCreature = (Creature*)(ObjectAccessor::GetUnit((*me), i));
                    if(pCreature && !pCreature->IsAlive())
                    {
                        pCreature->Respawn();
                        pCreature->AI()->EnterEvadeMode();
                    }
                }
            }
            _Reset();
        }
    
        void KilledUnit(Unit*) override
        {
            switch(rand()%3)
            {
                case 0: DoScriptText(SAY_SLAY1, me); break;
                case 1: DoScriptText(SAY_SLAY2, me); break;
                case 2: DoScriptText(SAY_SLAY3, me); break;
            }
        }
    
        void JustDied(Unit* Killer) override
        {
            DoScriptText(SAY_DEATH, me);
            _JustDied();
        }
    
        void AddDeath()
        {
            switch(rand()%4)
            {
                case 0: DoScriptText(SAY_OGRE_DEATH1, me);break;
                case 1: DoScriptText(SAY_OGRE_DEATH2, me);break;
                case 2: DoScriptText(SAY_OGRE_DEATH3, me);break;
                case 3: DoScriptText(SAY_OGRE_DEATH4, me);break;
            }
        }
    
        void JustEngagedWith(Unit *who) override 
        {
            StartEvent(who);
            _JustEngagedWith();
        }
    
        void GetCouncil()
        {
            //get council member's guid to respawn them if needed
            Council[0] = instance->GetGuidData(DATA_KIGGLERTHECRAZED_GUID);
            Council[1] = instance->GetGuidData(DATA_BLINDEYETHESEER_GUID);
            Council[2] = instance->GetGuidData(DATA_OLMTHESUMMONER_GUID);
            Council[3] = instance->GetGuidData(DATA_KROSHFIREHAND_GUID);
        }
    
        void StartEvent(Unit *who)
        {
            GetCouncil();
    
            DoScriptText(SAY_AGGRO, me);
    
            instance->SetGuidData(DATA_MAULGAREVENT_TANK, who->GetGUID());
        }
    
        void UpdateAI(const uint32 diff) override 
        {
            //Only if not incombat check if the event is started
            if(!me->IsInCombat() && instance && instance->GetBossState(DATA_MAULGAR) == IN_PROGRESS)
            {
                Unit* target = ObjectAccessor::GetUnit((*me), instance->GetGuidData(DATA_MAULGAREVENT_TANK));
                if(target)
                {
                    AttackStart(target);
                    GetCouncil();
                }
            }
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            //someone evaded!
            if(!instance->GetBossState(DATA_MAULGAR))
            {
                EnterEvadeMode();
                return;
            }
    
            //ArcingSmash_Timer
            if (ArcingSmash_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_ARCING_SMASH);
                ArcingSmash_Timer = 10000;
            }else ArcingSmash_Timer -= diff;
    
            //Whirlwind_Timer
                   if (Whirlwind_Timer < diff)
                   {
                        DoCast(me->GetVictim(), SPELL_WHIRLWIND);
                        Whirlwind_Timer = 55000;
                   }else Whirlwind_Timer -= diff;
    
            //MightyBlow_Timer
            if (MightyBlow_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_MIGHTY_BLOW);
                MightyBlow_Timer = 30000+rand()%10000;
            }else MightyBlow_Timer -= diff;
    
            //Entering Phase 2
            if(!Phase2 && me->GetHealthPct() < 50)
            {
                Phase2 = true;
                DoScriptText(SAY_ENRAGE, me);
    
                me->CastSpell(me, SPELL_DUAL_WIELD, TRIGGERED_FULL_MASK);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 0);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
            }
    
            if(Phase2)
            {
                //Charging_Timer
                if(Charging_Timer < diff)
                {
                    Unit* target = nullptr;
                    target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if (target)
                    {
                        AttackStart(target);
                        DoCast(target, SPELL_BERSERKER_C);
                    }
                    Charging_Timer = 20000;
                }else Charging_Timer -= diff;
    
                //Intimidating Roar
                if(Roar_Timer < diff)
                {
                    DoCast(me, SPELL_ROAR);
                    Roar_Timer = 40000+(rand()%10000);
                }else Roar_Timer -= diff;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetGruulsLairAI<boss_high_king_maulgarAI>(creature);
    }
};


class boss_olm_the_summoner : public CreatureScript
{
public:
    boss_olm_the_summoner() : CreatureScript("boss_olm_the_summoner")
    { }

    class boss_olm_the_summonerAI : public ScriptedAI
    {
        public:
        boss_olm_the_summonerAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        uint32 DarkDecay_Timer;
        uint32 Summon_Timer;
           uint32 DeathCoil_Timer;
    
        InstanceScript* pInstance;
    
        void Reset()
        override {
            DarkDecay_Timer = 10000;
            Summon_Timer = 15000;
            DeathCoil_Timer = 20000;
    
            //reset encounter
            if (pInstance)
                pInstance->SetBossState(DATA_MAULGAR, NOT_STARTED);
        }
    
        void JustEngagedWith(Unit *who)
        override {
            if(pInstance)
            {
                pInstance->SetGuidData(DATA_MAULGAREVENT_TANK, who->GetGUID());
                pInstance->SetBossState(DATA_MAULGAR, IN_PROGRESS);
            }
        }
    
        void JustDied(Unit* Killer)
        override {
            if(pInstance)
            {
                Creature *Maulgar = nullptr;
                Maulgar = (Creature*)(ObjectAccessor::GetUnit((*me), pInstance->GetGuidData(DATA_MAULGAR_GUID)));
    
                if(Maulgar)
                    ((boss_high_king_maulgar::boss_high_king_maulgarAI*)Maulgar->AI())->AddDeath();
    
                if(CheckAllBossDied(pInstance, me))
                    pInstance->SetBossState(DATA_MAULGAR, DONE);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Only if not incombat check if the event is started
            if(!me->IsInCombat() && pInstance && pInstance->GetBossState(DATA_MAULGAR))
            {
                Unit* target = ObjectAccessor::GetUnit((*me), pInstance->GetGuidData(DATA_MAULGAREVENT_TANK));
    
                if(target)
                {
                    AttackStart(target);
                }
            }
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            //someone evaded!
            if(pInstance && !pInstance->GetBossState(DATA_MAULGAR))
            {
                EnterEvadeMode();
                return;
            }
    
            //DarkDecay_Timer
            if(DarkDecay_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_DARK_DECAY);
                DarkDecay_Timer = 20000;
            }else DarkDecay_Timer -= diff;
    
            //Summon_Timer
            if(Summon_Timer < diff)
            {
                DoCast(me, SPELL_SUMMON_WFH);
                Summon_Timer = 30000;
            }else Summon_Timer -= diff;
    
            //DeathCoil Timer /need correct timer
            if(DeathCoil_Timer < diff)
            {
                Unit* target = nullptr;
                target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                if(target)
                    DoCast(target, SPELL_DEATH_COIL);
                DeathCoil_Timer = 20000;
            }else DeathCoil_Timer -= diff;
    
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetGruulsLairAI<boss_olm_the_summonerAI>(creature);
    }
};


class boss_kiggler_the_crazed : public CreatureScript
{
public:
    boss_kiggler_the_crazed() : CreatureScript("boss_kiggler_the_crazed")
    { }

    class boss_kiggler_the_crazedAI : public ScriptedAI
    {
        public:
        boss_kiggler_the_crazedAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        uint32 GreaterPolymorph_Timer;
        uint32 LightningBolt_Timer;
        uint32 ArcaneShock_Timer;
        uint32 ArcaneExplosion_Timer;
    
        InstanceScript* pInstance;
    
        void Reset()
        override {
            GreaterPolymorph_Timer = 5000;
            LightningBolt_Timer = 10000;
            ArcaneShock_Timer = 20000;
            ArcaneExplosion_Timer = 30000;
    
            //reset encounter
            if (pInstance)
                pInstance->SetBossState(DATA_MAULGAR, NOT_STARTED);
        }
    
        void JustEngagedWith(Unit *who)
        override {
            if(pInstance)
            {
                pInstance->SetGuidData(DATA_MAULGAREVENT_TANK, who->GetGUID());
                pInstance->SetBossState(DATA_MAULGAR, IN_PROGRESS);
            }
        }
    
        void JustDied(Unit* Killer)
        override {
            if(pInstance)
            {
                Creature *Maulgar = nullptr;
                Maulgar = (Creature*)(ObjectAccessor::GetUnit((*me), pInstance->GetGuidData(DATA_MAULGAR_GUID)));
    
                if(Maulgar)
                    ((boss_high_king_maulgar::boss_high_king_maulgarAI*)Maulgar->AI())->AddDeath();
    
                if(CheckAllBossDied(pInstance, me))
                    pInstance->SetBossState(DATA_MAULGAR, DONE);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Only if not incombat check if the event is started
            if(!me->IsInCombat() && pInstance && pInstance->GetBossState(DATA_MAULGAR))
            {
                Unit* target = ObjectAccessor::GetUnit((*me), pInstance->GetGuidData(DATA_MAULGAREVENT_TANK));
    
                if(target)
                {
                    AttackStart(target);
                }
            }
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            //someone evaded!
            if(pInstance && !pInstance->GetBossState(DATA_MAULGAR))
            {
                EnterEvadeMode();
                return;
            }
    
            //GreaterPolymorph_Timer
            if(GreaterPolymorph_Timer < diff)
            {
                Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                if(target)
                    DoCast(target, SPELL_GREATER_POLYMORPH);
    
                GreaterPolymorph_Timer = 20000;
            }else GreaterPolymorph_Timer -= diff;
    
            //LightningBolt_Timer
            if(LightningBolt_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_LIGHTNING_BOLT);
                LightningBolt_Timer = 15000;
            }else LightningBolt_Timer -= diff;
    
            //ArcaneShock_Timer
            if(ArcaneShock_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_ARCANE_SHOCK);
                ArcaneShock_Timer = 20000;
            }else ArcaneShock_Timer -= diff;
    
            //ArcaneExplosion_Timer
            if(ArcaneExplosion_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_ARCANE_EXPLOSION);
                ArcaneExplosion_Timer = 30000;
            }else ArcaneExplosion_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetGruulsLairAI<boss_kiggler_the_crazedAI>(creature);
    }
};


class boss_blindeye_the_seer : public CreatureScript
{
public:
    boss_blindeye_the_seer() : CreatureScript("boss_blindeye_the_seer")
    { }

    class boss_blindeye_the_seerAI : public ScriptedAI
    {
        public:
        boss_blindeye_the_seerAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        uint32 GreaterPowerWordShield_Timer;
        uint32 Heal_Timer;
    
        InstanceScript* pInstance;
    
        void Reset()
        override {
            GreaterPowerWordShield_Timer = 5000;
            Heal_Timer = 30000;
    
            //reset encounter
            if (pInstance)
                pInstance->SetBossState(DATA_MAULGAR, NOT_STARTED);
        }
    
        void JustEngagedWith(Unit *who)
        override {
            if(pInstance)
            {
                pInstance->SetGuidData(DATA_MAULGAREVENT_TANK, who->GetGUID());
                pInstance->SetBossState(DATA_MAULGAR, IN_PROGRESS);
            }
        }
    
        void JustDied(Unit* Killer)
        override {
            if(pInstance)
            {
                Creature *Maulgar = nullptr;
                Maulgar = (Creature*)(ObjectAccessor::GetUnit((*me), pInstance->GetGuidData(DATA_MAULGAR_GUID)));
    
                if(Maulgar)
                    ((boss_high_king_maulgar::boss_high_king_maulgarAI*)Maulgar->AI())->AddDeath();
    
                if(CheckAllBossDied(pInstance, me))
                    pInstance->SetBossState(DATA_MAULGAR, DONE);
            }
        }
    
         void UpdateAI(const uint32 diff)
        override {
            //Only if not incombat check if the event is started
            if(!me->IsInCombat() && pInstance && pInstance->GetBossState(DATA_MAULGAR))
            {
                Unit* target = ObjectAccessor::GetUnit((*me), pInstance->GetGuidData(DATA_MAULGAREVENT_TANK));
    
                if(target)
                {
                    AttackStart(target);
                }
            }
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            //someone evaded!
            if(pInstance && !pInstance->GetBossState(DATA_MAULGAR))
            {
                EnterEvadeMode();
                return;
            }
    
            //GreaterPowerWordShield_Timer
            if(GreaterPowerWordShield_Timer < diff)
            {
                DoCast(me, SPELL_GREATER_PW_SHIELD);
                GreaterPowerWordShield_Timer = 40000;
            }else GreaterPowerWordShield_Timer -= diff;
    
            //Heal_Timer
            if(Heal_Timer < diff)
            {
                DoCast(me, SPELL_HEAL);
                Heal_Timer = 60000;
            }else Heal_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetGruulsLairAI<boss_blindeye_the_seerAI>(creature);
    }
};


class boss_krosh_firehand : public CreatureScript
{
public:
    boss_krosh_firehand() : CreatureScript("boss_krosh_firehand")
    { }

    class boss_krosh_firehandAI : public ScriptedAI
    {
        public:
        boss_krosh_firehandAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        uint32 GreaterFireball_Timer;
        uint32 SpellShield_Timer;
        uint32 BlastWave_Timer;
    
        InstanceScript* pInstance;
    
        void Reset()
        override {
            GreaterFireball_Timer = 1000;
            SpellShield_Timer = 5000;
            BlastWave_Timer = 20000;
    
            //reset encounter
            if (pInstance)
                pInstance->SetBossState(DATA_MAULGAR, NOT_STARTED);
        }
    
        void JustEngagedWith(Unit *who)
        override {
            if(pInstance)
            {
                pInstance->SetGuidData(DATA_MAULGAREVENT_TANK, who->GetGUID());
                pInstance->SetBossState(DATA_MAULGAR, IN_PROGRESS);
            }
        }
    
        void JustDied(Unit* Killer)
        override {
            if(pInstance)
            {
                Creature *Maulgar = nullptr;
                Maulgar = (Creature*)(ObjectAccessor::GetUnit((*me), pInstance->GetGuidData(DATA_MAULGAR_GUID)));
    
                if(Maulgar)
                    ((boss_high_king_maulgar::boss_high_king_maulgarAI*)Maulgar->AI())->AddDeath();
    
                if(CheckAllBossDied(pInstance, me))
                    pInstance->SetBossState(DATA_MAULGAR, DONE);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Only if not incombat check if the event is started
            if(!me->IsInCombat() && pInstance && pInstance->GetBossState(DATA_MAULGAR))
            {
                Unit* target = ObjectAccessor::GetUnit((*me), pInstance->GetGuidData(DATA_MAULGAREVENT_TANK));
    
                if(target)
                {
                    AttackStart(target);
                }
            }
    
            //Return since we have no target
            if (!UpdateVictim() )
                return;
    
            //someone evaded!
            if(pInstance && !pInstance->GetBossState(DATA_MAULGAR))
            {
                EnterEvadeMode();
                return;
            }
    
            //GreaterFireball_Timer
            if(GreaterFireball_Timer < diff || me->GetDistance(me->GetVictim()) < 30)
            {
                DoCast(me->GetVictim(), SPELL_GREATER_FIREBALL);
                GreaterFireball_Timer = 2000;
            }else GreaterFireball_Timer -= diff;
    
            //SpellShield_Timer
            if(SpellShield_Timer < diff)
            {
                me->InterruptNonMeleeSpells(false);
                DoCast(me->GetVictim(), SPELL_SPELLSHIELD);
                SpellShield_Timer = 30000;
            }else SpellShield_Timer -= diff;
    
            //BlastWave_Timer
            if(BlastWave_Timer < diff)
            {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [&](Unit* target) { return target->GetDistance2d(me) < 15.0f; });
                if (target)
                {
                    me->InterruptNonMeleeSpells(false);
                    DoCast(target, SPELL_BLAST_WAVE);
                }
                BlastWave_Timer = 60000;
            }else BlastWave_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetGruulsLairAI<boss_krosh_firehandAI>(creature);
    }
};


void AddSC_boss_high_king_maulgar()
{
    new boss_high_king_maulgar();
    new boss_kiggler_the_crazed();
    new boss_blindeye_the_seer();
    new boss_olm_the_summoner();
    new boss_krosh_firehand();
}

