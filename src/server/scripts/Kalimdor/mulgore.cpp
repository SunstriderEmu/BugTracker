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
SDName: Mulgore
SD%Complete: 100
SDComment: Support for quest: 11129, 772
SDCategory: Mulgore
EndScriptData */

/* ContentData
npc_skorn_whitecloud
npc_kyle_frenzied
npc_plains_vision
EndContentData */


#include "EscortAI.h"

/*######
# npc_skorn_whitecloud
######*/

#define GOSSIP_SW "Tell me a story, Skorn."

class npc_skorn_whitecloud : public CreatureScript
{
public:
    npc_skorn_whitecloud() : CreatureScript("npc_skorn_whitecloud")
    { }

    class npc_skorn_whitecloudAI : public ScriptedAI
    {
    public:
        npc_skorn_whitecloudAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (!pPlayer->GetQuestRewardStatus(770))
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SW, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(522, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            if (action == GOSSIP_ACTION_INFO_DEF)
                pPlayer->SEND_GOSSIP_MENU_TEXTID(523, me->GetGUID());

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_skorn_whitecloudAI(creature);
    }
};



/*#####
# npc_kyle_frenzied
######*/


class npc_kyle_frenzied : public CreatureScript
{
public:
    npc_kyle_frenzied() : CreatureScript("npc_kyle_frenzied")
    { }

    class npc_kyle_frenziedAI : public ScriptedAI
    {
        public:
        npc_kyle_frenziedAI(Creature *c) : ScriptedAI(c) {}
    
        int STATE;
        uint32 wait;
        uint64 player;
    
        void Reset()
        override {
            STATE = 0;
            me->SetDefaultMovementType(WAYPOINT_MOTION_TYPE);
            me->GetMotionMaster()->Initialize();
        }
        void EnterCombat(Unit* pWho) override {}
    
        void SpellHit(Unit* pCaster, const SpellInfo* spell)
        override {   // we can feed him without any quest
            if(spell->Id == 42222 && pCaster->GetTypeId() == TYPEID_PLAYER && (pCaster)->ToPlayer()->GetTeam() == HORDE)
            {
                STATE = 1;
                player = pCaster->GetGUID();
                float x, y, z, z2;
                pCaster->GetPosition(x, y, z);
                x = x + 3.7*cos(pCaster->GetOrientation());
                y = y + 3.7*sin(pCaster->GetOrientation());
                z2 = me->GetBaseMap()->GetHeight(x, y, z, false);
                z = (z2 <= INVALID_HEIGHT) ? z : z2;
                me->SetDefaultMovementType(IDLE_MOTION_TYPE);       //there is other way to stop waypoint movement?
                me->GetMotionMaster()->Initialize();
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                me->GetMotionMaster()->MovePoint(0, x, y, z);
            }
        }
    
        void MovementInform(uint32 type, uint32 id)
        override {
            if(type == POINT_MOTION_TYPE)
            {
                switch(STATE)
                {
                case 1:
                    {
                    Unit *plr = ObjectAccessor::GetUnit((*me),player);
                    if(plr)
                        me->SetOrientation(me->GetAngle(plr));
                    me->HandleEmoteCommand(EMOTE_STATE_USESTANDING);    //eat
                    WorldPacket data;
                    me->BuildHeartBeatMsg(&data);
                    me->SendMessageToSet(&data,true);
                    wait = 3000;
                    STATE = 2;
                    break;
                    }
                case 4:
                    me->SetDeathState(JUST_DIED);
                    me->Respawn();
                    break;
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!STATE || STATE == 4)
                return;
            if (wait < diff)
            {
                switch(STATE)
                {
                case 2:
                    STATE = 3; wait = 7000;
                    me->UpdateEntry(23622);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_DANCE);
                    break;
                case 3:
                    STATE = 4;  //go home
                    Player *plr = ObjectAccessor::GetPlayer(*me, player);
                    if(plr && plr->GetQuestStatus(11129) == QUEST_STATUS_INCOMPLETE)
                        plr->CompleteQuest(11129);
                    float x, y, z, z2, angle;
                    angle = me->GetAngle(-2146, -430);
                    me->GetPosition(x,y,z);
                    x = x + 40*cos(angle);
                    y = y + 40*sin(angle);
                    z2 = me->GetBaseMap()->GetHeight(x,y,MAX_HEIGHT,false);
                    z = (z2 <= INVALID_HEIGHT) ? z : z2;
                    me->GetMotionMaster()->MovePoint(0,x,y,z);
                    break;
                }
            } else wait -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kyle_frenziedAI(creature);
    }
};


/*#####
# npc_plains_vision
######*/

float wp_plain_vision[50][3] =
{
    { -2226.32f,  -408.09f,   -9.36235f },
    { -2203.04f,  -437.21f,   -5.72498f },
    { -2163.91f,  -457.85f,   -7.09049f },
    { -2123.87f,  -448.14f,   -9.29591f },
    { -2104.66f,  -427.17f,   -6.49513f },
    { -2101.48f,  -422.83f,   -5.35670f },
    { -2097.56f,  -417.08f,   -7.16716f },
    { -2084.87f,  -398.63f,   -9.88973f },
    { -2072.71f,  -382.32f,   -10.2488f },
    { -2054.05f,  -356.73f,   -6.22468f },
    { -2051.80f,  -353.65f,   -5.35791f },
    { -2049.08f,  -349.91f,   -6.15723f },
    { -2030.60f - 310.72f,   -9.59302f },
    { -2002.15f,  -249.31f,   -10.8124f },
    { -1972.85f,  -195.81f,   -10.6316f },
    { -1940.93f,  -147.65f,   -11.7055f },
    { -1888.06f,  -81.943f,   -11.4404f },
    { -1837.05f,  -34.011f,   -12.2580f },
    { -1796.12f,  -14.646f,   -10.3581f },
    { -1732.61f,  -4.2775f,   -10.0213f },
    { -1688.94f,  -0.8299f,   -11.7103f },
    { -1681.32f,  13.0313f,   -9.48056f },
    { -1677.04f,  36.8349f,   -7.10318f },
    { -1675.20f,  68.5590f,   -8.95384f },
    { -1676.57f,  89.0230f,   -9.65104f },
    { -1678.16f,  110.939f,   -10.1782f },
    { -1677.86f,  128.681f,   -5.73869f },
    { -1675.27f,  144.324f,   -3.47916f },
    { -1671.70f,  163.169f,   -1.23098f },
    { -1666.61f,  181.584f,    5.26145f },
    { -1661.51f,  196.154f,    8.95252f },
    { -1655.47f,  210.811f,    8.38727f },
    { -1647.07f,  226.947f,    5.27755f },
    { -1621.65f,  232.910f,    2.69579f },
    { -1600.23f,  237.641f,    2.98539f },
    { -1576.07f,  242.546f,    4.66541f },
    { -1554.57f,  248.494f,    6.60377f },
    { -1547.53f,  259.302f,    10.6741f },
    { -1541.70f,  269.847f,    16.4418f },
    { -1539.83f,  278.989f,    21.0597f },
    { -1540.16f,  290.219f,    27.8247f },
    { -1538.99f,  298.983f,    34.0032f },
    { -1540.38f,  307.337f,    41.3557f },
    { -1536.61f,  314.884f,    48.0179f },
    { -1532.42f,  323.277f,    55.6667f },
    { -1528.77f,  329.774f,    61.1525f },
    { -1525.65f,  333.180f,    63.2161f },
    { -1517.01f,  350.713f,    62.4286f },
    { -1511.39f,  362.537f,    62.4539f },
    { -1508.68f,  366.822f,    62.7330f },
};

struct npc_plains_visionAI  : public ScriptedAI
{

    bool newWaypoint;
    uint8 WayPointId;
    uint8 amountWP;
    uint32 despawnTimer;

    void Reset()
    override {
        WayPointId = 0;
        newWaypoint = true;
        amountWP  = 49;
    }

    void EnterCombat(Unit* pWho) override {}

    void MovementInform(uint32 type, uint32 id)
    override {
        if(type != POINT_MOTION_TYPE)
            return;

        if (id < amountWP)
        {
            ++WayPointId;
            newWaypoint = true;
        }
        else
        {
            me->DespawnOrUnsummon();
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if (despawnTimer <= diff) {
            me->DisappearAndDie();
        }
        else
            despawnTimer -= diff;

        if (newWaypoint)
        {
            me->GetMotionMaster()->MovePoint(WayPointId, wp_plain_vision[WayPointId][0], wp_plain_vision[WayPointId][1], wp_plain_vision[WayPointId][2]);
            newWaypoint = false;
        }
    }
};

class npc_plains_vision : public CreatureScript
{
public:
    npc_plains_vision() : CreatureScript("npc_plains_vision")
    { }

    class npc_plains_visionAI  : public ScriptedAI
    {
        public:
        npc_plains_visionAI(Creature *c) : ScriptedAI(c)
        {
            despawnTimer = 900000;
        }
    
        bool newWaypoint;
        uint8 WayPointId;
        uint8 amountWP;
        uint32 despawnTimer;
    
        void Reset()
        override {
            WayPointId = 0;
            newWaypoint = true;
            amountWP  = 49;
        }
    
        void EnterCombat(Unit* pWho) override {}
    
        void MovementInform(uint32 type, uint32 id)
        override {
            if(type != POINT_MOTION_TYPE)
                return;
    
            if (id < amountWP)
            {
                ++WayPointId;
                newWaypoint = true;
            }
            else
            {
                me->DespawnOrUnsummon();
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (despawnTimer <= diff) {
                me->DisappearAndDie();
            }
            else
                despawnTimer -= diff;
    
            if (newWaypoint)
            {
                me->GetMotionMaster()->MovePoint(WayPointId, wp_plain_vision[WayPointId][0], wp_plain_vision[WayPointId][1], wp_plain_vision[WayPointId][2]);
                newWaypoint = false;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_plains_visionAI(creature);
    }
};


/*#####
#
######*/

void AddSC_mulgore()
{

    new npc_skorn_whitecloud();

    new npc_kyle_frenzied();

    new npc_plains_vision();
}

