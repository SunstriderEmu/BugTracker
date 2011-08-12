UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 23374;
DELETE FROM eventai_scripts WHERE creature_id = 23374;

DELETE FROM creature_template_addon WHERE entry = 23374;
DELETE FROM creature_addon WHERE guid IN (SELECT guid FROM creature WHERE id = 23374);
INSERT INTO creature_template_addon (entry, bytes0, bytes2, auras) VALUES (23374, 16777472, 4097, "34189 0");

DELETE FROM smart_scripts WHERE entryorguid = 23374;
INSERT INTO smart_scripts VALUES
(23374, 0, 0, 0, 0, 0, 100, 2, 6000, 14000, 25000, 30000, 11, 34654, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Blind on random"),
(23374, 0, 1, 0, 0, 0, 100, 2, 2000, 5000, 6000, 10000, 11, 41189, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Instant Poison on target"),
(23374, 0, 2, 0, 0, 0, 100, 2, 3000, 5000, 15000, 18000, 11, 41190, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Cast Mind-numbing Poison on random");
