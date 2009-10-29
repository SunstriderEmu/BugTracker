
DELETE FROM `gameobject_template` where `entry` IN (123329, 124371);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `castBarCaption`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES
(123329, 3, 1, 'Baelog''s Chest', '', 0, 0, 1, 93, 5066, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''),
(124371, 0, 1369, 'Keystone', '', 0, 32, 1, 0, 359, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'go_keystone_chamber');

DELETE FROM `gameobject_loot_template` where `entry` = 5066;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `groupid`, `mincountOrRef`, `maxcount`, `lootcondition`, `condition_value1`, `condition_value2`) VALUES
(5066, 7740, 100, 0, 1, 1, 0, 0, 0);

DELETE FROM `areatrigger_teleport` where `id` = 288;
INSERT INTO `areatrigger_teleport` (`id`, `name`, `access_id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(288, 'Uldaman Instance Start', 0, 0, -6066.73, -2955.63, 209.776, 3);

DELETE FROM `areatrigger_scripts` where `entry` = 822;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES (822, 'at_map_chamber');
