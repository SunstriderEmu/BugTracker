DROP TABLE IF EXISTS `instance_encounter`;
CREATE TABLE `instance_encounter` (
  `mapid` smallint(5) unsigned NOT NULL default '0',
  `eventid` smallint(5) unsigned NOT NULL default '0',
  `comment` varchar(100) NOT NULL default '',
  PRIMARY KEY(`mapid`, `eventid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `creature_encounter_respawn`;
CREATE TABLE `creature_encounter_respawn` (
  `guid` int(10) unsigned NOT NULL default '0',
  `eventid` smallint(5) unsigned NOT NULL default '0',
  PRIMARY KEY(`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO command VALUES ("npc seteventid", 5, "Set linked instance event to (dis)allow creature respawn. Must target desired creature.");
