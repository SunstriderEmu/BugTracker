INSERT INTO script_texts(`entry`,`content_default`,`content_loc2`, `sound`,`type`,`language`,`emote`,`comment`) VALUES
(-1000709,'Beware! We are attacked!','Attention ! Nous sommes attaqués !',0,0,0,0,'SAY_WP_0'),
(-1000710,'It must be the purity of the Mark of the Lightbringer that is drawing forth the Scourge to attack us. We must proceed with caution lest we be overwhelmed!','Ce doit être la pureté de la Marque du la Lumière qui incite les Mort-Vivants à nous attaquer. Nous devons être prudents, sinon nous allons être submergés !',0,0,0,0,'SAY_WP_1'),
(-1000711,'This land truly needs to be cleansed by the Light! Let us continue on to the tomb. It isn\'t far now...','Ce pays a vraiment besoin d''être purifié par la Lumière. Continuons vers la tombe, ce n''est plus très loin...',0,0,0,0,'SAY_WP_2'),
(-1000712,'Be welcome, friends!','Soyez les bienvenus, frères !',0,0,0,0,'SAY_WP_3'),
(-1000713,'Thank you for coming here in remembrance of me. Your efforts in recovering that symbol, while unnecessary, are certainly touching to an old man\'s heart.','Merci d''être venus ici en souvenir de moi. Vos efforts pour retrouver ce symbole, bien que non nécessaires, touchent beaucoup un vieil homme.',0,0,0,0,'SAY_WP_4'),
(-1000714,'Please, rise my friend. Keep the Blessing as a symbol of the strength of the Light and how heroes long gone might once again rise in each of us to inspire.','Levez-vous, mes frères. Gardez la Bénédiction comme symbole de la force de la Lumière, et comme même des héros depuis longtemps disparus peuvent revenir briller en chacun de nous.',0,0,0,0,'SAY_WP_5'),
(-1000715,'Thank you my friend for making this possible. This is a day that I shall never forget! I think I will stay a while. Please return to High Priestess MacDonnell at the camp. I know that she\'ll be keenly interested to know of what has transpired here.','Merci mon ami d''avoir rendu cela possible. C''est un jour que je n''oublierai jamais ! Je pense que je vais rester ici un moment. Retournez voir la Grande Prêtresse MacDonnell au camp. Je sais qu''elle sera très intéressée par savoir ce qu''il s''est passé ici.',0,0,0,0,'SAY_WP_6');

DELETE FROM `escort_waypoints` WHERE `entry`=17238;
INSERT INTO `escort_waypoints` VALUES
   (17238,1,953.06,-1432.52,63.2255,0,''),
   (17238,2,969.60,-1438.15,65.3669,0,''),
   (17238,3,980.07,-1441.5,65.3997,0,''),
   (17238,4,995.01,-1450.47,61.3227,0,''),
   (17238,5,1032.71,-1473.49,63.7699,0,''),
   (17238,6,1039.69,-1491.42,65.2801,0,''),
   (17238,7,1038.81,-1523.32,64.4661,0,''),
   (17238,8,1035.43,-1572.97,61.5412,0,''),
   (17238,9,1034.45,-1612.83,61.6186,0,''),
   (17238,10,1040.12,-1663.41,60.923,0,''),
   (17238,11,1059.75,-1703.75,60.5768,0,''),
   (17238,12,1091.83,-1735.24,60.8057,0,''),
   (17238,13,1131.75,-1755.32,61.0073,0,''),
   (17238,14,1159.77,-1762.64,60.5699,0,''),
   (17238,15,1153.79,-1772,60.6475,0,''),
   (17238,16,1115.41,-1787.21,61.0759,0,''),
   (17238,17,1091.88,-1799.06,61.6055,0,''),
   (17238,18,1056.22,-1805.65,71.8112,0,''),
   (17238,19,1024.03,-1807.93,77.025,0,''),
   (17238,20,1012.74,-1811.67,77.5636,0,''),
   (17238,21,1006.74,-1813.59,80.4872,0,''),
   (17238,22,983.15,-1823.05,80.4872,0,''),
   (17238,23,974.95,-1825.33,81.3482,0,'');

UPDATE `creature_template` SET `ScriptName`='npc_anchorite_truuen' WHERE `entry`=17238;
