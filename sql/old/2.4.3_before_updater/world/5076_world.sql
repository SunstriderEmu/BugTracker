DROP TABLE IF EXISTS player_factionchange_reputations;
CREATE TABLE player_factionchange_reputations (
  race_from int unsigned not null,
  race_to int unsigned not null,
  faction_from int unsigned not null,
  faction_from_comment varchar(100) not null default '',
  faction_to int unsigned not null,
  faction_to_comment varchar(100) not null default '',
  primary key (race_from, race_to, faction_from)
) ENGINE=InnoDB, DEFAULT CHARSET=utf8;
