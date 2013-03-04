DELETE FROM creature_scripts WHERE entryorguid = 12264;
INSERT INTO creature_scripts VALUES (12264, 'Boss_Shazzrah');

UPDATE creature_template SET AIName = 'NullCreatureAI', ScriptName = '' WHERE entry = 12264;
