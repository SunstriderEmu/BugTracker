/* ScriptData
SDName: Durotar
SD%Complete: 100
SDComment: Quest support: 5441
SDCategory: Durotar
EndScriptData */

/* ContentData
npc_lazy_peon
EndContentData */



/*######
## npc_lazy_peon
######*/

enum LazyPeonYells
{
    SAY_SPELL_HIT                               = -1645010   //Ow! OK, I''ll get back to work, $N!'
};

enum LazyPeon
{
    GO_LUMBERPILE                               = 175784,

    SPELL_BUFF_SLEEP                            = 17743,
    SPELL_AWAKEN_PEON                           = 19938
};

struct npc_lazy_peonAI : public ScriptedAI
{
    npc_lazy_peonAI(Creature *c) : ScriptedAI(c) {}

    uint32 m_uiRebuffTimer;
    uint32 m_homeTimer;
    uint32 workTimer;
    
    uint8 workCount;
    
    bool work;

    void Reset ()
    override {
        work = false;
        m_uiRebuffTimer = 0;
        workCount = 0;
    }

    void MovementInform(uint32, uint32 id)
    override {
        if (id == 0) {
            if (!me->HasAuraEffect(SPELL_BUFF_SLEEP))
                DoCast(me, SPELL_BUFF_SLEEP);
            workCount = 0;
        }
        else if (id == 1) {
            work = true;
            m_homeTimer = 10000;
            workTimer = 1000;
        }
    }
    
    void EnterCombat(Unit* pWho) override {}

    void SpellHit(Unit *caster, const SpellInfo *spell)
    override {
        if (spell->Id == SPELL_AWAKEN_PEON && caster->GetTypeId() == TYPEID_PLAYER
            && (caster)->ToPlayer()->GetQuestStatus(5441) == QUEST_STATUS_INCOMPLETE)
        {
            (caster->ToPlayer())->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
            DoScriptText(SAY_SPELL_HIT, me, caster);
            me->RemoveAllAuras();
            me->SetSheath(SHEATH_STATE_MELEE);
            GameObject* Lumberpile = me->FindNearestGameObject(GO_LUMBERPILE, 20);
            if(Lumberpile)
                me->GetMotionMaster()->MovePoint(1, Lumberpile->GetPositionX()-1, Lumberpile->GetPositionY(), Lumberpile->GetPositionZ());
        }
    }

    void UpdateAI(const uint32 uiDiff)
    override {
        if (work) {
            if (workTimer <= uiDiff) {
                me->HandleEmoteCommand(EMOTE_STATE_WORK_NO_SHEATHE);
                workCount++;
                workTimer = 1000;
            }
            else
                workTimer -= uiDiff;
                
            if (workCount == 5)
                work = false;
        }
        
        if (m_uiRebuffTimer <= uiDiff)
        {
            DoCast(me, SPELL_BUFF_SLEEP);
            m_uiRebuffTimer = 90000;
        }
        else
            m_uiRebuffTimer -= uiDiff;
            
        if (m_homeTimer) {
            if (m_homeTimer <= uiDiff) {
                float x, y, z, o;
                me->SetSheath(SHEATH_STATE_UNARMED);
                me->GetHomePosition(x, y, z, o);
                me->GetMotionMaster()->MovePoint(0, x, y, z);
                m_homeTimer = 0;
            }
            else
                m_homeTimer -= uiDiff;
        }
            
        if (!UpdateVictim())
            return;
            
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_lazy_peon(Creature* pCreature)
{
    return new npc_lazy_peonAI(pCreature);
}

void AddSC_durotar()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name = "npc_lazy_peon";
    newscript->GetAI = &GetAI_npc_lazy_peon;
    sScriptMgr->RegisterOLDScript(newscript);
}
