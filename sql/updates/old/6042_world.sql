UPDATE version SET core_version = "Winrunner Rev: 6042";

ALTER TABLE creature_formations
	ADD COLUMN respawn BOOL DEFAULT FALSE COMMENT "respawn when group is ooc";