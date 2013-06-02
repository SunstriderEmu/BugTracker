UPDATE quest_template SET prevquestid = 11357 WHERE entry IN (11361, 11449, 11450);
UPDATE quest_template SET prevquestid = 11356 WHERE entry IN (11360, 11440, 11439);

UPDATE waypoint_data SET move_flag = 1 WHERE id = 25038;

UPDATE script_texts SET content_default = "Felmyst takes a deep breath.", content_loc2 = "Gangrebrume prend une profonde respiration." WHERE entry = -1580110;
