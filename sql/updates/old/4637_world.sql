DELETE FROM creature WHERE id = 2434;
INSERT INTO `creature` VALUES ('',2434,0,1,0,385,-743.164,-640.294,16.5805,6.24379,25,0,0,1500,0,0,0,0,'');

UPDATE creature_template SET faction_a = 35, faction_h = 35 WHERE entry = 2333;

DELETE FROM gameobject_questrelation WHERE quest = 551;
INSERT INTO gameobject_questrelation VALUES (1740, 551), (186420, 551);
