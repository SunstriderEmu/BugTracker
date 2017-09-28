UPDATE `eventai_scripts` SET `action1_param2` = 0 WHERE `creature_id` = 25509 AND `id` = 2550902;

UPDATE `eventai_scripts` SET `event_param1` = 10000, `event_param2` = 15000, `event_param3` = 10000, `event_param4` = 15000, `action1_param3` = 1 WHERE `creature_id` = 25597 AND `id` = 2559703;
UPDATE `eventai_scripts` SET `event_param1` = 3000, `event_param2` = 3000, `event_param3` = 3000, `event_param4` = 3000 WHERE `creature_id` = 25597 AND `id` = 2559702;
INSERT INTO `eventai_scripts` (`id`, `creature_id`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`) VALUES (2559704, 25597, 3, 10000, 15000, 10000, 15000, 11, 43991, 4, 1);
