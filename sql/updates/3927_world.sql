UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (13444, 13445);

DELETE FROM creature_text WHERE entry = 13445;
INSERT INTO creature_text VALUES (13445, 0, 1, "Joyeux Voile d'hiver à la population de WoW Mania !", 1, 0, 100, 0, 0, 0, "");

DELETE FROM smart_scripts WHERE entryorguid IN (13444, 13445);
INSERT INTO smart_scripts VALUES (13445, 0, 0, 0, 1, 0, 100, 0, 20000, 30000, 1750000, 1850000, 1, 13445, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Great-father Winter - Greetings every 30 min");
INSERT INTO smart_scripts VALUES (13444, 0, 0, 0, 1, 0, 100, 0, 20000, 30000, 1750000, 1850000, 1, 13445, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Greatfather Winter - Greetings every 30 min");
