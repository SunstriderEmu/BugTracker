UPDATE creature_template SET flags_extra = 130 WHERE entry IN (23059, 23260, 23312, 23313, 23328, 23500);

UPDATE creature_template SET faction_a = 90, faction_h = 90 WHERE entry IN (23055, 23113);

DELETE FROM creature WHERE id IN (23055, 23113, 23116);
INSERT INTO creature (id, map, spawnmask, position_x, position_y, position_z, orientation, spawntimesecs) VALUES
(23055, 530, 1, 2740.24, 7130.62, 365.841, 2.40912, 1800),	-- 30 mins but will be respawned by event
(23113, 530, 1, 2720.11, 7117.68, 367.31, 2.70509, 1800),
(23116, 530, 1, 2720.11, 7117.68, 367.31, 2.70509, 1800);

UPDATE creature_template SET scale = 5, flags_extra = 130 WHERE entry = 23116;
DELETE FROM creature_template_addon WHERE entry = 23116;
INSERT INTO creature_template_addon (entry, auras) VALUES (23116, "40158 0");

DELETE FROM spell_script_target WHERE entry = 40380;
INSERT INTO spell_script_target VALUES (40380, 1, 23059);

UPDATE creature_template SET scriptname = "npc_lr_trigger" WHERE entry = 23260;
