DELETE FROM creature WHERE id = 23301 AND map = 580;
INSERT INTO creature (id, map, spawnMask, position_x, position_y, position_z, orientation, MovementType) VALUES
(23301, 580, 1, 1550.51, 520.005, 27.9482, 1.99584, 0);

UPDATE creature_template SET flags_extra = flags_extra | 0x80 WHERE entry = 23301;

DELETE FROM spell_script_target WHERE entry = 46650;
INSERT INTO spell_script_target VALUES (46650, 1, 23301);

UPDATE creature_template SET ScriptName = "npc_kalec_felmyst", speed = 4 WHERE entry = 24844;
