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
SDName: Nagrand
SD%Complete: 90
SDComment: Quest support: 9849, 9918, 9874, 9991, 10107, 10108, 10044, 10172, 10646, 10085, 10987. TextId's unknown for altruis_the_sufferer and greatmother_geyah (npc_text)
SDCategory: Nagrand
EndScriptData */

/* ContentData
mob_shattered_rumbler
mob_lump
mob_sunspring_villager
npc_altruis_the_sufferer
npc_greatmother_geyah
npc_lantresor_of_the_blade
npc_creditmarker_visit_with_ancestors
mob_sparrowhawk
npc_maghar_captive
npc_sharvak
npc_kurenai_captive
EndContentData */


#include "EscortAI.h"
#include "Pet.h"

/*######
## mob_shattered_rumbler - this should be done with ACID
######*/

struct mob_shattered_rumblerAI : public ScriptedAI
{
    bool Spawn;

    mob_shattered_rumblerAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    override {
        Spawn = false;
    }

    void EnterCombat(Unit* pWho) override {}

    void SpellHit(Unit* pHitter, const SpellInfo* Spellkind)
    override {
        if(Spellkind->Id == 32001 && !Spawn)
        {
            float x = me->GetPositionX();
            float y = me->GetPositionY();
            float z = me->GetPositionZ();

            pHitter->SummonCreature(18181, x+(0.7 * (rand()%30)), y+(rand()%5), z, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            pHitter->SummonCreature(18181, x+(rand()%5), y-(rand()%5), z, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            pHitter->SummonCreature(18181, x-(rand()%5), y+(0.5 *(rand()%60)), z, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            me->SetDeathState(CORPSE);
            Spawn = true;
        }
        return;
    }
};

CreatureAI* GetAI_mob_shattered_rumbler(Creature* pCreature)
{
    return new mob_shattered_rumblerAI(pCreature);
}

/*######
## mob_lump
######*/

enum eLump
{
SPELL_VISUAL_SLEEP      = 16093,
SPELL_SPEAR_THROW       = 32248,

LUMP_SAY0               = -1000293,
LUMP_SAY1               = -1000294,

LUMP_DEFEAT             = -1000295
};

#define GOSSIP_HL "I need answers, ogre!"
#define GOSSIP_SL1 "Why are Boulderfist out this far? You know that this is Kurenai territory."
#define GOSSIP_SL2 "And you think you can just eat anything you want? You're obviously trying to eat the Broken of Telaar."
#define GOSSIP_SL3 "This means war, Lump! War I say!"

struct mob_lumpAI : public ScriptedAI
{
    mob_lumpAI(Creature *c) : ScriptedAI(c)
    {
        bReset = false;
    }

    uint32 Reset_Timer;
    uint32 Spear_Throw_Timer;
    bool bReset;

    void Reset()
    override {
        Reset_Timer = 60000;
        Spear_Throw_Timer = 2000;

        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void DamageTaken(Unit* pDoneBy, uint32 & damage)
    override {
        if (pDoneBy->GetTypeId() == TYPEID_PLAYER && (me->GetHealth() - damage)*100 / me->GetMaxHealth() < 30)
        {
            if (!bReset && (pDoneBy)->ToPlayer()->GetQuestStatus(9918) == QUEST_STATUS_INCOMPLETE)
            {
                //Take 0 damage
                damage = 0;

                (pDoneBy)->ToPlayer()->AttackStop();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAllAuras();
                me->DeleteThreatList();
                me->CombatStop();
                me->SetFaction(1080);               //friendly
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_SIT);
                DoScriptText(LUMP_DEFEAT, me);

                bReset = true;
            }
        }
    }

    void EnterCombat(Unit* pWho)
    override {
        if (me->HasAuraEffect(SPELL_VISUAL_SLEEP))
            me->RemoveAura(SPELL_VISUAL_SLEEP,0);

        if (!me->IsStandState())
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_NONE);

        switch(rand()%2)
        {
            case 0: DoScriptText(LUMP_SAY0, me); break;
            case 1: DoScriptText(LUMP_SAY1, me); break;
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        //check if we waiting for a reset
        if (bReset)
        {
            if (Reset_Timer < diff)
            {
                EnterEvadeMode();
                bReset = false;
                me->SetFaction(1711);               //hostile
                return;
            }
            else Reset_Timer -= diff;
        }

        //Return since we have no target
        if (!UpdateVictim())
            return;

        //Spear_Throw_Timer
        if (Spear_Throw_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_SPEAR_THROW);
            Spear_Throw_Timer = 20000;
        } else Spear_Throw_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_lump(Creature* pCreature)
{
    return new mob_lumpAI(pCreature);
}

bool GossipHello_mob_lump(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(9918) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU_TEXTID(9352, pCreature->GetGUID());

    return true;
}

bool GossipSelect_mob_lump(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SL1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9353, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SL2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9354, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SL3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9355, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9356, pCreature->GetGUID());
            pPlayer->TalkedToCreature(18354, pCreature->GetGUID());
            break;
    }
    return true;
}

/*####
# mob_sunspring_villager - should be done with ACID
####*/

struct mob_sunspring_villagerAI : public ScriptedAI
{
    mob_sunspring_villagerAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    override {
        me->SetUInt32Value(UNIT_DYNAMIC_FLAGS, 32);
        me->SetUInt32Value(UNIT_FIELD_BYTES_1,7);   // lay down
    }

    void EnterCombat(Unit* pWho) override {}

    void SpellHit(Unit* pCaster, const SpellInfo* spell)
    override {
        if(spell->Id == 32146)
        {
            me->DespawnOrUnsummon();
        }
    }
};
CreatureAI* GetAI_mob_sunspring_villager(Creature* pCreature)
{
    return new mob_sunspring_villagerAI(pCreature);
}

/*######
## npc_altruis_the_sufferer
######*/

#define GOSSIP_HATS1 "I see twisted steel and smell sundered earth."
#define GOSSIP_HATS2 "Well...?"
#define GOSSIP_HATS3 "[PH] Story about Illidan's Pupil"

#define GOSSIP_SATS1 "Legion?"
#define GOSSIP_SATS2 "And now?"
#define GOSSIP_SATS3 "How do you see them now?"
#define GOSSIP_SATS4 "Forge camps?"
#define GOSSIP_SATS5 "Ok."
#define GOSSIP_SATS6 "[PH] Story done"

bool GossipHello_npc_altruis_the_sufferer(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID() );

    //gossip before obtaining Survey the Land
    if (pPlayer->GetQuestStatus(9991) == QUEST_STATUS_NONE )
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HATS1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);

    //gossip when Survey the Land is incomplete (technically, after the flight)
    if (pPlayer->GetQuestStatus(9991) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HATS2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+20);

    //wowwiki.com/Varedis
    if (pPlayer->GetQuestStatus(10646) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HATS3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+30);

    pPlayer->SEND_GOSSIP_MENU_TEXTID(9419, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_altruis_the_sufferer(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF+10:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SATS1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9420, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+11:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SATS2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9421, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+12:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SATS3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9422, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+13:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SATS4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9423, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+14:
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9424, pCreature->GetGUID());
            break;

        case GOSSIP_ACTION_INFO_DEF+20:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SATS5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9427, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+21:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->AreaExploredOrEventHappens(9991);
            break;

        case GOSSIP_ACTION_INFO_DEF+30:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SATS6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(384, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+31:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->AreaExploredOrEventHappens(10646);
            break;
    }
    
    return true;
}

bool QuestAccept_npc_altruis_the_sufferer(Player* pPlayer, Creature* creature, Quest const* pQuest )
{
    if (pQuest->GetQuestId() == 9991 && !pPlayer->GetQuestRewardStatus(9991))              //Survey the Land, q-id 9991
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        std::vector<uint32> nodes;

        nodes.resize(2);
        nodes[0] = 113;                                     //from
        nodes[1] = 114;                                     //end at
        pPlayer->ActivateTaxiPathTo(nodes);                  //TaxiPath 532
        
        pPlayer->AreaExploredOrEventHappens(9991);
    }
    
    return true;
}

/*######
## npc_greatmother_geyah
######*/

#define GOSSIP_HGG1 "Hello, Greatmother. Garrosh told me that you wanted to speak with me."
#define GOSSIP_HGG2 "Garrosh is beyond redemption, Greatmother. I fear that in helping the Mag'har, I have convinced Garrosh that he is unfit to lead."

#define GOSSIP_SGG1 "You raised all of the orcs here, Greatmother?"
#define GOSSIP_SGG2 "Do you believe that?"
#define GOSSIP_SGG3 "What can be done? I have tried many different things. I have done my best to help the people of Nagrand. Each time I have approached Garrosh, he has dismissed me."
#define GOSSIP_SGG4 "Left? How can you choose to leave?"
#define GOSSIP_SGG5 "What is this duty?"
#define GOSSIP_SGG6 "Is there anything I can do for you, Greatmother?"
#define GOSSIP_SGG7 "I have done all that I could, Greatmother. I thank you for your kind words."
#define GOSSIP_SGG8 "Greatmother, you are the mother of Durotan?"
#define GOSSIP_SGG9 "Greatmother, I never had the honor. Durotan died long before my time, but his heroics are known to all on my world. The orcs of Azeroth reside in a place known as Durotar, named after your son. And ... (You take a moment to breathe and think through what you are about to tell the Greatmother.)"
#define GOSSIP_SGG10 "It is my Warchief, Greatmother. The leader of my people. From my world. He ... He is the son of Durotan. He is your grandchild."
#define GOSSIP_SGG11 "I will return to Azeroth at once, Greatmother."

//all the textId's for the below is unknown, but i do believe the gossip item texts are proper.
bool GossipHello_npc_greatmother_geyah(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(10044) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HGG1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
    }
    else if (pPlayer->GetQuestStatus(10172) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HGG2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
        SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
    }
    else
        SEND_DEFAULT_GOSSIP_MENU(pPlayer, pCreature);

    return true;
}

bool GossipSelect_npc_greatmother_geyah(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:
            pPlayer->AreaExploredOrEventHappens(10044);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;

        case GOSSIP_ACTION_INFO_DEF + 10:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG8, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG9, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG10, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 14:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SGG11, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 15:
            pPlayer->AreaExploredOrEventHappens(10172);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
    
    return true;
}

/*######
## npc_lantresor_of_the_blade
######*/

#define GOSSIP_HLB "I have killed many of your ogres, Lantresor. I have no fear."
#define GOSSIP_SLB1 "Should I know? You look like an orc to me."
#define GOSSIP_SLB2 "And the other half?"
#define GOSSIP_SLB3 "I have heard of your kind, but I never thought to see the day when I would meet a half-breed."
#define GOSSIP_SLB4 "My apologies. I did not mean to offend. I am here on behalf of my people."
#define GOSSIP_SLB5 "My people ask that you pull back your Boulderfist ogres and cease all attacks on our territories. In return, we will also pull back our forces."
#define GOSSIP_SLB6 "We will fight you until the end, then, Lantresor. We will not stand idly by as you pillage our towns and kill our people."
#define GOSSIP_SLB7 "What do I need to do?"

bool GossipHello_npc_lantresor_of_the_blade(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(10107) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(10108) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HLB, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU_TEXTID(9361, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_lantresor_of_the_blade(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SLB1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9362, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SLB2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9363, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SLB3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9364, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SLB4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9365, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SLB5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9366, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SLB6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9367, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SLB7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9368, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->SEND_GOSSIP_MENU_TEXTID(9369, pCreature->GetGUID());
            if (pPlayer->GetQuestStatus(10107) == QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(10107);
            if (pPlayer->GetQuestStatus(10108) == QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(10108);
            break;
    }
    return true;
}

/*######
## npc_creditmarker_visist_with_ancestors
######*/

struct npc_creditmarker_visit_with_ancestorsAI : public ScriptedAI
{
    npc_creditmarker_visit_with_ancestorsAI(Creature* c) : ScriptedAI(c) {}

    void Reset() override {}

    void EnterCombat(Unit* pWho) override {}

    void MoveInLineOfSight(Unit* pWho)
    override {
        if(!pWho)
            return;

        if(pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if((pWho)->ToPlayer()->GetQuestStatus(10085) == QUEST_STATUS_INCOMPLETE)
            {
                uint32 creditMarkerId = me->GetEntry();
                if((creditMarkerId >= 18840) && (creditMarkerId <= 18843))
                {
                    // 18840: Sunspring, 18841: Laughing, 18842: Garadar, 18843: Bleeding
                    if(!(pWho)->ToPlayer()->GetReqKillOrCastCurrentCount(10085, creditMarkerId))
                        (pWho)->ToPlayer()->KilledMonsterCredit(creditMarkerId, me->GetGUID());
                }
            }
        }
    }
};

CreatureAI* GetAI_npc_creditmarker_visit_with_ancestors(Creature* pCreature)
{
    return new npc_creditmarker_visit_with_ancestorsAI(pCreature);
}

/*######
## mob_sparrowhawk
######*/

enum eSparrowhawk
{
SPELL_SPARROWHAWK_NET           = 39810,
SPELL_ITEM_CAPTIVE_SPARROWHAWK  = 39812
};

struct mob_sparrowhawkAI : public ScriptedAI
{

    mob_sparrowhawkAI(Creature* c) : ScriptedAI(c) {}

    uint32 Check_Timer;
    uint64 PlayerGUID;
    bool fleeing;

    void Reset()
    override {
        me->RemoveAurasDueToSpell(SPELL_SPARROWHAWK_NET);
        Check_Timer = 1000;
        PlayerGUID = 0;
        fleeing = false;
    }
    void AttackStart(Unit* pWho)
    override {
        if(PlayerGUID)
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void EnterCombat(Unit* pWho) override {}

    void MoveInLineOfSight(Unit* pWho)
    override {
        if(!pWho || PlayerGUID)
            return;

        if(!PlayerGUID && pWho->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap((pWho), 30) && (pWho)->ToPlayer()->GetQuestStatus(10987) == QUEST_STATUS_INCOMPLETE)
        {
            PlayerGUID = pWho->GetGUID();
            return;
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void UpdateAI(const uint32 diff)
    override {
        if(Check_Timer < diff)
        {
            if(PlayerGUID)
            {
                if(fleeing && me->GetMotionMaster()->GetCurrentMovementGeneratorType() != FLEEING_MOTION_TYPE)
                    fleeing = false;

                Player* player = (ObjectAccessor::GetUnit((*me), PlayerGUID))->ToPlayer();
                if(player && me->IsWithinDistInMap(player, 30))
                {
                    if(!fleeing)
                    {
                        me->DeleteThreatList();
                        me->GetMotionMaster()->MoveFleeing(player);
                        fleeing = true;
                    }
                }
                else if(fleeing)
                {
                    me->GetMotionMaster()->MovementExpired(false);
                    PlayerGUID = 0;
                    fleeing = false;
                }
            }
            Check_Timer = 1000;
        } else Check_Timer -= diff;

        if (PlayerGUID)
            return;

        ScriptedAI::UpdateAI(diff);
    }

    void SpellHit(Unit* pCaster, const SpellInfo* spell)
    override {
        if (pCaster->GetTypeId() == TYPEID_PLAYER)
        {
            if(spell->Id == SPELL_SPARROWHAWK_NET && (pCaster)->ToPlayer()->GetQuestStatus(10987) == QUEST_STATUS_INCOMPLETE)
            {
                me->CastSpell(pCaster, SPELL_ITEM_CAPTIVE_SPARROWHAWK, true);
                me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
            }
        }
        
        return;
    }
};

CreatureAI* GetAI_mob_sparrowhawk(Creature* pCreature)
{
    return new mob_sparrowhawkAI(pCreature);
}

/*#####
## npc_maghar_captive
#####*/

enum eMagharCaptive
{
    SAY_MAG_START               = -1000482,
    SAY_MAG_NO_ESCAPE           = -1000483,
    SAY_MAG_MORE                = -1000484,
    SAY_MAG_MORE_REPLY          = -1000485,
    SAY_MAG_LIGHTNING           = -1000486,
    SAY_MAG_SHOCK               = -1000487,
    SAY_MAG_COMPLETE            = -1000488,

    SPELL_CHAIN_LIGHTNING       = 16006,
    SPELL_EARTHBIND_TOTEM       = 15786,
    SPELL_FROST_SHOCK           = 12548,
    SPELL_HEALING_WAVE          = 12491,

    QUEST_TOTEM_KARDASH_H       = 9868,

    NPC_MURK_RAIDER             = 18203,
    NPC_MURK_BRUTE              = 18211,
    NPC_MURK_SCAVENGER          = 18207,
    NPC_MURK_PUTRIFIER          = 18202
};

static float m_afAmbushA[]= {-1568.805786f, 8533.873047f, 1.958f};
static float m_afAmbushB[]= {-1491.554321f, 8506.483398f, 1.248f};

struct npc_maghar_captiveAI : public npc_escortAI
{
    npc_maghar_captiveAI(Creature* pCreature) : npc_escortAI(pCreature), summons(me) {}

    uint32 m_uiChainLightningTimer;
    uint32 m_uiHealTimer;
    uint32 m_uiFrostShockTimer;
    
    SummonList summons;

    void Reset()
    override {
        m_uiChainLightningTimer = 1000;
        m_uiHealTimer = 0;
        m_uiFrostShockTimer = 6000;
    }

    void EnterCombat(Unit* pWho)
    override {
        DoCast(me, SPELL_EARTHBIND_TOTEM, false);
    }

    void WaypointReached(uint32 uiPointId)
    override {
        switch(uiPointId)
        {
            case 7:
                DoScriptText(SAY_MAG_MORE, me);

                if (Creature* pTemp = me->SummonCreature(NPC_MURK_PUTRIFIER, m_afAmbushB[0], m_afAmbushB[1], m_afAmbushB[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000))
                    DoScriptText(SAY_MAG_MORE_REPLY, pTemp);

                me->SummonCreature(NPC_MURK_PUTRIFIER, m_afAmbushB[0]-2.5f, m_afAmbushB[1]-2.5f, m_afAmbushB[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);

                me->SummonCreature(NPC_MURK_SCAVENGER, m_afAmbushB[0]+2.5f, m_afAmbushB[1]+2.5f, m_afAmbushB[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                me->SummonCreature(NPC_MURK_SCAVENGER, m_afAmbushB[0]+2.5f, m_afAmbushB[1]-2.5f, m_afAmbushB[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                break;
            case 16:
                DoScriptText(SAY_MAG_COMPLETE, me);

                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->GroupEventHappens(QUEST_TOTEM_KARDASH_H, me);

                SetRun();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                break;
        }
    }

    void JustSummoned(Creature* pSummoned)
    override {
        if (pSummoned->GetEntry() == NPC_MURK_BRUTE)
            DoScriptText(SAY_MAG_NO_ESCAPE, pSummoned);

        if (pSummoned->IsTotem())
            return;

        pSummoned->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
        pSummoned->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
        pSummoned->AI()->AttackStart(me);
    }

    void SpellHitTarget(Unit* pTarget, const SpellInfo* pSpell)
    override {
        if (pSpell->Id == SPELL_CHAIN_LIGHTNING)
        {
            if (rand()%10)
                return;

            DoScriptText(SAY_MAG_LIGHTNING, me);
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (/*!me->SelectHostilTarget() ||*/ !me->GetVictim())
            return;

        if (m_uiChainLightningTimer <= uiDiff)
        {
            DoCast(me->GetVictim(), SPELL_CHAIN_LIGHTNING);
            m_uiChainLightningTimer = urand(7000, 14000);
        }
        else
            m_uiChainLightningTimer -= uiDiff;

        if (me->GetHealth()*100 < me->GetMaxHealth()*30)
        {
            if (m_uiHealTimer <= uiDiff)
            {
                DoCast(me, SPELL_HEALING_WAVE);
                m_uiHealTimer = 5000;
            }
            else
                m_uiHealTimer -= uiDiff;
        }

        if (m_uiFrostShockTimer <= uiDiff)
        {
            DoCast(me->GetVictim(), SPELL_FROST_SHOCK);
            m_uiFrostShockTimer = urand(7500, 15000);
        }
        else
            m_uiFrostShockTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

bool QuestAccept_npc_maghar_captive(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_TOTEM_KARDASH_H)
    {
        if (npc_maghar_captiveAI* pEscortAI = CAST_AI(npc_maghar_captiveAI, (pCreature->AI())))
        {
            pCreature->SetStandState(UNIT_STAND_STATE_STAND);
            pCreature->SetFaction(232);
            pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);

            pEscortAI->Start(true, true, false, pPlayer->GetGUID());

            DoScriptText(SAY_MAG_START, pCreature);

            pCreature->SummonCreature(NPC_MURK_RAIDER, m_afAmbushA[0]+2.5f, m_afAmbushA[1]-2.5f, m_afAmbushA[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
            pCreature->SummonCreature(NPC_MURK_PUTRIFIER, m_afAmbushA[0]-2.5f, m_afAmbushA[1]+2.5f, m_afAmbushA[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
            pCreature->SummonCreature(NPC_MURK_BRUTE, m_afAmbushA[0], m_afAmbushA[1], m_afAmbushA[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
        }
    }
    return true;
}

CreatureAI* GetAI_npc_maghar_captive(Creature* pCreature)
{
    auto  captiveAI = new npc_maghar_captiveAI(pCreature);
    
    captiveAI->AddWaypoint(0, -1581.410034, 8557.933594, 2.726),
    captiveAI->AddWaypoint(1, -1579.908447, 8553.716797, 2.559),
    captiveAI->AddWaypoint(2, -1577.829102, 8549.880859, 2.001),
    captiveAI->AddWaypoint(3, -1571.161987, 8543.494141, 2.001),
    captiveAI->AddWaypoint(4, -1563.944824, 8530.334961, 1.605),
    captiveAI->AddWaypoint(5, -1554.565552, 8518.413086, 0.364),
    captiveAI->AddWaypoint(6, -1549.239136, 8515.518555, 0.293),
    captiveAI->AddWaypoint(7, -1518.490112, 8516.771484, 0.683, 2000),
    captiveAI->AddWaypoint(8, -1505.038940, 8513.247070, 0.672),
    captiveAI->AddWaypoint(9, -1476.161133, 8496.066406, 2.157),
    captiveAI->AddWaypoint(10, -1464.450684, 8492.601563, 3.529),
    captiveAI->AddWaypoint(11, -1457.568359, 8492.183594, 4.449),
    captiveAI->AddWaypoint(12, -1444.100342, 8499.031250, 6.177),
    captiveAI->AddWaypoint(13, -1426.472168, 8510.116211, 7.686),
    captiveAI->AddWaypoint(14, -1403.685303, 8524.146484, 9.680),
    captiveAI->AddWaypoint(15, -1384.890503, 8542.014648, 11.180),
    captiveAI->AddWaypoint(16, -1382.286133, 8539.869141, 11.139, 7500),
    captiveAI->AddWaypoint(17, -1361.224609, 8521.440430, 11.144),
    captiveAI->AddWaypoint(18, -1324.803589, 8510.688477, 13.050),
    captiveAI->AddWaypoint(19, -1312.075439, 8492.709961, 14.235);
    
    return (CreatureAI*)captiveAI;

}

/*######
## npc_sharvak
######*/

struct npc_sharvakAI : public ScriptedAI
{
    npc_sharvakAI(Creature* c) : ScriptedAI(c) {}
    
    void EnterCombat(Unit* pWho) override {}
    
    void MoveInLineOfSight(Unit* pWho)
    override {
        if (me->GetDistance(pWho) <= 5.0f && pWho->GetTypeId() == TYPEID_PLAYER) {
			if (uint64 critter_guid = pWho->ToPlayer()->GetCritterGUID())
				if (Creature* pet = me->GetMap()->GetCreature(critter_guid)) {
					if (pWho->ToPlayer()->GetQuestStatus(10953) == QUEST_STATUS_INCOMPLETE && pet->GetEntry() == 22817)
						pWho->ToPlayer()->AreaExploredOrEventHappens(10953);
            }
        }
    }
};

CreatureAI* GetAI_npc_sharvakAI(Creature* pCreature)
{
    return new npc_sharvakAI(pCreature);
}

/*######
## npc_jheel
######*/

struct npc_jheelAI : public ScriptedAI
{
    npc_jheelAI(Creature* c) : ScriptedAI(c) {}
    
    void EnterCombat(Unit* pWho) override {}
    
    void MoveInLineOfSight(Unit* pWho)
    override {
        if (me->GetDistance(pWho) <= 5.0f && pWho->GetTypeId() == TYPEID_PLAYER) {
			if (uint64 critter_guid = pWho->ToPlayer()->GetCritterGUID())
				if (Creature* pet = me->GetMap()->GetCreature(critter_guid)) {
					if (pWho->ToPlayer()->GetQuestStatus(10954) == QUEST_STATUS_INCOMPLETE && pet->GetEntry() == 22818)
						pWho->ToPlayer()->AreaExploredOrEventHappens(10954);
				}
        }
    }
};

CreatureAI* GetAI_npc_jheelAI(Creature* pCreature)
{
    return new npc_jheelAI(pCreature);
}

/*######
## npc_rethhedron
######*/

struct npc_rethhedronAI : public ScriptedAI
{
    npc_rethhedronAI(Creature* c) : ScriptedAI(c) {}
    
    bool quest;
    
    void Reset()
    override {
        quest = false;
    }
    
    void EnterCombat(Unit* pWho) override {}
    
    void SpellHit(Unit* pHitter, const SpellInfo* spell)
    override {
        if (pHitter->ToPlayer()) {
            if (spell->Id == 41291) {
                me->AddUnitState(UNIT_STATE_ROOT);
                quest = true;
            }
        }
    }
    
    void JustDied(Unit* pKiller)
    override {
        if (!pKiller->ToPlayer())
            return;

        if (quest)
            pKiller->ToPlayer()->AreaExploredOrEventHappens(11090);
    }
    
    void UpdateAI(uint32 const diff)
    override {
        ScriptedAI::UpdateAI(diff);
    }
};

CreatureAI* GetAI_npc_rethhedronAI(Creature* pCreature)
{
    return new npc_rethhedronAI(pCreature);
}

/*######
## npc_kurenai_captive
######*/

enum KurenaiCaptive
{
    SAY_KUR_START                   = -1000758,
    SAY_KUR_NO_ESCAPE               = -1000759,
    SAY_KUR_MORE                    = -1000760,
    SAY_KUR_MORE_TWO                = -1000761,
    SAY_KUR_LIGHTNING               = -1000762,
    SAY_KUR_SHOCK                   = -1000763,
    SAY_KUR_COMPLETE                = -1000764,

    SPELL_KUR_CHAIN_LIGHTNING       = 16006,
    SPELL_KUR_EARTHBIND_TOTEM       = 15786,
    SPELL_KUR_FROST_SHOCK           = 12548,
    SPELL_KUR_HEALING_WAVE          = 12491,

    QUEST_TOTEM_KARDASH_A           = 9879,

    NPC_KUR_MURK_RAIDER             = 18203,
    NPC_KUR_MURK_BRUTE              = 18211,
    NPC_KUR_MURK_SCAVENGER          = 18207,
    NPC_KUR_MURK_PUTRIFIER          = 18202,
};

static float kurenaiAmbushA[]= {-1515.003052f, 8517.246094f, 0.817f};
static float kurenaiAmbushB[]= {-1491.554321f, 8506.483398f, 1.248f};

struct npc_kurenai_captiveAI : public npc_escortAI
{
    npc_kurenai_captiveAI(Creature *c) : npc_escortAI(c), summons(me) {}
    
    bool complete;
    
    uint32 ChainLightningTimer;
    uint32 HealTimer;
    uint32 FrostShockTimer;
    
    SummonList summons;
    
    void Reset()
    override {
        ChainLightningTimer = 1000;
        HealTimer = 0;
        FrostShockTimer = 6000;
    }

    void EnterCombat(Unit* /*who*/)
    override {
        DoCast(me, SPELL_KUR_EARTHBIND_TOTEM, false);
    }

    void JustDied(Unit* /*killer*/)
    override {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
            return;

        if (Player* player = GetPlayerForEscort())
        {
            if (player->GetQuestStatus(QUEST_TOTEM_KARDASH_A) != QUEST_STATUS_COMPLETE)
                player->FailQuest(QUEST_TOTEM_KARDASH_A);
        }
    }

    void WaypointReached(uint32 PointId)
    override {
        switch(PointId)
        {
            case 3:
            {
                DoScriptText(SAY_KUR_MORE, me);

                if (Creature* temp = me->SummonCreature(NPC_KUR_MURK_PUTRIFIER, kurenaiAmbushB[0], kurenaiAmbushB[1], kurenaiAmbushB[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000))
                    DoScriptText(SAY_KUR_MORE_TWO, me);

                me->SummonCreature(NPC_KUR_MURK_PUTRIFIER, kurenaiAmbushB[0]-2.5f, kurenaiAmbushB[1]-2.5f, kurenaiAmbushB[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                me->SummonCreature(NPC_KUR_MURK_SCAVENGER, kurenaiAmbushB[0]+2.5f, kurenaiAmbushB[1]+2.5f, kurenaiAmbushB[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                me->SummonCreature(NPC_KUR_MURK_SCAVENGER, kurenaiAmbushB[0]+2.5f, kurenaiAmbushB[1]-2.5f, kurenaiAmbushB[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                break;
            }
            case 7:
            {
                DoScriptText(SAY_KUR_COMPLETE, me);

                if (Player* player = GetPlayerForEscort())
                    player->GroupEventHappens(QUEST_TOTEM_KARDASH_A, me);

                SetRun();
                break;
            }
        }
    }

    void JustSummoned(Creature* summoned)
    override {
        if (summoned->GetEntry() == NPC_KUR_MURK_BRUTE)
            DoScriptText(SAY_KUR_NO_ESCAPE, me);

        // This function is for when we summoned enemies to fight - so that does NOT mean we should make our totem count in this!
        if (summoned->IsTotem()) {
            summoned->SetFaction(me->GetFaction());
            return;
        }

        summoned->RemoveUnitMovementFlag(MOVEFLAG_WALK);
        summoned->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
        summoned->AI()->AttackStart(me);
    }

    void SpellHitTarget(Unit* /*target*/, const SpellInfo* spell)
    override {
        if (spell->Id == SPELL_KUR_CHAIN_LIGHTNING)
        {
            if (rand()%30)
                return;

            DoScriptText(SAY_KUR_LIGHTNING, me);
        }

        if (spell->Id == SPELL_KUR_FROST_SHOCK)
        {
            if (rand()%30)
                return;

            DoScriptText(SAY_KUR_SHOCK, me);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        npc_escortAI::UpdateAI(diff);

        if (!UpdateVictim())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (ChainLightningTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_KUR_CHAIN_LIGHTNING);
            ChainLightningTimer = urand(7000,14000);
        } else ChainLightningTimer -= diff;

        if (me->IsBelowHPPercent(30))
        {
            if (HealTimer <= diff)
            {
                DoCast(me, SPELL_KUR_HEALING_WAVE);
                HealTimer = 5000;
            } else HealTimer -= diff;
        }

        if (FrostShockTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_KUR_FROST_SHOCK);
            FrostShockTimer = urand(7500,15000);
        } else FrostShockTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_kurenai_captive(Creature* creature)
{
    return new npc_kurenai_captiveAI(creature);
}

bool QuestAccept_npc_kurenai_captive(Player* player, Creature* creature, const Quest* quest)
{
    if (quest->GetQuestId() == QUEST_TOTEM_KARDASH_A) {
        creature->SetStandState(UNIT_STAND_STATE_STAND);
        ((npc_escortAI*)(creature->AI()))->Start(true, true, false, player->GetGUID(), creature->GetEntry());
        DoScriptText(SAY_KUR_START, creature);
        
        creature->SummonCreature(NPC_KUR_MURK_RAIDER, kurenaiAmbushA[0]+2.5f, kurenaiAmbushA[1]-2.5f, kurenaiAmbushA[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
        creature->SummonCreature(NPC_KUR_MURK_BRUTE, kurenaiAmbushA[0]-2.5f, kurenaiAmbushA[1]+2.5f, kurenaiAmbushA[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
        creature->SummonCreature(NPC_KUR_MURK_SCAVENGER, kurenaiAmbushA[0], kurenaiAmbushA[1], kurenaiAmbushA[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
    }

    return true;
}

/*######
## AddSC
######*/

void AddSC_nagrand()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name="mob_shattered_rumbler";
    newscript->GetAI = &GetAI_mob_shattered_rumbler;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="mob_lump";
    newscript->GetAI = &GetAI_mob_lump;
    newscript->OnGossipHello =  &GossipHello_mob_lump;
    newscript->OnGossipSelect = &GossipSelect_mob_lump;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="mob_sunspring_villager";
    newscript->GetAI = &GetAI_mob_sunspring_villager;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_altruis_the_sufferer";
    newscript->OnGossipHello =  &GossipHello_npc_altruis_the_sufferer;
    newscript->OnGossipSelect = &GossipSelect_npc_altruis_the_sufferer;
    newscript->OnQuestAccept =  &QuestAccept_npc_altruis_the_sufferer;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_greatmother_geyah";
    newscript->OnGossipHello =  &GossipHello_npc_greatmother_geyah;
    newscript->OnGossipSelect = &GossipSelect_npc_greatmother_geyah;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_lantresor_of_the_blade";
    newscript->OnGossipHello =  &GossipHello_npc_lantresor_of_the_blade;
    newscript->OnGossipSelect = &GossipSelect_npc_lantresor_of_the_blade;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_creditmarker_visit_with_ancestors";
    newscript->GetAI = &GetAI_npc_creditmarker_visit_with_ancestors;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="mob_sparrowhawk";
    newscript->GetAI = &GetAI_mob_sparrowhawk;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_maghar_captive";
    newscript->GetAI = &GetAI_npc_maghar_captive;
    newscript->OnQuestAccept = &QuestAccept_npc_maghar_captive;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name="npc_sharvak";
    newscript->GetAI = &GetAI_npc_sharvakAI;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name="npc_jheel";
    newscript->GetAI = &GetAI_npc_jheelAI;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name="npc_rethhedron";
    newscript->GetAI = &GetAI_npc_rethhedronAI;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_kurenai_captive";
    newscript->GetAI = &GetAI_npc_kurenai_captive;
    newscript->OnQuestAccept = &QuestAccept_npc_kurenai_captive;
    sScriptMgr->RegisterOLDScript(newscript);
}

