INSERT INTO creature_questrelation VALUES (23904, 11242), (23904, 11403);
INSERT INTO creature_involvedrelation VALUES (23973, 11403), (24519, 11242);

UPDATE creature_template SET npcflag = 2, minlevel = 70, maxlevel = 70, minhealth = 18000, maxhealth = 18000 WHERE entry = 23904;

UPDATE quest_template SET RequiredRaces = 690 WHERE entry = 11403;
UPDATE quest_template SET RequiredRaces = 1101 WHERE entry = 11242;
