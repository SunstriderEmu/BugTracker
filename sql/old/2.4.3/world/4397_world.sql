UPDATE creature_loot_template SET ChanceOrQuestChance = 100 WHERE item = 17309;

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 8521;
DELETE FROM smart_scripts WHERE entryorguid = 8521;
INSERT INTO smart_scripts VALUES (8521, 0, 0, 0, 8, 0, 100, 0, 21332, 0, 0, 0, 36, 13279, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Blighted Horror - Update template on spell hit");
