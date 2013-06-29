-- Outland Children's Week

-- Salandria's chain (Shattrath - Horde)
DELETE FROM creature_questrelation WHERE quest IN (10942, 10945, 10953, 10951, 11975, 10963, 10967);
DELETE FROM creature_involvedrelation WHERE quest IN (10942, 10945, 10953, 10951, 11975, 10963, 10967);
UPDATE creature_template SET npcflag = 2, minhealth = 500, maxhealth = 500 WHERE entry = 22914;

INSERT INTO creature_questrelation VALUES (22819, 10942);
INSERT INTO creature_involvedrelation VALUES (22914, 10942);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10942 WHERE entry = 10945;
INSERT INTO creature_questrelation VALUES (22914, 10945);
INSERT INTO creature_involvedrelation VALUES (22914, 10945);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10942 WHERE entry = 10953;
INSERT INTO creature_questrelation VALUES (22914, 10953);
INSERT INTO creature_involvedrelation VALUES (22914, 10953);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10942 WHERE entry = 10951;
INSERT INTO creature_questrelation VALUES (22914, 10951);
INSERT INTO creature_involvedrelation VALUES (22914, 10951);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10951 WHERE entry = 11975;
INSERT INTO creature_questrelation VALUES (22914, 11975);
INSERT INTO creature_involvedrelation VALUES (22914, 11975);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10951 WHERE entry = 10963;
INSERT INTO creature_questrelation VALUES (22914, 10963);
INSERT INTO creature_involvedrelation VALUES (22914, 10963);

UPDATE quest_template SET prevquestid = 10963 WHERE entry = 10967;
INSERT INTO creature_questrelation VALUES (22914, 10967);
INSERT INTO creature_involvedrelation VALUES (22819, 10967);

-- Missing NPC's
DELETE FROM creature WHERE id = 22823;
INSERT INTO creature (id, map, spawnmask, position_x, position_y, position_z, orientation, spawntimesecs, movementtype) VALUES (22823, 530, 1, 193.464, 8519.32, 24.043, 0.151276, 25, 0); -- Quest 10945

-- Quest 10945
UPDATE creature_template SET scriptname = "npc_hchuu" WHERE entry = 22823;

-- Quest 10953
UPDATE creature_template SET scriptname = "npc_sharvak" WHERE entry = 18072;

-- Quest 10951
DELETE FROM areatrigger_scripts WHERE entry = 4356;
INSERT INTO areatrigger_scripts VALUES (4356, "at_childweek_quest10951");

-- Quest 11975
UPDATE creature_template SET scriptname = "npc_schweitzer" WHERE entry = 23988;

-- Quest 10963
UPDATE creature_template SET scriptname = "npc_trigger_quest10963" WHERE entry = 22872;

-- Misc
INSERT INTO game_event_creature VALUES (7594791, 10);
