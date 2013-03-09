UPDATE `creature_template` SET `AIName` = 'NullCreatureAI', `ScriptName` = '' WHERE `entry` = 11502;

DELETE FROM `creature_scripts` WHERE `entryorguid` = 11502;
INSERT INTO `creature_scripts` VALUES (11502, 'Boss_Ragnaros');
