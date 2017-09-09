REPLACE INTO command (name, security, help, ircAllowed) VALUES ("debug spawnbatchobjects", 5, "Syntax: .debug spawnbatchobjects <filename> [savetodb]\n\Read gameobjects from file and summon them in the current map for previsualisation. Player must be in the map specified by the import file. See C++ code for required import file format. Use the [savetodb] arg to validates changes and write the gobjects to db", 0);

UPDATE gameobject_template SET flags = flags | 32 WHERE entry IN (186622, 186338, 186482);
UPDATE gameobject_template SET flags = flags | 2 WHERE entry IN (187380, 187378);
UPDATE gameobject SET position_x = 134.009, position_y = 1642.8, position_z = 42.0841, rotation0 = 0, rotation1 = 0, rotation2 = -1, rotation3 = 0 WHERE guid = 20447;
