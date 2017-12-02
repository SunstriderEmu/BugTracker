
/* ScriptData
SDName: Dark_Portal
SD%Complete: 30
SDComment: Misc NPC's and mobs for instance. Most here far from complete.
SDCategory: Caverns of Time, The Dark Portal
EndScriptData */

/* ContentData
npc_medivh_bm
npc_time_rift
npc_saat
npc_time_keeper
EndContentData */


#include "def_dark_portal.h"

enum Says
{
SAY_ENTER               =   -1269020,                   //where does this belong?
SAY_INTRO               =   -1269021,
SAY_WEAK75              =   -1269022,
SAY_WEAK50              =   -1269023,
SAY_WEAK25              =   -1269024,
SAY_DEATH               =   -1269025,
SAY_WIN                 =   -1269026,
SAY_ORCS_ENTER          =   -1269027,
SAY_ORCS_ANSWER         =   -1269028
};

enum Spells
{
SPELL_CHANNEL           =   31556,
SPELL_PORTAL_RUNE       =   32570,                      //aura(portal on ground effect)
SPELL_BLACK_CRYSTAL     =   32563,                      //aura
SPELL_PORTAL_CRYSTAL    =   32564,                      //summon
SPELL_BANISH_PURPLE     =   32566,                      //aura
SPELL_BANISH_GREEN      =   32567,                      //aura
SPELL_CORRUPT           =   31326,
SPELL_CORRUPT_AEONUS    =   37853
};

enum NPCs
{
C_COUNCIL_ENFORCER      =   17023
};


class npc_medivh_bm : public CreatureScript
{
public:
    npc_medivh_bm() : CreatureScript("npc_medivh_bm")
    { }

    class npc_medivh_bmAI : public ScriptedAI
    {
        public:
        npc_medivh_bmAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        uint32 SpellCorrupt_Timer;
        uint32 Check_Timer;
    
        bool Life75;
        bool Life50;
        bool Life25;
    
        void Reset()
        override {
            SpellCorrupt_Timer = 0;
    
            if (!pInstance)
                return;
    
            if (pInstance->GetData(TYPE_MEDIVH) == IN_PROGRESS)
                me->CastSpell(me,SPELL_CHANNEL, TRIGGERED_FULL_MASK);
            else if (me->HasAuraEffect(SPELL_CHANNEL,0))
                me->RemoveAura(SPELL_CHANNEL,0);
    
            me->CastSpell(me,SPELL_PORTAL_RUNE, TRIGGERED_FULL_MASK);
        }
    
        void MoveInLineOfSight(Unit *who)
        override {
            if (!pInstance)
                return;
                
            if (pInstance->GetData(TYPE_MEDIVH) == DONE)
                return;
    
            if (who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 10.0f))
            {
                if (pInstance->GetData(TYPE_MEDIVH) == IN_PROGRESS)
                    return;
    
                DoScriptText(SAY_INTRO, me);
                pInstance->SetData(TYPE_MEDIVH,IN_PROGRESS);
                me->CastSpell(me,SPELL_CHANNEL, TRIGGERED_NONE);
                Check_Timer = 5000;
            }
            else if (who->GetTypeId() == TYPEID_UNIT && me->IsWithinDistInMap(who, 15.0f))
            {
                if (pInstance->GetData(TYPE_MEDIVH) != IN_PROGRESS)
                    return;
    
                uint32 entry = who->GetEntry();
                if (entry == C_ASSAS || entry == C_WHELP || entry == C_CHRON || entry == C_EXECU || entry == C_VANQU)
                {
                    who->StopMoving();
                    who->CastSpell(me,SPELL_CORRUPT, TRIGGERED_NONE);
                }
                else if (entry == C_AEONUS)
                {
                    who->StopMoving();
                    who->CastSpell(me,SPELL_CORRUPT_AEONUS, TRIGGERED_NONE);
                }
            }
        }
    
        void AttackStart(Unit *who)
        override {
            //if (pInstance && pInstance->GetData(TYPE_MEDIVH) == IN_PROGRESS)
            //return;
    
            //ScriptedAI::AttackStart(who);
        }
    
        void EnterCombat(Unit *who) override {}
    
        void SpellHit(Unit* caster, const SpellInfo* spell)
        override {
            if (SpellCorrupt_Timer)
                return;
    
            if (spell->Id == SPELL_CORRUPT_AEONUS)
                SpellCorrupt_Timer = 1000;
    
            if (spell->Id == SPELL_CORRUPT)
                SpellCorrupt_Timer = 3000;
        }
    
        void JustDied(Unit* Killer)
        override {
            if (Killer->GetEntry() == me->GetEntry())
                return;
    
            DoScriptText(SAY_DEATH, me);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!pInstance)
                return;
                
            if (pInstance->GetData(TYPE_MEDIVH) == DONE)
                return;
    
            if (SpellCorrupt_Timer)
            {
                if (SpellCorrupt_Timer < diff)
                {
                        pInstance->SetData(TYPE_MEDIVH,SPECIAL);
    
                    if (me->HasAuraEffect(SPELL_CORRUPT_AEONUS,0))
                        SpellCorrupt_Timer = 1000;
                    else if (me->HasAuraEffect(SPELL_CORRUPT,0))
                        SpellCorrupt_Timer = 3000;
                    else
                        SpellCorrupt_Timer = 0;
                }else SpellCorrupt_Timer -= diff;
            }
    
            if (Check_Timer)
            {
                if (Check_Timer <= diff)
                {
                    /*if (!pInstance->GetData64(TYPE_GET_PLAYER)) {
                        Check_Timer = 0;
                        return;
                    }*/
                    
                    uint32 pct = pInstance->GetData(DATA_SHIELD);
                    
                    //check if DATA_SHIELD needs to be updated
                    Unit *temp = ObjectAccessor::GetUnit(*me,pInstance->GetData64(DATA_MEDIVH));
                    if (temp)
                    {
                        uint32 currentHealth = temp->GetHealth();
                        //I decided (arbitrarily) that 1 shield percent == 25000 damage. Then, apply a formula on the
                        //6 millions HP of Medivh to get a shield percent value
                        float currentHealthInShieldPercent = currentHealth / (2.42816f*25000);
                        
                        if (floor(currentHealthInShieldPercent) < pct) //current value is under stored value
                            pInstance->SetData(TYPE_MEDIVH,SPECIAL);
                    }
    
                    Check_Timer = 5000;
    
                    if (Life25 && pct <= 25)
                    {
                        DoScriptText(SAY_WEAK25, me);
                        Life25 = false;
                        Check_Timer = 0;
                    }
                    else if (Life50 && pct <= 50)
                    {
                        DoScriptText(SAY_WEAK50, me);
                        Life50 = false;
                    }
                    else if (Life75 && pct <= 75)
                    {
                        DoScriptText(SAY_WEAK75, me);
                        Life75 = false;
                    }
    
                    //if we reach this it means event was running but at some point reset.
                    if (pInstance->GetData(TYPE_MEDIVH) == NOT_STARTED)
                    {
                        me->DespawnOrUnsummon();
                        me->Respawn();
                        Check_Timer = 0;
                        return;
                    }
    
                    if (pInstance->GetData(TYPE_RIFT) == DONE)
                    {
                        DoScriptText(SAY_WIN, me);
                        Check_Timer = 0;
                        
                        if (me->HasAuraEffect(SPELL_CHANNEL,0))
                            me->RemoveAura(SPELL_CHANNEL,0);
                            
                        //TODO: start the post-event here
                        pInstance->SetData(TYPE_MEDIVH, DONE);
                    }
                }else Check_Timer -= diff;
            }
    
            //if (!UpdateVictim())
            //return;
    
            //DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_medivh_bmAI(creature);
    }
};


struct Wave
{
    uint32 PortalMob[4];                                    //spawns for portal waves (in order)
};

static Wave PortalWaves[]=
{
    {C_ASSAS, C_WHELP, C_CHRON, 0},
    {C_EXECU, C_CHRON, C_WHELP, C_ASSAS},
    {C_EXECU, C_VANQU, C_CHRON, C_ASSAS}
};


class npc_time_rift : public CreatureScript
{
public:
    npc_time_rift() : CreatureScript("npc_time_rift")
    { }

    class npc_time_riftAI : public ScriptedAI
    {
        public:
        npc_time_riftAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        uint32 TimeRiftWave_Timer;
        uint8 mRiftWaveCount;
        uint8 mPortalCount;
        uint8 mWaveId;
    
        void Reset()
        override {
    
            TimeRiftWave_Timer = 15000;
            mRiftWaveCount = 0;
    
            if (!pInstance)
                return;
    
            mPortalCount = pInstance->GetData(DATA_PORTAL_COUNT);
    
            if (mPortalCount < 6)
                mWaveId = 0;
            else if (mPortalCount > 12)
                mWaveId = 2;
            else mWaveId = 1;
    
        }
    
        void DoSummonAtRift(uint32 creature_entry)
        {
            if (!creature_entry)
                return;
    
            if (pInstance->GetData(TYPE_MEDIVH) != IN_PROGRESS)
            {
                me->InterruptNonMeleeSpells(true);
                me->RemoveAllAuras();
                return;
            }
    
            float x,y,z;
            me->GetRandomPoint(me,10.0f,x,y,z);
    
            //normalize Z-level if we can, if rift is not at ground level.
            z = std::max(me->GetMap()->GetHeight(x, y, MAX_HEIGHT), me->GetMap()->GetWaterLevel(x, y));
    
            Unit *Summon = me->SummonCreature(creature_entry,x,y,z,me->GetOrientation(),
                TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,30000);
    
            if (Summon)
            {
                if (Unit *temp = ObjectAccessor::GetUnit(*me,pInstance->GetData64(DATA_MEDIVH)))
                {
                    Summon->GetThreatManager().AddThreat(temp,0.0f);
                    (Summon->ToCreature())->AI()->AttackStart(temp); //force them to attack Medivh
                }
            }
        }
    
        void DoSelectSummon()
        {
            uint32 entry = 0;
    
            if ((mRiftWaveCount > 2 && mWaveId < 1) || mRiftWaveCount > 3)
                mRiftWaveCount = 0;
    
            entry = PortalWaves[mWaveId].PortalMob[mRiftWaveCount];
    
            ++mRiftWaveCount;
            
            if (pInstance->GetData(DATA_INSTANCE_BOSS) == IN_PROGRESS)      // Don't spawn anything from portal is boss is in progress
                entry = 0;
    
            if (entry == C_WHELP)
            {
                for(uint8 i = 0; i < 3; i++)
                    DoSummonAtRift(entry);
            }else DoSummonAtRift(entry);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if (!pInstance)
                return;
                
            if (mRiftWaveCount >= 18)
                return;
                
            if (mRiftWaveCount == 18)
                pInstance->SetData(TYPE_RIFT, DONE);
                
            if (pInstance->GetData(TYPE_MEDIVH) == DONE)
                return;
    
            if (TimeRiftWave_Timer < diff)
            {
                DoSelectSummon();
                TimeRiftWave_Timer = 15000;
            }else TimeRiftWave_Timer -= diff;
    
            if (me->IsNonMeleeSpellCast(false))
                return;
    
            me->SetDeathState(JUST_DIED);
    
            if (pInstance->GetData(TYPE_RIFT) == IN_PROGRESS)
                pInstance->SetData(TYPE_RIFT,SPECIAL);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_time_riftAI(creature);
    }
};


#define SAY_SAAT_WELCOME        -1269019

#define GOSSIP_ITEM_OBTAIN      "[PH] Obtenir Chrono-balise"
#define SPELL_CHRONO_BEACON     34975
#define ITEM_CHRONO_BEACON      24289

class npc_saat : public CreatureScript
{
public:
    npc_saat() : CreatureScript("npc_saat")
    { }

    class npc_saatAI : public ScriptedAI
    {
    public:
        npc_saatAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* pPlayer) override
        {
            if (me->IsQuestGiver())
                pPlayer->PrepareQuestMenu(me->GetGUID());

            if (pPlayer->GetQuestStatus(QUEST_OPENING_PORTAL) == QUEST_STATUS_INCOMPLETE && !pPlayer->HasItemCount(ITEM_CHRONO_BEACON,1))
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_OBTAIN,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(10000,me->GetGUID());
                return true;
            }
            else if (pPlayer->GetQuestRewardStatus(QUEST_OPENING_PORTAL) && !pPlayer->HasItemCount(ITEM_CHRONO_BEACON,1))
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_OBTAIN,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU_TEXTID(10001,me->GetGUID());
                return true;
            }

            pPlayer->SEND_GOSSIP_MENU_TEXTID(10002,me->GetGUID());
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                player->CLOSE_GOSSIP_MENU();
                me->CastSpell(player,SPELL_CHRONO_BEACON, TRIGGERED_NONE);
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_saatAI(creature);
    }
};



/*######
## npc_time_keeper
######*/

#define SPELL_SAND_BREATH   31478


class npc_time_keeper : public CreatureScript
{
public:
    npc_time_keeper() : CreatureScript("npc_time_keeper")
    { }

    class npc_time_keeperAI : public ScriptedAI
    {
        public:
        npc_time_keeperAI(Creature *c) : ScriptedAI(c) {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
        
        InstanceScript *pInstance;
        
        uint32 lifeTimer;
        uint32 sandBreathTimer;
        
        void Reset() override {
            lifeTimer = 30000;
            sandBreathTimer = 10000;
        }
        
        void EnterCombat(Unit *pWho) override {}
        
        void UpdateAI(uint32 const diff) override {
            if (lifeTimer <= diff)
                me->DisappearAndDie();
            else
                lifeTimer -= diff;
                
            if (!UpdateVictim())
                return;
                
            if (sandBreathTimer <= diff) {
                DoCast(me->GetVictim(), SPELL_SAND_BREATH);
                sandBreathTimer = 25000+rand()%10000;
            } else sandBreathTimer -= diff;
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_time_keeperAI(creature);
    }
};


void AddSC_dark_portal()
{

    new npc_medivh_bm();

    new npc_time_rift();

    new npc_saat();
    
    new npc_time_keeper();
}

