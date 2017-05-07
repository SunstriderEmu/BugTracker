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
SDName: boss_Halazzi
SD%Complete: 80
SDComment:
SDCategory: Zul'Aman
EndScriptData */


#include "def_zulaman.h"
//#include "spell.h"

#define YELL_AGGRO "À genoux, les idiots… devant la griffe et le croc !"
#define SOUND_AGGRO                     12020
#define YELL_SABER_ONE "Vous partirez pas en un seul morceau !"
#define SOUND_SABER_ONE                 12024
#define YELL_SABER_TWO "J'vais te couper en deux !"
#define SOUND_SABER_TWO                 12023
#define YELL_SPLIT "L'esprit en moi, il est indompté !"
#define SOUND_SPLIT                    12021
#define YELL_MERGE "Esprit, reviens à moi !"
#define SOUND_MERGE                    12022
#define YELL_KILL_ONE "J'ai trop la puissance pour vous !"
#define SOUND_KILL_ONE                12026
#define YELL_KILL_TWO "Vous allez tous échouer !"
#define SOUND_KILL_TWO                12027
#define YELL_DEATH "Chaga... choka'jinn."
#define SOUND_DEATH                    12028
#define YELL_BERSERK "Alors les gars, on retient ses coups ?"
#define SOUND_BERSERK                12025

#define SPELL_DUAL_WIELD                29651
#define SPELL_SABER_LASH                43267
#define SPELL_FRENZY                    43139
#define SPELL_FLAMESHOCK                43303
#define SPELL_EARTHSHOCK                43305
#define SPELL_TRANSFORM_SPLIT           43142
#define SPELL_TRANSFORM_SPLIT2          43573
#define SPELL_TRANSFORM_MERGE           43271
#define SPELL_SUMMON_LYNX               43143
#define SPELL_SUMMON_TOTEM              43302
#define SPELL_BERSERK                   45078

#define MOB_SPIRIT_LYNX                 24143
#define SPELL_LYNX_FRENZY               43290
#define SPELL_SHRED_ARMOR               43243

#define MOB_TOTEM                       24224
#define SPELL_LIGHTNING                 43301

enum PhaseHalazzi
{
    PHASE_NONE = 0,
    PHASE_LYNX = 1,
    PHASE_SPLIT = 2,
    PHASE_HUMAN = 3,
    PHASE_MERGE = 4,
    PHASE_ENRAGE = 5
};

struct boss_halazziAI : public ScriptedAI
{
    boss_halazziAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        // need to find out what controls totem's spell cooldown
        /*SpellInfo *TempSpell = (SpellInfo*)sSpellMgr->GetSpellInfo(SPELL_LIGHTNING);
        if(TempSpell && TempSpell->CastingTimeIndex != 5)
            TempSpell->CastingTimeIndex = 5; // 2000 ms casting time*/
    }

    InstanceScript *pInstance;

    uint32 FrenzyTimer;
    uint32 SaberlashTimer;
    uint32 ShockTimer;
    uint32 TotemTimer;
    uint32 CheckTimer;
    uint32 BerserkTimer;

    uint32 TransformCount;

    PhaseHalazzi Phase;

    uint64 LynxGUID;

    void Reset()
    override {
        if(pInstance && pInstance->GetData(DATA_HALAZZIEVENT) != DONE)
            pInstance->SetData(DATA_HALAZZIEVENT, NOT_STARTED);

        TransformCount = 0;
        BerserkTimer = 600000;
        CheckTimer = 1000;

        DoCast(me, SPELL_DUAL_WIELD, true);

        Phase = PHASE_NONE;
        EnterPhase(PHASE_LYNX);
    }

    void EnterCombat(Unit *who)
    override {
        if(pInstance)
            pInstance->SetData(DATA_HALAZZIEVENT, IN_PROGRESS);

        me->Yell(YELL_AGGRO, LANG_UNIVERSAL, nullptr);
        DoPlaySoundToSet(me, SOUND_AGGRO);

        EnterPhase(PHASE_LYNX);
    }

    void JustSummoned(Creature* summon)
    override {
        summon->AI()->AttackStart(me->GetVictim());
        if(summon->GetEntry() == MOB_SPIRIT_LYNX)
            LynxGUID = summon->GetGUID();
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    override {
        if(damage >= me->GetHealth() && Phase != PHASE_ENRAGE)
            damage = 0;
    }

    void SpellHit(Unit*, const SpellInfo *spell)
    override {
        if(spell->Id == SPELL_TRANSFORM_SPLIT2)
            EnterPhase(PHASE_HUMAN);
    }

    void AttackStart(Unit *who)
    override {
        if(Phase != PHASE_MERGE) ScriptedAI::AttackStart(who);
    }

    void EnterPhase(PhaseHalazzi NextPhase)
    {
        switch(NextPhase)
        {
        case PHASE_LYNX:
        case PHASE_ENRAGE:
            if(Phase == PHASE_MERGE)
            {
                me->CastSpell(me, SPELL_TRANSFORM_MERGE, true);
                me->Attack(me->GetVictim(), true);
                me->GetMotionMaster()->MoveChase(me->GetVictim());
            }
            if(Unit *Lynx = ObjectAccessor::GetUnit(*me, LynxGUID))
            {
                Lynx->SetVisibility(VISIBILITY_OFF);
                Lynx->SetDeathState(JUST_DIED);
            }
            me->SetMaxHealth(600000);
            me->SetHealth(600000 - 150000 * TransformCount);
            FrenzyTimer = 16000;
            SaberlashTimer = 20000;
            ShockTimer = 10000;
            TotemTimer = 12000;
            break;
        case PHASE_SPLIT:
            me->Yell(YELL_SPLIT, LANG_UNIVERSAL, nullptr);
            DoPlaySoundToSet(me, SOUND_SPLIT);
            me->CastSpell(me, SPELL_TRANSFORM_SPLIT, true);
            break;
        case PHASE_HUMAN:
            //DoCast(me, SPELL_SUMMON_LYNX, true);
            DoSpawnCreature(MOB_SPIRIT_LYNX, 5,5,0,0, TEMPSUMMON_CORPSE_DESPAWN, 0);
            me->SetMaxHealth(400000);
            me->SetHealth(400000);
            ShockTimer = 10000;
            TotemTimer = 12000;
            break;
        case PHASE_MERGE:
            if(Unit *Lynx = ObjectAccessor::GetUnit(*me, LynxGUID))
            {
                me->Yell(YELL_MERGE, LANG_UNIVERSAL, nullptr);
                DoPlaySoundToSet(me, SOUND_MERGE);
                Lynx->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                Lynx->GetMotionMaster()->Clear();
                Lynx->GetMotionMaster()->MoveFollow(me, 0, 0);
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveFollow(Lynx, 0, 0);
                TransformCount++;
            }break;
        default:
            break;
        }
        Phase = NextPhase;
    }

     void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;

        if(BerserkTimer < diff)
        {
            me->Yell(YELL_BERSERK, LANG_UNIVERSAL, nullptr);
            DoPlaySoundToSet(me, SOUND_BERSERK);
            DoCast(me, SPELL_BERSERK, true);
            BerserkTimer = 60000;
        }else BerserkTimer -= diff;

        if(Phase == PHASE_LYNX || Phase == PHASE_ENRAGE)
        {
            if(SaberlashTimer < diff)
            {
                switch(rand()%2) {
                case 0:
                    me->Yell(YELL_SABER_ONE, LANG_UNIVERSAL, nullptr);
                    DoPlaySoundToSet(me, SOUND_SABER_ONE);
                    break;

                case 1:
                    me->Yell(YELL_SABER_TWO, LANG_UNIVERSAL, nullptr);
                    DoPlaySoundToSet(me, SOUND_SABER_TWO);
                    break;
                }
                // A tank with more than 490 defense skills should receive no critical hit
                //me->CastSpell(me, 41296, true);
                me->CastSpell(me->GetVictim(), SPELL_SABER_LASH, true);
                //me->RemoveAurasDueToSpell(41296);
                SaberlashTimer = 30000;
            }else SaberlashTimer -= diff;

            if(FrenzyTimer < diff)
            {
                DoCast(me, SPELL_FRENZY);
                FrenzyTimer = (10+rand()%5)*IN_MILLISECONDS;
            }else FrenzyTimer -= diff;

            if(Phase == PHASE_LYNX)
            {
                if(CheckTimer < diff)
                {
                    if(me->GetHealth() * 4 < me->GetMaxHealth() * (3 - TransformCount))
                        EnterPhase(PHASE_SPLIT);
                    CheckTimer = 1000;
                } else { CheckTimer -= diff; }
            }
        }

        if(Phase == PHASE_HUMAN || Phase == PHASE_ENRAGE)
        {
            if(TotemTimer < diff)
            {
                //DoCast(me, SPELL_SUMMON_TOTEM);
                float totemX, totemY, totemZ;
                me->GetRandomPoint(me, 1.0f, totemX, totemY, totemZ);
                me->SummonCreature(MOB_TOTEM, totemX, totemY, totemZ, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
                TotemTimer = 20000;
            }else TotemTimer -= diff;

            if(ShockTimer < diff)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,80.0f,true))
                {
                    if(target->IsNonMeleeSpellCast(false))
                        DoCast(target,SPELL_EARTHSHOCK);
                    else
                        DoCast(target,SPELL_FLAMESHOCK);
                    ShockTimer = 10000 + rand()%5000;
                }
            }else ShockTimer -= diff;

            if(Phase == PHASE_HUMAN)
            {
                if(CheckTimer < diff)
                {
                    if( (me->GetHealthPct() <= 20)/*me->GetHealth() * 10 < me->GetMaxHealth()*/)
                    {
                        EnterPhase(PHASE_MERGE);
                    }
                    else /* WTF? */
                    {
                        Unit *Lynx = ObjectAccessor::GetUnit(*me, LynxGUID);
                        if(Lynx && (Lynx->GetHealthPct() <= 20)/*Lynx->GetHealth() * 10 < Lynx->GetMaxHealth()*/)
                            EnterPhase(PHASE_MERGE);
                    }
                    CheckTimer = 1000;
                } else { CheckTimer -= diff; }
            }
        }

        if(Phase == PHASE_MERGE)
        {
            if(CheckTimer < diff)
            {
                Unit *Lynx = ObjectAccessor::GetUnit(*me, LynxGUID);
                if(Lynx)
                {
                    Lynx->GetMotionMaster()->MoveFollow(me, 0, 0);
                    me->GetMotionMaster()->MoveFollow(Lynx, 0, 0);
                    if(me->IsWithinDistInMap(Lynx, 6.0f))
                    {
                        if(TransformCount < 3)
                            EnterPhase(PHASE_LYNX);
                        else
                            EnterPhase(PHASE_ENRAGE);
                    }
                }
                CheckTimer = 1000;
            }else CheckTimer -= diff;
        }

        DoMeleeAttackIfReady();
    }

    void KilledUnit(Unit* victim)
    override {
        switch(rand()%2)
        {
        case 0:
            me->Yell(YELL_KILL_ONE, LANG_UNIVERSAL, nullptr);
            DoPlaySoundToSet(me, SOUND_KILL_ONE);
            break;

        case 1:
            me->Yell(YELL_KILL_TWO, LANG_UNIVERSAL, nullptr);
            DoPlaySoundToSet(me, SOUND_KILL_TWO);
            break;
        }
    }

    void JustDied(Unit* Killer)
    override {
        if(pInstance)
            pInstance->SetData(DATA_HALAZZIEVENT, DONE);

        me->Yell(YELL_DEATH, LANG_UNIVERSAL, nullptr);
        DoPlaySoundToSet(me, SOUND_DEATH);
    }
};

// Spirits Lynx AI

struct boss_spiritlynxAI : public ScriptedAI
{
    boss_spiritlynxAI(Creature *c) : ScriptedAI(c) {}

    uint32 FrenzyTimer;
    uint32 shredder_timer;

    void Reset()
    override {
        FrenzyTimer = (30+rand()%20)*IN_MILLISECONDS;  //frenzy every 30-50 seconds
        shredder_timer = 4000;
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    override {
        if(damage >= me->GetHealth())
            damage = 0;
    }

    void AttackStart(Unit *who)
    override {
        if(!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            ScriptedAI::AttackStart(who);
    }

    void EnterCombat(Unit *who) override {/*DoZoneInCombat();*/}

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        if(FrenzyTimer < diff)
        {
            DoCast(me, SPELL_LYNX_FRENZY);
            FrenzyTimer = (30+rand()%20)*IN_MILLISECONDS;
        }else FrenzyTimer -= diff;

        if(shredder_timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_SHRED_ARMOR);
            shredder_timer = 4000;
        }else shredder_timer -= diff;

        DoMeleeAttackIfReady();
    }

};

struct  npc_corruptedlightningtotemAI : public ScriptedAI
{
    npc_corruptedlightningtotemAI(Creature *c) : ScriptedAI(c) 
    {
        SetCombatMovementAllowed(false);
    }
    
    uint32 globalCD;
    
    void Reset()
    override {
        globalCD = 100;     // Begin after 100 ms and then every 1000 ms
    }
    
    void EnterCombat(Unit* pWho) override {}
    
    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;
            
        Creature *halazzi = me->FindNearestCreature(23577, 150.0f, true);
        if (!halazzi)
            me->DisappearAndDie();
            
        if (globalCD < diff) {
            Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true);
            if (target) {
                DoCast(target, SPELL_LIGHTNING);
                globalCD = 1000;
            }
        }else globalCD -= diff;
    }
};

CreatureAI* GetAI_boss_halazziAI(Creature *_Creature)
{
    return new boss_halazziAI (_Creature);
}

CreatureAI* GetAI_boss_spiritlynxAI(Creature *_Creature)
{
    return new boss_spiritlynxAI (_Creature);
}

CreatureAI* GetAI_npc_corruptedlightningtotemAI(Creature* pCreature)
{
    return new npc_corruptedlightningtotemAI(pCreature);
}

void AddSC_boss_halazzi()
{
    OLDScript *newscript;
    newscript = new OLDScript;
    newscript->Name="boss_halazzi";
    newscript->GetAI = &GetAI_boss_halazziAI;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="mob_halazzi_lynx";
    newscript->GetAI = &GetAI_boss_spiritlynxAI;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "totem_halazzi";
    newscript->GetAI = &GetAI_npc_corruptedlightningtotemAI;
    sScriptMgr->RegisterOLDScript(newscript);
}

