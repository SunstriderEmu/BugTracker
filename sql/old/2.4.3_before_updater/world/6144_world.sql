# SPELL_ATTR_EX3_CANT_MISS for some illidan spells
UPDATE spell_template SET AttributesEx3 = 256 + 0x00040000 WHERE id = 40585;
UPDATE spell_template SET AttributesEx3 = 536870912 + 0x00040000 WHERE id = 41131;