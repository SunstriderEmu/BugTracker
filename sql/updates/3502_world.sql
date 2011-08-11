UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 23030;

DELETE FROM smart_scripts WHERE entryorguid = 23030;
INSERT INTO smart_scripts VALUES
(23030, 0, 0, 0, 4, 0, 100, 2, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Stop moving on Aggro"),
(23030, 0, 1, 0, 0, 0, 100, 2, 4000, 4000, 6000, 6000, 11, 40872, 3, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Immolation Arrow"),
(23030, 0, 2, 0, 0, 0, 100, 2, 500, 500, 3000, 4000, 11, 40873, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Shoot"),
-- (23030, 0, 3, 0, 9, 0, 100, 2, 0, 8, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Start Moving when < Shoot Range"),
(23030, 0, 3, 0, 9, 0, 100, 2, 36, 100, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Start Moving when > Shoot Range"),
(23030, 0, 4, 0, 9, 0, 100, 2, 9, 35, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Stop Moving at 35 yards"),
(23030, 0, 5, 0, 6, 0, 100, 2, 0, 0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Unmount at death");
