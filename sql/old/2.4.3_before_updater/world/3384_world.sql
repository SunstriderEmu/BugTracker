DELETE FROM gameobject WHERE id = 184247 AND map = 229;
INSERT INTO gameobject (id, map, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state) VALUES
(184247, 229, 216.392, -288.488, 76.9463, 0.00122643, 0, 0, 0.000613213, 1, 25, 0, 1);

UPDATE gameobject_template SET data2 = 0, flags = 36 WHERE entry = 184247;

DELETE FROM gameobject WHERE id = 170556 AND map = 229;
INSERT INTO gameobject (id, map, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state) VALUES
(170556, 229, 126.1, -319.069, 70.9562, 6.27937, 0, 0, 0.00190607, -0.999998, 25, 0, 1);

-- Don't lock door for now, questline for the key is not ready
-- UPDATE gameobject_template SET data2 = 0, data1 = 820, flags = 34 WHERE entry = 170556;

DELETE FROM gameobject WHERE id BETWEEN 175194 AND 175200 AND map = 229;
INSERT INTO gameobject (id, map, position_x, position_y, position_z, orientation, rotation2, rotation3, spawntimesecs, state) VALUES
(175194, 229, 192.74, -258.394, 76.8603, 0, 0, 1, 25, 1),
(175195, 229, 125.354, -340.439, 70.8575, 0.78996, 0.38479, 0.923004, 25, 1),
(175196, 229, 228.831, -301.556, 76.8603, 3.13569, 0.999996, 0.00294931, 25, 1),
(175197, 229, 124.769, -298.064, 70.8575, 5.49244, 0.385152, -0.922853, 25, 1),
(175198, 229, 215.15, -334.7, 76.8603, 2.36295, 0.925166, 0.379562, 25, 1),
(175199, 229, 155.329, -286.063, 70.8575, 4.73484, 0.699125, -0.715, 25, 1),
(175200, 229, 155.315, -353.047, 70.8575, 1.58932, 0.713625, 0.700528, 25, 1);

UPDATE instance_template SET script = "instance_blackrock_spire" WHERE map = 229;

DELETE FROM gameobject WHERE id BETWEEN 175266 AND 175272;
INSERT INTO gameobject (id, map, position_x, position_y, position_z, orientation, rotation2, rotation3, spawntimesecs, state) VALUES
(175266, 229, 162.408, -276.862, 91.45, 1.57336, 0.708012, 0.7062, 25, 1),
(175267, 229, 162.437, -258.995, 91.45, 1.52472, 0.690629, 0.723209, 25, 1),
(175268, 229, 162.391, -240.691, 91.45, 1.56988, 0.706783, 0.707431, 25, 1),
(175269, 229, 144.352, -240.814, 91.45, 3.14548, 0.999998, -0.00194232, 25, 1),
(175270, 229, 126.39, -240.717, 91.45, 3.14046, 1, 0.000566558, 25, 1),
(175271, 229, 126.348, -258.739, 91.45, 4.71104, 0.707584, -0.706629, 25, 1),
(175272, 229, 126.312, -276.781, 91.45, 4.71191, 0.707276, -0.706937, 25, 1);

DELETE FROM spell_script_target WHERE entry = 16068;
INSERT INTO spell_script_target VALUES (16068, 1, 9816);


