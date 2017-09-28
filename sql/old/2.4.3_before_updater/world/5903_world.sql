/* Cavern of times useless flying dragons */
UPDATE creature_template SET InhabitType = 5 WHERE entry = 19918;
REPLACE INTO creature_template_addon (entry, bytes1, moveflags) values (19918,0x02000,0x01800600);
UPDATE creature SET spawndist = 0 WHERE id = 19918;