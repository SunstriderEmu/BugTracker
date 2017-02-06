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
SDName: Azuremyst_Isle
SD%Complete: 75
SDComment: Quest support: 9283, 9537, 9582, 9554, 9531, 9303(special flight path, proper model for mount missing). Injured Draenei cosmetic only, 9582.
SDCategory: Azuremyst Isle
EndScriptData */

/* ContentData
npc_draenei_survivor
npc_engineer_spark_overgrind
npc_injured_draenei
npc_magwin
npc_susurrus
npc_geezle
mob_nestlewood_owlkin
go_ravager_cage
npc_death_ravager
EndContentData */


#include "EscortAI.h"
#include <cmath>
#include "Pet.h"

/*######
## npc_draenei_survivor
######*/

enum eDraeneiSurvivor
{
HEAL1       = -1000248,
HEAL2       = -1000249,
HEAL3       = -1000250,
HEAL4       = -1000251,

HELP1       = -1000252,
HELP2       = -1000253,
HELP3       = -1000254,
HELP4       = -1000255
};

struct npc_draenei_survivorAI : public ScriptedAI
{
    npc_draenei_survivorAI(Creature *c) : ScriptedAI(c) {}

    uint32 UnSpawnTimer;
    uint32 ResetlifeTimer;
    uint32 SayingTimer;
    uint32 HealSayTimer;
    bool UnSpawn;
    bool say;
    bool HealSay;
    bool isRun;
    bool isMove;

    void Reset() override
    {
        UnSpawnTimer = 2500;
        ResetlifeTimer= 60000;
        SayingTimer    = 5000;
        HealSayTimer = 6000;
        say = false;
        isRun = false;
        isMove = false;
        UnSpawn    = false;
        HealSay = false;
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
        //cast red shining
        me->CastSpell(me, 29152, false, nullptr);
        //set creature health
        me->SetHealth(int(me->GetMaxHealth()*.1));
        me->SetUInt32Value(UNIT_FIELD_BYTES_1, 3);
    }

    void MoveInLineOfSight(Unit *who) override                      //MoveInLineOfSight is called if creature could see you, updated all 100 ms
    {
        if (!who)
            return;

        if(who->GetTypeId() == TYPEID_PLAYER && me->IsFriendlyTo(who) && me->IsWithinDistInMap(who, 15) && say && !isRun)
        {
            switch (rand()%4)                               //Random switch between 4 texts
            {
                case 0:
                    DoScriptText(HELP1, me);
                    SayingTimer = 15000;
                    say = false;
                    break;
                case 1:
                    DoScriptText(HELP2, me);
                    SayingTimer = 15000;
                    say = false;
                    break;
                case 2:
                    DoScriptText(HELP3, me);
                    SayingTimer = 15000;
                    say = false;
                    break;
                case 3:
                    DoScriptText(HELP4, me);
                    SayingTimer = 15000;
                    say = false;
                    break;
            }
        }
        else
        {
            isRun = false;
        }
    }

    void UpdateAI(const uint32 diff) override                        //Is also called each ms for Creature AI Updates...
    {
        if (me->GetHealth() > 50)
        {
            if(ResetlifeTimer < diff)
            {
                ResetlifeTimer = 60000;
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
                //set creature health
                me->SetHealth(int(me->GetMaxHealth()*.1));
                // ley down
                me->SetUInt32Value(UNIT_FIELD_BYTES_1,3);
            }
            else ResetlifeTimer -= diff;
        }

        if(HealSay)
        {
            if (HealSayTimer < diff)
            {
                UnSpawn = true;
                isRun = true;
                isMove = true;
            }else HealSayTimer -= diff;
        }

        if(UnSpawn)
        {
            if(isMove)
            {
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovePoint(0, -4115.053711f, -13754.831055f, 73.508949f);
                isMove = false;
            }

            if (UnSpawnTimer < diff)
            {
                me->StopMoving();
                EnterEvadeMode();
                //set creature health
                me->SetHealth(int(me->GetMaxHealth()*.1));
                return;
            }else UnSpawnTimer -= diff;
        }

        if(SayingTimer < diff)
        {
            say = true;
        }else SayingTimer -= diff;
    }

    void SpellHit(Unit *Hitter, const SpellInfo *Spellkind) override //Called if you cast a spell and do some things if Specified spell is true!
    {
        if (Hitter && Spellkind->Id == 28880)
        {
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            me->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
            me->HandleEmoteCommand(ANIM_RISE);
            switch (rand()%4)                               //This switch doesn't work at all, creature say nothing!
            {
                case 0: DoScriptText(HEAL1, me, Hitter); break;
                case 1: DoScriptText(HEAL2, me, Hitter); break;
                case 2: DoScriptText(HEAL3, me, Hitter); break;
                case 3: DoScriptText(HEAL4, me, Hitter); break;
            }
            HealSay    = true;
        }
    }
};

CreatureAI* GetAI_npc_draenei_survivor(Creature *pCreature)
{
    return new npc_draenei_survivorAI (pCreature);
}

/*######
## npc_engineer_spark_overgrind
######*/

enum eSparkOvergrind
{
SAY_TEXT        = -1000256,
SAY_EMOTE       = -1000257,
ATTACK_YELL     = -1000258,

SPELL_DYNAMITE  = 7978
};

//TODO translate
#define GOSSIP_FIGHT    "Traître ! Tu vas être livré à la justice !"

struct npc_engineer_spark_overgrindAI : public ScriptedAI
{
    npc_engineer_spark_overgrindAI(Creature *c) : ScriptedAI(c) {}

    uint32 Dynamite_Timer;
    uint32 Emote_Timer;

    void Reset() override
    {
        Dynamite_Timer = 8000;
        Emote_Timer = 120000 + rand()%30000;
        me->SetFaction(875);
    }

    void UpdateAI(const uint32 diff) override
    {
        if( !me->IsInCombat() )
        {
            if (Emote_Timer < diff)
            {
                DoScriptText(SAY_TEXT, me);
                DoScriptText(SAY_EMOTE, me);
                Emote_Timer = 120000 + rand()%30000;
            }else Emote_Timer -= diff;
        }

        if(!UpdateVictim())
            return;

        if (Dynamite_Timer < diff)
        {
            DoCast(me->GetVictim(), SPELL_DYNAMITE);
            Dynamite_Timer = 8000;
        } else Dynamite_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_engineer_spark_overgrind(Creature *pCreature)
{
    return new npc_engineer_spark_overgrindAI (pCreature);
}

bool GossipHello_npc_engineer_spark_overgrind(Player *pPlayer, Creature *pCreature)
{
    if( pPlayer->GetQuestStatus(9537) == QUEST_STATUS_INCOMPLETE )
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FIGHT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);
    return true;
}

bool GossipSelect_npc_engineer_spark_overgrind(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action )
{
    if( action == GOSSIP_ACTION_INFO_DEF )
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->SetFaction(14);
        DoScriptText(ATTACK_YELL, pCreature, pPlayer);
        ((npc_engineer_spark_overgrindAI*)pCreature->AI())->AttackStart(pPlayer);
    }
    return true;
}

/*######
## npc_injured_draenei
######*/

struct npc_injured_draeneiAI : public ScriptedAI
{
    npc_injured_draeneiAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    override {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
        me->SetHealth(int(me->GetMaxHealth()*.15));
        switch (rand()%2)
        {
            case 0: me->SetUInt32Value(UNIT_FIELD_BYTES_1, 1); break;
            case 1: me->SetUInt32Value(UNIT_FIELD_BYTES_1, 3); break;
        }
    }

    void MoveInLineOfSight(Unit *who)
    override {
        return;                                             //ignore everyone around them (won't aggro anything)
    }

    void UpdateAI(const uint32 diff)
    override {
        return;
    }

};
CreatureAI* GetAI_npc_injured_draenei(Creature *pCreature)
{
    return new npc_injured_draeneiAI (pCreature);
}

/*######
## npc_magwin
######*/

enum eMagwin
{
SAY_START               = -1000111,
SAY_AGGRO               = -1000112,
SAY_PROGRESS            = -1000113,
SAY_END1                = -1000114,
SAY_END2                = -1000115,
EMOTE_HUG               = -1000116,

QUEST_A_CRY_FOR_HELP    = 9528
};

struct npc_magwinAI : public npc_escortAI
{
    npc_magwinAI(Creature *c) : npc_escortAI(c) {}


    void WaypointReached(uint32 i)
    override {
        Player* player = GetPlayerForEscort();

        if (!player)
            return;

        switch(i)
        {
        case 0:
            DoScriptText(SAY_START, me, player);
            break;
        case 17:
            DoScriptText(SAY_PROGRESS, me, player);
            break;
        case 28:
            DoScriptText(SAY_END1, me, player);
            break;
        case 29:
            DoScriptText(EMOTE_HUG, me, player);
            DoScriptText(SAY_END2, me, player);
            player->GroupEventHappens(QUEST_A_CRY_FOR_HELP,me);
            break;
        }
    }

    void EnterCombat(Unit* who)
    override {
        DoScriptText(SAY_AGGRO, me, who);
    }

    void Reset()
    override {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
            me->SetFaction(80);
    }

    void JustDied(Unit* killer)
    override {
        if (PlayerGUID)
        {
            Player* player = GetPlayerForEscort();
            if (player)
                player->FailQuest(QUEST_A_CRY_FOR_HELP);
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
        npc_escortAI::UpdateAI(diff);
    }
};

bool QuestAccept_npc_magwin(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_A_CRY_FOR_HELP)
    {
        pCreature->SetFaction(113);
        if (npc_escortAI* pEscortAI = CAST_AI(npc_magwinAI, (pCreature->AI())))
            pEscortAI->Start(true, true, false, pPlayer->GetGUID(), pCreature->GetEntry());
    }
    return true;
}

CreatureAI* GetAI_npc_magwinAI(Creature *pCreature)
{
    return new npc_magwinAI(pCreature);
}

/*######
## npc_susurrus
######*/

bool GossipHello_npc_susurrus(Player *pPlayer, Creature *pCreature)
{
    if (pCreature->IsQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->HasItemCount(23843, 1, true))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I am ready.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    SEND_PREPARED_GOSSIP_MENU(pPlayer, pCreature);

    return true;
}

bool GossipSelect_npc_susurrus(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action )
{
    if (action == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer,32474,true);               //apparently correct spell, possible not correct place to cast, or correct caster

        std::vector<uint32> nodes;

        nodes.resize(2);
        nodes[0] = 92;                                      //from susurrus
        nodes[1] = 91;                                      //end at exodar
        pPlayer->ActivateTaxiPathTo(nodes/*,11686*/);            //TaxiPath 506. Using invisible model, possible Trinity must allow 0(from dbc) for cases like this.
    }
    return true;
}

/*######
## npc_geezle
######*/

enum eGeezle
{
GEEZLE_SAY_1    = -1000259,
SPARK_SAY_2     = -1000260,
SPARK_SAY_3     = -1000261,
GEEZLE_SAY_4    = -1000262,
SPARK_SAY_5     = -1000263,
SPARK_SAY_6     = -1000264,
GEEZLE_SAY_7    = -1000265,

EMOTE_SPARK     = -1000266,

MOB_SPARK       = 17243,
GO_NAGA_FLAG    = 181694
};

static float SparkPos[3] = {-5030.95, -11291.99, 7.97};

struct npc_geezleAI : public ScriptedAI
{
    npc_geezleAI(Creature *c) : ScriptedAI(c) {}

    std::list<GameObject*> FlagList;

    uint64 SparkGUID;

    uint32 Step;
    uint32 SayTimer;

    bool EventStarted;

    void Reset() override
    {
        SparkGUID = 0;
        Step = 0;
        StartEvent();
    }

    void StartEvent()
    {
        Step = 1;
        EventStarted = true;
        Creature* Spark = me->SummonCreature(MOB_SPARK, SparkPos[0], SparkPos[1], SparkPos[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
        if(Spark)
        {
            SparkGUID = Spark->GetGUID();
            Spark->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            Spark->GetMotionMaster()->MovePoint(0, -5080.70, -11253.61, 0.56);
        }
        me->GetMotionMaster()->MovePoint(0, -5092.26, -11252, 0.71);
        SayTimer = 23000;
    }

    uint32 NextStep(uint32 Step)
    {
        Unit* Spark = ObjectAccessor::GetUnit((*me), SparkGUID);

        switch(Step)
        {
        case 0: return 99999;
        case 1:
            //DespawnNagaFlag(true);
            DoScriptText(EMOTE_SPARK, Spark);
            return 1000;
        case 2:
            DoScriptText(GEEZLE_SAY_1, me, Spark);
            if(Spark)
            {
                Spark->SetInFront(me);
                me->SetInFront(Spark);
            }
            return 5000;
        case 3: DoScriptText(SPARK_SAY_2, Spark); return 7000;
        case 4: DoScriptText(SPARK_SAY_3, Spark); return 8000;
        case 5: DoScriptText(GEEZLE_SAY_4, me, Spark); return 8000;
        case 6: DoScriptText(SPARK_SAY_5, Spark); return 9000;
        case 7: DoScriptText(SPARK_SAY_6, Spark); return 8000;
        case 8: DoScriptText(GEEZLE_SAY_7, me, Spark); return 2000;
        case 9:
            me->GetMotionMaster()->MoveTargetedHome();
            if(Spark)
                Spark->GetMotionMaster()->MovePoint(0, -5030.95, -11291.99, 7.97);
            return 20000;
        case 10:
            if(Spark)
                Spark->DealDamage(Spark,Spark->GetHealth(),nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
            //DespawnNagaFlag(false);
            me->SetVisibility(VISIBILITY_OFF);
        default: return 99999999;
        }
    }

    void DespawnNagaFlag(bool despawn)
    {
        Trinity::AllGameObjectsWithEntryInGrid go_check(GO_NAGA_FLAG);
        Trinity::GameObjectListSearcher<Trinity::AllGameObjectsWithEntryInGrid> go_search(me, FlagList, go_check);
        me->VisitNearbyGridObject(MAX_SEARCHER_DISTANCE, go_search);

        if (!FlagList.empty())
        {
            for(auto & itr : FlagList)
            {
                //TODO: Found how to despawn and respawn
                if(despawn)
                    itr->RemoveFromWorld();
                else
                    itr->Respawn();
            }
        } else error_log("SD2 ERROR: FlagList is empty!");
    }

    void UpdateAI(const uint32 diff)
    override {
        if(SayTimer < diff)
        {
            if(EventStarted)
            {
                SayTimer = NextStep(++Step);
            }
        }else SayTimer -= diff;
    }
};

CreatureAI* GetAI_npc_geezleAI(Creature *pCreature)
{
    return new npc_geezleAI(pCreature);
}

/*######
## mob_nestlewood_owlkin
######*/

enum eNestlewoodOwlkin
{
INOCULATION_CHANNEL = 29528,
INOCULATED_OWLKIN   = 16534
};

struct mob_nestlewood_owlkinAI : public ScriptedAI
{
    mob_nestlewood_owlkinAI(Creature *c) : ScriptedAI(c) {}

    uint32 ChannelTimer;
    bool Channeled;
    bool Hitted;

    void Reset()
    override {
        ChannelTimer = 0;
        Channeled = false;
        Hitted = false;
    }

    void SpellHit(Unit* caster, const SpellInfo* spell)
    override {
        if(!caster)
            return;

        if(caster->GetTypeId() == TYPEID_PLAYER && spell->Id == INOCULATION_CHANNEL)
        {
            ChannelTimer = 3000;
            Hitted = true;
        }
    }

    void UpdateAI(const uint32 diff)
    override {
        if(ChannelTimer < diff && !Channeled && Hitted)
        {
            me->DespawnOrUnsummon();
            me->SummonCreature(INOCULATED_OWLKIN, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 180000);
            Channeled = true;
        }else ChannelTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_nestlewood_owlkinAI(Creature *pCreature)
{
    return new mob_nestlewood_owlkinAI (pCreature);
}

/*######
## go_ravager_cage
######*/

enum eRavegerCage
{
NPC_DEATH_RAVAGER       = 17556,

SPELL_REND              = 13443,
SPELL_ENRAGING_BITE     = 30736,

QUEST_STRENGTH_ONE      = 9582
};

class RavagerCage : public GameObjectScript
{
public:
    RavagerCage() : GameObjectScript("go_ravager_cage")
    {}

    bool OnGossipHello(Player* p, GameObject* go) override
    {
        if (p->GetQuestStatus(QUEST_STRENGTH_ONE) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* ravager = go->FindNearestCreature(NPC_DEATH_RAVAGER, 5.0f, true))
            {
                ravager->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                ravager->SetReactState(REACT_AGGRESSIVE);
                ravager->AI()->AttackStart(p);
            }
        }
        return true;
    }
};

/*######
## npc_death_ravager
######*/

struct npc_death_ravagerAI : public ScriptedAI
{
    npc_death_ravagerAI(Creature *c) : ScriptedAI(c){}

    uint32 RendTimer;
    uint32 EnragingBiteTimer;

    void Reset()
    override {
        RendTimer = 30000;
        EnragingBiteTimer = 20000;

        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetReactState(REACT_PASSIVE);
    }
    
    void EnterCombat(Unit* who) override {}
    
    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        if(RendTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_REND);
            RendTimer = 30000;
        }
        else RendTimer -= diff;

        if(EnragingBiteTimer <= diff)
        {
            DoCast(me->GetVictim(), SPELL_ENRAGING_BITE);
            EnragingBiteTimer = 15000;
        }
        else EnragingBiteTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_death_ravagerAI(Creature* pCreature)
{
    return new npc_death_ravagerAI(pCreature);
}

/*########
## Quest: The Prophecy of Akida
########*/

enum BristlelimbCage
{
    CAPITIVE_SAY_1                      = -1600474,
    CAPITIVE_SAY_2                      = -1600475,
    CAPITIVE_SAY_3                      = -1600476,

    QUEST_THE_PROPHECY_OF_AKIDA         = 9544,
    NPC_STILLPINE_CAPITIVE              = 17375,
    GO_BRISTELIMB_CAGE                  = 181714

};


struct npc_stillpine_capitiveAI : public ScriptedAI
{
    npc_stillpine_capitiveAI(Creature *c) : ScriptedAI(c){}

    uint32 FleeTimer;

    void Reset()
    override {
        FleeTimer = 0;
        /*GameObject* cage = me->FindNearestGameObject(GO_BRISTELIMB_CAGE, 5.0f);
        if(cage)
            cage->ResetDoorOrButton();*/
    }

    void UpdateAI(const uint32 diff)
    override {
        if(FleeTimer)
        {
            if(FleeTimer <= diff)
                me->ForcedDespawn();
            else FleeTimer -= diff;
        }
    }
};

CreatureAI* GetAI_npc_stillpine_capitiveAI(Creature* pCreature)
{
    return new npc_stillpine_capitiveAI(pCreature);
}


class BristelimbCage : public GameObjectScript
{
public:
    BristelimbCage() : GameObjectScript("go_bristlelimb_cage")
    {}

    bool OnGossipHello(Player* p, GameObject* go) override
    {
        if (p->GetQuestStatus(QUEST_THE_PROPHECY_OF_AKIDA) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* pCreature = go->FindNearestCreature(NPC_STILLPINE_CAPITIVE, 5.0f, true);
            if (pCreature)
            {
                DoScriptText(RAND(CAPITIVE_SAY_1, CAPITIVE_SAY_2, CAPITIVE_SAY_3), pCreature, p);
                pCreature->GetMotionMaster()->MoveFleeing(p);
                p->KilledMonsterCredit(pCreature->GetEntry(), pCreature->GetGUID());
                CAST_AI(npc_stillpine_capitiveAI, pCreature->AI())->FleeTimer = 3500;
                return false;
            }
        }
        return true;
    }
};

/*######
## npc_trigger_quest10956
######*/

struct npc_trigger_quest10956AI : public ScriptedAI
{
    npc_trigger_quest10956AI(Creature* c) : ScriptedAI(c) {}

    void MoveInLineOfSight(Unit* pWho)
    override {
        if (me->GetDistance(pWho) <= 15.0f && pWho->GetTypeId() == TYPEID_PLAYER) {
            if (Pet* pet = pWho->ToPlayer()->GetMiniPet()) {
                if (pWho->ToPlayer()->GetQuestStatus(10956) == QUEST_STATUS_INCOMPLETE && pet->GetEntry() == 22818)
                    pWho->ToPlayer()->AreaExploredOrEventHappens(10956);
            }
        }
    }
};

CreatureAI* GetAI_npc_trigger_quest10956AI(Creature* pCreature)
{
    return new npc_trigger_quest10956AI(pCreature);
}

/*######
## AddSC
######*/

void AddSC_azuremyst_isle()
{
    OLDScript *newscript;

    newscript = new OLDScript;
    newscript->Name="npc_draenei_survivor";
    newscript->GetAI = &GetAI_npc_draenei_survivor;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_engineer_spark_overgrind";
    newscript->GetAI = &GetAI_npc_engineer_spark_overgrind;
    newscript->OnGossipHello =  &GossipHello_npc_engineer_spark_overgrind;
    newscript->OnGossipSelect = &GossipSelect_npc_engineer_spark_overgrind;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_injured_draenei";
    newscript->GetAI = &GetAI_npc_injured_draenei;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name = "npc_magwin";
    newscript->GetAI = &GetAI_npc_magwinAI;
    newscript->OnQuestAccept = &QuestAccept_npc_magwin;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_susurrus";
    newscript->OnGossipHello =  &GossipHello_npc_susurrus;
    newscript->OnGossipSelect = &GossipSelect_npc_susurrus;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_geezle";
    newscript->GetAI = &GetAI_npc_geezleAI;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="mob_nestlewood_owlkin";
    newscript->GetAI = &GetAI_mob_nestlewood_owlkinAI;
    sScriptMgr->RegisterOLDScript(newscript);

    newscript = new OLDScript;
    newscript->Name="npc_death_ravager";
    newscript->GetAI = &GetAI_npc_death_ravagerAI;
    sScriptMgr->RegisterOLDScript(newscript);

    new RavagerCage();

    newscript = new OLDScript;
    newscript->Name="npc_stillpine_capitive";
    newscript->GetAI = &GetAI_npc_stillpine_capitiveAI;
    sScriptMgr->RegisterOLDScript(newscript);
    
    new BristelimbCage();
    
    newscript = new OLDScript;
    newscript->Name="npc_trigger_quest10956";
    newscript->GetAI = &GetAI_npc_trigger_quest10956AI;
    sScriptMgr->RegisterOLDScript(newscript);
}

