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
SDName: Dustwallow_Marsh
SD%Complete: 95
SDComment: Quest support: 558, 1173, 1324, 11126, 11180. Vendor Nat Pagle
SDCategory: Dustwallow Marsh
EndScriptData */

/* ContentData
mobs_risen_husk_spirit
npc_restless_apparition
npc_deserter_agitator
npc_lady_jaina_proudmoore
npc_nat_pagle
npc_overlord_mokmorokk
npc_private_hendel
npc_stinky
npc_cassa_crimsonwing
npc_ogron
npc_captured_totem
EndContentData */


#include "EscortAI.h"
#include "SimpleCooldown.h"

/*######
## mobs_risen_husk_spirit
######*/

enum eHuskSpirit
{
SPELL_SUMMON_RESTLESS_APPARITION    = 42511,
SPELL_CONSUME_FLESH                 = 37933,          //Risen Husk
SPELL_INTANGIBLE_PRESENCE           = 43127           //Risen Spirit
};

struct mobs_risen_husk_spiritAI : public ScriptedAI
{
    mobs_risen_husk_spiritAI(Creature *c) : ScriptedAI(c) {}

    uint32 ConsumeFlesh_Timer;
    uint32 IntangiblePresence_Timer;

    void Reset()
    override {
        ConsumeFlesh_Timer = 10000;
        IntangiblePresence_Timer = 5000;
    }

    void EnterCombat(Unit* pWho) override { }

    void DamageTaken(Unit* pDoneBy, uint32 &damage)
    override {
        if( pDoneBy->GetTypeId() == TYPEID_PLAYER )
            if (damage >= me->GetHealth() && (pDoneBy)->ToPlayer()->GetQuestStatus(11180) == QUEST_STATUS_INCOMPLETE)
                me->CastSpell(pDoneBy, SPELL_SUMMON_RESTLESS_APPARITION, false);
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        if (ConsumeFlesh_Timer < diff)
        {
            if( me->GetEntry() == 23555 )
                DoCast(me->GetVictim(),SPELL_CONSUME_FLESH);
            ConsumeFlesh_Timer = 15000;
        } else ConsumeFlesh_Timer -= diff;

        if (IntangiblePresence_Timer < diff)
        {
            if( me->GetEntry() == 23554 )
                DoCast(me->GetVictim(),SPELL_INTANGIBLE_PRESENCE);
            IntangiblePresence_Timer = 20000;
        } else IntangiblePresence_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mobs_risen_husk_spirit(Creature* pCreature)
{
    return new mobs_risen_husk_spiritAI (pCreature);
}

/*######
## npc_restless_apparition
######*/

bool GossipHello_npc_restless_apparition(Player* pPlayer, Creature* pCreature)
{
    SEND_DEFAULT_GOSSIP_MENU(pPlayer, pCreature);

    pPlayer->TalkedToCreature(pCreature->GetEntry(), pCreature->GetGUID());
    pCreature->SetInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

    return true;
}

/*######
## npc_deserter_agitator
######*/

struct npc_deserter_agitatorAI : public ScriptedAI
{
    npc_deserter_agitatorAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    override {
        me->SetFaction(894);
    }

    void EnterCombat(Unit* pWho) override {}
};

CreatureAI* GetAI_npc_deserter_agitator(Creature* pCreature)
{
    return new npc_deserter_agitatorAI (pCreature);
}

bool GossipHello_npc_deserter_agitator(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(11126) == QUEST_STATUS_INCOMPLETE)
    {
        pCreature->SetFaction(1883);
        pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        pPlayer->TalkedToCreature(pCreature->GetEntry(), pCreature->GetGUID());
    }
    else
        SEND_DEFAULT_GOSSIP_MENU(pPlayer, pCreature);

    return true;
}

/*######
## npc_lady_jaina_proudmoore
######*/

#define GOSSIP_ITEM_JAINA "I know this is rather silly but i have a young ward who is a bit shy and would like your autograph."

bool GossipHello_npc_lady_jaina_proudmoore(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu( pCreature->GetGUID() );

    if( pPlayer->GetQuestStatus(558) == QUEST_STATUS_INCOMPLETE )
        pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_JAINA, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INFO );

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);

    return true;
}

bool GossipSelect_npc_lady_jaina_proudmoore(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_SENDER_INFO)
    {
        pPlayer->SEND_GOSSIP_MENU_TEXTID(7012, pCreature->GetGUID());
        pPlayer->CastSpell(pPlayer, 23122, false);
    }
    return true;
}

/*######
## npc_nat_pagle
######*/

bool GossipHello_npc_nat_pagle(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->IsVendor() && pPlayer->GetQuestRewardStatus(8227))
    {
        pPlayer->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
        pPlayer->SEND_GOSSIP_MENU_TEXTID(7640, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU_TEXTID(7638, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_nat_pagle(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetGUID());

    return true;
}

/*######
## npc_overlord_mokmorokk
######*/

enum eOverlordMokmorokk
{
QUEST_CHALLENGE_OVERLORD    = 1173,

FACTION_NEUTRAL             = 120,
FACTION_UNFRIENDLY          = 14    //guessed
};

struct npc_overlord_mokmorokkAI : public ScriptedAI
{
    npc_overlord_mokmorokkAI(Creature *c) : ScriptedAI(c) {}
    
    Player* player;
    
    void Reset()
    override {
        me->SetFaction(FACTION_NEUTRAL);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        me->SetHealth(me->GetMaxHealth());
        me->CombatStop();
        me->DeleteThreatList();
    }
    
    void EnterCombat(Unit* pWho) override {}
    
    void UpdateAI(const uint32 diff)
    override {
        if (me->GetFaction() == FACTION_NEUTRAL) //if neutral, event is not running
            return;
            
        if (me->GetHealth() < (me->GetMaxHealth()/5.0f)) //at 20%, he stops fighting and complete the quest
        {
            player = (me->GetVictim())->ToPlayer();
            
            if (player && player->GetQuestStatus(QUEST_CHALLENGE_OVERLORD) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(4500, me->GetGUID());
            
            me->Say("Do not throw anymore!", LANG_UNIVERSAL); //FIXME probably not the right text
            //me->MonsterSay("N'en jetez plus !", LANG_UNIVERSAL, 0);
            Reset();
            
            return;
        }
        
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_overlord_mokmorokk(Creature* pCreature)
{
    return new npc_overlord_mokmorokkAI(pCreature);
}

bool GossipHello_npc_overlord_mokmorokk(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());
    
    if (pPlayer->GetQuestStatus(QUEST_CHALLENGE_OVERLORD) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Go away!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        
    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
    
    return true;
}

bool GossipSelect_npc_overlord_mokmorokk(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        pCreature->Say("We'll see about this!", LANG_UNIVERSAL, nullptr);
        pCreature->SetFaction(FACTION_UNFRIENDLY);
        pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        pCreature->AI()->AttackStart(pPlayer);
    }
    
    return true;
}

bool QuestAccept_npc_overlord_mokmorokk(Player* player, Creature* creature, const Quest* quest) {
    if (quest->GetQuestId() == 1173) {
        creature->SetFaction(FACTION_UNFRIENDLY);
        creature->AI()->AttackStart(player);
    }
    
    return true;
}

/*######
## npc_private_hendel
######*/

enum eHendel
{
    // looks like all this text ids are wrong.
    SAY_PROGRESS_1_TER          = -1000411, // signed for 3568
    SAY_PROGRESS_2_HEN          = -1000412, // signed for 3568
    SAY_PROGRESS_3_TER          = -1000413,
    SAY_PROGRESS_4_TER          = -1000414,
    EMOTE_SURRENDER             = -1000415,

    QUEST_MISSING_DIPLO_PT16    = 1324,
    FACTION_HOSTILE             = 168,                      //guessed, may be different

    NPC_SENTRY                  = 5184,                     //helps hendel
    NPC_JAINA                   = 4968,                     //appears once hendel gives up
    NPC_TERVOSH                 = 4967
};

//TODO: develop this further, end event not created
struct npc_private_hendelAI : public ScriptedAI
{
    npc_private_hendelAI(Creature* pCreature) : ScriptedAI(pCreature) { }

    void Reset()
    override {
        me->RestoreFaction();
    }

    void AttackedBy(Unit* pAttacker)
    override {
        if (me->GetVictim())
            return;

        if (me->IsFriendlyTo(pAttacker))
            return;

        AttackStart(pAttacker);
    }
    
    void EnterCombat(Unit* pWho) override {}

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    override {
        if (uiDamage > me->GetHealth() || ((me->GetHealth() - uiDamage)*100 / me->GetMaxHealth() < 20))
        {
            uiDamage = 0;

            if (Player* pPlayer = pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
                pPlayer->GroupEventHappens(QUEST_MISSING_DIPLO_PT16, me);

            DoScriptText(EMOTE_SURRENDER, me);
            EnterEvadeMode();
        }
    }
};

bool QuestAccept_npc_private_hendel(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_MISSING_DIPLO_PT16)
        pCreature->SetFaction(FACTION_HOSTILE);

    return true;
}

CreatureAI* GetAI_npc_private_hendel(Creature* pCreature)
{
    return new npc_private_hendelAI(pCreature);
}

/*######
## npc_stinky
######*/

enum eStinky
{
    QUEST_STINKYS_ESCAPE_H                       = 1270,
    QUEST_STINKYS_ESCAPE_A                       = 1222,
    SAY_QUEST_ACCEPTED                           = -1000507,
    SAY_STAY_1                                   = -1000508,
    SAY_STAY_2                                   = -1000509,
    SAY_STAY_3                                   = -1000510,
    SAY_STAY_4                                   = -1000511,
    SAY_STAY_5                                   = -1000512,
    SAY_STAY_6                                   = -1000513,
    SAY_QUEST_COMPLETE                           = -1000514,
    SAY_ATTACKED_1                               = -1000515,
    EMOTE_DISAPPEAR                              = -1000516
};

struct npc_stinkyAI : public npc_escortAI
{
    npc_stinkyAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        completed = false;
    }

    bool completed;

    void WaypointReached(uint32 i)
    override {
        Player* pPlayer = GetPlayerForEscort();
        if (!pPlayer)
            return;

        switch (i) {
        case 7:
            DoScriptText(SAY_STAY_1, me, pPlayer);
            break;
        case 11:
                DoScriptText(SAY_STAY_2, me, pPlayer);
            break;
        case 25:
                DoScriptText(SAY_STAY_3, me, pPlayer);
            break;
        case 26:
                DoScriptText(SAY_STAY_4, me, pPlayer);
            break;
        case 27:
                DoScriptText(SAY_STAY_5, me, pPlayer);
            break;
        case 28:
                DoScriptText(SAY_STAY_6, me, pPlayer);
            me->SetStandState(UNIT_STAND_STATE_KNEEL);
            break;
        case 29:
            me->SetStandState(UNIT_STAND_STATE_STAND);
            break;
        case 37:
            DoScriptText(SAY_QUEST_COMPLETE, me, pPlayer);
            me->SetSpeedRate(MOVE_RUN, 1.2f, true);
            //me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            if (pPlayer && pPlayer->GetQuestStatus(QUEST_STINKYS_ESCAPE_H))
                pPlayer->GroupEventHappens(QUEST_STINKYS_ESCAPE_H, me);
            if (pPlayer && pPlayer->GetQuestStatus(QUEST_STINKYS_ESCAPE_A))
                pPlayer->GroupEventHappens(QUEST_STINKYS_ESCAPE_A, me);
            completed = true;
            break;
        case 39:
            DoScriptText(EMOTE_DISAPPEAR, me);
            break;
        }
    }

    void EnterCombat(Unit* pWho)
    override {
        DoScriptText(SAY_ATTACKED_1, me, pWho);
    }

    void Reset() override {}

    void JustDied(Unit* /*pKiller*/)
    override {
        if (completed)
            return;

        Player* pPlayer = GetPlayerForEscort();
        if (HasEscortState(STATE_ESCORT_ESCORTING) && pPlayer)
        {
            if (pPlayer->GetQuestStatus(QUEST_STINKYS_ESCAPE_H))
                pPlayer->FailQuest(QUEST_STINKYS_ESCAPE_H);
            if (pPlayer->GetQuestStatus(QUEST_STINKYS_ESCAPE_A))
                pPlayer->FailQuest(QUEST_STINKYS_ESCAPE_A);
        }
    }

   void UpdateAI(const uint32 uiDiff)
    override {
        npc_escortAI::UpdateAI(uiDiff);

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

bool QuestAccept_npc_stinky(Player* pPlayer, Creature* pCreature, Quest const *quest)
{
    if (quest->GetQuestId() == QUEST_STINKYS_ESCAPE_H || QUEST_STINKYS_ESCAPE_A) {
        pCreature->SetFaction(250);
        pCreature->SetStandState(UNIT_STAND_STATE_STAND);
        DoScriptText(SAY_QUEST_ACCEPTED, pCreature);
        ((npc_escortAI*)(pCreature->AI()))->Start(false, false, false, pPlayer->GetGUID(), pCreature->GetEntry());
    }
    return true;
}

CreatureAI* GetAI_npc_stinky(Creature* pCreature)
{
    return new npc_stinkyAI(pCreature);
}

/*######
## npc_cassa_crimsonwing
######*/

bool GossipHello_npc_cassa_crimsonwing(Player* player, Creature* creature)
{
    if (creature->IsQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    if (player->GetQuestStatus(11142) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je dois survoler l'île d'Alcaz.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        
    SEND_PREPARED_GOSSIP_MENU(player, creature);
        
    return true;
}

bool GossipSelect_npc_cassa_crimsonwing(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    player->CLOSE_GOSSIP_MENU();

    if (action == GOSSIP_ACTION_INFO_DEF) {
        player->CastSpell(player, 42316, true);
        std::vector<uint32> nodes;

        nodes.resize(2);
        nodes[0] = 180;                                     //from
        nodes[1] = 181;                                     //end at
        player->ActivateTaxiPathTo(nodes);
    }
        
    return true;
}

/*######
## npc_ogron
######*/

//TODO : texts are mostly made up

enum eOgron
{
    QUEST_QUESTIONING_REETHE                     = 1273
};

struct npc_ogronAI : public npc_escortAI
{
    npc_ogronAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        completed = false;
    }

    bool completed;
    uint32 step;
    uint32 timer;

    void WaypointReached(uint32 i)
    override {
        Player* pPlayer = GetPlayerForEscort();
        if (!pPlayer)
            return;

        switch (i) {
        case 7:
            me->Say("It's Reethe! Let's go hear what he has to say.", LANG_UNIVERSAL);
            //me->MonsterSay("C'est Reethe ! Allons voir ce qu'il a à nous dire, hein ?", LANG_UNIVERSAL, 0);
            break;
        case 8:
            step = 1;
            timer = 500;
            break;
        }
    }

    void EnterCombat(Unit* pWho)
    override {
        
    }

    void Reset()
    override {
        step = 0;
    }

    void JustDied(Unit* /*pKiller*/)
    override {
        if (completed)
            return;

        Player* pPlayer = GetPlayerForEscort();
        if (HasEscortState(STATE_ESCORT_ESCORTING) && pPlayer)
        {
            if (pPlayer->GetQuestStatus(QUEST_QUESTIONING_REETHE))
                pPlayer->FailQuest(QUEST_QUESTIONING_REETHE);
        }
    }

   void UpdateAI(const uint32 uiDiff)
    override {
        npc_escortAI::UpdateAI(uiDiff);
        
        if (step) {
            if (timer <= uiDiff) {
                Creature* reethe = me->FindNearestCreature(4980, 15.0f, true);
                Creature* caldwell = me->FindNearestCreature(5046, 20.0f, true);
                if (reethe && (caldwell || step < 8)) {
                    switch (step) {
                    case 1:
                        reethe->Say("I swear, I didn't steal anything! There, look into my belongings, and go away!", LANG_UNIVERSAL);
                        //reethe->MonsterSay("Je vous jure, je n'ai rien volé ! Tenez, servez-vous dans mes affaires, et allez-vous en !", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 2000;
                        break;
                    case 2:
                        me->Say("Just tell us what you know about the Shady Rest, and I'll refrain to crush your skull.", LANG_UNIVERSAL);
                        //me->MonsterSay("Dis-nous simplement ce que tu sais de l'auberge du Repos Ombragé, et je ne vais pas t'exploser le crâne.", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 2000;
                        break;
                    case 3:
                        reethe->Say("Well... I may have took some items at the inn... But why would an oger be concerned about this?", LANG_UNIVERSAL);
                        //reethe->MonsterSay("Hé bien... Il se pourrait que j'aie pris quelques trucs à l'auberge... Mais pourquoi un ogre s'en inquiéterait-il ?", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 2000;
                        break;
                    case 4:
                        me->Say("Tell me more about the fire, else...", LANG_UNIVERSAL);
                        //me->MonsterSay("Ecoute-moi bien, si tu ne m'en dis pas plus au sujet du feu...", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 800;
                        break;
                    case 5:
                        reethe->Say("Stop right there, ogre!", LANG_UNIVERSAL);
                        //reethe->MonsterSay("Pas un pas de plus, ogre !", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 1500;
                        break;
                    case 6:
                        reethe->Say("I don't know anything about your fire.", LANG_UNIVERSAL);
                        //reethe->MonsterSay("Et je ne sais rien à propos de ton feu...", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 1000;
                        break;
                    case 7:
                        if (Creature* caldspawn = me->SummonCreature(5046, -3376.830322, -3208.791260, 35.163025, 5.946863, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000)) {
                            caldspawn->GetMotionMaster()->MovePoint(0, -3371.119385, -3212.487061, 34.137459);
                            caldspawn->SetFaction(35);
                        }
                        reethe->Say("What was that? Did you hear something?", LANG_UNIVERSAL);
//                        reethe->MonsterSay("Qu'est-ce que c'était ? Avez-vous entendu quelque chose ?", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 2000;
                        break;
                    case 8:
                        if (Creature* add = me->SummonCreature(5044, -3373.989014, -3207.442871, 35.073441, 5.826434, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                            me->SetFaction(35);
                        if (Creature* add = me->SummonCreature(5044, -3374.850342, -3209.195557, 34.980534, 5.826434, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                            me->SetFaction(35);
                        if (Creature* add = me->SummonCreature(5045, -3375.389404, -3211.398682, 34.845543, 6.043204, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                            me->SetFaction(35);
                        caldwell->Say("Paval Reethe! I found you at last. And you're dealing with ogres now? Do not worry, even traitors and desertors deserve mercy.", LANG_UNIVERSAL);
                        //caldwell->MonsterSay("Paval Reethe ! Enfin je vous trouve. Vous vous acoquinez avec des ogres maintenant ? N'ayez crainte, même les traîtres et les déserteurs méritent un peu de pitié.", LANG_UNIVERSAL, 0);
                        reethe->SetFlag(UNIT_FIELD_FLAGS, 0);
                        reethe->SetFaction(me->GetFaction());
                        ++step;
                        timer = 2000;
                        break;
                    case 9:
                        caldwell->Say("Soldier, show Lieutenant Reethe some of your mercy.", LANG_UNIVERSAL);
                        //caldwell->MonsterSay("Soldat, montrez au Lieutement Reethe un peu de votre pitié.", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 800;
                        break;
                    case 10:
                        if (Creature* hallan = me->FindNearestCreature(5045, 20.0f, true))
                            hallan->CastSpell(reethe, 7105 /* Fake Shot*/, true);
                        ++step;
                        timer = 500;
                        break;
                    case 11:
                        reethe->Say("Hallan... How could you...", LANG_UNIVERSAL);
                        //reethe->MonsterSay("Hallan... Je ne pensais pas que tu avais ça en toi...", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 500;
                        break;
                    case 12:
                        caldwell->Say("Well gentlemen, let's clean up the remaining.", LANG_UNIVERSAL);
                        //caldwell->MonsterSay("Bien, maintenant, nettoyez le reste, messieurs !", LANG_UNIVERSAL, 0);
                        me->Say("What?! You'll die for this human.", LANG_UNIVERSAL);
                        //me->MonsterSay("Nom de... ! Tu ferais mieux de ne pas rendre l'âme devant moi, humain !", LANG_UNIVERSAL, 0);
                        ++step;
                        timer = 1000;
                        break;
                    case 13:
                    {
                        //TODO
                        /*std::list<Creature*> skirms;
                        me->GetCreatureListWithEntryInGrid(skirms, 5044, 30.0f);
                        for (std::list<Creature*>::iterator it = skirms.begin(); it != skirms.end(); it++) {
                            (*it)->SetFaction(14);
                            (*it)->AI()->AttackStart(reethe);
                        }
                        caldwell->SetFaction(14);
                        caldwell->AI()->AttackStart(reethe);
                        if (Creature* hallan = me->FindNearestCreature(5045, 20.0f, true)) {
                            hallan->SetFaction(14);
                            hallan->AI()->AttackStart(reethe);
                        }*/
                        ++step;
                        timer = 5000;
                        break;
                    }
                    case 14:
                        if (Player* pPlayer = GetPlayerForEscort())
                            pPlayer->AreaExploredOrEventHappens(QUEST_QUESTIONING_REETHE);
                        ++step;
                        timer = 999999;
                    }
                }
            }
            else
                timer -= uiDiff;
        }

        if (!UpdateVictim()) {
            if (step == 15) {
                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->AreaExploredOrEventHappens(QUEST_QUESTIONING_REETHE);
                
                step = 0;
                timer = 0;
                completed = true;
                
                me->DisappearAndDie();
                me->Respawn();
            }
            
            return;
        }

        DoMeleeAttackIfReady();
    }
};

bool QuestAccept_npc_ogron(Player* pPlayer, Creature* pCreature, Quest const *quest)
{
    if (quest->GetQuestId() == QUEST_QUESTIONING_REETHE) {
        pCreature->SetFaction(pPlayer->GetFaction());
        pCreature->SetStandState(UNIT_STAND_STATE_STAND);
        pCreature->Say("I saw a fire on the island there, as well as a human. Let's go check it.", LANG_UNIVERSAL);
        //pCreature->MonsterSay("J'ai remarqué du feu sur cette île, là-bas. Et un humain, aussi. Allons vérifier.", LANG_UNIVERSAL, 0);
        ((npc_escortAI*)(pCreature->AI()))->Start(true, true, false, pPlayer->GetGUID(), pCreature->GetEntry());
        ((npc_escortAI*)(pCreature->AI()))->SetDespawnAtEnd(false);
    }
    return true;
}

CreatureAI* GetAI_npc_ogron(Creature* pCreature)
{
    return new npc_ogronAI(pCreature);
}

/*######
## npc_captured_totem
######*/

struct npc_captured_totemAI : public ScriptedAI
{
    npc_captured_totemAI(Creature* creature) : ScriptedAI(creature)
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetFaction(35);
        SetCombatMovementAllowed(false);
    }

    void EnterCombat(Unit* pWho)
    override {
    }
    
    void MasterKilledUnit(Unit* victim)
    override {
        if (!me->GetOwner())
            return;
        
        if (victim->GetEntry() == 4344 || victim->GetEntry() == 4345)
            me->GetOwner()->ToPlayer()->KilledMonsterCredit(23811, victim->GetGUID());
    }
};

CreatureAI* GetAI_npc_captured_totem(Creature* creature)
{
    return new npc_captured_totemAI(creature);
}

/*######
## npc_searingwhelp
######*/

#define TIMER_FIREBALL 6000
#define SPELL_FIREBALL 11021

struct SearingWhelpAI : public ScriptedAI
{
    SimpleCooldown* SCDBdf;

    SearingWhelpAI(Creature *c) : ScriptedAI(c)
    {
        SCDBdf = new SimpleCooldown(TIMER_FIREBALL);
    }
    
    void EnterCombat(Unit* who)
    override {
        if(who)
            DoCast(who,SPELL_FIREBALL,false);
    }
    
    void Reset()
    override {
        SCDBdf->reinitCD();
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;
        
        if(SCDBdf->CheckAndUpdate(diff) && me->GetVictim())
            DoCast(me->GetVictim(),SPELL_FIREBALL,false);
        
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_SearingWhelp(Creature *_Creature)
{
    return new SearingWhelpAI(_Creature);
}

/*######
## AddSC
######*/

void AddSC_dustwallow_marsh()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name="mobs_risen_husk_spirit";
    newscript->GetAI = &GetAI_mobs_risen_husk_spirit;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_restless_apparition";
    newscript->OnGossipHello =   &GossipHello_npc_restless_apparition;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_deserter_agitator";
    newscript->GetAI = &GetAI_npc_deserter_agitator;
    newscript->OnGossipHello = &GossipHello_npc_deserter_agitator;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_lady_jaina_proudmoore";
    newscript->OnGossipHello = &GossipHello_npc_lady_jaina_proudmoore;
    newscript->OnGossipSelect = &GossipSelect_npc_lady_jaina_proudmoore;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_nat_pagle";
    newscript->OnGossipHello = &GossipHello_npc_nat_pagle;
    newscript->OnGossipSelect = &GossipSelect_npc_nat_pagle;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_overlord_mokmorokk";
    newscript->OnGossipHello =  &GossipHello_npc_overlord_mokmorokk;
    newscript->OnGossipSelect = &GossipSelect_npc_overlord_mokmorokk;
    newscript->OnQuestAccept = &QuestAccept_npc_overlord_mokmorokk;
    newscript->GetAI = &GetAI_npc_overlord_mokmorokk;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_private_hendel";
    newscript->GetAI = &GetAI_npc_private_hendel;
    newscript->OnQuestAccept = &QuestAccept_npc_private_hendel;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_stinky";
    newscript->GetAI = &GetAI_npc_stinky;
    newscript->OnQuestAccept = &QuestAccept_npc_stinky;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_cassa_crimsonwing";
    newscript->OnGossipHello = &GossipHello_npc_cassa_crimsonwing;
    newscript->OnGossipSelect = &GossipSelect_npc_cassa_crimsonwing;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_ogron";
    newscript->GetAI = &GetAI_npc_ogron;
    newscript->OnQuestAccept = &QuestAccept_npc_ogron;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_captured_totem";
    newscript->GetAI = &GetAI_npc_captured_totem;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_searingwhelp";
    newscript->GetAI = &GetAI_SearingWhelp;
    sScriptMgr->RegisterOLDScript(newscript);
}
