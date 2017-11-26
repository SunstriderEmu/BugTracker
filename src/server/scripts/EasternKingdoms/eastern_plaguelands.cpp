/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Eastern_Plaguelands
SD%Complete: 100
SDComment: Quest support: 5211, 5742, 9446. Special vendor Augustus the Touched
SDCategory: Eastern Plaguelands
EndScriptData */

/* ContentData
mobs_ghoul_flayer
npc_augustus_the_touched
npc_darrowshire_spirit
npc_tirion_fordring
npc_anchorite_truuen
EndContentData */


#include "EscortAI.h"

//id8530 - cannibal ghoul
//id8531 - gibbering ghoul
//id8532 - diseased flayer


class mobs_ghoul_flayer : public CreatureScript
{
public:
    mobs_ghoul_flayer() : CreatureScript("mobs_ghoul_flayer")
    { }

    class mobs_ghoul_flayerAI : public ScriptedAI
    {
        public:
        mobs_ghoul_flayerAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset() override { }
    
        void EnterCombat(Unit* pWho) override { }
    
        void JustDied(Unit* pKiller)
        override {
            if (pKiller->GetTypeId() == TYPEID_PLAYER)
                DoSpawnCreature(11064, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mobs_ghoul_flayerAI(creature);
    }
};


/*######
## npc_augustus_the_touched
######*/

class npc_augustus_the_touched : public CreatureScript
{
public:
    npc_augustus_the_touched() : CreatureScript("npc_augustus_the_touched")
    { }

    class npc_augustus_the_touchedAI : public ScriptedAI
    {
    public:
        npc_augustus_the_touchedAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (me->IsVendor() && pPlayer->GetQuestRewardStatus(6164))
                pPlayer->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if (action == GOSSIP_ACTION_TRADE)
                player->SEND_VENDORLIST(me->GetGUID());
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_augustus_the_touchedAI(creature);
    }
};



/*######
## npc_darrowshire_spirit
######*/

#define SPELL_SPIRIT_SPAWNIN    17321

class npc_darrowshire_spirit : public CreatureScript
{
public:
    npc_darrowshire_spirit() : CreatureScript("npc_darrowshire_spirit")
    { }

    class npc_darrowshire_spiritAI : public ScriptedAI
    {
        public:
        npc_darrowshire_spiritAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
            DoCast(me,SPELL_SPIRIT_SPAWNIN);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
    
        void EnterCombat(Unit* pWho) override { }
    

        virtual bool GossipHello(Player* pPlayer) override
        {
            pPlayer->SEND_GOSSIP_MENU_TEXTID(3873, me->GetGUID());
            pPlayer->TalkedToCreature(me->GetEntry(), me->GetGUID());
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_darrowshire_spiritAI(creature);
    }
};



/*######
## npc_tirion_fordring
######*/

class npc_tirion_fordring : public CreatureScript
{
public:
    npc_tirion_fordring() : CreatureScript("npc_tirion_fordring")
    { }

    class npc_tirion_fordringAI : public ScriptedAI
    {
    public:
        npc_tirion_fordringAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (pPlayer->GetQuestStatus(5742) == QUEST_STATUS_INCOMPLETE && pPlayer->GetStandState() == PLAYER_STATE_SIT )
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I am ready to hear your tale, Tirion.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Thank you, Tirion.  What of your identity?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(4493, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "That is terrible.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU_TEXTID(4494, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I will, Tirion.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->SEND_GOSSIP_MENU_TEXTID(4495, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+4:
                    player->CLOSE_GOSSIP_MENU();
                    player->AreaExploredOrEventHappens(5742);
                    break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_tirion_fordringAI(creature);
    }
};



/*######
##  npc_anchorite_truuen
######*/

enum eTruuen
{
    SAY_WP_0                    = -1000709,
    SAY_WP_1                    = -1000710,
    SAY_WP_2                    = -1000711,
    SAY_WP_3                    = -1000712,
    SAY_WP_4                    = -1000713,
    SAY_WP_5                    = -1000714,
    SAY_WP_6                    = -1000715,

    NPC_GHOST_UTHER             = 17233,
    NPC_THEL_DANIS              = 1854,
    NPC_GHOUL                   = 1791,

    QUEST_TOMB_LIGHTBRINGER     = 9446
};


class npc_anchorite_truuen : public CreatureScript
{
public:
    npc_anchorite_truuen() : CreatureScript("npc_anchorite_truuen")
    { }

    class npc_anchorite_truuenAI : public npc_escortAI
    {    
        public:
        npc_anchorite_truuenAI(Creature* pCreature) : npc_escortAI(pCreature) { }
    
        uint32 EventTimer;
        uint64 UterGUID;
        uint32 uiPhase;
    
        void Reset()
        override {        
            EventTimer = 5000;
            UterGUID = 0;
            uiPhase = 0;
        }
        
        void EnterCombat(Unit *pWho) override {}
        
        void WaypointReached(uint32 uiPointId, uint32 pathID)
        override {
            Player* pPlayer = GetPlayerForEscort();
    
            if (!pPlayer)
                return;
    
            switch (uiPointId)
            {
            case 8:
                DoScriptText(SAY_WP_0, me);
                for (int i = 0; i < 2; i++)
                    me->SummonCreature(NPC_GHOUL, 1035.43,-1572.97,61.5412, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 90000);
                break;
            case 9:
                DoScriptText(SAY_WP_1, me);
                break;
            case 14:
                for (int i = 0; i < 4; i++)
                    me->SummonCreature(NPC_GHOUL, 1159.77,-1762.64,60.5699, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                break;
            case 15:
                DoScriptText(SAY_WP_2, me);
                SetRun(false);
                break;
            case 22:
                if (Creature* pTheldanis = me->FindNearestCreature(NPC_THEL_DANIS, 50))
                    DoScriptText(SAY_WP_3, pTheldanis);
                break;
            case 23:
                if (Creature* pUter = me->SummonCreature(NPC_GHOST_UTHER, 971.86,-1825.42 ,81.99 , 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 10000))
                {
                    pUter->AddUnitMovementFlag(MOVEMENTFLAG_DISABLE_GRAVITY);
                    DoScriptText(SAY_WP_4, pUter, me);
                    UterGUID = pUter->GetGUID();
                    uiPhase = 1;
                    me->SetStandState(UNIT_STAND_STATE_KNEEL);
                    SetEscortPaused(true);
                }
                pPlayer->GroupEventHappens(QUEST_TOMB_LIGHTBRINGER, me);
                break;
            }
        }
    
        void UpdateAI(const uint32 uiDiff)
        override {
            npc_escortAI::UpdateAI(uiDiff);
    
            if (!UpdateVictim())
            {
                if (HasEscortState(STATE_ESCORT_PAUSED) && uiPhase)
                {
                    if (EventTimer <= uiDiff)
                    {
                        EventTimer = 5000;
    
                        if (Creature* pUter = ObjectAccessor::GetCreature(*me, UterGUID))
                        {
                            switch(uiPhase)
                            {
                            case 1:
                                DoScriptText(SAY_WP_5, pUter, me);
                                me->SetStandState(UNIT_STAND_STATE_STAND);
                                ++uiPhase;
                                break;
                            case 2:
                                DoScriptText(SAY_WP_6, pUter, me);
                                ++uiPhase = 0;
                                break;
                            case 3:
                                me->ForcedDespawn();
                                pUter->ForcedDespawn();
                                break;
                            }
                        }
                    }
                    else
                        EventTimer -= uiDiff;
                }
                return;
            }
    
            DoMeleeAttackIfReady();
        }
    
        void JustSummoned(Creature* pSummoned)
        override {
            if (pSummoned->GetEntry() == NPC_GHOUL)
                pSummoned->AI()->AttackStart(me);
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if (pQuest->GetQuestId() == QUEST_TOMB_LIGHTBRINGER)
            {
                if (npc_anchorite_truuenAI* pEscortAI = CAST_AI(npc_anchorite_truuen::npc_anchorite_truuenAI, me->AI()))
                {
                    pEscortAI->Start(true, true, false, pPlayer->GetGUID(), me->GetEntry());
                    pEscortAI->SetDespawnAtEnd(false);
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_anchorite_truuenAI(creature);
    }
};



void AddSC_eastern_plaguelands()
{

    new mobs_ghoul_flayer();

    new npc_augustus_the_touched();

    new npc_darrowshire_spirit();

    new npc_tirion_fordring();
    
    new npc_anchorite_truuen();
}

