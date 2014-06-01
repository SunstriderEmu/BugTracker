 -- Bone Crawler SAI
SET @ENTRY := 21849;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,5,6,4,0,100,0,0,0,0,0,28,33928,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Crawler - On Aggro - Remove Aura 'Sandworm Submerge Visual'"),
(@ENTRY,0,6,7,61,0,100,0,0,0,0,0,28,29147,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Crawler - On Aggro - Remove Aura 'Tunnel Bore Passive'"),
(@ENTRY,0,7,8,61,0,100,0,0,0,0,0,11,26262,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Crawler - On Aggro - Cast 'Birth'"),
(@ENTRY,0,2,3,61,0,100,0,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Crawler - On Reset - Disable Combat Movement"),
(@ENTRY,0,10,0,9,0,100,0,5,60,500,500,22,2,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bone Crawler - Within 5-60 Range - Set Event Phase 2"),
(@ENTRY,0,1,2,25,0,100,0,0,0,0,0,11,33928,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Crawler - On Reset - Cast 'Sandworm Submerge Visual'"),
(@ENTRY,0,3,4,61,0,100,0,0,0,0,0,11,29147,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Crawler - On Reset - Cast 'Tunnel Bore Passive'"),
(@ENTRY,0,8,9,61,0,100,0,0,0,0,0,19,33554434,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Crawler - On Aggro - Remove Flags Not Attackable & Not Selectable"),
(@ENTRY,0,4,0,61,0,100,0,0,0,0,0,18,33554434,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Crawler - On Reset - Set Flags Not Attackable & Not Selectable"),
(@ENTRY,0,9,0,61,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bone Crawler - On Aggro - Set Event Phase 2"),
(@ENTRY,0,11,0,0,1,100,0,3000,6000,20000,23000,11,32738,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bone Crawler - In Combat - Cast 'Bore' (Phase 1)"),
(@ENTRY,0,13,0,0,2,100,0,2000,2500,2500,4000,11,31747,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bone Crawler - In Combat - Cast 'Poison' (Phase 2)"),
(@ENTRY,0,12,0,9,0,100,0,0,5,500,500,22,1,0,0,0,0,0,2,0,0,0,0,0,0,0,"Bone Crawler - Within 0-5 Range - Set Event Phase 1");

UPDATE creature_template SET speed = 2, mindmg = 250, maxdmg = 500, flags_extra = 0 WHERE entry = 21849;

-- Gnomish Flame Turret SAI
SET @ENTRY := 17458;
UPDATE `creature_template` SET `armor` = 3000, `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,37,0,100,0,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnomish Flame Turret - On Initialize - Disable Combat Movement"),
(@ENTRY,0,1,0,60,0,100,0,200,200,400,400,11,30527,0,0,0,0,0,25,0,0,0,0,0,0,0,"Gnomish Flame Turret - On Update- Cast 'Flame Cannon'"),
(@ENTRY,0,2,0,37,0,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gnomish Flame Turret - On Initialize - Stop Attacking");

