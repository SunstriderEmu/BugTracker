-- Add Vampiric Embrace to Shadow focus
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x4 WHERE entry = 15260 AND effectId = 0;