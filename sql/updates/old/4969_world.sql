UPDATE `creature_template` SET `speed` = '1.2', `mechanic_immune_mask` = 1, `AIName` = 'NullCreatureAI', `ScriptName` = '' WHERE `entry` = 11663;
UPDATE `creature_template` SET `mindmg` = 2000, `maxdmg` = 2500, `baseattacktime` = 2000, `speed` = '1.2', `mechanic_immune_mask` = 1, `AIName` = 'NullCreatureAI', `ScriptName` = '' WHERE `entry` = 11664;
DELETE FROM `creature_scripts` WHERE `entryorguid` IN (11663, 11664);
INSERT INTO `creature_scripts` VALUES (11663, 'Mob_FlameWalker_Healer');
INSERT INTO `creature_scripts` VALUES (11664, 'Mob_FlameWalker_Elite');

DELETE FROM `spell_target_position` WHERE `id` = 20618;
INSERT INTO `spell_target_position` VALUES ('20618', '409', '736.66', '-1176.49', '-118.97', '6.256186');

UPDATE `creature_template` SET `AIName` = 'NullCreatureAI', `ScriptName` = 'Boss_Majordomo' WHERE `entry` = 12018;
DELETE FROM `creature` WHERE `guid` = 98228;
INSERT INTO `creature` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`) VALUES(98228, '12018','409','761.02','-1179.49','-118.89', '2.96','604800');
DELETE FROM `creature_scripts` WHERE `entryorguid` = 12018;
INSERT INTO `creature_scripts` VALUES (12018, 'Boss_Majordomo');

UPDATE `creature` SET `position_x` = '838.424255', `position_y` = '-831.220154', `position_z` = '-232.198166', `orientation` = '2.12' WHERE `id` = 11502;

UPDATE `script_texts` SET `content_loc2` = 'Imprudents mortels, nul ne défie les fils de la flamme vivante !' WHERE entry = -1409003;
UPDATE `script_texts` SET `content_loc2` = 'Les runes de gardes ont été détruites ! Traquez les infidèles mes frères.' WHERE entry = -1409004;
UPDATE `script_texts` SET `content_loc2` = 'Des cendres aux cendres !' WHERE entry = -1409005;
UPDATE `script_texts` SET `content_loc2` = 'Brûlez mortels, brûlez pour ce sacrilège !' WHERE entry = -1409006;
UPDATE `script_texts` SET `content_loc2` = 'Impossible ! Retenez vos coups mortels ! Je me rends ! Je me rends ! Vous êtes venu vous emparer des secrets de la flamme vivante... Vous regretterez bientôt votre témérité. Je vais aller invoquer le seigneur de ces lieux. Si vous désirez obtenir audience, sachez que vos misérables vies seront certainement anéanties. Mais partez à sa recherche ! Si vous l\'osez...' WHERE entry = -1409007;

DELETE FROM `creature_template` WHERE `entry` = 7;
INSERT INTO `creature_template`(`entry`, `modelid_A`, `modelid_H`, `name`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `faction_A`, `faction_H`, `AIName`) VALUES('7', '169', '169', 'Hot Coal', '73', '73', '1', '1', '35', '35', 'NullCreatureAI');
DELETE FROM `creature_scripts` WHERE `entryorguid` = 7;
INSERT INTO `creature_scripts` VALUES (7, 'Mob_Hot_Coal');

DELETE FROM `creature` WHERE `guid` = 98227;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) values('98227','7','409','1','0','0','736.712','-1176.58','-118.954','0.562596','25','0','0','1','0','0','0');

