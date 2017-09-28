UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 25948;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25948;
INSERT INTO `smart_scripts` (`entryorguid`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`,  `action_type`, `action_param1`, `target_type`) VALUES ('25948', '2', '1000', '1000', '360000', '420000', '11', '46305', '1');

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 25591;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25591;
INSERT INTO `smart_scripts` (`entryorguid`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`,  `action_type`, `action_param1`, `target_type`) VALUES ('25591', '2', '1000', '1000', '660000', '720000', '11', '46278', '1');

UPDATE `creature_template` SET `ScriptName` = 'npc_doomfire_destroyer' WHERE `entry` = 25592;
DELETE FROM `eventai_scripts` WHERE `creature_id` = 25592;

UPDATE `eventai_scripts` SET `event_flags` = 3 WHERE `creature_id` = 25595 AND `id` = 2559504;
