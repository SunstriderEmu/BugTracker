DROP TABLE IF EXISTS `points_of_interest`;
CREATE TABLE `points_of_interest` (
  `entry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `x` float NOT NULL DEFAULT '0',
  `y` float NOT NULL DEFAULT '0',
  `icon` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `flags` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `data` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `icon_name` text NOT NULL,
  `VerifiedBuild` smallint(5) DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

#change some IDs a bit too high
UPDATE gossip_menu SET entry = 4,text_id = 4 WHERE text_id = 10000000;
UPDATE gossip_menu SET entry = 6,text_id = 6 WHERE text_id = 16777214;
UPDATE gossip_menu SET entry = 7,text_id = 7 WHERE text_id = 16777215;
UPDATE gossip_menu SET entry = 9,text_id = 9 WHERE text_id = 200029;
UPDATE gossip_menu SET entry = 10, text_id = 10 WHERE text_id = 91190;

UPDATE creature_gossip SET menu_id = 4 WHERE menu_id = 10000000;
UPDATE creature_gossip SET menu_id = 6 WHERE menu_id = 16777214;
UPDATE creature_gossip SET menu_id = 7 WHERE menu_id = 16777215;
DELETE FROM creature_gossip WHERE menu_id = 1000000;
UPDATE creature_gossip SET menu_id = 9 WHERE menu_id = 200029;
UPDATE creature_gossip SET menu_id = 10 WHERE menu_id = 91190;

UPDATE gossip_text SET ID = 4 WHERE ID = 10000000;
UPDATE gossip_text SET ID = 6 WHERE ID = 16777214;
UPDATE gossip_text SET ID = 7 WHERE ID = 16777215;
UPDATE gossip_text SET ID = 9 WHERE ID = 200029;
UPDATE gossip_text SET ID = 10 WHERE ID = 91190;



ALTER TABLE gossip_menu
	DROP PRIMARY KEY;

ALTER TABLE gossip_menu
	ADD PRIMARY KEY(entry);