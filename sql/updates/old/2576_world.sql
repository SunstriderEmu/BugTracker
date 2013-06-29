UPDATE `quest_template` SET `SpecialFlags` = '2' WHERE `entry` = '1249';
UPDATE `quest_template` SET `ReqCreatureOrGOId1` = '0' WHERE `entry` = '1249';
UPDATE `quest_template` SET `ReqCreatureOrGOCount1` = '0' WHERE `entry` = '1249';

DELETE FROM `script_texts` WHERE `entry` IN (-1600411,-1600412);
INSERT INTO `script_texts` VALUES ('-1600411', '%s growls in acknowledgement before straightening and making her way off into the forest.', null, '%s gronde de façon reconnaissante et s''enfuit vers la forêt.', null, null, null, null, null, null, '0', '2', '0', '0', 'mist EMOTE_AT_HOME');
INSERT INTO `script_texts` VALUES ('-1600412', 'Mist! I feared I would never see you again! Yes, I am well, do not worry for me. You must rest and recover your health.', null, 'Mist ! J''ai cru ne jamais te revoir ! Oui je vais bien, ne t''en fais pas pour moi. Tu dois te reposer et te refaire la santé.', null, null, null, null, null, null, '0', '0', '7', '0', 'mist SAY_AT_HOME');
UPDATE `creature_template` SET `ScriptName` = 'npc_mist' WHERE `entry` = '3568';
UPDATE `quest_template` SET `SpecialFlags` = '2' WHERE `entry` = '938';
