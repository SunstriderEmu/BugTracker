UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22293;
DELETE FROM smart_scripts WHERE entryorguid = 22293;
INSERT INTO smart_scripts VALUES (22293, 0, 0, 0, 20, 0, 100, 0, 10850, 0, 0, 0, 33, 22293, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Complete quest 10855 on quest 10850 choose reward");
