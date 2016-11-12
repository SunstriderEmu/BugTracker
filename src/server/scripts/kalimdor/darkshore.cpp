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
SDName: Darkshore
SD%Complete: 100
SDComment: Quest support: 731, 2078, 5321
SDCategory: Darkshore
EndScriptData */

/* ContentData
npc_kerlonian
npc_threshwackonator
npc_prospector_remtravel
npc_rabid_thistle_bear
npc_tharnariun_treetender
npc_sentinel_aynasha
EndContentData */


#include "EscortAI.h"
#include "FollowerAI.h"
#include "Pet.h"

/*######
## npc_kerlonian
######*/

enum eKerlonian
{
    SAY_KER_START               = -1000434,

    EMOTE_KER_SLEEP_1           = -1000435,
    EMOTE_KER_SLEEP_2           = -1000436,
    EMOTE_KER_SLEEP_3           = -1000437,

    SAY_KER_SLEEP_1             = -1000438,
    SAY_KER_SLEEP_2             = -1000439,
    SAY_KER_SLEEP_3             = -1000440,
    SAY_KER_SLEEP_4             = -1000441,

    EMOTE_KER_AWAKEN            = -1000445,

    SAY_KER_ALERT_1             = -1000442,
    SAY_KER_ALERT_2             = -1000443,

    SAY_KER_END                 = -1000444,

    SPELL_SLEEP_VISUAL          = 25148,
    SPELL_AWAKEN                = 17536,
    QUEST_SLEEPER_AWAKENED      = 5321,
    NPC_LILADRIS                = 11219,                    //attackers entries unknown
    FACTION_KER_ESCORTEE        = 113
};

//TODO: make concept similar as "ringo" -escort. Find a way to run the scripted attacks, _if_ player are choosing road.
struct npc_kerlonianAI : public FollowerAI
{
    npc_kerlonianAI(Creature* pCreature) : FollowerAI(pCreature) { }

    uint32 m_uiFallAsleepTimer;

    void Reset()
    override {
        m_uiFallAsleepTimer = urand(10000, 45000);
    }

    void MoveInLineOfSight(Unit* pWho)
    override {
        FollowerAI::MoveInLineOfSight(pWho);

        if (!me->GetVictim() && !HasFollowState(STATE_FOLLOW_COMPLETE) && pWho->GetEntry() == NPC_LILADRIS)
        {
            if (me->IsWithinDistInMap(pWho, INTERACTION_DISTANCE*5))
            {
                if (Player* pPlayer = GetLeaderForFollower())
                {
                    if (pPlayer->GetQuestStatus(QUEST_SLEEPER_AWAKENED) == QUEST_STATUS_INCOMPLETE)
                        pPlayer->GroupEventHappens(QUEST_SLEEPER_AWAKENED, me);

                    DoScriptText(SAY_KER_END, me);
                }

                SetFollowComplete();
            }
        }
    }

    void SpellHit(Unit* pCaster, const SpellInfo* pSpell)
    override {
        if (HasFollowState(STATE_FOLLOW_INPROGRESS | STATE_FOLLOW_PAUSED) && pSpell->Id == SPELL_AWAKEN)
            ClearSleeping();
    }

    void SetSleeping()
    {
        SetFollowPaused(true);

        DoScriptText(RAND(EMOTE_KER_SLEEP_1,EMOTE_KER_SLEEP_2,EMOTE_KER_SLEEP_3), me);

        DoScriptText(RAND(SAY_KER_SLEEP_1,SAY_KER_SLEEP_2,SAY_KER_SLEEP_3,SAY_KER_SLEEP_4), me);

        me->SetStandState(UNIT_STAND_STATE_SLEEP);
        me->CastSpell(me, SPELL_SLEEP_VISUAL, false);
    }

    void ClearSleeping()
    {
        me->RemoveAurasDueToSpell(SPELL_SLEEP_VISUAL);
        me->SetStandState(UNIT_STAND_STATE_STAND);

        DoScriptText(EMOTE_KER_AWAKEN, me);

        SetFollowPaused(false);
    }

    void EnterCombat(Unit* pWho) override {}

    void UpdateFollowerAI(const uint32 uiDiff)
    override {
        if (!UpdateVictim())
        {
            if (!HasFollowState(STATE_FOLLOW_INPROGRESS))
                return;

            if (!HasFollowState(STATE_FOLLOW_PAUSED))
            {
                if (m_uiFallAsleepTimer <= uiDiff)
                {
                    SetSleeping();
                    m_uiFallAsleepTimer = urand(25000, 90000);
                }
                else
                    m_uiFallAsleepTimer -= uiDiff;
            }

            return;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_kerlonian(Creature* pCreature)
{
    return new npc_kerlonianAI(pCreature);
}

bool QuestAccept_npc_kerlonian(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_SLEEPER_AWAKENED)
    {
        if (npc_kerlonianAI* pKerlonianAI = CAST_AI(npc_kerlonianAI, pCreature->AI()))
        {
            pCreature->SetStandState(UNIT_STAND_STATE_STAND);
            DoScriptText(SAY_KER_START, pCreature, pPlayer);
            pKerlonianAI->StartFollow(pPlayer, FACTION_KER_ESCORTEE, pQuest);
        }
    }

    return true;
}

/*####
# npc_threshwackonator
####*/

enum eThreshwackonator
{
    EMOTE_START             = -1000413, //signed for 4966
    SAY_AT_CLOSE            = -1000414, //signed for 4966
    QUEST_GYROMAST_REV      = 2078,
    NPC_GELKAK              = 6667,
    FACTION_HOSTILE         = 14
};

#define GOSSIP_ITEM_INSERT_KEY  "[PH] Insert key"

struct npc_threshwackonatorAI : public FollowerAI
{
    npc_threshwackonatorAI(Creature* pCreature) : FollowerAI(pCreature) { }

    void Reset() override { }
    
    void EnterCombat(Unit* pWho) override {}

    void MoveInLineOfSight(Unit* pWho)
    override {
        FollowerAI::MoveInLineOfSight(pWho);

        if (!me->GetVictim() && !HasFollowState(STATE_FOLLOW_COMPLETE) && pWho->GetEntry() == NPC_GELKAK)
        {
            if (me->IsWithinDistInMap(pWho, 10.0f))
            {
                DoScriptText(SAY_AT_CLOSE, pWho);
                DoAtEnd();
            }
        }
    }

    void DoAtEnd()
    {
        me->SetFaction(FACTION_HOSTILE);

        SetFollowComplete(true);

        if (Player* pHolder = GetLeaderForFollower()) {
            me->AI()->AttackStart(pHolder);
            me->GetMotionMaster()->MoveChase(pHolder);
        }
    }
};

CreatureAI* GetAI_npc_threshwackonator(Creature* pCreature)
{
    return new npc_threshwackonatorAI(pCreature);
}

bool GossipHello_npc_threshwackonator(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_GYROMAST_REV) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_INSERT_KEY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
    return true;
}

bool GossipSelect_npc_threshwackonator(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        if (npc_threshwackonatorAI* pThreshAI = CAST_AI(npc_threshwackonatorAI, pCreature->AI()))
        {
            DoScriptText(EMOTE_START, pCreature);
            pThreshAI->StartFollow(pPlayer);
        }
    }

    return true;
}

/*####
# npc_prospector_remtravel
####*/

enum eRemtravel
{
    SAY_REM_START               = -1000327,
    SAY_REM_RAMP1_1             = -1000328,
    SAY_REM_RAMP1_2             = -1000329,
    SAY_REM_BOOK                = -1000330,
    SAY_REM_TENT1_1             = -1000331,
    SAY_REM_TENT1_2             = -1000332,
    SAY_REM_MOSS                = -1000333,
    EMOTE_REM_MOSS              = -1000334,
    SAY_REM_MOSS_PROGRESS       = -1000335,
    SAY_REM_PROGRESS            = -1000336,
    SAY_REM_REMEMBER            = -1000337,
    EMOTE_REM_END               = -1000338,
    SAY_REM_AGGRO               = -1000339,

    FACTION_ESCORTEE            = 10,
    QUEST_ABSENT_MINDED_PT2     = 731,
    NPC_GRAVEL_SCOUT            = 2158,
    NPC_GRAVEL_BONE             = 2159,
    NPC_GRAVEL_GEO              = 2160
};

struct npc_prospector_remtravelAI : public npc_escortAI
{
    npc_prospector_remtravelAI(Creature* pCreature) : npc_escortAI(pCreature) {}

    void WaypointReached(uint32 i)
    override {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

        switch(i)
        {
            case 0:
                DoScriptText(SAY_REM_START, me, pPlayer);
                break;
            case 1:
                DoScriptText(SAY_REM_RAMP1_1, me, pPlayer);
                break;
            case 2:
                DoSpawnCreature(NPC_GRAVEL_SCOUT, -10.0f, 5.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                DoSpawnCreature(NPC_GRAVEL_BONE, -10.0f, 7.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                break;
            case 4:
                DoScriptText(SAY_REM_RAMP1_2, me, pPlayer);
                break;
            case 7:
                DoScriptText(SAY_REM_TENT1_1, me, pPlayer);
                DoSpawnCreature(NPC_GRAVEL_SCOUT, -10.0f, 5.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                DoSpawnCreature(NPC_GRAVEL_BONE, -10.0f, 7.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                break;
            case 8:
                DoScriptText(SAY_REM_TENT1_2, me, pPlayer);
                break;
            case 14:
                DoScriptText(SAY_REM_MOSS_PROGRESS, me, pPlayer);
                break;
            case 15:
                DoSpawnCreature(NPC_GRAVEL_SCOUT, -15.0f, 3.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                DoSpawnCreature(NPC_GRAVEL_BONE, -15.0f, 5.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                DoSpawnCreature(NPC_GRAVEL_GEO, -15.0f, 7.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                break;
            case 18:
                DoScriptText(SAY_REM_BOOK, me, pPlayer);
                break;
            case 24:
                DoScriptText(SAY_REM_REMEMBER, me, pPlayer);
                break;
            case 25:
                DoScriptText(EMOTE_REM_END, me, pPlayer);
                pPlayer->GroupEventHappens(QUEST_ABSENT_MINDED_PT2, me);
                break;
        }
    }

    void Reset() override {}

    void EnterCombat(Unit* who)
    override {
        if (rand()%2)
            DoScriptText(SAY_REM_AGGRO, me, who);
    }
};

CreatureAI* GetAI_npc_prospector_remtravel(Creature* pCreature)
{
    return new npc_prospector_remtravelAI(pCreature);
}

bool QuestAccept_npc_prospector_remtravel(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_ABSENT_MINDED_PT2)
    {
        ((npc_escortAI*)(pCreature->AI()))->Start(true, true, false, pPlayer->GetGUID(), pCreature->GetEntry());
        pCreature->SetFaction(FACTION_ESCORTEE);
    }

    return true;
}

/*######
## npc_rabid_thistle_bear
######*/

struct npc_rabid_thistle_bearAI : public ScriptedAI
{
    npc_rabid_thistle_bearAI(Creature* pCreature) : ScriptedAI(pCreature) {}
    
    uint64 guid;

    void Reset() override {}

    void EnterCombat(Unit* who) override {}
    
    bool sOnDummyEffect(Unit* caster, uint32 spellId, uint32 effIndex)
    override {
        if (spellId == 9439) {
            if (Player* plr = ObjectAccessor::GetPlayer(*me, guid)) {
                me->UpdateEntry(11836);
                me->GetMotionMaster()->MoveFollow(plr, PET_FOLLOW_DIST, me->GetFollowAngle());
                plr->CastedCreatureOrGO(11836, me->GetGUID(), 9437);
                me->CombatStop();
                plr->CombatStop();
            }
        }
        return true;
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!UpdateVictim())
            return;
            
        if (me->GetVictim()->ToPlayer())
            guid = me->GetVictim()->GetGUID();
        
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_rabid_thistle_bear(Creature* pCreature)
{
    return new npc_rabid_thistle_bearAI(pCreature);
}

/*######
## npc_tharnariun_treetender
######*/

struct npc_tharnariun_treetenderAI : public ScriptedAI
{
    npc_tharnariun_treetenderAI(Creature* c) : ScriptedAI(c) {}
    
    void EnterCombat(Unit* who) override {}
    
    void MoveInLineOfSight(Unit* who)
    override {
        if (who->ToCreature() && who->GetEntry() == 11836)
            who->ToCreature()->ForcedDespawn();
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (!UpdateVictim())
            return;
            
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_tharnariun_treetender(Creature* creature)
{
    return new npc_tharnariun_treetenderAI(creature);
}

/*######
## npc_sentinel_aynasha
######*/

enum AynashaData
{
    SPELL_AYNASHAS_BOW      = 19767,
    
    QUEST_ONESHOT_ONEKILL   = 5713,
    
    NPC_BLACKWOOD_TRACKER   = 11713,
    NPC_MAROSH_THE_DEVIOUS  = 11714,
    
    TALK_QUESTACCEPT        = 0,
    TALK_QUESTFINISHED1     = 1,
    TALK_QUESTFINISHED2     = 2,
    TALK_QUESTFINISHED3     = 3
};

struct npc_sentinel_aynashaAI : public ScriptedAI
{
    npc_sentinel_aynashaAI(Creature* c) : ScriptedAI(c)
    {
        timer = 0;
        step = 0;
        said = false;
    }
    
    uint32 timer;
    uint32 step;
    bool said;
    
    void Reset()
    override {
        me->RemoveAurasDueToSpell(18373);
    }
    
    void EnterCombat(Unit* who) override {}
    
    void MovementInform(uint32 type, uint32 id)
    override {
        if (id == 1) {
            me->DisappearAndDie();
            me->Respawn();
            timer = 0;
            step = 0;
            said = false;
        }
    }
    
    void MoveInLineOfSight(Unit* who)
    override {
        if (!who->ToPlayer())
            return;

        if (!said && who->ToPlayer()->GetQuestStatus(QUEST_ONESHOT_ONEKILL) == QUEST_STATUS_COMPLETE && step == 3) {
            said = true;
            timer = 1;
        }
    }
    
    void EnterEvadeMode(EvadeReason why)
    override {
        CreatureAI::EnterEvadeMode(why);
        me->GetMotionMaster()->MoveIdle();
    }
    
    void UpdateAI(uint32 const diff)
    override {
        if (timer) {
            if (timer <= diff) {
                switch (step) {
                case 0: // 2 mobs
                    if (Creature* tracker = me->SummonCreature(NPC_BLACKWOOD_TRACKER, 4387.776855, -36.047455, 82.273827, 3.583573, TEMPSUMMON_DEAD_DESPAWN, 0))
                        tracker->AI()->AttackStart(me);
                    if (Creature* tracker = me->SummonCreature(NPC_BLACKWOOD_TRACKER, 4388.480469, -37.534382, 82.793724, 3.583573, TEMPSUMMON_DEAD_DESPAWN, 0))
                        tracker->AI()->AttackStart(me);
                    timer = 50000;
                    step++;
                    break;
                case 1: // 3 mobs
                    if (Creature* tracker = me->SummonCreature(NPC_BLACKWOOD_TRACKER, 4387.776855, -36.047455, 82.273827, 3.583573, TEMPSUMMON_DEAD_DESPAWN, 0))
                        tracker->AI()->AttackStart(me);
                    if (Creature* tracker = me->SummonCreature(NPC_BLACKWOOD_TRACKER, 4388.480469, -37.534382, 82.793724, 3.583573, TEMPSUMMON_DEAD_DESPAWN, 0))
                        tracker->AI()->AttackStart(me);
                    if (Creature* tracker = me->SummonCreature(NPC_BLACKWOOD_TRACKER, 4389.127441, -38.901089, 83.472984, 3.583573, TEMPSUMMON_DEAD_DESPAWN, 0))
                        tracker->AI()->AttackStart(me);
                    timer = 60000;
                    step++;
                    break;
                case 2: // Boss
                    if (Creature* marosh = me->SummonCreature(NPC_MAROSH_THE_DEVIOUS, 4388.480469, -37.534382, 82.793724, 3.583573, TEMPSUMMON_DEAD_DESPAWN, 0))
                        marosh->AI()->AttackStart(me);
                    timer = 0;
                    step++;
                    break;
                case 3: // Thanks 1
                    Talk(TALK_QUESTFINISHED1);
                    timer = 5000;
                    step++;
                    break;
                case 4: // Thanks 2
                    Talk(TALK_QUESTFINISHED2);
                    timer = 5000;
                    step++;
                    break;
                    
                case 5: // Thanks 3
                    Talk(TALK_QUESTFINISHED3);
                    timer = 5000;
                    step++;
                    break;
                case 6: // I'm leaving, cyaaa!
                    me->RemoveUnitMovementFlag(0x00000100/*MOVEMENTFLAG_WALKING*/);
                    //me->GetMotionMaster()->MovePoint(1, 4363.714844, -5.714110, 66.114090);
                    me->DisappearAndDie();
                    me->Respawn();
                    timer = 0;
                    step = 0;
                    said = false;
                    break;
                default:
                    break;
                }
            }
            else
                timer -= diff;
        }
        
        if (!UpdateVictim())
            return;
            
        if (me->GetVictim()->IsWithinDistInMap(me, 8.0f)) {
            me->GetMotionMaster()->MoveChase(me->GetVictim());
            DoMeleeAttackIfReady();
        }
        else {
            //me->GetMotionMaster()->MoveIdle();
            DoCast(me->GetVictim(), SPELL_AYNASHAS_BOW);
        }
    }
};

CreatureAI* GetAI_npc_sentinel_aynasha(Creature* creature)
{
    return new npc_sentinel_aynashaAI(creature);
}

bool QuestAccept_npc_sentinel_aynasha(Player* player, Creature* creature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_ONESHOT_ONEKILL) {
        ((npc_sentinel_aynashaAI*)creature->AI())->timer = 8000;
        creature->AI()->Talk(TALK_QUESTACCEPT);
    }
    
    return true;
}

/*######
## AddSC
######*/

void AddSC_darkshore()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name = "npc_kerlonian";
    newscript->GetAI = &GetAI_npc_kerlonian;
    newscript->OnQuestAccept = &QuestAccept_npc_kerlonian;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_threshwackonator";
    newscript->GetAI = &GetAI_npc_threshwackonator;
    newscript->OnGossipHello = &GossipHello_npc_threshwackonator;
    newscript->OnGossipSelect = &GossipSelect_npc_threshwackonator;
    newscript->OnGossipSelect = &GossipSelect_npc_threshwackonator;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_prospector_remtravel";
    newscript->GetAI = &GetAI_npc_prospector_remtravel;
    newscript->OnQuestAccept = &QuestAccept_npc_prospector_remtravel;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_rabid_thistle_bear";
    newscript->GetAI = &GetAI_npc_rabid_thistle_bear;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_tharnariun_treetender";
    newscript->GetAI = &GetAI_npc_tharnariun_treetender;
    sScriptMgr->RegisterOLDScript(newscript);
    
    newscript = new OLDScript;
    newscript->Name = "npc_sentinel_aynasha";
    newscript->GetAI = &GetAI_npc_sentinel_aynasha;
    newscript->OnQuestAccept = &QuestAccept_npc_sentinel_aynasha;
    sScriptMgr->RegisterOLDScript(newscript);
}
