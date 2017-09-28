UPDATE creature_template SET spell1 = 38920 WHERE entry IN (16943, 20928);
UPDATE creature_template SET spell2 = 36255, spell3 = 8599 WHERE entry = 16943;

DELETE FROM spell_script_target WHERE entry = 38920;
INSERT INTO spell_script_target VALUES (38920, 1, 19656);
INSERT INTO spell_script_target VALUES (38920, 1, 22348), (38920, 1, 22350), (38920, 1, 22351);
INSERT INTO spell_script_target VALUES (38920, 2, 22348), (38920, 2, 22350), (38920, 2, 22351);

UPDATE spell_template SET effectImplicitTargetA1 = 7 WHERE id = 38920;
