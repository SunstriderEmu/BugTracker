UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x200000000 WHERE entry IN (31234, 31235, 31236, 31237, 31238) AND effectId = 0;
