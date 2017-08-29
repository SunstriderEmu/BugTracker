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
SDName: Boss_Warp_Splinter
SD%Complete: 80
SDComment: Includes Sapling (need some better control with these).
SDCategory: Tempest Keep, The Botanica
EndScriptData */



/*#####
# mob_treant (Sapling)
#####*/

#define SPELL_HEAL_FATHER   6262

/*#####
# boss_warp_splinter
#####*/

#define SAY_AGGRO           -1553007
#define SAY_SLAY_1          -1553008
#define SAY_SLAY_2          -1553009
#define SAY_SUMMON_1        -1553010
#define SAY_SUMMON_2        -1553011
#define SAY_DEATH           -1553012

#define WAR_STOMP           34716
#define SUMMON_TREANTS      34727                           // DBC: 34727, 34731, 34733, 34734, 34736, 34739, 34741 (with Ancestral Life spell 34742)   // won't work (guardian summon)
#define ARCANE_VOLLEY       (HeroicMode?39133:36705)

#define CREATURE_TREANT     19949

#define TREANT_SPAWN_DIST   50                              //50 yards from Warp Splinter's spawn point

float treant_pos[6][3] =
{
    {24.301233, 427.221100, -27.060635},
    {16.795492, 359.678802, -27.355425},
    {53.493484, 345.381470, -26.196192},
    {61.867096, 439.362732, -25.921030},
    {109.861877, 423.201630, -27.356019},
    {106.780159, 355.582581, -27.593357}
};


class mob_warp_splinter_treant : public CreatureScript
{
public:
    mob_warp_splinter_treant() : CreatureScript("mob_warp_splinter_treant")
    { }

    class mob_treantAI : public ScriptedAI
    {
    public:
        mob_treantAI(Creature *c) : ScriptedAI(c)
        {
            WarpGuid = 0;
        }

        uint64 WarpGuid;
        uint32 check_Timer;

        void Reset()
            override {
            check_Timer = 0;
        }

        void EnterCombat(Unit *who) override {}

        void MoveInLineOfSight(Unit*) override {}

        void UpdateAI(const uint32 diff)
            override {
            if (!UpdateVictim())
            {
                if (WarpGuid && check_Timer < diff)
                {
                    if (Unit *Warp = (Unit*)ObjectAccessor::GetUnit(*me, WarpGuid))
                    {
                        if (me->IsWithinMeleeRange(Warp, 2.5f))
                        {
                            int32 CurrentHP_Treant = (int32)me->GetHealth();
                            Warp->CastCustomSpell(Warp, SPELL_HEAL_FATHER, &CurrentHP_Treant, nullptr, nullptr, true, nullptr, nullptr, me->GetGUID());
                            me->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                            return;
                        }
                        me->GetMotionMaster()->MoveFollow(Warp, 0, 0);
                    }
                    check_Timer = 1000;
                }
                else check_Timer -= diff;
                return;
            }

            if (me->GetVictim()->GetGUID() != WarpGuid)
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_treantAI(creature);
    }
};

class boss_warp_splinter : public CreatureScript
{
public:
    boss_warp_splinter() : CreatureScript("boss_warp_splinter")
    { }

    class boss_warp_splinterAI : public ScriptedAI
    {
        public:
        boss_warp_splinterAI(Creature *c) : ScriptedAI(c), summons(me)
        {
            HeroicMode = c->GetMap()->IsHeroic();
            Treant_Spawn_Pos_X = c->GetPositionX();
            Treant_Spawn_Pos_Y = c->GetPositionY();
        }
    
        uint32 War_Stomp_Timer;
        uint32 Summon_Treants_Timer;
        uint32 Arcane_Volley_Timer;
        bool HeroicMode;
    
        float Treant_Spawn_Pos_X;
        float Treant_Spawn_Pos_Y;
        
        SummonList summons;
    
        void Reset()
        override {
            War_Stomp_Timer = 25000 + rand()%15000;
            Summon_Treants_Timer = 45000;
            Arcane_Volley_Timer = 8000 + rand()%12000;
    
            me->SetSpeedRate( MOVE_RUN, 0.7f, true);
            
            summons.DespawnAll();
        }
        
        void JustSummoned(Creature* pSummon)
        override {
            summons.Summon(pSummon);
        }
        
        void SummonedCreatureDespawn(Creature* pSummon) override { summons.Despawn(pSummon); }
    
        void EnterCombat(Unit *who)
        override {
            DoScriptText(SAY_AGGRO, me);
        }
    
        void KilledUnit(Unit* victim)
        override {
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_SLAY_1, me); break;
            case 1: DoScriptText(SAY_SLAY_2, me); break;
            }
        }
    
        void JustDied(Unit* Killer)
        override {
            DoScriptText(SAY_DEATH, me);
        }
    
        void SummonTreants()
        {
            for(int i = 0; i < 6; ++i)
            {
                float angle = (M_PI / 3) * i;
    
                float X = Treant_Spawn_Pos_X + TREANT_SPAWN_DIST * cos(angle);
                float Y = Treant_Spawn_Pos_Y + TREANT_SPAWN_DIST * sin(angle);
                float O = - me->GetAngle(X,Y);
    
                if(Creature *pTreant = me->SummonCreature(CREATURE_TREANT,treant_pos[i][0],treant_pos[i][1],treant_pos[i][2],O,TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN,25000))
                    ((mob_warp_splinter_treant::mob_treantAI*)pTreant->AI())->WarpGuid = me->GetGUID();
            }
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_SUMMON_1, me); break;
            case 1: DoScriptText(SAY_SUMMON_2, me); break;
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!UpdateVictim() )
                return;
    
            if (me->GetDistance2d(65.8663f, 392.454f) >= 50.0f) {
                EnterEvadeMode();
                return;
            }
    
            //Check for War Stomp
            if(War_Stomp_Timer < diff)
            {
                DoCast(me->GetVictim(),WAR_STOMP);
                War_Stomp_Timer = 25000 + rand()%15000;
            }else War_Stomp_Timer -= diff;
    
            //Check for Arcane Volley
            if(Arcane_Volley_Timer < diff)
            {
                DoCast(me->GetVictim(),ARCANE_VOLLEY);
                Arcane_Volley_Timer = 20000 + rand()%15000;
            }else Arcane_Volley_Timer -= diff;
    
            //Check for Summon Treants
            if(Summon_Treants_Timer < diff)
            {
                SummonTreants();
                Summon_Treants_Timer = 45000;
            }else Summon_Treants_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_warp_splinterAI(creature);
    }
};


void AddSC_boss_warp_splinter()
{
    new boss_warp_splinter();
    new mob_warp_splinter_treant();
}

