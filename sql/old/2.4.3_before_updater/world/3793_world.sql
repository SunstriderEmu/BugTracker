UPDATE quest_template SET specialflags = 2, ReqCreatureOrGOId1 = 0, ReqCreatureOrGOCount1 = 0 WHERE entry IN (8359, 8358, 8354, 8360);
UPDATE quest_template SET specialflags = 0 WHERE entry = 8312;

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 6929;
DELETE FROM smart_scripts WHERE entryorguid = 6929;
INSERT INTO smart_scripts VALUES (6929, 0, 0, 0, 22, 0, 100, 0, 41, 500, 500, 0, 15, 8359, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Orgrimmar Innkeeper - Complete quest 8359 on /flex");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 6746;
DELETE FROM smart_scripts WHERE entryorguid = 6746;
INSERT INTO smart_scripts VALUES (6746, 0, 0, 0, 22, 0, 100, 0, 34, 500, 500, 0, 15, 8360, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Thunder Bluff Innkeeper - Complete quest 8360 on /dance");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 6741;
DELETE FROM smart_scripts WHERE entryorguid = 6741;
INSERT INTO smart_scripts VALUES (6741, 0, 0, 0, 22, 0, 100, 0, 22, 500, 500, 0, 15, 8354, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Undercity Innkeeper - Complete quest 8354 on /chicken");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 11814;
DELETE FROM smart_scripts WHERE entryorguid = 11814;
INSERT INTO smart_scripts VALUES (11814, 0, 0, 0, 22, 0, 100, 0, 264, 500, 500, 0, 15, 8358, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Sen'jin Innkeeper - Complete quest 8358 on /train");

UPDATE quest_template SET specialflags = 2, ReqCreatureOrGOId1 = 0, ReqCreatureOrGOCount1 = 0 WHERE entry IN (8356, 8355, 8353, 8357);

DELETE FROM creature_questrelation WHERE quest IN (8356, 8355, 8353, 8357);

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 6740;
DELETE FROM smart_scripts WHERE entryorguid = 6740;
INSERT INTO smart_scripts VALUES (6740, 0, 0, 0, 22, 0, 100, 0, 41, 500, 500, 0, 15, 8356, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Stormwind Innkeeper - Complete quest 8356 on /flex");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 6735;
DELETE FROM smart_scripts WHERE entryorguid = 6735;
INSERT INTO smart_scripts VALUES (6735, 0, 0, 0, 22, 0, 100, 0, 34, 500, 500, 0, 15, 8357, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Darnassus Innkeeper - Complete quest 8357 on /dance");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 5111;
DELETE FROM smart_scripts WHERE entryorguid = 5111;
INSERT INTO smart_scripts VALUES (5111, 0, 0, 0, 22, 0, 100, 0, 22, 500, 500, 0, 15, 8353, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Ironforge Innkeeper - Complete quest 8353 on /chicken");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 6826;
DELETE FROM smart_scripts WHERE entryorguid = 6826;
INSERT INTO smart_scripts VALUES (6826, 0, 0, 0, 22, 0, 100, 0, 264, 500, 500, 0, 15, 8355, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Gnomeregan Innkeeper - Complete quest 835558 on /train");
