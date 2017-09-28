UPDATE gameobject_template SET AIName = "SmartGameObjectAI", ScriptName = "" WHERE entry IN (180453, 180454, 180455);

DELETE FROM smart_scripts WHERE entryorguid IN (180453, 180454, 180455);
INSERT INTO smart_scripts VALUES
(180453, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 56, 20456, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Give Rubbing on GossipHello"),
(180454, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 56, 20455, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Give Rubbing on GossipHello"),
(180455, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 56, 20454, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Give Rubbing on GossipHello");
