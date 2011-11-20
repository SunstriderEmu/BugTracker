UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22311;
DELETE FROM smart_scripts WHERE entryorguid = 22311;
INSERT INTO smart_scripts VALUES (22311, 0, 0, 0, 2, 0, 100, 1, 5, 15, 0, 0, 11, 29948, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Raging Fire-Soul - Cast Immolate one time at 5-15% health");
