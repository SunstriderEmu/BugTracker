UPDATE `creature_template` SET `mechanic_immune_mask` = 536872961 WHERE `entry` = 25367;
UPDATE `creature_template` SET `mechanic_immune_mask` = 2049 WHERE `entry` = 25371;

UPDATE `creature_template` SET `minhealth` = 190000, `maxhealth` = 190000 WHERE `entry` = 25370;

DELETE FROM `script_texts` WHERE `entry` = -1580118;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc2`, `type`) VALUES (-1580118, "Ennemis en vue ! Passez à l'attaque pendant que j'essaie d'activer un protecteur !", "Ennemis en vue ! Passez à l'attaque pendant que j'essaie d'activer un protecteur !", 1);
