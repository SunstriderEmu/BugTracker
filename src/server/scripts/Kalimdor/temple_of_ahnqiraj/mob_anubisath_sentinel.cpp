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
SDName: mob_anubisath_sentinel
SD%Complete: 95
SDComment: Shadow storm is not properly implemented in core it should only target ppl outside of melee range.
SDCategory: Temple of Ahn'Qiraj
EndScriptData */


#include "WorldPacket.h"

#include "Item.h"
#include "Player.h"
#include "Spell.h"

#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"

#define SPELL_MENDING_BUFF      2147

#define SPELL_KNOCK_BUFF        21737
#define SPELL_KNOCK             25778
#define SPELL_MANAB_BUFF        812
#define SPELL_MANAB             25779

#define SPELL_REFLECTAF_BUFF    13022
#define SPELL_REFLECTSFr_BUFF   19595
#define SPELL_THORNS_BUFF       25777

#define SPELL_THUNDER_BUFF      2834
#define SPELL_THUNDER           8732

#define SPELL_MSTRIKE_BUFF      9347
#define SPELL_MSTRIKE           24573

#define SPELL_STORM_BUFF        2148
#define SPELL_STORM             26546

class NearbyAQSentinel
{
    public:
        NearbyAQSentinel(Unit const* obj) : i_obj(obj) {}
        bool operator()(Unit* u)
        {
            if (u->GetEntry() == 15264 && i_obj->IsWithinDistInMap(u, 70) && !u->IsDead())
                return true;
            else
                return false;
        }
    private:
        Unit const* i_obj;
};

struct aqsentinelAI;
class SentinelAbilityAura : public Aura
{
    public:
        ~SentinelAbilityAura() override;
        Unit* GetTriggerTarget() const;
        SentinelAbilityAura(Creature* abilityOwner, SpellInfo *spell, uint32 ability, uint32 eff);
    protected:
        Creature* aOwner;
        int32 currentBasePoints;
        uint32 abilityId;
};

enum AQSentinelMessage
{
    MESSAGE_GET_HATED_MANA_USER,
};

class mob_anubisath_sentinel : public CreatureScript
{
public:
    mob_anubisath_sentinel() : CreatureScript("mob_anubisath_sentinel")
    { }

    class aqsentinelAI : public ScriptedAI
    {
        public:
        uint32 ability;
        int abselected;
    
        void selectAbility(int asel)
        {
            switch (asel)
            {
                case 0: ability = SPELL_MENDING_BUFF;break;
                case 1: ability = SPELL_KNOCK_BUFF;break;
                case 2: ability = SPELL_MANAB_BUFF;break;
                case 3: ability = SPELL_REFLECTAF_BUFF;break;
                case 4: ability = SPELL_REFLECTSFr_BUFF;break;
                case 5: ability = SPELL_THORNS_BUFF;break;
                case 6: ability = SPELL_THUNDER_BUFF;break;
                case 7: ability = SPELL_MSTRIKE_BUFF;break;
                case 8: ability = SPELL_STORM_BUFF;break;
            }
        }
    
        aqsentinelAI(Creature *c) : ScriptedAI(c)
        {
            ClearBudyList();
            abselected = 0;                                     // just initialization of variable
        }
    
        Creature *nearby[3];
    
        void ClearBudyList()
        {
            nearby[0] = nearby[1] = nearby[2] = nullptr;
        }
    
        void AddBuddyToList(Creature *c)
        {
            if (c==me)
                return;
            for (auto & i : nearby)
            {
                if (i == c)
                    return;
                if (!i)
                {
                    i = c;
                    return;
                }
            }
        }
    
        void GiveBuddyMyList(Creature *c)
        {
            aqsentinelAI *cai = (mob_anubisath_sentinel::aqsentinelAI*)(c->AI());
            for (auto & i : nearby)
                if (i && i!=c)
                    cai->AddBuddyToList(i);
            cai->AddBuddyToList(me);
        }
    
        void SendMyListToBuddies()
        {
            for (auto & i : nearby)
                if (i)
                    GiveBuddyMyList(i);
        }
    
        void CallBuddiesToAttack(Unit *who)
        {
            for (auto c : nearby)
            {
                if (c)
                {
                    if (!c->IsInCombat())
                    {
                        c->SetNoCallAssistance(true);
                        if(c->AI())
                            c->AI()->AttackStart(who);
                    }
                }
            }
        }
    
        void AddSentinelsNear(Unit *nears)
        {
            std::list<Creature*> assistList;
    
            NearbyAQSentinel u_check(nears);
            Trinity::CreatureListSearcher<NearbyAQSentinel> searcher(me, assistList, u_check);
            Cell::VisitGridObjects(me, searcher, MAX_SEARCHER_DISTANCE);
    
            for(auto & iter : assistList)
                AddBuddyToList(iter);
        }
    
        int pickAbilityRandom(bool *chosenAbilities)
        {
            for (int t = 0; t < 2; t++)
            {
                for (int i = !t ? (rand()%9) : 0; i < 9; i++)
                {
                    if (!chosenAbilities[i])
                    {
                        chosenAbilities[i] = true;
                        return i;
                    }
                }
            }
            return 0;                                           // should never happen
        }
    
        void GetOtherSentinels(Unit *who)
        {
            auto chosenAbilities = new bool[9];
            memset(chosenAbilities, 0, 9*sizeof(bool));
            selectAbility(pickAbilityRandom(chosenAbilities));
    
            ClearBudyList();
            AddSentinelsNear(me);
            int bli;
            for (bli = 0; bli < 3;bli++)
            {
                if (!nearby[bli])
                    break;
                AddSentinelsNear(nearby[bli]);
                ((mob_anubisath_sentinel::aqsentinelAI*)nearby[bli]->AI())->gatherOthersWhenAggro = false;
                ((mob_anubisath_sentinel::aqsentinelAI*)nearby[bli]->AI())->selectAbility(pickAbilityRandom(chosenAbilities));
            }
            /*if (bli < 3)
                me->Yell("I dont have enough buddies.", LANG_NEUTRAL, 0);*/
            SendMyListToBuddies();
            CallBuddiesToAttack(who);
        }
    
        bool gatherOthersWhenAggro;
    
        void Reset()
        override {
            if (!me->IsDead())
            {
                for (auto & i : nearby)
                {
                    if (!i)
                        continue;
                    if (i->IsDead())
                        i->Respawn();
                }
            }
            ClearBudyList();
            gatherOthersWhenAggro = true;
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, false);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, false);
        }
    
        void GainSentinelAbility(uint32 id)
        {
            const SpellInfo *spell = sSpellMgr->GetSpellInfo(id);
            for (int i=0; i<3; i++)
            {
                if (!spell->Effects[i].Effect)
                    continue;
                auto a = new SentinelAbilityAura(me, (SpellInfo *)spell, id, i);
                me->AddAura(a);
            }
            if (id == SPELL_KNOCK_BUFF)
            {
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
            }
        }
    
        void JustEngagedWith(Unit *who)
        override {
            if (gatherOthersWhenAggro)
                GetOtherSentinels(who);
    
            GainSentinelAbility(ability);
            DoZoneInCombat();
        }
    
        void JustDied(Unit*)
        override {
            for (auto sent : nearby)
            {
                if (!sent)
                    continue;
                if (sent->IsDead())
                    continue;
                int h = sent->GetHealth() + (sent->GetMaxHealth() / 2);
                if (h > sent->GetMaxHealth())
                    h = sent->GetMaxHealth();
                sent->SetHealth(h);
                ((mob_anubisath_sentinel::aqsentinelAI*)sent->AI())->GainSentinelAbility(ability);
            }
        }
    
        uint64 message(uint32 id, uint64 data) override
        {
            if (id == MESSAGE_GET_HATED_MANA_USER)
            {
                std::list<HostileReference*>::iterator i;
                for (i = me->GetThreatManager().getThreatList().begin(); i != me->GetThreatManager().getThreatList().end(); ++i)
                {
                    Unit* pUnit = ObjectAccessor::GetUnit((*me), (*i)->getUnitGuid());
                    if (pUnit->GetPowerType() == POWER_MANA)
                        return pUnit->GetGUID();
                }
            }
            return 0;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new aqsentinelAI(creature);
    }
};


void AddSC_mob_anubisath_sentinel()
{
    new mob_anubisath_sentinel();
}

SentinelAbilityAura::~SentinelAbilityAura() {}
Unit* SentinelAbilityAura::GetTriggerTarget() const
{
    switch (abilityId)
    {
        case SPELL_KNOCK_BUFF:
        case SPELL_THUNDER_BUFF:
        case SPELL_MSTRIKE_BUFF:
        case SPELL_STORM_BUFF:
            return aOwner->GetVictim();
        case SPELL_MANAB_BUFF:
        {
            if (!aOwner->AI())
                return nullptr;

            uint64 guid = aOwner->AI()->message(MESSAGE_GET_HATED_MANA_USER, 0);
            Unit* target = ObjectAccessor::GetUnit(*aOwner, guid);
            return target;
        }
        case SPELL_MENDING_BUFF:
        case SPELL_REFLECTAF_BUFF:
        case SPELL_REFLECTSFr_BUFF:
        case SPELL_THORNS_BUFF:
        default:
            return aOwner;
    }
}

SentinelAbilityAura::SentinelAbilityAura(Creature* abilityOwner, SpellInfo *spell, uint32 ability, uint32 eff)
: Aura(spell, eff, nullptr, abilityOwner, abilityOwner, nullptr)
{
    aOwner = abilityOwner;
    abilityId = ability;
    currentBasePoints = 0;
}

