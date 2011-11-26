DELETE FROM gameobject_template WHERE entry = 187236;
INSERT INTO gameobject_template VALUES (187236, 2, 5254, 'Winter Veil Gift', 'Opening', 0, 0, 1, 43, 8417, 0, 6798, 0, 0, 21400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '');

INSERT INTO gameobject_questrelation VALUES
(180746, 8767),
(187236, 11528);

INSERT INTO gameobject_involvedrelation VALUES
(180746, 8767),
(187236, 11528);

INSERT INTO locales_gameobject (entry, name_loc2, castbarcaption_loc2) VALUES (187236, 'Cadeau du Voile d''hiver', 'Ouverture');

UPDATE quest_template SET minlevel = 0 WHERE entry = 8744;
UPDATE quest_template SET minlevel = 0 WHERE entry = 8767;
UPDATE quest_template SET minlevel = 20 WHERE entry = 8768;
UPDATE quest_template SET minlevel = 10 WHERE entry = 11528;

UPDATE game_event SET start_time = FROM_UNIXTIME(1324767660) WHERE entry = 57;

UPDATE quest_template SET details = "The tag on this present reads:$B$BTo $N,$B$BMay your feast of Great-Winter be merry and bright!" WHERE entry = 8744;
UPDATE quest_template SET details = "This present looks like it has been shaken a few times. The tag on it reads:$B$BTp a very special $R $C." WHERE entry = 8767;
UPDATE quest_template SET details = "This festively-wrapped present has your name on it.$B$BWait, did it just move?" WHERE entry = 8768;
UPDATE quest_template SET details = "Have a joyous Feast of Great-Winter from your friends at Smokeywood Pastures." WHERE entry = 8769;
UPDATE quest_template SET details = "The note on this present reads:$B$BTo $N,$B$BIn hoping this will help you spread warm tidings and holiday cheer to all of Azeroth.$B$BFrom Greatfather Winter" WHERE entry = 8803;
UPDATE quest_template SET details = "" WHERE entry = 11528;

UPDATE locales_quest SET details_loc2 = "Une petite carte sur ce cadeau dit :$B$BPour $N$B$BPuissiez-vous passer une joyeuse fête de Grand-Hiver !" WHERE entry = 8744;
UPDATE locales_quest SET details_loc2 = "Ce cadeau donne l'impression d'avoir été secoué plusieurs fois. Il porte une petite carte qui dit$B$BA $Gun:une; $R $C hors du commun." WHERE entry = 8767;
UPDATE locales_quest SET details_loc2 = "Ce cadeau à l'emballage multicolore porte votre nom !" WHERE entry = 8768;
UPDATE locales_quest SET details_loc2 = "Encore un pour vous !" WHERE entry = 8769;
UPDATE locales_quest SET details_loc2 = "La petite note placée sur le cadeau dit :$B$BPour $N,$B$BEn espérant que cela vous aidera à propager l’ambiance de fête et de bonnes nouvelles sur tout Azeroth.$B$BDe la part de Grandpère Hiver." WHERE entry = 8803;

UPDATE locales_quest SET OfferRewardText_loc2 = Details_loc2 WHERE entry IN (8744, 8767, 8768, 8769, 8803, 11528);
UPDATE quest_template SET OfferRewardText = Details WHERE entry IN (8744, 8767, 8768, 8769, 8803, 11528);

DELETE FROM gameobject WHERE id IN (180743, 180746, 180747, 180748, 180793, 187236);
INSERT INTO `gameobject` VALUES
('',180746,1,1,1622.39,-4415.57,14.491,1.03592,0,0,0.49511,0.86883,25,0,1),
('',180743,1,1,1623.54,-4416.09,14.7388,1.16994,0,0,0.552175,0.833728,25,0,1),
('',180747,1,1,1622.02,-4411.18,14.419,5.63312,0,0,0.319339,-0.947641,25,0,1),
('',180748,1,1,1625.59,-4409.86,15.0568,4.54927,0,0,0.762363,-0.64715,25,0,1),
('',180793,1,1,1627.59,-4410.55,15.5525,3.76649,0,0,0.951584,-0.30739,25,0,1),
('',180743,0,1,-4915.46,-979.716,501.447,4.90402,0,0,0.636217,-0.77151,25,0,1),
('',180746,0,1,-4915.58,-981.07,501.878,4.90402,0,0,0.636217,-0.77151,25,0,1),
('',180747,0,1,-4918.65,-980.301,501.454,4.7886,0,0,0.679654,-0.733533,25,0,1),
('',180748,0,1,-4921.09,-981.512,501.463,4.47248,0,0,0.786644,-0.617407,25,0,1),
('',180793,0,1,-4917.07,-980.795,501.724,4.50259,0,0,0.777259,-0.62918,25,0,1),
('',187236,0,1,-4916.98,-979.635,501.451,5.0144,0,0,0.592687,-0.805433,25,0,1),
('',187236,1,1,1628.5,-4413.21,15.7856,3.00617,0,0,0.997708,0.067662,25,0,1);
