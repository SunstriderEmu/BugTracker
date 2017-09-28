UPDATE spell_proc_event SET SpellFamilyMask = 0xFFFFFFFF WHERE entry IN (29180, 29179, 30160);
UPDATE spell_proc_event SET SpellFamilyMask = SpellFamilyMask & ~0x200000 WHERE entry IN (29180, 29179, 30160);
