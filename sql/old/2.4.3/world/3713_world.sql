UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 23398;

DELETE FROM smart_scripts WHERE entryorguid = 23398;
INSERT INTO smart_scripts VALUES (23398, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 5000, 8000, 11, 23398, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Anger on victim (AOE)");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 23401;

DELETE FROM smart_scripts WHERE entryorguid = 23401;
INSERT INTO smart_scripts VALUES (23401, 0, 0, 0, 0, 0, 10, 2, 5000, 5000, 2000, 2000, 11, 41248, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Consuming Strikes on self");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 23399;

DELETE FROM smart_scripts WHERE entryorguid = 23399;
INSERT INTO smart_scripts VALUES (23399, 0, 0, 0, 0, 0, 100, 2, 2000, 5000, 15000, 20000, 11, 41245, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Soul Blast on victim (AOE)");

UPDATE creature_template SET equipment_id = 440, AIName = "SmartAI", ScriptName = "", minlevel = 72, maxlevel = 72, mindmg = 3109, maxdmg = 6357, attackpower = 33131 WHERE entry = 23369;

DELETE FROM smart_scripts WHERE entryorguid = 23369;
INSERT INTO smart_scripts VALUES
(23369, 0, 0, 1, 1, 0, 100, 3, 14000, 14000, 0, 0, 51, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Suicide after 14 sec"),
(23369, 0, 1, 0, 61, 0, 100, 2, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Set visibility off"),
(23369, 0, 2, 3, 0, 0, 100, 3, 14000, 14000, 0, 0, 51, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Suicide after 14 sec"),
(23369, 0, 3, 0, 61, 0, 100, 2, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Set visibility off"),
(23369, 0, 4, 0, 4, 0, 100, 2, 0, 0, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Allow combat movement");

INSERT INTO eventai_scripts VALUES (2301806, 23018, 0, 0, 100, 3, 2000, 3000, 10000, 15000, 11, 32908, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Houndmaster - Cast Wing Clip");

UPDATE eventai_scripts SET event_chance = 100, event_param1 = 2000, event_param2 = 5000, event_param3 = 5000, event_param4 = 10000 WHERE id = 2288201;

UPDATE eventai_scripts SET action1_param2 = 1 WHERE id = 2295302;

INSERT INTO eventai_scripts VALUES (2295702, 22957, 0, 0, 100, 3, 10000, 15000, 22000, 30000, 11, 41404, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Priestess of Dementia - Cast Dementia");
INSERT INTO eventai_scripts VALUES (2295703, 22957, 2, 0, 100, 2, 30, 0, 0, 0, 32, 23436, 4, 20, 0, 0, 0, 0, 0, 0, 0, 0, "Priestess of Dementia - Summon Image of Dementia");
INSERT INTO eventai_summons VALUES (20, 0, 0, 0, 0, 10, "Image of Dementia");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 23436;

DELETE FROM smart_scripts WHERE entryorguid = 23436;
INSERT INTO smart_scripts VALUES (23436, 0, 0, 0, 0, 0, 100, 2, 2000, 5000, 20000, 30000, 11, 41399, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Whirlwind on victim");

UPDATE creature_template SET minlevel = 72, maxlevel = 72, faction_a = 1813, faction_h = 1813, minhealth = 36000, maxhealth = 40000, mindmg = 3109, maxdmg = 6357, attackpower = 33131 WHERE entry = 23436;

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22964;

DELETE FROM smart_scripts WHERE entryorguid = 22964;
INSERT INTO smart_scripts VALUES (22964, 0, 0, 0, 4, 0, 100, 2, 0, 0, 0, 0, 11, 41363, 3, 0, 0, 0, 0, 9, 22956, 1, 10, 0, 0, 0, 0, "Cast Shared Bounds on aggro"), (22964, 0, 1, 0, 0, 0, 100, 2, 5000, 10000, 12000, 18000, 11, 41380, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Holy Nova"), (22964, 0, 2, 0, 0, 0, 100, 2, 10000, 15000, 25000, 30000, 11, 41378, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Greater Heal"), (22964, 0, 3, 0, 2, 0, 100, 3, 40, 50, 0, 0, 11, 41381, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Shell of Life at 20% HP");

UPDATE creature_template SET minlevel = 72, maxlevel = 72, minhealth = 1000000, maxhealth = 1000000, faction_a = 1813, faction_h = 1813, unit_flags = unit_flags | 2, AIName = "SmartAI", ScriptName = "" WHERE entry = 23429;

DELETE FROM smart_scripts WHERE entryorguid = 23429;
INSERT INTO smart_scripts VALUES (23429, 0, 0, 0, 25, 0, 100, 2, 0, 0, 0, 0, 11, 41347, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Spotlight on spawn"), (23429, 0, 1, 2, 60, 0, 100, 3, 2500, 2500, 0, 0, 51, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Suicide after 2.5 sec"), (23429, 0, 2, 0, 61, 0, 100, 3, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Set visibility off"), (23429, 0, 3, 0, 60, 0, 100, 3, 2000, 2000, 0, 0, 11, 41349, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast L4 Arcane Charge 2 sec after spawn");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 23394;

DELETE FROM smart_scripts WHERE entryorguid = 23394;
INSERT INTO smart_scripts VALUES (23394, 0, 0, 0, 4, 0, 100, 2, 0, 0, 0, 0, 11, 41359, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast L1 Arcane Charge on Aggro"), (23394, 0, 1, 0, 0, 0, 100, 2, 5000, 8000, 5000, 8000, 11, 41348, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast L4 Arcane Charge on random"), (23394, 0, 2, 0, 0, 0, 100, 2, 8000, 12000, 10000, 15000, 11, 41360, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast L5 Arcane Charge on random");
