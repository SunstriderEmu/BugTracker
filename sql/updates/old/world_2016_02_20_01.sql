
DROP TABLE IF EXISTS `game_event_npc_trainer`;
CREATE TABLE `game_event_npc_trainer` (
  `event` INT(11) UNSIGNED NOT NULL,
  `entry` MEDIUMINT(8) UNSIGNED NOT NULL,
  `spell` INT(10) UNSIGNED NOT NULL,
  `spellcost` INT(10) UNSIGNED NOT NULL,
  `reqskill` SMALLINT(5) UNSIGNED NOT NULL,
  `reqskillvalue` SMALLINT(5) UNSIGNED NOT NULL,
  `reqlevel` TINYINT(3) UNSIGNED NOT NULL,
  PRIMARY KEY (`entry`,`spell`),
  KEY `spell` (`spell`),
  CONSTRAINT `game_event_npc_trainer_ibfk_1` FOREIGN KEY (`spell`) REFERENCES `spell_template` (`entry`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `game_event_npc_trainer_ibfk_2` FOREIGN KEY (`entry`) REFERENCES `creature_template` (`entry`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=INNODB DEFAULT CHARSET=latin1;


DROP TABLE IF EXISTS `gossip_menu_option_generic`;
CREATE TABLE `gossip_menu_option_generic` (
  `id` smallint(5) unsigned NOT NULL DEFAULT '0',
  `option_icon` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `option_text` text,
  `option_id` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `npc_option_npcflag` int(10) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*Data for the table `gossip_menu_option_generic` */

insert  into `gossip_menu_option_generic`(`id`,`option_icon`,`option_text`,`option_id`,`npc_option_npcflag`) values (2,0,'Do quests',2,2),(3,1,'I want to browse your goods',3,128),(4,2,'I want to travel fast',4,8192),(5,3,'Train me!',5,16),(6,4,'Bring me back to life',6,16384),(7,5,'Unknown',7,32768),(8,5,'Make this inn my home',8,65536),(9,6,'Show me my bank',9,131072),(10,7,'How do I form a guild?',10,262144),(11,8,'I want to create a guild crest.',11,524288),(12,10,'I want to join the Battle Ground.',12,1048576),(13,11,'Auction!',13,2097152),(14,12,'UNIT_NPC_FLAG_STABLE',14,4194304),(15,13,'UNIT_NPC_FLAG_ARMORER',15,4096),(49,2,'I wish to unlearn my talents',16,16),(50,2,'I wish to unlearn my pet\'s skills',17,16),(51,0,'UNIT_NPC_FLAG_OUTDOORPVP',18,536870912),(52,0,'Tricks or treat!',19,65536);

DELETE FROM gossip_menu_option WHERE menu_id = 0;