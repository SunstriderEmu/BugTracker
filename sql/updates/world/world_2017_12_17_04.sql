-- Blood furnace change :

-- Delete db Broggok orcs
DELETE FROM creature WHERE position_x > 400 AND position_x < 510 AND position_y > 76 AND position_y < 123 AND id IN (17429, 17398);
UPDATE creature_template SET unit_flags = 0x1 WHERE entry IN (17429, 17398);
UPDATE creature_template SET ArmorModifier = 1 WHERE entry IN (17377, 17371, 17414, 17395, 17380);