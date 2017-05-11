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
SDName: Boss_NexusPrince_Shaffar
SD%Complete: 80
SDComment: Need more tuning of spell timers, it should not be as linear fight as current. Also should possibly find a better way to deal with his three initial beacons to make sure all aggro.
SDCategory: Auchindoun, Mana Tombs
EndScriptData */

/* ContentData
boss_nexusprince_shaffar
mob_ethereal_beacon
EndContentData */



#define SAY_INTRO                       -1557000

#define SAY_AGGRO_1                     -1557001
#define SAY_AGGRO_2                     -1557002
#define SAY_AGGRO_3                     -1557003

#define SAY_SLAY_1                      -1557004
#define SAY_SLAY_2                      -1557005

#define SAY_SUMMON                      -1557006

#define SAY_DEAD                        -1557007

#define SPELL_BLINK                     34605
#define SPELL_FROSTBOLT                 32370
#define SPELL_FIREBALL                  20420
#define SPELL_FROSTNOVA                 32365

#define SPELL_ETHEREAL_BEACON           32371               // Summon 18431
#define SPELL_ETHEREAL_BEACON_VISUAL    32368

#define ENTRY_BEACON                    18431
#define ENTRY_SHAFFAR                   18344

#define NR_INITIAL_BEACONS              3

struct boss_nexusprince_shaffarAI : public ScriptedAI
{
    boss_nexusprince_shaffarAI(Creature *c) : ScriptedAI(c), Summons(me) {}

    uint32 Blink_Timer;
    uint32 Beacon_Timer;
    uint32 FireBall_Timer;
    uint32 Frostbolt_Timer;
    uint32 FrostNova_Timer;

    SummonList Summons;

    bool IntroDone;
    bool CanBlink;

    void Reset()
    override {
        Summons.DespawnAll();

        Blink_Timer = 1500;
        Beacon_Timer = 10000;
        FireBall_Timer = 8000;
        Frostbolt_Timer = 4000;
        FrostNova_Timer = 15000;

        IntroDone = false;

        float dist = 3.0f;
        float posX, posY, posZ, angle;
        me->GetHomePosition(posX, posY, posZ, angle);
        float x[3] = { posX - dist, posX - dist, posX + dist };
        float y[3] = { posY - dist, posY + dist, posY };

        for(uint8 i = 0; i < NR_INITIAL_BEACONS; i++)
            me->SummonCreature(ENTRY_BEACON, x[i], y[i], posZ, angle, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
    }

    void MoveInLineOfSight(Unit *who)
    override {
        if( !me->GetVictim() && me->CanAttack(who) == CAN_ATTACK_RESULT_OK && ( me->IsHostileTo( who )) && who->isInAccessiblePlaceFor(me) )
        {
            if( !IntroDone && me->IsWithinDistInMap(who, 100.0) )
            {
                DoScriptText(SAY_INTRO, me);
                IntroDone = true;
            }

            if (!me->CanFly() && me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                return;

            float attackRadius = me->GetAggroRange(who);
            if( me->IsWithinDistInMap(who, attackRadius) && me->IsWithinLOSInMap(who) )
            {
                //who->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
                AttackStart(who);
            }
        }
    }

    void EnterCombat(Unit *who)
    override {
        switch(rand()%3)
        {
            case 0: DoScriptText(SAY_AGGRO_1, me); break;
            case 1: DoScriptText(SAY_AGGRO_2, me); break;
            case 2: DoScriptText(SAY_AGGRO_3, me); break;
        }
    }

    void JustSummoned(Creature *summoned)
    override {
        Summons.Summon(summoned);
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
        DoScriptText(SAY_DEAD, me);
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        if( FrostNova_Timer < diff )
        {
            if( me->IsNonMeleeSpellCast(false) )
                me->InterruptNonMeleeSpells(true);

            DoCast(me,SPELL_FROSTNOVA);
            FrostNova_Timer  = 17500 + rand()%7500;
            Blink_Timer = 1000 + rand()%1500;
        }else FrostNova_Timer -= diff;

        if( Frostbolt_Timer < diff )
        {
            DoCast(me->GetVictim(),SPELL_FROSTBOLT);
            Frostbolt_Timer = 4500 + rand()%1500;
        }else Frostbolt_Timer -= diff;

        if( FireBall_Timer < diff )
        {
            DoCast(me->GetVictim(),SPELL_FIREBALL);
            FireBall_Timer = 4500 + rand()%1500;
        }else FireBall_Timer -= diff;

        if( Blink_Timer )
        {
            if( Blink_Timer <= diff )
            {
                if(DoCast(me,SPELL_BLINK) == SPELL_CAST_OK)
                    Blink_Timer = 0;
            }else Blink_Timer -= diff;
        }

        if( Beacon_Timer < diff)
        {
            if(DoCast(me,SPELL_ETHEREAL_BEACON) == SPELL_CAST_OK)
            {
                Beacon_Timer = 10000;

                if( !urand(0,3) )
                    DoScriptText(SAY_SUMMON, me);
            }

        }else Beacon_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_nexusprince_shaffar(Creature *_Creature)
{
    return new boss_nexusprince_shaffarAI (_Creature);
}

#define SPELL_ARCANE_BOLT               15254
#define SPELL_ETHEREAL_APPRENTICE       32372               // Summon 18430

struct mob_ethereal_beaconAI : public ScriptedAI
{
    mob_ethereal_beaconAI(Creature *c) : ScriptedAI(c)
    {
        HeroicMode = me->GetMap()->IsHeroic();
    }

    bool HeroicMode;
    uint32 Apprentice_Timer;
    uint32 ArcaneBolt_Timer;

    void KillSelf()
    {
        me->Kill(me);
    }

    void Reset()
    override {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->CastSpell(me,SPELL_ETHEREAL_BEACON_VISUAL,false);
        Apprentice_Timer = (HeroicMode ? 10000 : 20000);
        ArcaneBolt_Timer = 1000;
    }

    void EnterCombat(Unit *who)
    override {
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void JustSummoned(Creature *summoned)
    override {
        summoned->AI()->AttackStart(me->GetVictim());
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        if( ArcaneBolt_Timer < diff )
        {
            DoCast(me->GetVictim(),SPELL_ARCANE_BOLT);
            ArcaneBolt_Timer = 2000 + rand()%2500;
        }else ArcaneBolt_Timer -= diff;

        if( Apprentice_Timer < diff )
        {
            if(me->CastSpell(me,SPELL_ETHEREAL_APPRENTICE,true) == SPELL_CAST_OK)
            {
                KillSelf();
                Apprentice_Timer = (HeroicMode ? 10000 : 20000);
            }
        }else Apprentice_Timer -= diff;
    }
};

CreatureAI* GetAI_mob_ethereal_beacon(Creature *_Creature)
{
    return new mob_ethereal_beaconAI (_Creature);
}

#define SPELL_ETHEREAL_APPRENTICE_FIREBOLT          32369
#define SPELL_ETHEREAL_APPRENTICE_FROSTBOLT         32370

struct mob_ethereal_apprenticeAI : public ScriptedAI
{
    mob_ethereal_apprenticeAI(Creature *c) : ScriptedAI(c) {}

    uint32 Cast_Timer;

    bool isFireboltTurn;

    void EnterEvadeMode(EvadeReason /* why */)
    override {
        me->Kill(me);
    }

    void Reset()
    override {
        Cast_Timer = 3000;
        isFireboltTurn = true;
    }

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;

        if(Cast_Timer < diff)
        {
            me->CastSpell(me->GetVictim(), isFireboltTurn ? SPELL_ETHEREAL_APPRENTICE_FIREBOLT : SPELL_ETHEREAL_APPRENTICE_FROSTBOLT, true);
            isFireboltTurn = !isFireboltTurn;
            Cast_Timer = 3000;
        }else Cast_Timer -= diff;
    }
};

CreatureAI* GetAI_mob_ethereal_apprentice(Creature *_Creature)
{
    return new mob_ethereal_apprenticeAI (_Creature);
}

void AddSC_boss_nexusprince_shaffar()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="boss_nexusprince_shaffar";
    newscript->GetAI = &GetAI_boss_nexusprince_shaffar;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="mob_ethereal_beacon";
    newscript->GetAI = &GetAI_mob_ethereal_beacon;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name="mob_ethereal_apprentice";
    newscript->GetAI = &GetAI_mob_ethereal_apprentice;
    sScriptMgr->RegisterOLDScript(newscript);
}

