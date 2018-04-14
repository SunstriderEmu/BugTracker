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
SDName: GO_Scripts
SD%Complete: 100
SDComment: Quest support: 4285,4287,4288(crystal pylons), 4296. Field_Repair_Bot->Teaches spell 22704. Barov_journal->Teaches spell 26089
SDCategory: Game Objects
EndScriptData */

/* ContentData
go_northern_crystal_pylon
go_eastern_crystal_pylon
go_western_crystal_pylon
go_barov_journal
go_field_repair_bot_74A
go_orb_of_command
go_tablet_of_madness
go_tablet_of_the_seven
go_teleporter
go_fel_crystalforge
go_bashir_crystalforge
go_shrine_hawk
go_southfury_moonstone
go_warmaul_prison
go_green_spot_grog_keg
go_ripe_moonshine_keg
go_fermented_seed_beer_keg
go_practice_lockbox
go_crystalline_tear
go_blacksmithing_plans
go_testing_equipment
go_forged_illidari_blade
go_blood_filled_orb
go_ice_stone_ahune
go_matrix_3005a
go_matrix_punchograph_3005
go_tablet_of_theka
go_fel_reaver_control_console
go_veil_skith_cage
EndContentData */



/*######
## go_crystal_pylons (3x)
######*/


class NorthernCrystalPylon : public GameObjectScript
{
public:
    NorthernCrystalPylon() : GameObjectScript("go_northern_crystal_pylon")
    {}

    struct NorthernCrystalPylonAI : public GameObjectAI
    {
        NorthernCrystalPylonAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
            {
                player->PrepareQuestMenu(me->GetGUID());
                player->SendPreparedQuest(me->GetGUID());
            }

            if (player->GetQuestStatus(4285) == QUEST_STATUS_INCOMPLETE)
                player->AreaExploredOrEventHappens(4285);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new NorthernCrystalPylonAI(go);
    }
};

class EasternCrystalPylon : public GameObjectScript
{
public:
    EasternCrystalPylon() : GameObjectScript("go_eastern_crystal_pylon")
    {}

    struct EasternCrystalPylonAI : public GameObjectAI
    {
        EasternCrystalPylonAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
            {
                player->PrepareQuestMenu(me->GetGUID());
                player->SendPreparedQuest(me->GetGUID());
            }

            if (player->GetQuestStatus(4287) == QUEST_STATUS_INCOMPLETE)
                player->AreaExploredOrEventHappens(4287);

            return true;
        }
    };
    
    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new EasternCrystalPylonAI(go);
    }
};

class WesternCrystalPylon : public GameObjectScript
{
public:
    WesternCrystalPylon() : GameObjectScript("go_western_crystal_pylon")
    {}

    struct WesternCrystalPylonAI : public GameObjectAI
    {
        WesternCrystalPylonAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
            {
                player->PrepareQuestMenu(me->GetGUID());
                player->SendPreparedQuest(me->GetGUID());
            }

            if (player->GetQuestStatus(4288) == QUEST_STATUS_INCOMPLETE)
                player->AreaExploredOrEventHappens(4288);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new WesternCrystalPylonAI(go);
    }
};

/*######
## go_barov_journal
######*/

class BarovJournal : public GameObjectScript
{
public:
    BarovJournal() : GameObjectScript("go_barov_journal")
    {}

    struct BarovJournalAI : public GameObjectAI
    {
        BarovJournalAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->HasSkill(SKILL_TAILORING) && player->GetBaseSkillValue(SKILL_TAILORING) >= 280 && !player->HasSpell(26086))
            {
                player->CastSpell(player, 26095, TRIGGERED_NONE);
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new BarovJournalAI(go);
    }
};

class FieldRepairBot74A : public GameObjectScript
{
public:
    FieldRepairBot74A() : GameObjectScript("go_field_repair_bot_74A")
    {}

    struct FieldRepairBot74A_AI : public GameObjectAI
    {
        FieldRepairBot74A_AI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->HasSkill(SKILL_ENGINEERING) && player->GetBaseSkillValue(SKILL_ENGINEERING) >= 300 && !player->HasSpell(22704))
            {
                player->CastSpell(player, 22864, TRIGGERED_NONE);
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new FieldRepairBot74A_AI(go);
    }
};

class OrbOfCommand : public GameObjectScript
{
public:
    OrbOfCommand() : GameObjectScript("go_orb_of_command")
    {}

    struct OrbOfCommandAI : public GameObjectAI
    {
        OrbOfCommandAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->GetQuestRewardStatus(7761))
                player->TeleportTo(469, -7673.03, -1106.08, 396.65, 0.7);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new OrbOfCommandAI(go);
    }
};

class TableOfMadness : public GameObjectScript
{
public:
    TableOfMadness() : GameObjectScript("go_tablet_of_madness")
    {}

    struct TableOfMadnessAI : public GameObjectAI
    {
        TableOfMadnessAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->HasSkill(SKILL_ALCHEMY) && player->GetSkillValue(SKILL_ALCHEMY) >= 300 && !player->HasSpell(24266))
            {
                player->CastSpell(player, 24267, TRIGGERED_NONE);
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new TableOfMadnessAI(go);
    }
};

class TableOfTheSeven : public GameObjectScript
{
public:
    TableOfTheSeven() : GameObjectScript("go_tablet_of_the_seven")
    {}

    struct TableOfTheSevenAI : public GameObjectAI
    {
        TableOfTheSevenAI(GameObject* obj) : GameObjectAI(obj) { }

        //TODO: use gossip option ("Transcript the Tablet") instead, if Trinity adds support.
        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() != GAMEOBJECT_TYPE_QUESTGIVER)
                return true;

            if (player->GetQuestStatus(4296) == QUEST_STATUS_INCOMPLETE)
                player->CastSpell(player, 15065, TRIGGERED_NONE);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new TableOfTheSevenAI(go);
    }
};

class Teleporter : public GameObjectScript
{
public:
    Teleporter() : GameObjectScript("go_teleporter")
    {}

    struct TeleporterAI : public GameObjectAI
    {
        TeleporterAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            player->TeleportTo(0, 1807.07f, 336.105f, 70.3975f, 0.0f);
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new TeleporterAI(go);
    }
};

class JumpATron : public GameObjectScript
{
public:
    JumpATron() : GameObjectScript("go_jump_a_tron")
    {}

    struct JumpATronAI : public GameObjectAI
    {
        JumpATronAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->GetQuestStatus(10111) == QUEST_STATUS_INCOMPLETE)
                player->CastSpell(player, 33382, TRIGGERED_FULL_MASK);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new JumpATronAI(go);
    }
};

class EthereumPrison : public GameObjectScript
{
public:
    EthereumPrison() : GameObjectScript("go_ethereum_prison")
    {}

    struct EthereumPrisonAI : public GameObjectAI
    {
        EthereumPrisonAI(GameObject* obj) : GameObjectAI(obj) { }

        const float ethereum_NPC[2][7] =
        {
            { 20785,20790,20789,20784,20786,20783,20788 }, // hostile npc
            { 22810,22811,22812,22813,22814,22815,0 }      // fiendly npc (need script in acid ? only to cast spell reputation reward)
        };

        bool GossipHello(Player* player) override
        {
            me->SetGoState(GO_STATE_ACTIVE);
            switch (rand() % 2) {
            case 0:
                me->SummonCreature(ethereum_NPC[0][rand() % 6], me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 0.3, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                break;
            case 1:
                me->SummonCreature(ethereum_NPC[1][rand() % 5], me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 0.3, 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
                break;
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new EthereumPrisonAI(go);
    }
};

class SacredFireOfLife : public GameObjectScript
{
public:
    SacredFireOfLife() : GameObjectScript("go_sacred_fire_of_life")
    {}

    enum
    {
        NPC_ARIKARA = 10882,
    };

    struct SacredFireOfLifeAI : public GameObjectAI
    {
        SacredFireOfLifeAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
                pPlayer->SummonCreature(NPC_ARIKARA, -5008.338, -2118.894, 83.657, 0.874, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new SacredFireOfLifeAI(go);
    }
};

#define GOSSIP_FEL_CRYSTALFORGE_TEXT 31000
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN 31001
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_1 "Acheter 1 Flacon de la Bete Instable pour 10 Eclats Apogides."
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_5 "Acheter 5 Flacons de la Bete Instables pour 50 Eclats Apogides."
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN "Utiliser la cristalforge gangrenee pour un autre achat."

class FelCrystalforge : public GameObjectScript
{
public:
    FelCrystalforge() : GameObjectScript("go_fel_crystalforge")
    {}

    enum
    {
        SPELL_CREATE_1_FLASK_OF_BEAST = 40964,
        SPELL_CREATE_5_FLASK_OF_BEAST = 40965,
    };

    struct FelCrystalforgeAI : public GameObjectAI
    {
        FelCrystalforgeAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER) /* != GAMEOBJECT_TYPE_QUESTGIVER) */
                pPlayer->PrepareQuestMenu(me->GetGUID()); /* return true*/

            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            pPlayer->SEND_GOSSIP_MENU_TEXTID(GOSSIP_FEL_CRYSTALFORGE_TEXT, me->GetGUID());

            return true;
        }

        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF:
                player->CastSpell(player, SPELL_CREATE_1_FLASK_OF_BEAST, TRIGGERED_NONE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CastSpell(player, SPELL_CREATE_5_FLASK_OF_BEAST, TRIGGERED_NONE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU_TEXTID(GOSSIP_FEL_CRYSTALFORGE_TEXT, me->GetGUID());
                break;
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new FelCrystalforgeAI(go);
    }
};

/*######
## 
######*/

class BashirCrystalforge : public GameObjectScript
{
public:
    BashirCrystalforge() : GameObjectScript("go_bashir_crystalforge")
    {}

    enum
    {
        SPELL_CREATE_1_FLASK_OF_SORCERER = 40968,
        SPELL_CREATE_5_FLASK_OF_SORCERER = 40970,
        APEXIS_SHARD = 32569,
    };

    struct BashirCrystalforgeAI : public GameObjectAI
    {
        BashirCrystalforgeAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (!pPlayer->HasItemCount(APEXIS_SHARD, 50, false))
                pPlayer->CastSpell(pPlayer, SPELL_CREATE_1_FLASK_OF_SORCERER, TRIGGERED_NONE);
            else
                pPlayer->CastSpell(pPlayer, SPELL_CREATE_5_FLASK_OF_SORCERER, TRIGGERED_NONE);

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new BashirCrystalforgeAI(go);
    }
};

class ShrineHawk : public GameObjectScript
{
public:
    ShrineHawk() : GameObjectScript("go_shrine_hawk")
    {}

    enum
    {
        QUEST_HAWKS_ESSENCE  = 10992,
    };

    struct ShrineHawkAI : public GameObjectAI
    {
        ShrineHawkAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        { //workaround as WDB data for this GO seem to be crazy (the GO from the two previous quests are working fine...)
            if (pPlayer->GetQuestStatus(QUEST_HAWKS_ESSENCE) == QUEST_STATUS_INCOMPLETE)
            {
                ItemPosCountVec dest;
                uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 32356, 1);
                if (msg == EQUIP_ERR_OK)
                {
                    Item* item = pPlayer->StoreNewItem(dest, 32356, true);
                    pPlayer->SendNewItem(item, 1, true, false);
                }
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ShrineHawkAI(go);
    }
};

/*######
## 
######*/

class SouthfuryMoonstone : public GameObjectScript
{
public:
    SouthfuryMoonstone() : GameObjectScript("go_southfury_moonstone")
    {}

    enum
    {
        NPC_RIZZLE = 23002,
        SPELL_BLACKJACK = 39865, //stuns player
        SPELL_SUMMON_RIZZLE = 39866
    };

    struct SouthfuryMoonstoneAI : public GameObjectAI
    {
        SouthfuryMoonstoneAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            //implicitTarget=48 not implemented as of writing this code, and manual summon may be just ok for our purpose
            //pPlayer->CastSpell(pPlayer,SPELL_SUMMON_RIZZLE, TRIGGERED_NONE);

            if (Creature* pCreature = pPlayer->SummonCreature(NPC_RIZZLE, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0))
                pCreature->CastSpell(pPlayer, SPELL_BLACKJACK, TRIGGERED_NONE);

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new SouthfuryMoonstoneAI(go);
    }
};

class WarmaulPrison : public GameObjectScript
{
public:
    WarmaulPrison() : GameObjectScript("go_warmaul_prison")
    {}

    enum
    {
        QUEST_SURVIVORS = 9948,
        MAGHAR_PRISONER = 18428,
    };

    struct WarmaulPrisonAI : public GameObjectAI
    {
        WarmaulPrisonAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(QUEST_SURVIVORS) == QUEST_STATUS_INCOMPLETE)
                pPlayer->KilledMonsterCredit(MAGHAR_PRISONER, ObjectGuid::Empty);

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new WarmaulPrisonAI(go);
    }
};

enum Keg
{
    QUEST_SMALLEST_CREATURES = 10720,
};

class GreenSpotGrogKeg : public GameObjectScript
{
public:
    GreenSpotGrogKeg() : GameObjectScript("go_green_spot_grog_keg")
    {}

    enum
    {
        GREEN_SPOT_GROG_KEG_CREDIT = 22356
    };

    struct GreenSpotGrogKegAI : public GameObjectAI
    {
        GreenSpotGrogKegAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(QUEST_SMALLEST_CREATURES) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature* credit = pPlayer->FindNearestCreature(GREEN_SPOT_GROG_KEG_CREDIT, 5, true)) {
                    Unit::DealDamage(pPlayer, credit, credit->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                    credit->Respawn();
                }
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new GreenSpotGrogKegAI(go);
    }
};


class RipeMoonshineKeg : public GameObjectScript
{
public:
    RipeMoonshineKeg() : GameObjectScript("go_ripe_moonshine_keg")
    {}
    
    enum
    {
        RIPE_MOONSHINE_KEG_CREDIT = 22367
    };

    struct RipeMoonshineKegAI : public GameObjectAI
    {
        RipeMoonshineKegAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(QUEST_SMALLEST_CREATURES) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature* credit = pPlayer->FindNearestCreature(RIPE_MOONSHINE_KEG_CREDIT, 5, true)) {
                    Unit::DealDamage(pPlayer, credit, credit->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                    credit->Respawn();
                }
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new RipeMoonshineKegAI(go);
    }
};

class FermentedSeedBeerKeg : public GameObjectScript
{
public:
    FermentedSeedBeerKeg() : GameObjectScript("go_fermented_seed_beer_keg")
    {}
    
    enum
    {
        FERMENTED_SEED_BEER_KEG_CREDIT = 22368,
    };

    struct FermentedSeedBeerKegAI : public GameObjectAI
    {
        FermentedSeedBeerKegAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(QUEST_SMALLEST_CREATURES) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature* credit = pPlayer->FindNearestCreature(FERMENTED_SEED_BEER_KEG_CREDIT, 5, true)) {
                    Unit::DealDamage(pPlayer, credit, credit->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
                    credit->Respawn();
                }
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new FermentedSeedBeerKegAI(go);
    }
};

class PracticeLockbox : public GameObjectScript
{
public:
    PracticeLockbox() : GameObjectScript("go_practice_lockbox")
    {}

    struct PracticeLockboxAI : public GameObjectAI
    {
        PracticeLockboxAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (25 > rand() % 100)
            {
                switch (rand() % 2)
                {
                case 0:
                    me->CastSpell(pPlayer, 10017);
                    break;
                case 1:
                    me->CastSpell(pPlayer, 10018);
                    break;
                }
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new PracticeLockboxAI(go);
    }
};

class CrystallineTear : public GameObjectScript
{
public:
    CrystallineTear() : GameObjectScript("go_crystalline_tear")
    {}

    struct CrystallineTearAI : public GameObjectAI
    {
        CrystallineTearAI(GameObject* obj) : GameObjectAI(obj) { }

        void QuestAccept(Player* pPlayer, Quest const* quest) override
        {
            if (quest->GetQuestId() == 8519)
            {
                WorldPacket data(SMSG_TRIGGER_CINEMATIC, 4);
                data << uint32(2);
                pPlayer->GetSession()->SendPacket(&data);
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new CrystallineTearAI(go);
    }
};

class BlacksmithingPlans : public GameObjectScript
{
public:
    BlacksmithingPlans() : GameObjectScript("go_blacksmithing_plans")
    {}

    enum
    {
        ENTRY_CRIMSON = 11120
    };

    struct BlacksmithingPlansAI : public GameObjectAI
    {
        BlacksmithingPlansAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            pPlayer->SendLoot(me->GetGUID(), LOOT_CORPSE);
            if (Creature* crimson = me->SummonCreature(ENTRY_CRIMSON, 3567.002930, -2931.949951, 125.001495, 5.163120, TEMPSUMMON_DEAD_DESPAWN, 0))
                crimson->AI()->AttackStart(pPlayer);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new BlacksmithingPlansAI(go);
    }
};

class TestingEquipment : public GameObjectScript
{
public:
    TestingEquipment() : GameObjectScript("go_testing_equipment")
    {}

    enum
    {
        QUEST_BATCH_OF_OOZE = 4294,
        ITEM_TESTED_SAMPLE = 15102,
        ITEM_SLIME_SAMPLE = 12235,
    };

    struct TestingEquipmentAI : public GameObjectAI
    {
        TestingEquipmentAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(QUEST_BATCH_OF_OOZE) == QUEST_STATUS_INCOMPLETE) {
                if (pPlayer->HasItemCount(ITEM_SLIME_SAMPLE, 1, false)) {
                    ItemPosCountVec dest;
                    uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_TESTED_SAMPLE, 1);
                    if (msg == EQUIP_ERR_OK) {
                        Item* item = pPlayer->StoreNewItem(dest, ITEM_TESTED_SAMPLE, true);
                        pPlayer->SendNewItem(item, 1, true, false);
                        pPlayer->DestroyItemCount(ITEM_SLIME_SAMPLE, 1, true, true);
                    }
                }

                return false;
            }

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new TestingEquipmentAI(go);
    }
};

/*######
## Quest 1126: Hive in the Tower
######*/

class HivePod : public GameObjectScript
{
public:
    HivePod() : GameObjectScript("go_hive_pod")
    {}

    enum eHives
    {
        QUEST_HIVE_IN_THE_TOWER = 9544,
        NPC_HIVE_AMBUSHER = 13301
    };

    struct HivePodAI : public GameObjectAI
    {
        HivePodAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            pPlayer->SendLoot(me->GetGUID(), LOOT_CORPSE);
            me->SummonCreature(NPC_HIVE_AMBUSHER, me->GetPositionX() + 1, me->GetPositionY(), me->GetPositionZ(), me->GetAbsoluteAngle(pPlayer), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
            me->SummonCreature(NPC_HIVE_AMBUSHER, me->GetPositionX(), me->GetPositionY() + 1, me->GetPositionZ(), me->GetAbsoluteAngle(pPlayer), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new HivePodAI(go);
    }
};

class ForgedIllidariBlade : public GameObjectScript
{
public:
    ForgedIllidariBlade() : GameObjectScript("go_forged_illidari_blade")
    {}

    struct ForgedIllidariBladeAI : public GameObjectAI
    {
        ForgedIllidariBladeAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(10679) == QUEST_STATUS_INCOMPLETE) {
                ItemPosCountVec dest;
                uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 30876, 1);
                if (msg == EQUIP_ERR_OK) {
                    Item* item = pPlayer->StoreNewItem(dest, 30876, true);
                    pPlayer->SendNewItem(item, 1, true, false);
                }

                return true;
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new ForgedIllidariBladeAI(go);
    }
};

class BloodFilledOrb : public GameObjectScript
{
public:
    BloodFilledOrb() : GameObjectScript("go_blood_filled_orb")
    {}

    struct BloodFilledOrbAI : public GameObjectAI
    {
        BloodFilledOrbAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->GetQuestStatus(9692) == QUEST_STATUS_INCOMPLETE)
                me->SummonCreature(17830, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 60000);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new BloodFilledOrbAI(go);
    }
};

class CorruptionPlans : public GameObjectScript
{
public:
    CorruptionPlans() : GameObjectScript("go_corruption_plans")
    {}

    enum
    {
        NPC_BLACKGUARD_SWORDSMITH = 11121
    };

    struct CorruptionPlansAI : public GameObjectAI
    {
        CorruptionPlansAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            pPlayer->SendLoot(me->GetGUID(), LOOT_CORPSE);
            if (Creature* swordsmith = me->SummonCreature(NPC_BLACKGUARD_SWORDSMITH, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 45000))
                swordsmith->AI()->AttackStart(pPlayer);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new CorruptionPlansAI(go);
    }
};

class IceStoneAhune : public GameObjectScript
{
public:
    IceStoneAhune() : GameObjectScript("go_ice_stone_ahune")
    {}

    struct IceStoneAhuneAI : public GameObjectAI
    {
        IceStoneAhuneAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* pPlayer) override
        {
            if (pPlayer->HasItemCount(34953, 1, false)) {
                me->SummonCreature(25740, -90.151627, -243.480011, -1.102788, 1.621057, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 600000);
                me->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                me->SetLootState(GO_JUST_DEACTIVATED);
                me->SetRespawnTime(1 * DAY);
            }

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new IceStoneAhuneAI(go);
    }
};

class Matrix3005A : public GameObjectScript
{
public:
    Matrix3005A() : GameObjectScript("go_matrix_3005a")
    {}

    struct Matrix3005A_AI : public GameObjectAI
    {
        Matrix3005A_AI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->HasItemCount(9279, 1, false)) {
                player->DestroyItemCount(9279, 1, true);
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 9280, 1);
                if (msg == EQUIP_ERR_OK) {
                    Item* item = player->StoreNewItem(dest, 9280, true);
                    player->SendNewItem(item, 1, true, false);
                }
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new Matrix3005A_AI(go);
    }
};

class MatrixPunchograph3005 : public GameObjectScript
{
public:
    MatrixPunchograph3005() : GameObjectScript("go_matrix_punchograph_3005")
    {}

    struct MatrixPunchograph3005_AI : public GameObjectAI
    {
        MatrixPunchograph3005_AI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            uint32 itemEntry = 0;

            switch (me->GetEntry()) {
            case 142475: // B
                itemEntry = 14639;
                break;
            case 142696: // D
                itemEntry = 4413;
            default:
                break;
            }

            if (!itemEntry)
                return true;

            if (player->HasItemCount(9327, 1, false) && !player->HasItemCount(itemEntry, 1, true)) {
                //player->DestroyItemCount(9327, 1, true);
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemEntry, 1);
                if (msg == EQUIP_ERR_OK) {
                    Item* item = player->StoreNewItem(dest, itemEntry, true);
                    player->SendNewItem(item, 1, true, false);
                }
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new MatrixPunchograph3005_AI(go);
    }
};

class TabletOfTheka : public GameObjectScript
{
public:
    TabletOfTheka() : GameObjectScript("go_tablet_of_theka")
    {}

    struct TabletOfThekaAI : public GameObjectAI
    {
        TabletOfThekaAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (Creature* theka = player->FindNearestCreature(7272, 150.0f, false))
                player->AreaExploredOrEventHappens(2936);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new TabletOfThekaAI(go);
    }
};

class FelReaverControlConsole : public GameObjectScript
{
public:
    FelReaverControlConsole() : GameObjectScript("go_fel_reaver_control_console")
    {}

    struct FelReaverControlConsoleAI : public GameObjectAI
    {
        FelReaverControlConsoleAI(GameObject* obj) : GameObjectAI(obj) { }

        // Not working for some reason
        bool GossipHello(Player* player) override
        {
            if (Creature* felreaver = player->SummonCreature(21949, -2646.709961, 2673.530029, 74.858299, 4.974770, TEMPSUMMON_MANUAL_DESPAWN, 0))
                player->CastSpell(felreaver, 530, TRIGGERED_FULL_MASK);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new FelReaverControlConsoleAI(go);
    }
};

/*########
 #### go_veil_skith_cage
 #####*/

enum MissingFriends
{
    QUEST_MISSING_FRIENDS = 10852,
    NPC_CAPTIVE_CHILD = 22314,
    SAY_FREE = 0,
};

class go_veil_skith_cage : public GameObjectScript
{
public:
    go_veil_skith_cage() : GameObjectScript("go_veil_skith_cage") { }

    struct go_veil_skith_cageAI : public GameObjectAI
    {
        go_veil_skith_cageAI(GameObject* obj) : GameObjectAI(obj) { }

        bool GossipHello(Player* player) override
        {
            if (player->GetQuestStatus(QUEST_MISSING_FRIENDS) == QUEST_STATUS_INCOMPLETE)
            {
                std::list<Creature*> ChildrenList;
                me->GetCreatureListWithEntryInGrid(ChildrenList, NPC_CAPTIVE_CHILD, INTERACTION_DISTANCE);
                for (std::list<Creature*>::const_iterator itr = ChildrenList.begin(); itr != ChildrenList.end(); ++itr)
                {
                    me->UseDoorOrButton();
                    player->KilledMonsterCredit(NPC_CAPTIVE_CHILD, (*itr)->GetGUID());
                    (*itr)->DespawnOrUnsummon(5000);
                    (*itr)->GetMotionMaster()->MovePoint(1, me->GetPositionX() + 5, me->GetPositionY(), me->GetPositionZ());
                    (*itr)->AI()->Talk(SAY_FREE);
                    (*itr)->GetMotionMaster()->Clear();
                }
            }
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_veil_skith_cageAI(go);
    }
};

/*######
## AddSC
######*/

void AddSC_go_scripts()
{
    new NorthernCrystalPylon();
    new EasternCrystalPylon();
    new WesternCrystalPylon();
    new BarovJournal();
    new FieldRepairBot74A();
    new OrbOfCommand();
    new TableOfMadness();
    new TableOfTheSeven();
    new Teleporter();
    new JumpATron();
    new EthereumPrison();
    new SacredFireOfLife();
    new FelCrystalforge();
    new BashirCrystalforge();
    new ShrineHawk();
    new SouthfuryMoonstone();
    new WarmaulPrison();
    new GreenSpotGrogKeg();
    new RipeMoonshineKeg();
    new FermentedSeedBeerKeg();
    new PracticeLockbox();
    new CrystallineTear();
    new BlacksmithingPlans();
    new TestingEquipment();
    new HivePod();
    new ForgedIllidariBlade();
    new BloodFilledOrb();
    new CorruptionPlans();
    new IceStoneAhune();
    new Matrix3005A();
    new MatrixPunchograph3005();
    new TabletOfTheka();
    new FelReaverControlConsole();
    new go_veil_skith_cage();
}
