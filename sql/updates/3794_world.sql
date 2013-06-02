DELETE FROM spell_script_target WHERE entry = 42339;
INSERT INTO spell_script_target VALUES (42339, 1, 23537);

UPDATE creature_template SET ScriptName = "npc_fire_effigy_fire" WHERE entry = 23537;
INSERT INTO creature_template_addon (entry, auras) VALUES (23537, "42074 0");

UPDATE quest_template SET minlevel = 0, questlevel = 0 WHERE entry IN (11449, 11361, 11450);


