-- Add Devouring Plague to Force of Will
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x000002000000 WHERE entry = 18544 AND effectId = 2;