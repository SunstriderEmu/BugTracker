/* Shadowsword Fury Mage damage*/
UPDATE `creature_template` SET 
    `mindmg` = 15000,
    `maxdmg` = 18500,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25799;

/* Shadowsword Berserker damage*/
UPDATE `creature_template` SET 
    `mindmg` = 15000,
    `maxdmg` = 18500,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25798;

/* Void sentinel (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 33000,
    `maxdmg` = 36000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25772;

/* Entropius (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 30000,
    `maxdmg` = 36000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25840;

/* Speed for Dark Fiends */
UPDATE creature_template SET speed = 0.7 WHERE entry = 25744;

/* Speed for Singularity */
UPDATE creature_template SET speed = 0.5 WHERE entry = 25855;
