UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x800000 WHERE entry BETWEEN 20101 AND 20105;

DELETE FROM creature_scripts WHERE entryorguid = 18104;
INSERT INTO creature_scripts VALUES (18095, "mob_doomfire"), (18104, "mob_doomfire_targeting");
