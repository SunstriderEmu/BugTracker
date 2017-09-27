DELETE FROM creature_template_addon WHERE entry = 25580;
INSERT INTO `creature_template_addon` (`entry`,`bytes2`,`emote`) VALUES (25580,1,379);
DELETE FROM creature_equip_template WHERE entry = 25580;
UPDATE creature_template SET equipment_id = 25580 WHERE entry = 25580;
INSERT INTO creature_equip_template (entry, equipmodel1) VALUES (25580, 20619);
