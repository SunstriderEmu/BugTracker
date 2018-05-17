-- Add chastise and SWD to Mental Agility
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x1000000000 | 0x200000000 WHERE  entry = 14520;
-- Delete higher ranks
DELETE FROM spell_affect WHERE entry IN (14780, 14781, 14782, 14783);