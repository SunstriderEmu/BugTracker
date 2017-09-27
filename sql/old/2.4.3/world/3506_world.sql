UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22847;

DELETE FROM smart_scripts WHERE entryorguid = 22847;
INSERT INTO smart_scripts VALUES
(22847, 0, 0, 0, 4, 0, 100, 2, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Stop movement on aggro"),
(22847, 0, 9, 0, 0, 0, 100, 2, 2000, 5000, 20000, 26000, 11, 41186, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Wyrvern Sting on random"),
(22847, 0, 2, 0, 0, 0, 100, 2, 5000, 8000, 12000, 18000, 11, 41187, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Multi-Shot on random"),
(22847, 0, 3, 0, 0, 0, 100, 2, 1000, 1000, 2000, 5000, 11, 41188, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Shoot on victim"),
(22847, 0, 4, 5, 9, 0, 100, 2, 1, 5, 3000, 3000, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Start moving if victim is in 0-5 yards"),
(22847, 0, 5, 6, 61, 0, 100, 2, 0, 0, 0, 0, 11, 39584, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Sweeping Wing Clip on target"),
(22847, 0, 6, 0, 61, 0, 100, 2, 0, 0, 0, 0, 46, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Move 10 yards forward"),
(22847, 0, 7, 0, 9, 0, 100, 2, 5, 30, 3000, 3000, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Stop movement on target in 5-30 yards"),
(22847, 0, 8, 0, 0, 0, 100, 2, 5000, 9000, 13000, 22000, 11, 39584, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Sweeping Wing Clip on target");
