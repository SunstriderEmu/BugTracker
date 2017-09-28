UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 1395;

DELETE FROM smart_scripts WHERE entryorguid = 1395;
INSERT INTO smart_scripts VALUES (1395, 0, 0, 0, 1, 0, 100, 0, 5000, 8000, 45000, 50000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Ol' Beasley - Random say");

DELETE FROM creature_text WHERE entry = 1395;
INSERT INTO creature_text VALUES
(1395, 0, 0, "C’est entièrement leur faute à ces imbéciles de soldats de l’Alliance. Il fallait qu'ils aillent construire leurs tours juste derrière ma ferme.", 0, 0, 100, 0, 0, 0, "Ol' Beasley"),
(1395, 0, 1, "Vous n’auriez pas une ou deux pièces ?", 0, 0, 100, 0, 0, 0, "Ol' Beasley"),
(1395, 0, 2, "Je te paierai volontiers mardi pour avoir un bon steak aujourd’hui.", 0, 0, 100, 0, 0, 0, "Ol' Beasley"),
(1395, 0, 3, "C’est entièrement leur faute à ces imbéciles d’orcs. Il fallait qu’ils réduisent ma ferme en cendres !", 0, 0, 100, 0, 0, 0, "Ol' Beasley"),
(1395, 0, 4, "Un coup de main à un pauvre malheureux ?", 0, 0, 100, 0, 0, 0, "Ol' Beasley"),
(1395, 0, 5, "La charité ?", 0, 0, 100, 0, 0, 0, "Ol' Beasley");

DELETE FROM eventai_scripts WHERE creature_id = 1395;
DELETE FROM eventai_texts WHERE entry IN (-412, -413);
