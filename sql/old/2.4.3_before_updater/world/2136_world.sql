DELETE FROM eventai_scripts WHERE creature_id = 11490;
INSERT INTO eventai_scripts (id, creature_id, event_type, event_flags, event_param1, event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, comment) VALUES
(1149001, 11490, 0, 7, 1000, 1000, 30000, 30000, 11, 22478, 1, 0, "Zevrim Thornhoof - Cast Intense Pain"),
(1149002, 11490, 0, 7, 15000, 15000, 30000, 30000, 11, 22651, 5, 0, "Zevrim Thornhoof - Cast Sacrifice"),
(1149003, 11490, 6, 7, 0, 0, 0, 0, 34, 0, 3, 0, "Zevrim Thornhoof - Set instance data at death");

UPDATE creature_template SET scriptname = "mob_eventai" WHERE entry = 11490;

DELETE FROM creature WHERE id = 14241;
UPDATE creature_template SET scriptname = "npc_ironbark_redeemed", npcflag = 1, faction_A = 35, faction_H = 35 WHERE entry = 14241;

UPDATE gameobject_template SET flags = 36 WHERE entry = 179549;

INSERT INTO waypoint_data (id, point, position_x, position_y, position_z) VALUES
(14241, 0, -56.590000, -269.119995, -57.869999),
(14241, 1, 59.183815, -273.338043, -53.846962),
(14241, 2, 127.622383, -278.449097, -55.886822);

INSERT INTO `gameobject` VALUES (8000196,179549,429,1,131.96,-278.692,-56.2295,0.0652241,0,0,0.0326063,0.999468,25,0,1);
