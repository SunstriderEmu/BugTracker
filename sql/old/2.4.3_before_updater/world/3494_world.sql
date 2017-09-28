UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22878;
UPDATE creature SET ScriptName = "" WHERE id = 22878;

DELETE FROM smart_scripts WHERE entryorguid = 22878;
INSERT INTO `smart_scripts` VALUES
(22878,0,0,0,0,0,100,2,5000,5000,20000,20000,11,40099,1,0,0,0,0,5,0,0,0,0,0,0,0,'Cast Vile Slime on random'),
(22878,0,1,0,0,0,100,2,18000,21000,25000,30000,11,40100,1,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Crashing Wave on tank'),
(22878,0,2,0,0,0,100,2,30000,30000,45000,45000,11,40106,1,0,0,0,0,19,22881,0,0,0,0,0,0,'Cast Merge on Aqueous Surger'),
(22878,0,3,0,0,0,100,2,8000,8000,45000,60000,12,22881,6,10000,0,0,0,1,0,0,0,0,0,0,0,'Summon Aqueous Surger');

INSERT INTO eventai_scripts VALUES (2288102, 22881, 1, 0, 100, 2, 15000, 15000, 15000, 15000, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Aqueous Surger - Die after 15 sec OOC");
