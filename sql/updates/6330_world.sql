DELETE FROM smart_scripts WHERE entryorguid = 24972 AND id = 4;

-- Aqueous Surger SAI
SET @ENTRY := 22881;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
DELETE FROM eventai_scripts where creature_id = @ENTRY;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,85,2,30000,30000,35000,35000,11,40095,0,0,0,0,0,2,0,0,0,0,0,0,0,"Aqueous Surger - In Combat - Cast 40095 (Normal Dungeon)");

#Sunblade Scout
DELETE FROM eventai_scripts WHERE creature_id IN (25372,25507);
UPDATE creature_template SET AIName = "" WHERE entry IN (25372,25507);
REPLACE INTO creature_template_addon (entry,auras) VALUES (25372,"18950 0 18950 1 45769 0 45769 1");