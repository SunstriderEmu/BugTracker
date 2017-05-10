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
SDName: Boss_Brutallus
SD%Complete: 80
SDComment: Find a way to start the intro, best code for the intro
EndScriptData */


#include "def_sunwell_plateau.h"

enum Quotes
{
    YELL_INTRO                 =   -1580017,
    YELL_INTRO_BREAK_ICE       =   -1580018,
    YELL_INTRO_CHARGE          =   -1580019,
    YELL_INTRO_KILL_MADRIGOSA  =   -1580020,
    YELL_INTRO_TAUNT           =   -1580021,

    YELL_MADR_ICE_BARRIER      =   -1580031,
    YELL_MADR_INTRO            =   -1580032,
    YELL_MADR_ICE_BLOCK        =   -1580033,
    YELL_MADR_TRAP             =   -1580034,
    YELL_MADR_DEATH            =   -1580035,

    YELL_AGGRO                 =   -1580022,
    YELL_KILL1                 =   -1580023,
    YELL_KILL2                 =   -1580024,
    YELL_KILL3                 =   -1580025,
    YELL_LOVE1                 =   -1580026,
    YELL_LOVE2                 =   -1580027,
    YELL_LOVE3                 =   -1580028,
    YELL_BERSERK               =   -1580029,
    YELL_DEATH                 =   -1580030
};

enum Spells
{
    SPELL_METEOR_SLASH                 =   45150,
    SPELL_BURN                         =   46394,
    SPELL_STOMP                        =   45185,
    SPELL_BERSERK                      =   26662,
    SPELL_DUAL_WIELD                   =   42459,

    SPELL_INTRO_FROST_BLAST            =   45203,
    SPELL_INTRO_FROSTBOLT              =   44843,
    SPELL_INTRO_ENCAPSULATE            =   45665,
    SPELL_INTRO_ENCAPSULATE_CHANELLING =   45661
};

#define FELMYST 25038

struct boss_brutallusAI : public ScriptedAI
{
    boss_brutallusAI(Creature *c) : ScriptedAI(c){
        pInstance = ((InstanceScript*)c->GetInstanceScript());
        Intro = true;
    }

    InstanceScript* pInstance;

    uint32 SlashTimer;
    uint32 BurnTimer;
    uint32 StompTimer;
    uint32 BerserkTimer;

    uint32 IntroPhase;
    uint32 IntroPhaseTimer;
    uint32 IntroFrostBoltTimer;

    bool Intro;
    bool IsIntro;
    bool Enraged;

    void Reset() override
    {
        SlashTimer = 11000;
        StompTimer = 30000;
        BurnTimer = 20000;
        BerserkTimer = 360000;

        IntroPhase = 0;
        IntroPhaseTimer = 0;
        IntroFrostBoltTimer = 0;

        IsIntro = false;
        Enraged = false;
        //Intro = true; // TODO: RESTORE INTRO IN CONSTRUCTOR AFTER TESTS

        me->CastSpell(me, SPELL_DUAL_WIELD, true);

        if (pInstance && pInstance->GetData(DATA_BRUTALLUS_EVENT) != DONE)
            pInstance->SetData(DATA_BRUTALLUS_EVENT, NOT_STARTED);

        if (pInstance && pInstance->GetData(DATA_BRUTALLUS_EVENT) == DONE && pInstance->GetData(DATA_FELMYST_EVENT) != DONE) {
            if (Player *plr = pInstance->GetPlayer()) {
                float x,y,z;
                me->GetPosition(x,y,z);
                plr->SummonCreature(FELMYST, x,y, z+30, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
                if (Creature *Madrigosa = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_MADRIGOSA)))
                    Madrigosa->SetVisible(false);
            }
        }
        
        me->SetFullTauntImmunity(false);
    }

    void EnterCombat(Unit *who) override
    {
        if (Intro || IsIntro)
            return;

        DoScriptText(YELL_AGGRO, me);

        if (pInstance)
            pInstance->SetData(DATA_BRUTALLUS_EVENT, IN_PROGRESS);
            
        if (who->ToPlayer() && !Intro && !IsIntro) {
            if (Creature *Madrigosa = ObjectAccessor::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MADRIGOSA) : 0))
                Madrigosa->SetVisible(false);
        }
    }

    void KilledUnit(Unit* victim) override
    {
        DoScriptText(RAND(YELL_KILL1,YELL_KILL2,YELL_KILL3), me);
    }
    
    void EnterEvadeMode(EvadeReason why)
    override {
        if (!Intro)
            ScriptedAI::EnterEvadeMode(why);
    }

    void JustDied(Unit* Killer)
    override {
        if (Creature *Madrigosa = ObjectAccessor::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MADRIGOSA) : 0)) {
            Madrigosa->SetVisible(false);
            Madrigosa->Respawn();
            Madrigosa->Kill(Madrigosa);
            Madrigosa->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
            Madrigosa->SetVisible(true);
            Madrigosa->SummonCreature(25703, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
        }

        DoScriptText(YELL_DEATH, me);

        if (pInstance){
            pInstance->SetData(DATA_BRUTALLUS_EVENT, DONE);
            
            // Force removal of Burn aura on all players in map
            Map::PlayerList const& players = pInstance->instance->GetPlayers();
            if (!players.isEmpty()) {
                for(const auto & player : players) {
                    if (Player* plr = player.GetSource())
                        plr->RemoveAurasDueToSpell(SPELL_BURN);
                }
            }
        }
    }

    void StartIntro()
    {
        if (!Intro || IsIntro)
            return;
            
        if (me->IsDead())
            return;
            
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);

        Creature *Madrigosa = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_MADRIGOSA));
        if (Madrigosa) {
            (Madrigosa->ToCreature())->Respawn();
            Madrigosa->SetKeepActiveTimer(5 * MINUTE*IN_MILLISECONDS);
            IsIntro = true;
            Madrigosa->SetMaxHealth(10000000);
            Madrigosa->SetHealth(me->GetMaxHealth());
            IntroPhaseTimer = 1000;
        }
        else {
            //Madrigosa not found, end intro
            error_log("Madrigosa was not found");
            EndIntro();
        }
    }

    void EndIntro()
    {
        //error_log("Brutallus: Ending intro");
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        me->SetReactState(REACT_AGGRESSIVE);
        Intro = false;
        IsIntro = false;
    }

    void DoIntro()
    {
        Creature *Madrigosa = ObjectAccessor::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MADRIGOSA) : 0);
        if (!Madrigosa)
            return;
            
        //TC_LOG_INFO("IntroPhase %u", IntroPhase);

        switch (IntroPhase) {
        case 0:
            DoScriptText(YELL_MADR_ICE_BARRIER, Madrigosa);
            if (GameObject *IceBarrier = GameObject::GetGameObject(*me, pInstance ? pInstance->GetData64(DATA_GO_ICE_BARRIER) : 0)) {
                IceBarrier->SetLootState(GO_READY);
                IceBarrier->UseDoorOrButton();
            }
            else
                TC_LOG_ERROR("scripts","Sunwell/Brutallus Intro: Ice Barrier not found!");
            me->AttackStop();
            me->SetReactState(REACT_DEFENSIVE);
            Madrigosa->SetReactState(REACT_DEFENSIVE);
            IntroPhaseTimer = 7000;
            ++IntroPhase;
            break;
        case 1:
            me->SetInFront(Madrigosa);
            Madrigosa->SetInFront(me);
            DoScriptText(YELL_MADR_INTRO, Madrigosa, me);
            IntroPhaseTimer = 9000;
            ++IntroPhase;
            break;
        case 2:
            DoScriptText(YELL_INTRO, me, Madrigosa);
            AttackStart(Madrigosa);
            Madrigosa->AI()->AttackStart(me);
            IntroPhaseTimer = 13000;
            ++IntroPhase;
            break;
        case 3:
        {
            Madrigosa->GetMotionMaster()->Clear(false);
            Madrigosa->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
            Madrigosa->SetDisableGravity(true);
            IntroPhaseTimer = 500;
            ++IntroPhase;
            break;
        }
        case 4:
        {
            Madrigosa->GetMotionMaster()->MovePoint(0, Madrigosa->GetPositionX(), Madrigosa->GetPositionY()+2, Madrigosa->GetPositionZ()+8);
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            Madrigosa->AttackStop();
            Madrigosa->SetReactState(REACT_PASSIVE);
            IntroPhaseTimer = 3000;
            ++IntroPhase;
            break;
        }
        case 5:
        {
            //((ScriptedAI*)Madrigosa->AI())->AttackStart(me, false);
            Madrigosa->CastSpell(me, 45203, true);
            IntroPhaseTimer = 800;
            ++IntroPhase;
            break;
        }
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        {
            Madrigosa->CastSpell(me, 44843, true);
            IntroPhaseTimer = 1100;
            ++IntroPhase;
            break;
        }
        case 12:
        {
            float x, y, z, ori;
            Madrigosa->GetHomePosition(x, y, z, ori);
            Madrigosa->GetMotionMaster()->MovePoint(1, x, y, z);
            IntroPhaseTimer = 1000;
            ++IntroPhase;
            break;
        }
        case 13:
        {
            Madrigosa->SetDisableGravity(false);
            Madrigosa->StopMoving();
            Madrigosa->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
            IntroPhaseTimer = 1000;
            ++IntroPhase;
            break;
        }
        case 14:
        {
            //Madrigosa->AI()->AttackStart(me);
            AttackStart(Madrigosa);
            IntroPhaseTimer = 6000;
            ++IntroPhase;
            break;
        }
        case 15:
            Madrigosa->CastSpell(me, SPELL_INTRO_ENCAPSULATE_CHANELLING, true);
            DoScriptText(YELL_MADR_TRAP, Madrigosa);
            DoCast(me, SPELL_INTRO_ENCAPSULATE);
            IntroPhaseTimer = 11000;
            ++IntroPhase;
            break;
        case 16:
            DoScriptText(YELL_INTRO_CHARGE, me);
            IntroPhaseTimer = 5000;
            ++IntroPhase;
            break;
        case 17:
            DoCast(Madrigosa, SPELL_STOMP);
            me->Kill(Madrigosa);
            DoScriptText(YELL_MADR_DEATH, Madrigosa);
            me->SetHealth(me->GetMaxHealth());
            me->AttackStop();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            IntroPhaseTimer = 4000;
            ++IntroPhase;
            break;
        case 18:
            DoScriptText(YELL_INTRO_KILL_MADRIGOSA, me);
            me->SetOrientation(0.14f);
            me->StopMoving();
            Madrigosa->SetDeathState(CORPSE);
            Madrigosa->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
            IntroPhaseTimer = 8000;
            ++IntroPhase;
            break;
        case 19:
            DoScriptText(YELL_INTRO_TAUNT, me);
            IntroPhaseTimer = 5000;
            ++IntroPhase;
            break;
        case 20:
            DoCast(me, 46637);
            IntroPhaseTimer = 2000;
            ++IntroPhase;
            break;
        case 21:
        {
            if (GameObject *IceBarrier = GameObject::GetGameObject(*me, pInstance ? pInstance->GetData64(DATA_GO_ICE_BARRIER) : 0)) {
                IceBarrier->SetLootState(GO_READY);
                IceBarrier->UseDoorOrButton();
            }
            else
                TC_LOG_ERROR("scripts","Sunwell/Brutallus Intro: Ice Barrier not found!");
            
            IntroPhaseTimer = 200;
            ++IntroPhase;
            break;
        }
        case 22:
        {
            if (pInstance)
                pInstance->SetData(DATA_ICEBARRIER_EVENT, DONE);
            
            IntroPhaseTimer = 500;
            ++IntroPhase;
            break;
        }
        case 23:
            EndIntro();
            break;
        }
    }
    
    void DamageTaken(Unit* doneBy, uint32& damage)
    override {
        if ((Intro || IsIntro) && doneBy->ToPlayer())
            damage = 0;
            
        if ((Intro || IsIntro) && damage >= me->GetHealth())
            damage = 0;
    }

    void MoveInLineOfSight(Unit *who) override {
        if (me->CanAttack(who) != CAN_ATTACK_RESULT_OK || !me->IsHostileTo(who))
            return;

        if (pInstance && Intro)
            pInstance->SetData(DATA_BRUTALLUS_EVENT, SPECIAL);
        
        if (!Intro && !IsIntro)
            ScriptedAI::MoveInLineOfSight(who);
    }

    void UpdateAI(const uint32 diff)
    override {
        if (IsIntro)
        {
            if (IntroPhaseTimer <= diff)
                DoIntro();
            else IntroPhaseTimer -= diff;

            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }

        if (!UpdateVictim() || IsIntro)
            return;

        me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);

        if (SlashTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_METEOR_SLASH);
            SlashTimer = 11000;
        } else SlashTimer -= diff;

        if (StompTimer <= diff)
        {
            DoScriptText(RAND(YELL_LOVE1,YELL_LOVE2,YELL_LOVE3), me);
            DoCast(me->GetVictim(), SPELL_STOMP);
            StompTimer = 30000;
            //give some time to heal this
            me->ResetAttackTimer();
            me->ResetAttackTimer(OFF_ATTACK);
        } else StompTimer -= diff;

        if (BurnTimer <= diff)
        {
            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true)) {
                if(!target->HasAuraEffect(SPELL_BURN, 0)) {
                    target->CastSpell(target, SPELL_BURN, true);
                    //BurnTimer = urand(60000,180000);
                    BurnTimer = 20000;
                }
                else
                    BurnTimer = 1000 + diff; // if target has SPELL_BURN, wait a bit.
            }
            else
                BurnTimer = urand(60000,180000); // no targets!?
        } else BurnTimer -= diff;

        if (BerserkTimer < diff && !Enraged)
        {
            DoScriptText(YELL_BERSERK, me);
            DoCast(me, SPELL_BERSERK, true);
            Enraged = true;
            me->SetFullTauntImmunity(true);
        } else BerserkTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_brutallus(Creature *_Creature)
{
    return new boss_brutallusAI (_Creature);
}

class ATBrutallusIntro : AreaTriggerScript
{
public:
    ATBrutallusIntro() : AreaTriggerScript("at_brutallus_intro") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *at) override
    {
        if (pPlayer->IsGameMaster())
            return false;

        if (InstanceScript* pInstance = ((InstanceScript*)pPlayer->GetInstanceScript())) {
            if (pInstance->GetData(DATA_BRUTALLUS_EVENT) == DONE)
                return true;
            if (Creature *Brutallus = ObjectAccessor::GetCreature(*pPlayer, pInstance ? pInstance->GetData64(DATA_BRUTALLUS) : 0))
                ((boss_brutallusAI*)Brutallus->AI())->StartIntro();
        }

        return true;
    }
};

struct trigger_death_cloudAI : public ScriptedAI
{
    trigger_death_cloudAI(Creature* c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }
    
    InstanceScript* pInstance;
    
    uint32 bornTimer;
    
    void Reset() override
    {
        DoCast(me, 45212, true);
        
        me->SetSpeedRate(MOVE_WALK, 2.0f);
        me->SetSpeedRate(MOVE_RUN, 2.0f);

        Creature *Madrigosa = ObjectAccessor::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MADRIGOSA) : 0);
        if (!Madrigosa)
            return;

        float x, y, z;
        Madrigosa->GetPosition(x, y, z);
        me->GetMotionMaster()->MovePoint(0, x, y, z);
        
        bornTimer = 0;
    }
    
    void MovementInform(uint32 type, uint32 id) override
    {
        if (Creature *Madrigosa = ObjectAccessor::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MADRIGOSA) : 0)) {
            me->AddAura(44885, Madrigosa);
            bornTimer = 10000;
        }
    }
    
    void UpdateAI(uint32 const diff) override
    {
        if (!bornTimer)
            return;
            
        if (bornTimer <= diff) {
            if (Creature *Madrigosa = ObjectAccessor::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MADRIGOSA) : 0)) {
                Madrigosa->RemoveAurasDueToSpell(44885);
                Madrigosa->SetVisible(false);
                float x, y, z;
                Madrigosa->GetPosition(x, y, z);
                me->SummonCreature(FELMYST, x, y, z, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
                bornTimer = 0;
                me->DisappearAndDie();
            }
        }
        else
            bornTimer -= diff;
    }
};

CreatureAI* GetAI_trigger_death_cloud(Creature* creature)
{
    return new trigger_death_cloudAI(creature);
}

void AddSC_boss_brutallus()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="boss_brutallus";
    newscript->GetAI = &GetAI_boss_brutallus;
    sScriptMgr->RegisterOLDScript(newscript);
    
    new ATBrutallusIntro();

    newscript = new OLDScript;
    newscript->Name = "trigger_death_cloud";
    newscript->GetAI = &GetAI_trigger_death_cloud;
    sScriptMgr->RegisterOLDScript(newscript);
}
