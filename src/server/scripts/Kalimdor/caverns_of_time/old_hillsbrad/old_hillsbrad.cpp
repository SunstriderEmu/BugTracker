
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
            // "Je suis prêt à aller à Fort-de-Durn."
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " I am ready to go to Durnholde Keep.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            SEND_PREPARED_GOSSIP_MENU(player, me);
            return true;
        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
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
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I need a pack of Incendiary Bombs.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1); //   "J'ai besoin d'un paquet de bombes incendiaires."

            if( !player->GetQuestRewardStatus(QUEST_ENTRY_RETURN) && player->GetQuestStatus(QUEST_ENTRY_RETURN) == QUEST_STATUS_COMPLETE )
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Take me back to my time.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2); //Renvoyez-moi à mon époque. 

            player->SEND_GOSSIP_MENU_TEXTID(9778, me->GetGUID());

            return true;

        }


        virtual bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
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
#define GOSSIP_ITEM_SKARLOC1    "Taretha cannot see you, Thrall." // "Taretha ne peut pas vous voir, Thrall." 
#define GOSSIP_ID_SKARLOC2      9579                        // What do you mean by this? Is Taretha in danger?
#define GOSSIP_ITEM_SKARLOC2    "The situation is rather complicated, Thrall. It would be best for you to head into the mountains now, before more of Blackmoore's men show up. We'll make sure Taretha is safe." // "La situation est assez compliquée, Thrall. Il vaudrait mieux que vous filiez vers les montagnes dès maintenant, avant que d'autres hommes de Landenoire ne se montrent. Nous veillerons à la sécurité de Taretha." 
#define GOSSIP_ID_SKARLOC3      9580

#define GOSSIP_ID_TARREN        9597                        // Tarren mill is beyond these trees...
#define GOSSIP_ITEM_TARREN      "We're ready, Thrall." // "Nous sommes prêts, Thrall." 

#define GOSSIP_ID_COMPLETE      9578                        // Thank you friends, I owe my freedom to you. Where is Taretha? I hoped to see her


class npc_thrall_old_hillsbrad : public CreatureScript
{
public:
    npc_thrall_old_hillsbrad() : CreatureScript("npc_thrall_old_hillsbrad")
    { }

    class npc_thrall_old_hillsbradAI : public EscortAI
    {
        public:
        npc_thrall_old_hillsbradAI(Creature *c) : EscortAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
            me->SetKeepActive(30 * MINUTE*IN_MILLISECONDS);

            AddWaypoint(0, 2230.91, 118.765, 82.2947);
            AddWaypoint(1, 2230.33, 114.980, 82.2946);
            AddWaypoint(2, 2233.36, 111.057, 82.2996);
            AddWaypoint(3, 2231.17, 108.486, 82.6624);
            AddWaypoint(4, 2220.22, 114.605, 89.4264);
            AddWaypoint(5, 2215.23, 115.990, 89.4549);
            AddWaypoint(6, 2210.00, 106.849, 89.4549);
            AddWaypoint(7, 2205.66, 105.234, 89.4549);
            //spawn armorer
            AddWaypoint(8, 2192.26, 112.618, 89.4549);

            //get weapon
            AddWaypoint(9, 2181.28, 118.612, 89.4549, 0.0f, 8000);
            //get armor
            AddWaypoint(10, 2181.62, 120.385, 89.4549, 0.0f, 5000);

            AddWaypoint(11, 2189.44, 113.922, 89.4549);
            AddWaypoint(12, 2195.63, 110.584, 89.4549);
            AddWaypoint(13, 2201.09, 115.115, 89.4549);
            AddWaypoint(14, 2204.34, 121.036, 89.4355);
            //first ambush
            AddWaypoint(15, 2208.66, 129.127, 87.9560);
            AddWaypoint(16, 2193.09, 137.940, 88.2164);
            AddWaypoint(17, 2173.39, 149.064, 87.9227);
            AddWaypoint(18, 2164.25, 137.965, 85.0595);
            AddWaypoint(19, 2149.31, 125.645, 77.0858);
            AddWaypoint(20, 2142.78, 127.173, 75.5954);
            //second ambush
            AddWaypoint(21, 2139.28, 133.952, 73.6386);
            AddWaypoint(22, 2139.54, 155.235, 67.1269);
            AddWaypoint(23, 2145.38, 167.551, 64.8974);
            AddWaypoint(24, 2134.28, 175.304, 67.9446);
            AddWaypoint(25, 2118.08, 187.387, 68.8141);
            //third ambush
            AddWaypoint(26, 2105.88, 195.461, 65.1854);
            AddWaypoint(27, 2096.77, 196.939, 65.2117);
            AddWaypoint(28, 2083.90, 209.395, 64.8736);
            //in front of keeps gate, meeting scarloc
            AddWaypoint(29, 2067.84, 224.376, 64.8022, 0.0f, 30000);

            //ref point after skarloc fight
            AddWaypoint(30, 2055.40, 242.90, 63.3418);

            //mount up!
            AddWaypoint(31, 2039.20, 266.460, 63.0182, 0.0f, 10000);
            AddWaypoint(32, 2011.77, 278.478, 65.3388);
            AddWaypoint(33, 2005.08, 289.676, 66.1179);
            AddWaypoint(34, 2033.11, 337.450, 66.0948);
            AddWaypoint(35, 2070.30, 416.208, 66.0893);
            AddWaypoint(36, 2086.76, 469.768, 65.9182);
            //possible road ambush
            AddWaypoint(37, 2101.70, 497.955, 61.7881);

            AddWaypoint(38, 2133.39, 530.933, 55.3700, 0.0f, 5000);
            AddWaypoint(39, 2157.91, 559.635, 48.5157);
            AddWaypoint(40, 2167.34, 586.191, 42.4394);
            AddWaypoint(41, 2174.17, 637.643, 33.9002);
            AddWaypoint(42, 2179.31, 656.053, 34.723);
            AddWaypoint(43, 2183.65, 670.941, 34.0318);
            AddWaypoint(44, 2201.50, 668.616, 36.1236);
            AddWaypoint(45, 2221.56, 652.747, 36.6153);
            AddWaypoint(46, 2238.97, 640.125, 37.2214);
            AddWaypoint(47, 2251.17, 620.574, 40.1473);
            AddWaypoint(48, 2261.98, 595.303, 41.4117);
            AddWaypoint(49, 2278.67, 560.172, 38.9090);
            AddWaypoint(50, 2336.72, 528.327, 40.9369);
            AddWaypoint(51, 2381.04, 519.612, 37.7312);
            AddWaypoint(52, 2412.20, 515.425, 39.2068);
            AddWaypoint(53, 2452.39, 516.174, 42.9387);
            AddWaypoint(54, 2467.38, 539.389, 47.4992);
            AddWaypoint(55, 2470.70, 554.333, 46.6668);
            AddWaypoint(56, 2478.07, 575.321, 55.4549);
            AddWaypoint(57, 2480.00, 585.408, 56.6921);
            AddWaypoint(58, 2482.67, 608.817, 55.6643);
            //demount
            AddWaypoint(59, 2485.62, 626.061, 58.0132, 0.0f, 2000);
            //scare the shit out of horse, so it'll run off
            AddWaypoint(60, 2486.91, 626.356, 58.0761);

            AddWaypoint(61, 2488.58, 660.940, 57.3913);
            AddWaypoint(62, 2502.56, 686.059, 55.6252);
            AddWaypoint(63, 2502.08, 694.360, 55.5083);
            AddWaypoint(64, 2491.46, 694.321, 55.7163);
            AddWaypoint(65, 2491.10, 703.300, 55.7630);
            AddWaypoint(66, 2485.64, 702.992, 55.7917);

            AddWaypoint(67, 2479.10, 695.291, 55.7901, 0.0f, 10000);
            //spawn mobs
            AddWaypoint(68, 2476.75, 693.689, 55.7960);
            AddWaypoint(69, 2475.39, 695.983, 55.8146);
            AddWaypoint(70, 2477.75, 694.473, 55.7945);
            //meet mobs in doorway
            AddWaypoint(71, 2481.27, 697.747, 55.7910);

            AddWaypoint(72, 2486.31, 703.131, 55.7861, 0.0f, 5000);
            AddWaypoint(73, 2490.76, 703.511, 55.7662);
            AddWaypoint(74, 2491.30, 694.792, 55.7195);
            AddWaypoint(75, 2518.69, 693.876, 55.1383);
            AddWaypoint(76, 2531.33, 681.914, 55.1383);
            AddWaypoint(77, 2568.25, 682.654, 55.1778);
            AddWaypoint(78, 2589.61, 689.981, 55.1421);
            AddWaypoint(79, 2634.74, 679.833, 54.6613);
            AddWaypoint(80, 2630.41, 661.464, 54.2761);
            AddWaypoint(81, 2629.00, 656.982, 56.0651);
            //stop in church
            AddWaypoint(82, 2620.84, 633.007, 56.0300, 0.0f, 3000);
            //summon
            AddWaypoint(83, 2622.99, 639.178, 56.0300);

            AddWaypoint(84, 2628.73, 656.693, 56.0610, 0.0f, 5000);
            AddWaypoint(85, 2630.34, 661.135, 54.2738);
            AddWaypoint(86, 2635.38, 672.243, 54.4508);
            AddWaypoint(87, 2644.13, 668.158, 55.3797);
            AddWaypoint(88, 2646.82, 666.740, 56.9898);
            AddWaypoint(89, 2658.22, 665.432, 57.1725);
            AddWaypoint(90, 2661.88, 674.849, 57.1725);
            AddWaypoint(91, 2656.23, 677.208, 57.1725);

            AddWaypoint(92, 2652.28, 670.270, 61.9353);
            //summon inn
            AddWaypoint(93, 2650.79, 664.290, 61.9302);
            AddWaypoint(94, 2658.19, 660.454, 61.9320, 0.0f, 5000);
            //speak with Taretha
            AddWaypoint(95, 2660.57, 659.173, 61.9370);

            //epoch calls
            AddWaypoint(96, 2658.19, 660.454, 61.9320, 0.0f, 5000);
            //taretha "dies"
            AddWaypoint(97, 2659.84, 659.482, 61.9361, 0.0f, 5000);

            AddWaypoint(98, 2654.28, 662.722, 61.9313);
            AddWaypoint(99, 2652.37, 670.561, 61.9368);
            AddWaypoint(100, 2656.05, 676.761, 57.1727);
            AddWaypoint(101, 2658.49, 677.166, 57.1727);
            AddWaypoint(102, 2659.28, 667.117, 57.1727);
            AddWaypoint(103, 2649.71, 665.387, 57.1727);
            //he's outside inn here
            AddWaypoint(104, 2634.79, 672.964, 54.4577);

            //getting ready here, must start attack before 30secs up
            AddWaypoint(105, 2635.06, 673.892, 54.4713, 0.0f, 30000);

            //ref point, will move here when all dead and meet Taretha
            AddWaypoint(106, 2634.79, 672.964, 54.4577, 0.0f, 60000);

            //run off
            AddWaypoint(107, 2631.72, 665.629, 54.2923);
            AddWaypoint(108, 2647.40, 640.530, 55.7634);

            HadMount = false;
            LowHp = false;
        }
    
        InstanceScript *pInstance;
    
        bool LowHp;
        bool HadMount;
    
        void WaypointReached(uint32 i, uint32 pathID)
        override {
            if (!pInstance)
                return;
    
            switch( i )
            {
                case 8:
                    SetRun(false);
                    me->SummonCreature(18764, 2181.87, 112.46, 89.45, 0.26, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    break;
                case 9:
                    DoScriptText(SAY_TH_ARMORY, me);
                    SetRun(false);
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
                    SetRun(true);
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
                    me->SummonCreature(ENTRY_SCARLOC, 2036.48,271.22,63.43,5.27,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,30000);
                    //temporary,skarloc should rather be triggered to walk up to thrall
                    break;
                case 30:
                    SetEscortPaused(true);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    break;
                case 31:
                    DoScriptText(SAY_TH_MOUNTS_UP, me);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                    DoMount();
                    SetRun(true);
                    HadMount = true;
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
                    SetEscortPaused(true);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    pInstance->SetData(TYPE_THRALL_PART2, DONE);
                    break;
                case 64:
                    SetRun(false);
                    break;
                case 68:
                    me->SummonCreature(MOB_ENTRY_BARN_PROTECTOR,2500.22,692.60,55.50,2.84,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_BARN_LOOKOUT,2500.13,696.55,55.51,3.38,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_BARN_GUARDSMAN,2500.55,693.64,55.50,3.14,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_BARN_GUARDSMAN,2500.94,695.81,55.50,3.14,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    break;
                case 71:
                    SetRun(true);
                    break;
                case 81:
                    SetRun(false);
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
                    SetRun(false);
                    break;
                case 93:
                    me->SummonCreature(MOB_ENTRY_INN_PROTECTOR,2652.71,660.31,61.93,1.67,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_INN_LOOKOUT,2648.96,662.59,61.93,0.79,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_INN_GUARDSMAN,2657.36,662.34,61.93,2.68,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    me->SummonCreature(MOB_ENTRY_INN_GUARDSMAN,2656.39,659.77,61.93,2.61,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    break;
                case 94:
                    SetRun(false);
                    if (ObjectGuid tarethaGUID = ObjectGuid(pInstance->GetData64(DATA_TARETHA)))
                    {
                        if (Unit* Taretha = ObjectAccessor::GetUnit((*me), tarethaGUID))
                            DoScriptText(SAY_TA_ESCAPED, Taretha, me);
                    }
                    break;
                case 95:
                    DoScriptText(SAY_TH_MEET_TARETHA, me);
                    pInstance->SetData(TYPE_THRALL_PART3,DONE);
                    SetEscortPaused(true);
                    break;
                case 96:
                    DoScriptText(SAY_TH_EPOCH_WONDER, me);
                     me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                    break;
                case 97:
                    DoScriptText(SAY_TH_EPOCH_KILL_TARETHA, me);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                    SetRun(true);
                    break;
                case 98:
                    //trigger epoch Yell("Thrall! Come outside and face your fate! ....")
                    //from here, thrall should not never be allowed to move to point 106 which he currently does.
                    break;
                case 106:
                    {
                        //trigger taretha to run down outside
                        if (ObjectGuid tarethaGUID = ObjectGuid(pInstance->GetData64(DATA_TARETHA)))
                        {
                            if (Creature* Taretha = (ObjectAccessor::GetCreature(*me, tarethaGUID)))
                                if (Player* player = GetPlayerForEscort())
                                    ((EscortAI*)(Taretha->AI()))->Start(false, true, player->GetGUID());
                        }
    
                        //kill credit creature for quest
                        Map *map = me->GetMap();
                        Map::PlayerList const& players = map->GetPlayers();
                        if (!players.isEmpty() && map->IsDungeon())
                        {
                            for(const auto & player : players)
                            {
                                if (Player* pPlayer = player.GetSource())
                                    pPlayer->KilledMonsterCredit(20156, me->GetGUID());
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
            SetEscortPaused(false);
        }

        void DoMount()
        {
            me->Mount(SKARLOC_MOUNT_MODEL);
            me->SetSpeedRate(MOVE_RUN, SPEED_MOUNT);
            SetRun(true);
        }

        void DoDismount()
        {
            me->Dismount();
            me->SetSpeedRate(MOVE_RUN, SPEED_RUN);
        }

        void JustEngagedWith(Unit* who)
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
            EscortAI::UpdateAI(diff);
    
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
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "We are ready to get you out of here, Thrall. Let's go!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1); //"Nous allons vous sortir de là, Thrall. On y va !"
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
            ClearGossipMenuFor(player);
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

                    ((EscortAI*)(me->AI()))->Start(true, true, player->GetGUID());
                    ((EscortAI*)(me->AI()))->SetDespawnAtEnd(false);
                    ((EscortAI*)(me->AI()))->SetDespawnAtFar(false);
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
//"Un sorcier bizarre ?"
#define GOSSIP_ITEM_EPOCH1      "Strange wizard?"
#define GOSSIP_ID_EPOCH2        9613                        // Yes, friends. This man was no wizard of
//"Nous vous sortirons de là, Taretha, ne vous inquiétez pas. Je ne pense pas que ce sorcier soit parti bien loin."
#define GOSSIP_ITEM_EPOCH2      "We'll get you out. Taretha. Don't worry. I doubt the wizard would wander too far away."

class npc_taretha : public CreatureScript
{
public:
    npc_taretha() : CreatureScript("npc_taretha")
    { }

    class npc_tarethaAI : public EscortAI
    {
        public:
        npc_tarethaAI(Creature *c) : EscortAI(c)
        {
            pInstance = ((InstanceScript*)c->GetInstanceScript());
        }
    
        InstanceScript *pInstance;
    
        void WaypointReached(uint32 i, uint32 pathID)
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
        void JustEngagedWith(Unit* who) override {}
    
        void UpdateAI(const uint32 diff)
        override {
            EscortAI::UpdateAI(diff);
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
            ClearGossipMenuFor(player);
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

                     if (ObjectGuid ThrallGUID = ObjectGuid(pInstance->GetData64(DATA_THRALL)))
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

