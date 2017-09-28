UPDATE creature_template SET AIName = "SmartAI" WHERE entry = 23080;
DELETE FROM smart_scripts WHERE entryorguid = 23080;
INSERT INTO smart_scripts VALUES  (23080, 0, 0, 0, 0, 0, 100, 3, 200, 200, 5000, 5000, 11, 40089, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Geyser (Knockback) when summoned"), (23080, 0, 1, 0, 0, 0, 100, 1, 500, 500, 5000, 5000, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Suicide himself");

UPDATE creature_template SET minlevel = 70, maxlevel = 70, faction_A = 1813, faction_H = 1813, flags_extra = 2 WHERE entry = 23080;
