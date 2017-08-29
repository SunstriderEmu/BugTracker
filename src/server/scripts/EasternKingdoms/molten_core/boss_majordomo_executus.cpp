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
SDName: Boss_Majordomo_Executus
SD%Complete: 30
SDComment: Correct spawning and Event NYI
SDCategory: Molten Core
EndScriptData */


#include "def_molten_core.h"

#define TEXT_ID_SUMMON_1 4995
#define TEXT_ID_SUMMON_2 5011
#define TEXT_ID_SUMMON_3 5012
 
#define GOSSIP_ITEM_SUMMON_1 "Dites m'en plus."
#define GOSSIP_ITEM_SUMMON_2 "Qu'avez vous d'autre à dire?"
#define GOSSIP_ITEM_SUMMON_3 "Vous nous avez défiés et nous sommes venus. Où est donc ce maître dont vous parlez?"

enum
{
    SAY_AGGRO                  = -1409003,
    SAY_SPAWN                  = -1409004,
    SAY_SLAY                   = -1409005,
    SAY_SPECIAL                = -1409006,
    SAY_DEFEAT                 = -1409007,

    // major spells
    SPELL_MAGIC_REFLECTION     = 20619,
    SPELL_DAMAGE_REFLECTION    = 21075,
    SPELL_BLASTWAVE            = 20229,
    SPELL_AEGIS                = 20620,                  //This is self casted whenever we are below 50%
    SPELL_TELEPORT             = 20618,
    SPELL_SUMMON_RAGNAROS      = 19774,

    // Healer spells
    SPELL_SHADOWSHOCK          = 20603,
    SPELL_SHADOWBOLT           = 21077,

    // Elite spells
    SPELL_FIREBLAST            = 20623,
    SPELL_SEPARATION_ANXIETY   = 21095,

    CREATURE_FLAMEWALKER_HEALER   = 11663,
    CREATURE_FLAMEWALKER_ELITE    = 11664,

    GOBJECT_CACHEOFTHEFIRELORD = 179703,

    SPELL_HOTCOAL              = 30512
};

struct Locations
{
    float x, y, z, o;
};

static Locations RoomCenter =
{
    736.55f, -1175.83f, -119.08f, 0.0f
};

static Locations CacheLocation =
{
    748.365f, -1195.52f, -118.145f, 0.0f
};

static Locations CaolLocation =
{
    736.663025f, -1176.569946f, -119.797997f, 0.0f
};


static Locations GuardsLocations[] =
{
	{ 757.638245f, -1187.058594f, -118.657173f, 2.579740f },
	{ 753.697266f, -1192.992554f, -118.387291f, 2.395171f },
	{ 747.905396f, -1197.361450f, -118.173851f, 2.049596f },
	{ 741.920837f, -1200.637817f, -118.056541f, 1.892516f },
	{ 759.999695f, -1172.765747f, -119.046082f, 3.278744f },
	{ 757.849915f, -1167.811523f, -119.006889f, 3.506510f },
	{ 755.279541f, -1163.614624f, -119.140846f, 3.822240f },
	{ 752.244751f, -1159.199585f, -119.253311f, 3.841875f },
};

enum DomoPhases
{
    NOT_VISIBLE,
    VISIBLE,
    DOWN,
    RAGNAGNA,
};

class Boss_Majordomo : public CreatureScript
{
    public:
        Boss_Majordomo() : CreatureScript("Boss_Majordomo") {}

    class Boss_MajordomoAI : public CreatureAI
    {
        public:
            enum event
            {
                EV_REFLECTION       = 1,
                EV_TELEPORT         = 2,
                EV_BLASTWAVE        = 3,
                EV_DOWN             = 4,
                EV_CHECK_PHASE      = 5
            };
            InstanceScript* _instance;
            uint8 guardCount;
            uint8 phase;

            Boss_MajordomoAI(Creature* creature) : CreatureAI(creature), Summons(me)
            {
                _instance = ((InstanceScript*)creature->GetInstanceScript());
                phase = NOT_VISIBLE;
            }

            EventMap events;

            void Reset()
            override {
                Summons.DespawnAll();
                events.RescheduleEvent(EV_REFLECTION, 10000, 0, VISIBLE);
                events.RescheduleEvent(EV_TELEPORT, 30000, 0, VISIBLE);
                events.RescheduleEvent(EV_BLASTWAVE, 3000, VISIBLE);
                events.RescheduleEvent(EV_DOWN, 33000, 0, DOWN);
                events.RescheduleEvent(EV_CHECK_PHASE, 10000, 0, NOT_VISIBLE);

                if (_instance)
                    _instance->SetData(DATA_MAJORDOMO, NOT_STARTED);

                setPhase(NOT_VISIBLE);
            }

            void JustSummoned(Creature* summoned)
            override {
                Summons.Summon(summoned);
            }
    
            void SummonedCreatureDespawn(Creature* unit)
            override {
                Summons.Despawn(unit);
            }

            void setPhase(uint32 newPhase)
            {
                phase = newPhase;
                events.SetPhase(newPhase);
                switch (newPhase)
                {
                    case NOT_VISIBLE:
                        me->SetFaction(FACTION_FRIENDLY);
                        me->SetVisible(false);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        break;
                    case VISIBLE:
                        DoScriptText(SAY_SPAWN, me);
                        summonGuards();
                        me->SetFaction(54);
                        me->SetVisible(true);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        break;
                    case DOWN:
                    {
                        Summons.DespawnAll();
                        me->SetFaction(FACTION_FRIENDLY);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetReactState(REACT_PASSIVE);
                        me->GetMotionMaster()->MoveTargetedHome();
                        me->CombatStop();
                        
                        if (_instance)
                            _instance->SetData(DATA_MAJORDOMO, DONE);

                        me->SummonGameObject(GOBJECT_CACHEOFTHEFIRELORD, Position(CacheLocation.x, CacheLocation.y, CacheLocation.z, 0), G3D::Quat(), 0);

                        Map *map = me->GetMap();
                        Map::PlayerList const &PlayerList = map->GetPlayers();

                        for(const auto & i : PlayerList)
                            if (Player* i_pl = i.GetSource())
                                if (i_pl->IsAlive())
                                    i_pl->CombatStop(true);

                        break;
                    }
                    case RAGNAGNA:
                        me->SetFaction(FACTION_FRIENDLY);
                        me->SetVisible(true);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);  
                        me->SetSpeedRate(MOVE_WALK, 0.9);
                        me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        me->UpdateSpeed(MOVE_WALK);
                        break;
                }
            }

            bool isSpawnReady()
            {
                if (_instance)
                {
                    if (_instance->GetData(DATA_MAJORDOMO) == DONE)
                        return false;

                    if (_instance->GetData(DATA_MAJORDOMO) == NOT_STARTED)
                    {
                        for (int i = DATA_LUCIFRON; i <= DATA_SULFURON; i++)
                        {
                            if (_instance->GetData(i) != DONE)
                                return false;
                        }
                    }
                    else
                        return false;
                }
                return true;
            }

            void summonGuards()
            {
                guardCount = 0;
                Summons.DespawnAll();
                for (int i = 0; i < 8; i++)
                {
                    uint32 creatureId = (i%2) ? CREATURE_FLAMEWALKER_HEALER : CREATURE_FLAMEWALKER_ELITE;
                    Creature* Guard;
                    if (me->GetMapId() == 409)
                        Guard = me->SummonCreature(creatureId, GuardsLocations[i].x, GuardsLocations[i].y, GuardsLocations[i].z, GuardsLocations[i].o, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000); 
                    else
                    {
                        float x = ((i < 4) ? (i*10)+10 : -(i-4)*10-10);
                        Guard = me->SummonCreature(creatureId, me->GetPositionX() + x, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                    }

                    if (Guard)
                    {
                        Guard->SetOwnerGUID(me->GetGUID());
                        guardCount++;
                    }
                }
            }

            void EnterCombat(Unit* /*victim*/)
            override {
                if (_instance)
                    _instance->SetData(DATA_MAJORDOMO, IN_PROGRESS);

                DoScriptText(SAY_AGGRO, me);
            }

            void KilledUnit(Unit* /*victim*/)
            override {
                if (!(rand()%5))
                    DoScriptText(SAY_SLAY, me);
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            override {
                if (damage > me->GetHealth())
                {
                    damage = 0;
                    me->SetHealth(me->GetMaxHealth());
                }
            }
        
            void UpdateAI(uint32 const diff)
            override {
                events.Update(diff);
            
                switch (events.GetEvent())
                {
                    case 0:
                        break;
                    case EV_CHECK_PHASE:
                        if (me->GetOwnerGUID() != 0)
                            setPhase(RAGNAGNA);
                        else if (isSpawnReady())
                            setPhase(VISIBLE);

                        events.RescheduleEvent(EV_CHECK_PHASE, 10000);
                        break;
                    case EV_DOWN:
                        me->CastSpell(me, SPELL_TELEPORT, true);
                        setPhase(NOT_VISIBLE);
                        DoScriptText(SAY_DEFEAT, me);
                        break;
                }

                if (!UpdateVictim())
                    return;

                switch (events.GetEvent())
                {
                case 0:
                    break;
                case EV_REFLECTION:
                {
                    uint32 spellID = rand() % 2 ? SPELL_MAGIC_REFLECTION : SPELL_DAMAGE_REFLECTION;
                    Creature* NagaFriend;
                    for (uint64 & Summon : Summons)
                    {
                        NagaFriend = ObjectAccessor::GetCreature((*me), Summon);
                        if (NagaFriend && NagaFriend->IsAlive())
                            me->AddAura(spellID, NagaFriend);
                    }
                    me->AddAura(spellID, me);
                    events.RescheduleEvent(EV_REFLECTION, 30000);
                    break;
                }
                case EV_TELEPORT:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        me->CastSpell(target, SPELL_TELEPORT, true);

                    events.RescheduleEvent(EV_TELEPORT, 30000);
                    break;
                case EV_BLASTWAVE:
                    me->CastSpell(me->GetVictim(), SPELL_BLASTWAVE);
                    events.RescheduleEvent(EV_BLASTWAVE, urand(3000, 10000));
                    break;
                }

                if (me->GetDistance(RoomCenter.x, RoomCenter.y , RoomCenter.z) > 100)
                    EnterEvadeMode();

                if (guardCount < 1 && phase != DOWN)
                    setPhase(DOWN);

                if (me->IsBelowHPPercent(50.0f) && !me->HasAuraEffect(SPELL_AEGIS, 0))
                    me->CastSpell(me, SPELL_AEGIS);

                DoMeleeAttackIfReady();
            }

            bool GossipHello(Player *player) override
            {
                if (_instance)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SUMMON_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

                    player->SEND_GOSSIP_MENU_TEXTID(TEXT_ID_SUMMON_1, me->GetGUID());
                }

                return true;
            }

            bool GossipSelect(Player* player, uint32 sender, uint32 action) override
            {
                switch (action)
                {
                case GOSSIP_ACTION_INFO_DEF + 1:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SUMMON_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(TEXT_ID_SUMMON_2, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SUMMON_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU_TEXTID(TEXT_ID_SUMMON_3, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 3:
                    player->CLOSE_GOSSIP_MENU();
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    break;
                }

                return true;
            }

        private:
            SummonList Summons;
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new Boss_MajordomoAI(creature);
    }
};

class Mob_FlameWalker_Healer : public CreatureScript
{
    public:
        Mob_FlameWalker_Healer() : CreatureScript("Mob_FlameWalker_Healer") {}
    
    class Mob_FlameWalker_HealerAI : public CreatureAI
    {
        public:
            enum event
            {
                EV_SHADOWBOLT         = 1,
                EV_SHADOWSHOCK        = 2,
            };
            Boss_Majordomo::Boss_MajordomoAI* domoAI;

            Mob_FlameWalker_HealerAI(Creature* creature) : CreatureAI(creature)
            {
                _instance = ((InstanceScript*)creature->GetInstanceScript());
            }

            EventMap events;

            void Reset()
            override {
                domoAI = nullptr;

                events.RescheduleEvent(EV_SHADOWBOLT, urand(8000, 12000));
                events.RescheduleEvent(EV_SHADOWSHOCK, urand(7000, 12000));
            }

            void JustDied(Unit* /*killer*/)
            override {
                if (domoAI)
                    domoAI->guardCount--;
            }
        
            void UpdateAI(uint32 const diff)
            override {
                if (!UpdateVictim())
                    return;

                if (!domoAI)
                {
                    if (Creature* domo = _instance->instance->GetCreature(_instance->GetData64(DATA_MAJORDOMO)))
                        domoAI = (Boss_Majordomo::Boss_MajordomoAI*)domo->AI();
                }
                else
                {
                    if (domoAI->guardCount <= 4 && !me->HasAuraEffect(SPELL_SEPARATION_ANXIETY, 0))
                        me->CastSpell(me, SPELL_SEPARATION_ANXIETY, true);
                }
            
                events.Update(diff);
            
                switch (events.GetEvent())
                {
                    case 0:
                        break;
                    case EV_SHADOWBOLT:
                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 100.0f, true))
                            if(me->CastSpell(target, SPELL_SHADOWBOLT) == SPELL_CAST_OK)
                                events.RescheduleEvent(EV_SHADOWBOLT, urand(8000, 12000));
                        break;
                    case EV_SHADOWSHOCK:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            if (me->CastSpell(target, SPELL_SHADOWSHOCK) == SPELL_CAST_OK)
                                events.RescheduleEvent(EV_SHADOWSHOCK, urand(15000, 25000));
                        break;
                }

                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* _instance;
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new Mob_FlameWalker_HealerAI(creature);
    }
};

class Mob_FlameWalker_Elite : public CreatureScript
{
    public:
        Mob_FlameWalker_Elite() : CreatureScript("Mob_FlameWalker_Elite") {}
    
    class Mob_FlameWalker_EliteAI : public CreatureAI
    {
        public:
            enum event
            {
                EV_BLASTWAVE          = 1,
                EV_FIREBLAST          = 2,
            };
            Boss_Majordomo::Boss_MajordomoAI* domoAI;

            Mob_FlameWalker_EliteAI(Creature* creature) : CreatureAI(creature)
            {
                _instance = ((InstanceScript*)creature->GetInstanceScript());
            }

            EventMap events;

            void Reset()
            override {
                domoAI = nullptr;

                events.RescheduleEvent(EV_BLASTWAVE, urand(3000, 10000));
                events.RescheduleEvent(EV_FIREBLAST, 10000);
            }

            void JustDied(Unit* /*killer*/)
            override {
                if (domoAI)
                    domoAI->guardCount--;
            }
        
            void UpdateAI(uint32 const diff)
            override {
                if (!UpdateVictim())
                    return;

                if (!domoAI)
                {
                    if (Creature* domo = _instance->instance->GetCreature(_instance->GetData64(DATA_MAJORDOMO)))
                        domoAI = (Boss_Majordomo::Boss_MajordomoAI*)domo->AI();
                }
                else
                {
                    if (domoAI->guardCount <= 4 && !me->HasAuraEffect(SPELL_SEPARATION_ANXIETY, 0))
                        me->CastSpell(me, SPELL_SEPARATION_ANXIETY, true);

                    if (Creature* domo = _instance->instance->GetCreature(_instance->GetData64(DATA_MAJORDOMO)))
                        domo->AddThreat(me->GetVictim(), 0);
                }
            
                events.Update(diff);
            
                switch (events.GetEvent())
                {
                    case 0:
                        break;
                    case EV_BLASTWAVE:
                        me->CastSpell(me->GetVictim(), SPELL_BLASTWAVE);
                        events.RescheduleEvent(EV_BLASTWAVE, urand(3000, 10000));
                        break;
                    case EV_FIREBLAST:
                        me->CastSpell(me->GetVictim(), SPELL_FIREBLAST);
                        events.RescheduleEvent(EV_FIREBLAST, 10000);
                        break;
                }

                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* _instance;
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new Mob_FlameWalker_EliteAI(creature);
    }
};

class Mob_Hot_Coal : public CreatureScript
{
    public:
        Mob_Hot_Coal() : CreatureScript("Mob_Hot_Coal") {}
    
    class Mob_Hot_CoalAI : public CreatureAI
    {
        public:
            enum event
            {
                EV_COAL          = 1
            };

            Mob_Hot_CoalAI(Creature* creature) : CreatureAI(creature)
            {
                _instance = ((InstanceScript*)creature->GetInstanceScript());
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            EventMap events;

            void Reset()
            override {
                events.RescheduleEvent(EV_COAL, 1000);

                me->SetVisible(false);
            }

            void UpdateAI(uint32 const diff)
            override {
                events.Update(diff);
            
                switch (events.GetEvent())
                {
                    case 0:
                        break;
                    case EV_COAL:
                        Map *map = me->GetMap();
                        Map::PlayerList const &PlayerList = map->GetPlayers();

                        for (const auto & i : PlayerList)
                        {
                            if (Player* i_pl = i.GetSource())
                                if (i_pl->IsAlive() && i_pl->IsAttackableByAOE() && i_pl->GetDistance(CaolLocation.x, CaolLocation.y, CaolLocation.z) <= 8)
                                {
                                    me->CastSpell(i_pl, SPELL_HOTCOAL, true);
                                    i_pl->CombatStop(true);
                                }
                        }

                        me->CombatStop(true);
                        events.RescheduleEvent(EV_COAL, 1000);
                        break;
                }

            }

        private:
            InstanceScript* _instance;
    };

    CreatureAI* GetAI(Creature* creature) const
    override {
        return new Mob_Hot_CoalAI(creature);
    }
};

void AddSC_boss_majordomo()
{
    new Boss_Majordomo();
    new Mob_FlameWalker_Healer();
    new Mob_FlameWalker_Elite();
    new Mob_Hot_Coal();
}

