UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 23236;

DELETE FROM smart_scripts WHERE entryorguid = 23236;
INSERT INTO smart_scripts VALUES (23236, 0, 0, 0, 0, 0, 100, 2, 5000, 10000, 15000, 22000, 11, 41198, 0, 0, 0, 0, 0, 9, 23237, 8, 35, 0, 0, 0, 0, "Cast Intervene on friend"), (23236, 0, 1, 0, 0, 0, 100, 2, 2000, 5000, 10000, 12000, 11, 41197, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Shield Bash on victim"), (23236, 0, 2, 0, 0, 0, 100, 2, 6000, 10000, 12000, 18000, 11, 41213, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Throw Shield on random");
