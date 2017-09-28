DELETE FROM creature_scripts WHERE entryorguid = 6109;
INSERT INTO creature_scripts VALUES (6109, "boss_azuregos_new");

UPDATE creature_template SET AIName = "NullCreatureAI", ScriptName = "" WHERE entry = 6109;
