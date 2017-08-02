/*
 * Copyright (C) 2005-2008 MaNGOS <http://www.mangosproject.org/>
 *
 * Copyright (C) 2008 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2009 - 2011 Windrunner
 *
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



struct npc_fire_effigy_fire : public ScriptedAI
{
    npc_fire_effigy_fire(Creature* c) : ScriptedAI(c)
    {
        me->SetReactState(REACT_PASSIVE);
        SetCombatMovementAllowed(false);
    }
    
    uint32 addAuraTimer;
    
    void Reset()
    override {
        addAuraTimer = 0;
    }
    
    void EnterCombat(Unit* who) override {}
    
    void DamageTaken(Unit* doneBy, uint32& damage)
    override {
        damage = 0;
    }
    
    bool sOnDummyEffect(Unit* caster, uint32 spellId, uint32 effIndex)
    override {
        if (!caster->ToPlayer())
            return false;
            
        if (!me->HasAuraEffect(42074))
            return false;

        if (spellId == 42339) {
            uint32 questId = 0;

            switch (me->GetZoneId()) {
            case 85: // Tirisfal
                questId = 11449;
                break;
            case 14: // Durotar
                questId = 11361;
                break;
            case 3430: // Eversong Woods
                questId = 11450;
                break;
            case 12: // Elwynn
                questId = 11360;
                break;
            case 3524: // Azure Watch
                questId = 11440;
                break;
            case 1: // Dun Morogh
                questId = 11439;
                break;
            default:
                break;
            }
            
            if (questId)
                caster->ToPlayer()->KilledMonsterCredit(me->GetEntry(), me->GetGUID(), questId);
            
            DoCast(me, 42348, true);
            me->RemoveAurasDueToSpell(42074);
            addAuraTimer = 10000;
        }
        
        return true;
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (addAuraTimer) {
            if (addAuraTimer <= diff) {
                DoCast(me, 42074, true);
                addAuraTimer = 0;
            }
            else
                addAuraTimer -= diff;
        }
    }
};

CreatureAI* GetAI_fire_effigy_fire(Creature* creature)
{
    return new npc_fire_effigy_fire(creature);
}

class WickermanEmber : public GameObjectScript
{
public:
    WickermanEmber() : GameObjectScript("go_wickerman_ember")
    {}

    bool OnGossipHello(Player* player, GameObject* _GO) override
    {
        player->CastSpell(player, 24705, true);

        return true;
    }
};

enum shadeOfHorsemanData {
    SPELL_CLEAVE        = 15496,
    SPELL_CONFLAGRATION = 42380,
    SPELL_FIRE_SMOKE    = 42355,
    SPELL_FIRE          = 42074,
    SPELL_FIRE_GROW     = 42091,
    SPELL_THROW_FLAME   = 42079,
    SPELL_BUCKET_LANDS  = 42339,
    
    NPC_FLAME_BUNNY     = 23758,
    
    GOB_JACKOLANTERN    = 186887,
    
    YELL_BEGIN          = -1000722,
    YELL_5_THROWS       = -1000723,
    YELL_13_MINS        = -1000724,
    YELL_FEW_FLAMES     = -1000725,
    YELL_MANY_FLAMES    = -1000726,
    YELL_DEATH          = -1000727,
    YELL_CONFLAG        = -1000728
};


struct boss_shade_of_horsemanAI : public ScriptedAI
{
    boss_shade_of_horsemanAI(Creature* c) : ScriptedAI(c)
    {
        throwCount = 0;
        flamesCount = 0;
        despawnTimer = 900000; // 15 minutes
        flightPhase = true;
        
        me->SetDisableGravity(true);

        me->SetReactState(REACT_PASSIVE);
        
        yelled5Throws = false;
        yelled13Mins = false;
        yelledFewFlames = false;
        yelledManyFlames = false;
        
        DoScriptText(YELL_BEGIN, me, nullptr);
        
        me->SetKeepActive(5 * MINUTE*IN_MILLISECONDS);
    }
    
    uint32 cleaveTimer;
    uint32 conflagTimer;
    uint32 throwFlameTimer;
    uint32 despawnTimer;
    uint32 landingTimer;
    uint32 flamesCount;
    uint32 yellTimer;
    
    uint8 throwCount;
    
    bool flightPhase;
    bool yelled5Throws;
    bool yelled13Mins;
    bool yelledFewFlames;
    bool yelledManyFlames;
    
    std::set<uint64> fireGUIDs;
    
    void Reset()
    override {
        fireGUIDs.clear();

        cleaveTimer = 3000;
        conflagTimer = 10000;
        throwFlameTimer = 2000;
        yellTimer = 1000;
        
        if (flightPhase)
            me->GetMotionMaster()->MovePath(GetPathFromZone());
    }
    
    uint32 GetPathFromZone()
    {
        uint32 pathId = 0;
        switch (me->GetZoneId()) {
        case 85: // Tirisfal
            pathId = 23758;
            break;
        case 12: // Elwynn
            pathId = 23759;
            break;
        case 3430: // Eversong Woods
            pathId = 23760;
            break;
        case 1: // Dun Morogh
            pathId = 23761;
            break;
        case 3524: // Azure Watch
            pathId = 23762;
            break;
        case 14: // Durotar
            pathId = 23763;
            break;
        default:
            break;
        }
        
        return pathId;
    }
    
    void GetLandingCoordsFromZone(float& x, float& y, float& z)
    {
        switch (me->GetZoneId()) {
        case 85: // Tirisfal
            x = 2260.666260;
            y = 295.938843;
            z = 34.113869;
            break;
        case 14: // Durotar
            x = 321.620972;
            y = -4738.326172;
            z = 9.687964;
            break;
        case 3430: // Eversong Woods
            x = 9528.690430;
            y = -6823.195801;
            z = 16.492004;
            break;
        case 12: // Elwynn
            x = -9452.374023;
            y = 63.770973;
            z = 55.976582;
            break;
        case 3524: // Azure Watch
            x = -4175.732910;
            y = -12477.948242;
            z = 44.328426;
            break;
        case 1: // Dun Morogh
            x = -5602.907715;
            y = -482.826233;
            z = 396.980743;
            break;
        default:
            break;
        }
    }
    
    void MoveInLineOfSight(Unit* who)
    override {
        if (!flightPhase)
            ScriptedAI::MoveInLineOfSight(who);
    }
    
    void EnterCombat(Unit* who)
    override {
        me->SetDisableGravity(false);
        me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
        me->SetReactState(REACT_AGGRESSIVE);
        me->Dismount();
    }
    
    void JustDied(Unit* killer)
    override {
        // Yell die text
        DoScriptText(YELL_DEATH, me, nullptr);
        
        // Summon Jack-o-lantern
        killer->SummonGameObject(GOB_JACKOLANTERN, me->GetPosition(), G3D::Quat(), 600000);
        
        despawnTimer = 0;
        
        std::list<WorldObject*> targets;
        float dist = 100.0f;
        Trinity::AllWorldObjectsInRange u_check(me, dist);
        Trinity::WorldObjectListSearcher<Trinity::AllWorldObjectsInRange> searcher(me, targets, u_check);
        Cell::VisitAllObjects(me, searcher, dist);

        for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); itr++) {
            if ((*itr)->ToPlayer()) {
                (*itr)->ToPlayer()->AreaExploredOrEventHappens(11219);
                (*itr)->ToPlayer()->AreaExploredOrEventHappens(11131);
            }
        }
    }
    
    void MovementInform(uint32 type, uint32 id)
    override {
        if (id == 0 && !flightPhase) {
            me->SetDisableGravity(false);
            me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
            me->SetReactState(REACT_AGGRESSIVE);
            me->Dismount();
        }
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (flightPhase) {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            
            if (despawnTimer) {
                if (despawnTimer <= diff) {
                    me->DisappearAndDie();
                    despawnTimer = 0;
                }
                else
                    despawnTimer -= diff;
            }
            
            if (yellTimer <= diff) {
                if (throwCount > 5 && !yelled5Throws) {
                    DoScriptText(YELL_5_THROWS, me, nullptr);
                    yelled5Throws = true;
                }
                else if (despawnTimer <= 120000 && !yelled13Mins) {
                    DoScriptText(YELL_13_MINS, me, nullptr);
                    yelled13Mins = true;
                }
                else if (throwCount >= 10 && flamesCount <= 5 && !yelledFewFlames) {
                    DoScriptText(YELL_FEW_FLAMES, me, nullptr);
                    yelledFewFlames = true;
                }
                else if (throwCount >= 10 && flamesCount >= 10 && !yelledManyFlames) {
                    DoScriptText(YELL_MANY_FLAMES, me, nullptr);
                    yelledManyFlames = true;
                }

                yellTimer = 1000;
            }
            else
                yellTimer -= diff;
            
            if ((flamesCount == 0 || despawnTimer <= 120000) && throwCount >= 15) {
                float x, y, z;
                GetLandingCoordsFromZone(x, y, z);
                flightPhase = false;
                me->GetMotionMaster()->MovePoint(0, x, y, z, false);
            }
            
            if (throwFlameTimer <= diff && throwCount < 15) {
                if (Creature* bunny = me->FindNearestCreature(NPC_FLAME_BUNNY, 50.0f, true)) {
                    DoCast(bunny, SPELL_THROW_FLAME);
                    throwCount++;
                    flamesCount++;
                    throwFlameTimer = 10000 + rand() % 8000;
                }
            }
            else
                throwFlameTimer -= diff;
        }
        else {
            if (!UpdateVictim())
                return;

            if (cleaveTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_CLEAVE);
                cleaveTimer = 4000 + rand() % 3000;
            }
            else
                cleaveTimer -= diff;

            if (conflagTimer <= diff) {
                DoScriptText(YELL_CONFLAG, me, nullptr);
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_CONFLAGRATION, true);
                conflagTimer = 15000 + rand()% 15000;
            }
            else
                conflagTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_shade_of_horseman(Creature* creature)
{
    return new boss_shade_of_horsemanAI(creature);
}

struct npc_shade_of_horseman_bunnyAI : public ScriptedAI
{
    npc_shade_of_horseman_bunnyAI(Creature* c) : ScriptedAI(c)
    {
        stackCount = 0;
        me->SetFaction(FACTION_FRIENDLY);
        SetCombatMovementAllowed(false);
    }
    
    uint64 shadeGUID;
    
    uint32 growTimer;
    uint32 checkEventTimer;
    
    uint8 stackCount;
    
    void Reset()
    override {
        growTimer = 30000;
        checkEventTimer = 10000 + rand() % 15000;
        shadeGUID = 0;
        me->SetReactState(REACT_PASSIVE);
    }

    void EnterCombat(Unit* who) override {}
    
    bool sOnDummyEffect(Unit* caster, uint32 spellId, uint32 effIndex)
    override {
        if (spellId == SPELL_THROW_FLAME) {
            if (me->HasAuraEffect(SPELL_FIRE_SMOKE))
                me->RemoveAurasDueToSpell(SPELL_FIRE_SMOKE);

            stackCount++;
            DoCast(me, SPELL_FIRE);
            
            shadeGUID = caster->GetGUID();
        }
        else if (spellId == SPELL_BUCKET_LANDS) {
            if (!stackCount)
                return true;

            stackCount--;
            if (Creature* shade = ObjectAccessor::GetCreature(*me, shadeGUID))
                ((boss_shade_of_horsemanAI*)shade->AI())->flamesCount--;

            if (stackCount == 0) {
                me->RemoveAurasDueToSpell(SPELL_FIRE);
                me->RemoveAurasDueToSpell(SPELL_FIRE_GROW);
                DoCast(me, SPELL_FIRE_SMOKE);
            }
            else
                me->RemoveSingleAuraFromStack(SPELL_FIRE_GROW, 0);
        }
        
        return true;
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!me->HasAuraEffect(SPELL_FIRE))
            return;
        
        if (checkEventTimer <= diff) {
            if (shadeGUID) { // Actually it should be != 0, as we don't reach this code if we don't have fire aura
                Creature* shade = ObjectAccessor::GetCreature(*me, shadeGUID);
                if (!shade) {
                    me->RemoveAurasDueToSpell(SPELL_FIRE);
                    me->RemoveAurasDueToSpell(SPELL_FIRE_GROW);
                    DoCast(me, SPELL_FIRE_SMOKE);
                    return;
                }
            }
            checkEventTimer = 10000 + rand() % 15000;
        }
        else
            checkEventTimer -= diff;
            
        if (growTimer <= diff) {
            DoCast(me, SPELL_FIRE_GROW, true);
            growTimer = 30000;
            stackCount++;
            if (Creature* shade = ObjectAccessor::GetCreature(*me, shadeGUID))
                ((boss_shade_of_horsemanAI*)shade->AI())->flamesCount++;
        }
        else
            growTimer -= diff;
    }
};

CreatureAI* GetAI_npc_shade_of_horseman_bunny(Creature* creature)
{
    return new npc_shade_of_horseman_bunnyAI(creature);
}

void AddSC_hallows_end()
{
    OLDScript* newscript;
    
    newscript = new OLDScript;
    newscript->Name = "npc_fire_effigy_fire";
    newscript->GetAI = &GetAI_fire_effigy_fire;
    sScriptMgr->RegisterOLDScript(newscript);
    
    new WickermanEmber();
    
    newscript = new OLDScript;
    newscript->Name = "boss_shade_of_horseman";
    newscript->GetAI = &GetAI_boss_shade_of_horseman;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_shade_of_horseman_bunny";
    newscript->GetAI = &GetAI_npc_shade_of_horseman_bunny;
    sScriptMgr->RegisterOLDScript(newscript);
}    
