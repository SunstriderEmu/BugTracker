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
SDName: Stonetalon_Mountains
SD%Complete: 95
SDComment: Quest support: 6627, 6523
SDCategory: Stonetalon Mountains
EndScriptData */

/* ContentData
npc_braug_dimspirit
npc_kaya_flathoof
EndContentData */


#include "EscortAI.h"

/*######
## npc_braug_dimspirit
######*/

#define GOSSIP_HBD1 "Ysera"
#define GOSSIP_HBD2 "Neltharion"
#define GOSSIP_HBD3 "Nozdormu"
#define GOSSIP_HBD4 "Alexstrasza"
#define GOSSIP_HBD5 "Malygos"

class npc_braug_dimspirit : public CreatureScript
{
public:
    npc_braug_dimspirit() : CreatureScript("npc_braug_dimspirit")
    { }

    class npc_braug_dimspiritAI : public ScriptedAI
    {
    public:
        npc_braug_dimspiritAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if (player->GetQuestStatus(6627) == QUEST_STATUS_INCOMPLETE)
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HBD5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

                player->SEND_GOSSIP_MENU_TEXTID(5820, me->GetGUID());
            }
            else
                player->SEND_GOSSIP_MENU_TEXTID(5819, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                player->CLOSE_GOSSIP_MENU();
                me->CastSpell(player,6766,false);

            }
            if (action == GOSSIP_ACTION_INFO_DEF+2)
            {
                player->CLOSE_GOSSIP_MENU();
                player->AreaExploredOrEventHappens(6627);
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_braug_dimspiritAI(creature);
    }
};



/*######
## npc_kaya_flathoof
######*/

#define SAY_START   -1000347
#define SAY_AMBUSH  -1000348
#define SAY_END     -1000349

#define QUEST_PK    6523
#define MOB_GB      11912
#define MOB_GR      11910
#define MOB_GS      11913


class npc_kaya_flathoof : public CreatureScript
{
public:
    npc_kaya_flathoof() : CreatureScript("npc_kaya_flathoof")
    { }

    class npc_kaya_flathoofAI : public npc_escortAI
    {
        public:
        npc_kaya_flathoofAI(Creature* c) : npc_escortAI(c) {}
    
        void WaypointReached(uint32 i)
        override {
            Player* player = GetPlayerForEscort();
    
            if(!player)
                return;
    
            switch(i)
            {
            case 16:
                DoScriptText(SAY_AMBUSH, me);
                me->SummonCreature(MOB_GB, -48.53, -503.34, -46.31, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                me->SummonCreature(MOB_GR, -38.85, -503.77, -45.90, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                me->SummonCreature(MOB_GS, -36.37, -496.23, -45.71, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                break;
            case 18: me->SetInFront(player);
                DoScriptText(SAY_END, me, player);
                player->GroupEventHappens(QUEST_PK, me);
                break;
            }
        }
    
        void JustSummoned(Creature* summoned)
        override {
            summoned->AI()->AttackStart(me);
        }
    
        void Reset()override {}
    
        void EnterCombat(Unit* who)override {}
    
        void JustDied(Unit* killer)
        override {
            if (PlayerGUID)
            {
                Player* player = GetPlayerForEscort();
                if (player)
                    player->FailQuest(QUEST_PK);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            npc_escortAI::UpdateAI(diff);
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_PK)
            {
                ((npc_escortAI*)(me->AI()))->Start(true, true, false, player->GetGUID(), me->GetEntry());
                DoScriptText(SAY_START, me);
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kaya_flathoofAI(creature);
    }
};



/*######
# npc_piznik
######*/

float spawns[3][4] = {
    {941.866272f, -255.601471f, -2.403625f, 6.070902f},
    {942.277771f, -253.692307f, -2.335533f, 6.070902f},
    {942.529968f, -252.522171f, -2.293756f, 6.070902f}};


class npc_piznik : public CreatureScript
{
public:
    npc_piznik() : CreatureScript("npc_piznik")
    { }

    class npc_piznikAI : public ScriptedAI
    {
        public:
        npc_piznikAI(Creature* c) : ScriptedAI(c) {}
        
        uint8 count;
        uint64 pGUID;
        
        void EnterCombat(Unit* who) override {}
        
        void Start(uint64 guid)
        {
            count = 0;
            pGUID = guid;
            for (auto & spawn : spawns) {
                if (Creature* summon = me->SummonCreature(3999, spawn[0], spawn[1], spawn[2], spawn[3], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000))
                   summon->AI()->AttackStart(me);
            }
        }
        
        void SummonedCreatureDespawn(Creature* creature)
        override {
            if (creature->GetEntry() == 3999)
                ++count;
            else
                return;
            
            if (count == 3) {
                if (Player* player = ObjectAccessor::GetPlayer(*me, pGUID)) {
                    player->AreaExploredOrEventHappens(1090);
                    player->AreaExploredOrEventHappens(1092);
                }
            }
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == 1090 || quest->GetQuestId() == 1092)
                ((npc_piznik::npc_piznikAI*)(me->AI()))->Start(player->GetGUID());
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_piznikAI(creature);
    }
};



/*######
## AddSC
######*/

void AddSC_stonetalon_mountains()
{

    new npc_braug_dimspirit();

    new npc_kaya_flathoof();
    
    new npc_piznik();
}

