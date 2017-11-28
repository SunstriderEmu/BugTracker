/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ScriptData
SDName: Ashenvale
SD%Complete: 70
SDComment: Quest support: 6544, 6482, 976
SDCategory: Ashenvale Forest
EndScriptData */

/* ContentData
npc_torek
npc_ruul_snowhoof
npc_feero_ironhand
EndContentData */


#include "EscortAI.h"
#include "Pet.h"

/*####
# npc_torek
####*/

enum eTorek
{
SAY_READY                   = -1000106,
SAY_MOVE                    = -1000107,
SAY_PREPARE                 = -1000108,
SAY_WIN                     = -1000109,
SAY_END                     = -1000110,

SPELL_REND                  = 11977,
SPELL_THUNDERCLAP           = 8078,

QUEST_TOREK_ASSULT          = 6544,

ENTRY_SPLINTERTREE_RAIDER   = 12859,
ENTRY_DURIEL                = 12860,
ENTRY_SILVERWING_SENTINEL   = 12896,
ENTRY_SILVERWING_WARRIOR    = 12897
};


class npc_torek : public CreatureScript
{
public:
    npc_torek() : CreatureScript("npc_torek")
    { }

    class npc_torekAI : public EscortAI
    {
        public:
        npc_torekAI(Creature *c) : EscortAI(c) {}
    
        uint32 Rend_Timer;
        uint32 Thunderclap_Timer;
        bool Completed;
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* player = GetPlayerForEscort();
    
            if (!player)
                return;
    
            switch (i)
            {
            case 1:
                DoScriptText(SAY_MOVE, me, player);
                break;
            case 8:
                DoScriptText(SAY_PREPARE, me, player);
                break;
            case 19:
                //TODO: verify location and creatures amount.
                me->SummonCreature(ENTRY_DURIEL,1776.73,-2049.06,109.83,1.54,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,25000);
                me->SummonCreature(ENTRY_SILVERWING_SENTINEL,1774.64,-2049.41,109.83,1.40,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,25000);
                me->SummonCreature(ENTRY_SILVERWING_WARRIOR,1778.73,-2049.50,109.83,1.67,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,25000);
                break;
            case 20:
                DoScriptText(SAY_WIN, me, player);
                Completed = true;
                player->GroupEventHappens(QUEST_TOREK_ASSULT,me);
                break;
            case 21:
                DoScriptText(SAY_END, me, player);
                break;
            }
        }
        
        void GatherGuards()
        {
            std::list<Creature*> templist;
            float x, y, z;
            me->GetPosition(x, y, z);
    
            {
                Trinity::AllFriendlyCreaturesInGrid check(me);
                Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid> searcher(me, templist, check);
    
                Cell::VisitGridObjects(me, searcher, MAX_SEARCHER_DISTANCE);
            }
    
            if(!templist.size())
                return;
    
            for(auto & i : templist)
            {
                if(i && i->GetEntry() == 12859)
                {
                    i->SetNoCallAssistance(true);
                    i->GetMotionMaster()->MoveFollow(me, PET_FOLLOW_DIST, i->GetFollowAngle());
                }
            }
        }
    
        void Reset() override
        {
            Rend_Timer = 5000;
            Thunderclap_Timer = 8000;
            Completed = false;
        }
    
        void EnterCombat(Unit* who) override
        {
        }
    
        void JustSummoned(Creature* summoned) override
        {
            summoned->AI()->AttackStart(me);
        }
    
        void JustDied(Unit* killer) override
        {
            if (_playerGUID && !Completed)
            {
                if (Player* player = GetPlayerForEscort())
                    player->FailQuest(QUEST_TOREK_ASSULT);
            }
        }
    
        void UpdateAI(const uint32 diff) override
        {
            EscortAI::UpdateAI(diff);
    
            if (!UpdateVictim())
                return;
    
            if (Rend_Timer < diff)
            {
                DoCast(me->GetVictim(),SPELL_REND);
                Rend_Timer = 20000;
            }else Rend_Timer -= diff;
    
            if (Thunderclap_Timer < diff)
            {
                DoCast(me,SPELL_THUNDERCLAP);
                Thunderclap_Timer = 30000;
            }else Thunderclap_Timer -= diff;
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_TOREK_ASSULT)
            {
                //TODO: find companions, make them follow Torek, at any time (possibly done by mangos/database in future?)
                if (EscortAI* pEscortAI = CAST_AI(npc_torekAI, (me->AI()))) {
                    pEscortAI->Start(true, true, pPlayer->GetGUID(), quest);
                    ((npc_torek::npc_torekAI*)pEscortAI)->GatherGuards();
                }
                    
                DoScriptText(SAY_READY, me, pPlayer);
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_torekAI(creature);
    }
};



/*####
# npc_ruul_snowhoof
####*/

#define QUEST_FREEDOM_TO_RUUL    6482
#define GO_CAGE                  178147


class npc_ruul_snowhoof : public CreatureScript
{
public:
    npc_ruul_snowhoof() : CreatureScript("npc_ruul_snowhoof")
    { }

    class npc_ruul_snowhoofAI : public EscortAI
    {
        public:
        npc_ruul_snowhoofAI(Creature *c) : EscortAI(c) {}
        
        bool completed;
    
        void EnterCombat(Unit*) override {}
    
        void WaypointReached(uint32 i, uint32 pathID) override
        {
            Player* player = GetPlayerForEscort();
    
            if (!player)
                return;
    
            switch(i)
            {
            case 0:    {
                    me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                    GameObject* Cage = me->FindNearestGameObject(GO_CAGE, 20);
                    if(Cage)
                        Cage->SetGoState(GO_STATE_ACTIVE);
                    break;}
            case 13:
                    me->SummonCreature(3922, 3449.218018, -587.825073, 174.978867, 4.714445, TEMPSUMMON_DEAD_DESPAWN, 60000);
                    me->SummonCreature(3921, 3446.384521, -587.830872, 175.186279, 4.714445, TEMPSUMMON_DEAD_DESPAWN, 60000);
                    me->SummonCreature(3926, 3444.218994, -587.835327, 175.380600, 4.714445, TEMPSUMMON_DEAD_DESPAWN, 60000);
                    break;
            case 19:
                    me->SummonCreature(3922, 3508.344482, -492.024261, 186.929031, 4.145029, TEMPSUMMON_DEAD_DESPAWN, 60000);
                    me->SummonCreature(3921, 3506.265625, -490.531006, 186.740128, 4.239277, TEMPSUMMON_DEAD_DESPAWN, 60000);
                    me->SummonCreature(3926, 3503.682373, -489.393799, 186.629684, 4.349232, TEMPSUMMON_DEAD_DESPAWN, 60000);
                    break;
    
            case 21:
                    player->GroupEventHappens(QUEST_FREEDOM_TO_RUUL,me);
                    completed = true;
                    break;
            }
        }
    
        void Reset() override
        {
            if (!HasEscortState(STATE_ESCORT_ESCORTING))
                me->SetFaction(1602);
    
            GameObject* Cage = me->FindNearestGameObject(GO_CAGE, 20);
            if(Cage)
                Cage->ResetDoorOrButton();
                
            completed = false;
        }
    
        void JustSummoned(Creature* summoned) override
        {
            summoned->AI()->AttackStart(me);
        }
    
        void JustDied(Unit* killer) override
        {
            if (_playerGUID)
            {
                Player* player = GetPlayerForEscort();
                if (player && !completed)
                    player->FailQuest(QUEST_FREEDOM_TO_RUUL);
            }
        }
    
        void UpdateAI(const uint32 diff) override
        {
            EscortAI::UpdateAI(diff);
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_FREEDOM_TO_RUUL)
            {
                me->SetFaction(player->GetFaction());
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                ((EscortAI*)(me->AI()))->Start(true, false, player->GetGUID(), quest);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ruul_snowhoofAI(creature);
    }
};



enum eEnums
{
    SAY_MUG_START1          = -1800054,
    SAY_MUG_START2          = -1800055,
    SAY_MUG_BRAZIER         = -1800056,
    SAY_MUG_BRAZIER_WAIT    = -1800057,
    SAY_MUG_ON_GUARD        = -1800058,
    SAY_MUG_REST            = -1800059,
    SAY_MUG_DONE            = -1800060,
    SAY_MUG_GRATITUDE       = -1800061,
    SAY_MUG_PATROL          = -1800062,
    SAY_MUG_RETURN          = -1800063,

    QUEST_VORSHA            = 6641,

    GO_NAGA_BRAZIER         = 178247,    

    NPC_WRATH_RIDER         = 3713,
    NPC_WRATH_SORCERESS     = 3717,
    NPC_WRATH_RAZORTAIL     = 3712,

    NPC_WRATH_PRIESTESS     = 3944,
    NPC_WRATH_MYRMIDON      = 3711,
    NPC_WRATH_SEAWITCH      = 3715,

    NPC_VORSHA              = 12940,
    NPC_MUGLASH             = 12717
};

static float m_afFirstNagaCoord[3][3]=
{
    {3603.504150f, 1122.631104f,  1.635f },                      // rider
    {3589.293945f, 1148.664063f,  5.565f },                      // sorceress
    {3609.925537f, 1168.759521f, -1.168f },                      // razortail
};

static float m_afSecondNagaCoord[3][3] =
{
    {3609.925537f, 1168.759521f, -1.168f},                      // witch
    {3645.652100f, 1139.425415f,  1.322f},                      // priest
    {3583.602051f, 1128.405762f,  2.347f},                      // myrmidon
};

static float m_fVorshaCoord[]={3633.056885f, 1172.924072f, -5.388f};




class npc_muglash : public CreatureScript
{
public:
    npc_muglash() : CreatureScript("npc_muglash")
    { }

    class npc_muglashAI : public EscortAI
    {
        public:
        npc_muglashAI(Creature* pCreature) : EscortAI(pCreature) { }
    
        uint32 m_uiWaveId;
        uint32 m_uiEventTimer;
        bool m_bIsBrazierExtinguished;
        bool m_completed;
        
        uint64 playerGUID;
    
        void JustSummoned(Creature* pSummoned)
        override {
            pSummoned->AI()->AttackStart(me);        
        }
        
        void SummonedCreatureDespawn(Creature* summon)
        override {
            if (summon->GetEntry() == NPC_VORSHA) {
                if (Player* player = GetPlayerForEscort()) {
                    player->GroupEventHappens(QUEST_VORSHA, summon);
                    m_completed = true;
                }
            }
        }
        
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* pPlayer = GetPlayerForEscort();
            if (pPlayer)
                    playerGUID = pPlayer->GetGUID();
    
            switch(i)
            {
                case 0:
                    if (pPlayer)
                        DoScriptText(SAY_MUG_START2, me, pPlayer);
                    break;
                case 13:
                    if (pPlayer)
                        DoScriptText(SAY_MUG_BRAZIER, me, pPlayer);
    
                    if (pPlayer) {
                        if (GameObject* pGo = pPlayer->FindNearestGameObject(GO_NAGA_BRAZIER, INTERACTION_DISTANCE*2))
                        {
                            //TODO translate
                            me->Say("Light the blaze, if you please.", LANG_UNIVERSAL);
                            //me->Say("Activez le brasier, s'il vous plait.", LANG_UNIVERSAL, nullptr);
                            pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                            //AddEscortState(STATE_ESCORT_ESCORTING);
                            SetEscortPaused(true);
                        }
                    }
                    break;
                case 14:
                    //AddEscortState(STATE_ESCORT_ESCORTING);
                    break;
            }
        }
    
        void EnterCombat(Unit* pWho) override
        {
            if (HasEscortState(STATE_ESCORT_PAUSED))
            {
                if (urand(0, 1))                
                    DoScriptText(SAY_MUG_ON_GUARD, me);
                return;
            }
        }
    
        void Reset() override
        {
            m_uiEventTimer = 10000;
            m_uiWaveId = 0;
            m_bIsBrazierExtinguished = false;
            m_completed = false;
        }
    
        void JustDied(Unit* pKiller) override
        {
            Player* pPlayer = GetPlayerForEscort();
            if (HasEscortState(STATE_ESCORT_ESCORTING) && !m_completed)
            {
                if (pPlayer)
                {
                    pPlayer->FailQuest(QUEST_VORSHA);
                }
            }        
        }
    
        void DoWaveSummon()
        {
            switch(m_uiWaveId)
            {
                case 1:
                    me->SummonCreature(NPC_WRATH_RIDER,     m_afFirstNagaCoord[0][0], m_afFirstNagaCoord[0][1], m_afFirstNagaCoord[0][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                    me->SummonCreature(NPC_WRATH_SORCERESS, m_afFirstNagaCoord[1][0], m_afFirstNagaCoord[1][1], m_afFirstNagaCoord[1][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                    me->SummonCreature(NPC_WRATH_RAZORTAIL, m_afFirstNagaCoord[2][0], m_afFirstNagaCoord[2][1], m_afFirstNagaCoord[2][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                    break;
                case 2:
                    me->SummonCreature(NPC_WRATH_PRIESTESS, m_afSecondNagaCoord[0][0], m_afSecondNagaCoord[0][1], m_afSecondNagaCoord[0][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                    me->SummonCreature(NPC_WRATH_MYRMIDON,  m_afSecondNagaCoord[1][0], m_afSecondNagaCoord[1][1], m_afSecondNagaCoord[1][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                    me->SummonCreature(NPC_WRATH_SEAWITCH,  m_afSecondNagaCoord[2][0], m_afSecondNagaCoord[2][1], m_afSecondNagaCoord[2][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                    break;
                case 3:
                    me->SummonCreature(NPC_VORSHA, m_fVorshaCoord[0], m_fVorshaCoord[1], m_fVorshaCoord[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                    break;
                case 4:
                {
                    SetEscortPaused(false);
                    DoScriptText(SAY_MUG_DONE, me);
                    me->DisappearAndDie();
                    me->Respawn();
                    if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID)) {
                        player->GroupEventHappens(QUEST_VORSHA, me);
                        m_completed = true;
                    }
                    break;
                }
            }
        }    
    
        void UpdateAI(const uint32 uiDiff)
        override {
            EscortAI::UpdateAI(uiDiff);
    
            if (!me->GetVictim())
            {
                if (m_bIsBrazierExtinguished)
                {
                    if (m_uiEventTimer < uiDiff)
                    {
                        ++m_uiWaveId;
                        DoWaveSummon();
                        m_uiEventTimer = 10000;
                    }
                    else
                        m_uiEventTimer -= uiDiff;
                }    
                return;            
            }
            
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_VORSHA)
            {
                if (npc_muglashAI* pEscortAI = CAST_AI(npc_muglash::npc_muglashAI, me->AI()))
                {
                    DoScriptText(SAY_MUG_START1, me);
                    me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);

                    pEscortAI->Start(true, true, pPlayer->GetGUID(), quest);
                    pEscortAI->SetDespawnAtEnd(false);
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_muglashAI(creature);
    }
};



class NagaBrazier : public GameObjectScript
{
public:
    NagaBrazier() : GameObjectScript("go_naga_brazier")
    {}

    struct NagaBrazierAI : public GameObjectAI
    {
        NagaBrazierAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* p) override
        {
            if (Creature* pCreature = p->FindNearestCreature(NPC_MUGLASH, INTERACTION_DISTANCE * 2, true))
            {
                if (npc_muglash::npc_muglashAI* pEscortAI = CAST_AI(npc_muglash::npc_muglashAI, pCreature->AI()))
                {
                    DoScriptText(SAY_MUG_BRAZIER_WAIT, pCreature);

                    pEscortAI->m_bIsBrazierExtinguished = true;
                    return false;
                }
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new NagaBrazierAI(go);
    }
};

/*######
## npc_feero_ironhand
######*/

enum FeeroIronhandData
{
    QUEST_SUPPLIES_TO_AUBERDINE = 976,
    
    FEERO_SAY_START             = -1000766, // Start
    FEERO_SAY_AMBUSH1           = -1000767, // Ambush 1
    FEERO_SAY_AMBUSH1_AFTER     = -1000768,
    FEERO_SAY_AMBUSH2           = -1000769,
    FEERO_SAY_AMBUSH2_ENEMY     = -1000770, // Said by one of the Forsaken Scouts
    FEERO_SAY_AMBUSH2_AFTER     = -1000771,
    FEERO_SAY_AMBUSH3           = -1000772,
    FEERO_SAY_AMBUSH3_ENEMY     = -1000773,
    FEERO_SAY_AMBUSH3_GO        = -1000774,
    FEERO_SAY_END               = -1000775,
    
    NPC_FEERO                   = 4484,
    NPC_DARK_STRAND_ASSASSIN    = 3879,
    NPC_FORSAKEN_SCOUT          = 3893,
    NPC_CAEDAKAR_THE_VICIOUS    = 3900, // West
    NPC_ALIGAR_THE_TORMENTOR    = 3898, // Center
    NPC_BALIZAR_THE_UMBRAGE     = 3899, // East
};


class npc_feero_ironhand : public CreatureScript
{
public:
    npc_feero_ironhand() : CreatureScript("npc_feero_ironhand")
    { }

    class npc_feero_ironhandAI : public EscortAI
    {
        public:
        npc_feero_ironhandAI(Creature* c) : EscortAI(c), summons(me) {}
        
        SummonList summons;
        
        bool tauntedSatyr;
        
        void Reset() override
        {
            tauntedSatyr = false;
        }
        
        void JustDied(Unit* killer) override
        {
            Player* player = GetPlayerForEscort();
            if (HasEscortState(STATE_ESCORT_ESCORTING)) {
                if (player)
                    player->FailQuest(QUEST_SUPPLIES_TO_AUBERDINE);
            }
    
            summons.DespawnAll();
        }
    
        void SummonedCreatureDespawn(Creature* summon)
        override {
            summons.Despawn(summon);
            
            switch (summon->GetEntry()) {
                case NPC_CAEDAKAR_THE_VICIOUS:
                case NPC_ALIGAR_THE_TORMENTOR:
                case NPC_BALIZAR_THE_UMBRAGE:
                {
                    if (summons.IsEmpty()) {
                        if (Player* player = GetPlayerForEscort()) {
                            DoScriptText(FEERO_SAY_END, me, nullptr);
                            if (player->GetGroup())
                                player->GroupEventHappens(QUEST_SUPPLIES_TO_AUBERDINE, me);
                            else
                                player->AreaExploredOrEventHappens(QUEST_SUPPLIES_TO_AUBERDINE);
                        }
                    }
                    break;
                }
                case NPC_DARK_STRAND_ASSASSIN:
                    if (summons.IsEmpty())
                        DoScriptText(FEERO_SAY_AMBUSH1_AFTER, me, nullptr);
                    break;
                case NPC_FORSAKEN_SCOUT:
                    if (summons.IsEmpty())
                        DoScriptText(FEERO_SAY_AMBUSH2_AFTER, me, nullptr);
                    break;
            }
        }
        
        void AttackStart(Unit* who)
        override {
            if (who->GetEntry() == NPC_BALIZAR_THE_UMBRAGE && !tauntedSatyr) {
                tauntedSatyr = true;
                DoScriptText(FEERO_SAY_AMBUSH3_GO, me, nullptr);
            }
                
            EscortAI::AttackStart(who);
        }
        
        void JustSummoned(Creature* summon)
        override {
            summons.Summon(summon);
            
            switch (summon->GetEntry()) {
                case NPC_FORSAKEN_SCOUT:
                    if (rand()%3 == 0)
                        DoScriptText(FEERO_SAY_AMBUSH2_ENEMY, summon, nullptr);
                    break;
                case NPC_BALIZAR_THE_UMBRAGE:
                    DoScriptText(FEERO_SAY_AMBUSH3_ENEMY, summon, nullptr);
                    summon->AI()->AttackStart(me); // Force him to attack me
                    return;
            }
            
            Player* player = GetPlayerForEscort();
            if (player) {
                if (rand()%2)
                    summon->AI()->AttackStart(player);
                else
                    summon->AI()->AttackStart(me);
            }
            else
                summon->AI()->AttackStart(me);
        }
        
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            //Player* player = GetPlayerForEscort();
    
            switch(i)
            {
                case 8:
                    DoScriptText(FEERO_SAY_AMBUSH1, me, nullptr);
                    me->SummonCreature(NPC_DARK_STRAND_ASSASSIN, 3568.471924, 218.518387, 5.006559, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    me->SummonCreature(NPC_DARK_STRAND_ASSASSIN, 3569.471924, 218.518387, 5.006559, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    me->SummonCreature(NPC_DARK_STRAND_ASSASSIN, 3567.471924, 218.518387, 5.006559, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    me->SummonCreature(NPC_DARK_STRAND_ASSASSIN, 3568.471924, 219.518387, 5.006559, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    break;
                case 11:
                    DoScriptText(FEERO_SAY_AMBUSH2, me, nullptr);
                    me->SummonCreature(NPC_FORSAKEN_SCOUT, 3796.817627, 133.361282, 9.080805, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    me->SummonCreature(NPC_FORSAKEN_SCOUT, 3796.817627, 133.361282, 9.080805, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    me->SummonCreature(NPC_FORSAKEN_SCOUT, 3796.817627, 133.361282, 9.080805, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    break;
                case 19:
                    DoScriptText(FEERO_SAY_AMBUSH3, me, nullptr);
                    me->SummonCreature(NPC_CAEDAKAR_THE_VICIOUS, 4305.477051, 158.758896, 47.088223, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    me->SummonCreature(NPC_ALIGAR_THE_TORMENTOR, 4307.477051, 158.758896, 47.088223, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    me->SummonCreature(NPC_BALIZAR_THE_UMBRAGE, 4306.477051, 158.758896, 47.088223, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                    SetRun();
                    break;
                case 20:
                    me->DisappearAndDie();
                    break;
            }
        }
        
        void EnterCombat(Unit*) override {}
    
        void UpdateAI(uint32 const diff)
        override {
            EscortAI::UpdateAI(diff);
            
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_SUPPLIES_TO_AUBERDINE) {
                if (npc_feero_ironhandAI* escortAI = CAST_AI(npc_feero_ironhand::npc_feero_ironhandAI, me->AI())) {
                    DoScriptText(FEERO_SAY_START, me);
                    me->SetFaction(player->GetFaction());

                    escortAI->Start(true, false, player->GetGUID(), quest);
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_feero_ironhandAI(creature);
    }
};



void AddSC_ashenvale()
{

    new npc_torek();

    new npc_ruul_snowhoof();
    
    new npc_muglash();

    new NagaBrazier();

    new npc_feero_ironhand();
}

