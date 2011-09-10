UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (14380, 14378, 14379);

DELETE FROM smart_scripts WHERE entryorguid IN (14380, 14378, 14379);
INSERT INTO smart_scripts VALUES
(14380, 0, 0, 0, 0, 0, 100, 0, 2000, 5000, 10000, 20000, 11, 14030, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Hooked Net on random"),
(14380, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 12000, 15000, 11, 15572, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Sunder Armor on target"),
(14378, 0, 0, 0, 0, 0, 100, 0, 2000, 5000, 10000, 20000, 11, 14030, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Hooked Net on random"),
(14378, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 12000, 15000, 11, 15572, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Sunder Armor on target"),
(14379, 0, 0, 0, 0, 0, 100, 0, 2000, 5000, 10000, 20000, 11, 14030, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Hooked Net on random"),
(14379, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 12000, 15000, 11, 15572, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Sunder Armor on target");
