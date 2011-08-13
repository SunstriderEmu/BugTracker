UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (7766, 1754, 1755);

DELETE FROM smart_scripts WHERE entryorguid IN (7766, 1754, 1755, 175400, 175500);
INSERT INTO smart_scripts VALUES
(7766, 0, 0, 0, 19, 0, 100, 0, 434, 0, 0, 0, 12, 1754, 6, 10000, 0, 0, 0, 8, 0, 0, 0, -8401.541016, 462.091553, 123.760002, 5.403464, "Spawn Lescovar on Quest accept"),
(7766, 0, 1, 0, 19, 0, 100, 0, 434, 0, 0, 0, 12, 1755, 6, 10000, 0, 0, 0, 8, 0, 0, 0, -8399.460938, 459.464569, 123.760155, 2.241359, "Spawn Marzon on Quest accept"),
(1754, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 80, 175400, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Start timed action list at spawn"),
(1754, 0, 1, 0, 6, 0, 100, 0, 0, 0, 0, 0, 33, 1754, 0, 0, 0, 0, 0, 18, 15, 0, 0, 0, 0, 0, 0, "Complete quest 434 on death"),
(1755, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 80, 175500, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Start timed action list at spawn"),
(1755, 0, 1, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 1 on aggro"),
(1755, 0, 2, 0, 6, 0, 100, 0, 0, 0, 0, 0, 33, 1755, 0, 0, 0, 0, 0, 18, 15, 0, 0, 0, 0, 0, 0, "Complete quest 434 on death"),
(1755, 0, 3, 0, 6, 0, 100, 0, 0, 0, 0, 0, 26, 434, 0, 0, 0, 0, 0, 18, 15, 0, 0, 0, 0, 0, 0, "Complete quest 434 on death"),
-- Timed action lists
(175400, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 0"),
(175400, 9, 1, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 1"),
(175400, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 2, 14, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Change faction"),
(175500, 9, 0, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 0"),
(175500, 9, 1, 0, 0, 0, 100, 0, 8000, 8000, 0, 0, 2, 14, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Change faction");

DELETE FROM creature_text WHERE entry IN (1754, 1755);
INSERT INTO creature_text VALUES
(1754, 0, 0, "Vous voilà. Quelles sont les nouvelles de la Marche de l'Ouest ?", 0, 0, 100, 1, 0, 0, "Text 0"),
(1754, 1, 0, "Mmh, ça pourrait être Shaw. Je vais voir ce que je peux trouver. Allez-y, je vous recontacterai bientôt.", 0, 0, 100, 1, 0, 0, "Text 1"),
(1755, 0, 0, "VanCleef a fait transmettre l'information que les plans sont en route. Mais il y a des rumeurs au sujet d'un espion.", 0, 0, 100, 1, 0, 0, "Text 0"),
(1755, 1, 0, "Les Defias vaincront ! Aucun aventurier ne nous arrêtera !", 0, 0, 100, 5, 0, 0, "Text 1");
