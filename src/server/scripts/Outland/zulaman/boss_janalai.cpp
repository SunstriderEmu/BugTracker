 /* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
*(at your option) any later version.
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
SDName: Boss_Janalai
SD%Complete: 100
SDComment:
SDCategory: Zul'Aman
EndScriptData */


#include "def_zulaman.h"
#include "GridNotifiers.h"

#define SAY_AGGRO                   -1568000
#define SAY_FIRE_BOMBS              -1568001
#define SAY_SUMMON_HATCHER          -1568002
#define SAY_ALL_EGGS                -1568003
#define SAY_BERSERK                 -1568004
#define SAY_SLAY_1                  -1568005
#define SAY_SLAY_2                  -1568006
#define SAY_DEATH                   -1568007
#define SAY_EVENT_STRANGERS         -1568008
#define SAY_EVENT_FRIENDS           -1568009

// Jan'alai
// --Spell
#define SPELL_FLAME_BREATH          43140
#define SPELL_FIRE_WALL             43113
#define SPELL_ENRAGE                44779
#define SPELL_SUMMON_PLAYERS        43097
#define SPELL_TELE_TO_CENTER        43098 // coord
#define SPELL_HATCH_ALL             43144
#define SPELL_BERSERK               45078
// -- Fire Bob Spells
#define SPELL_FIRE_BOMB_CHANNEL     42621 // last forever
#define SPELL_FIRE_BOMB_THROW       42628 // throw visual
#define SPELL_FIRE_BOMB_DUMMY       42629 // bomb visual
#define SPELL_FIRE_BOMB_DAMAGE      42630

// --Summons
#define MOB_AMANI_HATCHER           23818
#define MOB_HATCHLING               23598   // 42493
#define MOB_EGG                     23817
#define MOB_FIRE_BOMB               23920

// -- Hatcher Spells
#define SPELL_HATCH_EGG             43734   // 42471

// -- Hatchling Spells
#define SPELL_FLAMEBUFFET           43299

const int area_dx = 44;
const int area_dy = 51;

float JanalainPos[1][3] =
{
    {-33.93f, 1149.27f, 19.0f}
};

float FireWallCoords[4][4] =
{
    {-10.13f, 1149.27f, 19.0f, 3.1415f},
    {-33.93f, 1123.90f, 19.0f, 0.5f*M_PI},
    {-54.80f, 1150.08f, 19.0f, 0.0f},
    {-33.93f, 1175.68f, 19.0f, 1.5f*M_PI}
};

float hatcherway[2][5][3] =
{
    {
        {-87.46f,1170.09f,6.0f },
        {-74.41f,1154.75f,6.0f },
        {-52.74f,1153.32f,19.0f },
        {-33.37f,1172.46f,19.0f },
        {-33.09f,1203.87f,19.0f }
    },
    {
        {-86.57f,1132.85f,6.0f },
        {-73.94f,1146.00f,6.0f },
        {-52.29f,1146.51f,19.0f },
        {-33.57f,1125.72f,19.0f },
        {-34.29f,1095.22f,19.0f }
    }
};


class boss_janalai : public CreatureScript
{
public:
    boss_janalai() : CreatureScript("boss_janalai")
    { }

    class boss_janalaiAI : public ScriptedAI
    {
        public:
        boss_janalaiAI(Creature *c) : ScriptedAI(c)
        {
            pInstance =((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        uint32 FireBreathTimer;
        uint32 BombTimer;
        uint32 BombSequenceTimer;
        uint32 BombCount;
        uint32 HatcherTimer;
        uint32 EnrageTimer;
        uint32 ResetTimer;
    
        bool noeggs;
        bool enraged;
        bool isBombing;
    
        bool isFlameBreathing;
    
        uint64 FireBombGUIDs[40];
    
        void Reset()
        override {
            if(pInstance && pInstance->GetData(DATA_JANALAIEVENT) != DONE)
                pInstance->SetData(DATA_JANALAIEVENT, NOT_STARTED);
    
            FireBreathTimer = 8000;
            BombTimer = 30000;
            BombSequenceTimer = 1000;
            BombCount = 0;
            HatcherTimer = 10000;
            EnrageTimer = 300000;
            ResetTimer = 5000;
    
            noeggs = false;
            isBombing =false;
            enraged = false;
    
            isFlameBreathing = false;
    
            for(uint64 & FireBombGUID : FireBombGUIDs)
                FireBombGUID = 0;
    
            HatchAllEggs(1);
        }
    
        void JustDied(Unit* Killer)
        override {
            DoScriptText(SAY_DEATH, me);
    
            if(pInstance)
                pInstance->SetData(DATA_JANALAIEVENT, DONE);
        }
    
        void KilledUnit(Unit* victim)
        override {
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_SLAY_1, me); break;
            case 1: DoScriptText(SAY_SLAY_2, me); break;
            }
        }
    
        void EnterCombat(Unit *who)
        override {
            if(pInstance)
                pInstance->SetData(DATA_JANALAIEVENT, IN_PROGRESS);
    
            DoScriptText(SAY_AGGRO, me);
    //        DoZoneInCombat();
        }
    
        void DamageDeal(Unit* target, uint32 &damage)
        {
            if(isFlameBreathing)
            {
                if(!me->HasInArc(M_PI/6, target))
                    damage = 0;
            }
        }
    
        void FireWall()
        {
            uint8 WallNum;
            Creature* wall = nullptr;
            for(uint8 i = 0; i < 4; i++)
            {
                if(i == 0 || i == 2)
                    WallNum = 3;
                else
                    WallNum = 2;
    
                for(uint8 j = 0; j < WallNum; j++)
                {
                    if(WallNum == 3)
                        wall = me->SummonCreature(MOB_FIRE_BOMB, FireWallCoords[i][0],FireWallCoords[i][1]+5*(j-1),FireWallCoords[i][2],FireWallCoords[i][3],TEMPSUMMON_TIMED_DESPAWN,15000);
                    else
                        wall = me->SummonCreature(MOB_FIRE_BOMB, FireWallCoords[i][0]-2+4*j,FireWallCoords[i][1],FireWallCoords[i][2],FireWallCoords[i][3],TEMPSUMMON_TIMED_DESPAWN,15000);
                    if(wall) wall->CastSpell(wall, SPELL_FIRE_WALL, true);
                }
            }
        }
    
        void SpawnBombs()
        {
            float dx, dy;
            for(uint64 & FireBombGUID : FireBombGUIDs)
            {
                dx =(rand()%(area_dx))-(area_dx/2);
                dy =(rand()%(area_dy))-(area_dy/2);
    
                Creature* bomb = DoSpawnCreature(MOB_FIRE_BOMB, dx, dy, 0, 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
                if(bomb) FireBombGUID = bomb->GetGUID();
            }
            BombCount = 0;
        }
    
        bool HatchAllEggs(uint32 action) //1: reset, 2: isHatching all
        {
            me->CastSpell(me, SPELL_HATCH_EGG, true);
            return true;
        }
    
        void Boom()
        {
            std::list<Creature*> templist;
            float x, y, z;
            me->GetPosition(x, y, z);
    
            {
                Trinity::AllCreaturesOfEntryInRange check(me, MOB_FIRE_BOMB, 100);
                Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, templist, check);
                Cell::VisitGridObjects(me, searcher, MAX_SEARCHER_DISTANCE);
            }
            for(auto & i : templist)
            {
               i->CastSpell(i, SPELL_FIRE_BOMB_DAMAGE, true);
               i->RemoveAllAuras();
            }
        }
    
        void HandleBombSequence()
        {
            if(BombCount < 40)
            {
                if(Unit *FireBomb = ObjectAccessor::GetUnit((*me), FireBombGUIDs[BombCount]))
                {
                    FireBomb->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    DoCast(FireBomb, SPELL_FIRE_BOMB_THROW, true);
                    FireBomb->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
                BombCount++;
                if(BombCount == 40)
                {
                    BombSequenceTimer = 5000;
                }else BombSequenceTimer = 100;
            }
            else
            {
                Boom();
                isBombing = false;
                BombTimer = 20000+rand()%20000;
                me->RemoveAurasDueToSpell(SPELL_FIRE_BOMB_CHANNEL);
                if(EnrageTimer <= 10000)
                    EnrageTimer = 0;
                else
                    EnrageTimer -= 10000;
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(isFlameBreathing)
            {
                if(!me->IsNonMeleeSpellCast(false))
                {
                    isFlameBreathing = false;
                }else return;
            }
    
            if(isBombing)
            {
                if(BombSequenceTimer < diff)
                {
                    HandleBombSequence();
                }else BombSequenceTimer -= diff;
                return;
            }
    
            if(!UpdateVictim())
                return;
    
            //enrage if under 25% hp before 5 min.
            if(!enraged && me->GetHealth() * 4 < me->GetMaxHealth())
                EnrageTimer = 0;
    
            if(EnrageTimer < diff)
            {
                if(!enraged)
                {
                    me->CastSpell(me, SPELL_ENRAGE, true);
                    enraged = true;
                    EnrageTimer = 300000;
                }
                else
                {
                    DoScriptText(SAY_BERSERK, me);
                    me->CastSpell(me, SPELL_BERSERK, true);
                    EnrageTimer = 300000;
                }
            }else EnrageTimer -= diff;
    
            if(BombTimer < diff)
            {
                DoScriptText(SAY_FIRE_BOMBS, me);
    
                me->AttackStop();
                me->GetMotionMaster()->Clear();
                DoTeleportTo(JanalainPos[0][0],JanalainPos[0][1],JanalainPos[0][2]);
                me->StopMoving();
                me->CastSpell(me, SPELL_FIRE_BOMB_CHANNEL, false);
                //DoTeleportPlayer(me, JanalainPos[0][0], JanalainPos[0][1],JanalainPos[0][2], 0);
                //me->CastSpell(me, SPELL_TELE_TO_CENTER, true);
    
                FireWall();
                SpawnBombs();
                isBombing = true;
                BombSequenceTimer = 100;
    
                //Teleport every Player into the middle
                Map *map = me->GetMap();
                if(!map->IsDungeon()) return;
                Map::PlayerList const &PlayerList = map->GetPlayers();
                float pDistance = 0.0f;
                for(const auto & i : PlayerList)
                {
                    if (Player* i_pl = i.GetSource()) {
                        pDistance = me->GetDistance(i_pl);
                        if (i_pl->IsAlive() && pDistance > 20.0f && pDistance < 100.0f && !i_pl->IsGameMaster())       // May prevent ghost players to be teleported (strange bug o_O)
                            DoTeleportPlayer(i_pl, JanalainPos[0][0] - 5 + rand() % 10, JanalainPos[0][1] - 5 + rand() % 10, JanalainPos[0][2], 0);
                    }
                }
                //me->CastSpell(Temp, SPELL_SUMMON_PLAYERS, true); // core bug, spell does not work if too far
                return;
            }else BombTimer -= diff;
    
            if(!noeggs)
            {
                if(100 * me->GetHealth() < 35 * me->GetMaxHealth())
                {
                    DoScriptText(SAY_ALL_EGGS, me);
    
                    me->AttackStop();
                    me->GetMotionMaster()->Clear();
                    DoTeleportTo(JanalainPos[0][0],JanalainPos[0][1],JanalainPos[0][2]);
                    me->StopMoving();
                    me->CastSpell(me, SPELL_HATCH_ALL, false);
                    HatchAllEggs(2);
                    noeggs = true;
                }
                else if(HatcherTimer < diff)
                {
                    if(HatchAllEggs(0))
                    {
                        DoScriptText(SAY_SUMMON_HATCHER, me);
                        me->SummonCreature(MOB_AMANI_HATCHER,hatcherway[0][0][0],hatcherway[0][0][1],hatcherway[0][0][2],0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10000);
                        me->SummonCreature(MOB_AMANI_HATCHER,hatcherway[1][0][0],hatcherway[1][0][1],hatcherway[1][0][2],0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10000);
                        HatcherTimer = 90000;
                    }
                    else
                        noeggs = true;
                }else HatcherTimer -= diff;
            }
    
            if(ResetTimer < diff)
            {
                float x, y, z, o;
                me->GetHomePosition(x, y, z, o);
                if(me->GetPositionZ() <= z-7)
                {
                    EnterEvadeMode();
                    return;
                }
                ResetTimer = 5000;
            }else ResetTimer -= diff;
    
            DoMeleeAttackIfReady();
    
            if(FireBreathTimer < diff)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                {
                    me->AttackStop();
                    me->GetMotionMaster()->Clear();
                    me->CastSpell(target, SPELL_FLAME_BREATH, false);
                    me->StopMoving();
                    isFlameBreathing = true;
                }
                FireBreathTimer = 8000;
            }else FireBreathTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_janalaiAI(creature);
    }
};



class mob_janalai_firebomb : public CreatureScript
{
public:
    mob_janalai_firebomb() : CreatureScript("mob_janalai_firebomb")
    { }

    class mob_janalai_firebombAI : public ScriptedAI
    {
        public:
        mob_janalai_firebombAI(Creature *c) : ScriptedAI(c){}
    
        void Reset() override {}
    
        void SpellHit(Unit *caster, const SpellInfo *spell)
        override {
            if(spell->Id == SPELL_FIRE_BOMB_THROW)
                me->CastSpell(me, SPELL_FIRE_BOMB_DUMMY, true);
        }
    
        void EnterCombat(Unit* who) override {}
    
        void AttackStart(Unit* who) override {}
    
        void MoveInLineOfSight(Unit* who) override {}
    
        void UpdateAI(const uint32 diff) override {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_janalai_firebombAI(creature);
    }
};



class mob_janalai_hatcher : public CreatureScript
{
public:
    mob_janalai_hatcher() : CreatureScript("mob_janalai_hatcher")
    { }

    class mob_amanishi_hatcherAI : public ScriptedAI
    {
        public:
        mob_amanishi_hatcherAI(Creature *c) : ScriptedAI(c)
        {
            pInstance =((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        uint32 waypoint;
        uint32 HatchNum;
        uint32 WaitTimer;
    
        bool side;
        bool hasChangedSide;
        bool isHatching;
    
        void Reset()
        override {
            side =(me->GetPositionY() < 1150);
            waypoint = 0;
            isHatching = false;
            hasChangedSide = false;
            WaitTimer = 1;
            HatchNum = 0;
        }
    
        bool HatchEggs(uint32 num)
        {
            me->CastSpell(me, SPELL_HATCH_EGG, true);
            std::list<Creature*> templist;
            float x, y, z;
            me->GetPosition(x, y, z);

            {
                Trinity::AllCreaturesOfEntryInRange check(me, 23817, 50);
                Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, templist, check);
                Cell::VisitAllObjects(me, searcher, MAX_SEARCHER_DISTANCE);
            }

            //error_log("Eggs %d at %d", templist.size(), side);

            for (auto i = templist.begin(); i != templist.end() && num > 0; ++i)
            {
                if ((*i)->GetDisplayId() != 11686)
                {
                    (*i)->AI()->message(0, 0); //send whatever, hatch egg
                    num--;
                }
            }

            if (num)
                return false;   // no more templist
            else
                return true;
        }
    
        void EnterCombat(Unit* who) override {}
        void AttackStart(Unit*) override {}
        void MoveInLineOfSight(Unit*) override {}
        void MovementInform(uint32, uint32)
        override {
            if(waypoint == 5)
            {
                isHatching = true;
                HatchNum = 1;
                WaitTimer = 5000;
            }
            else
                WaitTimer = 1;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!pInstance || !(pInstance->GetData(DATA_JANALAIEVENT) == IN_PROGRESS))
            {
                me->SetVisible(false);
                me->SetDeathState(JUST_DIED);
                return;
            }
    
            if(!isHatching)
            {
                if(WaitTimer)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MovePoint(0,hatcherway[side][waypoint][0],hatcherway[side][waypoint][1],hatcherway[side][waypoint][2]);
                    waypoint++;
                    WaitTimer = 0;
                }
            }
            else
            {
                if(WaitTimer < diff)
                {
                    if(HatchEggs(HatchNum))
                    {
                        HatchNum++;
                        WaitTimer = 10000;
                    }
                    else if(!hasChangedSide)
                    {
                        side = side ? 0 : 1;
                        isHatching = false;
                        waypoint = 3;
                        WaitTimer = 1;
                        hasChangedSide = true;
                    }
                    else
                    {
                        me->SetVisible(false);
                        me->SetDeathState(JUST_DIED);
                    }
                }else WaitTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_amanishi_hatcherAI(creature);
    }
};



class mob_janalai_hatchling : public CreatureScript
{
public:
    mob_janalai_hatchling() : CreatureScript("mob_janalai_hatchling")
    { }

    class mob_hatchlingAI : public ScriptedAI
    {
        public:
        mob_hatchlingAI(Creature *c) : ScriptedAI(c)
        {
            pInstance =((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
        uint32 BuffetTimer;
    
        void Reset()
        override {
            BuffetTimer = 7000;
            if(me->GetPositionY() > 1150)
                me->GetMotionMaster()->MovePoint(0, hatcherway[0][3][0]+rand()%4-2,1150+rand()%4-2,hatcherway[0][3][2]);
            else
                me->GetMotionMaster()->MovePoint(0,hatcherway[1][3][0]+rand()%4-2,1150+rand()%4-2,hatcherway[1][3][2]);
    
            me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!pInstance || !(pInstance->GetData(DATA_JANALAIEVENT) == IN_PROGRESS))
            {
                me->SetVisible(false);
                me->SetDeathState(JUST_DIED);
                return;
            }
    
            if(!UpdateVictim())
                return;
    
            if(BuffetTimer < diff)
            {
                me->CastSpell(me->GetVictim(), SPELL_FLAMEBUFFET, false);
                BuffetTimer = 10000;
            }else BuffetTimer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_hatchlingAI(creature);
    }
};



class mob_janalai_egg : public CreatureScript
{
public:
    mob_janalai_egg() : CreatureScript("mob_janalai_egg")
    { }

    class mob_eggAI : public ScriptedAI
    {
        public:
        mob_eggAI(Creature *c) : ScriptedAI(c){}
        void Reset() override {}
        void EnterCombat(Unit* who) override {}
        void AttackStart(Unit* who) override {}
        void MoveInLineOfSight(Unit* who) override {}
        void UpdateAI(const uint32 diff) override {}

        void Hatch()
        {
            if (me->GetDisplayId() != 11686)
            {
                DoSpawnCreature(MOB_HATCHLING, 0, 0, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000);
                me->SetDisplayId(11686);
            }
        }

        virtual uint64 message(uint32 id, uint64 data) 
        { 
            Hatch();
            return 0;
        }

        void SpellHit(Unit *caster, const SpellInfo *spell)
        override {
            if (spell->Id == SPELL_HATCH_EGG)
                Hatch();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_eggAI(creature);
    }
};


void AddSC_boss_janalai()
{
    new boss_janalai();
    new mob_janalai_firebomb();
    new mob_janalai_hatcher();
    new mob_janalai_hatchling();
    new mob_janalai_egg();
}

