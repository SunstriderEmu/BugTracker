DELETE FROM `escort_waypoints` WHERE `entry`=2917;
INSERT INTO `escort_waypoints` VALUES
(2917,0,4675.812500,598.614563,17.645658,0, 'SAY_REM_START'),
(2917,1,4672.844238,599.325378,16.417622,0, ''),
(2917,2,4663.449707,607.430176,10.494752,0, ''),
(2917,3,4655.969238,613.761353,8.523270,0, ''),
(2917,4,4640.804688,623.999329,8.377054,0, ''),
(2917,5,4631.678711,630.801086,6.414999,5000, 'SAY_REM_RAMP1_1'),
(2917,6,4633.533203,632.476440,6.509831,0, 'ambush'),
(2917,7,4639.413574,637.120789,13.338119,0, ''),
(2917,8,4642.352051,637.668152,13.437444,0, ''),
(2917,9,4645.082031,634.463989,13.437208,5000, 'SAY_REM_RAMP1_2'),
(2917,10,4642.345215,637.584839,13.435211,0, ''),
(2917,11,4639.630859,637.233765,13.339752,0, ''),
(2917,12,4633.363281,632.462280,6.488438,0, ''),
(2917,13,4624.714844,631.723511,6.264030,0, ''),
(2917,14,4623.525879,629.718506,6.201339,5000, 'SAY_REM_BOOK'),
(2917,15,4623.452148,630.369629,6.218942,0, 'SAY_REM_TENT1_1'),
(2917,16,4622.622070,637.221558,6.312845,0, 'ambush'),
(2917,17,4619.755371,637.386230,6.312050,5000, 'SAY_REM_TENT1_2'),
(2917,18,4620.027832,637.367676,6.312050,0, ''),
(2917,19,4624.154785,637.560303,6.313898,0, ''),
(2917,20,4622.967773,634.016479,6.294979,0, ''),
(2917,21,4616.926758,630.303284,6.239193,0, ''),
(2917,22,4614.546387,616.983337,5.687642,0, ''),
(2917,23,4610.279297,610.029419,5.442539,0, ''),
(2917,24,4601.149902,604.111694,2.054856,0, ''),
(2917,25,4589.618164,597.685730,1.057147,0, ''),
(2917,26,4577.588379,592.145813,1.120190,0, 'SAY_REM_MOSS (?)'),
(2917,27,4569.848145,592.177490,1.260874,5000, 'EMOTE_REM_MOSS (?)'),
(2917,28,4568.791992,590.870911,1.211338,3000, 'SAY_REM_MOSS_PROGRESS (?)'),
(2917,29,4566.722656,564.077881,1.343084,0, 'ambush'),
(2917,30,4568.269531,551.958435,5.004200,0, ''),
(2917,31,4566.731934,551.557861,5.426314,5000, 'SAY_REM_PROGRESS'),
(2917,32,4566.741699,560.767639,1.703257,0, ''),
(2917,33,4573.916016,582.566101,0.749801,0, ''),
(2917,34,4594.206055,598.533020,1.034056,0, ''),
(2917,35,4601.194824,604.283081,2.060146,0, ''),
(2917,36,4609.539551,610.844727,5.402220,0, ''),
(2917,37,4624.800293,618.076477,5.851541,0, ''),
(2917,38,4632.414063,623.778442,7.286243,0, ''),
(2917,39,4645.915039,621.983765,8.579967,0, ''),
(2917,40,4658.669922,611.092651,8.891747,0, ''),
(2917,41,4671.924316,599.752197,16.01242,5000, 'SAY_REM_REMEMBER'),
(2917,42,4676.976074,600.649780,17.82566,5000, 'EMOTE_REM_END');

UPDATE `creature_template` SET `ScriptName` = 'npc_prospector_remtravel' WHERE `entry` = '2917';
UPDATE `quest_template` SET `SpecialFlags` = '2' WHERE `entry` = '731';
UPDATE `quest_template` SET `SpecialFlags` = '2' WHERE `entry` = '5321';
DELETE FROM `script_texts` WHERE `entry` BETWEEN '-1600444' AND '-1600413';
INSERT INTO `script_texts` VALUES ('-1600444', 'Oh, I can see Liladris from here... Tell her I\'m here, won\'t you?', null, 'Oh, je peux voir Liladris d''ici... Dites-lui que je suis ici, voulez-vous ?', null, null, null, null, null, null, '0', '0', '0', '0', 'kerlonian SAY_KER_END');
INSERT INTO `script_texts` VALUES ('-1600440', 'Oh, I am so tired...', null, 'Oh, je suis si fatigué...', null, null, null, null, null, null, '0', '0', '0', '0', 'kerlonian SAY_KER_SLEEP_3');
INSERT INTO `script_texts` VALUES ('-1600441', 'You don\'t mind if I stop here for a moment, do you?', null, 'Ca ne vous ennuie pas si je m''arrête un moment, n''est-ce pas ?', null, null, null, null, null, null, '0', '0', '0', '0', 'kerlonian SAY_KER_SLEEP_4');
INSERT INTO `script_texts` VALUES ('-1600442', 'Be on the alert! The Blackwood furbolgs are numerous in the area...', null, 'Soyez prudents, les furbolgs sont nombreux dans cette zone...', null, null, null, null, null, null, '0', '0', '0', '0', 'kerlonian SAY_KER_ALERT_1');
INSERT INTO `script_texts` VALUES ('-1600443', 'It\'s quiet... Too quiet...', null, 'C''est calme... Trop calme.', null, null, null, null, null, null, '0', '0', '0', '0', 'kerlonian SAY_KER_ALERT_2');
INSERT INTO `script_texts` VALUES ('-1600439', 'Yaaaaawwwwwnnnn...', null, 'Yaaaaaaawwwwwwnnnnn', null, null, null, null, null, null, '0', '0', '0', '0', 'kerlonian SAY_KER_SLEEP_2');
INSERT INTO `script_texts` VALUES ('-1600438', 'This looks like the perfect place for a nap...', null, 'Ca a l''air parfait pour une sieste...', null, null, null, null, null, null, '0', '0', '0', '0', 'kerlonian SAY_KER_SLEEP_1');
INSERT INTO `script_texts` VALUES ('-1600437', '%s begins to drift off...', null, '%s commence à dériver...', null, null, null, null, null, null, '0', '2', '0', '0', 'kerlonian EMOTE_KER_SLEEP_3');
INSERT INTO `script_texts` VALUES ('-1600435', '%s looks very sleepy...', null, '%s a l''air très endormi...', null, null, null, null, null, null, '0', '2', '0', '0', 'kerlonian EMOTE_KER_SLEEP_1');
INSERT INTO `script_texts` VALUES ('-1600436', '%s suddenly falls asleep', null, '%s s''endort soudain', null, null, null, null, null, null, '0', '2', '0', '0', 'kerlonian EMOTE_KER_SLEEP_2');
INSERT INTO `script_texts` VALUES ('-1600434', 'Liladris has been waiting for me at Maestra\'s Post, so we should make haste, $N.', null, 'Liladris m''attend au poste de Maestra, nous devrions nous dépêcher, $N.', null, null, null, null, null, null, '0', '0', '0', '0', 'kerlonian SAY_KER_START');
INSERT INTO `script_texts` VALUES ('-1600427', 'Something tells me this $r wants the mysterious fossil too. Help!', null, 'Quelque chose me dit que ce $r veut le fossile aussi. A l''aide !', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_AGGRO');
INSERT INTO `script_texts` VALUES ('-1600426', '%s goes back to work, oblivious to everything around him.', null, '%s retourne au travail, à la recherche de quelque chose autour de lui.', null, null, null, null, null, null, '0', '2', '7', '0', 'remtravel EMOTE_REM_END');
INSERT INTO `script_texts` VALUES ('-1600425', 'Ah. I remember now! I gave the mysterious fossil to Hollee! Check with her.', null, 'Ah. Je me rappelle maintenant ! J''ai donné le mystérieux fossile à Hollee ! Vérifiez cela avec elle.', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_REMEMBER');
INSERT INTO `script_texts` VALUES ('-1600424', 'Nope. didn\'t leave the fossil back here!', null, 'Non. Je n''ai pas laissé le fossile ici !', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_PROGRESS');
INSERT INTO `script_texts` VALUES ('-1600423', 'Oh wait! I\'m supposed to be looking for that mysterious fossil!', null, 'Oh attendez ! Je suis censé chercher ce mystérieux fossile !', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_MOSS_PROGRESS');
INSERT INTO `script_texts` VALUES ('-1600422', '%s inspects the ancient, mossy stone.', null, '%s inspecte la vieille pierre.', null, null, null, null, null, null, '0', '2', '7', '0', 'remtravel EMOTE_REM_MOSS');
INSERT INTO `script_texts` VALUES ('-1600421', 'Interesting... I hadn\'t noticed this earlier...', null, 'Intéressant... Je n''avais jamais remarqué ça auparavant.', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_MOSS');
INSERT INTO `script_texts` VALUES ('-1600420', 'Oh wait, that\'s Hollee\'s tent... and it\'s empty.', null, 'Oh attendez. C''est la tente d''Hollee... et elle est vide.', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_TENT1_2');
INSERT INTO `script_texts` VALUES ('-1600419', 'I bet you I left it in the tent!', null, 'Je parie que vous l''avez laissé dans la tente !', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_TENT1_1');
INSERT INTO `script_texts` VALUES ('-1600418', 'No mysterious fossil here... Ah, but my copy of Green Hills of Stranglethorn. What a good book!', null, 'Pas de fossile ici... Ah, mais il y a ma copie des Vertes Collines de Strangleronce. Quel bon livre !', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_BOOK');
INSERT INTO `script_texts` VALUES ('-1600417', 'Hrm, nothing up here.', null, 'Mmh, rien ici.', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_RAMP1_2');
INSERT INTO `script_texts` VALUES ('-1600416', 'Now where did I put that mysterious fossil? Ah, maybe up there...', null, 'Où ai-je mis ce mystérieux fossile... Ah, peut-être ici...', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_RAMP1_1');
INSERT INTO `script_texts` VALUES ('-1600415', 'Ok, $n, let\'s go find where I left that mysterious fossil. Follow me!', null, 'Ok $n, allons chercher après ce mystérieux fossile. Suivez-moi !', null, null, null, null, null, null, '0', '0', '7', '0', 'remtravel SAY_REM_START');
INSERT INTO `script_texts` VALUES ('-1600414', 'YARRR! Swabie, what have ye done?! He\'s gone mad! Baton him down the hatches! Hoist the mast! ARRRR! Every man for hi\'self!', null, 'YARRR ! Swabie, qu''avez-vous fait ? Il est devenu fou ! Tuez le ! Chacun pour soi !', null, null, null, null, null, null, '0', '0', '7', '0', 'threshwackonator SAY_AT_CLOSE');
INSERT INTO `script_texts` VALUES ('-1600413', '\"Threshwackonator First Mate unit prepared to follow\"', null, 'Le Destructomembreur Premier Officier est prêt à vous suivre.', null, null, null, null, null, null, '0', '2', '0', '0', 'threshwackonator EMOTE_START');
