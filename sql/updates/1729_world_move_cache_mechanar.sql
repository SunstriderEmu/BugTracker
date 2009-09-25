-- Respawn the Caches in normal (spawnMask 1) and heroic version (spawnMask 2)
UPDATE gameobject SET spawnMask = 1 WHERE id = 184465;
UPDATE gameobject SET spawnMask = 2 WHERE id = 184849;

-- Add required key to open the Caches
-- UPDATE gameobject_template SET flags = 2 WHERE entry = 184465;
-- UPDATE gameobject_template SET flags = 2 WHERE entry = 184849;
-- Doesn't work, when flags = 2, loot window doesn't appear at all, CMSG_LOOT_RELEASE is called immediately...

-- Move the Caches near the last boss to avoid abusing farming
UPDATE gameobject SET position_x = 138.8253, position_y = 162.6093, position_z = 25.5798, orientation = 4.6613 WHERE id IN (184465, 184849) AND map = 554;
