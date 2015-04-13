ALTER TABLE smart_scripts
	ADD COLUMN `target_flags` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0'
	AFTER `target_type`;