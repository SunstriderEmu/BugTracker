UPDATE `creature_template` SET `AIName` = 'NullCreatureAI' WHERE `entry` = 25315;

UPDATE `creature_template` SET `modelid_A` = 16946, `modelid_A2` = 0, `modelid_H` = 16946, `modelid_H2` = 0 WHERE `entry` = 26262;

UPDATE `creature_template` SET `modelid_A` = 22742, `modelid_A2` = 0, `modelid_H` = 22742 , `modelid_H2` = 0 WHERE `entry` = 24925;

UPDATE `creature` SET `spawntimesecs` = 604800 WHERE `id` = 25608;

UPDATE `creature` SET `spawntimesecs` = 604800 WHERE `id` = 25319;

DELETE FROM `command` WHERE `name` = 'debug threatunitlist';
INSERT INTO `command` (`name`,`security`,`help`) VALUES('debug threatunitlist', 3, 'Syntax: .debug threatunitlist');

DELETE FROM `spell_script_target` WHERE `entry` = 46707;
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES (46707, 1, 25653);

DELETE FROM `spell_script_target` WHERE `entry` = 46474;
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES (46474, 1, 25315);

DELETE FROM `spell_target_position` WHERE `id` = 46473;
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES (46473, 580, 1701.7, 635.515, 27.8, 4.65461);

