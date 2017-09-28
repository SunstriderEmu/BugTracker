UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 20561;

DELETE FROM smart_scripts WHERE entryorguid = 20561;
INSERT INTO smart_scripts VALUES
(20561, 0, 0, 0, 67, 0, 100, 0, 35372, 0, 0, 0, 33, 20561, 0, 0, 0, 0, 0, 18, 5, 0, 0, 0, 0, 0, 0, "KilledMonster on SpellHit");
