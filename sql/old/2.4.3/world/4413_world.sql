DELETE FROM creature_equip_template WHERE entry = 23863;
INSERT INTO creature_equip_template (entry, equipmodel1, equipinfo1) VALUES (23863, 47174, 218172674);

UPDATE creature_template SET equipment_id = 23863 WHERE entry = 23863;
