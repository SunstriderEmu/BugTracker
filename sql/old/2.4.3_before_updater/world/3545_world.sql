UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 15609;

DELETE FROM smart_scripts WHERE entryorguid = 15609;
INSERT INTO smart_scripts VALUES
(15609, 0, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 56, 21160, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Add Hive'Regal Scout Report on GossipHello");
