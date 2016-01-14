ALTER TABLE `game_event_save`   
  CHANGE `event_id` `event_id` INT(8) UNSIGNED NOT NULL;

ALTER TABLE `character_skills`   
  CHANGE `skill` `skill` INT(11) UNSIGNED NOT NULL,
  CHANGE `value` `value` INT(11) UNSIGNED NOT NULL,
  CHANGE `max` `max` INT(11) UNSIGNED NOT NULL;
