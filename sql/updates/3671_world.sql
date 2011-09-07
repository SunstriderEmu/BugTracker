UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 24972;

DELETE FROM smart_scripts WHERE entryorguid = 24972;
INSERT INTO smart_scripts VALUES
(24972, 0, 0, 0, 0, 0, 100, 0, 2000, 5000, 8000, 10000, 11, 45336, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Electrical Overload on target"),
(24972, 0, 1, 0, 0, 0, 100, 0, 1000, 5000, 2000, 5000, 11, 33688, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Crystal Strike on target"),
(24972, 0, 2, 0, 0, 0, 100, 0, 12000, 15000, 20000, 25000, 11, 35892, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Suppression on target"),
(24972, 0, 4, 0, 8, 0, 100, 0, 44997, 0, 500, 500, 41, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Force despawn");

UPDATE item_template SET ScriptName = "" WHERE entry = 34368;
