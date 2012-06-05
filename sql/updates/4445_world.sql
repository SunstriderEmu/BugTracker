DELETE FROM eventai_scripts WHERE creature_id IN (3397, 3275, 3274);

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (3397, 3275, 3274);

DELETE FROM smart_scripts WHERE entryorguid IN (3397, 3275, 3274);
INSERT INTO smart_scripts VALUES (3274, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 9128, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kolkar Pack Runner - Cast Battle Shout on Aggro"), (3275, 0, 0, 0, 0, 0, 100, 0, 12000, 12000, 7000, 7000, 11, 11976, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Kolkar Marauder - Cast Strike"), (3397, 0, 0, 0, 0, 0, 100, 0, 35000, 35000, 10000, 10000, 11, 6742, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kolkar Bloodcharger - Cast Bloodlust"), (3397, 0, 1, 0, 0, 0, 100, 0, 20000, 20000, 5000, 5000, 11, 172, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Kolkar Bloodcharger - Cast Corruption"), (3274, 0, 1, 0, 6, 0, 8, 0, 0, 0, 0, 0, 12, 3395, 1, 120000, 0, 0, 0, 8, 0, 0, 0, -1210.512329, -2726.960938, 106.706238, 4.765843, "Kolkar Pack Runner - Random chance to spawn Verogh the Dervish on death"), (3275, 0, 1, 0, 6, 0, 8, 0, 0, 0, 0, 0, 12, 3395, 1, 120000, 0, 0, 0, 8, 0, 0, 0, -1210.512329, -2726.960938, 106.706238, 4.765843, "Kolkar Marauder - Random chance to spawn Verogh the Dervish on death"), (3397, 0, 2, 0, 6, 0, 8, 0, 0, 0, 0, 0, 12, 3395, 1, 120000, 0, 0, 0, 8, 0, 0, 0, -1210.512329, -2726.960938, 106.706238, 4.765843, "Kolkar Bloodcharger - Random chance to spawn Verogh the Dervish on death");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 3395;

DELETE FROM smart_scripts WHERE entryorguid = 3395;
INSERT INTO smart_scripts VALUES (3395, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Verogh the Dervish - Yell on spawn");

DELETE FROM creature_text WHERE entry = 3395;
INSERT INTO creature_text VALUES (3395, 0, 0, "I am summoned! Intruders, come to my tent to face your death!", "J'ai été invoqué ! Intrus, venez à ma tente pour faire face à votre mort !", 1, 0, 100, 0, 0, 0, "Verogh the Dervish - Announce spawn");

