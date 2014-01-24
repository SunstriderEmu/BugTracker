/* Removing wrong SPELL_ATTR_EX2_BEHIND_TARGET flag for some spells */
UPDATE spell_template SET AttributesEx2 = 0 WHERE id IN (1833,5938,20271);