UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry IN (20610, 20777);
DELETE FROM smart_scripts WHERE entryorguid IN (20610, 20777);
INSERT INTO smart_scripts VALUES
(20610, 0, 0, 1, 67, 0, 100, 0, 35771, 0, 0, 0, 33, 20982, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Talbuk Doe - Dummy effect - Complete quest 10427"),
(20610, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Talbuk Doe - Linked - Kill self"),
(20777, 0, 0, 0, 67, 0, 100, 0, 35771, 0, 0, 0, 33, 20982, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Talbuk Sire - Dummy effect - Complete quest 10427"),
(20777, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Talbuk Sire - Linked - Kill self");
