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
SDName: Stormwind_City
SD%Complete: 100
SDComment: Quest support: 1640, 1447, 4185, 8356, 11223. Receive emote General Marcus
SDCategory: Stormwind City
EndScriptData */

/* ContentData
npc_archmage_malin
npc_bartleby
npc_dashel_stonefist
npc_general_marcus_jonathan
npc_lady_katrana_prestor
npc_innkeeper_allison
npc_monty
EndContentData */



/*######
## npc_archmage_malin
######*/

//TODO translate
#define GOSSIP_ITEM_MALIN "Pouvez-vous m'envoyer à Theramore ? J'ai un message urgent pour Jaina, de la part de Bolvar."

class npc_archmage_malin : public CreatureScript
{
public:
    npc_archmage_malin() : CreatureScript("npc_archmage_malin")
    { }

    class npc_archmage_malinAI : public ScriptedAI
    {
    public:
        npc_archmage_malinAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if(me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if(player->GetQuestStatus(11223) == QUEST_STATUS_COMPLETE && !player->GetQuestRewardStatus(11223))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MALIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if(action == GOSSIP_ACTION_INFO_DEF)
            {
                player->CLOSE_GOSSIP_MENU();
                me->CastSpell(player, 42711, TRIGGERED_FULL_MASK);
            }

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_archmage_malinAI(creature);
    }
};



/*######
## npc_bartleby
######*/


class npc_bartleby : public CreatureScript
{
public:
    npc_bartleby() : CreatureScript("npc_bartleby")
    { }

    class npc_bartlebyAI : public ScriptedAI
    {
        public:
        npc_bartlebyAI(Creature *c) : ScriptedAI(c) {}
    
        uint64 PlayerGUID;
    
        void Reset()
        override {
            me->SetFaction(11);
            me->SetEmoteState(EMOTE_ONESHOT_EAT);
    
            PlayerGUID = 0;
        }
    
        void JustDied(Unit *who)
        override {
            me->SetFaction(11);
        }
    
        void DamageTaken(Unit *done_by, uint32 & damage)
        override {
            if(damage > me->GetHealth() || ((me->GetHealth() - damage)*100 / me->GetMaxHealth() < 15))
            {
                //Take 0 damage
                damage = 0;
    
                if (done_by->GetTypeId() == TYPEID_PLAYER && done_by->GetGUID() == PlayerGUID)
                {
                    (done_by->ToPlayer())->AttackStop();
                    (done_by->ToPlayer())->AreaExploredOrEventHappens(1640);
                }
                me->CombatStop();
                EnterEvadeMode();
            }
        }
    
        void EnterCombat(Unit *who) override {}

        virtual void QuestAccept(Player* player, Quest const* _Quest) override
        {
            if(_Quest->GetQuestId() == 1640)
            {
                me->SetFaction(168);
                ((npc_bartleby::npc_bartlebyAI*)me->AI())->PlayerGUID = player->GetGUID();
                ((npc_bartleby::npc_bartlebyAI*)me->AI())->AttackStart(player);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bartlebyAI(creature);
    }
};



/*######
## npc_dashel_stonefist
######*/


class npc_dashel_stonefist : public CreatureScript
{
public:
    npc_dashel_stonefist() : CreatureScript("npc_dashel_stonefist")
    { }

    class npc_dashel_stonefistAI : public ScriptedAI
    {
        public:
        npc_dashel_stonefistAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
            me->SetFaction(11);
            me->SetEmoteState(EMOTE_ONESHOT_EAT);
        }
    
        void DamageTaken(Unit *done_by, uint32 & damage)
        override {
            if((damage > me->GetHealth()) || (me->GetHealth() - damage)*100 / me->GetMaxHealth() < 15)
            {
                //Take 0 damage
                damage = 0;
    
                if (done_by->GetTypeId() == TYPEID_PLAYER)
                {
                    (done_by->ToPlayer())->AttackStop();
                    (done_by->ToPlayer())->AreaExploredOrEventHappens(1447);
                }
                //me->CombatStop();
                EnterEvadeMode();
            }
        }
    
        void EnterCombat(Unit *who) override {}

        virtual void QuestAccept(Player* player, Quest const* _Quest) override
        {
            if(_Quest->GetQuestId() == 1447)
            {
                me->SetFaction(168);
                ((npc_dashel_stonefist::npc_dashel_stonefistAI*)me->AI())->AttackStart(player);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dashel_stonefistAI(creature);
    }
};



/*######
## npc_general_marcus_jonathan
######*/

class npc_general_marcus_jonathan : public CreatureScript
{
public:
    npc_general_marcus_jonathan() : CreatureScript("npc_general_marcus_jonathan") {}

    class npc_general_marcus_jonathanAI : public ScriptedAI
    {
    public:
        npc_general_marcus_jonathanAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void ReceiveEmote(Player* player, uint32 emote) override
        {
            if (player->GetTeam() == ALLIANCE)
            {
                if (emote == TEXTEMOTE_SALUTE)
                {
                    me->SetOrientation(me->GetAngle(player));
                    me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                }
                if (emote == TEXTEMOTE_WAVE)
                {
                    //TODO: move to db to get translations
                    me->Say("Greetings citizen.", LANG_COMMON, nullptr);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
        override {
        return new npc_general_marcus_jonathanAI(creature);
    }
};

/*######
## npc_lady_katrana_prestor
######*/

//TODO translate
#define GOSSIP_ITEM_KAT_1 "Excusez mon intrusion, Dame Prestor, mais le Seigneur Bolvar a suggéré que je vous demande conseil."
#define GOSSIP_ITEM_KAT_2 "Mes excuses, Dame Prestor."
#define GOSSIP_ITEM_KAT_3 "Je vous demande pardon, Dame Prestor. Ce n'était pas mon intention."
#define GOSSIP_ITEM_KAT_4 "Merci pour votre temps, Dame Prestor."

class npc_lady_katrana_prestor : public CreatureScript
{
public:
    npc_lady_katrana_prestor() : CreatureScript("npc_lady_katrana_prestor")
    { }

    class npc_lady_katrana_prestorAI : public ScriptedAI
    {
    public:
        npc_lady_katrana_prestorAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if (player->GetQuestStatus(4185) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            player->SEND_GOSSIP_MENU_TEXTID(2693, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU_TEXTID(2694, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(2695, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU_TEXTID(2696, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    player->CLOSE_GOSSIP_MENU();
                    player->AreaExploredOrEventHappens(4185);
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lady_katrana_prestorAI(creature);
    }
};



/*######
## npc_innkeeper_allison
######*/

class npc_innkeeper_allison : public CreatureScript
{
public:
    npc_innkeeper_allison() : CreatureScript("npc_innkeeper_allison") {}

    class npc_innkeeper_allisonAI : public ScriptedAI
    {
    public:
        const uint32 QUEST_FLEXING_NOUGAT = 8356;

        npc_innkeeper_allisonAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void ReceiveEmote(Player* player, uint32 emote) override
        {
            if (emote == TEXTEMOTE_FLEX)
            {
                if (player->GetQuestStatus(QUEST_FLEXING_NOUGAT) == QUEST_STATUS_INCOMPLETE)
                    player->AreaExploredOrEventHappens(QUEST_FLEXING_NOUGAT);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
        override {
        return new npc_innkeeper_allisonAI(creature);
    }
};

/*######
## npc_monty
######*/

class npc_monty : public CreatureScript
{
public:
    npc_monty() : CreatureScript("npc_monty")
    { }

    class npc_montyAI : public ScriptedAI
    {
    public:
        npc_montyAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual void QuestReward(Player* player, Quest const* quest, uint32 option) override
        {
            if (quest->GetQuestId() == 6661) {
                DoScriptText(-1000765, me, nullptr);
                Creature* rat = me->FindNearestCreature(13017, 15.0f, true);
                while (rat) {
                    rat->DisappearAndDie();
                    rat->Respawn();
                    rat = me->FindNearestCreature(13017, 15.0f, true);
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_montyAI(creature);
    }
};


/*######
## AddSC
######*/

void AddSC_stormwind_city()
{

    new npc_archmage_malin();

    new npc_bartleby();

    new npc_dashel_stonefist();

    new npc_general_marcus_jonathan();

    new npc_lady_katrana_prestor();
    
    new npc_innkeeper_allison();
    
    new npc_monty();
}

