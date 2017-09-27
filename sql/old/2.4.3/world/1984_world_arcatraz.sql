-- --------------
-- Explode first huge pack in smaller ones
-- --------------

-- Despawn extra mobs
DELETE FROM creature WHERE guid IN (79402, 79399, 79400, 79395);

-- Replace others
UPDATE creature SET position_x = 173.5389, position_y = -0.3824, position_z = -10.1013 WHERE guid = 79444;
UPDATE creature SET position_x = 175.7707, position_y = -3.5390, position_z = -10.1013 WHERE guid = 79432;
UPDATE creature SET position_x = 170.5036, position_y = -4.4449, position_z = -10.0848 WHERE guid = 79427;
UPDATE creature SET position_x = 170.6174, position_y = 3.4659, position_z = -10.0909 WHERE guid = 79434;
UPDATE creature SET position_x = 175.6993, position_y = 3.0086, position_z = -10.0892 WHERE guid = 79445;

UPDATE creature SET position_x = 154.2604,  position_y = -0.0079, position_z = -10.1021 WHERE guid = 79415;
UPDATE creature SET position_x = 150.9527, position_y = 4.6199, position_z = -10.1021 WHERE guid = 79442;
UPDATE creature SET position_x = 150.9232, position_y = 2.2751, position_z = -10.1021 WHERE guid = 79417;
UPDATE creature SET position_x = 150.8936, position_y = -0.0696, position_z = -10.1021 WHERE guid = 79422;
UPDATE creature SET position_x = 150.8631, position_y = -2.4915, position_z = -10.1021 WHERE guid = 79436;

UPDATE creature SET position_x = 130.0231, position_y = 0.1496, position_z = -10.1021 WHERE guid = 79430;
UPDATE creature SET position_x = 127.2721, position_y = 0.1358, position_z = -10.1021 WHERE guid = 79413;
UPDATE creature SET position_x = 126.1866, position_y = -2.4178, position_z = -10.1021 WHERE guid = 79446;
UPDATE creature SET position_x = 125.4820, position_y = 2.3301, position_z = -10.1021 WHERE guid = 79439;
UPDATE creature SET position_x = 128.7529, position_y = 2.0231, position_z = -10.1021 WHERE guid = 79443;

UPDATE creature SET position_x = 104.2831, position_y = 5.2377, position_z = -10.1724 WHERE guid = 79401;
UPDATE creature SET position_x = 108.4682, position_y = 5.6821, position_z = -10.1724 WHERE guid = 79410;

-- Dead sentinel auras shouldn't be mobs
DELETE FROM creature WHERE id = 21761;

-- Pack of 6 sentinels - WTF ?
DELETE FROM creature WHERE guid IN (86055, 86054, 86059, 86056, 86057, 86058);

-- Final pack
UPDATE creature SET position_x = 472.4610, position_y = -72.1883, position_z = 48.3955 WHERE guid = 79577;
UPDATE creature SET position_x = 471.4412, position_y = -74.9457, position_z = 48.3955 WHERE guid = 79578;

UPDATE creature SET position_x = 422.4971, position_y = -66.1620, position_z = 48.3955 WHERE guid = 79575;
UPDATE creature SET position_x = 423.4712, position_y = -71.4808, position_z = 48.3955 WHERE guid = 79576;

-- Cieuriss' clones
UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry IN (21466, 21467);
