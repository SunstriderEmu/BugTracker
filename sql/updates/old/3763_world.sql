ALTER TABLE instance_encounter DROP COLUMN `comment`;
ALTER TABLE instance_encounter ADD COLUMN `name_en` varchar(100) NOT NULL default '' AFTER eventid;
ALTER TABLE instance_encounter ADD COLUMN `name_fr` varchar(100) NOT NULL default '' AFTER `name_en`;
