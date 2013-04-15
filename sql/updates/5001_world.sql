UPDATE `creature_template` SET `AIName` = 'NullCreatureAI', `ScriptName` = '' WHERE `entry` IN (21217, 21873, 21865);

DELETE FROM `creature_scripts` WHERE `entryorguid` = 21873;
INSERT INTO `creature_scripts` VALUES (21873, 'Mob_Coilfang_Guardian');

DELETE FROM `creature_scripts` WHERE `entryorguid` = 21865;
INSERT INTO `creature_scripts` VALUES (21865, 'Mob_Coilfang_Ambusher');

DELETE FROM `creature_scripts` WHERE `entryorguid` = 21217;
INSERT INTO `creature_scripts` VALUES (21217, 'Boss_Lurker_Below');
