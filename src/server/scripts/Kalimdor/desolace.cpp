/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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

struct npc_aged_dying_ancient_kodoAI : public ScriptedAI
{
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
};

bool EffectDummyCreature_npc_aged_dying_ancient_kodo(Unit *pCaster, uint32 spellId, uint32 effIndex, Creature *pCreatureTarget)
{
    //always check spellid and effectindex
    if (spellId == SPELL_KODO_KOMBO_ITEM && effIndex == 0)
    {
        //no effect if player/creature already have aura from spells
        if (pCaster->HasAuraEffect(SPELL_KODO_KOMBO_PLAYER_BUFF,0) || pCreatureTarget->HasAuraEffect(SPELL_KODO_KOMBO_DESPAWN_BUFF,0))
            return true;

        if (pCreatureTarget->GetEntry() == NPC_AGED_KODO ||
            pCreatureTarget->GetEntry() == NPC_DYING_KODO ||
            pCreatureTarget->GetEntry() == NPC_ANCIENT_KODO)
        {
            pCaster->CastSpell(pCaster,SPELL_KODO_KOMBO_PLAYER_BUFF,true);

            pCreatureTarget->UpdateEntry(NPC_TAMED_KODO);
            pCreatureTarget->CastSpell(pCreatureTarget,SPELL_KODO_KOMBO_DESPAWN_BUFF,false);

            if (pCreatureTarget->GetMotionMaster()->GetCurrentMovementGeneratorType() == WAYPOINT_MOTION_TYPE)
                pCreatureTarget->GetMotionMaster()->MoveIdle();

            pCreatureTarget->GetMotionMaster()->MoveFollow(pCaster, PET_FOLLOW_DIST,  pCreatureTarget->GetFollowAngle());
        }

        //always return true when we are handling this spell and effect
        return true;
    }

    return false;
}

bool GossipHello_npc_aged_dying_ancient_kodo(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->HasAuraEffect(SPELL_KODO_KOMBO_PLAYER_BUFF,0) && pCreature->HasAuraEffect(SPELL_KODO_KOMBO_DESPAWN_BUFF,0))
    {    
        pPlayer->RemoveAurasDueToSpell(SPELL_KODO_KOMBO_PLAYER_BUFF);
        pPlayer->CastSpell(pCreature,SPELL_KODO_KOMBO_GOSSIP,true);

        pCreature->RemoveAurasDueToSpell(SPELL_KODO_KOMBO_DESPAWN_BUFF);
        pCreature->GetMotionMaster()->MoveIdle();    

        pPlayer->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_KODO_HOME, pCreature->GetGUID());
        
        return true;
    }

    return false;
}

CreatureAI* GetAI_npc_aged_dying_ancient_kodo(Creature* pCreature)
{
    return new npc_aged_dying_ancient_kodoAI(pCreature);
}

/*######
## npc_dalinda_malem.
######*/

#define QUEST_RETURN_TO_VAHLARRIEL     1440

struct npc_dalindaAI : public npc_escortAI
{
    npc_dalindaAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        completed = false;
    }   
        
    bool completed;    
    
    void WaypointReached(uint32 i)
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
        npc_escortAI::UpdateAI(uiDiff);

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_dalinda(Creature* creature)
{
    return new npc_dalindaAI(creature);
}

bool QuestAccept_npc_dalinda(Player* player, Creature* creature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_RETURN_TO_VAHLARRIEL)
   {        
        if (npc_escortAI* pEscortAI = CAST_AI(npc_dalindaAI, creature->AI()))
        {
            pEscortAI->Start(true, true, false, player->GetGUID(), creature->GetEntry());
            creature->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    }
    return true;
}

struct npc_melizzaAI : public npc_escortAI
{
    npc_melizzaAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        completed = false;
    }   
        
    bool completed;    
    
    void WaypointReached(uint32 i)
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
        npc_escortAI::UpdateAI(uiDiff);

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_melizza(Creature* c)
{
    return new npc_melizzaAI(c);
}

bool QuestAccept_npc_melizza(Player* player, Creature* creature, Quest const* quest)
{
    if (quest->GetQuestId() == 6132)
   {        
        if (npc_escortAI* pEscortAI = CAST_AI(npc_melizzaAI, creature->AI()))
        {
            pEscortAI->Start(true, true, false, player->GetGUID(), creature->GetEntry());
            creature->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    }
    return true;
}

void AddSC_desolace()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name = "npc_aged_dying_ancient_kodo";
    newscript->GetAI = &GetAI_npc_aged_dying_ancient_kodo;
    newscript->OnEffectDummyCreature = &EffectDummyCreature_npc_aged_dying_ancient_kodo;
    newscript->OnGossipHello = &GossipHello_npc_aged_dying_ancient_kodo;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_dalinda";
    newscript->GetAI = &GetAI_npc_dalinda;
    newscript->OnQuestAccept = &QuestAccept_npc_dalinda;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_melizza";
    newscript->GetAI = &GetAI_npc_melizza;
    newscript->OnQuestAccept = &QuestAccept_npc_melizza;
    sScriptMgr->RegisterOLDScript(newscript);

}
