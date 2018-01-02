/* Copyright (C) 2009 - 2010 WoWMania Core
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
SDName: Dire_Maul
SD%Complete: 0
SDComment: 
SDCategory: Dire_Maul
EndScriptData */


#include "def_dire_maul.h"

/*######
## npc_ironbark_redeemed
######*/


class npc_ironbark_redeemed : public CreatureScript
{
public:
    npc_ironbark_redeemed() : CreatureScript("npc_ironbark_redeemed")
    { }

    class npc_ironbark_redeemedAI : public ScriptedAI
    {
        public:
        npc_ironbark_redeemedAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        InstanceScript *pInstance;
        
        void Reset() override {}
        void JustEngagedWith(Unit *pWho) override {}
        
        void MovementInform(uint32 type, uint32 id)
        override {
            if (id == 2) {
                if (pInstance) {
                    if (GameObject *pIronbarkDoor = me->FindNearestGameObject(179549, 20.0f)) {
                        pIronbarkDoor->SwitchDoorOrButton(true);
                        me->Kill(me);
                    }
                }
            }
        }

        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pInstance) {
                if (pInstance->GetData(DATA_ZEVRIM_THORNHOOF) == DONE) {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[PH] Ouvre la porte !", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                    pPlayer->SEND_GOSSIP_MENU_TEXTID(2601, me->GetGUID());
                    return true;
                }
            }
            return false;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF) {
                player->CLOSE_GOSSIP_MENU();
                me->SetSpeedRate(MOVE_WALK, 3);
                me->GetMotionMaster()->MovePath(14241); //this path is PATH_TYPE_ONCE
                return true;
            }
            return false;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ironbark_redeemedAI(creature);
    }
};




void AddSC_dire_maul()
{
    
    new npc_ironbark_redeemed();
}
