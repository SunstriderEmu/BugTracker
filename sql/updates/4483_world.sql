DELETE FROM `creature_equip_template` WHERE `entry` = 23864;
INSERT INTO `creature_equip_template` (`entry`, `equipmodel1`) VALUES (23864, 19779);

UPDATE `creature_template` SET `equipment_id` = 23864 WHERE `entry` = 7354;
