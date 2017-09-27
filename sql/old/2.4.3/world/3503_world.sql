UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22844;

DELETE FROM smart_scripts WHERE entryorguid = 22844;
INSERT INTO smart_scripts VALUES
(22844, 0, 0, 0, 0, 0, 100, 2, 5000, 5000, 18000, 18000, 11, 15284, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Cleave"),
(22844, 0, 1, 0, 0, 0, 100, 2, 6000, 6000, 20000, 20000, 11, 32588, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Concussion Blow"),
(22844, 0, 2, 0, 0, 0, 100, 2, 15000, 15000, 22000, 22000, 11, 41182, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Concussive Throw"),
(22844, 0, 3, 4, 2, 0, 100, 3, 10, 30, 1000, 1000, 11, 34970, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Enrage at 30%"),
(22844, 0, 4, 0, 61, 0, 100, 3, 0, 0, 0, 0, 1, 0, 100, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Enrage emote at 30%");

DELETE FROM creature_text WHERE entry = 22844;
INSERT INTO creature_text (entry, groupid, id, text, type, comment) VALUES (22844, 0, 0, "Seigneur de bataille cendrelangue devient fou furieux !", 2, "Enrage emote");
