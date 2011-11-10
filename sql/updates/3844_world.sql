UPDATE spell_proc_event SET procEx = procEx | 0x40 WHERE entry = 40407;
DELETE FROM spell_proc_event WHERE entry = 39444;
INSERT INTO spell_proc_event (entry, procEx) VALUES (39444, 0x40);
