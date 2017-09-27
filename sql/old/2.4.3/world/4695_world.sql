UPDATE creature_template SET faction_a = 31, faction_h = 31, scale = 2 WHERE entry IN (18095, 18104);

DELETE FROM creature_scripts WHERE entryorguid = 18104;
INSERT INTO creature_scripts VALUES (18095, "mob_doomfire"), (18104, "mob_doomfire_targeting");
