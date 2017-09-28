UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22484;

DELETE FROM smart_scripts WHERE entryorguid = 22484;
INSERT INTO smart_scripts VALUES
(22484, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Follow master at spawn"),
(22484, 0, 1, 0, 66, 0, 100, 0, 18884, 0, 0, 0, 11, 39244, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Gather Warp Chaser Blood when Master killed Warp Chaser");
