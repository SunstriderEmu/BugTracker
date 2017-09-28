DELETE FROM creature_template_addon WHERE entry = 23188;
INSERT INTO creature_template_addon (entry, mount, bytes1, moveflags) VALUES (23188, 16314, 1, 1024);

DELETE FROM creature WHERE id = 23188;
INSERT INTO creature (id, map, spawnMask, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, movementtype) VALUES
(23188, 530, 1, -4587.59, 34.7017, 226.164, 0.0133414, 60, 15, 1),
(23188, 530, 1, -4497.08, -46.6537, 201.992, 2.10577, 60, 15, 1),
(23188, 530, 1, -4503.96, 44.5636, 215.904, 3.40539, 60, 15,1),
(23188, 530, 1, -4924.68, 35.4741, 78.7984, 3.72327, 60, 15, 1),
(23188, 530, 1, -4726.65, 114.537, 93.8158, 6.23218, 60, 15, 1),
(23188, 530, 1, -4676.44, 167.757, 94.4119, 3.96412, 60, 15, 1),
(23188, 530, 1, -4698.28, 287.738, 91.9575, 2.76399, 60, 15, 1),
(23188, 530, 1, -4877.17, 128.309, 49.187, 2.63854, 60, 15, 1),
(23188, 530, 1, -5010.76, -60.4384, 81.571, 1.2737, 60, 15, 1),
(23188, 530, 1, -4882.29,  223.83, 65.1555, 3.46648, 60, 15, 1);

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 23188;
DELETE FROM smart_scripts WHERE entryorguid = 23188;
INSERT INTO smart_scripts VALUES
(23188, 0, 0, 0, 0, 0, 100, 0, 1000, 1000, 15000, 20000, 11, 38859, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Serpent Sting on target"),
(23188, 0, 1, 0, 0, 0, 100, 0, 6000, 12000, 20000, 25000, 11, 38861, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Aimed Shot at target"),
(23188, 0, 2, 0, 0, 0, 100, 0, 2000, 2000, 2000, 2000, 11, 38858, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Shoot at target"),
(23188, 0, 3, 0, 0, 0, 100, 0, 15000, 20000, 35000, 40000, 11, 19503, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Scatter Shot");
