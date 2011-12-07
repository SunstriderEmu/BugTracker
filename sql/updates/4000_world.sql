UPDATE gameobject_template SET AIName = "SmartGameObjectAI", ScriptName = "" WHERE entry = 182350;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 20812;

DELETE FROM smart_scripts WHERE entryorguid IN (182350, 20812);
INSERT INTO smart_scripts VALUES
(182350, 1, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 4, 20812, 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 9924 - Cage"),
(20812, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 5, 182350, 1000, 1, 20, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 9924 - NPC");

DELETE FROM creature_text WHERE entry = 20812;
INSERT INTO creature_text VALUES
(20812, 0, 0, "C'est la dernière fois que je me fais attraper ! Promis ! Salut !", 0, 0, 100, 0, 0, 0, "Corki");
