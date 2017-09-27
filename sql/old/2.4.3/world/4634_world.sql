INSERT INTO creature_questrelation VALUES
(4485, 1361),
(10540, 1361);

UPDATE creature_template SET ScriptName = "npc_aged_dying_ancient_kodo" WHERE entry = 4702;

DELETE FROM escort_waypoints WHERE entry = 12277;
INSERT INTO escort_waypoints (entry, pointid, location_x, location_y, location_z) VALUES
(12277, 0, -1166.174927, 2715.101807, 111.956856),
(12277, 1, -1259.092773, 2673.001953, 111.565979),
(12277, 2, -1291.352783, 2643.750732, 111.556122),
(12277, 3, -1356.462891, 2569.171631, 111.556671),
(12277, 4, -1365.443237, 2555.130371, 108.894249),
(12277, 5, -1383.299438, 2488.166992, 88.890526),
(12277, 6, -1388.648682, 2449.074219, 88.439545),
(12277, 7, -1411.870239, 2404.333008, 88.947990);

UPDATE creature_template SET ScriptName = "npc_melizza" WHERE entry = 12277;
UPDATE quest_template SET method = 0 WHERE entry IN (5821, 5943);
