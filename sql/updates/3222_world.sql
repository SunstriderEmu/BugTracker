-- Outland Children's Week

-- Dornaa's chain (Shattrath - Alliance)
DELETE FROM creature_questrelation WHERE quest IN (10943, 10950, 10954, 10952, 10956, 10962, 10966);
DELETE FROM creature_involvedrelation WHERE quest IN (10943, 10950, 10954, 10952, 10956, 10962, 10966);
UPDATE creature_template SET npcflag = 2, minhealth = 500, maxhealth = 500 WHERE entry = 22913;

INSERT INTO creature_questrelation VALUES (22819, 10943);
INSERT INTO creature_involvedrelation VALUES (22913, 10943);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10943 WHERE entry = 10950;
INSERT INTO creature_questrelation VALUES (22913, 10950);
INSERT INTO creature_involvedrelation VALUES (22913, 10950);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10942 WHERE entry = 10954;
INSERT INTO creature_questrelation VALUES (22913, 10954);
INSERT INTO creature_involvedrelation VALUES (22913, 10954);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10942 WHERE entry = 10952;
INSERT INTO creature_questrelation VALUES (22913, 10952);
INSERT INTO creature_involvedrelation VALUES (22913, 10952);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10952 WHERE entry = 10956;
INSERT INTO creature_questrelation VALUES (22913, 10956);
INSERT INTO creature_involvedrelation VALUES (22913, 10956);

UPDATE quest_template SET questflags = 140, specialflags = 2, prevquestid = 10952 WHERE entry = 10962;
INSERT INTO creature_questrelation VALUES (22913, 10962);
INSERT INTO creature_involvedrelation VALUES (22913, 10962);

UPDATE quest_template SET prevquestid = 10962 WHERE entry = 10966;
INSERT INTO creature_questrelation VALUES (22913, 10966);
INSERT INTO creature_involvedrelation VALUES (22819, 10966);

-- Quest 10950
UPDATE creature_template SET scriptname = "npc_trigger_quest10950" WHERE entry = 22831;

-- Quest 10954
UPDATE creature_template SET scriptname = "npc_jheel" WHERE entry = 22836;

-- Quest 10956
UPDATE creature_template SET scriptname = "npc_trigger_quest10956" WHERE entry = 22851;

-- Misc
INSERT INTO game_event_creature VALUES (7680688, 10);


