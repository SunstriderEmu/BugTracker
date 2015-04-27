#per creature - guid & menu id
ALTER TABLE npc_gossip
 RENAME TO creature_gossip,
 CHANGE textid menu_id MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0';
 
ALTER TABLE npc_option
 RENAME TO npc_option_old;
 
ALTER TABLE npc_text
 RENAME TO gossip_text;
ALTER TABLE locales_npc_text
  RENAME TO locales_gossip_text;
  
DROP TABLE IF EXISTS `gossip_menu`;
CREATE TABLE `gossip_menu` (
  `entry` smallint(5) unsigned NOT NULL DEFAULT '0',
  `text_id` mediumint(8) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`,`text_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
REPLACE INTO gossip_menu
SELECT menu_id, menu_id FROM creature_gossip;

DROP TABLE IF EXISTS `gossip_menu_option`;
CREATE TABLE `gossip_menu_option` (
  `menu_id` smallint(5) unsigned NOT NULL DEFAULT '0',
  `id` smallint(5) unsigned NOT NULL DEFAULT '0',
  `option_icon` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `option_text` text,
  `OptionBroadcastTextID` mediumint(6) NOT NULL DEFAULT '0',
  `option_id` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `npc_option_npcflag` int(10) unsigned NOT NULL DEFAULT '1',
  `action_menu_id` int(10) unsigned NOT NULL DEFAULT '0',
  `action_poi_id` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `box_coded` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `box_money` int(10) unsigned NOT NULL DEFAULT '0',
  `box_text` text,
  `BoxBroadcastTextID` mediumint(6) NOT NULL DEFAULT '0',
  PRIMARY KEY (`menu_id`,`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
INSERT INTO gossip_menu_option 
	SELECT 0, id, icon, option_text, 0,  action, npcflag, 0, 0, 0, 0, NULL, 0 FROM npc_option_old WHERE action != 0;
 
ALTER TABLE locales_npc_option 
  RENAME TO locales_gossip_menu_option,
  CHANGE entry id MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0',
  ADD menu_id SMALLINT(6) UNSIGNED NOT NULL DEFAULT '0' FIRST;
  
 #drop useless table
DROP TABLE IF EXISTS npc_gossip_textid;
DROP TABLE game_event_npc_gossip;
DROP TABLE npc_option_old;

# test query :
#SELECT guid, c.id, NAME, menu_id, gm.text_id, gt.text0_0, gt.text0_1 
#FROM creature c
#JOIN creature_template ct ON c.id = ct.entry
#JOIN creature_gossip ON npc_guid = guid
#JOIN gossip_menu gm ON gm.entry = menu_id
#JOIN gossip_text gt ON gt.ID = gm.text_id 
#WHERE guid = 29