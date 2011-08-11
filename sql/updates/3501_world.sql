UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (23028, 22963);

DELETE FROM spell_script_target WHERE entry = 40851;
INSERT INTO spell_script_target VALUES (40851, 1, 22963);

DELETE FROM smart_scripts WHERE entryorguid IN (23028, 22963);
INSERT INTO smart_scripts VALUES
(23028, 0, 0, 0, 0, 0, 100, 2, 10000, 10000, 30000, 45000, 11, 40851, 1, 0, 0, 0, 0, 19, 22963, 0, 0, 0, 0, 0, 0, "Cast Disgruntled on Bonechewer Worker"),
(22963, 0, 0, 0, 2, 0, 100, 3, 1, 5, 500, 500, 11, 40845, 1, 0, 0, 0, 0, 19, 23028, 0, 0, 0, 0, 0, 0, "Cast Fury on Bonechewer Taskmaster"),
(22963, 0, 1, 0, 0, 0, 100, 3, 500, 500, 25000, 25000, 11, 40844, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Throw Pick on aggro");
