UPDATE gameobject_template SET flags = flags | 0x4 | 0x10 WHERE entry = 185952;
UPDATE creature_template SET ScriptName = "npc_skyguard_prisoner" WHERE entry = 23383;

DELETE FROM escort_waypoints WHERE entry = 23383;
INSERT INTO escort_waypoints VALUES
(23383, 0, -4109.187988, 3035.756104, 344.107330, 0, ""),
(23383, 1, -4117.319824, 3034.286377, 344.069733, 0, ""),
(23383, 2, -4125.014160, 3025.541748, 344.151367, 0, ""),
(23383, 3, -4129.055664, 3026.356934, 344.013489, 0, ""),
(23383, 4, -4147.939453, 3030.165283, 336.942352, 0, ""),
(23383, 5, -4162.532227, 3033.108398, 338.735657, 0, ""),
(23383, 6, -4173.444824, 3035.309326, 343.310089, 0, ""),
(23383, 7, -4176.087402, 3045.384521, 343.973389, 0, ""),
(23383, 8, -4178.576172, 3055.109375, 344.058380, 0, ""),
(23383, 9, -4183.550293, 3062.051270, 344.143097, 0, ""),
(23383, 10, -4182.639160, 3067.029541, 341.326538, 0, ""),
(23383, 11, -4181.441406, 3073.570801, 334.612213, 0, ""),
(23383, 12, -4180.008789, 3081.392822, 328.085693, 0, ""),
(23383, 13, -4178.566406, 3089.269775, 323.887512, 0, ""),
(23383, 14, -4175.484863, 3095.865234, 323.366913, 3000, "SAY_SKYGUARD_PRISONER_THANKS"),
(23383, 15, -4160.078613, 3100.822754, 320.009003, 0, "");

DELETE FROM script_texts WHERE entry BETWEEN -1000827 AND -1000825;
INSERT INTO script_texts (entry, content_default, content_loc2, comment) VALUES
(-1000825, "Thanks for your help. Let's get out of here!", "Merci de votre aide. Barrons-nous d'ici !", "SAY_SKYGUARD_PRISONER_START"),
(-1000826, "Let's keep moving. I don't like this place.", "Continuons à avancer. Je n'aime pas cet endroit.", "SAY_SKYGUARD_PRISONER_CONTINUE"),
(-1000827, "Thanks again. Sergeant Doryn will be glad to hear he has one less scout to replace this week.", "Encore merci. Le sergent Doryn sera heureux de savoir qu'il a un éclaireur de moins à remplacer cette semaine.", "SAY_SKYGUARD_PRISONER_THANKS");

DELETE FROM creature WHERE id = 23383;
INSERT INTO `creature` VALUES ('',23383,530,1,21169,0,-4106.64,3029.76,344.877,0.820305,25,0,0,9250,0,0,0,0,'');

UPDATE quest_template SET SpecialFlags = SpecialFlags | 0x2 WHERE entry = 11085;
