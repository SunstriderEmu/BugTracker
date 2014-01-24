#re setting SPELL_INTERRUPT_FLAG_INTERRUPT for Malande empowered smite

UPDATE spell_template
SET preventionType = 0x4
WHERE id = 41471;

#converting some eventAI to smartAI

-- Blazing Trickster SAI
SET @ENTRY := 20905;
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` ='' WHERE `entry`=@ENTRY;
DELETE FROM `eventai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,7,0,0,0,0,34,5,1,0,0,0,0,1,0,0,0,0,0,0,0,"Blazing Trickster - On Aggro - Set Instance Data Field To 5 To Data 1 (Dungeon Only)"),
(@ENTRY,0,1,0,6,0,100,7,0,0,0,0,34,5,3,0,0,0,0,1,0,0,0,0,0,0,0,"Blazing Trickster - On Death - Set Instance Data Field To 5 To Data 3 (Dungeon Only)"),
(@ENTRY,0,2,0,7,0,100,7,0,0,0,0,34,4,2,0,0,0,0,1,0,0,0,0,0,0,0,"Blazing Trickster - On Evade - Set Instance Data Field To 4 To Data 2 (Dungeon Only)"),
(@ENTRY,0,3,0,0,0,85,6,4500,4500,12000,15000,11,36906,0,0,0,0,0,6,0,0,0,0,0,0,0,"Blazing Trickster - In Combat - Cast 36906 (Dungeon Only)"),
(@ENTRY,0,4,0,0,0,85,6,2000,2000,10000,16000,11,39023,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blazing Trickster - In Combat - Cast 39023 (Dungeon Only)"),
(@ENTRY,0,5,0,0,0,100,6,500,500,180000,190000,11,36907,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blazing Trickster - In Combat - Cast 36907 (Dungeon Only)");

-- Phase-Hunter SAI
SET @ENTRY := 20906;
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` ='' WHERE `entry`=@ENTRY;
DELETE FROM `eventai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,7,0,0,0,0,34,5,1,0,0,0,0,1,0,0,0,0,0,0,0,"Phase-Hunter - On Aggro - Set Instance Data Field To 5 To Data 1 (Dungeon Only)"),
(@ENTRY,0,1,0,6,0,100,7,0,0,0,0,34,5,3,0,0,0,0,1,0,0,0,0,0,0,0,"Phase-Hunter - On Death - Set Instance Data Field To 5 To Data 3 (Dungeon Only)"),
(@ENTRY,0,2,0,7,0,100,7,0,0,0,0,34,4,2,0,0,0,0,1,0,0,0,0,0,0,0,"Phase-Hunter - On Evade - Set Instance Data Field To 4 To Data 2 (Dungeon Only)"),
(@ENTRY,0,3,0,0,0,100,7,0,0,1000,1000,11,36908,0,0,0,0,0,1,0,0,0,0,0,0,0,"Phase-Hunter - In Combat - Cast 36908 (Dungeon Only)"),
(@ENTRY,0,4,0,0,0,100,6,2500,2500,5000,6000,11,36909,0,0,0,0,0,2,0,0,0,0,0,0,0,"Phase-Hunter - In Combat - Cast 36909 (Dungeon Only)"),
(@ENTRY,0,5,0,0,0,100,6,0,0,20000,25000,11,36910,0,0,0,0,0,1,0,0,0,0,0,0,0,"Phase-Hunter - In Combat - Cast 36910 (Dungeon Only)");

-- Akkiris Lightning-Waker SAI
SET @ENTRY := 20908;
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` ='' WHERE `entry`=@ENTRY;
DELETE FROM `eventai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,7,0,0,0,0,34,7,1,0,0,0,0,1,0,0,0,0,0,0,0,"Akkiris Lightning-Waker - On Aggro - Set Instance Data Field To 7 To Data 1 (Dungeon Only)"),
(@ENTRY,0,1,0,6,0,100,7,0,0,0,0,34,7,3,0,0,0,0,1,0,0,0,0,0,0,0,"Akkiris Lightning-Waker - On Death - Set Instance Data Field To 7 To Data 3 (Dungeon Only)"),
(@ENTRY,0,2,0,7,0,100,7,0,0,0,0,34,4,2,0,0,0,0,1,0,0,0,0,0,0,0,"Akkiris Lightning-Waker - On Evade - Set Instance Data Field To 4 To Data 2 (Dungeon Only)"),
(@ENTRY,0,3,0,4,0,100,7,0,0,0,0,11,38642,0,0,0,0,0,1,0,0,0,0,0,0,0,"Akkiris Lightning-Waker - On Aggro - Cast 38642 (Dungeon Only)"),
(@ENTRY,0,4,0,0,0,80,6,2000,2000,3000,5000,11,36915,0,0,0,0,0,1,0,0,0,0,0,0,0,"Akkiris Lightning-Waker - In Combat - Cast 36915 (Dungeon Only)"),
(@ENTRY,0,5,0,0,0,75,6,9000,9000,12000,16000,11,39028,0,0,0,0,0,1,0,0,0,0,0,0,0,"Akkiris Lightning-Waker - In Combat - Cast 39028 (Dungeon Only)"),
(@ENTRY,0,6,0,0,0,85,6,30000,30000,90000,100000,11,36914,0,0,0,0,0,2,0,0,0,0,0,0,0,"Akkiris Lightning-Waker - In Combat - Cast 36914 (Dungeon Only)"),
(@ENTRY,0,7,0,8,0,50,6,0,127,30000,30000,11,19714,0,0,0,0,0,1,0,0,0,0,0,0,0,"Akkiris Lightning-Waker - On Spellhit By 0 - Cast 19714 (Dungeon Only)"),
(@ENTRY,0,8,0,13,0,40,6,10000,10000,0,0,11,32691,0,0,0,0,0,7,0,0,0,0,0,0,0,"Akkiris Lightning-Waker - On Target Casting - Cast 32691 (Dungeon Only)");

-- Sulfuron Magma-Thrower SAI
SET @ENTRY := 20909;
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` ='' WHERE `entry`=@ENTRY;
DELETE FROM `eventai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,7,0,0,0,0,34,7,1,0,0,0,0,1,0,0,0,0,0,0,0,"Sulfuron Magma-Thrower - On Aggro - Set Instance Data Field To 7 To Data 1 (Dungeon Only)"),
(@ENTRY,0,1,0,6,0,100,7,0,0,0,0,34,7,3,0,0,0,0,1,0,0,0,0,0,0,0,"Sulfuron Magma-Thrower - On Death - Set Instance Data Field To 7 To Data 3 (Dungeon Only)"),
(@ENTRY,0,2,0,7,0,100,7,0,0,0,0,34,4,2,0,0,0,0,1,0,0,0,0,0,0,0,"Sulfuron Magma-Thrower - On Evade - Set Instance Data Field To 4 To Data 2 (Dungeon Only)"),
(@ENTRY,0,3,0,0,0,100,6,4000,4000,60000,70000,11,36917,0,0,0,0,0,5,0,0,0,0,0,0,0,"Sulfuron Magma-Thrower - In Combat - Cast 36917 (Dungeon Only)");

-- Twilight Drakonaar SAI
SET @ENTRY := 20910;
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` ='' WHERE `entry`=@ENTRY;
DELETE FROM `eventai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,7,0,0,0,0,34,8,1,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Drakonaar - On Aggro - Set Instance Data Field To 8 To Data 1 (Dungeon Only)"),
(@ENTRY,0,1,0,4,0,100,7,0,0,0,0,31,1,5,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Drakonaar - On Aggro - Random Phase Range (1-5) (Dungeon Only)"),
(@ENTRY,0,2,0,6,0,100,7,0,0,0,0,34,8,3,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Drakonaar - On Death - Set Instance Data Field To 8 To Data 3 (Dungeon Only)"),
(@ENTRY,0,3,0,7,0,100,7,0,0,0,0,34,4,2,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Drakonaar - On Evade - Set Instance Data Field To 4 To Data 2 (Dungeon Only)"),
(@ENTRY,0,4,0,7,0,100,7,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Drakonaar - On Evade - Set Event Phase 0 (Dungeon Only)"),
(@ENTRY,0,5,0,0,2,80,2,2000,2000,4000,6000,11,22560,0,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight Drakonaar - In Combat - Cast 22560 (Normal Dungeon) (Phase 2)"),
(@ENTRY,0,6,0,0,2,80,4,5000,5000,8000,11500,11,39033,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Drakonaar - In Combat - Cast 39033 (Heroic Dungeon) (Phase 2)"),
(@ENTRY,0,7,0,0,4,80,2,3000,3000,8000,12000,11,22559,0,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight Drakonaar - In Combat - Cast 22559 (Normal Dungeon) (Phase 4)"),
(@ENTRY,0,8,0,0,4,80,4,1000,1000,12000,15500,11,39037,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Drakonaar - In Combat - Cast 39037 (Heroic Dungeon) (Phase 4)"),
(@ENTRY,0,9,0,0,8,90,2,5000,5000,10000,10000,11,22642,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Drakonaar - In Combat - Cast 22642 (Normal Dungeon) (Phase 8)"),
(@ENTRY,0,10,0,0,8,80,4,7000,7000,12000,15500,11,39036,0,0,0,0,0,1,0,0,0,0,0,0,0,"Twilight Drakonaar - In Combat - Cast 39036 (Heroic Dungeon) (Phase 8)"),
(@ENTRY,0,11,0,0,16,100,6,2000,2000,2000,4000,11,22561,0,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight Drakonaar - In Combat - Cast 22561 (Dungeon Only) (Phase 16)"),
(@ENTRY,0,12,0,0,0,85,2,3000,3000,8000,10500,11,22558,0,0,0,0,0,5,0,0,0,0,0,0,0,"Twilight Drakonaar - In Combat - Cast 22558 (Normal Dungeon)"),
(@ENTRY,0,13,0,0,0,85,4,6000,6000,12000,14000,11,39034,0,0,0,0,0,2,0,0,0,0,0,0,0,"Twilight Drakonaar - In Combat - Cast 39034 (Heroic Dungeon)");

-- Blackwing Drakonaar SAI
SET @ENTRY := 20911;
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName` ='' WHERE `entry`=@ENTRY;
DELETE FROM `eventai_scripts` WHERE `creature_id`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,7,0,0,0,0,34,8,1,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Drakonaar - On Aggro - Set Instance Data Field To 8 To Data 1 (Dungeon Only)"),
(@ENTRY,0,1,0,6,0,100,7,0,0,0,0,34,8,3,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Drakonaar - On Death - Set Instance Data Field To 8 To Data 3 (Dungeon Only)"),
(@ENTRY,0,2,0,7,0,100,7,0,0,0,0,34,4,2,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Drakonaar - On Evade - Set Instance Data Field To 4 To Data 2 (Dungeon Only)"),
(@ENTRY,0,3,0,0,0,100,6,9000,9000,20000,25000,11,39038,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blackwing Drakonaar - In Combat - Cast 39038 (Dungeon Only)"),
(@ENTRY,0,4,0,0,0,100,6,5000,5000,14000,18000,11,39033,0,0,0,0,0,5,0,0,0,0,0,0,0,"Blackwing Drakonaar - In Combat - Cast 39033 (Dungeon Only)"),
(@ENTRY,0,5,0,0,0,100,6,12000,12000,9000,18000,11,13737,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blackwing Drakonaar - In Combat - Cast 13737 (Dungeon Only)");

UPDATE script_texts SET content_loc2 = "Par tous les grands gluants de Gnomeregan où suis-je ? Et qui êtes-vous -- Yaaghh ! Ma tête... la mère de toute les migraines..." WHERE entry = -1552010;