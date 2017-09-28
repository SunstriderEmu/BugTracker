UPDATE creature_loot_template SET ChanceOrQuestChance = 100, lootcondition = 9, condition_value1 = 10723 WHERE item = 31754;
UPDATE gameobject_template SET data0 = 0 WHERE entry = 185309;
DELETE FROM gameobject_template WHERE entry = 300159;
INSERT INTO gameobject_template (entry, type, displayId, name, size, data0, data1) VALUES (300159, 8, 0, "TEMP Gorgrom cadaver", 1, 1450, 30);
DELETE FROM gameobject WHERE id = 300159;
INSERT INTO gameobject VALUES ('',300159,530,1,3605.41,7186.59,141.124,5.41951,0,0,0.418541,-0.908198,25,0,1);
UPDATE event_scripts SET x = 3632.555176, y = 7157.131836, z = 142.267349, o = 2.300337 WHERE id = 14400 AND datalong = 21514;

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 21514;
DELETE FROM smart_scripts WHERE entryorguid = 21514;
INSERT INTO smart_scripts VALUES
(21514, 0, 0, 4, 25, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 3607.167480, 7184.440918, 139.595367, 5.442365, "Gorgrom - Move to altar at spawn"),
(21514, 0, 1, 2, 34, 0, 100, 0, 0, 0, 0, 0, 11, 39225, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Gorgrom - Cast Sablemane's Teleport when reaching altar"),
(21514, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Gorgrom - Suicide when reaching altar"),
(21514, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 2000, 0, 0, 0, 0, 0, 19, 10204, 30, 0, 0, 0, 0, 0, "Gorgrom - Make Misha disappear when reaching altar"),
(21514, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Gorgrom - Set passive reactstate at spawn");

UPDATE creature_template SET unit_flags = unit_flags | 0x2 | 0x2000000, flags_extra = flags_extra | 0x2, faction_a = 35, faction_h = 35 WHERE entry = 21514;

