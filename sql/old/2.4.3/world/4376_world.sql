UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 25855;

UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` IN (25798, 25799, 25824);
DELETE FROM `eventai_scripts` WHERE creature_id IN (25798, 25799, 25772, 25824);
DELETE FROM `smart_scripts` WHERE entryorguid IN (25798, 25799, 25772, 25824);
/* Shadowsword Berserker - Cast Flurry */
INSERT INTO `smart_scripts` (`entryorguid`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `target_type`, `comment`) VALUES (25798, 2, 20000, 20000, 20000, 35000, 11, 46160, 20, 1, 'Shadowsword Berserker - Cast Flurry');
/* Shadowsword Fury Mage - Cast Spell Fury */
INSERT INTO `smart_scripts` (`entryorguid`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `target_type`, `comment`) VALUES (25799, 2, 25000, 25000, 45000, 55000, 11, 46102, 1, 1, 'Shadowsword Fury Mage - Cast Spell Fury');
/* Shadowsword Fury Mage - Cast Fel Fireball */
INSERT INTO `smart_scripts` (`entryorguid`, `id`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (25799, 1, 2, 10000, 10000, 5000, 7000, 11, 46101, 2, 'Shadowsword Fury Mage - Cast Fel Fireball');
/* Void Spawn - Cast Shadow Bolt Volley */
INSERT INTO `smart_scripts` (`entryorguid`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES (25824, 2, 15000, 15000, 25000, 35000, 11, 46082, 1, 'Void Spawn - Cast Shadow Bolt Volley');