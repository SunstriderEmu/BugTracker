DELETE FROM escort_waypoints WHERE entry = 22458;
INSERT INTO escort_waypoints (entry, pointid, location_x, location_y, location_z, waittime, point_comment) VALUES
(22458, 0, -3737.466797, 5387.790527, -5.669578, 2000, "When researchers move to him"),
(22458, 1, -3708.968018, 5371.538574, -9.154227, 0, ""),
(22458, 2, -3649.878174, 5402.731445, -10.427496, 0, ""),
(22458, 3, -3610.909668, 5405.932617, -12.838598, 0, ""),
(22458, 4, -3556.854736, 5447.235352, -11.813972, 0, ""),
(22458, 5, -3548.220703, 5460.004395, -12.517664, 120000, "Digging site");

DELETE FROM creature WHERE id = 22466;
UPDATE creature_template SET ScriptName = "npc_chief_letoll" WHERE entry = 22458;

DELETE FROM script_texts WHERE entry BETWEEN -1000824 AND -1000804;
INSERT INTO script_texts (entry, content_default, content_loc2, type, comment) VALUES
(-1000804, "Aright, listen up! Form a circle around me and move out!", "Parfait, écoutez-moi ! Formez un cercle autour de moi et allons-y !", 0, ""),
(-1000805, "Aright, $R, just keep us safe from harm while we work. We'll pay you when we return.", "$R, votre travail est de veiller à notre sécurité pendant nos fouilles. Nous vous paierons en retour.", 0, ""),
(-1000806, "The dig site is just north of here.", "Le site de fouille est juste au nord d'ici.", 0, ""),
(-1000807, "We're here! Start diggin'!", "Nous y sommes ! Commencez à fouiller !", 0, ""),
(-1000808, "I think there's somethin' buried here, beneath the sand!", "Je crois qu'il y a quelque chose enterré ici, sous le sable !", 0, ""),
(-1000809, "Almost got it!", "J'y suis presque !", 0, ""),
(-1000810, "By Brann's brittle bananas! What is it?! It... It looks like a drum.", "Par la barbe de Brann ! Qu'est-ce que c'est que ça ?! On dirait... un tambour.", 0, ""),
(-1000811, "Wow... a drum.", "Wow... Un tambour.", 0, ""),
(-1000812, "This discovery will surely rock the foundation of modern archaeology.", "Cette découverte va sûrement faire trembler l'archéologie moderne sur ses bases.", 0, ""),
(-1000813, "Yea, great. Can we leave now? This desert is giving me hives.", "Ouais, super. On peut partir maintenant ? Ce désert me donne la chair de poule.", 0, ""),
(-1000814, "Have ye gone mad? You expect me to leave behind a drum without first beatin' on it? Not this son of Ironforge! No sir!", "Vous êtes devenus fous ? Vous espérez que je vais laisser derrière moi un tambour sans avoir d'abord frappé dessus ? Non messieurs !", 0, ""),
(-1000815, "This reminds me of that one time where you made us search Silithus for evidence of sand gnomes.", "Ça me rappelle la fois où il nous a fait chercher dans Silithus après des preuves de l'existence des gnomes des sables.", 0, ""),
(-1000816, "Or that time when you told us that you'd discovered the cure for the plague of the 20th century. What is that even? 20th century?", "Ou la fois où vous nous avez raconté que vous alliez découvrir un remède à la peste du 20e siècle. Déjà, qu'est-ce que c'est, le 20e siècle ?", 0, ""),
(-1000817, "I don't think it can top the one time where he told us that he'd heard that Arthas's \"cousin's\" skeleton was frozen beneath a glacier in Winterspring. I'll never forgive you for that one, Letoll. I mean honestly... Arthas's cousin?", "Je pense que ça ne vaut pas la fois où il nous a raconté qu'il avait entendu dire que le squelette du \"cousin\" d'Arthas était gelé sous un glacier au Berceau-de-l'Hiver. Je n'oublierai jamais celle là, Leglas. Sérieusement... Le cousin d'Arthas ?", 0, ""),
(-1000818, "
I dunno. It can't possibly beat the time he tried to convince us that we're all actually a figment of some being's imagination and that they only use us for their own personal amusement. That went over well during dinner with the family.", "Je ne sais pas. Ça ne peut pas battre la fois où il a tenté de nous convaincre que nous n'étions en fait qu'un produit de l'imagination de quelque être et qu'il nous utilisait pour son amusement personnel. Ça l'a vraiment fait pendant le souper de famille.", 0, ""),
(-1000819, "Shut yer yaps! I'm gonna bang on this drum and that's that!", "Taisez-vous ! Je vais frapper ce tambour et c'est tout !", 0, ""),
(-1000820, "bangs on the drum.", "frappe sur le tambour.", 2, ""),
(-1000821, "IN YOUR FACE! I told you there was somethin' here!", "PRENDS ÇA ! Je t'avais dit qu'il y avait quelque chose ici !", 0, ""),
(-1000822, "Don't just stand there! Help him out!", "Ne restez pas là à rien faire, aidez-le !", 0, ""),
(-1000823, "picks up the drum.", "ramasse le tambour.", 2, ""),
(-1000824, "You've been a tremendous help, $R! Let's get out of here before more of those things show up! I'll let Dwarfowitz know you did the job asked of ya' admirably.", "Vous avez été d'une aide précieuse, $R. Allons-nous en d'ici avant que d'autres de ces choses se montrent. Je ferai savoir à Nanowitz que vous avez fait votre travail de façon admirable.", 0, "");
