UPDATE creature_template SET mindmg = 11800, maxdmg = 13700, attackpower = 19250 WHERE entry = 25165;
UPDATE creature_template SET armor = 6200 WHERE entry IN (25165, 25166, 25038, 24850, 24892, 25315);
UPDATE creature_template SET armor = 7700 WHERE entry IN (24882, 25741, 25840);
UPDATE creature_template SET mechanic_immune_mask = 1024 WHERE entry = 25214;
UPDATE creature_equip_template SET equipmodel2 = 33069, equipinfo2 = 33492738, equipslot2 = 871 WHERE entry = 25581;
