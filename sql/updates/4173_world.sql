DELETE FROM creature_text WHERE entry = 23863;
INSERT INTO creature_text VALUES
(23863, 0, 0, "Everybody always wanna take from us. Now we gonna start takin' back. Anybody who get in our way...gonna drown in their own blood! De Amani empire be back now...seekin' vengeance. And we gonna start...with you!", "Depuis toujours tout le monde il veut nous dépouiller. Mais on va commencer à prendre ce qui nous a été pris. Ceux qui se mettront sur notre chemin, on les noiera dans leur propre sang. L'empire Amani est de retour pour se venger. Et on va commencer par vous !", 1, 0, 100, 0, 0, 12090, "Zul'jin - Intro"),
(23863, 1, 0, "Let me introduce to you my new bruddahs: fang and claw!", "J'vous présente mes nouveaux frères : griffe et croc !", 1, 0, 100, 0, 0, 12094, "Zul'jin - Lynx"),
(23863, 2, 0, "Got me some new tricks...like me bruddah bear!", "J'ai des nouveaux tours... comme mon frère ours...", 1, 0, 100, 0, 0, 12092, "Zul'jin - Bear"),
(23863, 3, 0, "Ya don' have to look to da sky to see da dragonhawk!", "Pas besoin d'lever les yeux au ciel pour voir l'faucon-dragon !", 1, 0, 100, 0, 0, 12095, "Zul'jin - Dragonhawk"),
(23863, 4, 0, "Dere be no hidin' from da eagle!", "L'aigle, il vous trouvera partout !", 1, 0, 100, 0, 0, 12093, "Zul'jin - Eagle"),
(23863, 5, 0, "Da Amani de chuka!", "Da Amani de chuka !", 1, 0, 100, 0, 0, 12098, "Zul'jin - Kill"),
(23863, 5, 1, "Lot more gonna fall like you!", "Plein d'autres y vont tomber comme vous !", 1, 0, 100, 0, 0, 12099, "Zul'jin - Kill"),
(23863, 6, 0, "Fire kill you just as quick!", "Le feu, il va vous tuer aussi vite !", 1, 0, 100, 0, 0, 12096, "Zul'jin - Fire breath"),
(23863, 7, 0, "Nobody badduh dan me!", "Y'a personne plus balèze que moi !", 1, 0, 100, 0, 0, 12091, "Zul'jin - Aggro"),
(23863, 8, 0, "You too slow! Me too strong!", "Vous trop lents et moi trop fort !", 1, 0, 100, 0, 0, 12097, "Zul'jin - Berserk"),
(23863, 9, 0, "Mebbe me fall...but da Amani empire...never gonna die...", "J'suis peut-être vaincu... Mais l'empire Amani, il mourra jamais !", 1, 0, 100, 0, 0, 12100, "Zul'jin - Death");

UPDATE locales_quest SET RequestItemsText_loc2 = "Ceux qui badinent avec cette tâche pourraient tout aussi bien finir comme leurs frères et soeurs du village, tombés et errant sans but. Espérons que vous vous en sortirez mieux que ça, hein ?$B$B" WHERE entry = 3901;
UPDATE locales_quest SET requestitemstext_loc2 = "Méfiez-vous du poison des araignées, $N. Si vous sentez une brûlure douloureuse, vous devriez y jeter un oeil." WHERE entry = 380;
UPDATE locales_quest SET requestitemstext_loc2 = "Nous devons respecter nos morts, $N. C'est une des choses pour lesquelles nous sommes différents des Mort-Vivants..." WHERE entry = 6395;
UPDATE locales_quest SET offerrewardtext_loc2 = "Ceux-ci feront parfaitement l'affaire, $N. Merci.$B$BSi vous êtes prêt, nous pouvons entamer l'étape suivante." WHERE entry = 5901;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous déjà les termites, $N ? Je suis sûr que c'est évident pour $Gun:une; $C comme vous.$B$BUne fois que vous en aurez assez, nous nous assurerons que personne ne puisse plus jamais utiliser le moulin !" WHERE entry = 5901;
UPDATE locales_quest SET offerrewardtext_loc2 = "Les termites sont visiblement très agitées alors que vous posez le tonneau sur la caisse." WHERE entry = 5902;
UPDATE locales_quest SET requestitemstext_loc2 = "Vous n'avez pas encore accompli votre devoir, $C. Nous ne pouvons espérer récupérer les plans de la Dame Noire tant que la Croisade Ecarlate pourchassera nos soldats. Apportez-leur la mort et accomplissez votre devoir pour Sylvanas !" WHERE entry = 372;
UPDATE locales_quest SET requestitemstext_loc2 = "J'attends une preuve de votre allégeance, $C." WHERE entry = 409;
UPDATE locales_quest SET offerrewardtext_loc2 = "Ne vous préoccupez pas du monde sous Teldrassil pour le moment. Nous aurons du temps pour ça plus tard. Maintenant, allez-y et parlez aux autres de Sombrevallon -- ils pourront vous en dire plus sur ce qui est arrivé. Aidez-les autant que vous le pouvez, et si à un moment vous sentez que vous avez besoin de plus d'entraînement, revenez me voir et je vous apprendrai ce que je sais." WHERE entry = 3119;
UPDATE locales_quest SET requestitemstext_loc2 = "Cela me fait plaisir de voir que vous êtes arrivé si vite, $N. Bienvenue.$B$BComme vous l'avez sans doute entendu, tout Teldrassil est animé par les arrivées et départs des voyageurs. Même des membres de l'Alliance ont été autorisés à accéder à Teldrassil pour rencontrer d'autres Kaldorei qui se préparent pour d'autres aventures." WHERE entry = 3119;
UPDATE locales_quest SET offerrewardtext_loc2 = "Merci, $N. Quand je retournerai à Darnassus, je comparerai le venin contenu dans ces sacs avec le venin d'autres araignées. Je pense qu'il va avoir des propriétés liées à la récente ascencion de notre nouvel arbre monde." WHERE entry = 916;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous collecté les sacs de venin, $N ?" WHERE entry = 916;
UPDATE locales_quest SET offerrewardtext_loc2 = "Ah, très bien. Je vais faire transporter cet oeuf et le venin à Darnassus, puis y retourner quand mes études ici seront terminées. J'espère faire une grande découverte avec ces specimens, $N. Vous m'avez été d'une aide précieuse." WHERE entry = 917;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous été dans la Grotte de Sombrefil, $N ? Avez-vous trouvé un oeuf d'araignée ?" WHERE entry = 917;
UPDATE locales_quest SET requestitemstext_loc2 = "Notre fraternité ne peut pas s'éveiller avant qu'Ursal le Marteleur ait été tué, $N." WHERE entry = 486;
UPDATE locales_quest SET offerrewardtext_loc2 = "Bien joué ! Ces tumeurs sont les symptômes de la maladie sylvaine. Elles sont pleines d'un poison que nous devons nettoyer de notre nouveau pays.$B$BJe vais m'occuper de ces tumeurs. Merci, $N." WHERE entry = 923;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous été au lac d'Aigue-vive, $N ? Avez-vous chassé les sylvains là-bas ?" WHERE entry = 923;
UPDATE locales_quest SET offerrewardtext_loc2 = "Je savais que vous étiez plus que capable de débarasser le lac de cette horrible bête.$B$BC'est une situation pénible; Froncechêne était autrefois un grand chef de sa race... mais la corruption ne fait pas de différence entre les petits et les nobles.$B$BLa taille de cette tumeur est assez déroutante, mais je dois l'étudier pour en apprendre plus sur la maladie qui rend les sylvains fous furieux.$B$BMerci, $N." WHERE entry = 2499;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous déjà localisé Froncechêne, $N ?" WHERE entry = 2499;
UPDATE locales_quest SET offerrewardtext_loc2 = "Mon Capturêve d'émeraude est d'une grande importance pour moi. C'est un cadeau qui n'est donné qu'à peu de gens. Merci de me l'avoir ramené, $N." WHERE entry = 2438;
UPDATE locales_quest SET requestitemstext_loc2 = "Essayez de bouger rapidement. Je peux seulement espérer que les Furbolgs n'aient pas abîmé mon Capturêve d'émeraude.$B$BL'avez-vous déjà récupéré, $N ?" WHERE entry = 2438;
UPDATE locales_quest SET offerrewardtext_loc2 = "... Qu'est-ce ? Un coeur de sylvain ?? Il est couvert de mousse !$B$BMerci de m'avoir amené ceci, $N. Je vais examiner le coeur et, si la chance me sourit, déterminer la nature de la mousse qui le recouvre." WHERE entry = 927;
UPDATE locales_quest SET requestitemstext_loc2 = "$N ! Vous avez quelque chose pour moi ?" WHERE entry = 927;
UPDATE locales_quest SET requestitemstext_loc2 = "La route n'est de nouveau plus sécurisée, $C. Suivez-la et tuez 6 Embusqués Pins-tordus, et revenez ensuite me voir." WHERE entry = 487;
UPDATE creature_template SET Scriptname = "npc_mist" WHERE entry = 3568;
UPDATE locales_quest SET offerrewardtext_loc2 = "Qu'avez-vous à rapporter, $N ? Avez-vous été à la mine de Fondugouffre ?" WHERE entry = 62;
UPDATE locales_quest SET offerrewardtext_loc2 = "Salutations, $N. Qu'avez-vous à rapporter ? Etes-vous allé explorer la mine de Veine-de-jaspe ?" WHERE entry = 76;
UPDATE locales_quest SET offerrewardtext_loc2 = "Merci, $N ! Et revenez me voir si vous voulez à nouveau faire du commerce." WHERE entry = 16;
UPDATE locales_quest SET requestitemstext_loc2 = "L'agriculture est une activité qui donne soif, et je suis toujours à la recherche d'eau de source rafraîchissante.$B$BSi vous en avez, je suis intéressé par un échange." WHERE entry = 16;
UPDATE locales_quest SET offerrewardtext_loc2 = "Avez-vous les ailerons ? Parfait ! Le maréchal Dughan est inquiet au sujet de la situation des Murlocs à l'Est d'Elwynn, et j'aimerais lui dire qu'elle est sous contrôle.$B$BVos actions ont permis de réaliser cela." WHERE entry = 46;
UPDATE locales_quest SET requestitemstext_loc2 = "Comment se passe la chasse, $N ?" WHERE entry = 46;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous tué les loups et les ours ?" WHERE entry = 52;
UPDATE locales_quest SET requestitemstext_loc2 = "A... Alors ?" WHERE entry = 109;
UPDATE locales_quest SET offerrewardtext_loc2 = "Hmm, miam ! Cette tarte est la meilleure !$B$BJe pense que ma mémoire me revient..." WHERE entry = 84;
UPDATE locales_quest SET requestitemstext_loc2 = "Ugh... Je suis affamé ! Avez-vous de la tarte pour moi, $N ?" WHERE entry = 84;
UPDATE locales_quest SET requestitemstext_loc2 = "Je suis impatient d'entendre comment mes amis vont réagir !$B$BIls ne vont pas du tout s'y attendre." WHERE entry = 111;
UPDATE locales_quest SET requestitemstext_loc2 = "Comment se passe la chasse, $N ? Avez-vous trouvé et tué cette vermine ?" WHERE entry = 7;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous été aux mines ? Etes-vous prêt à faire votre rapport ?" WHERE entry = 15;
UPDATE locales_quest SET requestitemstext_loc2 = "Je sais que c'est un travail de titan, $N, mais c'est vital pour la survie de Comté-du-Nord. Etes-vous prêt à faire votre rapport ?" WHERE entry = 21;
UPDATE locales_quest SET offerrewardtext_loc2 = "Oh merci, $N ! Vous avez sauvé ma récolte ! Et j'espère que vous avez montré à quelques-uns de ces Defias qu'ils ne peuvent pas semer le trouble par ici.$B$BNous sommes à court de gardes ces jours-ci, mais nous avons de la chance d'avoir des héros tels que vous pour nous protéger !" WHERE entry = 3904;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous ma récolte, $N ?" WHERE entry = 3904;
UPDATE locales_quest SET requestitemstext_loc2 = "J'espère que vous n'êtes pas revenu pour tenter de me convaincre que vous avez complété votre tâche, $N ? Non, bien sûr que non. J'attends mieux de vous." WHERE entry = 788;
UPDATE locales_quest SET requestitemstext_loc2 = "Pour prouver que vous êtes opposés à la Lame Ardente, vous devez d'abord tuer des vils quasits. Revenez me voir quand vous l'aurez fait." WHERE entry = 792;
UPDATE locales_quest SET offerrewardtext_loc2 = "Vous l'avez récupéré ! Bien joué !$B$BVos efforts à l'intérieur du Convent de la Lame ardente sont une clé pour la destruction de ce culte dans la Vallée des Epreuves. Mais j'ai peur qu'ils aient des buts plus avancés dans notre région.$B$BNous n'en avons pas fini avec eux." WHERE entry = 794;
UPDATE locales_quest SET requestitemstext_loc2 = "Votre tâche est-elle complète, $N ? Avez-vous le Médaillon de la Lame ardente ?" WHERE entry = 794;
UPDATE locales_quest SET offerrewardtext_loc2 = "Magnifique, $N ! Comme promis, voici votre pomme de cactus surprise accompagnée d'un petit supplément." WHERE entry = 4402;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous fini de collecter les pommes de cactus ?" WHERE entry = 4402;
UPDATE locales_quest SET offerrewardtext_loc2 = "Bien, vous l'avez ! Merci beaucoup, . C'est ma pioche favorite ! Maintenant, si mes péons finissent un jour d'abattre ces arbres, peut-être pourrons-nous trouver une belle grotte pour miner." WHERE entry = 6394;
UPDATE locales_quest SET requestitemstext_loc2 = "Etes-vous entré dans le Convent de la Lame ardente, $N ? Avez-vous trouvé ma pioche ?" WHERE entry = 6394;
UPDATE locales_quest SET requestitemstext_loc2 = "La carapace d'un scorpide n'est pas si robuste que la force d'un guerrier déterminé. Frappez fort et sans hésitation, et les scorpides devraient se révéler une proie facile." WHERE entry = 4641;
UPDATE locales_quest SET offerrewardtext_loc2 = "Vous avez réussi, $N. Avec nos sanctums des arcanes non opérationnels à pleine puissance, ces noyaux de puissance vont combler nos besoins encore longtemps." WHERE entry = 8472;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous déjà réussi à récolter les noyaux des arcanes, $N ?" WHERE entry = 8472;
UPDATE locales_quest SET requestitemstext_loc2 = "Je crains de vous demander, $N... La tâche est-elle accomplie ?" WHERE entry = 8473;
UPDATE locales_quest SET requestitemstext_loc2 = "Vous êtes de retour, $N. Avez-vous déjà tué les morts-vivants le long de la Malebrèche ?" WHERE entry = 8475;
UPDATE locales_quest SET requestitemstext_loc2 = "Vous trouverez Tor'Watha et Zeb'Watha au sud-est d'ici. Revenez quand vous aurez tué les trolls." WHERE entry = 8476;
UPDATE locales_quest SET offerrewardtext_loc2 = "Les rumeurs étaient donc vraies ! Ce Taille-Epieu est léger et fort à la fois; je devrais me débrouiller pour terminer plusieurs de mes projets en cours. Et bien sûr, je vous laisserai choisir en premier." WHERE entry = 8477;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous récuperé le Taille-Epieu Otembe ?" WHERE entry = 8477;
UPDATE locales_quest SET requestitemstext_loc2 = "Vous êtes-vous occupé des âmes en peine ?" WHERE entry = 8486;
UPDATE locales_quest SET offerrewardtext_loc2 = "Excellent. Je vais lancer un enchantement d'augmentation sur les échantillons, et j'espère analyser clairement la souillure du sol." WHERE entry = 8487;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous collecté les échantillons que je vous ai demandés, $N ?" WHERE entry = 8487;
UPDATE locales_quest SET offerrewardtext_loc2 = "Excellent. Les défenses devraient repousser les morts-vivants encore un peu. Merci pour le coup de main, $N." WHERE entry = 8490;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous déjà réussi à renforcer la pierre runique, $N ?" WHERE entry = 8490;
UPDATE locales_quest SET objectives_loc2 = "Oh vous, adorable, adorable $C ! Je ne me doutais pas que ces horribles murlocs sinistrécailles avaient aussi volé mes gouvernails ! Sans eux, je n'aurai plus la chance de naviguer à nouveau sur les mers une fois que nous aurons repris l'ancrage et réparé le navire.$B$BMerci beaucoup ! Tenez, prenez cette pièce en signe d'amitié. " WHERE entry = 8887;
UPDATE locales_quest SET offerrewardtext_loc2 = "Bonjour, $C, vous êtes un régal pour les yeux. Je sais, c'est fou de ma part d'être ici, avec l'ancrage envahi par les misérables. Velendris et ses soldats ont juré de me protéger à condition que je parte d'ici dès que j'ai récupéré mon bateau.$B$BQu'avez-vous là... Celà me semble vaguement familier ?" WHERE entry = 8887;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous donné une leçon à ces misérables ?" WHERE entry = 8892;
UPDATE locales_quest SET requestitemstext_loc2 = "Vous êtes-vous occupé de ça ? Avez-vous marchandé avec un bon nombre de ces anomalies magiques ? Qu'est ce que je vais faire si le magistère Ternesoir réapparaissait, avec toutes ces choses tapies dans l'ombre ?" WHERE entry = 8894;
UPDATE locales_quest SET offerrewardtext_loc2 = "Merci, $N. J'ai tant attendu cette lettre." WHERE entry = 8895;
UPDATE locales_quest SET requestitemstext_loc2 = "Oui, $C ?" WHERE entry = 8895;
UPDATE locales_quest SET offerrewardtext_loc2 = "Vous dites que ces deux fous incompétents ont tentés de me mentir ? Vous avez très bien fait de venir me voir, $N." WHERE entry = 9064;
UPDATE locales_quest SET requestitemstext_loc2 = "Quelle est la raison de cette interruption dans ma lecture, $C ?" WHERE entry = 9064;
UPDATE locales_quest SET offerrewardtext_loc2 = "Excellent travail, $N. Ne vous inquiétez pas, la transformation n'est pas permanente. Leur apprentissage, cependant, ne reprendra pas tant qu'ils ne reviendront pas." WHERE entry = 9066;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous fait ce que je vous ai demandé, $N ?" WHERE entry = 9066;
UPDATE locales_quest SET offerrewardtext_loc2 = "Vous êtes très énergique $Gjeune homme:jeune femme;, n'est-ce pas ?$B$BTout cela me semble parfait. Vous méritez vraiment une compensation pour tout ce que vous avez ramené pour moi, et quelque chose comme un petit extra je pense.$B$BOh, j'ai presque oublié, il y a une invitation à la fête. Et $C, la prochaine fois que vous venez, essayez d'être habillé de manière un peu plus... festive." WHERE entry = 9067;
UPDATE locales_quest SET requestitemstext_loc2 = "Nous vaincrons, $N." WHERE entry = 9252;
UPDATE locales_quest SET requestitemstext_loc2 = "Avez-vous découvert quelque chose ? Est-ce que les elfes de la nuit sont derrière tout ça ?" WHERE entry = 9352;

UPDATE script_texts SET content_loc2 = "Quel genre de tour est-ce là, $R ? Si vous cherchez à m'attirer dans un piège, je dois vous avertir que je ne vais pas me laisser faire !" WHERE entry = -1000282;
UPDATE script_texts SET content_loc2 = "Très bien. Voyons ce que vous avez à me montrer, $N." WHERE entry = -1000281;
UPDATE script_texts SET content_loc2 = "libère ce qu'il reste de ses énergies dans la Pierre runique proche, parvenant à la réactiver." WHERE entry = -1000283;

UPDATE gameobject SET spawntimesecs = 15 WHERE id IN (181110, 180600, 181107, 180917);

UPDATE gameobject_template SET data1 = 20 WHERE entry = 300086;

UPDATE eventai_texts SET content_loc2 = "N'avez-vous pas assez frappé ? Devez-vous aussi déranger mon sommeil ?" WHERE entry = -115;
UPDATE eventai_texts SET content_loc2 = "Quel bien cette violence procure-t-elle ? Ce qui est fait, est fait. J'ai échoué pour mon peuple." WHERE Entry = -116;
