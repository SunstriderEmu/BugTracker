
DROP TABLE IF EXISTS `db_script_string`;

UPDATE quest_start_scripts SET datalong2 = 0, dataint = 1 WHERE command = 3;
UPDATE quest_end_scripts SET datalong2 = 0, dataint = 1 WHERE command = 3;
UPDATE spell_scripts SET datalong2 = 0, dataint = 1 WHERE command = 3;
UPDATE spell_scripts SET datalong2 = 0, dataint = 1 WHERE command = 3;
UPDATE gameobject_scripts SET datalong2 = 0, dataint = 1 WHERE command = 3;
UPDATE event_scripts SET datalong2 = 0, dataint = 1 WHERE command = 3;
UPDATE waypoint_scripts SET datalong2 = 0, dataint = 1 WHERE command = 3;
