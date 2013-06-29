UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17612;

DELETE FROM smart_scripts WHERE entryorguid = 17612;
INSERT INTO smart_scripts VALUES (17612, 0, 0, 0, 6, 0, 100, 0, 0, 0, 0, 0, 26, 9595, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Complete quest 9595 on death");
