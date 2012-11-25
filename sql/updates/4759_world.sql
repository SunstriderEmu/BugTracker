UPDATE creature_template SET AIName = '', ScriptName = '' WHERE entry IN (25319, 25315, 25608, 25588, 25603, 25598, 25735, 25502, 25708);

DELETE FROM creature_scripts WHERE entryorguid IN (25319, 25315, 25608, 25588, 25603, 25598, 25735, 25502, 25708);
INSERT INTO creature_scripts VALUES (25319, 'boss_kalecgos_kj');
INSERT INTO creature_scripts VALUES (25315, 'boss_kiljaeden');
INSERT INTO creature_scripts VALUES (25608, 'mob_kiljaeden_controller');
INSERT INTO creature_scripts VALUES (25588, 'mob_hand_of_the_deceiver');
INSERT INTO creature_scripts VALUES (25603, 'mob_felfire_portal');
INSERT INTO creature_scripts VALUES (25598, 'mob_volatile_felfire_fiend');
INSERT INTO creature_scripts VALUES (25735, 'mob_armageddon');
INSERT INTO creature_scripts VALUES (25502, 'mob_shield_orb');
INSERT INTO creature_scripts VALUES (25708, 'mob_sinster_reflection');

/* Hand of the Deceiver equip*/
DELETE FROM `creature_equip_template` WHERE entry = 3004;
INSERT INTO `creature_equip_template` (`entry`, `equipmodel1`) VALUES (3004, 47994);

UPDATE creature_template SET minhealth = 206000, maxhealth = 206000, minmana = 165450, maxmana = 165450,  mechanic_immune_mask = 65616, speed = 1.71, equipment_id = 3004 WHERE entry = 25588;
