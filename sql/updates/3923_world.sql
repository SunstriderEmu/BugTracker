DELETE FROM creature_questrelation WHERE quest IN (8799, 8763);
INSERT INTO creature_questrelation VALUES (13418, 8799), (13433, 8763);
UPDATE quest_template SET SkillOrClass = 185, RequiredSkillValue = 300 WHERE entry IN (8799, 8763);
DELETE FROM gameobject_involvedrelation WHERE quest IN (8799, 8763);
INSERT INTO gameobject_involvedrelation VALUES (180715, 8799), (180715, 8763);
