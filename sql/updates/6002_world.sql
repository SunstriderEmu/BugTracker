UPDATE VERSION SET core_version = "Winrunner Rev: 6002";

UPDATE trinity_string 
SET content_loc2 = "La quête est actuellement marquée comme irréalisable et a été auto-validée, mais ne vous offrira pas de récompenses d'XP ou d'argent."
WHERE entry = 11900;
