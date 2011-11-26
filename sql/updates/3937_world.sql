UPDATE item_loot_template SET ChanceOrQuestChance = 0, groupid = 1 WHERE entry = 21270;
INSERT INTO item_loot_template VALUES (21270, 21241, 0, 1, 5, 5, 0, 0, 0);

INSERT INTO item_loot_template VALUES (34426, 34425, 100, 0, 1, 1, 0, 0, 0);

UPDATE item_loot_template SET ChanceOrQuestChance = 0, groupid = 1 WHERE entry = 21310;

UPDATE item_loot_template SET ChanceOrQuestChance = 100 WHERE entry = 21327;
INSERT INTO item_loot_template VALUES (21327, 17725, 0, 1, 1, 1, 0, 0, 0), (21327, 17722, 0, 1, 1, 1, 0, 0, 0), (21327, 17706, 0, 1, 1, 1, 0, 0, 0), (21327, 17720, 0, 1, 1, 1, 0, 0, 0), (21327, 17724, 0, 1, 1, 1, 0, 0, 0), (21327, 17709, 0, 1, 1, 1, 0, 0, 0);
