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
SDName: Wetlands
SD%Complete: 100
SDComment: Quest support: 1249
SDCategory: Wetlands
EndScriptData */

/* ContentData
npc_mikhail
npc_tapoke_slim_jahn
EndContentData */


#include "EscortAI.h"

/*######
## npc_tapoke_slim_jahn
######*/

enum eTapokeSlim
{
    QUEST_MISSING_DIPLO_PT11    = 1249,
    SPELL_STEALTH               = 1785,
    SPELL_CALL_FRIENDS          = 16457,                    //summons 1x friend
    NPC_SLIMS_FRIEND            = 4971,
    NPC_TAPOKE_SLIM_JAHN        = 4962
};


class npc_tapoke_slim_jahn : public CreatureScript
{
public:
    npc_tapoke_slim_jahn() : CreatureScript("npc_tapoke_slim_jahn")
    { }

    class npc_tapoke_slim_jahnAI : public EscortAI
    {
        public:
        npc_tapoke_slim_jahnAI(Creature* pCreature) : EscortAI(pCreature) { }
    
        bool m_bFriendSummoned;
    
        void Reset()
        override {
            if (!HasEscortState(STATE_ESCORT_ESCORTING))
                m_bFriendSummoned = false;
        }
    
        void WaypointReached(uint32 uiPointId, uint32 pathID)
        override {
            switch(uiPointId)
            {
                case 2:
                    if (me->HasStealthAura())
                        me->RemoveAurasDueToSpell(SPELL_AURA_MOD_STEALTH);
    
                    SetRun();
                    me->SetFaction(FACTION_ENEMY);
                break;
            }
        }
    
        void EnterCombat(Unit* pWho)
        override {
            Player* pPlayer = GetPlayerForEscort();
    
            if (HasEscortState(STATE_ESCORT_ESCORTING) && !m_bFriendSummoned && pPlayer)
            {
                DoCast(me, SPELL_CALL_FRIENDS, true);
                DoCast(me, SPELL_CALL_FRIENDS, true);
                DoCast(me, SPELL_CALL_FRIENDS, true);
    
                m_bFriendSummoned = true;
            }
        }
    
        void JustSummoned(Creature* pSummoned)
        override {
            if (Player* pPlayer = GetPlayerForEscort())
                pSummoned->AI()->AttackStart(pPlayer);
        }
    
        void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
        override {
            if (me->GetHealth()*100 < me->GetMaxHealth()*20)
            {
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    if (pPlayer->GetTypeId() == TYPEID_PLAYER)
                        (pPlayer)->ToPlayer()->GroupEventHappens(QUEST_MISSING_DIPLO_PT11, me);
    
                    uiDamage = 0;
    
                    me->RestoreFaction();
                    me->RemoveAllAuras();
                    me->GetThreatManager().ClearAllThreat();
                    me->CombatStop(true);
    
                    //SetRun(false);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_tapoke_slim_jahnAI(creature);
    }
};


/*######
## npc_mikhail
######*/

class npc_mikhail : public CreatureScript
{
public:
    npc_mikhail() : CreatureScript("npc_mikhail")
    { }

    class npc_mikhailAI : public ScriptedAI
    {
    public:
        npc_mikhailAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_MISSING_DIPLO_PT11)
            {
                Creature* pSlim = me->FindNearestCreature(NPC_TAPOKE_SLIM_JAHN, 25.0f);

                if (!pSlim)
                    return;

                if (!pSlim->HasStealthAura())
                    pSlim->CastSpell(pSlim, SPELL_STEALTH, true);

                ((EscortAI*)(me->AI()))->Start(false, false, pPlayer->GetGUID(), quest);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mikhailAI(creature);
    }
};


/*######
## AddSC
######*/

void AddSC_wetlands()
{

    new npc_tapoke_slim_jahn();

    new npc_mikhail();
}
