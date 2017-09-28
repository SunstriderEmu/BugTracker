/* setting some battleground emissaries non attackable */
UPDATE creature_template SET unit_flags = 33088 WHERE entry = 14990 OR entry = 14991 OR entry = 15105 OR entry = 15106 OR entry = 15103  OR entry = 15102 OR entry = 22013;
