INSERT INTO gameobject_scripts VALUES(50476, 2, 10, 22993, 30000, 0, -2627.925049, 4571.515137, 140.270767, 1.077514); -- Quest 10990
INSERT INTO gameobject_scripts VALUES(50477, 2, 10, 22994, 30000, 0, -3164.413574, 3811.696777, 59.153202, 4.664436); -- Quest 10991
UPDATE gameobject_template SET `type` = 10, flags = 4, displayId = 7351, `size` = 0.45, castBarCaption = "Summoning", data0 = 1691, data1 = 10992, data3 = 196608, data14 = 21062 WHERE entry = 185551; -- Quest 10992 - WDB data are just crazy about it...
UPDATE gameobject_template SET scriptname = "go_shrine_hawk" WHERE entry = 185551; -- SD2 script to work around the wrong data
