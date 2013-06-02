UPDATE smart_scripts SET event_flags = 3 WHERE entryorguid = 8127 AND id IN (0, 1);
UPDATE smart_scripts SET link = 1 WHERE entryorguid = 8127 AND id = 0;
UPDATE smart_scripts SET event_type = 61 WHERE entryorguid = 8127 AND id = 1;
