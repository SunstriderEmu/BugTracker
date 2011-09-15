UPDATE creature_template SET speed = 2 WHERE entry = 25165;
UPDATE creature_template SET speed = 1.5 WHERE entry = 25214;

INSERT INTO creature_equip_template (entry, equipmodel1, equipinfo1, equipslot1) VALUES (25581, 33069, 33492738, 871);
UPDATE creature_template SET equipment_id = 25581 WHERE entry = 25165;

INSERT INTO creature_equip_template (entry, equipmodel1, equipinfo1, equipslot1) VALUES (25582, 32648, 33492738, 871);
UPDATE creature_template SET equipment_id = 25582 WHERE entry = 25214;
