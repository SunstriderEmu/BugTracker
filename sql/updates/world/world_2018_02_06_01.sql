
-- fixed some more wrong spell_proc's
UPDATE spell_proc SET SpellFamilyMask = 64 WHERE SpellId = 28744;
UPDATE spell_proc SET SpellFamilyMask = 192 WHERE SpellId = 28823;
UPDATE spell_proc SET SpellFamilyMask = 128 WHERE SpellId = 28849;
UPDATE spell_proc SET SpellFamilyMask = 4096 WHERE SpellId = 37594;