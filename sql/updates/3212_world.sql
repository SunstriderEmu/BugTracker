UPDATE quest_template SET specialFlags = 2 WHERE entry = 1800;

DELETE FROM areatrigger_scripts WHERE entry = 3547;
INSERT INTO areatrigger_scripts VALUES (3547, "at_childweek_quest1800");

