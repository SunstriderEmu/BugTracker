UPDATE spell_template SET spellFamilyFlags1 = 1, spellFamilyFlags2 = 1 WHERE id = 43741;
UPDATE spell_proc_event SET SpellFamilyMask = 0x100000001 WHERE entry = 43741;
