UPDATE version SET core_version = "Winrunner Rev: 6063";

ALTER TABLE creature_formations
	ADD COLUMN linkedloot TINYINT(1) DEFAULT '0';