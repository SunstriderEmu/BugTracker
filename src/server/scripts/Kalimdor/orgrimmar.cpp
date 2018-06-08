
/* ScriptData
SDName: Orgrimmar
SD%Complete: 100
SDComment: Quest support: 2460, 5727, 6566
SDCategory: Orgrimmar
EndScriptData */

/* ContentData
npc_neeru_fireblade     npc_text + gossip options text missing
npc_shenthul
npc_thrall_warchief
npc_eitrigg
EndContentData */



/*######
## npc_neeru_fireblade
######*/

#define QUEST_5727  5727

#define GOSSIP_HNF "You may speak frankly, Neeru..."
#define GOSSIP_SNF "[PH] ..."
class npc_neeru_fireblade : public CreatureScript
{
public:
    npc_neeru_fireblade() : CreatureScript("npc_neeru_fireblade")
    { }

    class npc_neeru_firebladeAI : public ScriptedAI
    {
    public:
        npc_neeru_firebladeAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if (player->GetQuestStatus(QUEST_5727) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HNF, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            player->SEND_GOSSIP_MENU_TEXTID(4513, me->GetGUID());
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SNF, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU_TEXTID(4513, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->CLOSE_GOSSIP_MENU();
                    player->AreaExploredOrEventHappens(QUEST_5727);
                    break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_neeru_firebladeAI(creature);
    }
};



/*######
## npc_shenthul
######*/

#define QUEST_2460  2460

class npc_shenthul : public CreatureScript
{
public:
    npc_shenthul() : CreatureScript("npc_shenthul")
    { }

    class npc_shenthulAI : public ScriptedAI
    {
        public:
        npc_shenthulAI(Creature* c) : ScriptedAI(c) {}
    
        bool CanTalk;
        bool CanEmote;
        uint32 Salute_Timer;
        uint32 Reset_Timer;
        ObjectGuid playerGUID;
    
        void Reset()
        override {
            CanTalk = false;
            CanEmote = false;
            Salute_Timer = 6000;
            Reset_Timer = 0;
            playerGUID = ObjectGuid::Empty;
        }
    
        void JustEngagedWith(Unit* who) override { }
    
        void UpdateAI(const uint32 diff)
        override {
            if( CanEmote )
            {
                if( Reset_Timer < diff )
                {
                    if( Player* temp = ObjectAccessor::GetPlayer(*me, playerGUID) )
                        temp->FailQuest(QUEST_2460);
                    Reset();
                } else Reset_Timer -= diff;
            }
    
            if( CanTalk && !CanEmote )
            {
                if( Salute_Timer < diff )
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                    CanEmote = true;
                    Reset_Timer = 60000;
                } else Salute_Timer -= diff;
            }
    
            if (!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if( quest->GetQuestId() == QUEST_2460 )
            {
                ((npc_shenthul::npc_shenthulAI*)me->AI())->CanTalk = true;
                ((npc_shenthul::npc_shenthulAI*)me->AI())->playerGUID = player->GetGUID();
            }
        }


        virtual void ReceiveEmote(Player* player, uint32 emote) override
        {
            if( emote == TEXTEMOTE_SALUTE && player->GetQuestStatus(QUEST_2460) == QUEST_STATUS_INCOMPLETE )
                if( ((npc_shenthul::npc_shenthulAI*)me->AI())->CanEmote )
            {
                player->AreaExploredOrEventHappens(QUEST_2460);
                ((npc_shenthul::npc_shenthulAI*)me->AI())->Reset();
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_shenthulAI(creature);
    }
};




/*######
## npc_thrall_warchief
######*/

#define NPC_EITRIGG 3144
#define QUEST_6566              6566

#define SPELL_CHAIN_LIGHTNING   16033
#define SPELL_SHOCK             16034

#define GOSSIP_HTW "Please share your wisdom with me, Warchief."
#define GOSSIP_STW1 "What discoveries?"
#define GOSSIP_STW2 "Usurper?"
#define GOSSIP_STW3 "With all due respect, Warchief - why not allow them to be destroyed? Does this not strengthen our position?"
#define GOSSIP_STW4 "I... I did not think of it that way, Warchief."
#define GOSSIP_STW5 "I live only to serve, Warchief! My life is empty and meaningless without your guidance."
#define GOSSIP_STW6 "Of course, Warchief!"

//TODO: verify abilities/timers
class npc_thrall_warchief : public CreatureScript
{
public:
    npc_thrall_warchief() : CreatureScript("npc_thrall_warchief")
    { }

    enum ThrallTalk
    {
        TALK_MESSENGER_EVENT_1 = 0, // My people have survived in Outland...
        TALK_MESSENGER_EVENT_2, // Unnoticed for years...
        TALK_MESSENGER_EVENT_3, // ...uncorrupted!
        TALK_MESSENGER_EVENT_5, // I'll be fine, Eitrigg. We must begin preparations... I need to go to Outland at once!
        TALK_MESSENGER_EVENT_7, // You are right, Eitrigg. The timing is unfavorable. Make sure our best ambassadors are sent as envoys to Hellscream.
        TALK_MESSENGER_EVENT_9, // If he's anything like his father, allying with the Mag'har will mark the dawn of a new age for the Horde.
        //BROKERING_OF_PEACE_YELL,
    };

    enum EitriggTalk
    {
        TALK_MESSENGER_EVENT_4 = 0, // Thrall! My lord... are you all right?
        TALK_MESSENGER_EVENT_6, // With all due respect, Warchief. Our enemies would take advantage of your sudden absence if we don't prepare properly.
        TALK_MESSENGER_EVENT_8, // At once, sir! For the Horde!
    };

    enum ThrallMessage
    {
        MESSAGE_START_MESSENGER_EVENT,
    };

    class npc_thrall_warchiefAI : public ScriptedAI
    {
    public:
        npc_thrall_warchiefAI(Creature* creature) : ScriptedAI(creature)
        { }

        enum events
        {
            EV_MESSENGER = 1,
        };

        uint32 ChainLightning_Timer;
        uint32 Shock_Timer;
        uint32 messengerEventStep;
        EventMap events;
        ObjectGuid EitriggGUID;

        uint64 message(uint32 id, uint64 data) override
        {
            switch (id)
            {
            case MESSAGE_START_MESSENGER_EVENT:
                messengerEventStep = 0;
                if (Creature* c = me->FindNearestCreature(NPC_EITRIGG, 100.0f))
                    EitriggGUID = c->GetGUID();

                if(EitriggGUID)
                    events.RescheduleEvent(EV_MESSENGER, 1);
                break;
            }
            return 0;
        }

        void Reset()
            override {
            ChainLightning_Timer = 2000;
            Shock_Timer = 8000;
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            events.Reset();
            messengerEventStep = 0;
            me->SetSheath(SHEATH_STATE_MELEE);
            me->SetStandState(UNIT_STAND_STATE_SIT);
            EitriggGUID = ObjectGuid::Empty;
        }

        void UpdateAI(const uint32 diff)
            override 
        {
            if (UpdateVictim())
            {
                if (ChainLightning_Timer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_CHAIN_LIGHTNING);
                    ChainLightning_Timer = 9000;
                }
                else ChainLightning_Timer -= diff;

                if (Shock_Timer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_SHOCK);
                    Shock_Timer = 15000;
                }
                else Shock_Timer -= diff;

                DoMeleeAttackIfReady();
                return;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
                switch (eventId)
                {
                case 0:
                    break;
                case EV_MESSENGER:
                    Creature* eitrigg = me->GetMap()->GetCreature(EitriggGUID);
                    if (!eitrigg)
                    {
                        //reset
                        EnterEvadeMode();
                        return;
                    }

                    switch(messengerEventStep)
                    {
                    case 0:
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        me->SetSheath(SHEATH_STATE_UNARMED);
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        events.RescheduleEvent(EV_MESSENGER, 4000);
                        break;
                    case 1:
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovePoint(0, 1924.233643, -4136.424805, 40.360466, true, 4.724128);
                        events.RescheduleEvent(EV_MESSENGER, 4000);
                        break;
                    case 2:
                        Talk(TALK_MESSENGER_EVENT_1);
                        events.RescheduleEvent(EV_MESSENGER, 4000);
                        break;
                    case 3:
                        me->SetStandState(UNIT_STAND_STATE_KNEEL);
                        events.RescheduleEvent(EV_MESSENGER, 2000);
                        break;
                    case 4:
                        Talk(TALK_MESSENGER_EVENT_2);
                        events.RescheduleEvent(EV_MESSENGER, 2000);
                        break;
                    case 5:
                        Talk(TALK_MESSENGER_EVENT_3);
                        events.RescheduleEvent(EV_MESSENGER, 1000);
                        break;
                    case 6:
                        eitrigg->SetWalk(false);
                        eitrigg->GetMotionMaster()->MovePoint(0, 1924.891846, -4139.466309, 40.405350, true, 1.598646);
                        events.RescheduleEvent(EV_MESSENGER, 3000);
                        break;
                    case 7:
                        eitrigg->AI()->Talk(TALK_MESSENGER_EVENT_4);
                        events.RescheduleEvent(EV_MESSENGER, 2000);
                        break;
                    case 8:
                        eitrigg->SetStandState(UNIT_STAND_STATE_KNEEL);
                        events.RescheduleEvent(EV_MESSENGER, 2000);
                        break;
                    case 9:
                        Talk(TALK_MESSENGER_EVENT_5);
                        events.RescheduleEvent(EV_MESSENGER, 5000);
                        break;
                    case 10:
                        eitrigg->AI()->Talk(TALK_MESSENGER_EVENT_6);
                        events.RescheduleEvent(EV_MESSENGER, 2000);
                        break;
                    case 11:
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovePoint(0, 1920.069946, -4126.490234, 42.914200, true, 1.645362);
                        me->SetStandState(UNIT_STAND_STATE_STAND);
                        events.RescheduleEvent(EV_MESSENGER, 7000);
                        break;
                    case 12:
                        me->SetOrientation(4.783030);
                        me->SendMovementFlagUpdate();
                        events.RescheduleEvent(EV_MESSENGER, 3000);
                        break;
                    case 13:
                        eitrigg->SetStandState(UNIT_STAND_STATE_STAND);
                        events.RescheduleEvent(EV_MESSENGER, 1000);
                        break;
                    case 14:
                        Talk(TALK_MESSENGER_EVENT_7);
                        events.RescheduleEvent(EV_MESSENGER, 4000);
                        break;
                    case 15:
                        eitrigg->AI()->Talk(TALK_MESSENGER_EVENT_8);
                        events.RescheduleEvent(EV_MESSENGER, 3000);
                        break;
                    case 16:
                        eitrigg->GetMotionMaster()->MoveTargetedHome();
                        events.RescheduleEvent(EV_MESSENGER, 2000);
                        break;
                    case 17:
                        Talk(TALK_MESSENGER_EVENT_9);
                        events.RescheduleEvent(EV_MESSENGER, 5000);
                        break;
                    case 18:
                        //end, restore initial values
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        me->SetStandState(UNIT_STAND_STATE_SIT);
                        events.CancelEvent(EV_MESSENGER);
                        break;
                    }
                    messengerEventStep++;
                    break;
                }
        }

        bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            if (player->GetQuestStatus(QUEST_6566) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HTW, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            SEND_PREPARED_GOSSIP_MENU(player, me);
            return true;
        }

        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(5733, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU_TEXTID(5734, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->SEND_GOSSIP_MENU_TEXTID(5735, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU_TEXTID(5736, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->SEND_GOSSIP_MENU_TEXTID(5737, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STW6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->SEND_GOSSIP_MENU_TEXTID(5738, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                player->CLOSE_GOSSIP_MENU();
                player->AreaExploredOrEventHappens(QUEST_6566);
                break;
            }
            return true;
        }

        void QuestReward(Player* pPlayer, Quest const* pQuest, uint32 /*opt*/) override
        {
            switch (pQuest->GetQuestId())
            {
                //The Brokering of Peace
                case 8485:
                {
                    std::stringstream sst;
                    //TODO TRANSLATE
                    sst << "Sachez tous que " << pPlayer->GetName() << " - " << pPlayer->GetClass() << " de la Horde - a gagné le respect du Chef de guerre. Il a engagé la diplomatie avec les Grumegueules et accompli diverses actions en notre nom. Il est allé bien au delà de l'appel du devoir. Trois félicitations pour " << pPlayer->GetName() << " - un vrai héros de la Horde !";
                    me->Yell(sst.str().c_str(), LANG_UNIVERSAL);
                    break;
                }
                //Messenger to Thrall
                case 9438:
                {
                    me->AI()->message(MESSAGE_START_MESSENGER_EVENT, 0);
                    break;
                }
            }
        }
    };



    CreatureAI* GetAI(Creature* creature) const
        override {
        return new npc_thrall_warchiefAI(creature);
    }
};


/*######
## npc_eitrigg
######*/

class npc_eitrigg : public CreatureScript
{
public:
    npc_eitrigg() : CreatureScript("npc_eitrigg")
    { }

    class npc_eitriggAI : public ScriptedAI
    {
    public:
        npc_eitriggAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());
                
            //TODO translate
            if (player->GetQuestStatus(4941) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] Valider la quête \"Sagesse d'Eitrigg\".", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            SEND_PREPARED_GOSSIP_MENU(player, me);
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
                player->AreaExploredOrEventHappens(4941);
                
            player->CLOSE_GOSSIP_MENU();
                
            return true;
        }


        virtual void QuestReward(Player* player, Quest const* quest, uint32 /*opt*/) override
        {
            switch (quest->GetQuestId())
            {
            case 9438: //Messenger to Thrall

                break;
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_eitriggAI(creature);
    }
};




void AddSC_orgrimmar()
{

    new npc_neeru_fireblade();

    new npc_shenthul();

    new npc_thrall_warchief();
    
    new npc_eitrigg();
}

