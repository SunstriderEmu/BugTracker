-- Horde
DELETE FROM quest_pool WHERE pool_id = 2;
INSERT INTO quest_pool VALUES (2, 11339), (2, 11340), (2, 11341), (2, 11342);
INSERT INTO quest_pool_current VALUES (2, 11339);
-- UPDATE creature_template SET pool_id = 2 WHERE entry = 15350;

-- Alliance
DELETE FROM quest_pool WHERE pool_id = 3;
INSERT INTO quest_pool VALUES (3, 11335), (3, 11336), (3, 11337), (3, 11338);
INSERT INTO quest_pool_current VALUES (3, 11335);
-- UPDATE creature_template SET pool_id = 3 WHERE entry = 15351;
