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
SDName: Stonetalon_Mountains
SD%Complete: 95
SDComment: Quest support: 6627, 6523
SDCategory: Stonetalon Mountains
EndScriptData */

/* ContentData
npc_braug_dimspirit
npc_kaya_flathoof
EndContentData */


#include "EscortAI.h"

/*######
## npc_braug_dimspirit
######*/

#define GOSSIP_HBD1 "Ysera"
#define GOSSIP_HBD2 "Neltharion"
#define GOSSIP_HBD3 "Nozdormu"
#define GOSSIP_HBD4 "Alexstrasza"
#define GOSSIP_HBD5 "Malygos"

bool GossipHello_npc_braug_dimspirit(Player *player, Creature *_Creature)
{
    if (_Creature->IsQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );

    if (player->GetQuestStatus(6627) == QUEST_STATUS_INCOMPLETE)
    {
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        player->SEND_GOSSIP_MENU_TEXTID(5820, _Creature->GetGUID());
    }
    else
        player->SEND_GOSSIP_MENU_TEXTID(5819, _Creature->GetGUID());

    return true;
}

bool GossipSelect_npc_braug_dimspirit(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        player->CLOSE_GOSSIP_MENU();
        _Creature->CastSpell(player,6766,false);

    }
    if (action == GOSSIP_ACTION_INFO_DEF+2)
    {
        player->CLOSE_GOSSIP_MENU();
        player->AreaExploredOrEventHappens(6627);
    }
    return true;
}

/*######
## npc_kaya_flathoof
######*/

#define SAY_START   -1000347
#define SAY_AMBUSH  -1000348
#define SAY_END     -1000349

#define QUEST_PK    6523
#define MOB_GB      11912
#define MOB_GR      11910
#define MOB_GS      11913

struct npc_kaya_flathoofAI : public npc_escortAI
{
    npc_kaya_flathoofAI(Creature* c) : npc_escortAI(c) {}

    void WaypointReached(uint32 i)
    override {
        Player* player = GetPlayerForEscort();

        if(!player)
            return;

        switch(i)
        {
        case 16:
            DoScriptText(SAY_AMBUSH, me);
            me->SummonCreature(MOB_GB, -48.53, -503.34, -46.31, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
            me->SummonCreature(MOB_GR, -38.85, -503.77, -45.90, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
            me->SummonCreature(MOB_GS, -36.37, -496.23, -45.71, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
            break;
        case 18: me->SetInFront(player);
            DoScriptText(SAY_END, me, player);
            player->GroupEventHappens(QUEST_PK, me);
            break;
        }
    }

    void JustSummoned(Creature* summoned)
    override {
        summoned->AI()->AttackStart(me);
    }

    void Reset()override {}

    void EnterCombat(Unit* who)override {}

    void JustDied(Unit* killer)
    override {
        if (PlayerGUID)
        {
            Player* player = GetPlayerForEscort();
            if (player)
                player->FailQuest(QUEST_PK);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        npc_escortAI::UpdateAI(diff);
    }
};

bool QuestAccept_npc_kaya_flathoof(Player* player, Creature* creature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_PK)
    {
        ((npc_escortAI*)(creature->AI()))->Start(true, true, false, player->GetGUID(), creature->GetEntry());
        DoScriptText(SAY_START, creature);
        creature->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
        creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
    }
    return true;
}

CreatureAI* GetAI_npc_kaya_flathoofAI(Creature *pCreature)
{
    return new npc_kaya_flathoofAI(pCreature);
}

/*######
# npc_piznik
######*/

float spawns[3][4] = {
    {941.866272f, -255.601471f, -2.403625f, 6.070902f},
    {942.277771f, -253.692307f, -2.335533f, 6.070902f},
    {942.529968f, -252.522171f, -2.293756f, 6.070902f}};

struct npc_piznikAI : public ScriptedAI
{
    npc_piznikAI(Creature* c) : ScriptedAI(c) {}
    
    uint8 count;
    uint64 pGUID;
    
    void EnterCombat(Unit* who) override {}
    
    void Start(uint64 guid)
    {
        count = 0;
        pGUID = guid;
        for (auto & spawn : spawns) {
            if (Creature* summon = me->SummonCreature(3999, spawn[0], spawn[1], spawn[2], spawn[3], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000))
               summon->AI()->AttackStart(me);
        }
    }
    
    void SummonedCreatureDespawn(Creature* creature)
    override {
        if (creature->GetEntry() == 3999)
            ++count;
        else
            return;
        
        if (count == 3) {
            if (Player* player = ObjectAccessor::GetPlayer(*me, pGUID)) {
                player->AreaExploredOrEventHappens(1090);
                player->AreaExploredOrEventHappens(1092);
            }
        }
    }
};

bool QuestAccept_npc_piznik(Player* player, Creature* creature, Quest const* quest)
{
    if (quest->GetQuestId() == 1090 || quest->GetQuestId() == 1092)
        ((npc_piznikAI*)(creature->AI()))->Start(player->GetGUID());

    return true;
}

CreatureAI* GetAI_npc_piznik(Creature *pCreature)
{
    return new npc_piznikAI(pCreature);
}

/*######
## AddSC
######*/

void AddSC_stonetalon_mountains()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="npc_braug_dimspirit";
    newscript->OnGossipHello = &GossipHello_npc_braug_dimspirit;
    newscript->OnGossipSelect = &GossipSelect_npc_braug_dimspirit;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_kaya_flathoof";
    newscript->GetAI = &GetAI_npc_kaya_flathoofAI;
    newscript->OnQuestAccept = &QuestAccept_npc_kaya_flathoof;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name="npc_piznik";
    newscript->GetAI = &GetAI_npc_piznik;
    newscript->OnQuestAccept = &QuestAccept_npc_piznik;
    sScriptMgr->RegisterOLDScript(newscript);
}

