/* Shadowsword Fury Mage damage*/
UPDATE `creature_template` SET 
    `AIName` = "",
    `mindmg` = 15000,
    `maxdmg` = 19500,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25799;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25799;
DELETE FROM `creature_scripts` WHERE `entryorguid` = 25799;
INSERT INTO `creature_scripts` VALUES (25799, 'npc_mage');

/* Shadowsword Berserker damage*/
UPDATE `creature_template` SET 
    `AIName` = "",
    `mindmg` = 15000,
    `maxdmg` = 19500,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25798;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25798;
DELETE FROM `creature_scripts` WHERE `entryorguid` = 25798;
INSERT INTO `creature_scripts` VALUES (25798, 'npc_berserker');

/* Void sentinel (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 38000,
    `maxdmg` = 42000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25772;

/* Entropius (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 36000,
    `maxdmg` = 42000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25840;

/* Speed for Dark Fiends */
UPDATE creature_template SET speed = 0.8 WHERE entry = 25744;

/* Speed for Singularity */
UPDATE creature_template SET speed = 0.7 WHERE entry = 25855;
