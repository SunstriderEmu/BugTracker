UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 2953;

DELETE FROM smart_scripts WHERE entryorguid = 2953;
INSERT INTO smart_scripts VALUES
(2953, 0, 0, 1, 4, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Bristleback Shaman - Aggro - Prevent combat movement"),
(2953, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Bristleback Shaman - Aggro - Set Phase 1"),
(2953, 0, 2, 3, 3, 0, 100, 0, 5, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Bristleback Shaman - 15% Mana - Allow combat movement"),
(2953, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Bristleback Shaman - 15% Mana - Set Phase 2"),
(2953, 0, 4, 0, 9, 1, 100, 0, 35, 80, 1000, 1000, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Bristleback Shaman - Phase 1 - Allow combat movement at 35 yards"),
(2953, 0, 5, 0, 9, 1, 100, 0, 5, 15, 1000, 1000, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Bristleback Shaman - Phase 1 - Prevent combat movement at 15 yards"),
(2953, 0, 6, 0, 0, 1, 100, 0, 500, 500, 2400, 3800, 11, 9532, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Bristleback Shaman - Phase 1 - Cast Lightning Bolt"),
(2953, 0, 7, 0, 7, 0, 100, 0, 0, 0, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Bristleback Shaman - Evade - Allow combat movement");
