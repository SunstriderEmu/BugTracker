-- Change for normal scale size
-- Use spell for change scale size
UPDATE `creature_template` SET `scale` = '1' WHERE `entry` = 25708;

-- Add script for Power of the Blue Flight
UPDATE `creature_template` SET `AIName` = 'NullCreatureAI' WHERE `entry` = 25653;

DELETE FROM `creature_scripts` WHERE `entryorguid` = 25653;
INSERT INTO `creature_scripts` VALUES (25653, 'npc_power_blue_flight');

