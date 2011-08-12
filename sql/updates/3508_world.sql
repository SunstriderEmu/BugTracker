UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22849;
DELETE FROM eventai_scripts WHERE creature_id = 22849;

DELETE FROM smart_scripts WHERE entryorguid = 22849;
INSERT INTO smart_scripts VALUES
(22849, 0, 0, 0, 0, 0, 100, 2, 2000, 5000, 15000, 18000, 11, 39575, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Charge Frenzy on random"),
(22849, 0, 1, 0, 0, 0, 100, 2, 12000, 15000, 20000, 25000, 11, 39578, 1, 0, 0, 0, 0, 19, 22847, 0, 0, 0, 0, 0, 0, "Cast Spirit Bond on closest Ashtongue Primalist");
