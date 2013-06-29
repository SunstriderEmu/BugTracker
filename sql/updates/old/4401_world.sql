/* Portal effect */
UPDATE creature_template SET scale = 2 where entry = 25770;

/* Shadowsword Fury Mage (Fel Fireball) */
DELETE FROM smart_scripts WHERE entryorguid = 25799 AND action_param1 = 46101;
INSERT INTO `smart_scripts` (`entryorguid`, `id`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (25799, 1, 2, 10000, 10000, 1000, 1000, 11, 46101, 2, 'Shadowsword Fury Mage - Cast Fel Fireball');

/* Shadowsword Fury Mage damage*/
UPDATE `creature_template` SET 
    `mindmg` = 14000,
    `maxdmg` = 15000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25799;

/* Shadowsword Berserker damage*/
UPDATE `creature_template` SET 
    `mindmg` = 14000,
    `maxdmg` = 15000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25798;
