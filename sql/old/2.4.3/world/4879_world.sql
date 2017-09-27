UPDATE spell_template SET procflags = procflags & ~0x800000 WHERE id IN (14186, 14190, 14193, 14194, 14195);
UPDATE spell_proc_event SET SpellFamilyMask = SpellFamilyMask | 0x200000000 WHERE entry IN (14186, 14190, 14193, 14194, 14195);
UPDATE spell_proc_event SET SpellFamilyMask = SpellFamilyMask | 0x400000000 WHERE entry IN (14186, 14190, 14193, 14194, 14195);
UPDATE spell_proc_event SET SpellFamilyMask = SpellFamilyMask | 0x20000000 WHERE entry IN (14186, 14190, 14193, 14194, 14195);
