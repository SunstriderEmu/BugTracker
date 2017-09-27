DELETE FROM creature_scripts WHERE entryorguid IN (12057, 12099);
INSERT INTO creature_scripts VALUES (12057, 'Boss_Garr');
INSERT INTO creature_scripts VALUES (12099, 'Mob_FiresWorn');

UPDATE creature_template SET AIName = 'NullCreatureAI', ScriptName = '' WHERE entry = 12057;
UPDATE creature_template SET AIName = 'NullCreatureAI', ScriptName = '' WHERE entry = 12099;
