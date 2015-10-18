UPDATE creature_template SET minlevel = 14, maxlevel = 14, minhealth = 630, maxhealth = 630 WHERE entry = 2675;
UPDATE creature_template SET minlevel = 17, maxlevel = 29, minhealth = 100, maxhealth = 150, armor = 820 WHERE entry = 2676;

-- Eredar Deathbringer SAI
SET @ENTRY := 20880;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,100,2,0,0,0,0,11,27987,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eredar Deathbringer - On Aggro - Cast 'Unholy Aura' (Normal Dungeon)"),
(@ENTRY,0,1,0,4,0,100,4,0,0,0,0,11,38844,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eredar Deathbringer - On Aggro - Cast 'Unholy Aura' (Heroic Dungeon)"),
(@ENTRY,0,2,0,0,0,100,2,10000,10000,10000,10000,11,36789,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar Deathbringer - In Combat - Cast 'Diminish Soul' (Normal Dungeon)"),
(@ENTRY,0,3,0,0,0,100,4,10000,10000,10000,10000,11,38848,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eredar Deathbringer - In Combat - Cast 'Diminish Soul' (Heroic Dungeon)"),
(@ENTRY,0,4,0,0,0,100,2,5000,10000,6000,12000,11,36787,2,0,0,0,0,0,0,0,0,0,0,0,0,"Eredar Deathbringer - In Combat - Cast 'Forceful Cleave' (Normal Dungeon)"),
(@ENTRY,0,5,0,0,0,100,4,5000,10000,5000,10000,11,38846,2,0,0,0,0,0,0,0,0,0,0,0,0,"Eredar Deathbringer - In Combat - Cast 'Forceful Cleave' (Heroic Dungeon)");
