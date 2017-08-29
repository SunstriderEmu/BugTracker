
#define GOSSIP_TELEPORT "Teleport me"
#define QUEST_TELEPORT_HORDE    80000
#define QUEST_TELEPORT_ALLIANCE 80001



class npc_pack58_teleporter : public CreatureScript
{
public:
    npc_pack58_teleporter() : CreatureScript("npc_pack58_teleporter")
    { }

    class npc_pack58_teleporterAI : public ScriptedAI
    {
        public:
        npc_pack58_teleporterAI(Creature* c) : ScriptedAI(c) 
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);  
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        virtual bool GossipHello(Player* player) override
        {
            if(player->GetLevel() > 1)
            {
                me->Whisper("You need to be level 1 to use the pack.", LANG_UNIVERSAL, player);
                return true;
            }

            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            bool alliance = player->TeamForRace(player->GetRace()) == ALLIANCE;

            if(player->GetQuestStatus(alliance ? QUEST_TELEPORT_ALLIANCE : QUEST_TELEPORT_HORDE) == QUEST_STATUS_COMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TELEPORT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+(alliance ? 1 : 2));

            SEND_DEFAULT_GOSSIP_MENU(player, me);
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            switch(action)
            {
            case GOSSIP_ACTION_INFO_DEF+1: //alliance
                player->TeleportTo(0, -8921.09, -119.16, 82.0, 6.0); //Northshire
                break;
            case GOSSIP_ACTION_INFO_DEF+2: //horde
                player->TeleportTo(1, -618.52, -4251.67, 38.72, 0); //Valley of Trials
                break;
            }       

            player->CLOSE_GOSSIP_MENU();
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_pack58_teleporterAI(creature);
    }
};




#define QUEST_DUEL_HORDE    80004
#define QUEST_DUEL_ALLIANCE 80005
#define GOSSIP_DUEL "Challenge to duel"
//#define GOSSIP_DUEL "Defier en duel"

enum DuelGuyMessages
{
    MESSAGE_START_DUEL,
    MESSAGE_STOP_DUEL,
};


class npc_pack58_duelguy : public CreatureScript
{
public:
    npc_pack58_duelguy() : CreatureScript("npc_pack58_duelguy")
    { }

    class npc_pack58_duelguyAI : public ScriptedAI
    {
        public:
        npc_pack58_duelguyAI(Creature* c) : ScriptedAI(c) 
        {
            originalFaction = me->GetFaction();
        }
    
        uint64 PlayerGUID;
        uint32 originalFaction;
    
        uint64 message(uint32 id, uint64 data) 
        override { 
            switch(id)
            {
            case MESSAGE_START_DUEL:
                PlayerGUID = data;
    
                me->SetFaction(FACTION_MONSTER);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                
                if(Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                    AttackStart(player);
    
                break;
            case MESSAGE_STOP_DUEL:
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetFaction(originalFaction);
                me->DeleteThreatList();
                me->CombatStop();
                me->GetMotionMaster()->MoveTargetedHome();
                if(Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                {
                    player->GroupEventHappens(QUEST_DUEL_HORDE, me);
                    player->GroupEventHappens(QUEST_DUEL_ALLIANCE, me);
                }
                break;
            }
            return 0;     
        }
    
        void Reset()
        override {
            PlayerGUID = 0;
    
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFaction(originalFaction);
        }
        
        void DamageTaken(Unit *pSource, uint32 &damage)
        override {
            if (damage > me->GetHealth()) {
                damage = 0;
                message(MESSAGE_STOP_DUEL,PlayerGUID);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            //some attacks ?
    
            DoMeleeAttackIfReady();
        }

        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            uint32 questid;
            if(player->TeamForRace(player->GetRace()) == ALLIANCE)
                questid = QUEST_DUEL_ALLIANCE;
            else
                questid = QUEST_DUEL_HORDE;

            if(player->GetQuestStatus(questid) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DUEL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            SEND_DEFAULT_GOSSIP_MENU(player, me);
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            if (action == GOSSIP_ACTION_INFO_DEF+1)
                (me->AI())->message(MESSAGE_START_DUEL,player->GetGUID());
                
            player->CLOSE_GOSSIP_MENU();
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_pack58_duelguyAI(creature);
    }
};




void AddSC_pack58()
{
 
    new npc_pack58_teleporter();

    new npc_pack58_duelguy();
}