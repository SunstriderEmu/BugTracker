UPDATE creature_template SET scale = 1.5, minlevel = 70, maxlevel = 70, minhealth = 110000, maxhealth = 110000, minmana = 78875, maxmana = 78875, rank = 1, mechanic_immune_mask = 68944 WHERE entry = 25708;

UPDATE `creature_template` SET 
    `mindmg` = 8000,
    `maxdmg` = 13000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25708;
