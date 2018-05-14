-- Add curse of Doom to Contagion talent
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x200000000 WHERE entry = 18174;
