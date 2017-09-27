UPDATE creature_template SET faction_A = 1216, faction_H = 1216 WHERE entry IN (14762,14763);
UPDATE creature_template SET ScriptName = "AV_Warmasters" WHERE ScriptName = "AV_Marshals";
UPDATE creature_template SET mindmg = 3000, maxdmg = 6000 WHERE entry IN (14762,14763,14764,14765);
UPDATE creature_template SET minhealth = 96715, maxhealth = 96715 WHERE entry IN (14762,14763,14764);
UPDATE creature_template SET armor = 5000, speed = 2 WHERE entry IN (11946,11948,14762,14763,14764,14765,14772,14773,14776,14777,11949,11947);
UPDATE creature_template SET minhealth = 190000, maxhealth = 190000 WHERE entry IN (11947,11949);