DELETE FROM `creature` WHERE `guid` = '70248';
DELETE FROM `creature` WHERE `guid` = '70249';
DELETE FROM `creature` WHERE `guid` = '70250';
DELETE FROM `creature` WHERE `guid` = '70251';
DELETE FROM `creature` WHERE `guid` = '70252';
DELETE FROM `creature` WHERE `guid` = '70253';
DELETE FROM `creature` WHERE `guid` = '70254';

UPDATE `creature_template` SET `unit_flags` = '4' WHERE entry = '20284';
UPDATE `creature_template` SET `flags_extra` = '2' WHERE entry = '19692';
UPDATE `creature_template` SET `ScriptName` = 'npc_dr_boom' WHERE `entry` = '20284';
UPDATE `creature_template` SET `ScriptName` = 'npc_boom_bot' WHERE `entry` = '19692';
