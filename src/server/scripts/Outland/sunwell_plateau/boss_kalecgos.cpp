
/* ScriptData
SDName: Boss_Kalecgos
SD%Complete: 95
SDComment:
SDCategory: Sunwell_Plateau
EndScriptData */


#include "def_sunwell_plateau.h"
#include "Pet.h"

enum Quotes
{
    //Kalecgos dragon form
    SAY_EVIL_AGGRO          = -1580000,
    SAY_EVIL_SPELL1         = -1580001,
    SAY_EVIL_SPELL2         = -1580002,
    SAY_EVIL_SLAY1          = -1580003,
    SAY_EVIL_SLAY2          = -1580004,
    SAY_EVIL_ENRAGE         = -1580005,

    //Kalecgos humanoid form
    SAY_GOOD_AGGRO          = -1580006,
    SAY_GOOD_NEAR_DEATH     = -1580007,
    SAY_GOOD_NEAR_DEATH2    = -1580008,
    SAY_GOOD_PLRWIN         = -1580009,

    //Sathrovarr
    SAY_SATH_AGGRO          = -1580010,
    SAY_SATH_DEATH          = -1580011,
    SAY_SATH_SPELL1         = -1580012,
    SAY_SATH_SPELL2         = -1580013,
    SAY_SATH_SLAY1          = -1580014,
    SAY_SATH_SLAY2          = -1580015,
    SAY_SATH_ENRAGE         = -1580016
};

enum SpellIds
{
    AURA_SUNWELL_RADIANCE       =   45769,
    SPELL_SPECTRAL_EXHAUSTION    =   44867,
    SPELL_SPECTRAL_REALM_AURA         =   46021,
    AURA_SPECTRAL_INVISIBILITY  =   44801,
    AURA_DEMONIC_VISUAL         =   44800,

    SPELL_SPECTRAL_BLAST        =   44869,
    SPELL_SPECTRAL_BLAST_EFFECT   = 44866,
    SPELL_SPECTRAL_BLAST_VISUAL   = 46648,
    SPELL_SPECTRAL_REALM_TRIGGER  = 44811,
    SPELL_SPECTRAL_REALM_TELEPORT     =   46019,
    SPELL_SPECTRAL_REALM_2        = 44845,
    SPELL_SPECTRAL_REALM_REACTION = 44852,
    SPELL_ARCANE_BUFFET         =   45018,
    SPELL_FROST_BREATH          =   44799,
    SPELL_TAIL_LASH             =   45122,

    SPELL_BANISH                =   44836,
    SPELL_TRANSFORM_KALEC       =   44670,
    SPELL_ENRAGE                =   44807,

    SPELL_CORRUPTION_STRIKE     =   45029,
    SPELL_AGONY_CURSE           =   45032,
    SPELL_SHADOW_BOLT           =   45031,

    SPELL_HEROIC_STRIKE         =   29426/*45026*/,
    SPELL_REVITALIZE            =   45027

    
};

#define GO_FAILED   "Vous ne pouvez pas faire cela maintenant."

#define FLY_X   1679
#define FLY_Y   900
#define FLY_Z   82

#define CENTER_X    1705
#define CENTER_Y    930
#define RADIUS      30

#define DRAGON_REALM_Z  53.079
#define DEMON_REALM_Z   -74.558

uint32 WildMagic[]= { 44978, 45001, 45002, 45004, /*45006, */45010 };


class KalecgosTeleporter : public GameObjectScript
{
public:
    KalecgosTeleporter() : GameObjectScript("kalecgos_teleporter")
    {}

    struct KalecgosTeleporterAI : public GameObjectAI
    {
        KalecgosTeleporterAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->HasAuraEffect(SPELL_SPECTRAL_EXHAUSTION))
                player->GetSession()->SendNotification(GO_FAILED);
            else {
                player->CastSpell(player, SPELL_SPECTRAL_REALM_TELEPORT, TRIGGERED_FULL_MASK);
                if (player->GetPet()) {
                    player->GetPet()->CastSpell(player->GetPet(), SPELL_SPECTRAL_REALM_TELEPORT, TRIGGERED_FULL_MASK);
                    player->AddAura(SPELL_SPECTRAL_REALM_AURA, player->GetPet());
                }
                player->RemoveAurasDueToSpell(SPELL_ARCANE_BUFFET);
                if (player->HasAuraEffect(SPELL_SPECTRAL_EXHAUSTION)) {
                    player->RemoveAurasDueToSpell(SPELL_SPECTRAL_EXHAUSTION);    // FIXME: If this happens, this is a bug.
                    TC_LOG_ERROR("scripts", "Sunwell Plateau/Kalecgos: Spectral Blast target (guid %u) had Spectral exhaustion when teleported VIA PORTAL!", player->GetGUID().GetCounter());
                }
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new KalecgosTeleporterAI(go);
    }
};

class boss_kalecgos : public CreatureScript
{
public:
    boss_kalecgos() : CreatureScript("boss_kalecgos")
    { }

    class boss_kalecgosAI : public ScriptedAI
    {
        public:
        boss_kalecgosAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            pulledOnce = false;
            hasEnded = true;
        }
    
        InstanceScript *pInstance;
    
        uint32 ArcaneBuffetTimer;
        uint32 FrostBreathTimer;
        uint32 WildMagicTimer;
        uint32 SpectralBlastTimer;
        uint32 TailLashTimer;
        uint32 CheckTimer;
        uint32 TalkTimer;
        uint32 TalkSequence;
        uint32 CloseDoorsTimer;
    
        bool isFriendly;
        bool isEnraged;
        bool isBanished;
        bool pulledOnce;
        bool hasEnded;
    
        ObjectGuid SathGUID;
        ObjectGuid ForceFieldGUID;
        ObjectGuid Wall1GUID;
        ObjectGuid Wall2GUID;
    
        void Reset()
        override {
            if(pInstance)
            {
                SathGUID = ObjectGuid(pInstance->GetData64(DATA_SATHROVARR));
                ForceFieldGUID = ObjectGuid(pInstance->GetData64(DATA_GO_FORCEFIELD));
                Wall1GUID = ObjectGuid(pInstance->GetData64(DATA_GO_KALEC_WALL_1));
                Wall2GUID = ObjectGuid(pInstance->GetData64(DATA_GO_KALEC_WALL_2));
            }
    
            Unit *Sath = ObjectAccessor::GetUnit(*me,SathGUID);
            if(Sath) {
                (Sath->ToCreature())->AI()->EnterEvadeMode();
                Sath->ToCreature()->SetReactState(REACT_PASSIVE);
            }
    
            GameObject *Door = GameObject::GetGameObject(*me, ForceFieldGUID);
            if (Door)
                Door->UseDoorOrButton();
            GameObject* Wall1 = GameObject::GetGameObject(*me, Wall1GUID);
            if (Wall1)
            {
                if (me->IsAlive())
                    Wall1->ResetDoorOrButton();
                else
                    Wall1->UseDoorOrButton();
            }
            GameObject *Wall2 = GameObject::GetGameObject(*me, Wall2GUID);
            if (Wall2)
                Wall2->UseDoorOrButton();
    
            me->SetFaction(FACTION_MONSTER);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE + UNIT_FLAG_NOT_SELECTABLE);
            me->SetDisableGravity(false);
            me->SetVisible(true);
            me->SetStandState(PLAYER_STATE_SLEEP);
            me->SetReactState(REACT_AGGRESSIVE);
    
            ArcaneBuffetTimer = 8000;
            FrostBreathTimer = 15000;
            WildMagicTimer = 10000;
            TailLashTimer = 25000;
            SpectralBlastTimer = 20000+(rand()%5000);
            CheckTimer = SpectralBlastTimer+20000; //after spectral blast
            CloseDoorsTimer = 0;
    
            TalkTimer = 0;
            TalkSequence = 0;
            isFriendly = false;
            isEnraged = false;
            isBanished = false;
                
            if (pInstance && pInstance->GetData(DATA_KALECGOS_EVENT) == DONE) {
                me->SetFaction(FACTION_FRIENDLY);
                me->SetVisible(false);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                
                GameObject* door = GameObject::GetGameObject(*me, ObjectGuid(pInstance->GetData64(DATA_GO_FORCEFIELD)));
                if (door)
                    door->UseDoorOrButton();
                GameObject* wall1 = GameObject::GetGameObject(*me, ObjectGuid(pInstance->GetData64(DATA_GO_KALEC_WALL_1)));
                if (wall1)
                    wall1->UseDoorOrButton();
                GameObject* wall2 = GameObject::GetGameObject(*me, ObjectGuid(pInstance->GetData64(DATA_GO_KALEC_WALL_2)));
                if (wall2) 
                    wall2->UseDoorOrButton();
            }
            
            // Raid wipe
            /*if (!hasEnded && pulledOnce) {
                TalkTimer = 1;
                isFriendly = false;
            }*/
        }
        
        void EnterEvadeMode(EvadeReason why)
        override {
            /*if (!hasEnded) {
                TalkTimer = 1;
                isFriendly = false;
            }*/
            
            if (me->IsInCombat() && me->IsVisible()) {
                TalkSequence = 0;
                TalkTimer = 1;
                isFriendly = false;
                me->SetReactState(REACT_PASSIVE);
                
                return;
            }
            
            ScriptedAI::EnterEvadeMode(why);
        }
    
        void DamageTaken(Unit *done_by, uint32 &damage)
        override {
            if(damage >= me->GetHealth() && done_by != me)
                damage = 0;
        }
    
        void JustEngagedWith(Unit* who)
        override {
            me->SetStandState(PLAYER_STATE_NONE);
            DoScriptText(SAY_EVIL_AGGRO, me);
            GameObject* Door = GameObject::GetGameObject(*me, ForceFieldGUID);
            if(Door) 
                Door->ResetDoorOrButton();
            GameObject* Wall1 = GameObject::GetGameObject(*me, Wall1GUID);
            if(Wall1) 
                Wall1->ResetDoorOrButton();
            GameObject* Wall2 = GameObject::GetGameObject(*me, Wall2GUID);
            if(Wall2) 
                Wall2->ResetDoorOrButton();
            DoZoneInCombat();
            CloseDoorsTimer = 5000;
            
            pulledOnce = true;
            hasEnded = false;
    
            if(pInstance)
                pInstance->SetData(DATA_KALECGOS_EVENT, IN_PROGRESS);
                
            Unit *Sath = ObjectAccessor::GetUnit(*me,SathGUID);
            if(Sath)
                Sath->ToCreature()->SetReactState(REACT_AGGRESSIVE);
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(RAND(SAY_EVIL_SLAY1, SAY_EVIL_SLAY2), me);
        }
        
        void MoveInLineOfSight(Unit *pWho) override {
            if (pWho->GetTypeId() == TYPEID_PLAYER && me->GetDistance(pWho) <= 30.0f && !me->IsInCombat() && me->GetFaction() != 35)
                AttackStart(pWho);
        }
    
        void MovementInform(uint32 type,uint32 id)
        override {
            if (type != POINT_MOTION_TYPE)
                return;
                
            if (id != 1)
                return;
            
            me->SetVisible(false);
            if(isFriendly)
                me->SetDeathState(JUST_DIED);
            else
            {
                me->GetMotionMaster()->MoveTargetedHome();
                TalkTimer = 30000;
            }
        }
    
        void GoodEnding()
        {
            switch(TalkSequence)
            {
            case 1:
                me->SetFaction(FACTION_FRIENDLY);
                if (pInstance)
                    pInstance->SetData(DATA_KALECGOS_EVENT, DONE);
                TalkTimer = 1000;
                break;
            case 2:
                DoScriptText(SAY_GOOD_PLRWIN, me);
                TalkTimer = 10000;
                break;
            case 3:
                me->SetDisableGravity(true);
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovePoint(1,FLY_X,FLY_Y,FLY_Z);
                TalkTimer = 600000;
                hasEnded = true;
                break;
            default:
                break;
            }
        }
    
        void BadEnding()
        {
            switch(TalkSequence)
            {
            case 1:
                DoScriptText(SAY_EVIL_ENRAGE, me);
                TalkTimer = 3000;
                break;
            case 2:
                me->SetDisableGravity(true);
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovePoint(1,FLY_X,FLY_Y,FLY_Z);
                me->GetThreatManager().ClearAllThreat();
                TalkTimer = 600000;
                break;
            case 3:
                hasEnded = true;
                EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
                break;
            default:
                break;
            }
        }
            
        void UpdateAI(const uint32 diff) override;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_kalecgosAI(creature);
    }
};


class boss_sathrovarr : public CreatureScript
{
public:
    boss_sathrovarr() : CreatureScript("boss_sathrovarr")
    { }

    class boss_sathrovarrAI : public ScriptedAI
    {
        public:
        boss_sathrovarrAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        uint32 CorruptionStrikeTimer;
        uint32 AgonyCurseTimer;
        uint32 ShadowBoltTimer;
        uint32 CheckTimer;
        uint32 ResetThreat;
    
        ObjectGuid KalecGUID;
        ObjectGuid KalecgosGUID;
    
        bool isEnraged;
        bool isBanished;
    
        void Reset()
        override {
            if(pInstance)
                KalecgosGUID = ObjectGuid(pInstance->GetData64(DATA_KALECGOS_DRAGON));
    
            if(KalecGUID)
            {
                if(Unit* Kalec = ObjectAccessor::GetUnit(*me, KalecGUID))
                    Kalec->SetDeathState(JUST_DIED);
                KalecGUID = ObjectGuid::Empty;
            }
    
            ShadowBoltTimer = 7000 + rand()%3 * 1000;
            AgonyCurseTimer = 20000;
            CorruptionStrikeTimer = 13000;
            CheckTimer = 1000;
            ResetThreat = 1000;
            isEnraged = false;
            isBanished = false;
    
            if(pInstance && pInstance->GetData(DATA_KALECGOS_EVENT) != DONE)
                pInstance->SetData(DATA_KALECGOS_EVENT, NOT_STARTED);
        }
    
        void JustEngagedWith(Unit* who) override {
            Creature *Kalec = me->SummonCreature(MOB_KALEC, me->GetPositionX() + 10, me->GetPositionY() + 5, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0);
            if(Kalec)
            {
                me->EngageWithTarget(Kalec);
                me->GetThreatManager().AddThreat(Kalec, 100.0f);
            }
            DoScriptText(SAY_SATH_AGGRO, me);
        }
    
        void DamageTaken(Unit *done_by, uint32 &damage)
        override {
            if(damage >= me->GetHealth() && done_by != me)
                damage = 0;
        }
    
        void KilledUnit(Unit *target)
        override {
            if(target->GetGUID() == KalecGUID)
            {
                TeleportAllPlayersBack();
                if(Unit *Kalecgos = ObjectAccessor::GetUnit(*me, KalecgosGUID))
                {
                    ((boss_kalecgos::boss_kalecgosAI*)(Kalecgos->ToCreature())->AI())->TalkTimer = 1;
                    ((boss_kalecgos::boss_kalecgosAI*)(Kalecgos->ToCreature())->AI())->isFriendly = false;
                    ((boss_kalecgos::boss_kalecgosAI*)(Kalecgos->ToCreature())->AI())->TalkSequence = 0;
                }
                EnterEvadeMode();
                return;
            }
            DoScriptText(RAND(SAY_SATH_SLAY1, SAY_SATH_SLAY2), me);
        }
    
        void JustDied(Unit *killer)
        override {
            DoScriptText(SAY_SATH_DEATH, me);
            me->Relocate(me->GetPositionX(), me->GetPositionY(), DRAGON_REALM_Z, me->GetOrientation());
            WorldPacket data;                       //send update position to client
            me->BuildHeartBeatMsg(&data);
            me->SendMessageToSet(&data,true);
            
            TeleportAllPlayersBack();
            if(Unit *Kalecgos = ObjectAccessor::GetUnit(*me, KalecgosGUID))
            {
                ((boss_kalecgos::boss_kalecgosAI*)(Kalecgos->ToCreature())->AI())->TalkTimer = 1;
                ((boss_kalecgos::boss_kalecgosAI*)(Kalecgos->ToCreature())->AI())->isFriendly = true;
            }
            if(pInstance)
                pInstance->SetData(DATA_KALECGOS_EVENT, DONE);
                
            GameObject *Door = GameObject::GetGameObject(*me, ObjectGuid(pInstance->GetData64(DATA_GO_FORCEFIELD)));
            if (Door) Door->UseDoorOrButton();
            GameObject *Wall1 = GameObject::GetGameObject(*me, ObjectGuid(pInstance->GetData64(DATA_GO_KALEC_WALL_1)));
            if (Wall1) Wall1->UseDoorOrButton();
            GameObject *Wall2 = GameObject::GetGameObject(*me, ObjectGuid(pInstance->GetData64(DATA_GO_KALEC_WALL_2)));
            if (Wall2) Wall2->UseDoorOrButton();
                
            // Remove invisibility auras
            me->RemoveAurasDueToSpell(44800);
            me->RemoveAurasDueToSpell(44801);
        }
    
        void TeleportAllPlayersBack()
        {
            Map *map = me->GetMap();
            if(!map->IsDungeon()) return;
            Map::PlayerList const &PlayerList = map->GetPlayers();
            Map::PlayerList::const_iterator i;
            for(i = PlayerList.begin(); i != PlayerList.end(); ++i)
                if(Player* i_pl = i->GetSource()) {
                    i_pl->RemoveAurasDueToSpell(SPELL_AGONY_CURSE);
                    if(i_pl->HasAuraEffect(SPELL_SPECTRAL_REALM_AURA))
                        i_pl->RemoveAurasDueToSpell(SPELL_SPECTRAL_REALM_AURA);
                }
        }
                
        void _DoMeleeAttackIfReady(bool withCorruptionStrike)
        {
            if (withCorruptionStrike)
                DoCast(me->GetVictim(), SPELL_CORRUPTION_STRIKE, true);
                
            UnitAI::DoMeleeAttackIfReady();
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
                
            // Check LoS EVERY update, maybe the current target was teleported back
            if (me->GetVictim()->GetPositionZ() >= -65.0f || !me->GetVictim()->IsWithinLOSInMap(me)) {
                me->GetThreatManager().ClearThreat(me->GetVictim());
                if(KalecGUID) {
                    if(Unit* Kalec = ObjectAccessor::GetUnit(*me, KalecGUID))
                        me->AI()->AttackStart(Kalec);
                }
            }
                
            // If tank has not the aura anymore, maybe he was teleported back -> start attack on Kalecgos human form
            if (me->GetVictim()->GetTypeId() == TYPEID_PLAYER && !me->GetVictim()->HasAuraEffect(SPELL_SPECTRAL_REALM_AURA)) {
                if(KalecGUID) {
                    if(Unit* Kalec = ObjectAccessor::GetUnit(*me, KalecGUID))
                        me->AI()->AttackStart(Kalec);
                }
            }
    
            if(CheckTimer < diff)
            {
                if (((me->GetHealthPct()) < 10) && !isEnraged)
                {
                    Unit* Kalecgos = ObjectAccessor::GetUnit(*me, KalecgosGUID);
                    if(Kalecgos)
                    {
                        //Kalecgos->CastSpell(Kalecgos, SPELL_ENRAGE, TRIGGERED_FULL_MASK);
                        Kalecgos->AddAura(SPELL_ENRAGE, Kalecgos);
                        ((boss_kalecgos::boss_kalecgosAI*)(Kalecgos->ToCreature())->AI())->isEnraged = true;
                    }
                    //DoCast(me, SPELL_ENRAGE, true);
                    me->AddAura(SPELL_ENRAGE, me);
                    isEnraged = true;
                }
    
                if(!isBanished && me->GetHealthPct() < 1)
                {
                    if(Unit *Kalecgos = ObjectAccessor::GetUnit(*me, KalecgosGUID))
                    {
                        if(((boss_kalecgos::boss_kalecgosAI*)(Kalecgos->ToCreature())->AI())->isBanished)
                        {
                            me->KillSelf();
                            return;
                        }
                        else
                        {
                            DoCast(me, SPELL_BANISH);
                            isBanished = true;
                        }
                    }
                    else
                    {
                        me->TextEmote("is unable to find Kalecgos", nullptr);
                        EnterEvadeMode();
                        return;
                    }
                }
                CheckTimer = 1000;
            }else CheckTimer -= diff;
    
            if(ResetThreat < diff)
            {
                if (( me->GetVictim()->HasAuraEffect(SPELL_SPECTRAL_EXHAUSTION)) && (me->GetVictim()->GetTypeId() == TYPEID_PLAYER))
                    me->GetThreatManager().ClearThreat(me->GetVictim());

                ResetThreat = 1000;
            }else ResetThreat -= diff;
    
            if(ShadowBoltTimer < diff)
            {
                DoScriptText(SAY_SATH_SPELL1, me);
                DoCast(me, SPELL_SHADOW_BOLT);
                ShadowBoltTimer = 7000+(rand()%3000);
            }else ShadowBoltTimer -= diff;
    
            if(AgonyCurseTimer < diff)
            {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                if(!target) target = me->GetVictim();
                DoCast(target, SPELL_AGONY_CURSE);
                AgonyCurseTimer = 20000;
            }else AgonyCurseTimer -= diff;
    
            if(CorruptionStrikeTimer < diff)
            {
                DoScriptText(SAY_SATH_SPELL2, me);
                _DoMeleeAttackIfReady(true);
                CorruptionStrikeTimer = 13000;
            }else CorruptionStrikeTimer -= diff;
    
            _DoMeleeAttackIfReady(false);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_sathrovarrAI(creature);
    }
};


void boss_kalecgos::boss_kalecgosAI::UpdateAI(const uint32 diff)
{
    if (TalkTimer)
    {
        if (!TalkSequence)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE + UNIT_FLAG_NOT_SELECTABLE);
            me->InterruptNonMeleeSpells(true);
            if (isFriendly)
                me->RemoveAurasDueToSpell(SPELL_ENRAGE);
            me->SetHealth(me->GetMaxHealth());
            me->RemoveAllAuras();
            me->GetThreatManager().ClearAllThreat();
            me->CombatStop();
            GameObject *Door = GameObject::GetGameObject(*me, ForceFieldGUID);
            if (Door) Door->UseDoorOrButton();
            GameObject *Wall1 = GameObject::GetGameObject(*me, Wall1GUID);
            if (Wall1) Wall1->SetGoState(isFriendly ? GO_STATE_ACTIVE : GO_STATE_READY);
            GameObject *Wall2 = GameObject::GetGameObject(*me, Wall2GUID);
            if (Wall2) Wall2->UseDoorOrButton();
            TalkSequence++;
        }
        if (TalkTimer <= diff)
        {
            if (isFriendly)
                GoodEnding();
            else
                BadEnding();
            TalkSequence++;
        }
        else TalkTimer -= diff;
    }
    else
    {
        if (!UpdateVictim())
            return;

        if (me->GetDistance(1704.22, 924.758, 53.1608) > 35.0f) {
            EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
            return;
        }

        // Check LoS EVERY update, maybe the current target was teleported in the spectral realm
        if (me->GetVictim()->GetPositionZ() <= 52.5f || !me->GetVictim()->IsWithinLOSInMap(me))
        {
            me->GetThreatManager().ClearThreat(me->GetVictim());
            UpdateVictim();
        }

        if (CheckTimer < diff)
        {
            if (((me->GetHealthPct()) < 10) && !isEnraged)
            {
                Unit* Sath = ObjectAccessor::GetUnit(*me, SathGUID);
                if (Sath)
                {
                    //Sath->CastSpell(Sath, SPELL_ENRAGE, TRIGGERED_FULL_MASK);
                    Sath->AddAura(SPELL_ENRAGE, Sath);
                    ((boss_sathrovarr::boss_sathrovarrAI*)(Sath->ToCreature())->AI())->isEnraged = true;
                }
                //DoCast(me, SPELL_ENRAGE, true);
                me->AddAura(SPELL_ENRAGE, me);
                isEnraged = true;
            }

            if (!isBanished && me->GetHealthPct() < 1)
            {
                if (Unit *Sath = ObjectAccessor::GetUnit(*me, SathGUID))
                {
                    if (((boss_sathrovarr::boss_sathrovarrAI*)(Sath->ToCreature())->AI())->isBanished)
                    {
                        Sath->KillSelf();
                        return;
                    }
                    else
                    {
                        DoCast(me, SPELL_BANISH);
                        isBanished = true;
                    }
                }
                else
                {
                    error_log("TSCR: Didn't find Shathrowar. Kalecgos event reseted.");
                    EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
                    return;
                }
            }
            CheckTimer = 1000;
        }
        else CheckTimer -= diff;

        if (ArcaneBuffetTimer < diff)
        {
            DoCastAOE(SPELL_ARCANE_BUFFET);
            ArcaneBuffetTimer = 8000;
        }
        else ArcaneBuffetTimer -= diff;

        if (FrostBreathTimer < diff)
        {
            DoCastAOE(SPELL_FROST_BREATH);
            FrostBreathTimer = 15000;
        }
        else FrostBreathTimer -= diff;

        if (TailLashTimer < diff)
        {
            DoCastAOE(SPELL_TAIL_LASH);
            TailLashTimer = 15000;
        }
        else TailLashTimer -= diff;

        if (WildMagicTimer < diff)
        {
            DoCastAOE(WildMagic[rand() % 5]);
            WildMagicTimer = 20000;
        }
        else WildMagicTimer -= diff;

        if (SpectralBlastTimer < diff)
        {
            DoCastAOE(SPELL_SPECTRAL_BLAST, true);
            SpectralBlastTimer = 20000 + (rand() % 5000);
        }
        else SpectralBlastTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

class SpectralBlastSelector : NonTankTargetSelector
{
public:
    SpectralBlastSelector(Unit* source) : NonTankTargetSelector(source, true) { }

    bool operator()(WorldObject* target) const
    {
        if (Unit* unitTarget = target->ToUnit())
            return !NonTankTargetSelector::operator()(unitTarget) 
            || unitTarget->HasAura(SPELL_SPECTRAL_EXHAUSTION) 
            || unitTarget->HasAura(SPELL_SPECTRAL_REALM_AURA)
            || unitTarget->IsDead()
            || unitTarget->GetPositionZ() <= 52.5f; //in spectral realm
        return false;
    }
};

class boss_kalec : public CreatureScript
{
public:
    boss_kalec() : CreatureScript("boss_kalec")
    { }

    class boss_kalecAI : public ScriptedAI
    {
        public:
        InstanceScript *pInstance;
    
        uint32 RevitalizeTimer;
        uint32 HeroicStrikeTimer;
        uint32 YellTimer;
        uint32 YellSequence;
    
        ObjectGuid SathGUID;
    
        bool isEnraged; // if demon is enraged
    
        boss_kalecAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        void Reset()
        override {
            if(pInstance)
                SathGUID = ObjectGuid(pInstance->GetData64(DATA_SATHROVARR));
    
            RevitalizeTimer = 5000;
            HeroicStrikeTimer = 3000;
            YellTimer = 5000;
            YellSequence = 0;
    
            isEnraged = false;
        }
    
        void JustEngagedWith(Unit* who) override {}
        
        void HealReceived(Unit* done_by, uint32& addhealth)
        override {
            addhealth = 0;
        }
    
        void DamageTaken(Unit *done_by, uint32 &damage)
        override {
            if (done_by->ToPlayer() && done_by->ToPlayer()->IsGameMaster())
                return;
            if(done_by->GetGUID() != SathGUID)
                damage = 0;
            else if(isEnraged)
                damage *= 3;
            if (done_by->GetGUID() == SathGUID)
                damage *= 1.3f;
            if (damage >= me->GetHealth() && done_by->ToCreature() && done_by->GetGUID() == SathGUID)
                done_by->ToCreature()->AI()->KilledUnit(me);
        }
        
        void JustDied(Unit *pKiller)
        override {
            TeleportAllPlayersBack();
        }
        
        void TeleportAllPlayersBack()
        {
            Map *map = me->GetMap();
            if(!map->IsDungeon()) return;
            Map::PlayerList const &PlayerList = map->GetPlayers();
            Map::PlayerList::const_iterator i;
            for(i = PlayerList.begin(); i != PlayerList.end(); ++i)
                if(Player* i_pl = i->GetSource()) {
                    i_pl->RemoveAurasDueToSpell(SPELL_AGONY_CURSE);
                    if(i_pl->HasAuraEffect(SPELL_SPECTRAL_REALM_AURA))
                        i_pl->RemoveAurasDueToSpell(SPELL_SPECTRAL_REALM_AURA);
                }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if(YellTimer < diff)
            {
                switch(YellSequence)
                {
                case 0:
                    DoScriptText(SAY_GOOD_AGGRO, me);
                    YellSequence++;
                    break;
                case 1:
                    if(me->GetHealthPct() < 50)
                    {
                        DoScriptText(SAY_GOOD_NEAR_DEATH, me);
                        YellSequence++;
                    }
                    break;
                case 2:
                    if(me->GetHealthPct() < 10)
                    {
                        DoScriptText(SAY_GOOD_NEAR_DEATH2, me);
                        YellSequence++;
                    }
                    break;
                default:
                    break;
                }
                YellTimer = 5000;
            }
    
            if(RevitalizeTimer < diff)
            {
                me->InterruptNonMeleeSpells(false);
                DoCast(me, SPELL_REVITALIZE);
                RevitalizeTimer = 5000;
            }else RevitalizeTimer -= diff;
    
            if(HeroicStrikeTimer < diff)
            {
                DoCast(me->GetVictim(), SPELL_HEROIC_STRIKE);
                HeroicStrikeTimer = 2000;
            }else HeroicStrikeTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_kalecAI(creature);
    }
};

// 44869 - Spectral Blast
class spell_kalecgos_spectral_blast : public SpellScript
{
    PrepareSpellScript(spell_kalecgos_spectral_blast);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_SPECTRAL_BLAST_EFFECT,
            SPELL_SPECTRAL_BLAST_VISUAL,
            SPELL_SPECTRAL_REALM_TRIGGER
        });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(SpectralBlastSelector(GetCaster()));
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        target->CastSpell(target, SPELL_SPECTRAL_BLAST_EFFECT, true);
        caster->CastSpell(target, SPELL_SPECTRAL_BLAST_VISUAL, true);
        caster->CastSpell(target, SPELL_SPECTRAL_REALM_TRIGGER, true);

        //take pet with player
        if (target->ToPlayer() && target->ToPlayer()->GetPet()) {
            Pet *pet = target->ToPlayer()->GetPet();
            target->CastSpell(pet, SPELL_SPECTRAL_REALM_TELEPORT, TRIGGERED_FULL_MASK);
            target->AddAura(SPELL_SPECTRAL_REALM_AURA, pet);
            pet->Relocate(pet->GetPositionX(), pet->GetPositionY(), pet->GetPositionZ(), pet->GetOrientation());
        }
        caster->GetThreatManager().ModifyThreatByPercent(target, -100);  // Reset threat so Kalecgos does not follow the player in spectral realm :)
        target->RemoveAurasDueToSpell(SPELL_ARCANE_BUFFET); // FIXME: I'm not sure this is blizzlike
        if (target->HasAuraEffect(SPELL_SPECTRAL_EXHAUSTION)) {
            target->RemoveAurasDueToSpell(SPELL_SPECTRAL_EXHAUSTION);    // FIXME: If this happens, this is a bug.
            TC_LOG_ERROR("scripts", "Sunwell Plateau/Kalecgos: Spectral Blast target (guid %u) had Spectral exhaustion when teleported!", target->GetGUID().GetCounter());
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_kalecgos_spectral_blast::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_kalecgos_spectral_blast::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 44811 - Spectral Realm
class spell_kalecgos_spectral_realm_trigger : public SpellScript
{
    PrepareSpellScript(spell_kalecgos_spectral_realm_trigger);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_SPECTRAL_REALM_TELEPORT,
            SPELL_SPECTRAL_REALM_AURA,
            SPELL_SPECTRAL_REALM_2,
            SPELL_SPECTRAL_REALM_REACTION
        });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* target = GetHitUnit();
        target->CastSpell(target, SPELL_SPECTRAL_REALM_TELEPORT, true);
        target->CastSpell(target, SPELL_SPECTRAL_REALM_AURA, true);
        target->CastSpell(target, SPELL_SPECTRAL_REALM_2, true);
        target->CastSpell(target, SPELL_SPECTRAL_REALM_REACTION, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_kalecgos_spectral_realm_trigger::HandleDummy, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

void AddSC_boss_kalecgos()
{
    new boss_kalecgos();
    new boss_sathrovarr();
    new boss_kalec();
    new KalecgosTeleporter();

    RegisterSpellScript(spell_kalecgos_spectral_blast);
    RegisterSpellScript(spell_kalecgos_spectral_realm_trigger);
}
