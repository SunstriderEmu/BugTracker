UPDATE creature_template SET AIName = "", ScriptName = "npc_rabid_thistle_bear" WHERE entry = 2164;
UPDATE creature_template SET AIName = "", ScriptName = "npc_tharnariun_treetender" WHERE entry = 3701;

DELETE FROM spell_template WHERE id = 9439;
INSERT INTO spell_template (id, effect1, effectImplicitTargetA1, effectRadiusIndex1, spellName3) VALUES (9439, 3, 38, 8, "Trap for quest 2118");
