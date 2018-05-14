-- Add curse of Doom to Improved Drain Soul
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x200000000 WHERE entry = 18213;
DELETE FROM spell_affect WHERE entry = 18372;