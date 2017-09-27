DELETE FROM eventai_scripts WHERE id = 2060002;
INSERT INTO eventai_scripts VALUES (2060002, 20600, 6, 0, 100, 0, 0, 0, 0, 0, 104, 185569, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Maggoc - Summon Treasure Chest on Death");
DELETE FROM creature_loot_template WHERE entry = 20600 AND item = 32380;
