UPDATE creature_template SET scriptname = "npc_ranshalla" WHERE entry = 10300;

DELETE FROM escort_waypoints WHERE entry = 10300;
INSERT INTO escort_waypoints (entry, pointid, location_x, location_y, location_z, point_comment) VALUES
(10300, 0, 5726.812500, -4797.979004, 778.055969, ''),
(10300, 1, 5721.901367, -4849.633789, 782.762451, ''),
(10300, 2, 5705.146973, -4893.775879, 797.657776, ''),
(10300, 3, 5665.518555, -4924.465820, 804.933105, ''),
(10300, 4, 5631.193359, -4892.020996, 805.632324, 'First fire'),
(10300, 5, 5637.063965, -4897.290527, 804.877075, ''),
(10300, 6, 5668.041504, -4925.246094, 804.939087, ''),
(10300, 7, 5720.101074, -4981.542969, 808.104675, ''),
(10300, 8, 5768.163086, -4994.456543, 809.957520, 'Second fire'),
(10300, 9, 5757.904785, -4991.258789, 809.123474, ''),
(10300, 10, 5712.395020, -4981.708008, 807.418823, ''),
(10300, 11, 5686.963867, -5009.900879, 807.142273, ''),
(10300, 12, 5694.832520, -5055.198242, 808.136169, 'Third fire'),
(10300, 13, 5693.484375, -5048.557617, 807.346252, ''),
(10300, 14, 5685.230957, -5007.904785, 807.095825, ''),
(10300, 15, 5649.712402, -5002.858398, 807.560364, ''),
(10300, 16, 5610.134766, -5027.030762, 808.660767, 'Fourth fire'),
(10300, 17, 5622.132324, -5019.782715, 808.404846, ''),
(10300, 18, 5651.607422, -5000.604004, 807.779419, ''),
(10300, 19, 5625.451660, -4948.688477, 810.317810, ''),
(10300, 20, 5568.958496, -4936.618652, 831.900024, ''),
(10300, 21, 5514.549316, -4949.849121, 847.821594, ''),
(10300, 22, 5498.075195, -4949.790527, 849.900940, ''),
(10300, 23, 5465.934082, -4981.937012, 851.526733, 'Fifth fire'),
(10300, 24, 5471.778809, -4976.572754, 850.442078, ''),
(10300, 25, 5500.333008, -4948.274414, 850.027832, ''),
(10300, 26, 5521.205078, -4924.216309, 843.681152, ''),
(10300, 27, 5517.816895, -4920.993652, 844.860107, 'In front of the altar'),
(10300, 28, 5518.946289, -4912.187012, 845.474915, ''),
(10300, 29, 5509.369629, -4912.261230, 847.760376, ''),
(10300, 30, 5510.861328, -4913.903320, 847.274414, 'Behind the altar'),
(10300, 31, 5508.666504, -4922.549316, 846.508545, ''),
(10300, 32, 5519.201660, -4921.910645, 844.425842, ''),
(10300, 33, 5517.868652, -4920.710938, 844.900696, 'In front of the altar again');

DELETE FROM creature_text WHERE entry = 10300;
INSERT INTO creature_text (entry, groupid, id, text_en, text_fr, probability) VALUES
(10300, 0, 0, 'Remember, I need your help to properly channel. I will ask you to aid me several times on our path, so please be ready.', 'Souvenez-vous, j''ai besoin de votre aide pour réussir. Je vais vous demander de m''aider plusieurs fois sur le chemin, alors soyez prêt.', 100),
(10300, 1, 0, 'We''ve found it!', 'Nous l''avons trouvé !', 100),
(10300, 1, 1, 'Please, light this while I am channeling.', 'S''il vous plait, éclairez ceci pendant que je canalise.', 100),
(10300, 1, 2, 'This is the place. Let''s light it.', 'C''est l''endroit. Eclairons-le.', 100),
(10300, 3, 0, 'Let''s find the next one.', 'Allons trouver la prochaine flamme.', 100),
(10300, 3, 1, 'We must continue on now.', 'Nous devons continuer.', 100),
(10300, 4, 0, 'It is time for the final step; we must activate the altar.', 'C''est la dernière étape; nous devons activer l''autel.', 100),
(10300, 5, 0, 'I will read the words carved into the stone, and you must find a way to light it.', 'Je vais prononcer les mots gravés sur la pierre, et vous devrez trouver un moyen de l''allumer.', 100),
(10300, 6, 0, 'The altar is glowing! We have done it!', 'L''autel brille ! Nous l''avons fait !', 100),
(10300, 7, 0, 'What is happening? Look!', 'Que se passe-t-il ? Regardez !', 100),
(10300, 8, 0, 'Please, priesstesses, forgive us for our intrusion. We do not wish any harm here.', 'S''il vous plait, prêtresses, pardonnez notre intrusion. Nous ne vous voulons aucun mal.', 100),
(10300, 9, 0, 'We only wish to know why the wildkin guard this area...', 'Nous voulons seulement savoir pourquoi les Indomptables gardent cette zone...', 100),
(10300, 10, 0, 'Thank you for you help, <name>. I wish you well in your adventures.', 'Merci pour votre aide, %s. Je vous souhaite du courage pour vos aventures.', 100),
(10300, 11, 0, 'I want to stay here and reflect on what we have seen. Please see Erelas and tell him what we have learned.', 'J''ai envie de rester ici et de réfléchir à ce que nous venons de voir. S''il vous plait, allez voir Erelas et dites-lui ce que nous avons appris.', 100);

INSERT INTO creature_text (entry, groupid, id, text_en, text_fr, type, probability) VALUES
(10300, 2, 0, 'Ranshalla begins chanting a strange spell...', 'Ranshalla commence à incanter un sort étrange...', 2, 100);

DELETE FROM creature_text WHERE entry = 12116;
INSERT INTO creature_text (entry, groupid, id, text_en, text_fr, probability) VALUES
(12116, 0, 0, 'It has been many years...', 'Cela fait beaucoup d''années...', 100),
(12116, 1, 0, 'Who has disturbed the altar of the goddess?', 'Qui perturbe l''autel de la déesse ?', 100),
(12116, 2, 0, 'Enu thora''serador. This is a sacred place.', 'Enu thora''serador. C''est une place sacrée.', 100),
(12116, 3, 0, 'We will show you...', 'Nous allons vous montrer...', 100),
(12116, 4, 0, 'Look above you; thara dormil dorah...', 'Regardez au-dessus de vous; thara dormil dorah...', 100),
(12116, 5, 0, 'This gem once allowed direct communication with Elune, herself.', 'Cette gemme a une fois permis une communication directe avec Elune elle-même.', 100),
(12116, 6, 0, 'Through the gem, Elune channeled her infinite wisdom...', 'A travers cette gemme, Elune canalisait sa sagesse infinie...', 100),
(12116, 7, 0, 'Realizing that the gem needed to be protected, we turned to the goddess herself.', 'En réalisant que la gemme avait besoin d''être protégée, nous nous sommes tournées vers la déesse elle-même...', 100),
(12116, 8, 0, 'Soon after, we began to have visions of a creature... A creature with the feathers of an owl, but the will and might of a bear...', 'Peu de temps après, nous avons commencé à avoir des visions d''une créature... Une créature avec les plumes d''une chouette, mais avec la volonté et le pouvoir d''un ours...', 100),
(12116, 9, 0, 'It was on that day that the wildkin were given to us. Fierce guardians, the goddess assigned the wildkin to protect all of her sacred places.', 'Ce fut ce jour-là que les Indomptables nous furent donnés. Fiers gardiens, la déesse assigna aux Indomptables la protection de toutes ses places sacrées.', 100),
(12116, 10, 0, 'But now, many years later, the wildkin have grown more feral, and without the guidance of the goddess, they are confused...', 'Mais désormais, après de nombreuses années, les Indomptables sont devenus plus sauvages, et sans la présence de la déesse, ils sont confus...', 100),
(12116, 11, 0, 'Without a purpose, they wander... But many find their way back to the sacred areas that they once were sworn to protect.', 'Ils errent sans but... Mais beaucoup retrouvent leur chemin vers les zones sacrées qu''ils ont un jour été chargés de protéger.', 100),
(12116, 12, 0, 'Wildkin are inherently magical; this power was bestowed upon them by the goddess.', 'Les Indomptables sont profondément magiques; leur pouvoir leur a été conféré par la déesse.', 100),
(12116, 13, 0, 'Know that wherever you might find them in the world, they are protecting something of importance, as they were entrusted to do so long ago.', 'Sachez que peu importe où vous les trouverez dans le monde, ils protègent quelque chose d''important, comme il leur a été demandé de le faire il y a longtemps.', 100),
(12116, 14, 0, 'Please, remember what we have shown you...', 'S''il vous plait, souvenez-vous de ce que nous vous avons montré...', 100),
(12116, 15, 0, 'Farewell.', 'Adieu.', 100);

DELETE FROM creature_text WHERE entry = 12152;
INSERT INTO creature_text (entry, groupid, id, text_en, text_fr, probability) VALUES
(12152, 0, 0, 'Anu''dorini Talah, Ru shallora enudoril.', 'Anu''dorini Talah, Ru shallora enudoril.', 100);

UPDATE gameobject_template SET flags = 0, ScriptName = "go_altar_of_elune" WHERE entry = 177404;
UPDATE gameobject_template SET size = 5 WHERE entry = 177414;
UPDATE creature_template SET modelid_a = 12236, modelid_h = 12236, faction_a = 35, faction_h = 35 WHERE entry = 12152;