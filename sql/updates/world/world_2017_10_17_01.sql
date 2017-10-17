
DROP TABLE IF EXISTS `locales_broadcast_text`;

CREATE TABLE `locales_broadcast_text` (
  `ID` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `locale` varchar(4) NOT NULL,
  `MaleText` text DEFAULT NULL,
  `FemaleText` text DEFAULT NULL,
  `VerifiedBuild` smallint(5) DEFAULT 0,
  PRIMARY KEY (`ID`,`locale`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
