DELETE FROM eventai_scripts WHERE creature_id = 22877;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22877;
DELETE FROM smart_scripts WHERE entryorguid = 22877;
INSERT INTO smart_scripts VALUES
(22877, 0, 0, 0, 0, 0, 100, 2, 5000, 5000, 10000, 12000, 11, 15284, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Cleave"),
(22877, 0, 1, 0, 0, 0, 100, 2, 2000, 2000, 20000, 25000, 11, 40066, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Lightning Prod"),
(22877, 0, 2, 0, 0, 0, 100, 2, 12000, 12000, 28000, 32000, 11, 40076, 1, 0, 0, 0, 0, 19, 22884, 0, 0, 0, 0, 0, 0, "Cast Electric Spur on Leviathan");
