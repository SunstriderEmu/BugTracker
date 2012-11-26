UPDATE creature_template SET faction_A = 114, faction_H = 114 WHERE entry IN (25588, 25608);
UPDATE creature SET ScriptName = '' WHERE id IN (25588, 25608);
DELETE FROM creature WHERe id = 25319;
