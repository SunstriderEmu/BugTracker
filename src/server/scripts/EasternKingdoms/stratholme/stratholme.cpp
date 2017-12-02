/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Stratholme
SD%Complete: 100
SDComment: Misc mobs for instance. GO-script to apply aura and start event for quest 8945
SDCategory: Stratholme
EndScriptData */

/* ContentData
go_gauntlet_gate
mob_freed_soul
mob_restless_soul
mobs_spectral_ghostly_citizen
at_timmy_the_cruel
npc_ashari_crystal
go_stratholme_supply_crate
EndContentData */


#include "def_stratholme.h"

/*######
##  (this is the _first_ of the gauntlet gates, two exist)
######*/

class GauntletGate : public GameObjectScript
{
public:
    GauntletGate() : GameObjectScript("go_gauntlet_gate")
    {}

    struct GauntletGateAI : public GameObjectAI
    {
        GauntletGateAI(GameObject* obj) : GameObjectAI(obj), pInstance(obj->GetInstanceScript()) { }

        InstanceScript* pInstance;

        bool GossipHello(Player* player) override
        {
            if (!pInstance)
                return false;

            if (pInstance->GetData(TYPE_BARON_RUN) != NOT_STARTED)
                return false;

            if (Group *pGroup = player->GetGroup())
            {
                for (GroupReference *itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
                {
                    Player* pGroupie = itr->GetSource();
                    if (!pGroupie)
                        continue;

                    if (pGroupie->GetQuestStatus(QUEST_DEAD_MAN_PLEA) == QUEST_STATUS_INCOMPLETE &&
                        !pGroupie->HasAuraEffect(SPELL_BARON_ULTIMATUM, 0) &&
                        pGroupie->GetMap() == me->GetMap())
                        pGroupie->CastSpell(pGroupie, SPELL_BARON_ULTIMATUM, TRIGGERED_FULL_MASK);
                }
            }
            else if (player->GetQuestStatus(QUEST_DEAD_MAN_PLEA) == QUEST_STATUS_INCOMPLETE &&
                !player->HasAuraEffect(SPELL_BARON_ULTIMATUM, 0) &&
                player->GetMap() == me->GetMap())
                player->CastSpell(player, SPELL_BARON_ULTIMATUM, TRIGGERED_FULL_MASK);

            pInstance->SetData(TYPE_BARON_RUN, IN_PROGRESS);
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new GauntletGateAI(go);
    }
};

/*######
## mob_freed_soul
######*/

//Possibly more of these quotes around.
#define SAY_ZAPPED0 "Thanks to Egan"
#define SAY_ZAPPED1 "Rivendare must die"
#define SAY_ZAPPED2 "Who you gonna call?"
#define SAY_ZAPPED3 "Don't cross those beams!"


class mob_freed_soul : public CreatureScript
{
public:
    mob_freed_soul() : CreatureScript("mob_freed_soul")
    { }

    class mob_freed_soulAI : public ScriptedAI
    {
        public:
        mob_freed_soulAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset()
        override {
            switch (rand()%4)
            {
                case 0: me->Say(SAY_ZAPPED0,LANG_UNIVERSAL,nullptr); break;
                case 1: me->Say(SAY_ZAPPED1,LANG_UNIVERSAL,nullptr); break;
                case 2: me->Say(SAY_ZAPPED2,LANG_UNIVERSAL,nullptr); break;
                case 3: me->Say(SAY_ZAPPED3,LANG_UNIVERSAL,nullptr); break;
            }
        }
    
        void EnterCombat(Unit* who) override { }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_freed_soulAI(creature);
    }
};


/*######
## mob_restless_soul
######*/

#define SPELL_EGAN_BLASTER  17368
#define SPELL_SOUL_FREED    17370
#define QUEST_RESTLESS_SOUL 5282
#define ENTRY_RESTLESS      11122
#define ENTRY_FREED         11136


class mob_restless_soul : public CreatureScript
{
public:
    mob_restless_soul() : CreatureScript("mob_restless_soul")
    { }

    class mob_restless_soulAI : public ScriptedAI
    {
        public:
        mob_restless_soulAI(Creature *c) : ScriptedAI(c) {}
    
        uint64 Tagger;
        uint32 Die_Timer;
        bool Tagged;
    
        void Reset()
        override {
            Tagger = 0;
            Die_Timer = 5000;
            Tagged = false;
        }
    
        void EnterCombat(Unit* who) override { }
    
        void SpellHit(Unit *caster, const SpellInfo *spell)
        override {
            if (caster->GetTypeId() == TYPEID_PLAYER)
            {
                if (!Tagged && spell->Id == SPELL_EGAN_BLASTER && (caster->ToPlayer())->GetQuestStatus(QUEST_RESTLESS_SOUL) == QUEST_STATUS_INCOMPLETE)
                {
                    Tagged = true;
                    Tagger = caster->GetGUID();
                }
            }
        }
    
        void JustSummoned(Creature *summoned)
        override {
            summoned->CastSpell(summoned,SPELL_SOUL_FREED, TRIGGERED_NONE);
        }
    
        void JustDied(Unit* Killer)
        override {
            if (Tagged)
                me->SummonCreature(ENTRY_FREED, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 300000);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (Tagged)
            {
                if (Die_Timer < diff)
                {
                    if (Unit* pTemp = ObjectAccessor::GetUnit(*me,Tagger))
                    {
                        (pTemp)->ToPlayer()->KilledMonsterCredit(ENTRY_RESTLESS, me->GetGUID());
                        me->Kill(me);
                    }
                }else Die_Timer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_restless_soulAI(creature);
    }
};


/*######
## mobs_spectral_ghostly_citizen
######*/

#define SPELL_HAUNTING_PHANTOM  16336


class mobs_spectral_ghostly_citizen : public CreatureScript
{
public:
    mobs_spectral_ghostly_citizen() : CreatureScript("mobs_spectral_ghostly_citizen")
    { }

    class mobs_spectral_ghostly_citizenAI : public ScriptedAI
    {
        public:
        mobs_spectral_ghostly_citizenAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 Die_Timer;
        bool Tagged;
    
        void Reset()
        override {
            Die_Timer = 5000;
            Tagged = false;
        }
    
        void EnterCombat(Unit* who) override { }
    
        void SpellHit(Unit *caster, const SpellInfo *spell)
        override {
            if (!Tagged && spell->Id == SPELL_EGAN_BLASTER)
                Tagged = true;
        }
    
        void JustDied(Unit* Killer)
        override {
            if (Tagged)
            {
                for(uint32 i = 1; i <= 4; i++)
                {
                    float x,y,z;
                     me->GetRandomPoint(me,20.0f,x,y,z);
    
                     //100%, 50%, 33%, 25% chance to spawn
                     uint32 j = urand(1,i);
                     if (j==1)
                         me->SummonCreature(ENTRY_RESTLESS,x,y,z,0,TEMPSUMMON_CORPSE_DESPAWN,600000);
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (Tagged)
            {
                if (Die_Timer < diff)
                {
                    me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                }else Die_Timer -= diff;
            }
    
            if (!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
        }
    
        void ReceiveEmote(Player* player, uint32 emote) override
        {
            switch (emote)
            {
            case TEXTEMOTE_DANCE:
                EnterEvadeMode();
                break;
            case TEXTEMOTE_RUDE:
                //Should instead cast spell, kicking player back. Spell not found.
                if (me->IsWithinDistInMap(player, 5))
                    me->HandleEmoteCommand(EMOTE_ONESHOT_RUDE);
                else
                    me->HandleEmoteCommand(EMOTE_ONESHOT_RUDE);
                break;
            case TEXTEMOTE_WAVE:
                me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                break;
            case TEXTEMOTE_BOW:
                me->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
                break;
            case TEXTEMOTE_KISS:
                me->HandleEmoteCommand(EMOTE_ONESHOT_FLEX);
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mobs_spectral_ghostly_citizenAI(creature);
    }
};


class ATTimmyTheCruel : AreaTriggerScript
{
public:
    ATTimmyTheCruel() : AreaTriggerScript("at_timmy_the_cruel") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        InstanceScript *pInstance = ((InstanceScript*)pPlayer->GetInstanceScript());
        if (!pInstance)
            return false;
        if (pInstance->GetData(TYPE_TIMMY_SPAWN))
            return false;
        if (Creature* cr = pPlayer->FindNearestCreature(10148, 50.0f, true))
            return false;
        if (Creature* cr = pPlayer->FindNearestCreature(10391, 50.0f, true))
            return false;
        if (Creature* cr = pPlayer->FindNearestCreature(10390, 50.0f, true))
            return false;
        if (Creature* cr = pPlayer->FindNearestCreature(10420, 50.0f, true))
            return false;
        if (Creature* cr = pPlayer->FindNearestCreature(10419, 50.0f, true))
            return false;

        // Else, the square is clean, wait 3 sec and spawn Timmy
        pInstance->SetData(TYPE_TIMMY_SPAWN, DONE);
        return true;
    }
};

class CannonballStack : public GameObjectScript
{
public:
    CannonballStack() : GameObjectScript("go_cannonball_stack")
    {}

    struct CannonballStackAI : public GameObjectAI
    {
        CannonballStackAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            //pPlayer->SendLoot(pGo->GetGUID(), LOOT_CORPSE);
            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 12973, 1);
            if (msg == EQUIP_ERR_OK)
            {
                Item* item = pPlayer->StoreNewItem(dest, 12973, true);
                pPlayer->SendNewItem(item, 1, true, false);
                me->SetLootState(GO_READY); // Should despawn GO, can be respawned if boss resets

                return false;
            }
            me->SetLootState(GO_ACTIVATED);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new CannonballStackAI(go);
    }
};

/*######
## npc_ashari_crystal
######*/

#define NPC_THUZADIN_ACOLYTE    10399


class npc_ashari_crystal : public CreatureScript
{
public:
    npc_ashari_crystal() : CreatureScript("npc_ashari_crystal")
    { }

    class npc_ashari_crystalAI : public ScriptedAI
    {
        public:
        npc_ashari_crystalAI(Creature *c) : ScriptedAI(c) {}
        
        void Reset()
        override {
            me->SetDisableGravity(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
        
        void Aggro (Unit *pWho) {}
        
        void MoveInLineOfSight(Unit *pWho)
        override {
            if (pWho->GetTypeId() != TYPEID_PLAYER)
                return;
                
            if (me->GetDistance2d(pWho) >= 10.0f)
                return;
                
            if (Creature *acolyte = pWho->FindNearestCreature(NPC_THUZADIN_ACOLYTE, 15.0f, true))
                return;
                
            me->Kill(me);
        }
        
        void UpdateAI (uint32 const diff) 
        override {
            me->SetDisableGravity(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ashari_crystalAI(creature);
    }
};


class SupplyCrate : public GameObjectScript
{
public:
    SupplyCrate() : GameObjectScript("go_stratholme_supply_crate")
    {}

    struct SupplyCrateAI : public GameObjectAI
    {
        SupplyCrateAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            switch (rand() % 5) {
            case 0:
            case 1:
            {
                uint8 amount = rand() % 3 + 1;
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 13180, amount);
                if (msg == EQUIP_ERR_OK) {
                    Item* item = player->StoreNewItem(dest, 13180, true);
                    player->SendNewItem(item, amount, true, false);
                }
                break;
            }
            case 2:
                for (uint8 i = 0; i < 5; i++)
                    if (Creature* summon = player->SummonCreature(10441, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0))
                        summon->AI()->AttackStart(player);
                break;
            case 3:
                for (uint8 i = 0; i < 5; i++)
                    if (Creature* summon = player->SummonCreature(10461, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0))
                        summon->AI()->AttackStart(player);
                break;
            case 4:
                for (uint8 i = 0; i < 8; i++)
                    if (Creature* summon = player->SummonCreature(10536, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0))
                        summon->AI()->AttackStart(player);
                break;
            }

            me->SetLootState(GO_JUST_DEACTIVATED);

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new SupplyCrateAI(go);
    }
};

/*######
## AddSC
######*/

void AddSC_stratholme()
{

    new GauntletGate();

    new mob_freed_soul();

    new mob_restless_soul();

    new mobs_spectral_ghostly_citizen();
    
    new ATTimmyTheCruel();
    new CannonballStack();
    
    new npc_ashari_crystal();
    
    new SupplyCrate();
}

