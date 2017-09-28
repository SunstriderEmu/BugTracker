DELETE FROM reference_loot_template WHERE entry = 42999;
INSERT INTO reference_loot_template VALUES (42999, 30575, 0, 1, 1, 1, 0, 0, 0), (42999, 30582, 0, 1, 1, 1, 0, 0, 0), (42999, 30581, 0, 1, 1, 1, 0, 0, 0);
UPDATE creature_loot_template SET item = 42999, ChanceOrQuestChance = 30, mincountOrRef = -42999 WHERE entry = 21624 AND item = 43003;
