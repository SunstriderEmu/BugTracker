/*
* Copyright (C) 2008-2009 Trinity <http://www.trinitycore.org/>
*
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


#include "def_blackfathom_deeps.h"

enum Spells
{
    SPELL_NET                                              = 6533
};

struct boss_gelihastAI : public ScriptedAI
{
    boss_gelihastAI(Creature* c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }

    uint32 uiNetTimer;

    InstanceScript *pInstance;

    void Reset()
    override {
        uiNetTimer = urand(2000,4000);
        if (pInstance)
            pInstance->SetData(TYPE_GELIHAST, NOT_STARTED);
    }

    void EnterCombat(Unit* pWho)
    override {
        if (pInstance)
            pInstance->SetData(TYPE_GELIHAST, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    override {
        if (pInstance)
            pInstance->SetData(TYPE_GELIHAST, DONE);
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        if (uiNetTimer < diff)
        {
            if (me->GetVictim())
                DoCast(me->GetVictim(), SPELL_NET);
            uiNetTimer = urand(4000,7000);
        } else uiNetTimer -= diff;
        
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_gelihast(Creature* pCreature)
{
    return new boss_gelihastAI(pCreature);
}

void AddSC_boss_gelihast()
{
    OLDScript* newscript;

    newscript = new OLDScript;
    newscript->Name = "boss_gelihast";
    newscript->GetAI = &GetAI_boss_gelihast;
    sScriptMgr->RegisterOLDScript(newscript);
}
