DELETE FROM creature WHERE id = 23081;
INSERT INTO creature (id, map, position_x, position_y, position_z, orientation, spawntimesecs) VALUES
(23081, 530, 3304.414307, 4644.131348, 216.634796, 3.173299, 10),
(23081, 530, 3292.766113, 4619.867188, 216.674759, 2.209869, 10),
(23081, 530, 3261.655762, 4625.360352, 216.624985, 0.774776, 10),
(23081, 530, 3257.306885, 4653.872559, 216.631027, 5.803508, 10),
(23081, 530, 3279.442139, 4664.499023, 216.160980, 4.694584, 10);

UPDATE creature_template SET flags_extra = flags_extra | 128, inhabittype = 5 WHERE entry = 23081;

DELETE FROM spell_script_target WHERE entry = 39921;
INSERT INTO spell_script_target VALUES (39921, 1, 23081);
