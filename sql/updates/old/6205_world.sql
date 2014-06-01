DELETE FROM `creature_template_addon` WHERE `entry` = 25502;
INSERT INTO `creature_template_addon` VALUES ('25502', '0', '0', '0', '0', '0', '0', '1024', NULL);

UPDATE `creature_template` SET `InhabitType` = 4 WHERE `entry` = 25502;

