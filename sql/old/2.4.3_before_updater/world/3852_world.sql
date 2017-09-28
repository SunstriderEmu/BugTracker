UPDATE gameobject_template SET data1 = 3701, AIName = "SmartGameObjectAI" WHERE entry = 153556;
DELETE FROM smart_scripts WHERE entryorguid = 153556;
INSERT INTO smart_scripts VALUES (153556, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 86, 153556, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Thaurissan Relic - Validate quest 3701 on gossip hello");
