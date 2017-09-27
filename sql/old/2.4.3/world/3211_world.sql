UPDATE quest_template SET specialFlags = 2 WHERE entry = 911;

DELETE FROM areatrigger_scripts WHERE entry = 3549;
INSERT INTO areatrigger_scripts VALUES (3549, "at_childweek_quest911");
