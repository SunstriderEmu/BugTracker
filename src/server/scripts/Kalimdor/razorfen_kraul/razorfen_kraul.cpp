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
SDName: Razorfen Kraul
SD%Complete: 100
SDComment: Quest support: 1144
SDCategory: Razorfen Kraul
EndScriptData */

/* ContentData
npc_willix
EndContentData */


#include "EscortAI.h"
#include "def_razorfen_kraul.h"

#define SAY_READY -1047000
#define SAY_POINT -10470001
#define SAY_AGGRO1 -1047002
#define SAY_BLUELEAF -1047003
#define SAY_DANGER -1047004
#define SAY_BAD -1047005
#define SAY_THINK -1047006
#define SAY_SOON -1047007
#define SAY_FINALY -1047008
#define SAY_WIN -1047009
#define SAY_END -1047010

#define QUEST_WILLIX_THE_IMPORTER 1144
#define ENTRY_BOAR 4514
#define SPELL_QUILLBOAR_CHANNELING 7083


class npc_willix : public CreatureScript
{
public:
    npc_willix() : CreatureScript("npc_willix")
    { }

    class npc_willixAI : public npc_escortAI
    {
        public:
        npc_willixAI(Creature *c) : npc_escortAI(c) {}
        
        bool complete;
    
        void WaypointReached(uint32 i)
        override {
            Player* player = GetPlayerForEscort();
    
            if (!player)
                return;
    
            switch (i)
            {
            case 3:
                me->HandleEmoteCommand(EMOTE_STATE_POINT);
                DoScriptText(SAY_POINT, me, player);
                break;
            case 4:
                me->SummonCreature(ENTRY_BOAR, 2137.66, 1843.98, 48.08, 1.54, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                break;
            case 8:
                DoScriptText(SAY_BLUELEAF, me, player);
                break;
            case 9:
                DoScriptText(SAY_DANGER, me, player);
                break;
            case 13:
                DoScriptText(SAY_BAD, me, player);
                break;
            case 14:
                me->SummonCreature(ENTRY_BOAR, 2078.91, 1704.54, 56.77, 1.54, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                break;
            case 25:
                DoScriptText(SAY_THINK, me, player);
                break;
            case 31:
                DoScriptText(SAY_SOON, me, player);
                break;
            case 42:
                DoScriptText(SAY_FINALY, me, player);
                break;
            case 43:
                me->SummonCreature(ENTRY_BOAR, 1956.43, 1596.97, 81.75, 1.54,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                break;
            case 45:
                DoScriptText(SAY_WIN, me, player);
                player->GroupEventHappens(QUEST_WILLIX_THE_IMPORTER,me);
                complete = true;
                break;
            case 46:
                DoScriptText(SAY_END, me, player);
                break;
            }
        }
    
        void Reset()
        override {
            complete = false;
        }
    
        void EnterCombat(Unit* who)
        override {
            DoScriptText(SAY_AGGRO1, me, nullptr);
        }
    
        void JustSummoned(Creature* summoned)
        override {
            summoned->AI()->AttackStart(me);
        }
    
        void JustDied(Unit* killer)
        override {
            if (PlayerGUID && !complete)
            {
                if (Player* player = GetPlayerForEscort())
                    player->FailQuest(QUEST_WILLIX_THE_IMPORTER);
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            npc_escortAI::UpdateAI(diff);
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_WILLIX_THE_IMPORTER)
            {
                ((npc_escortAI*)(me->AI()))->Start(true, true, false, player->GetGUID(), me->GetEntry());
                DoScriptText(SAY_READY, me, player);
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_willixAI(creature);
    }
};



class npc_deaths_head_ward_keeper : public CreatureScript
{
public:
    npc_deaths_head_ward_keeper() : CreatureScript("npc_deaths_head_ward_keeper")
    { }

    class npc_deaths_head_ward_keeperAI : public ScriptedAI
    {
        public:
        npc_deaths_head_ward_keeperAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
        uint32 QuillboarChanneling_Timer;
    
        void Reset()
        override {
            QuillboarChanneling_Timer = 1500;
        }
    
        void EnterCombat(Unit *who)
        override {
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!me->IsAlive())
                return;
    
            if (QuillboarChanneling_Timer < diff)
            {
                if( me->IsNonMeleeSpellCast(false) )
                    me->InterruptNonMeleeSpells(true);
                DoCast(me, SPELL_QUILLBOAR_CHANNELING);
                QuillboarChanneling_Timer = 1100;
            }else QuillboarChanneling_Timer -= diff;
    
        }
    
        void JustDied(Unit* /*killer*/)
        override {
            if (pInstance)
                pInstance->SetData(TYPE_WARD_KEEPERS, NOT_STARTED);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_deaths_head_ward_keeperAI(creature);
    }
};



void AddSC_razorfen_kraul()
{

    new npc_willix();
    
    new npc_deaths_head_ward_keeper();
}

