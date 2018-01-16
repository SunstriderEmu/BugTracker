ALTER TABLE `creature_template`   
  ADD COLUMN IF NOT EXISTS `unit_flags2` INT(10) UNSIGNED DEFAULT 0  NOT NULL AFTER `unit_flags`;
