DELETE FROM `escort_waypoints` WHERE `entry`=5644;
INSERT INTO `escort_waypoints` VALUES
(5644, 1, -339.679, 1752.04, 139.482, 0, ''),
(5644, 2, -328.957, 1734.95, 139.327, 0, ''),
(5644, 3, -350.747, 1731.12, 139.338, 0, ''),
(5644, 4, -365.064, 1739.04, 139.376, 0, ''),
(5644, 5, -371.105, 1746.03, 139.374, 0, ''),
(5644, 6, -383.141, 1738.62, 138.93, 0, ''),
(5644, 7, -390.445, 1733.98, 136.353, 0, ''),
(5644, 8, -401.368, 1726.77, 131.071, 0, ''),
(5644, 9, -416.016, 1721.19, 129.807, 0, ''),
(5644, 10, -437.139, 1709.82, 126.342, 0, ''),
(5644, 11, -459.862, 1687.92, 116.059, 0, ''),
(5644, 12, -460.686, 1679.55, 111.976, 0, ''),
(5644, 13, -461.485, 1670.94, 109.033, 0, ''),
(5644, 14, -468.53, 1645.51, 102.811, 0, ''),
(5644, 15, -474.529, 1615.97, 97.228, 0, ''),
(5644, 16, -474.329, 1590.01, 94.4982, 0, '');

UPDATE `creature_template` SET `ScriptName` = 'npc_dalinda' WHERE `entry` = '5644';
UPDATE `creature_template` SET `ScriptName` = 'npc_aged_dying_ancient_kodo' WHERE `entry` = '4700';
UPDATE `creature_template` SET `ScriptName` = 'npc_aged_dying_ancient_kodo' WHERE `entry` = '4701';
UPDATE `creature_template` SET `ScriptName` = 'npc_aged_dying_ancient_kodo' WHERE `entry` = '4702';
UPDATE `creature_template` SET `ScriptName` = 'npc_aged_dying_ancient_kodo' WHERE `entry` = '11627';
UPDATE `quest_template` SET `ReqSpellCast1` = '18362' WHERE `entry` = '5561';
DELETE FROM `npc_text` WHERE `ID`=21000;
INSERT INTO `npc_text` VALUES ('21000', 'Why is it that small creatures such as goblins are always fascinated with larger creatures?', null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', 'Comment se fait-ce que les petites créatures telles que les gobelins soient toujours fascinées par les créatures plus grosses ?', null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0');
DELETE FROM `script_texts` WHERE `entry` BETWEEN '-1600350' AND '-1600348';
INSERT INTO `script_texts` VALUES ('-1600348', 'Ah...the wondrous sound of kodos. I love the way they make the ground shake... inspect the beast for me.', null, 'Ah... Le merveilleux son des kodos. J''adore la façon qu''ils ont de faire trembler le sol... Inspectez cette bête pour moi.', null, null, null, null, null, null, '0', '0', '0', '0', 'kodo round SAY_SMEED_HOME_1');
INSERT INTO `script_texts` VALUES ('-1600349', 'Hey, look out with that kodo! You had better inspect that beast before I give you credit!', null, 'Hey, regardez à ce kodo ! Vous devez inspecter cette bête avant que je vous paye !', null, null, null, null, null, null, '0', '0', '0', '0', 'kodo round SAY_SMEED_HOME_2');
INSERT INTO `script_texts` VALUES ('-1600350', 'That kodo sure is a beauty. Wait a minute, where are my bifocals? Perhaps you should inspect the beast for me.', null, 'Ce kodo est vraiment beau. Attendez une minute, où sont mes lunettes ? Peut-être devriez-vous inspecter cette bête pour moi.', null, null, null, null, null, null, '0', '0', '0', '0', 'kodo round SAY_SMEED_HOME_3');
