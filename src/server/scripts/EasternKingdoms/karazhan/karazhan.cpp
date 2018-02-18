
#include "karazhan.h"
#include "Chat.h"
#include "ObjectMgr.h"

/*###
# npc_hastings
####*/

#define HASTINGS_TEXT_HELLO             554
#define HASTINGS_TEXT_MENU1             555
#define HASTINGS_TEXT_MENU2             556
#define HASTINGS_GOSSIP_ITEM_1          557
#define HASTINGS_GOSSIP_ITEM_2          19999

class npc_hastings : public CreatureScript
{
public:
    npc_hastings() : CreatureScript("npc_hastings")
    { }

    class npc_hastingsAI : public ScriptedAI
    {
    public:
        npc_hastingsAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM_TEXTID(0, HASTINGS_GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            player->SEND_GOSSIP_MENU_TEXTID(HASTINGS_TEXT_HELLO,me->GetGUID());
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF+1:     
                    player->ADD_GOSSIP_ITEM_TEXTID(0, HASTINGS_GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU_TEXTID(HASTINGS_TEXT_MENU1,me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:     
                    player->SEND_GOSSIP_MENU_TEXTID(HASTINGS_TEXT_MENU2,me->GetGUID()); 
                    break;
            }

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hastingsAI(creature);
    }
};



/*###
# npc_calliard
####*/

#define CALLIARD_TEXT_HELLO             454
#define CALLIARD_TEXT_MENU1             455
#define CALLIARD_GOSSIP_ITEM_1          456

class npc_calliard : public CreatureScript
{
public:
    npc_calliard() : CreatureScript("npc_calliard")
    { }

    class npc_calliardAI : public ScriptedAI
    {
    public:
        npc_calliardAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM_TEXTID(0, CALLIARD_GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    
            player->SEND_GOSSIP_MENU_TEXTID(CALLIARD_TEXT_HELLO,me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if(action == GOSSIP_ACTION_INFO_DEF + 1)
                player->SEND_GOSSIP_MENU_TEXTID(CALLIARD_TEXT_MENU1, me->GetGUID());

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_calliardAI(creature);
    }
};



/*###
# npc_image_of_medivh
####*/

//TODO translate
#define SAY_DIALOG_MEDIVH_1         "Vous avez attiré mon attention, dragon. Mais on ne m'effraie pas aussi facilement que les villageois d'en-dessous."
#define SAY_DIALOG_ARCANAGOS_2      "Votre jeu avec la force des arcanes est allé trop loin, Medivh. Vous avez attiré l'attention de puissances au-delà de votre compréhension. Vous devez quitter Karazhan sur le champ !!"
#define SAY_DIALOG_MEDIVH_3         "Vous osez me défier dans ma propre demeure ? Votre arrogance est stupéfiante, même pour un dragon !"
#define SAY_DIALOG_ARCANAGOS_4      "Une puissance obscure cherche à vous utiliser, Medivh ! Si vous restez, de sombres jours vont suivre. Il faut vous dépêcher, nous n'avons pas beaucoup de temps !"
#define SAY_DIALOG_MEDIVH_5         "Je ne vois pas de quoi vous voulez parler, dragon... mais je ne vais pas me laisser intimider par tant d'insolence. Je quitterai Karazhan quand je l'aurai décidé !"
#define SAY_DIALOG_ARCANAGOS_6      "Vous ne me laissez pas le choix. Je vous arrêterai par la force si vous ne voulez pas revenir à la raison."
#define EMOTE_DIALOG_MEDIVH_7       "commence à invoquer un sort d'une grande puissance, tissant sa propre essence avec la magie."
#define SAY_DIALOG_ARCANAGOS_8      "Qu'avez-vous fait, magicien ? Cela ne peut être... ! Je brûle de... à l'intérieur !"
#define SAY_DIALOG_MEDIVH_9         "Il n'aurait pas dû me mettre en colère. Je dois désormais aller... récupérer ma puissance..."

#define MOB_ARCANAGOS               17652
#define SPELL_FIRE_BALL             30967
#define SPELL_UBER_FIREBALL         30971
#define SPELL_CONFLAGRATION_BLAST   30977
#define SPELL_MANA_SHIELD           31635

static float MedivPos[4] = {-11161.49f,-1902.24f,91.48f,1.94f};
static float ArcanagosPos[4] = {-11169.75f,-1881.48f,95.39f,4.83f};


class npc_image_of_medivh : public CreatureScript
{
public:
    npc_image_of_medivh() : CreatureScript("npc_image_of_medivh")
    { }

    class npc_image_of_medivhAI : public ScriptedAI
    {
        public:
        npc_image_of_medivhAI(Creature* c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        ObjectGuid ArcanagosGUID;
    
        uint32 YellTimer;
        uint32 Step;
        uint32 FireMedivhTimer;
        uint32 FireArcanagosTimer;
    
        bool EventStarted;
    
        void Reset()
        override {
            ArcanagosGUID = ObjectGuid::Empty;
    
            if(pInstance && !pInstance->GetGuidData(DATA_IMAGE_OF_MEDIVH))
            {
                pInstance->SetGuidData(DATA_IMAGE_OF_MEDIVH, me->GetGUID());
                (*me).GetMotionMaster()->MovePoint(1,MedivPos[0],MedivPos[1],MedivPos[2]);
                Step = 0;
            }else
            {
                me->DespawnOrUnsummon();
            }
        }
        void JustEngagedWith(Unit* who)override {}
    
        void MovementInform(uint32 type, uint32 id)
        override {
            if(type != POINT_MOTION_TYPE)
                return;
            if(id == 1)
            {
                StartEvent();
                me->SetOrientation(MedivPos[3]);
                me->SetOrientation(MedivPos[3]);
            }
        }
    
        void StartEvent()
        {
            Step = 1;
            EventStarted = true;
            Creature* Arcanagos = me->SummonCreature(MOB_ARCANAGOS,ArcanagosPos[0],ArcanagosPos[1],ArcanagosPos[2],0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,20000);
            if(!Arcanagos)
                return;
            ArcanagosGUID = Arcanagos->GetGUID();
            Arcanagos->SetDisableGravity(true);
            (*Arcanagos).GetMotionMaster()->MovePoint(0,ArcanagosPos[0],ArcanagosPos[1],ArcanagosPos[2]);
            Arcanagos->SetOrientation(ArcanagosPos[3]);
            me->SetOrientation(MedivPos[3]);
            YellTimer = 10000;
        }
    
    
        uint32 NextStep(uint32 step)
        {
            Unit* arca = ObjectAccessor::GetUnit((*me),ArcanagosGUID);
            Map *map = me->GetMap();
            switch(step)
            {
            case 1:
                me->Yell(SAY_DIALOG_MEDIVH_1,LANG_UNIVERSAL,nullptr);
                return 10000;
            case 2:
                if(arca)
                    (arca->ToCreature())->Yell(SAY_DIALOG_ARCANAGOS_2,LANG_UNIVERSAL,nullptr);
                return 20000;
            case 3:
                me->Yell(SAY_DIALOG_MEDIVH_3,LANG_UNIVERSAL,nullptr);
                return 10000;
            case 4:
                if(arca)
                    (arca->ToCreature())->Yell(SAY_DIALOG_ARCANAGOS_4, LANG_UNIVERSAL, nullptr);
                return 20000;
            case 5:
                me->Yell(SAY_DIALOG_MEDIVH_5, LANG_UNIVERSAL, nullptr);
                return 20000;
            case 6:
                if(arca)
                    (arca->ToCreature())->Yell(SAY_DIALOG_ARCANAGOS_6, LANG_UNIVERSAL, nullptr);
                return 10000;
            case 7:
                FireArcanagosTimer = 500;
                return 5000;
            case 8:
                FireMedivhTimer = 500;
                DoCast(me, SPELL_MANA_SHIELD);
                return 10000;
            case 9:
                me->TextEmote(EMOTE_DIALOG_MEDIVH_7, nullptr, false);
                return 10000;
            case 10:
                if(arca)
                    me->CastSpell(arca, SPELL_CONFLAGRATION_BLAST, TRIGGERED_NONE);
                return 1000;
            case 11:
                if(arca)
                    (arca->ToCreature())->Yell(SAY_DIALOG_ARCANAGOS_8, LANG_UNIVERSAL, nullptr);
                return 5000;
            case 12:
                arca->GetMotionMaster()->MovePoint(0, -11010.82,-1761.18, 156.47);
                arca->SetKeepActive(true);
                arca->SetFarVisible(true);
                arca->InterruptNonMeleeSpells(true);
                arca->SetSpeedRate(MOVE_FLIGHT, 2.0f);
                return 10000;
            case 13:
                me->Yell(SAY_DIALOG_MEDIVH_9, LANG_UNIVERSAL, nullptr);
                return 10000;
            case 14:
                me->SetVisible(false);
                me->ClearInCombat();
    
                if(map->IsDungeon())
                {
                    InstanceMap::PlayerList const &PlayerList = ((InstanceMap*)map)->GetPlayers();
                    for (const auto & i : PlayerList)
                    {
                        if(i.GetSource()->IsAlive())
                        {
                            if(i.GetSource()->GetQuestStatus(9645) == QUEST_STATUS_INCOMPLETE)
                                i.GetSource()->CompleteQuest(9645);
                        }
                    }
                }
                return 50000;
            case 15:
                arca->KillSelf();
                return 5000;
            default : 
                return 9999999;
            }
    
        }
    
        void UpdateAI(const uint32 diff)
        override {
    
            if(YellTimer < diff)
            {
                if(EventStarted)
                {
                    YellTimer = NextStep(Step++);
                }
            }else YellTimer -= diff;
    
            if(Step >= 7 && Step <= 12 )
            {
                Unit* arca = ObjectAccessor::GetUnit((*me),ArcanagosGUID);
    
                if(FireArcanagosTimer < diff)
                {
                    if(arca)
                        arca->CastSpell(me, SPELL_FIRE_BALL, TRIGGERED_NONE);
                    FireArcanagosTimer = 6000;
                }else FireArcanagosTimer -= diff;
    
                if(FireMedivhTimer < diff)
                {
                    if(arca)
                        DoCast(arca, SPELL_FIRE_BALL);
                    FireMedivhTimer = 5000;
                }else FireMedivhTimer -= diff;
    
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_image_of_medivhAI(creature);
    }
};


/*######
## npc_archmage_leryda
######*/

class npc_archmage_leryda : public CreatureScript
{
public:
    npc_archmage_leryda() : CreatureScript("npc_archmage_leryda")
    { }

    class npc_archmage_lerydaAI : public ScriptedAI
    {
    public:
        npc_archmage_lerydaAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());
                
            if (!pPlayer->HasItemCount(29290, 1, true) && !pPlayer->HasItemCount(29279, 1, true) && !pPlayer->HasItemCount(29283, 1, true) &&
                 !pPlayer->HasItemCount(29287, 1, true) && pPlayer->GetReputationRank(967) == REP_EXALTED) {
                if (pPlayer->GetQuestStatus(11031) == QUEST_STATUS_COMPLETE || pPlayer->GetQuestStatus(11032) == QUEST_STATUS_COMPLETE
                        || pPlayer->GetQuestStatus(11033) == QUEST_STATUS_COMPLETE || pPlayer->GetQuestStatus(11034) == QUEST_STATUS_COMPLETE) {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je voudrais une chevalière de grand guérisseur.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je voudrais une chevalière de maître assassin.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je voudrais une chevalière de l'archimage.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je voudrais une chevalière du grand protecteur.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                }
            }
            
            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            uint32 itemId = 0;
            switch (action) {
            case GOSSIP_ACTION_INFO_DEF+1:
                itemId = 29290;
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                itemId = 29283;
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                itemId = 29287;
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                itemId = 29279;
                break;
            }
            
            ItemPosCountVec dest;
            uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, 1);
            if (msg == EQUIP_ERR_OK)
            {
                Item* item = player->StoreNewItem( dest, itemId, true);
                player->SendNewItem(item, 1, true, false);
            }
            
            player->CLOSE_GOSSIP_MENU();
            
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_archmage_lerydaAI(creature);
    }
};



class SealedTome : public GameObjectScript
{
public:
    SealedTome() : GameObjectScript("go_sealed_tome")
    {}

    struct SealedTomeAI : public GameObjectAI
    {
        SealedTomeAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (rand() % 3 == 1)
                player->CastSpell(player, RAND(30762, 30763, 30764, 30765, 30766), TRIGGERED_FULL_MASK);

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new SealedTomeAI(go);
    }
};

/*######
## woefulhealer
######*/
 
class woefulhealer : public CreatureScript
{
public:
    woefulhealer() : CreatureScript("woefulhealer")
    { }

    enum woefulhealer_defines
    {
        TIMER_GLOBALWAIT_MIN       =  2000,
        TIMER_GLOBALWAIT_MAX       =  5000,
        MAXMANA                    =  10000,
        SPELL_FLASHHEAL            =  25235,
        VALUE_FLASHHEAL            =  1200,  
        SPELL_PRAYEROFHEALING      =  25308,
        VALUE_PRAYEROFHEALING      =  1300,
    };

    class woefulhealerAI : public ScriptedAI
    {
        public:
        woefulhealerAI(Creature *c) : ScriptedAI(c) {}
        
        bool flagsset;
        Player* owner; //may be null
        uint16 wait_timer; //Time between two heals
        
        void Reset()
        override {
            owner = me->GetCharmerOrOwner() ? nullptr : me->GetCharmerOrOwner()->ToPlayer();
            if(owner)
                me->GetMotionMaster()->MoveFollow(owner, 0.8f, 210.0f);
            me->SetReactState(REACT_PASSIVE);
            wait_timer = urand(TIMER_GLOBALWAIT_MIN, TIMER_GLOBALWAIT_MAX);
            flagsset = false;
        }
        
        void JustEngagedWith(Unit* who) override {}
      
        void UpdateAI(const uint32 diff)
        override {                
            if (!flagsset) 
            {        
                me->SetMaxPower(POWER_MANA, MAXMANA);
                me->SetPower(POWER_MANA, MAXMANA);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                flagsset = true;
            } //does not seem to work in reset... how to fix this?
                
            if ( !me->IsAlive() || me->IsNonMeleeSpellCast(false) )
                return;
        
            if (wait_timer > diff)
            {
                wait_timer -= diff;
                return;    
            }
            //Reset timer before next heal
            wait_timer = urand(TIMER_GLOBALWAIT_MIN, TIMER_GLOBALWAIT_MAX);
    
            Unit* single_heal_target = nullptr;
            uint8 players_needing_aoe_heal = 0;
            uint32 lowest_hp = 0;
            
            //Select heal target(s)
            for(const auto& i : me->GetMap()->GetPlayers())
            {
                if (Player* i_pl = i.GetSource())
                {
                    // select players close enough and with enough health deficit
                    if (i_pl->IsAlive() && i_pl->GetDistance(me) < 40.0f
                        && ((i_pl->GetMaxHealth() - i_pl->GetHealth()) > VALUE_PRAYEROFHEALING)) // VALUE_FLASHHEAL and VALUE_PRAYEROFHEALING are about the same... let's only use one to simplify the logic
                    {
                        if (!lowest_hp || lowest_hp > i_pl->GetHealth())
                        {
                            single_heal_target = i_pl;
                            lowest_hp = i_pl->GetHealth();
                        }
                        if (owner && i_pl->IsInSameGroupWith(owner))
                            players_needing_aoe_heal++;
                    }
                }
            }
                
            if (!single_heal_target)
                return;
                
            // Cast 
            if (players_needing_aoe_heal >= 3)
                DoCast(me, SPELL_PRAYEROFHEALING);
            else
                DoCast(single_heal_target, SPELL_FLASHHEAL);
                
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new woefulhealerAI(creature);
    }
};

/*######
## npc_arcane_anomaly
######*/


class npc_arcane_anomaly : public CreatureScript
{
public:
    npc_arcane_anomaly() : CreatureScript("npc_arcane_anomaly")
    { }

    enum Spells
    {
        ANOMALY_SPELL_MANA_SHIELD       = 29880,
        ANOMALY_SPELL_BLINK             = 29883, //Spell with a dummy effect NYI
        ANOMALY_SPELL_ARCANE_VOLLEY     = 29885,
        ANOMALY_SPELL_LOOSE_MANA        = 29882,
    };

    class npc_arcane_anomalyAI : public ScriptedAI
    {
        public:
        npc_arcane_anomalyAI(Creature *c) : ScriptedAI(c) {}
        
        bool castedShield;
        uint32 blinkTimer;
        uint32 volleyTimer;
    
        void Reset()
        override {
            blinkTimer = 5000 + rand()%10000;
            volleyTimer = 10000 + rand()%5000;
            castedShield = false;
        }
    
        void JustEngagedWith(Unit* who) 
        override {
            DoCast(me, ANOMALY_SPELL_MANA_SHIELD, true);
            castedShield = true;
        }

        void JustDied(Unit* /*who*/) override 
        {
            DoCast(me, ANOMALY_SPELL_LOOSE_MANA, true);
        }
    
        //cannot die if we havent casted our mana shield
        void DamageTaken(Unit* pKiller, uint32 &damage) override 
        {
            if(!castedShield && damage >= me->GetHealth())
                damage = me->GetHealth()-1; //down to 1 hp
        }
      
        void UpdateAI(const uint32 diff) override 
        {                
            if(!UpdateVictim())
                return;
    
            if(blinkTimer < diff)
            {
                if (DoCast(me, ANOMALY_SPELL_BLINK) == SPELL_CAST_OK)
                    blinkTimer = urand(10 * SECOND*IN_MILLISECONDS, 15 * SECOND*IN_MILLISECONDS);
            } else blinkTimer -= diff;
    
            if(volleyTimer < diff)
            {
                if (DoCast(me, ANOMALY_SPELL_ARCANE_VOLLEY) == SPELL_CAST_OK)
                    volleyTimer = urand(20 * SECOND*IN_MILLISECONDS, 25 * SECOND*IN_MILLISECONDS);
            } else volleyTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_arcane_anomalyAI(creature);
    }
};


void AddSC_karazhan()
{
    new npc_image_of_medivh();
    new npc_archmage_leryda();
    new SealedTome();
    new woefulhealer();
    new npc_arcane_anomaly();
    new npc_hastings();
    new npc_calliard();
}

