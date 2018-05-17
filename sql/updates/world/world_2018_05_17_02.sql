-- Add chastise and SWD to Mental Agility
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x1000000000 | 0x200000000 WHERE  entry = 14520;