
/* ScriptData
SDName: Blades_Edge_Mountains
SD%Complete: 90
SDComment: Quest support: 10503, 10504, 10556, 10609, 10682, 10821, 10980, 10998, 11000 Ogri'la->Skettis Flight. (npc_daranelle needs bit more work before consider complete)
SDCategory: Blade's Edge Mountains
EndScriptData */

/* ContentData
mobs_bladespire_ogre
mobs_nether_drake
npc_daranelle
npc_overseer_nuaar
npc_saikkal_the_elder
npc_skyguard_handler_irena
go_legion_obelisk
npc_prophecy_questcredit
npc_grishna_falconwing
go_ethereum_chamber
npc_kolphis_darkscale
trigger_vimgol_circle_bunny
npc_vimgol
npc_soulgrinder
npc_skulloc
npc_sundered_ghost
go_apexis_relic
npc_simon_bunny
go_blue_cluster
go_green_cluster
go_red_cluster
go_yellow_cluster
go_fel_crystal_prism
npc_braxxus
npc_moarg_incinerator
npc_galvanoth
npc_zarcsin
npc_aether_ray
npc_wrangled_aether_ray
go_drake_egg
npc_rivendark
npc_obsidia
npc_insidion
npc_furywing
trigger_banishing_crystal_bunny01
npc_rally_zapnabber
npc_grulloc
npc_grishna
EndContentData */


#include "Pet.h"
#include "ObjectMgr.h"
#include "TemporarySummon.h"

/*######
## mobs_bladespire_ogre
######*/

//TODO: add support for quest 10512 + creature abilities
class mobs_bladespire_ogre : public CreatureScript
{
public:
    mobs_bladespire_ogre() : CreatureScript("mobs_bladespire_ogre")
    { }

    class mobs_bladespire_ogreAI : public ScriptedAI
    {
        public:
        mobs_bladespire_ogreAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
        }
    
        void JustEngagedWith(Unit* pWho)
        override {
        }
    
        void JustDied(Unit* pKiller)
        override {
            if (pKiller->GetTypeId() == TYPEID_PLAYER)
                (pKiller)->ToPlayer()->KilledMonsterCredit(19995, me->GetGUID());
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mobs_bladespire_ogreAI(creature);
    }
};


/*######
## mobs_nether_drake
######*/

enum eNetherDrake
{
SAY_NIHIL_1                 = -1000396,
SAY_NIHIL_2                 = -1000397,
SAY_NIHIL_3                 = -1000398,
SAY_NIHIL_4                 = -1000399,
SAY_NIHIL_INTERRUPT         = -1000400,

ENTRY_WHELP                 = 20021,
ENTRY_PROTO                 = 21821,
ENTRY_ADOLE                 = 21817,
ENTRY_MATUR                 = 21820,
ENTRY_NIHIL                 = 21823,

SPELL_T_PHASE_MODULATOR     = 37573,
SPELL_ARCANE_BLAST          = 38881,
SPELL_MANA_BURN             = 38884,
SPELL_INTANGIBLE_PRESENCE   = 36513
};


class mobs_nether_drake : public CreatureScript
{
public:
    mobs_nether_drake() : CreatureScript("mobs_nether_drake")
    { }

    class mobs_nether_drakeAI : public ScriptedAI
    {
        public:
        mobs_nether_drakeAI(Creature *c) : ScriptedAI(c) {}
    
        bool IsNihil;
        uint32 NihilSpeech_Timer;
        uint32 NihilSpeech_Phase;
    
        uint32 ArcaneBlast_Timer;
        uint32 ManaBurn_Timer;
        uint32 IntangiblePresence_Timer;
    
        void Reset()
        override {
            NihilSpeech_Timer = 2000;
            IsNihil = false;
            if( me->GetEntry() == ENTRY_NIHIL )
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                IsNihil = true;
            }
            NihilSpeech_Phase = 1;
    
            ArcaneBlast_Timer = 7500;
            ManaBurn_Timer = 10000;
            IntangiblePresence_Timer = 15000;
        }
    
        void JustEngagedWith(Unit* pWho) override { }
    
        void SpellHit(Unit *caster, const SpellInfo *spell)
        override {
            if (spell->Id == SPELL_T_PHASE_MODULATOR && caster->GetTypeId() == TYPEID_PLAYER)
            {
                uint32 cEntry = 0;
    
                switch (me->GetEntry())
                {
                    case ENTRY_WHELP:
                        cEntry = RAND(ENTRY_PROTO, ENTRY_ADOLE, ENTRY_MATUR, ENTRY_NIHIL);
                        break;
                    case ENTRY_PROTO:
                    case ENTRY_ADOLE:
                    case ENTRY_MATUR:
                        cEntry = RAND(ENTRY_ADOLE, ENTRY_MATUR, ENTRY_NIHIL);
                        break;
                    case ENTRY_NIHIL:
                        if (NihilSpeech_Phase)
                        {
                            DoScriptText(SAY_NIHIL_INTERRUPT, me);
                            IsNihil = false;
                            cEntry = RAND(ENTRY_ADOLE, ENTRY_MATUR, ENTRY_NIHIL);
                        }
                        break;
                }
    
                if (cEntry)
                {
                    me->UpdateEntry(cEntry);
    
                    if (cEntry == ENTRY_NIHIL)
                    {
                        me->InterruptNonMeleeSpells(true);
                        me->RemoveAllAuras();
                        me->GetThreatManager().ClearAllThreat();
                        me->CombatStop();
                        Reset();
                    }
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (IsNihil)
            {
                if (NihilSpeech_Phase)
                {
                    if (NihilSpeech_Timer <= diff)
                    {
                        switch (NihilSpeech_Phase)
                        {
                            case 1:
                                DoScriptText(SAY_NIHIL_1, me);
                                ++NihilSpeech_Phase;
                                break;
                            case 2:
                                DoScriptText(SAY_NIHIL_2, me);
                                ++NihilSpeech_Phase;
                                break;
                            case 3:
                                DoScriptText(SAY_NIHIL_3, me);
                                ++NihilSpeech_Phase;
                                break;
                            case 4:
                                DoScriptText(SAY_NIHIL_4, me);
                                ++NihilSpeech_Phase;
                                break;
                            case 5:
                                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                                                // + MOVEMENTFLAG_DISABLE_GRAVITY
                                me->SetDisableGravity(true);
                                //then take off to random location. creature is initially summoned, so don't bother do anything else.
                                me->GetMotionMaster()->MovePoint(0, me->GetPositionX()+100, me->GetPositionY(), me->GetPositionZ()+100);
                                NihilSpeech_Phase = 0;
                                break;
                        }
                        NihilSpeech_Timer = 5000;
                    }else NihilSpeech_Timer -=diff;
                }
                return;                                         //anything below here is not interesting for Nihil, so skip it
            }
    
            if (!UpdateVictim())
                return;
    
            if (IntangiblePresence_Timer <= diff)
            {
                DoCast(me->GetVictim(),SPELL_INTANGIBLE_PRESENCE);
                IntangiblePresence_Timer = 15000+rand()%15000;
            }else IntangiblePresence_Timer -= diff;
    
            if (ManaBurn_Timer <= diff)
            {
                Unit* target = me->GetVictim();
                if (target && target->GetPowerType() == POWER_MANA)
                    DoCast(target,SPELL_MANA_BURN);
                ManaBurn_Timer = 8000+rand()%8000;
            }else ManaBurn_Timer -= diff;
    
            if (ArcaneBlast_Timer <= diff)
            {
                DoCast(me->GetVictim(),SPELL_ARCANE_BLAST);
                ArcaneBlast_Timer = 2500+rand()%5000;
            }else ArcaneBlast_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mobs_nether_drakeAI(creature);
    }
};


/*######
## npc_daranelle
######*/

#define SAY_DARANELLE -1000401


class npc_daranelle : public CreatureScript
{
public:
    npc_daranelle() : CreatureScript("npc_daranelle")
    { }

    class npc_daranelleAI : public ScriptedAI
    {
        public:
        npc_daranelleAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
        }
    
        void JustEngagedWith(Unit* pWho)
        override {
        }
    
        void MoveInLineOfSight(Unit* pWho)
        override {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                if (pWho->HasAuraEffect(36904))
                {
                    DoScriptText(SAY_DARANELLE, me, pWho);
                    //TODO: Move the below to updateAI and run if this statement == true
                    pWho->ToPlayer()->KilledMonsterCredit(21511, me->GetGUID());
                    (pWho)->RemoveAurasDueToSpell(36904);
                }
            }
    
            ScriptedAI::MoveInLineOfSight(pWho);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_daranelleAI(creature);
    }
};


/*######
## npc_overseer_nuaar
######*/

#define GOSSIP_HON "Overseer, I am here to negotiate on behalf of the Cenarion Expedition."

class npc_overseer_nuaar : public CreatureScript
{
public:
    npc_overseer_nuaar() : CreatureScript("npc_overseer_nuaar")
    { }

   class npc_overseer_nuaarAI : public ScriptedAI
   {
   public:
        npc_overseer_nuaarAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(10682) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(10532, me->GetGUID());

            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                player->SEND_GOSSIP_MENU_TEXTID(10533, me->GetGUID());
                player->AreaExploredOrEventHappens(10682);
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_overseer_nuaarAI(creature);
    }
};



/*######
## npc_saikkal_the_elder
######*/

//TODO translate
#define GOSSIP_HSTE "Yes... yes, it's me."
#define GOSSIP_SSTE "Yes elder. Tell me more of the book."

class npc_saikkal_the_elder : public CreatureScript
{
public:
    npc_saikkal_the_elder() : CreatureScript("npc_saikkal_the_elder")
    { }

   class npc_saikkal_the_elderAI : public ScriptedAI
   {
   public:
        npc_saikkal_the_elderAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(10980) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HSTE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(10794, me->GetGUID());

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SSTE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU_TEXTID(10795, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->TalkedToCreature(me->GetEntry(), me->GetGUID());
                    player->SEND_GOSSIP_MENU_TEXTID(10796, me->GetGUID());
                    break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_saikkal_the_elderAI(creature);
    }
};



/*######
## npc_skyguard_handler_irena
######*/

#define GOSSIP_SKYGUARD "Fly me to Skettis please"

class npc_skyguard_handler_irena : public CreatureScript
{
public:
    npc_skyguard_handler_irena() : CreatureScript("npc_skyguard_handler_irena")
    { }

   class npc_skyguard_handler_irenaAI : public ScriptedAI
   {
   public:
        npc_skyguard_handler_irenaAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu( me->GetGUID() );

            if (pPlayer->GetReputationRank(1031) >= REP_HONORED)
                pPlayer->ADD_GOSSIP_ITEM( 2, GOSSIP_SKYGUARD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                player->CLOSE_GOSSIP_MENU();

                std::vector<uint32> nodes;

                nodes.resize(2);
                nodes[0] = 172;                                     //from ogri'la
                nodes[1] = 171;                                     //end at skettis
                player->ActivateTaxiPathTo(nodes);                  //TaxiPath 706
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_skyguard_handler_irenaAI(creature);
    }
};



/*######
## go_legion_obelisk
######*/

//Support for quest: You're Fired! (10821)
bool bObeliskOne, bObeliskTwo, bObeliskThree, bObeliskFour, bObeliskFive;    

enum eLegionObelisk
{
LEGION_OBELISK_ONE           = 185193,
LEGION_OBELISK_TWO           = 185195,
LEGION_OBELISK_THREE         = 185196,
LEGION_OBELISK_FOUR          = 185197,
LEGION_OBELISK_FIVE          = 185198
};
class LegionObelisk : public GameObjectScript
{
public:
    LegionObelisk() : GameObjectScript("go_legion_obelisk")
    {}

    struct LegionObeliskAI : public GameObjectAI
    {
        LegionObeliskAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(10821) == QUEST_STATUS_INCOMPLETE)
            {
                switch (me->GetEntry())
                {
                case LEGION_OBELISK_ONE:
                    bObeliskOne = true;
                    break;
                case LEGION_OBELISK_TWO:
                    bObeliskTwo = true;
                    break;
                case LEGION_OBELISK_THREE:
                    bObeliskThree = true;
                    break;
                case LEGION_OBELISK_FOUR:
                    bObeliskFour = true;
                    break;
                case LEGION_OBELISK_FIVE:
                    bObeliskFive = true;
                    break;
                }

                if (bObeliskOne && bObeliskTwo && bObeliskThree && bObeliskFour && bObeliskFive)
                {
                    me->SummonCreature(19963, 2943.40f, 4778.20f, 284.49f, 0.94f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    //reset global var
                    bObeliskOne = false;
                    bObeliskTwo = false;
                    bObeliskThree = false;
                    bObeliskFour = false;
                    bObeliskFive = false;
                }
            }

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new LegionObeliskAI(go);
    }
};

/*######
## npc_prophecy_questcredit
######*/

#define QUEST_WHISPERS_RAVEN_GOD    10607


class npc_prophecy_questcredit : public CreatureScript
{
public:
    npc_prophecy_questcredit() : CreatureScript("npc_prophecy_questcredit")
    { }

    class npc_prophecy_questcreditAI : public ScriptedAI
    {
        public:
        npc_prophecy_questcreditAI(Creature *c) : ScriptedAI(c) {}
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void Reset()
        override {
            me->SetReactState(REACT_AGGRESSIVE);
        }
        
        void MoveInLineOfSight(Unit *pWho)
        override {
            if (me->GetDistance(pWho) >= 5.0f)
                return;
            if (pWho->GetTypeId() != TYPEID_PLAYER)
                return;
            
            Player *plr = reinterpret_cast<Player*>(pWho);
            if (plr->GetQuestStatus(QUEST_WHISPERS_RAVEN_GOD) == QUEST_STATUS_INCOMPLETE) {
                if (plr->HasAuraEffect(37642))
                    plr->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_prophecy_questcreditAI(creature);
    }
};


/*######
## npc_grishna_falconwing
######*/


class npc_grishna_falconwing : public CreatureScript
{
public:
    npc_grishna_falconwing() : CreatureScript("npc_grishna_falconwing")
    { }

    class npc_grishna_falconwingAI : public ScriptedAI
    {
        public:
        npc_grishna_falconwingAI(Creature *c) : ScriptedAI(c) {}
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void JustDied(Unit *pKiller)
        override {
            pKiller->AddAura(37642, pKiller);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_grishna_falconwingAI(creature);
    }
};


/*######
## go_ethereum_chamber
######*/

uint32 ethereumPrisoners[5] = { 22828, 22826, 22827, 20888, 22825 };

class EthereumChamber : public GameObjectScript
{
public:
    EthereumChamber() : GameObjectScript("go_ethereum_chamber")
    {}

    struct EthereumChamberAI : public GameObjectAI
    {
        EthereumChamberAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (Creature *pCreature = pPlayer->SummonCreature(ethereumPrisoners[rand() % 5], me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
                pCreature->AI()->AttackStart(pPlayer);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new EthereumChamberAI(go);
    }
};


/*######
## npc_kolphis_darkscale
######*/

class npc_kolphis_darkscale : public CreatureScript
{
public:
    npc_kolphis_darkscale() : CreatureScript("npc_kolphis_darkscale")
    { }

   class npc_kolphis_darkscaleAI : public ScriptedAI
   {
   public:
        npc_kolphis_darkscaleAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            pPlayer->GroupEventHappens(10722, me);
            
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kolphis_darkscaleAI(creature);
    }
};


/*######
## trigger_vimgol_circle_bunny
######*/

bool vimgol1, vimgol2, vimgol3, vimgol4, vimgol5;


class trigger_vimgol_circle_bunny : public CreatureScript
{
public:
    trigger_vimgol_circle_bunny() : CreatureScript("trigger_vimgol_circle_bunny")
    { }

    class trigger_vimgol_circle_bunnyAI : public ScriptedAI
    {
        public:
        trigger_vimgol_circle_bunnyAI(Creature *c) : ScriptedAI(c) 
        {
            SetCombatMovementAllowed(false);
        }
        
        uint32 checkTimer;
        bool hasResetVisual;
        
        void Reset()
        override {
            vimgol1 = false;
            vimgol2 = false;
            vimgol3 = false;
            vimgol4 = false;
            vimgol5 = false;
            
            checkTimer = 500;
            
            hasResetVisual = false;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void JustDied(Unit *pKiller)
        override {
            vimgol1 = false;
            vimgol2 = false;
            vimgol3 = false;
            vimgol4 = false;
            vimgol5 = false;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!hasResetVisual) {
                if (Creature *visualBunny = me->FindNearestCreature(23081, 2.0f, true))
                    visualBunny->GetMotionMaster()->MoveTargetedHome();
                    
                hasResetVisual = true;
            }
            if (checkTimer <= diff) {
                Creature *vimgol = me->FindNearestCreature(22911, 45.0f, true);
                if (vimgol) {    // No need to continue if vimgol's already there
                    checkTimer = 500;
                    return;
                }
                    
                Player* plr = nullptr;
                Trinity::AnyPlayerInObjectRangeCheck p_check(me, 0.5f);
                Trinity::PlayerSearcher<Trinity::AnyPlayerInObjectRangeCheck>  checker(me, plr, p_check);
                Cell::VisitWorldObjects(me, checker, 5.0f);
                
                if (plr) {
                    if (int32(me->GetPositionX()) == 3304)
                        vimgol1 = true;
                    else if (int32(me->GetPositionX()) == 3292)
                        vimgol2 = true;
                    else if (int32(me->GetPositionX()) == 3261)
                        vimgol3 = true;
                    else if (int32(me->GetPositionX()) == 3257)
                        vimgol4 = true;
                    else if (int32(me->GetPositionX()) == 3279)
                        vimgol5 = true;
                }
                else {
                    if (int32(me->GetPositionX()) == 3304)
                        vimgol1 = false;
                    else if (int32(me->GetPositionX()) == 3292)
                        vimgol2 = false;
                    else if (int32(me->GetPositionX()) == 3261)
                        vimgol3 = false;
                    else if (int32(me->GetPositionX()) == 3257)
                        vimgol4 = false;
                    else if (int32(me->GetPositionX()) == 3279)
                        vimgol5 = false;
                }
                
                // Check if 5 players are in circles
                if (vimgol1 && vimgol2 && vimgol3 && vimgol4 && vimgol5) {
                    Creature* _vimgol = me->FindNearestCreature(22911, 45.0f, true);
                    if (!_vimgol) {
                        _vimgol = me->SummonCreature(22911, 3279.770020, 4640.019531, 216.527039, 1.5874, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
    
                        std::list<Creature*> visualBunnies;
    
                        Trinity::AllCreaturesOfEntryInRange check(me, 23081, 50.0f);
                        Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, visualBunnies, check);
                        Cell::VisitGridObjects(me, searcher, 50.0f);
    
                        for (auto & visualBunnie : visualBunnies)
                            visualBunnie->CastSpell(visualBunnie, 39921, TRIGGERED_NONE);
                    }
                }
                
                checkTimer = 500;
            }
            else
                checkTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new trigger_vimgol_circle_bunnyAI(creature);
    }
};


/*######
## npc_vimgol
######*/

#define SPELL_SPAWN     7741
#define SPELL_GROWTH    40545       // FIXME: Not handled atm: it should interrupt itself if all players get back in circles during cast. Afaik, AI interface doesn't support such check for now.


class npc_vimgol : public CreatureScript
{
public:
    npc_vimgol() : CreatureScript("npc_vimgol")
    { }

    class npc_vimgolAI : public ScriptedAI
    {
        public:
        npc_vimgolAI(Creature *c) : ScriptedAI(c) {}
        
        void Reset()
        override {
            DoCast(me, SPELL_SPAWN);
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void JustDied(Unit *pKiller)
        override {
            pKiller->SummonGameObject(185562, pKiller->GetPosition(), G3D::Quat(), 0);
    
            std::list<Creature*> triggers;
    
            Trinity::AllCreaturesOfEntryInRange check(me, 23040, 50.0f);
            Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, triggers, check);
            Cell::VisitGridObjects(me, searcher, 50.0f);
    
            for (auto & trigger : triggers)
                trigger->KillSelf();
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vimgolAI(creature);
    }
};


/*######
## npc_skulloc
######*/

#define SPELL_SHADOWFORM_1      39943
#define SPELL_SHADOWFORM_2      39944
#define SPELL_SHADOWFORM_3      39946
#define SPELL_SHADOWFORM_4      39947

#define SPELL_VISUAL_INPROGRESS     39918       // At spawn
#define SPELL_VISUAL_BEAM           39920       // Blue/Black beam

#define GOB_SOUL                    185577


class npc_skulloc : public CreatureScript
{
public:
    npc_skulloc() : CreatureScript("npc_skulloc")
    { }

    class npc_skullocAI : public ScriptedAI
    {
        public:
        npc_skullocAI(Creature *c) : ScriptedAI(c) {}
        
        uint8 step;
        
        uint32 step5Timer;
        
        void Reset()
        override {
            step = 0;
            
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            
            step5Timer = 0;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void JustDied(Unit *pKiller)
        override {
            pKiller->SummonGameObject(GOB_SOUL, Position(pKiller->GetPositionX(), pKiller->GetPositionY(), pKiller->GetPositionZ()+3, 0), G3D::Quat(), 0);
        }
        
        void ChangePhase(uint8 phase)
        {
            switch (phase) {
            case 0:
                DoCast(me, SPELL_SHADOWFORM_1, true);
                break;
            case 1:
                me->RemoveAurasDueToSpell(SPELL_SHADOWFORM_1);
                DoCast(me, SPELL_SHADOWFORM_2, true);
                break;
            case 2:
                me->RemoveAurasDueToSpell(SPELL_SHADOWFORM_2);
                DoCast(me, SPELL_SHADOWFORM_3, true);
                break;
            case 3:
                me->RemoveAurasDueToSpell(SPELL_SHADOWFORM_3);
                DoCast(me, SPELL_SHADOWFORM_4, true);
                break;
            case 5:
            {
                // Remove all beams and cast one on the Soulgrinder
                std::list<Creature*> triggers;
    
                Trinity::AllCreaturesOfEntryInRange check(me, 23037, MAX_SEARCHER_DISTANCE);
                Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, triggers, check);
                Cell::VisitGridObjects(me, searcher, MAX_SEARCHER_DISTANCE);
    
                for (auto & trigger : triggers)
                    trigger->KillSelf();
                    
                if (Creature *soulgrinder = me->FindNearestCreature(23019, MAX_SEARCHER_DISTANCE, true)) {
                    DoCast(soulgrinder, SPELL_VISUAL_BEAM, true);
                    step5Timer = 10000;
                }
                break;
            }
            case 6:
                if (Creature *soulgrinder = me->FindNearestCreature(23019, 100.0f, true))
                    Unit::Kill(me, soulgrinder);
                me->RemoveAurasDueToSpell(SPELL_SHADOWFORM_4);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_AGGRESSIVE);
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (step5Timer) {
                if (step5Timer <= diff) {
                    ChangePhase(6);
                    
                    step5Timer = 0;
                }
                else
                    step5Timer -= diff;
            }
            
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;
                
            // Spells etc.
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_skullocAI(creature);
    }
};


/*######
## npc_soulgrinder
######*/

float ogresSpawns[6][4] = { { 3524.897705f, 5613.239258f, -4.257625f, 4.999918f },
                            { 3541.113037f, 5606.105469f, -3.300353f, 4.327529f },
                            { 3543.969238f, 5573.780273f, -2.774169f, 2.004281f },
                            { 3558.977295f, 5590.019531f, -4.172577f, 3.183468f },
                            { 3528.284424f, 5567.758789f, -1.199220f, 1.256619f },
                            { 3516.486328f, 5582.583984f, -3.198729f, 0.579210f }};

#define SPELL_VISUAL_BUNNY          39936       // On bunny?

#define NPC_SKULLOC                 22910
#define NPC_SUNDERED_GHOST          24039       // Seems to have no visible displayID, probably need to cast spell 3991 on them and FIXME: Change faction!


class npc_soulgrinder : public CreatureScript
{
public:
    npc_soulgrinder() : CreatureScript("npc_soulgrinder")
    { }

    class npc_soulgrinderAI : public ScriptedAI
    {
        public:
        npc_soulgrinderAI(Creature *c) : ScriptedAI(c) 
        {
            SetCombatMovementAllowed(false);
        }
        
        ObjectGuid skullocGUID;
        uint32 summonTimer;
        uint32 ogresKilled;
        
        uint8 step;
        
        void Reset()
        override {
            ogresKilled = 0;
            summonTimer = 8000;
            
            step = 0;
            
            DoCast(me, SPELL_VISUAL_INPROGRESS, true);
            if (Creature *skulloc = me->SummonCreature(NPC_SKULLOC, 3486.548340, 5554.811523, 7.519224, 3.755524, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000)) {
                skullocGUID = skulloc->GetGUID();
                ((npc_skulloc::npc_skullocAI*)skulloc->AI())->ChangePhase(step);
            }
        }
        
        void JustEngagedWith(Unit *pWho) override {}       // FIXME: Put summoner and his group in combat and stop it when entering phase 5 -> Maybe not needed if ogres have enough hp
        
        void IncrementOgresCounter()
        {
            ogresKilled++;
            if (ogresKilled%6 == 0) {    // Increment step (and add a beam) every 6 ogres
                step++;
                    
                AddBeam();
                if (Creature *skulloc = ObjectAccessor::GetCreature(*me, skullocGUID))
                    ((npc_skulloc::npc_skullocAI*)skulloc->AI())->ChangePhase(step);
            }
        }
        
        void AddBeam()
        {
            std::list<Creature*> triggers;
    
            Trinity::AllCreaturesOfEntryInRange check(me, 23037, MAX_SEARCHER_DISTANCE);
            Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, triggers, check);
            Cell::VisitGridObjects(me, searcher, MAX_SEARCHER_DISTANCE);
    
            for (auto & trigger : triggers) {
                trigger->GetMotionMaster()->MoveTargetedHome();
                if (step == 1 && int32(trigger->GetPositionX()) == 3493)
                    trigger->CastSpell(me, SPELL_VISUAL_BEAM, TRIGGERED_NONE);
                else if (step == 2 && int32(trigger->GetPositionX()) == 3465)
                    trigger->CastSpell(me, SPELL_VISUAL_BEAM, TRIGGERED_NONE);
                else if (step == 3 && int32(trigger->GetPositionX()) == 3515)
                    trigger->CastSpell(me, SPELL_VISUAL_BEAM, TRIGGERED_NONE);
                else if (step == 4 && int32(trigger->GetPositionX()) == 3472)
                    trigger->CastSpell(me, SPELL_VISUAL_BEAM, TRIGGERED_NONE);
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (step >= 5)
                return;
    
            if (summonTimer <= diff) {
                uint8 randomPoint = rand()%6;
                me->SummonCreature(NPC_SUNDERED_GHOST, ogresSpawns[randomPoint][0], ogresSpawns[randomPoint][1], ogresSpawns[randomPoint][2], ogresSpawns[randomPoint][3], TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                
                summonTimer = 8000;
            }
            else
                summonTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_soulgrinderAI(creature);
    }
};


/*######
## npc_sundered_ghost
######*/

#define SPELL_TRANSFORM_GHOST       39916
#define SPELL_CRIPPLE               11443
#define SPELL_SHADOW_BOLT           20816


class npc_sundered_ghost : public CreatureScript
{
public:
    npc_sundered_ghost() : CreatureScript("npc_sundered_ghost")
    { }

    class npc_sundered_ghostAI : public ScriptedAI
    {
        public:
        npc_sundered_ghostAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 crippleTimer;
        uint32 shadowBoltTimer;
        
        void Reset()
        override {
            me->SetFaction(FACTION_MONSTER);
            DoCast(me, SPELL_TRANSFORM_GHOST);
            
            crippleTimer = 4000;
            shadowBoltTimer = 3000;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void JustDied(Unit *pKiller)
        override {
            if (Creature *pSoulgrinder = me->FindNearestCreature(23019, 40.0f, true))
                ((npc_soulgrinder::npc_soulgrinderAI*)pSoulgrinder->AI())->IncrementOgresCounter();
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (crippleTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_CRIPPLE);
                
                crippleTimer = 20000+rand()%4000;
            }
            else
                crippleTimer -= diff;
                
            if (shadowBoltTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_SHADOW_BOLT);
                
                shadowBoltTimer = 5000+rand()%3000;
            }
            else
                shadowBoltTimer -= diff;
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sundered_ghostAI(creature);
    }
};


/*######
## go_apexis_relic
######*/

#define GOSSIP_START_GAME       "[PH] Démarrer le jeu !"
#define ITEM_APEXIS_SHARD       32569
#define GO_RELIC_DECHARGER      185894
#define NPC_SIMON_BUNNY         22923
//#define NPC_SIMON_SUMMONTARGET  23382     // Not used


class ApexisRelix : public GameObjectScript
{
public:
    ApexisRelix() : GameObjectScript("go_apexis_relic")
    {}

    struct ApexisRelixAI : public GameObjectAI
    {
        ApexisRelixAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY, 5.0f, true))        // Event is running, don't launch it twice
                return false;

            if (pPlayer->HasItemCount(ITEM_APEXIS_SHARD, 1, false)) {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_GAME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(31000, me->GetGUID());

                return true;
            }

            return false;
        }

        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF) {
                // Summon trigger that will player the event
                if (GameObject *gDecharger = player->FindNearestGameObject(GO_RELIC_DECHARGER, 5.0f))
                    player->SummonCreature(NPC_SIMON_BUNNY, gDecharger->GetPositionX(), gDecharger->GetPositionY(), gDecharger->GetPositionZ() + 5, player->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
            }

            player->CLOSE_GOSSIP_MENU();

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ApexisRelixAI(go);
    }
};

/*######
## npc_simon_bunny
######*/

enum eSimonSpells
{
    //SPELL_START_SOLO        = 41145,  // Not used
    //SPELL_START_GROUP       = 41146,  // Not used
    SPELL_START_VISUAL      = 40387,
    //SPELL_START_VISUAL_HIGH = 39993,  // Not used
    
    SPELL_WHITEAURA_BLUE    = 40281,
    SPELL_WHITEAURA_GREEN   = 40287,
    SPELL_WHITEAURA_RED     = 40288,
    SPELL_WHITEAURA_YELLOW  = 40289,
    
    SPELL_BEAM_BLUE         = 40244,
    SPELL_BEAM_GREEN        = 40245,
    SPELL_BEAM_RED          = 40246,
    SPELL_BEAM_YELLOW       = 40247,
    
    SPELL_LEVELSTART        = 40436,
    //SPELL_SOUND             = 41398,  // Not used
    
    SPELL_BAD_PRESS         = 41241,
    SPELL_GAME_FAILED       = 40437,
    
    SPELL_INTROSPECTION     = 40165,
    
    SPELL_APEXIS_VIBRATIONS = 40310
};

enum eSimonSteps
{
    STEP_BEGIN              = 0,
    STEP_WHITEAURA          = 1,
    STEP_SHOWSEQUENCE       = 2,
    STEP_REPRODSEQUENCE     = 3
};

enum eSimonBeams
{
    BEAM_BLUE               = 0,
    BEAM_GREEN              = 1,
    BEAM_RED                = 2,
    BEAM_YELLOW             = 3
};

enum eSimonSounds
{
    SOUND_BLUE              = 11588,
    SOUND_GREEN             = 11589,
    SOUND_RED               = 11590,
    SOUND_YELLOW            = 11591
};


class npc_simon_bunny : public CreatureScript
{
public:
    npc_simon_bunny() : CreatureScript("npc_simon_bunny")
    { }

    class npc_simon_bunnyAI : public ScriptedAI
    {
        public:
        npc_simon_bunnyAI(Creature *c) : ScriptedAI(c) {}
        
        ObjectGuid playerGUID;
        
        uint8 step;
        uint8 level;
        uint8 levelCounter;
        
        uint32 stepTimer;
        uint32 inactiveTimer;
        
        std::list<uint8> beamList;
        
        void Reset()
        override {
            me->GetMotionMaster()->MoveTargetedHome();
            
            if (Unit *summoner = ((TempSummon*)me)->GetSummoner()) {
                summoner->ToPlayer()->DestroyItemCount(ITEM_APEXIS_SHARD, 1, true);
                playerGUID = summoner->GetGUID();
            }
                
            if (!playerGUID) {
                TC_LOG_ERROR("scripts","Simon Game: no player found to start event, aborting.");
                me->DisappearAndDie();
            }
            
            step = STEP_BEGIN;
            stepTimer = 0;
            level = 0;
            inactiveTimer = 0;
            
            beamList.clear();
        }
        
        // This is hacky. I need to move npc to get him back in the air, or visual effect is fucked up.
        void JustReachedHome()
        override {
            stepTimer = 1;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        uint32 SelectRandomBeam()
        {
            Player *plr = ObjectAccessor::FindPlayer(playerGUID);
            if (!plr)
                return 0;
    
            switch (rand()%4) {
            case BEAM_BLUE:
                beamList.push_back(BEAM_BLUE);
                plr->PlaySound(GetSoundForButton(BEAM_BLUE), false);
                return SPELL_BEAM_BLUE;
            case BEAM_GREEN:
                beamList.push_back(BEAM_GREEN);
                plr->PlaySound(GetSoundForButton(BEAM_GREEN), false);
                return SPELL_BEAM_GREEN;
            case BEAM_RED:
                beamList.push_back(BEAM_RED);
                plr->PlaySound(GetSoundForButton(BEAM_RED), false);
                return SPELL_BEAM_RED;
            case BEAM_YELLOW:
                beamList.push_back(BEAM_YELLOW);
                plr->PlaySound(GetSoundForButton(BEAM_YELLOW), false);
                return SPELL_BEAM_YELLOW;
            }
            return 0;
        }
        
        uint32 GetSpellForBeam(uint8 beam)
        {
            switch (beam) {
            case BEAM_BLUE:
                return SPELL_BEAM_BLUE;
            case BEAM_GREEN:
                return SPELL_BEAM_GREEN;
            case BEAM_RED:
                return SPELL_BEAM_RED;
            case BEAM_YELLOW:
                return SPELL_BEAM_YELLOW;
            default:
                return 0;
            }
        }
    
        uint32 GetSoundForButton(uint8 button)
        {
            switch (button) {
            case BEAM_BLUE:
                return SOUND_BLUE;
            case BEAM_GREEN:
                return SOUND_GREEN;
            case BEAM_RED:
                return SOUND_RED;
            case BEAM_YELLOW:
                return SOUND_YELLOW;
            default:
                return 0;
            }
        }
    
        void PlayerProposal(uint8 prop)
        {
            if (step != STEP_REPRODSEQUENCE)
                return;
    
            uint8 next = beamList.front();
            if (next == prop) {     // Good
                DoCast(me, GetSpellForBeam(next), true);
                if (Player *plr = ObjectAccessor::FindPlayer(playerGUID))
                    plr->PlaySound(GetSoundForButton(next), false);
                
                beamList.pop_front();
                if (beamList.empty()) {     // All beams processed. Level up!
                    step = STEP_BEGIN;
                    stepTimer = 500;
                }
            }
            else {                  // Wrong, hurt player and restart level
                if (Player *plr = ObjectAccessor::FindPlayer(playerGUID)) {
                    plr->CastSpell(plr, SPELL_GAME_FAILED, TRIGGERED_FULL_MASK);
                    plr->CastSpell(plr, SPELL_BAD_PRESS, TRIGGERED_FULL_MASK);
                }
                
                beamList.clear();
                level--;
                
                step = STEP_BEGIN;
                stepTimer = 500;
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            Player *summoner = ObjectAccessor::FindPlayer(playerGUID);
            if (!summoner || !summoner->IsInWorld()) {
                me->DisappearAndDie();
                return;
            }
            
            if (level > 8) {        // Complete quest and stop event
                //DoCast(summoner, SPELL_APEXIS_VIBRATIONS, true);
                summoner->CastSpell(summoner, SPELL_APEXIS_VIBRATIONS, TRIGGERED_NONE);
                if (summoner->ToPlayer()->GetQuestStatus(11058) == QUEST_STATUS_INCOMPLETE) {
                    summoner->ToPlayer()->CompleteQuest(11058);
                    summoner->ToPlayer()->GroupEventHappens(11058, me);
                }
                if (summoner->ToPlayer()->GetQuestStatus(11080) == QUEST_STATUS_INCOMPLETE) {
                    summoner->ToPlayer()->CompleteQuest(11080);
                    summoner->ToPlayer()->GroupEventHappens(11080, me);
                }
                me->DisappearAndDie();
                return;
            }
            
            if (stepTimer) {
                if (stepTimer <= diff) {
                    switch (step) {
                    case STEP_BEGIN:
                        DoCast(me, SPELL_START_VISUAL, true);
                        step = STEP_WHITEAURA;
                        stepTimer = 1800;
                        break;
                    case STEP_WHITEAURA:
                        DoCast(me, SPELL_WHITEAURA_BLUE, true);
                        DoCast(me, SPELL_WHITEAURA_GREEN, true);
                        DoCast(me, SPELL_WHITEAURA_RED, true);
                        DoCast(me, SPELL_WHITEAURA_YELLOW, true);
                        
                        beamList.clear();
                        step = STEP_SHOWSEQUENCE;
                        stepTimer = 5000;
                        level++;
                        levelCounter = 0;
                        break;
                    case STEP_SHOWSEQUENCE:
                        if (levelCounter < level) {
                            DoCast(me, SelectRandomBeam(), true);
                            levelCounter++;
                            stepTimer = 1100;
                            break;
                        }
                        step = STEP_REPRODSEQUENCE;
                        stepTimer = 500;
                        break;
                    case STEP_REPRODSEQUENCE:
                        DoCast(me, SPELL_LEVELSTART, true);
                        stepTimer = 0;      // Stop event, we are waiting for player
                        inactiveTimer = 0;
                        break;
                    default:
                        TC_LOG_ERROR("scripts","Phase not handled for now.");
                        break;
                    }
                }
                else stepTimer -= diff;
            }
            else
                inactiveTimer += diff;
                
            if (inactiveTimer >= 300000)    // 5 min
                me->DisappearAndDie();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_simon_bunnyAI(creature);
    }
};


/*######
## go_blue_cluster
######*/

class BlueCluster : public GameObjectScript
{
public:
    BlueCluster() : GameObjectScript("go_blue_cluster")
    {}

    struct BlueClusterAI : public GameObjectAI
    {
        BlueClusterAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY, 5.0f, true);
            if (!bunny)
                return false;

            pPlayer->CastSpell(pPlayer, SPELL_INTROSPECTION, TRIGGERED_FULL_MASK);
            ((npc_simon_bunny::npc_simon_bunnyAI*)bunny->AI())->PlayerProposal(BEAM_BLUE);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new BlueClusterAI(go);
    }
};

class RedCluster : public GameObjectScript
{
public:
    RedCluster() : GameObjectScript("go_red_cluster")
    {}

    struct RedClusterAI : public GameObjectAI
    {
        RedClusterAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY, 5.0f, true);
            if (!bunny)
                return false;

            pPlayer->CastSpell(pPlayer, SPELL_INTROSPECTION, TRIGGERED_FULL_MASK);
            ((npc_simon_bunny::npc_simon_bunnyAI*)bunny->AI())->PlayerProposal(BEAM_RED);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new RedClusterAI(go);
    }
};

class GreenCluster : public GameObjectScript
{
public:
    GreenCluster() : GameObjectScript("go_green_cluster")
    {}

    struct GreenClusterAI : public GameObjectAI
    {
        GreenClusterAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY, 5.0f, true);
            if (!bunny)
                return false;

            pPlayer->CastSpell(pPlayer, SPELL_INTROSPECTION, TRIGGERED_FULL_MASK);
            ((npc_simon_bunny::npc_simon_bunnyAI*)bunny->AI())->PlayerProposal(BEAM_GREEN);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new GreenClusterAI(go);
    }
};

class YellowCluster : public GameObjectScript
{
public:
    YellowCluster() : GameObjectScript("go_yellow_cluster")
    {}

    struct YellowClusterAI : public GameObjectAI
    {
        YellowClusterAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY, 5.0f, true);
            if (!bunny)
                return false;

            pPlayer->CastSpell(pPlayer, SPELL_INTROSPECTION, TRIGGERED_FULL_MASK);
            ((npc_simon_bunny::npc_simon_bunnyAI*)bunny->AI())->PlayerProposal(BEAM_YELLOW);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new YellowClusterAI(go);
    }
};

/*######
## go_apexis_monument
######*/

//#define GOSSIP_START_GAME       "[PH] Démarrer le jeu !"
#define ITEM_APEXIS_SHARD       32569
#define GO_APEXIS_DECHARGER     185945
#define NPC_SIMON_BUNNY_LARGE   23378

class ApexisMonument : public GameObjectScript
{
public:
    ApexisMonument() : GameObjectScript("go_apexis_monument")
    {}

    struct ApexisMonumentAI : public GameObjectAI
    {
        ApexisMonumentAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            //if (pPlayer->GetQuestStatus(11059) != QUEST_STATUS_INCOMPLETE)                      // Only with quest
            //return false;

            if (Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY_LARGE, 5.0f, true))        // Event is running, don't launch it twice
                return false;

            if (pPlayer->HasItemCount(ITEM_APEXIS_SHARD, 35, false)) {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_GAME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(31000, me->GetGUID());

                return true;
            }

            return false;
        }

        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF) {
                // Summon trigger that will handle the event
                if (GameObject *gDecharger = player->FindNearestGameObject(GO_APEXIS_DECHARGER, 5.0f))
                    player->SummonCreature(NPC_SIMON_BUNNY_LARGE, gDecharger->GetPositionX(), gDecharger->GetPositionY(), gDecharger->GetPositionZ() + 8, player->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ApexisMonumentAI(go);
    }
};

/*######
## npc_simon_bunny_large
######*/

/*enum eSimonSpells
{
    //SPELL_START_SOLO        = 41145,  // Not used
    //SPELL_START_GROUP       = 41146,  // Not used
    SPELL_START_VISUAL      = 40387,
    //SPELL_START_VISUAL_HIGH = 39993,  // Not used
    
    SPELL_WHITEAURA_BLUE    = 40281,
    SPELL_WHITEAURA_GREEN   = 40287,
    SPELL_WHITEAURA_RED     = 40288,
    SPELL_WHITEAURA_YELLOW  = 40289,
    
    SPELL_BEAM_BLUE         = 40244,
    SPELL_BEAM_GREEN        = 40245,
    SPELL_BEAM_RED          = 40246,
    SPELL_BEAM_YELLOW       = 40247,
    
    SPELL_LEVELSTART        = 40436,
    //SPELL_SOUND             = 41398,  // Not used
    
    SPELL_BAD_PRESS         = 41241,
    SPELL_GAME_FAILED       = 40437,
    
    SPELL_INTROSPECTION     = 40165,
    
    SPELL_APEXIS_VIBRATIONS = 40310
};*/

/*enum eSimonSteps
{
    STEP_BEGIN              = 0,
    STEP_WHITEAURA          = 1,
    STEP_SHOWSEQUENCE       = 2,
    STEP_REPRODSEQUENCE     = 3
};

enum eSimonBeams
{
    BEAM_BLUE               = 0,
    BEAM_GREEN              = 1,
    BEAM_RED                = 2,
    BEAM_YELLOW             = 3
};

enum eSimonSounds
{
    SOUND_BLUE              = 11588,
    SOUND_GREEN             = 11589,
    SOUND_RED               = 11590,
    SOUND_YELLOW            = 11591
};*/


class npc_simon_bunny_large : public CreatureScript
{
public:
    npc_simon_bunny_large() : CreatureScript("npc_simon_bunny_large")
    { }

    class npc_simon_bunny_largeAI : public ScriptedAI
    {
        public:
        npc_simon_bunny_largeAI(Creature *c) : ScriptedAI(c) {}
        
        ObjectGuid playerGUID;
        
        uint8 step;
        uint8 level;
        uint8 levelCounter;
        
        uint32 stepTimer;
        uint32 inactiveTimer;
        
        std::list<uint8> beamList;
        
        void Reset()
        override {
            me->GetMotionMaster()->MoveTargetedHome();
            
            if (Unit *summoner = ((TempSummon*)me)->GetSummoner()) {
                summoner->ToPlayer()->DestroyItemCount(ITEM_APEXIS_SHARD, 35, true);
                playerGUID = summoner->GetGUID();
            }
                
            if (!playerGUID) {
                TC_LOG_ERROR("scripts","Simon Game: no player found to start event, aborting.");
                me->DisappearAndDie();
            }
            
            step = STEP_BEGIN;
            stepTimer = 0;
            level = 0;
            inactiveTimer = 0;
            
            beamList.clear();
        }
        
        // This is hacky. I need to move npc to get him back in the air, or visual effect is fucked up.
        void JustReachedHome()
        override {
            stepTimer = 1;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        uint32 SelectRandomBeam()
        {
            Player *plr = ObjectAccessor::FindPlayer(playerGUID);
            if (!plr)
                return 0;
    
            switch (rand()%4) {
            case BEAM_BLUE:
                beamList.push_back(BEAM_BLUE);
                plr->PlaySound(GetSoundForButton(BEAM_BLUE), false);
                return SPELL_BEAM_BLUE;
            case BEAM_GREEN:
                beamList.push_back(BEAM_GREEN);
                plr->PlaySound(GetSoundForButton(BEAM_GREEN), false);
                return SPELL_BEAM_GREEN;
            case BEAM_RED:
                beamList.push_back(BEAM_RED);
                plr->PlaySound(GetSoundForButton(BEAM_RED), false);
                return SPELL_BEAM_RED;
            case BEAM_YELLOW:
                beamList.push_back(BEAM_YELLOW);
                plr->PlaySound(GetSoundForButton(BEAM_YELLOW), false);
                return SPELL_BEAM_YELLOW;
            }
            return 0;
        }
        
        uint32 GetSpellForBeam(uint8 beam)
        {
            switch (beam) {
            case BEAM_BLUE:
                return SPELL_BEAM_BLUE;
            case BEAM_GREEN:
                return SPELL_BEAM_GREEN;
            case BEAM_RED:
                return SPELL_BEAM_RED;
            case BEAM_YELLOW:
                return SPELL_BEAM_YELLOW;
            default:
                return 0;
            }
        }
    
        uint32 GetSoundForButton(uint8 button)
        {
            switch (button) {
            case BEAM_BLUE:
                return SOUND_BLUE;
            case BEAM_GREEN:
                return SOUND_GREEN;
            case BEAM_RED:
                return SOUND_RED;
            case BEAM_YELLOW:
                return SOUND_YELLOW;
            default:
                return 0;
            }
        }
    
        void PlayerProposal(uint8 prop)
        {
            if (step != STEP_REPRODSEQUENCE)
                return;
    
            uint8 next = beamList.front();
            if (next == prop) {     // Good
                DoCast(me, GetSpellForBeam(next), true);
                if (Player *plr = ObjectAccessor::FindPlayer(playerGUID))
                    plr->PlaySound(GetSoundForButton(next), false);
                
                beamList.pop_front();
                if (beamList.empty()) {     // All beams processed. Level up!
                    step = STEP_BEGIN;
                    stepTimer = 500;
                }
            }
            else {                  // Wrong, hurt player and restart level
                if (Player *plr = ObjectAccessor::FindPlayer(playerGUID)) {
                    plr->CastSpell(plr, SPELL_GAME_FAILED, TRIGGERED_FULL_MASK);
                    plr->CastSpell(plr, SPELL_BAD_PRESS, TRIGGERED_FULL_MASK);
                }
                
                beamList.clear();
                level--;
                
                step = STEP_BEGIN;
                stepTimer = 500;
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            Player *summoner = ObjectAccessor::FindPlayer(playerGUID);
            if (!summoner || !summoner->IsInWorld()) {
                me->DisappearAndDie();
                return;
            }
            
            if (level > 6) {        // Complete quest and stop event
                //DoCast(summoner, SPELL_APEXIS_VIBRATIONS, true);
                //summoner->ToPlayer()->GroupEventHappens(11059, me);
                me->SummonCreature(22275, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()-8, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                me->DisappearAndDie();
                return;
            }
            
            if (stepTimer) {
                if (stepTimer <= diff) {
                    switch (step) {
                    case STEP_BEGIN:
                        DoCast(me, SPELL_START_VISUAL, true);
                        step = STEP_WHITEAURA;
                        stepTimer = 1800;
                        break;
                    case STEP_WHITEAURA:
                        DoCast(me, SPELL_WHITEAURA_BLUE, true);
                        DoCast(me, SPELL_WHITEAURA_GREEN, true);
                        DoCast(me, SPELL_WHITEAURA_RED, true);
                        DoCast(me, SPELL_WHITEAURA_YELLOW, true);
                        
                        beamList.clear();
                        step = STEP_SHOWSEQUENCE;
                        stepTimer = 5000;
                        level++;
                        levelCounter = 0;
                        break;
                    case STEP_SHOWSEQUENCE:
                        if (levelCounter < level) {
                            DoCast(me, SelectRandomBeam(), true);
                            levelCounter++;
                            stepTimer = 1100;
                            break;
                        }
                        step = STEP_REPRODSEQUENCE;
                        stepTimer = 500;
                        break;
                    case STEP_REPRODSEQUENCE:
                        DoCast(me, SPELL_LEVELSTART, true);
                        stepTimer = 0;      // Stop event, we are waiting for player
                        inactiveTimer = 0;
                        break;
                    default:
                        TC_LOG_ERROR("scripts","Phase not handled for now.");
                        break;
                    }
                }
                else stepTimer -= diff;
            }
            else
                inactiveTimer += diff;
                
            if (inactiveTimer >= 300000)        // 5 min
                me->DisappearAndDie();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_simon_bunny_largeAI(creature);
    }
};


class BlueClusterLarge : public GameObjectScript
{
public:
    BlueClusterLarge() : GameObjectScript("go_blue_cluster_large")
    {}

    struct BlueClusterLargeAI : public GameObjectAI
    {
        BlueClusterLargeAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY_LARGE, 20.0f, true);
            if (!bunny)
                return false;

            pPlayer->CastSpell(pPlayer, SPELL_INTROSPECTION, TRIGGERED_FULL_MASK);
            ((npc_simon_bunny_large::npc_simon_bunny_largeAI*)bunny->AI())->PlayerProposal(BEAM_BLUE);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new BlueClusterLargeAI(go);
    }
};

class GreenClusterLarge : public GameObjectScript
{
public:
    GreenClusterLarge() : GameObjectScript("go_green_cluster_large")
    {}

    struct GreenClusterLargeAI : public GameObjectAI
    {
        GreenClusterLargeAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY_LARGE, 20.0f, true);
            if (!bunny)
                return false;

            pPlayer->CastSpell(pPlayer, SPELL_INTROSPECTION, TRIGGERED_FULL_MASK);
            ((npc_simon_bunny_large::npc_simon_bunny_largeAI*)bunny->AI())->PlayerProposal(BEAM_GREEN);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new GreenClusterLargeAI(go);
    }
};

class RedClusterLarge : public GameObjectScript
{
public:
    RedClusterLarge() : GameObjectScript("go_red_cluster_large")
    {}

    struct RedClusterLargeAI : public GameObjectAI
    {
        RedClusterLargeAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY_LARGE, 20.0f, true);
            if (!bunny)
                return false;

            pPlayer->CastSpell(pPlayer, SPELL_INTROSPECTION, TRIGGERED_FULL_MASK);
            ((npc_simon_bunny_large::npc_simon_bunny_largeAI*)bunny->AI())->PlayerProposal(BEAM_RED);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new RedClusterLargeAI(go);
    }
};

class YellowClusterLarge : public GameObjectScript
{
public:
    YellowClusterLarge() : GameObjectScript("go_yellow_cluster_large")
    {}

    struct YellowClusterLargeAI : public GameObjectAI
    {
        YellowClusterLargeAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            Creature *bunny = me->FindNearestCreature(NPC_SIMON_BUNNY_LARGE, 20.0f, true);
            if (!bunny)
                return false;

            pPlayer->CastSpell(pPlayer, SPELL_INTROSPECTION, TRIGGERED_FULL_MASK);
            ((npc_simon_bunny_large::npc_simon_bunny_largeAI*)bunny->AI())->PlayerProposal(BEAM_YELLOW);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new YellowClusterLargeAI(go);
    }
};

class FelCrystalPrism : public GameObjectScript
{
public:
    FelCrystalPrism() : GameObjectScript("go_fel_crystal_prism")
    {}

    struct FelCrystalPrismAI : public GameObjectAI
    {
        FelCrystalPrismAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (!pPlayer->HasItemCount(ITEM_APEXIS_SHARD, 35, false))
                return false;

            pPlayer->DestroyItemCount(ITEM_APEXIS_SHARD, 35, true);

            switch (rand() % 4) {
            case 0:
                me->SummonCreature(23353, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                break;
            case 1:
                me->SummonCreature(23354, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                break;
            case 2:
                me->SummonCreature(22281, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                break;
            case 3:
                me->SummonCreature(23355, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                break;
            }

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new FelCrystalPrismAI(go);
    }
};

/*######
## npc_braxxus
######*/

#define SPELL_DOUBLE_BREATH         41437
#define SPELL_MANGLE                41439
#define SPELL_PANIC                 41436


class npc_braxxus : public CreatureScript
{
public:
    npc_braxxus() : CreatureScript("npc_braxxus")
    { }

    class npc_braxxusAI : public ScriptedAI
    {
        public:
        npc_braxxusAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 doubleBreathTimer;
        uint32 mangleTimer;
        uint32 panicTimer;
        
        void Reset()
        override {
            doubleBreathTimer = 2000;
            mangleTimer = 5000;
            panicTimer = 15000;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (doubleBreathTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_DOUBLE_BREATH);
                doubleBreathTimer = 10000+rand()%3000;
            }
            else
                doubleBreathTimer -= diff;
                
            if (mangleTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_MANGLE);
                mangleTimer = 10000+rand()%4000;
            }
            else
                mangleTimer -= diff;
                
            if (panicTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_PANIC);
                panicTimer = 15000+rand()%3000;
            }
            else
                panicTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_braxxusAI(creature);
    }
};


/*######
## npc_moarg_incinerator
######*/

#define SPELL_ACID_GEYSER       44431
#define SPELL_MIGHTY_CHARGE     36606
#define SPELL_SUNDERING_CLEAVE  25174


class npc_moarg_incinerator : public CreatureScript
{
public:
    npc_moarg_incinerator() : CreatureScript("npc_moarg_incinerator")
    { }

    class npc_moarg_incineratorAI : public ScriptedAI
    {
        public:
        npc_moarg_incineratorAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 acidGeyserTimer;
        uint32 mightyChargeTimer;
        uint32 sunderingCleaveTimer;
        
        void Reset()
        override {
            acidGeyserTimer = 2000;
            sunderingCleaveTimer = 5000;
        }
        
        void JustEngagedWith(Unit *pWho)
        override {
            DoCast(pWho, SPELL_MIGHTY_CHARGE);
            mightyChargeTimer = 10000;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (acidGeyserTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_ACID_GEYSER);
                acidGeyserTimer = 10000+rand()%3000;
            }
            else
                acidGeyserTimer -= diff;
                
            if (sunderingCleaveTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_SUNDERING_CLEAVE);
                sunderingCleaveTimer = 5000+rand()%2000;
            }
            else
                sunderingCleaveTimer -= diff;
                
            if (mightyChargeTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0, true, true), SPELL_MIGHTY_CHARGE);
                mightyChargeTimer = 10000+rand()%3000;
            }
            else
                mightyChargeTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_moarg_incineratorAI(creature);
    }
};


/*######
## npc_galvanoth
######*/

#define SPELL_FEL_FLAMESTRIKE       39139
#define SPELL_MORTAL_STRIKE         15708
#define SPELL_WAR_STOMP             38750


class npc_galvanoth : public CreatureScript
{
public:
    npc_galvanoth() : CreatureScript("npc_galvanoth")
    { }

    class npc_galvanothAI : public ScriptedAI
    {
        public:
        npc_galvanothAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 felFlamestrikeTimer;
        uint32 mortalStrikeTimer;
        uint32 warStompTimer;
        
        void Reset()
        override {
            felFlamestrikeTimer = 2000;
            mortalStrikeTimer = 5000;
            warStompTimer = 8000;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (felFlamestrikeTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FEL_FLAMESTRIKE);
                felFlamestrikeTimer = 10000+rand()%3000;
            }
            else
                felFlamestrikeTimer -= diff;
                
            if (mortalStrikeTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_MORTAL_STRIKE);
                mortalStrikeTimer = 6000+rand()%2000;
            }
            else
                mortalStrikeTimer -= diff;
                
            if (warStompTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_WAR_STOMP);
                warStompTimer = 10000+rand()%3000;
            }
            else
                warStompTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_galvanothAI(creature);
    }
};


/*######
## npc_zarcsin
######*/

#define SPELL_FEL_FLAMES        41444
#define SPELL_ENRAGE            41447


class npc_zarcsin : public CreatureScript
{
public:
    npc_zarcsin() : CreatureScript("npc_zarcsin")
    { }

    class npc_zarcsinAI : public ScriptedAI
    {
        public:
        npc_zarcsinAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 felFlamesTimer;
        
        void Reset()
        override {
            felFlamesTimer = 2000;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (felFlamesTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FEL_FLAMES);
                felFlamesTimer = 10000+rand()%3000;
            }
            else
                felFlamesTimer -= diff;
                
            if (me->IsBelowHPPercent(50) && !me->HasAuraEffect(SPELL_ENRAGE))
                DoCast(me, SPELL_ENRAGE);
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_zarcsinAI(creature);
    }
};


/*######
## npc_aether_ray
######*/

#define SPELL_TAIL_SWIPE        35333


class npc_aether_ray : public CreatureScript
{
public:
    npc_aether_ray() : CreatureScript("npc_aether_ray")
    { }

    class npc_aether_rayAI : public ScriptedAI
    {
        public:
        npc_aether_rayAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 tailSwipeTimer;
        
        bool hasEmoted;
        
        void Reset()
        override {
            me->GetMotionMaster()->MoveTargetedHome();
            
            tailSwipeTimer = 2000;
            hasEmoted = false;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void SpellHit(Unit *pCaster, SpellInfo const *pSpell)
        override {
            if (pSpell->Id == 40856 && me->IsBelowHPPercent(30)) {
                me->DisappearAndDie();
                pCaster->CastSpell(pCaster, 40917, TRIGGERED_NONE);
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (me->IsBelowHPPercent(30) && !hasEmoted) {
               me->TextEmote("is ready to be captured.", nullptr);
                hasEmoted = true;
            }
                
            if (tailSwipeTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_TAIL_SWIPE);
                tailSwipeTimer = 10000+rand()%5000;
            }
            else
                tailSwipeTimer -= diff;
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_aether_rayAI(creature);
    }
};


/*######
## npc_wrangled_aether_ray
######*/


class npc_wrangled_aether_ray : public CreatureScript
{
public:
    npc_wrangled_aether_ray() : CreatureScript("npc_wrangled_aether_ray")
    { }

    class npc_wrangled_aether_rayAI : public ScriptedAI
    {
        public:
        npc_wrangled_aether_rayAI(Creature *c) : ScriptedAI(c) {}
        
        void Reset()
        override {
            if (Unit *summoner = ((TempSummon*)me)->GetSummoner()) {
                me->GetMotionMaster()->MoveFollow(summoner, PET_FOLLOW_DIST*2, M_PI);
                DoCast(summoner, 40926, true);
            }
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void MoveInLineOfSight(Unit *pWho)
        override {
            if (pWho->ToCreature() && pWho->ToCreature()->GetEntry() == 23335 && pWho->IsWithinDistInMap(me, 10.0f)) {
                if (Unit *summoner = ((TempSummon*)me)->GetSummoner()) {
                    summoner->ToPlayer()->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                    me->DisappearAndDie();
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wrangled_aether_rayAI(creature);
    }
};


class DrakeEgg : public GameObjectScript
{
public:
    DrakeEgg() : GameObjectScript("go_drake_egg")
    {}

    struct DrakeEggAI : public GameObjectAI
    {
        DrakeEggAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            //if (pPlayer->GetQuestStatus(11078) != QUEST_STATUS_INCOMPLETE)
            //return false;

            if (!pPlayer->HasItemCount(ITEM_APEXIS_SHARD, 35, false))
                return false;

            pPlayer->DestroyItemCount(ITEM_APEXIS_SHARD, 35, true);

            uint32 bossEntry;
            switch (me->GetEntry()) {
            case 185936:        // Rivendark
                bossEntry = 23061;
                break;
            case 185932:        // Obsidia
                bossEntry = 23282;
                break;
            case 185938:        // Insidion
                bossEntry = 23281;
                break;
            case 185937:        // Furywing
                bossEntry = 23261;
                break;
            default:
                bossEntry = 0;
                break;
            }

            if (Creature *boss = pPlayer->FindNearestCreature(bossEntry, 150.0f, true))
                boss->AI()->AttackStart(pPlayer);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new DrakeEggAI(go);
    }
};

/*######
## npc_rivendark
######*/

#define SPELL_CORRUPTION        41988
#define SPELL_TAIL_SWEEP        15847
#define SPELL_BELLOWING_ROAR    36922
#define SPELL_CLEAVE            40505
#define SPELL_FIERY_BREATH      40032
#define SPELL_FLAME_BREATH      9573


class npc_rivendark : public CreatureScript
{
public:
    npc_rivendark() : CreatureScript("npc_rivendark")
    { }

    class npc_rivendarkAI : public ScriptedAI
    {
        public:
        npc_rivendarkAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 corruptionTimer;
        uint32 tailSweepTimer;
        uint32 bellowingRoarTimer;
        uint32 cleaveTimer;
        uint32 fieryBreathTimer;
        uint32 flameBreathTimer;
        
        void Reset()
        override {
            corruptionTimer = 2000;
            tailSweepTimer = 10000;
            bellowingRoarTimer = 15000;
            cleaveTimer = 5000;
            fieryBreathTimer = 8000;
            flameBreathTimer = 12000;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff)
        override {
            if (!me->IsInCombat())
                me->SetDisableGravity(true);
            else if (me->IsInCombat())
                me->SetDisableGravity(false);
                
            if (!UpdateVictim())
                return;
                
            if (corruptionTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_CORRUPTION);
                corruptionTimer = 5000+rand()%3000;
            }
            else
                corruptionTimer -= diff;
                
            if (tailSweepTimer <= diff) {
                Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0, true, true);
                if (target && !me->HasInArc(M_PI, target))
                    DoCast(target, SPELL_TAIL_SWEEP);
                tailSweepTimer = 4000+rand()%3000;
            }
            else
                tailSweepTimer -= diff;
                
            if (bellowingRoarTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_BELLOWING_ROAR);
                bellowingRoarTimer = 15000+rand()%3000;
            }
            else
                bellowingRoarTimer -= diff;
                
            if (cleaveTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                cleaveTimer = 5000+rand()%3000;
            }
            else
                cleaveTimer -= diff;
                
            if (fieryBreathTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_FIERY_BREATH);
                fieryBreathTimer = 5000+rand()%2000;
            }
            else
                fieryBreathTimer -= diff;
                
            if (flameBreathTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FLAME_BREATH);
                flameBreathTimer = 12000+rand()%3000;
            }
            else
                flameBreathTimer -= diff;
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_rivendarkAI(creature);
    }
};


/*######
## npc_obsidia
######*/

#define SPELL_HELLFIRE      40717


class npc_obsidia : public CreatureScript
{
public:
    npc_obsidia() : CreatureScript("npc_obsidia")
    { }

    class npc_obsidiaAI : public ScriptedAI
    {
        public:
        npc_obsidiaAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 bellowingRoarTimer;
        uint32 cleaveTimer;
        uint32 fieryBreathTimer;
        uint32 flameBreathTimer;
        uint32 hellfireTimer;
        
        void Reset()
        override {
            bellowingRoarTimer = 15000;
            cleaveTimer = 5000;
            fieryBreathTimer = 8000;
            flameBreathTimer = 12000;
            hellfireTimer = 15000;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff)
        override {
            if (!me->IsInCombat())
                me->SetDisableGravity(true);
            else if (me->IsInCombat())
                me->SetDisableGravity(false);
                
            if (!UpdateVictim())
                return;
                
            if (bellowingRoarTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_BELLOWING_ROAR);
                bellowingRoarTimer = 15000+rand()%3000;
            }
            else
                bellowingRoarTimer -= diff;
                
            if (cleaveTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                cleaveTimer = 5000+rand()%3000;
            }
            else
                cleaveTimer -= diff;
                
            if (fieryBreathTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_FIERY_BREATH);
                fieryBreathTimer = 5000+rand()%2000;
            }
            else
                fieryBreathTimer -= diff;
                
            if (flameBreathTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FLAME_BREATH);
                flameBreathTimer = 12000+rand()%3000;
            }
            else
                flameBreathTimer -= diff;
                
            if (hellfireTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_HELLFIRE);
                hellfireTimer = 20000+rand()%8000;
            }
            else
                hellfireTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_obsidiaAI(creature);
    }
};


/*######
## npc_insidion
######*/

#define SPELL_FLAME_BUFFET      40719


class npc_insidion : public CreatureScript
{
public:
    npc_insidion() : CreatureScript("npc_insidion")
    { }

    class npc_insidionAI : public ScriptedAI
    {
        public:
        npc_insidionAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 bellowingRoarTimer;
        uint32 cleaveTimer;
        uint32 fieryBreathTimer;
        uint32 flameBreathTimer;
        uint32 flameBuffetTimer;
        
        void Reset()
        override {
            bellowingRoarTimer = 15000;
            cleaveTimer = 5000;
            fieryBreathTimer = 8000;
            flameBreathTimer = 12000;
            flameBuffetTimer = 15000;
            
            me->SetDisableGravity(true);
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff)
        override {
            if (!me->IsInCombat())
                me->SetDisableGravity(true);
            else /*if (me->IsInCombat())*/
                me->SetDisableGravity(false);
                
            if (!UpdateVictim())
                return;
                
            if (bellowingRoarTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_BELLOWING_ROAR);
                bellowingRoarTimer = 15000+rand()%3000;
            }
            else
                bellowingRoarTimer -= diff;
                
            if (cleaveTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                cleaveTimer = 5000+rand()%3000;
            }
            else
                cleaveTimer -= diff;
                
            if (fieryBreathTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_FIERY_BREATH);
                fieryBreathTimer = 5000+rand()%2000;
            }
            else
                fieryBreathTimer -= diff;
                
            if (flameBreathTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FLAME_BREATH);
                flameBreathTimer = 12000+rand()%3000;
            }
            else
                flameBreathTimer -= diff;
                
            if (flameBuffetTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_FLAME_BUFFET);
                flameBuffetTimer = 15000+rand()%8000;
            }
            else
                flameBuffetTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_insidionAI(creature);
    }
};


/*######
## npc_furywing
######*/

#define SPELL_WING_BUFFET       41572


class npc_furywing : public CreatureScript
{
public:
    npc_furywing() : CreatureScript("npc_furywing")
    { }

    class npc_furywingAI : public ScriptedAI
    {
        public:
        npc_furywingAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 tailSweepTimer;
        uint32 bellowingRoarTimer;
        uint32 cleaveTimer;
        uint32 fieryBreathTimer;
        uint32 flameBreathTimer;
        uint32 wingBuffetTimer;
        
        void Reset()
        override {
            tailSweepTimer = 10000;
            bellowingRoarTimer = 15000;
            cleaveTimer = 5000;
            fieryBreathTimer = 8000;
            flameBreathTimer = 12000;
            wingBuffetTimer = 2000;
        }
        
        void JustEngagedWith(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff)
        override {
            if (!me->IsInCombat())
                me->SetDisableGravity(true);
            else if (me->IsInCombat())
                me->SetDisableGravity(false);
                
            if (!UpdateVictim())
                return;
                
            if (tailSweepTimer <= diff) {
                Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0, true, true);
                if (target && !me->HasInArc(M_PI, target))
                    DoCast(target, SPELL_TAIL_SWEEP);
                tailSweepTimer = 4000+rand()%3000;
            }
            else
                tailSweepTimer -= diff;
                
            if (bellowingRoarTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_BELLOWING_ROAR);
                bellowingRoarTimer = 15000+rand()%3000;
            }
            else
                bellowingRoarTimer -= diff;
                
            if (cleaveTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                cleaveTimer = 5000+rand()%3000;
            }
            else
                cleaveTimer -= diff;
                
            if (fieryBreathTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_FIERY_BREATH);
                fieryBreathTimer = 5000+rand()%2000;
            }
            else
                fieryBreathTimer -= diff;
                
            if (flameBreathTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FLAME_BREATH);
                flameBreathTimer = 12000+rand()%3000;
            }
            else
                flameBreathTimer -= diff;
                
            if (wingBuffetTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_WING_BUFFET);
                wingBuffetTimer = 15000+rand()%3000;
            }
            else
                wingBuffetTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_furywingAI(creature);
    }
};


/*######
## trigger_banishing_crystal_bunny01
######*/


class trigger_banishing_crystal_bunny01 : public CreatureScript
{
public:
    trigger_banishing_crystal_bunny01() : CreatureScript("trigger_banishing_crystal_bunny01")
    { }

    class trigger_banishing_crystal_bunny01AI : public ScriptedAI
    {
        public:
        trigger_banishing_crystal_bunny01AI(Creature *c) : ScriptedAI(c) 
        {
            SetCombatMovementAllowed(false);
        }
        
        void Reset()
        override {
            me->AddAura(40849, me);
            me->AddAura(40857, me);
        }
        
        void JustEngagedWith(Unit *pWho) override {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new trigger_banishing_crystal_bunny01AI(creature);
    }
};


/*######
## npc_rally_zapnabber
######*/

#define QUEST_ZEPHYRIUM_CAPACITORIUM    10557
#define QUEST_SINGING_RIDGE             10710
#define GO_ZEPHYRIUM                    184628
#define SPELL_COSMETIC_LIGHTNING        37071
#define SPELL_SOARING_ZEPHYR            37910
#define SPELL_SOARING_SINGING           37962


class npc_rally_zapnabber : public CreatureScript
{
public:
    npc_rally_zapnabber() : CreatureScript("npc_rally_zapnabber")
    { }

    class npc_rally_zapnabberAI : public ScriptedAI
    {
        public:
        npc_rally_zapnabberAI(Creature* c) : ScriptedAI(c)
        {
            isEvent = false;
            lightningCount = 0;
            quest= 0;
        }
        
        bool isEvent;
        
        uint8 lightningCount;
        
        uint32 blueRayTimer;
        uint32 quest;
        
        ObjectGuid playerGUID;
        ObjectGuid triggerGUID;
        
        void Reset()
        override {
            blueRayTimer = 0;
        }
        
        void JustEngagedWith(Unit* who) override {}
        
        void StartEvent()
        {
            isEvent = true;
            if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                DoTeleportPlayer(player, 1920.138916, 5581.740723, 269.222229, 5.243360);
                
            if (Creature* trigger = me->SummonCreature(WORLD_TRIGGER, 1925.056152, 5574.165527, 269.162231, 0, TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                triggerGUID = trigger->GetGUID();
                trigger->SetFaction(FACTION_MONSTER);
            }
                
            blueRayTimer = 2000;
        }
        
        void EndEvent()
        {
            isEvent = false;
            playerGUID = ObjectGuid::Empty;
            blueRayTimer = 0;
            lightningCount = 0;
            if (Creature* trigger = ObjectAccessor::GetCreature(*me, triggerGUID))
                trigger->DespawnOrUnsummon();
            triggerGUID = ObjectGuid::Empty;
            quest = 0;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!isEvent)
                return;
                
            Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
            if (!player || player->GetDistance(me) > 50.0f) {
                EndEvent();
                return;
            }
            
            if (lightningCount >= 5) {
                if (Creature* trigger = ObjectAccessor::GetCreature(*me, triggerGUID))
                    player->CastSpell(player, (quest == QUEST_ZEPHYRIUM_CAPACITORIUM) ? SPELL_SOARING_ZEPHYR : SPELL_SOARING_SINGING, TRIGGERED_FULL_MASK);
                    
                EndEvent();
            }
                
            if (blueRayTimer <= diff) {
                if (Creature* trigger = ObjectAccessor::GetCreature(*me, triggerGUID)) {
                    trigger->CastSpell(player, SPELL_COSMETIC_LIGHTNING, TRIGGERED_FULL_MASK);
                    lightningCount++;
                }
                
                blueRayTimer = 500;
            }
            else
                blueRayTimer -= diff;
        }

        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            if (player->GetQuestStatus(QUEST_SINGING_RIDGE) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Emmenez-moi à la Crête chantante.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            else if (player->GetQuestStatus(QUEST_SINGING_RIDGE) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je viens tester le Zephyrium Capacitorium", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                
            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            player->CLOSE_GOSSIP_MENU();
            if (action == GOSSIP_ACTION_INFO_DEF) {
                player->CastSpell(player, 37958, TRIGGERED_FULL_MASK);
                ((npc_rally_zapnabber::npc_rally_zapnabberAI*)me->AI())->quest = QUEST_SINGING_RIDGE;
                ((npc_rally_zapnabber::npc_rally_zapnabberAI*)me->AI())->playerGUID = player->GetGUID();
                ((npc_rally_zapnabber::npc_rally_zapnabberAI*)me->AI())->StartEvent();
            }
            else if (action == GOSSIP_ACTION_INFO_DEF+1) {
                player->CastSpell(player, 37958, TRIGGERED_FULL_MASK);
                ((npc_rally_zapnabber::npc_rally_zapnabberAI*)me->AI())->quest = QUEST_ZEPHYRIUM_CAPACITORIUM;
                ((npc_rally_zapnabber::npc_rally_zapnabberAI*)me->AI())->playerGUID = player->GetGUID();
                ((npc_rally_zapnabber::npc_rally_zapnabberAI*)me->AI())->StartEvent();
            }

            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_rally_zapnabberAI(creature);
    }
};




/*######
## npc_grulloc
######*/

enum grullocSpells {
    SPELL_BURNING_RAGE      = 38771,
    SPELL_CRUSH_ARMOR       = 21055,
    SPELL_GRIEVOUS_WOUND    = 38772
};


class npc_grulloc : public CreatureScript
{
public:
    npc_grulloc() : CreatureScript("npc_grulloc")
    { }

    class npc_grullocAI : public ScriptedAI
    {
        public:
        npc_grullocAI(Creature* c) : ScriptedAI(c)
        {
            isEvent = false;
        }
        
        bool isEvent;
        
        uint32 burningRageTimer;
        uint32 crushArmorTimer;
        uint32 grievousWoundTimer;
        uint32 killHufferTimer;
        
        ObjectGuid hufferGUID;
        
        void Reset()
        override {
            burningRageTimer = 20000;
            crushArmorTimer = 7000;
            grievousWoundTimer = 10000;
            killHufferTimer = 0;
            hufferGUID.Clear();
        }
        
        void MoveInLineOfSight(Unit* who)
        override {
            if (isEvent)
                return;
                
            if (who->ToCreature() && who->GetEntry() == 22114) {
                isEvent = true;
                me->GetMotionMaster()->MoveFollow(who, 1.0f, M_PI);
                hufferGUID = who->GetGUID();
                killHufferTimer = 18000;
            }
        }
        
        void JustEngagedWith(Unit* who) override {}
        
        void UpdateAI(uint32 const diff)
        override {
                
            if (killHufferTimer) {
                if (killHufferTimer <= diff) {
                    if (Creature* huffer = ObjectAccessor::GetCreature(*me, hufferGUID)) {
                        Unit::Kill(me, huffer);
                        EnterEvadeMode();
                    }
                    killHufferTimer = 0;
                }
                else
                    killHufferTimer -= diff;
            }
    
            if (!UpdateVictim())
                return;
            
            if (me->GetVictim()->GetEntry() == 22114)
                return;
                
            if (burningRageTimer <= diff) {
                DoCast(me, SPELL_BURNING_RAGE, true);
                burningRageTimer = 20000 + rand() % 5000;
            }
            else
                burningRageTimer -= diff;
                
            if (crushArmorTimer <= diff) {
                DoCast(me->GetVictim(),SPELL_CRUSH_ARMOR);
                crushArmorTimer = 12000 + rand() % 4000;
            }
            else
                crushArmorTimer -= diff;
                
            if (grievousWoundTimer <= diff) {
                DoCast(me->GetVictim(),SPELL_GRIEVOUS_WOUND);
                grievousWoundTimer = 45000;
            }
            else
                grievousWoundTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    
        void JustDied(Unit* killer)
        override {
            killer->SummonGameObject(185567, Position(2694.32, 5525.05, 1.18, 0), G3D::Quat(), 60000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_grullocAI(creature);
    }
};


/*######
## npc_huffler
######*/


class npc_huffer : public CreatureScript
{
public:
    npc_huffer() : CreatureScript("npc_huffer")
    { }

    class npc_hufferAI : public ScriptedAI
    {
        public:
        npc_hufferAI(Creature* c) : ScriptedAI(c) {}
        
        void Reset()
        override {
            if (Creature* grulloc = me->FindNearestCreature(20216, 30.0f, true))
                me->GetMotionMaster()->MovePath(22114);
        }
        
        void JustEngagedWith(Unit* who) override {}
        
        void UpdateAI(uint32 const diff) override {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hufferAI(creature);
    }
};


/*######
## npc_grishna
######*/


class npc_grishna : public CreatureScript
{
public:
    npc_grishna() : CreatureScript("npc_grishna")
    { }

    class npc_grishnaAI : public ScriptedAI
    {
        public:
        npc_grishnaAI(Creature* c) : ScriptedAI(c) {}
        
        void JustEngagedWith(Unit* who) override {}
        
        void JustDied(Unit* killer)
        override {
            killer->CastSpell(killer, 37466, TRIGGERED_FULL_MASK);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_grishnaAI(creature);
    }
};


/*######
## AddSC
######*/

void AddSC_blades_edge_mountains()
{

    new mobs_bladespire_ogre();

    new mobs_nether_drake();

    new npc_daranelle();

    new npc_overseer_nuaar();

    new npc_saikkal_the_elder();
    
    new LegionObelisk();

    new npc_skyguard_handler_irena();
    
    new npc_prophecy_questcredit();
    
    new npc_grishna_falconwing();
    
    new EthereumChamber();
        
    new npc_kolphis_darkscale();
    
    new trigger_vimgol_circle_bunny();
    
    new npc_vimgol();
    
    new npc_soulgrinder();
    
    new npc_skulloc();
    
    new npc_sundered_ghost();
    
    new ApexisRelix();
    
    new npc_simon_bunny();
    
    new BlueCluster();
    new GreenCluster();
    new RedCluster();
    new YellowCluster();

    new ApexisMonument();
    
    new npc_simon_bunny_large();
    
    new BlueClusterLarge();
    new GreenClusterLarge();
    new RedClusterLarge();
    new YellowClusterLarge();

    new npc_braxxus();
    
    new npc_moarg_incinerator();
    
    new npc_galvanoth();
    
    new npc_zarcsin();
    
    new npc_aether_ray();
    
    new npc_wrangled_aether_ray();
    
    new DrakeEgg();

    new npc_rivendark();
    
    new npc_obsidia();
    
    new npc_insidion();
    
    new npc_furywing();
    
    new trigger_banishing_crystal_bunny01();
    
    new npc_rally_zapnabber();
    
    new npc_grulloc();
    
    new npc_huffer();
    
    new npc_grishna();
}

