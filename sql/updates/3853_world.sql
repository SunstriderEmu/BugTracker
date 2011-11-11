UPDATE gameobject_template SET AIName = "SmartGameObjectAI" WHERE entry = 179544;
DELETE FROM smart_scripts WHERE entryorguid = 179544;
INSERT INTO smart_scripts VALUES (179544, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 15, 7482, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Skeletal Remains of Kariel Winthalus - Complete quest 7482 on gossip hello");
