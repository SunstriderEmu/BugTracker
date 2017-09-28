UPDATE creature_template SET armor = 3800 WHERE entry = 12259;

UPDATE creature_template SET AIName = "NullCreatureAI", ScriptName = "" WHERE entry = 12259;

DELETE FROM creature_scripts WHERE entryorguid = 12259;
INSERT INTO creature_scripts VALUES (12259, "boss_gehennas");
