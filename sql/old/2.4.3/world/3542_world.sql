UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 15440;

DELETE FROM smart_scripts WHERE entryorguid = 15440;
INSERT INTO smart_scripts VALUES
(15440, 0, 0, 1, 64, 0, 100, 0, 0, 0, 0, 0, 56, 20810, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Add Signed Field Duty Papers on GossipHello"),
(15440, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 57, 23024, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Remove Prepared Field Duty Papers on GossipHello");
