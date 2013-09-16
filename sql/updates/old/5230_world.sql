UPDATE `spell_template` SET `effect1` = 6 WHERE `id` = 46818;
DELETE FROM `spell_script_target` WHERE `entry` = 46818;
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES (46818, 1, 26262);

UPDATE `creature_template` SET `mindmg` = 930, `maxdmg` = 1898, `attackpower` = 9894, `minrangedmg` = 930, `maxrangedmg` = 1898, `rangedattackpower` = 5000 WHERE entry = 21865;

