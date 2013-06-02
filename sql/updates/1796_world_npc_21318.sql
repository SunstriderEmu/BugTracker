DELETE FROM creature WHERE id = 21318; -- Prevent double spawn
INSERT INTO creature(id, map, spawnMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, DeathState, MovementType) VALUES(21318, 530, 1, 0, 0, -3794.74, 2591.79, 90.1176, 4.78548, 90, 0, 0, 11000, 0, 0, 0);
