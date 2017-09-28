UPDATE creature_template SET AIName = 'NullCreatureAI' WHERE entry = 25782;

DELETE FROM creature_scripts WHERE entryorguid = 25782;
INSERT INTO creature_scripts VALUES
(25782, "npc_sentinal_summoner");
