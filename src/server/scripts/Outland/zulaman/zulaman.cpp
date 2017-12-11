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
SDName: Zulaman
SD%Complete: 90
SDComment: Forest Frog will turn into different NPC's. Workaround to prevent new entry from running this script
SDCategory: Zul'Aman
EndScriptData */

/* ContentData
npc_forest_frog
npc_zulaman_hostage
npc_harrison_jones
go_za_gong
npc_amanishi_lookout
npc_amanishi_tempest
npc_amanishi_berserker
npc_amanishi_scout
at_quest_X_marks
mob_akilzon_gauntlet
EndContentData */


#include "def_zulaman.h"

/*######
## npc_forest_frog
######*/

#define SPELL_REMOVE_AMANI_CURSE    43732
#define SPELL_PUSH_MOJO             43923
#define ENTRY_FOREST_FROG           24396

class npc_forest_frog : public CreatureScript
{
public:
    npc_forest_frog() : CreatureScript("npc_forest_frog")
    { }

    class npc_forest_frogAI : public ScriptedAI
    {
        public:
        npc_forest_frogAI(Creature* c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        void Reset() override { }
    
        void EnterCombat(Unit *who) override { }
    
        void DoSpawnRandom()
        {
            if( pInstance )
            {
                uint32 cEntry = 0;
                switch(rand()%10)
                {
                    case 0: cEntry = 24397; break;          //Mannuth
                    case 1: cEntry = 24403; break;          //Deez
                    case 2: cEntry = 24404; break;          //Galathryn
                    case 3: cEntry = 24405; break;          //Adarrah
                    case 4: cEntry = 24406; break;          //Fudgerick
                    case 5: cEntry = 24407; break;          //Darwen
                    case 6: cEntry = 24445; break;          //Mitzi
                    case 7: cEntry = 24448; break;          //Christian
                    case 8: cEntry = 24453; break;          //Brennan
                    case 9: cEntry = 24455; break;          //Hollee
                }
    
                if (!pInstance->GetData(TYPE_RAND_VENDOR_1))
                    if(rand()%10 == 1) cEntry = 24408;      //Gunter
                if (!pInstance->GetData(TYPE_RAND_VENDOR_2))
                    if(rand()%10 == 1) cEntry = 24409;      //Kyren
    
                if (cEntry) me->UpdateEntry(cEntry);
    
                if (cEntry == 24408) pInstance->SetData(TYPE_RAND_VENDOR_1,DONE);
                if (cEntry == 24409) pInstance->SetData(TYPE_RAND_VENDOR_2,DONE);
            }
        }
    
        void SpellHit(Unit *caster, const SpellInfo *spell)
        override {
            if( spell->Id == SPELL_REMOVE_AMANI_CURSE && caster->GetTypeId() == TYPEID_PLAYER && me->GetEntry() == ENTRY_FOREST_FROG )
            {
                //increase or decrease chance of mojo?
                if( rand()%99 == 50 ) DoCast(caster,SPELL_PUSH_MOJO,true);
                else DoSpawnRandom();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_forest_frogAI(creature);
    }
};


/*######
## npc_zulaman_hostage
######*/

#define GOSSIP_HOSTAGE1        "I am glad to help you."

static uint32 HostageEntry[] = {23790, 23999, 24024, 24001};
static uint32 ChestEntry[] = {186648, 187021, 186667, 186672};


class npc_zulaman_hostage : public CreatureScript
{
public:
    npc_zulaman_hostage() : CreatureScript("npc_zulaman_hostage")
    { }

    class npc_zulaman_hostageAI : public ScriptedAI
    {
        public:
        npc_zulaman_hostageAI(Creature *c) : ScriptedAI(c) {IsLoot = false;}
        bool IsLoot;
        uint64 PlayerGUID;
        void Reset() override {}
        void EnterCombat(Unit *who) override {}
        void JustDied(Unit *)
        override {
            Player* player = ObjectAccessor::GetPlayer(*me, PlayerGUID);
            if(player) player->SendLoot(me->GetGUID(), LOOT_CORPSE);
        }
        void UpdateAI(const uint32 diff)
        override {
            if(IsLoot) me->CastSpell(me, 7, TRIGGERED_NONE);
        }

        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HOSTAGE1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            SEND_PREPARED_GOSSIP_MENU(player, me);
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if(action == GOSSIP_ACTION_INFO_DEF + 1)
                player->CLOSE_GOSSIP_MENU();

            if(!me->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
                return true;

            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            InstanceScript* pInstance = ((InstanceScript*)me->GetInstanceScript());
            if(pInstance)
            {
                //uint8 progress = pInstance->GetData(DATA_CHESTLOOTED);
                pInstance->SetData(DATA_CHESTLOOTED, 0);
                float x, y, z;
                me->GetPosition(x, y, z);
                uint32 entry = me->GetEntry();
                for(uint8 i = 0; i < 4; ++i)
                {
                    if(HostageEntry[i] == entry)
                    {
                        TC_LOG_ERROR("scripts","ZUL'AMAN CHEST: Data 7 was %u when spawning gameobject.", pInstance->GetData(DATA_CHESTLOOTED));
                        me->SummonGameObject(ChestEntry[i], Position(x-2.0f, y, z, 0), G3D::Quat(), 0);
                        break;
                    }
                }
                /*Creature* summon = me->SummonCreature(HostageInfo[progress], x-2, y, z, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
                if(summon)
                {
                    ((npc_zulaman_hostage::npc_zulaman_hostageAI*)summon->AI())->PlayerGUID = player->GetGUID();
                    ((npc_zulaman_hostage::npc_zulaman_hostageAI*)summon->AI())->IsLoot = true;
                    summon->SetDisplayId(10056);
                    summon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    summon->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                }*/
            }
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_zulaman_hostageAI(creature);
    }
};




/*######
## npc_harrison_jones
######*/

#define GONG_ENTRY          187359
#define MASSIVEGATE_ENTRY   186728



#define GOSSIP_GONG         "[PH] We are ready."
#define GOSSIP_GONG_DEBUG   "[DEBUG] Open Door."

class npc_harrison_jones : public CreatureScript
{
public:
    npc_harrison_jones() : CreatureScript("npc_harrison_jones")
    { }

    class  npc_harrison_jonesAI : public ScriptedAI
    {
        public:
        npc_harrison_jonesAI(Creature *c) : ScriptedAI(c) {}
        
        uint8 gongClicked;
        uint32 suicideTimer;
        uint32 deathTimer;
        
        std::vector<uint64> clickGUIDs;
        
        void Reset()
        override {
            gongClicked = 0;
            suicideTimer = 0;
            deathTimer = 0;
        }
        
        void EnterCombat(Unit* pWho) override {}
        
        bool IncreaseClick(uint64 pGUID)
        {
            // Don't allow the same player to click several times
            for (std::vector<uint64>::const_iterator itr = clickGUIDs.begin(); itr != clickGUIDs.end(); itr++) {
                if ((*itr) == pGUID)
                    return false;
            }
            
            gongClicked++;
            std::string s = "";
            if (gongClicked < 4)
                s = "s";
            std::stringstream sst;
            //sst << "Encore " << 5 - gongClicked << " personne" << s << " !";
            sst << "Need " << 5 - gongClicked << " more person" << s << "!";
            if (gongClicked < 5)
                me->Say(sst.str().c_str(), LANG_UNIVERSAL, nullptr);
            
            clickGUIDs.push_back(pGUID);
            
            if (gongClicked >= 5)
                OpenDoorAndStartTimer();
    
            return true;
        }
        
        void OpenDoorAndStartTimer()
        {
            if (GameObject* gong = me->FindNearestGameObject(GONG_ENTRY, 15.0f))   // Lock the gong again
                gong->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
            
            if (InstanceScript* pInstance = ((InstanceScript*)me->GetInstanceScript())) {
                pInstance->SetData(DATA_QUESTMINUTE, IN_PROGRESS);
                pInstance->SetData(DATA_GONG_EVENT, DONE);
                // Also remove aura on all players in map
                Map::PlayerList const& players = pInstance->instance->GetPlayers();
                if (!players.isEmpty()) {
                    for(const auto & player : players) {
                        if (Player* plr = player.GetSource())
                            plr->RemoveAurasDueToSpell(45225);
                    }
                }
            }
            
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);   // Prevent restarting the timer I don't know how...
            me->RemoveAurasDueToSpell(45225);
            
            me->GetMotionMaster()->MovePath(24358, false); //this path is PATH_TYPE_ONCE
            suicideTimer = 14000;
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (suicideTimer) {
                if (suicideTimer <= diff) {
                    if (GameObject* massiveDoor = me->FindNearestGameObject(MASSIVEGATE_ENTRY, 50.0f))
                        massiveDoor->UseDoorOrButton();
                    suicideTimer = 0;
                    deathTimer = 5000;
                }
                else
                    suicideTimer -= diff;
            }
            
            if (deathTimer) {
                if (deathTimer <= diff) {
                    me->DisappearAndDie();
                }
                else
                    deathTimer -= diff;
            }
        }

        virtual bool GossipHello(Player* pPlayer) override
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_GONG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            if (pPlayer->IsGameMaster())
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_GONG_DEBUG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            SEND_PREPARED_GOSSIP_MENU(pPlayer, me);
            
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1) {
                if (GameObject* pGo = me->FindNearestGameObject(GONG_ENTRY, 15.0f)) {
                    pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                    me->SetFacingTo(5.7499);
                    me->Say("Help me to hit the gong!", LANG_UNIVERSAL, nullptr);
                    me->AddAura(45225, me);
                }
                else
                    TC_LOG_ERROR("scripts","ERROR: Zul'aman: Harrison Jones couldn't find the gong.");
                    
                return true;
            }
            else if (action == GOSSIP_ACTION_INFO_DEF+2 && player->IsGameMaster()) {
                CAST_AI(npc_harrison_jones::npc_harrison_jonesAI, (me->AI()))->OpenDoorAndStartTimer();
            }
            player->PlayerTalkClass->SendCloseGossip();
            
            return false;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_harrison_jonesAI(creature);
    }
};



#define HARRISON_ENTRY  24358

class ZulAmanGong : public GameObjectScript
{
public:
    ZulAmanGong() : GameObjectScript("go_za_gong")
    {}

    struct ZulAmanGongAI : public GameObjectAI
    {
        ZulAmanGongAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (me->HasFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED))
                return false;
            else {
                if (Creature* harrisonJones = me->FindNearestCreature(HARRISON_ENTRY, 15.0f, true)) {
                    if (CAST_AI(npc_harrison_jones::npc_harrison_jonesAI, (harrisonJones->AI()))->IncreaseClick(pPlayer->GetGUID()))
                    {
                        pPlayer->InterruptNonMeleeSpells(true);
                        pPlayer->CastSpell(pPlayer, 45226, TRIGGERED_FULL_MASK);
                        //pPlayer->CastSpell(pPlayer, 44762, TRIGGERED_FULL_MASK);
                        /*if (!pPlayer->HasAuraEffect(45225))
                            pPlayer->AddAura(45225, pPlayer);*/
                    }
                }

                return true;
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ZulAmanGongAI(go);
    }
};

/*######
## npc_amanishi_lookout
######*/


class npc_amanishi_lookout : public CreatureScript
{
public:
    npc_amanishi_lookout() : CreatureScript("npc_amanishi_lookout")
    { }

    class  npc_amanishi_lookoutAI : public ScriptedAI
    {
        public:
        npc_amanishi_lookoutAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        InstanceScript *pInstance;
        
        void Reset()
        override {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            if (pInstance && pInstance->GetData(DATA_GAUNTLET) != DONE)
                pInstance->SetData(DATA_GAUNTLET, NOT_STARTED);
        }
        
        void EnterCombat(Unit *pWho) override {}
        
        void MoveInLineOfSight(Unit *pWho)
        override {
            if (!pInstance)
                return;
                
            if (me->GetDistance(pWho) <= 23.0f) {
                if (pInstance->GetData(DATA_GAUNTLET) == NOT_STARTED) {
                    pInstance->SetData(DATA_GAUNTLET, IN_PROGRESS);
                    me->SetSpeedRate(MOVE_WALK, 5);
                    me->GetMotionMaster()->MovePoint(1, 227.822556, 1402.593384, 37.555401);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    //me->GetMotionMaster()->MovePoint(0, 228.332535, 1435.903687, 26.650408);
                }
            }
        }
        
        void MovementInform(uint32 type, uint32 id)
        override {
            if (id == 0) {
                me->GetMotionMaster()->MovementExpired();
                me->GetMotionMaster()->MovePoint(1, 227.822556, 1402.593384, 37.555401);
            }
            else if (id == 1) {
                me->GetMotionMaster()->MovementExpired();
                me->DespawnOrUnsummon(1); //despawn at next update, otherwise may cause crash when deleting waypoint movement generator immediately (this function is called from there)
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_amanishi_lookoutAI(creature);
    }
};


/*######
## npc_amanishi_tempest
######*/

#define SPELL_THUNDERCLAP   44033


class npc_amanishi_tempest : public CreatureScript
{
public:
    npc_amanishi_tempest() : CreatureScript("npc_amanishi_tempest")
    { }

    class  npc_amanishi_tempestAI : public ScriptedAI
    {
        public:
        npc_amanishi_tempestAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        InstanceScript *pInstance;
        uint32 thunderclapTimer;
        
        void Reset()
        override {
            thunderclapTimer = 3000;
        }
        
        void EnterCombat(Unit *pWho)
        override {
            if (pInstance && pInstance->GetData(DATA_GAUNTLET) == IN_PROGRESS)
                pInstance->SetData(DATA_GAUNTLET, DONE);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            if (thunderclapTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_THUNDERCLAP);
                thunderclapTimer = 8000;
            }
            else
                thunderclapTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_amanishi_tempestAI(creature);
    }
};


/*######
## npc_amanishi_berserker
######*/

#define SPELL_MIGHTY_BLOW       43673
#define SPELL_FRENZY            28747


class npc_amanishi_berserker : public CreatureScript
{
public:
    npc_amanishi_berserker() : CreatureScript("npc_amanishi_berserker")
    { }

    class  npc_amanishi_berserkerAI : public ScriptedAI
    {
        public:
        npc_amanishi_berserkerAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 MightyBlowTimer;
        
        void Reset() override {
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
            MightyBlowTimer = 5000;
        }
        
        void EnterCombat(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff) override {
            if (!UpdateVictim())
                return;
                
            if (MightyBlowTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_MIGHTY_BLOW, true);
                MightyBlowTimer = 12000;
            } else MightyBlowTimer -= diff;
            
            if (me->GetHealth() <= me->GetMaxHealth()/5.0f) {   // Cast Frenzy at 20% health
                if (!me->HasAuraEffect(SPELL_FRENZY))
                    DoCast(me, SPELL_FRENZY, true);
            }
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_amanishi_berserkerAI(creature);
    }
};


/*######
## npc_amanishi_scout
######*/

enum eAmanishiScout
{
    SPELL_ALERT_DRUMS       = 42177,
    SPELL_MULTI_SHOOT       = 43205,
    SPELL_SHOOT             = 16496,
    GO_AMANI_DRUM           = 186865
};


class npc_amanishi_scout : public CreatureScript
{
public:
    npc_amanishi_scout() : CreatureScript("npc_amanishi_scout")
    { }

    class npc_amanishi_scoutAI : public ScriptedAI
    {
        public:
        npc_amanishi_scoutAI(Creature *c) : ScriptedAI(c) {}
        
        uint32 shootTimer;
        uint32 multiShootTimer;
        
        bool hasRunToDrum;
        
        void Reset()
        override {
            shootTimer = 2000;
            multiShootTimer = 6000;
            
            hasRunToDrum = false;
        }
        
        void EnterCombat(Unit *pWho)
        override {
            if (GameObject *amaniDrum = me->FindNearestGameObject(GO_AMANI_DRUM, 50.0f))
                me->GetMotionMaster()->MovePoint(0, amaniDrum->GetPositionX(), amaniDrum->GetPositionY(), amaniDrum->GetPositionZ());
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            // Check here if we're close from the drum
            
            if (shootTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_SHOOT);
                shootTimer = 4000+rand()%1000;
            }
            else
                shootTimer -= diff;
                
            if (multiShootTimer <= diff) {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_MULTI_SHOOT);
                multiShootTimer = 20000+rand()%4000;
            }
            else
                multiShootTimer -= diff;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_amanishi_scoutAI(creature);
    }
};


class ATQuestXMarks : AreaTriggerScript
{
public:
    ATQuestXMarks() : AreaTriggerScript("at_quest_X_marks") {}

    bool OnTrigger(Player *pPlayer, AreaTriggerEntry const *pAt) override
    {
        if (pPlayer->GetQuestStatus(11166) != QUEST_STATUS_INCOMPLETE)
            return false;

        uint32 cEntry = 0;
        switch (pAt->id) {
        case 4726:
            cEntry = 23815;
            break;
        case 4724:
            cEntry = 23813;
            break;
        case 4725:
            cEntry = 23814;
            break;
        default:
            TC_LOG_ERROR("scripts", "Scriptname at_quest_X_marks assigned to wrong AreaTrigger!");
            break;
        }

        pPlayer->KilledMonsterCredit(cEntry, 0);

        return true;
    }
};

/*######
## mob_akilzon_gauntlet
######*/


class mob_akilzon_gauntlet : public CreatureScript
{
public:
    mob_akilzon_gauntlet() : CreatureScript("mob_akilzon_gauntlet")
    { }

    class mob_akilzon_gauntletAI : public ScriptedAI
    {
        public:
        mob_akilzon_gauntletAI(Creature* c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        InstanceScript* pInstance;
        
        void EnterCombat(Unit* pWho) override {}
        
        void MovementInform(uint32 type, uint32 id)
        override {
            if (me->GetEntry() == 24225 && id == 6)
                me->DespawnOrUnsummon(1); //despawn at next update, otherwise may cause crash when deleting waypoint movement generator immediately (this function is called from there)
            else if (me->GetEntry() == 24159 && id == 7)
                me->DespawnOrUnsummon(1);
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;
                
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_akilzon_gauntletAI(creature);
    }
};


void AddSC_zulaman()
{

    new npc_forest_frog();

    new npc_zulaman_hostage();
    
    new npc_harrison_jones();
    
    new ZulAmanGong();
    
    new npc_amanishi_lookout();
    
    new npc_amanishi_tempest();
    
    new npc_amanishi_berserker();
    
    new npc_amanishi_scout();
    
    new ATQuestXMarks();
    
    new mob_akilzon_gauntlet();
}

