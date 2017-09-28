UPDATE creature_loot_template SET ChanceOrQuestChance = 100 WHERE entry = 20184 AND item = 43002;
UPDATE creature_loot_template SET groupid = 0 WHERE entry = 20184 AND item IN (43001, 43002, 43006);
