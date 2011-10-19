UPDATE gameobject_template SET AIName = "", ScriptName = "go_wickerman_ember" WHERE entry = 180437;

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 15195;

DELETE FROM smart_scripts WHERE entryorguid = 15195;
INSERT INTO smart_scripts VALUES (15195, 0, 0, 0, 6, 0, 100, 0, 0, 0, 0, 0, 50, 180437, 60000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Wickerman Guardian - Summon Wickerman Ember at death");

UPDATE gameobject_template SET size = 2.5 WHERE entry = 180433;

DELETE FROM gameobject WHERE id = 180433 AND map = 0;
INSERT INTO gameobject (id, map, spawnmask, position_x, position_y, position_z, orientation, rotation2, rotation3, spawntimesecs, animprogress, state) VALUES (180433, 0, 1, 1729.32, 500.187, 42.4016, 1.42862, 0.655096, 0.755546, 25, 0, 1);

DELETE FROM creature WHERE id IN (15195, 15197) AND map = 0;
INSERT INTO creature (id, map, spawnmask, position_x, position_y, position_z, orientation, spawntimesecs, curhealth) VALUES
(15195, 0, 1, 1746.66, 507.084, 39.9686, 1.37002, 90, 45000),
(15195, 0, 1, 1714.36, 513.659, 36.7751, 1.37002, 90, 45000),
(15197, 0, 1, 1732.19, 517.113, 38.245, 1.37417, 60, 1700);
