UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (14438, 14423, 14439);

DELETE FROM smart_scripts WHERE entryorguid IN (14438, 14423, 14439);
INSERT INTO smart_scripts VALUES
(14438, 0, 0, 0, 0, 0, 100, 0, 2000, 5000, 10000, 20000, 11, 14030, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Hooked Net on random"),
(14438, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 12000, 15000, 11, 15572, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Sunder Armor on target"),
(14423, 0, 0, 0, 0, 0, 100, 0, 2000, 5000, 10000, 20000, 11, 14030, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Hooked Net on random"),
(14423, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 12000, 15000, 11, 15572, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Sunder Armor on target"),
(14439, 0, 0, 0, 0, 0, 100, 0, 2000, 5000, 10000, 20000, 11, 14030, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Hooked Net on random"),
(14439, 0, 1, 0, 0, 0, 100, 0, 5000, 10000, 12000, 15000, 11, 15572, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Sunder Armor on target");
