UPDATE `creature_template` SET `minhealth` = 7000, `maxhealth` = 7000, `minmana` = 7200, `maxmana` = 7200, `minlevel` = 70, `maxlevel` = 70 WHERE `entry` = 26289;

DELETE FROM `spell_target_position` WHERE `id` = 46473;
INSERT INTO `spell_target_position` VALUES (46473, 580, 1667.30, 633.05, 28.05, 6.22);

UPDATE `script_texts` SET `content_default` = 'As the Legion\'s final defeat draws ever-nearer, stand proud in the knowledge that you have saved worlds without number from the flame.', `content_loc2` = 'Alors qu\'approche l\'ultime défaite de la Légion, vous pouvez vous enorgueillir d\'avoir sauvé des mondes innombrables des flammes.' WHERE `entry` = -1580100;

DELETE FROM `script_texts` WHERE `entry` = -1580111;
INSERT INTO `script_texts` (`entry`, `content_default`,  `content_loc2`, `sound`) VALUES (-1580111, 'Just as this day marks an ending, so too does it herald a new beginning...', 'Ce jour marque une fin, mais il annonce également un nouveau commencement…', 12517);

UPDATE `script_texts` SET `sound` = 12526 WHERE `entry` = -1580109;

