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
SDName: Boss_Onyxia
SD%Complete: 90
SDComment: Spell Heated Ground is wrong, flying animation, visual for area effect
SDCategory: Onyxia's Lair
EndScriptData */



#define SAY_AGGRO                   -1249000
#define SAY_KILL                    -1249001
#define SAY_PHASE_2_TRANS           -1249002
#define SAY_PHASE_3_TRANS           -1249003
#define EMOTE_BREATH                -1249004

#define SPELL_WINGBUFFET            18500
#define SPELL_FLAMEBREATH           18435
#define SPELL_CLEAVE                19983
#define SPELL_TAILSWEEP             15847
#define SPELL_KNOCK_AWAY            19633

#define SPELL_ENGULFINGFLAMES       20019
#define SPELL_DEEPBREATH            23461
#define SPELL_FIREBALL              18392

#define SPELL_BELLOWINGROAR         18431
#define SPELL_HEATED_GROUND         22191       //Wrong Spell

#define SPELL_SUMMONWHELP           17646

#define CREATURE_WHELP      11262

static float MovementLocations[4][3]=
{
    {-64.0523f, -213.0619f, -68.2985f},
    { 12.4636f, -220.0149f, -68.0548f},
    {-38.8391f, -182.3220f, -68.9457f},
    {-37.0390f, -244.8760f, -68.1278f},
};

static float SpawnLocations[4][3]=
{
    {-30.127f, -254.463f, -89.440f},
    {-30.817f, -177.106f, -89.258f},
    { 14.480f, -241.560f, -85.630f},
    { 17.372f, -190.840f, -85.281f},
};


class boss_onyxia : public CreatureScript
{
public:
    boss_onyxia() : CreatureScript("boss_onyxia")
    { }

    class boss_onyxiaAI : public ScriptedAI
    {
        public:
        boss_onyxiaAI(Creature* c) : ScriptedAI(c) {}
    
        uint32 Phase;
    
        uint32 FlameBreathTimer;
        uint32 CleaveTimer;
        uint32 TailSweepTimer;
        uint32 MovementTimer;
        uint32 EngulfingFlamesTimer;
        uint32 SummonWhelpsTimer;
        uint32 BellowingRoarTimer;
        uint32 WingBuffetTimer;
        uint32 KnockAwayTimer;
        uint32 FireballTimer;
    
        bool InitialSpawn;
    
        void Reset()
        override {
            Phase = 1;
    
            FlameBreathTimer = 20000;
            TailSweepTimer = 2000;
            CleaveTimer = 15000;
            MovementTimer = 3000;
            EngulfingFlamesTimer = 15000;
            SummonWhelpsTimer = 45000;
            BellowingRoarTimer = 30000;
            WingBuffetTimer = 17000;
            KnockAwayTimer = 15000;
            FireballTimer = 18000;
    
            InitialSpawn = true;
    
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
            me->ApplySpellImmune(1, IMMUNITY_EFFECT,SPELL_EFFECT_ATTACK_ME, true);
        }
    
        void EnterCombat(Unit* who)
        override {
            DoScriptText(SAY_AGGRO, me);
            DoZoneInCombat();
        }
    
        void JustDied(Unit* Killer)
        override {
        }
    
        void KilledUnit(Unit *victim)
        override {
            DoScriptText(SAY_KILL, me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!UpdateVictim())
                return;
    
            if(((me->GetHealthPct()) < 60) && (Phase == 1))
            {
                Phase = 2;
                me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
                me->SetDisableGravity(true);
                me->SetHover(true);
                me->GetMotionMaster()->Clear(false);
                me->GetMotionMaster()->MoveIdle();
                DoScriptText(SAY_PHASE_2_TRANS, me);
            }
    
            if(((me->GetHealthPct()) < 40) && (Phase == 2))
            {
                Phase = 3;
                me->SetDisableGravity(false);
                me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
                me->SetHover(false);
                me->GetMotionMaster()->MovePoint(0, -10.6155, -219.357, -87.7344);
                DoStartMovement(me->GetVictim());
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                DoScriptText(SAY_PHASE_3_TRANS, me);
            }
    
            if(Phase == 1 || Phase == 3)
            {
                if(FlameBreathTimer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_FLAMEBREATH);                
                    FlameBreathTimer = 15000;
                }else FlameBreathTimer -= diff;
    
                if(TailSweepTimer < diff)
                {
                    Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 10.0, true, true);
                    if(target && !me->HasInArc(M_PI, target))
                    {
                        DoCast(target, SPELL_TAILSWEEP);
                        TailSweepTimer = 10000;
                    }
                }else TailSweepTimer -= diff;
    
                if(CleaveTimer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_CLEAVE);
                    CleaveTimer = 10000;
                }else CleaveTimer -= diff;
    
                if(WingBuffetTimer < diff)
                {
                    DoCast(me->GetVictim(), SPELL_WINGBUFFET);
                    WingBuffetTimer = 7000 + ((rand()%8)*IN_MILLISECONDS);
                }else WingBuffetTimer -= diff;
    
                if(KnockAwayTimer < diff)
                {
                    if(rand() <= 30)
                    {
                        DoCast(me->GetVictim(), SPELL_KNOCK_AWAY);
                    }
                    KnockAwayTimer = 15000;
                }else KnockAwayTimer -= diff;
    
                if(Phase == 3)
                {
                    if(BellowingRoarTimer < diff)
                    {
                        DoCast(me->GetVictim(), SPELL_BELLOWINGROAR);
    
                        BellowingRoarTimer = 30000;
                    }else BellowingRoarTimer -= diff;
    
                    if(SummonWhelpsTimer < diff)
                    {
                        SummonWhelps();
    
                        SummonWhelpsTimer = 45000;
                    }else SummonWhelpsTimer -= diff;
                }
    
                DoMeleeAttackIfReady();
            }
    
            if(Phase == 2)
            {
                if(InitialSpawn)
                {
                    InitialSpawn = false;
    
                    for(uint32 i = 0; i < 10; ++i)
                    {
                        uint32 random = rand()%4;
                        Creature* Whelp = me->SummonCreature(CREATURE_WHELP, SpawnLocations[random][0], SpawnLocations[random][1], SpawnLocations[random][2], 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000);
                        if(Whelp)
                            Whelp->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM, 0));
                    }
                }
    
                if(EngulfingFlamesTimer < diff)
                {
                    DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_ENGULFINGFLAMES);
                    me->HandleEmoteCommand(ANIM_FLY);
    
                    EngulfingFlamesTimer = 10000;
                }
                else EngulfingFlamesTimer -= diff;
    
                if(FireballTimer < diff)
                {
                    DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_FIREBALL);
    
                    FireballTimer = 18000;
                }
                else FireballTimer -= diff;
    
                if(MovementTimer < diff)
                {
                    if(rand()%100 < 30)
                    {
                        DoScriptText(EMOTE_BREATH, me);
                        DoCast(me->GetVictim(), SPELL_DEEPBREATH);
                    }
                    else ChangePosition();
    
                    MovementTimer = 25000;
                }else MovementTimer -= diff;
    
                if(SummonWhelpsTimer < diff)
                {
                    SummonWhelps();
    
                    SummonWhelpsTimer = 45000;
                }
                else SummonWhelpsTimer -= diff;
            }
        }
    
        void ChangePosition()
        {
            uint32 random = rand() % 4;
            if(random<4){
                me->GetMotionMaster()->MovePoint(0, MovementLocations[random][0], MovementLocations[random][1], MovementLocations[random][2]);}
        }
    
        void SummonWhelps()
        {
            if(Phase == 2)
            {
                uint32 max = rand()%10;
                for(uint32 i = 0; i < max; ++i)
                {
                    uint32 random = rand()%3;
                    Creature* Whelp = me->SummonCreature(CREATURE_WHELP, SpawnLocations[random][0], SpawnLocations[random][1], SpawnLocations[random][2], 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000);
                    if(Whelp)
                        Whelp->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM, 0));
                }
            }
    
            if(Phase == 3)
            {
                uint32 max = rand() % 10 +1;
                if(max < 5)
                {
                    for(uint32 i = 0; i < max; ++i)
                    {
                        uint32 random = rand()%4;
                        Creature* Whelp = me->SummonCreature(CREATURE_WHELP, SpawnLocations[random][0], SpawnLocations[random][1], SpawnLocations[random][2], 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000);
                        if(Whelp)
                            Whelp->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM, 0));
                    }
                }
            }
        }
        
        void OnSpellFinish(Unit *caster, uint32 spellId, Unit *target, bool ok)
        override {
            if (spellId == SPELL_FLAMEBREATH) {
                if (GameObject* blade = me->FindNearestGameObject(179561, 50.0f)) {
                    if (me->HasInArc(M_PI, blade)) {
                        float x, y, z;
                        blade->GetPosition(x, y, z);
                        if (Player* pPlayer = blade->GetOwner()->ToPlayer()) {
                            pPlayer->SummonGameObject(uint32(179562), blade->GetPosition(), G3D::Quat(), 0);
                            blade->Delete();
                        }
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_onyxiaAI(creature);
    }
};


void AddSC_boss_onyxia()
{
    new boss_onyxia();
}

