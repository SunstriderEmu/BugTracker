#include "MapManager.h"
#include "GameEventMgr.h"

#define MORPH_MAX 0.5
#define HOUR 3600

enum Firework
{
    GOSSIP_START,
    GOSSIP_SELECT_EVENT,
    GOSSIP_RELOAD,
    GOSSIP_PRELOAD,

    GOBJECT_RAMP = 34,
    CREATURE_LAUNCHER = 1412,

    SPELL_FIREWORK_BLUE = 11540,
    SPELL_FIREWORK_RED = 6668,
    SPELL_FIREWORK_GREEN = 11541,
    SPELL_FIREWORK_BLUE_WHITE_RED = 11543, //multixplosion
    SPELL_FIREWORK_YELLOW_PINK = 11544, //spirate
    SPELL_FIREWORK_PURPLE = 30161, //spirale/Multixplosion
    SPELL_FIREWORK_LOVE = 44940,
    SPELL_ROCKET_RED = 47004, //boum au sol avant de partir
    //poulet fus�es au milieu hihi
    GOB_ROCKET_RED = 180851,
    GOB_ROCKET_BLUE = 180854,
    GOB_ROCKET_GREEN = 180855,
    //no purple for some reason...
    GOB_ROCKET_WHITE = 180857,
    GOB_ROCKET_YELLOW = 180858,
    //there are more spells with BIG variation, such as 180862
    GOB_ROCKET_RED_BIG = 180860,
    GOB_ROCKET_BLUE_BIG = 180861,
    GOB_ROCKET_GREEN_BIG = 180862,
    GOB_ROCKET_PURPLE_BIG = 180863,
    GOB_ROCKET_WHITE_BIG = 180864,
    GOB_ROCKET_YELLOW_BIG = 180865,
};

struct FireworkEvent {

    FireworkEvent(uint32 spellorGobId, float size, uint8 posX, uint8 posY, float ori = 0.0f, float morphX = 0.0f, float morphY = 0.0f) :
        spellorGobId(spellorGobId),size(size),posX(posX),posY(posY),ori(ori),morphX(morphX),morphY(morphY) 
    { }

    uint32 spellorGobId;
    float size;
    uint8 posX;
    uint8 posY;
    float ori;
    float morphX;
    float morphY;
};


class npc_firework_controller : public CreatureScript
{
public:
    npc_firework_controller() : CreatureScript("npc_firework_controller")
    { }

    class firework_controllerAI : public ScriptedAI
    {
        public:
        firework_controllerAI(Creature* creature) : 
            ScriptedAI(creature),
            cellSize(3.0f),
            eventId(0)
        {
            SetupEvent();
            lastHourDone = time(nullptr) / HOUR;
        } 
    
        float gridStartX, gridStartY, gridZ;
        float cellSize;
        uint32 endTime;
        uint8 eventId;
    
        uint32 lastEventTime; //time of the last event
        int currentTime; //time counter (increment with each updateAI)
        bool eventStarted;
    
        uint32 lastHourDone;
    
        std::multimap<uint32,FireworkEvent*> eventMap;
        
        void Reset() override {
            me->GetPosition(gridStartX,gridStartY,gridZ);
            me->SetReactState(REACT_PASSIVE);
            me->SetVisible(false);
            me->SetDisableGravity(true);
    
            eventStarted = false;
            currentTime = 0;
            lastEventTime = 0;
        }
    
        bool AddEvent(uint32 time, uint32 spellorGobId, float size, uint8 posX, uint8 posY, float ori = 0.0f, float morphX = 0.0f, float morphY = 0.0f)
        {
            if(!spellorGobId)
                return false;
            if(morphX < -MORPH_MAX || morphX > MORPH_MAX)
                morphX = MORPH_MAX;
            if(morphY < -MORPH_MAX || morphY > MORPH_MAX)
                morphY = MORPH_MAX;
            
            auto  event = new FireworkEvent(spellorGobId,size,posX,posY,ori,morphX,morphY);
    
            eventMap.insert(std::make_pair(time,event));
    
            if(time > endTime)
                endTime = time;
    
            return true;
        }
    
        void SetupEvent()
        {
            Reset();
            eventMap.clear();
            endTime = 0;
            QueryResult result = WorldDatabase.PQuery("SELECT time, spellorgob, size, posX, posY, ori, morphX, morphY FROM game_event_fireworks WHERE groupid = %u ORDER BY time",eventId);
            if (result) {
                do {
                    Field* fields = result->Fetch();
                    if(!AddEvent(fields[0].GetUInt32(),fields[1].GetUInt32(), fields[2].GetFloat(),fields[3].GetUInt8(),fields[4].GetUInt8(), fields[5].GetFloat(),fields[6].GetFloat(),fields[7].GetFloat()))
                        TC_LOG_ERROR("scripts","firework_controller : invalid db entry");
                } while (result->NextRow());
            }
        }
    
        //get real coords
        void GetTargetCoords(uint8 posX, uint8 posY, float& realPositionX, float& realPositionY)
        {
            realPositionX = gridStartX + posX * cellSize;
            realPositionY = gridStartY + posY * cellSize;
        }
    
        void ExecEvent(FireworkEvent* event)
        {
            float x,y,z;
            GetTargetCoords(event->posX,event->posY,x,y);
            z = gridZ;
            me->UpdateAllowedPositionZ(x, y, z);
            if(event->spellorGobId < 100000) //if it's a spell
            {    
                if(Creature* c = me->SummonCreature(CREATURE_LAUNCHER,x,y,z,event->ori,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,6000))
                {
                    c->SetDisplayId(11686); //invisible model
                    c->SetDisableGravity(true);
                    c->SetFloatValue(OBJECT_FIELD_SCALE_X, event->size);
                    c->CastSpell(c,event->spellorGobId,true);
                }
            } else {
                if(GameObject* gob = me->SummonGameObject(event->spellorGobId,Position(x,y,z,event->ori), G3D::Quat(event->morphX,event->morphY,0,0),0))
                {
                    gob->SetFloatValue(OBJECT_FIELD_SCALE_X, event->size);
                    Map* map = me->GetMap();
                    map->RemoveFromMap(gob,false); 
                    gob->SetMap(map);
                    map->AddToMap(gob);
                    gob->Delete(); //this trigger explosion
                }
            }
        }
    
        void Preload() //gobject arent shown properly the first time
        {
            for (auto itr : eventMap)
            {
                if(itr.second->spellorGobId > 100000) //only needed for gobjects
                    ExecEvent(itr.second);
            }
        }
    
        void UpdateAI(uint32 const diff)
        override {
            if(!eventStarted)
            {
                uint32 currentHour = time(nullptr) / HOUR;
                if(isEventActive() && currentHour != lastHourDone)
                {
                    Reset();
                    eventStarted = true;
                    lastHourDone = currentHour;
                }
                
                return;
            }
    
            currentTime += diff;
    
            for (auto it1 = eventMap.cbegin(), it2 = it1, end = eventMap.cend(); it1 != end; it1 = it2)
            {
                //not yet time
                if(currentTime < it1->first)
                    break;
    
                // skip if already done
                if(lastEventTime >= it1->first) 
                {
                    it2++;
                    continue;
                }
                
                lastEventTime = it1->first;
                do
                {
                    ExecEvent(it2->second);
                    ++it2;
                } while (it2->first == it1->first);
            }
    
            if(currentTime > endTime)
                eventStarted = false;
        }
    
        bool isEventActive()
        {
            const GameEventMgr::ActiveEvents& activeEvents = sGameEventMgr->GetActiveEventList();
            bool active = activeEvents.find(6) != activeEvents.end();
    
            return active;
        }

        virtual bool GossipHello(Player* player) override
        {
            
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "(Re)start event", GOSSIP_SENDER_MAIN, GOSSIP_START);
            player->ADD_GOSSIP_ITEM_EXTENDED( 0, "Change Event", GOSSIP_SENDER_MAIN, GOSSIP_SELECT_EVENT, "", 0, true);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Reload event", GOSSIP_SENDER_MAIN, GOSSIP_RELOAD);
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Preload spells", GOSSIP_SENDER_MAIN, GOSSIP_PRELOAD);
                
            player->SEND_GOSSIP_MENU_TEXTID(3,me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch (action)
            {
            case GOSSIP_START:
                Reset();
                eventStarted = true;
                break;
            case GOSSIP_RELOAD:
                Reset();
                SetupEvent();
                break;
            case GOSSIP_PRELOAD:
                Preload();
                break;
            }
            player->CLOSE_GOSSIP_MENU();
            return true;

        }


        virtual bool GossipSelectCode(Player* player, uint32 sender, uint32 gossipListId, const char* Code) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if(action == GOSSIP_SELECT_EVENT)
            {
                uint8 event = (uint8)atoi(Code);
                eventId = event;
                SetupEvent();
            }
            
            player->CLOSE_GOSSIP_MENU();

            return true;

        }


        virtual void ReceiveEmote(Player* p, uint32 emote) override
        {
            if(!p->IsGameMaster())
                return;

            switch(emote)
            {
            case TEXTEMOTE_HUG:
                Reset();
                SetupEvent();
                break;
            case TEXTEMOTE_KISS:
                Reset();
                eventStarted = true;
                break;
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new firework_controllerAI(creature);
    }
};

void AddSC_firework_controller()
{

    new npc_firework_controller();
}
