UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 15215;

DELETE FROM smart_scripts WHERE entryorguid = 15215;
INSERT INTO smart_scripts VALUES
(15215, 0, 0, 0, 0, 0, 100, 0, 15000, 22000, 25000, 35000, 11, 44415, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Blackout on random"),
(15215, 0, 1, 0, 0, 0, 100, 0, 30000, 45000, 60000, 90000, 11, 20740, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Dominate Mind on random"),
(15215, 0, 2, 0, 0, 0, 100, 0, 15000, 25000, 30000, 40000, 11, 35096, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Cast Greater Heal on self"),
(15215, 0, 3, 0, 0, 0, 100, 0, 3000, 4000, 4000, 8000, 11, 16568, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Mind Flay on target"),
(15215, 0, 4, 0, 0, 0, 100, 0, 8000, 12000, 24000, 28000, 11, 13704, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Cast Psychic Screal on target"),
(15215, 0, 5, 0, 0, 0, 100, 0, 5000, 8000, 12000, 15000, 11, 11639, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, "Cast Shadow Word: Pain on random");
