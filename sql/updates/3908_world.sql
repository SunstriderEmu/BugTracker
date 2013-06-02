-- Kurenai Captive
UPDATE `creature_template` SET `ScriptName`='npc_kurenai_captive' WHERE `entry`=18209;
DELETE FROM `creature_template_addon` WHERE `entry`=18209;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (18209,0,0,8,0,0,''); -- Kneel
DELETE FROM `escort_waypoints` WHERE `entry`=18209;
INSERT INTO `escort_waypoints` (`entry`,`pointid`,`location_x`,`location_y`,`location_z`,`waittime`,`point_comment`) VALUES
(18209,1,-1518.593872,8469.956055,-4.101756,0,''),
(18209,2,-1511.784546,8480.531250,-4.033919,0,''),
(18209,3,-1513.447754,8509.764698,-0.109888,0,''),
(18209,4,-1498.857788,8508.805664,0.844676,0,''),
(18209,5,-1454.215088,8495.808594,4.912439,0,''),
(18209,6,-1437.483521,8504.165039,6.879123,0,''),
(18209,7,-1382.29,8539.87,11.139,7500,''),
(18209,8,-1361.22,8521.44,11.144,0,''),
(18209,9,-1324.8,8510.69,13.05,0,''),
(18209,10,-1312.08,8492.71,14.235,0,'');

DELETE FROM `script_texts` WHERE `entry` BETWEEN -1000764 AND -1000758;
INSERT INTO `script_texts` (entry, content_default, content_loc2, comment) VALUES
(-1000758,"Look out!","Nous sommes encerclés !","SAY_KUR_START"),
(-1000759,"Don't let them escape! Kill the strong one first!","C'est une embuscade ! Défendez-vous !","SAY_KUR_NO_ESCAPE"),
(-1000760,"More of them are coming! Watch out!","Nous devons partir avant d'en alerter d'autres.","SAY_KUR_MORE"),
(-1000761,"Where do you think you're going? Kill them all!","Où pensez-vous aller comme ça ? Tuez les tous !","SAY_KUR_MORE_TWO"),
(-1000762,"Ride the lightning, filth!","Prends ça !","SAY_KUR_LIGHTNING"),
(-1000763,"FROST SHOCK!","HORION DE GIVRE !","SAY_KUR_SHOCK"),
(-1000764,"Up ahead is the road to Telaar. We will split up when we reach the fork as they will surely send more Murkblood after us. Hopefully one of us makes it back to Telaar alive.","Devant nous se trouve la route de Telaar. Nous nous séparerons à l'embranchement, car ils enverront sûrement d'autres Bourbesang à nos trousses. Espérons que l'un d'entre nous arrivera à Telaar vivant.","SAY_KUR_COMPLETE");
