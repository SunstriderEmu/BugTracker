-- kara opera doors and curtain
UPDATE gameobject SET spawntimesecs = 0 WHERE id IN (184278, 183932, 24919);
-- remove decor, spawned via script now
DELETE FROM gameobject WHERE id IN (183496,183442);