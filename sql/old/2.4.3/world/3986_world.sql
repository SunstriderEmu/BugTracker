UPDATE gameobject_template SET data2 = 3932160 WHERE name = "Ethereum prison";
UPDATE gameobject_template SET flags = 0 WHERE name = "Ethereum prison";
UPDATE gameobject SET spawntimesecs = 60 WHERE id IN (SELECT entry FROM gameobject_template WHERE name = "Ethereum prison");
