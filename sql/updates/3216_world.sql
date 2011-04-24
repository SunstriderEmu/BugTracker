UPDATE quest_template SET specialFlags = 2 WHERE entry = 1687;

DELETE FROM areatrigger_scripts WHERE entry = 3552;
INSERT INTO areatrigger_scripts VALUES (3552, "at_childweek_quest1687");
