#use orientation to mark already altered column, just to make sure we dont fuck everything if re applying this
# 0 say -> CHAT_TYPE_SAY 0
# nothing to do

# 1 whisper -> CHAT_TYPE_WHISPER 4
UPDATE quest_start_scripts SET datalong = 4 WHERE command = 0 AND datalong = 1 AND o < 0.01;
UPDATE quest_end_scripts SET datalong = 4 WHERE command = 0 AND datalong = 1 AND o < 0.01;
UPDATE spell_scripts SET datalong = 4 WHERE command = 0 AND datalong = 1 AND o < 0.01;
UPDATE spell_scripts SET datalong = 4 WHERE command = 0 AND datalong = 1 AND o < 0.01;
UPDATE gameobject_scripts SET datalong = 4 WHERE command = 0 AND datalong = 1 AND o < 0.01;
UPDATE event_scripts SET datalong = 4 WHERE command = 0 AND datalong = 1 AND o < 0.01;
UPDATE waypoint_scripts SET datalong = 4 WHERE command = 0 AND datalong = 1 AND o < 0.01;

#2 yell -> CHAT_TYPE_YELL 1
UPDATE quest_start_scripts SET datalong = 1 WHERE command = 0 AND datalong = 2 AND o < 0.01;
UPDATE quest_end_scripts SET datalong = 1 WHERE command = 0 AND datalong = 2 AND o < 0.01;
UPDATE spell_scripts SET datalong = 1 WHERE command = 0 AND datalong = 2 AND o < 0.01;
UPDATE spell_scripts SET datalong = 1 WHERE command = 0 AND datalong = 2 AND o < 0.01;
UPDATE gameobject_scripts SET datalong = 1 WHERE command = 0 AND datalong = 2 AND o < 0.01;
UPDATE event_scripts SET datalong = 1 WHERE command = 0 AND datalong = 2 AND o < 0.01;
UPDATE waypoint_scripts SET datalong = 1 WHERE command = 0 AND datalong = 2 AND o < 0.01;

#3 emote -> CHAT_TYPE_TEXT_EMOTE 2
UPDATE quest_start_scripts SET datalong = 2 WHERE command = 0 AND datalong = 3 AND o < 0.01;
UPDATE quest_end_scripts SET datalong = 2 WHERE command = 0 AND datalong = 3 AND o < 0.01;
UPDATE spell_scripts SET datalong = 2 WHERE command = 0 AND datalong = 3 AND o < 0.01;
UPDATE spell_scripts SET datalong = 2 WHERE command = 0 AND datalong = 3 AND o < 0.01;
UPDATE gameobject_scripts SET datalong = 2 WHERE command = 0 AND datalong = 3 AND o < 0.01;
UPDATE event_scripts SET datalong = 2 WHERE command = 0 AND datalong = 3 AND o < 0.01;
UPDATE waypoint_scripts SET datalong = 2 WHERE command = 0 AND datalong = 3 AND o < 0.01;

# mark all as done
UPDATE quest_start_scripts SET o = 0.01 WHERE command = 0;
UPDATE quest_end_scripts SET o = 0.01 WHERE command = 0;
UPDATE spell_scripts SET o = 0.01 WHERE command = 0;
UPDATE spell_scripts SET o = 0.01 WHERE command = 0;
UPDATE gameobject_scripts SET o = 0.01 WHERE command = 0;
UPDATE event_scripts SET o = 0.01 WHERE command = 0;
UPDATE waypoint_scripts SET o = 0.01 WHERE command = 0;
