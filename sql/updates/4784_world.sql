/* Damage for Hand of the Deceiver */
UPDATE `creature_template` SET 
    `mindmg` = 12000, 
    `maxdmg` = 15000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 25588;
