/* Black Hole Effect */
UPDATE spell_template SET effectBasePoints1 = 15, effectMiscValue1 = 200 where id = 46230;
/* Black Hole Template */
UPDATE creature_template SET faction_A = 14, faction_H = 14, speed = 1 WHERE entry = 25855;

/* M'uru (damage) */
UPDATE creature_template SET mindmg = 0, maxdmg = 0, attackpower = 0 WHERE entry = 25741;

/* Shadowsword Fury Mage damage*/
UPDATE `creature_template` SET 
    `mindmg` = 10000,
    `maxdmg` = 11000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25799;

/* Shadowsword Berserker damage*/
UPDATE `creature_template` SET 
    `mindmg` = 10000,
    `maxdmg` = 11000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25798;
