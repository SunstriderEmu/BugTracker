struct theinformAI : public ScriptedAI
{
    theinformAI(Creature *c) : ScriptedAI(c) 
    {}

    void DamageTaken(Unit* who, uint32& damage) 
    override {
        RandomizeDisplayID();
        damage = 0;
    }

    void RandomizeDisplayID()
    {
        me->SetDisplayId(urand(4,25958));
    }

    void EnterCombat(Unit* /* who */) override {}
};

CreatureAI* GetAI_theinform(Creature *_Creature)
{
    return new theinformAI (_Creature);
}
 
void AddSC_theinform()
{
    OLDScript *newscript; 
 
    newscript = new OLDScript;
    newscript->Name="custom_theinform";
    newscript->GetAI = &GetAI_theinform;
    sScriptMgr->RegisterOLDScript(newscript);
}
