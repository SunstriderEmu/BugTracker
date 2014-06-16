#setting some alythess spells non resistible
UPDATE spell_template SET AttributesEx3 = AttributesEx3 + 0x00040000  WHERE id IN (45348,45342,45235,46771,45246) AND NOT AttributesEx3 & 0x00040000;