UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask | 0x200000000 WHERE entry IN (13733, 13865, 13866) AND effectId = 1;
