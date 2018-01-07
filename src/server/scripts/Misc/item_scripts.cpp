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
SDName: Item_Scripts
SD%Complete: 100
SDComment: Items for a range of different items. See content below (in script)
SDCategory: Items
EndScriptData */

/* ContentData
item_area_52_special(i28132)        Prevents abuse of this item
item_blackwhelp_net(i31129)         Quest Whelps of the Wyrmcult (q10747). Prevents abuse
item_draenei_fishing_net(i23654)    Hacklike implements chance to spawn item or creature
item_disciplinary_rod               Prevents abuse
item_nether_wraith_beacon(i31742)   Summons creatures for quest Becoming a Spellfire Tailor (q10832)
item_flying_machine(i34060,i34061)  Engineering crafted flying machines
item_gor_dreks_ointment(i30175)     Protecting Our Own(q10488)
item_muiseks_vessel                 Cast on creature, they must be dead(q 3123,3124,3125,3126,3127)
item_only_for_flight                Items which should only useable while flying
item_protovoltaic_magneto_collector Prevents abuse
item_razorthorn_flayer_gland        Quest Discovering Your Roots (q11520) and Rediscovering Your Roots (q11521). Prevents abuse
item_tame_beast_rods(many)          Prevent cast on any other creature than the intended (for all tame beast quests)
item_soul_cannon(i32825)            Prevents abuse of this item
item_sparrowhawk_net(i32321)        Quest To Catch A Sparrowhawk (q10987). Prevents abuse
item_voodoo_charm                   Provide proper error message and target(q2561)
item_vorenthals_presence(i30259)    Prevents abuse of this item
item_zezzak_shard(i31463)           Quest The eyes of Grillok (q10813). Prevents abuse
item_inoculating_crystal            Quest Inoculating. Prevent abuse
item_cantation_manifestation        Quest 1960 (Horde) && 1920 (Alliance) : Rift Spawn *4
item_bloodmaul_keg                  Quests 10512 && 10545
item_purification_mixture           Quest 9361
item_staff_elders                   Quest 10369
item_attuned_crystal_cores
item_orwins_shovel
item_netherwave_net
EndContentData */


#include "SpellMgr.h"
#include "Spell.h"
#include "WorldPacket.h"

class ItemArea52Special : ItemScript
{
public:
    ItemArea52Special() : ItemScript("item_area_52_special") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (player->GetAreaId() == 3803)
        {
            return false;
        }
        else
        {
            player->SendEquipError(EQUIP_ERR_OUT_OF_RANGE, _Item, nullptr);
            return true;
        }
    }
};

class ItemOnlyForFlight : ItemScript
{
public:
    ItemOnlyForFlight() : ItemScript("item_only_for_flight") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        uint32 itemId = _Item->GetEntry();
        bool disabled = false;

        //for special scripts
        switch (itemId)
        {
        case 24538:
            if (player->GetAreaId() != 3628)
                disabled = true;
            break;
        case 34489:
            if (player->GetZoneId() != 4080)
                disabled = true;
            break;
        }

        // allow use in flight only
        if (player->IsInFlight() && !disabled)
            return false;

        // error
        player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, _Item, nullptr);
        return true;
    }
};

class ItemBlackwhelpNet : ItemScript
{
public:
    ItemBlackwhelpNet() : ItemScript("item_blackwhelp_net") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 21387)
            return false;

        player->SendEquipError(EQUIP_ERR_YOU_CAN_NEVER_USE_THAT_ITEM, _Item, nullptr);
        return true;
    }
};

//This is just a hack and should be removed from here.
//Creature/Item are in fact created before spell are sucessfully casted, without any checks at all to ensure proper/expected behavior.
class ItemDraeneiFishingNet : ItemScript
{
public:
    ItemDraeneiFishingNet() : ItemScript("item_draenei_fishing_net") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        //if( targets.GetGOTarget() && targets.GetGOTarget()->GetTypeId() == TYPEID_GAMEOBJECT &&
        //targets.GetGOTarget()->GetGOInfo()->type == GAMEOBJECT_TYPE_SPELL_FOCUS && targets.GetGOTarget()->GetEntry() == 181616 )
        //{
        if (player->GetQuestStatus(9452) == QUEST_STATUS_INCOMPLETE)
        {
            if (rand() % 100 < 35)
            {
                Creature *Murloc = player->SummonCreature(17102, player->GetPositionX(), player->GetPositionY() + 20, player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
                if (Murloc)
                    Murloc->AI()->AttackStart(player);
            }
            else
            {
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 23614, 1);
                if (msg == EQUIP_ERR_OK)
                {
                    Item* item = player->StoreNewItem(dest, 23614, true);
                    if (item)
                        player->SendNewItem(item, 1, false, true);
                }
                else
                    player->SendEquipError(msg, nullptr, nullptr);
            }
        }
        //}
        return false;
    }
};

/*#####
# 
#####*/
class ItemDisciplinaryRod : ItemScript
{
public:
    ItemDisciplinaryRod() : ItemScript("item_disciplinary_rod") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            (targets.GetUnitTarget()->GetEntry() == 15941 || targets.GetUnitTarget()->GetEntry() == 15945))
            return false;

        player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, _Item, nullptr);
        return true;
    }
};

class ItemNetherWraithBeacon : ItemScript
{
public:
    ItemNetherWraithBeacon() : ItemScript("item_nether_wraith_beacon") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (player->GetQuestStatus(10832) == QUEST_STATUS_INCOMPLETE)
        {
            Creature *Nether;
            Nether = player->SummonCreature(22408, player->GetPositionX(), player->GetPositionY() + 20, player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 180000);
            Nether = player->SummonCreature(22408, player->GetPositionX(), player->GetPositionY() - 20, player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 180000);
            if (Nether)
                ((CreatureAI*)Nether->AI())->AttackStart(player);
        }
        return false;
    }
};

class ItemFlyingMachine : ItemScript
{
public:
    ItemFlyingMachine() : ItemScript("item_flying_machine") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        uint32 itemId = _Item->GetEntry();
        if (itemId == 34060)
            if (player->GetBaseSkillValue(SKILL_RIDING) >= 225)
                return false;

        if (itemId == 34061)
            if (player->GetBaseSkillValue(SKILL_RIDING) == 300)
                return false;

        player->SendEquipError(EQUIP_ERR_ERR_CANT_EQUIP_SKILL, _Item, nullptr);
        return true;
    }
};

class ItemGorDreksOintment : ItemScript
{
public:
    ItemGorDreksOintment() : ItemScript("item_gor_dreks_ointment") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 20748 && !targets.GetUnitTarget()->HasAuraEffect(32578, 0))
            return false;

        player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, _Item, nullptr);
        return true;
    }
};

/*#####
# 
#####*/
class ItemMuiseksVessel : ItemScript
{
public:
    ItemMuiseksVessel() : ItemScript("item_muiseks_vessel") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        Unit* uTarget = targets.GetUnitTarget();
        uint32 itemSpell = _Item->GetTemplate()->Spells[0].SpellId;
        uint32 cEntry = 0;
        uint32 cEntry2 = 0;
        uint32 cEntry3 = 0;
        uint32 cEntry4 = 0;

        if (itemSpell)
        {
            switch (itemSpell)
            {
            case 11885:                                     //Wandering Forest Walker
                cEntry = 7584;
                break;
            case 11886:                                     //Owlbeasts
                cEntry = 2927;
                cEntry2 = 2928;
                cEntry3 = 2929;
                cEntry4 = 7808;
                break;
            case 11887:                                     //Freyfeather Hippogryphs
                cEntry = 5300;
                cEntry2 = 5304;
                cEntry3 = 5305;
                cEntry4 = 5306;
                break;
            case 11888:                                     //Sprite Dragon Sprite Darters
                cEntry = 5276;
                cEntry2 = 5278;
                break;
            case 11889:                                     //Zapped Land Walker Land Walker Zapped Cliff Giant Cliff Giant
                cEntry = 5357;
                cEntry2 = 5358;
                cEntry3 = 14640;
                cEntry4 = 14604;
                break;
            }
            if (uTarget && uTarget->GetTypeId() == TYPEID_UNIT && uTarget->IsDead() &&
                (uTarget->GetEntry() == cEntry || uTarget->GetEntry() == cEntry2 || uTarget->GetEntry() == cEntry3 || uTarget->GetEntry() == cEntry4))
            {
                (uTarget->ToCreature())->RemoveCorpse();
                return false;
            }
        }

        WorldPacket data(SMSG_CAST_FAILED, (4 + 2));              // prepare packet error message
        data << uint32(_Item->GetEntry());                      // itemId
        data << uint8(SPELL_FAILED_BAD_TARGETS);                // reason
        player->GetSession()->SendPacket(&data);                // send message: Invalid target

        player->SendEquipError(EQUIP_ERR_NONE, _Item, nullptr);      // break spell
        return true;
    }
};

/*#####
# 
#####*/
class ItemInoculatingCrystal : ItemScript
{
public:
    ItemInoculatingCrystal() : ItemScript("item_inoculating_crystal") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 16518)
            return false;

        WorldPacket data(SMSG_CAST_FAILED, (4 + 2));              // prepare packet error message
        data << uint32(_Item->GetEntry());                      // itemId
        data << uint8(SPELL_FAILED_BAD_TARGETS);                // reason
        player->GetSession()->SendPacket(&data);                // send message: Invalid target

        player->SendEquipError(EQUIP_ERR_NONE, _Item, nullptr);      // break spell
        return true;
    }
};

class ItemRazorthornFlayerGland : ItemScript
{
public:
    ItemRazorthornFlayerGland() : ItemScript("item_razorthorn_flayer_gland") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 24922)
            return false;

        player->SendEquipError(EQUIP_ERR_YOU_CAN_NEVER_USE_THAT_ITEM, _Item, nullptr);
        return true;
    }
};

/*#####
# 
#####*/
class ItemTameBeastRods : ItemScript
{
public:
    ItemTameBeastRods() : ItemScript("item_tame_beast_rods") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        uint32 itemSpell = _Item->GetTemplate()->Spells[0].SpellId;
        uint32 cEntry = 0;

        if (itemSpell)
        {
            switch (itemSpell)
            {
            case 19548: cEntry = 1196; break;              //Ice Claw Bear
            case 19674: cEntry = 1126; break;              //Large Crag Boar
            case 19687: cEntry = 1201; break;              //Snow Leopard
            case 19688: cEntry = 2956; break;              //Adult Plainstrider
            case 19689: cEntry = 2959; break;              //Prairie Stalker
            case 19692: cEntry = 2970; break;              //Swoop
            case 19693: cEntry = 1998; break;              //Webwood Lurker
            case 19694: cEntry = 3099; break;              //Dire Mottled Boar
            case 19696: cEntry = 3107; break;              //Surf Crawler
            case 19697: cEntry = 3126; break;              //Armored Scorpid
            case 19699: cEntry = 2043; break;              //Nightsaber Stalker
            case 19700: cEntry = 1996; break;              //Strigid Screecher
            case 30646: cEntry = 17217; break;              //Barbed Crawler
            case 30653: cEntry = 17374; break;              //Greater Timberstrider
            case 30654: cEntry = 17203; break;              //Nightstalker
            case 30099: cEntry = 15650; break;              //Crazed Dragonhawk
            case 30102: cEntry = 15652; break;              //Elder Springpaw
            case 30105: cEntry = 16353; break;              //Mistbat
            }
            if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
                targets.GetUnitTarget()->GetEntry() == cEntry)
                return false;
        }

        WorldPacket data(SMSG_CAST_FAILED, (4 + 2));              // prepare packet error message
        data << uint32(_Item->GetEntry());                      // itemId
        data << uint8(SPELL_FAILED_BAD_TARGETS);                // reason
        player->GetSession()->SendPacket(&data);                // send message: Invalid target

        player->SendEquipError(EQUIP_ERR_NONE, _Item, nullptr);      // break spell
        return true;
    }
};

class ItemProtovoltaicMagnetoCollector : ItemScript
{
public:
    ItemProtovoltaicMagnetoCollector() : ItemScript("item_protovoltaic_magneto_collector") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 21729)
            return false;

        player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, _Item, nullptr);
        return true;
    }
};

/*#####
# 
#####*/
class ItemSoulCannon : ItemScript
{
public:
    ItemSoulCannon() : ItemScript("item_soul_cannon") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        // allow use
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 22357)
            return false;

        // error
        player->SendEquipError(EQUIP_ERR_YOU_CAN_NEVER_USE_THAT_ITEM, _Item, nullptr);
        return true;
    }
};

/*#####
# 
#####*/
class ItemSparrowhawkNet : ItemScript
{
public:
    ItemSparrowhawkNet() : ItemScript("item_sparrowhawk_net") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 22979)
            return false;

        player->SendEquipError(EQUIP_ERR_YOU_CAN_NEVER_USE_THAT_ITEM, _Item, nullptr);
        return true;
    }
};

class ItemVoodooCharm : ItemScript
{
public:
    ItemVoodooCharm() : ItemScript("item_voodoo_charm") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT && targets.GetUnitTarget()->IsDead() &&
            targets.GetUnitTarget()->GetEntry() == 7318)
            return false;

        WorldPacket data(SMSG_CAST_FAILED, (4 + 2));              // prepare packet error message
        data << uint32(_Item->GetEntry());                      // itemId
        data << uint8(SPELL_FAILED_BAD_TARGETS);                // reason
        player->GetSession()->SendPacket(&data);                // send message: Invalid target

        player->SendEquipError(EQUIP_ERR_NONE, _Item, nullptr);      // break spell
        return true;
    }
};

class ItemVorenthalsPresence : ItemScript
{
public:
    ItemVorenthalsPresence() : ItemScript("item_vorenthals_presence") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        // allow use
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 20132)
            return false;

        // error
        player->SendEquipError(EQUIP_ERR_YOU_CAN_NEVER_USE_THAT_ITEM, _Item, nullptr);
        return true;
    }
};

class ItemZezzakShard : ItemScript
{
public:
    ItemZezzakShard() : ItemScript("item_zezzak_shard") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 19440)
            return false;

        player->SendEquipError(EQUIP_ERR_YOU_CAN_NEVER_USE_THAT_ITEM, _Item, nullptr);
        return true;
    }
};

class ItemCantationManifestation : ItemScript
{
public:
    ItemCantationManifestation() : ItemScript("item_cantation_manifestation") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (!player)
            return true;

        if (player->GetZoneId() == 85) //Undercity, Horde player /!\ Incorrect Zone ID, this is Tirisfal (bad map handling ?)
        {
            player->SummonCreature(6492, 1406.296021, 366.913544, -66.028725, 5.488527, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 45000);
            player->SummonCreature(6492, 1394.303101, 371.347839, -66.037758, 5.728081, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 45000);
            player->SummonCreature(6492, 1397.491577, 383.645813, -66.028618, 5.361302, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 45000);
            player->SummonCreature(6492, 1412.722534, 380.046356, -66.023552, 5.044792, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 45000);
        }
        else if (player->GetZoneId() == 1519) //Stormwind, Alliance player
        {
            player->SummonCreature(6492, -9062.350586, 825.794678, 108.418610, 2.058017, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 45000);
            player->SummonCreature(6492, -9075.598633, 828.228027, 108.418732, 0.797452, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 45000);
            player->SummonCreature(6492, -9078.819336, 835.014221, 108.420052, 5.969300, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 45000);
            player->SummonCreature(6492, -9070.746094, 845.652344, 108.419289, 5.101437, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 45000);
        }

        return false;
    }
};

class ItemBloodmaulKeg : ItemScript
{
public:
    ItemBloodmaulKeg() : ItemScript("item_bloodmaul_keg") {}

    enum
    {
        QUEST_BLADESPIRE_A = 10512,
        QUEST_BLADESPIRE_H = 10545,

        BLOODMAUL_TRIGGER = 21241,
    };

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (!player)
            return true;

        if ((player->GetTeam() == ALLIANCE && player->GetQuestStatus(QUEST_BLADESPIRE_A) == QUEST_STATUS_INCOMPLETE)
            || (player->GetTeam() == HORDE && player->GetQuestStatus(QUEST_BLADESPIRE_H) == QUEST_STATUS_INCOMPLETE))
            player->KilledMonsterCredit(BLOODMAUL_TRIGGER, player->GetGUID());

        return false;
    }
};

class ItemPurificationMixture : ItemScript
{
public:
    ItemPurificationMixture() : ItemScript("item_purification_mixture") {}


    enum ePurificationMixture
    {
        QUEST_HELBOAR_MEAT = 9361,

        SPELL_PURIFIED_MEAT = 29277,
        SPELL_TOXIC_MEAT = 29278,

        ITEM_TAINTED_MEAT = 23270,
    };

    bool OnUse(Player* pPlayer, Item* _Item, SpellCastTargets const& targets) override
    {
        if (!pPlayer)
            return true;

        if (pPlayer->GetQuestStatus(QUEST_HELBOAR_MEAT) == QUEST_STATUS_INCOMPLETE)
        {
            if (pPlayer->HasItemCount(ITEM_TAINTED_MEAT, 1, false))
            {
                uint32 spell_id = roll_chance_i(50) ? 29277 : 29278;
                pPlayer->CastSpell(pPlayer, spell_id, true);
                pPlayer->DestroyItemCount(ITEM_TAINTED_MEAT, 1, true, false);

                return false;
            }
        }

        return true;
    }
};

class ItemStaffElders : ItemScript
{
public:
    ItemStaffElders() : ItemScript("item_staff_elders") {}

    enum eArzethDemise {
        QUEST_ARZETH_DEMISE = 10369,

        ENTRY_ARZETH_MERCILESS = 19354,
        ENTRY_ARZETH_POWERLESS = 20680
    };

    bool OnUse(Player* pPlayer, Item* _Item, SpellCastTargets const& targets) override
    {
        if (Creature* arzeth = pPlayer->FindNearestCreature(ENTRY_ARZETH_MERCILESS, 15.0f, true)) {
            arzeth->UpdateEntry(ENTRY_ARZETH_POWERLESS);

            return false;
        }

        return true;
    }
};

class ItemOrwinsShovel : ItemScript
{
public:
    ItemOrwinsShovel() : ItemScript("item_orwins_shovel") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (GameObject* cobalt = player->FindNearestGameObject(144050, 2.0f))
            player->SummonGameObject(144064, player->GetPosition(), G3D::Quat(), 86400);

        return true;
    }
};

class ItemNetherwaveNet : ItemScript
{
public:
    ItemNetherwaveNet() : ItemScript("item_netherwave_net") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        if (Unit* target = ObjectAccessor::GetUnit(*player, player->GetTarget())) {
            if (!target->IsFriendlyTo(player)) {
                player->CastSpell(target, 31367, TRIGGERED_NONE);
                //player->DestroyItemCount(item->GetEntry(), 1, true);
            }
        }

        return false;
    }
};

void AddSC_item_scripts()
{
    new ItemArea52Special();
    new ItemOnlyForFlight();
    new ItemBlackwhelpNet();
    new ItemDisciplinaryRod();
    new ItemDraeneiFishingNet();
    new ItemNetherWraithBeacon();
    new ItemFlyingMachine();
    new ItemGorDreksOintment();
    new ItemMuiseksVessel();
    new ItemInoculatingCrystal();
    new ItemRazorthornFlayerGland();
    new ItemTameBeastRods();
    new ItemProtovoltaicMagnetoCollector();
    new ItemSoulCannon();
    new ItemSparrowhawkNet();
    new ItemVoodooCharm();
    new ItemVorenthalsPresence();
    new ItemZezzakShard();
    new ItemCantationManifestation();
    new ItemBloodmaulKeg();
    new ItemPurificationMixture();
    new ItemStaffElders();
    new ItemOrwinsShovel();
    new ItemNetherwaveNet();
}

