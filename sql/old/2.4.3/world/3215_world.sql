UPDATE quest_template SET specialFlags = 2 WHERE entry = 1558;

DELETE FROM areatrigger_scripts WHERE entry = 3548;
INSERT INTO areatrigger_scripts VALUES (3548, "at_childweek_quest1558");
