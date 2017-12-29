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
SDName: The_Barrens
SD%Complete: 90
SDComment: Quest support: 863, 898, 1719, 2458, 4921, 6981, 4021
SDCategory: Barrens
EndScriptData */

/* ContentData
npc_beaten_corpse
npc_sputtervalve
npc_taskmaster_fizzule
npc_twiggy_flathead
npc_wizzlecrank_shredder
npc_regthar_deathgate
npc_gilthares_firebough
EndContentData */


#include "EscortAI.h"

/*######
## npc_beaten_corpse
######*/

#define GOSSIP_CORPSE "Examine corpse in detail..."

class npc_beaten_corpse : public CreatureScript
{
public:
    npc_beaten_corpse() : CreatureScript("npc_beaten_corpse")
    { }

    class npc_beaten_corpseAI : public ScriptedAI
    {
    public:
        npc_beaten_corpseAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if( pPlayer->GetQuestStatus(4921) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(4921) == QUEST_STATUS_COMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CORPSE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(3557, me->GetGUID());
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {

            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if(action == GOSSIP_ACTION_INFO_DEF +1)
            {
                player->SEND_GOSSIP_MENU_TEXTID(3558, me->GetGUID());
                player->KilledMonsterCredit( 10668, me->GetGUID() );
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_beaten_corpseAI(creature);
    }
};



/*######
# npc_gilthares
######*/

enum eGilthares
{
    SAY_GIL_START               = -1000370,
    SAY_GIL_AT_LAST             = -1000371,
    SAY_GIL_PROCEED             = -1000372,
    SAY_GIL_FREEBOOTERS         = -1000373,
    SAY_GIL_AGGRO_1             = -1000374,
    SAY_GIL_AGGRO_2             = -1000375,
    SAY_GIL_AGGRO_3             = -1000376,
    SAY_GIL_AGGRO_4             = -1000377,
    SAY_GIL_ALMOST              = -1000378,
    SAY_GIL_SWEET               = -1000379,
    SAY_GIL_FREED               = -1000380,

    QUEST_FREE_FROM_HOLD        = 898,
    AREA_MERCHANT_COAST         = 391,
    FACTION_ESCORTEE            = 232                       //guessed, possible not needed for this quest
};


class npc_gilthares : public CreatureScript
{
public:
    npc_gilthares() : CreatureScript("npc_gilthares")
    { }

    class npc_giltharesAI : public EscortAI
    {
        public:
        npc_giltharesAI(Creature* pCreature) : EscortAI(pCreature) { }
    
        void Reset() override { }
    
        void WaypointReached(uint32 uiPointId, uint32 pathID)
        override {
            Player* pPlayer = GetPlayerForEscort();
    
            if (!pPlayer)
                return;
    
            switch(uiPointId)
            {
                case 16:
                    DoScriptText(SAY_GIL_AT_LAST, me, pPlayer);
                    break;
                case 17:
                    DoScriptText(SAY_GIL_PROCEED, me, pPlayer);
                    break;
                case 18:
                    DoScriptText(SAY_GIL_FREEBOOTERS, me, pPlayer);
                    break;
                case 37:
                    DoScriptText(SAY_GIL_ALMOST, me, pPlayer);
                    break;
                case 47:
                    DoScriptText(SAY_GIL_SWEET, me, pPlayer);
                    break;
                case 53:
                    DoScriptText(SAY_GIL_FREED, me, pPlayer);
                    pPlayer->GroupEventHappens(QUEST_FREE_FROM_HOLD, me);
                    break;
            }
        }
    
        void EnterCombat(Unit* pWho)
        override {
            //not always use
            if (rand()%4)
                return;
    
            //only aggro text if not player and only in this area
            if (pWho->GetTypeId() != TYPEID_PLAYER && me->GetAreaId() == AREA_MERCHANT_COAST)
            {
                //appears to be pretty much random (possible only if escorter not in combat with pWho yet?)
                DoScriptText(RAND(SAY_GIL_AGGRO_1, SAY_GIL_AGGRO_2, SAY_GIL_AGGRO_3, SAY_GIL_AGGRO_4), me, pWho);
            }
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_FREE_FROM_HOLD)
            {
                me->SetFaction(FACTION_ESCORTEE);
                me->SetStandState(PLAYER_STATE_NONE);

                DoScriptText(SAY_GIL_START, me, pPlayer);

                /*if (npc_giltharesAI* pEscortAI = CAST_AI(npc_gilthares::npc_giltharesAI, me->AI()))
                    pEscortAI->Start(false, false, pPlayer->GetGUID(), pQuest);*/
                ((EscortAI*)(me->AI()))->Start(true, false, pPlayer->GetGUID(), quest);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_giltharesAI(creature);
    }
};



/*######
## npc_sputtervalve
######*/

#define GOSSIP_SPUTTERVALVE "Can you tell me about this shard?"

class npc_sputtervalve : public CreatureScript
{
public:
    npc_sputtervalve() : CreatureScript("npc_sputtervalve")
    { }

    class npc_sputtervalveAI : public ScriptedAI
    {
    public:
        npc_sputtervalveAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if( pPlayer->GetQuestStatus(6981) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SPUTTERVALVE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            if(action == GOSSIP_ACTION_INFO_DEF)
            {
                player->SEND_GOSSIP_MENU_TEXTID(2013, me->GetGUID());
                player->AreaExploredOrEventHappens(6981);
            }
            return true;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sputtervalveAI(creature);
    }
};



/*######
## npc_taskmaster_fizzule
######*/

enum eTaskmasterFizzule
{
FACTION_HOSTILE_F       = 16,
FACTION_FRIENDLY_F      = 35,

SPELL_FLARE             = 10113,
SPELL_FOLLY             = 10137
};


class npc_taskmaster_fizzule : public CreatureScript
{
public:
    npc_taskmaster_fizzule() : CreatureScript("npc_taskmaster_fizzule")
    { }

    class npc_taskmaster_fizzuleAI : public ScriptedAI
    {
        public:
        npc_taskmaster_fizzuleAI(Creature* c) : ScriptedAI(c) {}
    
        bool IsFriend;
        uint32 Reset_Timer;
        uint32 FlareCount;
    
        void Reset()
        override {
            IsFriend = false;
            Reset_Timer = 120000;
            FlareCount = 0;
            me->SetFaction(FACTION_HOSTILE_F);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        }
    
        //This is a hack. Spellcast will make creature aggro but that is not
        //supposed to happen (Trinity not implemented/not found way to detect this spell kind)
        void DoUglyHack()
        {
            me->RemoveAllAuras();
            me->GetThreatManager().ClearAllThreat();
            me->CombatStop();
        }
    
        void SpellHit(Unit* caster, const SpellInfo* spell)
        override {
            if( spell->Id == SPELL_FLARE || spell->Id == SPELL_FOLLY )
            {
                DoUglyHack();
                ++FlareCount;
                if( FlareCount >= 2 )
                {
                    me->SetFaction(FACTION_FRIENDLY_F);
                    IsFriend = true;
                }
            }
        }
    
        void EnterCombat(Unit* pWho) override { }
    
        void UpdateAI(const uint32 diff)
        override {
            if( IsFriend )
            {
                if( Reset_Timer < diff )
                {
                    EnterEvadeMode();
                    return;
                } else Reset_Timer -= diff;
            }
    
            if (!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
        }

        virtual void ReceiveEmote(Player* pPlayer, uint32 emote) override
        {
            if( emote == TEXTEMOTE_SALUTE )
            {
                if ((CAST_AI(npc_taskmaster_fizzule::npc_taskmaster_fizzuleAI, (me->AI())))->FlareCount >= 2 )
                {
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_taskmaster_fizzuleAI(creature);
    }
};


/*#####
## npc_twiggy_flathead
#####*/

enum eTwiggyFlathead
{
    NPC_BIG_WILL                = 6238,
    NPC_AFFRAY_CHALLENGER       = 6240,

    SAY_BIG_WILL_READY          = -1000123,
    SAY_TWIGGY_FLATHEAD_BEGIN   = -1000124,
    SAY_TWIGGY_FLATHEAD_FRAY    = -1000125,
    SAY_TWIGGY_FLATHEAD_DOWN    = -1000126,
    SAY_TWIGGY_FLATHEAD_OVER    = -1000127,
};

float AffrayChallengerLoc[6][4]=
{
    {-1683.0f, -4326.0f, 2.79f, 0.0f},
    {-1682.0f, -4329.0f, 2.79f, 0.0f},
    {-1683.0f, -4330.0f, 2.79f, 0.0f},
    {-1680.0f, -4334.0f, 2.79f, 1.49f},
    {-1674.0f, -4326.0f, 2.79f, 3.49f},
    {-1677.0f, -4334.0f, 2.79f, 1.66f}
};


class npc_twiggy_flathead : public CreatureScript
{
public:
    npc_twiggy_flathead() : CreatureScript("npc_twiggy_flathead")
    { }

    class npc_twiggy_flatheadAI : public ScriptedAI
    {
        public:
        npc_twiggy_flatheadAI(Creature *c) : ScriptedAI(c) {}
    
        bool EventInProgress;
        bool EventGrate;
        bool EventBigWill;
        bool Challenger_down[6];
        uint32 Wave;
        uint32 Wave_Timer;
        uint32 Challenger_checker;
        uint64 PlayerGUID;
        uint64 AffrayChallenger[6];
        uint64 BigWill;
    
        void Reset()
        override {
            EventInProgress = false;
            EventGrate = false;
            EventBigWill = false;
            Wave_Timer = 600000;
            Challenger_checker = 0;
            Wave = 0;
            PlayerGUID = 0;
    
            for(uint8 i = 0; i < 6; ++i)
            {
                AffrayChallenger[i] = 0;
                Challenger_down[i] = false;
            }
            BigWill = 0;
        }
    
        void EnterCombat(Unit* pWho) override { }
    
        void MoveInLineOfSight(Unit* pWho)
        override {
            if(!pWho || (!pWho->IsAlive())) return;
    
            if (me->IsWithinDistInMap(pWho, 10.0f) && (pWho->GetTypeId() == TYPEID_PLAYER) && (pWho)->ToPlayer()->GetQuestStatus(1719) == QUEST_STATUS_INCOMPLETE && !EventInProgress)
            {
                PlayerGUID = pWho->GetGUID();
                EventInProgress = true;
            }
        }
    
        void KilledUnit(Unit* pVictim) override { }
    
        void UpdateAI(const uint32 diff)
        override {
            if (EventInProgress) {
                Player* pWarrior = nullptr;
    
                if (PlayerGUID)
                    pWarrior = ObjectAccessor::GetPlayer(*me, PlayerGUID);
    
                if(!pWarrior)
                    return;
    
                if(!pWarrior->IsAlive() && pWarrior->GetQuestStatus(1719) == QUEST_STATUS_INCOMPLETE) {
                    EventInProgress = false;
                    DoScriptText(SAY_TWIGGY_FLATHEAD_DOWN, me);
                    pWarrior->FailQuest(1719);
    
                    for(uint8 i = 0; i < 6; ++i)
                    {
                        if (AffrayChallenger[i])
                        {
                            Creature* pCreature = ObjectAccessor::GetCreature((*me), AffrayChallenger[i]);
                            if(pCreature) {
                                if(pCreature->IsAlive())
                                {
                                    pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
                                    pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                    pCreature->SetDeathState(JUST_DIED);
                                }
                            }
                        }
                        AffrayChallenger[i] = 0;
                        Challenger_down[i] = false;
                    }
    
                    if (BigWill)
                    {
                        Creature* pCreature = ObjectAccessor::GetCreature((*me), BigWill);
                        if(pCreature) {
                            if(pCreature->IsAlive()) {
                                pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
                                pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                pCreature->SetDeathState(JUST_DIED);
                            }
                        }
                    }
                    BigWill = 0;
                }
    
                if (!EventGrate && EventInProgress)
                {
                    float x,y,z;
                    pWarrior->GetPosition(x, y, z);
    
                    if (x >= -1684 && x <= -1674 && y >= -4334 && y <= -4324) {
                        pWarrior->AreaExploredOrEventHappens(1719);
                        DoScriptText(SAY_TWIGGY_FLATHEAD_BEGIN, me, pWarrior);
    
                        for(uint8 i = 0; i < 6; ++i)
                        {
                            Creature* pCreature = me->SummonCreature(NPC_AFFRAY_CHALLENGER, AffrayChallengerLoc[i][0], AffrayChallengerLoc[i][1], AffrayChallengerLoc[i][2], AffrayChallengerLoc[i][3], TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000);
                            if(!pCreature)
                                continue;
                            pCreature->SetFaction(FACTION_FRIENDLY);
                            pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            pCreature->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                            AffrayChallenger[i] = pCreature->GetGUID();
                        }
                        Wave_Timer = 5000;
                        Challenger_checker = 1000;
                        EventGrate = true;
                    }
                }
                else if (EventInProgress)
                {
                    if (Challenger_checker < diff)
                    {
                        for(uint8 i = 0; i < 6; ++i)
                        {
                            if (AffrayChallenger[i])
                            {
                                Creature* pCreature = ObjectAccessor::GetCreature((*me), AffrayChallenger[i]);
                                if((!pCreature || (!pCreature->IsAlive())) && !Challenger_down[i])
                                {
                                    DoScriptText(SAY_TWIGGY_FLATHEAD_DOWN, me);
                                    Challenger_down[i] = true;
                                }
                            }
                        }
                        Challenger_checker = 1000;
                    } else Challenger_checker -= diff;
    
                    if(Wave_Timer < diff)
                    {
                        if (AffrayChallenger[Wave] && Wave < 6 && !EventBigWill)
                        {
                            DoScriptText(SAY_TWIGGY_FLATHEAD_FRAY, me);
                            Creature* pCreature = ObjectAccessor::GetCreature((*me), AffrayChallenger[Wave]);
                            if(pCreature && (pCreature->IsAlive()))
                            {
                                pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pCreature->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                                pCreature->SetFaction(FACTION_MONSTER);
                                ((CreatureAI*)pCreature->AI())->AttackStart(pWarrior);
                                ++Wave;
                                Wave_Timer = 20000;
                            }
                        }
                        else if (Wave >= 6 && !EventBigWill) {
                            if(Creature* pCreature = me->SummonCreature(NPC_BIG_WILL, -1722, -4341, 6.12, 6.26, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 480000))
                            {
                                BigWill = pCreature->GetGUID();
                                //pCreature->GetMotionMaster()->MovePoint(0, -1693, -4343, 4.32);
                                //pCreature->GetMotionMaster()->MovePoint(1, -1684, -4333, 2.78);
                                pCreature->GetMotionMaster()->MovePoint(2, -1682, -4329, 2.79);
                                //pCreature->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                                pCreature->HandleEmoteCommand(EMOTE_STATE_READYUNARMED);
                                EventBigWill = true;
                                Wave_Timer = 1000;
                            }
                        }
                        else if (Wave >= 6 && EventBigWill && BigWill)
                        {
                            Creature* pCreature = ObjectAccessor::GetCreature((*me), BigWill);
                            if (!pCreature || !pCreature->IsAlive())
                            {
                                DoScriptText(SAY_TWIGGY_FLATHEAD_OVER, me);
                                EventInProgress = false;
                                EventBigWill = false;
                                EventGrate = false;
                                PlayerGUID = 0;
                                Wave = 0;
                            }
                        }
                    } else Wave_Timer -= diff;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_twiggy_flatheadAI(creature);
    }
};


/*#####
## npc_wizzlecrank_shredder
#####*/

enum eEnums_Wizzlecrank
{
    SAY_START           = -1000272,
    SAY_STARTUP1        = -1000273,
    SAY_STARTUP2        = -1000274,
    SAY_MERCENARY       = -1000275,
    SAY_PROGRESS_1      = -1000276,
    SAY_PROGRESS_2      = -1000277,
    SAY_PROGRESS_3      = -1000278,
    SAY_END             = -1000279,

    QUEST_ESCAPE        = 863,
    FACTION_RATCHET     = 637,
    NPC_PILOT_WIZZ      = 3451,
    NPC_MERCENARY       = 3282,
};


class npc_wizzlecrank_shredder : public CreatureScript
{
public:
    npc_wizzlecrank_shredder() : CreatureScript("npc_wizzlecrank_shredder")
    { }

    class npc_wizzlecrank_shredderAI : public EscortAI
    {
        public:
        npc_wizzlecrank_shredderAI(Creature* pCreature) : EscortAI(pCreature)
        {
            m_bIsPostEvent = false;
            m_uiPostEventTimer = 1000;
            m_uiPostEventCount = 0;
        }
    
        bool m_bIsPostEvent;
        uint32 m_uiPostEventTimer;
        uint32 m_uiPostEventCount;
    
        void Reset()
        override {
            if (HasEscortState(STATE_ESCORT_ESCORTING))
            {
                if (me->GetStandState() == UNIT_STAND_STATE_DEAD)
                     me->SetStandState(UNIT_STAND_STATE_STAND);
    
                m_bIsPostEvent = false;
                m_uiPostEventTimer = 1000;
                m_uiPostEventCount = 0;
            }
        }
        
        void EnterCombat(Unit* pWho) override {}
    
        void WaypointReached(uint32 uiPointId, uint32 pathID)
        override {
            Player* pPlayer = GetPlayerForEscort();
            if (!pPlayer)
                return;
    
            switch(uiPointId)
            {
            case 0:
                DoScriptText(SAY_STARTUP1, me);
                break;
            case 9:
                SetRun(false);
                break;
            case 17:
                if (Creature* pTemp = me->SummonCreature(NPC_MERCENARY, 1128.489f, -3037.611f, 92.701f, 1.472f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000))
                {
                    DoScriptText(SAY_MERCENARY, pTemp);
                    me->SummonCreature(NPC_MERCENARY, 1160.172f, -2980.168f, 97.313f, 3.690f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                }
                break;
            case 24:
                m_bIsPostEvent = true;
                pPlayer->GroupEventHappens(QUEST_ESCAPE, me);
                break;
            }
        }
    
        void WaypointStart(uint32 uiPointId)
        {
            Player* pPlayer = GetPlayerForEscort();
    
            if (!pPlayer)
                return;
    
            switch(uiPointId)
            {
                case 9:
                    DoScriptText(SAY_STARTUP2, me, pPlayer);
                    break;
                case 18:
                    DoScriptText(SAY_PROGRESS_1, me, pPlayer);
                    SetRun();
                    break;
            }
        }
    
        void JustSummoned(Creature* pSummoned)
        override {
            if (pSummoned->GetEntry() == NPC_PILOT_WIZZ)
                me->SetStandState(UNIT_STAND_STATE_DEAD);
    
            if (pSummoned->GetEntry() == NPC_MERCENARY)
                pSummoned->AI()->AttackStart(me);
        }
    
        void UpdateEscortAI(uint32 uiDiff) override
        {
            if (!UpdateVictim())
            {
                if (m_bIsPostEvent)
                {
                    if (m_uiPostEventTimer <= uiDiff)
                    {
                        switch(m_uiPostEventCount)
                        {
                            case 0:
                                DoScriptText(SAY_PROGRESS_2, me);
                                break;
                            case 1:
                                DoScriptText(SAY_PROGRESS_3, me);
                                break;
                            case 2:
                                DoScriptText(SAY_END, me);
                                break;
                            case 3:
                                if (Player* pPlayer = GetPlayerForEscort())
                                {
                                    pPlayer->GroupEventHappens(QUEST_ESCAPE, me);
                                    me->SummonCreature(NPC_PILOT_WIZZ, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 180000);
                                }
                                break;
                        }
    
                        ++m_uiPostEventCount;
                        m_uiPostEventTimer = 5000;
                    }
                    else
                        m_uiPostEventTimer -= uiDiff;
                }
    
                return;
            }
    
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_ESCAPE)
            {
                if (EscortAI* pEscortAI = CAST_AI(npc_wizzlecrank_shredderAI, (me->AI())))
                    pEscortAI->Start(true, false, pPlayer->GetGUID(), quest);
                    
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wizzlecrank_shredderAI(creature);
    }
};



/*######
## npc_regthar_deathgate
######*/

enum RegtharDeathgateData {
    QUEST_COUNTERATTACK     = 4021,
    
    NPC_HORDE_DEFENDER      = 9457,
    NPC_HORDE_AXE_THROWER   = 9458,
    NPC_KOLKAR_INVADER      = 9524,
    NPC_KOLKAR_STORMSEER    = 9523,
    NPC_LANTI_GAH           = 9990,
    NPC_WARLOCK_KROMZAR     = 9456,
    
    YELL_COUNTERATTACK_LANTIGAH     = -1000800,
    SAY_COUNTERATTACK_DEFENDER      = -1000801,
    SAY_COUNTERATTACK_BEWARE        = -1000802,
    YELL_COUNTERATTACK_KROMZAR      = -1000803
};

float attackersPos[][4] = { { -301.483246f, -1864.453125f, 92.982010f, 5.107399f },
                            { -296.849884f, -1864.198120f, 92.681602f, 4.956865f },
                            { -292.218994f, -1863.122681f, 92.529182f, 4.685903f },
                            { -288.826233f, -1863.246704f, 92.524986f, 4.675867f },
                            { -284.970764f, -1858.442993f, 92.458336f, 4.645762f },
                            { -280.549591f, -1858.738037f, 92.583649f, 4.645762f },
                            { -286.257660f, -1865.968018f, 92.625084f, 4.645762f },
                            { -272.915497f, -1846.779907f, 93.371109f, 4.164052f },
                            { -282.390839f, -1843.288086f, 92.586586f, 4.489207f },
                            { -290.774078f, -1842.121582f, 92.882210f, 4.736608f },
                            { -300.243317f, -1842.350952f, 93.933723f, 4.736608f },
                            { -307.937622f, -1843.978638f, 94.907982f, 5.060192f },
                            { -316.356171f, -1848.410156f, 95.201050f, 5.319373f },
                            { -229.504166f, -1917.720459f, 92.358574f, 2.399001f },
                            { -234.851791f, -1921.778442f, 92.701218f, 2.219930f },
                            { -238.310852f, -1927.177368f, 92.959702f, 2.571789f },
                            { -241.936066f, -1932.835693f, 92.934319f, 2.571789f },
                            { -251.544861f, -1933.647949f, 91.972511f, 2.571789f },
                            { -252.290527f, -1927.605347f, 91.928032f, 2.571789f },
                            { -246.580887f, -1923.654297f, 92.278069f, 2.571789f },
                            { -243.556091f, -1918.933105f, 92.251320f, 2.571789f },
                            { -243.148834f, -1912.324341f, 91.964806f, 2.571789f },
                            { -251.019424f, -1911.610718f, 91.883850f, 2.571789f },
                            { -255.817886f, -1916.005737f, 91.875778f, 2.571789f },
                            { -260.920074f, -1921.308594f, 91.817719f, 2.571789f },
                            { -265.865906f, -1925.523193f, 91.897148f, 2.571789f }};

    
float defendersPos[][4] = {     { -292.977020f, -1892.080566f, 91.995491f, 1.584019f },
                                { -287.853455f, -1892.012817f, 92.257652f, 1.584019f },
                                { -280.889069f, -1891.920776f, 92.060722f, 1.584019f },
                                { -276.943176f, -1876.993286f, 92.618614f, 1.584019f },
                                { -287.600189f, -1872.038208f, 92.740288f, 1.584019f },
                                { -247.661148f, -1911.826416f, 91.863655f, 6.151107f },
                                { -241.494400f, -1915.744019f, 92.160278f, 6.151107f },
                                { -236.513535f, -1912.012329f, 92.013985f, 6.151107f },
                                { -235.899582f, -1907.390991f, 91.823219f, 6.151107f },
                                { -236.531174f, -1917.745117f, 92.372627f, 6.151107f },
                                { -273.915649f, -1925.971069f, 92.491234f, 1.333126f },
                                { -276.039703f, -1922.492432f, 92.560356f, 1.333126f },
                                { -272.844818f, -1917.105469f, 92.344337f, 1.333126f }};


class npc_regthar_deathgate : public CreatureScript
{
public:
    npc_regthar_deathgate() : CreatureScript("npc_regthar_deathgate")
    { }

    class npc_regthar_deathgateAI : public ScriptedAI
    {
        public:
        npc_regthar_deathgateAI(Creature* c) : ScriptedAI(c), summons(me) {}
        
        bool eventRunning;
        bool lantigahYelled;
        bool kromzar;
        
        uint8 maxDefenders;
        uint8 maxAttackers;
        uint8 defendersCount;
        uint8 attackersCount;
        uint8 killsNeeded;
        uint8 killsCounter;
        
        uint32 despawnAllTimer;
        uint32 defendersTimer;
        uint32 attackersTimer;
        
        uint64 starterGUID;
        
        SummonList summons;
        
        void Reset()
        override {
            maxDefenders = 15;
            maxAttackers = 20;
            despawnAllTimer = 0;
            starterGUID = 0;
            eventRunning = false;
            lantigahYelled = false;
            killsNeeded = 0;
            killsCounter = 0;
            kromzar = false;
        }
        
        void EnterCombat(Unit* who) override {}
        
        void JustSummoned(Creature* summoned)
        override {
            summons.Summon(summoned);
            
            switch (summoned->GetEntry()) {
                case NPC_KOLKAR_INVADER:
                case NPC_KOLKAR_STORMSEER:
                    attackersCount++;
                    break;
                case NPC_HORDE_DEFENDER:
                case NPC_HORDE_AXE_THROWER:
                    defendersCount++;
                    break;
                case NPC_WARLOCK_KROMZAR:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, starterGUID))
                        player->CastSpell(player, 13965, TRIGGERED_FULL_MASK);
                    break;
                }
            }
        }
        
        void SummonedCreatureDespawn(Creature* summon)
        override {
            summons.Despawn(summon);
            
            switch (summon->GetEntry()) {
                case NPC_KOLKAR_INVADER:
                case NPC_KOLKAR_STORMSEER:
                    attackersCount--;
                    killsCounter++;
                    break;
                case NPC_HORDE_DEFENDER:
                case NPC_HORDE_AXE_THROWER:
                    defendersCount--;
                    killsCounter++;
                    if (rand()%10 > 3)
                        DoScriptText(SAY_COUNTERATTACK_DEFENDER, me, nullptr);
                    break;
                case NPC_WARLOCK_KROMZAR:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, starterGUID))
                        player->CastSpell(player, 13965, TRIGGERED_FULL_MASK);
    
                    EndEvent();
                    break;
                }
            }
        }
        
        void StartEvent(uint64 playerGUID)
        {
            if (eventRunning)
                return;
                
            if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                DoScriptText(SAY_COUNTERATTACK_BEWARE, me, player);
                
            despawnAllTimer = 0;
            starterGUID = playerGUID;
                
            eventRunning = true;
            lantigahYelled = false;
            killsNeeded = 18 + rand()%6;
            killsCounter = 0;
            kromzar = false;
            defendersTimer = 10000;
            attackersTimer = 8000;
            
            for (uint8 i = 0; i < 8; i++)
                me->SummonCreature(RAND(NPC_HORDE_DEFENDER, NPC_HORDE_AXE_THROWER), defendersPos[rand()%13][0], defendersPos[rand()%13][1], defendersPos[rand()%13][2], defendersPos[rand()%13][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
                
            for (uint8 i = 0; i < 6; i++)
                me->SummonCreature(RAND(NPC_KOLKAR_INVADER, NPC_KOLKAR_STORMSEER), attackersPos[rand()%25][0], attackersPos[rand()%25][1], attackersPos[rand()%25][2], attackersPos[rand()%25][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
                
            for (uint8 i = 13; i < 17; i++)
                me->SummonCreature(RAND(NPC_KOLKAR_INVADER, NPC_KOLKAR_STORMSEER), attackersPos[rand()%25][0], attackersPos[rand()%25][1], attackersPos[rand()%25][2], attackersPos[rand()%25][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
        }
        
        void EndEvent()
        {
            despawnAllTimer = 15000;
            eventRunning = false;
            killsNeeded = 0;
            killsCounter = 0;
            kromzar = false;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (despawnAllTimer) {
                if (despawnAllTimer <= diff) {
                    summons.DespawnAll();
                    despawnAllTimer = 0;
                }
                else
                    despawnAllTimer -= diff;
            }
            
            if (!eventRunning)
                return;
    
                
            Player* player = ObjectAccessor::GetPlayer(*me, starterGUID);
            if (!player || player->IsDead()) {
                EndEvent();
                return;
            }
                
            if (defendersTimer <= diff) {
                if (defendersCount < maxDefenders)
                    me->SummonCreature(RAND(NPC_HORDE_DEFENDER, NPC_HORDE_AXE_THROWER), defendersPos[rand()%13][0], defendersPos[rand()%13][1], defendersPos[rand()%13][2], defendersPos[rand()%13][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
                
                defendersTimer = 10000 + rand()%2000;
            }
            else
                defendersTimer -= diff;
                
            if (attackersTimer <= diff) {
                if (attackersCount < maxAttackers)
                    me->SummonCreature(RAND(NPC_KOLKAR_INVADER, NPC_KOLKAR_STORMSEER), attackersPos[rand()%25][0], attackersPos[rand()%25][1], attackersPos[rand()%25][2], attackersPos[rand()%25][3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
    
                attackersTimer = 8000 + rand()%2000;
            }
            else
                attackersTimer -= diff;
                
            if (killsCounter >= killsNeeded/2 && !lantigahYelled) {
                if (Creature* lantigah = me->FindNearestCreature(NPC_LANTI_GAH, 100.0f, true)) {
                    lantigahYelled = true;
                    DoScriptText(YELL_COUNTERATTACK_LANTIGAH, lantigah, nullptr);
                }
            }
            
            if (killsCounter >= killsNeeded && !kromzar) {
                if (Creature* warlordKromzar = me->SummonCreature(NPC_WARLOCK_KROMZAR, -307.937622, -1843.978638, 94.907982, 5.060192, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 8000)) {
                    kromzar = true;
                    DoScriptText(YELL_COUNTERATTACK_KROMZAR, warlordKromzar, nullptr);
                }
            }
        }

        virtual bool GossipHello(Player* player) override
        {
            //todo translate
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            if (player->GetQuestStatus(QUEST_COUNTERATTACK) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Où est le Seigneur de guerre Krom'zar ?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                
            SEND_PREPARED_GOSSIP_MENU(player, me);
            
            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF)
            {
                ((npc_regthar_deathgate::npc_regthar_deathgateAI*)me->AI())->StartEvent(player->GetGUID());
                player->CLOSE_GOSSIP_MENU();
            }
                
            return true;
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_COUNTERATTACK)
                ((npc_regthar_deathgate::npc_regthar_deathgateAI*)me->AI())->StartEvent(player->GetGUID());
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_regthar_deathgateAI(creature);
    }
};





/*######
## npc_gilthares_firebough
######*/

enum GiltharesFireboughData
{
    TALK_GILTHARES_START        = 0,
    TALK_GILTHARES_THANKS       = 1,

    QUEST_FREE_FROM_THE_HOLD    = 898,
    FACTION_ESCORT              = 232
};


class npc_gilthares_firebough : public CreatureScript
{
public:
    npc_gilthares_firebough() : CreatureScript("npc_gilthares_firebough")
    { }

    class npc_gilthares_fireboughAI : public EscortAI
    {
        public:
        npc_gilthares_fireboughAI(Creature* c) : EscortAI(c) {}
        
        bool completed;
        
        void EnterCombat(Unit* who) override {}
        
        void Reset()
        override {
            completed = false;
        }
        
        void JustDied(Unit* killer)
        override {
            if (!completed) {
                if (Player* player = GetPlayerForEscort())
                    player->FailQuest(QUEST_FREE_FROM_THE_HOLD);
            }
        }
        
        void WaypointReached(uint32 id, uint32 pathID)
        override {
            switch (id) {
            case 0:
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                Talk(TALK_GILTHARES_START);
                break;
            case 10:
                Talk(TALK_GILTHARES_THANKS);
                if (Player* player = GetPlayerForEscort())
                    player->GroupEventHappens(QUEST_FREE_FROM_THE_HOLD, me);
                SetRun(true);
                break;
            case 11:
                completed = true;
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->DespawnOrUnsummon(1);
                break;
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            EscortAI::UpdateAI(diff);
            
            if (!UpdateVictim())
                return;
                
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_FREE_FROM_THE_HOLD) {
                if (EscortAI* escortAI = CAST_AI(npc_gilthares_fireboughAI, (me->AI())))
                    escortAI->Start(true, false, player->GetGUID(), quest);
                    
                me->SetFaction(FACTION_ESCORT);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gilthares_fireboughAI(creature);
    }
};



void AddSC_the_barrens()
{

    new npc_beaten_corpse();
    
    new npc_gilthares();

    new npc_sputtervalve();

    new npc_taskmaster_fizzule();

    new npc_twiggy_flathead();

    new npc_wizzlecrank_shredder();
    
    new npc_regthar_deathgate();
    
    new npc_gilthares_firebough();
}

