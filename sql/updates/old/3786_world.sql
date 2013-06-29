DELETE FROM spell_affect WHERE entry IN (11189, 28332);
INSERT INTO spell_affect VALUES (11189, 0, 0x80100);
INSERT INTO spell_affect VALUES (28332, 0, 0x80100);

DELETE FROM spell_affect WHERE entry IN (11094, 13043);
INSERT INTO spell_affect VALUES (11094, 1, 0x8);
INSERT INTO spell_affect VALUES (13043, 1, 0x8);
