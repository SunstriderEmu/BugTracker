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


#include "def_razorfen_downs.h"

enum Spells
{
    SPELL_SHADOW_BOLT           = 12471,
    SPELL_SHADOW_WORD           = 11639,
    SPELL_DOMINATE_MIND         = 7645,
    SPELL_HEAL                  = 12039,
};

struct boss_ragglesnoutAI : public ScriptedAI
{
    boss_ragglesnoutAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((InstanceScript*)c->GetInstanceScript());
    }

    InstanceScript *pInstance;
    uint32 phase;
    uint32 shadowboltTimer;
    uint32 eventTimer;
    uint32 perc;
    uint32 phase2Timer;
    uint32 shadowwordTimer;
    uint32 dominatemindTimer;
    uint32 healTimer;
    bool action1Reapeat;
    bool action2Reapeat;
    bool action3Reapeat;
    bool action4Reapeat;

    void Reset()
    override {
        phase = 0;
        shadowboltTimer = urand(2400, 3800);
        eventTimer = 500;
        perc = 0;
        phase2Timer = 100;
        shadowwordTimer = urand(3000, 5000);
        dominatemindTimer = urand(9000, 13000);
        healTimer = urand(12000, 16000);
        action1Reapeat = false;
        action2Reapeat = false;
        action3Reapeat = false;
        action4Reapeat = false;

        me->GetMotionMaster()->Clear();
        me->GetMotionMaster()->MoveIdle();

        if (pInstance && pInstance->GetData(DATA_RAGGLESNOUT_EVENT) != DONE)
            pInstance->SetData(DATA_RAGGLESNOUT_EVENT, NOT_STARTED);
    }

    void EnterCombat(Unit *who)
    override {
        if (pInstance)
            pInstance->SetData(DATA_RAGGLESNOUT_EVENT, IN_PROGRESS);

        DoCast(who, SPELL_SHADOW_BOLT);
        
        phase = 1;
    }
    
    void JustDied(Unit *killer)
    override {
        if (pInstance)
            pInstance->SetData(DATA_RAGGLESNOUT_EVENT, DONE);
    }

    void UpdateAI(const uint32 diff)
    override {
        if (!UpdateVictim())
            return;

        if (eventTimer <= diff)
        {
            if (shadowwordTimer <= diff)
            {
                me->InterruptNonMeleeSpells(false);
                DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_SHADOW_WORD);
                shadowwordTimer = urand(20000, 25000);
            }
            else
                shadowwordTimer -= diff;

            if (dominatemindTimer <= diff)
            {
                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0, true, true))
                    if(DoCast(target,SPELL_DOMINATE_MIND) == SPELL_CAST_OK)
                        dominatemindTimer = urand(15000, 20000);
            }
            else
                dominatemindTimer -= diff;

            if (healTimer <= diff)
            {
                Unit* pUnit = DoSelectLowestHpFriendly(3000, 40);
                if (pUnit)
                    DoCast(pUnit, SPELL_HEAL);
                
                healTimer = urand(12000, 16000);
            }
            else
                healTimer -= diff;

            switch (phase)
            {
                case 1:
                    if (shadowboltTimer <= diff)
                    {
                        if (me->IsWithinDistInMap(me->GetVictim(), 40.0f))
                        {
                            if (me->GetDistance(me->GetVictim()) >= 0.0f)
                                DoCast(me->GetVictim(), SPELL_SHADOW_BOLT);
                        }
                        shadowboltTimer = urand(2400, 3800);
                    }
                    else
                        shadowboltTimer -= diff;
                        
                    if (me->IsWithinDistInMap(me->GetVictim(), 80.0f))
                    {
                        if (me->GetDistance(me->GetVictim()) >= 35.0f)
                        {
                            if (!action2Reapeat)
                            {
                                me->GetMotionMaster()->Clear();
                                me->GetMotionMaster()->MoveChase(me->GetVictim(), 0.0f, 0.0f);
                                action2Reapeat = true;
                            }
                        }
                    }
                    
                    if (me->IsWithinDistInMap(me->GetVictim(), 15.0f))
                    {
                        if (me->GetDistance(me->GetVictim()) >= 5.0f)
                        {
                            if (!action3Reapeat)
                            {
                                me->GetMotionMaster()->Clear();
                                me->GetMotionMaster()->MoveIdle();
                                action3Reapeat = true;
                            }
                        }
                    }
                    
                    if (me->IsWithinDistInMap(me->GetVictim(), 5.0f))
                    {
                        if (me->GetDistance(me->GetVictim()) >= 0.0f)
                        {
                            if (!action4Reapeat)
                            {
                                me->GetMotionMaster()->Clear();
                                me->GetMotionMaster()->MoveChase(me->GetVictim(), 0.0f, 0.0f);
                                action4Reapeat = true;
                            }
                        }
                    }
                    
                    perc = (me->GetPower(POWER_MANA)*100) / me->GetMaxPower(POWER_MANA);
                    if(me->GetHealthPct() < 15.0f)
                    {
                        if (!action1Reapeat)
                        {
                            action1Reapeat = true;
                            phase = 2;
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MoveChase(me->GetVictim(), 0.0f, 0.0f);
                        }
                    }

                    break;
                case 2:
                if (phase2Timer <= diff)
                {
                    perc = (me->GetPower(POWER_MANA)*100) / me->GetMaxPower(POWER_MANA);
                    if (perc <= 100 && perc >= 30)
                        phase = 1;
                        
                    phase2Timer = 100;
                }
                else
                    phase2Timer -= diff;
            }
            eventTimer = 500;
        }
        else
            eventTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_ragglesnout(Creature *_Creature)
{
    return new boss_ragglesnoutAI (_Creature);
}

void AddSC_boss_ragglesnout()
{
    OLDScript *newscript;
    newscript = new OLDScript;
    newscript->Name="boss_ragglesnout";
    newscript->GetAI = &GetAI_boss_ragglesnout;
    sScriptMgr->RegisterOLDScript(newscript);
}
