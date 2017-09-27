UPDATE eventai_texts SET content_loc2 = "Que les sables vous avalent !" WHERE entry = -320;
UPDATE eventai_texts SET content_loc2 = "Mourrez !" WHERE entry = -212;
DELETE FROM eventai_texts WHERE entry = -688;
INSERT INTO eventai_texts (entry, content_default, content_loc2, type, comment) VALUES (-688, "How dare you enter my sanctuary!", "Comment osez-vous entrer dans mon sanctuaire !", 1, "7271");
UPDATE eventai_scripts SET action2_type = 1, action2_param1 = -688 WHERE id = 727101;
UPDATE creature_loot_template SET ChanceOrQuestChance = 0 WHERE entry = 7271 AND item IN (18082, 18083);
