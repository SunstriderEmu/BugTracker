UPDATE quest_template SET specialFlags = 2 WHERE entry = 1479;

DELETE FROM areatrigger_scripts WHERE entry = 3546;
INSERT INTO areatrigger_scripts VALUES (3546, "at_childweek_quest1479");
