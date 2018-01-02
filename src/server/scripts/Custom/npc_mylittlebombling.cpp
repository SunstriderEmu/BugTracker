#include "ObjectMgr.h"

#define BADABOUM_RANGE 24.0f
#define SPELL_VISUAL_BADABOUM 46225
#define CREATURE_BADABOUM 91448
#define WAITTIME 2500
#define TEXT_HOHI "Coucou !"
#define TEXT_GIMME_TARGET "Donnez moi une cible !"


class npc_mylittlebombling : public CreatureScript
{
public:
    npc_mylittlebombling() : CreatureScript("npc_mylittlebombling")
    { }

    class mylittlebomblingAI : public ScriptedAI
    {
        public:
        short phase;
        uint32 waitTimer;
    
        enum PHASES {
            IDLE,
            TRACKING,
            HOHI
        };
    
        mylittlebomblingAI(Creature* creature) : ScriptedAI(creature) 
        {} 
    
        void Reset() override {
            me->SetReactState(REACT_PASSIVE);
            phase = IDLE;
            waitTimer = WAITTIME;
        }
        
        void JustEngagedWith(Unit* who)
        override {}
    
        void UpdateAI(uint32 const diff)
        override {
            switch(phase)
            {
            case IDLE:
                break;
            case TRACKING:
                if(me->GetVictim())
                {
                    if (me->GetDistance(me->GetVictim()) < 5)
                    {
                        phase = HOHI;
                        me->Say(TEXT_HOHI,LANG_UNIVERSAL,nullptr);
                        me->StopMoving();
                    }
                } else {
                    Reset();
                }
                break;
            case HOHI:
                if (waitTimer < diff)
                {
                    Kaboom();
                    me->DisappearAndDie();
                } else {
                    waitTimer -= diff;
                }
                break;
            }
        }
    
        void Kaboom()
        {
            DoSpawnCreature(CREATURE_BADABOUM, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN, 5000); //just for the effect
    
            std::list<Player*> playerlist;
            Trinity::AnyPlayerInObjectRangeCheck check(me, BADABOUM_RANGE);
            Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, playerlist, check);
            Cell::VisitGridObjects(me, searcher, BADABOUM_RANGE);
            if(!playerlist.size())
                return;
    
            for(auto & i : playerlist)
            {
                if(i && !i->IsGameMaster())
                {
                    me->DealDamage(i, 500000, nullptr, SPELL_DIRECT_DAMAGE, SPELL_SCHOOL_MASK_FIRE, nullptr, false);
                }
            }
        }
    
        bool GoHurt(const char* Code)
        {
            std::string name = Code;
    
            if(!normalizePlayerName(name))
                return false;
    
            Player *target = ObjectAccessor::FindConnectedPlayerByName(name.c_str());
    
            if(target) {
                AttackStart(target);
                phase = TRACKING;
                return true;
            } else {
                return false;
            }
        }
    
        void JustDied(Unit* /* who */)
        override {
            Kaboom();
        }

        virtual bool GossipHello(Player* player) override
        {
            
            if (phase == mylittlebomblingAI::IDLE)
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, TEXT_GIMME_TARGET, GOSSIP_SENDER_MAIN, 1, "", 0, true);
                
                player->SEND_GOSSIP_MENU_TEXTID(3,me->GetGUID());

            return true;

        }


        virtual bool GossipSelectCode(Player* player, uint32 menuId, uint32 gossipListId, const char* Code) override
        {
            if (!GoHurt(Code))
                me->Say("Me not find :(", LANG_UNIVERSAL,nullptr);

            player->PlayerTalkClass->SendCloseGossip();
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mylittlebomblingAI(creature);
    }
};






class npc_mylittlebombling_visual : public CreatureScript
{
public:
    npc_mylittlebombling_visual() : CreatureScript("npc_mylittlebombling_visual")
    { }

    class  mylittlebombling_visualAI : public ScriptedAI
    {
        public:
        mylittlebombling_visualAI(Creature* creature) : ScriptedAI(creature) 
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->CastSpell(me, SPELL_VISUAL_BADABOUM, TRIGGERED_FULL_MASK);
        }
    
        void JustEngagedWith(Unit* who)
        override {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mylittlebombling_visualAI(creature);
    }
};


void AddSC_mylittlebombling()
{

    new npc_mylittlebombling();

    new npc_mylittlebombling_visual();
}
