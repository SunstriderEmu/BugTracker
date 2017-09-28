UPDATE creature_template SET type_flags = type_flags | 0x80 WHERE entry IN (8888, 9299);
UPDATE creature_template SET flags_extra = flags_extra | 0x80000 WHERE entry IN (8888, 9299);
