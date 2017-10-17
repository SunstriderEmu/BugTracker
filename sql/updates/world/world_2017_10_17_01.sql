
DROP TABLE IF EXISTS `locales_broadcast_text`;

CREATE TABLE `locales_broadcast_text` (
  `ID` int(11) unsigned NOT NULL DEFAULT 0,
  `locale` varchar(4) NOT NULL,
  `MaleText` text DEFAULT NULL,
  `FemaleText` text DEFAULT NULL,
  `VerifiedBuild` smallint(5) DEFAULT 0,
  PRIMARY KEY (`ID`,`locale`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

ALTER TABLE broadcast_text CHANGE COLUMN `ID` `ID` INT(11) UNSIGNED NOT NULL;
