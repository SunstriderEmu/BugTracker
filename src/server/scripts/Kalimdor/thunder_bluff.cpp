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
SDName: Thunder_Bluff
SD%Complete: 100
SDComment: Quest support: 925
SDCategory: Thunder Bluff
EndScriptData */



/*#####
# npc_cairne_bloodhoof
######*/

#define SPELL_BERSERKER_CHARGE  16636
#define SPELL_CLEAVE            16044
#define SPELL_MORTAL_STRIKE     16856
#define SPELL_THUNDERCLAP       23931
#define SPELL_UPPERCUT          22916

#define GOSSIP_HCB "I know this is rather silly but a young ward who is a bit shy would like your hoofprint."
//TODO: verify abilities/timers
class npc_cairne_bloodhoof : public CreatureScript
{
public:
    npc_cairne_bloodhoof() : CreatureScript("npc_cairne_bloodhoof")
    { }

    class npc_cairne_bloodhoofAI : public ScriptedAI
    {
        public:
        npc_cairne_bloodhoofAI(Creature* c) : ScriptedAI(c) {}
    
        uint32 BerserkerCharge_Timer;
        uint32 Cleave_Timer;
        uint32 MortalStrike_Timer;
        uint32 Thunderclap_Timer;
        uint32 Uppercut_Timer;
    
        void Reset()
        override {
            BerserkerCharge_Timer = 30000;
            Cleave_Timer = 5000;
            MortalStrike_Timer = 10000;
            Thunderclap_Timer = 15000;
            Uppercut_Timer = 10000;
        }
    
        void EnterCombat(Unit *who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if( BerserkerCharge_Timer < diff )
            {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0);
                if( target )
                    DoCast(target,SPELL_BERSERKER_CHARGE);
                BerserkerCharge_Timer = 25000;
            }else BerserkerCharge_Timer -= diff;
    
            if( Uppercut_Timer < diff )
            {
                DoCast(me->GetVictim(),SPELL_UPPERCUT);
                Uppercut_Timer = 20000;
            }else Uppercut_Timer -= diff;
    
            if( Thunderclap_Timer < diff )
            {
                DoCast(me->GetVictim(),SPELL_THUNDERCLAP);
                Thunderclap_Timer = 15000;
            }else Thunderclap_Timer -= diff;
    
            if( MortalStrike_Timer < diff )
            {
                DoCast(me->GetVictim(),SPELL_MORTAL_STRIKE);
                MortalStrike_Timer = 15000;
            }else MortalStrike_Timer -= diff;
    
            if( Cleave_Timer < diff )
            {
                DoCast(me->GetVictim(),SPELL_CLEAVE);
                Cleave_Timer = 7000;
            }else Cleave_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }

        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if( player->GetQuestStatus(925) == QUEST_STATUS_INCOMPLETE )
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HCB, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INFO );

            player->SEND_GOSSIP_MENU_TEXTID(7013, me->GetGUID() );

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if( action == GOSSIP_SENDER_INFO )
            {
                player->CastSpell(player, 23123, false);
                player->SEND_GOSSIP_MENU_TEXTID(7014, me->GetGUID() );
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_cairne_bloodhoofAI(creature);
    }
};




void AddSC_thunder_bluff()
{

    new npc_cairne_bloodhoof();
}

