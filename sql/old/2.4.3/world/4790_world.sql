UPDATE creature SET position_x = '3323.15', position_y =  '-2995', position_z = '165', orientation = '5.4' WHERE id = 14494;
UPDATE creature_template SET faction_A = 35, faction_H = 35, ScriptName = 'npc_eris_havenfire' WHERE entry = 14494;
UPDATE creature_template SET faction_A = 35, faction_H = 35, speed = 0.5, ScriptName = 'npc_escaping_peasant', unit_flags = 4096 WHERE entry = 14485;
UPDATE creature_template SET faction_A = 35, faction_H = 35, speed = 0.5, ScriptName = 'npc_escaping_peasant', unit_flags = 4096 WHERE entry = 14484;

UPDATE creature_template SET equipment_id = 8, ScriptName = 'npc_scourge_archer' WHERE entry = 14489;

DELETE FROM script_texts WHERE entry BETWEEN -1590007 AND -1590000;
INSERT INTO script_texts (entry, content_default, content_loc2) VALUES (-1590000, "The Scourge are upon us ! Run ! Run for your lives !", "Le fléau est sur nous ! Courez ! Courez pour vos vies !");
INSERT INTO script_texts (entry, content_default, content_loc2) VALUES (-1590001, "Please help us ! The Prince has gone mad !", "A l'aide ! Le prince est devenu fou !");
INSERT INTO script_texts (entry, content_default, content_loc2) VALUES (-1590002, "Seek sanctuary in Hearthglen ! It is our only hope !", "Cherchez refuge à Âtreval! C'est notre seul espoir !");
INSERT INTO script_texts (entry, content_default, content_loc2) VALUES (-1590003, "We are saved ! The peasants have escaped the Scourge !", "Nous sommes sauvés ! Les paysans ont échappés au Fléau !");
INSERT INTO script_texts (entry, content_default, content_loc2) VALUES (-1590004, "I have failed once more...", "J'ai échoué à nouveau...");
INSERT INTO script_texts (entry, content_default, content_loc2) VALUES (-1590005, "Thank you, kind stranger. May your heroism never be forgotten.", "Merci, noble étranger. Puisse votre héroisme n'être jamais oublié.");
INSERT INTO script_texts (entry, content_default, content_loc2) VALUES (-1590006, "The power of the light is truly great and merciful.", "La puissance de la lumière est vraiment grande et miséricordieuse.");
INSERT INTO script_texts (entry, content_default, content_loc2) VALUES (-1590007, "Stranger, find the fallen Prince Menethil and end his reign of terror.", "Etranger, trouvez le Prince Menethil et mettez fin à son règne de terreur.");
