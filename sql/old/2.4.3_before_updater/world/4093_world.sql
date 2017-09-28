UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (16346, 16469, 16308, 16249, 16320, 16245, 16246);

DELETE FROM smart_scripts WHERE entryorguid IN (16346, 16469, 16308, 16249, 16320, 16245, 16246);
INSERT INTO smart_scripts VALUES
(16346, 0, 0, 0, 15, 0, 100, 0, 2, 5000, 5000, 0, 11, 17201, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Shadowpine Hexxer - CCed - Cast Dispel Magic"),
(16346, 0, 1, 0, 0, 0, 100, 0, 12000, 18000, 22000, 30000, 11, 29044, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Shadowpine Hexxer - IC Timer - Cast Hex"),

(16469, 0, 0, 0, 0, 0, 100, 0, 500, 500, 30000, 45000, 11, 31394, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowpine Shadowcaster - IC Timer - Cast Mark of Shadow"),
(16469, 0, 1, 0, 0, 0, 100, 0, 5000, 8000, 4000, 5000, 11, 16568, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Shadowpine Shadowcaster - IC Timer - Cast Mind Flay"),

(16308, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 1, 20792, 3500, 3500, 25, 10, 2, 0, 0, 0, 0, 0, 0, 0, "Deathcage Sorcerer - Caster Template"),
(16308, 0, 1, 0, 9, 1, 100, 0, 1, 9, 15000, 22000, 11, 12748, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Deathcage Sorcerer - Range 1-9 yards - Cast Frost Nova"),

(16249, 0, 0, 0, 37, 0, 100, 0, 0, 0, 0, 0, 58, 1, 20792, 3500, 3500, 25, 10, 2, 0, 0, 0, 0, 0, 0, 0, "Masophet the Black - Caster Template"),
(16249, 0, 1, 0, 0, 1, 100, 0, 500, 500, 12000, 18000, 11, 16568, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Masophet the Black - IC Timer - Mind Flay"),

(16320, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 8140, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Eye of Dar'Khan - Aggro - Cast Befuddlement"),
(16320, 0, 1, 0, 0, 0, 100, 0, 1000, 2000, 22000, 30000, 11, 14868, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Eye of Dar'Khan - IC Timer - Cast Curse of Agony"),

(16245, 0, 0, 0, 0, 0, 100, 0, 5000, 8000, 8000, 12000, 11, 40504, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Luzran - IC Timer - Cast Cleave"),
(16245, 0, 1, 0, 0, 0, 100, 0, 12000, 20000, 22000, 30000, 11, 31389, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Luzran - IC Timer - Cast Knock Away"),
(16245, 0, 2, 0, 0, 0, 100, 0, 2000, 3000, 8000, 11000, 11, 13444, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Luzran - IC Timer - Cast Sunder Armor"),

(16246, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 8014, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Knucklerot - Aggro - Cast Tetanus"),
(16246, 0, 1, 0, 0, 0, 100, 0, 2000, 8000, 22000, 30000, 11, 3396, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Knucklerot - IC Timer - cast Corrosive Poison");
