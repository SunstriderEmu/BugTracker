DELETE FROM npc_text WHERE ID IN (43, 44, 45, 46);
INSERT INTO npc_text (ID, text2_0) VALUES
(43, "Bonjour, tu viens pour t'inscrire à la loterie WoW Mania ? N'oublie pas qu'elle est réservée aux personnages ayant plus de 30 jours de /played. Attention, une seule inscription par compte !"),
(44, "Parfait, te voilà inscrit(e)."),
(45, "Désolé, il y a déjà une inscription sur ce compte."),
(46, "Désolé mais tu n'as pas les 30 jours de jeu nécessaires pour t'inscrire.");

DELETE FROM creature_template WHERE entry = 45;
INSERT INTO creature_template VALUES(45, 0, 19645, 0, 19645, 0, "Lotterie WoW Mania", "Event WoW Mania", NULL, 70, 70, 5000, 5000, 5000, 5000, 1, 35, 35, 1, 1, 1, 1, 500, 500, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 5, 5, 5, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, "", 0, 3, 0, 1, 0, 0, 2, "npc_lottery", 0);
