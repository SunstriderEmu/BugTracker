UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (15391, 15392, 15389, 15390, 15386, 15388, 15385, 15344, 15387);

DELETE FROM smart_scripts WHERE entryorguid IN (15391, 15392, 15389, 15390, 15386, 15388, 15385, 15344, 15387);
INSERT INTO smart_scripts VALUES
-- Wave 1
(15391, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 6000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Qeez - IC Timer - Cast Cleave on victim"),
(15391, 0, 1, 0, 0, 0, 100, 2, 15000, 22000, 22000, 30000, 11, 19134, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Qeez - IC Timer - Cast Frightning Shout"),
(15391, 0, 2, 0, 0, 0, 100, 2, 3000, 5000, 3000, 5000, 11, 24317, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Qeez - IC Timer - Cast Sunder Armor"),
-- Wave 2
(15392, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 6000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Tuubid - IC Timer - Cast Cleave on victim"),
(15392, 0, 1, 0, 0, 0, 100, 2, 3000, 5000, 3000, 5000, 11, 24317, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Tuubid - IC Timer - Cast Sunder Armor"),
-- TODO: Attack Order (spell 25471) - special handling (all adds must attack marked target) - linked yell: "Kill <name>!"
-- Wave 3
(15389, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 6000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Drenn - IC Timer - Cast Cleave on victim"),
(15389, 0, 1, 0, 0, 0, 100, 2, 3000, 5000, 3000, 5000, 11, 24317, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Drenn - IC Timer - Cast Sunder Armor"),
(15389, 0, 2, 0, 0, 0, 100, 2, 15000, 30000, 45000, 60000, 11, 26550, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, "Captain Drenn - IC Timer - Cast Lightning Cloud"),
-- Wave 4
(15390, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 6000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Xurrem - IC Timer - Cast Cleave on victim"),
(15390, 0, 1, 0, 0, 0, 100, 2, 3000, 5000, 3000, 5000, 11, 24317, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Xurrem - IC Timer - Cast Sunder Armor"),
(15390, 0, 2, 0, 0, 0, 100, 2, 7000, 12000, 15000, 22000, 11, 25425, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Captain Xurrem - IC Timer - Cast Shockwave"),
-- Wave 5
(15386, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 6000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Major Yeggeth - IC Timer - Cast Cleave on victim"),
(15386, 0, 1, 0, 0, 0, 100, 2, 3000, 5000, 3000, 5000, 11, 24317, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Major Yeggeth - IC Timer - Cast Sunder Armor"),
(15386, 0, 2, 0, 0, 0, 100, 2, 15000, 22000, 45000, 60000, 11, 25282, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Major Yeggeth - IC Timer - Cast Shield of Rajaxx"),
-- Wave 6
(15388, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 6000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Major Pakkon - IC Timer - Cast Cleave on victim"),
(15388, 0, 1, 0, 0, 0, 100, 2, 3000, 5000, 3000, 5000, 11, 24317, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Major Pakkon - IC Timer - Cast Sunder Armor"),
(15388, 0, 2, 0, 0, 0, 100, 2, 15000, 22000, 45000, 60000, 11, 25322, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Major Pakkon - IC Timer - Cast Sweeping Slam"),
-- Wave 7
(15385, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 6000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Colonel Zerran - IC Timer - Cast Cleave on victim"),
(15385, 0, 1, 0, 0, 0, 100, 2, 3000, 5000, 3000, 5000, 11, 24317, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Colonel Zerran - IC Timer - Cast Sunder Armor"),
(15385, 0, 2, 0, 0, 0, 100, 2, 500, 500, 60000, 60000, 11, 25462, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Colonel Zerran - IC Timer - Cast Enlarge"),
-- All waves
(15344, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 6000, 10000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Swarmguard Needler - IC Timer - Cast Cleave"),
(15387, 0, 1, 0, 0, 0, 100, 2, 12000, 15000, 22000, 30000, 11, 15588, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Qiraji Warrior - IC Timer - Cast Thunderclap"),
(15387, 0, 2, 0, 2, 0, 100, 3, 10, 15, 0, 0, 11, 8599, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Qiraji Warrior - 10-15% Health - Cast Enrage");