-- Delete higher ranks of Silent Resolve
DELETE FROM spell_affect WHERE entry IN (14784, 14785, 14786, 14787);

-- resist dispell effect
REPLACE INTO spell_affect VALUES (14523, 1, 0x7FFFFFFFFFFFFF);
-- threat reduction effect
REPLACE INTO spell_affect VALUES (14523, 2, 0x1 | 01000000000 | 0x10000000 | 0x1000000 | 0x800 | 0x1000 | 0x400 | 0x100000 | 0x40000 | 0x200 | 0x200000 | 0x40 | 0x80);
