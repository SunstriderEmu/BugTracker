DELETE FROM spell_script_target WHERE entry IN (36384, 37285);
INSERT INTO spell_script_target VALUES (36384, 1, 21211);
INSERT INTO spell_script_target VALUES (37285, 1, 21211);

UPDATE creature_template SET scriptname = "npc_skartax" WHERE entry = 21207;

UPDATE event_scripts SET datalong2 = 300000, x = -3358.90, y = 2139.48, z = -8.28, o = 0.74 WHERE id = 13980;
