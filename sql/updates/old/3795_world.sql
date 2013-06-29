-- Template
DELETE FROM item_template WHERE entry = 38175;
INSERT INTO item_template (entry, class, subclass, unk0, name, displayid, quality, flags, buycount, buyprice, sellprice, InventoryType, AllowableClass, AllowableRace, ItemLevel, RequiredLevel, maxcount, stackable, stat_type1, stat_value1, stat_type2, stat_value2, dmg_min1, dmg_max1, delay, spellid_1, spelltrigger_1, spellid_2, spellcooldown_2, spellcategory_2, spellcategorycooldown_2, description, Material, sheath, MaxDurability, RequiredDisenchantSkill, DisenchantID) VALUES
(38175, 2, 7, -1, "The Horseman's Blade", 31419, 4, 64, 1, 599469, 119893, 21, -1, -1, 115, 70, 1, 1, 3, 14, 7, 16, 165, 308, 2700, 15811, 1, 50070, 600000, 94, 60000, "Soldiers arise, stand and fight!", 1, 3, 105, 300, 67);

-- French locale
DELETE FROM locales_item WHERE entry = 38175;
INSERT INTO locales_item (entry, name_loc2, description_loc2) VALUES (38175, "La lame du Cavalier", "Levez-vous, mes recrues ! Au combat sans surseoir !");

-- Loot table
DELETE FROM creature_loot_template WHERE entry = 23682 AND item = 38175;
INSERT INTO creature_loot_template VALUES (23682, 38175, 5, 2, 1, 1, 0, 0, 0);

-- Template
DELETE FROM creature_template WHERE entry = 27936;
INSERT INTO creature_template (entry, heroic_entry, modelid_A, modelid_H, name, subname, iconname, minlevel, maxlevel, faction_A, faction_H, mindmg, maxdmg, attackpower, baseattacktime, dynamicflags, minrangedmg, maxrangedmg, type, type_flags) VALUES
(27936, 0, 24950, 24950, "Pumpkin Soldier", "", "", 1, 1, 35, 35, 2, 2, 24, 2000, 8, 1, 1, 4, 8);

-- French locale
DELETE FROM locales_creature WHERE entry = 27936;
INSERT INTO locales_creature (entry, name_loc2, subname_loc2) VALUES (27936, "Soldat de citrouille", "");

-- Script
-- UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 27936;
-- DELETE FROM smart_scripts WHERE entryorguid = 27936;
-- INSERT INTO smart_scripts VALUES (27936, 0, 0, 0, 0, 0, 100, 0, 2000, 5000, 8000, 12000, 11, 50066, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Pumpkin Blast in combat");
