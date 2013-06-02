/* Void sentinel (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 20000,
    `maxdmg` = 22000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25772;
