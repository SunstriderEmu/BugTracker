UPDATE gameobject_template SET AIName = "SmartGameObjectAI", ScriptName = "" WHERE entry = 182349;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 18445;

DELETE FROM smart_scripts WHERE entryorguid IN (18445, 182349);
INSERT INTO smart_scripts VALUES
-- (182349, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 45, 0, 0, 0, 0, 0, 0, 19, 18445, 5, 0, 0, 0, 0, 0, "Quest 9923 - Cage"),
-- (18445, 0, 0, 0, 38, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, -2551.738770, 6268.343262, 15.197194, 5.374778, "Quest 9923 - NPC");
(182349, 1, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 4, 18445, 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 9923 - Cage"),
(18445, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 5, 182349, 1000, 1, 25, 1, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 9923 - NPC"),
(18445, 0, 1, 0, 1, 0, 100, 0, 5000, 10000, 45000, 60000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Corki - OOC Timer - Random say");

DELETE FROM creature_text WHERE entry = 18445;
INSERT INTO creature_text VALUES
(18445, 0, 0, "Allez, mangez-moi ! Je ne supporte plus de rester enfermé dans cette cage avec de gros ploucs puants tout autour.", 0, 0, 100, 0, 0, 0, "Corki"),
(18445, 0, 1, "Hé, bande d'imbéciles, vous allez avoir des ennuis si je sors d'ici !", 0, 0, 100, 0, 0, 0, "Corki"),
(18445, 0, 2, "Hé, imbécile, et si on mangeait !?", 0, 0, 100, 0, 0, 0, "Corki"),
(18445, 0, 3, "Je veux mon papa !", 0, 0, 100, 0, 0, 0, "Corki"),
(18445, 1, 0, "Merci ! Je suis sûr que mon papa vous donnera une très belle récompense ! Salut !", 0, 0, 100, 0, 0, 0, "Corki");

UPDATE quest_template SET ReqCreatureOrGOId1 = 18445, ReqCreatureOrGOCount1 = 1 WHERE entry = 9923;
