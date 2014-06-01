#Guetteur des Flammes infernales :
REPLACE INTO creature_equip_template VALUES (91504,23673,0,0,772,0,0,10,0,0);
UPDATE creature_template SET equipment_id = 91504 WHERE entry IN (17309,18058);

#Vazruden :
REPLACE INTO creature_equip_template VALUES (91505,36729,0,0,1538,0,0,17,0,0);
UPDATE creature_template SET equipment_id = 91505 WHERE entry IN (17537,18434);

#Affameur mâche-les-os :
REPLACE INTO creature_equip_template VALUES (91506,42749,18793,0,2,33490436,0,21,1038,0);
UPDATE creature_template SET equipment_id = 91506 WHERE entry IN (17259,18053);

#Vorace mâche-les-os :
REPLACE INTO creature_equip_template VALUES (91507,20122,29769,0,33490690,33490436,0,781,781,0);
UPDATE creature_template SET equipment_id = 91507 WHERE entry IN (17264,18054);

#Archer de l'Orbite-sanglante :
REPLACE INTO creature_equip_template VALUES (91508,22478,0,31748,258,0,514,13,0,15);
UPDATE creature_template SET equipment_id = 91508 WHERE entry IN (17270,18048);

#Destructeur mâche-les-os :
REPLACE INTO creature_equip_template VALUES (91509,28207,0,0,3842,0,0,13,0,0);
UPDATE creature_template SET equipment_id = 91509 WHERE entry IN (17271,17043);

#Invocateur noir de l'Orbite-sanglante :
REPLACE INTO creature_equip_template VALUES (91510,35563,0,0,722,0,0,10,0,0);
UPDATE creature_template SET equipment_id = 91510 WHERE entry IN (17269,18049);

#Clairvoyant de l'Orbite-sanglante :
REPLACE INTO creature_equip_template VALUES (91511,43817,0,0,722,0,0,10,0,0);
UPDATE creature_template SET equipment_id = 91511 WHERE entry IN (17478,17048);

#Eventreur mâche-les-os :
REPLACE INTO creature_equip_template VALUES (91512,15720,15720,0,3330,3330,0,21,22,0);
UPDATE creature_template SET equipment_id = 91512 WHERE entry IN (17281,18055);

#Belluaire mâche-les-os :
REPLACE INTO creature_equip_template VALUES (91513,39874,0,0,3330,0,0,21,0,0);
UPDATE creature_template SET equipment_id = 91513 WHERE entry IN (17455,18051);

#Factionnaire des Flammes infernales :
REPLACE INTO creature_equip_template VALUES (91514,8090,0,0,33490690,0,0,781,0,0);
UPDATE creature_template SET equipment_id = 91514 WHERE entry IN (17517,18057);

#Affâmeur mâche-les-os :
UPDATE creature_template SET minhealth = '27350', maxhealth = '28114' WHERE entry = 18053;
UPDATE creature_template SET minhealth = '17702', maxhealth = '17957' WHERE entry = 17259;

#Vorace :
UPDATE creature_template SET minhealth = '23750', maxhealth = '28114' WHERE entry = 18054;
UPDATE creature_template SET minhealth = '17702', maxhealth = '17702' WHERE entry = 17264;

#Invocateur noir :
UPDATE creature_template SET minhealth = '27350', maxhealth = '28114', minmana = '7196', maxmana = '7332' WHERE entry = 18049;
UPDATE creature_template SET minhealth = '14161', maxhealth = '14367', minlevel = '60', maxlevel = '61', minmana = '5751', maxmana = '5875' WHERE entry = 17269;

#Destructeur :
UPDATE creature_template SET minhealth = '27350', maxhealth = '28114' WHERE entry = 17043;
UPDATE creature_template SET minhealth = '17702', maxhealth = '17957', minlevel = '60', maxlevel = '61' WHERE entry = 17271;

#Chien :
UPDATE creature_template SET minhealth = '9310', maxhealth = '9310', minlevel = '69', maxlevel = '69' WHERE entry = 18059;
UPDATE creature_template SET minhealth = '5922', maxhealth = '5922', minlevel = '59', maxlevel = '59' WHERE entry = 17280;

#Clairvoyant :
UPDATE creature_template SET minhealth = '17465', maxhealth = '17952', minlevel = '70', maxlevel = '71', minmana = '7196', maxmana = '7332' WHERE entry = 17048;
UPDATE creature_template SET minhealth = '14161', maxhealth = '14367', minlevel = '60', maxlevel = '61', minmana = '5751', maxmana = '5875' WHERE entry = 17478;

#Archer :
UPDATE creature_template SET minhealth = '27350', maxhealth = '28114', minlevel = '70', maxlevel = '71', minmana = '3155', maxmana = '3231' WHERE entry = 18048;
UPDATE creature_template SET minhealth = '17702', maxhealth = '17957', minlevel = '60', maxlevel = '61', minmana = '2434', maxmana = '2486' WHERE entry = 17270;

#Eventreur :
UPDATE creature_template SET minhealth = '57448', maxhealth = '57448', minlevel = '70', maxlevel = '71' WHERE entry = 18055;
UPDATE creature_template SET minhealth = '19814', maxhealth = '19814' WHERE entry = 17281;

#Belluaire :
UPDATE creature_template SET minhealth = '27944', maxhealth = '27944', minlevel = '70', maxlevel = '71' WHERE entry = 18051;
UPDATE creature_template SET minhealth = '17702', maxhealth = '17702' WHERE entry = 17455;

#Boss 1 :
UPDATE creature_template SET minhealth = '103320', maxhealth = '103320' WHERE entry = 18436;
UPDATE creature_template SET minhealth = '59660', maxhealth = '59660' WHERE entry = 17306;

#Boss 1 Adds:
UPDATE creature_template SET minhealth = '26068', maxhealth = '26068', minmana = '7031', maxmana = '7031' WHERE entry = 18058;
UPDATE creature_template SET minhealth = '16583', maxhealth = '16583', minmana = '5598', maxmana = '5598' WHERE entry = 17309;

#Boss 2:
UPDATE creature_template SET minhealth = '103320', maxhealth = '103320', minmana = '16545', maxmana = '16545' WHERE entry = 18433;
UPDATE creature_template SET minhealth = '131880', maxhealth = '131880', minmana = '12840', maxmana = '12840' WHERE entry = 17308;

#Boss 2 Add:
UPDATE creature_template SET minhealth = '11876', maxhealth = '11876', minmana = '3155', maxmana = '3155' , minlevel = '70', maxlevel = '70' WHERE entry = 18056;
UPDATE creature_template SET minhealth = '3357', maxhealth = '3357', minmana = '2434', maxmana = '2434' , minlevel = '60', maxlevel = '60' WHERE entry = 17540;

#Factionnaire :
UPDATE creature_template SET minhealth = '33009', maxhealth = '33009' WHERE entry = 18057;
UPDATE creature_template SET minhealth = '19488', maxhealth = '20097' WHERE entry = 17517;

#Vazruden+Nazan :
UPDATE creature_template SET minhealth = '88560', maxhealth = '88650' WHERE entry = 18435;
UPDATE creature_template SET minhealth = '59660', maxhealth = '59660' WHERE entry = 17307;

#Vazruden :
UPDATE creature_template SET minhealth = '62730', maxhealth = '62730' WHERE entry = 18434;
UPDATE creature_template SET minhealth = '33912', maxhealth = '33912' WHERE entry = 17537;

#Nazan :
UPDATE creature_template SET minhealth = '88560', maxhealth = '88650' WHERE entry = 18432;
UPDATE creature_template SET minhealth = '56520', maxhealth = '56520' WHERE entry = 17536;

#Modification de la vitesse des vorace :
UPDATE creature_template SET speed = '1' WHERE entry = 17264;

#Seigneur des marais Musel'ek :
REPLACE INTO creature_equip_template VALUES (91496,8379,8379,6233,3330,3330,514,21,22,15);
UPDATE creature_template SET equipment_id = 91496 WHERE entry = 17826;

#Mirmydon Iraileron :
REPLACE INTO creature_equip_template VALUES (91477,8747,0,0,1538,0,0,17,0,0);
UPDATE creature_template SET equipment_id = 91477 WHERE entry = 17726;

#Factionnaire Iraileron :
REPLACE INTO creature_equip_template VALUES (91498,13078,18509,0,33490690,33490436,0,781,1038,0);
UPDATE creature_template SET equipment_id = 91498 WHERE entry = 17727;

#Guerrier Iraileron :
REPLACE INTO creature_equip_template VALUES (91499,20215,18662,0,33490690,33490436,0,781,1038,0);
UPDATE creature_template SET equipment_id = 91499 WHERE entry = 17735;

#Porte-épieu bourbesang :
REPLACE INTO creature_equip_template VALUES (91500,39874,21144,0,3330,3330,0,21,22,0);
UPDATE creature_template SET equipment_id = 91500 WHERE entry = 17729;

#Membre de la tribu bourbesang :
REPLACE INTO creature_equip_template VALUES (91501,8568,8568,0,1026,1026,0,21,22,0);
UPDATE creature_template SET equipment_id = 91501 WHERE entry = 17728;

#Oracle bourbesang :
REPLACE INTO creature_equip_template VALUES (91502,5404,0,0,772,0,0,10,0,0);
UPDATE creature_template SET equipment_id = 91502 WHERE entry = 17771;

#Soigneur bourbesang :
REPLACE INTO creature_equip_template VALUES (91503,28544,0,0,33490690,0,0,781,0,0);
UPDATE creature_template SET equipment_id = 91503 WHERE entry = 17730;

#Creation du NPC Fen Ray Dead 88912
REPLACE INTO `creature_template` VALUES ('88912', '0', '19405', '0', '19405', '0', 'Fen Ray Dead', NULL, NULL, '1', '1', '1', '1', '0', '0', '0', '14', '14', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '33554432', '32', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '0', '1', '0', '0', '0', '', '0');

#Emissary of Hate : Dualwield + HP
UPDATE `creature_template` SET `flags_extra` = '2097152' WHERE `creature_template`.`entry` = 25003;
UPDATE `creature_template` SET `minhealth` = '8856' WHERE `creature_template`.`entry` = 25003;
UPDATE `creature_template` SET `maxhealth` = '8856' WHERE `creature_template`.`entry` = 25003;

#Oratrice du courroux :  Dualwield + Civilian + HP
UPDATE `creature_template` SET `flags_extra` = '2097154' WHERE `creature_template`.`entry` = 24999;
UPDATE `creature_template` SET `maxhealth` = '6986' WHERE `creature_template`.`entry` = 24999;
UPDATE `creature_template` SET `minhealth` = '6986' WHERE `creature_template`.`entry` = 24999;

#Hélion déchaîné : HP
UPDATE `creature_template` SET `minhealth` = '6986' WHERE `creature_template`.`entry` = 25002;
UPDATE `creature_template` SET `maxhealth` = '7181' WHERE `creature_template`.`entry` = 25002;

#Marcheflammes abyssal : HP
UPDATE `creature_template` SET `maxhealth` = '7181' WHERE `creature_template`.`entry` = 25001;

#Guerrier du Soleil Brisé : HP
UPDATE `creature_template` SET `minhealth` = '10479' WHERE `creature_template`.`entry` = 25115;
UPDATE `creature_template` SET `maxhealth` = '10479' WHERE `creature_template`.`entry` = 25115;

#Chevalier de sang de la Lame de l'Aube : HP
UPDATE `creature_template` SET `maxhealth` = '6986' WHERE `creature_template`.`entry` = 24976;
UPDATE `creature_template` SET `minhealth` = '6986' WHERE `creature_template`.`entry` = 24976;

#Invocateur de la Lame de l'Aube : HP
UPDATE `creature_template` SET `maxhealth` = '6986' WHERE `creature_template`.`entry` = 24978;
UPDATE `creature_template` SET `minhealth` = '6986' WHERE `creature_template`.`entry` = 24978;

#Réserviste de la Lame de l'Aube : HP
UPDATE `creature_template` SET `maxhealth` = '6986' WHERE `creature_template`.`entry` = 25087;
UPDATE `creature_template` SET `minhealth` = '6986' WHERE `creature_template`.`entry` = 25087;

#Tireur d'élite de la Lame de l'Aube : HP
UPDATE `creature_template` SET `maxhealth` = '6986' WHERE `creature_template`.`entry` = 24979;
UPDATE `creature_template` SET `minhealth` = '6986' WHERE `creature_template`.`entry` = 24979;

#Mannequin d'entraînement : HP + Niveau
UPDATE `creature_template` SET `maxhealth` = '4194' WHERE `creature_template`.`entry` = 25225;
UPDATE `creature_template` SET `minhealth` = '4194' WHERE `creature_template`.`entry` = 25225;
UPDATE `creature_template` SET `minlevel` = '25' WHERE `creature_template`.`entry` = 25225;
UPDATE `creature_template` SET `maxlevel` = '25' WHERE `creature_template`.`entry` = 25225;

#Dévoreur déshérité : HP + Mana
UPDATE `creature_template` SET `maxhealth` = '6986' WHERE `creature_template`.`entry` = 24960;
UPDATE `creature_template` SET `minhealth` = '6986' WHERE `creature_template`.`entry` = 24960;
UPDATE `creature_template` SET `minmana` = '0' WHERE `creature_template`.`entry` = 24960;

#Fielleux déshérité : HP + Mana
UPDATE `creature_template` SET `maxhealth` = '6986' WHERE `creature_template`.`entry` = 24966;
UPDATE `creature_template` SET `minhealth` = '6986' WHERE `creature_template`.`entry` = 24966;
UPDATE `creature_template` SET `minmana` = '0' WHERE `creature_template`.`entry` = 24966;

#Factionnaire erratique : HP
UPDATE `creature_template` SET `maxhealth` = '6986' WHERE `creature_template`.`entry` = 24972;
UPDATE `creature_template` SET `minhealth` = '6986' WHERE `creature_template`.`entry` = 24972;

#Faucon dragon débridé : HP
UPDATE `creature_template` SET `maxhealth` = '13972' WHERE `creature_template`.`entry` = 25236;
UPDATE `creature_template` SET `minhealth` = '13972' WHERE `creature_template`.`entry` = 25236;

#Faucon dragon du Soleil Brisé : HP
UPDATE `creature_template` SET `maxhealth` = '20958' WHERE `creature_template`.`entry` = 25175;
UPDATE `creature_template` SET `minhealth` = '20958' WHERE `creature_template`.`entry` = 25175;

#Sunblade Arch Mage SAI
SET @ENTRY := 25367;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,0,0,30000,30000,11,46319,0,0,0,0,0,9,25953,0,20,0,0,0,0,"Sunblade Arch Mage - On Fel Crystal Spell Target - Cast"),
(@ENTRY,0,1,0,0,0,100,0,5000,10000,5000,10000,11,46553,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunblade Arch Mage - On Victim - Arcane Explosion"),
(@ENTRY,0,2,0,0,0,100,0,5000,10000,5000,10000,11,46573,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunblade Arch Mage - On Victim - Blink"),
(@ENTRY,0,3,0,0,0,100,0,10000,15000,10000,15000,11,46555,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunblade Arch Mage - On Victim - Frost Nova");

#Sunblade Cabalist SAI
SET @ENTRY := 25363;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,6000,6000,30000,30000,11,46319,0,0,0,0,0,9,25953,0,20,0,0,0,0,"Sunblade Cabalist - On Fel Crystal Spell Target - Cast"),
(@ENTRY,0,1,0,0,0,100,0,1000,2000,2000,2000,11,47248,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunblade Cabalist - On Victim - Shadow Bolt"),
(@ENTRY,0,2,0,0,0,100,0,5000,10000,5000,10000,11,46543,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sunblade Cabalist - On Random Hostile - Ignite mana"),
(@ENTRY,0,3,0,0,0,100,0,5000,10000,5000,10000,11,46544,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunbalde Cabalist - On Self - Summon imp");

#Sunblade Dusk Priest SAI
SET @ENTRY := 25370;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,12000,12000,30000,30000,11,46319,0,0,0,0,0,9,25953,0,20,0,0,0,0,"Sunblade Dusk Priest - On Fel Crystal Spell Target - Cast"),
(@ENTRY,0,1,0,0,0,100,0,5000,10000,5000,10000,11,46560,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sunblade Dusk Priest - On Random Hostile - Cast"),
(@ENTRY,0,2,0,0,0,100,0,10000,15000,10000,15000,11,46562,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunblade Dusk Priest - On Victim - Cast"),
(@ENTRY,0,3,0,0,0,100,0,5000,10000,5000,10000,11,46561,0,0,0,0,0,6,0,0,0,0,0,0,0,"Sunblade Dusk Priest - On Random Not Top - Cast");

#Sunblade Vindicator SAI
SET @ENTRY := 25369;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,18000,18000,30000,30000,11,46319,0,0,0,0,0,9,25953,0,20,0,0,0,0,"Sunblade Vindicator - On Fel Crystall Spell Target - Cast"),
(@ENTRY,0,1,0,0,0,100,0,5000,15000,5000,15000,11,46559,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunblade Vindicator - On Victim - Cast"),
(@ENTRY,0,2,0,0,0,100,0,5000,15000,5000,15000,11,43441,0,0,0,0,0,2,0,0,0,0,0,0,0,"Sunblade Vindicator - On Victim - Cast");

#Sunblade Dawn Priest SAI
SET @ENTRY := 25371;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,24000,24000,30000,30000,11,46319,0,0,0,0,0,9,25953,0,20,0,0,0,0,"Sunblade Dawn Priest - On Fel Crystal Spell Target - Cast"),
(@ENTRY,0,1,0,4,0,100,0,0,0,0,0,11,46565,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunblade Dawn Priest - On Self - Cast (Holy)"),
(@ENTRY,0,2,0,0,0,100,0,15000,20000,8000,12000,11,46564,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sunblade Dawn Priest - On Self - Cast (Nova)"),
(@ENTRY,0,3,0,14,0,100,0,30000,25,5000,10000,11,46563,0,0,0,0,0,26,25,0,0,0,0,0,0,"Sunblade Dawn Priest - On Friendly - Cast (Renew)");

#Irespeaker SAI
SET @ENTRY := 24999;
UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`=""  WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,25,0,100,0,0,0,0,0,11,45023,0,0,0,0,0,9,25953,0,12,0,0,0,0,"Irespeaker - On Fel Crystal Spell Target Spawn - Cast"),
(@ENTRY,0,1,0,0,0,100,0,1000,2000,3000,3000,11,35913,0,0,0,0,0,2,0,0,0,0,0,0,0,"Irespeaker - On Victim - Fel Fireball"),
(@ENTRY,0,2,0,0,0,100,0,10000,20000,30000,30000,11,18267,0,0,0,0,0,2,0,0,0,0,0,0,0,"Irespeaker - On Victim - Curse of Weakness");