ALTER TABLE characters ADD COLUMN `deleted` tinyint(3) unsigned NOT NULL DEFAULT '0' AFTER lastGenderChange;
ALTER TABLE characters ADD COLUMN `deleted_time` bigint(20) unsigned NOT NULL DEFAULT '0' AFTER deleted;
