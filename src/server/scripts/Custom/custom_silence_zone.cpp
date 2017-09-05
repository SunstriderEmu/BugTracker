
/* TODO : This won't work with multiple npc's (they'll conflift with each other)
*/

/* 
npc_zone_silence
Custom NPC acting like a totem silencing nearby players
 */

 
#define SPELL_SILENCE 42201 //can only be cast on self
#define SILENCE_RANGE 30.0f
 
 
class npc_zone_silence : public CreatureScript
{
public:
    npc_zone_silence() : CreatureScript("npc_zone_silence")
    { }

    class npc_zonedesilenceAI : public ScriptedAI
    {
        public:
        npc_zonedesilenceAI(Creature *c) : ScriptedAI(c)
        {
    		me->SetVisible(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            SetCombatMovementAllowed(false);
        }
     
        void MoveInLineOfSight2(Unit *who)
        override {
            if (who->GetTypeId() == TYPEID_PLAYER) {
                if (who->GetDistance(me) < SILENCE_RANGE ) {
                    if(!who->HasAuraEffect(SPELL_SILENCE, 0) && who->IsAlive())
                        who->AddAura(SPELL_SILENCE, who); //not a cast, else rendement décroissant qui s'applique
                }
                else if(who->HasAuraEffect(SPELL_SILENCE, 0)) {
                    who->RemoveAurasDueToSpell(SPELL_SILENCE);
                }
            }
        }
        
        void EnterCombat(Unit* who) override {}
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_zonedesilenceAI(creature);
    }
};

 
void AddSC_zone_silence()
{
 
    new npc_zone_silence();
}
