UPDATE creature_template SET AIName = "SmartAI", ScriptName = "" WHERE entry = 15199;

DELETE FROM smart_scripts WHERE entryorguid = 15199;
INSERT INTO smart_scripts VALUES (15199, 0, 0, 0, 1, 0, 100, 0, 1000, 5000, 30000, 45000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Sergeant Hartman - Say OOC");

DELETE FROM creature_text WHERE entry = 15199;
INSERT INTO creature_text VALUES (15199, 0, 0, "Je suis le sergent d'armement Hartman et votre chef instructeur.", 0, 0, 100, 1, 0, 0, "Sergeant Hartman - Say OOC");
