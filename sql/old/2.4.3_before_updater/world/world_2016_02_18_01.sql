ALTER TABLE `instance_template`   
  ADD COLUMN `forceHeroicEnabled` BOOL DEFAULT 0  NOT NULL AFTER `script`;

DROP table `instance_template_addon`;  