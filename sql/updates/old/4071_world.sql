DROP TABLE IF EXISTS `player_factionchange_titles`;
CREATE TABLE IF NOT EXISTS `player_factionchange_titles` (
  `alliance_id` int(8) NOT NULL,
  `alliance_comment` text,
  `horde_id` int(8) NOT NULL,
  `horde_comment` text,
  PRIMARY KEY  (`alliance_id`,`horde_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
