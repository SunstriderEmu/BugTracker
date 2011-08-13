UPDATE creature SET spawnMask = 0 WHERE id = 20794 AND map = 530;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 20132;

DELETE FROM smart_scripts WHERE entryorguid = 20132;
INSERT INTO smart_scripts VALUES
(20132, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 19, 0x100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Remove OOC_NOT_ATTACKABLE flag at reset"),
(20132, 0, 1, 0, 4, 
