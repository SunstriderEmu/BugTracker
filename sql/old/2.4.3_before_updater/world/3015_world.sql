DELETE FROM spell_script_target WHERE entry IN (40830, 40825);
INSERT INTO spell_script_target VALUES (40830, 1, 22204), (40830, 1, 19973), (40830, 1, 22201), (40830, 1, 22202), (40830, 1, 20557), (40830, 1, 22291), (40830, 1, 22195);
INSERT INTO spell_script_target VALUES (40825, 1, 22204), (40825, 1, 19973), (40825, 1, 22201), (40825, 1, 22202), (40825, 1, 20557), (40825, 1, 22291), (40825, 1, 22195);

UPDATE creature_template SET scriptname = "trigger_banishing_crystal_bunny01" WHERE entry = 23322;
UPDATE creature_template SET flags_extra = 130 WHERE entry IN (23322, 23327);
