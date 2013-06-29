UPDATE spell_affect SET SpellFamilyMask = 67109382|0x2800000 WHERE entry IN (14143, 14149); -- Hemorrage
UPDATE spell_affect SET SpellFamilyMask = SpellFamilyMask|0x600000000 WHERE entry IN (14143, 14149); -- Mutilate
