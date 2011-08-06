DROP TABLE IF EXISTS `creature_text`;
CREATE TABLE `creature_text` (
  `entry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `groupid` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `id` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `text` longtext,
  `type` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `language` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `probability` float NOT NULL DEFAULT '0',
  `emote` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `duration` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `sound` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `comment` varchar(255) DEFAULT '',
  PRIMARY KEY (`entry`,`groupid`,`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELETE FROM `command` WHERE `name` LIKE 'reload creature_text';
INSERT INTO `command` (`name`,`security`,`help`) VALUES
('reload creature_text',3,'Syntax: .reload creature_text\r\nReload creature_text table.');

UPDATE creature_template SET AIName = "SmartAI" WHERE entry = 23093;
DELETE FROM smart_scripts WHERE entryorguid IN (23093, 2309300);
INSERT INTO smart_scripts VALUES
-- (23093, 0, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2473.520996, 4699.958008, 155.471802, 0.065673, "Move to summon point on GossipHello"),
(23093, 0, 1, 0, 64, 0, 100, 0, 0, 0, 0, 0, 80, 2309300, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Run script when reaching summon point"),
-- Timed action list
(2309300, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 0"),
(2309300, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 50, 185856, 5000, 0, 0, 0, 0, 0, 0, 0, 0, -2466.338379, 4700.503906, 155.795624, 3.201742, "Summon Fetish");

DELETE FROM creature_text WHERE entry = 23093;
INSERT INTO creature_text VALUES
(23093, 0, 1, "Text 0", 0, 0, 100, 1, 0, 0, "Text 0");
