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
SDName: Thousand Needles
SD%Complete: 100
SDComment: Support for Quest: 1950, 4770, 4904, 4966, 5151.
SDCategory: Thousand Needles
EndScriptData */

/* ContentData
npc_swiftmountain
npc_plucky
go_panther_cage
npc_enraged_panther
npc_kanati
npc_lakota_windsong
EndContentData */


#include "EscortAI.h"

/*######
## npc_swiftmountain
######*/

#define SAY_START                 -1000147
#define SAY_WYVERN                 -1000148
#define SAY_COMPLETE             -1000149

#define QUEST_HOMEWARD_BOUND     4770
#define ENTRY_WYVERN             4107


class npc_swiftmountain : public CreatureScript
{
public:
    npc_swiftmountain() : CreatureScript("npc_swiftmountain")
    { }

    class npc_swiftmountainAI : public EscortAI
    {
        public:
    npc_swiftmountainAI(Creature *c) : EscortAI(c) {}
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* player = GetPlayerForEscort();
    
            if (!player)
                return;
    
            switch (i)
            {
            case 15:
                DoScriptText(SAY_WYVERN, me, player);
                me->SummonCreature(ENTRY_WYVERN, -5016.45, -935.01, -5.46, 5.36,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                me->SummonCreature(ENTRY_WYVERN, -5001.98, -934.96, -5.55, 3.18,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                me->SummonCreature(ENTRY_WYVERN, -4999.06, -949.61, -5.42, 2.04,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                break;
            case 26:
                DoScriptText(SAY_COMPLETE, me);
                break;
            case 27:
                player->GroupEventHappens(QUEST_HOMEWARD_BOUND,me);
                break;
            }
        }
    
        void Reset()
        override {
            me->SetFaction(104);
        }
    
        void JustEngagedWith(Unit* who)override {}
    
        void JustSummoned(Creature* summoned)
        override {
            summoned->AI()->AttackStart(me);
        }
    
        void JustDied(Unit* /*killer*/)
        override {
            if (_playerGUID)
            {
                if (Player* player = GetPlayerForEscort())
                    player->FailQuest(QUEST_HOMEWARD_BOUND);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            EscortAI::UpdateAI(diff);
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_HOMEWARD_BOUND)
            {
                ((EscortAI*)(me->AI()))->Start(true, false, player->GetGUID(), quest);
                DoScriptText(SAY_START, me, player);
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_swiftmountainAI(creature);
    }
};



/*######
## npc_plucky
######*/

#define GOSSIP_P    "<Learn Secret phrase>"

#define SPELL_TRANSFORM_HUMAN 9192
#define QUEST_GET_THE_SCOOP 1950


class npc_plucky : public CreatureScript
{
public:
    npc_plucky() : CreatureScript("npc_plucky")
    { }

    class npc_pluckyAI : public ScriptedAI
    {
        public:
        npc_pluckyAI(Creature *c) : ScriptedAI(c) {}
    
        bool Transformed;
        bool Chicken;
    
        uint32 Timer;
        uint32 ChickenTimer;
    
        void Reset()   override {
    
           Transformed = false;
           Chicken     = false;
           me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
           Timer        = 0;
           ChickenTimer = 0;
           }
    
        void JustEngagedWith(Unit *who)override {}
    
        void TransformHuman(uint32 emoteid)
        {
             if (!Transformed)
             {
                 Transformed = true;
                 DoCast(me, SPELL_TRANSFORM_HUMAN);
                 Timer = 120000;
                 if (emoteid == TEXTEMOTE_BECKON)
                     me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                 else
                 {
                     ChickenTimer = 1500;
                     Chicken = true;
                 }
             }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (Transformed)
            {
                if (Timer < diff)
                    Reset();
                else Timer-=diff;
            }
    
            if(Chicken)
            {
                if (ChickenTimer < diff)
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                    Chicken = false;
                }else ChickenTimer-=diff;
            }
    
            if(!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
       }

        virtual void ReceiveEmote(Player* player, uint32 emote) override
        {
            if( (emote == TEXTEMOTE_BECKON || emote == TEXTEMOTE_CHICKEN) &&
                player->GetQuestStatus(QUEST_GET_THE_SCOOP) == QUEST_STATUS_INCOMPLETE )
            {
                me->SetInFront(player);
                ((npc_plucky::npc_pluckyAI*)(me->ToCreature())->AI())->TransformHuman(emote);
            }
        }


        virtual bool GossipHello(Player* player) override
        {
            if(player->GetQuestStatus(QUEST_GET_THE_SCOOP) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_P, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU_TEXTID(738, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch( action )
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->CLOSE_GOSSIP_MENU();
                    player->CompleteQuest(QUEST_GET_THE_SCOOP);
                break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_pluckyAI(creature);
    }
};





class PantherCage : public GameObjectScript
{
public:
    PantherCage() : GameObjectScript("go_panther_cage")
    {}

    enum ePantherCage
    {
        ENRAGED_PANTHER = 10992
    };

    struct PantherCageAI : public GameObjectAI
    {
        PantherCageAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(5151) == QUEST_STATUS_INCOMPLETE) {
                if (Creature* panther = me->FindNearestCreature(ENRAGED_PANTHER, 5.0f, true)) {
                    panther->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    panther->SetReactState(REACT_AGGRESSIVE);
                    panther->AI()->AttackStart(pPlayer);
                }
            }

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new PantherCageAI(go);
    }
};

/*######
## npc_enraged_panther
######*/


class npc_enraged_panther : public CreatureScript
{
public:
    npc_enraged_panther() : CreatureScript("npc_enraged_panther")
    { }

    class npc_enraged_pantherAI : public ScriptedAI
    {
        public:
        npc_enraged_pantherAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetReactState(REACT_PASSIVE);
        }
    
        void JustEngagedWith(Unit* who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_enraged_pantherAI(creature);
    }
};


/*#####
# npc_kanati
######*/

enum eKanati
{
    SAY_KAN_START              = -1600410,

    QUEST_PROTECT_KANATI        = 4966,
    NPC_GALAK_ASS               = 10720
};

const float m_afGalakLoc[] = { -4867.387695f, -1357.353760f, -48.226f };


class npc_kanati : public CreatureScript
{
public:
    npc_kanati() : CreatureScript("npc_kanati")
    { }

    class npc_kanatiAI : public EscortAI
    {
        public:
        npc_kanatiAI(Creature* pCreature) : EscortAI(pCreature) { }
    
        void Reset() override {}
        
        void JustEngagedWith(Unit *pWho) override {}
    
        void WaypointReached(uint32 uiPointId, uint32 pathID)
        override {
            switch(uiPointId)
            {
                case 0:
                    DoScriptText(SAY_KAN_START, me);
                    DoSpawnGalak();
                    break;
                case 1:
                    if (Player* pPlayer = GetPlayerForEscort())
                        pPlayer->GroupEventHappens(QUEST_PROTECT_KANATI, me);
                    break;
            }
        }
    
        void DoSpawnGalak()
        {
            for (int i = 0; i < 3; ++i)
                me->SummonCreature(NPC_GALAK_ASS,
                m_afGalakLoc[0], m_afGalakLoc[1], m_afGalakLoc[2], 0.0f,
                TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
        }
    
        void JustSummoned(Creature* pSummoned)
        override {
            pSummoned->AI()->AttackStart(me);
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_PROTECT_KANATI)
                ((EscortAI*)(me->AI()))->Start(false, false, pPlayer->GetGUID(), quest);
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kanatiAI(creature);
    }
};



/*######
# npc_lakota_windsong
######*/

enum eLakota
{
    SAY_LAKO_START              = -1600365,
    SAY_LAKO_LOOK_OUT           = -1600366,
    SAY_LAKO_HERE_COME          = -1600367,
    SAY_LAKO_MORE               = -1600368,
    SAY_LAKO_END                = -1600369,

    QUEST_FREE_AT_LAST          = 4904,
    NPC_GRIM_BANDIT             = 10758,
    FACTION_ESCORTEE_LAKO       = 232,                      //guessed

    ID_AMBUSH_1                 = 0,
    ID_AMBUSH_2                 = 2,
    ID_AMBUSH_3                 = 4
};

float m_afBanditLoc[6][6]=
{
    {-4905.479492f, -2062.732666f, 84.352f},
    {-4915.201172f, -2073.528320f, 84.733f},
    {-4878.883301f, -1986.947876f, 91.966f},
    {-4877.503906f, -1966.113403f, 91.859f},
    {-4767.985352f, -1873.169189f, 90.192f},
    {-4788.861328f, -1888.007813f, 89.888f}
};


class npc_lakota_windsong : public CreatureScript
{
public:
    npc_lakota_windsong() : CreatureScript("npc_lakota_windsong")
    { }

    class npc_lakota_windsongAI : public EscortAI
    {
        public:
        npc_lakota_windsongAI(Creature* pCreature) : EscortAI(pCreature) {}
    
        void Reset() override {}
        
        void JustEngagedWith(Unit *pWho) override {}
    
        void WaypointReached(uint32 uiPointId, uint32 pathID)
        override {
            switch(uiPointId)
            {
                case 8:
                    DoScriptText(SAY_LAKO_LOOK_OUT, me);
                    DoSpawnBandits(ID_AMBUSH_1);
                    break;
                case 14:
                    DoScriptText(SAY_LAKO_HERE_COME, me);
                    DoSpawnBandits(ID_AMBUSH_2);
                    break;
                case 21:
                    DoScriptText(SAY_LAKO_MORE, me);
                    DoSpawnBandits(ID_AMBUSH_3);
                    break;
                case 45:
                    if (Player* pPlayer = GetPlayerForEscort())
                        pPlayer->GroupEventHappens(QUEST_FREE_AT_LAST, me);
                    break;
            }
        }
    
        void DoSpawnBandits(int uiAmbushId)
        {
            for (int i = 0; i < 2; ++i)
                me->SummonCreature(NPC_GRIM_BANDIT,
                m_afBanditLoc[i+uiAmbushId][0], m_afBanditLoc[i+uiAmbushId][1], m_afBanditLoc[i+uiAmbushId][2], 0.0f,
                TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_FREE_AT_LAST)
            {
                DoScriptText(SAY_LAKO_START, me, pPlayer);
                me->SetFaction(FACTION_ESCORTEE_LAKO);

                ((EscortAI*)(me->AI()))->Start(false, false, pPlayer->GetGUID(), quest);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lakota_windsongAI(creature);
    }
};



/*######
## AddSC
######*/

void AddSC_thousand_needles()
{

    new npc_swiftmountain();

    new npc_plucky();
    
    new PantherCage();
    
    new npc_enraged_panther();
    
    new npc_kanati();

    new npc_lakota_windsong();
}
