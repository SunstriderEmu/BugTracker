UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` IN (21302, 20683, 21314, 21500, 19740, 19755, 21499, 21501, 21305);
UPDATE `creature_template_addon` SET `emote`=0 WHERE `entry`=21302;
UPDATE `creature_addon` SET `emote`=0 WHERE `guid` IN (SELECT `guid` FROM `creature` WHERE `id`=21302);
UPDATE `creature` SET `position_x`= -3441.672363, `position_y`= 2950.212646, `position_z`= 171.877686, `orientation`= 6.151093 WHERE `guid`= 74657;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (21302, 21305, 19755, 21499, 21501, 19740, 21500, 21314, 20683) AND `source_type` = 0 ;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(21302,0,0,0,25,0,100,0,0,0,0,0,11,33346,0,0,0,0,0,19,21348,15,0,0,0,0,0,'Shadow Council Warlock - On Reset - Cast Green Beam'),
(21302,0,1,0,1,0,100,1,0,0,0,0,11,33346,0,0,0,0,0,19,21348,15,0,0,0,0,0,'Shadow Council Warlock- OOC - Cast Green Beam (No repeat)'),
(21302,0,2,0,0,0,100,0,1000,2000,5000,7000,11,9613,0,0,0,0,0,2,0,0,0,0,0,0,0,'Shadow Council Warlock- IC - Cast Shadow Bolt'),
(21302,0,3,0,0,0,100,0,6000,8000,10000,12000,11,37992,0,0,0,0,0,2,0,0,0,0,0,0,0,'Shadow Council Warlock- IC - Cast Drain Life'),
(19755,0,0,0,0,0,100,0,4000,5000,15000,17000,11,36253,0,0,0,0,0,2,0,0,0,0,0,0,0,'Mo''arg Weaponsmith- IC - Chemical Flames'),
(19755,0,1,0,0,0,100,0,6000,8000,10000,12000,11,37580,0,0,0,0,0,2,0,0,0,0,0,0,0,'Mo''arg Weaponsmith - IC - Drill Armor'),
(21499,0,0,0,0,0,100,0,4000,5000,15000,17000,11,35321,0,0,0,0,0,2,0,0,0,0,0,0,0,'Overseer Ripsaw - IC - Gushing Wound'),
(21499,0,1,0,0,0,100,0,6000,8000,9000,11000,11,32735,0,0,0,0,0,2,0,0,0,0,0,0,0,'Overseer Ripsaw - IC - Saw Blade'),
(21305,0,0,0,0,0,100,0,4000,5000,10000,12000,11,37950,0,0,0,0,0,2,0,0,0,0,0,0,0,'Mutant Horror - IC - Mutant Horror'),
(21305,0,1,0,0,0,100,0,15000,15000,15000,15000,11,8599,0,0,0,0,0,2,0,0,0,0,0,0,0,'Mutant Horror - IC - Enrage'),
(19740,0,0,0,0,0,100,0,1000,2000,9000,13000,11,33799,0,0,0,0,0,2,0,0,0,0,0,0,0,'wrathwalker - IC - Cast Flame Wave'),
(20683,0,0,0,0,0,100,0,1000,2000,15000,17000,11,37629,0,0,0,0,0,2,0,0,0,0,0,0,0,'Prophetess Cavrylin - IC - Cast Melt Flesh'),
(20683,0,1,0,0,0,100,0,6000,8000,10000,12000,11,37997,0,0,0,0,0,2,0,0,0,0,0,0,0,'Prophetess Cavrylin - IC - Cast Chaos Nova'),
(21314,0,0,0,0,0,100,0,1000,2000,4000,7000,11,15496,0,0,0,0,0,2,0,0,0,0,0,0,0,'Terrormaster - IC - Cast Cleave'),
(21314,0,1,0,0,0,100,0,9000,12000,20000,25000,11,38154,0,0,0,0,0,2,0,0,0,0,0,0,0,'Terrormaster - IC - Cast Fear'), 
(21500,0,0,0,0,0,100,0,1000,2000,6000,9000,11,22859,0,0,0,0,0,2,0,0,0,0,0,0,0,'Morgroron - IC - Cast Mortal Cleave'),
(21500,0,1,0,0,0,100,0,12000,15000,20000,25000,11,38741,0,0,0,0,0,2,0,0,0,0,0,0,0,'Morgroron - IC - Rain of Fire'),
(21500,0,2,0,0,0,100,0,5000,7000,10000,13000,11,38750,0,0,0,0,0,2,0,0,0,0,0,0,0,'Morgroron - IC - War Stomp'),
(21501,0,0,0,0,0,100,0,1000,2000,8000,12000,11,11443,0,0,0,0,0,2,0,0,0,0,0,0,0,'Makazradon - IC - Cripple'),
(21501,0,1,0,0,0,100,0,4000,5000,7000,10000,11,38742,0,0,0,0,0,2,0,0,0,0,0,0,0,'Makazradon - IC - Fel Cleave'),
(21501,0,2,0,0,0,100,0,12000,15000,20000,25000,11,38741,0,0,0,0,0,2,0,0,0,0,0,0,0,'Makazradon - IC - Rain of Fire');