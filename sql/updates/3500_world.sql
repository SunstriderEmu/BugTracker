UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22873;
DELETE FROM eventai_scripts WHERE creature_id = 22873;
DELETE FROM smart_scripts WHERE entryorguid = 22873;
INSERT INTO smart_scripts VALUES
(22873, 0, 1, 0, 4, 0, 100, 3, 0, 0, 0, 0, 11, 29651, 3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Dual wield on aggro"),
(22873, 0, 2, 0, 15, 0, 100, 2, 15, 8000, 8000, 0, 11, 40081, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Cast Free Friend on CCed friend"),
(22873, 0, 3, 0, 0, 0, 100, 2, 4000, 4000, 30000, 30000, 11, 40080, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Booming Voice");
