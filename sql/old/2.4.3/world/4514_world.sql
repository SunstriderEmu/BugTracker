/* Hp for M'uru and entropius */
UPDATE creature_template SET minhealth = 2995000, maxhealth = 2995000 WHERE entry = 25741;
UPDATE creature_template SET minhealth = 2210000, maxhealth = 2210000 WHERE entry = 25840;

/* Speed for Dark Fiends */
UPDATE creature_template SET speed = 0.5 WHERE entry = 25744;

/* Speed for Singularity */
UPDATE creature_template SET speed = 0.3 WHERE entry = 25855;

/* Black Hole Effect */
UPDATE spell_template SET effectBasePoints1 = 12 WHERE id = 46230;

/* Shadowsword Fury Mage damage*/
UPDATE `creature_template` SET 
    `mindmg` = 15000,
    `maxdmg` = 17000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25799;

/* Shadowsword Berserker damage*/
UPDATE `creature_template` SET 
    `mindmg` = 15000,
    `maxdmg` = 17000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25798;

/* Void sentinel (damage) */
UPDATE `creature_template` SET 
    `dmgschool` = 0,
    `mindmg` = 23000,
    `maxdmg` = 25000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE `entry` = 25772;
