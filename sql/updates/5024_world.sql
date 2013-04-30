/* door next chess : no more despawn */
UPDATE gameobject_template SET flags = 0x20 WHERE entry = 184276;

/* civilian flag  for Calliard*/
UPDATE creature_template SET flags_extra = 2 WHERE entry = 16159;

/* npc at the forge*/
UPDATE `creature` SET `position_x` = '-11091.8', `position_y` = '-1912.28', `position_z` = '49.8527', `orientation` = '5.59909' WHERE guid = 85376;
UPDATE `creature` SET `position_x` = '-11097.2', `position_y` = '-1902.25', `position_z` = '49.8454', `orientation` = '5.12707' WHERE guid = 85377;
DELETE FROM creature_addon WHERE guid = 85376
OR guid = 85377;
INSERT INTO creature_addon (guid,emote) VALUES (85376,233);
INSERT INTO creature_addon (guid,emote) VALUES (85377,233);

UPDATE `creature` SET `id` = '16407',`position_x` = '-11090.9', `position_y` = '-1914.67', `position_z` = '49.8472', `orientation` = '2.82' WHERE guid = 85347;
UPDATE `creature` SET `id` = '16407',`position_x` = '-11096', `position_y` = '-1904.26', `position_z` = '49.8548', `orientation` = '2.14' WHERE guid = 85344;
UPDATE `creature` SET `id` = '16407',`position_x` = '-11099.2', `position_y` = '-1900.9', `position_z` = '49.8482', `orientation` = '0.97' WHERE guid = 85343;

/* Adding some models to spectral npcs */
UPDATE `creature_template` SET `modelid_A2` = '16440', `modelid_H2` = '16441', `equipment_id` = '429' WHERE `entry` = '16389'; 
UPDATE `creature_template` SET `modelid_A2` = '16487', `modelid_H2` = '16488' WHERE `entry` = '16407';
UPDATE `creature_template` SET `modelid_A2` = '16399', `modelid_H2` = '16400' WHERE `entry` = '15551';
UPDATE `creature_template` SET `modelid_A2` = '16496', `modelid_H2` = '16497' WHERE `entry` = '16408';
UPDATE `creature_template` SET `modelid_A2` = '16466', `modelid_H2` = '16467' WHERE `entry` = '16409';