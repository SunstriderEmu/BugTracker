DELETE FROM creature_scripts WHERE entryorguid IN (12098, 11662);
INSERT INTO creature_scripts VALUES (12098, 'Boss_Sulfuron');
INSERT INTO creature_scripts VALUES (11662, 'Mob_Flamewaker_Priest');

UPDATE creature_template SET AIName = 'NullCreatureAI', ScriptName = '' WHERE entry = 12098;
UPDATE creature_template SET AIName = 'NullCreatureAI', ScriptName = '' WHERE entry = 11662;
