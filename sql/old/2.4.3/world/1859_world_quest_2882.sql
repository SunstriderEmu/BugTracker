DELETE FROM `waypoint_data` WHERE `id` IN (2090, 2091, 2092, 2093, 2094);

INSERT INTO `waypoint_data`(`id`,`point`,`position_x`,`position_y`,`position_z`,`delay`,`move_flag`) VALUES
(2090,1,-10090.72,-4047.45,6.21,500,1),
(2090,2,-10117.05,-4055.85,5.42,1000,0),
(2090,3,-10117.52,-4080.50,3.88,90000,0);

INSERT INTO `waypoint_data`(`id`,`point`,`position_x`,`position_y`,`position_z`,`delay`,`move_flag`) VALUES
(2091,1,-10090.72,-4047.45,6.21,0,1),
(2091,2,-10117.05,-4055.85,5.42,1000,0),
(2091,3,-10119.52,-4080.50,3.88,90000,0);

INSERT INTO `waypoint_data`(`id`,`point`,`position_x`,`position_y`,`position_z`,`delay`,`move_flag`) VALUES
(2092,1,-10090.72,-4045.45,6.21,0,1),
(2092,2,-10119.70,-4050.45,5.33,1500,0),
(2092,3,-10151.39,-4046.32,3.22,90000,0);

INSERT INTO `waypoint_data`(`id`,`point`,`position_x`,`position_y`,`position_z`,`delay`,`move_flag`) VALUES
(2093,1,-10090.72,-4045.45,6.21,0,1),
(2093,2,-10119.70,-4050.45,5.33,1500,0),
(2093,3,-10151.39,-4048.32,3.22,90000,0);

INSERT INTO `waypoint_data`(`id`,`point`,`position_x`,`position_y`,`position_z`,`delay`,`move_flag`) VALUES
(2094,1,-10090.72,-4045.45,6.21,500,1),
(2094,2,-10119.70,-4050.45,5.33,1500,0),
(2094,3,-10151.39,-4050.32,3.22,90000,0);

DELETE FROM `gameobject` WHERE `id` = 142189;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(17498, 142189, 1, 1, -10119.7, -4052.46, 5.33005, -0.366519, 0, 0, 0.182236, -0.983255, 900, 100, 1);

UPDATE `gameobject_template` SET `ScriptName` = 'go_landmark_treasure' WHERE `entry` =  142189;
