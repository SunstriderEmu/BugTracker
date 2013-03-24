UPDATE `creature_template` SET `AIName` = 'NullCreatureAI', `ScriptName` = '' WHERE `entry` = 12143;

DELETE FROM `creature_scripts` WHERE `entryorguid` = 12143;
INSERT INTO `creature_scripts` VALUES (12143, 'Son_Of_Flame');
