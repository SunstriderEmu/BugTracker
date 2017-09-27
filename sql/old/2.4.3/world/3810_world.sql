UPDATE creature_template SET minhealth = 12220, maxhealth = 12220, ScriptName = "boss_shade_of_horseman", flags_extra = 0 WHERE entry = 23543;
UPDATE creature_template SET flags_extra = 128, ScriptName = "npc_shade_of_horseman_bunny" WHERE entry = 23758;

DELETE FROM creature_template_addon WHERE entry = 23543;
INSERT INTO creature_template_addon (entry, mount) VALUES (23543, 22653);

DELETE FROM spell_script_target WHERE entry = 42339 AND targetEntry = 23758;
INSERT INTO spell_script_target VALUES (42339, 1, 23758);

DELETE FROM waypoint_data WHERE id BETWEEN 23758 AND 23763;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, move_flag) VALUES
-- Brill
(23758, 0, 2262.396484, 286.847351, 70.914734, 1),
(23758, 1, 2295.089844, 262.552582, 66.726143, 1),
(23758, 2, 2332.469971, 220.253510, 52.394009, 1),
(23758, 3, 2273.846191, 245.492844, 56.789700, 1),
(23758, 4, 2265.170410, 308.380188, 52.466187, 1),
(23758, 5, 2237.596191, 336.995636, 53.514088, 1),
(23758, 6, 2225.023193, 294.364349, 55.151421, 1),
(23758, 7, 2216.406250, 262.373047, 56.894348, 1),
(23758, 8, 2248.509277, 263.611084, 58.346222, 1),
-- Goldshire
(23759, 0, -9459.054688, 57.270653, 77.856445, 1),
(23759, 1, -9474.834961, 35.699390, 93.268852, 1),
(23759, 2, -9505.852539, 73.075935, 76.322426, 1),
(23759, 3, -9470.720703, 90.481514, 80.686844, 1),
(23759, 4, -9440.083008, 114.937874, 92.527725, 1),
(23759, 5, -9453.435547, 66.458511, 78.226898, 1),
(23759, 6, -9439.914062, 36.158966, 78.048073, 1),
-- Silvermoon
(23760, 0, 9518.760742, -6807.618164, 56.322880, 1),
(23760, 1, 9538.866211, -6774.463379, 38.299335, 1),
(23760, 2, 9509.365234, -6788.511719, 36.451454, 1),
(23760, 3, 9496.362305, -6773.986328, 35.429935, 1),
(23760, 4, 9552.111328, -6789.377441, 32.337513, 1),
(23760, 5, 9547.741211, -6832.890137, 33.596218, 1),
(23760, 6, 9501.386719, -6831.997070, 41.348606, 1),
(23760, 7, 9478.027344, -6789.735840, 34.450279, 1),
-- Kharanos
(23761, 0, -5583.088379, -485.727509, 433.896271, 1),
(23761, 1, -5614.406738, -447.315704, 438.697388, 1),
(23761, 2, -5566.332520, -439.674744, 446.323242, 1),
(23761, 3, -5540.237793, -481.622101, 424.455139, 1),
(23761, 4, -5584.629395, -495.610626, 438.653503, 1),
(23761, 5, -5632.142578, -515.734680, 434.874878, 1),
(23761, 6, -5584.102051, -523.286316, 431.758270, 1),
(23761, 7, -5552.254883, -504.067230, 424.237823, 1),
-- Azure Watch
(23762, 0, -4190.686035, -12506.031250, 68.293228, 1),
(23762, 1, -4201.136719, -12477.631836, 63.538429, 1),
(23762, 2, -4159.308105, -12469.464844, 74.083244, 1),
(23762, 3, -4124.865723, -12501.916016, 66.903992, 1),
(23762, 4, -4151.417969, -12531.039062, 68.672585, 1),
(23762, 5, -4190.253418, -12554.699219, 68.106567, 1),
(23762, 6, -4227.607422, -12506.526367, 69.225388, 1),
-- Razor Hill
(23763, 0, 303.909485, -4746.700684, 42.853191, 1),
(23763, 1, 280.277954, -4723.163574, 26.879597, 1),
(23763, 2, 315.816315, -4705.532227, 32.346573, 1),
(23763, 3, 374.518768, -4711.586914, 36.441689, 1),
(23763, 4, 368.191162, -4755.639648, 30.382557, 1),
(23763, 5, 314.471680, -4764.357422, 41.902008, 1),
(23763, 6, 270.115234, -4749.185547, 23.382351, 1);

DELETE FROM game_event WHERE entry BETWEEN 51 AND 56;
INSERT INTO game_event VALUES
(51, TIMESTAMP('2011-10-22 00:00:00'), TIMESTAMP('2020-12-31 00:00:00'), 240, 16, "Shade of the Horseman - Brill", 0),
(52, TIMESTAMP('2011-10-22 00:40:00'), TIMESTAMP('2020-12-31 00:00:00'), 240, 16, "Shade of the Horseman - Goldshire", 0),
(53, TIMESTAMP('2011-10-22 01:20:00'), TIMESTAMP('2020-12-31 00:00:00'), 240, 16, "Shade of the Horseman - Silvermoon", 0),
(54, TIMESTAMP('2011-10-22 02:00:00'), TIMESTAMP('2020-12-31 00:00:00'), 240, 16, "Shade of the Horseman - Kharanos", 0),
(55, TIMESTAMP('2011-10-22 02:40:00'), TIMESTAMP('2020-12-31 00:00:00'), 240, 16, "Shade of the Horseman - Azure Watch", 0),
(56, TIMESTAMP('2011-10-22 03:20:00'), TIMESTAMP('2020-12-31 00:00:00'), 240, 16, "Shade of the Horseman - Razor Hill", 0);

DELETE FROM script_texts WHERE entry BETWEEN -1000728 AND -1000722;
INSERT INTO script_texts (entry, content_default, content_loc2, sound, `type`, `language`, comment) VALUES
(-1000722, "Prepare yourselves, the bells have tolled! Shelter your weak, your young and your old! Each of you shall pay the final sum! Cry for mercy; the reckoning has come!", "Ne soyez pas surpris, le toccin a sonné ! Mettez bien à l'abri infirmes, vieillards, enfants. Chacun aura le prix en entier à payer. Implorez ma merci, à l'heure du jugement !", 11966, 1, 0, "Shade of the Horse - YELL_BEGIN"),
(-1000723, "The sky is dark. The fire burns. You strive in vain as Fate's wheel turns.", "Le ciel est sombre. Le feu brûle. Vous combattez en vain alors que la roue du Destin tourne.", 0, 1, 0, "Shade of the Horseman - YELL_5_THROWS"),
(-1000724, "The town still burns. A cleansing fire! Time is short, I'll soon retire!", "La ville brûle toujours. Un feu purificateur ! Le temps est compté, je vais bientôt me retirer.", 0, 1, 0, "Shade of the Horseman - YELL_13_MINS"),
(-1000725, "My flames have died, left not a spark! I shall send you now to the lifeless dark!", "Mes flames ont décliné, plus un reflet n'y court. Je vais vous dérober votre vie, votre jour !", 11968, 1, 0, "Shade of the Horseman - YELL_FEW_FLAMES"),
(-1000726, "Fire consumes! You've tried and failed. Let there be no doubt, justice prevailed!", "Le festin du brasier scelle votre débâcle. Justice a triomphé en un ardent spectacle !", 11967, 1, 0, "Shade of the Horseman - YELL_MANY_FLAMES"),
(-1000727, "So eager you are, for my blood to spill. Yet to vanquish me, 'tis my head you must kill!", "Pour que coule mon sang, vous luttez sans faillir. C'est ma tête pourtant, qu'il vous faudra occire !", 11969, 1, 0, "Shade of the Horseman - YELL_DEATH"),
(-1000728, "Harken, cur! Tis you I spurn! Now feel... the burn!", "Ecoutez-moi ! Je vous repousse ! Maintenant, ressentez... La brûlure !", 0, 1, 0, "Shade of the Horseman - YELL_CONFLAG");
