UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (1368, 1370, 1371);
DELETE FROM smart_scripts WHERE entryorguid IN (1368, 1370, 1371);
INSERT INTO smart_scripts VALUES
(1371, 0, 0, 0, 1, 0, 100, 0, 6000, 10000, 55000, 65000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Roman - OOC Timer - Random Say"),
(1368, 0, 0, 0, 1, 0, 100, 0, 4000, 8000, 55000, 65000, 1, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Justin - OOC Timer - Random Say"),
(1368, 0, 1, 0, 52, 0, 100, 0, 0, 0, 0, 0, 45, 0, 0, 0, 0, 0, 0, 19, 1370, 50, 0, 0, 0, 0, 0, "Justin - Set data (0, 0) on Brandon on text over"),
(1370, 0, 0, 0, 38, 0, 100, 0, 0, 0, 10000, 10000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Bradon - Get data (0, 0) - Say random");

DELETE FROM creature_text WHERE entry IN (1368, 1370, 1371);
INSERT INTO creature_text VALUES
(1371, 0, 0, "Pouah... ce n’est pas un poisson !", 0, 0, 100, 0, 0, 0, "Roman"),
(1371, 0, 1, "Il y a une odeur bizarre.", 0, 0, 100, 0, 0, 0, "Roman"),
(1371, 0, 2, "Je crois que je vois quelque chose.", 0, 0, 100, 0, 0, 0, "Roman"),
(1371, 0, 3, "J'ai un ver de terre écrabouillé sur mes chaussures.", 0, 0, 100, 0, 0, 0, "Roman"),
(1371, 0, 4, "J'espère que c'était un poisson !", 0, 0, 100, 0, 0, 0, "Roman"),
(1371, 0, 5, "J'ai cru entendre un bruit.", 0, 0, 100, 0, 0, 0, "Roman"),
(1371, 0, 6, "On accroche le ver à l'hameçon, on plonge l'hameçon dans l'eau. Le poisson, notre poisson, est dans l'eau.", 0, 0, 100, 0, 0, 0, "Roman"),
(1368, 0, 0, "Et alors le lapin l’a mordu et lui a arraché la tête... Je le jure.", 0, 0, 100, 0, 1000, 0, "Justin"),
(1368, 0, 1, "On dit qu’il se métamorphose parfois en corbeau.", 0, 0, 100, 0, 1000, 0, "Justin"),
(1368, 0, 2, "Les chevaliers firent face aux charges de la Horde et résistèrent à un millier d’orcs enragés qui déferlaient à travers la vallée.", 0, 0, 100, 0, 1000, 0, "Justin"),
(1368, 0, 3, "Tu sais qu’il y a des crocilisques dans les canaux. Les gens les ont capturés dans les marais pour s'en faire des animaux de compagnie et ont fini par les relâcher dans les canaux.", 0, 0, 100, 0, 1000, 0, "Justin"),
(1368, 0, 4, "Il n’y a pas de cuillère.", 0, 0, 100, 0, 1000, 0, "Justin"),
(1368, 0, 5, "Tu sais pourquoi les orcs ont des yeux rougeoyants ? Parce qu’ils boivent du sang !", 0, 0, 100, 0, 1000, 0, "Justin"),
(1368, 0, 6, "Et c’est comme ça que Lothar a tué trente-six orcs à mains nues !", 0, 0, 100, 0, 1000, 0, "Justin"),
(1370, 0, 0, "Tu t'imagines ?", 0, 0, 100, 0, 0, 0, "Brandon"),
(1370, 0, 1, "Allez, ce n’est pas vrai.", 0, 0, 100, 0, 0, 0, "Brandon"),
(1370, 0, 2, "Vraiment ?", 0, 0, 100, 0, 0, 0, "Brandon"),
(1370, 0, 3, "Incroyable.", 0, 0, 100, 0, 0, 0, "Brandon"),
(1370, 0, 4, "Oh oui, j'ai entendu parler de cela.", 0, 0, 100, 0, 0, 0, "Brandon"),
(1370, 0, 5, "Ça me fait penser aux histoires de poisson que Billy raconte.", 0, 0, 100, 0, 0, 0, "Brandon"),
(1370, 0, 6, "C’est super.", 0, 0, 100, 0, 0, 0, "Brandon");

UPDATE waypoint_data SET action = 0 WHERE id IN (1618, 1619, 1620);
