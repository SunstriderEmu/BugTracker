/* Coilfang Guardian equip*/
DELETE FROM `creature_equip_template` WHERE entry = 3002;
INSERT INTO `creature_equip_template` (`entry`, `equipmodel1`) VALUES (3002, 39894);
UPDATE `creature_template` SET `equipment_id` = 3002 WHERE `entry` = 21873;

/* Coilfang Ambusher equip*/
DELETE FROM `creature_equip_template` WHERE entry = 3003;
INSERT INTO `creature_equip_template` (`entry`, `equipmodel1`) VALUES (3003, 2786);
UPDATE `creature_template` SET `equipment_id` = 3003 WHERE `entry` = 21865;
