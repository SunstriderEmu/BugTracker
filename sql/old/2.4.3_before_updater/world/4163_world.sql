DELETE FROM areatrigger_scripts WHERE entry IN (4613, 4615, 4616, 4617);
INSERT INTO areatrigger_scripts VALUES (4613, "at_quest_whispers_raven_god"), (4615, "at_quest_whispers_raven_god"), (4616, "at_quest_whispers_raven_god"), (4617, "at_quest_whispers_raven_god");

UPDATE creature_template SET AIName = "", ScriptName = "npc_grishna" WHERE entry IN (19990, 19988, 19989);
