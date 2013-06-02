UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 7272;
DELETE FROM smart_scripts WHERE entryorguid = 7272;
INSERT INTO smart_scripts VALUES (7272, 0, 0, 0, 0, 0, 100, 0, 2000, 4000, 15000, 20000, 11, 8600, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Theka the Martyr - IC Timer - Cast Fevered Plague");

