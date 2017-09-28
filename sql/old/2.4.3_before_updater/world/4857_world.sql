UPDATE creature_model_info SET bounding_radius = 11.0, combat_reach = 11.0 WHERE modelid = 23200;
DELETE FROM command WHERE name IN ('npcevent enable', 'npcevent disable', 'npcevent schedule');
INSERT INTO command VALUES ('npcevent enable', 2, 'Usage: .npcevent enable $eventid');
INSERT INTO command VALUES ('npcevent disable', 2, 'Usage: .npcevent disable $eventid');
INSERT INTO command VALUES ('npcevent schedule', 2, 'Usage: .npcevent schedule $eventid $timer');
