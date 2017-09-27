DELETE FROM script_texts WHERE entry IN (-1765300, -1765301, -1765302);
INSERT INTO script_texts (entry, content_default, content_loc2, `type`) VALUES
(-1765300, "Ignorant whelps!", "Morveux ignorants !", 1),
(-1765301, "You fools! He'll kill us all!", "Fous ! Il nous tuera tous !", 1),
(-1765302, "You mustn't let him loose!", "Vous ne devez pas le libérer !", 1);

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17397;
DELETE FROM smart_scripts WHERE entryorguid = 17397;
INSERT INTO smart_scripts VALUES
(17397, 0, 0, 0, 4, 0, 100, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Adept - Aggro - Random say"),
(17397, 0, 1, 0, 1, 0, 100, 6, 1000, 1000, 10000, 10000, 11, 31059, 0, 0, 0, 0, 0, 11, 17477, 5, 0, 0, 0, 0, 0, "Shadowmoon Adept - OOC Timer - Cosmetic"),
(17397, 0, 2, 0, 0, 0, 100, 6, 5000, 8000, 18000, 22000, 11, 3391, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Adept - IC Timer - Cast Thrash"),
(17397, 0, 3, 0, 0, 0, 100, 6, 8000, 12000, 25000, 30000, 11, 11978, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Adept - IC Timer - Cast Kick"),
(17397, 0, 4, 0, 2, 0, 100, 7, 20, 30, 0, 0, 25, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Adept - 30% HP - Flee for assist");

DELETE FROM creature_text WHERE entry = 17397;
INSERT INTO creature_text VALUES
(17397, 0, 0, "Ce monde nous APPARTIENT !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17397, 0, 1, "Gakarah ma !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17397, 0, 2, "Le sang est notre force !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17397, 0, 3, "Lok narash !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17397, 0, 4, "Lok'tar Illadari !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17397, 0, 5, "Nous sommes la véritable Horde !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17397, 0, 6, "Pour Kargath ! Pour la victoire !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17370;
DELETE FROM smart_scripts WHERE entryorguid = 17370;
INSERT INTO smart_scripts VALUES
(17370, 0, 0, 0, 4, 0, 100, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Enforcer - Aggro - Random say"),
(17370, 0, 1, 0, 0, 0, 100, 6, 8000, 12000, 25000, 30000, 11, 15655, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Enforcer - IC Timer - Cast Shield Slam"),
(17370, 0, 2, 0, 0, 0, 100, 6, 2000, 5000, 10000, 150000, 11, 17370, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Enforcer - IC TImer - Cast Strike");

DELETE FROM creature_text WHERE entry = 17370;
INSERT INTO creature_text VALUES
(17370, 0, 0, "Ce monde nous APPARTIENT !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17370, 0, 1, "Gakarah ma !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17370, 0, 2, "Le sang est notre force !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17370, 0, 3, "Lok narash !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17370, 0, 4, "Lok'tar Illadari !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17370, 0, 5, "Nous sommes la véritable Horde !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17370, 0, 6, "Pour Kargath ! Pour la victoire !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17477;
DELETE FROM smart_scripts WHERE entryorguid = 17477;
INSERT INTO smart_scripts VALUES
(17477, 0, 0, 1, 4, 0, 100, 6, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - Aggro - Prevent combat movement"),
(17477, 0, 1, 0, 61, 0, 100, 6, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - Aggro - Set Phase 1"),
(17477, 0, 2, 3, 3, 0, 100, 7, 5, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - 15% Mana - Allow combat movement"),
(17477, 0, 3, 0, 61, 0, 100, 6, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - 15% Mana - Set Phase 2"),
(17477, 0, 4, 0, 9, 1, 100, 6, 35, 80, 1000, 1000, 21, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - Phase 1 - Allow combat movement at 35 yards"),
(17477, 0, 5, 0, 9, 1, 100, 6, 5, 15, 1000, 1000, 21, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - Phase 1 - Prevent combat movement at 15 yards"),
(17477, 0, 6, 0, 0, 1, 100, 2, 1000, 2000, 4000, 5000, 11, 15242, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - Phase 1 - Cast Fireball (Normal)"),
(17477, 0, 7, 0, 0, 1, 100, 4, 1000, 2000, 4000, 5000, 11, 17290, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - Phase 1 - Cast Fireball (Heroic)"),
(17477, 0, 8, 0, 0, 1, 100, 4, 5000, 8000, 12000, 18000, 11, 16144, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - Phase 1 - Cast Fire Blast"),
(17477, 0, 9, 0, 7, 0, 100, 6, 0, 0, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Hellfire Imp - Evade - Allow combat movement");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17491;
DELETE FROM smart_scripts WHERE entryorguid = 17491;
INSERT INTO smart_scripts VALUES
(17491, 0, 0, 1, 4, 0, 100, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Rogue - Aggro - Random say"),
(17491, 0, 1, 0, 61, 0, 100, 6, 0, 0, 0, 0, 28, 30991, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Rogue - Aggro - Remove Stealth"),
(17491, 0, 2, 0, 0, 0, 100, 6, 1000, 2000, 4000, 8000, 11, 34969, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Rogue - IC Timer - Cast Poison"),
(17491, 0, 3, 0, 0, 0, 100, 6, 8000, 12000, 30000, 38000, 11, 6434, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Rogue - IC Timer - Cast Slice and Dice"),
(17491, 0, 4, 0, 0, 0, 100, 6, 15000, 22000, 30000, 38000, 11, 30832, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Rogue - IC Timer - Cast Kidney Shot"),
(17491, 0, 5, 0, 1, 0, 100, 7, 1000, 1000, 0, 0, 11, 30991, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Rogue - OOC Timer - Cast Stealth");

DELETE FROM creature_text WHERE entry = 17491;
INSERT INTO creature_text VALUES
(17491, 0, 0, "Ce monde nous APPARTIENT !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17491, 0, 1, "Gakarah ma !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17491, 0, 2, "Le sang est notre force !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17491, 0, 3, "Lok narash !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17491, 0, 4, "Lok'tar Illadari !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17491, 0, 5, "Nous sommes la véritable Horde !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17491, 0, 6, "Pour Kargath ! Pour la victoire !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17371;
DELETE FROM smart_scripts WHERE entryorguid = 17371;
INSERT INTO smart_scripts VALUES
(17371, 0, 0, 1, 4, 0, 100, 6, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Aggro - Prevent combat movement"),
(17371, 0, 1, 0, 61, 0, 100, 6, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Aggro - Set Phase 1"),
(17371, 0, 2, 3, 3, 0, 100, 7, 5, 15, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - 15% Mana - Allow combat movement"),
(17371, 0, 3, 0, 61, 0, 100, 6, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - 15% Mana - Set Phase 2"),
(17371, 0, 4, 0, 9, 1, 100, 6, 35, 80, 1000, 1000, 21, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Phase 1 - Allow combat movement at 35 yards"),
(17371, 0, 5, 0, 9, 1, 100, 6, 5, 15, 1000, 1000, 21, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Phase 1 - Prevent combat movement at 15 yards"),
(17371, 0, 6, 0, 0, 1, 100, 2, 500, 500, 4000, 5000, 11, 12739, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Phase 1 - Cast Shadow Bolt (Normal)"),
(17371, 0, 7, 0, 0, 1, 100, 4, 500, 500, 4000, 5000, 11, 15472, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Phase 1 - Cast Shadow Bolt (Heroic)"),
(17371, 0, 8, 0, 0, 1, 100, 2, 1000, 2000, 12000, 15000, 11, 32197, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Phase 1 - Cast Corruption (Normal)"),
(17371, 0, 9, 0, 0, 1, 100, 4, 1000, 2000, 12000, 15000, 11, 37113, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Phase 1 - Cast Corruption (Heroic)"),
(17371, 0, 10, 0, 0, 1, 100, 6, 2000, 8000, 15000, 24000, 11, 13338, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Phase 1 - Cast Curse of Tongues"),
(17371, 0, 11, 0, 0, 1, 100, 4, 5000, 10000, 13000, 18000, 11, 32863, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Phase 1 - Cast Seed of Corruption (Heroic)"),
(17371, 0, 12, 0, 4, 0, 100, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Aggro - Random say"),
(17371, 0, 13, 0, 7, 0, 100, 6, 0, 0, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Warlock - Evade - Allow combat movement"),
(17371, 0, 14, 0, 16, 0, 100, 6, 33111, 8, 6000, 6000, 11, 33111, 0, 0, 0, 0, 0, 7, 0, 0, 8, 0, 0, 0, 0, "Shadowmoon Warlock - Missing Buff - Cast Fel Power"),
(17371, 0, 15, 0, 16, 0, 100, 6, 33111, 8, 6000, 6000, 11, 33111, 0, 0, 0, 0, 0, 7, 0, 0, 8, 0, 0, 0, 0, "Shadowmoon Warlock - Missing Buff - Cast Fel Power");

DELETE FROM creature_text WHERE entry = 17371;
INSERT INTO creature_text VALUES
(17371, 0, 0, "Ce monde nous APPARTIENT !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17371, 0, 1, "Gakarah ma !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17371, 0, 2, "Le sang est notre force !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17371, 0, 3, "Lok narash !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17371, 0, 4, "Lok'tar Illadari !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17371, 0, 5, "Nous sommes la véritable Horde !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17371, 0, 6, "Pour Kargath ! Pour la victoire !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17626;
DELETE FROM smart_scripts WHERE entryorguid = 17626;
INSERT INTO smart_scripts VALUES
(17626, 0, 0, 0, 0, 0, 100, 6, 5800, 7200, 11900, 12400, 11, 10966, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Legionaire - Cast Uppercut"),
(17626, 0, 1, 2, 2, 0, 100, 7, 20, 30, 0, 0, 11, 8599, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Legionaire - 30% HP - Cast Enrage"),
(17626, 0, 2, 0, 61, 0, 100, 6, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Legionaire - 30% HP - Enrage Emote"),
(17626, 0, 3, 0, 4, 0, 100, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Legionaire - Aggro - Random say");

DELETE FROM creature_text WHERE entry = 17626;
INSERT INTO creature_text VALUES
(17626, 0, 0, "Ce monde nous APPARTIENT !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17626, 0, 1, "Gakarah ma !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17626, 0, 2, "Le sang est notre force !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17626, 0, 3, "Lok narash !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17626, 0, 4, "Lok'tar Illadari !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17626, 0, 5, "Nous sommes la véritable Horde !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17626, 0, 6, "Pour Kargath ! Pour la victoire !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17626, 1, 0, "entre dans une rage folle !", 2, 0, 100, 0, 0, 0, "Laughing Skull Legionaire - Enrage Emote");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17414;
DELETE FROM smart_scripts WHERE entryorguid = 17414;
INSERT INTO smart_scripts VALUES
(17414, 0, 0, 0, 4, 0, 100, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Technician - Aggro - Random say"),
(17414, 0, 1, 2, 0, 0, 100, 2, 2800, 4700, 17700, 23400, 11, 30846, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Technician - IC Timer - Cast Throw Proximity Bomb (Normal)"),
(17414, 0, 2, 0, 61, 0, 100, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Technician - IC Timer - Bomb Emote"),
(17414, 0, 3, 4, 0, 0, 100, 4, 2800, 4700, 17700, 23400, 11, 32784, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Technician - IC Timer - Cast Throw Proximity Bomb (Heroic)"),
(17414, 0, 4, 0, 61, 0, 100, 4, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Technician - IC Timer - Bomb Emote"),
(17414, 0, 5, 0, 0, 0, 100, 2, 4400, 10600, 3600, 6200, 11, 40062, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Technician - IC Timer - Cast Throw Dynamite (Normal)"),
(17414, 0, 6, 0, 0, 0, 100, 4, 4400, 10600, 3600, 6200, 11, 40064, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Technician - IC Timer - Cast Throw Dynamite (Heroic)"),
(17414, 0, 7, 0, 0, 0, 100, 6, 5400, 11600, 24300, 24300, 11, 6726, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowmoon Technician - IC Timer - Cast Silence");

DELETE FROM creature_text WHERE entry = 17414;
INSERT INTO creature_text VALUES
(17414, 0, 0, "Ce monde nous APPARTIENT !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17414, 0, 1, "Gakarah ma !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17414, 0, 2, "Le sang est notre force !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17414, 0, 3, "Lok narash !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17414, 0, 4, "Lok'tar Illadari !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17414, 0, 5, "Nous sommes la véritable Horde !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17414, 0, 6, "Pour Kargath ! Pour la victoire !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(17414, 1, 0, "Technicien Ombrelune commence à armer la bombe de proximité !", 2, 0, 100, 0, 0, 0, "Laughing Skull Legionaire - Enrage Emote");

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 17624;
DELETE FROM smart_scripts WHERE entryorguid = 17624;
INSERT INTO smart_scripts VALUES
(17624, 0, 0, 0, 1, 0, 100, 7, 1000, 1000, 0, 0, 11, 38551, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Warden - OOC Timer - Cast Stealth Detection"),
(17624, 0, 1, 0, 4, 0, 100, 6, 0, 0, 0, 0, 11, 30833, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Warden - Aggro - Cast Battle Shout"),
(17624, 0, 2, 0, 4, 0, 100, 6, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Laughing Skull Warden - Aggro - Random say");

DELETE FROM creature_text WHERE entry = 14624;
INSERT INTO creature_text VALUES
(14624, 0, 0, "Ce monde nous APPARTIENT !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(14624, 0, 1, "Gakarah ma !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(14624, 0, 2, "Le sang est notre force !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(14624, 0, 3, "Lok narash !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(14624, 0, 4, "Lok'tar Illadari !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(14624, 0, 5, "Nous sommes la véritable Horde !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say"),
(14624, 0, 6, "Pour Kargath ! Pour la victoire !", 0, 0, 60, 0, 0, 0, "Blood Furnace trash mob - Aggro - Random say");

UPDATE creature_template SET equipment_id = 18894 WHERE entry IN (17400, 18604);
UPDATE creature_template SET equipment_id = 17626 WHERE entry IN (17626, 18609);
DELETE FROM creature_equip_template WHERE entry = 17626;
INSERT INTO creature_equip_template (entry, equipmodel1) VALUES (17626, 5128);

UPDATE smart_scripts SET event_param1 = 500, event_param2 = 500 WHERE entryorguid = 17395 AND id = 4;
UPDATE smart_scripts SET event_param1 = 10500, event_param2 = 10500 WHERE entryorguid = 17395 AND id = 5;

DELETE FROM creature_equip_template WHERE entry = 17377;
INSERT INTO creature_equip_template (entry, equipmodel1) VALUES (17377, 24014);
UPDATE creature_template SET equipment_id = 17377 WHERE entry IN (17377, 18607);

SET @GUID := 1000000;

DELETE FROM `creature` WHERE map = 542;
INSERT INTO `creature` (guid, id, `map`, spawnMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, deathstate, movementtype, pool_id) VALUES
(@GUID,17397,542,3,0,0,224.21,-71.9266,9.61857,4.01001,25,0,0,11965,2486,0,0,0),
(@GUID+1,17256,542,3,0,0,308.203,-141.769,-137.368,1.36136,604800,0,0,242800,1016100,0,0,0),
(@GUID+2,17256,542,3,0,0,274.133,-87.1647,-137.368,0.017453,604800,0,0,242800,1016100,0,0,0),
(@GUID+3,17256,542,3,0,0,307.784,-31.8502,-137.368,4.95674,604800,0,0,242800,1016100,0,0,0),
(@GUID+4,17256,542,3,0,0,369.15,-55.5658,-137.368,3.71755,604800,0,0,242800,1016100,0,0,0),
(@GUID+5,17256,542,3,0,0,369.461,-118.757,-137.368,2.54818,604800,0,0,242800,1016100,0,0,0),
(@GUID+6,17397,542,3,0,0,1.24754,-86.3075,-41.3328,0.902199,25,0,0,11965,2486,0,0,0),
(@GUID+7,17370,542,3,0,993,8.16532,-56.8039,-41.3405,1.67449,25,0,0,14958,5158,0,0,34),
(@GUID+8,17370,542,3,0,993,-3.37668,-57.4802,-41.3405,1.67449,25,0,0,14958,5158,0,0,34),
(@GUID+9,17380,542,3,0,0,455.336,-1.82919,9.6299,1.43117,43200,0,0,30960,18468,0,0,0),
(@GUID+10,17477,542,3,0,0,-10.1328,-80.7288,-41.3339,5.10407,25,0,0,4126,9944,0,0,0),
(@GUID+11,17397,542,3,0,0,7.62365,-84.2735,-41.3317,2.94816,25,0,0,11965,2486,0,0,0),
(@GUID+12,17397,542,3,0,0,23.6173,-89.9426,-40.9195,1.48418,25,0,0,11965,2486,0,0,0),
(@GUID+13,17370,542,3,0,993,49.1393,-93.2072,-40.2689,3.15,25,0,0,14958,5158,0,0,35),
(@GUID+14,17397,542,3,0,0,28.3938,-84.198,-41.1055,3.35578,25,0,0,11965,2486,0,0,0),
(@GUID+15,17397,542,3,0,0,343.558,7.22853,9.62178,3.09605,25,0,0,11965,2486,0,0,40),
(@GUID+16,17491,542,3,0,17491,180.553,-75.6421,9.60469,3.13744,25,0,0,7479,0,0,0,0),
(@GUID+17,17370,542,3,0,993,195.465,-78.4971,9.61762,3.13744,25,0,0,14958,5158,0,0,0),
(@GUID+18,21174,542,3,0,0,320.912,-83.0625,-133.307,3.00197,7200,0,0,4818380,0,0,0,0),
(@GUID+19,17370,542,3,0,993,195.416,-90.292,9.6164,3.13744,25,0,0,14958,5158,0,0,0),
(@GUID+20,17477,542,3,0,0,23.9827,-85.2393,-41.2441,5.91932,25,0,0,4126,9944,0,0,0),
(@GUID+21,17477,542,3,0,0,3.51669,-83.7316,-41.3303,5.67052,25,0,0,4126,9944,0,0,0),
(@GUID+22,17397,542,3,0,0,246.411,-69.8552,9.61645,3.74377,25,0,0,11965,2486,0,0,0),
(@GUID+23,17397,542,3,0,0,245.899,-75.4009,9.62052,2.35439,25,0,0,11965,2486,0,0,0),
(@GUID+24,17477,542,3,0,0,221.463,-75.1858,9.62295,6.26253,25,0,0,4126,9944,0,0,0),
(@GUID+25,17626,542,3,0,0,279.169,0.500806,8.02572,3.74467,25,0,0,14958,5158,0,0,39),
(@GUID+26,17370,542,3,0,993,323.606,29.4792,9.62214,4.84592,25,0,0,14958,5158,0,0,0),
(@GUID+27,17370,542,3,0,993,331.264,30.0487,9.62056,4.84592,25,0,0,14958,5158,0,0,0),
(@GUID+28,17491,542,3,0,17491,181.813,-94.4178,9.61659,3.06856,25,0,0,7479,0,0,0,0),
(@GUID+29,17395,542,3,0,0,337.472,10.5178,9.61857,5.33601,25,0,0,10472,17625,0,0,40),
(@GUID+30,17395,542,3,0,0,338.261,1.60129,9.61575,0.999823,25,0,0,10472,17625,0,0,40),
(@GUID+31,17397,542,3,0,0,317.999,9.90239,9.62067,2.14808,25,0,0,11965,2486,0,0,41),
(@GUID+32,17397,542,3,0,0,320.408,17.8495,9.6244,3.69767,25,0,0,11965,2486,0,0,41),
(@GUID+33,17395,542,3,0,0,314.227,14.657,9.61697,6.07193,25,0,0,10472,17625,0,0,41),
(@GUID+34,17398,542,3,0,0,370.998,66.9011,9.65379,3.09365,25,0,0,6963,0,0,0,0),
(@GUID+35,17626,542,3,0,0,345.91,64.2973,9.61722,1.45291,25,0,0,14958,5158,0,2,0),
(@GUID+36,17414,542,3,0,0,331.394,64.8008,9.61422,2.27845,25,0,0,10472,5875,0,0,0),
(@GUID+37,17398,542,3,0,0,371.138,70.5035,9.65479,3.09365,25,0,0,7210,0,0,0,0),
(@GUID+38,17414,542,3,0,0,342.379,64.2432,9.61692,1.45291,25,0,0,10843,6015,0,2,0),
(@GUID+39,17626,542,3,0,0,312.241,64.8913,9.61697,1.54463,25,0,0,14958,5158,0,2,0),
(@GUID+40,17414,542,3,0,0,327.676,69.696,9.61491,5.34382,25,0,0,10472,5875,0,0,0),
(@GUID+41,17395,542,3,0,0,321.622,93.3459,9.61582,2.23919,25,0,0,10472,17625,0,0,0),
(@GUID+42,17626,542,3,0,0,298.504,0.906181,9.60513,3.30906,7200,0,0,14958,5158,0,2,0),
(@GUID+43,17398,542,3,0,0,314.478,195.642,11.6815,5.01966,7200,0,0,6963,0,0,0,10),
(@GUID+44,17398,542,3,0,0,345.078,202.309,11.6826,4.90708,7200,0,0,6963,0,0,0,11),
(@GUID+45,17398,542,3,0,0,437.158,201.984,11.6815,4.639,7200,0,0,6963,0,0,0,15),
(@GUID+46,17371,542,3,0,0,373.804,190.948,9.597,1.09081,25,0,0,10472,5875,0,0,12),
(@GUID+47,17398,542,3,0,0,376.497,195.305,9.5939,4.61725,25,0,0,7210,0,0,0,12),
(@GUID+48,17414,542,3,0,0,331.846,191.344,9.60436,1.67424,25,0,0,10472,5875,0,0,10),
(@GUID+49,17414,542,3,0,0,349.574,193.054,9.60769,2.0206,25,0,0,10472,5875,0,0,11),
(@GUID+50,17624,542,3,0,993,364.133,189.885,9.59542,3.40963,25,0,0,16023,0,0,2,0),
(@GUID+51,17491,542,3,0,17491,471.553,175.234,9.62109,2.94781,25,0,0,7479,0,0,0,0),
(@GUID+52,17414,542,3,0,0,321.558,184.754,9.61926,2.16708,25,0,0,10843,6015,0,0,10),
(@GUID+53,17398,542,3,0,0,498.064,86.5477,9.65126,5.42675,7200,0,0,6963,0,0,0,0),
(@GUID+54,17398,542,3,0,0,499.084,82.6819,9.65147,1.36781,7200,0,0,6963,0,0,0,0),
(@GUID+55,17398,542,3,0,0,501.71,85.9602,9.65554,3.76799,7200,0,0,6963,0,0,0,0),
(@GUID+56,17429,542,3,0,0,413.188,83.6095,9.65322,2.85379,25,0,0,10682,0,0,0,0),
(@GUID+57,17398,542,3,0,0,410.765,86.1218,9.65759,4.94766,7200,0,0,6963,0,0,0,0),
(@GUID+58,17398,542,3,0,0,409.226,83.2983,9.65786,0.141552,7200,0,0,6963,0,0,0,0),
(@GUID+59,17429,542,3,0,0,413.397,114.31,9.65213,3.02019,25,0,0,10682,0,0,0,0),
(@GUID+60,17429,542,3,0,0,409.11,112.172,9.65949,1.19964,25,0,0,10682,0,0,0,0),
(@GUID+61,17429,542,3,0,0,411.022,117.185,9.65541,4.41977,25,0,0,10682,0,0,0,0),
(@GUID+62,17398,542,3,0,0,407.17,115.172,9.66061,0.0185067,7200,0,0,6963,0,0,0,0),
(@GUID+63,17429,542,3,0,0,498.78,116.599,9.64976,5.44393,25,0,0,10682,0,0,0,0),
(@GUID+64,17398,542,3,0,0,502.642,112.954,9.65743,2.33847,7200,0,0,6963,0,0,0,0),
(@GUID+65,17398,542,3,0,0,502.63,116.706,9.65821,3.97759,7200,0,0,6963,0,0,0,0),
(@GUID+66,17429,542,3,0,0,498.35,112.381,9.65222,0.637292,25,0,0,10682,0,0,0,0),
(@GUID+67,17371,542,3,0,0,327.291,-8.2357,9.54777,1.59875,25,0,0,10472,5875,0,2,0),
(@GUID+68,17491,542,3,0,17491,459.915,-38.8803,9.55219,6.13882,25,0,0,7479,0,0,2,0),
(@GUID+69,19016,542,3,0,0,486.723,3.50609,9.54299,1.59294,25,0,0,4126,9944,0,0,23),
(@GUID+70,17371,542,3,0,0,418.141,-84.2463,9.61676,6.24405,25,5,0,10472,5875,0,1,21),
(@GUID+71,19016,542,3,0,0,424.746,-75.4779,9.61969,0.137595,25,5,0,4126,9944,0,1,21),
(@GUID+72,19016,542,3,0,0,484.153,8.1885,9.54906,0.315101,25,0,0,4126,9944,0,0,23),
(@GUID+73,19016,542,3,0,0,488.337,10.1549,9.54906,3.5423,25,0,0,4126,9944,0,0,23),
(@GUID+74,17371,542,3,0,0,492.749,3.54277,9.546,2.19613,25,0,0,10843,6015,0,0,23),
(@GUID+75,17371,542,3,0,0,330.831,-192.172,-25.5046,1.49001,25,0,0,10843,6015,0,0,24),
(@GUID+76,17377,542,3,0,0,325.862,-87.2087,-24.6512,5.87314,43200,0,0,34830,6156,0,0,0),
(@GUID+77,17370,542,3,0,993,48.5511,-76.8379,-40.2703,3.19162,25,0,0,14958,5158,0,0,35),
(@GUID+78,17414,542,3,0,0,479.609,97.8457,9.62269,6.16845,25,0,0,10472,5875,0,0,19),
(@GUID+79,17414,542,3,0,0,481.905,93.5323,9.62269,0.984824,25,0,0,10472,5875,0,0,19),
(@GUID+80,17414,542,3,0,0,481.71,101.289,9.61692,5.90142,25,0,0,10843,6015,0,0,19),
(@GUID+81,17414,542,3,0,0,347.069,199.396,11.3149,2.21183,25,0,0,10843,6015,0,0,11),
(@GUID+82,17414,542,3,0,0,308.63,64.9858,9.61837,1.54463,25,0,0,10472,5875,0,2,0),
(@GUID+83,17414,542,3,0,0,316.491,97.9412,9.61732,5.50645,25,0,0,10843,6015,0,0,0),
(@GUID+84,17371,542,3,0,0,338.16,116.62,9.61562,4.49132,25,0,0,10472,5875,0,0,0),
(@GUID+85,17414,542,3,0,0,336.32,110.956,9.61694,1.23584,25,0,0,10843,6015,0,0,0),
(@GUID+86,17397,542,3,0,0,-13.8418,-78.6574,-41.3358,5.73632,25,0,0,11965,2486,0,0,0),
(@GUID+87,17397,542,3,0,0,-9.82879,-84.9112,-41.3347,1.64597,25,0,0,11965,2486,0,0,0),
(@GUID+88,17397,542,3,0,0,230.486,-101.706,9.62282,2.56959,25,0,0,11965,2486,0,0,0),
(@GUID+89,17397,542,3,0,0,229.41,-96.0488,9.61768,3.9299,25,0,0,11965,2486,0,0,0),
(@GUID+90,17477,542,3,0,0,226.356,-98.9013,9.61689,0.058674,25,0,0,4126,9944,0,0,0),
(@GUID+91,17477,542,3,0,0,242.953,-72.3724,9.61526,6.16515,25,0,0,4126,9944,0,0,0),
(@GUID+92,17397,542,3,0,0,225.028,-77.736,9.6247,2.57902,25,0,0,11965,2486,0,0,0),
(@GUID+93,17370,542,3,0,993,258.009,-32.2622,7.07814,4.09496,25,0,0,14958,5158,0,0,38),
(@GUID+94,17370,542,3,0,993,284.001,-8.53554,8.72491,3.74624,25,0,0,14958,5158,0,0,39),
(@GUID+95,17626,542,3,0,0,248.968,-26.4479,6.95341,4.21198,25,0,0,14958,5158,0,0,38),
(@GUID+96,17398,542,3,0,0,376.29,68.396,9.66058,3.09365,25,0,0,7210,0,0,0,0),
(@GUID+97,17398,542,3,0,0,372.738,98.5148,9.6571,3.22167,25,0,0,6963,0,0,0,0),
(@GUID+98,17398,542,3,0,0,372.381,102.953,9.6571,3.22167,25,0,0,7210,0,0,0,0),
(@GUID+99,17398,542,3,0,0,376.501,100.64,9.66214,3.22167,25,0,0,6963,0,0,0,0),
(@GUID+100,17398,542,3,0,0,282.447,101.694,9.65617,0.222234,25,0,0,7210,0,0,0,0),
(@GUID+101,17398,542,3,0,0,283.468,97.1739,9.65476,0.222234,25,0,0,6963,0,0,0,0),
(@GUID+102,17398,542,3,0,0,278.804,99.193,9.66205,0.222234,25,0,0,6963,0,0,0,0),
(@GUID+103,17398,542,3,0,0,283.179,71.5788,9.65483,6.19047,25,0,0,7210,0,0,0,0),
(@GUID+104,17398,542,3,0,0,282.724,66.6929,9.65483,6.19047,25,0,0,6963,0,0,0,0),
(@GUID+105,17398,542,3,0,0,278.669,69.6265,9.65982,6.19047,25,0,0,7210,0,0,0,0),
(@GUID+106,17371,542,3,0,0,208.535,-84.717,9.57439,6.28208,25,0,0,10472,5875,0,2,0),
(@GUID+107,17381,542,3,0,0,326.918,135.707,9.61591,4.64814,25,5,0,38722,0,0,1,0),
(@GUID+108,17371,542,3,0,0,379.044,190.929,9.59681,2.23514,25,0,0,10472,5875,0,0,12),
(@GUID+109,17398,542,3,0,0,407.78,193.546,9.59551,4.28737,25,0,0,7210,0,0,0,14),
(@GUID+110,17371,542,3,0,0,409.575,189.041,9.59859,1.96562,25,0,0,10472,5875,0,0,14),
(@GUID+111,17371,542,3,0,0,403.976,189.516,9.59616,1.1187,25,0,0,10472,5875,0,0,14),
(@GUID+112,17624,542,3,0,993,364.958,186.881,9.59683,3.40963,25,0,0,16023,0,0,2,0),
(@GUID+113,17624,542,3,0,993,466.131,178.069,9.61918,2.95644,25,0,0,16023,0,0,2,0),
(@GUID+114,17624,542,3,0,993,466.641,180.793,9.61918,2.95644,25,0,0,16023,0,0,2,0),
(@GUID+115,17414,542,3,0,0,435.129,191.994,9.60497,1.22315,25,0,0,10843,6015,0,0,15),
(@GUID+116,17414,542,3,0,0,448.523,191.164,9.60537,0.591687,25,0,0,10472,5875,0,0,15),
(@GUID+117,1412,542,3,0,0,377.739,-37.8195,-24.6529,4.32772,25,0,0,8,0,0,0,0),
(@GUID+118,17395,542,3,0,0,447.893,98.8007,9.61686,0.752667,25,0,0,10472,17625,0,0,20),
(@GUID+119,19016,542,3,0,0,428.106,-84.4901,9.61571,4.59237,25,5,0,4126,9944,0,1,21),
(@GUID+120,18894,542,3,0,18894,455.932,-89.5175,9.60532,6.11447,25,0,0,14958,0,0,0,22),
(@GUID+121,17429,542,3,0,0,469.135,55.6605,9.61407,1.52205,25,0,0,10682,0,0,0,28),
(@GUID+122,17414,542,3,0,0,472.554,59.6033,9.6095,3.97623,25,0,0,10472,5875,0,0,28),
(@GUID+123,17371,542,3,0,0,466.425,59.3003,9.6138,5.29178,25,0,0,10843,6015,0,0,28),
(@GUID+124,17429,542,3,0,0,445.73,55.773,9.61462,1.62493,25,0,0,10682,0,0,0,29),
(@GUID+125,17371,542,3,0,0,448.667,59.2208,9.61455,4.06342,25,0,0,10843,6015,0,0,29),
(@GUID+126,17395,542,3,0,0,443.469,59.4859,9.61294,5.26508,25,0,0,10472,17625,0,0,29),
(@GUID+127,17371,542,3,0,0,447.236,103.553,9.6167,5.92373,25,0,0,10843,6015,0,0,20),
(@GUID+128,17414,542,3,0,0,452.502,102.32,9.61547,3.23374,25,0,0,10472,5875,0,0,20),
(@GUID+129,18894,542,3,0,18894,455.948,-77.5483,9.61356,6.11447,25,0,0,14958,0,0,0,22),
(@GUID+130,17491,542,3,0,17491,442.465,14.2575,9.54786,4.80914,25,0,0,7479,0,0,2,0),
(@GUID+131,17371,542,3,0,0,487.159,15.2406,9.55198,4.83743,25,0,0,10843,6015,0,0,23),
(@GUID+132,19016,542,3,0,0,422.845,-91.9675,9.62455,5.63538,25,5,0,4126,9944,0,1,21),
(@GUID+133,19016,542,3,0,0,412.636,-91.8976,9.62468,0.866439,25,5,0,4126,9944,0,1,21),
(@GUID+134,19016,542,3,0,0,411.529,-80.9528,9.61947,6.20636,25,5,0,4126,9944,0,1,21),
(@GUID+135,18894,542,3,0,18894,494.519,-5.65663,9.55562,4.63321,25,0,0,14958,0,0,0,0),
(@GUID+136,17371,542,3,0,0,490.004,-5.29839,9.55562,4.63321,25,0,0,10472,5875,0,0,0),
(@GUID+137,18894,542,3,0,18894,492.011,-81.0516,9.56252,1.64241,25,0,0,14958,0,0,0,0),
(@GUID+138,17371,542,3,0,0,488.269,-81.32,9.56252,1.64241,25,0,0,10843,6015,0,0,0),
(@GUID+139,17400,542,3,0,0,354.169,-176.092,-25.5428,0.0975055,25,0,0,15489,0,0,0,26),
(@GUID+140,17400,542,3,0,0,354.267,-162.775,-25.53,0.0975055,25,0,0,15489,0,0,0,26),
(@GUID+141,17400,542,3,0,0,335.973,-192.588,-25.5034,1.49001,25,0,0,15489,0,0,0,24),
(@GUID+142,17400,542,3,0,0,326.519,-191.823,-25.5097,1.49001,25,0,0,15489,0,0,0,24),
(@GUID+143,17371,542,3,0,0,313.472,-174.724,-25.5081,0.0173924,25,0,0,10472,5875,0,0,25),
(@GUID+144,17400,542,3,0,0,313.537,-178.455,-25.5095,0.0173924,25,0,0,15489,0,0,0,25),
(@GUID+145,17400,542,3,0,0,313.404,-170.833,-25.5093,0.0173924,25,0,0,15489,0,0,0,25),
(@GUID+146,17626,542,3,0,0,476.205,114.512,9.61977,3.13699,25,0,0,14958,5158,0,2,27),
(@GUID+147,17624,542,3,0,993,476.22,117.655,9.61977,3.13699,25,0,0,16023,0,0,2,27),
(@GUID+148,17626,542,3,0,0,476.236,121.19,9.61889,3.13699,25,0,0,14958,5158,0,2,27);

UPDATE creature SET spawnMask = 3 WHERE `map` = 542;
UPDATE creature SET spawntimesecs = 7200 WHERE `map` = 542;
UPDATE creature SET spawntimesecs = 86400 WHERE `map` = 542 AND id IN (17380, 17381, 17377, 17256);
UPDATE creature SET spawntimesecs = 3600 WHERE `map` = 542 AND id = 17491;
UPDATE gameobject SET spawntimesecs = 86400 WHERE `map` = 542 AND id IN (181823, 181766, 181812, 181811, 181822, 181819);
UPDATE creature SET pool_id = pool_id + 130 WHERE map = 542 AND pool_id != 0;

DELETE FROM creature_addon WHERE guid BETWEEN @GUID+1 AND @GUID+5;
INSERT INTO creature_addon (guid, bytes0, bytes2) VALUES
(@GUID+1, 66048, 4097), (@GUID+2, 66048, 4097), (@GUID+3, 66048, 4097), (@GUID+4, 66048, 4097), (@GUID+5, 66048, 4097);

DELETE FROM creature_addon WHERE guid IN (@GUID+35, @GUID+38, @GUID+39, @GUID+42, @GUID+50, @GUID+67, @GUID+68, @GUID+82, @GUID+106, @GUID+112, @GUID+113, @GUID+114, @GUID+130, @GUID+146, @GUID+147, @GUID+148);
INSERT INTO creature_addon (guid, path_id) VALUES
(@GUID+35, @GUID+35), (@GUID+38, @GUID+38), (@GUID+39, @GUID+39), (@GUID+42, @GUID+42), (@GUID+50, @GUID+50), (@GUID+67, @GUID+67),
(@GUID+68, @GUID+68), (@GUID+82, @GUID+82), (@GUID+106, @GUID+106), (@GUID+112, @GUID+112), (@GUID+113, @GUID+113), (@GUID+114, @GUID+114),
(@GUID+130, @GUID+130), (@GUID+146, @GUID+146), (@GUID+147, @GUID+147), (@GUID+148, @GUID+148);

DELETE FROM waypoint_data WHERE id IN (@GUID+35, @GUID+38, @GUID+39, @GUID+42, @GUID+50, @GUID+67, @GUID+68, @GUID+82, @GUID+106, @GUID+112, @GUID+113, @GUID+114, @GUID+130, @GUID+146, @GUID+147, @GUID+148);
INSERT INTO `waypoint_data` VALUES
(@GUID+42,1,284.936,-1.96804,9.04424,0,0,0,100,0),
(@GUID+42,2,266.223,-13.4516,6.96003,0,0,0,100,0),
(@GUID+42,3,254.934,-26.0985,6.95547,0,0,0,100,0),
(@GUID+42,4,244.856,-40.045,8.6632,0,0,0,100,0),
(@GUID+42,5,253.197,-27.9716,6.95299,0,0,0,100,0),
(@GUID+42,6,268.678,-12.4847,6.95837,0,0,0,100,0),
(@GUID+42,7,287.2,-2.90165,9.42918,0,0,0,100,0),
(@GUID+35,1,346.077,64.2714,9.61839,0,0,0,100,0),
(@GUID+35,2,345.416,108.807,9.61977,0,0,0,100,0),
(@GUID+38,1,342.575,63.9214,9.61769,0,0,0,100,0),
(@GUID+38,2,341.914,108.458,9.61837,0,0,0,100,0),
(@GUID+82,1,308.693,64.9842,9.61782,0,0,0,100,0),
(@GUID+82,2,309.985,114.345,9.61358,0,0,0,100,0),
(@GUID+39,1,312.072,64.8722,9.61761,0,0,0,100,0),
(@GUID+39,2,313.366,114.296,9.61543,0,0,0,100,0),
(@GUID+50,1,364.122,189.926,9.59542,0,0,0,100,0),
(@GUID+50,2,314.847,176.392,9.62025,0,0,0,100,0),
(@GUID+112,1,364.895,186.915,9.59524,0,0,0,100,0),
(@GUID+112,2,315.255,173.282,9.62128,0,0,0,100,0),
(@GUID+113,1,465.977,178.097,9.61907,0,0,0,100,0),
(@GUID+113,2,419.885,186.73,9.59365,0,0,0,100,0),
(@GUID+114,1,466.489,180.793,9.61953,0,0,0,100,0),
(@GUID+114,2,420.464,189.414,9.59446,0,0,0,100,0),
(@GUID+130,1,442.463,14.2849,9.54786,0,0,0,100,0),
(@GUID+130,2,435.484,2.83177,9.54786,0,0,0,100,0),
(@GUID+130,3,444.313,-10.0901,9.55167,0,0,0,100,0),
(@GUID+130,4,435.027,-22.2833,9.55045,0,0,0,100,0),
(@GUID+130,5,434.137,-10.1557,9.55987,0,0,0,100,0),
(@GUID+130,6,440.499,-0.151238,9.54832,0,0,0,100,0),
(@GUID+130,7,433.083,13.6874,9.54718,0,0,0,100,0),
(@GUID+68,1,459.571,-38.8539,9.55131,0,0,0,100,0),
(@GUID+68,2,466.216,-48.0988,9.56146,0,0,0,100,0),
(@GUID+68,3,474.261,-36.9078,9.55258,0,0,0,100,0),
(@GUID+68,4,479.511,-33.1751,9.55111,0,0,0,100,0),
(@GUID+68,5,486.023,-43.4294,9.55645,0,0,0,100,0),
(@GUID+68,6,491.657,-46.0494,9.55926,0,0,0,100,0),
(@GUID+68,7,491.997,-35.1761,9.55211,0,0,0,100,0),
(@GUID+68,8,478.628,-41.509,9.55455,0,0,0,100,0),
(@GUID+68,9,468.971,-46.6638,9.55957,0,0,0,100,0),
(@GUID+147,1,476.22,117.669,9.61889,0,0,0,100,0),
(@GUID+147,2,435.285,117.858,9.61769,0,0,0,100,0),
(@GUID+148,1,476.328,121.134,9.61777,0,0,0,100,0),
(@GUID+148,2,435.166,121.323,9.61668,0,0,0,100,0),
(@GUID+146,1,476.211,114.414,9.61814,0,0,0,100,0),
(@GUID+146,2,435.166,114.603,9.61914,0,0,0,100,0),
(@GUID+67,1,327.291,-8.2367,9.54766,0,0,0,100,0),
(@GUID+67,2,326.493,20.3016,9.61588,0,0,0,100,0),
(@GUID+106,1,208.78,-84.7173,9.57551,0,0,0,100,0),
(@GUID+106,2,225.251,-84.7355,9.59256,0,0,0,100,0),
(@GUID+106,3,229.01,-83.6926,9.59947,0,0,0,100,0),
(@GUID+106,4,231.816,-81.3054,9.61977,0,0,0,100,0),
(@GUID+106,5,233.955,-77.9818,9.6243,0,0,0,100,0),
(@GUID+106,6,234.854,-73.9629,9.61759,0,0,0,100,0),
(@GUID+106,7,239.132,-62.6261,9.61944,0,0,0,100,0),
(@GUID+106,8,235.508,-75.4607,9.61927,0,0,0,100,0),
(@GUID+106,9,234.803,-79.058,9.6235,0,0,0,100,0),
(@GUID+106,10,233.574,-81.6855,9.61897,0,0,0,100,0),
(@GUID+106,11,231.7,-83.5308,9.60423,0,0,0,100,0),
(@GUID+106,12,228.676,-84.7342,9.59625,0,0,0,100,0),
(@GUID+106,13,224.612,-85.2066,9.59657,0,0,0,100,0),
(@GUID+106,14,210.172,-84.952,9.57891,0,0,0,100,0);

UPDATE creature_template JOIN creature ON creature.id = creature_template.entry SET faction_a = 14, faction_h = 14 WHERE map = 542 AND (faction_a = 16 OR faction_h = 16);

DELETE FROM creature_addon WHERE guid IN (@GUID+109, @GUID+47, @GUID+121, @GUID+124);
INSERT INTO creature_addon (guid, bytes1) VALUES
(@GUID+109, 8), (@GUID+47, 8), (@GUID+121, 8), (@GUID+124, 8);

UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 21174;
DELETE FROM smart_scripts WHERE entryorguid = 21174;
INSERT INTO smart_scripts VALUES
(21174, 0, 0, 0, 1, 0, 100, 6, 5000, 10000, 80000, 100000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Blood Furnace - Magtheridon - Random taunts");

DELETE FROM creature_text WHERE entry = 21174;
INSERT INTO creature_text VALUES
(21174, 0, 0, "Mon sang sera votre perte !", 1, 0, 100, 0, 0, 10252, "Blood Furnace - Magtheridon - Random taunts"),
(21174, 0, 1, "Vous croyez que votre sorcellerie de bas étage pourra me retenir longtemps ?", 1, 0, 100, 0, 0, 10251, "Blood Furnace - Magtheridon - Random taunts"),
(21174, 0, 2, "Du balai, parasites inconscients. Mon sang est à moi !", 1, 0, 100, 0, 0, 20250, "Blood Furnace - Magtheridon - Random taunts"),
(21174, 0, 3, "Illidan est un crétin arrogant. Je l'écraserai et l'Outreterre sera de nouveau à moi.", 1, 0, 100, 0, 0, 10249, "Blood Furnace - Magtheridon - Random taunts"),
(21174, 0, 4, "Vermines ! Sangsues ! Prenez mon sang et qu'il vous étouffe !", 1, 0, 100, 0, 0, 10248, "Blood Furnace - Magtheridon - Random taunts"),
(21174, 0, 5, "Misérables insectes importuns, libérez-moi et je vous accorderai peut-être une mort rapide !", 1, 0, 100, 0, 0, 10247, "Blood Furnace - Magtheridon - Random taunts");

UPDATE creature_template SET ScriptName = "mob_fel_orc_neophyte" WHERE entry = 17429;
