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
SDName: Isle_of_Queldanas
SD%Complete: 100
SDComment: Quest support: 11524, 11525, 11532, 11533, 11542, 11543, 11541
SDCategory: Isle Of Quel'Danas
EndScriptData */

/* ContentData
npc_ayren_cloudbreaker
npc_converted_sentry
npc_unrestrained_dragonhawk
npc_greengill_slave
EndContentData */

#include "Pet.h"


/*######
## npc_ayren_cloudbreaker
######*/

#define GOSSIP_FLY1 "Speaking of action, I've been ordered to undertake an air strike."
#define GOSSIP_FLY2 "I need to intercept the Dawnblade reinforcements."

bool GossipHello_npc_ayren_cloudbreaker(Player* pPlayer, Creature* pCreature)
{
    if( pPlayer->GetQuestStatus(11532) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(11533) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FLY1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    if( pPlayer->GetQuestStatus(11542) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(11543) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FLY2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
    return true;
}

bool GossipSelect_npc_ayren_cloudbreaker(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action )
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, 45071, true);               //TaxiPath 779
    }
    if (action == GOSSIP_ACTION_INFO_DEF+2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, 45113, true);               //TaxiPath 784
    }
    return true;
}

/*######
## npc_converted_sentry
######*/

enum eConvertedSentry
{
    SAY_CONVERTED_1         = -1000284,
    SAY_CONVERTED_2         = -1000284, //TODO: type here, what is the right text?

    SPELL_CONVERT_CREDIT    = 45009
};

struct npc_converted_sentryAI : public ScriptedAI
{
    npc_converted_sentryAI(Creature *c) : ScriptedAI(c)
    {
        if (Creature* sentry = me->FindNearestCreature(24972, 10.0f, false))
        {
            sentry->DespawnOrUnsummon();
        }
    }

    bool Credit;
    uint32 Timer;

    void Reset()
    override {
        Credit = false;
        Timer = 2500;
    }

    void MoveInLineOfSight(Unit* pWho)
    override {
        return;
    }
    
    void EnterCombat(Unit* pWho) override {}

    void UpdateAI(const uint32 diff)
    override {
        if( !Credit )
        {
            if( Timer <= diff )
            {
                DoScriptText( urand(0,1) ? SAY_CONVERTED_1 : SAY_CONVERTED_2, me);
                DoCast(me, SPELL_CONVERT_CREDIT);
                if(me->IsPet())
                    ((Pet*)me)->SetDuration(7500);
                Credit = true;
            }else Timer -= diff;
        }
    }
};

CreatureAI* GetAI_npc_converted_sentry(Creature* pCreature)
{
    return new npc_converted_sentryAI(pCreature);
}

/*######
## npc_unrestrained_dragonhawk
######*/

#define GOSSIP_UD "<Ride the dragonhawk to Sun's Reach>"

bool GossipHello_npc_unrestrained_dragonhawk(Player* pPlayer, Creature* pCreature)
{
    if( pPlayer->GetQuestStatus(11542) == QUEST_STATUS_COMPLETE || pPlayer->GetQuestStatus(11543) == QUEST_STATUS_COMPLETE )
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
    return true;
}

bool GossipSelect_npc_unrestrained_dragonhawk(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, 45353, true);               //TaxiPath 788
    }
    return true;
}

/*######
## npc_greengill_slave
######*/

enum eGreengill
{
ENRAGE  = 45111,
ORB     = 45109,
QUESTG  = 11541,
DM      = 25060
};

struct npc_greengill_slaveAI : public ScriptedAI
{
    npc_greengill_slaveAI(Creature* c) : ScriptedAI(c) {}

    uint64 PlayerGUID;

    void EnterCombat(Unit* pWho) override {}

    void Reset()
    override {
        PlayerGUID = 0;
    }

    void SpellHit(Unit* pCaster, const SpellInfo* spell)
    override {
        if(!pCaster)
            return;

        if(pCaster->GetTypeId() == TYPEID_PLAYER && spell->Id == ORB && !me->HasAuraEffect(ENRAGE))
        {
            PlayerGUID = pCaster->GetGUID();
            if(PlayerGUID)
            {
                Player* plr = ObjectAccessor::GetPlayer(*me, PlayerGUID);
                if(plr && plr->GetQuestStatus(QUESTG) == QUEST_STATUS_INCOMPLETE)
                    plr->KilledMonsterCredit(25086, me->GetGUID());
            }
            DoCast(me, ENRAGE);
            Unit* Myrmidon = me->FindNearestCreature(DM, 70);
            if(Myrmidon)
            {
                me->AddThreat(Myrmidon, 100000.0f);
                AttackStart(Myrmidon);
            }
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_greengill_slaveAI(Creature* pCreature)
{
    return new npc_greengill_slaveAI(pCreature);
}

void AddSC_isle_of_queldanas()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name="npc_ayren_cloudbreaker";
    newscript->OnGossipHello = &GossipHello_npc_ayren_cloudbreaker;
    newscript->OnGossipSelect = &GossipSelect_npc_ayren_cloudbreaker;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_converted_sentry";
    newscript->GetAI = &GetAI_npc_converted_sentry;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_unrestrained_dragonhawk";
    newscript->OnGossipHello = &GossipHello_npc_unrestrained_dragonhawk;
    newscript->OnGossipSelect = &GossipSelect_npc_unrestrained_dragonhawk;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_greengill_slave";
    newscript->GetAI = &GetAI_npc_greengill_slaveAI;
    sScriptMgr->RegisterOLDScript(newscript);
}

