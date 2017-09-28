ALTER TABLE creature_text 
	CHANGE `text_en` `text` LONGTEXT NOT NULL,
	ADD COLUMN BroadcastTextId MEDIUMINT(6) NOT NULL DEFAULT 0,
	ADD COLUMN TextRange TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,
	DROP COLUMN `text_fr`;
	

DELETE FROM `creature_text`
WHERE `entry` IN (1506, 1507, 1667);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(1506, 0, 0, 'You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.', 12, 7, 25, 0, 0, 0, 2625, 0, 'Scarlet Convert 1'),
(1506, 0, 1, 'There is no escape for you.  The Crusade shall destroy all who carry the Scourge''s taint.', 12, 7, 25, 0, 0, 0, 2626, 0, 'Scarlet Convert 2'),
(1506, 0, 2, 'The Light condemns all who harbor evil.  Now you will die!', 12, 7, 25, 0, 0, 0, 2627, 0, 'Scarlet Convert 3'),
(1506, 0, 3, 'The Scarlet Crusade shall smite the wicked and drive evil from these lands!', 12, 7, 25, 0, 0, 0, 2628, 0, 'Scarlet Convert 4'),
(1507, 0, 0, 'You carry the taint of the Scourge.  Prepare to enter the Twisting Nether.', 12, 7, 25, 0, 0, 0, 2625, 0, 'Scarlet Initiate 1'),
(1507, 0, 1, 'There is no escape for you.  The Crusade shall destroy all who carry the Scourge''s taint.', 12, 7, 25, 0, 0, 0, 2626, 0, 'Scarlet Initiate 2'),
(1507, 0, 2, 'The Light condemns all who harbor evil.  Now you will die!', 12, 7, 25, 0, 0, 0, 2627, 0, 'Scarlet Initiate 3'),
(1507, 0, 3, 'The Scarlet Crusade shall smite the wicked and drive evil from these lands!', 12, 7, 25, 0, 0, 0, 2628, 0, 'Scarlet Initiate 4'),
(1667, 0, 0, 'These lands shall be cleansed!', 12, 0, 100, 5, 0, 0, 314, 0, 'Meven Korgal - Nearby aggro'),
(1667, 1, 0, 'These undead atrocities will be destroyed!', 12, 0, 100, 5, 0, 0, 316, 0, 'Meven Korgal - Spawn'),
(1667, 2, 0, 'The Scarlet Crusade shall not fail in its mission!', 12, 0, 100, 0, 0, 0, 317, 0, 'Meven Korgal - On aggro');