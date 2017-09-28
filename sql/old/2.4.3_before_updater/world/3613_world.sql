UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 16544;

DELETE FROM smart_scripts WHERE entryorguid = 16544;
INSERT INTO smart_scripts VALUES
(16544, 0, 0, 0, 4, 0, 100, 2, 0, 0, 0, 0, 11, 29982, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Spatial Distortion on self on aggro"),
(16544, 0, 1, 0, 9, 0, 100, 3, 0, 1, 1000, 1000, 11, 30013, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Disarm on target when reaching melee"),
(16544, 0, 2, 0, 0, 0, 100, 2, 12000, 18000, 12000, 18000, 11, 30013, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Disarm on target"),
(16544, 0, 3, 0, 0, 0, 100, 2, 5000, 8000, 8000, 10000, 11, 30014, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Cleave on target"),
(16544, 0, 4, 0, 5, 0, 100, 2, 500, 500, 500, 500, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text on unit kill"),
(16544, 0, 5, 0, 6, 0, 100, 2, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text on death");

DELETE FROM creature_text WHERE entry = 16544;
INSERT INTO creature_text VALUES
(16544, 1, 0, "Faites demi-tour tant qu'il est encore temps !", 1, 0, 100, 0, 1000, 0, "On unit kill"),
(16544, 2, 0, "Vous n'allez réussir qu'à vous maudire vous-mêmes !", 1, 0, 100, 0, 1000, 0, "On death");
