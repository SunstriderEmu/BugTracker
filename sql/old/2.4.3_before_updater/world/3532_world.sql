UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 20058;

DELETE FROM smart_scripts WHERE entryorguid IN (20058, 2005800);
INSERT INTO smart_scripts VALUES
(20058, 0, 0, 0, 8, 0, 100, 0, 36310, 0, 0, 0, 33, 21176, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Killcredit on SpellHit - Quest 10506"),
(20058, 0, 1, 0, 8, 0, 100, 0, 36310, 0, 0, 0, 2, 35, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Set friendly for 60 sec"),
(20058, 0, 2, 0, 8, 0, 100, 0, 36310, 0, 0, 0, 85, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Stop combat"),
(20058, 0, 3, 0, 8, 0, 100, 0, 36310, 0, 0, 0, 80, 2005800, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Start timed action list"),
(2005800, 9, 0, 0, 0, 0, 100, 0, 100, 100, 0, 0, 77, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Reset"),
(2005800, 9, 1, 0, 0, 0, 100, 0, 60000, 60000, 0, 0, 2, 1781, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Reset faction after 60 sec");
