UPDATE command SET `name` = "npc setemotestate" where `name` = "npc playemote";
REPLACE INTO command VALUES ("debug playemote", 2, "Syntax: .debug playemote <emoteId>", 0);