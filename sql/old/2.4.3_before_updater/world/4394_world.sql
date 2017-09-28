/* Shadowsword Fury Mage equip*/
DELETE FROM `creature_equip_template` WHERE entry = 3001;
INSERT INTO `creature_equip_template` (`entry`, `equipmodel1`) VALUES (3001, 40899);
UPDATE `creature_template` SET `equipment_id` = 3001 WHERE `entry` = 25799;

/* Shadowsword Fury Mage damage*/
UPDATE `creature_template` SET 
    `mindmg` = 7000,
    `maxdmg` = 8000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25799;

/* Shadowsword Berserker damage*/
UPDATE `creature_template` SET 
    `mindmg` = 7000,
    `maxdmg` = 8000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25798;

/* Void Spawn (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 4000,
    `maxdmg` = 5000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25824;
