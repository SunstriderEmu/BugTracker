UPDATE creature_template SET mechanic_immune_mask = mechanic_immune_mask & ~0x10 WHERE entry IN (25373, 25485);
