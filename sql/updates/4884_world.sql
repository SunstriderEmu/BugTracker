UPDATE creature_template SET armor = 4700 WHERE entry = 11982;
UPDATE spell_template SET procflags = procflags | 0x4 WHERE id = 19449;
UPDATE creature_template SET AIName = "NullCreatureAI", ScriptName = "" WHERE entry = 11982;
DELETE FROM creature_scripts WHERE entryorguid = 11982;
INSERT INTO creature_scripts VALUES (11982, "boss_magmadar");
