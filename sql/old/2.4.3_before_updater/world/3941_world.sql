UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 3518;

DELETE FROM smart_scripts WHERE entryorguid = 3518;
INSERT INTO smart_scripts VALUES (3518, 0, 0, 0, 1, 0, 100, 0, 5000, 8000, 45000, 50000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Thomas Miller - Random say");

DELETE FROM creature_text WHERE entry = 3518;
INSERT INTO creature_text VALUES
(3518, 0, 0, "Brioches, petits pains et miches. Tout frais, sortis du four !", 0, 0, 100, 0, 0, 0, "Thomas Miller"),
(3518, 0, 1, "Du pain bien chaud, bien nourrissant !", 0, 0, 100, 0, 0, 0, "Thomas Miller"),
(3518, 0, 2, "J'avais entendu parler de souris trouvées dans des bouteilles de bière, mais jamais dans une miche de pain. Je vous en prie, prenez tout ceci, et n'en parlez à personne.", 0, 0, 100, 0, 0, 0, "Thomas Miller"),
(3518, 0, 3, "Oh… Quelqu'un est tombé malade en mangeant mon pain ? Mais comment ? Je vous en prie, j'espère que mes maigres économies suffiront à régler tout problème.", 0, 0, 100, 0, 0, 0, "Thomas Miller"),
(3518, 0, 4, "Pain frais, tout juste sorti du four !", 0, 0, 100, 0, 0, 0, "Thomas Miller"),
(3518, 0, 5, "Pain frais !", 0, 0, 100, 0, 0, 0, "Thomas Miller");


DELETE FROM eventai_scripts WHERE creature_id = 3518;
DELETE FROM eventai_texts WHERE entry IN (-204, -205);
