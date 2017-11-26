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
SDName: Netherstorm
SD%Complete: 80
SDComment: Quest support: 10337, 10438, 10652 (special flight paths), 10299,10321,10322,10323,10329,10330,10338,10365(Shutting Down Manaforge), 10198, 10191
SDCategory: Netherstorm
EndScriptData */

/* ContentData
npc_manaforge_control_console
go_manaforge_control_console
npc_commander_dawnforge
npc_protectorate_nether_drake
npc_veronia
npc_bessy
npc_maxx_a_million
npc_dr_boom
npc_boom_bot
npc_drijya
EndContentData */


#include "EscortAI.h"
#include "Unit.h"

/*######
## npc_manaforge_control_console
######*/

#define EMOTE_START     -1000296
#define EMOTE_60        -1000297
#define EMOTE_30        -1000298
#define EMOTE_10        -1000299
#define EMOTE_COMPLETE  -1000300
#define EMOTE_ABORT     -1000301

#define ENTRY_BNAAR_C_CONSOLE   20209
#define ENTRY_CORUU_C_CONSOLE   20417
#define ENTRY_DURO_C_CONSOLE    20418
#define ENTRY_ARA_C_CONSOLE     20440

#define ENTRY_SUNFURY_TECH      20218
#define ENTRY_SUNFURY_PROT      20436

#define ENTRY_ARA_TECH          20438
#define ENTRY_ARA_ENGI          20439
#define ENTRY_ARA_GORKLONN      20460

#define SPELL_DISABLE_VISUAL    35031
#define SPELL_INTERRUPT_1       35016                       //ACID mobs should cast this
#define SPELL_INTERRUPT_2       35176                       //ACID mobs should cast this (Manaforge Ara-version)

class npc_manaforge_control_console : public CreatureScript
{
public:
    npc_manaforge_control_console() : CreatureScript("npc_manaforge_control_console")
    { }

    class npc_manaforge_control_consoleAI : public ScriptedAI
    {
        public:
        npc_manaforge_control_consoleAI(Creature *c) : ScriptedAI(c) {}
    
        uint32 Event_Timer;
        uint32 Wave_Timer;
        uint32 Phase;
        bool Wave;
        uint64 someplayer;
        uint64 goConsole;
        Creature* add;
    
        void Reset()
        override {
            Event_Timer = 3000;
            Wave_Timer = 0;
            Phase = 1;
            Wave = false;
            someplayer = 0;
            goConsole = 0;
            add = nullptr;
        }
    
        void EnterCombat(Unit *who) override { return; }
    
        /*void SpellHit(Unit *caster, const SpellInfo *spell)
        {
            //we have no way of telling the creature was hit by spell -> got aura applied after 10-12 seconds
            //then no way for the mobs to actually stop the shutdown as intended.
            if( spell->Id == SPELL_INTERRUPT_1 )
                me->Say("Silence! I kill you!",LANG_UNIVERSAL, NULL);
        }*/
    
        void JustDied(Unit* killer)
        override {
            DoScriptText(EMOTE_ABORT, me);
    
            if( someplayer )
            {
                Player* p = ObjectAccessor::GetPlayer(*me, someplayer);
                if(p)
                {
                    switch( me->GetEntry() )
                    {
                        case ENTRY_BNAAR_C_CONSOLE:
                            p->FailQuest(10299);
                            p->FailQuest(10329);
                            break;
                        case ENTRY_CORUU_C_CONSOLE:
                            p->FailQuest(10321);
                            p->FailQuest(10330);
                            break;
                        case ENTRY_DURO_C_CONSOLE:
                            p->FailQuest(10322);
                            p->FailQuest(10338);
                            break;
                        case ENTRY_ARA_C_CONSOLE:
                            p->FailQuest(10323);
                            p->FailQuest(10365);
                            break;
                    }
                }
            }
    
            if( goConsole )
            {
                if( GameObject* go = GameObject::GetGameObject((*me),goConsole) )
                    go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
            }
        }
    
        void DoWaveSpawnForCreature(Creature *creature)
        {
            switch( creature->GetEntry() )
            {
                case ENTRY_BNAAR_C_CONSOLE:
                    if( rand()%2 )
                    {
                        add = me->SummonCreature(ENTRY_SUNFURY_TECH,2933.68,4162.55,164.00,1.60,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                        if( add ) add->GetMotionMaster()->MovePoint(0,2927.36,4212.97,164.00);
                    }
                    else
                    {
                        add = me->SummonCreature(ENTRY_SUNFURY_TECH,2927.36,4212.97,164.00,4.94,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                        if( add ) add->GetMotionMaster()->MovePoint(0,2933.68,4162.55,164.00);
                    }
                    Wave_Timer = 30000;
                    break;
                case ENTRY_CORUU_C_CONSOLE:
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2445.21,2765.26,134.49,3.93,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2424.21,2740.15,133.81);
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2429.86,2731.85,134.53,1.31,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2435.37,2766.04,133.81);
                    Wave_Timer = 20000;
                    break;
                case ENTRY_DURO_C_CONSOLE:
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2986.80,2205.36,165.37,3.74,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2985.15,2197.32,164.79);
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2952.91,2191.20,165.32,0.22,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2060.01,2185.27,164.67);
                    Wave_Timer = 15000;
                    break;
                case ENTRY_ARA_C_CONSOLE:
                    if( rand()%2 )
                    {
                        add = me->SummonCreature(ENTRY_ARA_TECH,4035.11,4038.97,194.27,2.57,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                        if( add ) add->GetMotionMaster()->MovePoint(0,4003.42,4040.19,193.49);
                        add = me->SummonCreature(ENTRY_ARA_TECH,4033.66,4036.79,194.28,2.57,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                        if( add ) add->GetMotionMaster()->MovePoint(0,4003.42,4040.19,193.49);
                        add = me->SummonCreature(ENTRY_ARA_TECH,4037.13,4037.30,194.23,2.57,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                        if( add ) add->GetMotionMaster()->MovePoint(0,4003.42,4040.19,193.49);
                    }
                    else
                    {
                        add = me->SummonCreature(ENTRY_ARA_TECH,3099.59,4049.30,194.22,0.05,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                        if( add ) add->GetMotionMaster()->MovePoint(0,4028.01,4035.17,193.59);
                        add = me->SummonCreature(ENTRY_ARA_TECH,3999.72,4046.75,194.22,0.05,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                        if( add ) add->GetMotionMaster()->MovePoint(0,4028.01,4035.17,193.59);
                        add = me->SummonCreature(ENTRY_ARA_TECH,3996.81,4048.26,194.22,0.05,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                        if( add ) add->GetMotionMaster()->MovePoint(0,4028.01,4035.17,193.59);
                    }
                    Wave_Timer = 15000;
                    break;
            }
        }
        void DoFinalSpawnForCreature(Creature *creature)
        {
            switch( creature->GetEntry() )
            {
                case ENTRY_BNAAR_C_CONSOLE:
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2946.52,4201.42,163.47,3.54,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2927.49,4192.81,163.00);
                    break;
                case ENTRY_CORUU_C_CONSOLE:
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2453.88,2737.85,133.27,2.59,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2433.96,2751.53,133.85);
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2441.62,2735.32,134.49,1.97,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2433.96,2751.53,133.85);
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2450.73,2754.50,134.49,3.29,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2433.96,2751.53,133.85);
                    break;
                case ENTRY_DURO_C_CONSOLE:
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2956.18,2202.85,165.32,5.45,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2972.27,2193.22,164.48);
                    add = me->SummonCreature(ENTRY_SUNFURY_TECH,2975.30,2211.50,165.32,4.55,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2972.27,2193.22,164.48);
                    add = me->SummonCreature(ENTRY_SUNFURY_PROT,2965.02,2217.45,164.16,4.96,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,2972.27,2193.22,164.48);
                    break;
                case ENTRY_ARA_C_CONSOLE:
                    add = me->SummonCreature(ENTRY_ARA_ENGI,3994.51,4020.46,192.18,0.91,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,4008.35,4035.04,192.70);
                    add = me->SummonCreature(ENTRY_ARA_GORKLONN,4021.56,4059.35,193.59,4.44,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    if( add ) add->GetMotionMaster()->MovePoint(0,4016.62,4039.89,193.46);
                    break;
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if( Event_Timer < diff )
            {
                switch(Phase)
                {
                    case 1:
                        if( someplayer )
                        {
                            Unit* u = ObjectAccessor::GetUnit((*me), someplayer);
                            if( u && u->GetTypeId() == TYPEID_PLAYER ) DoScriptText(EMOTE_START, me, u);
                        }
                        Event_Timer = 60000;
                        Wave = true;
                        ++Phase;
                        break;
                    case 2:
                        DoScriptText(EMOTE_60, me);
                        Event_Timer = 30000;
                        ++Phase;
                        break;
                    case 3:
                        DoScriptText(EMOTE_30, me);
                        Event_Timer = 20000;
                        DoFinalSpawnForCreature(me);
                        ++Phase;
                        break;
                    case 4:
                        DoScriptText(EMOTE_10, me);
                        Event_Timer = 10000;
                        Wave = false;
                        ++Phase;
                        break;
                    case 5:
                        DoScriptText(EMOTE_COMPLETE, me);
                        if( someplayer )
                        {
                            Player* player = ObjectAccessor::GetPlayer(*me, someplayer);
                            if(player)
                               player->KilledMonsterCredit(me->GetEntry(),me->GetGUID());
                            DoCast(me,SPELL_DISABLE_VISUAL);
                        }
                        if( goConsole )
                        {
                            if( GameObject* go = GameObject::GetGameObject((*me),goConsole) )
                                go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
                        }
                        ++Phase;
                        break;
                }
            } else Event_Timer -= diff;
    
            if( Wave )
            {
                if( Wave_Timer < diff )
                {
                    DoWaveSpawnForCreature(me);
                } else Wave_Timer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_manaforge_control_consoleAI(creature);
    }
};


class ManaforgeControlConsole : public GameObjectScript
{
public:
    ManaforgeControlConsole() : GameObjectScript("go_manaforge_control_console")
    {}

    struct ManaforgeControlConsoleAI : public GameObjectAI
    {
        ManaforgeControlConsoleAI(GameObject* obj) : GameObjectAI(obj) { }

        //TODO: clean up this workaround when Trinity adds support to do it properly (with gossip selections instead of instant summon)
        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
            {
                player->PrepareQuestMenu(me->GetGUID());
                player->SendPreparedQuest(me->GetGUID());
            }

            Creature* manaforge;
            manaforge = nullptr;

            switch (me->GetAreaId())
            {
            case 3726:                                          //b'naar
                if ((player->GetQuestStatus(10299) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(10329) == QUEST_STATUS_INCOMPLETE) &&
                    player->HasItemCount(29366, 1))
                    manaforge = player->SummonCreature(ENTRY_BNAAR_C_CONSOLE, 2918.95, 4189.98, 161.88, 0.34, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 125000);
                break;
            case 3730:                                          //coruu
                if ((player->GetQuestStatus(10321) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(10330) == QUEST_STATUS_INCOMPLETE) &&
                    player->HasItemCount(29396, 1))
                    manaforge = player->SummonCreature(ENTRY_CORUU_C_CONSOLE, 2426.77, 2750.38, 133.24, 2.14, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 125000);
                break;
            case 3734:                                          //duro
                if ((player->GetQuestStatus(10322) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(10338) == QUEST_STATUS_INCOMPLETE) &&
                    player->HasItemCount(29397, 1))
                    manaforge = player->SummonCreature(ENTRY_DURO_C_CONSOLE, 2976.48, 2183.29, 163.20, 1.85, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 125000);
                break;
            case 3722:                                          //ara
                if ((player->GetQuestStatus(10323) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(10365) == QUEST_STATUS_INCOMPLETE) &&
                    player->HasItemCount(29411, 1))
                    manaforge = player->SummonCreature(ENTRY_ARA_C_CONSOLE, 4013.71, 4028.76, 192.10, 1.25, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 125000);
                break;
            }

            if (manaforge)
            {
                ((npc_manaforge_control_console::npc_manaforge_control_consoleAI*)manaforge->AI())->someplayer = player->GetGUID();
                ((npc_manaforge_control_console::npc_manaforge_control_consoleAI*)manaforge->AI())->goConsole = me->GetGUID();
                me->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ManaforgeControlConsoleAI(go);
    }
};

/*######
## npc_commander_dawnforge
######*/

// The Speech of Dawnforge, Ardonis & Pathaleon
#define SAY_COMMANDER_DAWNFORGE_1           -1000128
#define SAY_ARCANIST_ARDONIS_1              -1000129
#define SAY_COMMANDER_DAWNFORGE_2           -1000130
#define SAY_PATHALEON_CULATOR_IMAGE_1       -1000131
#define SAY_COMMANDER_DAWNFORGE_3           -1000132
#define SAY_PATHALEON_CULATOR_IMAGE_2       -1000133
#define SAY_PATHALEON_CULATOR_IMAGE_2_1     -1000134
#define SAY_PATHALEON_CULATOR_IMAGE_2_2     -1000135
#define SAY_COMMANDER_DAWNFORGE_4           -1000136
#define SAY_ARCANIST_ARDONIS_2              -1000136
#define SAY_COMMANDER_DAWNFORGE_5           -1000137

#define QUEST_INFO_GATHERING                10198
#define SPELL_SUNFURY_DISGUISE              34603

// Entries of Arcanist Ardonis, Commander Dawnforge, Pathaleon the Curators Image
int CreatureEntry[3][1] =
{
    {19830},                                                // Ardonis
    {19831},                                                // Dawnforge
    {21504}                                                 // Pathaleon
};


class npc_commander_dawnforge : public CreatureScript
{
public:
    npc_commander_dawnforge() : CreatureScript("npc_commander_dawnforge")
    { }

    class npc_commander_dawnforgeAI : public ScriptedAI
    {
        public:
        npc_commander_dawnforgeAI(Creature *c) : ScriptedAI(c) { Reset (); }
    
    
        uint64 playerGUID;
        uint64 ardonisGUID;
        uint64 pathaleonGUID;
    
    
        uint32 Phase;
        uint32 PhaseSubphase;
        uint32 Phase_Timer;
        bool isEvent;
    
        float angle_dawnforge;
        float angle_ardonis;
    
        void Reset()
        override {
            playerGUID = 0;
            ardonisGUID = 0;
            pathaleonGUID = 0;
    
            Phase = 1;
            PhaseSubphase = 0;
            Phase_Timer = 4000;
            isEvent = false;
        }
    
        void EnterCombat(Unit *who) override { }
    
        void JustSummoned(Creature *summoned)
        override {
            pathaleonGUID = summoned->GetGUID();
        }
    
        // Emote Ardonis and Pathaleon
        void Turn_to_Pathaleons_Image()
        {
            Creature *ardonis = ObjectAccessor::GetCreature(*me,ardonisGUID);
            Creature *pathaleon = ObjectAccessor::GetCreature(*me,pathaleonGUID);
            Player *player = ObjectAccessor::GetPlayer(*me, playerGUID);
    
            if (!ardonis || !pathaleon || !player)
                return;
    
            //Calculate the angle to Pathaleon
            angle_dawnforge = me->GetAngle(pathaleon->GetPositionX(), pathaleon->GetPositionY());
            angle_ardonis = ardonis->GetAngle(pathaleon->GetPositionX(), pathaleon->GetPositionY());
    
            //Turn Dawnforge and update
            me->SetOrientation(angle_dawnforge);
            me->SendUpdateToPlayer(player);
            //Turn Ardonis and update
            ardonis->SetOrientation(angle_ardonis);
            ardonis->SendUpdateToPlayer(player);
    
            //Set them to kneel
            me->SetStandState(PLAYER_STATE_KNEEL);
            ardonis->SetStandState(PLAYER_STATE_KNEEL);
        }
    
        //Set them back to each other
        void Turn_to_eachother()
        {
            if (Unit *ardonis = ObjectAccessor::GetUnit(*me,ardonisGUID))
            {
                Player *player = ObjectAccessor::GetPlayer(*me, playerGUID);
    
                if (!player)
                    return;
    
                angle_dawnforge = me->GetAngle(ardonis->GetPositionX(), ardonis->GetPositionY());
                angle_ardonis = ardonis->GetAngle(me->GetPositionX(), me->GetPositionY());
    
                //Turn Dawnforge and update
                me->SetOrientation(angle_dawnforge);
                me->SendUpdateToPlayer(player);
                //Turn Ardonis and update
                ardonis->SetOrientation(angle_ardonis);
                ardonis->SendUpdateToPlayer(player);
    
                //Set state
                me->SetStandState(PLAYER_STATE_NONE);
                ardonis->SetStandState(PLAYER_STATE_NONE);
            }
        }
    
        bool CanStartEvent(Player *player)
        {
            if (!isEvent)
            {
                Creature *ardonis = me->FindNearestCreature(CreatureEntry[0][0], 10.0f);
                if (!ardonis)
                    return false;
    
                ardonisGUID = ardonis->GetGUID();
                playerGUID = player->GetGUID();
    
                isEvent = true;
    
                Turn_to_eachother();
                return true;
            }
    
            return false;
        }
    
        void UpdateAI(const uint32 diff)
        override {
            //Is event even running?
            if (!isEvent)
                return;
    
            //Phase timing
            if (Phase_Timer >= diff)
            {
                Phase_Timer -= diff;
                return;
            }
    
            Unit *ardonis = ObjectAccessor::GetUnit(*me,ardonisGUID);
            Unit *pathaleon = ObjectAccessor::GetUnit(*me,pathaleonGUID);
            Player *player = ObjectAccessor::GetPlayer(*me, playerGUID);
    
            if (!ardonis || !player)
            {
                Reset();
                return;
            }
    
            if (Phase > 4 && !pathaleon)
            {
                Reset();
                return;
            }
    
            //Phase 1 Dawnforge say
            switch (Phase)
            {
            case 1:
                DoScriptText(SAY_COMMANDER_DAWNFORGE_1, me);
                ++Phase;
                Phase_Timer = 16000;
                break;
                //Phase 2 Ardonis say
            case 2:
                DoScriptText(SAY_ARCANIST_ARDONIS_1, ardonis);
                ++Phase;
                Phase_Timer = 16000;
                break;
                //Phase 3 Dawnforge say
            case 3:
                DoScriptText(SAY_COMMANDER_DAWNFORGE_2, me);
                ++Phase;
                Phase_Timer = 16000;
                break;
                //Phase 4 Pathaleon spawns up to phase 9
            case 4:
                //spawn pathaleon's image
                me->SummonCreature(CreatureEntry[2][0], 2325.851563, 2799.534668, 133.084229, 6.038996, TEMPSUMMON_TIMED_DESPAWN, 90000);
                ++Phase;
                Phase_Timer = 500;
                break;
                //Phase 5 Pathaleon say
            case 5:
                DoScriptText(SAY_PATHALEON_CULATOR_IMAGE_1, pathaleon);
                ++Phase;
                Phase_Timer = 6000;
                break;
                //Phase 6
            case 6:
                switch(PhaseSubphase)
                {
                    //Subphase 1: Turn Dawnforge and Ardonis
                case 0:
                    Turn_to_Pathaleons_Image();
                    ++PhaseSubphase;
                    Phase_Timer = 8000;
                    break;
                    //Subphase 2 Dawnforge say
                case 1:
                    DoScriptText(SAY_COMMANDER_DAWNFORGE_3, me);
                    PhaseSubphase = 0;
                    ++Phase;
                    Phase_Timer = 8000;
                    break;
                }
                break;
                //Phase 7 Pathaleons say 3 Sentence, every sentence need a subphase
            case 7:
                switch(PhaseSubphase)
                {
                    //Subphase 1
                case 0:
                    DoScriptText(SAY_PATHALEON_CULATOR_IMAGE_2, pathaleon);
                    ++PhaseSubphase;
                    Phase_Timer = 12000;
                    break;
                    //Subphase 2
                case 1:
                    DoScriptText(SAY_PATHALEON_CULATOR_IMAGE_2_1, pathaleon);
                    ++PhaseSubphase;
                    Phase_Timer = 16000;
                    break;
                    //Subphase 3
                case 2:
                    DoScriptText(SAY_PATHALEON_CULATOR_IMAGE_2_2, pathaleon);
                    PhaseSubphase = 0;
                    ++Phase;
                    Phase_Timer = 10000;
                    break;
                }
                break;
                //Phase 8 Dawnforge & Ardonis say
            case 8:
                DoScriptText(SAY_COMMANDER_DAWNFORGE_4, me);
                DoScriptText(SAY_ARCANIST_ARDONIS_2, ardonis);
                ++Phase;
                Phase_Timer = 4000;
                break;
                //Phase 9 Pathaleons Despawn, Reset Dawnforge & Ardonis angle
            case 9:
                Turn_to_eachother();
                //hide pathaleon, unit will despawn shortly
                pathaleon->SetVisible(false);
                PhaseSubphase = 0;
                ++Phase;
                Phase_Timer = 3000;
                break;
                //Phase 10 Dawnforge say
            case 10:
                DoScriptText(SAY_COMMANDER_DAWNFORGE_5, me);
                player->AreaExploredOrEventHappens(QUEST_INFO_GATHERING);
                Reset();
                break;
            }
         }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_commander_dawnforgeAI(creature);
    }
};


Creature* SearchDawnforge(Player *source, uint32 entry, float range)
{
    Creature* pCreature = nullptr;

    Trinity::NearestCreatureEntryWithLiveStateInObjectRangeCheck creature_check(*source, entry, true, range);
    Trinity::CreatureLastSearcher<Trinity::NearestCreatureEntryWithLiveStateInObjectRangeCheck> searcher(pCreature, creature_check);

    Cell::VisitGridObjects(source, searcher, range);

    return pCreature;
}

class ATCommanderDawnforge : AreaTriggerScript
{
public:
    ATCommanderDawnforge() : AreaTriggerScript("at_commander_dawnforge") {}

    bool OnTrigger(Player *player, AreaTriggerEntry const *at) override
    {
        //if player lost aura or not have at all, we should not try start event.
        if (!player->HasAuraEffect(SPELL_SUNFURY_DISGUISE, 0))
            return false;

        if (player->IsAlive() && player->GetQuestStatus(QUEST_INFO_GATHERING) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* Dawnforge = SearchDawnforge(player, CreatureEntry[1][0], 30.0f);

            if (!Dawnforge)
                return false;

            if (((npc_commander_dawnforge::npc_commander_dawnforgeAI*)Dawnforge->AI())->CanStartEvent(player))
                return true;
        }
        return false;
    }
};

/*######
## npc_protectorate_nether_drake
######*/

#define GOSSIP_ITEM_DRAKE "I'm ready to fly! Take me up, dragon!"

class npc_protectorate_nether_drake : public CreatureScript
{
public:
    npc_protectorate_nether_drake() : CreatureScript("npc_protectorate_nether_drake")
    { }

   class npc_protectorate_nether_drakeAI : public ScriptedAI
   {
   public:
        npc_protectorate_nether_drakeAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            //On Nethery Wings
            if (player->GetQuestStatus(10438) == QUEST_STATUS_INCOMPLETE && player->HasItemCount(29778,1) )
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DRAKE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                player->CLOSE_GOSSIP_MENU();

                std::vector<uint32> nodes;

                nodes.resize(2);
                nodes[0] = 152;                                     //from drake
                nodes[1] = 153;                                     //end at drake
                player->ActivateTaxiPathTo(nodes);                  //TaxiPath 627 (possibly 627+628(152->153->154->155) )
            }
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_protectorate_nether_drakeAI(creature);
    }
};



/*######
## npc_professor_dabiri
######*/

#define SPELL_PHASE_DISTRUPTOR  35780
#define GOSSIP_ITEM_DABIRI "I need a new phase distruptor, Professor"
#define WHISPER_DABIRI -1000302

#define QUEST_DIMENSIUS 10439
#define QUEST_ON_NETHERY_WINGS 10438

class npc_professor_dabiri : public CreatureScript
{
public:
    npc_professor_dabiri() : CreatureScript("npc_professor_dabiri")
    { }

   class npc_professor_dabiriAI : public ScriptedAI
   {
   public:
        npc_professor_dabiriAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            if(player->GetQuestStatus(QUEST_ON_NETHERY_WINGS) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(29778, 1))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DABIRI, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                me->CastSpell(player, SPELL_PHASE_DISTRUPTOR, false);
                player->CLOSE_GOSSIP_MENU();
            }

            return true;
        }


        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if(quest->GetQuestId() == QUEST_DIMENSIUS)
                DoScriptText(WHISPER_DABIRI, me, player);
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_professor_dabiriAI(creature);
    }
};




/*######
## npc_veronia
######*/

#define GOSSIP_HV "Fly me to Manaforge Coruu please"

class npc_veronia : public CreatureScript
{
public:
    npc_veronia() : CreatureScript("npc_veronia")
    { }

   class npc_veroniaAI : public ScriptedAI
   {
   public:
        npc_veroniaAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu( me->GetGUID() );

            //Behind Enemy Lines
            if (player->GetQuestStatus(10652) && !player->GetQuestRewardStatus(10652))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HV, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

            SEND_PREPARED_GOSSIP_MENU(player, me);

            return true;
        }

        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            ClearGossipMenuFor(player);
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF)
            {
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player,34905,true);               //TaxiPath 606
            }
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_veroniaAI(creature);
    }
};



/*######
## mob_phase_hunter
######*/

#define SUMMONED_MOB            19595
#define EMOTE_WEAK              -1000303

// Spells
#define SPELL_PHASE_SLIP        36574
#define SPELL_MANA_BURN         13321
#define SPELL_MATERIALIZE       34804
#define SPELL_DE_MATERIALIZE    34804


class mob_phase_hunter : public CreatureScript
{
public:
    mob_phase_hunter() : CreatureScript("mob_phase_hunter")
    { }

    class mob_phase_hunterAI : public ScriptedAI
    {
        public:
    
        mob_phase_hunterAI(Creature *c) : ScriptedAI(c) {}
    
        bool Weak;
        bool Materialize;
        bool Drained;
    
        int WeakPercent;
        uint64 PlayerGUID;
        uint32 Health;
        uint32 Level;
        uint32 PhaseSlipVulnerabilityTimer;
        uint32 ManaBurnTimer;
    
        void Reset()
        override {
            Weak = false;
            Materialize = false;
            Drained = false;
    
            WeakPercent = 20;
            PlayerGUID = 0;
            ManaBurnTimer = 5000 + (rand()%3 * 1000); // 5-8 sec cd
        }
    
        void EnterCombat(Unit *who)
        override {
            if(Player *player = who->GetCharmerOrOwnerPlayerOrPlayerItself())
                PlayerGUID = player->GetGUID();
        }
    
        void SpellHit(Unit *caster, const SpellInfo *spell)
        override {
            DoCast(me, SPELL_DE_MATERIALIZE);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            if(!Materialize)
            {
                DoCast(me, SPELL_MATERIALIZE);
                Materialize = true;
            }
    
            if(me->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED) || me->HasUnitState(UNIT_STATE_ROOT)) // if the mob is rooted/slowed by spells eg.: Entangling Roots, Frost Nova, Hamstring, Crippling Poison, etc. => remove it
                DoCast(me, SPELL_PHASE_SLIP);
    
            if (!UpdateVictim())
                return;
    
            if(ManaBurnTimer < diff) // cast Mana Burn
            {
                if(me->GetVictim()->GetCreateMana() > 0)
                {
                    DoCast(me->GetVictim(), SPELL_MANA_BURN);
                    ManaBurnTimer = 8000 + (rand()%10 * 1000); // 8-18 sec cd
                }
            }else ManaBurnTimer -= diff;
    
            if(PlayerGUID) // start: support for quest 10190
            {
                Player* target = ObjectAccessor::GetPlayer(*me, PlayerGUID);
    
                if(target && !Weak && me->GetHealth() < (me->GetMaxHealth() / 100 * WeakPercent)
                    && target->GetQuestStatus(10190) == QUEST_STATUS_INCOMPLETE)
                {
                    DoScriptText(EMOTE_WEAK, me);
                    Weak = true;
                }
                if(Weak && !Drained && me->HasAuraEffect(34219, 0))
                {
                    Drained = true;
    
                    Health = me->GetHealth(); // get the normal mob's data
                    Level = me->GetLevel();
    
                    me->AttackStop(); // delete the normal mob
                    me->DespawnOrUnsummon();
    
                    Creature* DrainedPhaseHunter = nullptr;
    
                    if(!DrainedPhaseHunter)
                        DrainedPhaseHunter = me->SummonCreature(SUMMONED_MOB, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000); // summon the mob
    
                    if(DrainedPhaseHunter)
                    {
                        DrainedPhaseHunter->SetLevel(Level); // set the summoned mob's data
                        DrainedPhaseHunter->SetHealth(Health);
                        DrainedPhaseHunter->GetThreatManager().AddThreat(target, 10000.0f);
                        DrainedPhaseHunter->AI()->AttackStart(target);
                    }
                }
            }// end: support for quest 10190
    
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new mob_phase_hunterAI(creature);
    }
};


/*######
>>>>>>> creaturescript
## npc_bessy
######*/

#define Q_ALMABTRIEB    10337
#define N_THADELL       20464
#define SPAWN_FIRST     20512
#define SPAWN_SECOND    19881
#define SAY_THADELL_1   -1000304
#define SAY_THADELL_2   -1000305


class npc_bessy : public CreatureScript
{
public:
    npc_bessy() : CreatureScript("npc_bessy")
    { }

    class npc_bessyAI : public npc_escortAI
    {
        public:
        npc_bessyAI(Creature *c) : npc_escortAI(c) {}
    
        bool Completed;
    
        void JustDied(Unit* killer)
        override {
            if (PlayerGUID)
            {
                if (Player* player = GetPlayerForEscort())
                    player->FailQuest(Q_ALMABTRIEB);
            }
        }
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* player = GetPlayerForEscort();
    
            if (!player)
                return;
    
            switch(i)
            {
                case 3: //first spawn
                    me->SummonCreature(SPAWN_FIRST, 2449.67, 2183.11, 96.85, 6.20, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    me->SummonCreature(SPAWN_FIRST, 2449.53, 2184.43, 96.36, 6.27, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    me->SummonCreature(SPAWN_FIRST, 2449.85, 2186.34, 97.57, 6.08, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    break;
    
                case 7:
                    me->SummonCreature(SPAWN_SECOND, 2309.64, 2186.24, 92.25, 6.06, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    me->SummonCreature(SPAWN_SECOND, 2309.25, 2183.46, 91.75, 6.22, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    break;
    
                case 12:
                    if (player)
                    {
                        player->GroupEventHappens(Q_ALMABTRIEB, me);
                        Completed = true;
                    }
                    {Unit* Thadell = me->FindNearestCreature(N_THADELL, 30);
                    if(Thadell)
                        DoScriptText(SAY_THADELL_1, me);}break;
                case 13:
                    {Unit* Thadell = me->FindNearestCreature(N_THADELL, 30);
                    if(Thadell)
                        DoScriptText(SAY_THADELL_2, me, player);}break;
            }
        }
    
        void JustSummoned(Creature* summoned)
        override {
            summoned->AI()->AttackStart(me);
            AttackStart(summoned);
        }
    
        void EnterCombat(Unit* who)override {}
    
        void Reset()
        override {
            Completed = false;
            me->SetFaction(FACTION_FRIENDLY);
        }
    
        void UpdateAI(const uint32 diff)
        override {
            npc_escortAI::UpdateAI(diff);
        }
    

        virtual void QuestAccept(Player* player, Quest const* quest) override
        {
            if (quest->GetQuestId() == Q_ALMABTRIEB)
            {
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                ((npc_escortAI*)(me->AI()))->Start(true, true, false, player->GetGUID(), me->GetEntry());
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bessyAI(creature);
    }
};



/*######
## npc_maxx_a_million
######*/

enum
{
    QUEST_MARK_V_IS_ALIVE = 10191,
    GO_DRAENEI_MACHINE = 183771
};


class npc_maxx_a_million_escort : public CreatureScript
{
public:
    npc_maxx_a_million_escort() : CreatureScript("npc_maxx_a_million_escort")
    { }

    class npc_maxx_a_million_escortAI : public npc_escortAI
    {
        public:
        npc_maxx_a_million_escortAI(Creature* pCreature) : npc_escortAI(pCreature) {}
    
        bool bTake;
        uint32 uiTakeTimer;
    
        void Reset()
        override {
            bTake=false;
            uiTakeTimer = 3000;
        }
        
        void EnterCombat(Unit *pWho) override {}
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            Player* pPlayer = GetPlayerForEscort();
            if (!pPlayer)
                return;
    
            switch (i) {
            case 7:
            case 17:
            case 29:
                //Find Object and "work"
                if (GameObject* pGO = me->FindNearestGameObject(GO_DRAENEI_MACHINE,INTERACTION_DISTANCE)) {
                    // take the GO -> animation
                    me->HandleEmoteCommand(428);
                    SetEscortPaused(true);
                    bTake=true;
                }
                break;
            case 36: //return and quest_complete
                if (pPlayer)
                    pPlayer->CompleteQuest(QUEST_MARK_V_IS_ALIVE);
                break;
            }
        }
    
        void JustDied(Unit* pKiller)
        override {
            Player* pPlayer = GetPlayerForEscort();
            if (pPlayer && pPlayer->GetQuestStatus(QUEST_MARK_V_IS_ALIVE) == QUEST_STATUS_INCOMPLETE)
                pPlayer->FailQuest(QUEST_MARK_V_IS_ALIVE);
        }
    
        void UpdateAI(const uint32 uiDiff)
        override {
            npc_escortAI::UpdateAI(uiDiff);
    
            if (bTake) {
                if (uiTakeTimer < uiDiff) {
                    me->HandleEmoteCommand(EMOTE_STATE_NONE);
                    if (GameObject* pGO = me->FindNearestGameObject(GO_DRAENEI_MACHINE,INTERACTION_DISTANCE))
                    {
                        SetEscortPaused(false);
                        bTake=false;
                        uiTakeTimer = 3000;
                        pGO->Delete();
                    }
                }
                else
                    uiTakeTimer -= uiDiff;
            }
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if (pQuest->GetQuestId() == QUEST_MARK_V_IS_ALIVE) {
                me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                ((npc_escortAI*)(me->AI()))->Start(true, true, false, pPlayer->GetGUID(), me->GetEntry());
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_maxx_a_million_escortAI(creature);
    }
};



enum
{
    QUEST_A_NOT_SO_MODEST_PROPOSAL = 10270,
    NPC_IMAGE_OF_WIND_TRADER_MARID = 20518
};

class EtherealTeleportPad : public GameObjectScript
{
public:
    EtherealTeleportPad() : GameObjectScript("go_ethereal_teleport")
    {}

    struct EtherealTeleportPadAI : public GameObjectAI
    {
        EtherealTeleportPadAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->GetQuestStatus(QUEST_A_NOT_SO_MODEST_PROPOSAL) == QUEST_STATUS_COMPLETE)
            {
                Creature *npc = me->FindNearestCreature(NPC_IMAGE_OF_WIND_TRADER_MARID, 1.0f); // prevents double spawn
                if (npc)
                    npc->DisappearAndDie();
                me->SummonCreature(NPC_IMAGE_OF_WIND_TRADER_MARID, 4007.11f, 1517.15f, -115.535f, 4.97726f, TEMPSUMMON_TIMED_DESPAWN, 60000);
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new EtherealTeleportPadAI(go);
    }
};

/*######
## npc_dr_boom
######*/

enum
{
    THROW_DYNAMITE    = 35276,
    BOOM_BOT          = 19692,
    BOOM_BOT_TARGET   = 20392
};


class npc_dr_boom : public CreatureScript
{
public:
    npc_dr_boom() : CreatureScript("npc_dr_boom")
    { }

    class npc_dr_boomAI : public ScriptedAI
    {
        public:
        npc_dr_boomAI(Creature *pCreature) : ScriptedAI(pCreature) {}
    
        std::vector<uint64> targetGUID;
        uint32 SummonTimer;
        uint32 InitTimer;
    
        void Reset()
        override {
            SummonTimer = 1500;
            InitTimer = 1000;
            SetCombatMovementAllowed(false);
        }
        
        void EnterCombat(Unit* who) override {}
    
        void UpdateAI(const uint32 uiDiff)
        override {
            if (InitTimer) {
                if (InitTimer <= uiDiff) {
                    std::list<Creature*> targets;
                    me->GetCreatureListWithEntryInGrid(targets, BOOM_BOT_TARGET, 30.0f);
                    targetGUID.clear();
                    for (auto & target : targets)
                        targetGUID.push_back(target->GetGUID());
                        
                    InitTimer = 0;
                }
                else
                    InitTimer -= uiDiff;
            }
    
            if (SummonTimer <= uiDiff)
            {
                if (targetGUID.size())
                {
                    if (Unit* target = ObjectAccessor::GetUnit(*me, targetGUID[rand()%targetGUID.size()]))
                    {
                        if (Unit* bot = DoSpawnCreature(BOOM_BOT, 0, 0, 0, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 20000))
                            bot->GetMotionMaster()->MovePoint(0, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
                    }
                }
    
                SummonTimer = 1500;
            }
            else SummonTimer -= uiDiff;
    
            if (!UpdateVictim())
                return;
    
            if (!me->IsWithinDistInMap(me->GetVictim(), 30.0f))
            {
                EnterEvadeMode();
                return;
            }
    
            if (me->IsAttackReady() && me->IsWithinDistInMap(me->GetVictim(), 8.0f))
            {
                DoCast(me->GetVictim(), THROW_DYNAMITE, true);
                me->ResetAttackTimer();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dr_boomAI(creature);
    }
};


/*######
## npc_boom_bot
######*/

#define    SPELL_BOOM    35132                         


class npc_boom_bot : public CreatureScript
{
public:
    npc_boom_bot() : CreatureScript("npc_boom_bot")
    { }

    class npc_boom_botAI : public ScriptedAI
    {
        public:
        npc_boom_botAI(Creature *pCreature) : ScriptedAI(pCreature) {}
    
        bool Boom;
        uint32 BoomTimer;
    
        void Reset()
        override {
            Boom = false;
            BoomTimer = 800;
            me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
        }
        
        void MovementInform(uint32 type, uint32 id)
        override {
            if (type != POINT_MOTION_TYPE)
                return;
    
            DoCast(me, SPELL_BOOM);
            Boom = true;
        }
    
        void MoveInLineOfSight(Unit *pWho)
        override {
            if (!pWho->isCharmedOwnedByPlayerOrPlayer())
                return;
    
            if (me->IsWithinDistInMap(pWho, 4.0f, false))
            {
                DoCast(me, SPELL_BOOM);
                Boom = true;
            }
        }
    
        void UpdateAI(const uint32 uiDiff)
        override {
            if (Boom)
            {
                if (BoomTimer <= uiDiff)
                {
                    me->SetDeathState(CORPSE);
                }
                else BoomTimer -= uiDiff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_boom_botAI(creature);
    }
};


/*######
## npc_drijya
######*/

enum
{
    SAY_DR_START           = -1900156,
    SAY_DR_1               = -1900157,
    SAY_DR_2               = -1900158,
    SAY_DR_3               = -1900159,
    SAY_DR_4               = -1900160,
    SAY_DR_5               = -1900161,
    SAY_DR_6               = -1900162,
    SAY_DR_7               = -1900163,
    SAY_DR_COMPLETE        = -1900164,

    QUEST_WARP_GATE        = 10310,

    MAX_TROOPER            = 9,
    MAX_IMP                = 6,

    NPC_EXPLODE_TRIGGER    = 20296,
    NPC_IMP                = 20399,
    NPC_TROOPER            = 20402,
    NPC_DESTROYER          = 20403,

    GO_SMOKE               = 185318,
    GO_FIRE                = 185317,
    GO_BIG_FIRE            = 185319
};


class npc_drijya : public CreatureScript
{
public:
    npc_drijya() : CreatureScript("npc_drijya")
    { }

    class npc_drijyaAI : public npc_escortAI
    {
        public:
        npc_drijyaAI(Creature* pCreature) : npc_escortAI(pCreature) {}
    
        bool Destroy;
        bool SummonImp;
        bool SummonTrooper;
        bool SummonDestroyer;
    
        uint32 Count;
        uint32 SpawnTimer;
        uint32 StartSpawnTimer;
        uint32 DestroyingTimer;
    
        void Reset()
        override {
            Destroy = false;
            SummonImp = false;
            SummonTrooper = false;
            SummonDestroyer = false;
            Count = 0;
            SpawnTimer = 3500;
            StartSpawnTimer = 15000;
            DestroyingTimer = 60000;
        }
    
        void EnterCombat(Unit* who) override {}
    
        void SpawnImp()
        {
            ++Count;
            me->SummonCreature(NPC_IMP, 3025.752f, 2715.122, 113.758, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        }
    
        void SpawnTrooper()
        {
            ++Count;
            me->SummonCreature(NPC_TROOPER, 3025.752f, 2715.122, 113.758, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        }
    
        void SpawnDestroyer()
        {
            me->SummonCreature(NPC_DESTROYER, 3019.741f, 2720.757, 115.189, 2.5f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        }
    
        void JustSummoned(Creature* pSummoned)
        override {
            if (pSummoned->GetEntry() == NPC_IMP)
            {
                if (Player* pPlayer = GetPlayerForEscort())
                    pSummoned->AI()->AttackStart(pPlayer); 
            }
    
            if (pSummoned->GetEntry() == NPC_TROOPER)
            {
                if(Player* pPlayer = GetPlayerForEscort())
                    pSummoned->AI()->AttackStart(pPlayer);
            }
            else
            {
                if (pSummoned->GetEntry() == NPC_DESTROYER)
                {
                    if (Player* pPlayer = GetPlayerForEscort())
                        pSummoned->AI()->AttackStart(pPlayer);
                }
            }
        }
    
        void WaypointReached(uint32 uiPointId, uint32 pathID)
        override {
            switch(uiPointId)
            {
                case 0:
                    DoScriptText(SAY_DR_START, me);
                    SetRun();
                    break;
                case 1:
                    DoScriptText(SAY_DR_1, me);
                    break;
                case 5:
                    DoScriptText(SAY_DR_2, me);
                    break;
                case 7:
                    SetEscortPaused(true);
                    Destroy = true;
                    SummonImp = true;
                    break;
                case 8:
                    me->SummonGameObject(GO_SMOKE, Position(3049.354f, 2726.431f, 113.922f, 0.0f), G3D::Quat(), 215);
                    DoScriptText(SAY_DR_4, me);
                    break;
                case 12:
                    SetEscortPaused(true);
                    Destroy = true;
                    SummonTrooper = true;
                    break;
                case 13:
                    me->SummonGameObject(GO_SMOKE, Position(3020.842f, 2697.501f, 113.368f, 0.0f), G3D::Quat(), 140);
                    DoScriptText(SAY_DR_5, me);
                    break;
                case 17:
                    SetEscortPaused(true);
                    Destroy = true;
                    SummonDestroyer = true;
                    break;
                case 18:
                    DoScriptText(SAY_DR_6, me);
                    if (Creature* pTrigger = me->FindNearestCreature(NPC_EXPLODE_TRIGGER, 20.0f))
                    {
                        pTrigger->CastSpell(pTrigger, SPELL_BOOM , false);
                    }
                    me->SummonGameObject(GO_SMOKE, Position(3008.503f, 2729.432f, 114.350f, 0.0f), G3D::Quat(), 60);
                    me->SummonGameObject(GO_FIRE, Position(3026.163f, 2723.538f, 113.681f, 0.0f), G3D::Quat(), 60);
                    me->SummonGameObject(GO_BIG_FIRE, Position(3021.556f, 2718.887f, 115.055f, 0.0f), G3D::Quat(), 60);
                    break;
                case 19:
                    DoScriptText(SAY_DR_7, me);
                    break;
                case 22:
                    SetRun(false);
                    break;
                case 26:
                    if (Player* pPlayer = GetPlayerForEscort())
                    {
                        DoScriptText(SAY_DR_COMPLETE, me, pPlayer);
                        pPlayer->GroupEventHappens(QUEST_WARP_GATE, me);
                    }
                    break;
            }
        }
    
        void UpdateAI(const uint32 uiDiff)
        override {
            npc_escortAI::UpdateAI(uiDiff);
    
            if (SummonImp)
            {
                if (StartSpawnTimer <= uiDiff) 
                {
                    if (SpawnTimer <= uiDiff)
                    {
                        if (Count >= MAX_IMP)
                        {
                            DoScriptText(SAY_DR_3, me);
                            SummonImp = false;
                            StartSpawnTimer = 15000;
                        }
                        SpawnTimer = 3500;
                        SpawnImp();
                    }
                    else SpawnTimer -= uiDiff;
                }
                else StartSpawnTimer -= uiDiff;
            }
    
            if (SummonTrooper)
            {
                if (StartSpawnTimer <= uiDiff)
                {
                    if (SpawnTimer <= uiDiff)
                    {
                        if (Count >= MAX_TROOPER)
                        {
                            SummonTrooper = false;
                            StartSpawnTimer = 15000;
                        }
    
                        SpawnTimer = 3500;
                        SpawnTrooper();
                    }
                    else SpawnTimer -= uiDiff;
                }
                else StartSpawnTimer -= uiDiff;
            }
    
            if (SummonDestroyer)
            {
                if (StartSpawnTimer <= uiDiff)
                {
                    SpawnDestroyer();
                    SummonDestroyer = false;
                    StartSpawnTimer = 15000;
                }
                else StartSpawnTimer -= uiDiff;
            }
    
            if (Destroy)
            {
                if (DestroyingTimer <= uiDiff)
                {
                    SetEscortPaused(false);
                    Destroy = false;
                    DestroyingTimer = 60000;
                }
                else DestroyingTimer -= uiDiff;
    
                me->HandleEmoteCommand(173);
    
            }
            DoMeleeAttackIfReady();
        }

        virtual void QuestAccept(Player* pPlayer, Quest const* pQuest) override
        {
            if (pQuest->GetQuestId() == QUEST_WARP_GATE)
            {
                if (npc_drijyaAI* pEscortAI = dynamic_cast<npc_drijyaAI*>(me->AI()))
                {
                    me->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
                    pEscortAI->Start(true, true, false, pPlayer->GetGUID(), me->GetEntry());
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_drijyaAI(creature);
    }
};



/*######
## AddSC
######*/

void AddSC_netherstorm()
{
    new ManaforgeControlConsole();
    new npc_manaforge_control_console();
    new npc_commander_dawnforge();
    new ATCommanderDawnforge();
    new npc_protectorate_nether_drake();
    new npc_professor_dabiri();
    new npc_veronia();
    new mob_phase_hunter();
    new npc_bessy();
    new npc_maxx_a_million_escort();
    new EtherealTeleportPad();
    new npc_dr_boom();
    new npc_boom_bot();
    new npc_drijya();
}
