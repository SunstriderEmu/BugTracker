UPDATE script_texts SET content_loc2 = "Drainez la fille ! Drainez toute sa puissance, qu'il n'en reste qu'une coquille vide !" WHERE entry = -1580070;
UPDATE script_texts SET content_loc2 = "Echouez, et vous souffrirez pour l'éternité !" WHERE entry = -1580069;
UPDATE script_texts SET content_loc2 = "J'ai assez attendu !" WHERE entry = -1580068;
UPDATE script_texts SET content_loc2 = "Continuez ! Ne perdez pas de temps !", content_default = "Stay on task! Do not waste time" WHERE entry = -1580067;
UPDATE script_texts SET content_loc2 = "Tous mes plans aboutissent ici !" WHERE entry = -1580066;

UPDATE creature_template SET scriptname = "trigger_death_cloud", flags_extra = 129 WHERE entry = 25703;

DELETE FROM waypoint_data WHERE id = 25038;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z) VALUES
(25038, 0, 1464.687378, 656.609558, 48.756775),
(25038, 1, 1492.565796, 642.713074, 48.756775),
(25038, 2, 1451.704590, 568.224365, 48.999962),
(25038, 3, 1489.954346, 555.354065, 48.062958),
(25038, 4, 1503.633301, 580.513977, 48.948380),
(25038, 5, 1451.850342, 629.153320, 48.739479);
