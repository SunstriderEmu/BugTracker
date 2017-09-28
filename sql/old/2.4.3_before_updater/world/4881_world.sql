UPDATE creature_template SET armor = 3800 WHERE entry = 12118;
UPDATE creature SET pool_id = 172 WHERE id IN (12118, 12119);
UPDATE creature SET spawntimesecs = 604800 WHERE id = 12119;
DELETE FROM eventai_scripts WHERE creature_id = 12119;

DELETE FROM creature_scripts WHERE entryorguid IN (12118, 12119);
INSERT INTO creature_scripts (entryorguid, scriptname) VALUES (12118, "boss_lucifron"), (12119, "add_flamewakerprotector");

UPDATE creature_template SET AIName = "NullCreatureAI", ScriptName = "" WHERE entry IN (12118, 12119);
