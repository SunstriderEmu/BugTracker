RENAME TABLE `quest_mail_loot_template` TO `mail_loot_template`;

DROP TABLE IF EXISTS `quest_mail_sender`;

CREATE TABLE `quest_mail_sender` (
  `QuestId` int(5) unsigned NOT NULL DEFAULT '0',
  `RewardMailSenderEntry` int(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`QuestId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

insert into `quest_mail_sender` (`QuestId`, `RewardMailSenderEntry`) values('8729','11811');
insert into `quest_mail_sender` (`QuestId`, `RewardMailSenderEntry`) values('10588','18166');
insert into `quest_mail_sender` (`QuestId`, `RewardMailSenderEntry`) values('10966','22818');
insert into `quest_mail_sender` (`QuestId`, `RewardMailSenderEntry`) values('10967','22817');

REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`) VALUES('12115','1285','0','1','0','0','-8831.75','596.355','95.7618','0.942478','310','0','0','0','0');
