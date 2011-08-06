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
DELETE FROM smart_scripts WHERE entryorguid IN (23093, 2309300, 2309301);
INSERT INTO smart_scripts VALUES
(23093, 0, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2473.520996, 4699.958008, 155.471802, 0, "Move to summon point on GossipHello"),
(23093, 0, 1, 0, 64, 0, 100, 0, 0, 0, 0, 0, 83, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Remove Gossip flag"),
(23093, 0, 2, 0, 34, 0, 100, 1, 0, 0, 0, 0, 80, 2309300, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Summon totem and talk when reaching totem summon point"),
-- Timed action list 1
(2309300, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 0"),
(2309300, 9, 1, 0, 0, 0, 100, 0, 500, 500, 0, 0, 50, 185856, 60000, 0, 0, 0, 0, 8, 0, 0, 0, -2466.338379, 4700.503906, 155.795624, 3.201742, "Summon Fetish"),
-- (2309300, 9, 3, 0, 0, 0, 100, 0, 500, 500, 0, 0, 66, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1.460915, "Set orientation to face event"), -- Display issue
(2309300, 9, 2, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2485.359375, 4668.020996, 161.187256, 1.234376, "Move to main event point"),
(2309300, 9, 3, 0, 0, 0, 100, 0, 12000, 12000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 1"),
(2309300, 9, 4, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 23096, 6, 10000, 0, 0, 0, 8, 0, 0, 0, -2488.237061, 4691.252930, 154.815414, 5.501273, "Summon Acolyte of Air"),
(2309300, 9, 5, 0, 0, 0, 100, 0, 15000, 15000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 2"),
(2309300, 9, 6, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 23097, 6, 10000, 0, 0, 0, 8, 0, 0, 0, -2488.237061, 4691.252930, 154.815414, 5.501273, "Summon Acolyte of Water"),
(2309300, 9, 7, 0, 0, 0, 100, 0, 15000, 15000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 3"),
(2309300, 9, 8, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 23098, 6, 10000, 0, 0, 0, 8, 0, 0, 0, -2488.237061, 4691.252930, 154.815414, 5.501273, "Summon Acolyte of Earth"),
(2309300, 9, 9, 0, 0, 0, 100, 0, 15000, 15000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 4"),
(2309300, 9, 10, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 23099, 6, 10000, 0, 0, 0, 8, 0, 0, 0, -2488.237061, 4691.252930, 154.815414, 5.501273, "Summon Acolyte of Fire"),
(2309300, 9, 11, 0, 0, 0, 100, 0, 15000, 15000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Say text 5"),
(2309300, 9, 12, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 12, 23100, 6, 10000, 0, 0, 0, 8, 0, 0, 0, -2488.237061, 4691.252930, 154.815414, 5.501273, "Summon Flawless Arcane Elemental"),
(2309300, 9, 13, 0, 0, 0, 100, 0, 20000, 20000, 0, 0, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2527.735107, 4661.290527, 170.488464, 3.310488, "Move to home"),
(2309300, 9, 14, 0, 0, 0, 100, 0, 20000, 20000, 0, 0, 82, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Set Gossip flag"),
(2309300, 9, 15, 0, 0, 0, 100, 0, 500, 500, 0, 0, 77, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Reset base object");

DELETE FROM creature_text WHERE entry = 23093;
INSERT INTO creature_text VALUES
(23093, 0, 0, "[PH] Pose du totem", 0, 0, 100, 1, 0, 0, "Text 0"),
(23093, 1, 0, "[PH] Acolyte de l'Air", 0, 0, 100, 1, 0, 0, "Text 1"),
(23093, 2, 0, "[PH] Acolyte de l'Eau", 0, 0, 100, 1, 0, 0, "Text 2"),
(23093, 3, 0, "[PH] Acolyte de la Terre", 0, 0, 100, 1, 0, 0, "Text 3"),
(23093, 4, 0, "[PH] Acolyte du Feu", 0, 0, 100, 1, 0, 0, "Text 4"),
(23093, 5, 0, "[PH] Elémentaire des arcanes sans défaut !", 1, 0, 100, 5, 0, 0, "Text 5");

-- DELETE FROM waypoints WHERE entry = 23093;
-- INSERT INTO waypoints VALUES
-- (23093, 1, -2508.368164, 4671.690430, 164.986343, "First point"),
-- (23093, 1, -2473.520996, 4699.958008, 155.471802, "Summon totem"),
-- (23093, 2, -2483.194336, 4668.797852, 160.338531, "Summoning elems");

UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry IN (23096, 23097, 23098, 23099, 23100);
