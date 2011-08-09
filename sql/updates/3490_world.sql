UPDATE creature_template SET AIName = "SmartAI" WHERE entry = 23080;
DELETE FROM smart_scripts WHERE entryorguid = 23080;
INSERT INTO smart_scripts VALUES  (23080, 0, 0, 0, 1, 0, 100, 3, 500, 500, 5000, 5000, 11, 40089, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Geyser (Knockback) when summoned");
