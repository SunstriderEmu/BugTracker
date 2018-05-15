-- Add curse of Doom to Grim Reach
DELETE FROM spell_affect WHERE entry = 18219;
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x200000000 WHERE entry = 18218 and effectId = 0;
