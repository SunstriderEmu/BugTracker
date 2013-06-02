/* Void Spawn */
UPDATE `creature_template` SET 
    `mindmg` = 1500, 
    `maxdmg` = 3000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 25824;
