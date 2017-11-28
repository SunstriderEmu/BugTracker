
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

class npc_bunthen_plainswind : public CreatureScript
{
public:
    npc_bunthen_plainswind() : CreatureScript("npc_bunthen_plainswind")
    { }

    class npc_bunthen_plainswindAI : public ScriptedAI
    {
    public:
        npc_bunthen_plainswindAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if(pPlayer->GetClass() != CLASS_DRUID)
                pPlayer->SEND_GOSSIP_MENU_TEXTID(4916, me->GetGUID());
            else if(pPlayer->GetTeam() != HORDE)
            {
                if(pPlayer->GetQuestStatus(272) == QUEST_STATUS_INCOMPLETE)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BP1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

                pPlayer->SEND_GOSSIP_MENU_TEXTID(4917,me->GetGUID());
            }
            else if(pPlayer->GetClass() == CLASS_DRUID && pPlayer->GetTeam() == HORDE)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BP2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

                if(pPlayer->GetQuestStatus(30) == QUEST_STATUS_INCOMPLETE)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BP1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

                pPlayer->SEND_GOSSIP_MENU_TEXTID(4918, me->GetGUID());
            }
            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch(action)
            {
                case GOSSIP_ACTION_INFO_DEF + 1:
                {
                    player->CLOSE_GOSSIP_MENU();
                    if (player->GetClass() == CLASS_DRUID && player->GetTeam() == HORDE)
                    {
                        std::vector<uint32> nodes;

                        nodes.resize(2);
                        nodes[0] = 63;                              // Nighthaven, Moonglade
                        nodes[1] = 22;                              // Thunder Bluff, Mulgore
                        player->ActivateTaxiPathTo(nodes);
                    }
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 2:
                    player->SEND_GOSSIP_MENU_TEXTID(5373, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 3:
                    player->SEND_GOSSIP_MENU_TEXTID(5376, me->GetGUID());
                    break;
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bunthen_plainswindAI(creature);
    }
};



/*######
## npc_great_bear_spirit
######*/

#define GOSSIP_BEAR1 "What do you represent, spirit?"
#define GOSSIP_BEAR2 "I seek to understand the importance of strength of the body."
#define GOSSIP_BEAR3 "I seek to understand the importance of strength of the heart."
#define GOSSIP_BEAR4 "I have heard your words, Great Bear Spirit, and I understand. I now seek your blessings to fully learn the way of the Claw."

class npc_great_bear_spirit : public CreatureScript
{
public:
    npc_great_bear_spirit() : CreatureScript("npc_great_bear_spirit")
    { }

    class npc_great_bear_spiritAI : public ScriptedAI
    {
    public:
        npc_great_bear_spiritAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            //ally or horde quest
            if (pPlayer->GetQuestStatus(5929) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(5930) == QUEST_STATUS_INCOMPLETE)
            {
                pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_BEAR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(4719, me->GetGUID());
            }
            else
                pPlayer->SEND_GOSSIP_MENU_TEXTID(4718, me->GetGUID());

            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU_TEXTID(4721, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 1:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(4733, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BEAR4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU_TEXTID(4734, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 3:
                    player->SEND_GOSSIP_MENU_TEXTID(4735, me->GetGUID());
                    if (player->GetQuestStatus(5929) == QUEST_STATUS_INCOMPLETE)
                        player->AreaExploredOrEventHappens(5929);
                    if (player->GetQuestStatus(5930) == QUEST_STATUS_INCOMPLETE)
                        player->AreaExploredOrEventHappens(5930);
                    break;
            }
            
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_great_bear_spiritAI(creature);
    }
};



/*######
## npc_silva_filnaveth
######*/

#define GOSSIP_SF1 "Do you know where I can find Half Pendant of Aquatic Agility?"
#define GOSSIP_SF2 "I'd like to fly to Rut'theran Village."

class npc_silva_filnaveth : public CreatureScript
{
public:
    npc_silva_filnaveth() : CreatureScript("npc_silva_filnaveth")
    { }

    class npc_silva_filnavethAI : public ScriptedAI
    {
    public:
        npc_silva_filnavethAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetClass() != CLASS_DRUID)
                pPlayer->SEND_GOSSIP_MENU_TEXTID(4913, me->GetGUID());
            else if (pPlayer->GetTeam() != ALLIANCE)
            {
                if (pPlayer->GetQuestStatus(30) == QUEST_STATUS_INCOMPLETE)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SF1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

                pPlayer->SEND_GOSSIP_MENU_TEXTID(4915, me->GetGUID());
            }
            else if (pPlayer->GetClass() == CLASS_DRUID && pPlayer->GetTeam() == ALLIANCE)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SF2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

                if (pPlayer->GetQuestStatus(272) == QUEST_STATUS_INCOMPLETE)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SF1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

                pPlayer->SEND_GOSSIP_MENU_TEXTID(4914, me->GetGUID());
            }
            
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch(action)
            {
                case GOSSIP_ACTION_INFO_DEF + 1:
                {
                    player->CLOSE_GOSSIP_MENU();
                    if (player->GetClass() == CLASS_DRUID && player->GetTeam() == ALLIANCE)
                    {
                        std::vector<uint32> nodes;

                        nodes.resize(2);
                        nodes[0] = 62;                              // Nighthaven, Moonglade
                        nodes[1] = 27;                              // Rut'theran Village, Teldrassil
                        player->ActivateTaxiPathTo(nodes);
                    }
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 2:
                    player->SEND_GOSSIP_MENU_TEXTID(5374, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 3:
                    player->SEND_GOSSIP_MENU_TEXTID(5375, me->GetGUID());
                    break;
            }
            
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_silva_filnavethAI(creature);
    }
};



/*######
## npc_clintar_spirit
######*/

float Clintar_spirit_WP[41][5] =
{
//        pos_x     pos_y      pos_z     orien  waitTime
    { 7465.28f, -3115.46f, 439.327f, 0.83f, 4000 },
    { 7476.49f, -3101.00f, 443.457f, 0.89f, 0 },
    { 7486.57f, -3085.59f, 439.478f, 1.07f, 0 },
    { 7472.19f, -3085.06f, 443.142f, 3.07f, 0 },
    { 7456.92f, -3085.91f, 438.862f, 3.24f, 0 },
    { 7446.68f, -3083.43f, 438.245f, 2.40f, 0 },
    { 7446.17f, -3080.21f, 439.826f, 1.10f, 6000 },
    { 7452.41f, -3085.80f, 438.984f, 5.78f, 0 },
    { 7469.11f, -3084.94f, 443.048f, 6.25f, 0 },
    { 7483.79f, -3085.44f, 439.607f, 6.25f, 0 },
    { 7491.14f, -3090.96f, 439.983f, 5.44f, 0 },
    { 7497.62f, -3098.22f, 436.854f, 5.44f, 0 },
    { 7498.72f, -3113.41f, 434.596f, 4.84f, 0 },
    { 7500.06f, -3122.51f, 434.749f, 5.17f, 0 },
    { 7504.96f, -3131.53f, 434.475f, 4.74f, 0 },
    { 7504.31f, -3133.53f, 435.693f, 3.84f, 6000 },
    { 7504.55f, -3133.27f, 435.476f, 0.68f, 15000 },
    { 7501.99f, -3126.01f, 434.930f, 1.83f, 0 },
    { 7490.76f, -3114.97f, 434.431f, 2.51f, 0 },
    { 7479.64f, -3105.51f, 431.123f, 1.83f, 0 },
    { 7474.63f, -3086.59f, 428.994f, 1.83f, 2000 },
    { 7472.96f, -3074.18f, 427.566f, 1.57f, 0 },
    { 7472.25f, -3063.00f, 428.268f, 1.55f, 0 },
    { 7473.46f, -3054.22f, 427.588f, 0.36f, 0 },
    { 7475.08f, -3053.60f, 428.653f, 0.36f, 6000 },
    { 7474.66f, -3053.56f, 428.433f, 3.19f, 4000 },
    { 7471.81f, -3058.84f, 427.073f, 4.29f, 0 },
    { 7472.16f, -3064.91f, 427.772f, 4.95f, 0 },
    { 7471.56f, -3085.36f, 428.924f, 4.72f, 0 },
    { 7473.56f, -3093.48f, 429.294f, 5.04f, 0 },
    { 7478.94f, -3104.29f, 430.638f, 5.23f, 0 },
    { 7484.46f, -3109.61f, 432.769f, 5.79f, 0 },
    { 7490.23f, -3111.08f, 434.431f, 0.02f, 0 },
    { 7496.29f, -3108.00f, 434.783f, 1.15f, 0 },
    { 7497.46f, -3100.66f, 436.191f, 1.50f, 0 },
    { 7495.64f, -3093.39f, 438.349f, 2.10f, 0 },
    { 7492.44f, -3086.01f, 440.267f, 1.38f, 0 },
    { 7498.26f, -3076.44f, 440.808f, 0.71f, 0 },
    { 7506.40f, -3067.35f, 443.640f, 0.77f, 0 },
    { 7518.37f, -3057.42f, 445.584f, 0.74f, 0 },
    { 7517.51f, -3056.30f, 444.568f, 2.49f, 4500 }
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


class npc_clintar_spirit : public CreatureScript
{
public:
    npc_clintar_spirit() : CreatureScript("npc_clintar_spirit")
    { }

    class npc_clintar_spiritAI : public EscortAI
    {
        public:
    public:
        npc_clintar_spiritAI(Creature *c) : EscortAI(c) {}
    
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
            
            EscortAI::EnterEvadeMode(why);
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
                Start(true, false, PlayerGUID);
            }
            return;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            EscortAI::UpdateAI(diff);
    
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
                                    mob->GetThreatManager().AddThreat(me,10000.0f);
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
    
        void WaypointReached(uint32 id, uint32 pathID)
        override {
            CurrWP = id;
            Event_Timer = 0;
            Step = 0;
            Event_onWait = true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_clintar_spiritAI(creature);
    }
};


/*####
# npc_clintar_dreamwalker
####*/

#define CLINTAR_SPIRIT 22916

class npc_clintar_dreamwalker : public CreatureScript
{
public:
    npc_clintar_dreamwalker() : CreatureScript("npc_clintar_dreamwalker")
    { }

    class npc_clintar_dreamwalkerAI : public ScriptedAI
    {
    public:
        npc_clintar_dreamwalkerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if (pQuest->GetQuestId() == 10965)
            {
                Creature* clintar_spirit = me->SummonCreature(CLINTAR_SPIRIT, CLINTAR_SPIRIT_SUMMON_X, CLINTAR_SPIRIT_SUMMON_Y, CLINTAR_SPIRIT_SUMMON_Z, CLINTAR_SPIRIT_SUMMON_O, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 100000);
                if(clintar_spirit)
                    CAST_AI(npc_clintar_spirit::npc_clintar_spiritAI, (clintar_spirit->AI()))->StartEvent(pPlayer);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_clintar_dreamwalkerAI(creature);
    }
};


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
    { 7817.186523f, -2304.227539f, 455.941071f, 4.804095f }, // walk wp 1 (cross)
    { 7925.188477f, -2312.769043f, 471.415039f, 6.254246f }, // walk wp 2 (before turn)
    { 7942.157227f, -2321.153076f, 476.773834f, 5.792509f }, // walk wp 3 (after turn)
    { 7957.152344f, -2373.932373f, 486.453094f, 4.794063f }, // walk wp 4 (before house)
    { 7965.914551f, -2491.798340f, 487.759705f, 4.844883f }, // walk wp 5 (after house)
    { 7972.112305f, -2517.210449f, 487.689850f, 4.824812f }, // walk wp 6 (before bridge)
    { 7975.595703f, -2551.107422f, 490.081543f, 4.839223f }, // walk wp 7 (after bridge)
    { 7945.702637f, -2573.971191f, 489.783569f, 4.252142f }, // walk wp 8 (after bridge 2)
    { 7951.856934f, -2595.572998f, 489.919556f, 4.447841f }, // walk wp 9 (before platform)
    { 7948.349609f, -2610.257080f, 492.345001f, 4.477947f }, // walk wp 10 (on platform)
    { 7926.278320f, -2633.262451f, 492.530151f, 3.842072f }, // invocation of eranikus
    { 7948.349609f, -2610.257080f, 492.345001f, 1.395251f }, // walk wp 12 (on platform)
    { 7951.856934f, -2595.572998f, 489.919556f, 1.395251f }, // walk wp 13 (before platform)
    { 7945.702637f, -2573.971191f, 489.783569f, 2.750073f }, // walk wp 14 (after bridge 2)
    { 7898.774414f, -2566.517334f, 487.833344f, 3.216603f }, // walk wp 15 (after bridge 3)
    { 7836.721680f, -2571.058350f, 489.286804f, 3.216603f }, // house
    { 7844.209961f, -2570.704346f, 489.285278f, 0.129769f }, // house, waiting for combat
    { 7877.886719f, -2565.909424f, 486.946411f, 0.043205f }, // in front of house
};

static Locations EranikusWP[] =
{
    { 7863.083984f, -2682.686035f, 469.532166f, 0.642453f }, // spawn
    { 7941.503906f, -2576.785889f, 501.884308f, 2.918067f }, // hover 1
    { 7930.495605f, -2574.283447f, 501.884308f, 2.835252f }, // hover 2
    { 7919.830566f, -2570.955811f, 489.375031f, 2.918945f }, // landing
};

/*static Locations TyrandeWP[] =
{
    { 7884.979004, -2566.499023, 486.958527, 6.255793 }, // casting
};*/

static Locations PriestessSP[] =
{
    { 7814.898926f, -2301.132812f, 456.282923f, 0.0f },
    { 7813.714355f, -2305.572510f, 455.794922f, 0.0f },
    { 7812.495605f, -2298.683594f, 456.128387f, 0.0f },
    { 7811.326172f, -2302.086670f, 455.870941f, 0.0f },
    { 7810.257812f, -2306.418213f, 455.531525f, 0.0f },
    { 7809.302246f, -2299.352539f, 455.838287f, 0.0f },
    { 7808.051270f, -2303.647461f, 455.473450f, 0.0f },
    { 7806.024902f, -2300.486084f, 455.584351f, 0.0f },
};

static Locations AddsSP[] =
{
    { 7884.774414f, -2550.940918f, 483.867340f, 0.0f },
    { 7898.257812f, -2552.235596f, 483.919922f, 0.0f },
    { 7906.317871f, -2584.823730f, 484.623108f, 0.0f },
    { 7944.910645f, -2562.068604f, 485.228790f, 0.0f },
    { 7955.473633f, -2551.123291f, 484.568634f, 0.0f },
    { 7959.822754f, -2552.863770f, 484.098755f, 0.0f },
    { 7939.934570f, -2597.583252f, 482.697784f, 0.0f },
    { 7983.933105f, -2471.372803f, 487.516327f, 0.0f },
    { 7946.840820f, -2469.763672f, 485.254822f, 0.0f },
    { 7928.883301f, -2554.717773f, 485.188904f, 0.0f },
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


class npc_keeper_remulos : public CreatureScript
{
public:
    npc_keeper_remulos() : CreatureScript("npc_keeper_remulos")
    { }

    class npc_keeper_remulosAI : public ScriptedAI
    {
        public:
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
                ((TempSummon*)c)->UnSummon();
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
            me->GetThreatManager().ClearAllThreat();
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
                    eranikus->SetFaction(FACTION_FRIENDLY);
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
                    ((TempSummon*)eranikus)->UnSummon();
                }
                else {
                    //else set to last position (dunno if this is correct, this is a quickfix
                    x = EranikusWP[3].x;
                    y = EranikusWP[3].y;
                    z = EranikusWP[3].z;
                    o = 0.0f;
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

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if (pQuest->GetQuestId() == 8736)
            {
                CAST_AI(npc_keeper_remulos::npc_keeper_remulosAI, (me->AI()))->StartEvent(pPlayer->GetGUID());
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_keeper_remulosAI(creature);
    }
};



/*####
# npc_nightmare_phantasm
####*/

#define SWELL_OF_SOULS 21307
#define NIGHT_SHADOW_BOLT_VOLLEY 17228
#define AURA_OF_FEAR 26641


class npc_nightmare_phantasm : public CreatureScript
{
public:
    npc_nightmare_phantasm() : CreatureScript("npc_nightmare_phantasm")
    { }

    class npc_nightmare_phantasmAI : public ScriptedAI
    {
        public:
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
            Creature* c = me->FindNearestCreature(REMULOS, 500);
            if (c)
                CAST_AI(npc_keeper_remulos::npc_keeper_remulosAI, (c->AI()))->NightKilled();
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!me->IsInCombat()) {
                Creature* c = me->FindNearestCreature(REMULOS, 500);
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_nightmare_phantasmAI(creature);
    }
};


/*####
# npc_eranikus_tyrant_of_the_dream
####*/

#define ACID_BREATH             24839
#define NOXIOUS_BREATH          24818
#define ERA_SHADOW_BOLT_VOLLEY  25586


class npc_eranikus_tyrant_of_the_dream : public CreatureScript
{
public:
    npc_eranikus_tyrant_of_the_dream() : CreatureScript("npc_eranikus_tyrant_of_the_dream")
    { }

    class npc_eranikus_tyrant_of_the_dreamAI : public ScriptedAI
    {
        public:
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
            Creature* c = me->FindNearestCreature(REMULOS, 500);
            if (c)
                CAST_AI(npc_keeper_remulos::npc_keeper_remulosAI, (c->AI()))->EventFailed();
        }
    
        void MoveInLineOfSight(Unit*) override {}
    
        void EnterEvadeMode(EvadeReason /* why */)
        override {
            combatPhase = false;
            me->InterruptNonMeleeSpells(true);
            me->RemoveAllAuras();
            me->GetThreatManager().ClearAllThreat();
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
                Creature* c = me->FindNearestCreature(REMULOS, 500);
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_eranikus_tyrant_of_the_dreamAI(creature);
    }
};


#define MASS_HEALING    25839


class npc_tyrande : public CreatureScript
{
public:
    npc_tyrande() : CreatureScript("npc_tyrande")
    { }

    class npc_tyrandeAI : public ScriptedAI
    {
        public:
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
            Creature* c = me->FindNearestCreature(REMULOS, 500);
            if (c)
                CAST_AI(npc_keeper_remulos::npc_keeper_remulosAI, (c->AI()))->EventFailed();
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
                Creature* remulos = me->FindNearestCreature(REMULOS, 500);
                if (remulos)
                    CAST_AI(npc_keeper_remulos::npc_keeper_remulosAI, (remulos->AI()))->TyrandeComes(false);
                break;
            }
            case 18:
            {
                Creature* remulos = me->FindNearestCreature(REMULOS, 500);
                if (remulos)
                    CAST_AI(npc_keeper_remulos::npc_keeper_remulosAI, (remulos->AI()))->TyrandeComes(true);
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
    
            Creature* remulos = me->FindNearestCreature(REMULOS, 500);
            if (remulos && CAST_AI(npc_keeper_remulos::npc_keeper_remulosAI, (remulos->AI()))->GetPhase() != PHASE_COMBAT2)
                return;
    
            if (Heal_Timer <= diff)
            {
                DoCast(me, MASS_HEALING);
                Heal_Timer = 20000;
            } else
                Heal_Timer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_tyrandeAI(creature);
    }
};



class npc_priestess_of_the_moon : public CreatureScript
{
public:
    npc_priestess_of_the_moon() : CreatureScript("npc_priestess_of_the_moon")
    { }

    class npc_priestess_of_the_moonAI : public ScriptedAI
    {
        public:
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_priestess_of_the_moonAI(creature);
    }
};


/*####
# AddSC
####*/

void AddSC_moonglade()
{

    new npc_bunthen_plainswind();

    new npc_great_bear_spirit();

    new npc_silva_filnaveth();

    new npc_clintar_dreamwalker();

    new npc_clintar_spirit();

    new npc_keeper_remulos();

    new npc_nightmare_phantasm();

    new npc_eranikus_tyrant_of_the_dream();

    new npc_tyrande();

    new npc_priestess_of_the_moon();
}

