-- Setting correct npcflag & ScriptName for Lakka
UPDATE creature_template SET npcflag = 1, ScriptName = "npc_lakka" WHERE entry = 18956;
-- Adding spawn
DELETE FROM creature WHERE id = 18956;
INSERT INTO creature(id, map, spawnMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, DeathState, MovementType)
    VALUES(18956, 556, 3, 0, 0, -160.009, 151.617, 0.0104124, 1.01395, 25, 0, 0, 8700, 0, 0, 0);
