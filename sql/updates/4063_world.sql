DELETE FROM command WHERE name = "debug resetdaily";
INSERT INTO command VALUES ("debug resetdaily", 5, "DON'T TOUCH!!");

DELETE FROM creature_questrelation WHERE quest IN (9884, 9885, 9886, 9887);
INSERT INTO creature_questrelation VALUES (18265, 9884), (18265, 9885), (18265, 9886), (18265, 9887);

DELETE FROM creature_involvedrelation WHERE quest IN (9884, 9885, 9886, 9887);
INSERT INTO creature_involvedrelation VALUES (18265, 9884), (18265, 9885), (18265, 9886), (18265, 9887);

-- translation
UPDATE locales_quest SET OfferRewardText_loc2 = "Le Consortium est bien connu pour prendre bien soin de ses amis. Au début de chaque mois, j'aurai quelques gemmes prêtes pour vous, en paiement pour vos services.$B$BLa qualité des gemmes que vous obtiendrez dépendra de votre loyauté vis-à-vis de nous. J'espère que vous ferez le bon choix et resterez avec nous." WHERE entry IN (9884, 9885, 9886, 9887);
