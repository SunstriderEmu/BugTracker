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
SDName: Moonglade
SD%Complete: 100
SDComment: Quest support: 30, 272, 5929, 5930, 10965. Special Flight Paths for Druid class.
SDCategory: Moonglade
EndScriptData */

/* ContentData
npc_bunthen_plainswind
npc_great_bear_spirit
npc_silva_filnaveth
npc_clintar_spirit
npc_clintar_dreamwalker
EndContentData */


#include "EscortAI.h"
#include "Pet.h"
#include "World.h"
#include "TemporarySummon.h"

/*######
## npc_bunthen_plainswind
######*/

#define GOSSIP_BP1 "Do you know where I can find Half Pendant of Aquatic Endurance?"
#define GOSSIP_BP2 "I'd like to fly to Thunder Bluff."

bool GossipHello_npc_bunthen_plainswind(Player* pPlayer, Creature* pCreature)
{
    if(pPlayer->GetClass() != CLASS_DRUID)
        pPlayer->SEND_GOSSIP_MENU_TEXTID(4916, pCreature->GetGUID());
    else if(pPlayer->GetTeam() != TEAM_HORDE)
    {
        if(pPlayer->GetQuestStatus(272) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BP1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        pPlayer->SEND_GOSSIP_MENU_TEXTID(4917,pCreature->GetGUID());
    }
    else if(pPlayer->GetClass() == CLASS_DRUID && pPlayer->GetTeam() == TEAM_HORDE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BP2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if(pPlayer->GetQuestStatus(30) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BP1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        pPlayer->SEND_GOSSIP_MENU_TEXTID(4918, pCreature->GetGUID());
    }
    return true;
}

bool GossipSelect_npc_bunthen_plainswind(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action )
{
    switch(action)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            if (pPlayer->GetClass() == CLASS_DRUID && pPlayer->GetTeam() == TEAM_HORDE)
            {
                std::vector<uint32> nodes;

                nodes.resize(2);
                nodes[0] = 63;                              // Nighthaven, Moonglade
                nodes[1] = 22;                              // Thunder Bluff, Mulgore
                pPlayer->ActivateTaxiPathTo(nodes);
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->SEND_GOSSIP_MENU_TEXTID(5373, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->SEND_GOSSIP_MENU_TEXTID(5376, pCreature->GetGUID());
            break;
    }
    return true;
}

/*######
## npc_great_bear_spirit
######*/

#define GOSSIP_BEAR1 "What do you represent, spirit?"
#define GOSSIP_BEAR2 "I seek to understand the importance of strength of the body."
#define GOSSIP_BEAR3 "I seek to understand the importance of strength of the heart."
#define GOSSIP_BEAR4 "I have heard your words, Great Bear Spirit, and I understand. I now seek your blessings to fully learn the way of the Claw."

bool GossipHello_npc_great_bear_spirit(Player* pPlayer, Creature* pCreature)
{
    //ally or horde quest
    if (pPlayer->GetQuestStatus(5929) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(5930) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_BEAR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        pPlayer->SEND_GOSSIP_MENU_TEXTID(4719, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU_TEXTID(4718, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_great_bear_spirit(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action )
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(4721, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(4733, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(4734, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->SEND_GOSSIP_MENU_TEXTID(4735, pCreature->GetGUID());
            if (pPlayer->GetQuestStatus(5929) == QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(5929);
            if (pPlayer->GetQuestStatus(5930) == QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(5930);
            break;
    }
    
    return true;
}

/*######
## npc_silva_filnaveth
######*/

#define GOSSIP_SF1 "Do you know where I can find Half Pendant of Aquatic Agility?"
#define GOSSIP_SF2 "I'd like to fly to Rut'theran Village."

bool GossipHello_npc_silva_filnaveth(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetClass() != CLASS_DRUID)
        pPlayer->SEND_GOSSIP_MENU_TEXTID(4913, pCreature->GetGUID());
    else if (pPlayer->GetTeam() != TEAM_ALLIANCE)
    {
        if (pPlayer->GetQuestStatus(30) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SF1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        pPlayer->SEND_GOSSIP_MENU_TEXTID(4915, pCreature->GetGUID());
    }
    else if (pPlayer->GetClass() == CLASS_DRUID && pPlayer->GetTeam() == TEAM_ALLIANCE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SF2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if (pPlayer->GetQuestStatus(272) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SF1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        pPlayer->SEND_GOSSIP_MENU_TEXTID(4914, pCreature->GetGUID());
    }
    
    return true;
}

bool GossipSelect_npc_silva_filnaveth(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action )
{
    switch(action)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            if (pPlayer->GetClass() == CLASS_DRUID && pPlayer->GetTeam() == TEAM_ALLIANCE)
            {
                std::vector<uint32> nodes;

                nodes.resize(2);
                nodes[0] = 62;                              // Nighthaven, Moonglade
                nodes[1] = 27;                              // Rut'theran Village, Teldrassil
                pPlayer->ActivateTaxiPathTo(nodes);
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->SEND_GOSSIP_MENU_TEXTID(5374, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->SEND_GOSSIP_MENU_TEXTID(5375, pCreature->GetGUID());
            break;
    }
    
    return true;
}

/*######
## npc_clintar_spirit
######*/

float Clintar_spirit_WP[41][5] =
{
 //pos_x   pos_y    pos_z    orien waitTime
{7465.28, -3115.46, 439.327, 0.83, 4000},
{7476.49, -3101,    443.457, 0.89, 0},
{7486.57, -3085.59, 439.478, 1.07, 0},
{7472.19, -3085.06, 443.142, 3.07, 0},
{7456.92, -3085.91, 438.862, 3.24, 0},
{7446.68, -3083.43, 438.245, 2.40, 0},
{7446.17, -3080.21, 439.826, 1.10, 6000},
{7452.41, -3085.8,  438.984, 5.78, 0},
{7469.11, -3084.94, 443.048, 6.25, 0},
{7483.79, -3085.44, 439.607, 6.25, 0},
{7491.14, -3090.96, 439.983, 5.44, 0},
{7497.62, -3098.22, 436.854, 5.44, 0},
{7498.72, -3113.41, 434.596, 4.84, 0},
{7500.06, -3122.51, 434.749, 5.17, 0},
{7504.96, -3131.53, 434.475, 4.74, 0},
{7504.31, -3133.53, 435.693, 3.84, 6000},
{7504.55, -3133.27, 435.476, 0.68, 15000},
{7501.99, -3126.01, 434.93,  1.83, 0},
{7490.76, -3114.97, 434.431, 2.51, 0},
{7479.64, -3105.51, 431.123, 1.83, 0},
{7474.63, -3086.59, 428.994, 1.83, 2000},
{7472.96, -3074.18, 427.566, 1.57, 0},
{7472.25, -3063,    428.268, 1.55, 0},
{7473.46, -3054.22, 427.588, 0.36, 0},
{7475.08, -3053.6,  428.653, 0.36, 6000},
{7474.66, -3053.56, 428.433, 3.19, 4000},
{7471.81, -3058.84, 427.073, 4.29, 0},
{7472.16, -3064.91, 427.772, 4.95, 0},
{7471.56, -3085.36, 428.924, 4.72, 0},
{7473.56, -3093.48, 429.294, 5.04, 0},
{7478.94, -3104.29, 430.638, 5.23, 0},
{7484.46, -3109.61, 432.769, 5.79, 0},
{7490.23, -3111.08, 434.431, 0.02, 0},
{7496.29, -3108,    434.783, 1.15, 0},
{7497.46, -3100.66, 436.191, 1.50, 0},
{7495.64, -3093.39, 438.349, 2.10, 0},
{7492.44, -3086.01, 440.267, 1.38, 0},
{7498.26, -3076.44, 440.808, 0.71, 0},
{7506.4,  -3067.35, 443.64,  0.77, 0},
{7518.37, -3057.42, 445.584, 0.74, 0},
{7517.51, -3056.3,  444.568, 2.49, 4500}
};

enum eClintarSpirit
{
ASPECT_RAVEN                        = 22915,

CLINTAR_SPIRIT_SAY_START            = -1000286,
CLINTAR_SPIRIT_SAY_UNDER_ATTACK_1   = -1000287,
CLINTAR_SPIRIT_SAY_UNDER_ATTACK_2   = -1000288,
CLINTAR_SPIRIT_SAY_GET_ONE          = -1000289,
CLINTAR_SPIRIT_SAY_GET_TWO          = -1000290,
CLINTAR_SPIRIT_SAY_GET_THREE        = -1000291,
CLINTAR_SPIRIT_SAY_GET_FINAL        = -1000292
};

#define ASPECT_RAVEN_SUMMON_X               7472.96
#define ASPECT_RAVEN_SUMMON_Y               -3074.18
#define ASPECT_RAVEN_SUMMON_Z               427.566
#define CLINTAR_SPIRIT_SUMMON_X             7459.2275
#define CLINTAR_SPIRIT_SUMMON_Y             -3122.5632
#define CLINTAR_SPIRIT_SUMMON_Z             438.9842
#define CLINTAR_SPIRIT_SUMMON_O             0.8594

struct npc_clintar_spiritAI : public npc_escortAI
{
public:
    npc_clintar_spiritAI(Creature *c) : npc_escortAI(c) {}

    uint32 Step;
    uint32 CurrWP;
    uint32 Event_Timer;
    uint32 checkPlayer_Timer;

    uint64 PlayerGUID;

    bool Event_onWait;

    void Reset()
    override {
        if(!PlayerGUID)
        {
            Step = 0;
            CurrWP = 0;
            Event_Timer = 0;
            PlayerGUID = 0;
            checkPlayer_Timer = 1000;
            Event_onWait = false;
        }
    }

    void JustDied(Unit* pKiller)
    override {
        if(!PlayerGUID)
            return;

        Player* player = (ObjectAccessor::GetUnit((*me), PlayerGUID))->ToPlayer();
        if(player && player->GetQuestStatus(10965) == QUEST_STATUS_INCOMPLETE)
        {
            player->FailQuest(10965);
            PlayerGUID = 0;
            Reset();
        }
    }

    void EnterEvadeMode(EvadeReason why)
    override {
        Player* player = (ObjectAccessor::GetUnit((*me), PlayerGUID))->ToPlayer();
        if(player && player->IsInCombat() && player->GetAttackerForHelper())
        {
            AttackStart(player->GetAttackerForHelper());
            return;
        }
        
        npc_escortAI::EnterEvadeMode(why);
    }

    void EnterCombat(Unit* pWho)
    override {
        uint32 rnd = rand()%2;
        switch(rnd)
        {
            case 0: DoScriptText(CLINTAR_SPIRIT_SAY_UNDER_ATTACK_1, me, pWho); break;
            case 1: DoScriptText(CLINTAR_SPIRIT_SAY_UNDER_ATTACK_2, me, pWho); break;
        }
    }

    void StartEvent(Player* pPlayer)
    {
        if(!pPlayer)
            return;
            
        if(pPlayer->GetQuestStatus(10965) == QUEST_STATUS_INCOMPLETE)
        {
            for(uint8 i = 0; i < 41; ++i)
            {
                AddWaypoint(i, Clintar_spirit_WP[i][0], Clintar_spirit_WP[i][1], Clintar_spirit_WP[i][2], (uint32)Clintar_spirit_WP[i][4]);
            }
            PlayerGUID = pPlayer->GetGUID();
            Start(true, true, false, PlayerGUID);
        }
        return;
    }

    void UpdateAI(const uint32 diff)
    override {
        npc_escortAI::UpdateAI(diff);

        if(!PlayerGUID)
        {
            me->SetDeathState(JUST_DIED);
            return;
        }

        if(!me->IsInCombat() && !Event_onWait && checkPlayer_Timer < diff)
        {
            Player* player = (ObjectAccessor::GetUnit((*me), PlayerGUID))->ToPlayer();
            if(player && player->IsInCombat() && player->GetAttackerForHelper())
                AttackStart(player->GetAttackerForHelper());
            checkPlayer_Timer = 1000;
        } else if(!me->IsInCombat() && !Event_onWait) checkPlayer_Timer -= diff;

        if(Event_onWait && Event_Timer < diff)
        {

            Player* player = (ObjectAccessor::GetUnit((*me), PlayerGUID))->ToPlayer();
            if(!player || (player && player->GetQuestStatus(10965) == QUEST_STATUS_NONE))
            {
                me->SetDeathState(JUST_DIED);
                return;
            }

            switch(CurrWP)
            {
                case 0:
                    switch(Step)
                    {
                        case 0:
                            me->old_Say(CLINTAR_SPIRIT_SAY_START, 0, PlayerGUID);
                            Event_Timer = 8000;
                            Step = 1;
                            break;
                        case 1:
                            Event_onWait = false;
                            break;
                    }
                    break;
                case 6:
                    switch(Step)
                    {
                        case 0:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 133);
                            Event_Timer = 5000;
                            Step = 1;
                            break;
                        case 1:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                            DoScriptText(CLINTAR_SPIRIT_SAY_GET_ONE, me, player);
                            Event_onWait = false;
                            break;
                    }
                    break;
                case 15:
                    switch(Step)
                    {
                        case 0:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 133);
                            Event_Timer = 5000;
                            Step = 1;
                            break;
                        case 1:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                            Event_onWait = false;
                            break;
                    }
                    break;
                case 16:
                    switch(Step)
                    {
                        case 0:
                            DoScriptText(CLINTAR_SPIRIT_SAY_GET_TWO, me, player);
                            Event_Timer = 15000;
                            Step = 1;
                            break;
                        case 1:
                            Event_onWait = false;
                            break;
                    }
                    break;
                case 20:
                    switch(Step)
                    {
                        case 0:
                            {
                            Creature *mob = me->SummonCreature(ASPECT_RAVEN, ASPECT_RAVEN_SUMMON_X, ASPECT_RAVEN_SUMMON_Y, ASPECT_RAVEN_SUMMON_Z, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 2000);
                            if(mob)
                            {
                                mob->AddThreat(me,10000.0f);
                                mob->AI()->AttackStart(me);
                            }
                            Event_Timer = 2000;
                            Step = 1;
                            break;
                            }
                        case 1:
                            Event_onWait = false;
                            break;
                    }
                    break;
                case 24:
                    switch(Step)
                    {
                        case 0:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 133);
                            Event_Timer = 5000;
                            Step = 1;
                            break;
                        case 1:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                            Event_onWait = false;
                            break;
                    }
                    break;
                case 25:
                    switch(Step)
                    {
                        case 0:
                            DoScriptText(CLINTAR_SPIRIT_SAY_GET_THREE, me, player);
                            Event_Timer = 4000;
                            Step = 1;
                            break;
                        case 1:
                            Event_onWait = false;
                            break;
                    }
                    break;
                case 40:
                    switch(Step)
                    {
                        case 0:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 2);
                            DoScriptText(CLINTAR_SPIRIT_SAY_GET_FINAL, me, player);
                            player->CompleteQuest(10965);
                            Event_Timer = 1500;
                            Step = 1;
                            break;
                        case 1:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                            Event_Timer = 3000;
                            Step = 2;
                            break;
                        case 2:
                            player->TalkedToCreature(me->GetEntry(), me->GetGUID());
                            PlayerGUID = 0;
                            Reset();
                            me->SetDeathState(JUST_DIED);
                            break;
                    }
                    break;
                default:
                    Event_onWait = false;
                    break;
            }

        } else if(Event_onWait) Event_Timer -= diff;
    }

    void WaypointReached(uint32 id)
    override {
        CurrWP = id;
        Event_Timer = 0;
        Step = 0;
        Event_onWait = true;
    }
};

CreatureAI* GetAI_npc_clintar_spirit(Creature* pCreature)
{
    return new npc_clintar_spiritAI(pCreature);
}

/*####
# npc_clintar_dreamwalker
####*/

#define CLINTAR_SPIRIT 22916

bool QuestAccept_npc_clintar_dreamwalker(Player* pPlayer, Creature* pCreature, Quest const* pQuest )
{
    if (pQuest->GetQuestId() == 10965)
    {
        Creature* clintar_spirit = pCreature->SummonCreature(CLINTAR_SPIRIT, CLINTAR_SPIRIT_SUMMON_X, CLINTAR_SPIRIT_SUMMON_Y, CLINTAR_SPIRIT_SUMMON_Z, CLINTAR_SPIRIT_SUMMON_O, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 100000);
        if(clintar_spirit)
            CAST_AI(npc_clintar_spiritAI, (clintar_spirit->AI()))->StartEvent(pPlayer);
    }
    
    return true;
}

/*####
# npc_keeper_remulos
####*/

#define REMULOS     11832
#define ERANIKUS    15491
#define REDEEMED    15628
#define NIGHTMARE   15629
#define TYRANDE     15633
#define PRIESTESS   15634

#define CONJURE_DREAM_RIFT  25813
#define PRAYER_OF_ELUNE     25841    

struct Conversation {
    int id;
    const char* text;
    uint32 creature;
    ChatType type;
    uint32 timer;
    uint32 emote;
};

static Conversation Convs[] =
{
    { 0, "Nous localiserons l'origine du Cauchemar grâce aux fragments que vous avez collecté, $n. D'ici, nous attirerons Eranikus à travers une faille dans le Rêve. Préparez-vous, $c. Nous invitons la personnification du Cauchemar dans notre monde.", REMULOS, CHAT_TYPE_SAY, 15000, 1 },
    { 1, "Allons à Havrenuit ! Gardez votre armée proche, champion.", REMULOS, CHAT_TYPE_SAY, 3000, 1 },
// goto nighthaven
    { 2, "La faille s'ouvrira ici, au dessus du Lac Elune'ara. Soyez prêt, $n. L'arrivée d'Eranikus dans notre monde se fera dans le chaos et les combats.", REMULOS, CHAT_TYPE_SAY, 10000, 0 },
    { 3, "Il ne s'arrêtera devant rien pour détruire la manifestation physique de Malfurion. Ceci ne doit pas arriver... Nous devons tenir la bête occupée jusqu'à ce que Tyrande arrive.", REMULOS, CHAT_TYPE_SAY, 10000, 0 },
    { 4, "Défendez Havrenuit, héros...", REMULOS, CHAT_TYPE_SAY, 5000, 0 },
// invoc
    { 5, "est entré dans notre monde.", ERANIKUS, CHAT_TYPE_SERVER_EMOTE, 5000, 0 },
    { 6, "Mortels pitoyables et prévisibles... Vous ne savez pas ce que vous avez fait ! La volonté du maître sera accomplie. Reflet-de-Lune sera détruit, emportant Malfurion avec lui !", ERANIKUS, CHAT_TYPE_YELL, 10000, 0 },
    { 7, "Démon ! Affronte la puissance de Cénarius !", REMULOS, CHAT_TYPE_YELL, 5000, 0 },
    { 8, "laisse échapper un rire sinistre.", ERANIKUS, CHAT_TYPE_TEXT_EMOTE, 5000, 0 },
    { 9, "Tu n'es certainement pas ton père, insecte. Si je le voulais, je t'écraserais d'un coup de griffe. Amène-moi Shan'do Hurlorage et ta misérable existence sera épargnée, ainsi que celles de ton peuple.", ERANIKUS, CHAT_TYPE_YELL, 15000, 0 },
    { 10, "Qui est prévisible, monstre ? Tu ne pensais tout de même pas que nous t'invoquerions devant Malfurion ? Ta rédemption est proche, Eranikus. Tu seras purgé de cette folie, cette corruption.", REMULOS, CHAT_TYPE_YELL, 15000, 0 },
    { 11, "Ma rédemption ? Tu oses, petite chose. Ma rédemption viendra par la volonté de mon dieu.", ERANIKUS, CHAT_TYPE_YELL, 5000, 0 },
    { 12, "rugit furieusement.", ERANIKUS, CHAT_TYPE_TEXT_EMOTE, 3000, 0 },
    { 13, "Dépêchons-nous, $n ! Il faut trouver un abri !", REMULOS, CHAT_TYPE_SAY, 3000, 0 },
// goto house
    { 14, "Je vous en prie champion, protégez notre peuple.", REMULOS, CHAT_TYPE_SAY, 5000, 0 },
    { 15, "Levez-vous, serviteurs du Cauchemar ! Levez-vous et détruisez ce monde ! Qu'il ne reste aucun survivant...", ERANIKUS, CHAT_TYPE_YELL, 3000, 0 },
// spawn adds
    { 16, "Nous combattrons ces démons, ensemble ! Les Gardiens de Reflet-de-Lune sont également parmi nous. Ils se battrons jusqu'à la mort s'il le faut. À présent, nous devons rapidement renvoyer ces aberrations dans le Cauchemar. Détruisez-les tous !", REMULOS, CHAT_TYPE_SAY, 5000, 0 },
// remulos engages
    { 17, "Où est votre sauveur ? Combien de temps tiendrez-vous contre mes attaques ?", ERANIKUS, CHAT_TYPE_YELL, 0, 0 }, // timed ?
    { 18, "Mes serviteurs sont vaincus ? Alors affrontez-moi, mortels !", ERANIKUS, CHAT_TYPE_YELL, 3000, 0 },
// eranikus engages
    { 19, "Remulos, regarde comment ils tombent facilement devant moi. Tu peux arrêter ceci, sot. Amène-moi le druide et cela s'arrêtera...", ERANIKUS, CHAT_TYPE_YELL, 0, 0 }, // timed ?
    { 20, "Elune, entend mes prières. Accorde-nous la sérénité ! Veille sur nos disparus...", TYRANDE, CHAT_TYPE_YELL, 0, 0 },
// tyrande comes
    { 21, "Soignez les blessés, mes soeurs !", TYRANDE, CHAT_TYPE_SAY, 10000, 0 },
    { 22, "Cherche l'absolution, Eranikus. Tout sera pardonné...", TYRANDE, CHAT_TYPE_YELL, 20000, 0 },
    { 23, "Tu seras pardonné, Eranikus. Elune t'aimera toujours. Libère toi des chaînes qui te commandent !", TYRANDE, CHAT_TYPE_YELL, 30000, 0 },
    { 24, "L'emprise des Anciens Dieux est tenace... Il est consumé par leurs noires pensées... Je... Je... Je ne peux pas... peux pas canaliser plus longtemps. Elune vienne à mon secours.", TYRANDE, CHAT_TYPE_SAY, 1000, 0 },
    { 25, "tombe à genoux.", TYRANDE, CHAT_TYPE_TEXT_EMOTE, 0, 0 },
// if eranikus is at 20% before #24, then force to say 24 and 25
    { 26, "ÇA BRÛLE ! LA DOULEUR.. BRÛLANTE...", ERANIKUS, CHAT_TYPE_YELL, 10000, 0 },
    { 27, "POURQUOI? Pourquoi est-ce arrivé à... à moi ? Où étais-tu Tyrande ? Où étais-tu quand j'ai perdu la grâce d'Elune ?", ERANIKUS, CHAT_TYPE_YELL, 10000, 0 },
    { 28, "Je... Je sens... Je sens le touché d'Elune sur mon être une fois de plus... Elle me sourit... Oui... Je...", ERANIKUS, CHAT_TYPE_YELL, 10000, 0 },
    { 29, "est entièrement consumé par la Lumière d'Elune. La tranquilité revient à Reflet-de-Lune.", ERANIKUS, CHAT_TYPE_SERVER_EMOTE, 5000, 0 },
    { 30, "Elune soit louée... Eranikus est racheté.", TYRANDE, CHAT_TYPE_SAY, 5000, 0 },
// despawn eranikus and spawn redeemed
    { 31, "Depuis si longtemps, j'étais perdu... La corruption du Cauchemar m'avait consumé... Et maintenant, vous tous, vous m'avez sauvé. Libéré de son emprise.", REDEEMED, CHAT_TYPE_SAY, 15000, 0 },
    { 32, "Mais... Malfurion, Cénarius, Ysera... Ils se battent encore. Ils ont besoin de moi. Je dois retourner au Rêve incessamment.", REDEEMED, CHAT_TYPE_SAY, 12000, 0 },
    { 33, "Ma dame, je ne suis pas digne de votre prière. Vraiment, vous êtes un ange de lumière. S'il-vous-plaît, aidez moi à retourner au Refuge des saisons, que je puisse retourner dans le Rêve. Comme Malfurion, j'ai aussi un amour qui m'attend... Je dois retourner auprès d'elle... pour la protéger...", REDEEMED, CHAT_TYPE_SAY, 20000, 0 },
    { 34, "Et héros... Je détiens ce que vous cherchez. Qu'il puisse une fois de plus voir le mal disparaître. Remulos, veillez à ce que notre champion reçoive le fragment du Vol Vert.", REDEEMED, CHAT_TYPE_SAY, 15000, 0 },
    { 35, "acquiesce.", TYRANDE, CHAT_TYPE_TEXT_EMOTE, 10000, 0 },
    { 36, "Ce sera fait, Eranikus. Portez-vous bien, vénérable.", REMULOS, CHAT_TYPE_SAY, 8000, 0 },
// despawn redeemed and tyrande
    { 37, "Quittons Havrenuit, héros. Trouvez-moi au bosquet.", REMULOS, CHAT_TYPE_SAY, 5000, 0 },
// despawn remulos (gobackhome)
    { 38, nullptr, 0, CHAT_TYPE_SAY, 90000, 0 }, // timer before #17
    { 39, nullptr, 0, CHAT_TYPE_SAY, 80000, 0 }, // timer before #19
    { 40, nullptr, 0, CHAT_TYPE_SAY, 5000, 0 }, // timer before #31
    { 41, nullptr, 0, CHAT_TYPE_SAY, 8000, 0 }, // timer before #37
    { 42, nullptr, 0, CHAT_TYPE_SAY, 3000, 0 }, // timer before #5
    { 43, nullptr, 0, CHAT_TYPE_SAY, 5000, 0 }, // timer before #0
};
    

struct Locations {
    float x, y, z, o;
};

static Locations RemulosWP[] =
{
    { 7817.186523, -2304.227539, 455.941071, 4.804095 }, // walk wp 1 (cross)
    { 7925.188477, -2312.769043, 471.415039, 6.254246 }, // walk wp 2 (before turn)
    { 7942.157227, -2321.153076, 476.773834, 5.792509 }, // walk wp 3 (after turn)
    { 7957.152344, -2373.932373, 486.453094, 4.794063 }, // walk wp 4 (before house)
    { 7965.914551, -2491.798340, 487.759705, 4.844883 }, // walk wp 5 (after house)
    { 7972.112305, -2517.210449, 487.689850, 4.824812 }, // walk wp 6 (before bridge)
    { 7975.595703, -2551.107422, 490.081543, 4.839223 }, // walk wp 7 (after bridge)
    { 7945.702637, -2573.971191, 489.783569, 4.252142 }, // walk wp 8 (after bridge 2)
    { 7951.856934, -2595.572998, 489.919556, 4.447841 }, // walk wp 9 (before platform)
    { 7948.349609, -2610.257080, 492.345001, 4.477947 }, // walk wp 10 (on platform)
    { 7926.278320, -2633.262451, 492.530151, 3.842072 }, // invocation of eranikus
    { 7948.349609, -2610.257080, 492.345001, 1.395251 }, // walk wp 12 (on platform)
    { 7951.856934, -2595.572998, 489.919556, 1.395251 }, // walk wp 13 (before platform)
    { 7945.702637, -2573.971191, 489.783569, 2.750073 }, // walk wp 14 (after bridge 2)
    { 7898.774414, -2566.517334, 487.833344, 3.216603 }, // walk wp 15 (after bridge 3)
    { 7836.721680, -2571.058350, 489.286804, 3.216603 }, // house
    { 7844.209961, -2570.704346, 489.285278, 0.129769 }, // house, waiting for combat
    { 7877.886719, -2565.909424, 486.946411, 0.043205 }, // in front of house
};

static Locations EranikusWP[] =
{
    { 7863.083984, -2682.686035, 469.532166, 0.642453 }, // spawn
    { 7941.503906, -2576.785889, 501.884308, 2.918067 }, // hover 1
    { 7930.495605, -2574.283447, 501.884308, 2.835252 }, // hover 2
    { 7919.830566, -2570.955811, 489.375031, 2.918945 }, // landing
};

/*static Locations TyrandeWP[] =
{
    { 7884.979004, -2566.499023, 486.958527, 6.255793 }, // casting
};*/

static Locations PriestessSP[] =
{
    { 7814.898926, -2301.132812, 456.282923, 0 },
    { 7813.714355, -2305.572510, 455.794922, 0 },
    { 7812.495605, -2298.683594, 456.128387, 0 },
    { 7811.326172, -2302.086670, 455.870941, 0 },
    { 7810.257812, -2306.418213, 455.531525, 0 },
    { 7809.302246, -2299.352539, 455.838287, 0 },
    { 7808.051270, -2303.647461, 455.473450, 0 },
    { 7806.024902, -2300.486084, 455.584351, 0 },
};

static Locations AddsSP[] =
{
    { 7884.774414, -2550.940918, 483.867340, 0 },
    { 7898.257812, -2552.235596, 483.919922, 0 },
    { 7906.317871, -2584.823730, 484.623108, 0 },
    { 7944.910645, -2562.068604, 485.228790, 0 },
    { 7955.473633, -2551.123291, 484.568634, 0 },
    { 7959.822754, -2552.863770, 484.098755, 0 },
    { 7939.934570, -2597.583252, 482.697784, 0 },
    { 7983.933105, -2471.372803, 487.516327, 0 },
    { 7946.840820, -2469.763672, 485.254822, 0 },
    { 7928.883301, -2554.717773, 485.188904, 0 },
};

enum PhaseRemulos
{
    PHASE_NULL = 0,
    PHASE_TALK,
    PHASE_WALK,
    PHASE_INVOCATION,
    PHASE_COMBAT1,
    PHASE_COMBAT2,
    PHASE_REDEMPTION,
    PHASE_EVENT_FAILED,
    PHASE_MAX,
};

enum EventRemulos
{
    EVENT_NULL = 0,
    EVENT_TALK_OVER,
    EVENT_WAYPOINT,
    EVENT_INVOCATION,
    EVENT_WAVE,
    EVENT_NIGHTMARES_KILLED,
    EVENT_TYRANDE_SPAWN,
    EVENT_ERANIKUS_REDEEMED,
    EVENT_FAILURE,
    EVENT_COUNT,
};

struct npc_keeper_remulosAI : public ScriptedAI
{
    npc_keeper_remulosAI(Creature *c) : ScriptedAI(c) {}

    bool EventRunning;
    uint64 HolderGUID;
    PhaseRemulos Phase;
    EventRemulos Event;

    bool newWP;
    uint32 WPId;
    uint32 TalkId;
    uint32 Timer[EVENT_COUNT];

    uint32 WaveId;
    uint32 KilledNightmares;

    uint64 EranikusGUID;
    uint64 RedeemedGUID;
    uint64 TyrandeGUID;

    uint64 PriestessGUIDs[8];

    bool canBeRedeemed;

    void Reset()
    override {
        EventRunning = false;
        HolderGUID = 0;
        Phase = PHASE_NULL;
        Event = EVENT_NULL;

        WPId = 0;
        newWP = false;
        TalkId = 0;

        WaveId = 0;
        KilledNightmares = 0;

        EranikusGUID = 0;
        RedeemedGUID = 0;
        TyrandeGUID = 0;

        for (uint32 & i : Timer)
            i = 0;
        for (uint64 & PriestessGUID : PriestessGUIDs)
            PriestessGUID = 0;

        canBeRedeemed = false;

        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
        me->SetReactState(REACT_DEFENSIVE);
    }

    void EnterCombat(Unit*) override {}

    void DespawnAll()
    {
        Creature* c;
        c = ObjectAccessor::GetCreature(*me, EranikusGUID);
        if (c)
        {
            c->DisappearAndDie();
            ((TemporarySummon*)c)->UnSummon();
        }
        c = ObjectAccessor::GetCreature(*me, RedeemedGUID);
        if (c)
            c->DisappearAndDie();
        c = ObjectAccessor::GetCreature(*me, TyrandeGUID);
        if (c)
            c->DisappearAndDie();
        for (uint64 PriestessGUID : PriestessGUIDs)
        {
            c = ObjectAccessor::GetCreature(*me, PriestessGUID);
            if (c)
                c->DisappearAndDie();
        }

        float x, y, z, o;
        me->GetHomePosition(x, y, z, o);
        me->DestroyForNearbyPlayers();
        me->GetMap()->CreatureRelocation(me, x, y, z, o);

        if (me->IsAlive())
            me->SetHealth(me->GetMaxHealth());
        else
            me->Respawn();

        Reset();
    }

    void JustDied(Unit*)
    override {
        EventFailed();
        DespawnAll();
    }

    void NightKilled()
    {
        KilledNightmares++;
    }

    void EnterEvadeMode(EvadeReason /* why */)
    override {
        me->InterruptNonMeleeSpells(true);
        me->RemoveAllAuras();
        me->DeleteThreatList();
        me->CombatStop(true);
    }

    void Talk(uint32 id)
    {
        Timer[EVENT_TALK_OVER] = Convs[id].timer;
        TalkId = id;

        Creature* creature = nullptr;
        if (Convs[id].creature == REMULOS)
            creature = me;
        else if (Convs[id].creature == ERANIKUS)
            creature = ObjectAccessor::GetCreature(*me, EranikusGUID);
        else if (Convs[id].creature == REDEEMED)
            creature = ObjectAccessor::GetCreature(*me, RedeemedGUID);
        else if (Convs[id].creature == TYRANDE)
            creature = ObjectAccessor::GetCreature(*me, TyrandeGUID);

        if (creature)
        {
            if (Convs[id].emote)
                creature->HandleEmoteCommand(Convs[id].emote);
            if (Convs[id].text)
            {
                if (Convs[id].type == CHAT_TYPE_SAY)
                    creature->Say(Convs[id].text, LANG_UNIVERSAL); // XXX a bit ugly, we should add a field in the struct for that
                else if (Convs[id].type == CHAT_TYPE_YELL)
                    creature->Yell(Convs[id].text, LANG_UNIVERSAL, nullptr);
                else if (Convs[id].type == CHAT_TYPE_TEXT_EMOTE)
                    creature->TextEmote(Convs[id].text, nullptr, false);
                else if (Convs[id].type == CHAT_TYPE_SERVER_EMOTE)
                    creature->ServerEmote(Convs[id].text, false);
            }
        }
    }

    void StartEvent(uint64 guid)
    {
        if (me->GetZoneId() != 493)
            return;

        HolderGUID = guid;
        EventRunning = true;

        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);

        Talk(43);
    }

    void EventFailed()
    {
        if (Phase == PHASE_EVENT_FAILED)
            return;
        EnterPhase(PHASE_EVENT_FAILED);
    }

    void NextWave()
    {
        WaveId++;
        Timer[EVENT_WAVE] = 0;

        for (auto & i : AddsSP)
        {
            Creature* cre = me->SummonCreature(NIGHTMARE, i.x, i.y, i.z, i.o, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 120000);
            if (cre)
                cre->SetKeepActive(true);
//            cre->AddThreat(me, 0.1f);
//            cre->AI()->AttackStart(me);
        }

        if (WaveId < 3)
            Timer[EVENT_WAVE] = 30000;
    }

    void TyrandeComes(bool ready)
    {
        if (!ready)
        {
            Talk(20);
            return;
        }

        Creature* c, *tyr, *era;

        tyr = ObjectAccessor::GetCreature(*me, TyrandeGUID);
        era = ObjectAccessor::GetCreature(*me, EranikusGUID);

        if (!tyr || !era)
            return;

        tyr->SetInFront(era);
        tyr->SendMovementFlagUpdate();

        for (uint64 PriestessGUID : PriestessGUIDs)
        {
            c = ObjectAccessor::GetCreature(*me, PriestessGUID);
            if (!c)
                continue;
            c->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 0);
            c->SetInFront(era);
            c->SendMovementFlagUpdate();
            c->AI()->EnterCombat(era);
        }
        canBeRedeemed = true;
        Talk(21);
    }

    void EnterPhase(PhaseRemulos phase)
    {
        Phase = phase;

        switch (phase)
        {
        case PHASE_INVOCATION:
            DoCast(me, CONJURE_DREAM_RIFT);
            Timer[EVENT_INVOCATION] = 8000;
            break;
        case PHASE_COMBAT1:
            me->SetReactState(REACT_AGGRESSIVE);
            NextWave();
            Talk(16);
            break;
        case PHASE_COMBAT2:
            Talk(18);
            break;
        case PHASE_EVENT_FAILED:
        {
            Timer[EVENT_FAILURE] = 300000;
            Player* player = ObjectAccessor::GetPlayer(*me, HolderGUID);
            if (player)
                player->FailQuest(8736);
            break;
        }
        default:
            break;
        }
    }

    PhaseRemulos GetPhase()
    {
        return Phase;
    }

    void HandleTalkSequence()
    {
        switch(TalkId)
        {
        case 0:
            EnterPhase(PHASE_TALK);
            break;
        case 1:
            // goto nighthaven
            me->GetMotionMaster()->MovePoint(1, RemulosWP[0].x, RemulosWP[0].y, RemulosWP[0].z);
            EnterPhase(PHASE_WALK);
            break;
        case 4:
            // start invocation
            EnterPhase(PHASE_INVOCATION);
            break;
        case 5:
            EnterPhase(PHASE_TALK);
            break;
        case 13:
        {
            // goto house
            Creature* eranikus = ObjectAccessor::GetCreature(*me, EranikusGUID);
            if (eranikus)
                eranikus->GetMotionMaster()->MovePoint(1, EranikusWP[1].x, EranikusWP[1].y, EranikusWP[1].z);
            me->GetMotionMaster()->MovePoint(12, RemulosWP[11].x, RemulosWP[11].y, RemulosWP[11].z);
            EnterPhase(PHASE_WALK);
            break;
        }
        case 15:
            // spawn adds
            EnterPhase(PHASE_COMBAT1);
            break;
        case 16:
            // remulos engages
            me->GetMotionMaster()->MovePoint(0, RemulosWP[17].x, RemulosWP[17].y, RemulosWP[17].z);
            Talk(38);
            break;
        case 18:
        {
            // eranikus engages
            Creature* eranikus = ObjectAccessor::GetCreature(*me, EranikusGUID);
            if (eranikus)
                eranikus->GetMotionMaster()->MovePoint(3, EranikusWP[3].x, EranikusWP[3].y, EranikusWP[3].z);
            Timer[EVENT_TYRANDE_SPAWN] = 40000;
            break;
        }
        case 20:
            // tyrande comes
            break;
        case 21:
        case 22:
        case 23:
        case 24:
        {
            Talk(TalkId+1);
            Creature *tyrande = ObjectAccessor::GetCreature(*me, TyrandeGUID);
            if (TalkId == 24 && tyrande)
                tyrande->SetStandState(UNIT_STAND_STATE_KNEEL);
/*            if (TalkId == 21 && tyrande)
                tyrande->CastSpell(tyrande, 14751, true);*/
            break;
        }
        case 27:
        {
            Creature* eranikus = ObjectAccessor::GetCreature(*me, EranikusGUID);
            if (eranikus)
            {
                uint32 health = eranikus->GetHealth();
                eranikus->AI()->EnterEvadeMode();
                eranikus->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                eranikus->SetFaction(35);
                eranikus->SetHealth(health);
            }
            break;
        }
        case 28:
        {
            Creature* eranikus = ObjectAccessor::GetCreature(*me, EranikusGUID);
            if (eranikus)
            {
                eranikus->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                eranikus->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            }
            break;
        }
        case 30:
        {
            // despawn eranikus and spawn redeemed
            float x, y, z, o;

            Creature* eranikus = ObjectAccessor::GetCreature(*me, EranikusGUID);
            if (eranikus)
            {
                eranikus->GetPosition(x, y, z, o);
                eranikus->DisappearAndDie();
                ((TemporarySummon*)eranikus)->UnSummon();
            }

            Creature* redeemed = me->SummonCreature(REDEEMED, x, y, z, o, TEMPSUMMON_DEAD_DESPAWN, 0);
            if (redeemed)
            {
                RedeemedGUID = redeemed->GetGUID();
                redeemed->SetHealth((redeemed->GetMaxHealth() / 100.0f) * 20.0f);
                Creature* tyrande = ObjectAccessor::GetCreature(*me, TyrandeGUID);
                if (tyrande)
                    redeemed->GetMotionMaster()->MoveChase(tyrande, CONTACT_DISTANCE, 0);
            }

            EnterPhase(PHASE_REDEMPTION);
            Talk(40);
            break;
        }
        case 31:
            EnterPhase(PHASE_TALK);
            break;
        case 34:
        {
            Creature* tyrande = ObjectAccessor::GetCreature(*me, TyrandeGUID);
            if (tyrande)
                tyrande->SetStandState(UNIT_STAND_STATE_STAND);
            break;
        }
        case 36:
        {
            // despawn redeemed and tyrande and mark quest as completed
            Creature *redeemed, *tyrande, *cre;
            Player *player;

            redeemed = ObjectAccessor::GetCreature(*me, RedeemedGUID);
            tyrande = ObjectAccessor::GetCreature(*me, TyrandeGUID);
            if (redeemed)
                redeemed->DisappearAndDie();

            for (uint64 PriestessGUID : PriestessGUIDs)
            {
                cre = ObjectAccessor::GetCreature(*me, PriestessGUID);
                if (cre)
                    cre->DisappearAndDie();
            }
            if (tyrande)
                tyrande->DisappearAndDie();

            player = ObjectAccessor::GetPlayer(*me, HolderGUID);
            if (player)
                player->GroupEventHappens(8736, me);

            EnterPhase(PHASE_REDEMPTION);
            Talk(41);
            break;
        }
        case 37:
        {
            // despawn remulos and stop event
            float x, y, z, o;
            Reset();
            me->DestroyForNearbyPlayers();
            me->GetHomePosition(x, y, z, o);
            me->GetMap()->CreatureRelocation(me, x, y, z, o);
            me->SetHealth(me->GetMaxHealth());
            break;
        }
        case 38:
            Talk(17);
            break;
        case 39:
            Talk(19);
            break;
        case 40:
        {
/*            Creature* redeemed = ObjectAccessor::GetCreature(*me, RedeemedGUID);
            Creature* tyrande = ObjectAccessor::GetCreature(*me, TyrandeGUID);
            if (redeemed && tyrande)
            {
                redeemed->SetInFront(tyrande);
                redeemed->SendMovementFlagUpdate();
            }*/
            Talk(31);
            break;
        }
        case 41:
            Talk(37);
            break;
        case 42:
            Talk(5);
            break;
        case 43:
            Talk(0);
            break;
        default:
            break;
        }

        if (Phase == PHASE_TALK)
            Talk(++TalkId);
    }

    void MovementInform(uint32 type, uint32 id)
    override {
        if (type != POINT_MOTION_TYPE)
            return;

        if (id == 0)
            return;

        switch(id)
        {
        case 6:
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            break;
        case 7:
            me->ClearUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            break;
        case 11:
            EnterPhase(PHASE_TALK);
            Talk(2);
            break;
        case 17:
            EnterPhase(PHASE_TALK);
            Talk(14);
            break;
        default:
            break;
        }

        if (id <= 10 || (id >= 12 && id <= 16))
        {
            WPId = id;
            newWP = true;
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!EventRunning)
            return;

        Event = EVENT_NULL;

        if (Phase == PHASE_COMBAT1 && KilledNightmares >= 25)
            Event = EVENT_NIGHTMARES_KILLED;

        if (Phase == PHASE_COMBAT2 && canBeRedeemed)
        {
            Creature* eranikus = ObjectAccessor::GetCreature(*me, EranikusGUID);
            if (eranikus && eranikus->IsBelowHPPercent(20))
                Event = EVENT_ERANIKUS_REDEEMED;
        }

        if (newWP)
        {
            Event = EVENT_WAYPOINT;
            newWP = false;
        }

        for (uint32 i = 1; i <= EVENT_COUNT; i++)
        {
            if (Timer[i])
            {
                if (Timer[i] <= diff)
                {
                    if (!Event)
                        Event = (EventRemulos)i;
                }
                else 
                {
                    Timer[i] -= diff;
                }
            }
        }

        if (Phase == PHASE_EVENT_FAILED && Event != EVENT_FAILURE)
            return;

        switch (Event)
        {
        case EVENT_TALK_OVER:
            Timer[EVENT_TALK_OVER] = 0;
            HandleTalkSequence();
            break;
        case EVENT_WAYPOINT:
            me->GetMotionMaster()->MovePoint(WPId+1, RemulosWP[WPId].x, RemulosWP[WPId].y, RemulosWP[WPId].z);
            break;
        case EVENT_INVOCATION:
        {
            Timer[EVENT_INVOCATION] = 0;
            Creature* cre = me->SummonCreature(ERANIKUS, EranikusWP[0].x, EranikusWP[0].y, EranikusWP[0].z, EranikusWP[0].o, TEMPSUMMON_DEAD_DESPAWN, 0);
            if (cre)
            {
                cre->SetKeepActive(true);
                cre->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                EranikusGUID = cre->GetGUID();
            }
            Talk(42);
            break;
        }
        case EVENT_WAVE:
            Timer[EVENT_WAVE] = 0;
            NextWave();
            break;
        case EVENT_NIGHTMARES_KILLED:
            EnterPhase(PHASE_COMBAT2);
            break;
        case EVENT_TYRANDE_SPAWN:
        {
            Timer[EVENT_TYRANDE_SPAWN] = 0;
            Creature *cre, *tyr;
            tyr = me->SummonCreature(TYRANDE, RemulosWP[0].x, RemulosWP[0].y, RemulosWP[0].z, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
            if (tyr)
            {
                tyr->SetKeepActive(true);
                TyrandeGUID = tyr->GetGUID();
            }
            for (int i = 0; i < 8; i++)
            {
                cre = me->SummonCreature(PRIESTESS, PriestessSP[i].x, PriestessSP[i].y, PriestessSP[i].z, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 120000);
                if (cre)
                {
                    cre->SetKeepActive(true);
                    PriestessGUIDs[i] = cre->GetGUID();
                    cre->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                    cre->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 9695);
                    cre->GetMotionMaster()->MoveFollow(tyr, PET_FOLLOW_DIST, cre->GetFollowAngle());
                }
            }
            if (tyr)
            {
                tyr->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                tyr->GetMotionMaster()->MovePoint(2, RemulosWP[1].x, RemulosWP[1].y, RemulosWP[1].z);
            }
            break;
        }
        case EVENT_ERANIKUS_REDEEMED:
        {
            EnterPhase(PHASE_TALK);
            if (Timer[EVENT_TALK_OVER])
            {
                if (TalkId < 24)
                    Talk(24);
            } else
                Talk(26);
            break;
        }
        case EVENT_FAILURE:
            DespawnAll();
            break;
        default:
            break;
        }

        if (Phase == PHASE_COMBAT1 || Phase == PHASE_COMBAT2)
        {
            if (!UpdateVictim(false))
                return;
            DoMeleeAttackIfReady();
        }
    }
};

bool QuestAccept_npc_keeper_remulos(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if (pQuest->GetQuestId() == 8736)
    {
        CAST_AI(npc_keeper_remulosAI, (pCreature->AI()))->StartEvent(pPlayer->GetGUID());
    }

    return true;
}

CreatureAI* GetAI_npc_keeper_remulos(Creature* pCreature)
{
    return new npc_keeper_remulosAI(pCreature);
}

/*####
# npc_nightmare_phantasm
####*/

#define SWELL_OF_SOULS 21307
#define NIGHT_SHADOW_BOLT_VOLLEY 17228
#define AURA_OF_FEAR 26641

struct npc_nightmare_phantasmAI : public ScriptedAI
{
    npc_nightmare_phantasmAI(Creature *c) : ScriptedAI(c) {}

    uint32 Bolt_Timer;
    uint32 Fear_Timer;

    void Reset()
    override {
        Bolt_Timer = 3000 + urand(0, 3)*IN_MILLISECONDS;
        Fear_Timer = 15000 + urand(0, 3)*IN_MILLISECONDS;
    }

    void EnterCombat(Unit*) override {}

    void MoveInLineOfSight(Unit*) override {}

    void KilledUnit(Unit*)
    override {
        DoCast(me, SWELL_OF_SOULS);
    }

    void JustDied(Unit*)
    override {
        Creature* c = FindCreature(REMULOS, 500, me)->ToCreature();
        if (c)
            CAST_AI(npc_keeper_remulosAI, (c->AI()))->NightKilled();
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!me->IsInCombat()) {
            Creature* c = FindCreature(REMULOS, 500, me)->ToCreature();
            if (c)
                AttackStart(c);
            else
                UpdateVictim(false);
            return;
        }

        Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 500, false);
        if (!me->GetVictim())
        {
            AttackStart(target);
            return;
        }

        if (!UpdateVictim(false))
            return;

        if (Bolt_Timer <= diff)
        {
            DoCast(me->GetVictim(), NIGHT_SHADOW_BOLT_VOLLEY);
            Bolt_Timer = 5000 + urand(0, 3)*IN_MILLISECONDS;
        } else
            Bolt_Timer -= diff;

        if (Fear_Timer <= diff)
        {
            DoCast(me->GetVictim(), AURA_OF_FEAR);
            Fear_Timer = 15000 + urand(0, 3)*IN_MILLISECONDS;
        } else
            Fear_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_nightmare_phantasm(Creature* pCreature)
{
    return new npc_nightmare_phantasmAI(pCreature);
}

/*####
# npc_eranikus_tyrant_of_the_dream
####*/

#define ACID_BREATH             24839
#define NOXIOUS_BREATH          24818
#define ERA_SHADOW_BOLT_VOLLEY  25586

struct npc_eranikus_tyrant_of_the_dreamAI : public ScriptedAI
{
    npc_eranikus_tyrant_of_the_dreamAI(Creature* c) : ScriptedAI(c) {}

    bool combatPhase;
    bool newWP;

    uint32 Acid_Timer;
    uint32 Noxious_Timer;
    uint32 Bolt_Timer;

    void Reset()
    override {
        combatPhase = false;
        newWP = false;

        Acid_Timer = 15000;
        Noxious_Timer = 10000;
        Bolt_Timer = 25000;
    }

    void EnterCombat(Unit*) override {}

    void JustDied(Unit*)
    override {
        Creature* c = FindCreature(REMULOS, 500, me)->ToCreature();
        if (c)
            CAST_AI(npc_keeper_remulosAI, (c->AI()))->EventFailed();
    }

    void MoveInLineOfSight(Unit*) override {}

    void EnterEvadeMode(EvadeReason /* why */)
    override {
        combatPhase = false;
        me->InterruptNonMeleeSpells(true);
        me->RemoveAllAuras();
        me->DeleteThreatList();
        me->CombatStop(true);
    }

    void MovementInform(uint32 type, uint32 id)
    override {
        if (type != POINT_MOTION_TYPE)
            return;

        if (id == 0)
            return;

        switch(id)
        {
        case 1:
//            newWP = true;
            break;
        case 2:
            me->SetDisableGravity(true);
            break;
        case 3:
        {
            me->SetDisableGravity(false);
//            me->SetOrientation(EranikusWP[3].o);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            combatPhase = true;
            me->SendMovementFlagUpdate();
            break;
        }
        default:
            break;
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if (newWP)
        {
            newWP = false;
            me->GetMotionMaster()->MovePoint(2, EranikusWP[2].x, EranikusWP[2].y, EranikusWP[2].z);
        }

        if (!combatPhase)
            return;

        if (!me->IsInCombat())
        {
            Creature* c = FindCreature(REMULOS, 500, me)->ToCreature();
            if (c)
                AttackStart(c);
            else
                UpdateVictim(false);
            return;
        }

        if (!UpdateVictim(false))
            return;

        if (Bolt_Timer <= diff)
        {
            DoCast(me->GetVictim(), ERA_SHADOW_BOLT_VOLLEY);
            Bolt_Timer = 25000;
        } else
            Bolt_Timer -= diff;

        if (Acid_Timer <= diff)
        {
            DoCast(me->GetVictim(), ACID_BREATH);
            Acid_Timer = 15000;
        } else
            Acid_Timer -= diff;

        if (Noxious_Timer <= diff)
        {
            DoCast(me->GetVictim(), NOXIOUS_BREATH);
            Noxious_Timer = 10000;
        } else
            Noxious_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_eranikus_tyrant_of_the_dream(Creature* pCreature)
{
    return new npc_eranikus_tyrant_of_the_dreamAI(pCreature);
}

#define MASS_HEALING    25839

struct npc_tyrandeAI : public ScriptedAI
{
    npc_tyrandeAI(Creature* c) : ScriptedAI(c) {}

    bool newWP;
    uint32 WPId;

    uint32 Heal_Timer;

    void Reset()
    override {
        newWP = false;
        WPId = 0;

        Heal_Timer = 3000;
    }

    void EnterCombat(Unit*) override {}

    void JustDied(Unit*)
    override {
        Creature* c = FindCreature(REMULOS, 500, me)->ToCreature();
        if (c)
            CAST_AI(npc_keeper_remulosAI, (c->AI()))->EventFailed();
    }

    void MoveInLineOfSight(Unit*) override {}

    void MovementInform(uint32 type, uint32 id)
    override {
        if (type != POINT_MOTION_TYPE)
            return;

        if (id == 0)
            return;

        if (id >= 2 && id <= 7)
        {
            newWP = true;
            WPId = id;
        }

        switch(id)
        {
        case 6:
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            break;
        case 7:
            me->ClearUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            break;
        case 8:
            newWP = true;
            WPId = 14;
            break;
        case 15:
        {
            newWP = true;
            WPId = 17;
            Creature* remulos = FindCreature(REMULOS, 500, me)->ToCreature();
            if (remulos)
                CAST_AI(npc_keeper_remulosAI, (remulos->AI()))->TyrandeComes(false);
            break;
        }
        case 18:
        {
            Creature* remulos = FindCreature(REMULOS, 500, me)->ToCreature();
            if (remulos)
                CAST_AI(npc_keeper_remulosAI, (remulos->AI()))->TyrandeComes(true);
            break;
        }
        default:
            break;
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if (newWP)
        {
            newWP = false;
            me->GetMotionMaster()->MovePoint(WPId+1, RemulosWP[WPId].x, RemulosWP[WPId].y, RemulosWP[WPId].z);
        }

        if (!me->IsStandState())
            return;

        Creature* remulos = FindCreature(REMULOS, 500, me)->ToCreature();
        if (remulos && CAST_AI(npc_keeper_remulosAI, (remulos->AI()))->GetPhase() != PHASE_COMBAT2)
            return;

        if (Heal_Timer <= diff)
        {
            DoCast(me, MASS_HEALING);
            Heal_Timer = 20000;
        } else
            Heal_Timer -= diff;
    }
};

CreatureAI* GetAI_npc_tyrande(Creature* pCreature)
{
    return new npc_tyrandeAI(pCreature);
}

struct npc_priestess_of_the_moonAI : public ScriptedAI
{
    npc_priestess_of_the_moonAI(Creature* c) : ScriptedAI(c) {}

    uint32 Shoot_Timer;

    void Reset()
    override {
        Shoot_Timer = 3000;
    }

    void MoveInLineOfSight(Unit*) override {}

    void EnterCombat(Unit* unit)
    override {
        if (unit->GetGUIDMid() == ERANIKUS)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            AttackStart(unit, false);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim(false))
            return;

        if (Shoot_Timer <= diff)
        {
            int bp0 = 1100;
            me->CastCustomSpell(me->GetVictim(), 37770, &bp0, nullptr, nullptr, false);
            Shoot_Timer = 3000;
        } else
            Shoot_Timer -= diff;
    }
};

CreatureAI* GetAI_npc_priestess_of_the_moon(Creature* pCreature)
{
    return new npc_priestess_of_the_moonAI(pCreature);
}

/*####
# AddSC
####*/

void AddSC_moonglade()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name="npc_bunthen_plainswind";
    newscript->OnGossipHello =  &GossipHello_npc_bunthen_plainswind;
    newscript->OnGossipSelect = &GossipSelect_npc_bunthen_plainswind;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_great_bear_spirit";
    newscript->OnGossipHello =  &GossipHello_npc_great_bear_spirit;
    newscript->OnGossipSelect = &GossipSelect_npc_great_bear_spirit;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_silva_filnaveth";
    newscript->OnGossipHello =  &GossipHello_npc_silva_filnaveth;
    newscript->OnGossipSelect = &GossipSelect_npc_silva_filnaveth;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_clintar_dreamwalker";
    newscript->OnQuestAccept = &QuestAccept_npc_clintar_dreamwalker;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_clintar_spirit";
    newscript->GetAI = &GetAI_npc_clintar_spirit;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_keeper_remulos";
    newscript->OnQuestAccept = &QuestAccept_npc_keeper_remulos;
    newscript->GetAI = &GetAI_npc_keeper_remulos;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_nightmare_phantasm";
    newscript->GetAI = &GetAI_npc_nightmare_phantasm;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_eranikus_tyrant_of_the_dream";
    newscript->GetAI = &GetAI_npc_eranikus_tyrant_of_the_dream;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_tyrande";
    newscript->GetAI = &GetAI_npc_tyrande;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_priestess_of_the_moon";
    newscript->GetAI = &GetAI_npc_priestess_of_the_moon;
    sScriptMgr->RegisterOLDScript(newscript);
}

