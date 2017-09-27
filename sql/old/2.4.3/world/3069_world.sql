DELETE FROM spell_proc_event WHERE entry IN (18073, 18350, 18093, 18096);
INSERT INTO spell_proc_event (entry, SpellFamilyName, SpellFamilyMask, procFlags, customchance) VALUES (18096, 5, 0x0000006000000080, 0x11001, 13);
INSERT INTO spell_proc_event (entry, SpellFamilyName, SpellFamilyMask, procFlags, customchance) VALUES (18073, 5, 0x0000006000000080, 0x11001, 26);
INSERT INTO spell_proc_event (entry, cooldown) VALUES (18093, 3);
