/* Akama's elementalist rain of fire timer */
UPDATE eventai_scripts SET event_chance = 100, event_param1 = 3000, event_param2 = 4000 where creature_id = 23523 AND id = 2352301;

/* Update rogue weapons */
UPDATE creature_equip_template SET equipmodel1 = 28525, equipmodel2 = 28525, equipinfo1 = 33488898, equipinfo2 = 33488898 WHERE entry =  (SELECT equipment_id FROM creature_template WHERE entry = 23318);

/*  "Akama Soul Retrieve Channel" TARGET_UNIT_NEARBY_ENTRY */
REPLACE INTO spell_script_target values (40902,1,22841);
UPDATE spell_template SET rangeIndex = 6 WHERE id = 40927;
UPDATE spell_template SET targets = 11,rangeIndex = 6, effectImplicitTargetA1 = 38 WHERE id = 40855;