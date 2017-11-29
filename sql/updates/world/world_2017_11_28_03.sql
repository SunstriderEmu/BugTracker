-- GT1 Thrall
UPDATE creature_template SET ArmorModifier = 1 WHERE entry = 17876;
-- GT1 Armorer
UPDATE creature_template SET ArmorModifier = 1 WHERE entry = 18764;
-- GT1 : Some guards faction
UPDATE creature_template SET faction = 14 WHERE entry IN (18093, 18094, 18092);