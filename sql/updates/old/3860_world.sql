UPDATE creature_template SET AIName = "", ScriptName = "npc_grulloc" WHERE entry = 20216;
UPDATE creature_template SET ScriptName = "npc_huffer" WHERE entry = 22114;

DELETE FROM waypoint_data WHERE id = 22114;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, move_flag) VALUES
(22114, 0, 2671.650146, 5574.037598, -10.568995, 1),
(22114, 1, 2703.128662, 5617.739258, -10.832470, 1),
(22114, 2, 2683.279297, 5650.354004, -13.399734, 1),
(22114, 3, 2662.444580, 5628.390625, -12.016475, 1),
(22114, 4, 2679.702393, 5605.079102, -11.510128, 1),
(22114, 5, 2703.559570, 5581.366211, -10.398445, 1);
