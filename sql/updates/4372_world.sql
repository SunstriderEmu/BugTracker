UPDATE areatrigger_teleport SET target_orientation = 2.6945 WHERE id = 4008;

DELETE FROM creature_scripts WHERE entryorguid = 15348;
INSERT INTO creature_scripts VALUES (15348, "boss_kurinaxx_new");

UPDATE gameobject_template SET data5 = 5 WHERE entry = 180647;
