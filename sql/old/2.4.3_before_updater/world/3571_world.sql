DELETE FROM creature WHERE id = 15625;
INSERT INTO creature (id, map, spawnmask, position_x, position_y, position_z, orientation, spawntimesecs, movementtype) VALUES (15625, 0, 1, -10328.915039, -488.423950, 50.034016, 2.934866, 868400, 0);
UPDATE creature_template SET minhealth=832750, maxhealth=832750, faction_A=14, faction_H=14 WHERE entry=15625;
