#include "ObjectMgr.h"

#define BADABOUM_RANGE 24.0f
#define SPELL_VISUAL_BADABOUM 46225
#define CREATURE_BADABOUM 91448
#define WAITTIME 2500
#define TEXT_HOHI "Coucou !"
#define TEXT_GIMME_TARGET "Donnez moi une cible !"

struct mylittlebomblingAI : public ScriptedAI
{
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
    
    void EnterCombat(Unit* who)
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
};

bool GossipHello_mylittlebombling(Player *player, Creature *_Creature)
{    
    if (((mylittlebomblingAI*)_Creature->AI())->phase == mylittlebomblingAI::IDLE)
        player->ADD_GOSSIP_ITEM_EXTENDED( 0, TEXT_GIMME_TARGET, GOSSIP_SENDER_MAIN, 1, "", 0, true);
        
        player->SEND_GOSSIP_MENU_TEXTID(3,_Creature->GetGUID());

    return true;
}

bool GossipSelectWithCode_mylittlebombling( Player *player, Creature *_Creature, uint32 sender, uint32 action, const char* Code )
{
    if (!((mylittlebomblingAI*)_Creature->AI())->GoHurt(Code))
        _Creature->Say("Me not find :(", LANG_UNIVERSAL,nullptr);

    player->PlayerTalkClass->SendCloseGossip();
    return true;
}

struct  mylittlebombling_visualAI : public ScriptedAI
{
    mylittlebombling_visualAI(Creature* creature) : ScriptedAI(creature) 
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->CastSpell(me, SPELL_VISUAL_BADABOUM, true);
    }

    void EnterCombat(Unit* who)
    override {}
};


CreatureAI* GetAI_mylittlebombling(Creature *_Creature)
{
    return new mylittlebomblingAI (_Creature);
}

CreatureAI* GetAI_mylittlebombling_visual(Creature *_Creature)
{
    return new mylittlebombling_visualAI (_Creature);
}

void AddSC_mylittlebombling()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="npc_mylittlebombling";
    newscript->GetAI = &GetAI_mylittlebombling;
    newscript->OnGossipHello = &GossipHello_mylittlebombling;
    newscript->OnGossipSelectCode = &GossipSelectWithCode_mylittlebombling;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_mylittlebombling_visual";
    newscript->GetAI = &GetAI_mylittlebombling_visual;
    sScriptMgr->RegisterOLDScript(newscript);
}
