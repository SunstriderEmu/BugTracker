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
SDName: Old_Hillsbrad
SD%Complete: 40
SDComment: Quest support: 10283, 10284. All friendly NPC's. Thrall waypoints fairly complete, missing many details, but possible to complete escort.
SDCategory: Caverns of Time, Old Hillsbrad Foothills
EndScriptData */

/* ContentData
npc_brazen
npc_erozion
npc_thrall_old_hillsbrad
npc_taretha
EndContentData */


#include "EscortAI.h"
#include "def_old_hillsbrad.h"

#define QUEST_ENTRY_HILLSBRAD   10282
#define QUEST_ENTRY_DIVERSION   10283
#define QUEST_ENTRY_ESCAPE      10284
#define QUEST_ENTRY_RETURN      10285
#define ITEM_ENTRY_BOMBS        25853

/*######
## npc_brazen
######*/

class npc_brazen : public CreatureScript
{
public:
    npc_brazen() : CreatureScript("npc_brazen")
    { }

    class npc_brazenAI : public ScriptedAI
    {
    public:
        npc_brazenAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Je suis prêt à aller à Fort-de-Durn.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1); // I am ready to go to Durnholde Keep.
            SEND_DEFAULT_GOSSIP_MENU(player, me);
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if (action == GOSSIP_ACTION_INFO_DEF+1)
            {
                if( !player->HasItemCount(ITEM_ENTRY_BOMBS,1) )
                    player->SEND_GOSSIP_MENU_TEXTID(9780, me->GetGUID());
                else
                {
                    player->CLOSE_GOSSIP_MENU();

                    std::vector<uint32> nodes;

                    nodes.resize(2);
                    nodes[0] = 115;                                 //from brazen
                    nodes[1] = 116;                                 //end outside durnholde
                    player->ActivateTaxiPathTo(nodes);              //TaxiPath 534
                }
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_brazenAI(creature);
    }
};



/*######
## npc_erozion
######*/

class npc_erozion : public CreatureScript
{
public:
    npc_erozion() : CreatureScript("npc_erozion")
    { }

    class npc_erozionAI : public ScriptedAI
    {
    public:
        npc_erozionAI(Creature* creature) : ScriptedAI(creature)
        {}


        virtual bool GossipHello(Player* player) override
        {
            if( me->IsQuestGiver() )
                player->PrepareQuestMenu( me->GetGUID() );

            InstanceScript* pInstance = ((InstanceScript*)me->GetInstanceScript());
            if( pInstance && pInstance->GetData(TYPE_BARREL_DIVERSION) != DONE && !player->HasItemCount(ITEM_ENTRY_BOMBS,1) )
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "J'ai besoin d'un paquet de bombes incendiaires.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1); // I need a pack of Incendiary Bombs.

            if( !player->GetQuestRewardStatus(QUEST_ENTRY_RETURN) && player->GetQuestStatus(QUEST_ENTRY_RETURN) == QUEST_STATUS_COMPLETE )
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Renvoyez-moi à mon époque.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2); // Take me back to my time.

            player->SEND_GOSSIP_MENU_TEXTID(9778, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if( action == GOSSIP_ACTION_INFO_DEF+1 )
            {
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_ENTRY_BOMBS, 1);
                if( msg == EQUIP_ERR_OK )
                {
                     player->StoreNewItem(dest, ITEM_ENTRY_BOMBS, true);
                }
                player->SEND_GOSSIP_MENU_TEXTID(9515, me->GetGUID());
            }
            if( action == GOSSIP_ACTION_INFO_DEF+2 )
            {
                player->CLOSE_GOSSIP_MENU();
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_erozionAI(creature);
    }
};



/*######
## npc_thrall_old_hillsbrad
######*/

//Thrall texts
#define SAY_TH_START_EVENT_PART1    -1560023
#define SAY_TH_ARMORY               -1560024
#define SAY_TH_SKARLOC_MEET         -1560025
#define SAY_TH_SKARLOC_TAUNT        -1560026
#define SAY_TH_START_EVENT_PART2    -1560027
#define SAY_TH_MOUNTS_UP            -1560028
#define SAY_TH_CHURCH_END           -1560029
#define SAY_TH_MEET_TARETHA         -1560030
#define SAY_TH_EPOCH_WONDER         -1560031
#define SAY_TH_EPOCH_KILL_TARETHA   -1560032
#define SAY_TH_EVENT_COMPLETE       -1560033

#define SAY_TH_RANDOM_LOW_HP1       -1560034
#define SAY_TH_RANDOM_LOW_HP2       -1560035

#define SAY_TH_RANDOM_DIE1          -1560036
#define SAY_TH_RANDOM_DIE2          -1560037

#define SAY_TH_RANDOM_AGGRO1        -1560038
#define SAY_TH_RANDOM_AGGRO2        -1560039
#define SAY_TH_RANDOM_AGGRO3        -1560040
#define SAY_TH_RANDOM_AGGRO4        -1560041

#define SAY_TH_RANDOM_KILL1         -1560042
#define SAY_TH_RANDOM_KILL2         -1560043
#define SAY_TH_RANDOM_KILL3         -1560044

#define SAY_TH_LEAVE_COMBAT1        -1560045
#define SAY_TH_LEAVE_COMBAT2        -1560046
#define SAY_TH_LEAVE_COMBAT3        -1560047

//Taretha texts
#define SAY_TA_FREE                 -1560048
#define SAY_TA_ESCAPED              -1560049

//Misc for Thrall
#define SPELL_STRIKE                14516
#define SPELL_SHIELD_BLOCK          12169
#define SPELL_SUMMON_EROZION_IMAGE  33954                   //if thrall dies during escort?

#define SPEED_WALK              (0.5f)
#define SPEED_RUN               (1.0f)
#define SPEED_MOUNT             (1.6f)

#define THRALL_WEAPON_MODEL     22106
#define THRALL_WEAPON_INFO      218169346
#define THRALL_SHIELD_MODEL     18662
#define THRALL_SHIELD_INFO      234948100
#define THRALL_MODEL_UNEQUIPPED 17292
#define THRALL_MODEL_EQUIPPED   18165

//Misc creature entries
#define ENTRY_ARMORER               18764
#define ENTRY_SCARLOC               17862

#define MOB_ENTRY_RIFLE         17820
#define MOB_ENTRY_WARDEN        17833
#define MOB_ENTRY_VETERAN       17860
#define MOB_ENTRY_WATCHMAN      17814
#define MOB_ENTRY_SENTRY        17815

#define MOB_ENTRY_BARN_GUARDSMAN    18092
#define MOB_ENTRY_BARN_PROTECTOR    18093
#define MOB_ENTRY_BARN_LOOKOUT      18094

#define MOB_ENTRY_CHURCH_GUARDSMAN  23175
#define MOB_ENTRY_CHURCH_PROTECTOR  23179
#define MOB_ENTRY_CHURCH_LOOKOUT    23177

#define MOB_ENTRY_INN_GUARDSMAN     23176
#define MOB_ENTRY_INN_PROTECTOR     23180
#define MOB_ENTRY_INN_LOOKOUT       23178

#define SKARLOC_MOUNT           18798
#define SKARLOC_MOUNT_MODEL     18223
#define EROZION_ENTRY           18723
#define ENTRY_EPOCH                 18096

//gossip items
#define GOSSIP_ID_START         9568
#define GOSSIP_ID_SKARLOC1      9614                        // I'm glad Taretha is alive. We now must find a way to free her...
#define GOSSIP_ITEM_SKARLOC1    "Taretha ne peut pas vous voir, Thrall." // Taretha cannot see you, Thrall.
#define GOSSIP_ID_SKARLOC2      9579                        // What do you mean by this? Is Taretha in danger?
#define GOSSIP_ITEM_SKARLOC2    "La situation est assez compliquée, Thrall. Il vaudrait mieux que vous filiez vers les montagnes dès maintenant, avant que d'autres hommes de Landenoire ne se montrent. Nous veillerons à la sécurité de Taretha." // The situation is rather complicated, Thrall. It would be best for you to head into the mountains now, before more of Blackmoore's men show up. We'll make sure Taretha is safe.
#define GOSSIP_ID_SKARLOC3      9580

#define GOSSIP_ID_TARREN        9597                        // Tarren mill is beyond these trees...
#define GOSSIP_ITEM_TARREN      "Nous sommes prêts, Thrall." // We're ready, Thrall.

#define GOSSIP_ID_COMPLETE      9578                        // Thank you friends, I owe my freedom to you. Where is Taretha? I hoped to see her


class npc_thrall_old_hillsbrad : public CreatureScript
{
public:
    npc_thrall_old_hillsbrad() : CreatureScript("npc_thrall_old_hillsbrad")
    { }

    class npc_thrall_old_hillsbradAI : public npc_escortAI
    {
        public:
        npc_thrall_old_hillsbradAI(Creature *c) : npc_escortAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            me->SetKeepActive(30 * MINUTE*IN_MILLISECONDS);
        }
    
        InstanceScript *pInstance;
    
        bool LowHp;
        bool HadMount;
    
        void WaypointReached(uint32 i)
        override {
            if (!pInstance)
                return;
    
            switch( i )
            {
                case 8:
                    me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    me->SummonCreature(18764,2181.87,112.46,89.45,0.26,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    break;
                case 9:
                    DoScriptText(SAY_TH_ARMORY, me);
                    me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, THRALL_WEAPON_MODEL);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO, THRALL_WEAPON_INFO);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+1, 781);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, THRALL_SHIELD_MODEL);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+2, THRALL_SHIELD_INFO);
                    me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+3, 1038);
                    break;
                case 10:
                    me->SetUInt32Value(UNIT_FIELD_DISPLAYID, THRALL_MODEL_EQUIPPED);
                    break;
                case 11:
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    break;
                case 15:
                    me->SummonCreature(MOB_ENTRY_RIFLE,2200.28,137.37,87.93,5.07,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_WARDEN,2197.44,131.83,87.93,0.78,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_VETERAN,2203.62,135.40,87.93,3.70,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_VETERAN,2200.75,130.13,87.93,1.48,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    break;
                case 21:
                    me->SummonCreature(MOB_ENTRY_RIFLE,2135.80,154.01,67.45,4.98,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_WARDEN,2144.36,151.87,67.74,4.46,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_VETERAN,2142.12,154.41,67.12,4.56,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_VETERAN,2138.08,155.38,67.24,4.60,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    break;
                case 25:
                    me->SummonCreature(MOB_ENTRY_RIFLE,2102.98,192.17,65.24,6.02,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_WARDEN,2108.48,198.75,65.18,5.15,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_VETERAN,2106.11,197.29,65.18,5.63,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_VETERAN,2104.18,194.82,65.18,5.75,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    break;
                case 29:
                    DoScriptText(SAY_TH_SKARLOC_MEET, me);
                    me->SummonCreature(17862,2036.48,271.22,63.43,5.27,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,30000);
                    //temporary,skarloc should rather be triggered to walk up to thrall
                    break;
                case 30:
                    IsOnHold = true;
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    break;
                case 31:
                    DoScriptText(SAY_TH_MOUNTS_UP, me);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                    DoMount();
                    break;
                case 37:
                    //possibly regular patrollers? If so, remove this and let database handle them
                    me->SummonCreature(MOB_ENTRY_WATCHMAN,2124.26,522.16,56.87,3.99,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_WATCHMAN,2121.69,525.37,57.11,4.01,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_SENTRY,2124.65,524.55,56.63,3.98,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    break;
                case 59:
                    me->SummonCreature(SKARLOC_MOUNT,2488.64,625.77,58.26,4.71,TEMPSUMMON_TIMED_DESPAWN,10000);
                    DoDismount();
                    HadMount = false;
                    break;
                case 60:
                    me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                    //make horsie run off
                    IsOnHold = true;
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    pInstance->SetData(TYPE_THRALL_PART2, DONE);
                    break;
                case 64:
                    me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    break;
                case 68:
                    me->SummonCreature(MOB_ENTRY_BARN_PROTECTOR,2500.22,692.60,55.50,2.84,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_BARN_LOOKOUT,2500.13,696.55,55.51,3.38,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_BARN_GUARDSMAN,2500.55,693.64,55.50,3.14,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_BARN_GUARDSMAN,2500.94,695.81,55.50,3.14,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    break;
                case 71:
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    break;
                case 81:
                    me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    break;
                case 83:
                    me->SummonCreature(MOB_ENTRY_CHURCH_PROTECTOR,2627.33,646.82,56.03,4.28,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,5000);
                    me->SummonCreature(MOB_ENTRY_CHURCH_LOOKOUT,2624.14,648.03,56.03,4.50,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,5000);
                    me->SummonCreature(MOB_ENTRY_CHURCH_GUARDSMAN,2625.32,649.60,56.03,4.38,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,5000);
                    me->SummonCreature(MOB_ENTRY_CHURCH_GUARDSMAN,2627.22,649.00,56.03,4.34,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,5000);
                    break;
                case 84:
                    DoScriptText(SAY_TH_CHURCH_END, me);
                    break;
                case 91:
                    me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    break;
                case 93:
                    me->SummonCreature(MOB_ENTRY_INN_PROTECTOR,2652.71,660.31,61.93,1.67,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_INN_LOOKOUT,2648.96,662.59,61.93,0.79,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_INN_GUARDSMAN,2657.36,662.34,61.93,2.68,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_INN_GUARDSMAN,2656.39,659.77,61.93,2.61,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    break;
                case 94:
                    me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    if (uint64 tarethaGUID = pInstance->GetData64(DATA_TARETHA))
                    {
                        if (Unit* Taretha = ObjectAccessor::GetUnit((*me), tarethaGUID))
                            DoScriptText(SAY_TA_ESCAPED, Taretha, me);
                    }
                    break;
                case 95:
                    DoScriptText(SAY_TH_MEET_TARETHA, me);
                    pInstance->SetData(TYPE_THRALL_PART3,DONE);
                    IsOnHold = true;
                    break;
                case 96:
                    DoScriptText(SAY_TH_EPOCH_WONDER, me);
                     me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                    break;
                case 97:
                    DoScriptText(SAY_TH_EPOCH_KILL_TARETHA, me);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    break;
                case 98:
                    //trigger epoch Yell("Thrall! Come outside and face your fate! ....")
                    //from here, thrall should not never be allowed to move to point 106 which he currently does.
                    break;
    
                case 106:
                    {
                        if (!PlayerGUID)
                            break;
    
                        //trigger taretha to run down outside
                        if (uint64 tarethaGUID = pInstance->GetData64(DATA_TARETHA))
                        {
                            if (Creature* Taretha = (ObjectAccessor::GetCreature(*me, tarethaGUID)))
                                ((npc_escortAI*)(Taretha->AI()))->Start(false, false, true, PlayerGUID);
                        }
    
                        //kill credit creature for quest
                        Map *map = me->GetMap();
                        Map::PlayerList const& players = map->GetPlayers();
                        if (!players.isEmpty() && map->IsDungeon())
                        {
                            for(const auto & player : players)
                            {
                                if (Player* pPlayer = player.GetSource())
                                    pPlayer->KilledMonsterCredit(20156,me->GetGUID());
                            }
                        }
    
                        //alot will happen here, thrall and taretha talk, erozion appear at spot to explain
                        me->SummonCreature(EROZION_ENTRY,2646.47,680.416,55.38,4.16,TEMPSUMMON_TIMED_DESPAWN,120000);
                    }
                    break;
                case 108:
                    //last waypoint, just set Thrall invisible, respawn is turned off
                    me->SetVisible(false);
                    break;
            }
        }
    
    
        void Reset()
        override {
            LowHp = false;
    
            if( HadMount )
                DoMount();
    
            if( !HasEscortState(STATE_ESCORT_ESCORTING))
            {
                DoDismount();
                HadMount = false;
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 0);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO, 0);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+1, 0);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+2, 0);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+3, 0);
                me->SetUInt32Value(UNIT_FIELD_DISPLAYID, THRALL_MODEL_UNEQUIPPED);
            }
            if(HasEscortState(STATE_ESCORT_ESCORTING))
            {
                switch(rand()%3)
                {
                case 0: DoScriptText(SAY_TH_LEAVE_COMBAT1, me); break;
                case 1: DoScriptText(SAY_TH_LEAVE_COMBAT2, me); break;
                case 2: DoScriptText(SAY_TH_LEAVE_COMBAT3, me); break;
                }
            }
        }
        void StartWP()
        {
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            IsOnHold = false;
        }
        void DoMount()
        {
            me->Mount(SKARLOC_MOUNT_MODEL);
            me->SetSpeedRate(MOVE_RUN,SPEED_MOUNT);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
        }
        void DoDismount()
        {
            me->Dismount();
            me->SetSpeedRate(MOVE_RUN,SPEED_RUN);
        }
        void EnterCombat(Unit* who)
        override {
            switch(rand()%4)
            {
            case 0: DoScriptText(SAY_TH_RANDOM_AGGRO1, me); break;
            case 1: DoScriptText(SAY_TH_RANDOM_AGGRO2, me); break;
            case 2: DoScriptText(SAY_TH_RANDOM_AGGRO3, me); break;
            case 3: DoScriptText(SAY_TH_RANDOM_AGGRO4, me); break;
            }
            if( me->IsMounted() )
            {
                DoDismount();
                HadMount = true;
            }
        }
    
        void JustSummoned(Creature* summoned)
        override {
             switch(summoned->GetEntry())
             {
            //TODO: make Scarloc start into event instead, and not start attack directly
             case MOB_ENTRY_BARN_GUARDSMAN:
             case MOB_ENTRY_BARN_PROTECTOR:
             case MOB_ENTRY_BARN_LOOKOUT:
             case SKARLOC_MOUNT:
             case EROZION_ENTRY:
                 break;
             default:
                 summoned->AI()->AttackStart(me);
                 break;
             }
        }
    
        void KilledUnit(Unit *victim)
        override {
            switch(rand()%3)
            {
            case 0: DoScriptText(SAY_TH_RANDOM_KILL1, me); break;
            case 1: DoScriptText(SAY_TH_RANDOM_KILL2, me); break;
            case 2: DoScriptText(SAY_TH_RANDOM_KILL3, me); break;
            }
        }
        void JustDied(Unit *slayer)
        override {
            if (pInstance)
                pInstance->SetData(TYPE_THRALL_EVENT,FAIL);
    
            // Don't do a yell if he kills self (if player goes too far or at the end).
            if(slayer == me)
                return;
    
            switch(rand()%2)
            {
            case 0: DoScriptText(SAY_TH_RANDOM_DIE1, me); break;
            case 1: DoScriptText(SAY_TH_RANDOM_DIE2, me); break;
            }
        }
    
        void UpdateAI(const uint32 diff)
        override {
            npc_escortAI::UpdateAI(diff);
    
            if (!UpdateVictim())
                return;
    
                 //TODO: add his abilities'n-crap here
                if( !LowHp && ((me->GetHealthPct()) < 20) )
                {
                    switch(rand()%2)
                    {
                    case 0: DoScriptText(SAY_TH_RANDOM_LOW_HP1, me); break;
                    case 1: DoScriptText(SAY_TH_RANDOM_LOW_HP2, me); break;
                    }
                    LowHp = true;
                }
        }

        virtual bool GossipHello(Player* player) override
        {
            if( me->IsQuestGiver() )
            {
                player->PrepareQuestMenu( me->GetGUID() );
                player->SendPreparedQuest(me->GetGUID());
            }

            if( pInstance )
            {
                if (pInstance->GetData(TYPE_BARREL_DIVERSION) == DONE && !pInstance->GetData(TYPE_THRALL_EVENT))
                {
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Nous allons vous sortir de là, Thrall. On y va !", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1); // We are ready to get you out of here, Thrall. Let's go!
                    player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_ID_START, me->GetGUID());
                }

                if( pInstance->GetData(TYPE_THRALL_PART1) == DONE && !pInstance->GetData(TYPE_THRALL_PART2) )
                {
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_SKARLOC1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                    player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_ID_SKARLOC1, me->GetGUID());
                }

                if( pInstance->GetData(TYPE_THRALL_PART2) == DONE && !pInstance->GetData(TYPE_THRALL_PART3) )
                {
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_TARREN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                    player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_ID_TARREN, me->GetGUID());
                }
            }
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            switch( action )
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->CLOSE_GOSSIP_MENU();
                    if(pInstance)
                    {
                        pInstance->SetData(TYPE_THRALL_EVENT,IN_PROGRESS);
                        pInstance->SetData(TYPE_THRALL_PART1,IN_PROGRESS);
                    }

                    DoScriptText(SAY_TH_START_EVENT_PART1, me);

                    ((npc_escortAI*)(me->AI()))->Start(true, true, true, player->GetGUID());
                    ((npc_escortAI*)(me->AI()))->SetMaxPlayerDistance(100.0f);//not really needed, because it will not despawn if player is too far
                    ((npc_escortAI*)(me->AI()))->SetDespawnAtEnd(false);
                    ((npc_escortAI*)(me->AI()))->SetDespawnAtFar(false);
                    break;

                case GOSSIP_ACTION_INFO_DEF+2:
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_SKARLOC2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+20);
                    player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_ID_SKARLOC2, me->GetGUID());
                    break;

                case GOSSIP_ACTION_INFO_DEF+20:
                    player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_ID_SKARLOC3, me->GetGUID());
                    me->SummonCreature(SKARLOC_MOUNT,2038.81,270.26,63.20,5.41,TEMPSUMMON_TIMED_DESPAWN,12000);
                    if(pInstance)
                        pInstance->SetData(TYPE_THRALL_PART2,IN_PROGRESS);

                    DoScriptText(SAY_TH_START_EVENT_PART2, me);

                    ((npc_thrall_old_hillsbrad::npc_thrall_old_hillsbradAI*)me->AI())->StartWP();
                    break;

                case GOSSIP_ACTION_INFO_DEF+3:
                    player->CLOSE_GOSSIP_MENU();
                    if(pInstance)
                        pInstance->SetData(TYPE_THRALL_PART3,IN_PROGRESS);
                    ((npc_thrall_old_hillsbrad::npc_thrall_old_hillsbradAI*)me->AI())->StartWP();
                    break;
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_thrall_old_hillsbradAI(creature);
    }
};




/*######
## npc_taretha
######*/

#define GOSSIP_ID_EPOCH1        9610                        // Thank you for helping Thrall escape, friends. Now I only hope
#define GOSSIP_ITEM_EPOCH1      "Un sorcier bizarre ?" // Strange wizard?
#define GOSSIP_ID_EPOCH2        9613                        // Yes, friends. This man was no wizard of
#define GOSSIP_ITEM_EPOCH2      "Nous vous sortirons de là, Taretha, ne vous inquiétez pas. Je ne pense pas que ce sorcier soit parti bien loin." // We'll get you out. Taretha. Don't worry. I doubt the wizard would wander too far away.

class npc_taretha : public CreatureScript
{
public:
    npc_taretha() : CreatureScript("npc_taretha")
    { }

    class npc_tarethaAI : public npc_escortAI
    {
        public:
        npc_tarethaAI(Creature *c) : npc_escortAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        void WaypointReached(uint32 i)
        override {
            switch( i )
            {
                case 6:
                    DoScriptText(SAY_TA_FREE, me);
                    break;
                case 7:
                    me->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                    break;
            }
        }
        void Reset() override {}
        void EnterCombat(Unit* who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            npc_escortAI::UpdateAI(diff);
        }

        virtual bool GossipHello(Player* player) override
        {
            if( pInstance && pInstance->GetData(TYPE_THRALL_PART3) == DONE && pInstance->GetData(TYPE_THRALL_PART4) == NOT_STARTED)
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_EPOCH1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_ID_EPOCH1, me->GetGUID());
            }
            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            if (!pInstance)
                return false;

            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            if( action == GOSSIP_ACTION_INFO_DEF+1 )
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOSSIP_ITEM_EPOCH2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_ID_EPOCH2, me->GetGUID());
            }
            if( action == GOSSIP_ACTION_INFO_DEF+2 )
            {
                player->CLOSE_GOSSIP_MENU();

                if( pInstance->GetData(TYPE_THRALL_EVENT) == IN_PROGRESS )
                {
                    pInstance->SetData(TYPE_THRALL_PART4,IN_PROGRESS);
                    if(pInstance->GetData64(DATA_EPOCH) == 0)
                         me->SummonCreature(ENTRY_EPOCH,2639.13,698.55,65.43,4.59,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,120000);

                     if (uint64 ThrallGUID = pInstance->GetData64(DATA_THRALL))
                     {
                         Creature* Thrall = (ObjectAccessor::GetCreature((*me), ThrallGUID));
                         if(Thrall)
                             ((npc_thrall_old_hillsbrad::npc_thrall_old_hillsbradAI*)Thrall->AI())->StartWP();
                     }
                }
            }
            return true;

        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_tarethaAI(creature);
    }
};




/*######
## AddSC
######*/

void AddSC_old_hillsbrad()
{

    new npc_brazen();

    new npc_erozion();

    new npc_thrall_old_hillsbrad();

    new npc_taretha();
}

