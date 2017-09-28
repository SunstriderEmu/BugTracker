UPDATE creature_template SET ScriptName = "npc_kaliri_egg_trigger" WHERE entry = 22991;
UPDATE spell_template SET effectImplicitTargetA1 = 7 WHERE id = 39844;
DELETE FROM spell_script_target WHERE entry = 39844;
INSERT INTO spell_script_target VALUES (39844, 1, 22991);
