-- shadow focus, delete higher ranks
UPDATE spell_affect SET SpellFamilyMask = 4681624166400 WHERE entry = 15260;
DELETE FROM spell_affect WHERE entry IN (15327, 15328, 15329, 15330);