UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22846;

DELETE FROM smart_scripts WHERE entryorguid = 22846;
INSERT INTO smart_scripts VALUES
(22846, 0, 0, 0, 4, 0, 100, 2, 0, 0, 0, 0, 11, 41151, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Lightning Shield on aggro"),
(22846, 0, 1, 0, 0, 0, 100, 2, 500, 500, 3000, 5000, 11, 41184, 0, 0, 0, 0, 0, 17, 8, 40, 0, 0, 0, 0, 0, "Cast Lightning Bolt on random in 8-40 yards"),
(22846, 0, 2, 0, 0, 0, 100, 2, 2000, 2000, 10000, 15000, 11, 41183, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Chain Lightning on tank");
