UPDATE creature_template SET Faction_A = 14, Faction_H = 14 WHERE entry IN (23161, 23162, 23163, 23165);
UPDATE creature_onkill_reputation SET RewOnKillRepValue1 = 500 WHERE creature_id IN (23161, 23165, 23163, 23162);
