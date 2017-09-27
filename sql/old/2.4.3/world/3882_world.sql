UPDATE spell_template SET spellFamilyFlags1 = 1, spellFamilyFlags2 = 1 WHERE id = 20784;
INSERT INTO spell_affect VALUES
(19621, 0, 0x100000001),
(19622, 0, 0x100000001),
(19623, 0, 0x100000001),
(19624, 0, 0x100000001),
(19625, 0, 0x100000001);
INSERT INTO spell_proc_event (entry, procEx) VALUES (20784, 2);
