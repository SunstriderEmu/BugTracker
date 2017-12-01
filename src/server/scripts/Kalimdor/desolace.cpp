
/* ScriptData
SDName: Desolace
SD%Complete: 100
SDComment: Quest support: 5561, 1440
SDCategory: Desolace
EndScriptData */

/* ContentData
npc_aged_dying_ancient_kodo
npc_dalinda
EndContentData */


#include "EscortAI.h"
#include "Pet.h"

enum eDyingKodo
{
    SAY_SMEED_HOME_1                = -1600348,
    SAY_SMEED_HOME_2                = -1600349,
    SAY_SMEED_HOME_3                = -1600350,

    GOSSIP_MENU_KODO_HOME            = 21000,

    QUEST_KODO                      = 5561,

    NPC_SMEED                       = 11596,
    NPC_AGED_KODO                   = 4700,
    NPC_DYING_KODO                  = 4701,
    NPC_ANCIENT_KODO                = 4702,
    NPC_TAMED_KODO                  = 11627,

    SPELL_KODO_KOMBO_ITEM           = 18153,
    SPELL_KODO_KOMBO_PLAYER_BUFF    = 18172,                //spells here have unclear function, but using them at least for visual parts and checks
    SPELL_KODO_KOMBO_DESPAWN_BUFF   = 18377,
    SPELL_KODO_KOMBO_GOSSIP         = 18362

};


class npc_aged_dying_ancient_kodo : public CreatureScript
{
public:
    npc_aged_dying_ancient_kodo() : CreatureScript("npc_aged_dying_ancient_kodo")
    { }

    class npc_aged_dying_ancient_kodoAI : public ScriptedAI
    {
        public:
        npc_aged_dying_ancient_kodoAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }
    
        uint32 m_uiDespawnTimer;
    
        void Reset()
        override {
            m_uiDespawnTimer = 0;
        }
        
        void EnterCombat(Unit *pWho) override {}
    
        void MoveInLineOfSight(Unit* pWho)
        override {
            if (pWho->GetEntry() == NPC_SMEED)
            {
                if (me->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
                    return;
    
                if (me->GetEntry() == NPC_TAMED_KODO && me->IsWithinDistInMap(pWho, 10.0f))
                {
                    DoScriptText(RAND(SAY_SMEED_HOME_1,SAY_SMEED_HOME_2,SAY_SMEED_HOME_3), pWho);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    m_uiDespawnTimer = 60000;                
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //timer should always be == 0 unless we already updated entry of creature. Then not expect this updated to ever be in combat.
            if (m_uiDespawnTimer && m_uiDespawnTimer <= diff)
            {
                if (!me->GetVictim() && me->IsAlive())
                {
                    Reset();
                    me->SetDeathState(JUST_DIED);
                    me->Respawn();
                    return;
                }
            } else m_uiDespawnTimer -= diff;
    
            if (!UpdateVictim())
                return;
        }

        virtual bool sOnDummyEffect(Unit* pCaster, uint32 spellId, uint32 effIndex) override
        {
            //always check spellid and effectindex
            if (spellId == SPELL_KODO_KOMBO_ITEM && effIndex == 0)
            {
                //no effect if player/creature already have aura from spells
                if (pCaster->HasAuraEffect(SPELL_KODO_KOMBO_PLAYER_BUFF, 0) || me->HasAuraEffect(SPELL_KODO_KOMBO_DESPAWN_BUFF, 0))
                    return true;

                if (me->GetEntry() == NPC_AGED_KODO ||
                    me->GetEntry() == NPC_DYING_KODO ||
                    me->GetEntry() == NPC_ANCIENT_KODO)
                {
                    pCaster->CastSpell(pCaster,SPELL_KODO_KOMBO_PLAYER_BUFF, TRIGGERED_FULL_MASK);

                    me->UpdateEntry(NPC_TAMED_KODO);
                    me->CastSpell(me,SPELL_KODO_KOMBO_DESPAWN_BUFF, TRIGGERED_NONE);

                    if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == WAYPOINT_MOTION_TYPE)
                        me->GetMotionMaster()->MoveIdle();

                    me->GetMotionMaster()->MoveFollow(pCaster, PET_FOLLOW_DIST, me->GetFollowAngle());
                }

                //always return true when we are handling this spell and effect
                return true;
            }

            return false;

        }


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->HasAuraEffect(SPELL_KODO_KOMBO_PLAYER_BUFF,0) && me->HasAuraEffect(SPELL_KODO_KOMBO_DESPAWN_BUFF,0))
            {    
                pPlayer->RemoveAurasDueToSpell(SPELL_KODO_KOMBO_PLAYER_BUFF);
                pPlayer->CastSpell(me, SPELL_KODO_KOMBO_GOSSIP, TRIGGERED_FULL_MASK);

                me->RemoveAurasDueToSpell(SPELL_KODO_KOMBO_DESPAWN_BUFF);
                me->GetMotionMaster()->MoveIdle();    

                pPlayer->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_KODO_HOME, me->GetGUID());
                
                return true;
            }

            return false;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_aged_dying_ancient_kodoAI(creature);
    }
};




/*######
## npc_dalinda_malem.
######*/

#define QUEST_RETURN_TO_VAHLARRIEL     1440


class npc_dalinda : public CreatureScript
{
public:
    npc_dalinda() : CreatureScript("npc_dalinda")
    { }

    class npc_dalindaAI : public EscortAI
    {
        public:
        npc_dalindaAI(Creature* pCreature) : EscortAI(pCreature)
        {
            completed = false;
        }   
            
        bool completed;    
        
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* player = GetPlayerForEscort();
            switch (i)
            {
                case 1:
                    me->SetStandState(UNIT_STAND_STATE_STAND);
                    break;            
                case 15:                
                    if (player)
                        player->GroupEventHappens(QUEST_RETURN_TO_VAHLARRIEL, me);
                        
                    completed = true;
                    break;            
            }
        }
    
        void EnterCombat(Unit* /*pWho*/) override { }
    
        void Reset() override {}
    
        void JustDied(Unit* /*pKiller*/)
        override {
            if (completed)
                return;
    
            Player* player = GetPlayerForEscort();
            if (player)
                player->FailQuest(QUEST_RETURN_TO_VAHLARRIEL);
    
            return;
        }
    
        void UpdateAI(const uint32 uiDiff)
        override {        
            EscortAI::UpdateAI(uiDiff);
    
            if (!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_RETURN_TO_VAHLARRIEL)
   {        
                if (EscortAI* pEscortAI = CAST_AI(npc_dalindaAI, me->AI()))
                {
                    pEscortAI->Start(true, false, player->GetGUID(), quest);
                    me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dalindaAI(creature);
    }
};




class npc_melizza : public CreatureScript
{
public:
    npc_melizza() : CreatureScript("npc_melizza")
    { }

    class npc_melizzaAI : public EscortAI
    {
        public:
        npc_melizzaAI(Creature* pCreature) : EscortAI(pCreature)
        {
            completed = false;
        }   
            
        bool completed;    
        
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* player = GetPlayerForEscort();
            switch (i)
            {        
                case 7:                
                    if (player)
                        player->GroupEventHappens(6132, me);
                        
                    me->DisappearAndDie();
                    completed = true;
                    break;            
            }
        }
    
        void EnterCombat(Unit* /*pWho*/) override { }
    
        void Reset() override {}
    
        void JustDied(Unit* /*pKiller*/)
        override {
            if (completed)
                return;
    
            Player* player = GetPlayerForEscort();
            if (player)
                player->FailQuest(6132);
    
            return;
        }
    
        void UpdateAI(const uint32 uiDiff)
        override {        
            EscortAI::UpdateAI(uiDiff);
    
            if (!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == 6132)
   {        
                if (EscortAI* pEscortAI = CAST_AI(npc_melizzaAI, me->AI()))
                {
                    pEscortAI->Start(true, false, player->GetGUID(), quest);
                    me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_melizzaAI(creature);
    }
};



void AddSC_desolace()
{

    new npc_aged_dying_ancient_kodo();

    new npc_dalinda();
    
    new npc_melizza();

}
