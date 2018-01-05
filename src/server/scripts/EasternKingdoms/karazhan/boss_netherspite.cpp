/* ScriptData
SDName: Boss_Netherspite
SD%Complete: 80
SDComment: some workaround
SDCategory: Karazhan
EndScriptData */


#include "karazhan.h"

#define EMOTE_PHASE_PORTAL          -1532089
#define EMOTE_PHASE_BANISH          -1532090

#define SPELL_NETHERBURN_AURA       30522
#define SPELL_VOIDZONE              37063
#define SPELL_NETHER_INFUSION       38688
#define SPELL_NETHERBREATH          38523
#define SPELL_BANISH_VISUAL         39833
#define SPELL_BANISH_ROOT           42716
#define SPELL_EMPOWERMENT           38549
#define SPELL_NETHERSPITE_ROAR      38684

const float PortalCoord[3][3] =
{
    {-11195.353516f, -1613.237183f, 278.237258f }, // Left side
    {-11137.846680f, -1685.607422f, 278.239258f }, // Right side
    {-11094.493164f, -1591.969238f, 279.949188f }  // Back side
};

enum Netherspite_Portal{
    RED_PORTAL   = 0, // Perseverence
    GREEN_PORTAL = 1, // Serenity
    BLUE_PORTAL  = 2 // Dominance
};

const uint32 PortalID[3] =     {17369, 17367, 17368};
const uint32 PortalVisual[3] = {30487, 30490, 30491};
const uint32 PortalBeam[3] =   {30465, 30464, 30463};
const uint32 PlayerBuff[3] =   {30421, 30422, 30423};
const uint32 NetherBuff[3] =   {30466, 30467, 30468};
const uint32 PlayerDebuff[3] = {38637, 38638, 38639};


class boss_netherspite : public CreatureScript
{
public:
    boss_netherspite() : CreatureScript("boss_netherspite")
    { }

    class  boss_netherspiteAI : public BossAI
    {
        public:
        boss_netherspiteAI(Creature* c) : BossAI(c, DATA_NETHERSPITE_EVENT)
        {
        }
        
        bool PortalPhase;
        bool Berserk;
        uint32 PhaseTimer; // timer for phase switching
        uint32 VoidZoneTimer;
        uint32 NetherInfusionTimer; // berserking timer
        uint32 NetherbreathTimer;
        uint32 EmpowermentTimer;
        uint32 PortalTimer; // timer for beam checking
        ObjectGuid PortalGUID[3]; // guid's of portals
        ObjectGuid BeamerGUID[3]; // guid's of auxiliary beaming portals
        ObjectGuid BeamTarget[3]; // guid's of portals' current targets
        uint32 BuffTimer[3]; // independant buff timer for each portal
    
        bool IsBetween(WorldObject* boss, WorldObject* target, WorldObject* portal) // the in-line checker
        {
            if(!boss || !portal || !target)
                return false;
    
            float xboss, yboss, xportal, yportal, xtarget, ytarget;
            xboss = boss->GetPositionX();
            yboss = boss->GetPositionY();
            xportal = portal->GetPositionX();
            yportal = portal->GetPositionY();
            xtarget = target->GetPositionX();
            ytarget = target->GetPositionY();
            
            // check if target is between (not checking distance from the beam yet)
            if(    dist(xboss,yboss,xtarget,ytarget)>=dist(xboss,yboss,xportal,yportal)  //boss is further from target than from portal
                || dist(xportal,yportal,xtarget,ytarget)>=dist(xboss,yboss,xportal,yportal)) //portal is further from target than from boss
                return false;
            // check  distance from the beam
            return (std::fabs((xboss-xportal)*ytarget+(yportal-yboss)*xtarget-xboss*yportal+xportal*yboss)/dist(xboss,yboss,xportal,yportal) < 2.0f);
        }
    
        float dist(float xa, float ya, float xb, float yb) // auxiliary method for distance
        {
            return sqrt((xa-xb)*(xa-xb) + (ya-yb)*(ya-yb));
        }
    
        void Reset()
        override {
            _Reset();
            Berserk = false;
            NetherInfusionTimer = 540000;
            VoidZoneTimer = 15000;
            NetherbreathTimer = 3000;
            
            for (uint32 & i : BuffTimer)
                i = 1000;
    
            Destroyportalortals();
            
            me->RemoveAurasDueToSpell(SPELL_NETHERBURN_AURA);
        }
    
        void SummonPortals()
        {
            uint8 r = rand()%4;
            uint8 pos[3];
            pos[RED_PORTAL] = (r%2 ? (r>1 ? 2: 1): 0);
            pos[GREEN_PORTAL] = (r%2 ? 0: (r>1 ? 2: 1));
            pos[BLUE_PORTAL] = (r>1 ? 1: 2); // Blue Portal not on the left side (0)
    
            for(int i=0; i<3; ++i)
                if(Creature *portal = me->SummonCreature(PortalID[i],PortalCoord[pos[i]][0],PortalCoord[pos[i]][1],PortalCoord[pos[i]][2],0,TEMPSUMMON_TIMED_DESPAWN,60000))
                {
                    PortalGUID[i] = portal->GetGUID();
                    portal->AddAura(PortalVisual[i], portal);
                    portal->SetReactState(REACT_PASSIVE);
                    if(portal->AI()) portal->AI()->SetCombatMovementAllowed(false);
                }
        }
    
        void Destroyportalortals()
        {
            for(int i=0; i<3; ++i)
            {
                if(Creature *portal = ObjectAccessor::GetCreature(*me, PortalGUID[i]))
                {
                    portal->SetVisible(false);
                    portal->DealDamage(portal, portal->GetMaxHealth());
                    portal->RemoveFromWorld();
                }
                if(Creature *portal = ObjectAccessor::GetCreature(*me, BeamerGUID[i]))
                {
                    portal->SetVisible(false);
                    portal->DealDamage(portal, portal->GetMaxHealth());
                    portal->RemoveFromWorld();
                }
                PortalGUID[i] = ObjectGuid::Empty;
                BeamTarget[i] = ObjectGuid::Empty;
            }
        }
    
        void UpdatePortals(uint32 const diff) // Here we handle the beams' behavior
        {
            for(int j=0; j<3; ++j) // j = color
                if(Creature *portal = ObjectAccessor::GetCreature(*me, PortalGUID[j]))
                {
                    // the one who's been casted upon before
                    Unit *current = ObjectAccessor::GetUnit(*portal, BeamTarget[j]);
                    // temporary store for the best suitable beam reciever
                    Unit *target = me;
    
                    if(Map* map = me->GetMap())
                    {
                        Map::PlayerList const& players = map->GetPlayers();
                    
                        // get the best suitable target
                        for(const auto & player : players)
                        {
                            Player* p = player.GetSource();
                            if(p && p->IsAlive() // alive
                                && !p->IsGameMaster()
                                && (!target || (target->GetExactDistance2d(portal)) > (p->GetExactDistance2d(portal)) ) // closer than current best
                                && !p->HasAuraEffect(PlayerDebuff[j],0) // not extargetausted
                                && !p->HasAuraEffect(PlayerBuff[(j+1)%3],0) // not on another beam
                                && !p->HasAuraEffect(PlayerBuff[(j+2)%3],0)
                                && IsBetween(me, p, portal)) // on the beam
                                target = p;
                        }
                    }
                    // buff the target
                    if(target->GetTypeId() == TYPEID_PLAYER) {
                        if (BuffTimer[j] <= diff) {
                            target->AddAura(PlayerBuff[j], target);
                            BuffTimer[j] = 1000;
                        }
                    }
                    else if (BuffTimer[j] <= diff) {
                        target->AddAura(NetherBuff[j], target);
                        BuffTimer[j] = 1000;
                    }
                    // cast visual beam on the chosen target if switched
                    // simple target switching isn't working -> using BeamerGUID to cast (workaround)
                    if(!current || target != current)
                    {
                        //if (current && current->GetTyportaleId() == TyportalEID_PLAYER)
                        //    current->AddAura(PlayerDebuff[j], current);
                        BeamTarget[j] = target->GetGUID();
                        // remove currently beaming portal
                        if(Creature *beamer = ObjectAccessor::GetCreature(*portal, BeamerGUID[j]))
                        {
                            beamer->CastSpell(target, PortalBeam[j], TRIGGERED_NONE);
                            beamer->SetVisible(false);
                            beamer->DealDamage(beamer, beamer->GetMaxHealth());
                            beamer->RemoveFromWorld();
                            BeamerGUID[j].Clear();
                        }
                        // create new one and start beaming on the target
                        if(Creature *beamer = portal->SummonCreature(PortalID[j],portal->GetPositionX(),portal->GetPositionY(),portal->GetPositionZ(),portal->GetOrientation(),TEMPSUMMON_TIMED_DESPAWN,60000))
                        {
                            beamer->CastSpell(target, PortalBeam[j], TRIGGERED_NONE);
                            BeamerGUID[j] = beamer->GetGUID();
                        }
                    }
                    // aggro target if Red Beam
                    if(j==RED_PORTAL && me->GetVictim() != target && target->GetTypeId() == TYPEID_PLAYER)
                        me->GetThreatManager().AddThreat(target, 100000.0f+me->GetThreatManager().GetThreat(me->GetVictim()));
                }
        }
    
        void SwitchToPortalPhase()
        {
            me->RemoveAurasDueToSpell(SPELL_BANISH_ROOT);
            me->RemoveAurasDueToSpell(SPELL_BANISH_VISUAL);
            SummonPortals();
            PhaseTimer = 60000;
            PortalPhase = true;
            PortalTimer = 8000;
            EmpowermentTimer = 10000;
            DoScriptText(EMOTE_PHASE_PORTAL,me);
        }
    
        void SwitchToBanishPhase()
        {
            me->RemoveAurasDueToSpell(SPELL_EMPOWERMENT);
            me->RemoveAurasDueToSpell(SPELL_NETHERBURN_AURA);
            DoCast(me,SPELL_BANISH_VISUAL,true);
            DoCast(me,SPELL_BANISH_ROOT,true);
            Destroyportalortals();
            PhaseTimer = 30000;
            PortalPhase = false;
            DoScriptText(EMOTE_PHASE_BANISH,me);
    
            for(uint32 i : NetherBuff)
                me->RemoveAurasDueToSpell(i);
        }
    
        void JustEngagedWith(Unit *who)
        override {
            _JustEngagedWith();
            me->AddAura(SPELL_NETHERBURN_AURA, me);
            
            SwitchToPortalPhase();
        }
    
        void JustDied(Unit* killer)
        override {
            _JustDied();
            Destroyportalortals();
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
                
            for (uint32 & i : BuffTimer) {
                if (i >= diff)
                    i -= diff;
            }
            
            float x, y, z, o;
            me->GetHomePosition(x, y, z, o);
            if (me->GetDistance2d(x, y) > 65.0f)
                EnterEvadeMode();
    
            // Void Zone
            if(VoidZoneTimer < diff)
            {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM,1,45,true),SPELL_VOIDZONE,true);
                VoidZoneTimer = 15000;
            }else VoidZoneTimer -= diff;
    
            // NetherInfusion Berserk
            if(!Berserk && NetherInfusionTimer < diff)
            {
                me->AddAura(SPELL_NETHER_INFUSION, me);
                DoCast(me, SPELL_NETHERSPITE_ROAR);
                Berserk = true;
            }else NetherInfusionTimer -= diff;
    
            if(PortalPhase) // PORTAL PHASE
            {
                // Distribute beams and buffs
                if(PortalTimer < diff)
                {
                    UpdatePortals(diff);
                    PortalTimer = 200;
                }else PortalTimer -= diff;
    
                // Empowerment & Nether Burn
                if(EmpowermentTimer < diff)
                {
                    DoCast(me, SPELL_EMPOWERMENT);
                    me->AddAura(SPELL_NETHERBURN_AURA, me);
                    EmpowermentTimer = 90000;
                }else EmpowermentTimer -= diff;
                
                if(PhaseTimer < diff)
                {
                    if(!me->IsNonMeleeSpellCast(false))
                    {
                        SwitchToBanishPhase();
                        return;
                    }
                }else PhaseTimer -= diff;
            }
            else // BANISH PHASE
            {
                // Netherbreath
                if(NetherbreathTimer < diff)
                {
                    if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,40,true))
                        DoCast(target,SPELL_NETHERBREATH);
                    NetherbreathTimer = 5000+rand()%2000;
                }else NetherbreathTimer -= diff;
    
                if(PhaseTimer < diff)
                {
                    if(!me->IsNonMeleeSpellCast(false))
                    {
                        SwitchToPortalPhase();
                        return;
                    }
                }else PhaseTimer -= diff;
            }
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetKarazhanAI<boss_netherspiteAI>(creature);
    }
};


void AddSC_boss_netherspite()
{
    new boss_netherspite();
}

