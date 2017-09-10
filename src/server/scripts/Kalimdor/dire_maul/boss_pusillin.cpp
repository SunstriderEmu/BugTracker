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


#include "def_dire_maul.h"

#define FACTION_FRIENDLY            35
#define FACTION_HOSTILE             90

enum ePusillinSpells {
    SPELL_SPIRIT_OF_RUNN        = 22735,
    SPELL_BLAST_WAVE            = 22424,
    SPELL_FIREBALL              = 15228,
    SPELL_FIREBLAST             = 14145
};

#define GOSSIP_TEMP     "[PH] Donne-moi cette clé !"


class boss_pusillin : public CreatureScript
{
public:
    boss_pusillin() : CreatureScript("boss_pusillin")
    { }

    class boss_pusillinAI : public ScriptedAI
    {
        public:
        boss_pusillinAI(Creature *c) : ScriptedAI(c) 
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        uint8 step;
        
        uint32 fireballTimer;
        uint32 fireblastTimer;
        uint32 blastwaveTimer;
    
        void Reset()
        override {
            /*if (pInstance && pInstance->GetData(DATA_PUSILLIN_STEP) < 4) {
                step = 0;
                pInstance->SetData(DATA_PUSILLIN_STEP, 0);
            }
            else if (pInstance) {
                step = 4;
                pInstance->SetData(DATA_PUSILLIN_STEP, 4);
                me->SetFaction(FACTION_HOSTILE);
                // TODO: teleport him to last position
            }*/
            /*step = 0;
            if (pInstance) {
                step = pInstance->GetData(DATA_PUSILLIN_STEP);
                switch (step) {
                case 1:
                    me->SummonCreature(14354, -149.159958, -274.567322, -4.147923, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 6000000);
                    me->DisappearAndDie();
                    break;
                case 2:
                    me->SummonCreature(14354, 111.177673, -352.949677, -4.101341, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 6000000);
                    me->DisappearAndDie();
                    break;
                case 3:
                    me->SummonCreature(14354, 47.163609, -653.998535, -25.160894, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 6000000);
                    me->DisappearAndDie();
                    break;
                case 4:
                    if (Creature *pNewCre = me->SummonCreature(14354, 17.699953, -704.177368, -12.642654, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 6000000)) {
                        pNewCre->SetFaction(FACTION_HOSTILE);
                        pNewCre->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    }
                    me->DisappearAndDie();
                    break;
                }
            }*/
            
            fireballTimer = 6000;
            fireblastTimer = 8000;
            blastwaveTimer = 12000;
        }
        
        uint8 GetStep()
        {
            return step;
        }
        
        void SetStep(uint8 currStep)
        {
            step = currStep;
        }
        
        void EnterCombat(Unit *pWho)
        override {
            DoCast(me, SPELL_SPIRIT_OF_RUNN, false);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (fireballTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FIREBALL, false);
                fireballTimer = 6000;
            }
            else
                fireballTimer -= diff;
                
            if (fireblastTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_FIREBLAST, false);
                fireblastTimer = 8000;
            }
            else
                fireblastTimer -= diff;
                
            if (blastwaveTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_BLAST_WAVE, false);
                blastwaveTimer = 15000;
            }
            else
                blastwaveTimer -= diff;
                
            DoMeleeAttackIfReady();
        }

        virtual bool GossipHello(Player* pPlayer) override
        {
            uint8 stepSwitch = ((boss_pusillin::boss_pusillinAI*)me->AI())->GetStep();
            switch (stepSwitch) {
            case 0:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEMP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(2601, me->GetGUID());
                break;
            case 1:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEMP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(2601, me->GetGUID());
                break;
            case 2:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEMP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(2601, me->GetGUID());
                break;
            case 3:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEMP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(2601, me->GetGUID());
                break;
            case 4:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEMP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(2601, me->GetGUID());
                break;
            }
            
            return true;

        }


        virtual bool GossipSelect(Player* pPlayer, uint32 sender, uint32 action) override
        {
            switch (action) {
            case GOSSIP_ACTION_INFO_DEF + 1:
                me->SetSpeedRate(MOVE_WALK, 8);
                me->GetMotionMaster()->MovePoint(0, 21.937908, -198.946259, -4.132668);
                ((boss_pusillin::boss_pusillinAI*)me->AI())->SetStep(1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                me->SetSpeedRate(MOVE_WALK, 8);
                me->GetMotionMaster()->MovePoint(0, -135.910263, -349.494873, -4.070144);
                ((boss_pusillin::boss_pusillinAI*)me->AI())->SetStep(2);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                me->SetSpeedRate(MOVE_WALK, 8);
                me->GetMotionMaster()->MovePoint(0, 112.385468, -469.288818, -2.719314);
                ((boss_pusillin::boss_pusillinAI*)me->AI())->SetStep(3);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                me->SetSpeedRate(MOVE_WALK, 8);
                me->GetMotionMaster()->MovePoint(0, 25.040466, -696.303101, -25.160894);
                ((boss_pusillin::boss_pusillinAI*)me->AI())->SetStep(4);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                // TODO: start fight
                break;
            }
            
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_pusillinAI(creature);
    }
};




void AddSC_boss_pusillin()
{
    
    new boss_pusillin();
}
