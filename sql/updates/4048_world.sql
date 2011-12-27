UPDATE locales_quest SET RequestItemsText_loc2 = "Tenaces ces bougres, n'est-ce pas ?" WHERE entry = 170;
UPDATE locales_quest SET OfferRewardText_loc2 = "Ah ! Merveilleux. La viande de loup devrait faire l'affaire. Oh, ne vous inquiétez pas, $N, je n'oublierai pas ma part de l'accord. Tenez-, l'un de ceux-ci devrait vous aller.", RequestItemsText_loc2 = "Les loups vous donnent du fil à retordre ? Vous allez vous débrouiller pour éviter crocs, griffes et autres morsures, non ?" WHERE entry = 179;
UPDATE locales_quest SET RequestItemsText_loc2 = "De ce que j'ai appris, ces trolls viennent du clan Crins-de-givre. Je crains de n'avoir aucune autre information sur eux qui pourrait vous aider, $N." WHERE entry = 182;
UPDATE eventai_texts SET content_loc2 = "La terre et le ciel vont brûler !" WHERE entry = -227;
UPDATE eventai_texts SET content_loc2 = "Mon arme avoir soif !" WHERE entry = -228;
UPDATE eventai_texts SET content_loc2 = "Tuer vous être facile." WHERE entry = -229;
UPDATE eventai_texts SET content_loc2 = "Vous mort bientôt !" WHERE entry = -230;
UPDATE eventai_texts SET content_loc2 = "Moi couper vous !" WHERE entry = -231;
INSERT INTO eventai_texts (entry, content_default, content_loc2, comment) VALUES (-689, "First da fire, and now da $C! You gonna die!", "D'abord le feu, et maintenant $Gle:la; $C ! Vous allez mourir !", "Grik'nir the Cold");
UPDATE eventai_scripts SET action2_type = 1, action2_param1 = -689 WHERE id = 80801;
UPDATE locales_quest SET RequestItemsText_loc2 = "Comment se passe la chasse ?" WHERE entry = 183;
UPDATE locales_quest SET OfferRewardText_loc2 = "Merveilleux, $N ! Un grand merci pour avoir ramené mon journal. Bien, il semblerait que la situation des trolls ici dans la Vallée des Frigères soit sous contrôle, et qu'il ne faille plus s'en inquiéter.$B$BAprès que j'aie mis la touche finale à mon rapport, j'aurai besoin de quelqu'un pour l'apporter à mon frère Senir.", RequestItemsText_loc2 = "$N ! Où en êtes-vous ?" WHERE entry = 218;
UPDATE gameobject SET spawntimesecs = 25 WHERE id IN (148499, 178084, 178085);
UPDATE db_script_string SET content_loc2 = "Oooooh chaud chaud chaud ! Si cela ne nous ramène pas le printemps, je ne sais pas ce qui le fera !" WHERE entry = 2000000046;
UPDATE db_script_string SET content_loc2 = "Il n'y a rien de tel qu'un brevage brûlant un jour frisquet à Dun Morogh pour bien démarrer la journée !" WHERE entry = 2000000045;
UPDATE locales_quest SET OfferRewardText_loc2 = "Excellent, $N ! Vous seriez surpris d'apprendre combien je rencontre de courriers qui oublient quelque chose d'aussi simple que de ramener la tasse. Les tasses ne poussent pas sur les arbres, ou alors qu'on me dise où !$B$BVoici un petit quelque chose pour l'effort. Merci encore pour votre aide.", RequestItemsText_loc2 = "J'espère que le brevage brûlant est arrivé chez Durnan à temps ! Vous êtes vous souvenu de me ramener ma tasse ?" WHERE entry = 3365;
UPDATE locales_quest SET OfferRewardText_loc2 = "Vous êtes en effet un héros spécial, $N. Nous vous souhaitons la bienvenue dans le monde d'Azeroth, et vous offrons un de ces cadeaux uniques !", RequestItemsText_loc2 = "Bonjour ! C'est un plaisir de vous rencontrer !$B$BJe vois que vous avez un bon spécial. Donnez-le moi et je vous offrirai quelque chose en échange." WHERE entry = 5841;

