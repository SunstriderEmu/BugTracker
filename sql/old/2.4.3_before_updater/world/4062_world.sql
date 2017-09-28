DELETE FROM game_event WHERE entry IN (58, 59);
INSERT INTO game_event VALUES (58, FROM_UNIXTIME(1316556060), FROM_UNIXTIME(1609369200), 525600, 262080, "Fishing: Winter", 0), (59, FROM_UNIXTIME(1332284460), FROM_UNIXTIME(1609369200), 525600, 266400, "Fishing: Summer", 0);

UPDATE reference_loot_template SET groupid = 2, lootcondition = 12, condition_value1 = 59, condition_value2 = 0 WHERE item = 13756;

DELETE FROM reference_loot_template WHERE item = 13755;
INSERT INTO reference_loot_template VALUES (11009, 13755, 15, 3, 1, 1, 12, 58, 0), (11105, 13755, 20, 3, 1, 1, 12, 58, 0);
