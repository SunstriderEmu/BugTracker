
DROP TABLE IF EXISTS `quest_start_scripts_tmp`;

CREATE TABLE `quest_start_scripts_tmp` (
  `id` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `delay` int(10) unsigned NOT NULL DEFAULT 0,
  `command` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `datalong` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `datalong2` int(10) unsigned NOT NULL DEFAULT 0,
  `dataint` int(11) NOT NULL DEFAULT 0,
  `x` float NOT NULL DEFAULT 0,
  `y` float NOT NULL DEFAULT 0,
  `z` float NOT NULL DEFAULT 0,
  `o` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO quest_start_scripts_tmp SELECT DISTINCT * FROM quest_start_scripts;

DELETE FROM quest_start_scripts;

INSERT INTO quest_start_scripts SELECT * FROM quest_start_scripts_tmp;