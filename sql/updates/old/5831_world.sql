/* Correct Archimonde HP & melee damages */
UPDATE creature_template SET minhealth = 4900000, maxhealth = 4900000, mindmg = 15543,maxdmg = 21953 WHERE entry = 17968;