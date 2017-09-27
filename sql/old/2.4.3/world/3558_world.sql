UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22461;

DELETE FROM smart_scripts WHERE entryorguid = 22461;
INSERT INTO smart_scripts VALUES
(22461, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Block combat movement at spawn"),
(22461, 0, 1, 0, 0, 0, 100, 0, 500, 500, 3000, 3000, 11, 36238, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Fel Cannon Blast on victim");
