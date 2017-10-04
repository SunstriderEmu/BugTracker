/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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
Name: Arena Spectator
%Complete: 100
Comment: OLDScript allow spectate arena games
Category: Custom OLDScript
EndScriptData */


#include "Language.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "BattleGroundMgr.h"
#include "ArenaTeam.h"
#include "World.h"
#include "BattleGround.h"

enum NpcSpectatorActions
{
    NPC_SPECTATOR_ACTION_2                   = 2000,
    NPC_SPECTATOR_ACTION_3                   = 3000,
    NPC_SPECTATOR_ACTION_5                   = 4000,
    NPC_SPECTATOR_ACTION_SELECTED_PLAYER     = 5000
};

const uint8  GamesOnPage    = 15;

std::string GetClassNameById(uint8 id)
{
    std::string sClass = "";
    switch (id)
    {
        case CLASS_WARRIOR:         sClass = "War";       break;
        case CLASS_PALADIN:         sClass = "Pal";       break;
        case CLASS_HUNTER:          sClass = "Hunt";      break;
        case CLASS_ROGUE:           sClass = "Rogue";     break;
        case CLASS_PRIEST:          sClass = "Priest";    break;
        case CLASS_SHAMAN:          sClass = "Cham";      break;
        case CLASS_MAGE:            sClass = "Mage";      break;
        case CLASS_WARLOCK:         sClass = "Demo";      break;
        case CLASS_DRUID:           sClass = "Druide";    break;
    }
    return sClass;
}

std::string GetApproximatedRating(uint32 rating)
{
    if (rating >= 2200)
        return "2200+";
    else if (rating >= 1900)
        return "1900+";
    else if (rating >= 1500)
        return "1500+";
    else
        return "1500-";
}

std::string GetGamesStringData(Battleground *arena)
{
    std::string data = "";

    for (uint8 i = 0; i < 2; i++)
    {
        if(arena->GetArenaTeamIdForIndex(i) == 0)
            continue;
        ArenaTeam *team =  sObjectMgr->GetArenaTeamById(arena->GetArenaTeamIdForIndex(i));

        auto begin = team->membersBegin();
        auto end = team->membersEnd();

        for (auto itr = begin; itr != end; itr++)
        {
            if (Player* player = ObjectAccessor::FindPlayer(itr->Guid))
            {
                if (arena->IsPlayerInBattleground(itr->Guid))
                {
                    //data += GetClassNameById(itr->Class);
                    data += "FIXME GetGamesStringData";
                    data += "/";
                }
            }
        }

        if (arena->isRated())
        {
            std::stringstream ss;
            ss << GetApproximatedRating(team->GetRating());
            data += "(" + ss.str() + ")";
        }
        else
            data += "(0)";

        if (i == 0)
            data += " - ";
    }

    if(data.empty())
        data = "Escarmouche";

    return data;
}

uint64 GetFirstPlayerGuid(Battleground *arena)
{
    for (const auto & itr : arena->GetPlayers())
        if (Player* player = ObjectAccessor::FindPlayer(itr.first))
            return itr.first;
    return 0;
}

void ShowPage(Player *player, uint32 page, ArenaType type)
{
    bool haveNextPage = false;
    /* Repair me
    uint16 nbArenas  = 0;

    for (uint8 i = BATTLEGROUND_AV; i <= BATTLEGROUND_RL; ++i)
    {
        if (!sBattlegroundMgr->IsArenaType((BattlegroundTypeId)i))
            continue;

        BattlegroundSet bgs = sBattlegroundMgr->GetBattlegroundByType((BattlegroundTypeId)i);
        for (auto & bg : bgs)
        {
            Battleground* arena = bg.second;

            if (!arena->GetPlayersSize())
               continue;

            if (arena->GetStatus() != STATUS_IN_PROGRESS)
                continue;

            if (type == arena->GetArenaType())
            {
                nbArenas++;
                if (nbArenas > (page + 1) * GamesOnPage)
                {
                    haveNextPage = true;
                    break;
                }

                if (nbArenas > page * GamesOnPage)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, GetGamesStringData(arena), GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_SELECTED_PLAYER + GetFirstPlayerGuid(arena));
            }
        }
    }
    */

    switch (type)
    {
        case ARENA_TYPE_2v2:
            if (page > 0)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Précédent...", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_2 + page - 1);

            if (haveNextPage)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Suivant...", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_2 + page + 1);
            break;
        case ARENA_TYPE_3v3:
            if (page > 0)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Précédent...", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_3 + page - 1);

            if (haveNextPage)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Suivant...", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_3 + page + 1);
            break;
        case ARENA_TYPE_5v5:
            if (page > 0)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Précédent...", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_5 + page - 1);

            if (haveNextPage)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Suivant...", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_5 + page + 1);
            break;
    }

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Retour", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Refresh", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3 + type);
}

void spectate(Player* player, uint64 targetGuid, Creature *mobArena)
{
    if (Player* target = ObjectAccessor::FindPlayer(targetGuid))
    {
        if (target == player || targetGuid == player->GetGUID())
            return;

        if (player->IsInCombat())
        {
            mobArena->Whisper("You must be out of combat.", LANG_UNIVERSAL, player);
            return;
        }

        if (!target)
        {
            mobArena->Whisper("Could not find the given player.", LANG_UNIVERSAL, player);
            return;
        }

        if (player->GetPet())
        {
            mobArena->Whisper("You must dismiss your pet first.", LANG_UNIVERSAL, player);
            return;
        }

        const Map* pMap = player->GetBaseMap();
        if (!pMap)
            return;

        if (pMap->IsBattlegroundOrArena() && !player->isSpectator())
        {
            mobArena->Whisper("You must leave your battleground or arena first.", LANG_UNIVERSAL, player);
            return;
        }

        const Map* tMap = target->GetBaseMap();
        if (!tMap)
            return;

        if (!tMap->IsBattleArena())
        {
            mobArena->Whisper("The target player is not in an arena.", LANG_UNIVERSAL, player);
            return;
        }

        if (pMap->IsBattleground())
        {
            mobArena->Whisper("You must leave your battleground first.", LANG_UNIVERSAL, player);
            return;
        }

        if (Battleground* bg = target->GetBattleground())
        {
            if (bg->GetStatus() != STATUS_IN_PROGRESS)
            {
                mobArena->Whisper("You must wait until the arena has started.", LANG_UNIVERSAL, player);
                return;
            }

            if (!bg->canEnterSpectator(player))
            {
                mobArena->Whisper("There is no more room for spectators in this match.", LANG_UNIVERSAL, player);
                return;
            }
        }

        if (target->isSpectator())
        {
            mobArena->Whisper("The target player is also a spectator.", LANG_UNIVERSAL, player);
            return;
        }

        // stop flight if need
        if (player->IsInFlight())
        {
            player->GetMotionMaster()->MovementExpired();
            player->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            player->SaveRecallPosition();

        // all's well, set bg id
        // when porting out from the bg, it will be reset to 0
        player->SetBattlegroundId(target->GetBattlegroundId(), target->GetBattlegroundTypeId());
        // search for two teams
        Battleground *bGround = target->GetBattleground();
        if (!bGround)
            return;

        // remember current position as entry point for return at bg end teleportation
        player->SetBattlegroundEntryPoint();

        if (bGround->isRated())
        {
            uint32 slot = bGround->GetArenaType() - 2;
            if (bGround->GetArenaType() > 3)
                slot = 2;
            uint32 firstTeamID = target->GetArenaTeamId(slot);
            uint32 secondTeamID = 0;
            Player *secondTeamMember = nullptr;
            for (const auto & itr : bGround->GetPlayers())
                if (Player* tmpPlayer = ObjectAccessor::FindPlayer(itr.first))
                {
                    if (tmpPlayer->isSpectator())
                        continue;

                    uint32 tmpID = tmpPlayer->GetArenaTeamId(slot);
                    if (tmpID != firstTeamID && tmpID > 0)
                    {
                        secondTeamID = tmpID;
                        secondTeamMember = tmpPlayer;
                        break;
                    }
                }

            if (firstTeamID > 0 && secondTeamID > 0 && secondTeamMember)
            {
                ArenaTeam *firstTeam  = sObjectMgr->GetArenaTeamById(firstTeamID);
                ArenaTeam *secondTeam = sObjectMgr->GetArenaTeamById(secondTeamID);
                if (firstTeam && secondTeam)
                {
                    ChatHandler chH = ChatHandler(player);
                    chH.PSendSysMessage("Your enter in a rated arena.");
                    chH.PSendSysMessage("Teams :");
                    chH.PSendSysMessage("%s - %s", firstTeam->GetName().c_str(), secondTeam->GetName().c_str());
                    chH.PSendSysMessage("%u - %u", firstTeam->GetRating(), secondTeam->GetRating());
                }
            }
        }

        // to point to see at target with same orientation
        float x, y, z;
        target->GetContactPoint(player, x, y, z);

        target->GetBattleground()->AddSpectator(player->GetGUID());
        player->TeleportTo(target->GetMapId(), x, y, z, player->GetAngle(target), TELE_TO_GM_MODE);
        player->SetSpectate(true);
    }
}

void ShowDefaultPage(Player* player, Creature* creature)
{
    if(sWorld->getConfig(CONFIG_ARENA_SPECTATOR_ENABLE))
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Arenas 2V2", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Arenas 3V3", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_3);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Arenas 5V5", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_5);
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Watch player...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2, "", 0, true);
        player->SEND_GOSSIP_MENU_TEXTID(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    }
    else
    {
        player->CLOSE_GOSSIP_MENU();
        creature->Whisper("Arena spectator is disabled.", LANG_UNIVERSAL, player);
    }
}

void RefreshPage(Player* player, Creature* creature, uint8 type)
{
    if(sWorld->getConfig(CONFIG_ARENA_SPECTATOR_ENABLE))
    {
        ShowPage(player, 0, (ArenaType)type);
        player->SEND_GOSSIP_MENU_TEXTID(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    }
    else
    {
        player->CLOSE_GOSSIP_MENU();
        creature->Whisper("Arena spectator is disabled.", LANG_UNIVERSAL, player);
    }
}

class npc_spectate : public CreatureScript
{
public:
    npc_spectate() : CreatureScript("npc_spectate")
    { }

    class npc_spectateAI : public ScriptedAI
    {
    public:
        npc_spectateAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if(sWorld->getConfig(CONFIG_ARENA_SPECTATOR_ENABLE))
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Arenas 2V2", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_2);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Arenas 3V3", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_3);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Arenas 5V5", GOSSIP_SENDER_MAIN, NPC_SPECTATOR_ACTION_5);
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Watch player...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2, "", 0, true);
            }
            else
            {
                me->Whisper("Arena spectator is disabled", LANG_UNIVERSAL, pPlayer);
                return true;
            }

            pPlayer->SEND_GOSSIP_MENU_TEXTID(DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 , uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
                ShowDefaultPage(player, me);
            else if (action >= (GOSSIP_ACTION_INFO_DEF + 3) && action < NPC_SPECTATOR_ACTION_2)
                RefreshPage(player, me, action - (GOSSIP_ACTION_INFO_DEF + 3));
            else if (action >= NPC_SPECTATOR_ACTION_2 && action < NPC_SPECTATOR_ACTION_3)
            {
                ShowPage(player, action - NPC_SPECTATOR_ACTION_2, ARENA_TYPE_2v2);
                player->SEND_GOSSIP_MENU_TEXTID(DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
            }
            else if (action >= NPC_SPECTATOR_ACTION_3 && action < NPC_SPECTATOR_ACTION_5)
            {
                ShowPage(player, action - NPC_SPECTATOR_ACTION_3, ARENA_TYPE_3v3);
                player->SEND_GOSSIP_MENU_TEXTID(DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
            }
            else if (action >= NPC_SPECTATOR_ACTION_5 && action < NPC_SPECTATOR_ACTION_SELECTED_PLAYER)
            {
                ShowPage(player, action - NPC_SPECTATOR_ACTION_5, ARENA_TYPE_5v5);
                player->SEND_GOSSIP_MENU_TEXTID(DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
            }
            else if (action >= NPC_SPECTATOR_ACTION_SELECTED_PLAYER)
            {
                player->CLOSE_GOSSIP_MENU();
                uint64 targetGuid = action - NPC_SPECTATOR_ACTION_SELECTED_PLAYER;
                spectate(player, targetGuid, me);
            }

            return true;

        }


        virtual bool GossipSelectCode(Player* player, uint32 menuId, uint32 gossipListId, const char* sCode) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            uint32 const sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
            if(sender == GOSSIP_SENDER_MAIN)
            {
                if(action == GOSSIP_ACTION_INFO_DEF + 2)
                {
                    std::string name = sCode;
                    if(!name.empty())
                    {
                        if(!normalizePlayerName(name))
                        {
                            me->Whisper("Invalid name.", LANG_UNIVERSAL, player);
                            player->CLOSE_GOSSIP_MENU();
                            return true;
                        }

                        Player* target = ObjectAccessor::FindConnectedPlayerByName(name.c_str());
                        if (!target)
                        {
                            me->Whisper("Could not find player.", LANG_UNIVERSAL, player);
                            player->CLOSE_GOSSIP_MENU();
                            return true;
                        }

                        spectate(player, target->GetGUID(), me);
                    }
                    else
                        me->Whisper("Empty field.", LANG_UNIVERSAL, player);

                    player->CLOSE_GOSSIP_MENU();
                    return true;
                }
            }
            return false;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_spectateAI(creature);
    }
};




void AddSC_arena_spectator_script()
{

    new npc_spectate();
}
