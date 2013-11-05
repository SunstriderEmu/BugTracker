#Fixed some moar sunwell creatures radiance
REPLACE INTO creature_template_addon (entry,auras) VALUES (25486,"45769 0 45769 1");
REPLACE INTO creature_template_addon (entry,auras) VALUES (25483,"45769 0 45769 1");
REPLACE INTO creature_template_addon (entry,auras) VALUES (25506,"45769 0 45769 1");
REPLACE INTO creature_template_addon (entry,auras) VALUES (25373,"45769 0 45769 1");

DELETE FROM eventai_scripts WHERE id IN (2550901,2559501,2559701,2559901,2586701);
DELETE FROM smartscripts WHERE entryorguid = 25948;
