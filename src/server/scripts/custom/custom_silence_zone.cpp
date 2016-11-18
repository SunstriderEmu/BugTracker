
/* TODO : This won't work with multiple npc's (they'll conflift with each other)
*/

/* ScriptData
SDName: npc_zone_silence
SD%Complete: 100
SDComment: Custom NPC acting like a totem silencing nearby players
SDCategory: Custom
EndScriptData */

 
#define SPELL_SILENCE 42201 //can only be cast on self
#define SILENCE_RANGE 30.0f
 
struct npc_zonedesilenceAI : public ScriptedAI
{
    npc_zonedesilenceAI(Creature *c) : ScriptedAI(c)
    {
        me->SetVisibility(VISIBILITY_OFF);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        SetCombatMovementAllowed(false);
    }
 
    void MoveInLineOfSight2(Unit *who)
    override {
        if (who->GetTypeId() == TYPEID_PLAYER) {
            if (who->GetDistance(me) < SILENCE_RANGE ) {
                if(!who->HasAuraEffect(SPELL_SILENCE, 0) && who->IsAlive())
                    who->AddAura(SPELL_SILENCE, who); //pas un cast sinon rendement décroissant qui s'applique
            }
            else if(who->HasAuraEffect(SPELL_SILENCE, 0)) {
                who->RemoveAurasDueToSpell(SPELL_SILENCE);
            }
        }
    }
    
    void EnterCombat(Unit* who) override {}
};
 
CreatureAI* GetAI_npc_zonedesilence(Creature *_Creature)
{
    return new npc_zonedesilenceAI (_Creature);
}
 
void AddSC_zone_silence()
{
    OLDScript *newscript;
 
    newscript = new OLDScript;
    newscript->Name="npc_zone_silence";
    newscript->GetAI = &GetAI_npc_zonedesilence;
    sScriptMgr->RegisterOLDScript(newscript);
}
