ALTER TABLE game_event_creature
MODIFY COLUMN event INT(16);

REPLACE INTO command VALUES ("npc linkgameevent",3,"Syntax: .npc linkgameevent #eventid [#guid]\n\nLink an npc of given guid (or the creature selected if none given) to given event.");
REPLACE INTO command VALUES ("npc unlinkgameevent",3,"Syntax: .npc unlinkgameevent [#guid]\n\nUnlink an npc of given guid (or the creature selected if none given) from all events.");
REPLACE INTO command VALUES ("gobject linkgameevent",3,"Syntax: .gobject linkgameevent #event #guid\n\nLink a gobjectl of given guid (or the creature selected if none given) to given event.");
REPLACE INTO command VALUES ("gobject unlinkgameevent",3,"Syntax: .gobject unlinkgameevent #guid\n\nUnlink an npc of given gobject (or the creature selected if none given) from all events.");

REPLACE INTO command VALUES ("event create",4,"Syntax: .event create $name\n\nNYI");