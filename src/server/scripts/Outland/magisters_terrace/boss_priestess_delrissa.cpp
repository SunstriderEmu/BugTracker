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
SDName: Boss_Priestess_Delrissa
SD%Complete: 45
SDComment: No Heroic support yet. Needs further testing. Several scripts for pets disabled, not seem to require any special script.
SDCategory: Magister's Terrace
EndScriptData */


#include "def_magisters_terrace.h"

struct Speech {
    int32 id;
};

static Speech LackeyDeath[] = {
    {-1585013},
    {-1585014},
    {-1585015},
    {-1585016},
};

static Speech PlayerDeath[]= {
    {-1585017},
    {-1585018},
    {-1585019},
    {-1585020},
    {-1585021},
};

#define SAY_AGGRO           -1585012
#define SAY_DEATH           -1585022

enum eDelrissa {
    SPELL_DISPEL_MAGIC      = 27609,
    SPELL_FLASH_HEAL        = 17843,
    SPELL_SW_PAIN_NORMAL    = 14032,
    SPELL_SW_PAIN_HEROIC    = 15654,
    SPELL_SHIELD            = 44291,
    SPELL_RENEW_NORMAL      = 44174,
    SPELL_RENEW_HEROIC      = 46192,
};

#define ORIENT               4.98
#define POS_Z               -19.9215

float LackeyLocations[4][2] = {
    {123.77, 17.6007},
    {131.731, 15.0827},
    {121.563, 15.6213},
    {129.988, 17.2355},
};

const uint32 AddEntry[8] = {
    24557,                                                  //Kagani Nightstrike
    24558,                                                  //Elris Duskhallow
    24554,                                                  //Eramas Brightblaze
    24561,                                                  //Yazzaj
    24559,                                                  //Warlord Salaris
    24555,                                                  //Garaxxas
    24553,                                                  //Apoko
    24556,                                                  //Zelfan
};

struct Add {
    Add(uint32 _entry, uint64 _guid)
    {
        entry = _entry;
        guid  = _guid;
    }

    uint32 entry;
    uint64 guid;
};

std::vector<Add*> Adds;

struct boss_priestess_delrissaAI : public ScriptedAI
{
    boss_priestess_delrissaAI(Creature* c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        //Adds.clear();
        //SummonAdds();
        Heroic = c->GetMap()->IsHeroic();
    }

    InstanceScript* pInstance;

    uint8 LackeysKilled;
    uint8 PlayersKilled;

    uint32 HealTimer;
    uint32 RenewTimer;
    uint32 ShieldTimer;
    uint32 SWPainTimer;
    uint32 DispelTimer;
    uint32 ResetTimer;

    uint32 CombatPulseTimer;                                // Periodically puts all players in the instance in combat

    bool Heroic;

    void Reset()
    override {
        me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
        me->SetCorpseDelay(60*60*IN_MILLISECONDS);
        LackeysKilled = 0;
        PlayersKilled = 0;

        HealTimer   = 15000;
        RenewTimer  = 10000;
        ShieldTimer = 2000;
        SWPainTimer = 5000;
        DispelTimer = 7500;
        ResetTimer = 5000;

        CombatPulseTimer  = 5000;

        //CheckAdds();
        ClearAddsList();
        SummonAdds();

        if(pInstance)
        {
            pInstance->SetData(DATA_DELRISSA_DEATH_COUNT, 0);
            if (me->IsDead())
                pInstance->SetData(DATA_DELRISSA_EVENT, DONE);
            else pInstance->SetData(DATA_DELRISSA_EVENT, NOT_STARTED);
        }else error_log(ERROR_INST_DATA);
    }

    void EnterCombat(Unit* who)
    override {
        DoScriptText(SAY_AGGRO, me);
        SetAddsInCombat(who);
    }

    void SetAddsInCombat(Unit* who)
    {
        for(auto & Add : Adds)
            if(Creature* pAdd = ObjectAccessor::GetCreature(*me, Add->guid))
                pAdd->AI()->AttackStart(who);
    }

    void SummonAdds()
    {
        /*if (me->IsDead())
            return;*/
        std::vector<uint32> AddList;
        for(uint32 i : AddEntry)
            AddList.push_back(i);

        while(AddList.size() > 4)
            AddList.erase(AddList.begin() + rand()%AddList.size());

        for(uint8 i = 0; i < AddList.size(); ++i)
        {
            Creature* pAdd = me->SummonCreature(AddList[i], LackeyLocations[i][0], LackeyLocations[i][1], POS_Z, ORIENT, TEMPSUMMON_DEAD_DESPAWN, 0);
            if(pAdd)
            {
                auto  nAdd = new Add(AddList[i], pAdd->GetGUID());
                Adds.push_back(nAdd);
            }
        }
        
        if (pInstance)
            pInstance->SetData(HAS_DELRISSA_SUMMONED, DONE);
    }

    void CheckAdds()
    {
        //if (me->IsDead())
        //  return;
        /*if(Adds.empty() && pInstance && !pInstance->GetData(HAS_DELRISSA_SUMMONED))
        {
            SummonAdds();
            return;
        }*/
        for(uint8 i = 0; i < Adds.size(); ++i)
        {
            Creature* pAdd = (ObjectAccessor::GetCreature(*me, Adds[i]->guid));
            if(pAdd && pAdd->IsAlive())
            {
                pAdd->AI()->EnterEvadeMode();
                pAdd->GetMotionMaster()->MovePoint(0,LackeyLocations[i][0], LackeyLocations[i][1], POS_Z);
            }
            else if(!pAdd || (pAdd && pAdd->IsDead()))
            {
                if(pAdd)
                    pAdd->RemoveCorpse();//looks stupid if mob is alive but has a dead corpse in front of him :)
                Creature* pAdd = me->SummonCreature(Adds[i]->entry, LackeyLocations[i][0], LackeyLocations[i][1], POS_Z, ORIENT, TEMPSUMMON_DEAD_DESPAWN, 0);
                if(pAdd)
                    Adds[i]->guid = pAdd->GetGUID();
            }
        }
    }
    
    void ClearAddsList()
    {
        /*for(uint8 i = 0; i < Adds.size(); ++i)
        {
            Creature* pAdd = (ObjectAccessor::GetCreature(*me, Adds[i]->guid));
            if(pAdd)
                pAdd->DisappearAndDie();
        }
        
        Adds.clear();
        
        // Also despawn adds' pets if needed
        if (Creature* fizzle = me->FindNearestCreature(24656, 30.0f, true))
            fizzle->DisappearAndDie();
        if (Creature* sliver = me->FindNearestCreature(24552, 30.0f, true))
            sliver->DisappearAndDie();*/
            
        // You want war? I'll give it to you!
        for (uint32 i : AddEntry) {
            if (Creature* add = me->FindNearestCreature(i, 30.0f, true))
                add->DisappearAndDie();
        }
        
        Adds.clear();
    }

    void KilledUnit(Unit* victim)
    override {
        if(victim->GetTypeId() != TYPEID_PLAYER || me->IsDead())
            return;

        DoScriptText(PlayerDeath[PlayersKilled].id, me);
        if( PlayersKilled < 4 )
            ++PlayersKilled;
    }

    void KilledLackey()
    {
        if(me->IsDead())//no sense to talk if dead..
            return;
        DoScriptText(LackeyDeath[LackeysKilled].id, me);
        if( LackeysKilled < 3 )
            ++LackeysKilled;

        CheckLootable();
    }

    void JustDied(Unit* killer)
    override {
        DoScriptText(SAY_DEATH, me);

        CheckLootable();

        if(!pInstance)
        {
            error_log(ERROR_INST_DATA);
            return;
        }

        pInstance->SetData(DATA_DELRISSA_DEATH_COUNT, 1);
        pInstance->SetData(DATA_DELRISSA_EVENT, DONE);
        if(GameObject* Door = GameObject::GetGameObject(*me, pInstance->GetData64(DATA_DELRISSA_DOOR)))
            Door->SetGoState(GO_STATE_ACTIVE);
    }

    void CheckLootable()
    {
        if(pInstance && pInstance->GetData(DATA_DELRISSA_DEATH_COUNT) >= 4)
            me->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
        else
            me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;

        if(ResetTimer < diff)
        {
            float x, y, z, o;
            me->GetHomePosition(x, y, z, o);
            if(me->GetPositionZ() >= z+10)
            {
                EnterEvadeMode();
                return;
            }
            ResetTimer = 5000;
        }else ResetTimer -= diff;

        if(HealTimer < diff)
        {
            uint32 health = me->GetHealth();
            Unit* target = me;
            for(auto & Add : Adds)
                if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add->guid))
                    if(pAdd->IsAlive() && pAdd->GetHealth() < health)
                        target = pAdd;

            DoCast(target, SPELL_FLASH_HEAL);
            HealTimer = 15000;
        }else HealTimer -= diff;

        if(RenewTimer < diff)
        {
            Unit* target = me;
            if(rand()%2 == 1)
            {
                auto itr = Adds.begin() + rand()%Adds.size();
                Unit* pAdd = ObjectAccessor::GetUnit(*me, (*itr)->guid);
                if(pAdd && pAdd->IsAlive())
                    target = pAdd;
            }
            DoCast(target,Heroic ? SPELL_RENEW_HEROIC : SPELL_RENEW_NORMAL);
            RenewTimer = 5000;
        }else RenewTimer -= diff;

        if(ShieldTimer < diff)
        {
            Unit* target = me;
            if(rand()%2 == 1)
            {
                auto itr = Adds.begin() + rand()%Adds.size();
                if(Unit* pAdd = ObjectAccessor::GetUnit(*me, (*itr)->guid))
                    if(!pAdd->HasAuraEffect(SPELL_SHIELD, 0) && pAdd->IsAlive())
                        target = pAdd;
            }
            DoCast(target, SPELL_SHIELD);
            ShieldTimer = 7500;
        }else ShieldTimer -= diff;

        if(DispelTimer < diff)
        {
            Unit* target = nullptr;
            bool friendly = false;
            if(rand()%2 == 1)
                target = SelectTarget(SELECT_TARGET_RANDOM, 0);
            else
            {
                friendly = true;
                if(rand()%2 == 1)
                    target = me;
                else
                {
                    auto itr = Adds.begin() + rand()%Adds.size();
                    Unit* pAdd = ObjectAccessor::GetUnit(*me, (*itr)->guid);
                    if(pAdd && pAdd->IsAlive())
                        target = pAdd;
                }
            }
            if(target)
            {
                DoCast(target, SPELL_DISPEL_MAGIC);
                DispelTimer = 12000;
            }
        }else DispelTimer -= diff;

        if(SWPainTimer < diff)
        {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0),Heroic ? SPELL_SW_PAIN_HEROIC : SPELL_SW_PAIN_NORMAL);
            SWPainTimer = 10000;
        }else SWPainTimer -= diff;

        /*
        if(CombatPulseTimer < diff)
        {
            DoZoneInCombat();
            for(uint8 i = 0; i < Adds.size(); ++i)
            {
                if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add[i]->guid))
                    if(pAdd->IsAlive())
                        DoZoneInCombat(pAdd);
            }

            CombatPulseTimer = 10000;
        }else CombatPulseTimer -= diff;*/

        DoMeleeAttackIfReady();
    }
};

#define SPELL_HEALING_POTION    15503

struct boss_priestess_guestAI : public ScriptedAI
{
    boss_priestess_guestAI(Creature* c) : ScriptedAI(c)
    {
        Group.clear();
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        AcquireGUIDs();
    }

    InstanceScript* pInstance;

    std::vector<Add*> Group;

    uint32 ResetThreatTimer;

    bool UsedPotion;

    void Reset()
    override {
        me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
        UsedPotion = false;
        if(pInstance)
        {
            Creature *boss = (ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_DELRISSA)));
            if (boss && boss->IsDead())
                boss->Respawn();
        }
        ResetThreatTimer = 5000 + rand()%15000;             // These guys like to switch targets often, and are not meant to be tanked.
    }

    void EnterCombat(Unit* who)
    override {
        Creature* Delrissa = (ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_DELRISSA)));
        if(Delrissa)
            ((boss_priestess_delrissaAI*)Delrissa->AI())->SetAddsInCombat(who);
    }

    void JustDied(Unit* killer)
    override {
        if(!pInstance)
        {
            error_log(ERROR_INST_DATA);
            return;
        }

        Creature* Delrissa = (ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_DELRISSA)));
        if(Delrissa)
        {
            ((boss_priestess_delrissaAI*)Delrissa->AI())->KilledLackey();
            if(!Delrissa->IsAlive() && pInstance->GetData(DATA_DELRISSA_DEATH_COUNT) > 3)
                ((boss_priestess_delrissaAI*)Delrissa->AI())->CheckLootable();

            pInstance->SetData(DATA_DELRISSA_DEATH_COUNT, 1);
        }
    }

    void KilledUnit(Unit* victim)
    override {
        if(!pInstance)
        {
            error_log(ERROR_INST_DATA);
            return;
        }

        Creature* Delrissa = (ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_DELRISSA)));
        if(Delrissa)
            Delrissa->AI()->KilledUnit(victim);
    }

    void AcquireGUIDs()
    {
        if(!pInstance)
        {
            error_log(ERROR_INST_DATA);
            return;
        }

        Creature* Delrissa = (ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_DELRISSA)));
        if(Delrissa)
        {
            Group = /*((boss_priestess_delrissaAI*)Delrissa->AI())->*/Adds;
            auto  dAdd = new Add(Delrissa->GetEntry(), Delrissa->GetGUID());
            Group.push_back(dAdd);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(((me->GetHealth()*100 / me->GetMaxHealth()) < 25) && !UsedPotion)
        {
            DoCast(me, SPELL_HEALING_POTION, true);
            UsedPotion = true;
        }

        if(ResetThreatTimer < diff)
        {
            DoResetThreat();
            ResetThreatTimer = 5000 + rand()%15000;
        }else ResetThreatTimer -= diff;
    }
};

enum eKaganiNightstrike {
    SPELL_KIDNEY_SHOT        = 27615,
    SPELL_GOUGE              = 12540,
    SPELL_KICK               = 27613,
    SPELL_VANISH             = 44290,
    SPELL_BACKSTAB           = 15657,
    SPELL_EVISCERATE         = 27611
};

struct boss_kagani_nightstrikeAI : public boss_priestess_guestAI
{
    //Rogue
    boss_kagani_nightstrikeAI(Creature *c) : boss_priestess_guestAI(c) {}

    uint32 Gouge_Timer;
    uint32 Kick_Timer;
    uint32 Vanish_Timer;
    uint32 Eviscerate_Timer;
    uint32 Wait_Timer;
    bool InVanish;

    void Reset()
    override {
        Gouge_Timer = 5500;
        Kick_Timer = 7000;
        Vanish_Timer = 2000;
        Eviscerate_Timer = 6000;
        Wait_Timer = 5000;
        InVanish = false;
        me->SetVisibility(VISIBILITY_ON);

        boss_priestess_guestAI::Reset();
    }
    
    void EnterCombat(Unit* who)
    override {
        for(auto & Add : Adds)
            if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add->guid))
                pAdd->AddThreat(who, 1.0f);
                
        boss_priestess_guestAI::EnterCombat(who);
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim() )
            return;

        boss_priestess_guestAI::UpdateAI(diff);

        if(Vanish_Timer < diff)
        {
            me->SetVisibility(VISIBILITY_OFF);      // ...? Hacklike
            DoCast(me, SPELL_VANISH);
            InVanish = true;
            Vanish_Timer = 30000;
            Wait_Timer = 10000;
            DoResetThreat();
            me->AddThreat(SelectTarget(SELECT_TARGET_RANDOM, 0), 1000.0f);
        }else Vanish_Timer -= diff;

        if(InVanish)
        {
            if(Wait_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_BACKSTAB, true);
                DoCast(me->GetVictim(), SPELL_KIDNEY_SHOT, true);
                me->SetVisibility(VISIBILITY_ON);       // ...? Hacklike
                InVanish = false;
            }else Wait_Timer -= diff;
        }

        if(Gouge_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_GOUGE);
            DoModifyThreatPercent(me->GetVictim(),-100);
            Gouge_Timer = 5500;
        }else Gouge_Timer -= diff;

        if(Kick_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_KICK);
            Kick_Timer = 7000;
        }else Kick_Timer -= diff;

        if(Eviscerate_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_EVISCERATE);
            Eviscerate_Timer = 4000;
        }else Eviscerate_Timer -= diff;

        if(!InVanish)
            DoMeleeAttackIfReady();
    }
};

enum eEllrisDuskhallow {
    SPELL_IMMOLATE               = 44267,
    SPELL_SHADOW_BOLT            = 12471,
    SPELL_SEED_OF_CORRUPTION     = 44141,
    SPELL_CURSE_OF_AGONY         = 14875,
    SPELL_FEAR                   = 38595,
    SPELL_IMP_FIREBALL           = 44164,
    SPELL_SUMMON_IMP             = 44163
};

//#define CREATURE_IMP                 44163
//#define CREATURE_FIZZLE              24656

/*struct mob_fizzleAI : public ScriptedAI
{
    mob_fizzleAI(Creature *c) : ScriptedAI(c) {}

    uint64 EllrisGUID;
    uint32 Firebal_Timer;

    void Reset() { EllrisGUID = 0; }

    void KilledUnit(Unit* victim);
    void JustDied(Unit* killer);

    void EnterCombat(Unit* who){}

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim() )
            return;

        //Chain cast
        if (!me->IsNonMeleeSpellCast(false))
            DoCast(me->GetVictim(),SPELL_IMP_FIREBALL);
        else DoMeleeAttackIfReady();
    }
};*/

struct boss_ellris_duskhallowAI : public boss_priestess_guestAI
{
    //Warlock
    boss_ellris_duskhallowAI(Creature *c) : boss_priestess_guestAI(c)
    {
    }

    bool HasSummonedImp;

    uint32 Immolate_Timer;
    uint32 Shadow_Bolt_Timer;
    uint32 Seed_of_Corruption_Timer;
    uint32 Curse_of_Agony_Timer;
    uint32 Fear_Timer;

    void Reset()
    override {
        //HasSummonedImp = false;

        Immolate_Timer = 6000;
        Shadow_Bolt_Timer = 3000;
        Seed_of_Corruption_Timer = 2000;
        Curse_of_Agony_Timer = 1000;
        Fear_Timer = 10000;

        boss_priestess_guestAI::Reset();
    }
    
    void EnterCombat(Unit* who)
    override {
        for(auto & Add : Adds)
            if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add->guid))
                pAdd->AddThreat(who, 1.0f);
                
        boss_priestess_guestAI::EnterCombat(who);
    }

    void JustDied(Unit* killer)
    override {
        boss_priestess_guestAI::JustDied(killer);
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!HasSummonedImp)
        {
            //Imp will not despawn unless it's killed, even if owner dies, this is correct way.
            DoCast(me,SPELL_SUMMON_IMP);
            HasSummonedImp = true;
        }

        if(!UpdateVictim() )
            return;

        boss_priestess_guestAI::UpdateAI(diff);

        if(Immolate_Timer < diff)
        {
            DoCast(me->GetVictim(),SPELL_IMMOLATE);
            Immolate_Timer = 6000;
        }else Immolate_Timer -= diff;

        if(Shadow_Bolt_Timer < diff)
        {
            DoCast(me->GetVictim(),SPELL_SHADOW_BOLT);
            Shadow_Bolt_Timer = 5000;
        }else Shadow_Bolt_Timer -= diff;

        if(Seed_of_Corruption_Timer < diff)
        {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_SEED_OF_CORRUPTION);
            Seed_of_Corruption_Timer = 10000;
        }else Seed_of_Corruption_Timer -= diff;

        if(Curse_of_Agony_Timer < diff)
        {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_CURSE_OF_AGONY);
            Curse_of_Agony_Timer = 13000;
        }else Curse_of_Agony_Timer -= diff;

        if(Fear_Timer < diff)
        {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_FEAR);
            Fear_Timer = 10000;
        }else Fear_Timer -= diff;

        if (me->GetDistance(me->GetVictim()) <= 10)
            me->StopMoving();
        //DoMeleeAttackIfReady();//should not melee, she's a warlock
    }
};

/*void mob_fizzleAI::JustDied(Unit* killer)
{
    if(Creature* Ellris = (ObjectAccessor::GetCreature(*me, EllrisGUID)))
        ((boss_ellris_duskhallowAI*)Ellris->AI())->ImpGUID = 0;
}

void mob_fizzleAI::KilledUnit(Unit* victim)
{
    if(Creature* Ellris = (ObjectAccessor::GetCreature(*me, EllrisGUID)))
        ((boss_ellris_duskhallowAI*)Ellris->AI())->KilledUnit(victim);
}*/

enum eEramasBrightblaze {
    SPELL_KNOCKDOWN            = 11428,
    SPELL_SNAP_KICK            = 46182
};

struct boss_eramas_brightblazeAI : public boss_priestess_guestAI
{
    //Monk
    boss_eramas_brightblazeAI(Creature *c) : boss_priestess_guestAI(c) {}

    uint32 Knockdown_Timer;
    uint32 Snap_Kick_Timer;

    void Reset()
    override {
        Knockdown_Timer = 6000;
        Snap_Kick_Timer = 4500;

        boss_priestess_guestAI::Reset();
    }
    
    void EnterCombat(Unit* who)
    override {
        for(auto & Add : Adds)
            if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add->guid))
                pAdd->AddThreat(who, 1.0f);
                
        boss_priestess_guestAI::EnterCombat(who);
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim() )
            return;

        boss_priestess_guestAI::UpdateAI(diff);

        if(Knockdown_Timer < diff)
        {
            DoCast(me->GetVictim(),SPELL_KNOCKDOWN);
            Knockdown_Timer = 6000;
        }else Knockdown_Timer -= diff;

        if(Snap_Kick_Timer < diff)
        {
            DoCast(me->GetVictim(),SPELL_SNAP_KICK);
            Snap_Kick_Timer  = 4500;
        }else Snap_Kick_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

enum eYazzai {
    SPELL_POLYMORPH             = 13323,
    SPELL_ICE_BLOCK             = 27619,
    SPELL_BLIZZARD              = 44178,
    SPELL_ICE_LANCE             = 46194,
    SPELL_CONE_OF_COLD          = 38384,
    SPELL_FROSTBOLT             = 15043,
    SPELL_BLINK                 = 14514
};

struct boss_yazzaiAI : public boss_priestess_guestAI
{
    //Mage
    boss_yazzaiAI(Creature *c) : boss_priestess_guestAI(c)  {}

    bool HasIceBlocked;

    uint32 Polymorph_Timer;
    uint32 Ice_Block_Timer;
    uint32 Wait_Timer;
    uint32 Blizzard_Timer;
    uint32 Ice_Lance_Timer;
    uint32 Cone_of_Cold_Timer;
    uint32 Frostbolt_Timer;
    uint32 Blink_Timer;

    void Reset()
    override {
        HasIceBlocked = false;

        Polymorph_Timer = 1000;
        Ice_Block_Timer = 20000;
        Wait_Timer = 10000;
        Blizzard_Timer = 8000;
        Ice_Lance_Timer = 12000;
        Cone_of_Cold_Timer = 10000;
        Frostbolt_Timer = 3000;
        Blink_Timer = 8000;

        boss_priestess_guestAI::Reset();
    }
    
    void EnterCombat(Unit* who)
    override {
        for(auto & Add : Adds)
            if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add->guid))
                pAdd->AddThreat(who, 1.0f);
                
        boss_priestess_guestAI::EnterCombat(who);
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim() )
            return;

        boss_priestess_guestAI::UpdateAI(diff);

        if(Polymorph_Timer < diff)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
            {
                DoCast(target, SPELL_POLYMORPH);
                DoModifyThreatPercent(target,-100);
                Polymorph_Timer = 20000;
            }
        }else Polymorph_Timer -= diff;

        if(((me->GetHealth()*100 / me->GetMaxHealth()) < 35) && !HasIceBlocked)
        {
            DoCast(me, SPELL_ICE_BLOCK);
            HasIceBlocked = true;
        }

        if(Blizzard_Timer < diff)
        {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_BLIZZARD);
            Blizzard_Timer = 8000;
        }else Blizzard_Timer -= diff;

        if(Ice_Lance_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_ICE_LANCE);
            Ice_Lance_Timer = 12000;
        }else Ice_Lance_Timer -= diff;

        if(Cone_of_Cold_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_CONE_OF_COLD);
            Cone_of_Cold_Timer = 10000;
        }else Cone_of_Cold_Timer -= diff;

        if(Frostbolt_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_FROSTBOLT);
            Frostbolt_Timer = 8000;
        }else Frostbolt_Timer -= diff;

        if(Blink_Timer < diff)
        {
            bool InMeleeRange = false;
            std::list<HostileReference*>& t_list = me->getThreatManager().getThreatList();
            for(auto & itr : t_list)
            {
                if(Unit* target = ObjectAccessor::GetUnit(*me, itr->getUnitGuid()))
                    //if in melee range
                    if (target->IsWithinDistInMap(me, 5))
                    {
                        InMeleeRange = true;
                        break;
                    }
            }
            //if anybody is in melee range than escape by blink
            if(InMeleeRange)
            {
                //DoCast(me, SPELL_BLINK);  //blink does not work on npcs
                float x,y,z;
                me->GetPosition(x,y,z);
                x = rand()%2 ? x+10+rand()%10 : x-10-rand()%10;
                y = rand()%2 ? y+10+rand()%10 : y-10-rand()%10;
                DoTeleportTo(x, y, z);
            }
            Blink_Timer = 8000;
        }else Blink_Timer -= diff;

        if (me->GetVictim() && me->GetDistance(me->GetVictim()) <= 10)
            me->StopMoving();

        //DoMeleeAttackIfReady(); //mage type, no melee needed
    }
};

enum eWarlordSalaris {
    SPELL_INTERCEPT_STUN         = 27577,
    SPELL_DISARM                 = 27581,
    SPELL_PIERCING_HOWL          = 23600,
    SPELL_FRIGHTENING_SHOUT      = 19134,
    SPELL_HAMSTRING              = 27584,
    SPELL_BATTLE_SHOUT           = 27578,
    SPELL_MORTAL_STRIKE          = 44268
};

struct boss_warlord_salarisAI : public boss_priestess_guestAI
{
    //Warrior
    boss_warlord_salarisAI(Creature *c) : boss_priestess_guestAI(c) {}

    uint32 Intercept_Stun_Timer;
    uint32 Disarm_Timer;
    uint32 Piercing_Howl_Timer;
    uint32 Frightening_Shout_Timer;
    uint32 Hamstring_Timer;
    uint32 Mortal_Strike_Timer;

    void Reset()
    override {
        Intercept_Stun_Timer = 500;
        Disarm_Timer = 6000;
        Piercing_Howl_Timer = 10000;
        Frightening_Shout_Timer = 18000;
        Hamstring_Timer = 4500;
        Mortal_Strike_Timer = 8000;
        DoCast(me, SPELL_BATTLE_SHOUT);
        boss_priestess_guestAI::Reset();
    }

    void EnterCombat(Unit* who)
    override {
        DoCast(me, SPELL_BATTLE_SHOUT);
        
        for(auto & Add : Adds)
            if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add->guid))
                pAdd->AddThreat(who, 1.0f);
                
        boss_priestess_guestAI::EnterCombat(who);
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim() )
            return;

        boss_priestess_guestAI::UpdateAI(diff);

        if(Intercept_Stun_Timer < diff)
        {
            bool InMeleeRange = false;
            std::list<HostileReference*>& t_list = me->getThreatManager().getThreatList();
            for(auto & itr : t_list)
            {
                if(Unit* target = ObjectAccessor::GetUnit(*me, itr->getUnitGuid()))
                                                            //if in melee range
                    if (target->IsWithinDistInMap(me, 5))
                {
                    InMeleeRange = true;
                    break;
                }
            }
            //if nobody is in melee range than try to use Intercept
            if(!InMeleeRange)
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_INTERCEPT_STUN);
            Intercept_Stun_Timer = 10000;
        }else Intercept_Stun_Timer -= diff;

        if(Disarm_Timer < diff)
        {
            DoCast(me->GetVictim(),SPELL_DISARM);
            Disarm_Timer = 6000;
        }else Disarm_Timer -= diff;

        if(Hamstring_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_HAMSTRING);
            Hamstring_Timer = 4500;
        }else Hamstring_Timer -= diff;

        if(Mortal_Strike_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_MORTAL_STRIKE);
            Mortal_Strike_Timer = 4500;
        }else Mortal_Strike_Timer -= diff;

        if(Piercing_Howl_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_PIERCING_HOWL);
            Piercing_Howl_Timer = 10000;
        }else Piercing_Howl_Timer -= diff;

        if(Frightening_Shout_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_FRIGHTENING_SHOUT);
            Frightening_Shout_Timer = 18000;
        }else Frightening_Shout_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

enum eGaraxxas {
    SPELL_AIMED_SHOT            = 44271,
    SPELL_SHOOT                 = 15620,
    SPELL_CONCUSSIVE_SHOT       = 27634,
    TRIGGER_CONCUSSIVE_SHOT     = 19410,
    SPELL_MULTI_SHOT            = 31942,
    SPELL_WING_CLIP             = 44286,
    SPELL_FREEZING_TRAP         = 44136,

    CREATURE_SLIVER             = 24552
};

/*struct mob_sliverAI : public ScriptedAI
{
    mob_sliverAI(Creature *c) : ScriptedAI(c) {}

    uint64 GaraxxasGUID;

    void Reset() { GaraxxasGUID = 0; }

    void KilledUnit(Unit* victim);
    void JustDied(Unit* killer);

    void EnterCombat(Unit* who){}

};*/

struct boss_garaxxasAI : public boss_priestess_guestAI
{
    //Hunter
    boss_garaxxasAI(Creature *c) : boss_priestess_guestAI(c) {}

    //uint64 SliverGUID;
    bool HasSummonedSliver;

    uint32 Aimed_Shot_Timer;
    uint32 Shoot_Timer;
    uint32 Concussive_Shot_Timer;
    uint32 Multi_Shot_Timer;
    uint32 Wing_Clip_Timer;
    uint32 Freezing_Trap_Timer;
    uint32 StopMoving;
    bool Stopped;

    void Reset()
    override {
        //SliverGUID = 0;
        //HasSummonedSliver = false;

        Aimed_Shot_Timer = 6000;
        Shoot_Timer = 2500;
        Concussive_Shot_Timer = 8000;
        Multi_Shot_Timer = 10000;
        Wing_Clip_Timer = 4000;
        Freezing_Trap_Timer = 15000;
        StopMoving = 2000;
        Stopped = false;

        boss_priestess_guestAI::Reset();
    }
    
    void EnterCombat(Unit* who)
    override {
        for(auto & Add : Adds)
            if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add->guid))
                pAdd->AddThreat(who, 1.0f);
                
        boss_priestess_guestAI::EnterCombat(who);
    }

    void JustDied(Unit* killer)
    override {
        boss_priestess_guestAI::JustDied(killer);
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!HasSummonedSliver)
        {
            Creature* Sliver = me->SummonCreature(CREATURE_SLIVER, 0, 0, 0, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
            if(Sliver)
            {
                //((mob_sliverAI*)Sliver->AI())->GaraxxasGUID = me->GetGUID();
                //SliverGUID = Sliver->GetGUID();
                HasSummonedSliver = true;
            }
        }

        if(!UpdateVictim() )
            return;

        boss_priestess_guestAI::UpdateAI(diff);

        if(me->IsWithinDistInMap(me->GetVictim(), 5))
        {
            if(Wing_Clip_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_WING_CLIP);
                Wing_Clip_Timer = 4000;
            }else Wing_Clip_Timer -= diff;

            if(Freezing_Trap_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_FREEZING_TRAP);
                DoModifyThreatPercent(me->GetVictim(),-100);
                Freezing_Trap_Timer = 30000;
            }else Freezing_Trap_Timer -= diff;

            if(!me->GetVictim()->HasUnitState(UNIT_STATE_STUNNED | UNIT_STATE_ROOT | UNIT_STATE_CONFUSED | UNIT_STATE_DISTRACTED))
                DoMeleeAttackIfReady();
        }else
        {
            if(Concussive_Shot_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_CONCUSSIVE_SHOT);
                Concussive_Shot_Timer = 8000;
            }else Concussive_Shot_Timer -= diff;

            if(Multi_Shot_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_MULTI_SHOT);
                Multi_Shot_Timer = 10000;
            }else Multi_Shot_Timer -= diff;

            if(Aimed_Shot_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_AIMED_SHOT);
                Aimed_Shot_Timer = 6000;
            }else Aimed_Shot_Timer -= diff;

            if(Shoot_Timer < diff)
            {
                DoCast(me->GetVictim(), SPELL_SHOOT);
                Shoot_Timer = 2500;
            }else Shoot_Timer -= diff;
        }
        if(StopMoving < diff)
        {
            if(Stopped)
                Stopped = false;
            else
                Stopped = true;
            StopMoving = 2000+rand()%5000;
        }else StopMoving -= diff;
        if (Stopped)
            me->StopMoving();
    }
};

/*void mob_sliverAI::JustDied(Unit* killer)
{
    if(Creature* Garaxxas = (ObjectAccessor::GetCreature(*me, GaraxxasGUID)))
        ((boss_garaxxasAI*)Garaxxas->AI())->SliverGUID = 0;
}

void mob_sliverAI::KilledUnit(Unit* victim)
{
    if(Creature* Garaxxas = (ObjectAccessor::GetCreature(*me, GaraxxasGUID)))
        ((boss_garaxxasAI*)Garaxxas->AI())->KilledUnit(victim);
}*/

enum eApoko {
    SPELL_WINDFURY_TOTEM         = 27621,
    SPELL_WAR_STOMP              = 46026,
    SPELL_PURGE                  = 27626,
    SPELL_LESSER_HEALING_WAVE    = 44256,
    SPELL_FROST_SHOCK            = 21401,
    SPELL_FIRE_NOVA_TOTEM        = 44257,
    SPELL_EARTHBIND_TOTEM        = 15786
};

struct boss_apokoAI : public boss_priestess_guestAI
{
    //Shaman
    boss_apokoAI(Creature *c) : boss_priestess_guestAI(c) {}

    uint32 Totem_Timer;
    uint8  Totem_Amount;
    uint32 War_Stomp_Timer;
    uint32 Purge_Timer;
    uint32 Healing_Wave_Timer;
    uint32 Frost_Shock_Timer;

    void Reset()
    override {
        Totem_Timer = 2000;
        Totem_Amount = 1;
        War_Stomp_Timer = 10000;
        Purge_Timer = 8000;
        Healing_Wave_Timer = 5000;
        Frost_Shock_Timer = 7000;

        boss_priestess_guestAI::Reset();
    }
    
    void EnterCombat(Unit* who)
    override {
        for(auto & Add : Adds)
            if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add->guid))
                pAdd->AddThreat(who, 1.0f);
                
        boss_priestess_guestAI::EnterCombat(who);
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim() )
            return;

        boss_priestess_guestAI::UpdateAI(diff);

        if(Totem_Timer < diff)
        {
            switch(rand()%3)
            {
                case 0: DoCast(me, SPELL_WINDFURY_TOTEM); break;
                case 1: DoCast(me, SPELL_FIRE_NOVA_TOTEM); break;
                case 2: DoCast(me, SPELL_EARTHBIND_TOTEM); break;
            }
            ++Totem_Amount;
            Totem_Timer = Totem_Amount*2000;
        }else Totem_Timer -= diff;

        if(War_Stomp_Timer < diff)
        {
            DoCast(me, SPELL_WAR_STOMP);
            War_Stomp_Timer = 10000;
        }else War_Stomp_Timer -= diff;

        if(Purge_Timer < diff)
        {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_PURGE);
            Purge_Timer = 15000;
        }else Purge_Timer -= diff;

        if(Frost_Shock_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_FROST_SHOCK);
            Frost_Shock_Timer = 7000;
        }else Frost_Shock_Timer -= diff;

        if(Healing_Wave_Timer < diff)
        {
            // std::vector<Add*>::iterator itr = Group.begin() + rand()%Group.size();
            // uint64 guid = (*itr)->guid;
            // if(guid)
            // {
            //   Unit* pAdd = ObjectAccessor::GetUnit(*me, (*itr)->guid);
            //   if(pAdd && pAdd->IsAlive())
            //   {
            DoCast(me, SPELL_LESSER_HEALING_WAVE);
            Healing_Wave_Timer = 5000;
            //    }
            // }
        }else Healing_Wave_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

enum eZelfan {
    SPELL_GOBLIN_DRAGON_GUN        = 44272,
    SPELL_ROCKET_LAUNCH            = 44137,
    SPELL_RECOMBOBULATE            = 44274,
    SPELL_HIGH_EXPLOSIVE_SHEEP     = 44276,
    SPELL_FEL_IRON_BOMB            = 46024,
    SPELL_SHEEP_EXPLOSION          = 44279,

    CREATURE_EXPLOSIVE_SHEEP       = 24715
};

struct boss_zelfanAI : public boss_priestess_guestAI
{
    //Engineer
    boss_zelfanAI(Creature *c) : boss_priestess_guestAI(c) {}

    uint32 Goblin_Dragon_Gun_Timer;
    uint32 Rocket_Launch_Timer;
    uint32 Recombobulate_Timer;
    uint32 High_Explosive_Sheep_Timer;
    uint32 Fel_Iron_Bomb_Timer;

    void Reset()
    override {
        Goblin_Dragon_Gun_Timer = 20000;
        Rocket_Launch_Timer = 7000;
        Recombobulate_Timer = 4000;
        High_Explosive_Sheep_Timer = 10000;
        Fel_Iron_Bomb_Timer = 15000;

        boss_priestess_guestAI::Reset();
    }
    
    void EnterCombat(Unit* who)
    override {
        for(auto & Add : Adds)
            if(Unit* pAdd = ObjectAccessor::GetUnit(*me, Add->guid))
                pAdd->AddThreat(who, 1.0f);
                
        boss_priestess_guestAI::EnterCombat(who);
    }
    
    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim() )
            return;

        boss_priestess_guestAI::UpdateAI(diff);

        if(Goblin_Dragon_Gun_Timer < diff)
        {
            if (me->GetDistance(me->GetVictim()) <= 5)
            {
                Goblin_Dragon_Gun_Timer = 10000;
                DoCast(me->GetVictim(), SPELL_GOBLIN_DRAGON_GUN);
            }else Goblin_Dragon_Gun_Timer = 2000;
        }else Goblin_Dragon_Gun_Timer -= diff;

        if(Rocket_Launch_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_ROCKET_LAUNCH);
            Rocket_Launch_Timer = 9000;
        }else Rocket_Launch_Timer -= diff;

        if(Fel_Iron_Bomb_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_FEL_IRON_BOMB);
            Fel_Iron_Bomb_Timer = 15000;
        }else Fel_Iron_Bomb_Timer -= diff;

        if(Recombobulate_Timer < diff)
        {
            for(auto & i : Group)
                if(Unit* pAdd = ObjectAccessor::GetUnit(*me, i->guid))
                    if(pAdd->IsPolymorphed())
                    {
                        DoCast(pAdd, SPELL_RECOMBOBULATE);
                        break;
                    }
        }else Recombobulate_Timer -= diff;

        if(High_Explosive_Sheep_Timer < diff)
        {
            DoCast(me, SPELL_HIGH_EXPLOSIVE_SHEEP);
            High_Explosive_Sheep_Timer = 65000;
        }else High_Explosive_Sheep_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

//struct mob_high_explosive_sheepAI : public ScriptedAI
//{
//    mob_high_explosive_sheepAI(Creature *c) : ScriptedAI(c) {}
//
//    uint32 Explosion_Timer;
//
//    void Reset()
//    {
//        Explosion_Timer = 60000;
//    }
//
//    void JustDied(Unit *Killer){}
//
//    void EnterCombat(Unit *who){}
//
//    void UpdateAI(const uint32 diff)
//    {
//        if(Explosion_Timer < diff)
//        {
//            DoCast(me->GetVictim(), SPELL_SHEEP_EXPLOSION);
//        }else
//            Explosion_Timer -= diff;
//    }
//};

/*CreatureAI* GetAI_mob_sliver(Creature *_Creature)
{
    return new mob_sliverAI (_Creature);
};*/

//CreatureAI* GetAI_mob_high_explosive_sheep(Creature *_Creature)
//{
//    return new mob_high_explosive_sheepAI (_Creature);
//};

/*CreatureAI* GetAI_mob_fizzle(Creature *_Creature)
{
    return new mob_fizzleAI (_Creature);
};*/

CreatureAI* GetAI_boss_priestess_delrissa(Creature *_Creature)
{
    return new boss_priestess_delrissaAI (_Creature);
}

CreatureAI* GetAI_boss_kagani_nightstrike(Creature *_Creature)
{
    return new boss_kagani_nightstrikeAI (_Creature);
}

CreatureAI* GetAI_ellris_duskhallow(Creature *_Creature)
{
    return new boss_ellris_duskhallowAI (_Creature);
}

CreatureAI* GetAI_eramas_brightblaze(Creature *_Creature)
{
    return new boss_eramas_brightblazeAI (_Creature);
}

CreatureAI* GetAI_yazzai(Creature *_Creature)
{
    return new boss_yazzaiAI (_Creature);
}

CreatureAI* GetAI_warlord_salaris(Creature *_Creature)
{
    return new boss_warlord_salarisAI (_Creature);
}

CreatureAI* GetAI_garaxxas(Creature *_Creature)
{
    return new boss_garaxxasAI (_Creature);
}

CreatureAI* GetAI_apoko(Creature *_Creature)
{
    return new boss_apokoAI (_Creature);
}

CreatureAI* GetAI_zelfan(Creature *_Creature)
{
    return new boss_zelfanAI (_Creature);
}

void AddSC_boss_priestess_delrissa()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="boss_priestess_delrissa";
    newscript->GetAI = &GetAI_boss_priestess_delrissa;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="boss_kagani_nightstrike";
    newscript->GetAI = &GetAI_boss_kagani_nightstrike;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="boss_ellris_duskhallow";
    newscript->GetAI = &GetAI_ellris_duskhallow;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="boss_eramas_brightblaze";
    newscript->GetAI = &GetAI_eramas_brightblaze;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="boss_yazzai";
    newscript->GetAI = &GetAI_yazzai;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="boss_warlord_salaris";
    newscript->GetAI = &GetAI_warlord_salaris;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="boss_garaxxas";
    newscript->GetAI = &GetAI_garaxxas;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="boss_apoko";
    newscript->GetAI = &GetAI_apoko;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="boss_zelfan";
    newscript->GetAI = &GetAI_zelfan;
    sScriptMgr->RegisterOLDScript(newscript);

    /*newscript = new OLDScript;
    newscript->Name="mob_high_explosive_sheep";
    newscript->GetAI = &GetAI_mob_high_explosive_sheep;
    sScriptMgr->RegisterOLDScript(newscript);*/

    /*newscript = new OLDScript;
    newscript->Name="mob_fizzle";
    newscript->GetAI = &GetAI_mob_fizzle;
    sScriptMgr->RegisterOLDScript(newscript);*/

    /*newscript = new OLDScript;
    newscript->Name="mob_sliver";
    newscript->GetAI = &GetAI_mob_sliver;
    sScriptMgr->RegisterOLDScript(newscript);*/
}

