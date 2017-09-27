/* No reputation from akama's summoned mobs */
DELETE FROM creature_onkill_reputation WHERE creature_id IN (23421,23524,23523,23215,23318,23216);