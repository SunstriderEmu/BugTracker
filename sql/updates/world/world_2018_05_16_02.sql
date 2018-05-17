-- Chastise threat
REPLACE INTO spell_threat VALUES (44041, 0, 0.5);

-- delete pw shield from spell_threat
DELETE FROM spell_threat WHERE entry IN (SELECT spell_id FROM spell_ranks WHERE first_spell_id = 17);