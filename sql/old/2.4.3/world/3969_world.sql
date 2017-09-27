UPDATE creature_template SET flags_extra = 130, ScriptName = "npc_halaa_bomb_target" WHERE entry = 18225;
DELETE FROM creature_template_addon WHERE entry = 18225;
INSERT INTO creature_template_addon (entry, auras) VALUES (18225, "31962 0");

