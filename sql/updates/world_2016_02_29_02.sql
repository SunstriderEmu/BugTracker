ALTER TABLE `sunworld`.`creature_formations`   
  CHANGE `dist_min` `dist` FLOAT UNSIGNED DEFAULT 0  NOT NULL,
  DROP COLUMN `dist_max`;

UPDATE creature_formations SET dist = 4 WHERE dist < 4;