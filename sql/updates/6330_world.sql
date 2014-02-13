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

-- Shadowmoon Houndmaster SAI
SET @ENTRY := 23018;
UPDATE `creature_template` SET `AIName`="SmartAI", ScriptName = "" WHERE `entry`=@ENTRY;
DELETE FROM eventai_scripts WHERE creature_id = @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,2,0,0,0,0,11,39906,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowmoon Houndmaster - On Aggro - Cast 'Summon Riding Warhound' (Normal Dungeon)"),
(@ENTRY,0,1,0,4,0,100,2,0,0,0,0,11,41085,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Houndmaster - On Aggro - Cast 'Freezing Trap' (Normal Dungeon)"),
(@ENTRY,0,2,0,9,0,100,2,5,30,1500,3000,11,41093,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Houndmaster - Within 5-30 Range - Cast 'Shoot' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,2,3500,3500,15000,20000,11,41084,0,0,0,0,0,5,0,0,0,0,0,0,0,"Shadowmoon Houndmaster - In Combat - Cast 'Silencing Shot' (Normal Dungeon)"),
(@ENTRY,0,4,0,0,0,100,2,20000,20000,45000,50000,11,41091,0,0,0,0,0,5,0,0,0,0,0,0,0,"Shadowmoon Houndmaster - In Combat - Cast 'Volley' (Normal Dungeon)"),
(@ENTRY,0,5,0,0,0,100,2,2000,3000,10000,15000,11,32908,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Houndmaster - In Combat - Cast 'Wing Clip' (Normal Dungeon)"),
(@ENTRY,0,6,0,4,0,100,2,0,0,0,0,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Shadowmoon Houndmaster - On Aggro - Dismount (Normal Dungeon)"),
(@ENTRY,0,7,0,25,0,100,2,0,0,0,0,43,0,14334,0,0,0,0,0,0,0,0,0,0,0,0,"Shadowmoon Houndmaster - On Reset - Mount To Model 14334 (Normal Dungeon)");

-- Shadowmoon Riding Hound SAI
SET @ENTRY := 23083;
UPDATE `creature_template` SET `AIName`="SmartAI", ScriptName = "" WHERE `entry`=@ENTRY;
DELETE FROM eventai_scripts WHERE creature_id = @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,3,0,0,0,0,11,25821,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Riding Hound - On Aggro - Cast 'Charge' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,1,0,0,0,100,2,3000,6000,20000,25000,11,41092,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowmoon Riding Hound - In Combat - Cast 'Carnivorous Bite' (Normal Dungeon)"),
(@ENTRY,0,2,0,2,0,100,3,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowmoon Riding Hound - Between 0-30% Health - Cast 'Enrage' (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,3,0,2,0,100,3,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowmoon Riding Hound - Between 0-30% Health - Say Line 0 (No Repeat) (Normal Dungeon)"),
(@ENTRY,0,4,0,7,0,100,2,0,0,0,0,37,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Shadowmoon Riding Hound - On Evade - Kill Self (Normal Dungeon)");

UPDATE creature_template SET AIName = "", ScriptName = "npc_arcane_anomaly" WHERE entry = 16488;