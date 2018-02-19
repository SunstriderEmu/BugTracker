
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "", InhabitType = 3 WHERE entry = 17724;
REPLACE INTO spell_script_names VALUES (34171, "spell_tentacle_lash");
REPLACE INTO spell_script_names VALUES (37956, "spell_tentacle_lash");

-- NPC 17724
SET @ENTRY = 17724;
UPDATE creature_template SET AIName='SmartAI', ScriptName='' WHERE entry = @ENTRY;
DELETE FROM smart_scripts WHERE entryorguid = @ENTRY AND source_type = 0;
INSERT IGNORE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_flags, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES 
(@ENTRY, 0, 0, 0, 0, 0, 100, 2, 4000, 14000, 4000, 14000, 11, 34171, 0, 0, 0, 0, 0, 2, 0, 0, 5, 0, 0, 0, 0, 0, 'Underbat - In Combat - Cast "<a href="http://wowhead.com/spell=34171">Tentacle Lash</a>" (Normal Dungeon)'),
(@ENTRY, 0, 1, 0, 0, 0, 100, 4, 4000, 14000, 4000, 14000, 11, 37956, 0, 0, 0, 0, 0, 2, 0, 0, 5, 0, 0, 0, 0, 0, 'Underbat - In Combat - Cast "<a href="http://wowhead.com/spell=37956">Tentacle Lash</a>" (Heroic Dungeon)');