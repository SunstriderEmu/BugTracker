UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 7274;
DELETE FROM smart_scripts WHERE entryorguid = 7274;
INSERT INTO smart_scripts VALUES (7274, 0, 0, 0, 0, 0, 100, 2, 2000, 5000, 5000, 8000, 11, 15496, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Sandfury Executioner - IC Timer - Cast Cleave");
