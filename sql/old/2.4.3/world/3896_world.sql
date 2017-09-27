UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22309;
DELETE FROM smart_scripts WHERE entryorguid = 22309;
INSERT INTO smart_scripts VALUES (22309, 0, 0, 0, 0, 0, 100, 0, 1000, 2000, 5000, 8000, 11, 34425, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Crashing Wave-Spirit - Cast Water Bolt in combat");
