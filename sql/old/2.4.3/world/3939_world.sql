UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 3520;

DELETE FROM smart_scripts WHERE entryorguid = 3520;
INSERT INTO smart_scripts VALUES (3520, 0, 0, 0, 1, 0, 100, 0, 5000, 8000, 45000, 50000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Ol' Emma - Random say");

DELETE FROM creature_text WHERE entry = 3520;
INSERT INTO creature_text VALUES 
(3520, 0, 0, "Bien sûr, je me parle à moi-même. C'est la seule façon d'entretenir une conversation décente dans cette ville.", 0, 1, 100, 0, 0, 0, "Ol' Emma"), 
(3520, 0, 1, "Comme si, à mon grand âge, je n'avais pas mieux à faire que de porter des seaux d'eau.", 0, 0, 100, 0, 0, 0, "Ol' Emma"), 
(3520, 0, 2, "Où est l'eau, Emma ? Va chercher l'eau, Emma ! Si je m'en chargeais pas, y'en aurait beaucoup qui n'sauraient pas à quoi r'semble l'eau...", 0, 0, 100, 0, 0, 0, "Ol' Emma"), 
(3520, 0, 3, "J'ai l'impression de faire une centaine de fois par jour ce trajet vers le puits pour aller chercher plus d'eau. Aucun respect pour leurs aînés, je vous dis.", 0, 0, 100, 0, 0, 0, "Ol' Emma"), 
(3520, 0, 4, "Une impression de déjà-vu. Un instant, j'ai cru que j'étais de nouveau à la maison... avant la peste...", 0, 0, 100, 0, 0, 0, "Ol' Emma"), 
(3520, 0, 5, "J'ai l'impression de m'enraciner dans les pavés.", 0, 0, 100, 0, 0, 0, "Ol' Emma");

DELETE FROM eventai_scripts WHERE creature_id = 3520;
DELETE FROM eventai_texts WHERE entry BETWEEN -428 AND -423;
