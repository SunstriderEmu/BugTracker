DELETE FROM creature_template_addon WHERE entry IN (17963,17964);
update creature_template set ScriptName = "npc_wastewalker_worker" where entry IN (17963,17964);

REPLACE INTO `creature_text` VALUES (17959,0,0,'Get back to work you!','Vous, retournez au travail !',1,0,100,0,0,0,'Conducteur esclaves de Glissecroc - Enclos'),(17959,0,1,'Wake up! Now get up and back to work!','Debout ! On se lève et on retourne au travail !',1,0,100,0,0,0,'Conducteur esclaves de Glissecroc - Enclos'),(17959,0,5,'What is this?! Didn\'t mommy and daddy teach you anything?!','Hé ben alors ? Papa et môman ne t\'ont rien appris ?',1,0,100,0,0,0,'Conducteur esclaves de Glissecroc - Enclos'),(17959,1,0,'Assist me slaves!','Esclaves, aidez-moi !',1,0,100,0,0,0,'Conducteur esclaves de Glissecroc - Aggro');

-- Coilfang Slavehandler 
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_coilfang_slavehandler" WHERE `entry`=17959;

UPDATE spell_template SET maxLevel = 0 WHERE id = 37661;