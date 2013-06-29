UPDATE creature_template_addon SET auras = "34840 0 34832 0" WHERE entry = 20086;
UPDATE creature_template_addon SET auras = "34858 0 34832 0" WHERE entry = 20114;

UPDATE creature_template SET flags_extra = flags_extra | 128 WHERE entry = 20114;
DELETE FROM creature WHERE id = 20114;
INSERT INTO creature (id, map, spawnMask, position_x, position_y, position_z, orientation, spawntimesecs, MovementType) VALUES
(20114, 530, 1, 3922.07, 3883.05, 177.676, 4.68181, 25, 0);
