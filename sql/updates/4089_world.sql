UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17682;
UPDATE gameobject_template SET AIName = "SmartGameObjectAI" WHERE entry = 181928;

DELETE FROM smart_scripts WHERE entryorguid IN (17682, 181928);
INSERT INTO smart_scripts VALUES
(17682, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 5, 181928, 1000, 1, 20, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 9667 - NPC"),
(181928, 1, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 4, 17682, 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 9667 - Cage");

DELETE FROM creature_text WHERE entry = 17682;
INSERT INTO creature_text VALUES
(17682, 0, 0, "Merci de m'avoir sauvée ! Mon père va être fou de joie !", 0, 0, 100, 0, 0, 0, "Princess Stillpine");

UPDATE creature SET orientation = 4.8099 WHERE id = 17682;
