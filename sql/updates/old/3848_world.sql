DELETE FROM script_texts WHERE entry BETWEEN -1000516 AND -1000507;
INSERT INTO script_texts (entry, content_default, content_loc2, comment) VALUES
(-1000507, "Ok, let's get started.", "Ok, c'est parti.", "stinky - quest accepted"),
(-1000508, "Now let's look for the herb.", "Maintenant, trouvons cette herbe.", "stinky - say1"),
(-1000509, "Nope, not here...", "Non, pas ici...", "stinky - say2"),
(-1000510, "There must be one around here somewhere...", "Il doit y en avoir une quelque part par ici...", "stinky - say3"),
(-1000511, "Ah, there's one!", "Ah, en voilà une !", "stinky - say4"),
(-1000512, "Come, $N! Let's go over there and collect it!", "Venez, $N ! Allons là-bas en cueillir !", "stinky - say5"),
(-1000513, "Ok, now let's get out of here!", "Ok, maintenant allons-nous en d'ici", "stinky - say6"),
(-1000514, "I can make it from here. Thanks, $N! And talk to my employer about a reward!", "Je peux me débrouiller à partir d'ici. Merci, $N ! Et parlez à mon employeur pour votre récompense !", "stinky - quest complete"),
(-1000515, "Help! The beast is on me!", "A l'aide ! La bête est sur moi !", "stinky - aggro"),
(-1000516, "\"Stinky\" Ignatz disappears back into the swamp.", "Ignatz « Puant » disparaît dans le marécage.", "stinky - emote disapper");
