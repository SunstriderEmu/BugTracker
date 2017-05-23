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

struct npc_swiftmountainAI : public npc_escortAI
{
npc_swiftmountainAI(Creature *c) : npc_escortAI(c) {}

    void WaypointReached(uint32 i)
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

    void EnterCombat(Unit* who)override {}

    void JustSummoned(Creature* summoned)
    override {
        summoned->AI()->AttackStart(me);
    }

    void JustDied(Unit* killer)
    override {
        if (PlayerGUID)
        {
            if (Player* player = GetPlayerForEscort())
                player->FailQuest(QUEST_HOMEWARD_BOUND);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        npc_escortAI::UpdateAI(diff);
    }
};

bool QuestAccept_npc_swiftmountain(Player* player, Creature* creature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_HOMEWARD_BOUND)
    {
        ((npc_escortAI*)(creature->AI()))->Start(true, true, false, player->GetGUID(), creature->GetEntry());
        DoScriptText(SAY_START, creature, player);
        creature->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
    }

    return true;
}

CreatureAI* GetAI_npc_swiftmountain(Creature *pCreature)
{
    return new npc_swiftmountainAI(pCreature);
}

/*######
## npc_plucky
######*/

#define GOSSIP_P    "<Learn Secret phrase>"

#define SPELL_TRANSFORM_HUMAN 9192
#define QUEST_GET_THE_SCOOP 1950

struct npc_pluckyAI : public ScriptedAI
{
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

    void EnterCombat(Unit *who)override {}

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
};

bool ReceiveEmote_npc_plucky( Player *player, Creature *_Creature, uint32 emote )
{
    if( (emote == TEXTEMOTE_BECKON || emote == TEXTEMOTE_CHICKEN) &&
        player->GetQuestStatus(QUEST_GET_THE_SCOOP) == QUEST_STATUS_INCOMPLETE )
    {
        _Creature->SetInFront(player);
        ((npc_pluckyAI*)(_Creature->ToCreature())->AI())->TransformHuman(emote);
    }

    return true;
}

bool GossipHello_npc_plucky(Player *player, Creature *_Creature)
{
    if(player->GetQuestStatus(QUEST_GET_THE_SCOOP) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_P, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    player->SEND_GOSSIP_MENU_TEXTID(738, _Creature->GetGUID());

    return true;
}

bool GossipSelect_npc_plucky(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    switch( action )
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->CLOSE_GOSSIP_MENU();
            player->CompleteQuest(QUEST_GET_THE_SCOOP);
        break;
    }
    return true;
}

CreatureAI* GetAI_npc_plucky(Creature *_Creature)
{
return new npc_pluckyAI(_Creature);
}

class PantherCage : public GameObjectScript
{
public:
    PantherCage() : GameObjectScript("go_panther_cage")
    {}

    enum ePantherCage
    {
        ENRAGED_PANTHER = 10992
    };

    bool OnGossipHello(Player* pPlayer, GameObject* pGo) override
    {
        if (pPlayer->GetQuestStatus(5151) == QUEST_STATUS_INCOMPLETE) {
            if (Creature* panther = pGo->FindNearestCreature(ENRAGED_PANTHER, 5.0f, true)) {
                panther->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                panther->SetReactState(REACT_AGGRESSIVE);
                panther->AI()->AttackStart(pPlayer);
            }
        }

        return true;
    }
};

/*######
## npc_enraged_panther
######*/

struct npc_enraged_pantherAI : public ScriptedAI
{
    npc_enraged_pantherAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    override {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        me->SetReactState(REACT_PASSIVE);
    }

    void EnterCombat(Unit* who) override {}

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_enraged_panther(Creature* pCreature)
{
    return new npc_enraged_pantherAI(pCreature);
}

/*#####
# npc_kanati
######*/

enum eKanati
{
    SAY_KAN_START              = -1600410,

    QUEST_PROTECT_KANATI        = 4966,
    NPC_GALAK_ASS               = 10720
};

const float m_afGalakLoc[] = { -4867.387695, -1357.353760, -48.226 };

struct npc_kanatiAI : public npc_escortAI
{
    npc_kanatiAI(Creature* pCreature) : npc_escortAI(pCreature) { }

    void Reset() override {}
    
    void EnterCombat(Unit *pWho) override {}

    void WaypointReached(uint32 uiPointId)
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
};

CreatureAI* GetAI_npc_kanati(Creature* pCreature)
{
    return new npc_kanatiAI(pCreature);
}

bool QuestAccept_npc_kanati(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_PROTECT_KANATI)
        ((npc_escortAI*)(pCreature->AI()))->Start(false, false, false, pPlayer->GetGUID(), pCreature->GetEntry());

    return true;
}

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
    {-4905.479492, -2062.732666, 84.352},
    {-4915.201172, -2073.528320, 84.733},
    {-4878.883301, -1986.947876, 91.966},
    {-4877.503906, -1966.113403, 91.859},
    {-4767.985352, -1873.169189, 90.192},
    {-4788.861328, -1888.007813, 89.888}
};

struct npc_lakota_windsongAI : public npc_escortAI
{
    npc_lakota_windsongAI(Creature* pCreature) : npc_escortAI(pCreature) {}

    void Reset() override {}
    
    void EnterCombat(Unit *pWho) override {}

    void WaypointReached(uint32 uiPointId)
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
};

CreatureAI* GetAI_npc_lakota_windsong(Creature* pCreature)
{
    return new npc_lakota_windsongAI(pCreature);
}

bool QuestAccept_npc_lakota_windsong(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_FREE_AT_LAST)
    {
        DoScriptText(SAY_LAKO_START, pCreature, pPlayer);
        pCreature->SetFaction(FACTION_ESCORTEE_LAKO);

        ((npc_escortAI*)(pCreature->AI()))->Start(false, false, false, pPlayer->GetGUID(), pCreature->GetEntry());
    }
    return true;
}

/*######
## AddSC
######*/

void AddSC_thousand_needles()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name = "npc_swiftmountain";
    newscript->GetAI = &GetAI_npc_swiftmountain;
    newscript->OnQuestAccept = &QuestAccept_npc_swiftmountain;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_plucky";
    newscript->GetAI = &GetAI_npc_plucky;
    newscript->OnReceiveEmote =  &ReceiveEmote_npc_plucky;
    newscript->OnGossipHello =   &GossipHello_npc_plucky;
    newscript->OnGossipSelect = &GossipSelect_npc_plucky;
    sScriptMgr->RegisterOLDScript(newscript);
    
    new PantherCage();
    
    newscript = new OLDScript;
    newscript->Name = "npc_enraged_panther";
    newscript->GetAI = &GetAI_npc_enraged_panther;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_kanati";
    newscript->GetAI = &GetAI_npc_kanati;
    newscript->OnQuestAccept = &QuestAccept_npc_kanati;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_lakota_windsong";
    newscript->GetAI = &GetAI_npc_lakota_windsong;
    newscript->OnQuestAccept = &QuestAccept_npc_lakota_windsong;
    sScriptMgr->RegisterOLDScript(newscript);
}
