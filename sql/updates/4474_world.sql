/* Buru the Gorger */
DELETE FROM creature_scripts WHERE entryorguid = 15370;
INSERT INTO creature_scripts VALUES (15370, 'boss_buru');

/* Buru Egg */
DELETE FROM creature_scripts WHERE entryorguid = 15514;
INSERT INTO creature_scripts VALUES (15514, 'buru_egg');

/* Buru Egg Trigger*/
DELETE FROM creature_scripts WHERE entryorguid = 15964;
INSERT INTO creature_scripts VALUES (15964, 'buru_egg_trigger');

/* Buru Egg Spawn */
UPDATE creature SET id = 15514, spawntimesecs = 30 WHERE id = 15521;
