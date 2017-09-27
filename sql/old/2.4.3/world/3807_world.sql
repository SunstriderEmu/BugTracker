UPDATE gameobject_template SET flags = 4 WHERE entry = 180433;

UPDATE script_texts SET entry = -1000716 WHERE entry = -2100023;
UPDATE script_texts SET entry = -1000717 WHERE entry = -2100024;
UPDATE script_texts SET entry = -1000718 WHERE entry = -2100025;
UPDATE script_texts SET entry = -1000719 WHERE entry = -2100026;
UPDATE script_texts SET entry = -1000720 WHERE entry = -2100027;
UPDATE script_texts SET entry = -1000721 WHERE entry = -2100028;

DELETE FROM game_event WHERE entry = 50;
INSERT INTO game_event VALUES (50, TIMESTAMP('2011-10-21 20:00:00'), TIMESTAMP('2020-12-31 20:00:00'), 1440, 600, "Wickerman Festival", 0);

-- I've done it on prod realm directly, just keeping track
-- DELETE FROM gameobject WHERE id = 180437;
-- INSERT INTO `gameobject` (id, map, spawnmask, position_x, position_y, position_z, orientation, rotation2, rotation3, spawntimesecs, animprogress, state) VALUES
-- (180437, 0, 1, 1738.39, 505.05, 41.8392, 1.96619, 0.832216, 0.554451, 25, 0, 1),
-- (180437, 0, 1, 1727.66, 517.546, 37.9842, 4.32958, 0.828712, -0.559676, 25, 0, 1),
-- (180437, 0, 1, 1733, 510.938, 40.7099, 4.43496, 0.798087, -0.602543, 25, 0, 1),
-- (180437, 0, 1, 1738.9, 514.431, 38.7493, 4.40485, 0.807066, -0.590461, 25, 0, 1),
-- (180437, 0, 1, 1722.98, 508.874, 40.4171, 3.44645, 0.988405, -0.151838, 25, 0, 1),
-- (180437, 0, 1, 1713.47, 505.804, 38.7652, 4.85144, 0.656277, -0.75452, 25, 0, 1),
-- (180437, 0, 1, 1720.29, 517.171, 36.8854, 5.95034, 0.165655, -0.986184, 25, 0, 1),
-- (180437, 0, 1, 1745.29, 498.819, 41.2909, 4.49016, 0.781154, -0.624338, 25, 0, 1);

