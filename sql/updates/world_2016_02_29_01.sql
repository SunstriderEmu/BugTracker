ALTER TABLE `sun_world`.`spell_template`   
  ADD COLUMN `customAttributesFlags` INT(11) UNSIGNED DEFAULT 0  NOT NULL AFTER `schoolMask`;
