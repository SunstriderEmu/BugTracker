-- Delete some old texts
DELETE FROM script_texts WHERE entry <= -1590000 and entry >= -1590007;
DELETE FROM script_texts WHERE entry <= -1564013 and entry >= -1564017;

CREATE TABLE `broadcast_text` (
  `ID` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `Language` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `MaleText` longtext,
  `FemaleText` longtext,
  `EmoteID0` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `EmoteID1` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `EmoteID2` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `EmoteDelay0` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `EmoteDelay1` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `EmoteDelay2` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `SoundId` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `Unk1` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `Unk2` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` smallint(5) DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


CREATE TABLE `locales_broadcast_text` (
  `ID` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `MaleText_loc1` longtext,
  `MaleText_loc2` longtext,
  `MaleText_loc3` longtext,
  `MaleText_loc4` longtext,
  `MaleText_loc5` longtext,
  `MaleText_loc6` longtext,
  `MaleText_loc7` longtext,
  `MaleText_loc8` longtext,
  `FemaleText_loc1` longtext,
  `FemaleText_loc2` longtext,
  `FemaleText_loc3` longtext,
  `FemaleText_loc4` longtext,
  `FemaleText_loc5` longtext,
  `FemaleText_loc6` longtext,
  `FemaleText_loc7` longtext,
  `FemaleText_loc8` longtext,
  `VerifiedBuild` smallint(5) DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

CREATE TABLE `locales_creature_text` (
  `entry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `groupid` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `id` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `text_loc1` text,
  `text_loc2` text,
  `text_loc3` text,
  `text_loc4` text,
  `text_loc5` text,
  `text_loc6` text,
  `text_loc7` text,
  `text_loc8` text,
  PRIMARY KEY (`entry`,`groupid`,`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

insert  into `broadcast_text`(`ID`,`Language`,`MaleText`,`FemaleText`,`EmoteID0`,`EmoteID1`,`EmoteID2`,`EmoteDelay0`,`EmoteDelay1`,`EmoteDelay2`,`SoundId`,`Unk1`,`Unk2`,`VerifiedBuild`) values (1,0,'The Scourge are upon us! Run! Run for your lives!',NULL,0,0,0,0,0,0,0,0,0,0),(2,0,'Please help us! The Prince has gone mad!',NULL,0,0,0,0,0,0,0,0,0,0),(3,0,'Seek sanctuary in Hearthglen! It is our only hope!',NULL,0,0,0,0,0,0,0,0,0,0),(4,0,'We are saved! The peasants have escaped the Scourge!',NULL,0,0,0,0,0,0,0,0,0,0),(5,0,'I have failed once more...',NULL,0,0,0,0,0,0,0,0,0,0),(6,0,'Thank you, kind stranger. May your heroism never be forgotten.',NULL,0,0,0,0,0,0,0,0,0,0),(7,0,'The power of the light is truly great and merciful.',NULL,0,0,0,0,0,0,0,0,0,0),(8,0,'Stranger, find the fallen Prince Menethil and end his reign of terror.',NULL,0,0,0,0,0,0,0,0,0,0),(9,0,'I will not last much longer...',NULL,0,0,0,0,0,0,11385,0,0,0),(10,0,'No! Not yet...',NULL,0,0,0,0,0,0,11386,0,0,0),(11,0,'Come out from the shadows! I\'ve returned to lead you against our true enemy! Shed your chains and raise your weapons against your Illidari masters!',NULL,0,0,0,0,0,0,0,0,0,0),(12,0,'Hail our leader! Hail Akama!',NULL,0,0,0,0,0,0,0,0,0,0),(13,0,'Hail Akama!',NULL,0,0,0,0,0,0,0,0,0,0),(1150,0,'%s attempts to run away in fear!','%s attempts to run away in fear!',0,0,0,0,0,0,0,0,1,18019),(2541,0,'%s calls for help!','%s calls for help!',0,0,0,0,0,0,0,0,1,18019),(29245,0,'%s has earned the achievement $a!','%s has earned the achievement $a!',0,0,0,0,0,0,0,0,1,18019);

ALTER TABLE gossip_text
	ADD COLUMN BroadcastTextID0 MEDIUMINT(6) NOT NULL DEFAULT 0 AFTER text0_1,
	ADD COLUMN BroadcastTextID1 MEDIUMINT(6) NOT NULL DEFAULT 0 AFTER text1_1,
	ADD COLUMN BroadcastTextID2 MEDIUMINT(6) NOT NULL DEFAULT 0 AFTER text2_1,
	ADD COLUMN BroadcastTextID3 MEDIUMINT(6) NOT NULL DEFAULT 0 AFTER text3_1,
	ADD COLUMN BroadcastTextID4 MEDIUMINT(6) NOT NULL DEFAULT 0 AFTER text4_1,
	ADD COLUMN BroadcastTextID5 MEDIUMINT(6) NOT NULL DEFAULT 0 AFTER text5_1,
	ADD COLUMN BroadcastTextID6 MEDIUMINT(6) NOT NULL DEFAULT 0 AFTER text6_1,
	ADD COLUMN BroadcastTextID7 MEDIUMINT(6) NOT NULL DEFAULT 0 AFTER text7_1;