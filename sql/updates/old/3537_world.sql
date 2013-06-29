UPDATE gameobject_template SET AIName = "SmartGameObjectAI", ScriptName = "" WHERE entry = 176581;

DELETE FROM smart_scripts WHERE entryorguid = 176581;
INSERT INTO smart_scripts VALUES
(176581, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 12, 11876, 6, 15000, 0, 0, 0, 8, 0, 0, 0, -345.394745, 1760.128174, 138.370956, 2.290092, "Summon Demon Spirit on GOHello");
