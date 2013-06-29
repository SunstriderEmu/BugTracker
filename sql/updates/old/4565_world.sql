UPDATE creature_template SET AIName = "NullCreatureAI" WHERE entry = 25879;

DELETE FROM creature_scripts WHERE entryorguid = 25879;
INSERT INTO creature_scripts (entryorguid, scriptname) VALUES (25879, 'npc_darkness');
