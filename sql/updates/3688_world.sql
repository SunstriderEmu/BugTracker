-- Tables structure

DROP TABLE IF EXISTS `player_factionchange_items`;
CREATE TABLE IF NOT EXISTS `player_factionchange_items` (
  `alliance_id` int(8) NOT NULL,
  `alliance_comment` text,
  `horde_id` int(8) NOT NULL,
  `horde_comment` text,
  PRIMARY KEY  (`alliance_id`,`horde_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `player_factionchange_items_race_specific`;
CREATE TABLE IF NOT EXISTS `player_factionchange_items_race_specific` (
  `id` int(8) NOT NULL,
  `race_id` int(8) NOT NULL,
  `item_id` int(8) NOT NULL,
  PRIMARY KEY (`race_id`, `item_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `player_factionchange_reputations`;
CREATE TABLE IF NOT EXISTS `player_factionchange_reputations` (
  `alliance_id` int(8) NOT NULL,
  `alliance_comment` text,
  `horde_id` int(8) NOT NULL,
  `horde_comment` text,
  PRIMARY KEY  (`alliance_id`,`horde_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `player_factionchange_spells`;
CREATE TABLE IF NOT EXISTS `player_factionchange_spells` (
  `alliance_id` int(8) NOT NULL,
  `alliance_comment` text,
  `horde_id` int(8) NOT NULL,
  `horde_comment` text,
  PRIMARY KEY  (`alliance_id`,`horde_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
