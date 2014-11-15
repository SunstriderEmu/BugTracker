#changing some db scriptings commands id

#SCRIPT_COMMAND_STOP_WP -> 25
UPDATE quest_start_scripts SET command = 25 WHERE command = 20;
UPDATE spell_scripts SET command = 25 WHERE command = 20;
UPDATE gameobject_scripts SET command = 25 WHERE command = 20;
UPDATE event_scripts SET command = 25 WHERE command = 20;
UPDATE waypoint_scripts SET command = 25 WHERE command = 20;
#SCRIPT_COMMAND_LOAD_PATH -> 20
UPDATE quest_start_scripts SET command = 20 WHERE command = 16;
UPDATE spell_scripts SET command = 20 WHERE command = 16;
UPDATE gameobject_scripts SET command = 20 WHERE command = 16;
UPDATE event_scripts SET command = 20 WHERE command = 16;
UPDATE waypoint_scripts SET command = 20 WHERE command = 16;
#SCRIPT_COMMAND_CALLSCRIPT_TO_UNIT -> 21
UPDATE quest_start_scripts SET command = 21 WHERE command = 17;
UPDATE spell_scripts SET command = 21 WHERE command = 17;
UPDATE gameobject_scripts SET command = 21 WHERE command = 17;
UPDATE event_scripts SET command = 21 WHERE command = 17;
UPDATE waypoint_scripts SET command = 21 WHERE command = 17;
#SCRIPT_COMMAND_KILL -> 22
UPDATE quest_start_scripts SET command = 22 WHERE command = 19;
UPDATE spell_scripts SET command = 22 WHERE command = 19;
UPDATE gameobject_scripts SET command = 22 WHERE command = 19;
UPDATE event_scripts SET command = 22 WHERE command = 19;
UPDATE waypoint_scripts SET command = 22 WHERE command = 19;
#SCRIPT_COMMAND_PLAYSOUND -> 16
UPDATE quest_start_scripts SET command = 16 WHERE command = 18;
UPDATE spell_scripts SET command = 16 WHERE command = 18;
UPDATE gameobject_scripts SET command = 16 WHERE command = 18;
UPDATE event_scripts SET command = 16 WHERE command = 18;
UPDATE waypoint_scripts SET command = 16 WHERE command = 18;