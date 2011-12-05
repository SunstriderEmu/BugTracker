UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (20601, 20609, 20614);
DELETE FROM smart_scripts WHERE entryorguid IN (20601, 20609, 20614);
INSERT INTO smart_scripts VALUES
(20601, 0, 0, 0, 6, 0, 8, 0, 0, 0, 0, 0, 12, 21057, 1, 60000, 0, 0, 0, 8, 0, 0, 0, 2912.030029, 5211.109863, 265.880005, 3.488740, "Razaani Raider - Death - 15% chance to spawn Razaan"),
(20609, 0, 0, 0, 6, 0, 8, 0, 0, 0, 0, 0, 12, 21057, 1, 60000, 0, 0, 0, 8, 0, 0, 0, 2912.030029, 5211.109863, 265.880005, 3.488740, "Razaani Nexus Stalker - Death - 15% chance to spawn Razaan"),
(20614, 0, 0, 0, 6, 0, 8, 0, 0, 0, 0, 0, 12, 21057, 1, 60000, 0, 0, 0, 8, 0, 0, 0, 2912.030029, 5211.109863, 265.880005, 3.488740, "Razaani Spell-Thief - Death - 15% chance to spawn Razaan");

DELETE FROM creature WHERE id = 21057;

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 21057;
DELETE FROM smart_scripts WHERE entryorguid = 21057;
INSERT INTO smart_scripts VALUES
(21057, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nexus-Prince Razaan - Reset - Yell"),
(21057, 0, 1, 0, 6, 0, 100, 0, 0, 0, 0, 0, 50, 185033, 60000, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nexus-Prince Razaan - Death - Spawn Collection of Souls");

DELETE FROM creature_text WHERE entry = 21057;
INSERT INTO creature_text VALUES
(21057, 0, 0, "Qui ose interrompre mes opérations ?", 1, 0, 100, 0, 0, 0, "Nexus-Prince Razaan - Spawn");
