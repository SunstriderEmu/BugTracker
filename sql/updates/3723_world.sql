DROP TABLE IF EXISTS `creature_scripts`;
CREATE TABLE `creature_scripts` (
  `id` mediumint(11) NOT NULL,
  `scriptname` char(64) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
