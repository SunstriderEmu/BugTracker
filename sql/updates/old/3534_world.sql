UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 21387;

DELETE FROM smart_scripts WHERE entryorguid IN (21387, 2138700);
INSERT INTO smart_scripts VALUES
(21387, 0, 0, 0, 8, 0, 100, 0, 38177, 0, 0, 0, 80, 2138700, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Run script at SpellHit"),
(2138700, 9, 0, 0, 0, 0, 100, 0, 500, 500, 0, 0, 85, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Stop combat"),
(2138700, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 11, 38178, 1, 0, 0, 0, 0, 18, 10, 0, 0, 0, 0, 0, 0, "Cast credit on players"),
(2138700, 9, 2, 0, 0, 0, 100, 0, 500, 500, 0, 0, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Suicide ourself");
