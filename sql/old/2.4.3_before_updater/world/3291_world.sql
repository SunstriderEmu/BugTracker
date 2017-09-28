UPDATE creature_template SET mechanic_immune_mask = mechanic_immune_mask | 0x820051 WHERE entry = 25851;
UPDATE creature_template SET mechanic_immune_mask = mechanic_immune_mask | 0x10 WHERE entry IN (25506, 25486, 25483, 25373, 25485, 25851, 25373, 25485);
