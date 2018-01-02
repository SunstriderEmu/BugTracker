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
SDName: Western_Plaguelands
SD%Complete: 90
SDComment: Quest support: 5097, 5098, 5216, 5219, 5222, 5225, 5229, 5231, 5233, 5235. To obtain Vitreous Focuser (could use more spesifics about gossip items)
SDCategory: Western Plaguelands
EndScriptData */

/* ContentData
npcs_dithers_and_arbington
npc_the_scourge_cauldron
npc_myranda_the_hag
npcs_andorhal_tower
EndContentData */



/*######
## npcs_dithers_and_arbington
######*/

#define GOSSIP_HDA1 "What does the Felstone Field Cauldron need?"
#define GOSSIP_HDA2 "What does the Dalson's Tears Cauldron need?"
#define GOSSIP_HDA3 "What does the Writhing Haunt Cauldron need?"
#define GOSSIP_HDA4 "What does the Gahrron's Withering Cauldron need?"

#define GOSSIP_SDA1 "Thanks, i need a Vitreous Focuser"

class npcs_dithers_and_arbington : public CreatureScript
{
public:
    npcs_dithers_and_arbington() : CreatureScript("npcs_dithers_and_arbington")
    { }

    class npcs_dithers_and_arbingtonAI : public ScriptedAI
    {
    public:
        npcs_dithers_and_arbingtonAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if(me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );
            if (me->IsVendor())
                player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

            if(player->GetQuestRewardStatus(5237) || player->GetQuestRewardStatus(5238))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HDA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HDA2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HDA3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HDA4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                player->SEND_GOSSIP_MENU_TEXTID(3985, me->GetGUID());
            }else
                SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch(action)
            {
                case GOSSIP_ACTION_TRADE:
                    player->SEND_VENDORLIST( me->GetGUID() );
                    break;
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SDA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    player->SEND_GOSSIP_MENU_TEXTID(3980, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SDA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    player->SEND_GOSSIP_MENU_TEXTID(3981, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SDA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    player->SEND_GOSSIP_MENU_TEXTID(3982, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+4:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SDA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                    player->SEND_GOSSIP_MENU_TEXTID(3983, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+5:
                    player->CLOSE_GOSSIP_MENU();
                    me->CastSpell(player, 17529, TRIGGERED_NONE);
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npcs_dithers_and_arbingtonAI(creature);
    }
};



/*######
## npc_the_scourge_cauldron
######*/

class npc_the_scourge_cauldron : public CreatureScript
{
public:
    npc_the_scourge_cauldron() : CreatureScript("npc_the_scourge_cauldron")
    { }

    class npc_the_scourge_cauldronAI : public ScriptedAI
    {
        public:
        npc_the_scourge_cauldronAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset() override {}
    
        void JustEngagedWith(Unit* who) override {}
    
        void DoDie()
        {
            //summoner dies here
            me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
            //override any database `spawntimesecs` to prevent duplicated summons
            uint32 rTime = me->GetRespawnDelay();
            if( rTime<600 )
                me->SetRespawnDelay(600);
        }
    
        void MoveInLineOfSight(Unit *who)
        override {
            if (!who || who->GetTypeId() != TYPEID_PLAYER)
                return;
    
            if(who->GetTypeId() == TYPEID_PLAYER)
            {
                switch(me->GetAreaId())
                {
                    case 199:                                   //felstone
                        if( (who->ToPlayer())->GetQuestStatus(5216) == QUEST_STATUS_INCOMPLETE ||
                            (who->ToPlayer())->GetQuestStatus(5229) == QUEST_STATUS_INCOMPLETE )
                        {
                            DoSpawnCreature(11075,0,0,0,me->GetOrientation(),TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000);
                            DoDie();
                        }
                        break;
                    case 200:                                   //dalson
                        if( (who->ToPlayer())->GetQuestStatus(5219) == QUEST_STATUS_INCOMPLETE ||
                            (who->ToPlayer())->GetQuestStatus(5231) == QUEST_STATUS_INCOMPLETE )
                        {
                            DoSpawnCreature(11077,0,0,0,me->GetOrientation(),TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000);
                            DoDie();
                        }
                        break;
                    case 201:                                   //gahrron
                        if( (who->ToPlayer())->GetQuestStatus(5225) == QUEST_STATUS_INCOMPLETE ||
                            (who->ToPlayer())->GetQuestStatus(5235) == QUEST_STATUS_INCOMPLETE )
                        {
                            DoSpawnCreature(11078,0,0,0,me->GetOrientation(),TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000);
                            DoDie();
                        }
                        break;
                    case 202:                                   //writhing
                        if( (who->ToPlayer())->GetQuestStatus(5222) == QUEST_STATUS_INCOMPLETE ||
                            (who->ToPlayer())->GetQuestStatus(5233) == QUEST_STATUS_INCOMPLETE )
                        {
                            DoSpawnCreature(11076,0,0,0,me->GetOrientation(),TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,600000);
                            DoDie();
                        }
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_the_scourge_cauldronAI(creature);
    }
};


/*##########
#npcs_andorhal_tower
##########*/

enum eAndorhalTower
{
    GO_BEACON_TORCH                             = 176093
};


class npc_andorhal_tower : public CreatureScript
{
public:
    npc_andorhal_tower() : CreatureScript("npc_andorhal_tower")
    { }

    class npc_andorhal_towerAI : public ScriptedAI
    {
        public:
        npc_andorhal_towerAI(Creature *c) : ScriptedAI(c) 
        {
            SetCombatMovementAllowed(false);
        }
        
        void JustEngagedWith(Unit *pWho) override {}
    
        void MoveInLineOfSight(Unit* pWho)
        override {
            if (!pWho || pWho->GetTypeId() != TYPEID_PLAYER)
                return;
    
            if (me->FindNearestGameObject(GO_BEACON_TORCH, 10.0f))
                (pWho)->ToPlayer()->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
            
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_andorhal_towerAI(creature);
    }
};


/*######
## npc_myranda_the_hag
######*/

enum eMyranda
{
    QUEST_SUBTERFUGE        = 5862,
    QUEST_IN_DREAMS         = 5944,
    SPELL_SCARLET_ILLUSION  = 17961
};

#define GOSSIP_ITEM_ILLUSION    "I am ready for the illusion, Myranda."

class npc_myranda_the_hag : public CreatureScript
{
public:
    npc_myranda_the_hag() : CreatureScript("npc_myranda_the_hag")
    { }

    class npc_myranda_the_hagAI : public ScriptedAI
    {
    public:
        npc_myranda_the_hagAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (pPlayer->GetQuestStatus(QUEST_SUBTERFUGE) == QUEST_STATUS_COMPLETE &&
                !pPlayer->GetQuestRewardStatus(QUEST_IN_DREAMS) && !pPlayer->HasAuraEffect(SPELL_SCARLET_ILLUSION, 0))
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ILLUSION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(4773, me->GetGUID());
                return true;
            }
            else
                SEND_PREPARED_GOSSIP_MENU(pPlayer, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, SPELL_SCARLET_ILLUSION, TRIGGERED_NONE);
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_myranda_the_hagAI(creature);
    }
};



/*######
## AddSC
######*/

void AddSC_western_plaguelands()
{

    new npcs_dithers_and_arbington();

    new npc_the_scourge_cauldron();
    
    new npc_andorhal_tower();
    
    new npc_myranda_the_hag();
}
