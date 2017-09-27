-- Re-lock Cache
UPDATE gameobject_template SET flags = 2 WHERE entry IN (184465, 184849);

-- Respawn Cache
UPDATE gameobject SET spawnMask = 1 WHERE id = 184465;
UPDATE gameobject SET spawnMask = 2 WHERE id = 184849;

-- Replace Cache on blizzlike position
UPDATE gameobject SET position_x = 220.919556, position_y = 71.170021, position_z = -0.004599, orientation = 4.335697 WHERE id IN (184465, 184849) AND map = 554;

-- Fix Jagged Crystals loot
UPDATE creature_loot_template SET ChanceOrQuestChance = 100 WHERE item IN (30436, 30437);

-- Remove Cache loots from Pathaleon
DELETE FROM creature_loot_template WHERE entry = 21537 AND item IN (28248, 28249, 28250, 28251, 28252);
UPDATE creature_loot_template SET mincountOrRef = 1, maxcount = 1 WHERE entry = 21537 AND item = 29434;
