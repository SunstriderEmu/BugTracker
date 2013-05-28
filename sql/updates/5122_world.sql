/* Ranged damage for Sinister Reflection */
UPDATE `creature_template` SET
    `minrangedmg` = 2750,
    `maxrangedmg` = 7750,
    `rangedattackpower` = 36750
  WHERE `entry` = 25708;

/* Ranged damage for Coilfang Ambusher */
UPDATE `creature_template` SET
    `minrangedmg` = 3003,
    `maxrangedmg` = 6139,
    `rangedattackpower` = 31997
  WHERE `entry` = 21873;
