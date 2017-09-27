/* Damage for The Lurker Below */
UPDATE `creature_template` SET 
    `mindmg` = 28000, 
    `maxdmg` = 33000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 21217;
