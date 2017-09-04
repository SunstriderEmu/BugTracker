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


#include "def_razorfen_downs.h"

enum Spells
{
    SPELL_WEB_SPRAY               = 12252,
    SPELL_CURSE_OF_TUTEN_KASH     = 12255,
};


class boss_tuten_kash : public CreatureScript
{
public:
    boss_tuten_kash() : CreatureScript("boss_tuten_kash")
    { }

    class boss_tuten_kashAI : public ScriptedAI
    {
        public:
        boss_tuten_kashAI(Creature* c) : ScriptedAI(c)
        {
            pInstance =(InstanceScript*)me->GetInstanceScript();
        }
    
        InstanceScript* pInstance;
    
        uint32 WebSprayTimer;
        uint32 CurseOfTutenKashTimer;
    
        void Reset()
        override {
            WebSprayTimer = urand(3000, 5000);
            CurseOfTutenKashTimer = urand(9000, 14000);
    
            if (pInstance && pInstance->GetData(DATA_TUTEN_KASH_EVENT) != DONE)
                    pInstance->SetData(DATA_TUTEN_KASH_EVENT, NOT_STARTED);
        }
    
        void EnterCombat(Unit *who)
        override {
            if (pInstance)
                pInstance->SetData(DATA_TUTEN_KASH_EVENT, IN_PROGRESS);
        }
    
        void JustDied(Unit* Killer)
        override {
            if(pInstance)
                pInstance->SetData(DATA_TUTEN_KASH_EVENT, DONE);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if (WebSprayTimer <= diff)
            {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true), SPELL_WEB_SPRAY);
                WebSprayTimer = urand(6000, 8000);
            }
            else
                WebSprayTimer -= diff;
    
            if (CurseOfTutenKashTimer <= diff)
            {
                me->InterruptNonMeleeSpells(false);
                DoCast(me, SPELL_CURSE_OF_TUTEN_KASH);
                CurseOfTutenKashTimer = urand(15000, 25000);
            }
            else
                CurseOfTutenKashTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_tuten_kashAI(creature);
    }
};


class Gong : public GameObjectScript
{
public:
    Gong() : GameObjectScript("go_gong")
    {}

    struct GongAI : public GameObjectAI
    {
        GongAI(GameObject* obj) : GameObjectAI(obj), pInstance(obj->GetInstanceScript()) { }

        InstanceScript* pInstance;

        bool GossipHello(Player* player) override
        {
            if (!pInstance)
                return true;

            if (pInstance->GetData(DATA_WAVE_EVENT) >= 3)
                return true;

            if (pInstance->GetData(DATA_CREATURE_CREDIT) != 0)
                return true;

            pInstance->SetData(DATA_WAVE_EVENT, 0);

            me->AddUse();

            switch (pInstance->GetData(DATA_WAVE_EVENT))
            {
            case 1:
                for (uint8 i = 0; i < 4; ++i)
                    if (Creature* add = me->SummonCreature(NPC_TOMB_FIEND, 2546.67f, 891.78f, 47.8f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0))
                        add->AI()->AttackStart(player);

                for (uint8 i = 0; i < 4; ++i)
                    if (Creature* add = me->SummonCreature(NPC_TOMB_FIEND, 2490.06f, 832.66f, 44.5f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0))
                        add->AI()->AttackStart(player);
                pInstance->SetData(DATA_CREATURE_CREDIT, 8);
                break;
            case 2:
                for (uint8 i = 0; i < 4; ++i)
                    if (Creature* add = me->SummonCreature(NPC_TOMB_REAVER, 2546.67f, 891.78f, 47.8f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0))
                        add->AI()->AttackStart(player);

                for (uint8 i = 0; i < 4; ++i)
                    if (Creature* add = me->SummonCreature(NPC_TOMB_REAVER, 2490.06f, 832.66f, 44.5f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0))
                        add->AI()->AttackStart(player);
                pInstance->SetData(DATA_CREATURE_CREDIT, 8);
                break;
            case 3:
                if (Creature* boss = me->SummonCreature(BOSS_TUTEN_KASH, 2490.06f, 832.66f, 44.5f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0))
                    boss->AI()->AttackStart(player);
                pInstance->SetData(DATA_CREATURE_CREDIT, 0);
                break;
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new GongAI(go);
    }
};

void AddSC_boss_tuten_kash()
{
    new boss_tuten_kash();

    new Gong();
}
