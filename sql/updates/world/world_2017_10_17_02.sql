
REPLACE INTO `broadcast_text` (`ID`, `Language`, `MaleText`) 
	SELECT `entry`, 0, `content_default` FROM `db_script_string`;

REPLACE INTO `locales_broadcast_text` (`ID`, `locale`, `MaleText`) 
	SELECT `entry`, "frFR", `content_loc2` FROM `db_script_string` WHERE `content_loc2` IS NOT NULL;
	