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
SDName: Hellfire_Peninsula
SD%Complete: 100
SDComment: Quest support: 9375, 9418, 10129, 10146, 10162, 10163, 10340, 10346, 10347, 10382 (Special flight paths), 10629, 10838, 10909, 11516
SDCategory: Hellfire Peninsula
EndScriptData */

/* ContentData
npc_aeranas
go_haaleshi_altar
npc_wing_commander_dabiree
npc_gryphoneer_windbellow
npc_wing_commander_brack
npc_wounded_blood_elf
npc_fel_guard_hound
npc_anchorite_relic
npc_living_flare
npc_ancestral_spirit_wolf
npc_anchorite_barada
npc_pathaleon_image
npc_demoniac_scryer
npc_magic_sucker_device_spawner
npc_sedai_quest_credit_marker
npc_vindicator_sedai
npc_anchorite_barada
npc_darkness_released
npc_foul_purge
dark_portal_event_controller

EndContentData */


#include "EscortAI.h"
#include "Unit.h"
#include "Pet.h"
#include "Movement/MovementGenerators/WaypointMovementGenerator.h"

/*######
## npc_aeranas
######*/

enum eAeranas
{
SAY_SUMMON                      = -1000138,
SAY_FREE                        = -1000139,

FACTION_HOSTILE                 = 16,
FACTION_FRIENDLY                = 35,

SPELL_ENVELOPING_WINDS          = 15535,
SPELL_SHOCK                     = 12553,

C_AERANAS                       = 17085
};

struct npc_aeranasAI : public ScriptedAI
{
    npc_aeranasAI(Creature* c) : ScriptedAI(c) {}

    uint32 Faction_Timer;
    uint32 EnvelopingWinds_Timer;
    uint32 Shock_Timer;

    void Reset()
    override {
        Faction_Timer = 8000;
        EnvelopingWinds_Timer = 9000;
        Shock_Timer = 5000;

        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        me->SetFaction(FACTION_FRIENDLY);

        DoScriptText(SAY_SUMMON, me);
    }

    void EnterCombat(Unit* pWho) override {}

    void UpdateAI(const uint32 diff)
    override {
        if (Faction_Timer)
        {
            if (Faction_Timer < diff)
            {
                me->SetFaction(FACTION_HOSTILE);
                Faction_Timer = 0;
            } else Faction_Timer -= diff;
        }

        if (!UpdateVictim())
            return;

        if (me->GetHealthPct() < 30)
        {
            me->SetFaction(FACTION_FRIENDLY);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop();
            DoScriptText(SAY_FREE, me);
            return;
        }

        if (Shock_Timer < diff)
        {
            DoCast(me->GetVictim(),SPELL_SHOCK);
            Shock_Timer = 10000;
        } else Shock_Timer -= diff;

        if (EnvelopingWinds_Timer < diff)
        {
            DoCast(me->GetVictim(),SPELL_ENVELOPING_WINDS);
            EnvelopingWinds_Timer = 25000;
        } else EnvelopingWinds_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_aeranas(Creature* pCreature)
{
    return new npc_aeranasAI(pCreature);
}

class HaaleshiAltar : public GameObjectScript
{
public:
    HaaleshiAltar() : GameObjectScript("go_haaleshi_altar")
    {}

    bool OnGossipHello(Player* player, GameObject* pGo) override
    {
        pGo->SummonCreature(C_AERANAS, -1321.79, 4043.80, 116.24, 1.25, TEMPSUMMON_TIMED_DESPAWN, 180000);
        return false;
    }
};

/*######
## npc_wing_commander_dabiree
######*/

#define GOSSIP_ITEM1_DAB "Fly me to Murketh and Shaadraz Gateways"
#define GOSSIP_ITEM2_DAB "Fly me to Shatter Point"

bool GossipHello_npc_wing_commander_dabiree(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    //Mission: The Murketh and Shaadraz Gateways
    if (pPlayer->GetQuestStatus(10146) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(2, GOSSIP_ITEM1_DAB, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    //Shatter Point
    if (!pPlayer->GetQuestRewardStatus(10340))
        pPlayer->ADD_GOSSIP_ITEM(2, GOSSIP_ITEM2_DAB, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);

    return true;
}

bool GossipSelect_npc_wing_commander_dabiree(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action )
{
    if (action == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, 33768, true);               //TaxiPath 585 (Gateways Murket and Shaadraz)
    }
    if (action == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, 35069, true);               //TaxiPath 612 (Taxi - Hellfire Peninsula - Expedition Point to Shatter Point)
    }
    return true;
}

/*######
## npc_gryphoneer_windbellow
######*/

#define GOSSIP_ITEM1_WIN "Fly me to The Abyssal Shelf"
#define GOSSIP_ITEM2_WIN "Fly me to Honor Point"

bool GossipHello_npc_gryphoneer_windbellow(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu( pCreature->GetGUID() );

    //Mission: The Abyssal Shelf || Return to the Abyssal Shelf
    if (pPlayer->GetQuestStatus(10163) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(10346) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(2, GOSSIP_ITEM1_WIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    //Go to the Front
    if (pPlayer->GetQuestStatus(10382) != QUEST_STATUS_NONE && !pPlayer->GetQuestRewardStatus(10382))
        pPlayer->ADD_GOSSIP_ITEM(2, GOSSIP_ITEM2_WIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);

    return true;
}

bool GossipSelect_npc_gryphoneer_windbellow(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action )
{
    if (action == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, 33899, true);               //TaxiPath 589 (Aerial Assault Flight (Alliance))
    }
    if (action == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, 35065, true);               //TaxiPath 607 (Taxi - Hellfire Peninsula - Shatter Point to Beach Head)
    }
    return true;
}

/*######
## npc_gryphoneer_leafbeard
######*/

enum
{
    SPELL_TAXI_TO_SHATTERP      = 35066
};

#define GOSSIP_ITEM1_LEAF       "Fly me to Shatter Point"

bool GossipHello_npc_gryphoneer_leafbeard(Player* pPlayer, Creature *pCreature)
{
    //Go back to Shatter Point if player has completed the quest 10340 - Shatter Point
    if (pPlayer->GetQuestStatus(10340) == QUEST_STATUS_COMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM1_LEAF, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
    return true;
}

bool GossipSelect_npc_gryphoneer_leafbeard(Player* pPlayer, Creature *pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        //TaxiPath 609 (3.x.x)
        pPlayer->CastSpell(pPlayer, SPELL_TAXI_TO_SHATTERP, true);
    }
    return true;
}

/*######
## npc_wing_commander_brack
######*/

#define GOSSIP_ITEM1_BRA "Fly me to Murketh and Shaadraz Gateways"
#define GOSSIP_ITEM2_BRA "Fly me to The Abyssal Shelf"
#define GOSSIP_ITEM3_BRA "Fly me to Spinebreaker Post"

bool GossipHello_npc_wing_commander_brack(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu( pCreature->GetGUID() );

    //Mission: The Murketh and Shaadraz Gateways
    if (pPlayer->GetQuestStatus(10129) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(2, GOSSIP_ITEM1_BRA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    //Mission: The Abyssal Shelf || Return to the Abyssal Shelf
    if (pPlayer->GetQuestStatus(10162) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(10347) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(2, GOSSIP_ITEM2_BRA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

    //Spinebreaker Post
    if (pPlayer->GetQuestStatus(10242) == QUEST_STATUS_COMPLETE && !pPlayer->GetQuestRewardStatus(10242))
        pPlayer->ADD_GOSSIP_ITEM(2, GOSSIP_ITEM3_BRA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);

    return true;
}

bool GossipSelect_npc_wing_commander_brack(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action )
{
    switch(action)
    {
    case GOSSIP_ACTION_INFO_DEF + 1:
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer,33659,true);               //TaxiPath 584 (Gateways Murket and Shaadraz)
        break;
    case GOSSIP_ACTION_INFO_DEF + 2:
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer,33825,true);               //TaxiPath 587 (Aerial Assault Flight (Horde))
        break;
    case GOSSIP_ACTION_INFO_DEF + 3:
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer,34578,true);               //TaxiPath 604 (Taxi - Reaver's Fall to Spinebreaker Ridge)
        break;
    }
        return true;
}

/*######
## npc_wounded_blood_elf
######*/

enum eWoundedElf
{
SAY_ELF_START               = -1000117,
SAY_ELF_SUMMON1             = -1000118,
SAY_ELF_RESTING             = -1000119,
SAY_ELF_SUMMON2             = -1000120,
SAY_ELF_COMPLETE            = -1000121,
SAY_ELF_AGGRO               = -1000122,

QUEST_ROAD_TO_FALCON_WATCH  = 9375
};

struct npc_wounded_blood_elfAI : public npc_escortAI
{
    npc_wounded_blood_elfAI(Creature *c) : npc_escortAI(c) {}

    void WaypointReached(uint32 i)
    override {
        Player* player = GetPlayerForEscort();

        if (!player)
            return;

        switch (i)
        {
        case 0:
            DoScriptText(SAY_ELF_START, me, player);
            break;
        case 9:
            DoScriptText(SAY_ELF_SUMMON1, me, player);
            // Spawn two Haal'eshi Talonguard
            DoSpawnCreature(16967, -15, -15, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            DoSpawnCreature(16967, -17, -17, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            break;
        case 13:
            DoScriptText(SAY_ELF_RESTING, me, player);
            // make the NPC kneel
            me->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
            break;
        case 14:
            DoScriptText(SAY_ELF_SUMMON2, me, player);
            // Spawn two Haal'eshi Windwalker
            DoSpawnCreature(16966, -15, -15, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            DoSpawnCreature(16966, -17, -17, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            break;
        case 27:
            DoScriptText(SAY_ELF_COMPLETE, me, player);
            // Award quest credit
            Player* player = GetPlayerForEscort();
            if (player)
                player->GroupEventHappens(QUEST_ROAD_TO_FALCON_WATCH,me);
            break;
        }
    }

    void Reset()
    override {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
            me->SetFaction(1604);
    }

    void EnterCombat(Unit* pWho)
    override {
        if (HasEscortState(STATE_ESCORT_ESCORTING))
            DoScriptText(SAY_ELF_AGGRO, me);
    }

    void JustSummoned(Creature* pSummoned)
    override {
        pSummoned->AI()->AttackStart(me);
    }

    void JustDied(Unit* pKiller)
    override {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
            return;

        if (PlayerGUID)
        {
            // If NPC dies, player fails the quest
            Player* player = GetPlayerForEscort();
            if (player)
                player->FailQuest(QUEST_ROAD_TO_FALCON_WATCH);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        npc_escortAI::UpdateAI(diff);
    }
};

CreatureAI* GetAI_npc_wounded_blood_elf(Creature* pCreature)
{
    return new npc_wounded_blood_elfAI(pCreature);
}

bool QuestAccept_npc_wounded_blood_elf(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_ROAD_TO_FALCON_WATCH)
    {
        CAST_AI(npc_escortAI, (pCreature->AI()))->Start(true, true, false, pPlayer->GetGUID(), pCreature->GetEntry());
        // Change faction so mobs attack
        pCreature->SetFaction(775);
    }

    return true;
}

/*######
## npc_fel_guard_hound
######*/

enum eFelGuard
{
SPELL_SUMMON_POO    = 37688,
SPELL_STANKY        = 37695,

DERANGED_HELBOAR    = 16863
};

struct npc_fel_guard_houndAI : public ScriptedAI
{
    npc_fel_guard_houndAI(Creature* c) : ScriptedAI(c) {}
    
    uint32 checkTimer;
    uint64 lastHelboar; //store last helboar GUID to prevent multiple spawns of poo with the same mob
    
    void Reset()
    override {
        me->GetMotionMaster()->MoveFollow(me->GetOwner(), PET_FOLLOW_DIST, me->GetFollowAngle());
        checkTimer = 5000; //check for creature every 5 sec
    }
    
    void EnterCombat(Unit* pWho) override {}
    
    void UpdateAI(const uint32 diff)
    override {
        if (checkTimer < diff)
        {
            Creature* helboar = me->FindNearestCreature(DERANGED_HELBOAR, 10, false);
            if (helboar && helboar->GetGUID() != lastHelboar)
            {
                lastHelboar = helboar->GetGUID();
                DoCast(me, SPELL_SUMMON_POO);
                DoCast(me->GetOwner(), SPELL_STANKY);
                helboar->RemoveCorpse();
                checkTimer = 5000;
            }
        }else checkTimer -= diff;
    }
};

CreatureAI* GetAI_npc_fel_guard_hound(Creature* pCreature)
{
    return new npc_fel_guard_houndAI(pCreature);
}

/*######
## npc_anchorite_relic
######*/

enum eAnchoriteRelic
{
MOB_BERSERKER   = 16878,
MOB_FEL_SPIRIT  = 22454
};

struct npc_anchorite_relicAI : public ScriptedAI
{
    npc_anchorite_relicAI(Creature* c) : ScriptedAI(c) {}
    
    uint32 checkTimer;
    bool hasTarget;
    Creature* berserker;
    
    void Reset()
    override {
        checkTimer = 5000;
        hasTarget = false;
        berserker = nullptr;
    }
    
    void EnterCombat(Unit* pWho) override {}
    
    void UpdateAI(const uint32 diff)
    override {
        if (checkTimer < diff)
        {
            if (!hasTarget) //can handle only one orc at a time, dunno if it's blizzlike, but it's easier :p
            {
                berserker = me->FindNearestCreature(MOB_BERSERKER, 20.0f);
                if (berserker)
                    hasTarget = true;
                //here, me should cast a channelling spell on the select orc, but I don't know which one...
            }
        }else checkTimer -= diff;
        
        //at each update, check if the orc is dead; if he is, summon a fel spirit (npc 22454) at his position
        if (berserker && !berserker->IsAlive())
        {
            me->SummonCreature(MOB_FEL_SPIRIT, berserker->GetPositionX(), berserker->GetPositionY(), berserker->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000)->AI()->AttackStart(me->GetOwner());
            hasTarget = false;
            berserker = nullptr; //unset berserker
        }
    }
};

CreatureAI* GetAI_npc_anchorite_relic(Creature* pCreature)
{
    return new npc_anchorite_relicAI(pCreature);
}

/*######
## npc_living_flare
######*/
enum
{
    SPELL_COSMETIC             = 44880,
    SPELL_UNSTABLE_COSMETIC    = 46196,
    SPELL_ABSORBED             = 44944,
    NPC_FEL_SPARK              = 22323,
    NPC_TRIGGER                = 24959,
    GO_FIRE                    = 185319
};

struct npc_living_flareAI : public ScriptedAI
{
    npc_living_flareAI(Creature* pCreature) : ScriptedAI(pCreature) {}
    uint32 uiCheckTimer;
    uint64 uiSparkGUID;
    uint32 Count;

    void Reset()
    override {
        DoCast(me, SPELL_COSMETIC);
        me->GetMotionMaster()->MoveFollow(me->GetOwner(), PET_FOLLOW_DIST, me->GetFollowAngle());
        uiCheckTimer = 8000;
        uiSparkGUID = 0;
        Count = 0;
    }

    void AttackedBy(Unit* pWho) override {}
    void AttackStart(Unit* pWho) override {}
    void EnterCombat(Unit* who) override {}

    void UpdateAI(const uint32 uiDiff)
    override {
        if (uiCheckTimer <= uiDiff)
        {
            if (Creature* pSpark = me->FindNearestCreature(NPC_FEL_SPARK, 10.0f, false))
            {
                if (pSpark->GetGUID() != uiSparkGUID && (me->GetOwner())->ToPlayer()->GetQuestStatus(11516) == QUEST_STATUS_INCOMPLETE)
                {
                    if (Count <= 7)
                    {
                        ++Count;
                        DoCast(me, SPELL_ABSORBED);
                        uiSparkGUID = pSpark->GetGUID();
                    }
                    else DoCast(me, SPELL_UNSTABLE_COSMETIC);
                }
            }

            if (Creature* pTrigger = me->FindNearestCreature(NPC_TRIGGER, 8.0f, true))
            {
                pTrigger->SummonGameObject(GO_FIRE, pTrigger->GetPosition(), G3D::Quat(), 60);
                (me->GetOwner())->ToPlayer()->AreaExploredOrEventHappens(11516);
                me->SetDeathState(CORPSE);
            }
        }
        else uiCheckTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_living_flare(Creature* pCreature)
{
    return new npc_living_flareAI(pCreature);
}

/*######
## npc_ancestral_wolf
######*/

enum eAncestralWolf
{
    EMOTE_WOLF_LIFT_HEAD            = -1000496,
    EMOTE_WOLF_HOWL                 = -1000497,
    SAY_WOLF_WELCOME                = -1000498,

    SPELL_ANCESTRAL_WOLF_BUFF       = 29981,

    NPC_RYGA                        = 17123
};

struct npc_ancestral_wolfAI : public npc_escortAI
{
    npc_ancestral_wolfAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        if (pCreature->GetOwner() && pCreature->GetOwner()->GetTypeId() == TYPEID_PLAYER)
            Start(false, false, true, pCreature->GetOwner()->GetGUID(), pCreature->GetEntry());
        else
            TC_LOG_ERROR("scripts","TRINITY: npc_ancestral_wolf can not obtain owner or owner is not a player.");

        pCreature->SetSpeedRate(MOVE_WALK, 1.5f);
        Reset();
    }

    Unit* pRyga;

    void Reset()
    override {
        pRyga = nullptr;
        DoCast(me, SPELL_ANCESTRAL_WOLF_BUFF, true);
    }

    void EnterCombat(Unit *pWho) override {}

    void MoveInLineOfSight(Unit* pWho)
    override {
        if (!pRyga && pWho->GetTypeId() == TYPEID_UNIT && pWho->GetEntry() == NPC_RYGA && me->IsWithinDistInMap(pWho, 15.0f))
            pRyga = pWho;

        npc_escortAI::MoveInLineOfSight(pWho);
    }

    void WaypointReached(uint32 uiPointId)
    override {
        switch(uiPointId)
        {
            case 0:
                DoScriptText(EMOTE_WOLF_LIFT_HEAD, me);
                break;
            case 2:
                DoScriptText(EMOTE_WOLF_HOWL, me);
                break;
            case 50:
                if (pRyga && pRyga->IsAlive() && !pRyga->IsInCombat())
                    DoScriptText(SAY_WOLF_WELCOME, pRyga);
                break;
        }
    }
};

CreatureAI* GetAI_npc_ancestral_wolf(Creature* pCreature)
{
    return new npc_ancestral_wolfAI(pCreature);
}

/*######
## npc_pathaleon_image
######*/

enum
{
    SAY_PATHALEON1         = -1900165,
    SAY_PATHALEON2         = -1900166,
    SAY_PATHALEON3         = -1900167,
    SAY_PATHALEON4         = -1900168,
    SPELL_ROOTS            = 35468,
    SPELL_INSECT           = 35471,
    SPELL_LIGHTING         = 35487,
    SPELL_TELE             = 7741,
    NPC_TARGET_TRIGGER     = 20781,
    NPC_CRYSTAL_TRIGGER    = 20617,
    NPC_GOLIATHON          = 19305,
};

struct npc_pathaleon_imageAI : public ScriptedAI
{
    npc_pathaleon_imageAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    bool Event;
    bool SummonTrigger;

    uint32 uiSumTimer;
    uint32 uiStepsTimer;
    uint32 uiSteps;

    void Reset()
    override {
        uiSumTimer = 5000;
        uiStepsTimer = 0;
        uiSteps = 0;
        Event = true;
        SummonTrigger = false;
    }
    
    void EnterCombat(Unit* who) override {}

    void DoSpawnGoliathon()
    {
        me->SummonCreature(NPC_GOLIATHON, 113.29f, 4858.19f, 74.37f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
    }

    void DoSpawnTrigger()
    {
        me->SummonCreature(NPC_TARGET_TRIGGER, 81.20f, 4806.26f, 51.75f, 2.0f, TEMPSUMMON_TIMED_DESPAWN, 120000);
    }

    void DoSpawnCtrigger()
    {
        me->SummonCreature(NPC_CRYSTAL_TRIGGER, 106.21f, 4834.39f, 79.56f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 7000);
        me->SummonCreature(NPC_CRYSTAL_TRIGGER, 124.98f, 4813.17f, 79.66f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 7000);
        me->SummonCreature(NPC_CRYSTAL_TRIGGER, 124.01f, 4778.61f, 77.86f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 7000);
        me->SummonCreature(NPC_CRYSTAL_TRIGGER, 46.37f, 4795.72f, 66.73f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 7000);
        me->SummonCreature(NPC_CRYSTAL_TRIGGER, 60.14f, 4830.46f, 77.83f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 7000);
    }

    void JustSummoned(Creature* pSummoned)
    override {
        if (pSummoned->GetEntry() == NPC_GOLIATHON)
        {
            pSummoned->CastSpell(pSummoned, SPELL_TELE, false);
            pSummoned->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
        }

        if (pSummoned->GetEntry() == NPC_CRYSTAL_TRIGGER)
        {
            pSummoned->CastSpell(pSummoned, SPELL_INSECT, false);
            pSummoned->CastSpell(pSummoned, SPELL_LIGHTING, false);
        }
        else
        {
            if (pSummoned->GetEntry() == NPC_TARGET_TRIGGER)
            {
                pSummoned->CastSpell(pSummoned, SPELL_ROOTS, false);
            }
        }
    }

    int32 NextStep(uint32 step)
    {              
        switch (step)
        {
            case 1:
                return 10000;
            case 2:
                DoSpawnTrigger();
                SummonTrigger = true;
                return 2000;
            case 3:
                DoScriptText(SAY_PATHALEON1, me, nullptr);
                return 15000;
            case 4:
                DoScriptText(SAY_PATHALEON2, me, nullptr);
                return 15000;
            case 5:
                DoScriptText(SAY_PATHALEON3, me, nullptr);
                return 15000;
            case 6:
                DoScriptText(SAY_PATHALEON4, me, nullptr);
                return 5000;
            case 7:
                DoSpawnGoliathon();
                return 1000;
            case 8:
                DoCast(me, SPELL_TELE);
                return 500;
            case 9:
                me->SetVisibility(VISIBILITY_OFF);
                return 60000;
            case 10:
                me->SetDeathState(CORPSE);
            default: return 0;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    override {
        if (uiStepsTimer <= uiDiff)
        {
            if (Event)
                uiStepsTimer = NextStep(++uiSteps);
        }
        else uiStepsTimer -= uiDiff;

        if (SummonTrigger)
        {
            if (uiSumTimer <= uiDiff)
            {
                DoSpawnCtrigger();
                uiSumTimer = 5000;
            }
            else uiSumTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_pathaleon_image(Creature* pCreature)
{
    return new npc_pathaleon_imageAI(pCreature);
}

/*######
## npc_demoniac_scryer
######*/

#define GOSSIP_ITEM_ATTUNE          "Oui, scrutateur. Vous pouvez me posséder."

enum
{
    GOSSIP_TEXTID_PROTECT           = 10659,
    GOSSIP_TEXTID_ATTUNED           = 10643,
    QUEST_DEMONIAC                  = 10838,
    NPC_HELLFIRE_WARDLING           = 22259,
    NPC_ORC_HA                      = 22273,
    NPC_BUTTRESS                    = 22267,
    NPC_BUTTRESS_SPAWNER            = 22260,

    MAX_BUTTRESS                    = 4,

    TIME_TOTAL                      = 10*MINUTE*IN_MILLISECONDS,

    SPELL_SUMMONED                  = 7741,
    SPELL_DEMONIAC_VISITATION       = 38708,
    SPELL_BUTTRESS_APPERANCE        = 38719,
    SPELL_SUCKER_CHANNEL            = 38721,
    SPELL_SUCKER_DESPAWN_MOB        = 38691,
};

struct npc_demoniac_scryerAI : public ScriptedAI
{
    npc_demoniac_scryerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        IfIsComplete = false;
        uiSpawnDemonTimer = 15000;
        uiSpawnOrcTimer = 30000;
        uiSpawnButtressTimer = 45000;
        uiEndTimer = 262000;
        uiButtressCount = 0;
        Reset();
    }

    bool IfIsComplete;

    uint32 uiSpawnDemonTimer;
    uint32 uiSpawnOrcTimer;
    uint32 uiSpawnButtressTimer;
    uint32 uiEndTimer;
    uint32 uiButtressCount;

    void Reset() override {}

    void AttackedBy(Unit* pEnemy) override {}

    void AttackStart(Unit* pEnemy) override {}

    void EnterCombat(Unit* who) override {}

    void DoSpawnButtress()
    {
        ++uiButtressCount;
        float fAngle;
        switch (uiButtressCount)
        {
			default:
            case 1: fAngle = 0.0f; break;
            case 2: fAngle = 4.6f; break;
            case 3: fAngle = 1.5f; break;
            case 4: fAngle = 3.1f; break;
        }

        float fX, fY, fZ;
        me->GetNearPoint(me, fX, fY, fZ, 0.0f, 7.0f, fAngle);
        uint32 uiTime = TIME_TOTAL - (uiSpawnButtressTimer * uiButtressCount);
        me->SummonCreature(NPC_BUTTRESS, fX, fY, fZ, me->GetAngle(fX, fY), TEMPSUMMON_TIMED_DESPAWN, uiTime);
        me->SummonCreature(NPC_BUTTRESS_SPAWNER, fX, fY, fZ, me->GetAngle(fX, fY), TEMPSUMMON_TIMED_DESPAWN, uiTime);
    }

    void DoSpawnDemon()
    {
        float fX, fY, fZ;
        me->GetNearPoint(me,fX, fY, fZ, 5.0f, 5.0f, -13.0f);
        me->SummonCreature(NPC_HELLFIRE_WARDLING, fX, fY, fZ, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    void DospawnOrc()
    {
        float fX, fY, fZ;
        me->GetNearPoint(me,fX, fY, fZ, 5.0f, 5.0f, -13.0f);
        me->SummonCreature(NPC_ORC_HA, fX, fY, fZ, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    void JustSummoned(Creature* pSummoned)
    override {
        if (pSummoned->GetEntry() == NPC_HELLFIRE_WARDLING)
        {
            pSummoned->CastSpell(pSummoned, SPELL_SUMMONED, false);
            pSummoned->AI()->AttackStart(me);
        }

        if (pSummoned->GetEntry() == NPC_ORC_HA)
        {
            pSummoned->CastSpell(pSummoned, SPELL_SUMMONED, false);
            pSummoned->AI()->AttackStart(me);
        }

        if (pSummoned->GetEntry() == NPC_BUTTRESS)
        {
            pSummoned->CastSpell(pSummoned, SPELL_BUTTRESS_APPERANCE, false);
        }
        else
        {
            if (pSummoned->GetEntry() == NPC_BUTTRESS_SPAWNER)
            {
                pSummoned->CastSpell(me, SPELL_SUCKER_CHANNEL, true);
            }
        }
    }

    void SpellHitTarget(Unit* pTarget, const SpellInfo* pSpell)
    override {
        if (pTarget->GetEntry() == NPC_BUTTRESS && pSpell->Id == SPELL_SUCKER_DESPAWN_MOB)
            ((Creature*)pTarget)->SetDeathState(CORPSE);

        if (pTarget->GetEntry() == NPC_BUTTRESS_SPAWNER && pSpell->Id == SPELL_SUCKER_DESPAWN_MOB)
            ((Creature*)pTarget)->SetDeathState(CORPSE);
    }

    void UpdateAI(const uint32 uiDiff)
    override {
        if (uiEndTimer <= uiDiff)
        {
            me->ForcedDespawn();
            uiEndTimer = 262000;
        }
        else uiEndTimer -= uiDiff;

        if (IfIsComplete || !me->IsAlive())
            return;

        if (uiSpawnButtressTimer <= uiDiff)
        {
            if (uiButtressCount >= MAX_BUTTRESS)
            {
                DoCast(me, SPELL_SUCKER_DESPAWN_MOB);
                IfIsComplete = true;
                return;
            }

            uiSpawnButtressTimer = 45000;
            DoSpawnButtress();
        }
        else uiSpawnButtressTimer -= uiDiff;

        if (uiSpawnDemonTimer <= uiDiff)
        {
            DoSpawnDemon();
            uiSpawnDemonTimer = 15000;
        }
        else uiSpawnDemonTimer -= uiDiff;

        if (uiSpawnOrcTimer <= uiDiff)
        {
            DospawnOrc();
            uiSpawnOrcTimer = 30000;
        }
        else uiSpawnOrcTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_demoniac_scryer(Creature* pCreature)
{
    return new npc_demoniac_scryerAI(pCreature);
}

bool GossipHello_npc_demoniac_scryer(Player* pPlayer, Creature* pCreature)
{
    if (npc_demoniac_scryerAI* pScryerAI = dynamic_cast<npc_demoniac_scryerAI*>(pCreature->AI()))
    {
        if (pScryerAI->IfIsComplete)
        {
            if (pPlayer->GetQuestStatus(QUEST_DEMONIAC) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ATTUNE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(GOSSIP_TEXTID_ATTUNED, pCreature->GetGUID());

            return true;
        }
    }

    pPlayer->SEND_GOSSIP_MENU_TEXTID(GOSSIP_TEXTID_PROTECT, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_demoniac_scryer(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->CastSpell(pPlayer, SPELL_DEMONIAC_VISITATION, false);
    }

    return true;
}

/*######
## npc_magic_sucker_device_spawner
######*/

enum
{
    SPELL_EFFECT    = 38724,
    NPC_SCRYER      = 22258,
    NPC_BUTTRES     = 22267
};

struct npc_magic_sucker_device_spawnerAI : public ScriptedAI
{
    npc_magic_sucker_device_spawnerAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    uint32 uiCastTimer;
    uint32 uiCheckTimer;

    void Reset()
    override {
        uiCastTimer = 1800;
        uiCheckTimer = 5000;
    }
    
    void EnterCombat(Unit* who) override {}

    void UpdateAI(const uint32 uiDiff)
    override {
        if (uiCastTimer <= uiDiff)
        {
            DoCast(me, SPELL_EFFECT);
            uiCastTimer = 1800;
        }
        else uiCastTimer -= uiDiff;

        if (uiCheckTimer <= uiDiff)
        {
            if (Creature* pScr = me->FindNearestCreature(NPC_SCRYER, 15.0f, false))
            {
                if (Creature* pBut = me->FindNearestCreature(NPC_BUTTRES, 5.0f))
                {
                    pBut->SetDeathState(CORPSE);
                    me->SetDeathState(CORPSE);
                }
            }
            else return;

            uiCheckTimer = 5000;
        }
        else uiCheckTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_magic_sucker_device_spawner(Creature* pCreature)
{
    return new npc_magic_sucker_device_spawnerAI(pCreature);
}

/*######
## npc_sedai_quest_credit_marker
######*/

enum
{
    NPC_ESCORT1    = 17417,
    NPC_SEDAI      = 17404
};

struct npc_sedai_quest_credit_markerAI : public ScriptedAI
{
    npc_sedai_quest_credit_markerAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset() 
    override {
        DoSpawn();
    }

    void EnterCombat(Unit* who) override {}

    void DoSpawn()
    {
        me->SummonCreature(NPC_SEDAI, 225.908, 4124.034, 82.505, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 100000);
        me->SummonCreature(NPC_ESCORT1, 229.257, 4125.271, 83.388, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 40000);
    }

    void JustSummoned(Creature* pSummoned)
    override {
        if (pSummoned->GetEntry() == NPC_ESCORT1)
        {
            pSummoned->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
            pSummoned->GetMotionMaster()->MovePoint(0, 208.029f, 4134.618f, 77.763f);
        }
    }
};

CreatureAI* GetAI_npc_sedai_quest_credit_marker(Creature* pCreature)
{
    return new npc_sedai_quest_credit_markerAI(pCreature);
}

/*######
## npc_vindicator_sedai
######*/

#define SAY_MAG_ESSCORT    -1900125
#define SAY_SEDAI1         -1900126
#define SAY_SEDAI2         -1900127
#define SAY_KRUN           -1900128

enum
{
    NPC_ESCORT        = 17417,
    NPC_AMBUSHER      = 17418,
    NPC_KRUN          = 17405,
    SPELL_STUN        = 13005,
    SPELL_HOLYFIRE    = 17141
};

struct npc_vindicator_sedaiAI : public ScriptedAI
{
    npc_vindicator_sedaiAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    bool Vision;

    uint32 uiStepsTimer;
    uint32 uiSteps;

    void Reset()
    override {
        Vision = true;
        uiStepsTimer =0;
        uiSteps = 0;
    }
    
    void EnterCombat(Unit* who) override {}

    void DoSpawnEscort()
    {
        me->SummonCreature(NPC_ESCORT, 227.188f, 4121.116f, 82.745f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 40000);
    }

    void DoSpawnAmbusher()
    {
        me->SummonCreature(NPC_AMBUSHER, 223.408f, 4120.086f, 81.843f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 30000);
    }

    void DoSpawnKrun()
    {
        me->SummonCreature(NPC_KRUN, 192.872f, 4129.417f, 73.655f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 6000);
    }

    void JustSummoned(Creature* pSummoned)
    override {
        if (pSummoned->GetEntry() == NPC_ESCORT)
        {
            pSummoned->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
            pSummoned->GetMotionMaster()->MovePoint(0, 205.660f, 4130.663f, 77.175f);
        }

        if (pSummoned->GetEntry() == NPC_AMBUSHER)
        {
            Creature* pEscort = pSummoned->FindNearestCreature(NPC_ESCORT, 15);
            pSummoned->AI()->AttackStart(pEscort);
        }
        else
        {
            if (pSummoned->GetEntry() == NPC_KRUN)
            {
                pSummoned->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
                pSummoned->GetMotionMaster()->MovePoint(0, 194.739868f, 4143.145996f, 73.798088f);
                DoScriptText(SAY_KRUN, pSummoned,nullptr);
                pSummoned->AI()->AttackStart(me);
            }
        }
    }

    void MoveInLineOfSight(Unit *who)
    override {
        if (who->GetTypeId() == TYPEID_PLAYER)
        {
            if ((who)->ToPlayer()->GetQuestStatus(9545) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature * pCr = me->FindNearestCreature(17413, 6.0f))
                {
                    float Radius = 10.0;
                    if (me->IsWithinDistInMap(who, Radius))
                    {
                        (who)->ToPlayer()->KilledMonsterCredit(17413, pCr->GetGUID());
                    }
                }
                else return;
            }
        }
    }

    uint32 NextStep(uint32 step)
    {
        Creature* pEsc = me->FindNearestCreature(NPC_ESCORT, 20);
        Creature* pAmb = me->FindNearestCreature(NPC_AMBUSHER, 35);
        Creature* pKrun = me->FindNearestCreature(NPC_KRUN, 20);

        switch(step)
        {
            case 1:
                DoSpawnEscort();
            case 2:
                me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
            case 3:
                me->GetMotionMaster()->MovePoint(0, 204.877f, 4133.172f, 76.897f);
                return 2900;
            case 4:
                DoScriptText(SAY_MAG_ESSCORT, pEsc,nullptr);
                return 1000;
            case 5:
                if (pEsc)
                    pEsc->GetMotionMaster()->MovePoint(0, 229.257f, 4125.271f, 83.388f);
                return 1500;
            case 6:
                if (pEsc)
                    pEsc->GetMotionMaster()->MovePoint(0, 227.188f, 4121.116f, 82.745f);
                return 1000;
            case 7:
                DoScriptText(SAY_SEDAI1, me,nullptr);
                return 1000;
            case 8:
                DoSpawnAmbusher();
                return 3000;
            case 9:
                DoSpawnAmbusher();
                return 1000;
            case 10:
                if (pAmb)
                    me->AI()->AttackStart(pAmb);
                return 2000;
            case 11:
                if (pAmb)
                    me->CastSpell(pAmb, SPELL_STUN , false);
                return 2000;
            case 12:
                if (pAmb)
                    pAmb->DealDamage(pAmb, pAmb->GetHealth(), nullptr, DIRECT_DAMAGE);
                return 1500;
            case 13:
                if (pEsc)
                    pEsc->DealDamage(pEsc, pEsc->GetHealth(), nullptr, DIRECT_DAMAGE);
            case 14:
                me->AI()->AttackStart(pAmb);
            case 15:
                if (pEsc && pAmb)
                    pEsc->AI()->AttackStart(pAmb);
                return 1000;
            case 16:
                if (pAmb)
                    me->CastSpell(pAmb, SPELL_HOLYFIRE , false);
                return 6000;
            case 17:
                if (pAmb)
                    pAmb->DealDamage(pAmb, pAmb->GetHealth(), nullptr, DIRECT_DAMAGE);
                return 1000;
            case 18:
                if (pEsc)
                    pEsc->GetMotionMaster()->MovePoint(0, 235.063f, 4117.826f, 84.471f);
                return 1000;
            case 19:
                me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
                me->GetMotionMaster()->MovePoint(0, 199.706f, 4134.302f, 75.404f);
                return 6000;       
            case 20:
                me->GetMotionMaster()->MovePoint(0, 193.524f, 4147.451f, 73.605f);
                return 7000;              
            case 21:
                me->SetStandState(UNIT_STAND_STATE_KNEEL);
                DoScriptText(SAY_SEDAI2, me,nullptr);
                return 5000;
            case 22:
                DoSpawnKrun();
                return 1000;
            case 23:
                if (pKrun)
                    me->CastSpell(pKrun, SPELL_HOLYFIRE, false);
                return 3000;
            case 24:
                me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE);
            default:
                return 0;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    override {
        if (uiStepsTimer <= uiDiff)
        {
            if (Vision)
                uiStepsTimer = NextStep(++uiSteps);
        }
        else uiStepsTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_vindicator_sedai(Creature* pCreature)
{
    return new npc_vindicator_sedaiAI(pCreature);
}

/*######
## npc_anchorite_barada
######*/

#define GOSSIP_ITEM_START      "Je suis prêt, Anachorète. Commençons l'exorcisme."

#define SAY_BARADA1            -1900100
#define SAY_BARADA2            -1900101
#define SAY_BARADA3            -1900104
#define SAY_BARADA4            -1900105
#define SAY_BARADA5            -1900106
#define SAY_BARADA6            -1900107
#define SAY_BARADA7            -1900108
#define SAY_BARADA8            -1900109

#define SAY_COLONEL1           -1900110
#define SAY_COLONEL2           -1900111
#define SAY_COLONEL3           -1900112
#define SAY_COLONEL4           -1900113
#define SAY_COLONEL5           -1900114
#define SAY_COLONEL6           -1900115
#define SAY_COLONEL7           -1900116
#define SAY_COLONEL8           -1900117

enum
{
    QUEST_THE_EXORCIM          = 10935,
    
    NPC_COLONEL_JULES          = 22432,
    NPC_DARKNESS_RELEASED      = 22507,
    
    SPELL_EXORCIM              = 39277,
    SPELL_EXORCIM2             = 39278,
    SPELL_COLONEL1             = 39283,         
    SPELL_COLONEL2             = 39294,
    SPELL_COLONEL3             = 39284,
    SPELL_COLONEL4             = 39294,
    SPELL_COLONEL5             = 39295,
    SPELL_COLONEL7             = 39381,
    SPELL_COLONEL8             = 39380
};

struct npc_anchorite_baradaAI : public ScriptedAI
{
    npc_anchorite_baradaAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    bool Exorcim;

    uint64 uiPlayerGUID;

    uint32 uiStepsTimer;
    uint32 uiSteps;

    float colonel;

    void Reset()
    override {
        Exorcim = false;
        uiStepsTimer = 0;
        uiSteps = 0;
        uiPlayerGUID = 0;
    }
    
    void EnterCombat(Unit* who) override {}

    void AttackedBy(Unit* pWho) override {}

    void AttackStart(Unit* pWho) override {}

    void DoSpawnDarkness()
    {
        me->SummonCreature(NPC_DARKNESS_RELEASED, -710.924, 2754.683, 105.0, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
    }

    void MoveInLineOfSight(Unit *pWho)
    override {
        if (pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if ((pWho)->ToPlayer()->GetQuestStatus(QUEST_THE_EXORCIM) == QUEST_STATUS_INCOMPLETE)
            {
                if (me->IsWithinDistInMap(((Player *)pWho), 5))
                {
                    uiPlayerGUID = pWho->GetGUID();
                }
            }
        }
    }

    uint32 NextStep(uint32 step)
    {
        Creature* pColonel = me->FindNearestCreature(NPC_COLONEL_JULES, 15);
        if (!pColonel)
            return 0;

        colonel = me->GetAngle(pColonel->GetPositionX(), pColonel->GetPositionY());

        switch(step)
        {
            case 1:me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                   pColonel->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                   me->SetStandState(UNIT_STAND_STATE_STAND);return 2000;
            case 2:DoScriptText(SAY_BARADA1, me,nullptr);return 5000;
            case 3:DoScriptText(SAY_BARADA2, me,nullptr);return 3000;
            case 4:DoScriptText(SAY_COLONEL1, pColonel, nullptr);return 3000;
            case 5:me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);return 3000;
            case 6:me->GetMotionMaster()->MovePoint(0, -707.702f, 2749.038f, 101.590f);return 2000;
            case 7:me->GetMotionMaster()->MovePoint(0, -710.810f, 2748.376f, 101.590f);return 2100;
            case 8:me->SetOrientation(colonel);
                   me->SendMovementFlagUpdate();return 2000;
            case 9:me->CastSpell(me, SPELL_EXORCIM , false);return 10000;
            case 10:DoScriptText(SAY_BARADA3, me,nullptr); return 10000;
            case 11:DoScriptText(SAY_COLONEL2, pColonel, nullptr);return 8000;
            case 12:me->RemoveAllAuras();
            case 13:me->CastSpell(me, SPELL_EXORCIM2 , false);
            case 14:pColonel->CastSpell(pColonel, SPELL_COLONEL1, false);
            case 15:pColonel->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
                    pColonel->SetSpeedRate(MOVE_RUN, 0.17f);
                    pColonel->GetMotionMaster()->MovePoint(0, -710.611f, 2753.435f, 103.774f);
                    pColonel->CastSpell(pColonel, SPELL_COLONEL3, false);return 14000;
            case 16:DoScriptText(SAY_COLONEL3, pColonel, nullptr);
                    DoSpawnDarkness();
                    DoSpawnDarkness();return 14000;
            case 17:DoScriptText(SAY_BARADA4, me, nullptr);
                    DoSpawnDarkness();
                    DoSpawnDarkness();return 14000;
            case 18:DoScriptText(SAY_COLONEL4, pColonel, nullptr);
                    DoSpawnDarkness();return 14000;
            case 19:DoScriptText(SAY_BARADA5, me, nullptr); return 14000;
            case 20:pColonel->CastSpell(pColonel, SPELL_COLONEL4, false);
                    pColonel->CastSpell(pColonel, SPELL_COLONEL2, false);
                    DoSpawnDarkness();return 1500;
            case 21:pColonel->GetMotionMaster()->MovePoint(0, -713.406f, 2744.240f, 103.774f);return 5000;
            case 22:DoScriptText(SAY_COLONEL5, pColonel, nullptr);return 1000;
            case 23:pColonel->GetMotionMaster()->MovePoint(0, -707.784f, 2749.562f, 103.774f);
                    DoSpawnDarkness();return 4000;
            case 24:pColonel->GetMotionMaster()->MovePoint(0, -708.558f, 2744.923f, 103.774f);
                    pColonel->CastSpell(me,SPELL_COLONEL5, false);return 2500;
            case 25:DoScriptText(SAY_BARADA6, me, nullptr);
            case 26:pColonel->GetMotionMaster()->MovePoint(0, -713.406f, 2744.240f, 103.774f);
                    DoSpawnDarkness();return 3500;
            case 27:pColonel->GetMotionMaster()->MovePoint(0, -714.212f, 2750.606f, 103.774f);return 4000;
            case 28:pColonel->GetMotionMaster()->MovePoint(0, -707.784f, 2749.562f, 103.774f);
                    DoScriptText(SAY_COLONEL6, pColonel, nullptr);
                    DoSpawnDarkness();return 4000;
            case 29:pColonel->GetMotionMaster()->MovePoint(0, -714.212f, 2750.606f, 103.774f);return 4000;
            case 30:pColonel->GetMotionMaster()->MovePoint(0, -707.784f, 2749.562f, 103.774f);return 4000;
            case 31: DoScriptText(SAY_BARADA7, me, nullptr); return 0;
            case 32:pColonel->GetMotionMaster()->MovePoint(0, -708.558f, 2744.923f, 103.774f);
                    DoSpawnDarkness();return 4000;
            case 33:pColonel->GetMotionMaster()->MovePoint(0, -713.406f, 2744.240f, 103.774f);return 4000;
            case 34:pColonel->GetMotionMaster()->MovePoint(0, -714.212f, 2750.606f, 103.774f);
                    DoScriptText(SAY_COLONEL7, pColonel, nullptr);
                    DoSpawnDarkness();return 4000;
            case 35:pColonel->GetMotionMaster()->MovePoint(0, -713.406f, 2744.240f, 103.774f);return 4000;
            case 36:pColonel->GetMotionMaster()->MovePoint(0, -714.212f, 2750.606f, 103.774f);
                    DoSpawnDarkness();return 4000;
            case 37:DoScriptText(SAY_BARADA6, me, nullptr);
            case 38:pColonel->GetMotionMaster()->MovePoint(0, -707.784f, 2749.562f, 103.774f);return 4000;
            case 39:pColonel->GetMotionMaster()->MovePoint(0, -708.558f, 2744.923f, 103.774f);return 4000;
            case 40:pColonel->GetMotionMaster()->MovePoint(0, -713.406f, 2744.240f, 103.774f);
                    DoScriptText(SAY_COLONEL8, pColonel, nullptr);return 4000;
            case 41:pColonel->GetMotionMaster()->MovePoint(0, -714.212f, 2750.606f, 103.774f);return 4000;
            case 42:pColonel->GetMotionMaster()->MovePoint(0, -707.784f, 2749.562f, 103.774f);return 4000;
            case 43:DoScriptText(SAY_BARADA6, me, nullptr); return 1000;
            case 44:pColonel->GetMotionMaster()->MovePoint(0, -708.558f, 2744.923f, 103.774f);return 4000;         
            case 45:pColonel->GetMotionMaster()->MovePoint(0, -713.406f, 2744.240f, 103.774f);
                    pColonel->CastSpell(pColonel, SPELL_COLONEL8, false);return 4000;
            case 46:pColonel->GetMotionMaster()->MovePoint(0, -714.212f, 2750.606f, 103.774f);
                    pColonel->CastSpell(pColonel, SPELL_COLONEL7, false);return 4000;
            case 47:pColonel->GetMotionMaster()->MovePoint(0, -710.792f, 2750.693f, 103.774f);return 5000;
            case 48:DoScriptText(SAY_BARADA8, me, nullptr); return 1000;
            case 49:pColonel->GetMotionMaster()->MovePoint(0, -710.111f, 2754.346f, 102.367f);return 3000;
            case 50:pColonel->RemoveAllAuras();
            case 51:me->RemoveAllAuras();return 2000;
            case 52:me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);return 2000;
            case 53:me->GetMotionMaster()->MovePoint(0, -706.726f, 2751.632f, 101.591f);return 2200;
            case 54:me->GetMotionMaster()->MovePoint(0, -707.382f, 2753.994f, 101.591f);return 7000;
            case 55:me->SetStandState(UNIT_STAND_STATE_KNEEL);
                    me->CombatStop();return 3000;
            case 56:pColonel->SetFlag(UNIT_NPC_FLAGS, 1);return 6000;
            case 57:me->SetFlag(UNIT_NPC_FLAGS, 1);
                    if (Player* pPlayer = ObjectAccessor::GetPlayer(*me, uiPlayerGUID))
                        pPlayer->AreaExploredOrEventHappens(QUEST_THE_EXORCIM);return 1000;
            case 58:Reset();
        default: return 0;
        }
    }

    void JustDied(Unit* pWho)
    override {
        if (Creature* pColonel = me->FindNearestCreature(NPC_COLONEL_JULES, 15.0f, true))
        {
            pColonel->GetMotionMaster()->MovePoint(0, -710.111f, 2754.346f, 102.367f);
            pColonel->RemoveAllAuras();
        }
    }

    void UpdateAI(const uint32 uiDiff)
    override {
        if (uiStepsTimer <= uiDiff)
        {
            if (Exorcim)
                uiStepsTimer = NextStep(++uiSteps);
        }
        else uiStepsTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_anchorite_barada(Creature* pCreature)
{
    return new npc_anchorite_baradaAI(pCreature);
}

bool GossipHello_npc_anchorite_barada(Player *pPlayer, Creature *pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_THE_EXORCIM) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_START, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);

    return true;
}

bool GossipSelect_npc_anchorite_barada(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        ((npc_anchorite_baradaAI*)pCreature->AI())->Exorcim = true;
        pPlayer->CLOSE_GOSSIP_MENU();
    }

    return true;
}

/*######
## npc_darkness_released
######*/

enum
{
    SPELL_AURA_ME     = 39303,
    SPELL_DARKNESS    = 39307,

    NPC_BARADA        = 22431
};

struct npc_darkness_releasedAI : public ScriptedAI
{
    npc_darkness_releasedAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    uint32 uiAtTimer;
    uint32 uiChTimer;

    void Reset()
    override {
        uiChTimer = 5000;
        uiAtTimer = 10000;

        DoCast(me, SPELL_AURA_ME);

        me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
        me->SetSpeedRate(MOVE_RUN, 0.10f);

        switch(urand(0,3))
        {
            case 0: me->GetMotionMaster()->MovePoint(0, -714.212f, 2750.606f, 105.0f); break;
            case 1: me->GetMotionMaster()->MovePoint(0, -713.406f, 2744.240f, 105.0f); break;
            case 2: me->GetMotionMaster()->MovePoint(0, -707.784f, 2749.562f, 105.0f); break;
            case 3: me->GetMotionMaster()->MovePoint(0, -708.558f, 2744.923f, 105.0f); break;
        }
    }
    
    void EnterCombat(Unit* who) override {}

    void AttackedBy(Unit* pWho) override {}

    void AttackStart(Unit* pWho) override {}

    void JustDied(Unit* pWho)
    override {
        me->RemoveCorpse();
    }

    void UpdateAI(const uint32 uiDiff)
    override {
        if (uiAtTimer <= uiDiff)
        {
            DoCast(me, SPELL_DARKNESS);

            switch (urand(0,3))
            {
                case 0: me->GetMotionMaster()->MovePoint(0, -714.212f, 2750.606f, 105.0f); break;
                case 1: me->GetMotionMaster()->MovePoint(0, -713.406f, 2744.240f, 105.0f); break;
                case 2: me->GetMotionMaster()->MovePoint(0, -707.784f, 2749.562f, 105.0f); break;
                case 3: me->GetMotionMaster()->MovePoint(0, -708.558f, 2744.923f, 105.0f); break;
            }

            uiAtTimer = 10000;
        }
        else uiAtTimer -= uiDiff;

        if (uiChTimer <= uiDiff)
        {
            if (Creature* pBar = me->FindNearestCreature(NPC_BARADA, 15.0f, false))
                me->SetDeathState(CORPSE);

            if (Creature* pBara = me->FindNearestCreature(NPC_BARADA, 15.0f, true))
            {
                if (!pBara->HasAuraEffect(SPELL_EXORCIM2, 0))
                    me->SetDeathState(CORPSE);
            }
            uiChTimer = 5000;
        }
        else uiChTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_darkness_released(Creature* pCreature)
{
    return new npc_darkness_releasedAI(pCreature);
}

/*######
## npc_foul_purge
######*/

struct npc_foul_purgeAI : public ScriptedAI
{
    npc_foul_purgeAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    uint32 uiChTimer;

    void Reset()
    override {
        if (Creature* pBara = me->FindNearestCreature(NPC_BARADA, 15.0f, true))
        {
            AttackStart(pBara);
        }

        uiChTimer = 4000;
    }
    
    void EnterCombat(Unit* who) override {}
    
    void JustDied(Unit* pWho)
    override {
        me->RemoveCorpse();
    }

    void UpdateAI(const uint32 uiDiff)
    override {
        if (uiChTimer <= uiDiff)
        {
            if (Creature* pBar = me->FindNearestCreature(NPC_BARADA, 15.0f, false))
                me->SetDeathState(CORPSE);

            if (Creature* pBara = me->FindNearestCreature(NPC_BARADA, 15.0f, true))
            {
                if (!pBara->HasAuraEffect(SPELL_EXORCIM2, 0))
                    me->SetDeathState(CORPSE);
            }

            uiChTimer = 4000;
        }
        else uiChTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_foul_purge(Creature* pCreature)
{
    return new npc_foul_purgeAI(pCreature);
}

/*
This invisible controller handle the demons paths and respawns for the Dark Portal permanent event

//inforno cooldown: 2 minutes
//2 infernals
//remove infernals spawn
*/

class FelSoldier : public CreatureScript
{
public:
	FelSoldier() : CreatureScript("fel_soldier") {}

	class FelSoldierAI : public CreatureAI
	{
	public:
		FelSoldierAI(Creature* creature) : CreatureAI(creature)
		{}
	};

	CreatureAI* GetAI(Creature* creature) const
		override
	{
		return new FelSoldierAI(creature);
	}
};


class DarkPortalEventDemonAI : public ScriptedAI
{
public:
	bool reachedHome;
	uint32 lastPathNodeID;

	DarkPortalEventDemonAI(Creature* creature) : ScriptedAI(creature) 
	{
		reachedHome = false;
		lastPathNodeID = 0;
	}
						
	enum Message
	{
		SET_PATH_ID,         //message: uint64 with pathID on the first 32 bits, lastNodeID on the 32 next.
		HAS_REACHED_HOME,    //returns 0 or 1
	};
	
	uint64 message(uint32 id, uint64 data) override
	{
		switch (id)
		{
			case SET_PATH_ID:
			{
				uint32 pathID = data & 0xFFFFFFFF;
				uint32 lastPointID = (data & 0xFFFFFFFF00000000) >> 32;

				if (pathID == 0 || lastPointID == 0)
				{
					TC_LOG_ERROR("scripts", "DarkPortalEventDemonAI received null pathID (%u) or lastPathNodeID (%u)", pathID, lastPathNodeID);
					return 0;
				}

				reachedHome = false;
				me->GetMotionMaster()->MovePath(pathID);
				lastPathNodeID = lastPointID;

				//set path type as WP_PATH_TYPE_ONCE
				MovementGenerator* movGen = me->GetMotionMaster()->GetMotionSlot(MOTION_SLOT_ACTIVE);
				if (WaypointMovementGenerator<Creature>* wpMovGen = dynamic_cast<WaypointMovementGenerator<Creature>*>(movGen))
				{
					wpMovGen->SetPathType(WaypointPathType::WP_PATH_TYPE_ONCE);
				}
				else {
					TC_LOG_ERROR("scripts", "DarkPortalEventDemonAI, cannot set path type to WP_PATH_TYPE_ONCE.");
				}
				break;
			}
			case HAS_REACHED_HOME:
			{
				return reachedHome;
				break;
			}
		}
		return 0;
	}

	void JustReachedHome() override
	{
		reachedHome = true;
	}

	void MovementInform(uint32 motionType, uint32 nodeID) override
	{
		if (motionType == WAYPOINT_MOTION_TYPE && nodeID == lastPathNodeID)
		{
			//we've arrived at our path end, lets break formation and go to our designed place
			if (me->GetFormation() && me->GetFormation()->getLeader() == me)
				sCreatureGroupMgr->BreakFormation(me);

			me->GetMotionMaster()->MoveTargetedHome();

		}
	}

	void Reset() override
	{

	}

	void UpdateAI(const uint32 diff)
		override
	{
		//todo: this check on timer ?
		if (!reachedHome
			&& me->GetMotionMaster()->GetMotionSlotType(MOTION_SLOT_ACTIVE) != WAYPOINT_MOTION_TYPE 
			&& me->GetMotionMaster()->GetMotionSlotType(MOTION_SLOT_ACTIVE) != HOME_MOTION_TYPE 
			&& !me->IsInCombat())
		{
			me->GetMotionMaster()->MoveTargetedHome();
		}
	}
};


class DarkPortalEventPitLord : public CreatureScript
{
public:
	DarkPortalEventPitLord() : CreatureScript("dark_portal_event_pit_lord") {}

	class DarkPortalEventPitLordAI : public DarkPortalEventDemonAI
	{
	public:
		DarkPortalEventPitLordAI(Creature* creature) : DarkPortalEventDemonAI(creature) {}

		void UpdateAI(const uint32 diff)
			override
		{
			DarkPortalEventDemonAI::UpdateAI(diff);

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* creature) const
		override
	{
		return new DarkPortalEventPitLordAI(creature);
	}
};

class DarkPortalEventFelSoldier : public CreatureScript
{
public:
	DarkPortalEventFelSoldier() : CreatureScript("dark_portal_event_fel_soldier") {}

	class DarkPortalEventFelSoldierAI : public DarkPortalEventDemonAI
	{
	public:
		DarkPortalEventFelSoldierAI(Creature* creature) : DarkPortalEventDemonAI(creature) {}

		void UpdateAI(const uint32 diff)
			override
		{
			DarkPortalEventDemonAI::UpdateAI(diff);

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* creature) const
		override
	{
		return new DarkPortalEventFelSoldierAI(creature);
	}
};

class DarkPortalEventWrathMaster : public CreatureScript
{
public:
	DarkPortalEventWrathMaster() : CreatureScript("dark_portal_event_wrath_master") {}

	class DarkPortalEventWrathMasterAI : public DarkPortalEventDemonAI
	{
	public:
		DarkPortalEventWrathMasterAI(Creature* creature) : DarkPortalEventDemonAI(creature) {}

		void UpdateAI(const uint32 diff)
			override
		{
			DarkPortalEventDemonAI::UpdateAI(diff);

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* creature) const
		override
	{
		return new DarkPortalEventWrathMasterAI(creature);
	}
};

class DarkPortalEventController : public CreatureScript
{
public:
	DarkPortalEventController() : CreatureScript("dark_portal_event_controller") {}

	static uint32 const DEMON_COMMON_PATH = 12949601;

	struct DemonSummonInfo
	{
		Position const pos;
		uint32 const npcId;
		uint64 guid;
		bool dead;
	};
	
	enum DemonsControllerEvent
	{
		EVENT_CHECK_DEADS = 1,
		EVENT_SEND_SIEGE_BREAKERS, //infernos
		EVENT_SEND_ATTACK_WAVE,
	};

	static uint32 const SUMMON_WAVE_SIZE = 5;
	static uint32 const ATTACK_WAVE_SIZE = 5;
	static uint32 const SPELL_SUMMON_INFERNALS = 33393;

	class DarkPortalEventControllerAI : public ScriptedAI
	{
	public:
		DarkPortalEventControllerAI(Creature* creature) : ScriptedAI(creature) 
		{
            uint32 pathId = DarkPortalEventController::DEMON_COMMON_PATH;
			auto path = sWaypointMgr->GetPath(pathId);
			if (!path->empty())
				LAST_POINT = path->back()->id;

			if (LAST_POINT == 0)
			{
				TC_LOG_ERROR("scripts", "DarkPortalEventControllerAI couldnt get last point for path %u", pathId);
				LAST_POINT = 1; //maybe we can recover from this, consider second point as last point
			}
		}

		uint32 LAST_POINT = 0;

		Position const teleporter1Pos =  { -145.65f, 1510.66f, 33.47f };
		Position const teleporter2Pos =  { -303.70f, 1525.00f, 37.88f };
		Position const pitlordSpawnPos = { -210.12f, 1574.15f, 28.8f };
		Position const attackPos =       { -252.23f, 1094.34f, 41.67f }; //point demons will try to get to when attacking

		// 18944 : fel soldier
		// 19005 : wrath master
		std::vector<DemonSummonInfo> demonSummons
		{
			{ Position(-198.475, 1152.46, 41.5387, 4.649050), 18944, 0, false },
			{ Position(-204.212, 1163.39, 42.7747, 4.649050), 18944, 0, false },
			{ Position(-209.724, 1153.05, 41.5781, 4.649050), 18944, 0, false },
			{ Position(-209.911, 1171.92, 42.4926, 4.649050), 18944, 0, false },
			{ Position(-215.193, 1164.25, 42.3766, 4.649050), 18944, 0, false },
			{ Position(-220.91, 1172.25, 41.6198, 4.649050), 18944, 0, false },
			{ Position(-231.111, 1172.32, 41.5725, 4.649050), 19005, 0, false },
			{ Position(-241.049, 1150.11, 41.651, 4.649050), 18944, 0, false },
			{ Position(-250.012, 1150.5, 41.651, 4.649050), 18944, 0, false },
			{ Position(-259.584, 1150.61, 41.651, 4.649050), 18944, 0, false },
			{ Position(-267.838, 1170.1, 41.6599, 4.649050), 19005, 0, false },
			{ Position(-278.802, 1169.95, 41.7551, 4.649050), 18944, 0, false },
			{ Position(-283.887, 1162.71, 41.2736, 4.649050), 18944, 0, false },
			{ Position(-289.163, 1155.73, 41.2988, 4.649050), 18944, 0, false },
			{ Position(-290.59, 1170.37, 41.7875, 4.649050), 18944, 0, false },
			{ Position(-295.487, 1162.31, 41.0212, 4.649050), 18944, 0, false },
			{ Position(-300.381, 1155.92, 41.223, 4.649050), 18944, 0, false },
		};
		
		DemonSummonInfo pitlordInfo = { Position(-248.82f, 1176.17f, 41.6652f, 4.69f), 18945, 0, false };

		EventMap events;

		uint32 GetDeadDemonsCount()
		{
			for (auto & demonSummon : demonSummons)
				UpdateDemonDeadState(demonSummon);

			uint32 count = 0;
			for (auto & demonSummon : demonSummons)
				if (demonSummon.dead)
					count++;

			return count;
		}

		void RemoveDemon(DemonSummonInfo& summonInfo)
		{
			if (summonInfo.guid)
			{
				if (Creature* c = me->GetMap()->GetCreature(summonInfo.guid))
					c->DisappearAndDie();

				summonInfo.guid = 0;
				summonInfo.dead = true;
			}
		}

		Creature* SpawnDemon(DemonSummonInfo& summonInfo, Position const* pos = nullptr)
		{
			Position const& summonPos = pos ? *pos : summonInfo.pos;
			if (Creature* c = me->SummonCreature(summonInfo.npcId, summonPos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30 * SECOND * IN_MILLISECONDS))
			{
				c->SetKeepActiveTimer(3 * MINUTE * IN_MILLISECONDS); //force active for a while so that creatures can get to their position
				c->SetHomePosition(summonInfo.pos);
				summonInfo.guid = c->GetGUID();
				summonInfo.dead = false;
				return c;
			}
			return nullptr;
		}

		void InitDemons()
		{
			//remove demons already present
			for (auto & demonSummon : demonSummons)
				RemoveDemon(demonSummon);

			RemoveDemon(pitlordInfo);

			//summon new ones
			for (auto & demonSummon : demonSummons)
				SpawnDemon(demonSummon);
				
			SpawnDemon(pitlordInfo);
		}

		void SummonDemonFormation(std::vector<DemonSummonInfo*>& info)
		{
			Position const& summonPos = (rand() % 2) ? teleporter1Pos : teleporter2Pos;
			std::vector<Creature*> justSummoned;
			for (auto itr : info)
			{
				if (Creature* c = SpawnDemon(*itr, &summonPos))
					justSummoned.push_back(c);
			}

			if (justSummoned.size() < 2)
			{
				TC_LOG_ERROR("scripts", "DarkPortalEventControllerAI::SummonDemonFormation could not find enough demons to compose a formation");
				return;
			}

			Creature* leader = justSummoned[0];
			sCreatureGroupMgr->AddCreatureToGroup(leader->GetGUIDLow(), leader);
			//spawn other in wedge formation
			for (uint8 i = 1; i < justSummoned.size(); i++)
			{
				Creature* member = justSummoned[i];
				MemberPosition pos;
				pos.follow_dist = i == 1 ? 6.0f : 6.0f * ((i-1) / 2 + 1);
				pos.follow_angle = i % 2 ? 2.1f : 4.2f; //a little behind, to the left or to the right
				sCreatureGroupMgr->AddCreatureToGroup(leader->GetGUIDLow(), member, &pos);
			}

			uint64 message = DarkPortalEventController::DEMON_COMMON_PATH;
			message += uint64(LAST_POINT) << 32; //see DarkPortalEventDemonAI::SET_PATH_ID comment
			leader->AI()->message(DarkPortalEventDemonAI::SET_PATH_ID, message);
		}

		//summon up to 5 demons from the demon teleporter
		void SummonDemonWave()
		{
			std::vector<DemonSummonInfo*> toSummon;
			for (auto & demonSummon : demonSummons)
			{
				if (demonSummon.dead)
					toSummon.push_back(&demonSummon);

				if (toSummon.size() >= SUMMON_WAVE_SIZE)
					break;
			}

			//not enough demons to summon, abort
			if (toSummon.size() < SUMMON_WAVE_SIZE)
				return;

			SummonDemonFormation(toSummon);
		}

		void SummonPitlord()
		{
			if (Creature* c = me->SummonCreature(pitlordInfo.npcId, pitlordSpawnPos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30 * SECOND * IN_MILLISECONDS))
			{
				pitlordInfo.guid = c->GetGUID();
				pitlordInfo.dead = false;
			}
		}

		Creature* GetPitLord()
		{
			return me->GetMap()->GetCreature(pitlordInfo.guid);
		}

		/*
		Wowhead:	Every minute or so, the Pit Commander at the Dark Portal will cast a spell, making two huge meteors hit the ground near the stairs, and out of the meteors comes 2 of these mobs. 
					If you're hit by the large AoE blast that comes as they hit the ground, you take roughly 3500 damage. Their attack hits everything in front of it, which can be very annoying 
					if you're trying to get past them, but it only hits for about 500 damage each swing.
		*/
		void SummonSiegeBreakers()
		{
			Creature* pitLord = GetPitLord();
			if (!pitLord)
				return;

			pitLord->CastSpell(pitLord, SPELL_SUMMON_INFERNALS, false);
			//spell script in its own class below
		}

		void SendAttackWave()
		{
			std::vector<Creature*> attackWave;

			//get creatures
			for (auto & demonSummon : demonSummons)
			{
				if (demonSummon.dead)
					continue;

				Creature* c = me->GetMap()->GetCreature(demonSummon.guid);
				if (!c)
					continue;

				if (c->AI()->message(DarkPortalEventDemonAI::HAS_REACHED_HOME, 0) == 0)
					continue;

				attackWave.push_back(c);

				if (attackWave.size() >= ATTACK_WAVE_SIZE)
					break;
			}

			//send them
			for (auto itr : attackWave)
			{
				itr->GetMotionMaster()->MovePoint(0, attackPos);
			}

			Creature* pitLord = GetPitLord();
			if(pitLord)
				pitLord->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
		}

		void Reset() override
		{
			InitDemons();

			events.Reset();
			events.ScheduleEvent(EVENT_CHECK_DEADS, 1000);
			events.ScheduleEvent(EVENT_SEND_ATTACK_WAVE, 1000);
			events.ScheduleEvent(EVENT_SEND_SIEGE_BREAKERS, 30000);
		}

		//update demon death state, set to dead if not found
		void UpdateDemonDeadState(DemonSummonInfo& info)
		{
			if (Creature* c = me->GetMap()->GetCreature(info.guid))
				info.dead = !c->IsAlive();
			else
				info.dead = true;
		}

		bool IsPitLordDead()
		{
			UpdateDemonDeadState(pitlordInfo);
			return pitlordInfo.dead;
		}

		void UpdateAI(const uint32 diff)
			override 
		{
			events.Update(diff);

			switch (events.ExecuteEvent())
			{
			case EVENT_CHECK_DEADS:
				if (GetDeadDemonsCount() >= 5)
					SummonDemonWave();

				if (IsPitLordDead())
					SummonPitlord();

				events.RescheduleEvent(EVENT_CHECK_DEADS, 1 * MINUTE * IN_MILLISECONDS);
				break;
			case EVENT_SEND_SIEGE_BREAKERS:
				SummonSiegeBreakers();
				events.RescheduleEvent(EVENT_SEND_SIEGE_BREAKERS, 90 * SECOND * IN_MILLISECONDS);
				break;
			case EVENT_SEND_ATTACK_WAVE:
				SendAttackWave();
				events.RescheduleEvent(EVENT_SEND_ATTACK_WAVE, 90 * SECOND * IN_MILLISECONDS);
				break;
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const
		override 
	{
		return new DarkPortalEventControllerAI(creature);
	}
};

/*
Infernal spells:
Main spell: 33393, will cast 32148 x 2 (infernal missiles) to defenders, from nearby NPC_INFERNAL_RELAY (id 19215)
32148 will cast 32150 on each target.
32150 apply the damage and the stun
*/

//spell 33393
class spell_summon_infernals : public SpellScriptLoader
{
public:
	spell_summon_infernals() : SpellScriptLoader("spell_summon_infernals") { }
	
	class spell_summon_infernals_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_summon_infernals_SpellScript);

		// missile spell
		static uint32 const SPELL_INFERNAL_MISSILE = 32148;
		// starting point
		static uint32 const NPC_INFERNAL_RELAY = 19215;
		// missile target
		Position const infernalTargets = { -252.23f, 1094.34f, 41.67f };
		static uint32 const INFERNAL_COUNT = 2;

		void CastInfernalMissiles()
		{
			std::list<Creature*> relaysList;
			FindCreatures(relaysList, NPC_INFERNAL_RELAY, 100.0f, GetCaster());
			
			std::vector<Creature*> relaysVector { std::begin(relaysList), std::end(relaysList) };

			if (relaysVector.empty())
				return;

			for (uint8 i = 0; i < INFERNAL_COUNT; i++)
			{
				//randomize target a bit
				float x, y, z;
				GetCaster()->GetRandomPoint(infernalTargets, 10.0f, x, y, z);

				//each infernal from a different relay
				Creature* relay = relaysVector[i % relaysVector.size()];
				relay->CastSpell(x, y, z, SPELL_INFERNAL_MISSILE, true);
			}
		}

		void Register() override
		{
			OnCast += SpellCastFn(spell_summon_infernals_SpellScript::CastInfernalMissiles);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_summon_infernals_SpellScript();
	}
};

//spell 32148
class spell_infernal_missile : public SpellScriptLoader
{
public:
	spell_infernal_missile() : SpellScriptLoader("spell_infernal_missile") { }

	class spell_infernal_missile_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_infernal_missile_SpellScript);

		Position const infernalTargets = { -252.23f, 1094.34f, 41.67f };
		static uint32 const NPC_SIEGE_BREAKER = 18946;

		void HandleHit(SpellEffIndex i)
		{
			//should be two ? // for (uint8 i : { 0, 1 })
				GetCaster()->SummonCreature(NPC_SIEGE_BREAKER, *(GetExplTargetDest()), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30 * SECOND * IN_MILLISECONDS);
		}

		void Register() override
		{
			OnEffectHit += SpellEffectFn(spell_infernal_missile_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_infernal_missile_SpellScript();
	}
};

/*######
## AddSC
######*/

void AddSC_hellfire_peninsula()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name = "npc_aeranas";
    newscript->GetAI = &GetAI_npc_aeranas;
    sScriptMgr->RegisterOLDScript(newscript);

    new HaaleshiAltar();

    newscript = new OLDScript;
    newscript->Name="npc_wing_commander_dabiree";
    newscript->OnGossipHello =   &GossipHello_npc_wing_commander_dabiree;
    newscript->OnGossipSelect =  &GossipSelect_npc_wing_commander_dabiree;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_gryphoneer_leafbeard";
    newscript->OnGossipHello = &GossipHello_npc_gryphoneer_leafbeard;
    newscript->OnGossipSelect = &GossipSelect_npc_gryphoneer_leafbeard;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_gryphoneer_windbellow";
    newscript->OnGossipHello =   &GossipHello_npc_gryphoneer_windbellow;
    newscript->OnGossipSelect =  &GossipSelect_npc_gryphoneer_windbellow;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_wing_commander_brack";
    newscript->OnGossipHello =   &GossipHello_npc_wing_commander_brack;
    newscript->OnGossipSelect =  &GossipSelect_npc_wing_commander_brack;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_wounded_blood_elf";
    newscript->GetAI = &GetAI_npc_wounded_blood_elf;
    newscript->OnQuestAccept = &QuestAccept_npc_wounded_blood_elf;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name="npc_demoniac_scryer";
    newscript->GetAI = &GetAI_npc_demoniac_scryer;
    newscript->OnGossipHello = &GossipHello_npc_demoniac_scryer;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name="npc_fel_guard_hound";
    newscript->GetAI = &GetAI_npc_fel_guard_hound;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name="npc_anchorite_relic";
    newscript->GetAI = &GetAI_npc_anchorite_relic;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_living_flare";
    newscript->GetAI = &GetAI_npc_living_flare;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_ancestral_wolf";
    newscript->GetAI = &GetAI_npc_ancestral_wolf;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_pathaleon_image";
    newscript->GetAI = &GetAI_npc_pathaleon_image;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_demoniac_scryer";
    newscript->OnGossipHello =  &GossipHello_npc_demoniac_scryer;
    newscript->OnGossipSelect = &GossipSelect_npc_demoniac_scryer;
    newscript->GetAI = &GetAI_npc_demoniac_scryer;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_magic_sucker_device_spawner";
    newscript->GetAI = &GetAI_npc_magic_sucker_device_spawner;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_sedai_quest_credit_marker";
    newscript->GetAI = &GetAI_npc_sedai_quest_credit_marker;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_vindicator_sedai";
    newscript->GetAI = &GetAI_npc_vindicator_sedai;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_anchorite_barada";
    newscript->OnGossipHello =  &GossipHello_npc_anchorite_barada;
    newscript->OnGossipSelect = &GossipSelect_npc_anchorite_barada;
    newscript->GetAI = &GetAI_npc_anchorite_barada;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_darkness_released";
    newscript->GetAI = &GetAI_npc_darkness_released;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_foul_purge";
    newscript->GetAI = &GetAI_npc_foul_purge;
    sScriptMgr->RegisterOLDScript(newscript);

	new DarkPortalEventController();
	new spell_summon_infernals();
	new spell_infernal_missile();
	new DarkPortalEventWrathMaster();
	new DarkPortalEventFelSoldier();
	new DarkPortalEventPitLord();
}
