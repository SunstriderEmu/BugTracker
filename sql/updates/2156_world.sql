UPDATE `creature_template` SET `ScriptName` = 'npc_muglash' WHERE `creature_template`.`entry` = 12717;
UPDATE `gameobject` SET `state` = 1 WHERE `guid` =47873;
UPDATE `gameobject_template` SET `ScriptName` = 'go_naga_brazier' WHERE `gameobject_template`.`entry` = 178247;

DELETE FROM `script_texts` WHERE `entry` BETWEEN -1800063 AND -1800054;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
(-1800054, 'Are you sure that you are ready? If we do not have a group of your allies to aid us, we will surely fail.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_START1'),
(-1800055, 'This will be a though fight, $N. Follow me closely.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_START2'),
(-1800056, 'This is the brazier, $N. Put it out. Vorsha is a beast, worthy of praise from no one!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_BRAZIER'),
(-1800057, 'Now we must wait. It won''t be long before the naga realize what we have done.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_BRAZIER_WAIT'),
(-1800058, 'Be on your guard, $N!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_ON_GUARD'),
(-1800059, 'Perhaps we will get a moment to rest. But I will not give up until we have faced off against Vorsha!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_REST'),
(-1800060, 'We have done it!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_DONE'),
(-1800061, 'You have my deepest gratitude. I thank you.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_GRATITUDE'),
(-1800062, 'I am going to patrol the area for a while longer and ensure that things are truly safe.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_PATROL'),
(-1800063, 'Please return to Zoram''gar and report our success to the Warsong runner.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 'muglash SAY_MUG_RETURN');

DELETE FROM `escort_waypoints` WHERE `entry`=12717;
INSERT INTO `escort_waypoints` VALUES
(12717, 0, 3346.25, 1007.88, 3.59, 0, 'SAY_MUG_START2'),
(12717, 1, 3367.39, 1011.51, 3.72, 0, ''),
(12717, 2, 3418.64, 1013.96, 2.905, 0, ''),
(12717, 3, 3426.84, 1015.1, 3.449, 0, ''),
(12717, 4, 3437.03, 1020.79, 2.742, 0, ''),
(12717, 5, 3460.56, 1024.26, 1.353, 0, ''),
(12717, 6, 3479.87, 1037.96, 1.023, 0, ''),
(12717, 7, 3490.53, 1043.35, 3.338, 0, ''),
(12717, 8, 3504.28, 1047.77, 8.205, 0, ''),
(12717, 9, 3510.73, 1049.79, 12.143, 0, ''),
(12717, 10, 3514.41, 1051.17, 13.235, 0, ''),
(12717, 11, 3516.94, 1052.91, 12.918, 0, ''),
(12717, 12, 3523.64, 1056.3, 7.563, 0, ''),
(12717, 13, 3531.94, 1059.86, 6.175, 0, ''),
(12717, 14, 3535.48, 1069.96, 1.697, 0, ''),
(12717, 15, 3546.98, 1093.49, 0.68, 0, ''),
(12717, 16, 3549.73, 1101.88, -1.123, 0, ''),
(12717, 17, 3555.14, 1116.99, -4.326, 0, ''),
(12717, 18, 3571.94, 1132.18, -0.634, 0, ''),
(12717, 19, 3574.28, 1137.58, 3.684, 0, ''),
(12717, 20, 3579.31, 1137.25, 8.205, 0, ''),
(12717, 21, 3590.22, 1143.65, 8.291, 0, ''),
(12717, 22, 3595.97, 1145.83, 6.773, 0, ''),
(12717, 23, 3603.65, 1146.92, 9.763, 0, ''),
(12717, 24, 3607.08, 1146.01, 10.692, 5000, 'SAY_MUG_BRAZIER'),
(12717, 25, 3614.52, 1142.63, 10.248, 0, ''),
(12717, 26, 3616.66, 1140.84, 10.682, 3000, 'SAY_MUG_PATROL'),
(12717, 27, 3621.08, 1138.11, 10.369, 0, 'SAY_MUG_RETURN'),
(12717, 28, 3615.48, 1145.53, 9.614, 0, ''),
(12717, 29, 3607.19, 1152.72, 8.871, 0, '');
