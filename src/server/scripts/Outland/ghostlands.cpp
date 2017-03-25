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
SDName: Ghostlands
SD%Complete: 100
SDComment: Quest support: 9692, 9212. Obtain Budd's Guise of Zul'aman. Vendor Rathis Tomber
SDCategory: Ghostlands
EndScriptData */

/* ContentData
npc_blood_knight_dawnstar
npc_budd_nedreck
npc_rathis_tomber
npc_ranger_lilatha
EndContentData */


#include "EscortAI.h"

/*######
## npc_blood_knight_dawnstar
######*/

#define GOSSIP_H_BKD "Take Blood Knight Insignia"

bool GossipHello_npc_blood_knight_dawnstar(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(9692) == QUEST_STATUS_INCOMPLETE && !pPlayer->HasItemCount(24226,1,true))
        pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_H_BKD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);

    return true;
}

bool GossipSelect_npc_blood_knight_dawnstar(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        ItemPosCountVec dest;
        uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 24226, 1);
        if (msg == EQUIP_ERR_OK)
        {
            pPlayer->StoreNewItem( dest, 24226, 1, true);
            pPlayer->PlayerTalkClass->ClearMenus();
        }
    }
    return true;
}

/*######
## npc_budd_nedreck
######*/

#define GOSSIP_HBN "You gave the crew disguises?"

bool GossipHello_npc_budd_nedreck(Player* pPlayer, Creature* pCreature)
{
    if( pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu( pCreature->GetGUID() );

    if( pPlayer->GetQuestStatus(11166) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HBN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
    return true;
}

bool GossipSelect_npc_budd_nedreck(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action )
{
    if( action == GOSSIP_ACTION_INFO_DEF )
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->CastSpell(pPlayer, 42540, false);
    }
    return true;
}

/*######
## npc_rathis_tomber
######*/

bool GossipHello_npc_rathis_tomber(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->IsVendor() && pPlayer->GetQuestRewardStatus(9152))
    {
        pPlayer->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
        pPlayer->SEND_GOSSIP_MENU_TEXTID(8432, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU_TEXTID(8431,pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_rathis_tomber(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action )
{
    if (action == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
        
    return true;
}

class GildedBrazier : public GameObjectScript
{
public:
    GildedBrazier() : GameObjectScript("go_gilded_brazier")
    {}

    bool OnGossipHello(Player* pPlayer, GameObject* _GO) override
    {
        if (pPlayer->GetQuestStatus(9678) == QUEST_STATUS_INCOMPLETE)
        {
            Creature *Stillblade = pPlayer->SummonCreature(17716, 8106.11, -7542.06, 151.775, 3.02598, TEMPSUMMON_DEAD_DESPAWN, 60000);
            if (Stillblade)
                CAST_AI(CreatureAI, (Stillblade->AI()))->AttackStart(pPlayer);
        }

        return true;
    }
};

/*######
## npc_ranger_lilatha
######*/

enum eLilatha
{
SAY_START                           = -1000140,
SAY_PROGRESS1                       = -1000141,
SAY_PROGRESS2                       = -1000142,
SAY_PROGRESS3                       = -1000143,
SAY_END1                            = -1000144,
SAY_END2                            = -1000145,
SAY_CAPTAIN_ANSWER                  = -1000146,

QUEST_ESCAPE_FROM_THE_CATACOMBS     = 9212,
GO_CAGE                             = 181152,
NPC_CAPTAIN_HELIOS                  = 16220
};

struct npc_ranger_lilathaAI : public npc_escortAI
{
    npc_ranger_lilathaAI(Creature *c) : npc_escortAI(c) {}

    std::list<GameObject*> CageList;

    void WaypointReached(uint32 i)
    override {
        Player* player = GetPlayerForEscort();

        if (!player)
            return;

        switch(i)
        {
        case 0:
            {
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            GameObject* Cage = FindGameObject(GO_CAGE, 20, me);
            if(Cage)
                Cage->UseDoorOrButton();
            DoScriptText(SAY_START, me, player);
            break;
            }
        case 5:
            DoScriptText(SAY_PROGRESS1, me, player);
        case 11:
            DoScriptText(SAY_PROGRESS2, me, player);
            me->SetOrientation(4.762841);
            break;
        case 18:
            {
            DoScriptText(SAY_PROGRESS3, me, player);
            Creature* Summ1 = me->SummonCreature(16342, 7627.083984, -7532.538086, 152.128616, 1.082733, TEMPSUMMON_DEAD_DESPAWN, 0);
            Creature* Summ2 = me->SummonCreature(16343, 7620.432129, -7532.550293, 152.454865, 0.827478, TEMPSUMMON_DEAD_DESPAWN, 0);
            if(Summ1 && Summ2)
            {
                Summ1->Attack(me, true);
                Summ2->Attack(player, true);
            }
            me->AI()->AttackStart(Summ1);
            break;
            }
        case 19: me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING); break;
        case 25: me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING); break;
        case 30:
            player->GroupEventHappens(QUEST_ESCAPE_FROM_THE_CATACOMBS,me);
            break;
        case 32:
            me->SetOrientation(2.978281);
            DoScriptText(SAY_END1, me, player);
            break;
        case 33:
            me->SetOrientation(5.858011);
            DoScriptText(SAY_END2, me, player);
            Unit* CaptainHelios = FindCreature(NPC_CAPTAIN_HELIOS, 50, me);
            if(CaptainHelios)
            DoScriptText(SAY_CAPTAIN_ANSWER, CaptainHelios, player);
            break;
        }
    }

    void EnterCombat(Unit* who) override {}

    void Reset()
    override {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
            me->SetFaction(1602);

        GameObject* Cage = FindGameObject(GO_CAGE, 20, me);
        if (Cage)
            Cage->ResetDoorOrButton();
    }

    void JustDied(Unit* killer)
    override {
        if (PlayerGUID)
        {
            Player* player = GetPlayerForEscort();
            if (player)
                player->FailQuest(QUEST_ESCAPE_FROM_THE_CATACOMBS);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        npc_escortAI::UpdateAI(diff);
    }
};

bool QuestAccept_npc_ranger_lilatha(Player* player, Creature* creature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_ESCAPE_FROM_THE_CATACOMBS)
    {
        creature->SetFaction(113);
        ((npc_escortAI*)(creature->AI()))->Start(true, true, false, player->GetGUID(), creature->GetEntry());
    }
    return true;
}

CreatureAI* GetAI_npc_ranger_lilathaAI(Creature *pCreature)
{
    return new npc_ranger_lilathaAI(pCreature);
}

void AddSC_ghostlands()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="npc_blood_knight_dawnstar";
    newscript->OnGossipHello = &GossipHello_npc_blood_knight_dawnstar;
    newscript->OnGossipSelect = &GossipSelect_npc_blood_knight_dawnstar;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_budd_nedreck";
    newscript->OnGossipHello = &GossipHello_npc_budd_nedreck;
    newscript->OnGossipSelect = &GossipSelect_npc_budd_nedreck;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_rathis_tomber";
    newscript->OnGossipHello = &GossipHello_npc_rathis_tomber;
    newscript->OnGossipSelect = &GossipSelect_npc_rathis_tomber;
    sScriptMgr->RegisterOLDScript(newscript);

    new GildedBrazier();

    newscript = new OLDScript;
    newscript->Name = "npc_ranger_lilatha";
    newscript->GetAI = &GetAI_npc_ranger_lilathaAI;
    newscript->OnQuestAccept = &QuestAccept_npc_ranger_lilatha;
    sScriptMgr->RegisterOLDScript(newscript);
}

