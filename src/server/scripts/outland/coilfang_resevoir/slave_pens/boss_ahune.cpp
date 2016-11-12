

#define SPELL_COLD_SLAP             46145
#define SPELL_AHUNE_SHIELD          45954
#define SPELL_AHUNE_SLIP_FLOOR      45945   // Nice snow visual on floor
#define SPELL_AHUNE_SELF_STUN       46416
#define SPELL_AHUNE_EMERGE          46402
#define SPELL_AHUNE_GHOST_DISGUISE  46786
#define SPELL_SUBMERGE              37550

#define SPELL_ICE_SPEAR             46360

#define SPELL_HAILSTONE_CHILL       46458

#define NPC_AHUNITE_HAILSTONE       /*(heroicMode ? 26342 : */25755//)
#define NPC_AHUNITE_FROSTWIND       /*(heroicMode ? 26341 : */25757//)
#define NPC_AHUNITE_COLDWAVE        /*(heroicMode ? 26340 : */25756//)
#define NPC_AHUNE                   25740
#define NPC_AHUNE_FROZEN_CORE       25865
#define NPC_AHUNE_GHOST             26239
#define NPC_ICE_SPEAR_BUNNY         25985

#define GO_AHUNE_ICE_CHEST          187892

class boss_ahune : public CreatureScript
{
public:
    boss_ahune() : CreatureScript("boss_ahune") { }

    CreatureAI* GetAI(Creature* pCreature) const override
    {
        return new boss_ahuneAI(pCreature);
    }

    struct boss_ahuneAI : public ScriptedAI
    {
        boss_ahuneAI(Creature* c) : ScriptedAI(c), summons(me)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            heroicMode = me->GetMap()->IsHeroic();
            SetCombatMovementAllowed(false);
        }
    
        InstanceScript* pInstance;
    
        bool heroicMode;
    
        uint8 phase;
    
        uint32 phaseChangeTimer;
        uint32 summonTimer;
        uint32 slipperyFloorTimer;
        uint32 iceSpearTimer;
    
        SummonList summons;
    
        void Reset()
        override {
            phase = 1;
            phaseChangeTimer = 90000;
            summonTimer = 8000;
            slipperyFloorTimer = 55000;
            iceSpearTimer = 8000;
        
            if (heroicMode) {
                me->SetMaxHealth(230000);
                me->SetHealth(me->GetMaxHealth());
            }
        
            DoCast(me, SPELL_AHUNE_SHIELD, true);
            me->RemoveAurasDueToSpell(SPELL_SUBMERGE);
            me->RemoveFlag(UNIT_NPC_EMOTESTATE, EMOTE_STATE_SUBMERGED);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        
            me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FROST, true);
        
            summons.DespawnAll();
        
            if (Creature* frozenCore = me->FindNearestCreature(NPC_AHUNE_FROZEN_CORE, 10.0f, true))
                frozenCore->DisappearAndDie();
            
            if (Creature* frozenCore = me->SummonCreature(NPC_AHUNE_FROZEN_CORE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0))
                frozenCore->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            
            if (Creature* ghost = me->FindNearestCreature(NPC_AHUNE_GHOST, 10.0f, true))
                ghost->DisappearAndDie();    
        
            if (Creature* ghost = me->SummonCreature(NPC_AHUNE_GHOST, -89.566528, -253.344315, -1.089609, 1.683741, TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                ghost->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                ghost->SetVisibility(VISIBILITY_OFF);
            }
        }

        void EnterCombat(Unit* pWho) override
        {
            me->SummonCreature(NPC_AHUNITE_HAILSTONE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0);
        
            //DoCast(me, SPELL_AHUNE_SLIP_FLOOR, true);
        }

        void JustDied(Unit* pKiller)
        override {
            if (Creature* frozenCore = me->FindNearestCreature(NPC_AHUNE_FROZEN_CORE, 10.0f, true))
                frozenCore->AI()->JustDied(pKiller);

            summons.DespawnAll();
        
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void JustSummoned(Creature* pSummon)
        override {
            summons.Summon(pSummon);
        
            if (pSummon->GetEntry() == NPC_AHUNE_FROZEN_CORE)
                return;
        
            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                pSummon->AI()->AttackStart(target);
        }

        void SummonedCreatureDespawn(Creature* pSummon)
        override {
            summons.Despawn(pSummon);
        
            if (pInstance && pSummon->GetEntry() == NPC_AHUNITE_HAILSTONE)
                pInstance->RemoveAuraOnAllPlayers(SPELL_HAILSTONE_CHILL);
        }
    
        void HandleColdSlap()
        {
            auto players = me->getThreatManager().getThreatList();
            for(auto itr : players) 
            {
                if (Unit* plr = itr->getTarget()) 
                {
                    if (plr->IsWithinMeleeRange(me) && plr->IsAttackableByAOE()) 
                    {
                        DoCast(plr, SPELL_COLD_SLAP);
                        plr->CastSpell(plr, SPELL_ICE_SPEAR, true);
                    }
                }
            }
        }
    
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;

            if (phase == 1) {
                HandleColdSlap();
            
                if (summonTimer <= diff) {
                    me->SummonCreature(RAND(NPC_AHUNITE_FROSTWIND, NPC_AHUNITE_COLDWAVE), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0);
                
                    summonTimer = 8000;
                }
                else
                    summonTimer -= diff;
            
                DoMeleeAttackIfReady();
            }
        
            if (iceSpearTimer <= diff) {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))
                    me->SummonCreature(NPC_ICE_SPEAR_BUNNY, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
            
                iceSpearTimer = 5000;
            }
            else
                iceSpearTimer -= diff;
        
            if (phaseChangeTimer <= diff) {
                phase = (phase == 1) ? 2 : 1;
            
                if (phase == 1) {
                    me->RemoveAurasDueToSpell(SPELL_AHUNE_SELF_STUN);
                    me->RemoveAurasDueToSpell(SPELL_SUBMERGE);
                    me->RemoveFlag(UNIT_NPC_EMOTESTATE, EMOTE_STATE_SUBMERGED);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    DoCast(me, SPELL_AHUNE_EMERGE, true);
                    DoCast(me, SPELL_AHUNE_SHIELD, true);
                    me->SetReactState(REACT_AGGRESSIVE);
                
                    if (Creature* ghost = me->FindNearestCreature(NPC_AHUNE_GHOST, 10.0f, true)) {
                        ghost->RemoveAurasDueToSpell(SPELL_AHUNE_GHOST_DISGUISE);
                        ghost->SetVisibility(VISIBILITY_OFF);
                    }
                
                    me->SummonCreature(NPC_AHUNITE_HAILSTONE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0);
                    summonTimer = 4000;
                
                    if (Creature* frozenCore = me->FindNearestCreature(NPC_AHUNE_FROZEN_CORE, 10.0f, true)) {
                        frozenCore->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->SetHealth(frozenCore->GetHealth());
                    }
                    
                    phaseChangeTimer = 90000;
                }
                else {
                    me->RemoveAurasDueToSpell(SPELL_AHUNE_SHIELD);
                    DoCast(me, SPELL_SUBMERGE);
                    me->SetFlag(UNIT_NPC_EMOTESTATE, EMOTE_STATE_SUBMERGED);
                    me->SetReactState(REACT_PASSIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                
                    if (Creature* frozenCore = me->FindNearestCreature(NPC_AHUNE_FROZEN_CORE, 10.0f, true)) {
                        frozenCore->SetHealth(me->GetHealth());
                        frozenCore->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    }
                    
                    if (Creature* ghost = me->FindNearestCreature(NPC_AHUNE_GHOST, 10.0f, true)) {
                        ghost->AddAura(SPELL_AHUNE_GHOST_DISGUISE, ghost);
                        ghost->SetVisibility(VISIBILITY_ON);
                    }
                    
                    phaseChangeTimer = 30000;
                }
            }
            else
                phaseChangeTimer -= diff;
            
            if (slipperyFloorTimer <= diff) {
                //DoCast(me, SPELL_AHUNE_SLIP_FLOOR, true);
            
                slipperyFloorTimer = 55000;
            }
            else
                slipperyFloorTimer -= diff;
        }
    };
};

struct boss_frozen_coreAI : public ScriptedAI
{
    boss_frozen_coreAI(Creature* c) : ScriptedAI(c) 
    {
        SetCombatMovementAllowed(false);
    }
    
    void Reset()
    override {
        me->SetReactState(REACT_PASSIVE);
    }
    
    void EnterCombat(Unit* pWho) override {}
    
    void JustDied(Unit* pKiller)
    override {
        if (Creature* ahune = me->FindNearestCreature(NPC_AHUNE, 10.0f, true))
            me->Kill(ahune);

        pKiller->SummonGameObject(GO_AHUNE_ICE_CHEST, Position(-96.525841, -200.255798, -1.262261, 4.748316), G3D::Quat(), 86400);
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!UpdateVictim())
            return;
    }
};

CreatureAI* GetAI_boss_frozen_core(Creature* pCreature)
{
    return new boss_frozen_coreAI(pCreature);
}

#define SPELL_PULVERIZE         2676
#define SPELL_CHILLING_AURA     46885

struct mob_ahunite_hailstoneAI : public ScriptedAI
{
    mob_ahunite_hailstoneAI(Creature* c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }
    
    uint32 pulverizeTimer;
    
    InstanceScript* pInstance;
    
    void Reset()
    override {
        me->AddAura(SPELL_CHILLING_AURA, me);
        
        pulverizeTimer = 3000;
    }
    
    void EnterCombat(Unit* pWho) override {}
    
    void JustDied(Unit* pKiller)
    override {
        if (pInstance)
            pInstance->RemoveAuraOnAllPlayers(SPELL_HAILSTONE_CHILL);
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!UpdateVictim())
            return;

        if (pulverizeTimer <= diff) {
            DoCast(me->GetVictim(), SPELL_PULVERIZE);
            
            pulverizeTimer = 6000;
        }
        else
            pulverizeTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_ahunite_hailstoneAI(Creature* pCreature)
{
    return new mob_ahunite_hailstoneAI(pCreature);
}

#define SPELL_KNOCKBACK_DELAYER     46878

#define GO_ICE_SPEAR                188077

struct npc_ice_spear_bunnyAI : public ScriptedAI
{
    npc_ice_spear_bunnyAI(Creature* c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        SetCombatMovementAllowed(false);
    }
    
    uint32 spawnTimer;
    uint32 activateTimer;
    uint32 deathTimer;
    
    InstanceScript* pInstance;
    
    void Reset()
    override {
        me->SetReactState(REACT_PASSIVE);
        DoCast(me, SPELL_KNOCKBACK_DELAYER);
        
        spawnTimer = 500;
        activateTimer = 2500;
        deathTimer = 99999;
    }
    
    void EnterCombat(Unit* pWho) override {}
    

    void HandleIceSpear()
    {
        auto players = me->getThreatManager().getThreatList();
        for (auto itr : players)
        {
            if (Unit* plr = itr->getTarget())
            {
                if (plr->IsWithinMeleeRange(me) && plr->IsAttackableByAOE())
                {
                    plr->CastSpell(plr, SPELL_ICE_SPEAR, true);
                }
            }
        }
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (spawnTimer <= diff) {
            if (GameObject* go = me->SummonGameObject(GO_ICE_SPEAR, me->GetPosition(), G3D::Quat(), 86400))
                go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                
            spawnTimer = 99999;
        }
        else
            spawnTimer -= diff;
            
        if (activateTimer <= diff) {
            if (GameObject* go = me->FindNearestGameObject(GO_ICE_SPEAR, 3.0f)) {
                go->UseDoorOrButton();
                HandleIceSpear();
                activateTimer = 99999;
                deathTimer = 1500;
            }
        }
        else
            activateTimer -= diff;
            
        if (deathTimer <= diff) {
            if (GameObject* go = me->FindNearestGameObject(GO_ICE_SPEAR, 3.0f)) {
                go->SetLootState(GO_JUST_DEACTIVATED);
                go->SetRespawnTime(86400);     // One day
                me->DisappearAndDie();
            }
            
            deathTimer = 99999;
        }
        else
            deathTimer -= diff;
    }
};

CreatureAI* GetAI_npc_ice_spear_bunny(Creature* pCreature)
{
    return new npc_ice_spear_bunnyAI(pCreature);
}

void AddSC_boss_ahune()
{
    new boss_ahune();

    OLDScript* newscript;
    
    newscript = new OLDScript;
    newscript->Name = "boss_frozen_core";
    newscript->GetAI = &GetAI_boss_frozen_core;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "mob_ahunite_hailstone";
    newscript->GetAI = &GetAI_mob_ahunite_hailstoneAI;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_ice_spear_bunny";
    newscript->GetAI = &GetAI_npc_ice_spear_bunny;
    sScriptMgr->RegisterOLDScript(newscript);
}
