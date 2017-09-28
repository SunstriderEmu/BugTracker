DELETE FROM `eventai_scripts` WHERE `creature_id` IN (7355, 7351, 7357, 7356, 7354, 8567);

DELETE FROM `smart_scripts` WHERE `entryorguid` = 7351;
/* Tomb Reaver - Web */
INSERT INTO `smart_scripts` (`entryorguid`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (7351, 2, 5000, 8000, 7000, 16000, 11, 745, 5, 'Tomb Reaver - Web');

UPDATE `creature_template` SET `ScriptName` = 'boss_tuten_kash' WHERE `entry` = 7355;
UPDATE `creature_template` SET `ScriptName` = '', `AIName` = 'SmartAI' WHERE `entry` = 7351;
UPDATE `creature_template` SET `ScriptName` = 'boss_mordresh_fire_eye' WHERE `entry` = 7357;
UPDATE `creature_template` SET `ScriptName` = 'boss_plaguemaw_the_rotting' WHERE `entry` = 7356;
UPDATE `creature_template` SET `ScriptName` = 'boss_ragglesnout' WHERE `entry` = 7354;
UPDATE `creature_template` SET `ScriptName` = 'boss_glutton' WHERE `entry` = 8567;
UPDATE `gameobject_template` SET `ScriptName` = 'go_gong' WHERE `entry` = 148917;
UPDATE `instance_template` SET `script` = 'instance_razorfen_downs' WHERE `map` = 129;
