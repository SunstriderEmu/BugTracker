replace into `creature_equip_template` (`creatureId`, `id`, `equipmodel1`, `equipmodel2`, `equipmodel3`, `equipinfo1`, `equipinfo2`, `equipinfo3`, `equipslot1`, `equipslot2`, `equipslot3`) values('424','2','7460','2080','0','33492482','33490436','0','1805','1038','0');
replace into `creature_equip_template` (`creatureId`, `id`, `equipmodel1`, `equipmodel2`, `equipmodel3`, `equipinfo1`, `equipinfo2`, `equipinfo3`, `equipslot1`, `equipslot2`, `equipslot3`) values('1976','2','7460','2080','0','33492482','33490436','0','1805','1038','0');

UPDATE game_event_model_equip SET equipment_id = 2 WHERE equipment_id = 504;

ALTER TABLE `game_event_model_equip`   
  CHANGE `equipment_id` `equipment_id` TINYINT(1) DEFAULT 0  NOT NULL;

ALTER TABLE `creature`   
  CHANGE `equipment_id` `equipment_id` TINYINT(1) DEFAULT 0  NOT NULL;
