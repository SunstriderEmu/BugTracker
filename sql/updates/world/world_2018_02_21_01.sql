-- Blood Elf Defender
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8581;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8581 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=858100 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8581,0,0,0,0,0,100,0,7000,12000,11000,14000,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blood Elf Defender - In Combat - Cast 'Shield Block'"),
(8581,0,1,0,0,0,100,0,5000,9000,8000,13000,11,12170,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blood Elf Defender - In Combat - Cast 'Revenge'"),
(8581,0,2,0,11,0,100,0,0,0,0,0,80,858100,2,0,0,0,0,1,0,0,0,0,0,0,0,"Blood Elf Defender - On Respawn - Run Script"),
(858100,9,0,0,0,0,100,0,0,0,0,0,11,51347,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blood Elf Defender - On Script - Cast 'Teleport Visual Only'"),
(858100,9,1,0,0,0,100,0,2000,2000,0,0,49,0,0,0,0,0,0,21,50,0,0,0,0,0,0,"Blood Elf Defender - On Script - Start Attacking"),
(858100,9,2,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blood Elf Defender - On Script - Say Line 0"),
(858100,9,3,0,0,0,100,0,10000,10000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blood Elf Defender - On Script - Say Line 1"),
(858100,9,4,0,0,0,100,0,6000,6000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blood Elf Defender - On Script - Say Line 2");

DELETE FROM `creature_text` WHERE `CreatureID`=8581;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(8581,0,0,"Who dares?! I will destroy you!",12,0,100,0,0,0,4502,0,"Blood Elf Defender"),
(8581,1,0,"Mistress!! They seek to destroy your work!!",12,0,100,0,0,0,4491,0,"Blood Elf Defender"),
(8581,2,0,"Ha! Now your death is ensured!",12,0,100,0,0,0,4492,0,"Blood Elf Defender");

-- Magus Rimtori
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=8578;
DELETE FROM `smart_scripts` WHERE `entryorguid`=8578 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(8578,0,0,0,0,0,100,0,0,0,3000,5000,11,20823,64,0,0,0,0,2,0,0,0,0,0,0,0,"Magus Rimtori - In Combat - Cast 'Fireball'"),
(8578,0,1,0,9,0,100,0,0,8,13000,16000,11,11831,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magus Rimtori - Within 0-8 Range - Cast 'Frost Nova'"),
(8578,0,2,0,11,0,100,0,0,0,0,0,11,51347,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magus Rimtori - On Respawn - Cast 'Teleport Visual Only'"),
(8578,0,3,0,4,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magus Rimtori - On Aggro - Say Line 0");

DELETE FROM `creature_text` WHERE `CreatureID`=8578;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(8578,0,0,"You dare! Now feel my wrath!",14,0,100,0,0,0,4495,0,"Magus Rimtori");

-- Ravasaur Runner
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=6506;
DELETE FROM `smart_scripts` WHERE `entryorguid`=6506 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6506,0,0,0,25,0,100,0,0,0,0,0,11,3417,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ravasaur Runner - On Reset - Cast 'Thrash'"),
(6506,0,1,0,4,0,100,0,0,0,0,0,11,6268,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ravasaur Runner - On Aggro - Cast 'Rushing Charge'");

-- Venomhide Ravasaur
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=6508;
DELETE FROM `smart_scripts` WHERE `entryorguid`=6508 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6508,0,0,0,25,0,100,0,0,0,0,0,11,14108,0,0,0,0,0,1,0,0,0,0,0,0,0,"Venomhide Ravasaur - On Reset - Cast 'Venomhide Poison'");

-- Muculent Ooze
DELETE FROM `smart_scripts` WHERE `entryorguid`=6556 AND `source_type`=0 AND `id`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6556,0,1,0,25,0,100,0,0,0,0,0,11,14133,0,0,0,0,0,1,0,0,0,0,0,0,0,"Muculent Ooze - On Reset - Cast 'Muculent Fever Proc'");

-- Primal Ooze
DELETE FROM `smart_scripts` WHERE `entryorguid`=6557 AND `source_type`=0 AND `id` IN (8,9);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6557,0,8,0,2,0,100,1,0,30,0,0,11,14146,0,0,0,0,0,1,0,0,0,0,0,0,0,"Primal Ooze - Between 0-30% Health - Cast 'Clone' (No Repeat)"),
(6557,0,9,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Primal Ooze - Between 0-30% Health - Say Line 0 (No Repeat)");

DELETE FROM `creature_text` WHERE `CreatureID`=6557;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(6557,0,0,"%s begins to make a copy of itself!",16,0,100,0,0,0,2082,0,"Primal Ooze");

-- Cloned Ooze
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=9477;
DELETE FROM `smart_scripts` WHERE `entryorguid`=9477 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(9477,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,30,0,0,0,0,0,0,"Cloned Ooze - Just Summoned - Start Attacking");

-- Glutinous Ooze
DELETE FROM `smart_scripts` WHERE `entryorguid`=6559 AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6559,0,2,0,6,0,100,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Glutinous Ooze - On Just Died - Say Line 0");

DELETE FROM `creature_text` WHERE `CreatureID`=6559;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(6559,0,0,"%s explodes into chunks of acidic slime!",16,0,100,0,0,0,4838,0,"Glutinous Ooze");

-- Gorishi Wasp
DELETE FROM `smart_scripts` WHERE `entryorguid`=6551 AND `source_type`=0 AND `id`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6551,0,1,0,25,0,100,0,0,0,0,0,11,13299,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gorishi Wasp - On Reset - Cast 'Poison Proc'");

-- Gorishi Worker
DELETE FROM `smart_scripts` WHERE `entryorguid`=6552 AND `source_type`=0 AND `id`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6552,0,1,0,2,0,100,1,0,50,0,0,39,20,1,0,0,0,0,1,0,0,0,0,0,0,0,"Gorishi Worker - Between 0-30% Health - Call For Help (No Repeat)");

-- Gorishi Reaver
DELETE FROM `smart_scripts` WHERE `entryorguid`=6553 AND `source_type`=0 AND `id`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6553,0,1,0,0,0,100,0,8000,12000,21000,25000,11,8137,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gorishi Reaver - In Combat - Cast 'Silithid Pox'");

-- Gorishi Stinger
DELETE FROM `smart_scripts` WHERE `entryorguid`=6554 AND `source_type`=0 AND `id`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6554,0,1,0,25,0,100,0,0,0,0,0,11,8601,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gorishi Stinger - On Reset - Cast 'Slowing Poison'");

-- Gorishi Tunneler
DELETE FROM `smart_scripts` WHERE `entryorguid`=6555 AND `source_type`=0 AND `id`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6555,0,1,0,0,0,100,0,8000,12000,21000,25000,11,8137,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gorishi Tunneler - In Combat - Cast 'Silithid Pox'");

-- Blazing Invader
UPDATE `creature_template` SET `unit_class`=2, `AIName`="SmartAI" WHERE `entry`=14460;
DELETE FROM `smart_scripts` WHERE `entryorguid`=14460 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(14460,0,0,0,0,0,100,0,7000,13000,19000,24000,11,23039,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blazing Invader - In Combat - Cast 'Blast Wave'");

-- Living Blaze
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=6521;
DELETE FROM `smart_scripts` WHERE `entryorguid`=6521 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6521,0,0,0,0,0,100,0,3000,3000,3000,3000,11,11351,0,0,0,0,0,1,0,0,0,0,0,0,0,"Living Blaze - In Combat - Cast 'Fire Shield'");


-- Starving Snickerfang
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5984;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5984 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5984,0,0,0,0,0,100,0,5000,8000,21000,24000,11,7367,0,0,0,0,0,2,0,0,0,0,0,0,0,"Starving Snickerfang - In Combat - Cast 'Infected Bite'");

-- Snickerfang Hyena
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5985;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5985 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5985,0,0,0,0,0,100,0,5000,8000,21000,24000,11,7367,0,0,0,0,0,2,0,0,0,0,0,0,0,"Snickerfang Hyena - In Combat - Cast 'Infected Bite'");

-- Ashmane Boar
DELETE FROM `smart_scripts` WHERE `entryorguid`=5992 AND `source_type`=0 AND `id` IN (0,1);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5992,0,0,0,25,0,100,0,0,0,0,0,11,12898,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ashmane Boar - On Reset - Cast 'Smoke Aura Visual'"),
(5992,0,1,0,0,0,100,0,3000,3000,3000,3000,11,11351,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ashmane Boar - In Combat - Cast 'Fire Shield'");

-- Shadowsworn Thug
DELETE FROM `smart_scripts` WHERE `entryorguid`=6005 AND `source_type`=0 AND `id` IN (1,2);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6005,0,1,0,25,0,100,0,0,0,0,0,11,8876,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowsworn Thug - On Reset - Cast 'Thrash'"),
(6005,0,2,0,0,0,100,0,8000,12000,14000,18000,11,8646,0,0,0,0,0,2,0,0,0,0,0,0,0,"Shadowsworn Thug - In Combat - Cast 'Snap Kick'");

-- Scorpok Stinger
DELETE FROM `smart_scripts` WHERE `entryorguid`=5988 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5988,0,0,0,0,0,100,0,7000,9000,14000,18000,11,5416,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scorpok Stinger - In Combat - Cast 'Venom Sting'");

-- Dreadmaul Ogre
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5974;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5974 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5974,0,0,0,0,0,100,0,5000,11000,28000,34000,11,11960,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dreadmaul Ogre - In Combat - Cast 'Curse of the Dreadmaul'"),
(5974,0,1,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dreadmaul Ogre - On Aggro - Say Line 0");

DELETE FROM `creature_text` WHERE `CreatureID`=5974;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(5974,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,1925,0,"Dreadmaul Ogre"),
(5974,0,1,"Me smash! You die!",12,0,100,0,0,0,1926,0,"Dreadmaul Ogre"),
(5974,0,2,"I'll crush you!",12,0,100,0,0,0,1927,0,"Dreadmaul Ogre");

-- Dreadmaul Brute
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=5976;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5976 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5976,0,0,0,0,0,100,0,5000,11000,28000,34000,11,11960,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dreadmaul Brute - In Combat - Cast 'Curse of the Dreadmaul'"),
(5976,0,1,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dreadmaul Brute - On Aggro - Say Line 0");

DELETE FROM `creature_text` WHERE `CreatureID`=5976;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(5976,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,1925,0,"Dreadmaul Brute"),
(5976,0,1,"Me smash! You die!",12,0,100,0,0,0,1926,0,"Dreadmaul Brute"),
(5976,0,2,"I'll crush you!",12,0,100,0,0,0,1927,0,"Dreadmaul Brute");

-- Dreadmaul Ogre Mage
DELETE FROM `smart_scripts` WHERE `entryorguid`=5975 AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5975,0,2,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dreadmaul Ogre Mage - On Aggro - Say Line 0");

DELETE FROM `creature_text` WHERE `CreatureID`=5975;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(5975,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,1925,0,"Dreadmaul Ogre Mage"),
(5975,0,1,"Me smash! You die!",12,0,100,0,0,0,1926,0,"Dreadmaul Ogre Mage"),
(5975,0,2,"I'll crush you!",12,0,100,0,0,0,1927,0,"Dreadmaul Ogre Mage");

-- Dreadmaul Warlock
UPDATE `smart_scripts` SET `action_param2`=32 WHERE `entryorguid`=5978 AND `source_type`=0 AND `id`=1;
DELETE FROM `smart_scripts` WHERE `entryorguid`=5978 AND `source_type`=0 AND `id`=2;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5978,0,2,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dreadmaul Warlock - On Aggro - Say Line 0");

DELETE FROM `creature_text` WHERE `CreatureID`=5978;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(5978,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,1925,0,"Dreadmaul Warlock"),
(5978,0,1,"Me smash! You die!",12,0,100,0,0,0,1926,0,"Dreadmaul Warlock"),
(5978,0,2,"I'll crush you!",12,0,100,0,0,0,1927,0,"Dreadmaul Warlock");

-- Dreadmaul Mauler
DELETE FROM `smart_scripts` WHERE `entryorguid`=5977 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(5977,0,0,0,25,0,100,0,0,0,0,0,11,8876,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dreadmaul Mauler - On Reset - Cast 'Thrash'"),
(5977,0,1,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dreadmaul Mauler - On Aggro - Say Line 0");

DELETE FROM `creature_text` WHERE `CreatureID`=5977;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(5977,0,0,"Raaar!!! Me smash $r!",12,0,100,0,0,0,1925,0,"Dreadmaul Mauler"),
(5977,0,1,"Me smash! You die!",12,0,100,0,0,0,1926,0,"Dreadmaul Mauler"),
(5977,0,2,"I'll crush you!",12,0,100,0,0,0,1927,0,"Dreadmaul Mauler");

-- Felbeast
UPDATE `smart_scripts` SET `event_param1`=4000, `event_param2`=8000, `event_param3`=18000, `event_param4`=24000 WHERE `entryorguid`=8675 AND `source_type`=0 AND `id`=0;


-- Un'Goro Thunderer
DELETE FROM `smart_scripts` WHERE `entryorguid`=-23952 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=651600 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(-23952,0,0,0,0,0,100,0,5000,5000,9000,15000,11,12553,0,0,0,0,0,2,0,0,0,0,0,0,0,"Un'Goro Thunderer - In Combat - Cast 'Shock'"),
(-23952,0,1,0,1,0,100,0,15000,30000,150000,180000,80,651600,0,0,0,0,0,1,0,0,0,0,0,0,0,"Un'Goro Thunderer - Out of Combat - Run Script"),
(-23952,0,2,0,4,0,100,0,0,0,0,0,91,7,0,0,0,0,0,1,0,0,0,0,0,0,0,"Un'Goro Thunderer - On Aggro - Remove Flag Standstate Dead"),
(651600,9,0,0,0,0,100,0,0,0,0,0,90,7,0,0,0,0,0,1,0,0,0,0,0,0,0,"Un'Goro Thunderer - On Script - Set Flag Standstate Dead"),
(651600,9,1,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Un'Goro Thunderer - On Script - Say Line 0"),
(651600,9,2,0,0,0,100,0,60000,60000,0,0,91,7,0,0,0,0,0,1,0,0,0,0,0,0,0,"Un'Goro Thunderer - On Script - Remove Flag Standstate Dead");

DELETE FROM `creature_text` WHERE `CreatureID`=6516;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(6516,0,0,"%s looks tired. He then yawns and lies down next to A-Me 01.",16,0,100,0,0,0,5045,0,"Un'Goro Thunderer"),
(6516,0,1,"%s snores loudly and cuddles up next to A-Me 01.",16,0,100,0,0,0,5046,0,"Un'Goro Thunderer");

UPDATE `creature_addon` SET `bytes1`=7 WHERE `guid`=24139;

-- Arkkoran Clacker
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=6135;
DELETE FROM `smart_scripts` WHERE `entryorguid`=6135 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(6135,0,0,0,2,0,100,1,0,50,0,0,39,30,1,0,0,0,0,1,0,0,0,0,0,0,0,"Arkkoran Clacker - Between 0-50% Health - Call For Help (No Repeat)");