DELETE FROM `script_texts` WHERE `entry` IN (-1600398,-1600397,-1600396,-1600395,-1600394,-1600393,-1600392,-1600391);
INSERT INTO `script_texts` VALUES ('-1600398', 'And try not to get lost this time...', null, 'Et essaye de ne pas te perdre cette fois...', null, null, null, null, null, null, '0', '0', '0', '0', 'tooga SAY_TORT_POST_6');
INSERT INTO `script_texts` VALUES ('-1600397', 'Yes Torta. Whatever your heart desires...', null, 'Oui Torta. Peu importe ce que ton coeur désire...', null, null, null, null, null, null, '0', '0', '0', '0', 'tooga SAY_TOOG_POST_5');
INSERT INTO `script_texts` VALUES ('-1600396', 'Enough with the rambling. I am starving! Now, get your dusty shell into that ocean and bring momma some grub.', null, 'Assez pour la randonnée. J''ai faim ! Maintenant, va dans l''océan avec ta coquille sale, et ramène moi quelque chose.', null, null, null, null, null, null, '0', '0', '0', '0', 'tooga SAY_TORT_POST_4');
INSERT INTO `script_texts` VALUES ('-1600395', 'My dearest Torta. I have been gone for so long. Finally we are reunited. At long last our love can blossom again.', null, 'Mon cher Torta. Je suis parti tellement longtemps. Nous sommes finalement réunis. Après si longtemps, notre amour peut fleurir à nouveau.', null, null, null, null, null, null, '0', '0', '0', '0', 'tooga SAY_TOOG_POST_3');
INSERT INTO `script_texts` VALUES ('-1600394', 'You have any idea how long I\'ve been waiting here? And where\'s dinner? All that time gone and nothing to show for it?', null, 'Vous avez une idée de combien de temps j''ai passé ici ? Et où est le repas ? Tout ce temps passé et rien à montrer ?', null, null, null, null, null, null, '0', '0', '0', '0', 'tooga SAY_TORT_POST_2');
INSERT INTO `script_texts` VALUES ('-1600393', 'Torta, my love! I have returned at long last.', null, 'Torga, mon amour ! Je suis revenu finalement.', null, null, null, null, null, null, '0', '0', '0', '0', 'tooga SAY_TOOG_POST_1');
INSERT INTO `script_texts` VALUES ('-1600392', 'Torta must be so worried.', null, 'Torta doit être si inquiet.', null, null, null, null, null, null, '0', '0', '0', '0', 'tooga SAY_TOOG_WORRIED');
INSERT INTO `script_texts` VALUES ('-1600391', 'I\'m Thirsty.', null, 'J''ai soif.', null, null, null, null, null, null, '0', '0', '0', '0', 'tooga SAY_TOOG_THIRST');

UPDATE `quest_template` SET `SpecialFlags` = '2' WHERE `entry` = '1560';
UPDATE `creature_template` SET `ScriptName` = 'npc_tooga' WHERE `entry` = '5955';

