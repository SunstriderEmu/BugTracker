UPDATE gameobject_template SET flags = 0 WHERE entry = 160845;
UPDATE npc_text SET text0_0 = "Vous ne pouvez pas étudier si vous ne connaissez pas les bases. Parlez avec Kamari si vous voulez apprendre." WHERE ID = 5353;
UPDATE gameobject_loot_template SET lootcondition = 0, condition_value1 = 0 WHERE item = 6172;
INSERT INTO gameobject_involvedrelation (id, quest) VALUES (141980, 2701);
DELETE FROM creature_involvedrelation WHERE quest = 2701 AND id = 7750;
UPDATE creature_loot_template SET ChanceOrQuestChance = -1 WHERE item = 13815;
UPDATE creature_template SET scriptname = "npc_magni_bronzebeard" WHERE entry = 2784;
UPDATE creature_loot_template SET ChanceOrQuestChance = 80 WHERE item = 9371;

