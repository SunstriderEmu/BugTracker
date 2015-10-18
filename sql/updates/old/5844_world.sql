/* RoS triggers should not be running around */
UPDATE creature SET spawndist = 0 WHERE id = 23472;

REPLACE INTO spell_script_target values (41537,1,23472);

/* Bloodboil */
UPDATE creature_template SET minhealth = 5600000, maxhealth = 5600000 WHERE entry = 22948;