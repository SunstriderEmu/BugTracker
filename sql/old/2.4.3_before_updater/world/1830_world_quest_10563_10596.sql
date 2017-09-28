DELETE FROM creature WHERE id = 21633; -- Not needed
UPDATE quest_template SET ReqCreatureOrGOId1 = 21502, ReqCreatureOrGOId3 = 0, ReqCreatureOrGOCount1 = 1, ReqCreatureOrGOCount3 = 0 WHERE entry = 10563 OR entry = 10596;
UPDATE creature_template SET scriptname = "npc_deathbringer_jovaan" WHERE entry = 21633;
