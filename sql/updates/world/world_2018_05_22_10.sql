-- Add Mind Flay to Misery
UPDATE spell_proc SET SpellFamilyMask = SpellFamilyMask | 0x800000 WHERE SpellId = -33191;