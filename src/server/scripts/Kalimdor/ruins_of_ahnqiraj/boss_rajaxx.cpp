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
SDName: Boss_Rajaxx
SD%Complete: 0
SDComment: Place Holder
SDCategory: Ruins of Ahn'Qiraj
EndScriptData */


#include "def_ruins_of_ahnqiraj.h"

/* WOWWIKI

Wave 1: Center -

    Captain Qeez - Intimidating Shout.
    Swarmguard Needler x2 - Qiraji Warrior x4 

Wave 2: Left side -

    Captain Tuubid - Marks a person with "Attack Order" debuff that causes the mobs to aggro that person.
    Swarmguard Needler x3 - Qiraji Warrior x3 

Wave 3: Right side -

    Captain Drenn - AoE lightning spell (Hurricane).
    Swarmguard Needler x5 - Qiraji Warrior x1 

Wave 4: Further left -

    Captain Xurrem - Shockwave (AOE knockdown).
    Swarmguard Needler x3 - Qiraji Warrior x3 

Wave 5: Further right -

    Major Yeggeth - Blessing of Protection, 900 damage cleave (against tank).
    Swarmguard Needler x4 - Qiraji Warrior x2 

Wave 6: Deep left side -

    Major Pakkon - Sweeping Slam.
    Swarmguard Needler x2 - Qiraji Warrior x4 

Wave 7: Deep right side -

    Colonel Zerran - Magic-dispellable enlarge on him self and the Swarmguards / Warriors causing more melee damage.
    Swarmguard Needler x3 - Qiraji Warrior x3 

General Rajaxx - Has two important abilities worth noting here:

    AoE Thunder Clap that cuts everyone's hitpoints in half (200 minimum damage) and wipes aggro.
    A single target deaggro, where he yells "You are not worth my time, <target>." and changes to a new target. 

*/

enum Yells
{
    SAY_ANDOROV_INTRO         = -1509003,
    SAY_ANDOROV_ATTACK        = -1509004,
    SAY_WAVE3                 = -1509005,
    SAY_WAVE4                 = -1509006,
    SAY_WAVE5                 = -1509007,
    SAY_WAVE6                 = -1509008,
    SAY_WAVE7                 = -1509009,
    SAY_INTRO                 = -1509010,
    SAY_UNK1                  = -1509011,
    SAY_UNK2                  = -1509012,
    SAY_UNK3                  = -1509013,
    SAY_UNK4                  = -1509014,
    SAY_DEAGGRO               = -1509015,
    SAY_KILLS_ANDOROV         = -1509016,
    SAY_COMPLETE_QUEST        = -1509017                        //Yell when realm complete quest 8743 for world event
};

enum Creatures
{
    // Raid allies
    NPC_ANDOROV             = 15471,
    NPC_KALDOREI_ELITE      = 15473,
    
    // Regular mobs
    NPC_SWARMGUARD_NEEDLER  = 15344,
    NPC_QIRAJI_WARRIOR      = 15387,
    
    // Captains
    NPC_CAPTAIN_QEEZ        = 15391, // Wave 1
    NPC_CAPTAIN_TUUBID      = 15392, // Wave 2
    NPC_CAPTAIN_DRENN       = 15389, // Wave 3
    NPC_CAPTAIN_XURREM      = 15390, // Wave 4
    NPC_MAJOR_YEGGETH       = 15386, // Wave 5
    NPC_MAJOR_PAKKON        = 15388, // Wave 6
    NPC_COLONEL_ZERRAN      = 15385, // Wave 7
    NPC_GENERAL_RAJAXX      = 15341  // Wave 8
};

class Boss_Rajaxx : public CreatureScript
{
public:
    Boss_Rajaxx() : CreatureScript("rajaxx"){}
    
    class Boss_RajaxxAI : public ScriptedAI
    {
    public:
        Boss_RajaxxAI(Creature* creature) : ScriptedAI (creature)
        {
            instance = ((InstanceScript*)creature->GetInstanceScript());
        }
        
        EventMap events;

        enum Talks
        {
            TALK_AGGRO=0,
            TALK_CHANGE_TARGET=1,
            TALK_DEATH=2,
        };
        
        enum Event
        {
            EV_THUNDER_CLAP=1,
        };
        enum Spells
        {
            SPELL_THUNDER_CLAP=25599,
        };
        
        void JustEngagedWith(Unit* victim)
        override {
            Talk(TALK_AGGRO);
            if (instance)
                instance->SetData(DATA_RAJAXX_EVENT, IN_PROGRESS);            
        }
        
        void UpdateAI(uint32 const diff)
        override {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            switch (events.GetEvent())
            {
                case 0:
                    break;
                case EV_THUNDER_CLAP:
                    if (me->CastSpell(me->GetVictim(), SPELL_THUNDER_CLAP) == SPELL_CAST_OK)
                    {
                        Talk(TALK_CHANGE_TARGET, me->GetVictim());
                        ResetThreatList();
                        events.RescheduleEvent(EV_THUNDER_CLAP, urand(25000, 35000));
                    }
                    break;
            }
            
        }
        void Reset ()
        override {
            events.RescheduleEvent(EV_THUNDER_CLAP, urand(25000, 35000));
                
            if (instance)
                instance->SetData(DATA_RAJAXX_EVENT, NOT_STARTED);
        }
        
        void JustDied(Unit* killer)
        override {
            Talk(TALK_DEATH);
        }
    
    private:
        InstanceScript* instance;
    };
    
    CreatureAI* GetAI(Creature* creature) const
    override {
        return new Boss_RajaxxAI(creature);
    }
};

void AddSC_boss_rajaxx()
{
    new Boss_Rajaxx();
}
