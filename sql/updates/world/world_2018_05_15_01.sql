-- Add curse of Doom to Amplify Curse first effect
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x200000000 WHERE entry = 18288 and effectId = 0;
-- and remove it from the second
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask & ~0x200000000 WHERE entry = 18288 and effectId = 1;
