DROP TABLE IF EXISTS `spell_scripts_new`;
CREATE TABLE `spell_scripts_new` (
  `id` mediumint(11) NOT NULL,
  `scriptname` char(64) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
