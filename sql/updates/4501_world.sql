UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 2713;

DELETE FROM smart_scripts WHERE entryorguid = 2713;
INSERT INTO smart_scripts VALUES (2713, 0, 0, 0, 19, 0, 100, 0, 660, 0, 0, 0, 12, 2714, 4, 60000, 0, 1, 0, 8, 0, 0, 0, -1421.951416, -3040.557861, 34.097221, 2.217370, "Kinelory - Summon Forsaken Courier on quest accept");
