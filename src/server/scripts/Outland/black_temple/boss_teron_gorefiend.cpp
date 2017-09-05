
/* ScriptData
SDName: Boss_Teron_Gorefiend
SD%Complete: 90
SDComment: don't know, maybe the blossoms can move up as on offi
SDCategory: Black Temple
EndScriptData */
/*

            
DELETE FROM `creature_template` WHERE (`entry`=23109);
INSERT INTO `creature_template` (`entry`, `heroic_entry`, `modelid_A`, `modelid_A2`, `modelid_H`, `modelid_H2`, `name`, `subname`, `IconName`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `baseattacktime`, `rangeattacktime`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `class`, `race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `RacialLeader`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES (23109, 0, 21300, 0, 21300, 0, 'Vengeful Spirit', '', '', 70, 70, 20000000, 20000000, 0, 0, 0, 35, 35, 0, 1, 1, 1, 0, 0, 0, 0, 1000000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40314, 40175, 40325, 40157, 0, 0, 0, '', 0, 1, 0, 1, 0, 8388624, 0, 'vengeful_spirit');

DELETE FROM spell_script_target WHERE ENTRY = 40268;
INSERT INTO spell_script_target VALUES (40268, 1, 23109);
           

UPDATE `creature_template` SET 
    `mindmg` = 2500, 
    `maxdmg` = 3000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 23111;

UPDATE `creature_template` SET `baseattacktime` = 2000 WHERE `entry` = 23111;
UPDATE `creature_template` SET `faction_A` = 1813, `faction_H` = 1813 WHERE `entry` = 23111;

UPDATE `creature_template` SET `speed` = 0.8 WHERE `entry` = 23111;
  */

#include "def_black_temple.h"
#include "SpellMgr.h"
#include "Spell.h"
#include "WorldPacket.h"

 //Speech'n'sound
#define SAY_INTRO                       -1564037
#define SAY_AGGRO                       -1564038
#define SAY_SLAY1                       -1564039
#define SAY_SLAY2                       -1564040
#define SAY_SPELL1                      -1564041
#define SAY_SPELL2                      -1564042
#define SAY_SPECIAL1                    -1564043
#define SAY_SPECIAL2                    -1564044
#define SAY_ENRAGE                      -1564045
#define SAY_DEATH                       -1564046

//Spells
#define SPELL_INCINERATE                40239
#define SPELL_CRUSHING_SHADOWS          40243
#define SPELL_SHADOWBOLT                40185
#define SPELL_PASSIVE_SHADOWFORM        40326
#define SPELL_SHADOW_OF_DEATH           40251
#define SPELL_BERSERK                   45078
#define SPELL_SUMMON_SPIRIT             40266

#define SPELL_ATROPHY                   40327               // Shadowy Constructs use this when they get within melee range of a player
#define SPELL_SHADOW_STRIKES            40334

enum Timers
{
    TIMER_INCINERATE = 20000,
    TIMER_INCINERATE_FIRST = 35000,
    TIMER_SHADOW_OF_DEATH = 30000,
    TIMER_SHADOW_OF_DEATH_FIRST = 15000,
    TIMER_CRUSHING_SHADOWS = 35000,
    TIMER_CRUSHING_SHADOWS_FIRST = 25000,
    TIMER_DOOM_BLOSSOM = 30000,
    TIMER_DOOM_BLOSSOM_FIRST = 10000,
    TIMER_ENRAGE = 600000,
};

//Blossom timer :
#define TIMER_SHADOW_BOLT 1000 + rand()%500

#define CREATURE_DOOM_BLOSSOM           23123
#define CREATURE_SHADOWY_CONSTRUCT      23111
#define CREATURE_GHOST                  23109

class mob_doom_blossom : public CreatureScript
{
public:
    mob_doom_blossom() : CreatureScript("mob_doom_blossom")
    { }

    class mob_doom_blossomAI : public ScriptedAI
    {
        public:
        mob_doom_blossomAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 MoveTimer;
        uint32 ShadowBoltTimer;
    
        void Reset()
        override {
            MoveTimer = 1000;
            ShadowBoltTimer = TIMER_SHADOW_BOLT;
    
            me->GetMotionMaster()->Clear(false);
            me->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 7);
        }
    
        void EnterCombat(Unit *who) override { }
        void AttackStart(Unit* who) override { }
        void MoveInLineOfSight(Unit* who) override { }
    
        void UpdateAI(const uint32 diff)
        override {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
    
            if (ShadowBoltTimer <= diff)
            {
                if(Unit* u = SelectTarget(0, 0.0f, 100.0f, true, false, true, 0, 0))
                {
                    DoCast(u, SPELL_SHADOWBOLT, true);
                    ShadowBoltTimer = TIMER_SHADOW_BOLT;
                }
            }else ShadowBoltTimer -= diff;
            
            if (MoveTimer <= diff) {
                if (Creature *pTeron = me->FindNearestCreature(22871, 80.0f, true)) //Teron
                {
                    me->GetMotionMaster()->MovePoint(0, pTeron->GetPositionX(), pTeron->GetPositionY(), me->GetPositionZ());
                    MoveTimer = 4000;
                }
            } else MoveTimer -= diff;
        }
        
        void DamageDeal(Unit* target, uint32 &damage)
        {
            if (target->GetDisplayId() == 21300) //= Vengeful Spirit
                damage = 0;
        }
    
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_doom_blossomAI(creature);
    }
};


class boss_teron_gorefiend : public CreatureScript
{
public:
    boss_teron_gorefiend() : CreatureScript("boss_teron_gorefiend")
    { }

    class boss_teron_gorefiendAI : public ScriptedAI
    {
        public:
        boss_teron_gorefiendAI(Creature *c) : ScriptedAI(c), Summons(me)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        uint32 IncinerateTimer;
        uint32 SummonDoomBlossomTimer;
        uint32 EnrageTimer;
        uint32 CrushingShadowsTimer;
        uint32 ShadowOfDeathTimer;
        uint32 RandomYellTimer;
        uint32 AggroTimer;
    
        uint64 AggroTargetGUID;
    
        SummonList Summons;
    
        bool Intro;
    
        void Reset()
        override {
            if(pInstance){
                if (pInstance->GetData(DATA_TERONGOREFIENDEVENT) != DONE)
                    pInstance->SetData(DATA_TERONGOREFIENDEVENT, NOT_STARTED);
            }
    
            IncinerateTimer = TIMER_INCINERATE_FIRST;
            SummonDoomBlossomTimer = TIMER_DOOM_BLOSSOM_FIRST;
            EnrageTimer = TIMER_ENRAGE;
            CrushingShadowsTimer = TIMER_CRUSHING_SHADOWS_FIRST;
            ShadowOfDeathTimer = TIMER_SHADOW_OF_DEATH_FIRST;
            RandomYellTimer = 50000;
    
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            // Start off unattackable so that the intro is done properly
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        
    
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT,SPELL_EFFECT_ATTACK_ME, true);
    
            
            me->ApplySpellImmune(0, IMMUNITY_ID, 40314, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 40175, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 40157, true);
            
            me->AddUnitState(UNIT_STATE_ROOT);
    
            AggroTimer = 25000;
    
            Intro = false;
            DespawnConstructs();
            Summons.DespawnAll();
            
            while (Creature *pGhost = me->FindNearestCreature(CREATURE_GHOST, 50.0f, true))
                pGhost->RemoveAurasDueToSpell(40268); //Spiritual Vengeance, disable players possesions
                
            //me->GetMotionMaster()->MoveTargetedHome();
            float x, y, z, o;
            me->GetHomePosition(x, y, z, o);
            me->GetMotionMaster()->MovePoint(0, x, y, z);
            me->SetOrientation(o);
            me->Relocate(x, y, z, o);
            me->StopMoving(); //to update orientation
    
            //immune to some spirits spells
            me->ApplySpellImmune(0, IMMUNITY_ID, 40157, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 40175, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 40314, true);
    
            /*
             TAUNT IMMUNE - DIRTY WAY 
            me->ApplySpellImmune(0, IMMUNITY_ID, 31789, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 39377, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 54794, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 37017, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 37486, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 49613, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 694, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 25266, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 39270, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 27344, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 6795, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 39270, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 1161, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 5209, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 355, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 34105, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 53477, true);
            */
        }
    
        void MoveInLineOfSight(Unit *who)
        override {
            if(!who || (!who->IsAlive())) return;
    
            if(me->CanAttack(who) == CAN_ATTACK_RESULT_OK && who->isInAccessiblePlaceFor(me) && me->IsHostileTo(who))
            {
                /*if (me->IsWithinDistInMap(who, attackRadius) && me->GetDistanceZ(who) <= CREATURE_Z_ATTACK_RANGE && me->IsWithinLOSInMap(who))
                {
                    me->AddThreat(who, 1.0f);
                    DoZoneInCombat();
                }*/
    
                if(!me->IsInCombat() && !Intro && me->IsWithinDistInMap(who, 40.0f) && (who->GetTypeId() == TYPEID_PLAYER))
                {
                    if(pInstance)
                        pInstance->SetData(DATA_TERONGOREFIENDEVENT, IN_PROGRESS);
    
                    me->GetMotionMaster()->Clear(false);
                    //me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    DoScriptText(SAY_INTRO, me);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_TALK);
                    AggroTargetGUID = who->GetGUID();
                    Intro = true;
                    me->SetOrientation(3.14159);
                }
            }
        }
        
        void JustSummoned(Creature* summon)
        override {
            Summons.Summon(summon);
        }
        
        Unit* GetConstructTarget() {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                return target;
            else
                return nullptr;
        }
        
        bool HasPlayerTarget()
        {
            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
            if (PlayerList.isEmpty())
                return false;
            for(auto & itr : me->getThreatManager().getThreatList())
            {
                for(const auto & i : PlayerList)
                {
                    if (Player* i_pl = i.GetSource())
                        if(i_pl->GetGUID() == itr->getUnitGuid())
                            return true;
                }
            }
            return false;
        }
    
        void KilledUnit(Unit *victim)
        override {
            switch(rand()%2)
            {
                case 0: DoScriptText(SAY_SLAY1, me); break;
                case 1: DoScriptText(SAY_SLAY2, me); break;
            }
        }
        
        void DamageTaken(Unit* done_by, uint32 &damage)
        override {
            /*
            if (done_by->GetDisplayId() == 21300) //vengeful spirit
            { 
                DoModifyThreatPercent(done_by,-100);
                damage = 0;
                if (done_by->GetTypeId() == TYPEID_PLAYER) {
                    WorldPacket data(SMSG_CAST_FAILED, (4+2));              // prepare packet error message
                    data << uint32(0);                                      // spellId
                    data << uint8(SPELL_FAILED_IMMUNE);                     // reason
                    done_by->ToPlayer()->GetSession()->SendPacket(&data);               // send message: Invalid target
                }
            }
            */
        }
        
        void DamageDeal(Unit* target, uint32 &damage)
        {
            if (target->GetDisplayId() == 21300) //spirits
                damage = 0;
        }
    
        void JustDied(Unit *victim)
        override {
            if(pInstance)
                pInstance->SetData(DATA_TERONGOREFIENDEVENT, DONE);
    
            DoScriptText(SAY_DEATH, me);
            DespawnConstructs();
            Summons.DespawnAll();
            
            while (Creature *pGhost = me->FindNearestCreature(CREATURE_GHOST, 50.0f, true))
                pGhost->RemoveAurasDueToSpell(40268); //Free players from constructs
        }
    
        void SetThreatList(Creature* unit)
        {
            if(!unit) return;
    
            std::list<HostileReference*>& m_threatlist = me->getThreatManager().getThreatList();
            auto i = m_threatlist.begin();
            for(i = m_threatlist.begin(); i != m_threatlist.end(); i++)
            {
                Unit* pUnit = ObjectAccessor::GetUnit((*me), (*i)->getUnitGuid());
                if(pUnit && pUnit->IsAlive())
                {
                    float threat = me->GetThreat(pUnit);
                    unit->AddThreat(pUnit, threat + 5000000.0f);
                }
            }
        }
        
        float CalculateRandomLocation(float Loc, uint32 radius)
        {
            float coord = Loc;
            switch(rand()%2)
            {
                case 0:
                    coord += rand()%radius;
                    break;
                case 1:
                    coord -= rand()%radius;
                    break;
            }
            return coord;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(Intro)
            {
                if(AggroTimer < diff)
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    DoScriptText(SAY_AGGRO, me);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                    Intro = false;
                    if(AggroTargetGUID)
                    {
                        me->ClearUnitState(UNIT_STATE_ROOT);
                        Unit* pUnit = ObjectAccessor::GetUnit((*me), AggroTargetGUID);
                        if(pUnit)
                            AttackStart(pUnit);
    
                        DoZoneInCombat();
                    }
                    else
                    {
                        EnterEvadeMode();
                        return;
                    }
                }else AggroTimer -= diff;
            }
    
            if (me->GetDistance(606.641, 402.173, 187.173) > 90.0f) {
                EnterEvadeMode();
                return;
            }
    
            if(!UpdateVictim() || Intro)
                return;
    
            // Ignore NPCs
            if(!HasPlayerTarget())
            {
                EnterEvadeMode();
                return;
            }
    
            if (me->GetVictim())
                me->SetInFront(me->GetVictim());
    
            if(ShadowOfDeathTimer < diff)
            {
                if (Unit* pShadowVictim = SelectTarget(1, 0.0f, 100.0f, true, true, true, SPELL_SHADOW_OF_DEATH, 1)) {
                    if (pShadowVictim->GetGUIDLow() == me->GetVictim()->GetGUIDLow()) //not tank?
                        ShadowOfDeathTimer = 100;       // Delay to next world tick
                    else {
                        if(DoCast(pShadowVictim, SPELL_SHADOW_OF_DEATH))
                            ShadowOfDeathTimer = TIMER_SHADOW_OF_DEATH;
                    }
                }
                
            }else ShadowOfDeathTimer -= diff;
    
            if(SummonDoomBlossomTimer < diff)
            {
                Creature* DoomBlossom = me->SummonCreature(CREATURE_DOOM_BLOSSOM, CalculateRandomLocation(me->GetPositionX(), 8), CalculateRandomLocation(me->GetPositionY(), 8), me->GetPositionZ() + 7, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
                if(DoomBlossom)
                {
                    DoomBlossom->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    DoomBlossom->SetFaction(me->GetFaction());
                    SetThreatList(DoomBlossom);
                    SummonDoomBlossomTimer = TIMER_DOOM_BLOSSOM;
                }
            }else SummonDoomBlossomTimer -= diff;
    
            if(IncinerateTimer < diff)
            {
                Unit* target = SelectTarget(1, 0.0f, 100.0f, true, false, true, 0, 0);
                if(!target)
                    target = me->GetVictim();
    
                if(target)
                {
                    switch(rand()%2)
                    {
                    case 0: DoScriptText(SAY_SPECIAL1, me); break;
                    case 1: DoScriptText(SAY_SPECIAL2, me); break;
                    }
                    DoCast(target, SPELL_INCINERATE);
                    IncinerateTimer = TIMER_INCINERATE;
                }
            }else IncinerateTimer -= diff;
    
            if(CrushingShadowsTimer < diff)
            {
                DoCast(me,SPELL_CRUSHING_SHADOWS, true);
                CrushingShadowsTimer = TIMER_CRUSHING_SHADOWS;
            }else CrushingShadowsTimer -= diff;
    
    
            if(RandomYellTimer < diff)
            {
                switch(rand()%2)
                {
                case 0: DoScriptText(SAY_SPELL1, me); break;
                case 1: DoScriptText(SAY_SPELL2, me); break;
                }
                RandomYellTimer = 50000 + rand()%51 * 1000;
            }else RandomYellTimer -= diff;
    
            if(!me->HasAuraEffect(SPELL_BERSERK, 0))
            {
                if(EnrageTimer < diff)
                {
                    DoCast(me, SPELL_BERSERK);
                    DoScriptText(SAY_ENRAGE, me);
                }else EnrageTimer -= diff;
            }
            DoMeleeAttackIfReady();
        }
    
        void DespawnConstructs()
        {
            std::list<Creature*> ConstructList;
    
            Trinity::AllCreaturesOfEntryInRange check(me, CREATURE_SHADOWY_CONSTRUCT, MAX_SEARCHER_DISTANCE);
            Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, ConstructList, check);
            Cell::VisitGridObjects(me, searcher, MAX_SEARCHER_DISTANCE);
    
            if(!ConstructList.empty())
                for(auto & itr : ConstructList)
                    itr->DespawnOrUnsummon();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_teron_gorefiendAI(creature);
    }
};


class mob_shadowy_construct : public CreatureScript
{
public:
    mob_shadowy_construct() : CreatureScript("mob_shadowy_construct")
    { }

    class mob_shadowy_constructAI : public ScriptedAI
    {
    public:
        mob_shadowy_constructAI(Creature* c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            me->SetKeepActive(5 * MINUTE*IN_MILLISECONDS);
        }

        InstanceScript* pInstance;

        uint32 AtrophyTimer;
        uint32 AttackTimer;
        uint32 ResetCheckTimer;
        uint64 TeronGUID;

        bool SetAggro;

        void Reset()
            override {
            //Freezing Trap (each rank)
            me->ApplySpellImmune(0, IMMUNITY_ID, 1499, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 14310, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 14311, true);

            // immune to frost trap aura
            me->ApplySpellImmune(0, IMMUNITY_ID, 3600, true);

            AtrophyTimer = 2000;
            SetAggro = false;
            AttackTimer = 3000;
            if (pInstance)
                TeronGUID = pInstance->GetData64(DATA_TERON);

            /*if (Creature *pTeron = me->FindNearestCreature(22871, 80.0f, true)) {
            if (Unit *pTarget = ((boss_teron_gorefiend::boss_teron_gorefiendAI*)pTeron->AI())->GetConstructTarget())
            me->AI()->AttackStart(pTarget);
            }*/

            if (pInstance) {
                if (Creature *pTeron = pInstance->instance->GetCreature(TeronGUID)) {
                    if (Unit *pTarget = ((boss_teron_gorefiend::boss_teron_gorefiendAI*)pTeron->AI())->GetConstructTarget())
                        me->AI()->AttackStart(pTarget);
                }
            }

            me->AddAura(SPELL_SHADOW_STRIKES, me);
            me->AddAura(SPELL_PASSIVE_SHADOWFORM, me);

            ResetCheckTimer = 1500;
        }

        void EnterCombat(Unit* who) override {}

        void DamageTaken(Unit* done_by, uint32 &damage)
            override {
            // can only be damaged by players in spirit form
            if (done_by->GetDisplayId() != 21300) {
                damage = 0;
                if (done_by->GetTypeId() == TYPEID_PLAYER) {
                    WorldPacket data(SMSG_CAST_FAILED, (4 + 2));              // prepare packet error message
                    data << uint32(0);                                      // spellId
                    data << uint8(SPELL_FAILED_IMMUNE);                     // reason
                    done_by->ToPlayer()->GetSession()->SendPacket(&data);               // send message: Invalid target
                }
            }
            else
                DoModifyThreatPercent(done_by, -100);
        }

        void SpellHit(Unit *caster, SpellInfo const* spellInfo)
            override {
            if (caster->GetDisplayId() != 21300)
                me->RemoveAurasByCasterSpell(spellInfo->Id, caster->GetGUID());
        }

        void UpdateAI(const uint32 diff)
            override {
            if (ResetCheckTimer <= diff) {
                if (Creature *pTeron = pInstance->instance->GetCreature(TeronGUID)) {
                    if (!pTeron->IsInCombat())
                        me->DisappearAndDie();
                }
                ResetCheckTimer = 1500;
            }
            else
                ResetCheckTimer -= diff;

            if (AttackTimer && AttackTimer <= diff)
            {
                SetAggro = true;
                AttackTimer = 0;

            }
            else AttackTimer -= diff;

            if (SetAggro) {
                if (Creature* Teron = (ObjectAccessor::GetCreature((*me), TeronGUID)))
                    SetThreatList(Teron);

                if (Unit* u = SelectTarget(0, 0.0f, 100.0f, true, true, true, SPELL_SHADOW_OF_DEATH, 1))
                    me->AI()->AttackStart(u);

                SetAggro = false;
            }

            if (AtrophyTimer < diff)
            {
                if (Unit *playerInMelee = me->SelectNearestTarget(5)) {
                    if (!playerInMelee->IsPossessed() && !playerInMelee->IsPossessing())
                        DoCast(playerInMelee, SPELL_ATROPHY);
                }
                AtrophyTimer = 2000;

            }
            else AtrophyTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void DoMeleeAttackIfReady() override
        {
            /*  FIXME
            if(me->IsAttackReady())
            {
            if(me->IsWithinMeleeRange(me->GetVictim()))
            {
            if (me->CanMelee() && (!me->GetVictim()->IsPossessed() && !me->GetVictim()->IsPossessing()))
            {
            me->AttackerStateUpdate(me->GetVictim());
            me->ResetAttackTimer();
            } else{
            me->ResetAttackTimer();
            }
            }
            } */
        }

        void SetThreatList(Creature* unit)
        {
            if (!unit) return;

            std::list<HostileReference*>& m_threatlist = unit->getThreatManager().getThreatList();
            auto i = m_threatlist.begin();
            for (i = m_threatlist.begin(); i != m_threatlist.end(); i++)
            {
                Unit* pUnit = ObjectAccessor::GetUnit((*me), (*i)->getUnitGuid());
                if (pUnit && pUnit->IsAlive())
                {
                    if (pUnit->GetDisplayId() != 21300 && !pUnit->HasAuraEffect(40282, 0)) {
                        float threat = unit->getThreatManager().getThreat(pUnit);
                        me->AddThreat(pUnit, threat + 5000000.0f);
                    }
                }
            }
        }

        void DamageDeal(Unit* target, uint32 &damage)
        {
            if (target->GetDisplayId() == 21300) //vengeful spirit
                damage = 0;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_shadowy_constructAI(creature);
    }
};


void AddSC_boss_teron_gorefiend()
{
    new mob_doom_blossom();
    new mob_shadowy_construct();
    new boss_teron_gorefiend();
}
