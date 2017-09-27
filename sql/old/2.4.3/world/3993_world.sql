UPDATE waypoint_data SET action = 0 WHERE id = 1874;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 3627;
DELETE FROM smart_scripts WHERE entryorguid = 3627;
INSERT INTO smart_scripts VALUES
(3627, 0, 0, 0, 1, 0, 100, 0, 5000, 8000, 45000, 60000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Erich Lohan - Random say");

DELETE FROM creature_text WHERE entry = 3627;
INSERT INTO creature_text VALUES
(3627, 0, 0, "La seule adresse à Hurlevent où le spirituel et les spiritueux se rencontrent, rendez-vous au Solitaire bleu !", 0, 0, 100, 0, 0, 0, "Erich Lohan"),
(3627, 0, 1, "L’étude de la magie vous fatigue les neurones ? Venez vous détendre au Solitaire bleu !", 0, 0, 100, 0, 0, 0, "Erich Lohan"),
(3627, 0, 2, "Boissons gratuites au Solitaire bleu !", 0, 0, 100, 0, 0, 0, "Erich Lohan"),
(3627, 0, 3, "Vous avez le cafard ? Venez vous amuser au Solitaire bleu !", 0, 0, 100, 0, 0, 0, "Erich Lohan");
