UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 22160;

DELETE FROM smart_scripts WHERE entryorguid = 22160;
INSERT INTO smart_scripts VALUES
(22160, 0, 0, 1, 8, 0, 100, 0, 38173, 0, 0, 0, 33, 22383, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Killcredit 22383 on SpellHit (quest 10714)"),
(22160, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 12, 22492, 3, 20000, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, "Summon Spirit");
