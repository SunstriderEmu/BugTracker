DELETE FROM `trinity_string` WHERE `entry` = 819;
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc2`) VALUES (819, "City", "Capitales");

DELETE FROM spell_script_target WHERE entry = 39914;
INSERT INTO spell_script_target VALUES (39914, 1, 24039);

DELETE FROM spell_script_target WHERE entry IN (41145, 41146);
INSERT INTO spell_script_target VALUES (41145, 1, 22923);
INSERT INTO spell_script_target VALUES (41146, 1, 22923);

UPDATE creature_template SET inhabittype = 4 WHERE entry = 22923;
