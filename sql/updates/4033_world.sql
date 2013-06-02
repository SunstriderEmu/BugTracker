UPDATE creature_template SET maxhealth = 21881 WHERE entry = 18615;
UPDATE creature_template SET mindmg = 8000, maxdmg = 9000, attackpower = ROUND((`mindmg` + `maxdmg`) / 4 * 7), mindmg = ROUND(`mindmg` - `attackpower` / 7), maxdmg = ROUND(`maxdmg` - `attackpower` / 7) WHERE entry = 18615;

UPDATE creature_template SET minhealth = 27000, maxhealth = 28000 WHERE entry = 21645;
UPDATE creature_template SET equipment_id = 18894 WHERE entry IN (18894, 21645);
DELETE FROM creature_equip_template WHERE entry = 18894;
INSERT INTO creature_equip_template (entry, equipmodel1) VALUES (18894, 19664);

UPDATE creature_template SET minhealth = 11000, maxhealth = 12000 WHERE entry = 18620;
UPDATE spell_template SET procFlags = 0 WHERE id = 30937; -- Was 139936

UPDATE creature_template SET maxhealth = 8000 WHERE entry = 18606;
UPDATE spell_template SET effectBasePoints1 = 300 WHERE id = 15242; -- Was 159
UPDATE spell_template SET effectBasePoints1 = 520 WHERE id = 17290; -- Was 254


