REPLACE INTO command (name, security, help) VALUES ("path type", 3, "Syntax : .path type <pathid> [type]\nNote that this doesn't update creatures already using this path.\n\nPossible types :\n0 - PATH_TYPE_LOOP\n1 - PATH_TYPE_ONCE\n2 - PATH_TYPE_ROUND_TRIP");
REPLACE INTO command (name, security, help) VALUES ("path direction", 3, "Syntax : .path direction <pathid> [dir]\nNote that this doesn't update creatures already using this path.\n\nPossible directions :\n0 - PATH_DIRECTION_NORMAL\n1 - PATH_DIRECTION_REVERSE\n2 - PATH_DIRECTION_RANDOM");
REPLACE INTO command (name, security, help) VALUES ("npc path type", 2, "Syntax : .npc path type [PathType]\nNo arguments means print current type. This DOES NOT update values in db, use .path type to do so.\n\nPossible types :\n0 - PATH_TYPE_LOOP\n1 - PATH_TYPE_ONCE\n2 - PATH_TYPE_ROUND_TRIP");
REPLACE INTO command (name, security, help) VALUES ("npc path direction", 2, "Syntax : .npc path direction [PathDirection]\nNo arguments means print current direction. This DOES NOT update values in db, use .path direction to do so.\n\nPossible directions :\n0 - PATH_DIRECTION_NORMAL\n1 - PATH_DIRECTION_REVERSE\n2 - PATH_DIRECTION_RANDOM");
REPLACE INTO command (name, security, help) VALUES ("npc path currentid", 1, "Syntax : .npc path currentid");

DROP TABLE IF EXISTS `waypoint_info`;

CREATE TABLE `waypoint_info` (
  `id` int(10) unsigned NOT NULL,
  `pathType` smallint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'see enum PathType',
  `pathDirection` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT 'see enum PathDirection',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

REPLACE INTO waypoint_info (id, pathType) VALUES (25851, 1);
REPLACE INTO waypoint_info (id, pathType) VALUES (14241, 1);
REPLACE INTO waypoint_info (id, pathType) VALUES (24225, 1);
REPLACE INTO waypoint_info (id, pathType) VALUES (24159, 1);
REPLACE INTO waypoint_info (id, pathType) VALUES (24358, 1);
REPLACE INTO waypoint_info (id, pathType) VALUES (12949375, 1);
REPLACE INTO waypoint_info (id, pathType) VALUES (12949374, 1);