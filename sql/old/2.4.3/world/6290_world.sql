DELETE FROM `creature_equip_template` WHERE `entry` = 91535;
INSERT INTO `creature_equip_template` VALUES (91535, 41560, 0, 0, 3842, 0, 0, 13, 0, 0);
UPDATE creature_template SET `equipment_id` = 91535 WHERE entry = 20064;

DELETE FROM `creature_equip_template` WHERE `entry` = 91536;
INSERT INTO `creature_equip_template` VALUES (91536, 0, 40867, 0, 0, 33490436, 0, 0, 1038, 0);
UPDATE `creature_template` SET `equipment_id` = 91536 WHERE entry = 20060;

DELETE FROM `creature_equip_template` WHERE `entry` = 91537;
INSERT INTO `creature_equip_template` VALUES (91537, 41872, 0, 0, 260, 0, 0, 16, 0, 0);
UPDATE `creature_template` SET `equipment_id` = 91537 WHERE entry = 20063;

DELETE FROM `creature_equip_template` WHERE `entry` = 91538;
INSERT INTO `creature_equip_template` VALUES (91538, 41895, 0, 0, 772, 0, 0, 10, 0, 0);
UPDATE `creature_template` SET `equipment_id` = 91538 WHERE entry = 20062;

UPDATE `creature_template` SET `minlevel` = 73, `maxlevel` = 73 WHERE entry = 20062;
