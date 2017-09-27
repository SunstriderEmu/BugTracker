DELETE FROM eventai_scripts WHERE id IN (2559301,2550801);
UPDATE creature_template_addon SET auras = "45769 0 45769 1" WHERE entry IN (25367,25370,25371,25363);

UPDATE creature_addon SET auras = "45769 0 45769 1" 
WHERE guid IN (select guid from creature where id IN (25486,25483,25506,25373,25367,25370,25371,25363));

UPDATE spell_template SET AttributesEx3 = 0x00040000 WHERE id = 27173;

REPLACE INTO creature_template_addon (entry, mount) values (17948,6074);
# arc
UPDATE creature_template set equipment_id = 812 WHERE entry = 17943;