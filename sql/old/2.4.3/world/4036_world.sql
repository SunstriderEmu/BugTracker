UPDATE creature_template SET maxhealth = 8000 WHERE entry = 18614;

UPDATE creature_template SET maxhealth = 19750 WHERE entry = 18618;
UPDATE eventai_texts SET content_loc2 = "commence à armer la bombe de proximité !" WHERE entry = -155;

UPDATE creature_template SET minhealth = 13500, maxhealth = 14000 WHERE entry = 18610;
UPDATE creature SET spawntimesecs = 3600 WHERE id = 17491;
DELETE FROM creature_equip_template WHERE entry = 17491;
INSERT INTO creature_equip_template (entry, equipmodel1, equipmodel2) VALUES (17491, 20502, 20502);
UPDATE creature_template SET equipment_id = 17491 WHERE entry IN (17491, 18610);
UPDATE eventai_scripts SET action1_param3 = 1 WHERE id = 1749105;

UPDATE creature_template SET maxhealth = 28500 WHERE entry = 18604;
UPDATE creature_template SET faction_a = 14, faction_h = 14 WHERE entry IN (17400, 18604);

UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181812';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181822';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181819';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181811';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181821';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181820';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181818';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181817';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181814';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181813';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181816';
UPDATE `gameobject_template` SET `flags` = '4' WHERE `entry` = '181815';

DELETE FROM gameobject WHERE id = 181982;
INSERT INTO gameobject VALUES ('', 181982, 542, 1, 455.872, 60.019, 9.61521, 6.21872, 0, 0, 0.032229, -0.99948, 25, 0, 1);
INSERT INTO gameobject VALUES ('', 181982, 542, 2, 455.872, 60.019, 9.61521, 6.21872, 0, 0, 0.032229, -0.99948, 25, 0, 1);

UPDATE `gameobject_template` SET `type` = '1' WHERE `entry` = '181982';
UPDATE `gameobject_template` SET `ScriptName` = 'go_prison_cell_lever' WHERE `entry` = '181982';

UPDATE `creature_template` SET `ScriptName` = 'mob_nascent_orc' WHERE `entry` = '17398';
UPDATE `creature_template` SET `unit_flags` = '33554434' WHERE entry = '17398';
UPDATE `creature_template` SET `flags_extra` = '2' WHERE entry = '17398';
UPDATE `creature_template` SET `unit_flags` = '33554434' WHERE entry = '18612';
UPDATE `creature_template` SET `flags_extra` = '2' WHERE entry = '18612';
UPDATE `creature_template` SET `unit_flags` = '2' WHERE entry = '17380';
UPDATE `creature_template` SET `unit_flags` = '2' WHERE entry = '18601';
UPDATE `creature_template` SET `ScriptName` = 'mob_broggok_poisoncloud' WHERE `entry` = '17662';
UPDATE `creature_template` SET `unit_flags` = '131072' WHERE `entry` = '17662';
UPDATE `creature_template` SET `flags_extra` = '128' WHERE entry = '17662';

