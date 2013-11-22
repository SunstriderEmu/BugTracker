UPDATE `spell_template` SET `effectBasePoints3` = 45657 WHERE `id` = 46605;
UPDATE `creature_template` SET `spell1` = '45862', `spell2` = '45856', `spell3` = '45860', `spell4` = '45848' WHERE `entry` = 25653;
UPDATE `creature_template` SET `modelid_A` = 15880, `modelid_H` = 15880, `minlevel` = 70, `maxlevel` = 70, `minhealth` = 20000, `maxhealth` = 20000, `faction_A` = 14, `faction_H` = 14, `AIName` = 'NullCreatureAI' WHERE `entry` = 25735;


DELETE FROM  `creature_text` WHERE `entry` IN (25608, 25315, 25319);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25608, 0, 0, 'All my plans have led to this!', 'Continuez ! Ne perdez pas de temps !', 1, 0, 100, 0, 0, 12495, 'off combat 1 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25608, 0, 1, 'Stay on task! Do not waste time', 'Tous mes plans aboutissent ici !', 1, 0, 100, 0, 0, 12496, 'off combat 2 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25608, 0, 2, 'I have waited long enough!', 'J''ai assez attendu !', 1, 0, 100, 0, 0, 12497, 'off combat 3 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25608, 0, 3, 'Fail me and suffer for eternity!', 'Echouez, et vous souffrirez pour l''éternité !', 1, 0, 100, 0, 0, 12498, 'off combat 4 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25608, 0, 4, 'Drain the girl! Drain her power until there is nothing but a vacant shell!', 'Drainez la fille ! Drainez toute sa puissance, qu''il n''en reste qu''une coquille vide !', 1, 0, 100, 0, 0, 12499, 'off combat 5 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 0, 0, 'The expendible have perished... So be it! Now I shall succeed where Sargeras could not! I will bleed this wretched world and secure my place as the true master of the Burning Legion. The end has come! Let the unraveling \nof this world commence!', 'Les sacrifiables ont péri ... Ainsi soit-il! Maintenant, je vais réussir là où Sargeras ne pouvait pas! Je vais saigner ce monde misérable et sécuriser ma place comme le véritable maître de la Légion ardente. La fin est venue! Que le dénouement de ce monde commence!', 1, 0, 100, 0, 0, 12500, 'emerge - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 1, 0, 'Another step towards destruction!', 'Un nouveau pas vers la destruction !', 1, 0, 100, 0, 0, 12501, 'slay 1 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 1, 1, 'Anak-ky''ri!', 'Anak-ky''ri!', 1, 0, 100, 0, 0, 12502, 'slay 2 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 2, 0, 'Who can you trust?', 'En qui avoir confiance ?', 1, 0, 100, 0, 0, 12503, 'reflection 1 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 2, 1, 'The enemy is among you.', 'L''ennemi est parmi vous !', 1, 0, 100, 0, 0, 12504, 'reflection 2 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 3, 0, 'begins to channel dark energy', 'commence à canaliser l’énergie noire', 3, 0, 100, 0, 0, 0, 'emote darkness - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 4, 0, 'Chaos!', 'Chaos !', 1, 0, 100, 0, 0, 12505, 'darkness 1 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 4, 1, 'Destruction!', 'Destruction !', 1, 0, 100, 0, 0, 12506, 'darkness 2 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 4, 2, 'Oblivion!', 'Oubli !', 1, 0, 100, 0, 0, 12507, 'darkness 3 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 5, 0, 'I will not be denied! This world shall fall!', 'Rien ne m''arrêtera ! Ce monde va tomber !', 1, 0, 100, 0, 0, 12508, 'phase 3 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 6, 0, 'Do not harbor false hope. You cannot win!', 'Assez de faux espoirs ! Vous ne pouvez pas gagner !', 1, 0, 100, 0, 0, 12509, 'phase 4 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 7, 0, 'Aggghh! The powers of the Sunwell... turned... against me! What have you done? WHAT HAVE YOU DONE?', 'AArggghhh ! Les pouvoirs du Puits de soleil… se retournent... contre moi ! Qu''avez-vous fait ? Qu''avez-vous fait ??', 1, 0, 100, 0, 0, 12510, 'phase 5 - Kil Jaeden');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25315, 8, 0, 'Nooooooooooooo!', 'Nooooooooooon !', 1, 0, 100, 0, 0, 12527, 'death - Kil Jaeden');

INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25319, 0, 0, 'You are not alone. The Blue Dragonflight shall help you vanquish the Deceiver.', 'Vous n''êtes pas seul. Le dragon bleu doit vous aider à vaincre le Trompeur.', 1, 0, 100, 0, 0, 12438, 'join - Kalecgos');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25319, 1, 0, 'I will channel my power into the orbs, be ready!', 'Je vais canaliser mon pouvoir dans les orbes, soyez prêts !', 1, 0, 100, 0, 0, 12440, 'orb 1 - Kalecgos');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25319, 2, 0, 'I have empowered another orb! Use it quickly!', 'J''ai transmis ma puissance à un autre orbe ! Utilisez-le rapidement !', 1, 0, 100, 0, 0, 12441, 'orb 2 - Kalecgos');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25319, 3, 0, 'Another orb is ready! Make haste!', 'Un autre orbe est prêt ! Soyez rapide !', 1, 0, 100, 0, 0, 12442, 'orb 2 - Kalecgos');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25319, 4, 0, 'I have channeled all I can! The power is in your hands!', 'J''ai canalisé tout ce que j''ai pu ! Le pouvoir est entre vos mains !', 1, 0, 100, 0, 0, 12443, 'orb 2 - Kalecgos');
