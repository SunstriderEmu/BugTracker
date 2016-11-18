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
SDName: Hyjal
SD%Complete: 80
SDComment: 
SDCategory: Caverns of Time, Mount Hyjal
EndScriptData */

/* ContentData
npc_jaina_proudmoore
npc_thrall
npc_tyrande_whisperwind
EndContentData */


#include "hyjalAI.h"

#define GOSSIP_MENU_BEGIN_ALLY      403
#define GOSSIP_ITEM_BEGIN_ALLY      395 // "My companions and I are with you, Lady Proudmoore."
#define GOSSIP_MENU_BEGIN_ALLY_2    404
#define GOSSIP_MENU_ANATHERON       405
#define GOSSIP_ITEM_ANETHERON       396 // "We are ready for whatever Archimonde might send our way, Lady Proudmoore."
#define GOSSIP_MENU_ANATHERON2      406
#define GOSSIP_MENU_RETREAT_ALLY    407
#define GOSSIP_ITEM_RETREAT_ALLY    399 // "Until we meet again, Lady Proudmoore."

#define GOSSIP_MENU_BEGIN_HORDE     408
#define GOSSIP_ITEM_BEGIN_HORDE     397 // "I am with you, Thrall."
#define GOSSIP_MENU_BEGIN_HORDE2    409
#define GOSSIP_MENU_AZGALOR         410
#define GOSSIP_ITEM_AZGALOR         398 // "We have nothing to fear."
#define GOSSIP_MENU_AZGALOR2        411
#define GOSSIP_MENU_RETREAT_HORDE   412
#define GOSSIP_ITEM_RETREAT_HORDE   402 // "Until we meet again, Thrall."

#define GOSSIP_MENU_TYRANDE         413
#define GOSSIP_ITEM_TYRANDE         400 // "I would be grateful for any aid you can provide, Priestess."
#define GOSSIP_MENU_TYRANDE2        414
#define ITEM_TEAR_OF_GODDESS        24494


CreatureAI* GetAI_npc_jaina_proudmoore(Creature *_Creature)
{
    auto  ai = new hyjalAI(_Creature);

    ai->Reset();
    ai->EnterEvadeMode(CreatureAI::EvadeReason::EVADE_REASON_OTHER);

    ai->Spell[0].SpellId = SPELL_BLIZZARD;
    ai->Spell[0].Cooldown = 15000 + rand()%20000;
    ai->Spell[0].TargetType = TARGETTYPE_RANDOM;

    ai->Spell[1].SpellId = SPELL_PYROBLAST;
    ai->Spell[1].Cooldown = 5500 + rand()%4000;
    ai->Spell[1].TargetType = TARGETTYPE_RANDOM;

    ai->Spell[2].SpellId = SPELL_SUMMON_ELEMENTALS;
    ai->Spell[2].Cooldown = 45000;
    ai->Spell[2].TargetType = TARGETTYPE_SELF;

    return ai;
}

bool GossipHello_npc_jaina_proudmoore(Player *player, Creature *_Creature)
{
    hyjalAI* ai = ((hyjalAI*)_Creature->AI());
    if(ai->EventBegun)
        return false;

    uint32 RageEncounter = ai->GetInstanceScript(DATA_RAGEWINTERCHILLEVENT);
    uint32 AnetheronEncounter = ai->GetInstanceScript(DATA_ANETHERONEVENT);
    
    if(player->IsGameMaster()) {
        player->ADD_GOSSIP_ITEM(2, "[GM] Toggle Debug Timers", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spawn Archimonde", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    }

    if(RageEncounter == NOT_STARTED)
    {
        player->ADD_GOSSIP_ITEM_TEXTID( 0, GOSSIP_ITEM_BEGIN_ALLY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_BEGIN_ALLY, _Creature->GetGUID());
    } else if(RageEncounter == DONE && AnetheronEncounter == NOT_STARTED) {
        player->ADD_GOSSIP_ITEM_TEXTID( 0, GOSSIP_ITEM_ANETHERON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_ANATHERON, _Creature->GetGUID());
    } else if(RageEncounter == DONE && AnetheronEncounter == DONE) {
        player->ADD_GOSSIP_ITEM_TEXTID( 0, GOSSIP_ITEM_RETREAT_ALLY, GOSSIP_SENDER_MAIN,    GOSSIP_ACTION_INFO_DEF + 3);
        player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_RETREAT_ALLY, _Creature->GetGUID());
    }
    return true;
}

bool GossipSelect_npc_jaina_proudmoore(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    hyjalAI* ai = ((hyjalAI*)_Creature->AI());
    switch(action)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            ai->StartEvent(player);
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_BEGIN_ALLY_2, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            ai->FirstBossDead = true;
            ai->WaveCount = 9;
            ai->StartEvent(player);
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_ANATHERON2, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            ai->Retreat();
            break;
         case GOSSIP_ACTION_INFO_DEF:
            ai->Debug = !ai->Debug;
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            if (InstanceScript *pInstance = ((InstanceScript*)_Creature->GetInstanceScript()))
                pInstance->SetData(DATA_AZGALOREVENT, DONE);
            break;
    }
    return true;
}

CreatureAI* GetAI_npc_thrall(Creature *_Creature)
{
    auto  ai = new hyjalAI(_Creature);

    ai->Reset();
    ai->EnterEvadeMode(CreatureAI::EvadeReason::EVADE_REASON_OTHER);

    ai->Spell[0].SpellId = SPELL_CHAIN_LIGHTNING;
    ai->Spell[0].Cooldown = 3000 + rand()%5000;
    ai->Spell[0].TargetType = TARGETTYPE_VICTIM;

    ai->Spell[1].SpellId = SPELL_SUMMON_DIRE_WOLF;
    ai->Spell[1].Cooldown = 60000;
    ai->Spell[1].TargetType = TARGETTYPE_SELF;

    return ai;
}

bool GossipHello_npc_thrall(Player *player, Creature *_Creature)
{
    hyjalAI* ai = ((hyjalAI*)_Creature->AI());
    if (ai->EventBegun)
        return false;

    if(player->IsGameMaster()) {
        player->ADD_GOSSIP_ITEM(2, "[GM] Toggle Debug Timers", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    }

    uint32 AnetheronEvent = ai->GetInstanceScript(DATA_ANETHERONEVENT);
    // Only let them start the Horde phases if Anetheron is dead.
    if (AnetheronEvent == DONE && ai->GetInstanceScript(DATA_ALLIANCE_RETREAT))
    {
        uint32 KazrogalEvent = ai->GetInstanceScript(DATA_KAZROGALEVENT);
        uint32 AzgalorEvent  = ai->GetInstanceScript(DATA_AZGALOREVENT);
        if(KazrogalEvent == NOT_STARTED) {
            player->ADD_GOSSIP_ITEM_TEXTID( 0, GOSSIP_ITEM_BEGIN_HORDE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_BEGIN_HORDE, _Creature->GetGUID());
        } else if(KazrogalEvent == DONE && AzgalorEvent == NOT_STARTED) {
            player->ADD_GOSSIP_ITEM_TEXTID( 0, GOSSIP_ITEM_AZGALOR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_AZGALOR, _Creature->GetGUID());
        } else if(AzgalorEvent == DONE) {
            player->ADD_GOSSIP_ITEM_TEXTID( 0, GOSSIP_ITEM_RETREAT_HORDE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_RETREAT_HORDE, _Creature->GetGUID());
        }
    }

    return true;
}

bool GossipSelect_npc_thrall(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    hyjalAI* ai = ((hyjalAI*)_Creature->AI());
    ai->DeSpawnVeins();//despawn the alliance veins
    switch(action)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            ai->StartEvent(player);
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_BEGIN_HORDE2, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            ai->FirstBossDead = true;
            ai->WaveCount = 9;
            ai->StartEvent(player);
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_AZGALOR2, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            ai->Retreat();
            break;
        case GOSSIP_ACTION_INFO_DEF:
            ai->Debug = !ai->Debug;
            break;
    }
    return true;
}

CreatureAI* GetAI_npc_tyrande_whisperwind(Creature *_Creature)
{
    auto  ai = new hyjalAI(_Creature);
    ai->Reset();
    ai->EnterEvadeMode(CreatureAI::EvadeReason::EVADE_REASON_OTHER);
    return ai;
}

bool GossipHello_npc_tyrande_whisperwind(Player* player, Creature* _Creature)
{
    hyjalAI* ai = ((hyjalAI*)_Creature->AI());
    uint32 AzgalorEvent = ai->GetInstanceScript(DATA_AZGALOREVENT);

    // Only let them get item if Azgalor is dead.
    if (AzgalorEvent == DONE && !player->HasItemCount(ITEM_TEAR_OF_GODDESS,1))
        player->ADD_GOSSIP_ITEM_TEXTID(0, GOSSIP_ITEM_TYRANDE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_TYRANDE, _Creature->GetGUID());
    return true;
}

bool GossipSelect_npc_tyrande_whisperwind(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF)
    {
            ItemPosCountVec dest;
            uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_TEAR_OF_GODDESS, 1);
            if (msg == EQUIP_ERR_OK)
            {
                 Item* item = player->StoreNewItem(dest, ITEM_TEAR_OF_GODDESS, true);
                 if(item && player)
                     player->SendNewItem(item,1,true,false,true);
            }
            player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_MENU_TYRANDE2, _Creature->GetGUID());
    }
    return true;
}

void AddSC_hyjal()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name = "npc_jaina_proudmoore";
    newscript->GetAI = &GetAI_npc_jaina_proudmoore;
    newscript->OnGossipHello = &GossipHello_npc_jaina_proudmoore;
    newscript->OnGossipSelect = &GossipSelect_npc_jaina_proudmoore;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_thrall";
    newscript->GetAI = &GetAI_npc_thrall;
    newscript->OnGossipHello = &GossipHello_npc_thrall;
    newscript->OnGossipSelect = &GossipSelect_npc_thrall;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_tyrande_whisperwind";
    newscript->OnGossipHello = &GossipHello_npc_tyrande_whisperwind;
    newscript->OnGossipSelect = &GossipSelect_npc_tyrande_whisperwind;
    newscript->GetAI = &GetAI_npc_tyrande_whisperwind;
    sScriptMgr->RegisterOLDScript(newscript);
}

