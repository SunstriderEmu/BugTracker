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
SDName: Winterspring
SD%Complete: 90
SDComment: Quest support: 5126 (Loraxs' tale missing proper gossip items text), 4901. Vendor Rivern Frostwind. Obtain Cache of Mau'ari
SDCategory: Winterspring
EndScriptData */

/* ContentData
npc_lorax
npc_rivern_frostwind
npc_witch_doctor_mauari
npc_zap_farflinger
npc_ranshalla
EndContentData */


#include "EscortAI.h"

/*######
## npc_lorax
######*/

#define GOSSIP_HL "Parlez-moi"

#define GOSSIP_SL1 "Que faites-vous ici ?"
#define GOSSIP_SL2 "Je peux vous aider"
#define GOSSIP_SL3 "Quel marché ?"
#define GOSSIP_SL4 "Et ensuite, qu'est-il arrivé ?"
#define GOSSIP_SL5 "Il n'est pas en sécurité, je vais m'en assurer."

class npc_lorax : public CreatureScript
{
public:
    npc_lorax() : CreatureScript("npc_lorax")
    { }

    class npc_loraxAI : public ScriptedAI
    {
    public:
        npc_loraxAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if (player->GetQuestStatus(5126) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_HL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SL1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU_TEXTID(3759, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SL2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU_TEXTID(3760, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SL3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU_TEXTID(3761, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SL4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->SEND_GOSSIP_MENU_TEXTID(3762, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+4:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_SL5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                    player->SEND_GOSSIP_MENU_TEXTID(3763, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF+5:
                    player->CLOSE_GOSSIP_MENU();
                    player->AreaExploredOrEventHappens(5126);
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_loraxAI(creature);
    }
};



/*######
## npc_rivern_frostwind
######*/

class npc_rivern_frostwind : public CreatureScript
{
public:
    npc_rivern_frostwind() : CreatureScript("npc_rivern_frostwind")
    { }

    class npc_rivern_frostwindAI : public ScriptedAI
    {
    public:
        npc_rivern_frostwindAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if (me->IsVendor() && player->GetReputationRank(589) == REP_EXALTED)
                player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_TRADE)
                player->SEND_VENDORLIST( me->GetGUID() );

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_rivern_frostwindAI(creature);
    }
};



/*######
## npc_witch_doctor_mauari
######*/

#define GOSSIP_HWDM "J'aimerais que vous me fassiez une nouvelle Cache de Mau'ari, s'il vous plait."

class npc_witch_doctor_mauari : public CreatureScript
{
public:
    npc_witch_doctor_mauari() : CreatureScript("npc_witch_doctor_mauari")
    { }

    class npc_witch_doctor_mauariAI : public ScriptedAI
    {
    public:
        npc_witch_doctor_mauariAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if(me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if(player->GetQuestRewardStatus(975))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HWDM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU_TEXTID(3377, me->GetGUID());
            }else
                player->SEND_GOSSIP_MENU_TEXTID(3375, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action==GOSSIP_ACTION_INFO_DEF+1)
            {
                player->CLOSE_GOSSIP_MENU();
                me->CastSpell(player, 16351, TRIGGERED_NONE);
            }

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_witch_doctor_mauariAI(creature);
    }
};



/*######
## npc_zap_farflinger
######*/

#define GOSSIP_ZAP                  "[PH] J'aimerais recevoir le déchiqueteur dimensionnel."
#define SPELL_GOBLIN_ENGINEER       20222
#define SPELL_DIMENS_RIPPER         23486

class npc_zap_farflinger : public CreatureScript
{
public:
    npc_zap_farflinger() : CreatureScript("npc_zap_farflinger")
    { }

    class npc_zap_farflingerAI : public ScriptedAI
    {
    public:
        npc_zap_farflingerAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->HasSkill(SKILL_ENGINEERING) && (pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 260) && pPlayer->HasSpell(SPELL_GOBLIN_ENGINEER) && !pPlayer->HasSpell(SPELL_DIMENS_RIPPER)) {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ZAP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(3377, me->GetGUID());
                
                return true;
            }
            
            return false;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1) {
                player->LearnSpell(SPELL_DIMENS_RIPPER, false);
                
                player->CLOSE_GOSSIP_MENU();
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_zap_farflingerAI(creature);
    }
};



/*######
## npc_ranshalla
######*/

enum eRanshalla
{
    QUEST_GUARDIANS_ALTAR       = 4901,
    GOB_FIRE                    = 177417,
    GOB_ALTAR                   = 177404,
    GOB_ELUNE_GEM               = 177414,
    
    TALK_START          = 0,
    TALK_REACH_FIRE     = 1,
    TALK_EMOTE_CHANNEL  = 2,
    TALK_CONT_AFTER_FIRE = 3,
    TALK_REACH_ALTAR_1  = 4,
    TALK_REACH_ALTAR_2  = 5,
    TALK_ALTAR_ACTIVATED = 6,
    TALK_WHATS_HAPPENING = 7,
    TALK_SORRY           = 8,
    TALK_WHY_GUARD       = 9,
    TALK_THANKS          = 10,
    TALK_STAY_HERE       = 11,
    
    TALK_PRI_MANY_YEARS = 0,
    TALK_PRI_DISTURBED_ALTAR = 1,
    TALK_PRI_SACRED_PLACE = 2,
    TALK_PRI_SHOW_YOU = 3,
    TALK_PRI_LOOK_ABOVE = 4,
    TALK_PRI_DIRECT_COMM = 5,
    TALK_PRI_WISDOM     = 6,
    TALK_PRI_PROTECT    = 7,
    TALK_PRI_VISIONS    = 8,
    TALK_PRI_ASSIGNED   = 9,
    TALK_PRI_MORE_FERAL = 10,
    TALK_PRI_WANDER     = 11,
    TALK_PRI_MAGICAL    = 12,
    TALK_PRI_PROTECTING = 13,
    TALK_PRI_REMEMBER   = 14,
    TALK_PRI_ADIOS      = 15,
    
    STEP_FIRE_BEFORE  = 1,
    STEP_FIRE_AFTER   = 2,
    STEP_ALTAR_1      = 3,
    STEP_ALTAR_2      = 4,
    STEP_ALTAR_3      = 5,
    STEP_ALTAR_4      = 6,
    STEP_ALTAR_5      = 7,
    STEP_ALTAR_6      = 8,
    STEP_ALTAR_7      = 9,
    STEP_ALTAR_8      = 10,
    STEP_ALTAR_9      = 11,
    STEP_ALTAR_10     = 12,
    STEP_ALTAR_11     = 13,
    STEP_ALTAR_12     = 14,
    STEP_ALTAR_13     = 15,
    STEP_ALTAR_14     = 16,
    STEP_ALTAR_15     = 17,
    STEP_ALTAR_16     = 18,
    
    SPELL_RANSHALLA_WAITING     = 18953,
    
    NPC_PRIESTESS_ELUNE = 12116,
    NPC_VOICE_ELUNE     = 12152
};


class npc_ranshalla : public CreatureScript
{
public:
    npc_ranshalla() : CreatureScript("npc_ranshalla")
    { }

    class npc_ranshallaAI : public EscortAI
    {
        public:
        npc_ranshallaAI(Creature* pCreature) : EscortAI(pCreature)
        {
            completed = false;
            step = 0;
            timer = 0;
            priestess1 = 0;
            priestess2 = 0;
            gem = 0;
            voiceOfElune = 0;
        }
    
        bool completed;
        uint32 step;
        uint32 timer;
        
        uint64 priestess1, priestess2, gem, voiceOfElune;
        
        GameObject* getNearestFire()
        {
            return me->FindNearestGameObject(GOB_FIRE, 10.0f);
        }
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* pPlayer = GetPlayerForEscort();
            if (!pPlayer)
                return;
    
            switch (i) {
            case 4:
            case 8:
            case 12:
            case 16:
            case 23:
                Talk(TALK_REACH_FIRE);
                Talk(TALK_EMOTE_CHANNEL);
                SetEscortPaused(true);
                step = STEP_FIRE_BEFORE;
                timer = 2000;
                break;
            case 27:
                Talk(TALK_REACH_ALTAR_1);
                SetEscortPaused(true);
                step = STEP_ALTAR_1;
                timer = 2000;
                break;
            case 30:
                SetEscortPaused(true);
                step = STEP_ALTAR_2;
                timer = 1000;
                break;
            case 33:
                SetEscortPaused(true);
                step = STEP_ALTAR_6;
                timer = 500;
            default:
                break;
            }
        }
    
        void JustEngagedWith(Unit* pWho)
        override {
            
        }
        
        void JustAppeared()
        override {
            completed = false;
            step = 0;
            timer = 0;
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            priestess1 = 0;
            priestess2 = 0;
            gem = 0;
            voiceOfElune = 0;
            
            me->RemoveAurasDueToSpell(SPELL_RANSHALLA_WAITING);
        }
    
        void Reset()
        override {
            
        }
    
        void JustDied(Unit* /*pKiller*/)
        override {
            if (completed)
                return;
    
            Player* pPlayer = GetPlayerForEscort();
            if (HasEscortState(STATE_ESCORT_ESCORTING) && pPlayer)
            {
                if (pPlayer->GetQuestStatus(QUEST_GUARDIANS_ALTAR))
                    pPlayer->FailQuest(QUEST_GUARDIANS_ALTAR);
            }
        }
        
        void AltarClicked()
        {
            if (step != STEP_ALTAR_1)
                return;
            
            me->RemoveAurasDueToSpell(SPELL_RANSHALLA_WAITING);
            Talk(TALK_ALTAR_ACTIVATED);
            SetEscortPaused(false);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            EscortAI::UpdateAI(diff);
            
            if (step) {
                switch (step) {
                case STEP_FIRE_BEFORE:
                    if (timer <= diff) {
                        if (GameObject* fire = getNearestFire()) {
                            fire->SetLootState(GO_READY);
                            fire->UseDoorOrButton(60000);
                        }
                        step = STEP_FIRE_AFTER;
                        timer = 2000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_FIRE_AFTER:
                    if (timer <= diff) {
                        step = 0;
                        timer = 0;
                        Talk(TALK_CONT_AFTER_FIRE);
                        SetEscortPaused(false);
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_1:
                    if (timer) {
                        if (timer <= diff) {
                            Talk(TALK_REACH_ALTAR_2);
                            DoCast(me, SPELL_RANSHALLA_WAITING, true);
                            timer = 0;
                        }
                        else
                            timer -= diff;
                    }
                    break;
                case STEP_ALTAR_2:
                    if (timer <= diff) {
                        Talk(TALK_WHATS_HAPPENING);
                        
                        if (Creature* priestess = me->SummonCreature(NPC_PRIESTESS_ELUNE, 5518.439941, -4908.915527, 845.573853, 4.507190, TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                            priestess->GetMotionMaster()->MovePoint(0, 5516.395020, -4913.244629, 846.023438);
                            priestess1 = priestess->GetGUID();
                        }
                        if (Creature* priestess = me->SummonCreature(NPC_PRIESTESS_ELUNE, 5504.080566, -4920.494629, 848.045166, 0.040459, TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                            priestess->GetMotionMaster()->MovePoint(0, 5510.499023, -4919.807617, 846.538757);
                            priestess2 = priestess->GetGUID();
                        }
                        
                        step = STEP_ALTAR_3;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_3:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->AI()->Talk(TALK_PRI_MANY_YEARS);
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->AI()->Talk(TALK_PRI_DISTURBED_ALTAR);
                        
                        step = STEP_ALTAR_4;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_4:
                    if (timer <= diff) {
                        Talk(TALK_SORRY);
                        Talk(TALK_WHY_GUARD);
                        
                        SetEscortPaused(false);
                        
                        step = STEP_ALTAR_5;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_5:
                    if (timer) {
                        if (timer <= diff) {
                            if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                                priestess->AI()->Talk(TALK_PRI_SACRED_PLACE);
                            if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                                priestess->AI()->Talk(TALK_PRI_SHOW_YOU);
    
                            step = 0;
                            timer = 0;
                        }
                        else
                            timer -= diff;
                    }
                    break;
                case STEP_ALTAR_6:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->AI()->Talk(TALK_PRI_LOOK_ABOVE);
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->AI()->Talk(TALK_PRI_DIRECT_COMM);
                        
                        if (GameObject* theGem = me->SummonGameObject(GOB_ELUNE_GEM, Position(5514.576660, -4917.354004, 852.392029, 5.631183), G3D::Quat(), 120000))
                            gem = theGem->GetGUID();
                        
                        step = STEP_ALTAR_7;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_7:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->AI()->Talk(TALK_PRI_WISDOM);
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->AI()->Talk(TALK_PRI_PROTECT);
                        
                        if (Creature* creature = me->SummonCreature(NPC_VOICE_ELUNE, 5499.504883, -4904.982422, 850.415649, 5.581344, TEMPSUMMON_MANUAL_DESPAWN, 0)) {
                            voiceOfElune = creature->GetGUID();
                            creature->GetMotionMaster()->MovePoint(0, 5510.686035, -4914.196289, 847.290710);
                        }
                        
                        step = STEP_ALTAR_8;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_8:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->AI()->Talk(TALK_PRI_VISIONS);
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->AI()->Talk(TALK_PRI_ASSIGNED);
                        
                        step = STEP_ALTAR_9;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_9:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->AI()->Talk(TALK_PRI_VISIONS);
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->AI()->Talk(TALK_PRI_ASSIGNED);
                        
                        step = STEP_ALTAR_10;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_10:
                    if (timer <= diff) {
                        if (Creature* voice = ObjectAccessor::GetCreature(*me, voiceOfElune))
                            voice->AI()->Talk(0);
                        
                        step = STEP_ALTAR_11;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_11:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->AI()->Talk(TALK_PRI_MORE_FERAL);
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->AI()->Talk(TALK_PRI_WANDER);
                        
                        step = STEP_ALTAR_12;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_12:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->AI()->Talk(TALK_PRI_MORE_FERAL);
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->AI()->Talk(TALK_PRI_WANDER);
                        
                        step = STEP_ALTAR_13;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_13:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->AI()->Talk(TALK_PRI_MAGICAL);
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->AI()->Talk(TALK_PRI_PROTECTING);
                        
                        step = STEP_ALTAR_14;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_14:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->AI()->Talk(TALK_PRI_REMEMBER);
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->AI()->Talk(TALK_PRI_ADIOS);
                        
                        step = STEP_ALTAR_15;
                        timer = 5000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_15:
                    if (timer <= diff) {
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess1))
                            priestess->DisappearAndDie();
                        if (Creature* priestess = ObjectAccessor::GetCreature(*me, priestess2))
                            priestess->DisappearAndDie();
                        if (Creature* voice = ObjectAccessor::GetCreature(*me, voiceOfElune))
                            voice->DisappearAndDie();
                        if (GameObject* theGem = GameObject::GetGameObject(*me, gem))
                            theGem->Delete();
                        
                        Talk(TALK_THANKS);
                        Talk(TALK_STAY_HERE);
                        
                        if (Player* player = GetPlayerForEscort()) {
                            player->GroupEventHappens(QUEST_GUARDIANS_ALTAR, me);
                            completed = true;
                        }
                        
                        step = STEP_ALTAR_16;
                        timer = 6000;
                    }
                    else
                        timer -= diff;
                    break;
                case STEP_ALTAR_16:
                    if (timer <= diff) {
                        step = 0;
                        timer = 0;
                        
                        me->DisappearAndDie();
                        me->Respawn();
                    }
                    else
                        timer -= diff;
                    break;
                }
            }
    
            if (!UpdateVictim())
                return;
    
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_GUARDIANS_ALTAR) {
                me->AI()->Talk(TALK_START);
                me->SetFaction(pPlayer->GetFaction());
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                ((EscortAI*)(me->AI()))->Start(true, false, pPlayer->GetGUID(), quest);
                ((EscortAI*)(me->AI()))->SetDespawnAtEnd(false);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ranshallaAI(creature);
    }
};



class AltarOfElune : public GameObjectScript
{
public:
    AltarOfElune() : GameObjectScript("go_altar_of_elune")
    {}

    struct AltarOfEluneAI : public GameObjectAI
    {
        AltarOfEluneAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            //if (player->GetQuestStatus(QUEST_GUARDIANS_ALTAR) == QUEST_STATUS_INCOMPLETE) {
            if (Creature* ranshalla = player->FindNearestCreature(10300, 30.0f, true))
                ((npc_ranshalla::npc_ranshallaAI*)ranshalla->AI())->AltarClicked();
            //}

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new AltarOfEluneAI(go);
    }
};

void AddSC_winterspring()
{

    new npc_lorax();

    new npc_rivern_frostwind();

    new npc_witch_doctor_mauari();
    
    new npc_zap_farflinger();
    
    new npc_ranshalla();
    
    new AltarOfElune();
}

