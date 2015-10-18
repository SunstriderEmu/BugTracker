/* Void sentinel (HP) */
UPDATE `creature_template` SET `minhealth` = 120000, `maxhealth` = 120000 WHERE `entry` = 25772;
/* Void Spawn (HP) */
UPDATE `creature_template` SET `minhealth` = 24000, `maxhealth` = 24000 WHERE `entry` = 25824;
/* Void sentinel (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 24000,
    `maxdmg` = 26000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25772;
/* Void Spawn (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 3000, /* not sure */
    `maxdmg` = 5000, /* not sure */
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25824;

/* Shadowsword Berserker equip*/
DELETE FROM `creature_equip_template` WHERE entry = 3000;
INSERT INTO `creature_equip_template` (`entry`, `equipmodel1`, `equipmodel2`) VALUES (3000, 46970, 46970);
UPDATE `creature_template` SET `equipment_id` = 3000 WHERE `entry` = 25798;