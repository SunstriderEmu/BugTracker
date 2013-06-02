/* Void sentinel (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 45000,
    `maxdmg` = 48000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25772;

/* Entropius (damage) */
UPDATE `creature_template` SET 
    `mindmg` = 40000,
    `maxdmg` = 50000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25840;
