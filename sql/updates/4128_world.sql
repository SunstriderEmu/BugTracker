UPDATE spell_template SET spellFamilyFlags2 = 0x00000000, spellFamilyFlags1 = 0x80000000 WHERE id IN (635, 639, 647, 1026, 1042, 3472, 10328, 10329, 25292, 27135, 27136);

UPDATE spell_proc_event SET SpellFamilyMask = 0x80000000 WHERE entry IN (43741, 31833, 31835, 31836);
UPDATE spell_template SET spellFamilyFlags1 = 0, spellFamilyFlags2 = 0 WHERE id = 43741;

DELETE FROM spell_affect WHERE entry IN (20205, 20206, 20207, 20208, 20209);
