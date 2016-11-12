/* Copyright (C) 2006 - 2008 WoWMania Core <https://scriptdev2.svn.sourceforge.net/>
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

// TODO : This won't work for multiple npc's (they'll conflift with each other)

/* ScriptData
SDName: npc_zone_silence
SD%Complete: 100
SDComment: Custom NPC acting like a totem silencing nearby players
SDCategory: Custom
EndScriptData */


 
#define SPELL_SILENCE 42201 //can only be cast on self
 
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
            if (who->GetDistance(me) < 30 ) {
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
