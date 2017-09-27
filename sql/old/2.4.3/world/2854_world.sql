UPDATE creature LEFT JOIN creature_template ON creature.id = creature_template.entry SET spawntimesecs = 7200 WHERE map = 580 AND rank IN (0,1);
