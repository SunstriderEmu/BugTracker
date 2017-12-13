-- Remove SPELL_SCHOOL_MASK_NORMAL from custom spell Magic immunity
UPDATE spell_template SET effectMiscValue1 = 126 WHERE entry = 53100;