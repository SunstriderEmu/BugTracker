DELETE FROM `trinity_string` WHERE `entry` IN (301, 300);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc2`)VALUES
('300', 'Your chat has been disabled for %u minutes. Reason: %s.', 'Votre chat a été désactivé pour %u minute(s). Raison: %s'),
('301', 'You have disabled %s\'s chat for %u minutes. Reason: %s.', 'Vous avez désactivé le chat de %s pour %u minute(s). Raison: %s');
