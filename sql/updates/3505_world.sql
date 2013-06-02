UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22845;

DELETE FROM smart_scripts WHERE entryorguid = 22845;
INSERT INTO smart_scripts VALUES
(22845, 0, 0, 0, 4, 0, 100, 2, 0, 0, 0, 0, 11, 39588, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Summon Searing Totem on aggro"),
(22845, 0, 1, 0, 0, 0, 100, 2, 30000, 30000, 30000, 30000, 11, 39588, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Resummon Searing Totem"),
(22845, 0, 2, 0, 0, 0, 100, 3, 1000, 1000, 90000, 90000, 11, 39586, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Summon Windfury Totem"),
(22845, 0, 3, 0, 0, 0, 100, 2, 4000, 4000, 15000, 15000, 11, 41115, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Flame Shock"),
(22845, 0, 4, 0, 0, 0, 100, 2, 6000, 8000, 15000, 18000, 11, 41116, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Frost shock"),
(22845, 0, 5, 0, 14, 0, 100, 2, 50, 15, 3000, 5000, 11, 41114, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Cast Chain Heal"),
(22845, 0, 6, 0, 0, 0, 100, 3, 15000, 45000, 1000, 1000, 11, 41185, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Bloodlust");

UPDATE creature_template SET spell1 = 39593 WHERE entry = 22896;
UPDATE creature_template SET spell1 = 32911 WHERE entry = 22897;

DELETE FROM spell_proc_event WHERE entry IN (32910, 32911);
INSERT INTO spell_proc_event (entry, cooldown) VALUES (32910, 15);
INSERT INTO spell_proc_event (entry, cooldown) VALUES (32911, 15);
