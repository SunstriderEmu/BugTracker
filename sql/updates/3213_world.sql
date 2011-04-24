UPDATE quest_template SET specialFlags = 2 WHERE entry = 910;

DELETE FROM areatrigger_scripts WHERE entry = 3550;
INSERT INTO areatrigger_scripts VALUES (3550, "at_childweek_quest910");
