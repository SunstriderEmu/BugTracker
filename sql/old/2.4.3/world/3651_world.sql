UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 25109;

DELETE FROM smart_scripts WHERE entryorguid = 25109;
INSERT INTO smart_scripts VALUES
(25109, 0, 0, 0, 1, 0, 100, 0, 1000, 10000, 45000, 90000, 11, 45255, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Rocket chicken OOC"),
(25109, 0, 1, 0, 1, 0, 20, 0, 60000, 65000, 45000, 90000, 11, 45254, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Suicide (20% chance)");
