UPDATE `creature_template` SET `minhealth` = 7335, `maxhealth` = 7335, `minlevel` = 70, `maxlevel` = 70, `equipment_id` = 3005 WHERE `entry` = 26259;

DELETE FROM `creature_equip_template` WHERE `entry` = 3005;
INSERT INTO `creature_equip_template` (`entry`, `equipmodel1`, `equipmodel2`) VALUES (3005, 38099, 48068);

UPDATE `creature_template` SET `minhealth` = 1850000, `maxhealth` = 1850000, `minmana` = 1693000, `maxmana` = 1693000 WHERE `entry` = 25319;

UPDATE `script_texts` SET `sound` = 12550 WHERE `entry` = -1580090;

UPDATE `creature_template` SET `minhealth` = 1517000, `maxhealth` = 1517000, `minmana` = 50805, `maxmana` = 50805 WHERE `entry` = 26246;

UPDATE `creature_template` SET `minhealth` = 1117000, `maxhealth` = 1117000, `minmana` = 31550, `maxmana` = 31550 WHERE `entry` = 26247;

