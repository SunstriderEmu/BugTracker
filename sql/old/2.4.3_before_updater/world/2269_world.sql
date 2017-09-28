DROP TABLE IF EXISTS `quest_pool`;
CREATE TABLE `quest_pool` (
  `pool_id` mediumint(2) unsigned NOT NULL default '0',
  `quest_id` mediumint(3) unsigned NOT NULL default '0',
  PRIMARY KEY (`pool_id`, `quest_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `quest_pool_current`;
CREATE TABLE `quest_pool_current` (
  `pool_id` mediumint(2) unsigned NOT NULL default '0',
  `quest_id` mediumint(3) unsigned NOT NULL default'0',
  PRIMARY KEY (`pool_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

ALTER TABLE `creature_template` ADD COLUMN `pool_id` mediumint(2) unsigned NOT NULL default '0' AFTER `ScriptName`;

-- First set of data
UPDATE creature_template SET pool_id = 1 WHERE entry = 24369;
INSERT INTO quest_pool VALUES 
(1, 11354),
(1, 11362),
(1, 11363),
(1, 11368),
(1, 11369),
(1, 11370),
(1, 11372),
(1, 11373),
(1, 11374),
(1, 11375),
(1, 11378),
(1, 11382),
(1, 11384),
(1, 11386),
(1, 11388),
(1, 11499);
