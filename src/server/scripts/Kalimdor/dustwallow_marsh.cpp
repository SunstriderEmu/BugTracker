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


class mobs_risen_husk_spirit : public CreatureScript
{
public:
    mobs_risen_husk_spirit() : CreatureScript("mobs_risen_husk_spirit")
    { }

    class mobs_risen_husk_spiritAI : public ScriptedAI
    {
        public:
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
                    me->CastSpell(pDoneBy, SPELL_SUMMON_RESTLESS_APPARITION, TRIGGERED_NONE);
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mobs_risen_husk_spiritAI(creature);
    }
};


/*######
## npc_restless_apparition
######*/

class npc_restless_apparition : public CreatureScript
{
public:
    npc_restless_apparition() : CreatureScript("npc_restless_apparition")
    { }

    class npc_restless_apparitionAI : public ScriptedAI
    {
    public:
        npc_restless_apparitionAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            SEND_DEFAULT_GOSSIP_MENU(pPlayer, me);

            pPlayer->TalkedToCreature(me->GetEntry(), me->GetGUID());
            me->SetInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_restless_apparitionAI(creature);
    }
};


/*######
## npc_deserter_agitator
######*/


class npc_deserter_agitator : public CreatureScript
{
public:
    npc_deserter_agitator() : CreatureScript("npc_deserter_agitator")
    { }

    class npc_deserter_agitatorAI : public ScriptedAI
    {
        public:
        npc_deserter_agitatorAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
            me->SetFaction(894);
        }
    
        void EnterCombat(Unit* pWho) override {}

        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(11126) == QUEST_STATUS_INCOMPLETE)
            {
                me->SetFaction(1883);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                pPlayer->TalkedToCreature(me->GetEntry(), me->GetGUID());
            }
            else
                SEND_DEFAULT_GOSSIP_MENU(pPlayer, me);

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_deserter_agitatorAI(creature);
    }
};



/*######
## npc_lady_jaina_proudmoore
######*/

#define GOSSIP_ITEM_JAINA "I know this is rather silly but i have a young ward who is a bit shy and would like your autograph."

class npc_lady_jaina_proudmoore : public CreatureScript
{
public:
    npc_lady_jaina_proudmoore() : CreatureScript("npc_lady_jaina_proudmoore")
    { }

    class npc_lady_jaina_proudmooreAI : public ScriptedAI
    {
    public:
        npc_lady_jaina_proudmooreAI(Creature* creature) : ScriptedAI(creature)
        {}

        EventMap events;

        enum Spells
        {
            SPELL_FIREBALL = 20692,
            SPELL_FIREBLAST = 20679,
            SPELL_BLIZZARD = 20680,
            SPELL_TELEPORT = 20682,
            SPELL_WATER_ELEMENTALS = 20681,
        };
        enum events
        {
            EV_FIREBALL = 1,
            EV_FIREBLAST,
            EV_BLIZZARD ,
            EV_TELEPORT,
            EV_WATER_ELEMENTALS,
        };

        void EnterCombat(Unit* victim) override
        {
            me->PlayDirectSound(5882);
        }

        void Reset() override
        {
            events.RescheduleEvent(EV_FIREBALL, 0);
            events.RescheduleEvent(EV_FIREBLAST, urand(5000, 9000));
            events.RescheduleEvent(EV_BLIZZARD, urand(8000, 12000));
            events.RescheduleEvent(EV_TELEPORT, 10000);
            events.RescheduleEvent(EV_WATER_ELEMENTALS, urand(4000, 5000));
        }

        void UpdateAI(const uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            switch (events.GetEvent())
            {
            case 0:
                break;
            case EV_FIREBALL:
                if (me->CastSpell(me->GetVictim(), SPELL_FIREBALL) == SPELL_CAST_OK)
                    events.RescheduleEvent(EV_FIREBALL, urand(2000, 3500));
                break;
            case EV_FIREBLAST:
                if (me->CastSpell(me->GetVictim(), SPELL_FIREBLAST) == SPELL_CAST_OK)
                    events.RescheduleEvent(EV_FIREBLAST, urand(15000, 17000));
                break;
            case EV_BLIZZARD:
                if (me->CastSpell(me->GetVictim(), SPELL_BLIZZARD) == SPELL_CAST_OK)
                    events.RescheduleEvent(EV_BLIZZARD, urand(25000, 28000));
                break;
            case EV_TELEPORT:
            {
                if (me->GetHealthPct() < 50.0f)
                {
                    me->CastSpell(me->GetVictim(), EV_TELEPORT);
                    events.CancelEvent(EV_TELEPORT);
                }
                else 
                {
                    events.RescheduleEvent(EV_TELEPORT, 10000);
                }
                break;
            }
            case EV_WATER_ELEMENTALS:
                if (me->CastSpell(me, SPELL_WATER_ELEMENTALS, TRIGGERED_FULL_MASK) == SPELL_CAST_OK)
                    events.RescheduleEvent(EV_WATER_ELEMENTALS, urand(45000, 55000));
                break;
            }
            DoMeleeAttackIfReady();
        }

        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if(player->GetQuestStatus(558) == QUEST_STATUS_INCOMPLETE )
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_JAINA, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INFO );

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if (action == GOSSIP_SENDER_INFO)
            {
                player->SEND_GOSSIP_MENU_TEXTID(7012, me->GetGUID());
                player->CastSpell(player, 23122, TRIGGERED_NONE);
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lady_jaina_proudmooreAI(creature);
    }
};



/*######
## npc_nat_pagle
######*/

class npc_nat_pagle : public CreatureScript
{
public:
    npc_nat_pagle() : CreatureScript("npc_nat_pagle")
    { }

    class npc_nat_pagleAI : public ScriptedAI
    {
    public:
        npc_nat_pagleAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (me->IsVendor() && pPlayer->GetQuestRewardStatus(8227))
            {
                pPlayer->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(7640, me->GetGUID());
            }
            else
                pPlayer->SEND_GOSSIP_MENU_TEXTID(7638, me->GetGUID());

            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if (action == GOSSIP_ACTION_TRADE)
                player->SEND_VENDORLIST(me->GetGUID());

            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_nat_pagleAI(creature);
    }
};



/*######
## npc_overlord_mokmorokk
######*/

enum eOverlordMokmorokk
{
QUEST_CHALLENGE_OVERLORD    = 1173,

FACTION_NEUTRAL             = 120,
FACTION_UNFRIENDLY          = 14    //guessed
};


class npc_overlord_mokmorokk : public CreatureScript
{
public:
    npc_overlord_mokmorokk() : CreatureScript("npc_overlord_mokmorokk")
    { }

    class npc_overlord_mokmorokkAI : public ScriptedAI
    {
        public:
        npc_overlord_mokmorokkAI(Creature *c) : ScriptedAI(c) {}
        
        Player* player;
        
        void Reset()
        override {
            me->SetFaction(FACTION_NEUTRAL);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetHealth(me->GetMaxHealth());
            me->CombatStop();
            me->GetThreatManager().ClearAllThreat();
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

        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());
            
            if (pPlayer->GetQuestStatus(QUEST_CHALLENGE_OVERLORD) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Go away!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                
            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            
            return true;
        }


        virtual bool GossipSelect(Player* _player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = _player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                me->Say("We'll see about this!", LANG_UNIVERSAL, nullptr);
                me->SetFaction(FACTION_UNFRIENDLY);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                me->AI()->AttackStart(_player);
                player->CLOSE_GOSSIP_MENU();

            }
            
            return true;
        }


        virtual void QuestAccept(Player* _player, Quest const* quest) override
        {
            if (quest->GetQuestId() == 1173) {
                me->SetFaction(FACTION_UNFRIENDLY);
                me->AI()->AttackStart(_player);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_overlord_mokmorokkAI(creature);
    }
};





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

class npc_private_hendel : public CreatureScript
{
public:
    npc_private_hendel() : CreatureScript("npc_private_hendel")
    { }

    class npc_private_hendelAI : public ScriptedAI
    {
        public:
        npc_private_hendelAI(Creature* pCreature) : ScriptedAI(pCreature) { }
    
        void Reset()
        override {
            me->RestoreFaction();
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

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if (pQuest->GetQuestId() == QUEST_MISSING_DIPLO_PT16)
                me->SetFaction(FACTION_HOSTILE);
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_private_hendelAI(creature);
    }
};



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


class npc_stinky : public CreatureScript
{
public:
    npc_stinky() : CreatureScript("npc_stinky")
    { }

    class npc_stinkyAI : public EscortAI
    {
        public:
        npc_stinkyAI(Creature* pCreature) : EscortAI(pCreature)
        {
            completed = false;
        }
    
        bool completed;
    
        void WaypointReached(uint32 i, uint32 pathID)
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
            EscortAI::UpdateAI(uiDiff);
    
            if (!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_STINKYS_ESCAPE_H || QUEST_STINKYS_ESCAPE_A) {
                me->SetFaction(250);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                DoScriptText(SAY_QUEST_ACCEPTED, me);
                ((EscortAI*)(me->AI()))->Start(false, false, pPlayer->GetGUID(), quest);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stinkyAI(creature);
    }
};



/*######
## npc_cassa_crimsonwing
######*/

class npc_cassa_crimsonwing : public CreatureScript
{
public:
    npc_cassa_crimsonwing() : CreatureScript("npc_cassa_crimsonwing")
    { }

    class npc_cassa_crimsonwingAI : public ScriptedAI
    {
    public:
        npc_cassa_crimsonwingAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            if (player->GetQuestStatus(11142) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je dois survoler l'île d'Alcaz.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                
            SEND_PREPARED_GOSSIP_MENU(player, me);
                
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            player->CLOSE_GOSSIP_MENU();

            if (action == GOSSIP_ACTION_INFO_DEF) {
                player->CastSpell(player, 42316, TRIGGERED_FULL_MASK);
                std::vector<uint32> nodes;

                nodes.resize(2);
                nodes[0] = 180;                                     //from
                nodes[1] = 181;                                     //end at
                player->ActivateTaxiPathTo(nodes);
            }
                
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_cassa_crimsonwingAI(creature);
    }
};



/*######
## npc_ogron
######*/

//TODO : texts are mostly made up

enum eOgron
{
    QUEST_QUESTIONING_REETHE                     = 1273
};


class npc_ogron : public CreatureScript
{
public:
    npc_ogron() : CreatureScript("npc_ogron")
    { }

    class npc_ogronAI : public EscortAI
    {
        public:
        npc_ogronAI(Creature* pCreature) : EscortAI(pCreature)
        {
            completed = false;
        }
    
        bool completed;
        uint32 step;
        uint32 timer;
    
        void WaypointReached(uint32 i, uint32 pathID)
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
            EscortAI::UpdateAI(uiDiff);
            
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
                                caldspawn->SetFaction(FACTION_FRIENDLY);
                            }
                            reethe->Say("What was that? Did you hear something?", LANG_UNIVERSAL);
    //                        reethe->MonsterSay("Qu'est-ce que c'était ? Avez-vous entendu quelque chose ?", LANG_UNIVERSAL, 0);
                            ++step;
                            timer = 2000;
                            break;
                        case 8:
                            if (Creature* add = me->SummonCreature(5044, -3373.989014, -3207.442871, 35.073441, 5.826434, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                                me->SetFaction(FACTION_FRIENDLY);
                            if (Creature* add = me->SummonCreature(5044, -3374.850342, -3209.195557, 34.980534, 5.826434, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                                me->SetFaction(FACTION_FRIENDLY);
                            if (Creature* add = me->SummonCreature(5045, -3375.389404, -3211.398682, 34.845543, 6.043204, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                                me->SetFaction(FACTION_FRIENDLY);
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
                                hallan->CastSpell(reethe, 7105 /* Fake Shot*/, TRIGGERED_FULL_MASK);
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
                                (*it)->SetFaction(FACTION_MONSTER);
                                (*it)->AI()->AttackStart(reethe);
                            }
                            caldwell->SetFaction(FACTION_MONSTER);
                            caldwell->AI()->AttackStart(reethe);
                            if (Creature* hallan = me->FindNearestCreature(5045, 20.0f, true)) {
                                hallan->SetFaction(FACTION_MONSTER);
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

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_QUESTIONING_REETHE) {
                me->SetFaction(pPlayer->GetFaction());
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->Say("I saw a fire on the island there, as well as a human. Let's go check it.", LANG_UNIVERSAL);
                //me->MonsterSay("J'ai remarqué du feu sur cette île, là-bas. Et un humain, aussi. Allons vérifier.", LANG_UNIVERSAL, 0);
                ((EscortAI*)(me->AI()))->Start(true, false, pPlayer->GetGUID(), quest);
                ((EscortAI*)(me->AI()))->SetDespawnAtEnd(false);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ogronAI(creature);
    }
};



/*######
## npc_captured_totem
######*/


class npc_captured_totem : public CreatureScript
{
public:
    npc_captured_totem() : CreatureScript("npc_captured_totem")
    { }

    class npc_captured_totemAI : public ScriptedAI
    {
        public:
        npc_captured_totemAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFaction(FACTION_FRIENDLY);
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_captured_totemAI(creature);
    }
};


/*######
## npc_searingwhelp
######*/

#define TIMER_FIREBALL 6000
#define SPELL_FIREBALL 11021


class npc_searingwhelp : public CreatureScript
{
public:
    npc_searingwhelp() : CreatureScript("npc_searingwhelp")
    { }

    class SearingWhelpAI : public ScriptedAI
    {
        public:
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new SearingWhelpAI(creature);
    }
};


/*######
## AddSC
######*/

void AddSC_dustwallow_marsh()
{

    new mobs_risen_husk_spirit();

    new npc_restless_apparition();

    new npc_deserter_agitator();

    new npc_lady_jaina_proudmoore();

    new npc_nat_pagle();
    
    new npc_overlord_mokmorokk();
    
    new npc_private_hendel();
    
    new npc_stinky();
    
    new npc_cassa_crimsonwing();
    
    new npc_ogron();
    
    new npc_captured_totem();

    new npc_searingwhelp();
}
