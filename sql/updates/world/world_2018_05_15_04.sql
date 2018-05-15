-- Remove Shadow Mastery higher ranks
DELETE FROM spell_affect WHERE entry IN (18272, 18273, 18274, 18275);
-- Add Drain Soul to Shadow Mastery
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x4000 WHERE entry = 18271;