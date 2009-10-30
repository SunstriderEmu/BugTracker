INSERT INTO gameobject_scripts VALUES(44735, 2, 10, 21319, 30000, 0, 1317.180054, 6694.919922, -18.881399, 5.090830); -- Spawn the ogre
UPDATE creature_template SET Faction_H = 1781, Faction_A = 1781 WHERE entry = 21319; -- Spawned ogre had wrong faction ID
