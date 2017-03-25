REPLACE INTO command (name, security, help, ircAllowed) VALUES ("debug spawnbatchobjects", 5, "Syntax: .debug spawnbatchobjects <filename> [savetodb]\n\Read gameobjects from file and summon them in the current map for previsualisation. Player must be in the map specified by the import file. See C++ code for required import file format. Use the [savetodb] arg to validates changes and write the gobjects to db", 0);

#add GO_FLAG_NOT_SELECTABLE to those gobjects
#select * from gameobject_template where entry = 186622;
UPDATE gameobject_template SET flags = flags | 32 WHERE entry IN (186622);