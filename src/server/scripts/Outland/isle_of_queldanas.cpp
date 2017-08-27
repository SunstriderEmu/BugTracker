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

class npc_ayren_cloudbreaker : public CreatureScript
{
public:
    npc_ayren_cloudbreaker() : CreatureScript("npc_ayren_cloudbreaker")
    { }

   class npc_ayren_cloudbreakerAI : public ScriptedAI
   {
   public:
        npc_ayren_cloudbreakerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if( pPlayer->GetQuestStatus(11532) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(11533) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FLY1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            if( pPlayer->GetQuestStatus(11542) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(11543) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FLY2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
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

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ayren_cloudbreakerAI(creature);
    }
};



/*######
## npc_converted_sentry
######*/

enum eConvertedSentry
{
    SAY_CONVERTED_1         = -1000284,
    SAY_CONVERTED_2         = -1000284, //TODO: type here, what is the right text?

    SPELL_CONVERT_CREDIT    = 45009
};


class npc_converted_sentry : public CreatureScript
{
public:
    npc_converted_sentry() : CreatureScript("npc_converted_sentry")
    { }

    class npc_converted_sentryAI : public ScriptedAI
    {
        public:
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_converted_sentryAI(creature);
    }
};


/*######
## npc_unrestrained_dragonhawk
######*/

#define GOSSIP_UD "<Ride the dragonhawk to Sun's Reach>"

class npc_unrestrained_dragonhawk : public CreatureScript
{
public:
    npc_unrestrained_dragonhawk() : CreatureScript("npc_unrestrained_dragonhawk")
    { }

   class npc_unrestrained_dragonhawkAI : public ScriptedAI
   {
   public:
        npc_unrestrained_dragonhawkAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if( pPlayer->GetQuestStatus(11542) == QUEST_STATUS_COMPLETE || pPlayer->GetQuestStatus(11543) == QUEST_STATUS_COMPLETE )
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->CastSpell(pPlayer, 45353, true);               //TaxiPath 788
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_unrestrained_dragonhawkAI(creature);
    }
};



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


class npc_greengill_slave : public CreatureScript
{
public:
    npc_greengill_slave() : CreatureScript("npc_greengill_slave")
    { }

    class npc_greengill_slaveAI : public ScriptedAI
    {
        public:
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_greengill_slaveAI(creature);
    }
};


void AddSC_isle_of_queldanas()
{

    new npc_ayren_cloudbreaker();

    new npc_converted_sentry();

    new npc_unrestrained_dragonhawk();

    new npc_greengill_slave();
}

