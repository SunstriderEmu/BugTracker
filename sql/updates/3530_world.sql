UPDATE creature SET spawnMask = 0 WHERE id = 20794 AND map = 530;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 20132;

DELETE FROM smart_scripts WHERE entryorguid = 20132;
INSERT INTO smart_scripts VALUES
(20132, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 19, 0x100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Remove OOC_NOT_ATTACKABLE flag at reset"),
(20132, 0, 1, 0, 0, 0, 100, 0, 2000, 5000, 10000, 15000, 11, 15496, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Cleave on victim"),
(20132, 0, 2, 0, 0, 0, 100, 0, 5000, 8000, 20000, 22000, 11, 37537, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Backslash on victim"),
(20132, 0, 3, 0, 0, 0, 100, 0, 15000, 15000, 30000, 35000, 11, 37540, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Fireball Barrage on random"),
(20132, 0, 4, 0, 0, 0, 100, 0, 100, 100, 25000, 30000, 11, 37539, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Nether Protection on self"),
(20132, 0, 5, 0, 0, 0, 100, 0, 3000, 3000, 30000, 38000, 11, 37538, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Anti-Magic Shield on self"),
(20132, 0, 6, 0, 0, 0, 100, 0, 20000, 22000, 20000, 25000, 11, 28448, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Shadow Bolt Volley on random");
