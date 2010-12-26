UPDATE quest_template SET RewRepFaction1 = 1031, RewRepValue1 = 500 WHERE entry = 11078;

UPDATE gameobject_template SET scriptname = "go_drake_egg" WHERE entry IN (185936, 185932, 185938, 185937);

DELETE FROM creature WHERE id IN (23061, 23282, 23281, 23261);
INSERT INTO creature (id, map, spawnmask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, deathstate, movementtype, pool_id, scriptname) VALUES
(23061,530,1,0,0,2064.69,7372.69,451.32,1.47611,300,50,0,184500,0,0,1,0,''),
(23261,530,1,0,0,3891.27,5227.05,350.09,-2.53073,300,50,0,184500,0,0,1,0,''),
(23281,530,1,0,0,4143.16,5441.75,354.26,1.72788,300,50,0,184500,0,0,1,0,''),
(23282,530,1,0,0,2426.8,7001.64,447.57,1.72788,300,50,0,184500,0,0,1,0,'');

UPDATE creature_template SET scriptname = "npc_rivendark" WHERE entry = 23061;
UPDATE creature_template SET scriptname = "npc_obsidia" WHERE entry = 23282;
UPDATE creature_template SET scriptname = "npc_insidion" WHERE entry = 23281;
UPDATE creature_template SET scriptname = "npc_furywing" WHERE entry = 23261;
