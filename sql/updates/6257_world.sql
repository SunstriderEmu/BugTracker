#Tranquility healing effect should not be affected by LoS
UPDATE spell_template SET AttributesEx2 = 0x60000000 + 0x004 WHERE id IN (44203,44205,44206,44207,44208);