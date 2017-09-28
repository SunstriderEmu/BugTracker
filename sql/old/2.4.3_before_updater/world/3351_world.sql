UPDATE quest_template SET srcItemId = 34953, srcItemCount = 1 WHERE entry = 11691;
UPDATE creature_template SET minlevel = 70, maxlevel = 70, minhealth = 5000, maxhealth = 5000 WHERE entry IN (25710, 25697);
UPDATE gameobject_template SET scriptname = "go_ice_stone_ahune" WHERE entry = 188152;

DELETE FROM gameobject_loot_template WHERE entry = 187892;
INSERT INTO gameobject_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount) VALUES
(187892, 35723, 100, 0, 1, 1),
(187892, 0, 100, 1, -187892, 1),
(187892, 35514, 1, 0, 1, 1),
(187892, 34955, 1, 0, 1, 1),
(187892, 35498, 1, 0, 1, 1),
(187892, 35557, 1, 0, 1, 1),
(187892, 35720, 1, 0, 1, 1);

DELETE FROM reference_loot_template WHERE entry = 187892;
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount) VALUES
(187892, 35507, 0, 1, 1, 1),
(187892, 35509, 0, 1, 1, 1),
(187892, 35508, 0, 1, 1, 1),
(187892, 35497, 0, 1, 1, 1),
(187892, 35511, 0, 1, 1, 1),
(187892, 35496, 0, 1, 1, 1),
(187892, 35494, 0, 1, 1, 1),
(187892, 35495, 0, 1, 1, 1);

UPDATE creature_template SET minlevel = 73, maxlevel = 73, minhealth = 150000, maxhealth = 150000, faction_A = 14, faction_H = 14 WHERE entry = 25865;
UPDATE creature_template SET minlevel = 73, maxlevel = 73, minhealth = 230000, maxhealth = 230000, faction_A = 14, faction_H = 14 WHERE entry = 26339;

UPDATE creature_template SET minlevel = 70, maxlevel = 70, minhealth = 55000, maxhealth = 55000, faction_A = 14, faction_H = 14 WHERE entry = 25755;
UPDATE creature_template SET minlevel = 70, maxlevel = 70, minhealth = 70000, maxhealth = 70000, faction_A = 14, faction_H = 14 WHERE entry = 26342;

UPDATE creature_template SET minlevel = 70, maxlevel = 70, minhealth = 1500, maxhealth = 1500, faction_A = 14, faction_H = 14 WHERE entry = 25757;
UPDATE creature_template SET minlevel = 70, maxlevel = 70, minhealth = 2000, maxhealth = 2000, faction_A = 14, faction_H = 14 WHERE entry = 26341;

UPDATE creature_template SET minlevel = 70, maxlevel = 70, minhealth = 1500, maxhealth = 1500, faction_A = 14, faction_H = 14 WHERE entry = 25756;
UPDATE creature_template SET minlevel = 70, maxlevel = 70, minhealth = 2000, maxhealth = 2000, faction_A = 14, faction_H = 14 WHERE entry = 26340;

DELETE FROM gameobject_template WHERE entry = 187892;
INSERT INTO gameobject_template VALUES (187892, 3, 1387, 'Ice Chest', '', 0, 0, 1, 1634, 187892, 99999, 1, 0, 0, 17507, 188187, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '');

UPDATE creature_template SET scriptname = "boss_ahune" WHERE entry = 25740;
UPDATE creature_template SET scriptname = "boss_frozen_core" WHERE entry = 25865;
UPDATE creature_template SET scriptname = "mob_ahunite_hailstone" WHERE entry = 25755;
UPDATE creature_template SET scriptname = "npc_ice_spear_bunny" WHERE entry = 25985;

UPDATE creature_template SET mindmg = 2, maxdmg = 2, attackpower = 24 WHERE entry IN (25755, 25756, 26340, 26342);
UPDATE creature_template SET mindmg = 422, maxdmg = 586, attackpower = 642 WHERE entry IN (25757, 26341);

UPDATE creature_model_info SET bounding_radius = 1, combat_reach = 1 WHERE modelid = 23447;

UPDATE instance_template SET script = "instance_slave_pens" WHERE map = 547;

UPDATE creature_template SET mindmg = 200, maxdmg = 400, attackpower = 100 WHERE entry IN (25755, 25756, 25757);
