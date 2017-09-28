UPDATE creature_template SET mindmg = 6650, maxdmg = 20000 WHERE entry = 25599;
UPDATE creature_template SET mindmg = 2500, maxdmg = 20000 WHERE entry = 25595;
DELETE FROM spell_target_position WHERE id = 46883;
INSERT INTO spell_target_position VALUES (46883, 580, 1823.103271, 644.404907, 33.403900, 1.220804);
