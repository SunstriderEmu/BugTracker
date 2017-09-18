ALTER TABLE `battleground_template` ADD COLUMN `StartMaxDist` float NOT NULL DEFAULT '0';
ALTER TABLE `battleground_template` ADD COLUMN `ScriptName` char(64) NOT NULL DEFAULT '';
ALTER TABLE `battleground_template` ADD COLUMN  `Comment` char(32) NOT NULL;

UPDATE battleground_template SET Comment = "Alterac Valley", StartMaxDist = 100 WHERE ID = 1;
UPDATE battleground_template SET Comment = "Warsong Gulch", StartMaxDist = 75 WHERE ID = 2;
UPDATE battleground_template SET Comment = "Arathi Basin", StartMaxDist = 75 WHERE ID = 3;
UPDATE battleground_template SET Comment = "Nagrand Arena" WHERE ID = 4;
UPDATE battleground_template SET Comment = "Blades's Edge Arena" WHERE ID = 5;
UPDATE battleground_template SET Comment = "All Arena" WHERE ID = 6;
UPDATE battleground_template SET Comment = "Eye of The Storm", StartMaxDist = 75 WHERE ID = 7;
UPDATE battleground_template SET Comment = "Ruins of Lordaeron" WHERE ID = 8;


DROP TABLE IF EXISTS `character_battleground_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `character_battleground_data` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `instanceId` int(10) unsigned NOT NULL COMMENT 'Instance Identifier',
  `team` smallint(5) unsigned NOT NULL,
  `joinX` float NOT NULL DEFAULT '0',
  `joinY` float NOT NULL DEFAULT '0',
  `joinZ` float NOT NULL DEFAULT '0',
  `joinO` float NOT NULL DEFAULT '0',
  `joinMapId` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT 'Map Identifier',
  `taxiStart` int(10) unsigned NOT NULL DEFAULT '0',
  `taxiEnd` int(10) unsigned NOT NULL DEFAULT '0',
  `mountSpell` mediumint(8) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Player System';