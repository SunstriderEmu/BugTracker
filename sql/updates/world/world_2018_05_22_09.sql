-- Darkness higher ranks
DELETE FROM spell_affect WHERE entry IN (15307, 15308, 15309, 15310);
-- Add Devouring Plague and Shadowguard
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x000002000000 WHERE entry = 15259 AND effectId = 1;