DELETE FROM spell_linked_spell WHERE spell_effect = 45348;

-- Was:
-- +---------------+--------------+------+---------------------+
-- | spell_trigger | spell_effect | type | comment             |
-- +---------------+--------------+------+---------------------+
-- |         45342 |        45348 |    1 | Apply Flame Touched |
-- |         46771 |        45348 |    1 | Apply Flame Touched |
-- |         45246 |        45348 |    1 | Apply Flame Touched |
-- +---------------+--------------+------+---------------------+

-- Missing old content (was saved in wrong files)
-- 3418
INSERT INTO spell_linked_spell VALUES (-32756, -38081, 0, "Quest 10040 and 40041");
INSERT INTO spell_linked_spell VALUES (-32756, -38080, 0, "Quest 10040 and 40041");

UPDATE creature_template SET scriptname = "npc_scout_neftis" WHERE entry = 18714;

-- 3420
UPDATE creature_loot_template SET chanceorquestchance = 33, lootcondition = 9, condition_value1 = 11020 WHERE item = 32502;

-- 3422
UPDATE creature_template SET scriptname = "npc_spirits_totem" WHERE entry = 21071;

-- 3423
UPDATE creature_template SET regenhealth = 0 WHERE entry = 20899;

-- 3425
UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry = 19480;

-- 3426
UPDATE quest_template SET RequiredMinRepFaction = 510, RequiredMinRepValue = 42000 WHERE entry = 8122;
UPDATE quest_template SET RequiredMinRepFaction = 509, RequiredMinRepValue = 42000 WHERE entry = 8115;


