DROP TABLE IF EXISTS `creature_scripts`;
CREATE TABLE `creature_scripts` (
  `entryorguid` mediumint(11) NOT NULL,
  `scriptname` char(64) NOT NULL,
  PRIMARY KEY (`entryorguid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
