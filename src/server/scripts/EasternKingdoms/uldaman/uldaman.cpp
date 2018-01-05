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
SDName: Uldaman
SD%Complete: 100
SDComment: Quest support: 2240, 2278 + 1 trash mob
SDCategory: Uldaman
EndScriptData */

/* ContentData
mob_jadespine_basilisk
npc_lore_keeper_of_norgannon
go_keystone_chamber
at_map_chamber
EndContentData */


#include "def_uldaman.h"

#define QUEST_HIDDEN_CHAMBER 2240



/*######
## mob_jadespine_basilisk
######*/

#define SPELL_CSLUMBER        3636


class mob_jadespine_basilisk : public CreatureScript
{
public:
    mob_jadespine_basilisk() : CreatureScript("mob_jadespine_basilisk")
    { }

    class mob_jadespine_basiliskAI : public ScriptedAI
    {
        public:
        mob_jadespine_basiliskAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 Cslumber_Timer;
    
        void Reset()
        override {
            Cslumber_Timer = 2000;
        }
    
        void JustEngagedWith(Unit *who)
        override {
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Return since we have no target
            if (!UpdateVictim())
                return;
    
            //Cslumber_Timer
            if (Cslumber_Timer < diff)
            {
                //Cast
                // DoCast(me->GetVictim(),SPELL_CSLUMBER);
                me->CastSpell(me->GetVictim(),SPELL_CSLUMBER, TRIGGERED_FULL_MASK);
                me->GetThreatManager().ResetThreat(me->EnsureVictim());
    
                //Stop attacking target thast asleep and pick new target
                Cslumber_Timer = 28000;

    
            }else Cslumber_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_jadespine_basiliskAI(creature);
    }
};


/*######
## npc_lore_keeper_of_norgannon
######*/

class npc_lore_keeper_of_norgannon : public CreatureScript
{
public:
    npc_lore_keeper_of_norgannon() : CreatureScript("npc_lore_keeper_of_norgannon")
    { }

    class npc_lore_keeper_of_norgannonAI : public ScriptedAI
    {
    public:
        npc_lore_keeper_of_norgannonAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (player->GetQuestStatus(2278) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Who are the Earthen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            player->SEND_GOSSIP_MENU_TEXTID(1079, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "What is a \"subterranean being matrix\"?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU_TEXTID(1080, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "What are the anomalies you speak of?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                    player->SEND_GOSSIP_MENU_TEXTID(1081, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "What is a resilient foundation of construction?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                    player->SEND_GOSSIP_MENU_TEXTID(1082, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+4:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "So... the Earthen were made out of stone?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    player->SEND_GOSSIP_MENU_TEXTID(1083, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+5:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Anything else I should know about the Earthen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                    player->SEND_GOSSIP_MENU_TEXTID(1084, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+6:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I think I understand the Creators' design intent for the Earthen now. What are the Earthen's anomalies that you spoke of earlier?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                    player->SEND_GOSSIP_MENU_TEXTID(1085, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+7:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "What high-stress environments would cause the Earthen to destabilize?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
                    player->SEND_GOSSIP_MENU_TEXTID(1086, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+8:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "What happens when the Earthen destabilize?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
                    player->SEND_GOSSIP_MENU_TEXTID(1087, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+9:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Troggs?! Are the troggs you mention the same as the ones in the world today?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
                    player->SEND_GOSSIP_MENU_TEXTID(1088, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+10:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "You mentioned two results when the Earthen destabilize. What is the second?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
                    player->SEND_GOSSIP_MENU_TEXTID(1089, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+11:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Dwarves!!! Now you're telling me that dwarves originally came from the Earthen?!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12);
                    player->SEND_GOSSIP_MENU_TEXTID(1090, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+12:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "These dwarves are the same ones today, yes? Do the dwarves maintain any other links to the Earthen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
                    player->SEND_GOSSIP_MENU_TEXTID(1091, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+13:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Who are the Creators?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14);
                    player->SEND_GOSSIP_MENU_TEXTID(1092, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+14:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "This is a lot to think about.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
                    player->SEND_GOSSIP_MENU_TEXTID(1093, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+15:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I will access the discs now.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+16);
                    player->SEND_GOSSIP_MENU_TEXTID(1094, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+16:
                    player->CLOSE_GOSSIP_MENU();
                    player->AreaExploredOrEventHappens(2278);
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lore_keeper_of_norgannonAI(creature);
    }
};



class KeystoneChamber : public GameObjectScript
{
public:
    KeystoneChamber() : GameObjectScript("go_keystone_chamber")
    {}

    struct KeystoneChamberAI : public GameObjectAI
    {
        KeystoneChamberAI(GameObject* obj) : GameObjectAI(obj), pInstance(obj->GetInstanceScript()) { }

        InstanceScript* pInstance;

        bool GossipHello(Player* player) override
        {
            if (!pInstance)
                return false;

            if (pInstance)
                pInstance->SetData(DATA_IRONAYA_SEAL, IN_PROGRESS); //door animation and save state.

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new KeystoneChamberAI(go);
    }
};

class ATMapChamber : AreaTriggerScript
{
public:
    ATMapChamber() : AreaTriggerScript("at_map_chamber") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (pPlayer && (pPlayer->ToPlayer())->GetQuestStatus(QUEST_HIDDEN_CHAMBER) == QUEST_STATUS_INCOMPLETE)
            pPlayer->AreaExploredOrEventHappens(QUEST_HIDDEN_CHAMBER);

        return true;
    }
};

void AddSC_uldaman()
{

    new mob_jadespine_basilisk();

    new npc_lore_keeper_of_norgannon();
    
    new KeystoneChamber();
    new ATMapChamber();
}

