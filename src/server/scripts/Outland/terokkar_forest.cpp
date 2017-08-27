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
SDName: Terokkar_Forest
SD%Complete: 80
SDComment: Quest support: 9889, 10009, 10873, 10896, 11096, 10052, 10051, 11093. Skettis->Ogri'la Flight, 10040, 10041
SDCategory: Terokkar Forest
EndScriptData */

/* ContentData
mob_unkor_the_ruthless
mob_infested_root_walker
mob_rotting_forest_rager
mob_netherweb_victim
npc_floon
npc_skyguard_handler_deesak
npc_isla_starmane
npc_hungry_nether_ray
npc_kaliri_trigger
npc_trigger_quest10950
npc_scout_neftis
npc_cenarion_sparrowhawk
npc_chief_letoll
npc_skyguard_prisoner
EndContentData */


#include "EscortAI.h"
#include "Pet.h"

/*######
## mob_unkor_the_ruthless
######*/

#define SAY_SUBMIT                      -1000351

#define FACTION_HOSTILE                 45
#define FACTION_FRIENDLY                35
#define QUEST_DONTKILLTHEFATONE         9889

#define SPELL_PULVERIZE                 2676
//#define SPELL_QUID9889                32174


class mob_unkor_the_ruthless : public CreatureScript
{
public:
    mob_unkor_the_ruthless() : CreatureScript("mob_unkor_the_ruthless")
    { }

    class mob_unkor_the_ruthlessAI : public ScriptedAI
    {
        public:
        mob_unkor_the_ruthlessAI(Creature* c) : ScriptedAI(c) {}
    
        bool CanDoQuest;
        uint32 UnkorUnfriendly_Timer;
        uint32 Pulverize_Timer;
    
        void Reset()
        override {
            CanDoQuest = false;
            UnkorUnfriendly_Timer = 0;
            Pulverize_Timer = 3000;
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_NONE);
            me->SetFaction(FACTION_HOSTILE);
        }
    
        void EnterCombat(Unit *who) override {}
    
        void DoNice()
        {
            DoScriptText(SAY_SUBMIT, me);
            me->SetFaction(FACTION_FRIENDLY);
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_SIT);
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop();
            UnkorUnfriendly_Timer = 60000;
        }
    
        void DamageTaken(Unit *done_by, uint32 &damage)
        override {
            if( done_by->GetTypeId() == TYPEID_PLAYER )
                if( (me->GetHealth()-damage)*100 / me->GetMaxHealth() < 30 )
            {
                if( Group* pGroup = (done_by->ToPlayer())->GetGroup() )
                {
                    for(GroupReference *itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
                    {
                        Player *pGroupie = itr->GetSource();
                        if( pGroupie &&
                            (pGroupie->GetQuestStatus(QUEST_DONTKILLTHEFATONE) == QUEST_STATUS_INCOMPLETE ||
                            pGroupie->GetReqKillOrCastCurrentCount(QUEST_DONTKILLTHEFATONE, 18260) == 10 ))
                        {
                            pGroupie->AreaExploredOrEventHappens(QUEST_DONTKILLTHEFATONE);
                            if( !CanDoQuest )
                                CanDoQuest = true;
                        }
                    }
                } else
                if( (done_by->ToPlayer())->GetQuestStatus(QUEST_DONTKILLTHEFATONE) == QUEST_STATUS_INCOMPLETE ||
                    (done_by->ToPlayer())->GetReqKillOrCastCurrentCount(QUEST_DONTKILLTHEFATONE, 18260) == 10 )
                {
                    (done_by->ToPlayer())->AreaExploredOrEventHappens(QUEST_DONTKILLTHEFATONE);
                    CanDoQuest = true;
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if( CanDoQuest )
            {
                if( !UnkorUnfriendly_Timer )
                {
                    //DoCast(me,SPELL_QUID9889);        //not using spell for now
                    DoNice();
                }
                else
                {
                    if( UnkorUnfriendly_Timer < diff )
                    {
                        EnterEvadeMode();
                        return;
                    }else UnkorUnfriendly_Timer -= diff;
                }
            }
    
            if(!UpdateVictim())
                return;
    
            if( Pulverize_Timer < diff )
            {
                DoCast(me,SPELL_PULVERIZE);
                Pulverize_Timer = 9000;
            }else Pulverize_Timer -= diff;
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_unkor_the_ruthlessAI(creature);
    }
};


/*######
## mob_infested_root_walker
######*/

class mob_infested_root_walker : public CreatureScript
{
public:
    mob_infested_root_walker() : CreatureScript("mob_infested_root_walker")
    { }

    class mob_infested_root_walkerAI : public ScriptedAI
    {
        public:
        mob_infested_root_walkerAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset() override { }
        void EnterCombat(Unit *who) override { }
    
        void DamageTaken(Unit *done_by, uint32 &damage)
        override {
            if (done_by && done_by->GetTypeId() == TYPEID_PLAYER)
                if (me->GetHealth() <= damage)
                    if (rand()%100 < 75)
                        //Summon Wood Mites
                        me->CastSpell(me,39130,true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_infested_root_walkerAI(creature);
    }
};


/*######
## mob_rotting_forest_rager
######*/

class mob_rotting_forest_rager : public CreatureScript
{
public:
    mob_rotting_forest_rager() : CreatureScript("mob_rotting_forest_rager")
    { }

    class mob_rotting_forest_ragerAI : public ScriptedAI
    {
        public:
        mob_rotting_forest_ragerAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset() override { }
        void EnterCombat(Unit *who) override { }
    
        void DamageTaken(Unit *done_by, uint32 &damage)
        override {
            if (done_by->GetTypeId() == TYPEID_PLAYER)
                if (me->GetHealth() <= damage)
                    if (rand()%100 < 75)
                        //Summon Lots of Wood Mights
                        me->CastSpell(me,39134,true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_rotting_forest_ragerAI(creature);
    }
};


/*######
## mob_netherweb_victim
######*/

#define QUEST_TARGET        22459
//#define SPELL_FREE_WEBBED   38950

const uint32 netherwebVictims[6] =
{
    18470, 16805, 21242, 18452, 22482, 21285
};
class mob_netherweb_victim : public CreatureScript
{
public:
    mob_netherweb_victim() : CreatureScript("mob_netherweb_victim")
    { }

    class mob_netherweb_victimAI : public ScriptedAI
    {
        public:
        mob_netherweb_victimAI(Creature *c) : ScriptedAI(c) {}
    
        void Reset() override { }
        void EnterCombat(Unit *who) override { }
        void MoveInLineOfSight(Unit *who) override { }
    
        void JustDied(Unit* Killer)
        override {
            if( Killer->GetTypeId() == TYPEID_PLAYER )
            {
                if( (Killer->ToPlayer())->GetQuestStatus(10873) == QUEST_STATUS_INCOMPLETE )
                {
                    if( rand()%100 < 25 )
                    {
                        DoSpawnCreature(QUEST_TARGET,0,0,0,0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,60000);
                        (Killer->ToPlayer())->KilledMonsterCredit(QUEST_TARGET, me->GetGUID());
                    }else
                    DoSpawnCreature(netherwebVictims[rand()%6],0,0,0,0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,60000);
    
                    if( rand()%100 < 75 )
                        DoSpawnCreature(netherwebVictims[rand()%6],0,0,0,0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,60000);
                    DoSpawnCreature(netherwebVictims[rand()%6],0,0,0,0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,60000);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_netherweb_victimAI(creature);
    }
};


/*######
## npc_floon
######*/

#define GOSSIP_FLOON1           "You owe Sim'salabim money. Hand them over or die!"
#define GOSSIP_FLOON2           "Hand over the money or die...again!"

#define SAY_FLOON_ATTACK        -1000352

#define FACTION_HOSTILE_FL      1738
#define FACTION_FRIENDLY_FL     35

#define SPELL_SILENCE           6726
#define SPELL_FROSTBOLT         9672
#define SPELL_FROST_NOVA        11831

struct npc_floonAI : public ScriptedAI
{
    npc_floonAI(Creature* c) : ScriptedAI(c) {}

    uint32 Silence_Timer;
    uint32 Frostbolt_Timer;
    uint32 FrostNova_Timer;

    void Reset()
    override {
        Silence_Timer = 2000;
        Frostbolt_Timer = 4000;
        FrostNova_Timer = 9000;
        me->SetFaction(FACTION_FRIENDLY_FL);
    }

    void EnterCombat(Unit *who) override {}

    void UpdateAI(const uint32 diff)
    override {
        if(!UpdateVictim())
            return;

        if( Silence_Timer < diff )
        {
            DoCast(me->GetVictim(),SPELL_SILENCE);
            Silence_Timer = 30000;
        }else Silence_Timer -= diff;

        if( FrostNova_Timer < diff )
        {
            DoCast(me,SPELL_FROST_NOVA);
            FrostNova_Timer = 20000;
        }else FrostNova_Timer -= diff;

        if( Frostbolt_Timer < diff )
        {
            DoCast(me->GetVictim(),SPELL_FROSTBOLT);
            Frostbolt_Timer = 5000;
        }else Frostbolt_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_npc_floon(Creature *_Creature)
{
    return new npc_floonAI (_Creature);
}

class npc_floon : public CreatureScript
{
public:
    npc_floon() : CreatureScript("npc_floon")
    { }

   class npc_floonAI : public ScriptedAI
   {
   public:
        npc_floonAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if( player->GetQuestStatus(10009) == QUEST_STATUS_INCOMPLETE )
                player->ADD_GOSSIP_ITEM(1, GOSSIP_FLOON1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            player->SEND_GOSSIP_MENU_TEXTID(9442, me->GetGUID());
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            if( action == GOSSIP_ACTION_INFO_DEF )
            {
                player->ADD_GOSSIP_ITEM(1, GOSSIP_FLOON2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU_TEXTID(9443, me->GetGUID());
            }
            if( action == GOSSIP_ACTION_INFO_DEF+1 )
            {
                player->CLOSE_GOSSIP_MENU();
                me->SetFaction(FACTION_HOSTILE_FL);
                DoScriptText(SAY_FLOON_ATTACK, me, player);
                ((npc_floon::npc_floonAI*)me->AI())->AttackStart(player);
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_floonAI(creature);
    }
};



/*######
## npc_skyguard_handler_deesak
######*/

#define GOSSIP_SKYGUARD "Fly me to Ogri'la please"

class npc_skyguard_handler_deesak : public CreatureScript
{
public:
    npc_skyguard_handler_deesak() : CreatureScript("npc_skyguard_handler_deesak")
    { }

   class npc_skyguard_handler_deesakAI : public ScriptedAI
   {
   public:
        npc_skyguard_handler_deesakAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if (player->GetReputationRank(1031) >= REP_HONORED)
                player->ADD_GOSSIP_ITEM( 2, GOSSIP_SKYGUARD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            SEND_DEFAULT_GOSSIP_MENU(player, me);

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player,41279,true);               //TaxiPath 705 (Taxi - Skettis to Skyguard Outpost)
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_skyguard_handler_deesakAI(creature);
    }
};



/*######
## npc_isla_starmane
######*/

#define SAY_PROGRESS_1  -1000353
#define SAY_PROGRESS_2  -1000354
#define SAY_PROGRESS_3  -1000355
#define SAY_PROGRESS_4  -1000356

#define QUEST_EFTW_H    10052
#define QUEST_EFTW_A    10051
#define GO_CAGE         182794
#define SPELL_CAT       32447


class npc_isla_starmane : public CreatureScript
{
public:
    npc_isla_starmane() : CreatureScript("npc_isla_starmane")
    { }

    class npc_isla_starmaneAI : public npc_escortAI
    {
        public:
        npc_isla_starmaneAI(Creature* c) : npc_escortAI(c) {}
    
        bool Completed;
        
        void Reset()
        override {
            
        }
    
        void WaypointReached(uint32 i)
        override {
            Player* player = GetPlayerForEscort();
    
            if(!player)
                return;
    
            switch(i)
            {
            case 0:
                {
                GameObject* Cage = me->FindNearestGameObject(GO_CAGE, 10);
                if(Cage)
                    Cage->UseDoorOrButton();
                }break;
            case 2: DoScriptText(SAY_PROGRESS_1, me, player); break;
            case 5: DoScriptText(SAY_PROGRESS_2, me, player); break;
            case 6: DoScriptText(SAY_PROGRESS_3, me, player); break;
            case 29:DoScriptText(SAY_PROGRESS_4, me, player);
                if (player)
                {
                    if( player->GetTeam() == ALLIANCE)
                        player->GroupEventHappens(QUEST_EFTW_A, me);
                    else if(player->GetTeam() == HORDE)
                        player->GroupEventHappens(QUEST_EFTW_H, me);
                } Completed = true;
                me->SetInFront(player); break;
            case 30: me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE); break;
            case 31: DoCast(me, SPELL_CAT);
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING); break;
            }
        }
    
        void JustRespawned()
        override {
            Completed = false;
            me->SetFaction(1660);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    
        void EnterCombat(Unit* who)override {}
    
        void JustDied(Unit* killer)
        override {
            if (PlayerGUID)
            {
                Player* player = GetPlayerForEscort();
                if (player && !Completed)
                {
                    if(player->GetTeam() == ALLIANCE)
                        player->FailQuest(QUEST_EFTW_A);
                    else if(player->GetTeam() == HORDE)
                        player->FailQuest(QUEST_EFTW_H);
                }
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            npc_escortAI::UpdateAI(diff);
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_EFTW_H || quest->GetQuestId() == QUEST_EFTW_A)
            {
                ((npc_escortAI*)(me->AI()))->Start(true, true, false, player->GetGUID(), me->GetEntry());
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_isla_starmaneAI(creature);
    }
};



/*######
## go_skull_pile
######*/
#define GOSSIP_S_DARKSCREECHER_AKKARAI      "Summon Darkscreecher Akkarai"
#define GOSSIP_S_KARROG                     "Summon Karrog"
#define GOSSIP_S_GEZZARAK_THE_HUNTRESS      "Summon Gezzarak the Huntress"
#define GOSSIP_S_VAKKIZ_THE_WINDRAGER       "Summon Vakkiz the Windrager"

class SkullPile : public GameObjectScript
{
public:
    SkullPile() : GameObjectScript("go_skull_pile")
    {}

    struct SkullPileAI : public GameObjectAI
    {
        SkullPileAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if ((player->GetQuestStatus(11885) == QUEST_STATUS_INCOMPLETE) || player->GetQuestRewardStatus(11885))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_S_DARKSCREECHER_AKKARAI, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_S_KARROG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_S_GEZZARAK_THE_HUNTRESS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_S_VAKKIZ_THE_WINDRAGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            }

            player->SEND_GOSSIP_MENU_TEXTID(me->GetGOInfo()->questgiver.gossipID, me->GetGUID());
            return true;
        }

        bool GossipSelect(Player *player, uint32 sender, uint32 action) override
        {
            switch (sender)
            {
            case GOSSIP_SENDER_MAIN:    SendActionMenu_go_skull_pile(player, me, action); break;
            }
            return true;
        }

        void SendActionMenu_go_skull_pile(Player *player, GameObject* _GO, uint32 action)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CastSpell(player, 40642, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->CastSpell(player, 40640, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->CastSpell(player, 40632, false);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->CastSpell(player, 40644, false);
                break;
            }
        }

    };

   
    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new SkullPileAI(go);
    }
};

/*######
## go_ancient_skull_pile
######*/

enum eAncientSkullPile
{
    QUEST_TEROKK_DOWNFALL       = 11073,

    ENTRY_TEROKK                = 21838
};

class AncientSkullPile : public GameObjectScript
{
public:
    AncientSkullPile() : GameObjectScript("go_ancient_skull_pile")
    {}

    struct AncientSkullPileAI : public GameObjectAI
    {
        AncientSkullPileAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(QUEST_TEROKK_DOWNFALL) == QUEST_STATUS_INCOMPLETE)
                pPlayer->SummonCreature(ENTRY_TEROKK, -3793.01, 3503.55, 287.01, 0.9485, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
            else if (pPlayer->HasItemCount(32720, 1, false)) {
                pPlayer->SummonCreature(ENTRY_TEROKK, -3793.01, 3503.55, 287.01, 0.9485, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                pPlayer->DestroyItemCount(32720, 1, true);
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new AncientSkullPileAI(go);
    }
};

/*######
## npc_hungry_nether_ray
######*/

#define SPELL_SUMMON_RAY    41423

#define RAY_FEED_CREDIT  23438


class npc_hungry_nether_ray : public CreatureScript
{
public:
    npc_hungry_nether_ray() : CreatureScript("npc_hungry_nether_ray")
    { }

    class npc_hungry_nether_rayAI : public ScriptedAI
    {
        public:
        npc_hungry_nether_rayAI(Creature* c) : ScriptedAI(c) {}
        
        uint32 checkTimer;
        uint64 lastCredit;
        
        void Reset()
        override {
            me->GetMotionMaster()->MoveFollow(me->GetOwner(), PET_FOLLOW_DIST, me->GetFollowAngle());
            checkTimer = 5000; //check for creature every 5 sec
        }
        
        void EnterCombat(Unit* who) override {}
        
        void UpdateAI(const uint32 diff)
        override {
            if (checkTimer < diff)
            {
                Creature* feedCredit = me->FindNearestCreature(RAY_FEED_CREDIT, 10);
                if (feedCredit && feedCredit->GetGUID() != lastCredit)
                {
                    lastCredit = feedCredit->GetGUID();
                    (me->GetOwner()->ToPlayer())->KilledMonsterCredit(RAY_FEED_CREDIT, feedCredit->GetGUID());
                    feedCredit->DespawnOrUnsummon();
                    checkTimer = 5000;
                }
            }else checkTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hungry_nether_rayAI(creature);
    }
};


/*######
## npc_kaliri_egg_trigger
######*/


class npc_kaliri_egg_trigger : public CreatureScript
{
public:
    npc_kaliri_egg_trigger() : CreatureScript("npc_kaliri_egg_trigger")
    { }

    class npc_kaliri_egg_triggerAI : public ScriptedAI
    {
        public:
        npc_kaliri_egg_triggerAI(Creature* c) : ScriptedAI(c) {}
    
        void Reset()
        override {
            me->SetFaction(FACTION_MONSTER);
            me->SetVisible(false);
            GameObject* eggGO = nullptr;
    
            Trinity::NearestGameObjectEntryInObjectRangeCheck go_check(*me, 185549, 1);
            Trinity::GameObjectLastSearcher<Trinity::NearestGameObjectEntryInObjectRangeCheck> searcher(me, eggGO, go_check);
            Cell::VisitGridObjects(me, searcher, MAX_SEARCHER_DISTANCE);
    
            if(eggGO)
                eggGO->ResetDoorOrButton();
        }
    
        void EnterCombat(Unit *who) override {}
        void AttackStart(Unit* who) override {}
        void MoveInLineOfSight(Unit* who) override {}
        void UpdateAI(const uint32 diff) override {}
        void SpellHit(Unit *caster, const SpellInfo *spell)
        override {
            if (spell->Id == 39844){
                GameObject* eggGO = me->FindNearestGameObject(185549, 10.0f);
                if(eggGO)
                    eggGO->UseDoorOrButton();
                    
                caster->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
            }
        }

        virtual bool sOnDummyEffect(Unit* caster, uint32 spellId, uint32 effIndex) override
        {
            if (spellId == 39844) {
                GameObject* eggGO = me->FindNearestGameObject(185549, 10.0f);
                if (eggGO)
                    eggGO->UseDoorOrButton();

                caster->DealDamage(me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                return true;
            }
            
            return false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kaliri_egg_triggerAI(creature);
    }
};



/*######
## npc_trigger_quest10950
######*/


class npc_trigger_quest10950 : public CreatureScript
{
public:
    npc_trigger_quest10950() : CreatureScript("npc_trigger_quest10950")
    { }

    class npc_trigger_quest10950AI : public ScriptedAI
    {
        public:
        npc_trigger_quest10950AI(Creature* c) : ScriptedAI(c) {}
        
        void EnterCombat(Unit* pWho) override {}
        
        void MoveInLineOfSight(Unit* pWho)
        override {
            if (me->GetDistance(pWho) <= 10.0f && pWho->GetTypeId() == TYPEID_PLAYER) {
    			if (uint64 critter_guid = pWho->ToPlayer()->GetCritterGUID())
    				if (Creature* pet = pWho->GetMap()->GetCreature(critter_guid)) {
    					if (pWho->ToPlayer()->GetQuestStatus(10950) == QUEST_STATUS_INCOMPLETE && pet->GetEntry() == 22818)
    						pWho->ToPlayer()->AreaExploredOrEventHappens(10950);
    				}
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trigger_quest10950AI(creature);
    }
};


/*######
## npc_scout_neftis
######*/

class npc_scout_neftis : public CreatureScript
{
public:
    npc_scout_neftis() : CreatureScript("npc_scout_neftis")
    { }

   class npc_scout_neftisAI : public ScriptedAI
   {
   public:
        npc_scout_neftisAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == 10040 || quest->GetQuestId() == 10041) {
                player->CastSpell(player, 32756, true);
                if (player->GetGender() == GENDER_MALE)
                    player->CastSpell(player, 38080, true);
                else
                    player->CastSpell(player, 38081, true);
            }
        }


        virtual bool GossipHello(Player* player) override
        {
            //todo translate
            player->PrepareQuestMenu(me->GetGUID());
            if (player->GetQuestStatus(10040) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(10041) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "J'ai perdu mon déguisement", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            
            SEND_PREPARED_GOSSIP_MENU(player, me);
            
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            if (action == GOSSIP_ACTION_INFO_DEF + 1) {
                player->CastSpell(player, 32756, true);
                if (player->GetGender() == GENDER_MALE)
                    player->CastSpell(player, 38080, true);
                else
                    player->CastSpell(player, 38081, true);
            }
            
            player->CLOSE_GOSSIP_MENU();

            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_scout_neftisAI(creature);
    }
};




/*######
## npc_cenarion_sparrowhawk
######*/


class npc_cenarion_sparrowhawk : public CreatureScript
{
public:
    npc_cenarion_sparrowhawk() : CreatureScript("npc_cenarion_sparrowhawk")
    { }

    class npc_cenarion_sparrowhawkAI : public ScriptedAI
    {
        public:
        npc_cenarion_sparrowhawkAI(Creature* c) : ScriptedAI(c) {}
        
        uint32 despawnTimer;
        
        void Reset()
        override {
            despawnTimer = 0;
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
    
            if (GameObject* ravenStone = me->FindNearestGameObject(185541, 100.0f)) {
                float x, y, z;
                ravenStone->GetPosition(x, y, z);
                me->GetMotionMaster()->MovePoint(0, x, y, z);
            }
            else
                despawnTimer = 10000;
        }
        
        void EnterCombat(Unit* who) override {}
        
        void MovementInform(uint32 type, uint32 id)
        override {
            if (id == 0)
                despawnTimer = 15000;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!despawnTimer)
                return;
                
            if (despawnTimer <= diff)
                me->DisappearAndDie();
            else
                despawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_cenarion_sparrowhawkAI(creature);
    }
};


/*######
## npc_chief_letoll
######*/

enum ChiefLetollData {
    QUEST_DIGGING_THROUGH_BONES = 10922,
    
    NPC_BONE_SIFTER             = 22466,
    NPC_RESEARCHER              = 22464,
    
    SAY_LETOLL_CIRCLE           = -1000804,
    SAY_LETOLL_ASK_PLAYER       = -1000805,
    SAY_LETOLL_DIGSITE_NORTH    = -1000806,
    SAY_LETOLL_START_DIGGING    = -1000807,
    SAY_LETOLL_FOUND_SOMETHING  = -1000808,
    SAY_LETOLL_ALMOST_GOT_IT    = -1000809,
    SAY_LETOLL_LOOKS_LIKE_DRUM  = -1000810,
    SAY_LETOLL_WOW_A_DRUM       = -1000811,
    SAY_LETOLL_DISCOVERY_ROCK   = -1000812,
    SAY_LETOLL_HIVES            = -1000813,
    SAY_LETOLL_YE_MAD           = -1000814,
    SAY_LETOLL_SILITHUS         = -1000815,
    SAY_LETOLL_PLAGUE           = -1000816,
    SAY_LETOLL_ARTHAS_COUSIN    = -1000817,
    SAY_LETOLL_FIGMENT_IMAGIN   = -1000818,
    SAY_LETOLL_SHUT_UP          = -1000819,
    EMOTE_LETOLL_BANG           = -1000820,
    SAY_LETOLL_TOLD_YA          = -1000821,
    SAY_LETOLL_HELP_HIM         = -1000822,
    EMOTE_LETOLL_PICKS_DRUM     = -1000823,
    SAY_LETOLL_THANKS_PLAYER    = -1000824,
};


class npc_chief_letoll : public CreatureScript
{
public:
    npc_chief_letoll() : CreatureScript("npc_chief_letoll")
    { }

    class npc_chief_letollAI : public npc_escortAI
    {
        public:
        npc_chief_letollAI(Creature* c) : npc_escortAI(c), summons(me)
        {
            timer = 0;
        }
        
        SummonList summons;
        
        uint32 timer;
        uint32 step;
        
        uint64 playerGUID;
        
        std::vector<uint64> researchers;
        
        void Reset() override {}
        
        void EnterCombat(Unit* who) override {}
        
        void SummonedCreatureDespawn(Creature* summon)
        override {
            Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
            if (player) {
                if (player->GetGroup())
                    player->GroupEventHappens(QUEST_DIGGING_THROUGH_BONES, me);
                else
                    player->AreaExploredOrEventHappens(QUEST_DIGGING_THROUGH_BONES);
            }
            
            DoScriptText(EMOTE_LETOLL_PICKS_DRUM, me);
            if (player)
                DoScriptText(SAY_LETOLL_THANKS_PLAYER, me, player);
            timer = 3000;
        }
        
        class AnyResearcherCheck
        {
            public:
                AnyResearcherCheck(WorldObject const* obj, float range) : i_obj(obj), i_range(range) {}
                bool operator()(Unit* u)
                {
                    Creature *c = u->ToCreature();
                    if (!i_obj->IsWithinDistInMap(c, i_range))
                        return false;
                    return (c->GetEntry() == NPC_RESEARCHER);
                }
    
            private:
                WorldObject const* i_obj;
                float i_range;
        };
    
        void AssignSearchersGUIDs()
        {
            researchers.clear();
            
            std::list<Creature*> unitList;
    
            AnyResearcherCheck u_check(me, 30.0f);
            Trinity::CreatureListSearcher<AnyResearcherCheck> searcher(me, unitList, u_check);
            Cell::VisitGridObjects(me, searcher, MAX_SEARCHER_DISTANCE);
    
            for(auto c : unitList)
            {
                if (c)
                    researchers.push_back(c->GetGUID());
            }
        }
        
        void WaypointReached(uint32 id)
        override {
            Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
            if (!player)
                return;
    
            switch (id) {
            case 0:
                SetEscortPaused(true);
                DoScriptText(SAY_LETOLL_CIRCLE, me);
                AssignSearchersGUIDs();
                if (researchers.size() >= 4) {
                    for (uint8 i = 0; i < 4; i++) {
                        if (Creature* researcher = ObjectAccessor::GetCreature(*me, researchers[i]))
                            researcher->GetMotionMaster()->MoveFollow(me, PET_FOLLOW_DIST, i * (M_PI/4.0f));
                    }
                }
                timer = 3000;
                break;
            case 5:
                DoScriptText(SAY_LETOLL_START_DIGGING, me);
                SetEscortPaused(true);
                timer = 1000;
                break;
            }
        }
        
        void StartEvent(uint64 pGUID)
        {
            playerGUID = pGUID;
            step = 0;
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        }
        
        void DoResearcherScriptText(uint32 researcherId, int32 textId)
        {
            if (researchers.size() >= 4) {
                if (Creature* researcher = ObjectAccessor::GetCreature(*me, researchers[researcherId]))
                    DoScriptText(textId, researcher);
            }
        }
        
        void EnterEvadeMode(EvadeReason why)
        override {
            if (researchers.size() >= 4) {
                for (uint8 i = 0; i < 4; i++) {
                    if (Creature* researcher = ObjectAccessor::GetCreature(*me, researchers[i]))
                        researcher->GetMotionMaster()->MoveFollow(me, PET_FOLLOW_DIST, i * (M_PI/2.0f));
                }
            }
            
            npc_escortAI::EnterEvadeMode(why);
        }
        
        void ResearchersSetRun(bool run)
        {
            if (researchers.size() >= 4) {
                for (uint8 i = 0; i < 4; i++) {
                    if (Creature* researcher = ObjectAccessor::GetCreature(*me, researchers[i])) {
                        if (run)
                            researcher->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        else
                            researcher->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    }
                }
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            npc_escortAI::UpdateAI(diff);
            
            Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
            if (!player) {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                EnterEvadeMode(EvadeReason::EVADE_REASON_OTHER);
            }
                
            if (timer) {
                if (timer <= diff) {
                    switch (step) {
                    case 0:
                        DoScriptText(SAY_LETOLL_ASK_PLAYER, me, player);
                        ResearchersSetRun(false);
                        step++;
                        timer = 3000;
                        break;
                    case 1:
                        DoScriptText(SAY_LETOLL_DIGSITE_NORTH, me);
                        step++;
                        timer = 3000;
                        break;
                    case 2:
                        SetEscortPaused(false);
                        timer = 0;
                        step++;
                        break;
                    case 3:
                        for (uint8 i = 0; i < 4; i++) {
                            if (Creature* researcher = ObjectAccessor::GetCreature(*me, researchers[i]))
                                researcher->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_WORK);
                        }
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_WORK);
                        timer = 15000;
                        step++;
                        break;
                    case 4:
                        DoScriptText(SAY_LETOLL_FOUND_SOMETHING, me);
                        for (uint8 i = 0; i < 4; i++) {
                            if (Creature* researcher = ObjectAccessor::GetCreature(*me, researchers[i]))
                                researcher->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                        }
                        timer = 6000;
                        step++;
                        break;
                    case 5:
                        DoScriptText(SAY_LETOLL_ALMOST_GOT_IT, me);
                        timer = 6000;
                        step++;
                        break;
                    case 6:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                        DoScriptText(SAY_LETOLL_LOOKS_LIKE_DRUM, me);
                        timer = 6000;
                        step++;
                        break;
                    case 7:
                        DoResearcherScriptText(0, SAY_LETOLL_WOW_A_DRUM);
                        timer = 4000;
                        step++;
                        break;
                    case 8:
                        DoResearcherScriptText(1, SAY_LETOLL_DISCOVERY_ROCK);
                        timer = 5000;
                        step++;
                        break;
                    case 9:
                        DoResearcherScriptText(2, SAY_LETOLL_HIVES);
                        timer = 4000;
                        step++;
                        break;
                    case 10:
                        DoScriptText(SAY_LETOLL_YE_MAD, me);
                        timer = 10000;
                        step++;
                        break;
                    case 11:
                        DoResearcherScriptText(3, SAY_LETOLL_SILITHUS);
                        timer = 8000;
                        step++;
                        break;
                    case 12:
                        DoResearcherScriptText(0, SAY_LETOLL_PLAGUE);
                        timer = 8000;
                        step++;
                        break;
                    case 13:
                        DoResearcherScriptText(1, SAY_LETOLL_ARTHAS_COUSIN);
                        timer = 12000;
                        step++;
                        break;
                    case 14:
                        DoResearcherScriptText(2, SAY_LETOLL_FIGMENT_IMAGIN);
                        timer = 12000;
                        step++;
                        break;
                    case 15:
                        DoScriptText(SAY_LETOLL_SHUT_UP, me);
                        timer = 3000;
                        step++;
                        break;
                    case 16:
                        DoScriptText(EMOTE_LETOLL_BANG, me);
                        timer = 2000;
                        step++;
                        break;
                    case 17:
                    {
                        if (Creature* sifter = me->SummonCreature(NPC_BONE_SIFTER, -3559.654785, 5442.702148, -12.548286, 1.220623, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000))
                            sifter->AI()->AttackStart(me);
                        
                        timer = 500;
                        step++;
                        break;
                    }
                    case 18:
                        DoScriptText(SAY_LETOLL_TOLD_YA, me);
                        timer = 2000;
                        step++;
                        break;
                    case 19:
                        DoScriptText(SAY_LETOLL_HELP_HIM, me);
                        timer = 0;
                        step++;
                        break;
                    case 20:
                        SetRun();
                        ResearchersSetRun(true);
                        me->GetMotionMaster()->MoveTargetedHome();
                        timer = 0;
                        step++;
                        break;
                    }
                }
                else
                    timer -= diff;
            }
            
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_DIGGING_THROUGH_BONES) {
                ((npc_escortAI*)me->AI())->Start(true, true, false, player->GetGUID(), me->GetEntry());
                ((npc_chief_letoll::npc_chief_letollAI*)me->AI())->StartEvent(player->GetGUID());
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_chief_letollAI(creature);
    }
};



/*######
## npc_skyguard_prisoner
######*/

enum SkyguardPrisonerData {
    QUEST_ESCAPE_FROM_SKETTIS       = 11085,
    
    GO_SKYGUARD_CAGE                = 185952,
    
    SAY_SKYGUARD_PRISONER_START     = -1000825,
    SAY_SKYGUARD_PRISONER_CONTINUE  = -1000826,
    SAY_SKYGUARD_PRISONER_THANKS    = -1000827,
    
    NPC_SKETTIS_WING_GUARD          = 21644
};


class npc_skyguard_prisoner : public CreatureScript
{
public:
    npc_skyguard_prisoner() : CreatureScript("npc_skyguard_prisoner")
    { }

    class npc_skyguard_prisonerAI : npc_escortAI
    {
        public:
        npc_skyguard_prisonerAI(Creature* c) : npc_escortAI(c) {}
        
        void Reset() override {}
        
        void EnterCombat(Unit* who) override {}
        
        void KilledUnit(Unit* victim)
        override {
            if (rand()%2)
                DoScriptText(SAY_SKYGUARD_PRISONER_CONTINUE, me);
        }
        
        void WaypointReached(uint32 id)
        override {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;
                
            switch (id) {
            case 11:
                if (Creature* add = me->SummonCreature(NPC_SKETTIS_WING_GUARD, -4182.494141, 3079.858643, 329.511017, 4.607359, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                    add->AI()->AttackStart(me);
                if (Creature* add = me->SummonCreature(NPC_SKETTIS_WING_GUARD, -4179.783691, 3079.299072, 329.644470, 4.384305, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
                    add->AI()->AttackStart(me);
                break;
            case 14:
                DoScriptText(SAY_SKYGUARD_PRISONER_THANKS, me);
                if (player->GetGroup())
                    player->GroupEventHappens(QUEST_ESCAPE_FROM_SKETTIS, me);
                else
                    player->AreaExploredOrEventHappens(QUEST_ESCAPE_FROM_SKETTIS);
                SetRun();
                break;
            }
        }
        
        void UpdateAI(uint32 const diff)
        override {
            npc_escortAI::UpdateAI(diff);
            
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_ESCAPE_FROM_SKETTIS) {
                if (GameObject* cage = me->FindNearestGameObject(GO_SKYGUARD_CAGE, 5.0f))
                    cage->UseDoorOrButton(30);
                DoScriptText(SAY_SKYGUARD_PRISONER_START, me);
                ((npc_escortAI*)me->AI())->Start(true, true, false, player->GetGUID(), me->GetEntry());
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_skyguard_prisonerAI(creature);
    }
};



/*######
## AddSC
######*/

void AddSC_terokkar_forest()
{

    new mob_unkor_the_ruthless();

    new mob_infested_root_walker();

    new mob_rotting_forest_rager();

    new mob_netherweb_victim();

    new npc_floon();

    new npc_skyguard_handler_deesak();

    new npc_isla_starmane();

    new SkullPile();
    
    new npc_hungry_nether_ray();
    
    new AncientSkullPile();
    
    new npc_kaliri_egg_trigger();
    
    new npc_trigger_quest10950();
    
    new npc_scout_neftis();
    
    new npc_cenarion_sparrowhawk();
    
    new npc_chief_letoll();
    
    new npc_skyguard_prisoner();
}

