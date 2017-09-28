UPDATE gameobject_template SET size = 3, AIName = "SmartGameObjectAI" WHERE entry IN (185519, 185522);

DELETE FROM gameobject WHERE id IN (185519, 185522) AND map = 557;
INSERT INTO gameobject (id, map, spawnmask, position_x, position_y, position_z, orientation, rotation2, rotation3, spawntimesecs, state) VALUES
(185519, 557, 2, 12.533, -223.088, -0.95259, 3.10777, 0.999857, 0.016909, 25, 1),
(185522, 557, 2, -249.201, -3.4634, 14.6605, 1.85204, 0.799233, 0.601021, 86400, 1);

DELETE FROM smart_scripts WHERE entryorguid IN (185519, 185522);
INSERT INTO smart_scripts VALUES
(185519, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 15, 10977, 0, 0, 0, 0, 0, 18, 50, 0, 0, 0, 0, 0, 0, "Complete quest 10977 on Gossip Hello"),
(185522, 1, 0, 1, 64, 0, 100, 0, 0, 0, 0, 0, 12, 22930, 6, 600000, 0, 0, 0, 8, 0, 0, 0, -248.766083, -5.250644, 15.097206, 1.771752, "Summon Yor on Gossip Hello"),
(185522, 1, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 500, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Despawn self immediately");

UPDATE creature_template SET faction_A = 16, faction_H = 16, AIName = "SmartAI", ScriptName = "" WHERE entry = 22930;
DELETE FROM smart_scripts WHERE entryorguid = 22930;
INSERT INTO smart_scripts VALUES
(22930, 0, 0, 0, 0, 0, 100, 4, 9000, 9000, 12000, 18000, 11, 36405, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Stomp on target"),
(22930, 0, 1, 0, 0, 0, 100, 4, 5000, 5000, 22000, 28000, 11, 38361, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Double Breath on target");
