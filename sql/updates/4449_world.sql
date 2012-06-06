DELETE FROM escort_waypoints WHERE entry = 3465;
INSERT INTO escort_waypoints VALUES (3465, 0, -2094.147217, -3648.204102, 61.716202, 0, "Start"), (3465, 1, -2100.020996, -3613.011963, 61.101109, 0, ""), (3465, 2, -2095.232422, -3596.354980, 57.249886, 0, ""), (3465, 3, -2065.825928, -3576.360840, 45.869682, 0, ""), (3465, 4, -2018.244141, -3570.602539, 23.093884, 0, ""), (3465, 5, -2010.714844, -3582.686768, 21.779972, 0, ""), (3465, 6, -2020.630127, -3614.086426, 21.759705, 0, ""), (3465, 7, -2016.179321, -3663.108643, 21.756626, 0, ""), (3465, 8, -1987.984741, -3687.576416, 18.683928, 0, ""), (3465, 9, -1942.271240, -3680.746094, 10.659886, 0, ""), (3465, 10, -1887.013184, -3696.228516, 6.967062, 2000, "Say thanks and run"), (3465, 11, -1851.558594, -3706.162354, 6.864869, 0, "Disappear and die, then respawn");

DELETE FROM creature_text WHERE entry = 3465;
INSERT INTO creature_text VALUES (3465, 0, 0, "Okay, let's go.", "OK, allons-y.", 0, 0, 100, 0, 0, 0, "TALK_GILTHARES_START"), (3465, 1, 0, "Thanks for helping me, goodbye!", "Merci de m'avoir aidé. Au revoir !", 0, 0, 100, 0, 0, 0, "TALK_GILTHARES_THANKS");

UPDATE creature_template SET AIName = "", ScriptName = "npc_gilthares_firebough" WHERE entry = 3465;

