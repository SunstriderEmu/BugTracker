/* Remove SPELL_ATTR_EX2_BEHIND_TARGET from Pounce */
UPDATE spell_template SET attributesEx2 = 0 WHERE spellFamilyFlags1 = 0x0000000000020000 AND spellFamilyName = 7;