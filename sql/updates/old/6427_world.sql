#Seigneur de guerre Kalithresh :
REPLACE INTO creature_equip_template VALUES (91487,22031,0,0,1538,0,0,17,0,0);
UPDATE creature_template SET equipment_id = 91487 WHERE entry IN (17798, 20633);

#Guerrier de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91488,20029,18702,0,33490690,33490436,0,781,1038,0);
UPDATE creature_template SET equipment_id = 91488 WHERE entry IN (17802,20626);

#Ingénieur de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91489,8568,0,0,1026,0,0,21,0,0);
UPDATE creature_template SET equipment_id = 91489 WHERE entry IN (17721, 20620);

#Sirène de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91490,10654,0,0,772,0,0,10,0,0);
UPDATE creature_template SET equipment_id = 91490 WHERE entry IN (17801, 20623);

#Oracle de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91491,22241,0,0,1538,0,0,17,0,0);
UPDATE creature_template SET equipment_id = 91491 WHERE entry IN (17803, 20622);

#Maître d'esclaves de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91492,22241,0,0,1538,0,0,17,0,0);
UPDATE creature_template SET equipment_id = 91492 WHERE entry IN (17805, 20624);

#Myrmidon de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91493,33835,0,0,258,0,0,13,0,0);
UPDATE creature_template SET equipment_id = 91493 WHERE entry IN (17800, 20621);

#Esclave crapuche :
REPLACE INTO creature_equip_template VALUES (91494,19234,0,0,258,0,0,21,0,0);
UPDATE creature_template SET equipment_id = 91494 WHERE entry IN (17799, 20628);

#Sorcière de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91495,20412,0,0,772,0,0,10,0,0);
UPDATE creature_template SET equipment_id = 91495 WHERE entry IN (17722, 20625);

#Lépreux et Mécaniciens:
REPLACE INTO `creature_equip_template` VALUES (91579,7494,0,6607,3586,0,770,21,0,26);
UPDATE `creature_template` SET `equipment_id`="91579" WHERE entry IN (17951, 20632, 21338, 21915); 

UPDATE `creature_template` SET `speed` = '1' WHERE entry IN(21696, 21916, 21695, 21917); 

#Mennu le traitre :
REPLACE INTO creature_equip_template VALUES (91475,32780,0,0,1026,0,0,21,0,0);
UPDATE creature_template SET equipment_id = 91475 WHERE entry IN (17941,19893);

#Conducteur d'esclave glissecroc :
REPLACE INTO creature_equip_template VALUES (91476,8747,0,0,1538,0,0,17,0,0);
UPDATE creature_template SET equipment_id = 91476 WHERE entry IN (17959,19889);

#Ouvrier marchefriche :
REPLACE INTO creature_equip_template VALUES (91477,19234,0,0,258,0,0,21,0,0);
UPDATE creature_template SET equipment_id = 91477 WHERE entry IN (17964,19904);

#Esclave marchefriche :
REPLACE INTO creature_equip_template VALUES (91478,19234,0,0,258,0,0,21,0,0);
UPDATE creature_template SET equipment_id = 91478 WHERE entry IN (17963,19902);

#Champion de glissecroc :
REPLACE INTO creature_equip_template VALUES (91479,31174,0,0,1538,0,0,17,0,0);
UPDATE creature_template SET equipment_id = 91479 WHERE entry IN (17957,19885);

#Défenseur de glissecroc :
REPLACE INTO creature_equip_template VALUES (91480,39474,18749,0,33490690,33490436,0,781,1038,0);
UPDATE creature_template SET equipment_id = 91480 WHERE entry IN (17958,19886);

#Soigne-écaille de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91481,10654,0,0,772,0,0,10,0,0);
UPDATE creature_template SET equipment_id = 91481 WHERE entry IN (21126,21842);

#Observateur de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91482,31613,0,0,1538,0,0,17,0,0);
UPDATE creature_template SET equipment_id = 91482 WHERE entry IN (17938,19888);

#Technicien de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91483,7494,0,0,3586,0,0,21,0,0);
UPDATE creature_template SET equipment_id = 91483 WHERE entry IN (17940,19891);

#Collaborateur de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91484,23909,0,0,2,0,0,13,0,0);
UPDATE creature_template SET equipment_id = 91484 WHERE entry IN (17962,19903);

#Enchanteresse de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91485,18368,0,0,772,0,0,10,0,0);
UPDATE creature_template SET equipment_id = 91485 WHERE entry IN (17961,19887);

#Devineresse de Glissecroc :
REPLACE INTO creature_equip_template VALUES (91486,20434,0,0,772,0,0,10,0,0);
UPDATE creature_template SET equipment_id = 91486 WHERE entry IN (17960,19890);

UPDATE `creature_template` SET `unit_flags` = '33554432' WHERE `creature_template`.`entry` = 18206;
UPDATE `creature_template` SET `unit_flags` = '33554432 ' WHERE `creature_template`.`entry` = 19901;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('18206', '0', '0', 'You over there! Help me find a way out of this wretched cage!', 'Vous là-bas ! Aidez-moi à sortir de cette maudite cage !', '0', '0', '100', '0', '0', '0', 'Captif Marchefriche');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('18206', '0', '1', 'Help me! Please help me!', 'Aidez-moi ! Aidez-moi, par pitié !', '0', '0', '100', '0', '0', '0', 'Captif Marchefriche');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('18206', '0', '2', 'Will the pain ever end?', 'La souffrance connaîtra-t-elle jamais une fin ?', '0', '0', '100', '0', '0', '0', 'Captif Marchefriche');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('18206', '0', '3', 'How can you just leave me here?', 'Comment pouvez-vous me laisser ici ?', '0', '0', '100', '0', '0', '0', 'Captif Marchefriche');

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17959', '0', '0', 'Get back to work you!', 'Vous, retournez au travail !', '1', '0', '100', '0', '0', '0', 'Conducteur esclaves de Glissecroc - Enclos');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17959', '0', '1', 'Wake up! Now get up and back to work!', 'Debout ! On se lève et on retourne au travail !', '1', '0', '100', '0', '0', '0', 'Conducteur esclaves de Glissecroc - Enclos');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17959', '0', '2', 'Too soon! You are slacking off too soon!', 'C\'est trop tôt ! Vous commencez à traînasser trop tôt !', '1', '0', '100', '0', '0', '0', 'Conducteur esclaves de Glissecroc - Enclos');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17959', '0', '3', 'This is terrible..... my armes grow tired from beating on you lazy peons!', 'C\'est terrible... À force de vous cogner dessus, bande de péons flemmards, j\'en ai mal aux bras !', '1', '0', '100', '0', '0', '0', 'Conducteur esclaves de Glissecroc - Enclos');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17959', '0', '4', 'Hurry up with it already! The longer you take, the more of a hurtin\' I\'m putting on you!', 'Allez, on se grouille ! Plus vous mettrez longtemps, plus je vous ferai mal !', '1', '0', '100', '0', '0', '0', 'Conducteur esclaves de Glissecroc - Enclos');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17959', '0', '5', 'What is this?! Didn\'t mommy and daddy teach you anything?!', 'Hé ben alors ? Papa et môman ne t\'ont rien appris ?', '1', '0', '100', '0', '0', '0', 'Conducteur esclaves de Glissecroc - Enclos');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17959', '1', '0', 'Assist me slaves!', 'Esclaves, aidez-moi !', '1', '0', '100', '0', '0', '0', 'Conducteur esclaves de Glissecroc - Aggro');

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17964', '0', '0', 'Will the pain ever end?', 'La souffrance connaîtra-t-elle jamais une fin ?', '1', '0', '100', '0', '0', '0', 'Ouvrier Marchefriche - Giflé');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17964', '1', '0', 'I spit on the corpse of these filthy naga.', 'Je crache sur les corps de ces abjects nagas.', '1', '0', '100', '0', '0', '0', 'Ouvrier Marchefriche - Libre');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17964', '1', '1', 'Thank you!', 'Merci !', '1', '0', '100', '0', '0', '0', 'Ouvrier Marchefriche - Libre');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17964', '1', '2', 'The pain is finally over.', 'La douleur s\'estompe enfin.', '1', '0', '100', '0', '0', '0', 'Ouvrier Marchefriche - Libre');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17964', '1', '3', 'We have waited forever for this day to come!', 'Nous attendions ce moment depuis toujours !', '1', '0', '100', '0', '0', '0', 'Ouvrier Marchefriche - Libre');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17964', '1', '4', 'Free at last!', 'La liberté, enfin !', '1', '0', '100', '0', '0', '0', 'Ouvrier Marchefriche - Libre');
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text_en`, `text_fr`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES ('17964', '1', '5', 'How can we ever repay you for this?', 'Comment pourrons-nous jamais vous remercier ?', '1', '0', '100', '0', '0', '0', 'Ouvrier Marchefriche - Libre');

#Patrouilleur forge-tempête :
UPDATE creature_template SET minhealth = '34480', maxhealth = '34480' WHERE entry = 19166;
UPDATE creature_template SET minhealth = '48472', maxhealth = '48472' WHERE entry = 21543;

#Destructeur forge-tempête :
UPDATE creature_template SET minhealth = '82752', maxhealth = '82752' WHERE entry = 19735;
UPDATE creature_template SET minhealth = '116000', maxhealth = '116000' WHERE entry = 21542;

#Centurion garde-sang :
UPDATE creature_template SET minhealth = '20424', maxhealth = '20424' WHERE entry = 19510;
UPDATE creature_template SET minhealth = '32314', maxhealth = '32314' WHERE entry = 21522;

#Médecin garde-sang :
UPDATE creature_template SET minhealth = '20160', maxhealth = '20160', minmana= '14665', maxmana = '14665' WHERE entry = 20990;
UPDATE creature_template SET minhealth = '24251', maxhealth = '24251', minmana= '15775', maxmana = '15775' WHERE entry = 21523;

#Astromage cherche-soleil :
UPDATE creature_template SET minhealth = '26880', maxhealth = '26880', minmana= '2933', maxmana = '2933' WHERE entry = 19168;
UPDATE creature_template SET minhealth = '37724', maxhealth = '37724', minmana= '3155', maxmana = '3155' WHERE entry = 21539;

#Ingénieur cherche-soleil :
UPDATE creature_template SET minhealth = '20160', maxhealth = '20160', minmana= '2933', maxmana = '2933' WHERE entry = 20988;
UPDATE creature_template SET minhealth = '28293', maxhealth = '28293', minmana= '3155', maxmana = '3155' WHERE entry = 21540;

#Pourfendeur garde-sang :
UPDATE creature_template SET minhealth = '20424', maxhealth = '20424' WHERE entry = 19167;
UPDATE creature_template SET minhealth = '28293', maxhealth = '28293' WHERE entry = 21524;

#Gardien de porte Gyro-Meurtre :
UPDATE creature_template SET minhealth = '132000', maxhealth = '132000' WHERE entry = 19218;
UPDATE creature_template SET minhealth = '184000', maxhealth = '184000' WHERE entry = 21525;

#Casseur du Méchanar :
UPDATE creature_template SET minhealth = '20424', maxhealth = '20424' WHERE entry = 19713;
UPDATE creature_template SET minhealth = '28293', maxhealth = '28293' WHERE entry = 21532;

#Perforateur du Méchanar :
UPDATE creature_template SET minhealth = '20424', maxhealth = '20424' WHERE entry = 19716;
UPDATE creature_template SET minhealth = '28293', maxhealth = '28293' WHERE entry = 21531;

#Bricoleur du Méchanar :
UPDATE creature_template SET minhealth = '10080', maxhealth = '10080' WHERE entry = 19716;
UPDATE creature_template SET minhealth = '14147', maxhealth = '14147' WHERE entry = 21531;

#Mécanoseigneur Capacitus :
UPDATE creature_template SET minhealth = '174000', maxhealth = '174000' WHERE entry = 19219;
UPDATE creature_template SET minhealth = '309000', maxhealth = '309000' WHERE entry = 21533;

#Néantomancienne Sepethrea :
UPDATE creature_template SET minhealth = '174000', maxhealth = '174000', minmana= '31550', maxmana = '31550' WHERE entry = 19221;
UPDATE creature_template SET minhealth = '250000', maxhealth = '250000', minmana= '33090', maxmana = '33090' WHERE entry = 21536;

#Flammes violentes :
UPDATE creature_template SET minhealth = '115000', maxhealth = '115000' WHERE entry = 20481;
UPDATE creature_template SET minhealth = '164000', maxhealth = '164000' WHERE entry = 21538;

#Pathaleon le Calculateur :
UPDATE creature_template SET minhealth = '157000', maxhealth = '157000', minmana= '31550', maxmana = '31550' WHERE entry = 19220;
UPDATE creature_template SET minhealth = '250000', maxhealth = '250000', minmana= '33090', maxmana = '33090' WHERE entry = 21537;

#Ame en peine du Néant :
UPDATE creature_template SET minhealth = '10470', maxhealth = '10470', minmana= '3155', maxmana = '3155' WHERE entry = 21062;
UPDATE creature_template SET minhealth = '14945', maxhealth = '14945', minmana= '3309', maxmana = '3309' WHERE entry = 21535;

#Garde sethekk :
REPLACE INTO `creature_equip_template` VALUES (91558,22402,0,0,2050,0,0,17,0,0);
UPDATE `creature_template` SET `equipment_id`="91558" WHERE `entry`=18323;

#Initié sethekk :
REPLACE INTO `creature_equip_template` VALUES (91559,31308,18696,0,33490690,1540,0,781,14,0);
UPDATE `creature_template` SET `equipment_id`="91559" WHERE `entry`=18318;

#Contrôleur perdu dans le temps :
REPLACE INTO `creature_equip_template` VALUES (91560,20444,0,0,772,0,0,10,0,0);
UPDATE `creature_template` SET `equipment_id`="91560" WHERE `entry`=18327;

#Oracle sethekk :
REPLACE INTO `creature_equip_template` VALUES (91561,27575,0,0,4866,0,0,26,0,0);
UPDATE `creature_template` SET `equipment_id`="91561" WHERE `entry`=18328;

#Garde-corbeau sethekk :
REPLACE INTO `creature_equip_template` VALUES (91562,7965,7965,0,2,2,0,13,22,0);
UPDATE `creature_template` SET `equipment_id`="91562" WHERE `entry`=18322;

#Chaman sethekk :
REPLACE INTO `creature_equip_template` VALUES (91563,18572,1648,0,1026,772,0,21,10,0);
UPDATE `creature_template` SET `equipment_id`="91563" WHERE `entry`=18326;

#Prophète sethekk :
REPLACE INTO `creature_equip_template` VALUES (91564,30875,0,0,4,0,0,23,0,0);
UPDATE `creature_template` SET `equipment_id`="91564" WHERE `entry`=18325;

#Seigneur-serres sethekk :
REPLACE INTO `creature_equip_template` VALUES (91565,4800,23976,0,33490690,1540,0,781,14,0);
UPDATE `creature_template` SET `equipment_id`="91565" WHERE `entry`=18321;

#Clairvoyant perdu dans le temps :
REPLACE INTO `creature_equip_template` VALUES (91566,6452,0,0,260,0,0,16,0,0);
UPDATE `creature_template` SET `equipment_id`="91566" WHERE `entry`=18319;

#Ikiss :
REPLACE INTO `creature_equip_template` VALUES (91567,31764,0,0,772,0,0,10,0,0);
UPDATE `creature_template` SET `equipment_id`="91567" WHERE `entry`=18473; 

#Avatar des martyrs:
REPLACE INTO `creature_equip_template` VALUES (91578,20195,0,0,2050,0,0,17,0,0);
UPDATE `creature_template` SET `equipment_id`="91578" WHERE entry IN (18478, 20303);

#Exarque Maladaar :
REPLACE INTO `creature_equip_template` VALUES (91577,36371,0,0,33490690,0,0,781,0,0);
UPDATE `creature_template` SET `equipment_id`="91577" WHERE entry IN (18373, 20306);

#Nécromancien auchenaï :
REPLACE INTO `creature_equip_template` VALUES (91576,35563,0,0,772,0,0,10,0,0);
UPDATE `creature_template` SET `equipment_id`="91576" WHERE entry IN (18702, 20300);

#Squelette colérique :
REPLACE INTO `creature_equip_template` VALUES (91575,36631,0,0,1026,0,0,21,0,0);
UPDATE `creature_template` SET `equipment_id`="91575" WHERE entry IN (18524, 20298);

#Squelette déchaîné :
REPLACE INTO `creature_equip_template` VALUES (91574,13078,0,0,33490690,0,0,781,0,0);
UPDATE `creature_template` SET `equipment_id`="91574" WHERE entry IN (18521, 20315);

#Soldat éclipsant :
REPLACE INTO `creature_equip_template` VALUES (91573,13078,40781,0,33490690,1540,0,781,14,0);
UPDATE `creature_template` SET `equipment_id`="91573" WHERE entry IN (18556, 20311);

#Clerc non-vivant :
REPLACE INTO `creature_equip_template` VALUES (91572,20384,0,0,772,0,0,10,0,0);
UPDATE `creature_template` SET `equipment_id`="91572" WHERE entry IN (18500);

#Traqueur éclipsant :
REPLACE INTO `creature_equip_template` VALUES (91571,20333,0,0,260,0,0,16,0,0);
UPDATE `creature_template` SET `equipment_id`="91571" WHERE entry IN (18559, 20313);

#Moine auchenaï :
REPLACE INTO `creature_equip_template` VALUES (91570,28836,0,0,772,0,0,10,0,0);
UPDATE `creature_template` SET `equipment_id`="91570" WHERE entry IN (18497, 20299);

#Redresseur de torts auchenaï :
REPLACE INTO `creature_equip_template` VALUES (91569,7438,0,0,1026,0,0,21,0,0);
UPDATE `creature_template` SET `equipment_id`="91569" WHERE entry IN (18495, 20302);

#Prêtre de l'âme auchenaï :
REPLACE INTO `creature_equip_template` VALUES (91568,20275,0,0,772,0,0,10,0,0);
UPDATE `creature_template` SET `equipment_id`="91568" WHERE entry IN (18493, 20301); 

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