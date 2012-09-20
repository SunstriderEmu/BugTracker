UPDATE creature_template SET AIName = "NullCreatureAI", ScriptName = "" WHERE entry IN (17968, 17946, 18095, 18104);
UPDATE creature_template SET lootid = 0 WHERE entry = 17968; -- Was 17968

DELETE FROM creature_scripts WHERE entryorguid IN (17968, 17946, 18104);
INSERT INTO creature_scripts VALUES
(17968, "boss_archimonde"),
(17946, "mob_ancient_whisp"),
(18104, "mob_walking_doomfire");

DELETE FROM trinity_string WHERE entry = 59;
INSERT INTO trinity_string (entry, content_default, content_loc2) VALUES
(59, "ATTENTION: This script is currently in testing phase, so no loot is given if you down him. Please report any bug to the developers!", "ATTENTION: Ce script est actuellement en phase de test, et aucun loot n'est donné si vous le tombez. Merci de signaler tout bug aux développeurs, les loots seront remis en place dès que le script aura été validé par les joueurs et le staff technique !");

UPDATE creature_template SET faction_a = 14, faction_h = 14 WHERE entry = 18104;
UPDATE creature_template SET faction_a = 14, faction_h = 14 WHERE entry = 18095;

DELETE FROM creature_text WHERE entry = 17968;
INSERT INTO creature_text (entry, groupid, id, text_en, text_fr, `type`, probability, sound, comment) VALUES
(17968, 0, 0, "Your resistance is insignificant.", "Votre résistance est futile.", 1, 100, 10987, "Archimonde - YELL_AGGRO"),
(17968, 1, 0, "This world will burn!", "Ce monde brûlera !", 1, 100, 10990, "Archimonde - YELL_DOOMFIRE"),
(17968, 1, 1, "Manach sheek-thrish!", "Manach sheek-trish !", 1, 100, 11041, "Archimonde - YELL_DOOMFIRE"),
(17968, 2, 0, "A-kreesh!", "A-Kreesh !", 1, 100, 10989, "Archimonde - YELL_AIRBURST"),
(17968, 2, 1, "Away vermin!", "Dégage vermine !", 1, 100, 11043, "Archimonde - YELL_AIRBURST"),
(17968, 3, 0, "All creation will be devoured!", "Toute la création sera dévorée !", 1, 100, 11044, "Archimonde - YELL_SLAY"),
(17968, 3, 1, "Your soul will languish for eternity.", "Ton âme se morfondra pour l'éternité.", 1, 100, 10991, "Archimonde - YELL_SLAY"),
(17968, 3, 2, "I am the coming of the end!", "Je suis l'avènement de la fin !", 1, 100, 11045, "Archimonde - YELL_SLAY"),
(17968, 4, 0, "At last it is here. Mourn and lament the passing of all you have ever known and all that would have been! Akmin-kurai!", "L'heure est enfin venue ! Pleurez et lamentez-vous, car voici venue la fin de tout ce que vous avez pu connaître et de tout avenir ! Akmin-kurai !", 1, 100, 10993, "Archimonde - YELL_ENRAGE"),
(17968, 5, 0, "No, it cannot be! Nooo!", "Non, c'est impossible ! Nooon !", 1, 100, 10992, "Archimonde - YELL_DEATH"),
(17968, 6, 0, "You are mine now.", "Vous êtes à moi maintenant !", 1, 100, 10988, "Archimonde - YELL_SOULCHARGE"),
(17968, 6, 1, "Bow to my will.", "Pliez devant ma volonté !", 1, 100, 11042, "Archimonde - YELL_SOULCHARGE");
