#really setting Divine Wrath as interruptible
UPDATE spell_template SET preventionType = 1 WHERE id = 41472;

UPDATE trinity_string SET content_loc2 = "La quête est reconnue comme bugguée et est marquée pour être auto-complétée, elle ne rapportera cependant pas d'argent ou d'expérience." WHERE entry =  11900;