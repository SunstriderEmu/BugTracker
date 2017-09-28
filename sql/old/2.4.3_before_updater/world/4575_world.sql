UPDATE gameobject_template SET AIName = "SmartGameObjectAI" WHERE entry = 177964;
DELETE FROM smart_scripts WHERE entryorguid = 177964;
INSERT INTO smart_scripts VALUES (177964, 1, 0, 0, 64, 0, 100, 1, 0, 0, 0, 0, 12, 12876, 1, 60000, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, "Summon Aquanis - Quest 908");

