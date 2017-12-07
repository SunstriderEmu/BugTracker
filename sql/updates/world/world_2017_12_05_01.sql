DROP TABLE IF EXISTS creature_respawn;
DROP TABLE IF EXISTS gameobject_respawn;

DROP TABLE IF EXISTS `spawn_group`;

CREATE TABLE `spawn_group` (
  `groupId` int(10) unsigned NOT NULL,
  `spawnType` tinyint(10) unsigned NOT NULL,
  `spawnId` int(10) unsigned NOT NULL,
  PRIMARY KEY (`groupId`,`spawnType`,`spawnId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `spawn_group_template`;

CREATE TABLE `spawn_group_template` (
  `groupId` int(10) unsigned NOT NULL,
  `groupName` varchar(100) NOT NULL,
  `groupFlags` int(10) unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`groupId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

insert into `spawn_group_template` (`groupId`, `groupName`, `groupFlags`) values('0','Default Group','1');
insert into `spawn_group_template` (`groupId`, `groupName`, `groupFlags`) values('1','Legacy Group','3');
insert into `spawn_group_template` (`groupId`, `groupName`, `groupFlags`) values('2','Dynamic Scaling (Quest objectives)','9');
insert into `spawn_group_template` (`groupId`, `groupName`, `groupFlags`) values('3','Dynamic Scaling (Escort NPCs)','25');
insert into `spawn_group_template` (`groupId`, `groupName`, `groupFlags`) values('4','Dynamic Scaling (Gathering nodes)','9');

DROP TABLE IF EXISTS `instance_spawn_groups`;

CREATE TABLE `instance_spawn_groups` (
  `instanceMapId` smallint(5) unsigned NOT NULL,
  `bossStateId` tinyint(3) unsigned NOT NULL,
  `bossStates` tinyint(3) unsigned NOT NULL,
  `spawnGroupId` int(10) unsigned NOT NULL,
  `flags` tinyint(3) unsigned NOT NULL,
  PRIMARY KEY (`instanceMapId`,`bossStateId`,`spawnGroupId`,`bossStates`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `linked_respawn`;

CREATE TABLE `linked_respawn` (
  `guid` int(10) unsigned NOT NULL COMMENT 'dependent creature',
  `linkedGuid` int(10) unsigned NOT NULL COMMENT 'master creature',
  `linkType` tinyint(3) unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`guid`,`linkType`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Creature Respawn Link System';

DROP TABLE IF EXISTS creature_linked_respawn;
REPLACE INTO linked_respawn VALUES (97405, 15691, 0);

DROP TABLE IF EXISTS `pool_creature`;

CREATE TABLE `pool_creature` (
  `guid` int(10) unsigned NOT NULL DEFAULT 0,
  `pool_entry` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `chance` float unsigned NOT NULL DEFAULT 0,
  `description` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`guid`),
  KEY `idx_guid` (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pool_gameobject`;

CREATE TABLE `pool_gameobject` (
  `guid` int(10) unsigned NOT NULL DEFAULT 0,
  `pool_entry` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `chance` float unsigned NOT NULL DEFAULT 0,
  `description` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`guid`),
  KEY `idx_guid` (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pool_pool`;

CREATE TABLE `pool_pool` (
  `pool_id` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `mother_pool` mediumint(8) unsigned NOT NULL DEFAULT 0,
  `chance` float NOT NULL DEFAULT 0,
  `description` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`pool_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pool_template`;

CREATE TABLE `pool_template` (
  `entry` mediumint(8) unsigned NOT NULL DEFAULT 0 COMMENT 'Pool entry',
  `max_limit` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'Max number of objects (0) is no limit',
  `description` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `game_event_pool`;

CREATE TABLE `game_event_pool` (
  `eventEntry` tinyint(4) NOT NULL COMMENT 'Entry of the game event. Put negative entry to remove during event.',
  `pool_entry` mediumint(8) unsigned NOT NULL DEFAULT 0 COMMENT 'Id of the pool',
  PRIMARY KEY (`pool_entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;