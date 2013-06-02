UPDATE creature_template SET minhealth = 19500, maxhealth = 20000 WHERE entry = 18619;
DELETE FROM eventai_scripts WHERE id = 1737115;
INSERT INTO eventai_scripts VALUES (1737115, 17371, 0, 0, 100, 5, 1100, 7800, 14800, 30100, 11, 32863, 4, 33, 0, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock (Heroic) - Cast Seed of Corruption");

UPDATE creature_model_info SET modelid_other_gender = 16332 WHERE modelid = 16332;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17398;

DELETE FROM smart_scripts WHERE entryorguid = 17398;
INSERT INTO smart_scripts VALUES (17398, 0, 0, 0, 0, 0, 100, 6, 5000, 8000, 20000, 35000, 11, 22427, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Nascent Fel Orc - IC Timer - Cast Concussion Blow"), (17398, 0, 1, 0, 0, 0, 100, 6, 8000, 11000, 20000, 35000, 11, 31900, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Nascent Fel Orc - IC Timer - Cast Stomp");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17429;
DELETE FROM smart_scripts WHERE entryorguid = 17429;
INSERT INTO smart_scripts VALUES (17429, 0, 0, 0, 0, 0, 100, 6, 8000, 11000, 25000, 30000, 11, 22120, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Fel Orc Neophyte - IC Timer - Cast Charge"), (17429, 0, 1, 0, 2, 0, 100, 7, 20, 30, 0, 0, 11, 8269, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Fel Orc Neophyte - HP 30% - Cast Frenzy");

UPDATE creature_template SET maxhealth = 8000 WHERE entry = 18605;
UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17401;
DELETE FROM smart_scripts WHERE entryorguid = 17401;
INSERT INTO smart_scripts VALUES (17401, 0, 0, 0, 0, 0, 100, 6, 3000, 5000, 11000, 17000, 11, 13321, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Felhound Manastalker - IC Timer - Cast Mana Burn"), (17401, 0, 1, 0, 0, 0, 100, 6, 8000, 12000, 25000, 30000, 11, 30849, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Felhound Manastalker - IC Timer - Cast Spell Lock");

UPDATE creature_template SET equipment_id = 993 WHERE entry = 17624;
UPDATE creature_template SET minhealth = 39000, maxhealth = 40000 WHERE entry = 18611;

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17395;
DELETE FROM smart_scripts WHERE entryorguid = 17395;
INSERT INTO smart_scripts VALUES (17395, 0, 0, 0, 0, 0, 100, 2, 2000, 4000, 2000, 4000, 11, 15242, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Summoner - IC Timer - Cast Fireball"), (17395, 0, 1, 0, 0, 0, 100, 4, 2000, 4000, 2000, 4000, 11, 17290, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Summoner - IC Timer - Cast Fireball"), (17395, 0, 2, 0, 0, 0, 100, 2, 8000, 120000, 20000, 28000, 11, 18399, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Summoner - IC Timer - Cast Flamestrike"), (17395, 0, 3, 0, 0, 0, 100, 4, 8000, 120000, 20000, 28000, 11, 16102, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Summoner - IC Timer - Cast Flamestrike"), (17395, 0, 4, 0, 0, 0, 100, 6, 8000, 8000, 20000, 20000, 11, 30851, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Summoner - IC Timer - Cast Summon Felhound Manastalker"), (17395, 0, 5, 0, 0, 0, 100, 6, 18000, 18000, 20000, 20000, 11, 30853, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Summoner - IC Timer - Cast Summon Seductress");

UPDATE creature_template SET maxhealth = 27500 WHERE entry = 18609;

UPDATE creature_template SET spell1 = 14516, spell2 = 15655 WHERE entry = 17370;
UPDATE creature_template SET minhealth = 28000, maxhealth = 28500 WHERE entry = 18608;

UPDATE creature_template SET modelid_A = 16891, modelid_H = 16891 WHERE entry = 19016;
