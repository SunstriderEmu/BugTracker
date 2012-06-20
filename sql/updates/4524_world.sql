UPDATE gameobject_template SET data0 = 0, data1 = 9368, faction = 35, flags = 32 WHERE entry BETWEEN 181332 AND 181337;

UPDATE gameobject SET spawntimesecs = 1 WHERE id BETWEEN 181332 AND 181337;

SET @GUID := 900000;

DELETE FROM gameobject WHERE guid BETWEEN @GUID AND @GUID+13;

-- Quest 9388
DELETE FROM gameobject WHERE id BETWEEN 181560 AND 181563;
INSERT INTO `gameobject` VALUES
(@GUID,181562,1,1,660.016,356.672,56.4247,5.60719,0,0,0.331599,-0.94342,1,0,1),
(@GUID+1,181563,1,1,4372.48,218.043,52.304,6.07456,0,0,0.104123,-0.994564,1,0,1),
(@GUID+2,181561,1,1,1924.81,-2039.6,103.89,0.602133,0,0,0.296539,0.955021,1,0,1),
(@GUID+3,181560,1,1,-999.073,-3392.37,81.8793,4.34942,0,0,0.823121,-0.567867,1,0,1);

DELETE FROM game_event_gameobject WHERE guid BETWEEN @GUID AND @GUID+3;
INSERT INTO game_event_gameobject (guid, event) VALUES
(@GUID, 1),
(@GUID+1, 1),
(@GUID+2, 1),
(@GUID+3, 1);

-- Quest 9389
DELETE FROM gameobject WHERE id BETWEEN 181564 AND 181567;
INSERT INTO `gameobject` VALUES
(@GUID+4,181567,0,1,-2607.62,-2509.21,83.2273,0.112325,0,0,0.0561332,0.998423,1,0,1),
(@GUID+5,181565,0,1,-11280.6,1807.87,39.4409,0.807526,0,0,0.392882,0.919589,1,0,1),
(@GUID+6,181564,0,1,-257.14,1155.99,62.9948,4.27264,0,0,0.844307,-0.535859,1,0,1),
(@GUID+7,181566,0,1,-317.952,-663.701,54.2827,5.33954,0,0,0.454512,-0.890741,1,0,1);

DELETE FROM game_event_gameobject WHERE guid BETWEEN @GUID+4 AND @GUID+7;
INSERT INTO game_event_gameobject (guid, event) VALUES
(@GUID+4, 1),
(@GUID+5, 1),
(@GUID+6, 1),
(@GUID+7, 1);

DELETE FROM creature_questrelation WHERE quest = 11922;
INSERT INTO creature_questrelation VALUES (26113, 11922);

DELETE FROM creature_involvedrelation WHERE quest = 11922;
INSERT INTO creature_involvedrelation VALUES (26113, 11922);

DELETE FROM creature_questrelation WHERE quest = 11926;
INSERT INTO creature_questrelation VALUES (26113, 11926);

DELETE FROM creature_involvedrelation WHERE quest = 11926;
INSERT INTO creature_involvedrelation VALUES (26113, 11926);

DELETE FROM creature_questrelation WHERE quest = 11731;
INSERT INTO creature_questrelation VALUES (25975, 11731);

DELETE FROM creature_involvedrelation WHERE quest = 11731;
INSERT INTO creature_involvedrelation VALUES (25975, 11731);

DELETE FROM creature_questrelation WHERE quest = 11921;
INSERT INTO creature_questrelation VALUES (25975, 11921);

DELETE FROM creature_involvedrelation WHERE quest = 11921;
INSERT INTO creature_involvedrelation VALUES (25975, 11921);

DELETE FROM creature_questrelation WHERE quest = 11882;
INSERT INTO creature_questrelation VALUES (25962, 11882);

DELETE FROM creature_involvedrelation WHERE quest = 11882;
INSERT INTO creature_involvedrelation VALUES (25975, 11882);

UPDATE quest_template SET prevquestid = 11915 WHERE entry = 11922;
UPDATE quest_template SET prevquestid = 11922 WHERE entry = 11926;
UPDATE quest_template SET SrcItemId = 34862, SrcItemCount = 1 WHERE entry IN (11922, 11926, 11731, 11921);

UPDATE quest_template SET prevquestid = 11882 WHERE entry = 11731;
UPDATE quest_template SET prevquestid = 11731 WHERE entry = 11921;

-- Spellfocus
UPDATE gameobject_template SET data1 = 50 WHERE entry = 300068;

INSERT INTO `gameobject` VALUES
(@GUID+8,300068,1,1,-1026.39,290.003,135.829,4.64258,0,0,0.331599,-0.94342,1,0,1),
(@GUID+9,300068,0,1,1823.75,212.431,60.2023,6.23082,0,0,0.331599,-0.94342,1,0,1),
(@GUID+10,300068,1,1,1917.02,-4341.81,20.658,5.61996,0,0,0.331599,-0.94342,1,0,1),
(@GUID+11,300068,1,1,8705.96,934.905,14.8791,1.02974,0,0,0.331599,-0.94342,1,0,1),
(@GUID+12,300068,0,1,-4701.44,-1230.36,501.743,5.044,0,0,0.331599,-0.94342,1,0,1),
(@GUID+13,300068,0,1,-8836.37,851.844,99.1308,4.81711,0,0,0.331599,-0.94342,1,0,1);

DELETE FROM game_event_gameobject WHERE guid BETWEEN @GUID+8 AND @GUID+13;
INSERT INTO game_event_gameobject (guid, event) VALUES
(@GUID+8, 1),
(@GUID+9, 1),
(@GUID+10, 1),
(@GUID+11, 1),
(@GUID+12, 1),
(@GUID+13, 1);

DELETE FROM spell_script_target WHERE entry = 46054;
INSERT INTO spell_script_target VALUES (46054, 1, 16606);

UPDATE creature_template SET scale = 1.5, ScriptName = "npc_midsummer_bonfire" WHERE entry = 16606;

UPDATE quest_template SET SpecialFlags = 0, ReqCreatureOrGOId1 = 16606, ReqCreatureOrGOCount1 = 8 WHERE entry = 11922;
UPDATE locales_quest SET ObjectiveText1_loc2 = "Toucher 8 braseros" WHERE entry = 11922;
UPDATE locales_quest SET EndText_loc2 = "" WHERE entry = 11922;
UPDATE quest_template SET SpecialFlags = 0, ReqCreatureOrGOId1 = 16606, ReqCreatureOrGOCount1 = 20 WHERE entry = 11926;
UPDATE locales_quest SET ObjectiveText1_loc2 = "Toucher 20 braseros" WHERE entry = 11926;
UPDATE locales_quest SET EndText_loc2 = "" WHERE entry = 11926;

UPDATE quest_template SET SpecialFlags = 0, ReqCreatureOrGOId1 = 16606, ReqCreatureOrGOCount1 = 8 WHERE entry = 11731;
UPDATE locales_quest SET ObjectiveText1_loc2 = "Toucher 8 braseros" WHERE entry = 11731;
UPDATE locales_quest SET EndText_loc2 = "" WHERE entry = 11731;
UPDATE quest_template SET SpecialFlags = 0, ReqCreatureOrGOId1 = 16606, ReqCreatureOrGOCount1 = 20 WHERE entry = 11921;
UPDATE locales_quest SET ObjectiveText1_loc2 = "Toucher 20 braseros" WHERE entry = 11921;
UPDATE locales_quest SET EndText_loc2 = "" WHERE entry = 11921;

SET @CREGUID := 16000000;

DELETE FROM creature WHERE id = 16606;
DELETE FROM creature WHERE guid BETWEEN @CREGUID AND @CREGUID+19;
INSERT INTO `creature` VALUES
(@CREGUID,16606,1,1,0,0,8717.3,920.104,15.1784,3.12217,25,0,0,5000,0,0,0,0,'npc_midsummer_bonfire'),
(@CREGUID+1,16606,1,1,0,0,8716.73,936.471,14.8964,3.12217,25,0,0,5000,0,0,0,0,'npc_midsummer_bonfire'),
(@CREGUID+2,16606,1,1,0,0,-1035.88,312.549,134.666,5.25977,25,0,0,5000,0,0,0,0,''),
(@CREGUID+3,16606,0,1,0,0,1837.19,225.627,60.246,3.10384,25,0,0,5000,0,0,0,0,''),
(@CREGUID+4,16606,0,1,0,0,1837.4,213.158,60.3433,3.10384,25,0,0,5000,0,0,0,0,''),
(@CREGUID+5,16606,0,1,0,0,1840.18,222.607,60.2069,3.10384,25,0,0,5000,0,0,0,0,''),
(@CREGUID+6,16606,0,1,0,0,1840.84,216.245,60.074,3.10384,25,0,0,5000,0,0,0,0,''),
(@CREGUID+7,16606,0,1,0,0,1838.23,218.969,60.1496,3.10384,25,0,0,5000,0,0,0,0,''),
(@CREGUID+8,16606,1,1,0,0,-1048.8,299.889,134.401,5.25977,25,0,0,5000,0,0,0,0,''),
(@CREGUID+9,16606,1,1,0,0,8722.04,933.662,15.9977,3.12217,25,0,0,5000,0,0,0,0,'npc_midsummer_bonfire'),
(@CREGUID+10,16606,1,1,0,0,8721.22,923.779,16.4874,3.12217,25,0,0,5000,0,0,0,0,'npc_midsummer_bonfire'),
(@CREGUID+11,16606,1,1,0,0,8716.85,928.883,15.3478,3.12217,25,0,0,5000,0,0,0,0,'npc_midsummer_bonfire'),
(@CREGUID+12,16606,1,1,0,0,1923.87,-4315.27,22.4918,4.57538,25,0,0,5000,0,0,0,0,''),
(@CREGUID+13,16606,1,1,0,0,1915.58,-4320.46,21.8202,4.92842,25,0,0,5000,0,0,0,0,''),
(@CREGUID+14,16606,1,1,0,0,1925.15,-4321.27,21.6547,4.92842,25,0,0,5000,0,0,0,0,''),
(@CREGUID+15,16606,1,1,0,0,-1042.52,306.56,134.451,5.30995,25,0,0,5000,0,0,0,0,''),
(@CREGUID+16,16606,1,1,0,0,-1041.61,313.163,133.278,5.35009,25,0,0,5000,0,0,0,0,''),
(@CREGUID+17,16606,1,1,0,0,-1049.08,306.373,132.937,5.25977,25,0,0,5000,0,0,0,0,''),
(@CREGUID+18,16606,1,1,0,0,1920.49,-4319.35,21.8167,3.54839,25,0,0,5000,0,0,0,0,''),
(@CREGUID+19,16606,1,1,0,0,1918.07,-4314.9,22.8562,4.66737,25,0,0,5000,0,0,0,0,'');

UPDATE quest_template SET EndText = "" WHERE entry = 11922;
UPDATE locales_quest SET EndText_loc2 = "" WHERE entry = 11922;
UPDATE spell_template SET effect1 = 0, effect2 = 0 WHERE id = 46651;
