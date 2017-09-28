DELETE FROM creature_scripts WHERE entryorguid = 15341;
INSERT INTO creature_scripts VALUES (15341, 'rajaxx');

DELETE FROM creature_text WHERE entry = 15341;
INSERT INTO `creature_text` VALUES (15341,0,0,'Impudent fool! I will kill you myself!','Imbécile imprudent ! Je vais te tuer moi-même !',1,0,100,0,0,0,'rajaxx aggro'),(15341,1,0,'I have no time to spend with you, $N !','je n\'ai pas de temps à perdre avec toi, $N !',1,0,100,0,0,0,'rajaxx change target'),(15341,2,0,'Warriors! Captains! Continue the fight!','Guerriers, capitaines, continuez le combat !',1,0,100,0,0,0,'rajaxx death');
