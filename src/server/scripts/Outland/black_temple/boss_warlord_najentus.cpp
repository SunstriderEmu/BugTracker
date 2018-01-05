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
SDName: Boss_Warlord_Najentus
SD%Complete: 95
SDComment:
SDCategory: Black Temple
EndScriptData */


#include "def_black_temple.h"

enum NajentusSay {
    SAY_AGGRO                      = -1564000,
    SAY_NEEDLE1                    = -1564001,
    SAY_NEEDLE2                    = -1564002,
    SAY_SLAY1                      = -1564003,
    SAY_SLAY2                      = -1564004,
    SAY_SPECIAL1                   = -1564005,
    SAY_SPECIAL2                   = -1564006,
    SAY_ENRAGE1                    = -1564007,            //is this text actually in use?
    SAY_ENRAGE2                    = -1564008,
    SAY_DEATH                      = -1564009
};

enum NajentusSpells {
    SPELL_NEEDLE_SPINE             = 39992, //dummy aura
    SPELL_NEEDLE_SPINE2            = 39835, // physical damage + script effect
    SPELL_NEEDLE_SPINE_EXPLOSION   = 39968, // AoE damages, linked via spell_linked_spell
    SPELL_TIDAL_BURST              = 39878,
    SPELL_TIDAL_SHIELD             = 39872,
    SPELL_IMPALING_SPINE           = 39837,
    SPELL_CREATE_NAJENTUS_SPINE    = 39956,
    SPELL_HURL_SPINE               = 39948,
    SPELL_BERSERK                  = 45078
};

#define TIMER_NEEDLE_SPINE           2000 + rand()%500
#define TIMER_NEEDLE_SPINE_START     5000
#define TIMER_TIDAL_SHIELD           60000
#define TIMER_SPECIAL_YELL           25000 + (rand()%76)*IN_MILLISECONDS // 25 - 100
#define TIMER_SPECIAL_YELL_START     TIMER_SPECIAL_YELL + 20000
#define TIMER_ENRAGE                 480000
#define TIMER_IMPALING_SPINE         21000

#define CREATURE_INVISIBLE_ANNOUNCER 30000 // To announce gate opening

enum NajentusGobjects {
    GOBJECT_SPINE                  = 185584
};

class boss_najentus : public CreatureScript
{
public:
    boss_najentus() : CreatureScript("boss_najentus")
    { }

    class boss_najentusAI : public ScriptedAI
    {
        public:
        boss_najentusAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript* pInstance;
    
        uint32 NeedleSpineTimer;
        uint32 EnrageTimer;
        uint32 SpecialYellTimer;
        uint32 TidalShieldTimer;
        uint32 ImpalingSpineTimer;
    
        ObjectGuid SpineTargetGUID;
    
        void Reset()
        override {
            EnrageTimer = TIMER_ENRAGE;
            SpecialYellTimer = TIMER_SPECIAL_YELL_START;
            TidalShieldTimer = TIMER_TIDAL_SHIELD;
    
            NeedleSpineTimer = TIMER_NEEDLE_SPINE_START;
            ImpalingSpineTimer = TIMER_IMPALING_SPINE;
    
            SpineTargetGUID.Clear();
    
            if(pInstance && me->IsAlive())
                pInstance->SetData(DATA_HIGHWARLORDNAJENTUSEVENT, NOT_STARTED);
        }
    
        void KilledUnit(Unit *victim)
        override {
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_SLAY1, me); break;
            case 1: DoScriptText(SAY_SLAY2, me); break;
            }
        }
    
        void JustDied(Unit *victim)
        override {
            if(pInstance)
            {
                DoSpawnCreature(CREATURE_INVISIBLE_ANNOUNCER,0,0,0,0, TEMPSUMMON_TIMED_DESPAWN, 30000);
                pInstance->SetData(DATA_HIGHWARLORDNAJENTUSEVENT, DONE);
            }
    
            DoScriptText(SAY_DEATH, me);
        }
    
        bool hasShield()
        {
            return me->HasAuraEffect(SPELL_TIDAL_SHIELD, 0);
        }
    
        void SpellHit(Unit *caster, const SpellInfo *spell)
        override {
            if(spell->Id == SPELL_HURL_SPINE && hasShield())
            {
                me->RemoveAurasDueToSpell(SPELL_TIDAL_SHIELD);
                me->CastSpell(me, SPELL_TIDAL_BURST, TRIGGERED_FULL_MASK);
                NeedleSpineTimer = 10000;
                ImpalingSpineTimer = TIMER_IMPALING_SPINE;
            }
        }
    
        void JustEngagedWith(Unit *who)
        override {
            if(pInstance)
                pInstance->SetData(DATA_HIGHWARLORDNAJENTUSEVENT, IN_PROGRESS);
    
            DoScriptText(SAY_AGGRO, me);
            DoZoneInCombat();
        }
    
        bool RemoveImpalingSpine()
        {
            if(!SpineTargetGUID) return false;
            Unit* target = ObjectAccessor::GetUnit(*me, SpineTargetGUID);
            if(target && target->HasAuraEffect(SPELL_IMPALING_SPINE, 1))
                target->RemoveAurasDueToSpell(SPELL_IMPALING_SPINE);
            SpineTargetGUID.Clear();
            return true;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim())
                return;
    
            if(TidalShieldTimer < diff)
            {
                me->CastSpell(me, SPELL_TIDAL_SHIELD, TRIGGERED_FULL_MASK);
                TidalShieldTimer = TIMER_TIDAL_SHIELD;
            }else TidalShieldTimer -= diff;
    
            DoMeleeAttackIfReady();
    
            if(hasShield())
                return;
    
            if(!me->HasAuraEffect(SPELL_BERSERK, 0))
            {
                if(EnrageTimer < diff)
                {
                    DoScriptText(SAY_ENRAGE2, me);
                    me->CastSpell(me, SPELL_BERSERK, TRIGGERED_FULL_MASK);
                }else EnrageTimer -= diff;
            }
    
            if(NeedleSpineTimer < diff)
            {
                //me->CastSpell(me, SPELL_NEEDLE_SPINE, TRIGGERED_FULL_MASK);
                std::list<Unit*> targets;
                SelectTargetList(targets, 3, SELECT_TARGET_RANDOM, 0, 0.0f, true);
                for(auto & i : targets)
                    me->CastSpell(i, SPELL_NEEDLE_SPINE2, TRIGGERED_FULL_MASK);
                NeedleSpineTimer = TIMER_NEEDLE_SPINE;
            }else NeedleSpineTimer -= diff;
    
            if(SpecialYellTimer < diff)
            {
                switch(rand()%2)
                {
                case 0: DoScriptText(SAY_SPECIAL1, me); break;
                case 1: DoScriptText(SAY_SPECIAL2, me); break;
                }
                SpecialYellTimer = TIMER_SPECIAL_YELL;
            }else SpecialYellTimer -= diff;
    
            if(ImpalingSpineTimer < diff)
            {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0, true, true);
                if(!target) target = me->GetVictim();
                if(target)
                {
                    me->CastSpell(target, SPELL_IMPALING_SPINE, TRIGGERED_FULL_MASK);
                    SpineTargetGUID = target->GetGUID();
                    //must let target summon, otherwise you cannot click the spine
                    target->SummonGameObject(GOBJECT_SPINE, target->GetPosition(), G3D::Quat(), 30);
    
                    switch(rand()%2)
                    {
                    case 0: DoScriptText(SAY_NEEDLE1, me); break;
                    case 1: DoScriptText(SAY_NEEDLE2, me); break;
                    }
                    ImpalingSpineTimer = TIMER_IMPALING_SPINE;
                }
            }else ImpalingSpineTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_najentusAI(creature);
    }
};



class NajentusSpine : public GameObjectScript
{
public:
    NajentusSpine() : GameObjectScript("go_najentus_spine")
    {}

    struct NajentusSpineAI : public GameObjectAI
    {
        NajentusSpineAI(GameObject* obj) : GameObjectAI(obj), pInstance(obj->GetInstanceScript()) { }

        InstanceScript* pInstance;

        bool GossipHello(Player* player) override
        {
            if (!pInstance)
                return true;

            if (Creature* Najentus = ObjectAccessor::GetCreature(*me, ObjectGuid(pInstance->GetData64(DATA_HIGHWARLORDNAJENTUS))))
                if (((boss_najentus::boss_najentusAI*)Najentus->AI())->RemoveImpalingSpine())
                {
                    player->CastSpell(player, SPELL_CREATE_NAJENTUS_SPINE, TRIGGERED_FULL_MASK);
                    me->SetLootState(GO_NOT_READY);
                    me->SetRespawnTime(604800); //one week respawn
                    me->RemoveFromWorld();
                }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new NajentusSpineAI(go);
    }
};

void AddSC_boss_najentus()
{
    new boss_najentus();
    new NajentusSpine();
}

