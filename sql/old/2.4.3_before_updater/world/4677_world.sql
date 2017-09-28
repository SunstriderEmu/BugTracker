/* Damage for Sunblade Protector */
UPDATE `creature_template` SET 
    `mindmg` = 25000, 
    `maxdmg` = 30000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 25507;

/* Script for Fire Fiend */
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26101;
INSERT INTO `smart_scripts` (`entryorguid`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`) VALUES (26101, 6, 5000, 10000, 5000, 10000, 11, 46551);
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 26101;

/* Damage for Sunblade Vindicator */
UPDATE `creature_template` SET 
    `mindmg` = 25000, 
    `maxdmg` = 30000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 25369;

/* Damage for  Kalecgos */
UPDATE `creature_template` SET 
    `mindmg` = 25000, 
    `maxdmg` = 30000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 24850;

/* Damage for  Sunblade Dusk Priest */
UPDATE `creature_template` SET 
    `mindmg` = 10000, 
    `maxdmg` = 15000, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `entry` = 25370;
