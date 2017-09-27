-- Cleanup
DELETE FROM spell_proc_event WHERE entry IN (33297, 33370, 38348, 34321, 18350, 42084, 60066, 33649, 60061, 33370, 32848, 39959, 33511, 33513, 38299, 38324, 28578, 34585, 34598, 34597);

-- Quagmirran's Eye http://www.wowhead.com/item=27683
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (33297, 45);

-- Sextant of Unstable Currents http://www.wowhead.com/item=30626
UPDATE spell_proc_event SET cooldown = 45 WHERE entry = 38347;
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (38348, 45);

-- Shiffar's Nexus-Horn http://www.wowhead.com/item=28418
UPDATE spell_proc_event SET cooldown = 45 WHERE entry = 34320;
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (34321, 45);

-- The Lightning Capacitor http://www.wowhead.com/item=28785
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (18350, 3);

-- Tsunami Talisman http://www.wowhead.com/item=30627
UPDATE spell_proc_event SET cooldown = 45 WHERE entry = 42083;
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (42084, 45);

-- Hourglass of the Unraveller http://www.wowhead.com/item=28034
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (60066, 45);
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (33649, 45);

-- Scarab of the Infinite Cycle http://www.wowhead.com/item=28190
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (60061, 45);
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (33370, 45);

-- Insightful Earthstorm Diamond http://www.wowhead.com/item=25901
UPDATE spell_proc_event SET cooldown = 15 WHERE entry = 27521;
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (32848, 15);

-- Thundering Skyfire Diamond http://www.wowhead.com/item=32410
UPDATE spell_proc_event SET cooldown = 40 WHERE entry = 39958;
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (39959, 40);

-- Mark of Defiance http://www.wowhead.com/item=27924
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (33511, 15);
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (33513, 15);

-- Fel Reaver's Piston http://www.wowhead.com/item=30619
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (38299, 15);
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (38324, 15);

-- Masquerade Gown http://www.wowhead.com/item=28578
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (28578, 45);
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (34585, 45);

-- Robe of the Elder Scribes http://www.wowhead.com/item=28602
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (34598, 45);
INSERT INTO spell_proc_event (entry, Cooldown) VALUES (34597, 45);
