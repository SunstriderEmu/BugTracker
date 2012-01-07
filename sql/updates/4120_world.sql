UPDATE creature_addon SET bytes1 = 0 WHERE guid IN (SELECT guid FROM creature WHERE id IN (9623, 6516));
