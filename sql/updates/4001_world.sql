UPDATE quest_template SET ReqCreatureOrGOId1 = 18369 WHERE entry = 9955;
UPDATE gameobject_template SET AIName = "SmartGameObjectAI", ScriptName = "" WHERE entry = 182521;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "", npcflag = npcflag & ~0x1, flags_extra = 2 WHERE entry = 18369;
UPDATE creature_template SET faction_a = 35, faction_h = 35 WHERE entry = 18428;

DELETE FROM smart_scripts WHERE entryorguid IN (182521, 18369);
INSERT INTO smart_scripts VALUES
(182521, 1, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 4, 18369, 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 9955 - Cage"),
(18369, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 5, 182521, 1000, 0, 0.5, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quest 9955 - NPC");

DELETE FROM creature_text WHERE entry = 18369;
INSERT INTO creature_text VALUES
(18369, 0, 0, "Merci ! Ça fait combien de fois que vous me sauvez la vie ? Trois ? Pour moi, c'est comme si on était du même sang !", 0, 0, 100, 0, 0, 0, "Corki");
