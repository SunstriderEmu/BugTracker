UPDATE spell_template SET spellFamilyFlags1 = 1, spellFamilyFlags2 = 1 WHERE id IN (635, 639, 647, 1026, 1042, 3472, 10328, 10329, 25292, 27135, 27136, 31833, 31835, 31836); -- Was 0, 0
UPDATE spell_proc_event SET SpellFamilyMask = 0x100000001 WHERE entry IN (31833, 31835, 31836); -- Was 0x80000000
