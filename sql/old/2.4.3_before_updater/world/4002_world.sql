UPDATE gameobject_template SET AIName = "SmartGameObjectAI", ScriptName = "" WHERE entry = 185202;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22314;
UPDATE gameobject SET id = 185202 WHERE id IN (185203, 185204, 185205);

DELETE FROM smart_scripts WHERE entryorguid IN (185202, 22314);
INSERT INTO smart_scripts VALUES
(185202, 1, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 4, 22314, 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 10852 - Cage"),
(22314, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 5, 185202, 1000, 1, 20, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 10852 - NPC");

DELETE FROM creature_text WHERE entry = 22314;
INSERT INTO creature_text VALUES
(22314, 0, 0, "Beurk !", 0, 0, 100, 0, 0, 0, "Captive child"),
(22314, 0, 1, "Je crois que ces trucs-oiseaux bizarres allaient nous manger. Beurk !", 0, 0, 100, 0, 0, 0, "Captive child"),
(22314, 0, 2, "Ouais ! On vous adore ! Vous nous avez sauvés !", 0, 0, 100, 0, 0, 0, "Captive child");
