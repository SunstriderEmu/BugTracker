DELETE FROM creature WHERE id IN (23353, 23354, 22281, 23355);
UPDATE creature_template SET faction_a = 90, faction_h = 90 WHERE entry IN (23353, 23354, 22281, 23355);
UPDATE creature_template SET scriptname = "npc_galvanoth" WHERE entry = 22281;
UPDATE creature_template SET scriptname = "npc_braxxus" WHERE entry = 23353;
UPDATE creature_template SET scriptname = "npc_moarg_incinerator" WHERE entry = 23354;
UPDATE creature_template SET scriptname = "npc_zarcsin" WHERE entry = 23355;
UPDATE creature_loot_template SET ChanceOrQuestChance = -100 WHERE item = 32733;
UPDATE gameobject_template SET scriptname = "go_fel_crystal_prism" WHERE entry = 185927;

DELETE FROM gameobject WHERE id = 185927;
INSERT INTO gameobject (id, map, spawnmask, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state) VALUES
(185927,530,1,2810.34,7006.05,376.088,1.15192,0,0,0.544639,0.838671,180,100,1),
(185927,530,1,3080.45,6914.96,371.14,3.13038,0,0,0.999984,0.0056061,25,0,1),
(185927,530,1,2908.54,6796.65,368.028,0.0193302,0,0,0.00966496,0.999953,25,0,1),
(185927,530,1,2988.6,7130.01,369.602,5.57996,0,0,0.344415,-0.938818,25,0,1),
(185927,530,1,1617.25,7207.19,377.492,6.21014,0,0,0.0365128,-0.999333,25,0,1),
(185927,530,1,1673.09,7376.83,377.205,1.28177,0,0,0.597906,0.801566,25,0,1),
(185927,530,1,1385.33,7390.72,373.195,2.14986,0,0,0.879556,0.475796,25,0,1),
(185927,530,1,1280.13,7164.64,378.194,4.39196,0,0,0.810857,-0.585245,25,0,1);
