UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 5702;

DELETE FROM creature WHERE id IN (5726, 5729, 5730);

DELETE FROM smart_scripts WHERE entryorguid IN (5702, 570200);
INSERT INTO smart_scripts VALUES
(5702, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 80, 570200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt - Animation"),
(5702, 0, 1, 0, 1, 0, 100, 0, 227500, 227500, 227500, 227500, 80, 570200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt - Animation"),
(570200, 9, 0, 0, 0, 0, 100, 0, 500, 500, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 1, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 2, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 3, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 5730, 3, 25000, 0, 0, 0, 8, 0, 0, 0, 1793.415527, 129.124390, -63.842342, 5.742132, "Jezelle Pruitt"),
(570200, 9, 4, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 5, 0, 0, 0, 100, 0, 24000, 24000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 6, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 7, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 8, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 5729, 3, 31000, 0, 0, 0, 8, 0, 0, 0, 1793.415527, 129.124390, -63.842342, 5.742132, "Jezelle Pruitt"),
(570200, 9, 9, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 10, 0, 0, 0, 100, 0, 29000, 29000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 11, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 12, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 13, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 5728, 3, 30000, 0, 0, 0, 8, 0, 0, 0, 1793.415527, 129.124390, -63.842342, 5.742132, "Jezelle Pruitt"),
(570200, 9, 14, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 15, 0, 0, 0, 100, 0, 28000, 28000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 16, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 17, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 18, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 5726, 3, 31000, 0, 0, 0, 8, 0, 0, 0, 1793.415527, 129.124390, -63.842342, 5.742132, "Jezelle Pruitt"),
(570200, 9, 19, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 20, 0, 0, 0, 100, 0, 29000, 29000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 21, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 22, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 23, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 5727, 3, 31000, 0, 0, 0, 8, 0, 0, 0, 1793.415527, 129.124390, -63.842342, 5.742132, "Jezelle Pruitt"),
(570200, 9, 24, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 25, 0, 0, 0, 100, 0, 29000, 29000, 0, 0, 11, 7794, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt"),
(570200, 9, 26, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Jezelle Pruitt");

DELETE FROM creature_text WHERE entry = 5702;
INSERT INTO creature_text VALUES
(5702, 0, 0, "Si vous êtes ici, cela signifie que vous êtes prêts à entamer une étude sur l'invocation des cohortes démoniaques en vue de réaliser votre union. Nous commencerons par les créatures les plus humbles que vous serez en mesure d'invoquer puis nous continuerons. Commençons.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 1, 0, "La créature que vous pourrez invoquer sans aucune difficulté est le diablotin. Vous devriez déjà être en mesure de créer ce serviteur, mais afin de vous délivrer un enseignement complet je vais commencer par lui.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 2, 0, "Cette ignoble petite créature est le diablotin. Il est petit et faible, et donc quasiment inutile en tant que bouclier de chair, et sa capacité à infliger des dégâts est au mieux médiocre. Il vaut mieux utiliser cette créature pour soutenir un groupe assez grand.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 3, 0, "Maintenant que vous avez eu la chance d'étudier un diablotin, passon au prochain serviteur que vous serez en mesure d'invoquer, le marcheur du Vide.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 4, 0, "Cette entité démoniaque est connue sous le nom de \"marcheur du Vide\". Sa force et son endurance, qui ne sont pas à négliger, sont parfaitement adaptées à la défense. Envoyez-la attaquer vos ennemis, puis utilisez-la comme un bouclier pendant que vous employez vos sorts et vos techniques pour drainer la vie hors du corps de votre adversaire.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 5, 0, "Si vous n'en avez jamais vu, c'est un spectacle à voir. Une créature très impressionnante, à la fois sur le champ de bataille et en dehors. A présent, jetons un oeil à celle que tous les étudiants mâles attendent. La succube.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 6, 0, "Voyons. Mis à part les diversions évidentes qu'une telle servante occasionnera envers vos ennemis mâles, elle est également capable de causer des dommages d'une ampleur impressionnante. Cependant, sa faible résistance la rend quasiment inutile en tant que bouclier.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 7, 0, "Etudiez assidûment, et un jour vous pourriez être capable d'en invoquer une par vous-même. Mais pour le moment, passons au chasseur corrompu.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 8, 0, "Ce que vous voyez devant vous est un chasseur corrompu. Les talents naturels de cette créature lui permettent de neutraliser des sorts. Ce talent, ainsi que d’autres capacités, la rendent sans égale face à un adversaires doté de pouvoirs magiques.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 9, 0, "Lorsque vous êtes face à un lanceur de sorts quelconque, cette bête sauvage est votre meilleur ami. Maintenant, intéressons-nous à quelque chose d'un peu différent. La créature suivante vous aidera à voyager et facilitera grandement vos futurs déplacements. Jetons un coup d'oeil sur un palefroi corrompu.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 10, 0, "Je ne pense pas que vous ayez eu de nombreuses occasions de voir une telle créature. Ces chevaux-démons rendront vos voyages beaucoup plus rapides si vous les utilisez comme montures. Du moins tant que vous pourrez les contrôler, ce qui n'est pas facile. Avant de faire une tentative, soyez sûrs d'être prêts.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt"),
(5702, 11, 0, "Voilà. Votre leçon sur l’invocation est terminée. Un nouveau cours est sur le point de commencer, alors si vous souhaitez réviser, n'hésitez pas à rester.", 0, 33, 100, 1, 0, 0, "Jezelle Pruitt");
