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
SDName: Zulfarrak
SD%Complete: 50
SDComment: Consider it temporary, no instance script made for this instance yet.
SDCategory: Zul'Farrak
EndScriptData */

/* ContentData
npc_sergeant_bly
npc_weegli_blastfuse
at_zumrah
at_antusul
go_shallow_grave
go_troll_cage
EndContentData */


#include "def_zulfarrak.h"

/*######
## npc_sergeant_bly
######*/

enum blyAndCrewFactions {
    FACTION_HOSTILE         = 14,
    FACTION_FREED           = 250       // After release (so they'll be hostile towards trolls)
};

enum weegliActionParam {
    BLY_INITIATED = 1,
    PLAYER_INITIATED = 2
};

enum blySays {
    SAY_1 = -1209002,
    SAY_2 = -1209003
};

enum blySpells {
    SPELL_SHIELD_BASH          = 11972,
    SPELL_REVENGE              = 12170
};

#define GOSSIP_BLY_RESTART_EVENT    "Repartons au combat !"
#define GOSSIP_BLY                  "C'en est assez ! Je n'en peux plus de vous aider. Il est temps de régler nos comptes par les armes !"

enum blyGossips {
    BLY_GOSSIP_CAGED = 1515,
    BLY_GOSSIP_FIGHTING = 1516,
    BLY_GOSSIP_DONE = 1517
};

class npc_sergeant_bly : public CreatureScript
{
public:
    npc_sergeant_bly() : CreatureScript("npc_sergeant_bly")
    { }

    class npc_sergeant_blyAI : public ScriptedAI
    {
        public:
        npc_sergeant_blyAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            postGossipStep = 0;
        }
    
        InstanceScript* pInstance;
        uint32 postGossipStep;
        uint32 Text_Timer;
    
        uint32 ShieldBash_Timer;
        uint32 Revenge_Timer;                                   //this is wrong, spell should never be used unless me->GetVictim() dodge, parry or block attack. Trinity support required.
    
        uint64 gossipPlayerGUID;
    
        void Reset()
        override {
            ShieldBash_Timer = 5000;
            Revenge_Timer = 8000;
    
            me->SetFaction(FACTION_FRIENDLY);
        }
    
        void EnterCombat(Unit *who) override {}
    
        void JustDied(Unit *victim) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if (postGossipStep > 0 && postGossipStep < 4) {
                if (Text_Timer <= diff) {
                    switch (postGossipStep)
                    {
                    case 1:
                        //weegli doesn't fight - he goes & blows up the door
                        if (pInstance)
                        {
                            if (Creature* weegli = pInstance->instance->GetCreature(pInstance->GetData64(ENTRY_WEEGLI))) {
                                weegli->AI()->DoAction(BLY_INITIATED);
                            }
                        }
                        DoScriptText(SAY_1,me);
                        Text_Timer = 5000;
                        break;
                    case 2:
                        DoScriptText(SAY_2,me);
                        Text_Timer = 5000;
                        break;
                    case 3:
                        switchFactionIfAlive(ENTRY_BLY);
                        switchFactionIfAlive(ENTRY_RAVEN);
                        switchFactionIfAlive(ENTRY_ORO);
                        switchFactionIfAlive(ENTRY_MURTA);
                        break;
                    }
                    postGossipStep++;
                } else Text_Timer -= diff;
            }
    
            if( !UpdateVictim() )
                return;
    
            if( ShieldBash_Timer < diff )
            {
                DoCast(me->GetVictim(),SPELL_SHIELD_BASH);
                ShieldBash_Timer = 15000;
            }else ShieldBash_Timer -= diff;
    
            if( Revenge_Timer < diff )
            {
                DoCast(me->GetVictim(),SPELL_REVENGE);
                Revenge_Timer = 10000;
            }else Revenge_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
        
        void DoAction(const int32 param) override {
            postGossipStep=1;
            Text_Timer = 0;
        }
        
        void switchFactionIfAlive(uint32 entry) {
            if (!pInstance)
                 return;
    
           if (Creature* crew = pInstance->instance->GetCreature(pInstance->GetData64(entry))) {
               if (crew->IsAlive()) {
                    crew->SetFaction(FACTION_HOSTILE);
                    crew->SetHealth(crew->GetMaxHealth());
                    if (Player* target = ObjectAccessor::GetPlayer(*me, gossipPlayerGUID)) {
                        crew->AI()->AttackStart(target);
                    }
               }
           }
        }

        virtual bool GossipHello(Player* player) override
        {
            if (pInstance) {
                if (pInstance->GetData(EVENT_PYRAMID) == PYRAMID_KILLED_ALL_TROLLS) {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BLY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                    player->SEND_GOSSIP_MENU_TEXTID(BLY_GOSSIP_DONE, me->GetGUID());
                }
                else if (pInstance->GetData(EVENT_PYRAMID) == PYRAMID_NOT_STARTED)
                    player->SEND_GOSSIP_MENU_TEXTID(BLY_GOSSIP_CAGED, me->GetGUID());
                else
                    player->SEND_GOSSIP_MENU_TEXTID(BLY_GOSSIP_FIGHTING, me->GetGUID());
                return true;
            }
            return false;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1) {
                CAST_AI(npc_sergeant_bly::npc_sergeant_blyAI,me->AI())->gossipPlayerGUID = player->GetGUID();
                CAST_AI(npc_sergeant_bly::npc_sergeant_blyAI,me->AI())->DoAction(0);
            }
            else if (action == GOSSIP_ACTION_INFO_DEF+2) {
                CAST_AI(npc_sergeant_bly::npc_sergeant_blyAI,me->AI())->gossipPlayerGUID = player->GetGUID();
                CAST_AI(npc_sergeant_bly::npc_sergeant_blyAI,me->AI())->DoAction(0);
            }

            player->CLOSE_GOSSIP_MENU();
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sergeant_blyAI(creature);
    }
};


void initBlyCrewMember(Player* pPlayer, uint32 entry,float x,float y, float z)
{
    if (Creature* crew = pPlayer->FindNearestCreature(entry, 10.0f, true)) {
        crew->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
        crew->SetReactState(REACT_AGGRESSIVE);
        crew->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
        crew->SetHomePosition(x,y,z,0);
        crew->GetMotionMaster()->MovePoint(1,x,y,z);
        crew->SetFaction(FACTION_FREED);
    }
}

class TrollCage : public GameObjectScript
{
public:
    TrollCage() : GameObjectScript("go_troll_cage")
    {}

    struct TrollCageAI : public GameObjectAI
    {
        TrollCageAI(GameObject* obj) : GameObjectAI(obj), pInstance(obj->GetInstanceScript()) { }

        InstanceScript* pInstance;

        bool GossipHello(Player* pPlayer) override
        {
            if (!pInstance)
                return false;

            pInstance->SetData(EVENT_PYRAMID, PYRAMID_CAGES_OPEN);
            //set bly & co to aggressive & start moving to top of stairs
            initBlyCrewMember(pPlayer, ENTRY_BLY, 1884.99, 1263, 41.52);
            initBlyCrewMember(pPlayer, ENTRY_RAVEN, 1882.5, 1263, 41.52);
            initBlyCrewMember(pPlayer, ENTRY_ORO, 1886.47, 1270.68, 41.68);
            initBlyCrewMember(pPlayer, ENTRY_WEEGLI, 1890, 1263, 41.52);
            initBlyCrewMember(pPlayer, ENTRY_MURTA, 1891.19, 1272.03, 41.60);
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new TrollCageAI(go);
    }
};

/*######
## npc_weegli_blastfuse
######*/

enum weegliSpells {
    SPELL_BOMB                 = 8858,
    SPELL_GOBLIN_LAND_MINE     = 21688,
    SPELL_SHOOT                = 6660,
    SPELL_WEEGLIS_BARREL       = 10772
};

enum weegliSays {
    SAY_WEEGLI_OHNO         = -1209000,
    SAY_WEEGLI_OK_I_GO      = -1209001,
    SAY_WEEGLI_OUT_OF_HERE  = -1209004
};

#define GOSSIP_WEEGLI               "[PH] Allez faire exploser la porte, s'il vous plait."

enum weegliGossips {
    WEEGLI_GOSSIP_CAGED = 1511,
    WEEGLI_GOSSIP_FIGHTING = 1513,
    WEEGLI_GOSSIP_DONE = 1514
};

class npc_weegli_blastfuse : public CreatureScript
{
public:
    npc_weegli_blastfuse() : CreatureScript("npc_weegli_blastfuse")
    { }

    class npc_weegli_blastfuseAI : public ScriptedAI
    {
        public:
        npc_weegli_blastfuseAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            destroyingDoor=false;
            Bomb_Timer = 10000;
            LandMine_Timer = 30000;
            
        }
    
        uint32 Bomb_Timer;
        uint32 LandMine_Timer;
        bool destroyingDoor;
        InstanceScript* pInstance;
    
        void Reset()
        override {
            /*if( pInstance )
                pInstance->SetData(0, NOT_STARTED);*/
        }
    
        void EnterCombat(Unit *who) override {}
    
        void JustDied(Unit *victim) override {}
        
        void MovementInform(uint32 type, uint32 id)
        override {
            if (pInstance) {
                if (pInstance->GetData(EVENT_PYRAMID) == PYRAMID_CAGES_OPEN) {
                    pInstance->SetData(EVENT_PYRAMID,PYRAMID_ARRIVED_AT_STAIR);
                    DoScriptText(SAY_WEEGLI_OHNO,me);
                    me->SetHomePosition(1882.69,1272.28,41.87,0);
                } else if (destroyingDoor) {
                    //pInstance->HandleGameObject(pInstance->GetData64(GO_END_DOOR), true, NULL);
                    //pInstance->SetData(DATA_OPEN_END_DOOR, DONE);
                    //if (GameObject* door = GameObject::GetGameObject(*me, pInstance->GetData64(GO_END_DOOR)))
                        //door->UseDoorOrButton();
                    if (GameObject* door = me->FindNearestGameObject(GO_END_DOOR, 50.0f))
                        door->UseDoorOrButton();
                    //TODO: leave the area...
                    me->ForcedDespawn();
                }
            }
        }
        
        void DoAction(const int32 param) override {
            DestroyDoor(param);
        }
        
        void DestroyDoor(int32 param) 
        {
            if (me->IsAlive()) {
                me->SetFaction(FACTION_FRIENDLY);
                me->GetMotionMaster()->MovePoint(0, 1858.57,1146.35,14.745);
                me->SetHomePosition(1858.57,1146.35,14.745,3.85); // in case he gets interrupted
                if (param == BLY_INITIATED) {
                    DoScriptText(SAY_WEEGLI_OUT_OF_HERE,me);
                } else {
                    DoScriptText(SAY_WEEGLI_OK_I_GO,me);
                }
                destroyingDoor=true;
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (Bomb_Timer < diff ) {
                DoCast(me->GetVictim(),SPELL_BOMB);
                Bomb_Timer = 10000;
            } else Bomb_Timer -= diff;
    
            if (me->IsAttackReady() && !me->IsWithinMeleeRange(me->GetVictim())) {
                DoCast(me->GetVictim(),SPELL_SHOOT);
                me->SetSheath(SHEATH_STATE_RANGED);
            } else {
                me->SetSheath(SHEATH_STATE_MELEE);
                DoMeleeAttackIfReady();
            }
        }

        virtual bool GossipHello(Player* player) override
        {
            if (pInstance) {
                switch (pInstance->GetData(EVENT_PYRAMID))
                {
                case PYRAMID_KILLED_ALL_TROLLS:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WEEGLI, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                    player->SEND_GOSSIP_MENU_TEXTID(WEEGLI_GOSSIP_DONE, me->GetGUID());  //if event can proceed to end
                    break;
                case PYRAMID_NOT_STARTED:
                    player->SEND_GOSSIP_MENU_TEXTID(WEEGLI_GOSSIP_CAGED, me->GetGUID());  //if event not started        
                    break;
                default:
                    player->SEND_GOSSIP_MENU_TEXTID(WEEGLI_GOSSIP_FIGHTING, me->GetGUID());  //if event are in progress
                }
                return true;
            }
            
            return false;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if( action == GOSSIP_ACTION_INFO_DEF+1 )
            {
                player->CLOSE_GOSSIP_MENU();
                //here we make him run to door, set the charge and run away off to nowhere
                me->AI()->DoAction(PLAYER_INITIATED);
            }

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_weegli_blastfuseAI(creature);
    }
};


class ATZumrah : AreaTriggerScript
{
public:
    ATZumrah() : AreaTriggerScript("at_zumrah") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (Creature *pZumrah = pPlayer->FindNearestCreature(7271, 15.0f, true)) {
            pZumrah->SetFaction(FACTION_MONSTER);
            pZumrah->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            pZumrah->AI()->AttackStart(pPlayer);
        }

        return true;
    }
};

class ATAntusul : AreaTriggerScript
{
public:
    ATAntusul() : AreaTriggerScript("at_antusul") {}

    bool OnTrigger(Player *player, AreaTriggerEntry const *at) override
    {
        if (Creature* antusul = player->FindNearestCreature(8127, 70.0f, true))
            antusul->AI()->AttackStart(player);

        return true;
    }
};

class ShallowGrave : public GameObjectScript
{
public:
    ShallowGrave() : GameObjectScript("go_shallow_grave")
    {}

    enum {
        ZOMBIE = 7286,
        DEAD_HERO = 7276,
        ZOMBIE_CHANCE = 65,
        DEAD_HERO_CHANCE = 10
    };

    struct ShallowGraveAI : public GameObjectAI
    {
        ShallowGraveAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (me->GetUseCount() == 0) {
                uint32 randomchance = urand(0, 100);
                if (randomchance < ZOMBIE_CHANCE)
                    me->SummonCreature(ZOMBIE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                else if ((randomchance - ZOMBIE_CHANCE) < DEAD_HERO_CHANCE)
                    me->SummonCreature(DEAD_HERO, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
            }
            me->AddUse();
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ShallowGraveAI(go);
    }
};

void AddSC_zulfarrak()
{

    new npc_sergeant_bly();

    new npc_weegli_blastfuse();
    
    new ATZumrah();
    new ATAntusul();
    new ShallowGrave();
    new TrollCage();
}

